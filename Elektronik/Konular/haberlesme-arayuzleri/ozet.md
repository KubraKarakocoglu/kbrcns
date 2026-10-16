# Haberleşme arayüzleri: elektriksel taraf

- **Oluşturma:** 2026-10-16
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Bağlantılı:** [Direnç (pull-up, seri sonlandırma)](../../Komponentler/01-direnc/ozet.md#55-seri-direnç-sonlandırma-ve-koruma) · [EMC için kart tasarımı, bölüm 6–7](../../EMC/02-emc-icin-kart-tasarimi/ozet.md#6-konnektörler-kablolar-ve-filtreler) · [Ferrit boncuk](../../Komponentler/04-ferrit-boncuk/ozet.md) · Kontrol listesi bölüm 7–8

> Bu ders protokolün yazılım tarafını değil, **tellerin ve dirençlerin** tarafını anlatır. Sayısal değerler tipik başlangıç noktalarıdır; transceiver ve MCU datasheet'i esastır.
>
> **Okuma planı:** 1. oturum: bölüm 1–3 (UART, RS-485) · 2. oturum: 4–6 (I²C, SPI, seviye çevirme) · 3. oturum: 7–14.

---

## ⚡ Hızlı tekrar

1. **Kart içi** (birkaç cm): UART, I²C, SPI. **Kart dışı, uzun kablo:** RS-485 (veya RS-232, CAN). Kart içi bir protokolü metrelerce kabloya taşımak sorun çıkarır.
2. **UART:** TX → RX **çapraz** bağlanır; boştayken hat yüksektedir. İki tarafın toplam saat hatası küçük olmalı → kristal veya kalibre edilmiş osilatör.
3. **RS-485:** iki telin **farkıyla** konuşur; gürültü iki tele eşit bindiği için farkı bozmaz. **120 Ω sonlandırma yalnızca iki uçta**; hat boşta kalınca belirsiz olmasın diye **bias** dirençleri.
4. **I²C:** hatlar açık-drenajdır; yüksek seviyeyi **pull-up** direnci verir. Değeri hız ve hat kapasitansından hesaplanır; hatta **tek set** pull-up olur.
5. **SPI:** hızlıdır; her slave'in kendi **CS**'i vardır. CS'lerde **pull-up**: açılışta hiçbir slave seçili olmasın. Çok sayıda slave'de **kod çözücü**, aynı anda tek CS'yi donanımla garanti eder.
6. **3,3 V ↔ 5 V:** Karşı tarafın giriş eşiğine (VIH) bak. 3,3 V çıkış, 5 V CMOS girişini güvenle süremez.
7. Hızlı kenarlı hatlarda sürücü tarafına **22–33 Ω seri direnç**.
8. Kartın dışına çıkan her hat: **konnektörde ESD/TVS**, seri direnç, gerekirse ortak mod bobini ve filtre. Binalar arası gibi toprak farkı büyük yerlerde **yalıtım**.

## 🧮 Formül kartı

| Formül | Ne zaman kullanılır | Örnek |
|---|---|---|
| `t_bit = 1 / baud` | UART bit süresi (osiloskopta ölçmek için) | 115200 → **8,68 µs** |
| `R_min = (VDD − 0,4 V) / 3 mA` | I²C pull-up alt sınırı | 3,3 V → **967 Ω** |
| `R_max = t_r / (0,8473 × C_b)` | I²C pull-up üst sınırı | 400 kHz (t_r 300 ns), 200 pF → **1,77 kΩ** |
| `V_fark = V × R_T / (2·R_bias + R_T)` | RS-485 boşta fark gerilimi (≥ 200 mV olmalı) | 5 V, 560 Ω, R_T = 60 Ω → **254 mV** |
| `R_T = 120 Ω // 120 Ω = 60 Ω` | RS-485 iki uç sonlandırma birlikte | — |

---

## 1. Kart içi mi, kart dışı mı?

**Benzetme:** Kart içi arayüzler aynı odada **konuşmak** gibidir: kısa mesafe, sessiz ortam. Kart dışı arayüzler gürültülü bir fabrikada **telefonla** konuşmak gibidir: uzun hat, her yerden gürültü. Odada fısıldamak yeter; fabrikada farklı bir yöntem gerekir.

| Arayüz | Tel sayısı | Mesafe | Hız | Çok cihaz | Nerede |
|---|---|---|---|---|---|
| UART (TTL) | 2 + GND | Kart içi, kısa kablo | ≤ ~1 Mbps | Hayır (noktadan noktaya) | Debug, modül bağlantısı |
| RS-232 | 2 + GND | ~15 m | Düşük | Hayır | Eski cihazlar, servis portu |
| **RS-485** | 2 (+ GND referansı) | **~1200 m** (düşük hızda) | 10 Mbps'e kadar (kısa) | **Evet, 32+ cihaz** | Saha cihazları, Modbus, bina sistemleri |
| I²C | 2 + GND | Kart içi | 100 kHz – 1 MHz | Evet (adresli) | Sensör, EEPROM, RTC |
| SPI | 3 + her slave için CS | Kart içi | MHz'ler | Evet (CS ile) | Flash, ekran, ADC |
| CAN | 2 (+ GND) | Yüzlerce m | ≤ 1 Mbps | Evet | Araç, endüstri |

## 2. UART

```
 MCU                     Modül
 UART_TX ──────────────► RX
 UART_RX ◄────────────── TX
 GND ─────────────────── GND
```

- **Çerçeve:** 1 start biti (0), 8 veri biti, 1 stop biti (1). Boştayken hat **1**'dir. Osiloskopta bir bitin süresini ölçerek baud hızını doğrulayabilirsin.
- **Çapraz bağlantı:** Bir tarafın TX'i diğerinin RX'ine. Net isimlerinde **kimin bakışından** olduğunu yaz: `MCU_TX` → modülün RX'ine.
- **Saat doğruluğu:** İki taraf aynı hızda saymazsa son bitlere doğru kayma büyür. İki tarafın toplam hatası yaklaşık **%2'nin altında** kalmalı. MCU'nun dahili RC osilatörü oda sıcaklığında yeterli olabilir ama sıcaklıkla birkaç %'ye kayabilir; sahada güvenilir haberleşme için **kristal** veya kalibrasyon.
- **RX pull-up:** Kablo takılı değilken boştaki RX gürültü kapar ve sahte veri gelir. RX'e pull-up (ör. 10–100 kΩ) koy ya da MCU'nun dahili pull-up'ını aç.
- **TTL ≠ RS-232:** RS-232'de gerilim ±3…±15 V'tur ve mantık terstir. MCU pinine doğrudan bağlanmaz; arada bir RS-232 sürücü IC'si (ör. MAX3232 tipi) olur.
- **Her karta bir debug UART'ı:** 3 pinlik bir başlık (GND, TX, RX) veya test pedi. Sahada ve üretimde çok iş görür.

## 3. RS-485

**Neden fark sinyali?** Uzun kabloya bir gürültü bindiğinde iki tele **aynı anda ve aynı miktarda** biner. Alıcı yalnızca `A − B` farkına baktığı için ortak gürültü birbirini götürür. Gürültülü bir fabrikada iki kişinin aynı anda bağırması değil, **aralarındaki farkın** duyulması gibi.

```
 Cihaz 1 (uç)                 Cihaz 2           Cihaz 3 (uç)
 ┌──────┐                    ┌──────┐           ┌──────┐
 │  A ──┼────────────────────┼──────┼───────────┼── A  │
 │ [120]│                    │      │           │[120] │
 │  B ──┼────────────────────┼──────┼───────────┼── B  │
 │ GND ─┼──── referans ──────┼──────┼───────────┼─ GND │
 └──────┘                    └──────┘           └──────┘
  sonlandırma VAR             sonlandırma YOK    sonlandırma VAR
```

**Kurallar:**
1. **Topoloji:** Cihazlar hatta **sırayla** (zincir gibi) bağlanır. Yıldız bağlantı ve uzun dal (stub) kullanılmaz.
2. **Sonlandırma: 120 Ω, yalnızca iki fiziksel uçta.** Kablo bir dalga kılavuzu gibidir; ucunda sonlandırma yoksa sinyal yansır ve kendi kendine karışır. Ortadaki cihazlara da 120 Ω takılırsa yük ağırlaşır ve sürücü hattı süremez. Kartta sonlandırmayı **jumper veya DNP** ile seçilebilir yap.
3. **Bias (fail-safe):** Kimse konuşmazken hat boşta kalır ve fark gerilimi 0 V civarında olur. Alıcı ±200 mV'un altını belirsiz görür ve sahte karakterler üretir. Çözüm: A'ya pull-up, B'ye pull-down.
   - **Örnek:** 5 V, iki uçta 120 Ω (birlikte 60 Ω), bias dirençleri 560 Ω → `5 × 60 / (2 × 560 + 60) = 254 mV` ✓.
   - 3,3 V'ta aynı dirençler 168 mV verir ✗ → 390 Ω ile 236 mV ✓.
   - Bias hatta **bir kez** (genelde master'da) konur. Alternatif: içinde "true fail-safe" özelliği olan transceiver.
4. **Ortak referans:** Alıcıların çalışabildiği ortak mod aralığı tipik olarak −7 V…+12 V'tur. Cihazların toprakları arasındaki fark bunu aşmamalı. Bu yüzden A ve B'nin yanında bir **referans (GND) teli** çekilir.
5. **Yalıtım:** Binalar veya katlar arasında toprak farkı büyükse **yalıtımlı (izoleli) transceiver** kullanılır.
6. **Yön kontrolü (DE/RE):** İki telli RS-485'te aynı anda tek cihaz konuşur. Firmware, **son stop biti hattan çıkmadan** sürücüyü kapatmamalı; aksi hâlde son karakter bozulur. MCU'nun donanımsal DE desteği veya "gönderim tamamlandı" bayrağı kullanılır.
7. **A/B isimleri:** Üreticiler A ve B'yi farklı adlandırabiliyor. Hiç iletişim yoksa ilk denenecek şey A–B'yi çevirmek.
8. **Koruma:** Uzun kablo, darbe ve ESD demektir. RS-485'in −7…+12 V aralığına uygun TVS (ör. SM712 tipi asimetrik TVS) konnektörün yanında.

**Kapasite:** Standart 32 "birim yük" tanımlar. 1/8 birim yüklü transceiver'larla hatta 256 cihaz bağlanabilir. Mesafe ve hız ters orantılıdır: ~1200 m'de ~100 kbps; 10 Mbps ancak kısa hatlarda.

## 4. I²C

**Açık-drenaj nedir?** Hattaki her cihaz hattı yalnızca **aşağı çekebilir**; yukarı çeken bir **pull-up direncidir**. Bir ipi düşün: herkes ipi aşağı çekebilir, bırakınca bir yay (pull-up) ipi yukarı çeker. Kimse çekmiyorsa ip yukarıdadır (1).

**Pull-up değeri iki sınırın arasında seçilir:**
- **Alt sınır:** Direnç çok küçükse cihaz hattı yeterince aşağı çekemez: `R_min = (VDD − 0,4 V) / 3 mA`.
- **Üst sınır:** Direnç çok büyükse hat kapasitansı yavaş dolar, kenar yavaş kalkar: `R_max = t_r / (0,8473 × C_b)`.

| Mod | t_r (en fazla) | C_b = 100 pF | C_b = 200 pF | C_b = 400 pF |
|---|---|---|---|---|
| Standart (100 kHz) | 1000 ns | 11,8 kΩ | 5,9 kΩ | 2,95 kΩ |
| Hızlı (400 kHz) | 300 ns | 3,54 kΩ | 1,77 kΩ | 885 Ω |

**Örnek:** 3,3 V, hızlı mod, ~100 pF → R_min 967 Ω, R_max 3,54 kΩ → **2,2 kΩ** iyi bir seçim.

**Dikkat:**
- **Tek set pull-up:** Her modül kendi pull-up'ı ile gelirse paralel bağlanırlar ve toplam direnç çok küçülür. Hatta bir set kalsın; diğerlerini DNP yap.
- **Hat kapasitansı:** Her cihazın pini ve her cm iz kapasitans ekler; sınır 400 pF'dir. I²C **kablo için tasarlanmamıştır**. Kart dışına çıkması gerekiyorsa I²C hat uzatıcı/tampon IC'si veya farklı bir arayüz kullan.
- **Adres çakışması:** Aynı adresli iki cihaz aynı hatta olamaz. Adresleri şematikte not et.
- **Hat kilitlenmesi:** MCU bir aktarımın ortasında reset olursa, slave SDA'yı aşağıda tutmaya devam edebilir ve hat kilitlenir. Firmware açılışta SCL'ye **9 saat darbesi** vererek hattı kurtarabilir; kritik cihazlarda slave'in beslemesini kesebilmek de bir çözümdür.

## 5. SPI

```
 MCU (master)          Slave 1          Slave 2
 SCK  ───────────────► SCK ───────────► SCK
 MOSI ───────────────► SDI ───────────► SDI
 MISO ◄─────────────── SDO ◄─────────── SDO
 CS1  ───────────────► CS
 CS2  ────────────────────────────────► CS
```

- **Her slave'in kendi CS'i (aktif düşük).** CS yüksekken slave MISO'yu bırakır (yüksek empedans) ve hattı diğerine açar.
- **CS pull-up'ları:** Açılışta MCU pinleri boştayken bir slave seçili gibi davranırsa MISO'da çakışma olur ya da Flash'a istenmeyen komut gidebilir. Her CS'ye pull-up (ör. 10–47 kΩ).
- **Çok sayıda slave ve az pin:** Bir **kod çözücü** (ör. 74HC138, 3 giriş → 8 çıkış) 3 pinle 8 CS üretir. Kod çözücü aynı anda **asla iki çıkışı seçmez**; firmware hatası olsa bile iki slave aynı anda konuşamaz. Kod çözücünün enable pini de açılışta pull-up/down ile "kapalı" tutulmalı. 74HC138'in çıkışları aktif düşük olduğu için doğrudan CS'ye uyar.
- **Mod (CPOL/CPHA):** Master ve slave aynı modda olmalı. Veri "bir bit kaymış" gibi geliyorsa ilk şüpheli moddur.
- **Hız ve iz:** MHz'lerdeki SCK, uzun izde çınlar. Sürücü tarafına 22–33 Ω seri direnç; SCK'yi analog bölgeden uzak geçir.
- SPI kısa bir şerit kablo dışında kart dışına çıkarılmaz.

## 6. Seviye çevirme: 3,3 V ↔ 5 V

**Soru her zaman aynı:** Alıcının giriş eşiği (VIH / VIL) ne, vericinin çıkışı (VOH / VOL) bunu sağlıyor mu?

| Bağlantı | Sonuç | Çözüm |
|---|---|---|
| 3,3 V çıkış → 5 V **CMOS** girişi (VIH = 0,7 × 5 = 3,5 V) | ✗ Garanti değil | 5 V beslemeli **74HCT** tampon (girişi TTL eşikli, VIH = 2,0 V) veya çevirici IC |
| 3,3 V çıkış → 5 V **TTL uyumlu** giriş (VIH = 2,0 V) | ✓ | Doğrudan |
| 5 V çıkış → 3,3 V MCU, pin **5 V toleranslı** | ✓ (koşullu) | Pin dijital modda olmalı; MCU kapalıyken gelen 5 V back-powering yapabilir |
| 5 V çıkış → 3,3 V MCU, pin toleranslı değil | ✗ | Bölücü (yavaş sinyal), 5 V toleranslı girişli 74LVC tampon |
| I²C 3,3 V ↔ 5 V | Çift yönlü, açık-drenaj | MOSFET'li (BSS138 tipi) çevirici veya I²C'ye özel çevirici IC |

> **Tuzak:** Otomatik yön algılayan genel amaçlı çeviriciler (TXB tipi) açık-drenaj hatlarda (I²C) ve güçlü yüklerde sorun çıkarır. I²C için I²C'ye uygun çevirici seç.

## 7. Hızlı kenarlar ve seri sonlandırma

Bir MCU pininin kenarı birkaç nanosaniyedir. Kenar ne kadar hızlıysa, iz o kadar kısa mesafede bir "hat" gibi davranmaya başlar ve uçtan yansıyan sinyal çınlama (ringing) yapar.

- **Kural:** Kart içinde ~10 cm'yi geçen hızlı saat ve veri hatlarında **sürücü tarafına 22–33 Ω seri direnç** koy (veya yerini bırak).
- Seri direnç çınlamayı ve aşmayı (overshoot) azaltır, EMI'yi düşürür.
- MCU'nun GPIO hız ayarını gereken en düşük seviyede tut ([MCU dersi, EMC](../../Komponentler/05-mikrodenetleyici-donanimi/ozet.md#10-emc-açısından)).

## 8. Kartın dışına çıkan hatlar

Kablo, hem bir **anten** (gürültü yayar ve toplar) hem de **ESD ve darbelerin giriş kapısıdır**.

| Önlem | Ne işe yarar | Nereye |
|---|---|---|
| ESD/TVS diyotu | ESD ve darbeyi kenetler | **Konnektörün dibinde**, kısa ve geniş GND |
| Seri direnç | Koruma diyotlarına giden akımı sınırlar, kenarı yumuşatır | TVS'den sonra |
| Ortak mod bobini (CMC) | Diferansiyel sinyali geçirir, ortak mod gürültüyü bastırır | RS-485, USB, CAN çiftleri |
| Ferrit + kapasitör | Tek uçlu hatlarda yüksek frekans filtresi | Konnektör girişi |
| **Üç uçlu kapasitör** | Yüzlerce MHz – GHz gürültüyü toprağa kaçırır | Telsiz/GSM gürültüsünün kabloyla girdiği hatlar |
| Kablo ekranı | Alanı keser | Konnektörde 360° sonlandırma |
| Galvanik yalıtım | Toprak farkını ve toprak döngüsünü keser | Binalar arası, uzun hatlar |

**Üç uçlu kapasitör neden daha iyi?** Normal kapasitörün toprağa giden yolunda pad, via ve iç yoldan oluşan küçük bir gizli bobin (ESL) vardır. Yüksek frekansta bu bobin baskın olur ve kapasitör "tel" olmaktan çıkar. Üç uçlu kapasitörde sinyal parçanın içinden geçer, toprak bağlantısı kısa ve geniştir; gizli bobin onlarca kat küçüktür. Toprak pad'lerini **birden fazla via** ile doğrudan GND düzlemine bağla; hattın akımı parçanın içinden geçtiği için **akım değerini** kontrol et.

Ayrıntı: [EMC için kart tasarımı, bölüm 6–7](../../EMC/02-emc-icin-kart-tasarimi/ozet.md#7-esd-koruması).

## 9. Şematikte

- Net isimleri yönüyle: `MCU_UART2_TX`, `RS485_A`, `RS485_B`, `I2C1_SDA`, `SPI1_CS_FLASH`.
- RS-485: sonlandırma **jumper veya DNP** ile; bias değerleri ve hesap notu; DE/RE bağlantısı; TVS.
- I²C: pull-up değeri ve hesap; hattaki cihazların **adres listesi**; diğer modüllerin pull-up'ları DNP.
- SPI: her CS'de pull-up; slave'lerin SPI modu notu.
- Debug UART başlığı ve haberleşme hatlarında test noktaları.
- Farklı gerilim domainleri arasındaki her sinyalde seviye kontrolü notu.

## 10. PCB / layout

- RS-485 A ve B **yan yana, eşit uzunlukta** bir çift olarak gider; koruma ve sonlandırma konnektöre yakın.
- I²C hatları kısa; SPI saat hattı analog bölgeden ve kristalden uzak; seri dirençler **sürücüye** yakın.
- Haberleşme izlerinin altındaki GND düzlemi **kesintisiz**; yarık üstünden geçen hızlı hat güçlü bir antendir.
- Konnektörler mümkünse kartın **tek kenarında**, koruma elemanları konnektör ile devre arasında.
- Yalıtımlı transceiver'da yalıtım bariyerinin altından bakır geçmez; iki tarafın toprakları ayrı kalır.

## 11. EMC açısından

- Konnektöre dokunan her hat ESD (IEC 61000-4-2) görür; uzun kablolar EFT (61000-4-4) ve surge (61000-4-5) taşır ([EMC 03](../../EMC/03-emc-testleri-ve-standartlar/ozet.md)).
- Fark sinyalli hatlar (RS-485, CAN) ortak mod gürültüye doğal olarak dayanıklıdır; CMC bunu daha da güçlendirir.
- Haberleşmeyi yazılımla da sağlamlaştır: CRC, zaman aşımı, tekrar deneme ([EMC 02, bölüm 9](../../EMC/02-emc-icin-kart-tasarimi/ozet.md#9-yazılımla-bağışıklık)).

## 12. Ölçüm ve doğrulama

1. **Lojik analizör / osiloskop çözümleme:** UART, I²C ve SPI çerçevelerini ekranda oku.
2. **UART baud:** Bir bitin süresini ölç (115200 → 8,68 µs).
3. **I²C yükselme süresi:** Kenarın %30'dan %70'e çıkış süresi standarttaki sınırın altında mı? Değilse pull-up'ı küçült.
4. **RS-485:** Osiloskopta A − B farkını izle (matematik fonksiyonu veya diferansiyel prob). Boştayken fark ≥ 200 mV mi? Uzun kabloda en yüksek hızda hata sayısı?
5. **SPI:** SCK'de çınlama var mı? Varsa seri direnç.
6. **Kablo testi:** Gerçek uzunlukta kabloyla ve sahadaki gibi topraklamayla dene.

## 13. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| UART TX'i TX'e bağlamak | İletişim yok | Çapraz bağlantı |
| Dahili RC osilatörle sahada UART | Sıcaklıkta baud kayar, hata | Kristal veya kalibrasyon |
| RS-485'te her cihaza 120 Ω | Sürücü hattı süremez | Yalnızca iki uçta |
| RS-485'te bias yok | Boşta sahte karakterler | A pull-up, B pull-down; hesapla |
| RS-485'te GND referansı yok | Ortak mod aralığı aşılır | Referans teli veya yalıtım |
| Her I²C modülünde pull-up | Toplam direnç çok küçük | Tek set |
| I²C'yi metrelerce kabloyla taşımak | Kapasitans ve gürültü | Hat uzatıcı veya RS-485 |
| CS'lerde pull-up yok | Açılışta çakışma, istenmeyen komut | Her CS'ye pull-up |
| 3,3 V çıkışla 5 V CMOS girişini sürmek | Eşik garanti değil | 74HCT veya çevirici |
| Konnektörde koruma yok | ESD'de port yanar | TVS konnektörün dibinde |

## 14. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Baud** | Saniyedeki sembol (bit) sayısı |
| **Diferansiyel sinyal** | Bilginin iki telin farkıyla taşınması |
| **Ortak mod** | İki tele aynı anda ve eşit binen gerilim |
| **Sonlandırma** | Hattın ucunda yansımayı önleyen direnç (RS-485'te 120 Ω) |
| **Fail-safe bias** | Hat boştayken tanımlı bir fark gerilimi veren dirençler |
| **Birim yük (UL)** | RS-485'te bir alıcının hatta getirdiği standart yük |
| **DE / RE** | RS-485 transceiver'da sürücü / alıcı etkinleştirme pinleri |
| **Açık-drenaj** | Hattı yalnızca aşağı çekebilen çıkış; yukarıyı pull-up verir |
| **CS (chip select)** | SPI'da konuşacak slave'i seçen hat |
| **CPOL / CPHA** | SPI saatinin boştaki seviyesi / verinin hangi kenarda okunduğu |
| **VIH / VIL** | Girişin kesin 1 / kesin 0 saydığı gerilim sınırları |
| **CMC** | Ortak mod bobini |
| **Galvanik yalıtım** | İki devre arasında doğrudan iletken bağlantı olmaması |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.4, bölüm 7–8):

- [x] RS-485: 120 Ω sonlandırma yalnızca uç cihazlarda (jumper/DNP); bias hesabı ile boşta fark ≥ 200 mV; GND referansı veya yalıtım
- [x] RS-485 DE/RE kontrolü firmware'de son stop bitinden sonra bırakılıyor
- [x] UART'ta saat kaynağı sıcaklık aralığında yeterli (kristal veya kalibrasyon); RX'te pull-up
- [x] I²C cihaz adresleri listelendi; hat uzunluğu ve kapasitansı kart içiyle sınırlı
- [x] Çok sayıda SPI slave'inde kod çözücü kullanıldıysa enable'ı açılışta kapalı
- [x] Debug UART başlığı veya test pedi var

## Kontrol soruları

→ [quiz.md](quiz.md) · 10 soru, 4'ü hesap
