# Güç katı: koruma ve regülatör seçimi

- **Oluşturma:** 2026-10-16
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Bağlantılı:** [Güç ve decoupling](../guc-ve-decoupling/ozet.md) · [Bobin (buck hesabı)](../../Komponentler/03-bobin-induktor/ozet.md) · [Kapasitör (inrush, hold-up)](../../Komponentler/02-kapasitor/ozet.md) · [EMC için kart tasarımı, bölüm 8](../../EMC/02-emc-icin-kart-tasarimi/ozet.md#8-güç-girişi) · Kontrol listesi bölüm 2–3

> Sayısal değerler **tipik başlangıç noktalarıdır**; tasarım değeri için kullandığın parçanın datasheet'i ve ürün standardı esastır. Örneklerdeki parça numaraları yalnızca örnektir.
>
> **Okuma planı:** 1. oturum: bölüm 1–5 (koruma) · 2. oturum: 6–8 (regülatörler, güç bütçesi) · 3. oturum: 9–14.

---

## ⚡ Hızlı tekrar

1. Güç katı bir **zincirdir**: konnektör → sigorta → ters polarite → TVS → filtre → bulk kapasitör → regülatör → raylar. Sıra önemlidir.
2. **Sigorta/PTC** yangını önler; değeri en yüksek normal akımın üstünde, kablo ve izin dayanabileceğinin altında olmalı.
3. **Ters polarite:** düşük akımda seri Schottky diyot yeterli; akım büyüdükçe P-MOSFET veya ideal diyot denetleyicisi.
4. **TVS** üç sayıyla seçilir: VRWM ≥ en yüksek normal gerilim; **VC** (kenetleme) ≤ arkadaki devrenin dayanımı. Arkadaki regülatörün gerilim dayanımını TVS'nin VC'sine göre seç.
5. **LDO**, aradaki gerilim farkını **ısıya** çevirir: `P = (Vin − Vout) × I`. Fark ya da akım büyükse **buck** kullan.
6. Isıyı her zaman hesapla: `Tj = Ta + P × θJA`. SOT-23 bir LDO 1 W'ı taşıyamaz.
7. Buck'ın gürültüsü yüksek frekanstadır. Hassas analog için **buck + arkasında LDO** veya ferrit/LC filtre kullanılır. Hassas devre yakınında **ekranlı bobin**.
8. Tasarıma **güç bütçesi** tablosuyla başla: her tüketicinin gerilimi ve en yüksek akımı → her ray → giriş akımı → sigorta.

## 🧮 Formül kartı

| Formül | Ne zaman kullanılır | Örnek |
|---|---|---|
| `P_LDO = (Vin − Vout) × I` | LDO'nun ısıya çevirdiği güç | 12 → 3,3 V, 100 mA → **0,87 W** |
| `Tj = Ta + P × θJA` | Parça sıcaklığı | 0,87 W, θJA 70 °C/W, Ta 50 °C → **111 °C** |
| `I_in = (Vout × Iout) / (η × Vin)` | Buck'ın girişten çektiği akım | 5 V × 0,215 A / (0,85 × 24 V) → **53 mA** |
| `P_kayıp = P_out × (1/η − 1)` | Buck kaybı | 1,075 W, η 0,85 → **0,19 W** |
| `P_D = V_F × I` | Seri ters polarite diyotunun kaybı | 0,4 V × 1 A → **0,4 W** |
| `P_FET = I² × R_DS(on)` | P-MOSFET ile ters polarite kaybı | 1 A, 50 mΩ → **50 mW** |
| `Vout = V_FB × (1 + R_üst / R_alt)` | Regülatör çıkış bölücüsü | V_FB 0,8 V, 52,3k / 10k → **4,98 V** |
| `I_sigorta ≥ I_max / k_derating` | Sigorta değeri (k ≈ 0,75 tipik) | 100 mA → ≥ 133 mA → **250 mA T** |

---

## 1. Güç katı zinciri

Binanın su girişini düşün:

| Su tesisatı | Güç katı | Görevi |
|---|---|---|
| Ana vana | **Sigorta / PTC** | Aşırı akımda keser |
| Çek valf | **Ters polarite koruması** | Ters bağlantıda akım akmasın |
| Basınç tahliye vanası | **TVS diyot** | Ani yüksek gerilimi kenetler |
| Filtre | **EMC filtresi** (ferrit, LC) | Gürültüyü içeri/dışarı geçirmez |
| Depo | **Bulk kapasitör** | Ani ihtiyaçları karşılar, kesintide kısa süre besler |
| Basınç düşürücü | **Regülatör** | Rayı sabit gerilimde tutar |

```
 J1 ──F1──D1/Q1──┬────┬── FB/LC ──┬──┬── [BUCK] ──┬── +5V ──[LDO]── +3V3
 (24 V)  sigorta  ters  │    │   filtre    │  │            │
          polarite     TVS  C_bulk        C  C_in         C_out
                        │    │             │  │            │
 GND ───────────────────┴────┴─────────────┴──┴────────────┴───────── GND
```

**Sıranın mantığı:**
- Sigorta en önde: arkadaki herhangi bir parça kısa devre olursa (TVS dahil) sigorta açar.
- TVS, ters polarite elemanının **arkasında** olursa ters bağlantıda iletime girmez ve sigortayı gereksiz attırmaz. Önünde olursa (tek yönlü TVS) ters bağlantıda doğrudan iletir ve sigortayı attırır; bu da bilinçli seçilmiş bir ters polarite yöntemi olabilir. Hangisini seçtiğini nota yaz.

## 2. Aşırı akım: sigorta mı, PTC mi?

| | Eriyen sigorta | PTC (resettable) |
|---|---|---|
| Çalışma | Tel erir, devre açılır | Isınınca direnci çok büyür, soğuyunca geri döner |
| Hız | Hızlı (F) veya gecikmeli (T) | Yavaş (saniyeler) |
| Sonrası | Değişmesi gerekir | Kendiliğinden döner |
| Normal çalışmada | Çok düşük direnç | Daha yüksek direnç (gerilim düşümü) |
| Sıcaklık | Az etkilenir | **Tutma akımı sıcaklıkla ciddi düşer** |
| Nerede | Güvenlik gereken, şebekeli cihazlar | Sahada kablolanan, kullanıcı hatasına açık girişler |

**Değer seçimi:**
1. En yüksek normal akımı bul (güç bütçesi, bölüm 8).
2. Ortam sıcaklığı için düşür: `I_sigorta ≥ I_max / 0,75` (tipik; datasheet eğrisine bak).
3. **Açılıştaki inrush** akımını kontrol et: bulk kapasitörün şarjı kısa ama büyük bir akımdır. Sigortanın I²t değeri bu darbeye dayanmalı → genelde **gecikmeli (T)** seçilir.
4. Sigorta, **kablo ve izden önce** açmalı: kartın girişindeki iz ve konnektör, sigortanın açma akımını rahatça taşımalı.
5. PTC'de: tutma akımı (I_hold) en yüksek **ortam sıcaklığında** yük akımından büyük olmalı.

## 3. Ters polarite koruması

**Ne olur?** Kullanıcı 24 V'u ters bağlar. Korumasız kartta regülatörlerin, elektrolitik kapasitörlerin ve IC'lerin içindeki diyotlar iletime girer; parçalar yanar.

| Yöntem | Kayıp | Artısı | Eksisi |
|---|---|---|---|
| Seri Schottky diyot | `0,3–0,5 V × I` | En basit, ucuz | Akım büyüdükçe ısınır, gerilim kaybı |
| Paralel diyot + sigorta | Yok (normalde) | Gerilim kaybı yok | Ters bağlantıda sigorta atar |
| P-MOSFET (yüksek taraf) | `I² × R_DS(on)` | Çok düşük kayıp | Gate koruması gerekir |
| İdeal diyot denetleyicisi | Çok düşük | Hızlı, geri akımı da keser | Pahalı, ek IC |

**Örnek:** 100 mA'lik bir kartta Schottky kaybı 0,4 V × 0,1 A = 40 mW, sorun değil. 1 A'de 0,4 W ve 0,4 V kayıp olur; burada P-MOSFET mantıklıdır (50 mΩ → 50 mW).

**P-MOSFET devresi:**

```
 VIN ──────┬─── D   S ───┬────── korunan taraf
           │     ╲ Q1 ╱  │
           │       G     │
           │       ├─────┤ Zener (ör. 12 V): katot S tarafında, |Vgs|'yi sınırlar
           │       │
           │      R (10–100 kΩ)
           │       │
 GND ──────┴───────┴──────────────
```

- Doğru bağlantıda: gövde diyotu önce iletir, S yükselir, G toprakta → Vgs negatif → MOSFET tam açılır.
- Ters bağlantıda: G pozitif kalır → MOSFET kapalı, gövde diyotu ters yönde → akım yok.
- **Zener şart:** Vin, MOSFET'in Vgs dayanımını (tipik ±20 V) geçebiliyorsa gate korunmalı. 24 V sistemde **mutlaka**.

> **Kaçın:** Toprak hattına (low-side) N-MOSFET ile ters koruma; kartın GND'si dış dünyanın GND'sinden kayar. Haberleşme hattı (RS-485, UART) olan cihazlarda referans bozulur.

## 4. Geçici gerilim: TVS diyot

Uzun kablolar, röleler, motorlar ve yıldırım kaynaklı darbeler mikrosaniyeler içinde yüzlerce volta çıkabilir. TVS bu darbeyi **yutar ve kenetler**.

| Parametre | Anlamı | Seçim kuralı |
|---|---|---|
| **VRWM** | Bu gerilime kadar TVS iletmez | ≥ en yüksek **normal** giriş gerilimi |
| **VBR** | İletmeye başladığı gerilim | VRWM'nin biraz üstü |
| **VC** | Darbe sırasında üzerinde kalan gerilim | ≤ arkadaki devrenin **mutlak maksimum** gerilimi |
| **Ipp** | Dayanabildiği darbe akımı | Test seviyesine göre (ör. IEC 61000-4-5 surge) |

**Örnek (24 V giriş, normalde en fazla 30 V):**
- VRWM ≥ 30 V → ör. **SMBJ33A** sınıfı: VRWM 33 V, darbe sırasında VC ≈ 53 V.
- Arkadaki buck regülatörün giriş dayanımı **53 V'tan büyük** olmalı → 40 V'luk değil **60 V'luk** buck seçilir.

> **Can alıcı nokta:** TVS gerilimi sıfıra indirmez; VC'ye kenetler. Arkadaki her şey VC'ye dayanmalı.

**Yerleşim:** TVS konnektöre **en yakın** noktada, GND bağlantısı kısa ve geniş olmalı. Uzun bir iz, darbe sırasında endüktansı yüzünden ek gerilim üretir (`V = L·di/dt`).

**Hot-plug sıçraması:** Uzun kablo (endüktans) + girişte düşük ESR'li seramik kapasitör bir rezonans devresidir. Kablo takıldığı anda giriş gerilimi kısa süre **iki katına** yaklaşabilir. Çözüm: girişte bir elektrolitik (ESR'si sönümler), seri direnç veya TVS.

## 5. Düşük gerilim ve kesinti

- **UVLO (Under Voltage Lock-Out):** Regülatör, giriş belli bir değerin altındaysa çalışmaz. Böylece yarım gerilimde garip davranış olmaz. Çoğu buck'ta EN pinine bir bölücüyle ayarlanabilir.
- **Brown-out (BOR):** MCU'nun kendi düşük gerilim reset'i; firmware'de etkin olmalı ([MCU dersi](../../Komponentler/05-mikrodenetleyici-donanimi/ozet.md)).
- **Kesinti anında veri kaydetme:** Hold-up kapasitörü ve erken uyarı (PVD) → [Kapasitör, bölüm 5.2](../../Komponentler/02-kapasitor/ozet.md#52-enerji-tutma-hold-up).

## 6. Regülatör seçimi: LDO mu, buck mı?

**LDO (doğrusal regülatör):** Girişle çıkış arasına seri bir "ayarlı direnç" gibi davranır. Fazla gerilimi **ısıya** çevirir.

**Buck (anahtarlamalı):** Girişi çok hızlı açıp kapar, bobin ve kapasitörle ortalamasını alır. Enerjiyi büyük ölçüde **aktarır**, ısıya çevirmez (verim %80–95).

| | LDO | Buck |
|---|---|---|
| Verim | `Vout/Vin` (12 → 3,3 V: %28) | %80–95 |
| Çıkış gürültüsü | Çok düşük | Anahtarlama ripple'ı ve yüksek frekans gürültü |
| EMC | Sorun çıkarmaz | Layout'a çok bağlı |
| Parça sayısı | 1 IC + 2 kapasitör | IC + bobin + kapasitörler + bölücü |
| Ne zaman | Fark küçük, akım küçük, temiz ray gerekli | Fark büyük veya akım büyük |

**Isı hesabı (karar burada verilir):**

| Durum | P_LDO | SOT-23 (θJA ≈ 200 °C/W) | SOT-223 (θJA ≈ 70 °C/W) | Karar |
|---|---|---|---|---|
| 5 → 3,3 V, 100 mA | 0,17 W | +34 °C | +12 °C | LDO uygun |
| 12 → 3,3 V, 30 mA | 0,26 W | +52 °C | +18 °C | SOT-223 LDO uygun |
| 12 → 3,3 V, 100 mA | 0,87 W | +174 °C ✗ | +61 °C (sınırda) | Buck tercih |
| 24 → 5 V, 150 mA | 2,85 W | ✗ | +200 °C ✗ | **Mutlaka buck** |

θJA değeri kartın bakır alanına çok bağlıdır; tablodaki değerler kabaca. Kendi parçanın datasheet'ine ve kart düzenine bak. Hesapta **en yüksek giriş gerilimi ve en yüksek akım** kullanılır.

**En sık kullanılan çözüm: ikisi birlikte.**

```
 24 V ──[BUCK]── +5V ──┬── yüksek akımlı yükler (sensör ısıtıcısı, buzzer)
                       └──[LDO]── +3V3_A ── ADC, op-amp (temiz ray)
```

Buck büyük gerilim farkını verimli düşürür; LDO küçük farkı (5 → 3,3 V) az ısıyla düşürür ve buck'ın düşük frekanslı ripple'ını temizler.

**LDO'da dikkat:**
- **Dropout:** En düşük girişte `Vin − Vout ≥ dropout` (tüm sıcaklık ve akım aralığında).
- **PSRR:** LDO'nun girişteki ripple'ı ne kadar bastırdığı. Düşük frekansta iyi (tipik 60–70 dB @1 kHz), **MHz'lerde zayıflar**. Buck'ın MHz gürültüsü için LDO'ya güvenme; ferrit/LC ekle.
- **Çıkış kapasitörü:** Bazı LDO'lar düşük ESR'li seramikle **kararsız** olur (salınım). Datasheet'teki kapasitör türü ve ESR aralığına uy.
- **Sükûnet akımı (Iq):** Pilli cihazda önemli.

## 7. Buck regülatörde pratik

1. **Datasheet'in "Typical Application" devresiyle başla.** Değerleri oradan al, sonra kendi koşuluna göre hesapla.
2. **Bobin:**
   - Isat ≥ regülatörün **akım limiti** (kısa devrede bobin doymamalı).
   - Hesap: [Bobin dersi](../../Komponentler/03-bobin-induktor/ozet.md).
   - **Ekranlı bobin seç:** Ekransız bobinin manyetik alanı havada dolaşır ve yakındaki iz ve sensör girişlerine gürültü bindirir. Ekranlı bobinde ferrit kılıf alanı içeride tutar. Kalıplanmış (metal kompozit) bobinler hem ekranlıdır hem yavaş doyar.
3. **Giriş kapasitörü:** IC'nin VIN–GND pinlerine **en yakın** yerde. Sıcak döngünün parçasıdır ([EMC 02, bölüm 5](../../EMC/02-emc-icin-kart-tasarimi/ozet.md#5-anahtarlamalı-regülatörler)). RMS akım derecesi yeterli olmalı.
4. **Geri besleme bölücüsü:** `Vout = V_FB × (1 + R_üst/R_alt)`. %1 direnç kullan. FB izi kısa ve SW düğümünden uzak.
5. **Anahtarlama frekansı:** Yüksek frekans → küçük bobin ama daha çok kayıp. Hassas bir bant varsa (ör. ölçtüğün sinyal veya bir radyo bandı) frekansı ondan uzak seç.
6. **Hafif yük modu (PFM / skip mode):** Az yükte bazı buck'lar frekansı düşürür. Ripple kHz'lere, hatta duyulabilir bölgeye iner ve analog ölçüme karışabilir. Hassas ölçümde **zorlanmış PWM (FPWM)** seçeneği olan IC'yi tercih et.
7. **Soft-start:** Açılışta çıkışı yavaşça yükseltir, inrush'ı azaltır.

## 8. Güç bütçesi

Tasarıma bu tabloyla başla. Hem regülatör seçimini hem sigortayı hem de kablo kesitini bu tablo belirler.

**Örnek (24 V girişli, sensör ısıtıcılı bir dedektör):**

| Tüketici | Ray | En yüksek akım |
|---|---|---|
| MCU ve dijital çevre | +3V3 | 25 mA |
| LED'ler | +3V3 | 10 mA |
| Sensör ısıtıcısı | +5V | 150 mA |
| Buzzer | +5V | 30 mA |
| Röle bobinleri (2 adet) | 24 V (doğrudan) | 30 mA |

**Ray ray hesap:**
1. **+3V3** = 25 + 10 = **35 mA**. 5 V'tan LDO ile: `P = (5 − 3,3) × 0,035 = 0,06 W` → küçük LDO yeter.
2. **+5V** = 150 + 30 + 35 (LDO'nun çektiği) = **215 mA** → `P = 5 × 0,215 = 1,075 W`.
3. **Buck'ın giriş akımı** (η = 0,85): `1,075 / 0,85 = 1,265 W` → 24 V'ta **53 mA**, en düşük giriş 18 V'ta **70 mA**.
4. **Toplam giriş:** 70 + 30 (röle) = **~100 mA** (18 V'ta, en kötü durum; röle akımı sabit kabul edildi).
5. **Sigorta:** `100 / 0,75 = 133 mA` → inrush için gecikmeli **250 mA T** makul bir başlangıç.
6. **Regülatör marjı:** Buck en az 1,5 × 215 mA ≈ 350 mA verebilmeli → 500 mA'lik bir buck rahat.

> Isıtıcılı sensörler gücün büyük kısmını harcar. Bu yüzden 24 V → 5 V'u LDO ile düşürmek (2,85 W) imkânsızdır; buck şarttır.

## 9. Şematikte

- Güç katını **tek bir sayfada** topla; zincir sırası soldan sağa okunsun.
- Her rayın yanına **gerilim ve en yüksek akımı** yaz: `+5V / 215 mA max`.
- Sigorta, TVS, ters koruma elemanının seçim gerekçesini not et (VC, I²t, kayıp).
- Regülatör sayfasında **güç bütçesi tablosu** olsun.
- EN, PG (power good), UVLO bölücüleri ve soft-start kapasitörü **boşta değil**.
- Her rayda bir **test noktası**: `TP_5V`, `TP_3V3`, `TP_VIN`.

## 10. PCB / layout

- Giriş konnektörü → sigorta → koruma → regülatör sırası kartta da aynı yönde akmalı; gürültülü giriş akımı kartın içine dolaşmasın.
- **TVS ve giriş kapasitörü:** GND'ye kısa ve geniş bağlantı, birden fazla via.
- **Buck sıcak döngüsü** en küçük alanda, aynı katmanda; **SW düğümü** küçük ([Bobin dersi](../../Komponentler/03-bobin-induktor/ozet.md), [EMC 02](../../EMC/02-emc-icin-kart-tasarimi/ozet.md)).
- Bobin, sensör girişleri ve kristalden uzakta; altından hassas iz geçmez.
- LDO ve güç dirençleri için **bakır alan = soğutucu**. Isı yayan parçaları sensörün ve elektrolitik kapasitörün yanına koyma.
- Güç izlerinin genişliği akıma göre: [PCB yerleşim dersi](../pcb-yerlesim-ve-iz-cizimi/ozet.md).

## 11. EMC açısından

- Buck, kartın en büyük gürültü kaynağıdır. Giriş filtresi (ferrit + kapasitör veya LC) gürültünün **kablodan dışarı** çıkmasını önler.
- Surge (IEC 61000-4-5) ve hızlı geçici darbe (EFT, IEC 61000-4-4) testleri güç girişini zorlar; TVS ve giriş filtresi bu testler için tasarlanır ([EMC 03](../../EMC/03-emc-testleri-ve-standartlar/ozet.md)).
- Hassas analog raylar için LDO + ferrit/LC; filtre rezonansını [ferrit boncuk dersine](../../Komponentler/04-ferrit-boncuk/ozet.md) göre sönümle.

## 12. Ölçüm ve doğrulama

1. **Çalışma aralığı:** Kartı en düşük ve en yüksek giriş geriliminde, en yüksek yükte çalıştır. Raylar toleransta mı?
2. **Ripple ölçümü:** Prob ucunu kapasitörün pedlerine doğrudan koy, **kısa GND yayı** kullan (timsah kablo sahte gürültü gösterir); osiloskopta 20 MHz bant sınırı ve AC kuplaj.
3. **Yük basamağı:** Yükü aniden aç-kapa (ör. ısıtıcı veya röle). Ray ne kadar çöküyor, ne kadar sürede toparlanıyor?
4. **Isı:** En yüksek ortam sıcaklığında parçaların sıcaklığını ölç (termokupl veya termal kamera). Hesapla uyuşuyor mu?
5. **Ters polarite testi:** Akım sınırlı bir güç kaynağıyla ters bağla; hiçbir şey ısınmamalı.
6. **Hot-plug testi:** Uzun kabloyla gerilim uygulanmışken kabloyu tak; girişteki sıçramayı osiloskopla yakala.
7. **Açılış:** Rayların yükselme sırası ve süresi; MCU reset'ten doğru çıkıyor mu?

## 13. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| LDO'nun ısısını hesaplamamak | Termal kapanma, ömür kısalır | `P = ΔV × I`, `Tj = Ta + P·θJA` |
| TVS'nin VC'sini unutmak | Darbe sırasında regülatör yanar | Regülatör dayanımı > VC |
| Sigortayı nominal akıma göre seçmek | Açılışta (inrush) atar | Gecikmeli tip, I²t kontrolü |
| PTC'nin sıcaklıkta tutma akımının düştüğünü bilmemek | Sıcak ortamda kendi kendine açar | En yüksek ortam sıcaklığındaki I_hold |
| P-MOSFET gate'ini korumasız bırakmak | 24 V'ta Vgs dayanımı aşılır | Gate–source Zener |
| Low-side ters koruma + haberleşme | GND kayar, iletişim bozulur | High-side P-MOSFET |
| Buck'ı hassas analoğun yanına koymak | Manyetik ve kapasitif kuplaj | Mesafe, ekranlı bobin, LDO/LC |
| PFM modunun gürültüsünü bilmemek | Az yükte kHz ripple ölçüme karışır | FPWM seçeneği |
| Güç bütçesi yapmamak | Regülatör ya da sigorta yetmez | Bölüm 8'deki tablo |
| LDO çıkış kapasitörünü datasheet'e uymadan seçmek | Salınım | Datasheet'teki tür ve ESR aralığı |

## 14. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **LDO** | Low Drop-Out; giriş-çıkış farkı küçükken de çalışabilen doğrusal regülatör |
| **Dropout** | LDO'nun regüle edebilmesi için gereken en küçük Vin − Vout |
| **Buck** | Gerilimi düşüren anahtarlamalı regülatör |
| **Verim (η)** | Çıkış gücü / giriş gücü |
| **θJA** | Junction'dan ortama ısıl direnç (°C/W) |
| **PSRR** | Girişteki ripple'ın çıkışa ne kadar zayıflayarak geçtiği |
| **TVS** | Ani gerilim darbesini kenetleyen diyot |
| **VRWM / VC** | TVS'nin iletmediği en yüksek gerilim / darbe sırasındaki kenetleme gerilimi |
| **PTC** | Isınınca direnci artan, kendini sıfırlayan sigorta |
| **I²t** | Sigortanın eriyebilmesi için gereken enerji ölçüsü |
| **UVLO** | Düşük girişte regülatörü kapalı tutan koruma |
| **PFM / FPWM** | Hafif yükte frekans düşüren mod / her yükte sabit frekans |
| **Güç bütçesi** | Tüm tüketicilerin akım ve güç tablosu |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.4, bölüm 2–3):

- [x] Arkadaki regülatörün giriş dayanımı, TVS'nin kenetleme gerilimi (VC) üstünde
- [x] P-MOSFET ters koruma kullanıldıysa gate–source Zener ile korunuyor
- [x] PTC kullanıldıysa en yüksek ortam sıcaklığındaki tutma akımı yük akımının üstünde
- [x] Güç bütçesi tablosu şematikte; her rayın gerilimi ve en yüksek akımı yazılı
- [x] Hassas analog varsa buck'ın hafif yük modu (PFM) değerlendirildi; gerekirse FPWM

## Kontrol soruları

→ [quiz.md](quiz.md) · 10 soru, 5'i hesap
