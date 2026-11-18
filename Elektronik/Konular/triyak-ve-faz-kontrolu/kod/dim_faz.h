/* dim_faz.h - faz kontrollü dimmer zamanlama çekirdeği (donanımdan bağımsız) */
#ifndef DIM_FAZ_H
#define DIM_FAZ_H

#include <stdbool.h>
#include <stdint.h>

#define DIM_KAPALI UINT32_MAX /* dönüş değeri: bu yarım periyotta tetik VERME */

typedef struct {
    uint32_t yarim_us; /* süzülmüş yarım periyot, µs (0 = henüz ölçülmedi) */
    uint32_t darbe_us; /* süzülmüş sıfır geçiş darbe genişliği, µs         */
    uint8_t  iyi;      /* art arda kabul edilen ölçüm sayısı (doyar)       */
    uint8_t  kotu;     /* art arda reddedilen ölçüm sayısı (doyar)         */
    bool     gecerli;  /* true: tetik üretmek serbest                      */
} dim_t;

void     dim_baslat(dim_t *d);
bool     dim_olcum_ekle(dim_t *d, uint32_t yarim_us, uint32_t darbe_us);
void     dim_zc_kayip(dim_t *d);
uint32_t dim_gecikme_us(const dim_t *d, uint16_t guc_binde, uint32_t marj_us);

#endif /* DIM_FAZ_H */
