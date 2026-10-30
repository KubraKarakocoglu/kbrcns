# ADC ile ölçüm: pratik rehber

- **Oluşturma:** 2026-10-30
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Kod:** [kod/adc_util.c](kod/adc_util.c) (derlenebilir, testli) · [kod/test_adc.c](kod/test_adc.c)
- **Bağlantılı:** [Mikrodenetleyici, ADC girişi](../../Komponentler/05-mikrodenetleyici-donanimi/ozet.md#7-adc-girişi) · [Aliasing ve anti-aliasing filtresi](../aliasing-ve-anti-aliasing-filtresi/ozet.md) · [Op-amp ve sensör ön ucu](../op-amp-ve-sensor-on-ucu/ozet.md) · [Kapasitör, bölüm 10 (RC filtre)](../../Komponentler/02-kapasitor/ozet.md#10-derinleştirme-rc-filtre-ve-aliasing) · Kontrol listesi bölüm 5–6

> Bu ders bir **iş başvuru kitabı** olarak yazıldı: tablolar, hazır hesaplar, reçeteler ve test edilmiş kod. Örneklerde MCU içindeki 12 bitlik SAR ADC (STM32 benzeri) varsayıldı. Tablodaki C_s = 8 pF ve R_ADC = 1 kΩ gibi değerler **örnektir**; kendi MCU'nun datasheet'indeki "ADC characteristics" tablosu esastır.
>
> **Okuma planı:** 1. oturum: bölüm 1–4 (temel, bit, tür, hata bütçesi) · 2. oturum: 5–7 (referans, örnekleme, giriş devreleri) · 3. oturum: 8–10 (gürültü, kalibrasyon, firmware) · 4. oturum: 11–16.

---

## ⚡ Hızlı tekrar

1. ADC bir **cetveldir**: `kod = V_giriş / V_ref × 4095` (12 bit). Cetvelin boyu referanstır; referans kayarsa her ölçüm kayar.
2. Datasheet'teki "12 bit" ile kartındaki **gerçek çözünürlük** aynı değildir. Kendi kartında gürültüyü (σ) ölç: **gürültüsüz bit ≈ N − log₂(6,6·σ)**.
3. Doğruluğu **hata bütçesi** belirler: referans + bölücü/şant toleransı + ADC hatası (TUE) + gürültü. Çoğu kartta en büyük kalem **referanstır** (VDDA = LDO toleransı).
4. VDDA'yı referans kullanıyorsan **VREFINT** kanalını ölçüp VDDA'yı hesapla ya da **oransal** ölçüm yap (NTC, köprü).
5. **Kaynak direnci ↔ örnekleme süresi:** 12 bitte ~9 zaman sabiti gerekir. Kaynak yüksek dirençliyse pine **≥ 100 nF** (yük deposu) koy ve yavaş örnekle, ya da tampon kullan.
6. **Ortalama** gürültüyü √N kadar azaltır; **4ᵏ örnek** ile k bit kazanılır (girişte ~1 LSB gürültü varsa).
7. Her kanalın **makul aralığı** olsun: açık/kısa devre bir ölçüm değeri değil, **arızadır**.
8. Doğruluk **kalibrasyonla** gelir: açılışta ADC'nin kendi kalibrasyonu, üretimde iki noktalı kalibrasyon, katsayılar CRC'li olarak Flash'ta.

## 🧮 Cep kartı

| Formül / kural | Ne zaman | Örnek |
|---|---|---|
| `LSB = V_ref / 2ᴺ` | Bir adımın gerilimi | 3,3 V, 12 bit → **0,806 mV** |
| `kod = V / V_ref × 4095` | Beklenen kod | 1,20 V @ 3,3 V → **1489** |
| `V_DDA = V_CAL × VREFINT_CAL / VREFINT_DATA` | Besleme düzeltmesi | 3,0 V × 1650 / 1500 → **3,30 V** |
| `n_τ = (N + 1) × ln 2` | ½ LSB'ye oturmak için zaman sabiti sayısı | 12 bit → **9,0** |
| `R_maks = t_s / (n_τ × C_s) − R_ADC` | En büyük kaynak direnci | 1 µs, 8 pF, 1 kΩ → **12,9 kΩ** |
| `C_ext ≥ C_s × (2^(N+1) − 1)` | Pin kapasitörü (yük deposu) | 12 bit, 8 pF → ≥ 66 nF → **100 nF** |
| `ΔV ≈ C_s × V × f_s × R` | Yüksek R + hızlı örneklemede çökme (en kötü durum) | 8 pF, 3 V, 1 kHz, 50 kΩ → **1,2 mV** |
| `oran = R2 / (R1 + R2)` · `oran hatası ≈ (1 − oran) × (t1 + t2)` | Bölücü ve toleransı | 100k/220k, %1 → **0,6875 ± %0,63** |
| `σ_ort = σ / √N` | Ortalamanın etkisi | σ 2 LSB, N 16 → **0,5 LSB** |
| `4ᵏ örnek → +k bit` | Aşırı örnekleme | 16 örnek → **+2 bit** |
| `Gürültüsüz bit = N − log₂(6,6 × σ)` | Titremeyen bit sayısı | σ 1,5 LSB → **8,7 bit** |
| `ENOB = (SINAD − 1,76) / 6,02` | Datasheet'teki dinamik çözünürlük | 70 dB → **11,3 bit** |
| `EMA: y ← y + (x − y) / 2ᵏ` · `τ ≈ 2ᵏ örnek` | Hafif dijital alçak geçiren | k = 4 → **~16 örnek** |

---

## 1. ADC ne yapar?

ADC'yi **4096 çizgili bir cetvel** gibi düşün. Cetvelin boyu **referans gerilimidir** (V_ref). Ölçtüğün gerilim bu cetvelin kaçıncı çizgisine denk geliyorsa ADC o sayıyı (kodu) verir.

```
 kod = V_giriş / V_ref × 4095        (12 bit)
 V_giriş = kod × V_ref / 4095
```

- **LSB:** İki çizgi arasındaki mesafe. 3,3 V'luk cetvelde 0,806 mV.
- **Kuantalama hatası:** Gerçek değer iki çizginin arasındaysa ADC birine yuvarlar: en fazla ±½ LSB.
- **Doyum:** Giriş V_ref'i geçerse kod 4095'te kalır; ADC "daha fazlasını" göremez. Sinyalin en yüksek değerini tam skalanın yaklaşık **%90'ında** tut.
- **Ölçek:** Bu derste ST'nin kütüphanelerinde de kullanılan `4095` (2ᴺ − 1) ölçeği kullanıldı. 4096 kullanan kaynaklarla aradaki fark 1 LSB'den küçüktür.

## 2. Bit sayısı, LSB ve gerçek çözünürlük

**LSB tablosu:**

| V_ref | 10 bit | 12 bit | 16 bit | 24 bit |
|---|---|---|---|---|
| 2,048 V | 2,00 mV | 500 µV | 31,3 µV | 0,122 µV |
| 2,5 V | 2,44 mV | 610 µV | 38,1 µV | 0,149 µV |
| 3,0 V | 2,93 mV | 732 µV | 45,8 µV | 0,179 µV |
| 3,3 V | 3,22 mV | 806 µV | 50,4 µV | 0,197 µV |
| 5,0 V | 4,88 mV | 1,22 mV | 76,3 µV | 0,298 µV |

**"12 bit" ne kadar gerçek?** Kart gürültüsü, referans gürültüsü ve ADC'nin kendi gürültüsü yüzünden aynı gerilimi ölçerken kod birkaç LSB oynar. Bu oynamanın standart sapmasına **σ** (LSB cinsinden) dersek:

| σ (LSB rms) | Gürültüsüz bit (titremeyen) | Etkin çözünürlük (rms) |
|---|---|---|
| 1,0 | 9,3 bit | 12,0 bit |
| 1,5 | 8,7 bit | 11,4 bit |
| 2,0 | 8,3 bit | 11,0 bit |
| 3,0 | 7,7 bit | 10,4 bit |

- **Gürültüsüz bit** `= N − log₂(6,6σ)`: ekranda titremeden duran bit sayısı (tepe-tepe gürültü ≈ 6,6σ).
- **Etkin çözünürlük** `= N − log₂(σ)`: ortalama alındığında kullanılabilecek çözünürlük.
- Datasheet'teki **ENOB** dinamik testten gelir: `ENOB = (SINAD − 1,76) / 6,02`. Örneğin 70 dB SINAD → 11,3 bit.

> **Kural:** Bir ölçümün kaç bit "işe yarar" verdiğini datasheet değil, **kendi kartındaki σ** söyler (ölçüm yöntemi: bölüm 14).

## 3. ADC türleri ve seçim

| Tür | Hız | Çözünürlük | Nerede | Not |
|---|---|---|---|---|
| **MCU içi SAR** | 0,1–5 MSPS | 10–12 bit | Besleme, pil, NTC, akım, çoğu sensör | Ucuz, çok kanallı; gürültüsü kart düzenine bağlı |
| **Harici SAR** | 100 kSPS – birkaç MSPS | 12–18 bit | Hızlı ve hassas ölçüm | SPI; kendi referansı |
| **Σ-Δ (sigma-delta)** | 10 SPS – birkaç kSPS | 16–24 bit | Köprü (pellistor, yük hücresi), termokupl, yavaş sensörler | Çoğunda dahili **PGA** (programlanabilir kazanç) ve 50/60 Hz bastıran filtre |

Örnek parça aileleri (seçimden önce datasheet'e bak): **ADS1115** (16 bit, I²C, PGA), **MCP342x** (18 bit Σ-Δ, I²C, PGA ×1–8), **ADS1220** (24 bit Σ-Δ, PGA ×1–128, köprü ölçümü için), **HX711** (24 bit, tartı köprüleri).

### Kaç bit gerekir? (bit bütçesi)

1. **Adım sayısı** = ölçüm aralığı / istenen çözünürlük → `bit = log₂(adım)`.
2. **Marj ekle:** gürültü, hata ve kalibrasyon için +2…3 bit.
3. **Kullanılmayan aralık:** Sinyal ADC aralığının yalnızca bir kısmını kullanıyorsa kayıp `= log₂(tam skala / sinyal aralığı)` bit.
4. Toplamı ADC'nin **kendi kartındaki gürültüsüz bit** sayısıyla karşılaştır.

**Örnek – gaz ölçümü (varsayım: köprü çıkışı 100 %LEL'de 60 mV; kendi sensörünün değerini kullan):**
- İstenen çözünürlük 0,5 %LEL → 200 adım → 7,6 bit; marjla **~10,6 bit** (sinyal aralığı içinde).
- **Köprüyü doğrudan 12 bit, 3,3 V'luk ADC'ye bağlarsan:** 60 mV = 74 LSB → **1,34 %LEL/LSB** ✗. Gürültü ±1–2 LSB ise okuma ±2 %LEL oynar.
- **×40 kazançla:** 2,4 V = 2979 LSB → 0,034 %LEL/LSB ✓. Ama op-amp'ın ofseti de 40 kat büyür ([Op-amp dersi, bölüm 5](../op-amp-ve-sensor-on-ucu/ozet.md#5-dc-hatalar-ofset-bias-akımı-direnç-toleransı)).
- **Ya da PGA'lı 24 bit Σ-Δ ADC:** Harici yükselteç gerekmez; köprü beslemesi ADC referansı olarak kullanılırsa ölçüm oransal olur.
- Üretim testindeki kabul toleransı ±2,5 %LEL ise ölçüm zincirinin kendi hatası bunun **küçük bir kısmı** (ör. ±0,5 %LEL) olmalı; yoksa iyi cihazlar testten kalır, kötüler geçer.

## 4. Hata kaynakları ve hata bütçesi

| Hata | Ne demek | Dahili 12 bit ADC'de tipik | Nasıl azaltılır |
|---|---|---|---|
| **Ofset** | Sıfırda kayma | ±1–2 LSB | Kalibrasyon |
| **Kazanç** | Eğimin hatası (tam skalada en büyük) | ±1–3 LSB | Kalibrasyon |
| **INL / DNL** | Doğrusallıktan sapma / adımların eşitsizliği | ±1–2,5 LSB | Kalibrasyonla tam düzelmez |
| **TUE** | Toplam ayarlanmamış hata (hepsi birden) | ±2–5 LSB | Datasheet'ten al |
| **Gürültü** | Ölçümden ölçüme oynama | 0,5–3 LSB rms (karta bağlı) | Ortalama, layout |
| **Referans** | Cetvelin kendi hatası | VDDA = LDO ±%1–2 | VREFINT, referans IC, oransal ölçüm |
| **Bölücü / şant** | Direnç toleransı ve sıcaklık katsayısı | %1 direnç → bölücüde ±%0,6 | %0,1 direnç, kalibrasyon |
| **Sıcaklık** | Hepsinin sıcaklıkla değişmesi | — | Sıcaklık testi, düşük TCR'li parçalar |

**Toplama yöntemi:**
- **En kötü durum:** hatalar toplanır. Güvenlikle ilgili ölçümlerde (alarm eşiği) bunu kullan.
- **RSS:** `√(e1² + e2² + …)`. Hatalar birbirinden bağımsızsa gerçekçi tipik değer.

### Örnek 1 – Pil gerilimi (Li-ion, en çok 4,2 V)

Bölücü 100 kΩ / 220 kΩ (oran 0,6875 → 4,2 V'ta 2,89 V), 12 bit ADC, referans VDDA = 3,3 V (LDO).

| Kalem | Hesap | Hata |
|---|---|---|
| Referans (LDO ±%1,5) | — | ±%1,5 |
| Bölücü (%1 dirençler) | (1 − 0,6875) × %2 | ±%0,63 |
| ADC TUE ±4 LSB | 4 / 3583 kod | ±%0,11 |
| **Toplam, en kötü** | toplam | **±%2,2 → 4,2 V'ta ±94 mV** |
| **Toplam, RSS** | karekök | ±%1,6 → ±68 mV |

**İyileştirme adımları ve etkisi (en kötü durum):**

| Adım | Toplam hata | 4,2 V'ta |
|---|---|---|
| Başlangıç | ±%2,2 | ±94 mV |
| + VREFINT ile VDDA düzeltmesi (referans ~±%0,5 varsayımı) | ±%1,2 | ±52 mV |
| + %0,1 dirençler | ±%0,7 | ±28 mV |
| + Üretimde iki noktalı kalibrasyon | Gürültü ve sıcaklık kayması kalır | birkaç mV |

> Li-ion pilin gerilimi kullanım süresinin büyük kısmında dar bir aralıkta (~3,6–3,9 V) kalır; ±94 mV, kalan kapasite tahmininde çok büyük bir hata demektir.

### Örnek 2 – Akım izleme (şant direnci, 150 mA)

| Seçenek | V @ 150 mA | Kod (12 bit, 3,3 V) | Çözünürlük | Şant gücü |
|---|---|---|---|---|
| 0,1 Ω | 15 mV | 19 | 8,1 mA/kod | 2,2 mW |
| 0,82 Ω | 123 mV | 153 | 0,98 mA/kod | 18 mW |
| 0,1 Ω + ×50 akım algılama yükselteci | 750 mV | 931 | 0,16 mA/kod | 2,2 mW |
| 2,2 Ω | 330 mV | 410 | 0,37 mA/kod | 50 mW (yüke 0,33 V düşüm) |

- **Kaba izleme** (kopuk mu, kısa devre mi?) için ~1 mA/kod yeterlidir.
- **Hassas ölçüm** için büyük şant yerine küçük şant + akım algılama yükselteci: hem kayıp hem yükteki gerilim düşümü küçük kalır.

## 5. Referans gerilimi: cetvelin kendisi

| Seçenek | Doğruluk | Ne zaman |
|---|---|---|
| VDDA (LDO çıkışı) | ±%1–2, gürültülü | Kaba ölçümler, oransal ölçümler |
| VDDA + **VREFINT düzeltmesi** | ~±%0,5 (aileye göre) | Pil, besleme, mutlak gerilim ölçümleri |
| Harici referans IC (ör. 2,5 V) | ±%0,05–0,2; düşük kayma | Hassas mutlak ölçüm |
| **Oransal (ratiometric)** | Besleme hatası iptal | NTC, köprü, potansiyometre |

### VREFINT ile VDDA hesabı

MCU'nun içinde, beslemeden bağımsız kararlı bir referans (VREFINT, ~1,2 V) vardır. Üretici onu fabrikada ölçüp sonucunu (**VREFINT_CAL**) belleğe yazar.

1. VREFINT kanalını ölç: **VREFINT_DATA**. Bu kanal için datasheet'te **en kısa örnekleme süresi** yazar (birkaç µs, ör. 4–10 µs); kısa tutarsan değer yanlış çıkar.
2. VREFINT_CAL'ı datasheet'te verilen adresten oku.
3. `VDDA = V_CAL × VREFINT_CAL / VREFINT_DATA`. **V_CAL** kalibrasyonun yapıldığı VDDA'dır; aileye göre **3,0 V veya 3,3 V** (datasheet'te yazar).
4. Diğer kanallar: `V = VDDA × kod / 4095`.

**Örnek:** VREFINT_CAL = 1650 (3,0 V'ta alınmış), şimdi VREFINT_DATA = 1500 → `VDDA = 3,0 × 1650 / 1500 = 3,30 V`.

- VREFINT de gürültülüdür: 16 örnek ortala, saniyede bir güncelle.
- Hesaplanan VDDA'yı **makullük** kontrolünden geçir (ör. 1,7–3,6 V dışı → hata).
- **Oransal ölçümlerde bu düzeltme gerekmez:** NTC bölücüsü VDDA'dan besleniyorsa VDDA hem sinyalde hem cetvelde bulunur ve kendini götürür.
- Aynı yöntem MCU'nun dahili sıcaklık sensöründe de kullanılır (TS_CAL1/TS_CAL2). Kalibrasyon verileri V_CAL'da alındığı için ölçümü bu gerilime ölçekle.

Kod: [kod/adc_util.c](kod/adc_util.c) → `adc_vdda_mv()`, `adc_code_to_mv()`.

## 6. Örnekleme süresi ve kaynak direnci

ADC örnekleme anında içindeki küçük bir kapasitörü (**C_s**) girişe bağlar ve onun **½ LSB içinde dolmasını** bekler. Kapasitör kaynak direnci + ADC'nin iç direnci (R_ADC) üzerinden dolar.

**Kaç zaman sabiti gerekir?** `n_τ = (N + 1) × ln 2`

| Bit | 8 | 10 | 12 | 14 | 16 |
|---|---|---|---|---|---|
| n_τ | 6,2 | 7,6 | **9,0** | 10,4 | 11,8 |

**En büyük kaynak direnci** (12 bit, C_s = 8 pF, R_ADC = 1 kΩ örnek değerleriyle): `R_maks = t_s / (9,0 × C_s) − R_ADC`

| Örnekleme süresi t_s | 0,25 µs | 0,5 µs | 1 µs | 2 µs | 5 µs | 10 µs | 20 µs |
|---|---|---|---|---|---|---|---|
| R_maks | 2,5 kΩ | 5,9 kΩ | **12,9 kΩ** | 26,7 kΩ | 68 kΩ | 138 kΩ | 276 kΩ |

Datasheet'te genelde örnekleme süresine göre izin verilen R_AIN tablosu bulunur; varsa onu kullan.

### Pin kapasitörü: yük deposu

Kaynak çok yüksek dirençliyse pine bir **dış kapasitör** konur. Örnekleme kapasitörü yükünü bu kapasitörden alır; hata, kapasitörlerin oranı kadardır.

| Bit | C_ext en az (C_s = 8 pF) | Pratik değer |
|---|---|---|
| 10 | 16 nF | 22 nF |
| 12 | 66 nF | **100 nF** |
| 14 | 262 nF | 330 nF |
| 16 | 1,05 µF | 1–2,2 µF |

12 bitte 100 nF ile kalan hata en kötü durumda **~0,33 LSB**'dir.

**Ama dikkat – yüksek direnç + hızlı örnekleme:** Dış kapasitör her örnekte biraz boşalır ve kaynak direnci üzerinden yavaşça dolar. Ortalama çekilen akım gerilimi düşürür: `ΔV ≈ C_s × V × f_s × R` (en kötü durum: kanallar arasında tam salınım).

| f_s \ R | 10 kΩ | 50 kΩ | 100 kΩ |
|---|---|---|---|
| 100 Hz | 0,03 LSB | 0,15 LSB | 0,3 LSB |
| 1 kHz | 0,3 LSB | **1,5 LSB** | 3,0 LSB |
| 10 kHz | 3,0 LSB | 15 LSB | 30 LSB |

**Kural:** Kaynak direnci yüksekse (pil bölücüsü, NTC) ya **yavaş örnekle** ya da **tampon (op-amp)** kullan.

**Kanal değiştirince ilk örnek:** Örnekleme kapasitörü bir önceki kanalın gerilimini taşır. Yüksek dirençli bir kanala geçince ilk örnek ona doğru çekilir. İlk örneği **at** veya o kanalın örnekleme süresini uzat.

## 7. Giriş devresi reçeteleri

### 7.1 Gerilim bölücü: pil ve besleme rayları

1. **Oran:** En yüksek giriş, ADC tam skalasının ~%90'ını geçmesin (4,2 V → ≤ ~3,0 V → oran ≤ 0,71).
2. **Toplam direnç:** Akım tüketimi ↔ kaynak direnci dengesi.
3. **Pin kapasitörü** bölüm 6'ya göre (12 bit → 100 nF).
4. Bölücü dış dünyaya bağlıysa koruma (seri direnç + kenetleme).

**Pil bölücüsü tablosu (oran 0,6875, 4,2 V):**

| R1 / R2 | Sürekli akım | Yılda tüketim | 2 Ah pilde yıllık | Kaynak direnci | Yorum |
|---|---|---|---|---|---|
| 10k / 22k | 131 µA | 1150 mAh | %57 ✗ | 6,9 kΩ | Pilli cihazda kabul edilemez |
| 100k / 220k | 13 µA | 115 mAh | %5,7 | 69 kΩ | Çoğu cihaz için makul; yavaş örnekle |
| 1M / 2,2M | 1,3 µA | 11,5 mAh | %0,6 | 688 kΩ | Pin kaçak akımı ciddi hata yapar ✗ |

- **MΩ'luk bölücü tuzağı:** Pinin kaçak akımı (datasheet'te I_lkg; en kötü durumda µA mertebesinde) 688 kΩ üzerinde yüzlerce mV hata yaratabilir.
- **Anahtarlı bölücü:** Bölücüyü yalnızca ölçüm anında açan bir **P-MOSFET** (yüksek taraf) ile tüketim neredeyse sıfıra iner. P-MOSFET'i MCU pininden doğrudan değil, küçük bir N-MOSFET üzerinden sür: 3,3 V'luk pin, kaynağı 4,2 V'ta olan bir P-MOSFET'i tam kapatamaz. Anahtarı alt tarafa koyma: kapalıyken ADC pini pil gerilimine çıkar.

### 7.2 Akım ölçümü: şant

- **Alt taraf (low-side) şant:** Şant yük ile GND arasında; ölçüm basit, ama yükün toprağı şant gerilimi kadar kayar.
- **Üst taraf (high-side):** Yükün toprağı bozulmaz; **akım algılama yükselteci** gerekir.
- Şant ölçüm izlerini **Kelvin** bağla; ölçüm hattına RC filtre koy.
- Seçim tablosu: bölüm 4, örnek 2.

### 7.3 NTC ile sıcaklık

```
 VDDA ──[R_f 10 kΩ]──┬── ADC pini (+ 100 nF)
                     │
                   [NTC 10 kΩ @25 °C, B = 3950]
                     │
                    GND
```

- **Oransaldır:** VDDA hem bölücüde hem cetvelde → VDDA'nın hatası iptal olur.
- NTC direnci: `R_NTC = R_f × kod / (4095 − kod)`
- Sıcaklık (B modeli): `T = 1 / (1/298,15 + ln(R_NTC / R_25) / B) − 273,15`
- **R_f'yi**, en önemli sıcaklık aralığının ortasındaki NTC direncine eşit seç; duyarlılık orada en yüksektir.

**Tablo (10 kΩ B3950 + 10 kΩ, 12 bit):**

| T (°C) | R_NTC (kΩ) | V (3,3 V'ta) | Kod | Çözünürlük (°C/LSB) |
|---|---|---|---|---|
| −20 | 105,4 | 3,014 | 3740 | 0,050 |
| −10 | 58,3 | 2,816 | 3495 | 0,034 |
| 0 | 33,6 | 2,543 | 3156 | 0,026 |
| 10 | 20,2 | 2,206 | 2738 | 0,022 |
| 20 | 12,5 | 1,836 | 2278 | 0,022 |
| 25 | 10,0 | 1,650 | 2048 | 0,022 |
| 30 | 8,04 | 1,470 | 1825 | 0,023 |
| 40 | 5,30 | 1,143 | 1419 | 0,027 |
| 50 | 3,59 | 0,871 | 1081 | 0,033 |
| 60 | 2,49 | 0,657 | 815 | 0,043 |
| 70 | 1,76 | 0,494 | 613 | 0,057 |
| 80 | 1,27 | 0,372 | 462 | 0,077 |

- **Asıl hata NTC'nin kendisinden gelir:** ±%1 R25 toleransı 25 °C'de ~±0,23 °C demektir. B toleransı 25 °C'den uzaklaştıkça hatayı büyütür.
- **Kendi kendine ısınma:** 25 °C'de NTC'de ~0,27 mW harcanır; tipik 1–2 mW/°C ısı yayma sabitiyle ~0,1–0,3 °C hata.
- **Arıza:** NTC kopuksa kod ~4095'e, kısa devreyse ~0'a gider. Bunlar "−40 °C" veya "+150 °C" değil, **arızadır**.
- Firmware'de `log()` yerine **tablo + doğrusal ara değer** kullanılabilir: 5 °C adımlı tabloyla hata < 0,2 °C. Kod: `ntc_code_to_temp_x10()`.

### 7.4 4–20 mA girişi

```
 Döngü + ──[PTC / akım sınırlayıcı]──┬──[ R_şant 150 Ω, %0,1 ]── Döngü −  (GND)
                                     │
                                  [TVS]──[RC]── ADC pini
```

| Döngü akımı | Şant gerilimi | Kod (12 bit, 3,3 V) | Anlamı |
|---|---|---|---|
| 3,6 mA | 0,54 V | 670 | Arıza alt sınırı (NAMUR NE 43: ≤ 3,6 mA) |
| 4 mA | 0,60 V | 745 | Ölçüm 0 |
| 12 mA | 1,80 V | 2234 | Ölçüm %50 |
| 20 mA | 3,00 V | 3723 | Ölçüm %100 |
| 21 mA | 3,15 V | 3909 | Arıza üst sınırı (NE 43: ≥ 21 mA) |
| 22 mA | 3,30 V | 4095 | ADC doyumu |

- **Çözünürlük:** 16 mA'lik aralık ~2980 koda yayılır → **5,4 µA/kod** (~%0,03).
- **Şant gücü:** 20 mA'de 60 mW. **Ama** girişe yanlışlıkla 24 V doğrudan gelirse 150 Ω'da **3,84 W** harcanır. PTC veya akım sınırlayıcı ve TVS şart; şant da en az 0,25–0,5 W olsun.
- 3,6 mA altı ve 21 mA üstü **arıza** olarak raporlanır (sensör kopuk, kablo kısa devre).

### 7.5 Köprü (pellistor ve benzeri)

- Ayrıntı: [Op-amp ve sensör ön ucu, bölüm 7–9](../op-amp-ve-sensor-on-ucu/ozet.md#7-köprü-devresi-ve-pellistor).
- **Seçenek A:** INA veya op-amp ile kazanç + dahili ADC (bit bütçesi: bölüm 3).
- **Seçenek B:** PGA'lı Σ-Δ ADC (16–24 bit). Köprü beslemesi ADC referansı olarak kullanılırsa ölçüm oransaldır ve besleme dalgalanması ölçüme girmez. Σ-Δ ADC'nin 50 Hz bastıran filtre ayarını şebeke frekansına göre seç.

### 7.6 Ortam ışığı (LDR / fototransistör)

- LDR bir bölücünün bir kolunda; direnç ışıkla **logaritmik** değişir (karanlıkta MΩ, aydınlıkta kΩ).
- Eşik kararlarında **histerezis** kullan (ör. "karanlık" için açılma eşiği ≠ kapanma eşiği); yoksa alacakaranlıkta lamba yanıp söner.
- Işık yavaş değişir: güçlü ortalama (EMA, k = 5–6) uygundur. Lambanın kendi ışığının sensöre düşmesini mekanik olarak engelle.

### 7.7 Şebeke potansiyelindeki kartlar (izolasyonsuz)

Nötrsüz bir dimmer gibi kartlarda devre genelde doğrudan şebekeye bağlıdır: **MCU'nun GND'si, ADC girişleri ve debug konnektörü şebeke potansiyelindedir.**

- Topraklı bir osiloskobun GND klipsini böyle bir karta takmak **kısa devre ve tehlike** demektir. **İzolasyon trafosu, diferansiyel prob** ve debugger/PC için **USB izolatörü** kullan.
- Şebekeyi ADC ile ölçmek gerekiyorsa (sıfır geçiş, faz açısı): gerilim dayanımı için **seri birkaç direnç** (tek bir küçük paket direnç yüzlerce volta dayanmaz), yeterli creepage ve pinde kenetleme ile akım sınırı.
- Sıfır geçiş algılama için çoğu zaman ADC yerine **karşılaştırıcı veya kesme pini** daha hızlı ve güvenilirdir.
- Ayrıntılı mesafe kuralları: [PCB yerleşim dersi, bölüm 6](../pcb-yerlesim-ve-iz-cizimi/ozet.md#6-mesafeler-clearance-ve-creepage).

## 8. Gürültü, ortalama ve aşırı örnekleme

**Ortalama:** N örneğin ortalaması gürültüyü √N kadar azaltır.

| N | 4 | 16 | 64 | 256 |
|---|---|---|---|---|
| Gürültü çarpanı | 0,50 | 0,25 | 0,125 | 0,0625 |

**Aşırı örnekleme ile bit kazanma:** 4ᵏ örneği topla ve sonucu k bit sağa kaydır → k ek bit. **Şartlar:** girişte ~1 LSB civarında gürültü olmalı (yoksa her örnek aynı çıkar) ve sinyal bu süre içinde değişmemeli.

| Ek bit (k) | Örnek sayısı (4ᵏ) | Çıkış hızı (f_s = 10 kHz) |
|---|---|---|
| 1 | 4 | 2,5 kHz |
| 2 | 16 | 625 Hz |
| 3 | 64 | 156 Hz |
| 4 | 256 | 39 Hz |

**Hangi dijital filtre?**

| Filtre | Ne yapar | Bellek | Ne zaman |
|---|---|---|---|
| Blok ortalama | N örnek topla, böl | 1 toplam | Periyodik ölçüm; 50 Hz için 20 ms'lik blok ([Aliasing dersi](../aliasing-ve-anti-aliasing-filtresi/ozet.md)) |
| Kayan ortalama | Son N örneğin ortalaması | N örnek | Her örnekte güncel çıktı |
| **EMA** (üstel) | `y ← y + (x − y)/2ᵏ` | 1 değişken | En hafif, en yaygın alçak geçiren |
| **Medyan** (3 veya 5) | Ortadaki değer | 3–5 örnek | Tek tük darbeleri (EFT, ESD) atmak |

**EMA ayar tablosu** (f_s = 1 kHz):

| k | α | Zaman sabiti | %99'a oturma | −3 dB frekansı |
|---|---|---|---|---|
| 2 | 1/4 | 3,5 örnek (3,5 ms) | 16 örnek | 46 Hz |
| 3 | 1/8 | 7,5 örnek | 34 örnek | 21 Hz |
| 4 | 1/16 | 15,5 örnek | 71 örnek | 10,3 Hz |
| 5 | 1/32 | 31,5 örnek | 145 örnek | 5,1 Hz |
| 6 | 1/64 | 63,5 örnek | 292 örnek | 2,5 Hz |

Güvenilir bir zincir: **medyan (darbeleri at) → EMA veya blok ortalama (gürültüyü azalt)**. Kod: `median5()`, `ema_update()`.

## 9. Kalibrasyon

**ADC'nin kendi kalibrasyonu:** Birçok MCU ailesinde ADC'nin ofsetini ölçen dahili bir kalibrasyon komutu vardır. Açılışta, ADC etkinleştirilmeden önce çalıştır; sıcaklık veya VDDA çok değiştiyse tekrarla.

**Ürün kalibrasyonu:**
- **Tek nokta (ofset):** Sıfır noktasında ölç, farkı çıkar.
- **İki nokta (ofset + kazanç):** `y = y0 + (x − x0) × (y1 − y0) / (x1 − x0)`
  - Noktaları kullanılan aralığa yay: sıfır ve aralığın üst kısmı (ör. tam skalanın %50'si).
  - Ham span (x1 − x0) çok küçükse sensör ölmüş veya kalibrasyon hatalıdır → **reddet**.
- **Saklama:** Katsayılar Flash'ta sürüm numarası ve **CRC** ile. Açılışta CRC ve makullük kontrolü; bozuksa cihaz **arıza** bildirmeli, varsayılan katsayılarla sessizce çalışmamalı.
- Kalibrasyon sonuçlarını seri numarasıyla kaydet; kayma eğilimi sensör ömrü hakkında bilgi verir.

Kod: `cal2_apply()` (yuvarlamalı, 64 bit ara hesap, geçersiz kalibrasyonu reddeder).

## 10. Firmware: sağlam ölçüm kodu

1. **ADC'yi timer tetiklesin, sonuçlar DMA ile gelsin.** f_s sabit kalır ([Aliasing dersi, bölüm 9](../aliasing-ve-anti-aliasing-filtresi/ozet.md#9-firmware-tarafı)).
2. **Kanal başına örnekleme süresi:** yüksek dirençli kanala (pil, NTC, VREFINT) uzun, düşük dirençliye kısa.
3. **İlk örneği at** (kanal değişimi, ADC açılışı).
4. **Makullük kontrolü her kanalda:**

| Kanal | Normal aralık (örnek) | Aralık dışı demek ki |
|---|---|---|
| VDDA (VREFINT'ten) | 3,1–3,5 V | Besleme veya ölçüm arızası |
| NTC | kod 401–3740 (−20…85 °C) | > 4000 kopuk, < 50 kısa devre |
| 4–20 mA | 3,8–20,5 mA | ≤ 3,6 mA veya ≥ 21 mA arıza |
| Isıtıcı / yük akımı | Nominalin ±%30'u | Kopuk veya kısa devre |
| Sensör köprüsü | Kalibre aralık ± marj | Sensör kopuk veya zehirlenmiş |

5. **Arıza = güvenli durum:** Aralık dışı ölçüm "0" ya da "temiz hava" gibi gösterilmez; arıza olarak raporlanır ve gerekirse arıza rölesi bırakılır.
6. **Gürültülü olaylarla zamanlama:** Röle, buzzer veya ısıtıcı PWM'i anahtarlanırken ölçüm alma; mümkünse ölçümü bu olaylardan uzak, sabit bir anda yap.

**Test edilmiş kod:** [kod/adc_util.c](kod/adc_util.c) içinde:

| Fonksiyon | Ne yapar |
|---|---|
| `adc_vdda_mv()` | VREFINT ile VDDA (mV); bozuk ölçümü reddeder |
| `adc_code_to_mv()` | Ham kod → mV (yuvarlamalı, doyumlu) |
| `ema_init()` / `ema_update()` | Tam sayı EMA; ilk örnekle başlar |
| `median5()` | 5 örneğin medyanı |
| `cal2_is_valid()` / `cal2_apply()` | İki noktalı kalibrasyon |
| `ntc_code_to_temp_x10()` | NTC kodu → 0,1 °C; kopuk/kısa devre durumu döner |

Kod `gcc -std=c99 -Wall -Wextra -Wpedantic -Wconversion` ile uyarısız derlendi; [kod/test_adc.c](kod/test_adc.c) içindeki testlerden geçti (NTC tablosunun B modeline göre en büyük hatası 0,18 °C). MCU'ya taşırken yalnızca `ADC_BITS`, `VREFINT_CAL_MV` ve NTC tablosunu kendi değerlerine göre değiştir.

**Örnek – VDDA düzeltmeli gerilim okuma:**

```c
uint32_t vdda_mv;
if (adc_vdda_mv(*VREFINT_CAL_ADDR, vrefint_avg, &vdda_mv)) {   /* adres datasheet'te */
    uint32_t vbat_mv = adc_code_to_mv(vbat_code, vdda_mv) * 320u / 220u;  /* bölücü 100k/220k */
    /* ... */
} else {
    fault_set(FAULT_VDDA);   /* projendeki arıza fonksiyonu: ölçüm güvenilmez → arıza */
}
```

## 11. Şematikte

- Her ADC kanalının yanına not: **ne ölçüyor, beklenen aralık, bölücü oranı, kaynak direnci, filtre f_c**.
- VDDA ve VREF+ pinlerinde datasheet'in dekuplaj önerisi (tipik 100 nF + 1 µF); VDDA'ya gerekiyorsa ferrit veya LC filtre.
- Pil ve besleme bölücülerinde akım tüketimi notu; pilli üründe anahtarlı bölücü değerlendirildi.
- 4–20 mA, sensör ve dış dünyaya açık girişlerde koruma (seri R/PTC, TVS, kenetleme).
- Hassas ölçümler için referans seçimi (VDDA, VREFINT düzeltmeli, harici referans, oransal) yazılı.
- Her ölçüm zincirinde bir test noktası.

## 12. PCB / layout

- ADC izleri kısa; anahtarlamalı regülatör, bobin, röle ve dijital hatlardan uzak.
- RC filtrenin kapasitörü ve pin kapasitörü **ADC pininin dibinde**; GND bağlantısı kısa.
- VDDA/VREF+ dekuplajı pine en yakın; dönüşü analog bölgede.
- **ADC pinine komşu pinlerde** ölçüm sırasında hızlı anahtarlama yapma (PWM, saat); pinler arası kuplaj ölçüme karışır.
- Yüksek akım dönüşleri (ısıtıcı, röle) ölçüm bölgesinin altından geçmesin ([PCB yerleşim dersi](../pcb-yerlesim-ve-iz-cizimi/ozet.md#4-toprak-ve-dönüş-akımı-pratik-özet)).
- Şebeke potansiyelindeki bölgeler ile düşük gerilim arasında mesafe ve yarıklar (bölüm 7.7).

## 13. EMC açısından

- RF bağışıklık testinde ADC okumasının kayması çoğu zaman **RF doğrultma** veya **aliasing**'dendir: girişte küçük C0G kapasitör, ferrit ve örnekleme frekansının seçimi ([Aliasing dersi, bölüm 12](../aliasing-ve-anti-aliasing-filtresi/ozet.md#12-emc-açısından)).
- EFT ve ESD tek tük ölçüm sıçramaları üretir: **medyan filtre** ve makullük kontrolü bunları ayıklar.
- Test sırasında okumanın en çok ne kadar kaydığı **performans kriterini** belirler ([EMC 03](../../EMC/03-emc-testleri-ve-standartlar/ozet.md)).

## 14. Ölçüm ve doğrulama: kendi ADC'ni tanı

1. **Gürültü testi:** Girişe sabit bir gerilim ver (pil + bölücü veya hassas kaynak). 1000 örnek al, standart sapmayı (σ) hesapla. Gürültüsüz bit `= N − log₂(6,6σ)`. Bunu her kart revizyonunda tekrarla.
2. **Doğrusallık:** Hassas bir kaynakla girişi 5–10 noktada tara; ölçülen–beklenen farkını çiz. Ofset ve kazanç hatası düz bir çizgi, INL eğri olarak görünür.
3. **Referans:** VDDA'yı toleransın iki ucuna götür; mutlak ölçümlerde VREFINT düzeltmesi okumayı sabit tutuyor mu, oransal ölçümler değişmiyor mu?
4. **Sıcaklık:** Kartı iklim kabininde veya ısıtarak ölç; sıfır ve kazanç ne kadar kayıyor?
5. **Girişim testi:** Ölçüm alırken röleyi, buzzer'ı ve ısıtıcıyı çalıştır; okuma sıçrıyor mu?
6. **Arıza senaryoları:** Sensörü sök, kısa devre et, 4–20 mA hattını aç. Cihaz her durumda arıza bildiriyor mu?

## 15. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| "12 bit = 12 bit doğruluk" sanmak | Gürültü ve hatalar birkaç bit yer | σ ölç, hata bütçesi yap |
| VDDA'yı referans alıp mutlak ölçüm | LDO toleransı ölçüme geçer | VREFINT düzeltmesi, referans IC |
| Yüksek empedanslı kaynağa kısa örnekleme | Kapasitör dolmaz, okuma düşük çıkar | t_s'yi hesapla, pin kapasitörü, tampon |
| Pin kapasitörü + hızlı örnekleme + büyük R | Ortalama akım okumayı düşürür | Yavaş örnekle veya tampon |
| Pilli üründe düşük dirençli bölücü | Pil bölücüden boşalır | Yüksek R veya anahtarlı bölücü |
| MΩ'luk bölücü | Pin kaçak akımı büyük hata yapar | Anahtarlı bölücü |
| Kanal değişiminden sonraki ilk örneği kullanmak | Önceki kanalın izi kalır | İlk örneği at |
| Açık/kısa devreyi ölçüm sanmak | Arızalı sensör "normal" görünür | Makullük kontrolü → arıza |
| 4–20 mA şantını korumasız bırakmak | Yanlış bağlantıda şant yanar | PTC/akım sınırlama + TVS |
| Kalibrasyon katsayılarını kontrolsüz kullanmak | Bozuk Flash, sessiz hata | CRC + makullük + arıza |
| Ölçümü röle/PWM anahtarlamasıyla aynı anda almak | Sıçramalar | Ölçümü olaylardan uzak zamanla |
| İzolasyonsuz karta topraklı osiloskop | Kısa devre, tehlike | İzolasyon trafosu, diferansiyel prob |

## 16. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **LSB** | ADC'nin en küçük adımı (V_ref / 2ᴺ) |
| **Tam skala (FS)** | ADC'nin ölçebildiği en büyük gerilim (≈ V_ref) |
| **SAR / Σ-Δ** | Ardışık yaklaşımlı / sigma-delta ADC türleri |
| **PGA** | Programlanabilir kazançlı yükselteç |
| **INL / DNL** | Doğrusallıktan sapma / adımların eşitsizliği |
| **TUE** | Toplam ayarlanmamış hata |
| **ENOB** | Etkin bit sayısı (dinamik ölçümden) |
| **Gürültüsüz bit** | Ölçüm sırasında titremeyen bit sayısı |
| **VREFINT** | MCU'nun içindeki, fabrikada ölçülmüş referans gerilimi |
| **Oransal ölçüm** | Sensör beslemesi ile ADC referansının aynı kaynaktan geldiği ölçüm |
| **C_s / örnekleme süresi** | ADC'nin içindeki örnekleme kapasitörü / onun dolma süresi |
| **Aşırı örnekleme** | Gereğinden hızlı örnekleyip toplayarak bit kazanma |
| **EMA** | Üstel hareketli ortalama (tek değişkenli alçak geçiren) |
| **NAMUR NE 43** | 4–20 mA'de ölçüm ve arıza sinyal sınırlarını tanımlayan öneri |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.5, bölüm 6):

- [x] Her ADC ölçümü için hata bütçesi hesaplandı ve gereken etkin bit sayısıyla karşılaştırıldı
- [x] VDDA referans olarak kullanılıyorsa VREFINT ile besleme düzeltmesi planlandı (veya harici referans / oransal ölçüm)
- [x] Pin kapasitörü yük paylaşımı kuralına göre (12 bit için ≥ ~100 nF); yüksek kaynak direncinde örnekleme hızı buna göre düşük
- [x] Pil/besleme bölücüsünün sürekli akımı pil ömrüne göre kontrol edildi; MΩ'luk bölücü yerine gerekirse anahtarlı bölücü
- [x] Firmware: açılışta ADC kalibrasyonu; kanal değişiminde ilk örnek atılıyor
- [x] Firmware: her kanalda makul aralık kontrolü; aralık dışı ölçüm arıza olarak raporlanıyor
- [x] 4–20 mA girişlerinde şant gücü ve koruması yanlış bağlantıya (ör. 24 V) göre; NAMUR arıza sınırları uygulanıyor
- [x] Şebeke potansiyelindeki ölçümlerde yüksek gerilim direnç dizisi; debug için izolasyon planı

## Kontrol soruları

→ [quiz.md](quiz.md) · 13 soru, 10'u hesap
