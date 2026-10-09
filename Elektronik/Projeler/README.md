# Projeler

Her proje `NN-proje-adi/` klasöründe tutulur:

| Dosya | İçerik |
|---|---|
| `README.md` | Proje kartı: amaç, gereksinim, blok diyagram, komponent seçimi, test planı |
| `sematik-review.md` | Ana kontrol listesinin bu projeye kopyası; review sırasında işaretlenir |

Yeni proje:

```powershell
.\scriptler\Yeni-Kayit.ps1 -Tur Proje -Baslik "GPIO buton"
```

## Önerilen proje basamakları

Her basamak hem elektronik hem C tarafında bir öncekinin üzerine kurulur.

| # | Proje | Elektronik | C / Gömülü |
|---|---|---|---|
| 1 | GPIO + buton | Pull-up/down, RC debounce, LED akım direnci | GPIO register'ları, yazılımla debounce |
| 2 | ADC ile sensör okuma | Gerilim bölücü, RC filtre, referans seçimi | ADC sürücüsü, ortalama ve filtreleme |
| 3 | Sinyal koşullandırma | Köprü sensör + enstrümantasyon amfisi | Offset/kazanç kalibrasyonu, sabit noktalı aritmetik |
| 4 | Güç kaynağı | LDO ve buck karşılaştırması, verim, ripple ölçümü | Besleme izleme, düşük güç modları |
| 5 | Kendi STM32 kartın | Şematik + PCB, kontrol listesiyle tam review | Bring-up: clock, SWD, ilk firmware |

## Her projede akış

1. Proje kartını doldur (amaç ve gereksinimler kod/şematikten **önce**).
2. Şematiği çiz.
3. `sematik-review.md` ile review et; istersen Claude'a da yaptır ([istem 4](../../sablonlar/claude-istemleri.md)).
4. Kur, ölç, test planındaki tabloyu doldur.
5. Her hatayı [hatalar-dersler.md](../Sematik-Tasarim/hatalar-dersler.md) dosyasına işle.
