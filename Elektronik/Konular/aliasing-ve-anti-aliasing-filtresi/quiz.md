# Quiz · Aliasing ve anti-aliasing filtresi

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında tur yöntemini veya en yakın kat kısayolunu kâğıda yaz. 13 soru, 5'i hesap.

## Sorular

1. Aliasing için en doğru tanım hangisidir?
   - A) ADC çözünürlüğünün ölçüm için yetersiz kalması
   - B) f_s/2'nin üstündeki bir frekansın, örneklemeden sonra daha düşük, sahte bir frekans olarak görünmesi
   - C) Sinyalin uzun kabloda yansıması
   - D) ADC referans gerilimindeki gürültünün ölçüme eklenmesi

2. **(Hesap)** f_s = 100 Hz, girişte filtre yok ve 80 Hz'lik bir bozucu var. Kayıtlı veride hangi frekansta görünür?
   - A) 80 Hz
   - B) 180 Hz
   - C) 40 Hz
   - D) 20 Hz

3. **(Hesap)** f_s = 1 kHz ve girişte filtre yok. 2,04 kHz'lik bir bozucu veride hangi frekansta görünür?
   - A) 40 Hz
   - B) 960 Hz
   - C) 1,04 kHz
   - D) 2,04 kHz

4. **(Hesap)** f_s = 200 Hz ile alınmış bir kayıtta 20 Hz'lik bir dalga görüyorsun. Aşağıdaki giriş frekanslarından hangisi bu 20 Hz'i **üretemez**?
   - A) 180 Hz
   - B) 220 Hz
   - C) 240 Hz
   - D) 380 Hz

5. Gaz sinyalinin bandı 0–1 Hz, f_s = 40 Hz ve girişte filtre yok. 50 Hz şebeke gürültüsü için hangisi doğrudur?
   - A) 10 Hz'e katlanır; gaz bandının dışında kaldığı için yazılımdaki ortalama onu silebilir
   - B) DC'ye katlanır ve gaz sinyalinden ayrılamaz
   - C) f_s'den büyük olduğu için kayıtta hiç görünmez
   - D) 90 Hz'e katlanır

6. **(Hesap)** Firmware ADC'yi filtresiz olarak f_s = 10 Hz ile okuyor. Şebeke frekansı o an 50,02 Hz. Okumada ne görülür?
   - A) 10 Hz'lik bir dalgalanma
   - B) 50 Hz'lik bir dalgalanma
   - C) Yaklaşık 50 saniye periyotla yavaşça inip çıkan bir kayma
   - D) Hiçbir etki; 50 Hz, f_s'nin katı olduğu için kendini yok eder

7. ADC 1 kHz'de örnekliyor. Veri hızını 10 Hz'e düşürmek için en doğru yöntem hangisidir?
   - A) Her 100 örnekten yalnızca birini almak
   - B) Örnekleri 100'lük bloklar halinde ortalamak ve her blok için tek çıkış üretmek
   - C) ADC'yi doğrudan 10 Hz'de çalıştırmak
   - D) Her örneği 100'e bölmek

8. **(Hesap)** R = 10 kΩ ve C = 1,5 µF'lık RC filtre (f_c ≈ 10,6 Hz), 1 kHz'lik bir bozucuyu yaklaşık kaç kat zayıflatır?
   - A) ≈ 10 kat
   - B) ≈ 47 kat
   - C) ≈ 940 kat
   - D) ≈ 94 kat

9. Sinyal bandı 1 Hz, f_s = 1 kHz olan bir sistemde tek kademeli RC anti-aliasing filtresi için en makul f_c hangisidir?
   - A) 0,5 Hz
   - B) 10 Hz
   - C) 500 Hz
   - D) 5 kHz

10. f_s = 1 kHz'de 20 örneklik ortalama, 50 Hz şebeke gürültüsünü neden tamamen siler?
    - A) 20 örnek tam 20 ms eder; bu 50 Hz'in bir tam periyodudur ve sinüsün tam periyot ortalaması sıfırdır
    - B) Ortalama her türlü gürültüyü tamamen siler
    - C) 50 Hz, Nyquist frekansının üstündedir
    - D) 20 sayısı 50'nin böleni değildir

11. Kayıtta 50 Hz'te bir tepe var; gerçek şebeke mi yoksa bir alias mı olduğundan emin değilsin. En hızlı ayırt etme yolu hangisidir?
    - A) ADC çözünürlüğünü artırmak
    - B) Ortalama sayısını iki katına çıkarmak
    - C) f_s'yi biraz değiştirmek (ör. 1000 → 1010 Hz) ve tepenin yerinde kalıp kalmadığına bakmak
    - D) Referans gerilimini değiştirmek

12. RF bağışıklık testinde taşıyıcı 1 kHz sinüsle %80 AM modüle ediliyor ve analog ön kat RF'i doğrultuyor. f_s = 1 kHz ve 20 örneklik ortalama kullanan bir dedektörde ne olur?
    - A) Hiçbir şey; 20 örneklik ortalama 1 kHz'i sıfırlar
    - B) 1 kHz, Nyquist frekansının altında kalır ve sorunsuz süzülür
    - C) 1 kHz'lik zarf 500 Hz'e katlanır
    - D) 1 kHz'lik zarf DC'ye katlanır; ortalama onu silemez ve test boyunca okuma kayar

13. 12. sorudaki dedektörde 50 Hz bastırmasını koruyarak sorunu gidermek için hangi f_s ve ortalama çifti en uygundur?
    - A) f_s = 1,2 kHz, 24 örneklik ortalama
    - B) f_s = 500 Hz, 10 örneklik ortalama
    - C) f_s = 1 kHz, 40 örneklik ortalama
    - D) f_s = 250 Hz, 5 örneklik ortalama

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **B** — Aliasing, örneklemenin kaçınılmaz bir sonucudur: f_s/2'nin üstündeki bir frekans 0 … f_s/2 aralığına katlanır ve gerçek, düşük frekanslı bir sinyalle aynı sayıları üretir. Çözünürlük, yansıma ve referans gürültüsü ayrı konulardır.

2. **D** — Tur yöntemi: x = 80/100 = 0,8 → r = 0,8 > 0,5 → `(1 − 0,8) × 100 = 20 Hz`. Kısayol: `|80 − 100| = 20 Hz`. Ayrıntı: [ozet.md bölüm 3](ozet.md#3-neden-olur-tam-turlar-görünmez).

3. **A** — En yakın 1 kHz katı 2 kHz: `|2040 − 2000| = 40 Hz`. Tur yöntemi: x = 2,04 → r = 0,04 → `0,04 × 1000 = 40 Hz`.

4. **C** — 20 Hz'e düşenler `k·200 ± 20`: 20, 180, 220, 380, 420 … Hz. 240 Hz ise `|240 − 200| = 40 Hz`'e düşer. Ayrıntı: [bölüm 4](ozet.md#4-katlanma-ve-nyquist-frekansı).

5. **A** — `|50 − 40| = 10 Hz`; 10 Hz gaz bandının (0–1 Hz) dışında olduğu için dijital filtre onu siler. Ama dikkat: aynı sistemde 200 Hz'lik bir bozucu (`200 / 40 = 5,0` tur) DC'ye düşer ve ayrılamaz. Bu yüzden filtresiz, düşük f_s yine de risklidir. Ayrıntı: [bölüm 5](ozet.md#5-alias-nereye-düşerse-zarar-verir).

6. **C** — `50,02 / 10 = 5,002` tur → r = 0,002 → `0,002 × 10 = 0,02 Hz`, yani 50 saniyelik periyot. Sensör kayması (drift) gibi görünür ve gaz bandının içindedir. D yanlıştır: f_s'nin tam katındaki bir bozucu yok olmaz, DC'ye katlanır. Ayrıntı: [bölüm 6](ozet.md#6-dcye-katlanma-sabit-ofset-ve-yavaş-kayma).

7. **B** — Örnek atlamak, 10 Hz ile yeniden örneklemektir: 50 Hz DC'ye katlanır. Önce ortalamak hem gürültüyü bastırır hem de 10 Hz'in katlarını sıfırlar. ADC'yi doğrudan 10 Hz'de çalıştırmak (C) aynı sorunu donanımda yaratır. Ayrıntı: [bölüm 9.3](ozet.md#93-seyreltme-tuzağı-önce-ortala-sonra-seyrelt).

8. **D** — `|H| = 1/√(1 + (1000/10,6)²) ≈ 1/94`, yani ≈ %1,06 geçer. Kısayol: f ≫ f_c için zayıflatma ≈ `f / f_c = 1000 / 10,6 ≈ 94`. (47 kat, 500 Hz'deki değerdir.)

9. **B** — 10 Hz, 1 Hz'lik gaz sinyalini %99,5 geçirir ve 1 kHz civarını ≈ 94 kat zayıflatır. 0,5 Hz gaz sinyalinin kendisini %45'e indirir. 500 Hz seçersen filtre f_s/2'de %70,7, 1 kHz'de %45 geçirir; neredeyse işe yaramaz. 5 kHz ise hiç filtre yokmuş gibidir.

10. **A** — 1 kHz'de 20 örnek = 20 ms = 50 Hz'in tam bir periyodu; sinüsün pozitif ve negatif yarıları birbirini götürür. Aynı ortalama 100, 150 … Hz'i de sıfırlar. B yanlıştır: ortalama, f_s'nin katlarından DC'ye düşen bozucuları hiç etkilemez (bkz. soru 12).

11. **C** — Gerçek bir sinyalin frekansı f_s'den bağımsızdır, yerinde kalır. Alias ise f_s'ye bağlıdır: 950 Hz'den gelen bir alias, f_s 1010 Hz olunca 60 Hz'e kayar. Ayrıntı: [bölüm 13.1](ozet.md#131-bir-tepe-alias-mı-örnekleme-hızını-biraz-değiştir).

12. **D** — `1000 / 1000 = 1,0` tur → r = 0 → DC. 20 örneklik ortalama 50 Hz'in katlarını sıfırlar ama DC'yi aynen geçirir; DC zaten korumak istediğin gaz sinyalidir. Ayrıntı: [bölüm 8](ozet.md#8-tasarım-örneği-lel-dedektörü-girişi) ve [bölüm 12](ozet.md#12-emc-açısından).

13. **A** — 1,2 kHz'de 1 kHz, `|1000 − 1200| = 200 Hz`'e düşer. 24 örnek = 20 ms olduğu için ortalama, 50 Hz'in katı olan 200 Hz'i ve şebekenin tüm harmoniklerini sıfırlar. B ve D'de 1 kHz yine f_s'nin tam katıdır (DC'ye düşer); C'de ortalamayı uzatmak DC'yi değiştirmez.

</details>
