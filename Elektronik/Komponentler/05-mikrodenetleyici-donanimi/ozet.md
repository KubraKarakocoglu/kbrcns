# 05 · Mikrodenetleyici donanımı

- **Oluşturma:** 2026-10-12
- **İlk kaynak:** ST AN4488 – *Getting started with STM32F4xxxx MCU hardware development* (st.com'da adıyla arat)
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)

> Örnekler STM32 ailesi üzerinden verilmiştir; mantık tüm mikrodenetleyiciler için geçerlidir. Değerler için her zaman kendi MCU'nun datasheet'i ve donanım uygulama notu esastır.

---

## ⚡ Hızlı tekrar

1. Her MCU kartının **minimum sistemi** dört bloktan oluşur: **güç ve decoupling, saat, reset/boot, debug**.
2. Datasheet'in "Power supply scheme" bölümü ve üreticinin donanım uygulama notu (STM32F4 için AN4488) şematiğin **reçetesidir**.
3. **Kristal:** C0G yük kapasitörleri, `C = 2·(C_L − C_stray)`. MCU'ya yakın yerleştir, altından iz geçirme. Frekansı kristale prob değdirerek değil, **MCO** çıkışından ölç.
4. **BOOT0 ve NRST tanımlı olmalı;** debug konnektöründe NRST bulunsun ("connect under reset" için).
5. GPIO'nun **pin başına ve toplam** akım limiti vardır. Yükleri transistör veya MOSFET ile sür.
6. Dış dünyadan gelen girişe **seri direnç + clamp** koy. MCU kapalıyken girişe gerilim verme (**back-powering**).
7. **ADC:** Kaynak empedansı ile örnekleme süresi uyumlu olmalı; pine konan kapasitör yük deposu görevi görür.
8. **EMC ve dayanıklılık için:** GPIO hızını (slew rate) gereken en düşük seviyede tut; **watchdog** ve **BOR** kullan.

## 🧮 Formül kartı

| Formül | Ne zaman kullanılır | Örnek |
|---|---|---|
| `C1 = C2 = 2·(C_L − C_stray)` | Kristal yük kapasitörleri | C_L 12,5 pF, stray 5 pF → 15 pF |
| `LSB = V_ref / 2^N` | ADC çözünürlüğü | 3,3 V, 12 bit → 0,81 mV |
| `t_s ≥ (N+1)·ln2·R·C` | ADC örnekleme süresi (½ LSB'ye oturma) | 12 bit → ~9τ; 10 kΩ × 5 pF → ~450 ns |
| `Hata ≈ C_ADC / C_harici` (LSB cinsinden × 2^N) | Pin kapasitörüyle yük paylaşım hatası | 5 pF / 100 nF → 0,2 LSB |
| `I_inj = (V_in − V_DD − V_diyot) / R_seri` | Clamp diyotuna giren akım | 5 V, 10 kΩ, 3,3 V → ~0,14 mA |
| 4ⁿ kat aşırı örnekleme → +n bit | Ortalama ile çözünürlük artırma | 16× → +2 bit (gürültü varsa) |

---

## 1. Minimum sistem

```
                 ┌────────────── MCU ──────────────┐
  3V3 ──────────►│ VDD × N   100 nF her pine + bulk │
  3V3 ─[boncuk]─►│ VDDA      yerel filtre           │
                 │ VCAP      datasheet değeri       │  (bazı ailelerde)
  3V3 / pil ────►│ VBAT      pil yoksa VDD'ye       │
  Kristal ──────►│ OSC_IN / OSC_OUT  C0G yük C      │
  Reset ────────►│ NRST      100 nF, buton, SWD     │
  Boot ─────────►│ BOOT0     pull-down              │
  Debug ◄──────►│ SWDIO, SWCLK (SWO)                │
                 └──────────────────────────────────┘
```

Her bloğu aşağıda tek tek inceleyeceğiz. Decoupling ayrı derste: [Güç ve decoupling](../../Konular/guc-ve-decoupling/ozet.md).

## 2. Güç

| Pin | Görevi | Dikkat |
|---|---|---|
| **VDD × N** | Ana besleme | Her pine 100 nF + rayda bulk (STM32F4: en az 4,7 µF, tipik 10 µF) |
| **VDDA** | ADC, DAC ve bazı analog bloklar | Birçok STM32'de **ADC kullanılmasa bile bağlanmalıdır**; datasheet'ten doğrula. Ferrit ile ayrılabilir |
| **VREF+** | ADC referansı | Gürültüsü doğrudan ölçüme eklenir |
| **VBAT** | RTC ve yedek domain | Pil yoksa genellikle VDD'ye bağlanır; datasheet'ten doğrula |
| **VCAP** | Dahili regülatörün çıkış kapasitörü (bazı ailelerde) | Datasheet'teki değer ve düşük ESR |

**Brown-out reset (BOR):** Besleme yavaşça düşerken MCU belirsiz bir gerilim bölgesinde rastgele davranabilir: yanlış komut çalıştırma, flash'a bozuk yazma. BOR, gerilim belirli bir eşiğin altına inince MCU'yu temiz şekilde resette tutar. STM32'de eşik option byte ile seçilir. Pil ile çalışan ve gürültülü beslemeli cihazlarda mutlaka etkinleştir.

**Düşük gerilim uyarısı (PVD):** Gerilim düşmeye başladığında kesme üretir; yazılım veriyi kaydetmeye zaman bulur (bkz. [Kapasitör – hold-up](../02-kapasitor/ozet.md)).

## 3. Saat (clock)

| Kaynak | Doğruluk | Ne zaman |
|---|---|---|
| **Dahili RC (HSI)** | Tipik ±%1 (25 °C'de); sıcaklık aralığında daha geniş | Basit işler, düşük hızlı UART (kontrol et) |
| **Harici kristal (HSE)** | Tipik ±10–50 ppm | USB, CAN, hassas zamanlama |
| **32,768 kHz kristal (LSE)** | ppm seviyesi | RTC |
| **Harici aktif osilatör** | ppm seviyesi | Gürültülü ortam, hızlı başlama |

- **USB full-speed** ±%0,25 doğruluk ister; bu yüzden kristal veya MCU'nun USB saat kurtarma (clock recovery) özelliği gerekir.
- **UART** iki taraf arasındaki toplam frekans hatasına birkaç yüzde tolerans gösterir. HSI ile çalışacaksan sıcaklıktaki sapmayı datasheet'ten kontrol et.

### Kristal tasarımı

- **Yük kapasitörleri:** `C1 = C2 = 2·(C_L − C_stray)`. C_L kristalin datasheet'inde yazar; C_stray (pin + iz kapasitansı) tipik 2–5 pF. Örnek: C_L = 12,5 pF, C_stray = 5 pF → **15 pF, C0G**.
- **Kazanç marjı:** Osilatörün güvenle başlaması için MCU'nun kazancı kristalin istediğinden yeterince büyük olmalı. ST AN2867 bunun hesabını anlatır ve marjın 5'in üstünde olmasını önerir. Yüksek ESR'li kristal başlamayabilir.
- **Sürüş seviyesi (drive level):** Kristal fazla sürülürse yaşlanır veya hasar görür.
- **Yerleşim:** Kristal ve kapasitörler OSC pinlerine en yakın konumda olmalı. Altından ve yanından sinyal izi geçmemeli. Kapasitörlerin GND bağlantısı kısa olmalı.
- **LSE (32,768 kHz) çok hassastır:** Çok düşük güçle çalışır; lehim pastası artıkları (flux) ve nem bile başlamasını engelleyebilir. Kartı iyi temizle.
- **Ölçüm:** Osiloskop probunun kapasitansı osilatörü yükler, frekansı kaydırır, hatta durdurur. Saati MCU'nun **MCO** (clock output) pininden dışarı verip orada ölç.

## 4. Reset ve boot

- **NRST:** STM32'de dahili pull-up vardır. Datasheet'in önerdiği kapasitörü (STM32'de tipik 100 nF) GND'ye ekle; hızlı bozucuların yanlış reset üretmesini azaltır. Bir reset butonu ve debug konnektörüne bağlantı ekle.
- **BOOT0:** 10 kΩ pull-down ile flash'tan başlatma. Bir jumper veya buton ile 3,3 V'a çekilebilir olması, MCU'nun dahili bootloader'ına (UART veya USB DFU) girmeyi sağlar. Bu hem kurtarma hem üretimde programlama için faydalıdır.
- **Fail-safe:** Reset sırasında GPIO'lar yüksek empedanstadır (STM32'de çoğu pin reset sonrası giriş veya analog moddadır). Yükleri süren hatları harici pull direnciyle güvenli duruma çek (bkz. [Direnç](../01-direnc/ozet.md)).

## 5. Debug ve programlama

| Sinyal | Görevi |
|---|---|
| SWDIO, SWCLK | Seri debug arayüzü |
| NRST | "Connect under reset" için |
| GND | Referans |
| VTref | Debugger'ın hedef gerilimini algılaması |
| SWO (opsiyonel) | İz (trace) ve printf çıktısı |

- **Standart konnektör:** ARM Cortex Debug 10 pin, 1,27 mm. Yer kısıtlıysa konnektörsüz pogo-pin çözümleri kullanılabilir.
- **Kilitlenme tuzağı:** Firmware SWD pinlerini GPIO olarak ayarlarsa debugger bağlanamaz. NRST konnektördeyse "connect under reset" ile kurtarılır. NRST yoksa kart kilitlenebilir.
- **UART konsol başlığı** (TX, RX, GND) koy; geliştirme sırasında printf ile hata ayıklamak çok zaman kazandırır.
- **Test noktaları:** Tüm güç rayları, MCO, kritik sinyaller.

## 6. GPIO

**Akım limitleri:** Datasheet'in "Absolute maximum ratings" tablosunda hem **pin başına** hem **toplam** (tüm VDD veya VSS pinleri üzerinden) limit vardır. Ayrıca çıkış gerilimi akım arttıkça düşer (VOH/VOL belirli bir akımda tanımlıdır).

**Yük sürme:**
- Birkaç mA'den fazlası veya endüktif yükler için transistör veya MOSFET kullan.
- MOSFET seçerken **R_DS(on)'un 2,5 V veya 3,3 V gate geriliminde** belirtildiğinden emin ol ("logic level" MOSFET). Yalnızca V_GS(th) yeterli değildir; o gerilimde MOSFET yalnızca iletime başlar.
- Gate'e seri direnç ve pull-down ekle; endüktif yükte flyback diyotu koy (bkz. [Bobin](../03-bobin-induktor/ozet.md)).

**5 V tolerans (FT pinler):** Yalnızca belirli pinler, belirli modlarda (dijital giriş, açık savak) 5 V'a dayanır. Analog moddaki pin 5 V'a dayanmaz.

**Back-powering (arkadan beslenme):** MCU kapalıyken bir girişe dışarıdan gerilim gelirse akım pinin ESD clamp diyotundan VDD rayına akar. MCU yarım çalışır, rastgele davranır veya latch-up olur.
- Önlemler: Seri direnç ile akımı datasheet'teki injection current limitinin altında tut; dış sinyalin MCU kapalıyken gelmemesini sağla; ya da güç kapalıyken yüksek empedans olan ("Ioff" özellikli) bir tampon kullan.
- Örnek: 5 V'luk sinyal 10 kΩ üzerinden 3,3 V'luk pine geliyor → `(5 − 3,3 − 0,3) / 10 kΩ ≈ 0,14 mA` injection akımı.

**Kullanılmayan pinler:** Asla boşta giriş olarak bırakma; boşta CMOS girişi akım çeker ve gürültü kapar. Yazılımda **analog moda** al (en düşük tüketim) veya çıkış-alçak yap.

## 7. ADC girişi

**Model:** ADC her örneklemede küçük bir örnekleme kapasitörünü (C_ADC, birkaç pF) kısa sürede şarj eder. Kaynak bu kapasitörü örnekleme süresi içinde doldurabilmeli.

**Kural:** N bitlik doğruluk için ½ LSB'ye oturmak gerekir: yaklaşık `(N+1)·ln2` zaman sabiti. 12 bit için **~9τ**.
- Örnek değerlerle: kaynak empedansı 10 kΩ, C_ADC 5 pF → τ = 50 ns → **~450 ns** örnekleme süresi (ADC'nin iç direnci de eklenir).
- Datasheet genellikle örnekleme süresine karşı izin verilen maksimum kaynak empedansını (R_AIN) tablo olarak verir. O tabloyu kullan.

**Pine kapasitör koymak:** ADC pinine 10–100 nF koymak, örnekleme anında yük deposu görevi görür.
- Yük paylaşım hatası ≈ C_ADC / C_harici. 5 pF / 100 nF → 12 bitte yaklaşık **0,2 LSB**.
- Bedeli: Kaynak direnci ile bu kapasitör bir alçak geçiren filtre oluşturur; hızlı değişen sinyalleri yavaşlatır. Kapasitörün örneklemeler arasında yeniden dolması gerekir.

**Diğer kurallar:**
- **Anti-aliasing:** Girişteki RC filtrenin kesimi, örnekleme frekansının yarısının altında olmalı.
- **Referans kalitesi:** VREF+ üzerindeki gürültü doğrudan sonuca eklenir.
- **Oransal (ratiometric) ölçüm:** Köprü sensörünü ADC referansıyla aynı kaynaktan beslersen, referans gerilimindeki değişim sonuçtan sadeleşir.
- **Aşırı örnekleme:** Sinyalde yeterli gürültü varsa her 4 kat örnekleme 1 bit çözünürlük kazandırır.
- **Toprak:** ADC bölümünü dijital kenarlardan uzak tut, ama GND düzlemini bölme.

## 8. İlk kart: bring-up adımları

1. **Gözle kontrol:** Kısa devre, ters takılmış parça, polarite, lehim köprüsü (özellikle QFN ve ince adımlı paketler).
2. **Enerji vermeden önce** her rayın GND'ye direncini ölç; kısa devre var mı?
3. **Akım sınırlı** laboratuvar güç kaynağıyla ilk enerji (ör. limit 100 mA); akımı izle.
4. **Rayları ölç:** gerilim ve ripple.
5. **Reset hattı** yüksek mi? **Saat** çalışıyor mu (MCO)?
6. **Debugger'ı bağla,** cihaz kimliğini (ID) oku.
7. **LED yak (blinky):** 1 Hz yanıp sönüyorsa saat ayarı da doğrudur.
8. **UART'tan "merhaba"** gönder: printf altyapısı hazır.
9. **Çevre birimlerini tek tek** dene: I²C taraması, ADC okuması...
10. **Her adımı proje kartına not et.**

İpucu: Her güç rayına seri bir 0 Ω direnç koyarsan, onu söküp ampermetre bağlayarak rayların akımını ayrı ayrı ölçebilirsin.

## 9. PCB / layout

- **Decoupling:** [Güç ve decoupling, bölüm 8](../../Konular/guc-ve-decoupling/ozet.md).
- **Kristal:** Bölüm 3'teki kurallar.
- **GND:** MCU'nun altında kesintisiz GND düzlemi. QFN paketlerde alttaki termal pad'i datasheet'e göre via'larla GND'ye bağla.
- **Debug konnektörü** kolay erişilebilir yerde olsun.
- **Analog bölge:** ADC pinlerine giden izler kısa olsun; anahtarlamalı regülatörden ve hızlı sinyallerden uzak tut.
- **Dış dünyaya giden hatlar** konnektörden MCU'ya doğrudan uzun izle gitmesin; konnektör tarafında filtre ve koruma olsun.

## 10. EMC açısından

**Emisyon:**
- Kristal frekansının ve PLL çıkışının harmonikleri emisyon spektrumunda görünür.
- **GPIO hızı:** STM32'de her pinin çıkış hızı (OSPEEDR) ayarlanabilir. En yüksek hız gereksiz yere çok keskin kenarlar üretir. **Gereken en düşük hızı** seç; bu, yazılımla yapılabilecek en ucuz EMC iyileştirmesidir.
- Destekliyorsa saat için **spread spectrum** özelliğini kullan.
- **MCO'yu üretimde kapat:** Dışarı saat veren bir pin küçük bir verici gibi davranır.

**Bağışıklık:**
- **NRST:** ESD'ye hassastır. İzi kısa tut, kapasitörünü koy.
- **Watchdog:** STM32'de bağımsız watchdog (IWDG) kendi dahili saatiyle çalışır; ana saat dursa bile MCU'yu resetler. Kilitlenmeye karşı son savunma hattıdır.
- **BOR:** Besleme bozulmalarında temiz reset sağlar.
- **Yazılım önlemleri:** Giriş değerlerinde makul aralık kontrolü, haberleşmede CRC, çevre birimi ayarlarını periyodik olarak yeniden yazma, güvenli varsayılan durumlar. Ayrıntılar: [EMC için kart tasarımı](../../EMC/02-emc-icin-kart-tasarimi/ozet.md).

## 11. Arıza modları ve sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| BOOT0'ı boşta bırakmak | MCU rastgele bootloader'a girer | Pull-down |
| NRST'yi debug konnektörüne bağlamamak | Firmware SWD'yi kapatınca kart kilitlenir | NRST + connect under reset |
| Kristal yük kapasitörünü yanlış hesaplamak | Frekans kayar veya osilatör başlamaz | Formül ve AN2867 |
| Kristale prob değdirerek ölçmek | Prob yükü osilatörü bozar | MCO pini |
| VDDA veya VBAT'ı bağlamamak | MCU çalışmaz veya tuhaf davranır | Datasheet önerisi |
| GPIO'dan doğrudan röle veya motor sürmek | Pin hasarı, reset | Transistör/MOSFET + flyback diyotu |
| MCU kapalıyken girişe sinyal gelmesi | Back-powering, latch-up | Seri R, Ioff'lu tampon |
| Kullanılmayan pinleri boşta bırakmak | Fazla akım, gürültü | Analog mod |
| ADC'ye yüksek empedanslı kaynak | Hatalı okuma | Örnekleme süresi, pin kapasitörü, tampon op-amp |
| GPIO hızını en yüksekte bırakmak | Gereksiz emisyon | En düşük yeterli hız |
| MCO'yu üretimde açık bırakmak | Emisyon kaynağı | Kapat |
| Watchdog kullanmamak | Kilitlenmede kendiliğinden kurtulamaz | IWDG |

## 12. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **HSI / HSE / LSE** | Dahili RC saat / harici kristal / 32,768 kHz kristal |
| **PLL** | Saat frekansını çarpan devre |
| **MCO** | Microcontroller Clock Output: saati dışarı veren pin |
| **POR / BOR** | Power-on reset / brown-out reset |
| **PVD** | Programmable Voltage Detector: düşük gerilim uyarısı |
| **NRST / BOOT0** | Reset pini / başlatma kaynağını seçen pin |
| **SWD / SWO** | Serial Wire Debug / Serial Wire Output |
| **Injection current** | Pine, clamp diyotları üzerinden giren akım |
| **Back-powering** | Kapalı devrenin giriş pinlerinden beslenmesi |
| **Ioff** | Güç kapalıyken girişin yüksek empedans kalma özelliği |
| **Slew rate** | Çıkış kenarının değişim hızı |
| **IWDG** | Independent Watchdog: bağımsız saatli watchdog |
| **Option bytes** | MCU'nun kalıcı yapılandırma ayarları (BOR seviyesi vb.) |
| **Aşırı örnekleme** | Çok sayıda örneği ortalayarak çözünürlük artırma |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.2, bölüm 5):

- [x] Debug konnektöründe NRST var (connect under reset); saat MCO veya test noktasından ölçülebilir
- [x] MCU kapalıyken gerilim gelebilecek girişlerde back-powering önlemi
- [x] Kullanılmayan pinlerin yazılımda analog moda alınacağı not edildi
- [x] ADC girişlerinde kaynak empedansı ve örnekleme süresi uyumlu (veya pin kapasitörü / tampon)
- [x] Watchdog ve BOR kullanımı planlandı
- [x] MOSFET'ler MCU gerilimine uygun (R_DS(on), 2,5 V veya 3,3 V gate'te belirtilmiş)

## Kontrol soruları

→ [quiz.md](quiz.md) · 12 soru, 4'ü hesap
