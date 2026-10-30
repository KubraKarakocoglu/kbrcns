/* test_adc.c — adc_util.c için host testleri (PC'de çalışır, MCU'da değil)
 * Derle ve çalıştır: gcc -std=c99 -Wall -Wextra -o test_adc test_adc.c -lm && ./test_adc */
#include <stdio.h>
#include <math.h>
#include "adc_util.c"
static int fails = 0;
#define CHECK(c) do { if (!(c)) { printf("FAIL line %d: %s\n", __LINE__, #c); fails++; } } while (0)
int main(void)
{
    uint32_t v = 0;
    CHECK(adc_vdda_mv(1650, 1500, &v) && v == 3300);
    CHECK(!adc_vdda_mv(1650, 0, &v));
    CHECK(!adc_vdda_mv(0, 1500, &v));
    CHECK(!adc_vdda_mv(1650, 4000, &v));          /* 1237 mV: makul değil */
    CHECK(adc_code_to_mv(4095, 3300) == 3300);
    CHECK(adc_code_to_mv(0, 3300) == 0);
    CHECK(adc_code_to_mv(5000, 3300) == 3300);      /* doyum */

    ema_t f;
    CHECK(!ema_init(&f, 0));
    CHECK(!ema_init(&f, 17));
    CHECK(ema_init(&f, 4));
    uint16_t y = ema_update(&f, 0);
    for (int i = 0; i < 16; i++) { y = ema_update(&f, 1000); }
    printf("EMA k=4 after 16 samples: %u (beklenen ~644)\n", y);
    for (int i = 16; i < 72; i++) { y = ema_update(&f, 1000); }
    printf("EMA k=4 after 72 samples: %u (beklenen ~990)\n", y);
    CHECK(y >= 985 && y <= 1000);
    for (int i = 0; i < 2000; i++) { y = ema_update(&f, 4095); }
    CHECK(y == 4095);                                /* taşma yok, tam oturma */

    uint16_t s1[5] = {10, 4095, 12, 11, 13};
    CHECK(median5(s1) == 12);
    uint16_t s2[5] = {4095, 4095, 0, 0, 7};
    CHECK(median5(s2) == 7);

    cal2_t c = {400, 2400, 0, 500};
    int32_t e = 0;
    CHECK(cal2_apply(&c, 1400, &e) && e == 250);
    CHECK(cal2_apply(&c, 400, &e) && e == 0);
    CHECK(cal2_apply(&c, 300, &e) && e == -25);
    CHECK(cal2_apply(&c, 405, &e) && e == 1);       /* 1,25 → 1 */
    CHECK(cal2_apply(&c, 406, &e) && e == 2);       /* 1,5 → 2 (yuvarlama) */
    CHECK(cal2_apply(&c, 394, &e) && e == -2);      /* -1,5 → -2 */
    cal2_t bad = {400, 420, 0, 500};
    CHECK(!cal2_apply(&bad, 410, &e));
    cal2_t neg = {2400, 400, 0, 500};               /* ters yönlü sensör */
    CHECK(cal2_apply(&neg, 1400, &e) && e == 250);

    int16_t t = 0;
    CHECK(ntc_code_to_temp_x10(4050, &t) == NTC_OPEN);
    CHECK(ntc_code_to_temp_x10(10, &t) == NTC_SHORT);
    CHECK(ntc_code_to_temp_x10(2048, &t) == NTC_OK && t == 250);
    CHECK(ntc_code_to_temp_x10(3800, &t) == NTC_RANGE_LOW);
    CHECK(ntc_code_to_temp_x10(300, &t) == NTC_RANGE_HIGH && t == 850);
    CHECK(ntc_code_to_temp_x10(2048, NULL) == NTC_ARG_ERR);
    double maxerr = 0.0; int worst = 0;
    for (int code = 401; code <= 3740; code++) {
        int16_t tx;
        if (ntc_code_to_temp_x10((uint16_t)code, &tx) != NTC_OK) { printf("unexpected status %d\n", code); fails++; continue; }
        double r = 10000.0 * code / (4095.0 - code);
        double texact = 1.0 / (1.0 / 298.15 + log(r / 10000.0) / 3950.0) - 273.15;
        double err = fabs(tx / 10.0 - texact);
        if (err > maxerr) { maxerr = err; worst = code; }
    }
    printf("NTC LUT max hata: %.3f C (kod %d)\n", maxerr, worst);
    CHECK(maxerr < 0.2);
    printf("%s (%d hata)\n", fails ? "BASARISIZ" : "TUM TESTLER GECTI", fails);
    return fails ? 1 : 0;
}
