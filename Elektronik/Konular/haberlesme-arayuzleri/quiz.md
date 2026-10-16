# Quiz · Haberleşme arayüzleri: elektriksel taraf

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 10 soru, 4'ü hesap.

## Sorular

1. **(Hesap)** I²C hızlı modda (400 kHz, t_r ≤ 300 ns) hat kapasitansı 200 pF. Pull-up direncinin üst sınırı yaklaşık kaçtır?
   - A) 11,8 kΩ
   - B) 1,77 kΩ
   - C) 5,9 kΩ
   - D) 177 Ω

2. **(Hesap)** 3,3 V'luk bir I²C hattında pull-up direncinin alt sınırı yaklaşık kaçtır (VOL = 0,4 V, 3 mA)?
   - A) 1,1 kΩ
   - B) 133 Ω
   - C) 9,7 kΩ
   - D) 967 Ω

3. **(Hesap)** 5 V'luk bir RS-485 hattının iki ucunda 120 Ω sonlandırma var. Bias dirençleri 560 Ω. Hat boştayken fark gerilimi kaçtır ve yeterli midir?
   - A) Yaklaşık 254 mV; ±200 mV eşiğinin üstünde olduğu için yeterli
   - B) 2,5 V; fazlasıyla yeterli
   - C) 54 mV; yetersiz
   - D) 0 V; bias işe yaramaz

4. **(Hesap)** 115200 baud'luk bir UART'ta bir bitin süresi yaklaşık kaçtır?
   - A) 115 µs
   - B) 0,87 µs
   - C) 8,68 µs
   - D) 86,8 µs

5. Beş cihazın zincir şeklinde bağlandığı bir RS-485 hattında 120 Ω sonlandırma dirençleri nereye takılır?
   - A) Her cihaza
   - B) Yalnızca master'a
   - C) Ortadaki cihaza
   - D) Yalnızca hattın iki fiziksel ucundaki cihazlara

6. Uzun ve gürültülü bir kabloda RS-485, TTL seviyeli UART'tan neden çok daha güvenilirdir?
   - A) Bilgi iki telin farkıyla taşınır; gürültü iki tele eşit bindiği için fark bozulmaz
   - B) Daha yüksek gerilim kullandığı için
   - C) Daha yavaş olduğu için
   - D) Kablo gerektirmediği için

7. SPI'daki CS hatlarına neden pull-up direnci konur?
   - A) SPI hızını artırmak için
   - B) MISO'yu güçlendirmek için
   - C) Açılışta MCU pinleri boştayken hiçbir slave'in seçili olmaması için; böylece MISO'da çakışma ve istenmeyen komut olmaz
   - D) Saat hattını sonlandırmak için

8. 3,3 V'luk bir MCU çıkışı, 5 V ile beslenen ve VIH = 0,7 × VDD olan bir CMOS girişini sürüyor. Hangisi doğrudur?
   - A) Her zaman güvenle çalışır
   - B) Giriş eşiği 3,5 V olduğu için 3,3 V'luk seviye 1 olarak garanti edilmez; 5 V beslemeli 74HCT tampon veya seviye çevirici kullanılmalıdır
   - C) Araya seri direnç koymak yeterlidir
   - D) 5 V cihazın girişi 3,3 V'ta yanar

9. MCU bir I²C aktarımının ortasında reset oldu; açılıştan sonra SDA sürekli düşük kalıyor. Yaygın kurtarma yöntemi hangisidir?
   - A) SCL'ye 9 saat darbesi vererek slave'in aktarımı tamamlayıp SDA'yı bırakmasını sağlamak; kritik cihazlarda slave beslemesini kesebilmek
   - B) Pull-up dirençlerini sökmek
   - C) Hattı 5 V'a çekmek
   - D) Hiçbir şey yapılamaz

10. İki ayrı binadaki cihazlar arasında RS-485 hattı çekiliyor; binaların toprakları arasında birkaç volt fark ölçülüyor. En sağlam çözüm hangisidir?
    - A) Sonlandırma direncini büyütmek
    - B) Baud hızını artırmak
    - C) A ve B'yi değiştirmek
    - D) Yalıtımlı (izoleli) RS-485 transceiver kullanmak; böylece toprak farkı alıcının ortak mod aralığını zorlamaz

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **B** — `R_max = 300 ns / (0,8473 × 200 pF) ≈ 1,77 kΩ`. Daha büyük direnç kenarı yavaşlatır ve hızlı mod sınırı aşılır.

2. **D** — `R_min = (3,3 − 0,4) / 0,003 ≈ 967 Ω`. Daha küçük direnç, cihazın hattı 0,4 V'un altına çekebilmesi için 3 mA'den fazla akım gerektirir.

3. **A** — İki uçtaki 120 Ω birlikte 60 Ω'dur. `5 × 60 / (2 × 560 + 60) ≈ 0,254 V`. Alıcılar ±200 mV'un üstünü kesin seviye olarak görür; 254 mV yeterlidir. 3,3 V'ta aynı dirençler yalnızca 168 mV verir.

4. **C** — `t = 1 / 115200 ≈ 8,68 µs`. Osiloskopta tek bir bitin süresini ölçmek, baud hatasını bulmanın en hızlı yoludur.

5. **D** — Sonlandırma, sinyalin hattın ucundan yansımasını önler; yansıma yalnızca iki uçta oluşur. Her cihaza takılırsa paralel dirençler hattı çok ağır yükler ve sürücü yeterli gerilimi üretemez.

6. **A** — Uzun kabloya binen gürültü iki tele hemen hemen eşit biner. Alıcı A − B farkına baktığı için ortak gürültü birbirini götürür. TTL UART ise tek tele ve toprağa göre çalışır; gürültü doğrudan sinyale eklenir.

7. **C** — Reset ve açılış sırasında MCU pinleri yüksek empedanstadır. Boştaki bir CS düşük algılanırsa birden fazla slave MISO'yu aynı anda sürebilir veya Flash'a istenmeyen bir komut gidebilir. Pull-up hepsini seçilmemiş tutar.

8. **B** — 5 V CMOS girişi için kesin 1 seviyesi 3,5 V ve üstüdür; 3,3 V bu sınırın altında kalır. 74HCT ailesi 5 V ile beslenir ama girişleri TTL eşiklidir (VIH = 2,0 V); 3,3 V'u güvenle algılar ve 5 V çıkış verir.

9. **A** — Slave hâlâ bir baytın ortasında olduğunu sanır ve SDA'yı bırakmaz. Master SCL'ye en fazla 9 darbe verince slave baytı tamamlar ve SDA'yı bırakır; ardından bir STOP koşulu gönderilir.

10. **D** — Alıcıların ortak mod aralığı sınırlıdır (tipik −7…+12 V). Binalar arasındaki toprak farkı, darbeler ve yıldırım bu aralığı zorlar. Yalıtımlı transceiver iki tarafın toprağını galvanik olarak ayırır ve toprak döngüsünü de keser.

</details>
