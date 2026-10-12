# 01 · Direnç

- **Oluşturma:** 2026-10-12
- **İlk kaynak:** Üretici datasheet'leri (ör. Yageo RC, Vishay CRCW kalın film serileri)
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)

> Sayısal değerler **tipik başlangıç noktalarıdır**; tasarım değeri için her zaman kullandığın serinin datasheet'i esastır.

---

## ⚡ Hızlı tekrar

1. Direnç seçmek yalnızca değer seçmek değildir: **güç, gerilim, tolerans, TCR ve darbe dayanımı** birlikte seçilir.
2. Anma gücünün **yarısını geçme** (derating). Anma gücü tipik olarak 70 °C ortam sıcaklığına kadar geçerlidir; üstünde düşer.
3. Her paketin bir **maksimum çalışma gerilimi** vardır (0603 için tipik 75 V). Yüksek değerli dirençte gerilim limiti, güç limitinden önce dolar.
4. Hassas ölçümde **ince film** (düşük TCR, düşük gürültü), genel işlerde **kalın film** kullanılır.
5. Akım ölçme şantında **Kelvin (4 telli) bağlantı** şarttır.
6. Yüksek değerli dirençlerde (MΩ) **parazitik kapasitans**, yüksek frekansta direnci devre dışı bırakır.
7. Dışarı açılan hatlardaki seri direnç hem **ESD ve kısa devre akımını sınırlar** hem de kenarları yumuşatır (EMC).
8. Kükürt içeren ortamlarda (rafineri, atık su, lastik ve gübre tesisleri) standart kalın film dirençler zamanla **açık devre** olabilir. Bu ortamlar için **anti-sülfür** tip kullanılır.

## 🧮 Formül kartı

| Formül | Ne zaman kullanılır | Örnek |
|---|---|---|
| `P = I²·R = V²/R` | Güç hesabı | 2 A, 50 mΩ → 0,2 W |
| `ΔR/R = TCR · ΔT` | Sıcaklıkla değer değişimi | 100 ppm/°C, 50 °C → %0,5 |
| `V_out = V_in · R2/(R1+R2)` · `R_th = R1·R2/(R1+R2)` | Gerilim bölücü ve çıkış empedansı | 12 V, 30k/10k → 3 V, R_th = 7,5 kΩ |
| `R = (V_cc − V_f) / I_LED` | LED akım sınırlama | 3,3 V, 2,0 V, 5 mA → 260 Ω → **270 Ω** |
| `R_p,max = t_r / (0,8473·C_b)` · `R_p,min = (V_DD − V_OL)/I_OL` | I²C pull-up | 400 kHz, 200 pF → 967 Ω ≤ R ≤ 1,77 kΩ |
| `R_kritik = V_max² / P_anma` | Hangi limitin önce dolduğu | 0603: 75² / 0,1 ≈ 56 kΩ |
| `v_n = √(4·k·T·R·B)` | Termal gürültü | 10 kΩ, 10 kHz → 1,3 µV rms |

---

## 1. Ne işe yarar? Temel fizik

Direnç devrede altı farklı iş yapar:

| Görev | Örnek |
|---|---|
| Akım sınırlama | LED, transistör tabanı, giriş koruma |
| Gerilim bölme | ADC ile 12 V ölçmek, regülatör geri beslemesi |
| Akımı gerilime çevirme | Akım ölçme şantı, 4–20 mA alıcısı |
| Seviye tanımlama | Pull-up / pull-down |
| Zaman sabiti kurma | RC filtre, gecikme |
| Enerjiyi ısıya çevirme | Yük direnci, sönümleme (snubber), sonlandırma |

**Isı her şeyin merkezinde:** Direnç enerjiyi `P = I²·R` ile ısıya çevirir. Bu ısı direncin değerini (TCR), ömrünü ve yanındaki parçaları (özellikle elektrolitik kapasitörler ve sensörler) etkiler.

**Her direnç gürültü üretir:** Termal (Johnson) gürültü fiziksel olarak kaçınılmazdır: `v_n = √(4kTRB)`.
- 10 kΩ, 10 kHz bant: **1,3 µV rms**
- 1 MΩ, 10 kHz bant: **12,8 µV rms**

Gürültü √R ile büyür. Köprü sensörleri (ör. katalitik LEL sensörü) mV seviyesinde sinyal verir; bu yüzden sinyal yolundaki dirençleri gereğinden büyük seçme.

## 2. Türleri ve seçim

| Tür | Tipik tolerans / TCR | Artı | Eksi | Nerede |
|---|---|---|---|---|
| **Kalın film çip** | %1–5 / ±100–200 ppm/°C | Ucuz, her değer var | Akım gürültüsü, sınırlı darbe dayanımı, kükürte hassas | Genel: pull-up, LED, bölücü |
| **İnce film çip** | %0,1–1 / ±5–25 ppm/°C | Hassas, düşük gürültü, kararlı | Pahalı, darbeye hassas | Ölçüm, referans bölücü, op-amp kazancı |
| **Metal film (bacaklı)** | %1 / ±50 ppm/°C | İyi genel performans | Yer kaplar | Prototip |
| **Akım ölçme (metal şerit)** | %0,5–1 / düşük | mΩ değerler, yüksek güç | Pahalı | Şant |
| **Telli (wirewound)** | — | Yüksek güç ve darbe dayanımı | **Endüktif** | Güç yükü, inrush sınırlama |
| **MELF** | — | Darbe dayanımı, uzun ömür | Silindir şekli | Güvenilirlik ve surge gereken yerler |
| **Anti-surge çip** | — | Darbe dayanımı | Biraz pahalı | Giriş koruma, inrush |
| **Anti-sülfür kalın film** | — | Kükürde dayanıklı | Biraz pahalı | Endüstriyel ortamlar |

### Paket, güç ve gerilim (standart kalın film serileri için tipik)

| Paket | Anma gücü | Maks. çalışma gerilimi |
|---|---|---|
| 0402 | 1/16 W | 50 V |
| 0603 | 1/10 W | 75 V |
| 0805 | 1/8 W | 150 V |
| 1206 | 1/4 W | 200 V |
| 2512 | 1 W | 200 V |

Aynı pakette yüksek güçlü seriler de vardır; kendi serinin datasheet'ine bak.

### Değer serileri

- **E24 (%5):** 10, 11, 12, 13, 15, 16, 18, 20, 22, 24, 27, 30, 33, 36, 39, 43, 47, 51, 56, 62, 68, 75, 82, 91
- **E96 (%1):** Dekad başına 96 değer

**BOM ipucu:** Bir kartta az sayıda farklı değer kullanmak (ör. 100 Ω, 1 kΩ, 4,7 kΩ, 10 kΩ, 100 kΩ) montajı, stoğu ve ürün ağacını sadeleştirir.

## 3. Datasheet'te nelere bakılır?

| Parametre | Anlamı | Tuzak |
|---|---|---|
| Tolerans | Yeni parçada, 25 °C'deki sapma | Sıcaklık ve yaşlanma ayrıca eklenir |
| Anma gücü | Tipik 70 °C ortama kadar | Üstünde **derating eğrisi** ile düşer |
| Maks. çalışma gerilimi | Sürekli uygulanabilecek gerilim | Yüksek değerli dirençte güç limitinden önce dolar |
| Aşırı yük gerilimi | Kısa süreli dayanım | Sürekli kullanım için değil |
| TCR (ppm/°C) | Sıcaklıkla değer değişimi | Hassas bölücüde iki direncin TCR'si eşleşmeli |
| Darbe dayanımı | Tek ve tekrarlı darbe eğrileri | ESD, surge ve inrush'ta kritik |
| Uzun süreli kararlılık | ör. 1000 saat yük sonrası % değişim | Kalibrasyon aralığını etkiler |
| Kükürt dayanımı | Anti-sülfür testi sonucu | Endüstriyel ortamda kritik |

**Hangi limit önce dolar?** `R_kritik = V_max² / P_anma`. 0603 için: 75² / 0,1 ≈ **56 kΩ**.
- **56 kΩ altında güç limiti** belirleyicidir. 100 Ω'luk 0603 en fazla √(0,1 × 100) ≈ 3,2 V taşır.
- **56 kΩ üstünde gerilim limiti** belirleyicidir. 1 MΩ'luk 0603, güç hesabına göre 316 V taşıyabilir gibi görünür, ama gerilim sınırı 75 V'tur.

## 4. Gerçek model (parazitikler)

```
        ┌──── C_par (~0,05–0,2 pF) ────┐
   ─────┤                               ├─────
        └── L_seri (~nH) ── R ──────────┘
```

- **Düşük değerlerde** (yaklaşık 100 Ω altı) yüksek frekansta **seri endüktans** baskın olur.
- **Yüksek değerlerde** (yaklaşık 10 kΩ üstü) **paralel kapasitans** baskın olur.
  - Örnek: 1 MΩ ve 0,1 pF → **~1,6 MHz** üstünde empedans düşmeye başlar.
  - Etkilediği yerler: yüksek dirençli geri besleme bölücüleri, yüksek empedanslı sensör girişleri.
- **Telli dirençler** çok endüktiftir; hızlı anahtarlamalı veya RF devrelerde kullanma.
- **Hassas DC ölçümde** farklı metallerin birleşim noktası mikrovolt seviyesinde termal gerilim (termokupl etkisi) üretebilir. Kritik ölçümde dirençleri aynı ısıl ortamda ve simetrik yerleştir.

## 5. Şematikte kullanım ve tipik devreler

### 5.1 Pull-up / pull-down

**Amaç:** Bir girişi, kimse sürmezken tanımlı bir seviyede tutmak. Örnekler: açık savaklı (open-drain) çıkış, buton, MCU reset sırasındaki pinler.

| Değer | Artı | Eksi |
|---|---|---|
| Düşük (1–4,7 kΩ) | Güçlü, hızlı, gürültüye dayanıklı | Daha fazla akım |
| Orta (10 kΩ) | Genel amaçlı denge | — |
| Yüksek (100 kΩ+) | Düşük güç tüketimi | Yavaş, gürültüye açık |

**I²C pull-up hesabı (NXP I²C spesifikasyonu):**
- Fast mode (400 kHz): yükselme süresi `t_r ≤ 300 ns`. Hat kapasitansı `C_b = 200 pF` olsun.
- Üst sınır: `R_max = 300 ns / (0,8473 × 200 pF) ≈ 1,77 kΩ`
- Alt sınır: `R_min = (3,3 − 0,4) V / 3 mA ≈ 967 Ω`
- Seçim: **1,5 kΩ**. Standard mode (100 kHz, t_r ≤ 1000 ns) için üst sınır 5,9 kΩ'dur, tipik seçim 4,7 kΩ.
- ⚠️ Hatta **yalnızca bir set** pull-up olmalı. Her modülde ayrı pull-up varsa paralel bağlanır ve direnç `R_min`'in altına düşer.

**Fail-safe:** MCU reset veya boot sırasında pinler yüksek empedanstadır. MOSFET gate'i, enable hattı ve röle sürücüsü gibi hatları pull-down ile **güvenli duruma** çek; aksi halde yük kendi kendine açılabilir.

### 5.2 LED akım sınırlama

- `R = (3,3 V − 2,0 V) / 5 mA = 260 Ω` → E24'te **270 Ω** → akım 4,8 mA, güç 6,3 mW.
- MCU pininin **pin başına ve toplam** akım limitlerini kontrol et (bkz. [Mikrodenetleyici donanımı](../05-mikrodenetleyici-donanimi/ozet.md)).

### 5.3 Gerilim bölücü ve ADC

**Örnek:** 12 V'luk bir rayı 3,3 V'luk ADC ile ölçmek.
- R1 = 30 kΩ, R2 = 10 kΩ → 12 V'ta 3,0 V (marj kalır).
- Çıkış empedansı `R_th = 7,5 kΩ`. ADC'nin izin verdiği kaynak empedansını kontrol et.
- ADC pinine 100 nF koymak örnekleme için yük deposu olur, ama zaman sabitini 0,75 ms'ye çıkarır. Yavaş değişen bir ray için sorun değildir.
- Bölücünün kendi tüketimi 0,3 mA'dir. Pil ile çalışan cihazda dirençleri büyütmek akımı azaltır, ama gürültüyü ve ADC hatasını artırır.

**Tolerans etkisi:** Oran hatası ≈ `(R1/(R1+R2)) × (ΔR1 + ΔR2)`. %1'lik dirençlerle bu örnekte en kötü durum **±%1,5**'tir. Daha iyisi için %0,1 ince film kullan ya da yazılımda kalibre et.

**Koruma:** Girişe 24 V'luk bir geçici darbe gelirse, R1 üzerinden ADC pinine akacak akım MCU'nun "injection current" limitini aşmamalı.

### 5.4 Akım ölçme şantı

- **Örnek:** 2 A'de 50 mΩ → 100 mV sinyal, **0,2 W** kayıp.
- %50 derating ile en az 0,4 W anma gücü gerekir: 1206 (0,25 W) yetmez, **2010 (0,75 W)** veya **2512 (1 W)** gerekir.
- **Alçak taraf** (GND tarafı) ölçüm basittir ama yükün toprağını kaydırır. **Yüksek taraf** ölçüm için akım algılama amplifikatörü kullanılır.
- **Kelvin bağlantısı** şarttır (bkz. bölüm 6).
- Şant ısındıkça TCR yüzünden değeri değişir; düşük TCR'li metal şerit tip seç.

### 5.5 Seri direnç: sonlandırma ve koruma

| Kullanım | Tipik değer | Neden |
|---|---|---|
| Hızlı sinyalde seri sonlandırma | 22–33 Ω, **sürücüye yakın** | Yansıma ve çınlamayı azaltır, EMC'ye yardımcı olur |
| Dış dünyaya açılan giriş | 100 Ω – 1 kΩ (+ TVS/clamp) | Clamp diyotlarından ve TVS'ten geçen akımı sınırlar |
| MOSFET gate | 10–100 Ω seri, 10–100 kΩ pull-down | Anahtarlama hızını kontrol eder, çınlamayı sönümler; gate'i güvenli tutar |

### 5.6 0 Ω direnç (jumper)

- Seçenek köprüsü ve montaj varyantı olarak kullanılır. Gerçekte birkaç on mΩ dirence sahiptir ve pakete göre bir akım limiti vardır (datasheet'te yazar).
- **Bring-up ipucu:** Her güç rayına seri bir 0 Ω koyarsan, onu söküp yerine ampermetre bağlayarak o rayın akımını ölçebilirsin.

## 6. PCB / layout

- **Güç dirençleri:** Datasheet'teki anma gücü belirli bir pad ve bakır alanı varsayar. Isıyı yaymak için bakır bırak. Elektrolitik kapasitörlerden, sensörlerden ve hassas dirençlerden uzak tut.
- **Şant (Kelvin bağlantısı):** Ölçüm izlerini pad'lerin **iç kenarından** al ve amplifikatöre yan yana (diferansiyel çift gibi) götür. Yüksek akım yolu ayrı olmalı.

```
  Yük akımı ═══╗           ╔═══ Yük akımı
               ║  [ŞANT]   ║
               ╚══╤═════╤══╝
                  │     │      ← Kelvin izleri: pad'in iç kenarından
                  └──┬──┘
                 Amplifikatör
```

- **Yüksek gerilim:** Gerilimi seri dirençlere böl. Creepage (yüzey) ve clearance (hava) mesafelerine uy. Yüksek gerilimli düğümler arasında via kullanma.
- **Hassas bölücü:** İki direnci yan yana, aynı yönde ve aynı ısıl ortamda yerleştir. ADC'ye veya amplifikatöre yakın koy, ısı kaynaklarından uzak tut.
- **Seri sonlandırma direnci** sürücü pininin hemen yanında olmalı.
- **Tombstoning:** Küçük pasiflerde (0402) iki pad farklı ısınırsa parça lehimleme sırasında dikilir. Pad'lerin bakır bağlantılarını simetrik tut, büyük bakır alanlara thermal relief kullan.

## 7. EMC açısından

- **Seri direnç kenarları yumuşatır:** Saat ve veri hatlarındaki 22–33 Ω çınlamayı ve yüksek frekanslı harmonikleri azaltır.
- **RC giriş filtreleri** yavaş girişleri (buton, analog sensör) EFT ve RF bozuculara karşı korur.
  - Buton: 10 kΩ + 100 nF → τ = 1 ms (debounce da sağlar).
  - Analog giriş: 1 kΩ + 1 nF → f_c ≈ 159 kHz.
- **Seri R + TVS:** Konnektörden gelen ESD akımının MCU'ya ulaşan kısmını sınırlar.
- **Gate direnci:** MOSFET'in anahtarlama kenarlarını yavaşlatır, emisyonu azaltır. Bedeli biraz daha fazla anahtarlama kaybıdır.
- **Parazitik kapasitans** yüksek frekansta direnci atlar. Yüksek frekans filtresinde yalnızca dirence güvenme; ferrit veya kapasitörle birlikte, düzgün yerleşimle kullan.

## 8. Arıza modları ve sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| Gücü anma değerinin sınırında kullanmak | Isınma, değer kayması, erken arıza | ≤ %50 derating; ortam sıcaklığını hesaba kat |
| Yüksek gerilimi tek küçük dirençle bölmek | Çalışma gerilimi aşılır, yüzeyde atlama olur | Seri dirençler veya yüksek gerilim serisi, creepage |
| Darbe/inrush yolunda standart kalın film | Darbede açık devre olur | Anti-surge, MELF; darbe eğrisini kontrol et |
| Şantı 2 telle ölçmek | Pad ve lehim direnci ölçüme eklenir | Kelvin bağlantısı |
| Hassas bölücüde %5 kalın film | Oran hatası ve sıcaklık kayması | %0,1–1 ince film, kalibrasyon |
| Gürültülü ortamda 1 MΩ pull-up | Gürültü kapar, yavaştır | 10–100 kΩ, gerekiyorsa RC |
| I²C'de birden fazla pull-up seti | Paralel direnç çok düşer, I_OL aşılır | Hatta tek set |
| Kükürtlü ortamda standart direnç | Gümüş sülfür oluşur, açık devre | Anti-sülfür seri |
| MOSFET gate'ini boşta bırakmak | Reset sırasında yük kendiliğinden açılabilir | Gate pull-down |
| 0402'yi elle lehimlemek, asimetrik pad | Tombstoning, kötü lehim | Prototipte 0603, simetrik pad |

**Arıza modu bilgisi:** Film dirençler aşırı yük ve darbede genellikle **açık devre** olur. Kükürt korozyonunda direnç yavaşça **artar** ve sonunda açık devreye gider. Bu yüzden saha arızalarında "değeri kaymış" bir direnç görürsen ortamı da sorgula.

## 9. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Kalın / ince film** | Direnç tabakasının üretim yöntemi; ince film daha hassas ve kararlıdır |
| **TCR** | Temperature Coefficient of Resistance: sıcaklıkla değişim, ppm/°C |
| **Derating** | Anma değerinin altında kullanarak güvenlik payı bırakmak |
| **Kelvin bağlantısı** | Akım ve ölçüm yollarının ayrıldığı 4 telli bağlantı |
| **Şant** | Akımı ölçmek için kullanılan düşük değerli direnç |
| **Pull-up / pull-down** | Hattı varsayılan olarak yükseğe veya alçağa çeken direnç |
| **R_kritik** | Güç ve gerilim limitlerinin eşitlendiği direnç değeri |
| **Anti-sülfür** | Kükürde dayanıklı elektrot yapısına sahip direnç |
| **Tombstoning** | Lehimleme sırasında küçük pasifin dikilmesi |
| **E24 / E96** | Standart değer serileri (%5 / %1) |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.2, bölüm 10):

- [x] Direnç gücü ≤ %50 anma; yüksek ortam sıcaklığında derating eğrisi kontrol edildi
- [x] Yüksek gerilimli dirençlerde çalışma gerilimi ve creepage kontrol edildi
- [x] Akım ölçme şantı Kelvin bağlantılı; gücü ve TCR'si uygun
- [x] Hassas ölçüm yolunda ince film / düşük TCR; bölücü oran hatası hesaplandı
- [x] Kükürtlü ortam riski varsa anti-sülfür dirençler

## Kontrol soruları

→ [quiz.md](quiz.md) · 11 soru, 5'i hesap
