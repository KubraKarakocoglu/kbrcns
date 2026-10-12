# Quiz · EMC testleri ve standartlar

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. 12 soru, 2'si hesap.

## Sorular

1. Gaz algılama cihazları için EMC ürün standardı hangisidir?
   - A) EN 61000-6-3
   - B) IEC 61000-4-2
   - C) EN 50270
   - D) CISPR 32

2. Bir ürün için hem ürün standardı hem de genel (generic) standart mevcutsa hangisi uygulanır?
   - A) Her zaman genel standart
   - B) Hangisi daha kolaysa
   - C) İkisi de uygulanmaz
   - D) Ürün standardı (önceliklidir)

3. ESD bağışıklık testinin temel standardı hangisidir?
   - A) IEC 61000-4-4
   - B) IEC 61000-4-5
   - C) IEC 61000-4-8
   - D) IEC 61000-4-2

4. Performans kriteri **B** ne anlama gelir?
   - A) Test sırasında geçici bozulma olabilir; test sonrası cihaz kendiliğinden normale döner
   - B) Cihaz hiç etkilenmez
   - C) Cihazın normale dönmesi için kullanıcı müdahalesi gerekir
   - D) Cihaz kalıcı olarak bozulur

5. ESD testinde seviye 4 kontak deşarj gerilimi kaçtır?
   - A) 2 kV
   - B) 4 kV
   - C) 8 kV
   - D) 15 kV

6. Surge testinde kullanılan dalga şekilleri hangisidir?
   - A) 5/50 ns
   - B) 1,2/50 µs gerilim ve 8/20 µs akım
   - C) 10/700 ms
   - D) 50 Hz sinüs

7. İletimli emisyon tipik olarak hangi frekans aralığında ve hangi düzenekle ölçülür?
   - A) 30 MHz – 1 GHz, anten
   - B) 150 kHz – 30 MHz, LISN / AMN
   - C) 1 – 6 GHz, akım probu
   - D) DC – 50 Hz, multimetre

8. Class A ve Class B emisyon sınırları için hangisi doğrudur?
   - A) Class B konut ortamı içindir ve sınırları daha sıkıdır
   - B) Class A konut, Class B endüstri içindir
   - C) İkisi aynıdır
   - D) Class B yalnızca bağışıklığı kapsar

9. Masada yapılan ön ölçümlerde ışınımlı emisyonun en iyi göstergesi hangisidir?
   - A) Kablolardaki ortak mod akımı (RF akım probu ile)
   - B) Besleme geriliminin DC değeri
   - C) Kartın sıcaklığı
   - D) MCU'nun saat frekansı

10. Işınımlı RF bağışıklık testinde bir gaz dedektörünün analog okuması kayıyor. En olası mekanizma nedir?
    - A) RF alanı sensörü ısıtıyor
    - B) MCU'nun saat frekansı değişiyor
    - C) Op-amp girişleri RF'yi doğrultarak DC kaymaya çeviriyor
    - D) Kasa manyetize oluyor

11. **(Hesap)** Ön ölçümde bir emisyon tepesi sınırın 6 dB altında ölçüldü. Ölçülen alan şiddeti sınır değerin yaklaşık ne kadarıdır?
    - A) %10'u
    - B) Yarısı
    - C) %25'i
    - D) %90'ı

12. **(Hesap)** Ölçülen alan şiddeti 34 dBµV/m, sınır 40 dBµV/m. Sınır µV/m cinsinden 100 µV/m ise ölçülen değer yaklaşık kaç µV/m'dir?
    - A) 25 µV/m
    - B) 85 µV/m
    - C) 150 µV/m
    - D) 50 µV/m

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **C** — EN 50270, yanıcı ve zehirli gazlar ile oksijen algılama cihazlarının EMC standardıdır. EN 61000-6-3 genel emisyon standardı, IEC 61000-4-2 ESD test yöntemi, CISPR 32 multimedya cihazlarının emisyon standardıdır.

2. **D** — Ürün standardı o ürün ailesine özgü testleri, seviyeleri ve performans kriterlerini tanımladığı için önceliklidir.

3. **D** — -4-4 EFT/burst, -4-5 surge, -4-8 güç frekansı manyetik alanıdır.

4. **A** — Kriter A: hiç etkilenmez · kriter B: geçici bozulur, kendiliğinden düzelir · kriter C: müdahale gerekir.

5. **C** — Kontak deşarj seviyeleri 2 / 4 / 6 / 8 kV; hava deşarjında seviye 4 15 kV'tur.

6. **B** — Surge testinde açık devrede 1,2/50 µs gerilim, kısa devrede 8/20 µs akım dalgası tanımlanır. Nanosaniyelik darbeler EFT testine aittir.

7. **B** — İletimli emisyon güç portunda LISN/AMN ile 150 kHz–30 MHz'te ölçülür. Işınımlı emisyon 30 MHz'ten itibaren anten ile ölçülür.

8. **A** — Class B konut ortamı içindir ve sınırları Class A'dan yaklaşık 10 dB daha sıkıdır.

9. **A** — 30–300 MHz bandında ışınımlı emisyonun büyük kısmı kablolardaki ortak mod akımından gelir. Bu akımı ölçmek, odada ölçülecek alan şiddetinin iyi bir habercisidir.

10. **C** — Op-amp girişindeki doğrusal olmayan yapılar RF'yi doğrultur ve sinyale DC bir kayma ekler. Girişlerde RC filtre ve kısa izler bu etkiyi azaltır.

11. **B** — `−6 dB = 10^(−6/20) ≈ 0,5`. Ölçülen değer sınırın yaklaşık yarısıdır.

12. **D** — Fark 6 dB; `100 µV/m × 10^(−6/20) ≈ 50 µV/m`. Kontrol: 50 µV/m = `20 × log10(50) ≈ 34 dBµV/m`.

</details>
