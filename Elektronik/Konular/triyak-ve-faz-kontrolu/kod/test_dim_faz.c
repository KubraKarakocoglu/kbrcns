/* test_dim_faz.c - dim_faz.c'yi doğrudan dahil eder (static tabloya erişmek için)
 * Derleme: gcc -std=c11 -Wall -Wextra -pedantic -Werror -Wconversion -Wshadow test_dim_faz.c -lm */
#include "dim_faz.c"

#include <assert.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846

static double guc_oran(double alfa) /* tam güce oranla */
{
    double p = 1.0 - alfa / PI + sin(2.0 * alfa) / (2.0 * PI);
    return (p < 0.0) ? 0.0 : p;
}

static void kilitle(dim_t *d, uint32_t yarim, uint32_t darbe)
{
    for (int i = 0; i < 4; i++) { (void)dim_olcum_ekle(d, yarim, darbe); }
}

int main(void)
{
    dim_t d;

    /* 0) tablo, formülden üretilen değerlerle aynı (±1) ve kesin azalan */
    for (uint32_t k = 0; k <= N_ARALIK; k++) {
        const double beklenen = guc_oran((double)k * PI / (double)N_ARALIK) * 65535.0;
        assert(fabs((double)k_guc_tab[k] - beklenen) <= 1.0);
        if (k < N_ARALIK) { assert(k_guc_tab[k] > k_guc_tab[k + 1u]); }
    }

    /* 1) NULL güvenliği */
    dim_baslat(NULL);
    dim_zc_kayip(NULL);
    assert(!dim_olcum_ekle(NULL, 10000u, 1300u));
    assert(dim_gecikme_us(NULL, 500u, 200u) == DIM_KAPALI);

    /* 2) açılışta kapalı; 4 iyi ölçümden önce kapalı */
    dim_baslat(&d);
    assert(dim_gecikme_us(&d, 500u, 200u) == DIM_KAPALI);
    for (int i = 0; i < 3; i++) {
        assert(dim_olcum_ekle(&d, 10000u, 1300u));
        assert(dim_gecikme_us(&d, 500u, 200u) == DIM_KAPALI);
    }
    assert(dim_olcum_ekle(&d, 10000u, 1300u));
    assert(d.gecerli);

    /* 3) %50 güç: yükselen kenardan 650 + 5000 µs */
    {
        const uint32_t g = dim_gecikme_us(&d, 500u, 200u);
        assert(g >= 5650u - 3u && g <= 5650u + 3u);
    }

    /* 4) %100: yalnız t_w (650 µs); geçersiz girişler kapalı */
    assert(dim_gecikme_us(&d, 1000u, 200u) == 650u);
    assert(dim_gecikme_us(&d, 0u, 200u) == DIM_KAPALI);
    assert(dim_gecikme_us(&d, 1001u, 200u) == DIM_KAPALI);
    assert(dim_gecikme_us(&d, 65535u, 200u) == DIM_KAPALI);

    /* 5) marj: çok düşük güç, büyük marj -> kapalı; marj >= yarım -> kapalı */
    assert(dim_gecikme_us(&d, 10u, 2000u) == DIM_KAPALI);
    assert(dim_gecikme_us(&d, 500u, 10000u) == DIM_KAPALI);

    /* 6) doğruluk ve tekdüzelik: 50 Hz ve 60 Hz */
    {
        const uint32_t yarimlar[2] = {10000u, 8333u};
        for (int h = 0; h < 2; h++) {
            dim_t e;
            dim_baslat(&e);
            kilitle(&e, yarimlar[h], 1300u);
            assert(e.gecerli);
            double en_kotu = 0.0;
            uint32_t onceki = 0u;
            for (uint16_t g = 1u; g <= 1000u; g++) {
                const uint32_t t = dim_gecikme_us(&e, g, 0u);
                assert(t != DIM_KAPALI);
                const uint32_t ta = t - (e.darbe_us / 2u);
                const double alfa = PI * (double)ta / (double)e.yarim_us;
                const double hata = fabs(guc_oran(alfa) - ((double)g / 1000.0));
                if (hata > en_kotu) { en_kotu = hata; }
                if (g > 1u) { assert(t <= onceki); } /* güç artarsa gecikme azalır */
                onceki = t;
            }
            printf("yarım=%u µs: en kötü güç hatası = %.3f %%\n", (unsigned)yarimlar[h], en_kotu * 100.0);
            assert(en_kotu < 0.0015); /* < %0,15 */
        }
    }

    /* 7) aralık dışı ölçüm: tek kötü tolere edilir, art arda iki kötü -> geçersiz */
    dim_baslat(&d);
    kilitle(&d, 10000u, 1300u);
    assert(!dim_olcum_ekle(&d, 2000u, 1300u));
    assert(d.gecerli);
    assert(!dim_olcum_ekle(&d, 8000u, 1300u)); /* aralıkta ama %20 sapma */
    assert(!d.gecerli);
    assert(dim_gecikme_us(&d, 500u, 200u) == DIM_KAPALI);

    /* 8) darbe genişliği geçersiz */
    dim_baslat(&d);
    assert(!dim_olcum_ekle(&d, 10000u, 50u));
    assert(!dim_olcum_ekle(&d, 10000u, 5000u));
    assert(!dim_olcum_ekle(&d, 10000u, 10000u));

    /* 9) sıfır geçiş kaybı -> kapalı; geri gelince 4 iyi ölçümle dönüş */
    dim_baslat(&d);
    kilitle(&d, 10000u, 1300u);
    dim_zc_kayip(&d);
    assert(dim_gecikme_us(&d, 500u, 200u) == DIM_KAPALI);
    for (int i = 0; i < 3; i++) { assert(dim_olcum_ekle(&d, 10000u, 1300u)); }
    assert(dim_gecikme_us(&d, 500u, 200u) == DIM_KAPALI);
    assert(dim_olcum_ekle(&d, 10000u, 1300u));
    assert(dim_gecikme_us(&d, 500u, 200u) != DIM_KAPALI);

    /* 10) 50 -> 60 Hz: kayıptan sonra yeniden kilitlenir */
    dim_baslat(&d);
    kilitle(&d, 10000u, 1300u);
    dim_zc_kayip(&d);
    kilitle(&d, 8333u, 1100u);
    assert(d.gecerli);
    assert(d.yarim_us == 8333u);

    /* 11) süzgeç yakınsar (±7 µs) ve sınır değerlerinde taşmaz */
    dim_baslat(&d);
    kilitle(&d, 10000u, 1300u);
    for (int i = 0; i < 200; i++) { (void)dim_olcum_ekle(&d, 10100u, 1300u); }
    assert(d.yarim_us >= 10093u && d.yarim_us <= 10100u);
    dim_baslat(&d);
    kilitle(&d, 12000u, 4000u);
    assert(d.gecerli);
    assert(dim_gecikme_us(&d, 1u, 0u) != DIM_KAPALI);
    dim_baslat(&d);
    kilitle(&d, 7000u, 100u);
    assert(d.gecerli);
    assert(dim_gecikme_us(&d, 1000u, 0u) == 50u);

    puts("TÜM TESTLER GEÇTİ");
    return 0;
}
