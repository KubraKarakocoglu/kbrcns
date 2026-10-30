/* adc_util.c — ADC yardımcı fonksiyonları
 * Ders: Elektronik/Konular/adc-ile-olcum/ozet.md
 * Host'ta test: gcc -std=c99 -Wall -Wextra -Wpedantic -Wconversion -o test_adc test_adc.c -lm && ./test_adc
 * MCU'ya taşırken: ADC_BITS, VREFINT_CAL_MV ve NTC tablosunu kendi donanımına göre değiştir. */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* ---- Ayarlar: kendi MCU'na göre değiştir ---------------------------------- */
#define ADC_BITS          12u
#define ADC_MAX_CODE      ((1u << ADC_BITS) - 1u)   /* 4095 */
#define VREFINT_CAL_MV    3000u   /* VREFINT_CAL'ın ölçüldüğü VDDA (aileye göre 3000 veya 3300) */
#define VDDA_MIN_MV       1700u   /* makullük sınırları: MCU'nun çalışma aralığı */
#define VDDA_MAX_MV       3600u

/* 1) VREFINT ile VDDA (mV). Ölçüm veya kalibrasyon değeri bozuksa false. */
bool adc_vdda_mv(uint16_t vrefint_cal, uint16_t vrefint_data, uint32_t *vdda_mv)
{
    if ((vdda_mv == NULL) || (vrefint_cal == 0u) || (vrefint_data == 0u)) {
        return false;
    }
    uint32_t v = ((uint32_t)VREFINT_CAL_MV * vrefint_cal + (vrefint_data / 2u)) / vrefint_data;
    if ((v < VDDA_MIN_MV) || (v > VDDA_MAX_MV)) {
        return false;
    }
    *vdda_mv = v;
    return true;
}

/* 2) Ham kod → mV (yuvarlamalı). */
uint32_t adc_code_to_mv(uint16_t code, uint32_t vdda_mv)
{
    if (code > ADC_MAX_CODE) {
        code = (uint16_t)ADC_MAX_CODE;
    }
    return ((uint32_t)code * vdda_mv + (ADC_MAX_CODE / 2u)) / ADC_MAX_CODE;
}

/* 3) Üstel hareketli ortalama (EMA), yalnızca tam sayı.
 *    alfa = 1/2^k ; zaman sabiti ≈ 2^k örnek. acc = y × 2^k */
typedef struct {
    uint32_t acc;
    uint8_t  k;
    bool     ready;
} ema_t;

bool ema_init(ema_t *f, uint8_t k)
{
    if ((f == NULL) || (k == 0u) || (k > 16u)) {   /* 4095 × 2^16 < 2^32 */
        return false;
    }
    f->acc = 0u;
    f->k = k;
    f->ready = false;
    return true;
}

uint16_t ema_update(ema_t *f, uint16_t x)
{
    if (x > ADC_MAX_CODE) {
        x = (uint16_t)ADC_MAX_CODE;
    }
    if (!f->ready) {                       /* ilk örnekle başlat: açılışta sıfırdan sürünmesin */
        f->acc = (uint32_t)x << f->k;
        f->ready = true;
    } else {
        f->acc = f->acc - (f->acc >> f->k) + x;
    }
    return (uint16_t)((f->acc + (1u << (f->k - 1u))) >> f->k);
}

/* 4) 5 örneğin medyanı: tek tük darbeleri (EFT, ESD) atar. */
uint16_t median5(const uint16_t in[5])
{
    uint16_t a[5];
    for (uint8_t i = 0u; i < 5u; i++) {
        a[i] = in[i];
    }
    for (uint8_t i = 1u; i < 5u; i++) {          /* insertion sort */
        uint16_t v = a[i];
        uint8_t j = i;
        while ((j > 0u) && (a[j - 1u] > v)) {
            a[j] = a[j - 1u];
            j--;
        }
        a[j] = v;
    }
    return a[2];
}

/* 5) İki noktalı kalibrasyon: ham → mühendislik birimi (ör. 0,1 %LEL). */
typedef struct {
    int32_t raw0;   /* sıfır noktasında ölçülen ham değer */
    int32_t raw1;   /* span noktasında ölçülen ham değer  */
    int32_t eng0;   /* sıfır noktasının değeri (ör. 0)      */
    int32_t eng1;   /* span noktasının değeri (ör. 500 = 50,0 %LEL) */
} cal2_t;

#define CAL2_MIN_SPAN  50   /* ham span bundan küçükse sensör/kalibrasyon şüpheli */

bool cal2_is_valid(const cal2_t *c)
{
    if (c == NULL) {
        return false;
    }
    int64_t dr = (int64_t)c->raw1 - c->raw0;              /* int64: taşma olmasın */
    return ((dr >= CAL2_MIN_SPAN) || (dr <= -CAL2_MIN_SPAN)) && (c->eng1 != c->eng0);
}

bool cal2_apply(const cal2_t *c, int32_t raw, int32_t *eng)
{
    if ((eng == NULL) || !cal2_is_valid(c)) {
        return false;
    }
    int64_t dr   = (int64_t)c->raw1 - c->raw0;
    int64_t num  = ((int64_t)raw - c->raw0) * ((int64_t)c->eng1 - c->eng0);
    int64_t half = dr / 2;
    int64_t q    = (((num < 0) == (dr < 0)) ? (num + half) : (num - half)) / dr;  /* yuvarlamalı */
    int64_t y    = q + c->eng0;
    if (y > INT32_MAX) { y = INT32_MAX; }
    if (y < INT32_MIN) { y = INT32_MIN; }
    *eng = (int32_t)y;
    return true;
}

/* 6) NTC: 10 kΩ B3950, 10 kΩ üst direnç (VDDA'ya), NTC alt tarafta, 12 bit.
 *    Tablo -20 … +85 °C, 5 °C adım; kod sıcaklıkla AZALIR. Sonuç 0,1 °C biriminde. */
#define NTC_T_MIN_X10   (-200)
#define NTC_STEP_X10    (50)
static const uint16_t ntc_lut[] = {
    3740u, 3629u, 3495u, 3337u, 3156u, 2955u, 2738u, 2510u, 2278u, 2048u, 1825u,
    1614u, 1419u, 1241u, 1081u,  940u,  815u,  707u,  613u,  532u,  462u,  401u
};
#define NTC_LUT_LEN   (sizeof(ntc_lut) / sizeof(ntc_lut[0]))
#define NTC_OPEN_CODE   4000u   /* üstü: NTC kopuk (açık devre)  */
#define NTC_SHORT_CODE    50u   /* altı: NTC kısa devre          */

typedef enum { NTC_OK = 0, NTC_OPEN, NTC_SHORT, NTC_RANGE_LOW, NTC_RANGE_HIGH, NTC_ARG_ERR } ntc_status_t;

ntc_status_t ntc_code_to_temp_x10(uint16_t code, int16_t *t_x10)
{
    if (t_x10 == NULL)          { return NTC_ARG_ERR; }
    if (code >= NTC_OPEN_CODE)  { return NTC_OPEN; }
    if (code <= NTC_SHORT_CODE) { return NTC_SHORT; }
    if (code > ntc_lut[0])      { *t_x10 = NTC_T_MIN_X10; return NTC_RANGE_LOW; }
    if (code < ntc_lut[NTC_LUT_LEN - 1u]) {
        *t_x10 = (int16_t)(NTC_T_MIN_X10 + (int32_t)(NTC_LUT_LEN - 1u) * NTC_STEP_X10);
        return NTC_RANGE_HIGH;
    }
    for (uint8_t i = 0u; i < (NTC_LUT_LEN - 1u); i++) {
        uint16_t hi = ntc_lut[i];
        uint16_t lo = ntc_lut[i + 1u];
        if ((code <= hi) && (code >= lo)) {
            int32_t span = (int32_t)hi - (int32_t)lo;             /* > 0 */
            int32_t frac = ((int32_t)hi - (int32_t)code) * NTC_STEP_X10;
            int32_t t = NTC_T_MIN_X10 + (int32_t)i * NTC_STEP_X10 + (frac + span / 2) / span;
            *t_x10 = (int16_t)t;
            return NTC_OK;
        }
    }
    return NTC_ARG_ERR;     /* buraya gelinmez */
}
