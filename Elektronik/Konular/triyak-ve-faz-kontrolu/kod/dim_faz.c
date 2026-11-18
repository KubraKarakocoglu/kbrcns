/* dim_faz.c - zamanlayıcı ve GPIO bu dosyanın DIŞINDADIR (ISR'den çağrılır) */
#include "dim_faz.h"

#include <stddef.h>

#define YARIM_MIN_US  7000u  /* 71,4 Hz üstü hat frekansı geçersiz */
#define YARIM_MAX_US 12000u  /* 41,7 Hz altı hat frekansı geçersiz */
#define DARBE_MIN_US   100u
#define DARBE_MAX_US  4000u
#define KILIT_SAYISI     4u  /* geçerli olmak için art arda iyi ölçüm */
#define KOTU_ESIK        2u  /* bu kadar art arda kötü ölçüm -> geçersiz */
#define SUZ_BOL          8   /* IIR: y += (x - y) / 8 */
#define SAPMA_BOL        8u  /* kabul penceresi: ±%12,5 */
#define N_ARALIK        32u  /* tablo aralığı sayısı; alfa_k = k * pi / N */

/* P(alfa_k) = 1 - k/N + sin(2*pi*k/N) / (2*pi), Q16 (65535 = tam güç) */
static const uint16_t k_guc_tab[N_ARALIK + 1u] = {
    65535u, 65522u, 65431u, 65186u, 64718u, 63968u, 62883u, 61429u, 59581u,
    57333u, 54692u, 51680u, 48335u, 44706u, 40855u, 36850u, 32768u, 28685u,
    24680u, 20829u, 17200u, 13855u, 10843u,  8202u,  5954u,  4106u,  2652u,
     1567u,   817u,   349u,   104u,    13u,     0u};

static bool sapma_var(uint32_t y, uint32_t x)
{
    const uint32_t fark = (x > y) ? (x - y) : (y - x);
    return fark > (y / SAPMA_BOL);
}

static uint32_t suz(uint32_t y, uint32_t x)
{
    const int32_t e = (int32_t)x - (int32_t)y; /* değerler < 2^15: taşma yok */
    return (uint32_t)((int32_t)y + (e / SUZ_BOL));
}

static void kotu_say(dim_t *d)
{
    d->iyi = 0u;
    if (d->kotu < UINT8_MAX) { d->kotu++; }
    if (d->kotu >= KOTU_ESIK) { d->gecerli = false; }
}

void dim_baslat(dim_t *d)
{
    if (d == NULL) { return; }
    d->yarim_us = 0u;
    d->darbe_us = 0u;
    d->iyi      = 0u;
    d->kotu     = 0u;
    d->gecerli  = false; /* açılışta KAPALI başla */
}

/* yarim_us: iki ardışık yükselen kenar arası; darbe_us: yükselen -> düşen kenar */
bool dim_olcum_ekle(dim_t *d, uint32_t yarim_us, uint32_t darbe_us)
{
    if (d == NULL) { return false; }

    if ((yarim_us < YARIM_MIN_US) || (yarim_us > YARIM_MAX_US) ||
        (darbe_us < DARBE_MIN_US) || (darbe_us > DARBE_MAX_US) ||
        (darbe_us >= yarim_us)) {
        kotu_say(d);
        return false;
    }

    /* ilk ölçüm ya da geçersizken sapma: yeniden kilitlen (örnek: 50 -> 60 Hz) */
    if ((d->yarim_us == 0u) || (!d->gecerli && sapma_var(d->yarim_us, yarim_us))) {
        d->yarim_us = yarim_us;
        d->darbe_us = darbe_us;
        d->iyi      = 1u;
        d->kotu     = 0u;
        return true;
    }

    if (sapma_var(d->yarim_us, yarim_us)) { /* geçerliyken tek sapma: parazit olabilir */
        kotu_say(d);
        return false;
    }

    d->yarim_us = suz(d->yarim_us, yarim_us);
    d->darbe_us = suz(d->darbe_us, darbe_us);
    d->kotu     = 0u;
    if (d->iyi < UINT8_MAX) { d->iyi++; }
    if (d->iyi >= KILIT_SAYISI) { d->gecerli = true; }
    return true;
}

/* Zaman aşımı zamanlayıcısı çağırır: 1,5 yarım periyot içinde sıfır geçiş gelmedi */
void dim_zc_kayip(dim_t *d)
{
    if (d == NULL) { return; }
    d->gecerli = false;
    d->iyi     = 0u;
    d->kotu    = KOTU_ESIK;
}

/* Dönüş: darbenin YÜKSELEN KENARINDAN tetiğe kadar geçecek süre (µs) ya da DIM_KAPALI.
 * guc_binde: 1..1000 (binde). marj_us: yarım periyodun sonundan önce bırakılacak süre
 * (kapı darbesi + mandallama payı). Geçersiz her durumda sonuç DIM_KAPALI'dır. */
uint32_t dim_gecikme_us(const dim_t *d, uint16_t guc_binde, uint32_t marj_us)
{
    if ((d == NULL) || !d->gecerli) { return DIM_KAPALI; }
    if ((guc_binde == 0u) || (guc_binde > 1000u)) { return DIM_KAPALI; } /* geçersiz -> kapalı */
    if (marj_us >= d->yarim_us) { return DIM_KAPALI; }

    const uint32_t p = (((uint32_t)guc_binde * 65535u) + 500u) / 1000u; /* Q16 */

    uint32_t k = 0u; /* k_guc_tab[k] >= p >= k_guc_tab[k+1] */
    while ((k < (N_ARALIK - 1u)) && (p < k_guc_tab[k + 1u])) { k++; }

    const uint32_t ust    = k_guc_tab[k];
    const uint32_t alt    = k_guc_tab[k + 1u];
    const uint32_t aralik = ust - alt;
    if (aralik == 0u) { return DIM_KAPALI; } /* tablo bozulduysa güvenli durum */

    const uint32_t kesir    = ((ust - p) << 16) / aralik;       /* Q16, 0..65536 */
    const uint32_t alfa_q16 = ((k << 16) + kesir) / N_ARALIK;   /* alfa/pi, Q16  */
    const uint32_t t_alfa   = (d->yarim_us * alfa_q16) >> 16;   /* µs            */

    if (t_alfa > (d->yarim_us - marj_us)) { return DIM_KAPALI; }
    return (d->darbe_us / 2u) + t_alfa;
}
