# Quiz · Şebeke güvenliği ve yalıtım

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 12 soru, 5'i hesap.

## Sorular

1. **(Hesap)** Şebeke 230 V, toleransı ±%10. En yüksek hat geriliminde (253 V rms) tepe değer yaklaşık kaçtır?
   - A) 253 V
   - B) 358 V
   - C) 325 V
   - D) 179 V

2. Clearance ve creepage hangi büyüklüklere bağlıdır?
   - A) Clearance anma darbe gerilimine; creepage çalışma gerilimine, kirlilik derecesine ve malzeme grubuna
   - B) İkisi de yalnızca çalışma gerilimine
   - C) Clearance malzeme grubuna, creepage darbe gerilimine
   - D) İkisi aynı büyüklüktür; yalnızca adları farklıdır

3. **(Hesap)** FR-4 kart (malzeme grubu IIIb varsayımı), PD2, 250 V rms çalışma gerilimi. Temel ve güçlendirilmiş yalıtım için en küçük creepage kaç mm'dir?
   - A) 1,25 / 2,5 mm
   - B) 1,0 / 2,0 mm
   - C) 2,5 / 5,0 mm
   - D) 4,0 / 8,0 mm

4. OVC III bir üründe temel yalıtım için clearance 3,0 mm (4 kV). Güçlendirilmiş yalıtım için IEC 60664-1 clearance'ı kaçtır?
   - A) 3,0 mm; clearance temel ve güçlendirilmişte aynıdır
   - B) 5,5 mm; clearance bir üst darbe basamağından (6 kV) bulunur
   - C) 6,0 mm; temel değer iki katına çıkar
   - D) 8,0 mm; iki basamak yukarı çıkılır

5. **(Hesap)** Class II bir flyback'te primer–sekonder köprüsünde 2,2 nF Y1 kapasitör var. Hat 264 V/60 Hz, kapasitör toleransı +%20. Kaçak akım ve 0,25 mA sınırıyla ilişkisi nedir?
   - A) 0,16 mA; sınırın altında
   - B) 0,22 mA; sınırın altında
   - C) 0,26 mA; sınır aşılıyor
   - D) 2,6 mA; sınır çok aşılıyor

6. **(Hesap)** 220 nF'lık bir X2 kapasitöre paralel, her biri 1 MΩ olan iki seri direnç bleeder olarak konmuş. Deşarj zaman sabiti τ kaçtır?
   - A) 0,22 s
   - B) 4,4 s
   - C) 0,11 s
   - D) 0,44 s

7. Şebeke ile SELV arasındaki **güçlendirilmiş** bariyeri köprüleyen kapasitör hangi sınıf olmalıdır?
   - A) X2
   - B) Tek bir Y2
   - C) Y1 (ürün standardı kabul ediyorsa seri iki Y2)
   - D) Sertifikalı olmasına gerek yoktur, 1 nF'lık seramik yeter

8. Prizden beslenen bir kartın hat girişinde, beklenen kısa devre akımı yüzlerce amper. Hangi sigorta doğrudur?
   - A) Cam tüp, hızlı (F), düşük kırma kapasiteli (L)
   - B) Seramik tüp, gecikmeli (T), yüksek kırma kapasiteli (H, 1500 A)
   - C) PTC; kendini sıfırladığı için şebekede en güvenlisidir
   - D) Ucuz olduğu için 250 V'luk herhangi bir cam tüp sigorta

9. **(Hesap)** Bulk kapasitörlü şebekeli bir kartta soğuk direnci 10 Ω olan bir NTC var. 230 V şebekede ilk anda akımın tepe değeri yaklaşık kaçtır?
   - A) 32,5 A
   - B) 23 A
   - C) 3,25 A
   - D) 65 A

10. Class II bir ürün için hangisi doğrudur?
    - A) Temel yalıtım ve PE'ye bağlı kasayla korunur
    - B) SELV bir besleme ile çalışır
    - C) Kasa PE'ye bağlanmak zorundadır, yoksa sertifika alamaz
    - D) Çift veya güçlendirilmiş yalıtımla korunur; PE gerekmez

11. PD2'de, iki şebeke bakırı arasındaki creepage'i artırmak için 0,5 mm genişliğinde yarık açıyorsun. Ne olur?
    - A) Yarık yolu uzatmış sayılmaz; yarık en az 1 mm olmalı
    - B) Her yarık, genişliğine bakmadan yolu iki katına çıkarır
    - C) Yarık clearance'ı büyütür
    - D) Yarık yalnızca iç katmanlarda işe yarar

12. Şebekeli bir kartın osiloskopla ölçülmesinde en güvenli yöntem hangisidir?
    - A) Prob toprağını primer GND'ye bağlayıp osiloskobun PE ucunu kırarak yüzdürmek
    - B) Variac ile besleyip normal probla ölçmek
    - C) Doğrudan şebekeye bağlayıp prob toprağını kartın GND'sine takmak
    - D) İzolasyon trafosuyla beslemek, diferansiyel prob kullanmak ve ilk açılışta seri ampulle akımı sınırlamak

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **B** — `253 × √2 = 357,8 V ≈ 358 V`. 325 V nominal 230 V'un tepesidir (C), 253 V rms'in kendisi (A), 179 V ise yanlışlıkla `253 / √2` hesabıdır (D). Tablolarda clearance **tepe/darbe**, creepage **rms** ile okunur; bu yüzden ikisini karıştırma.

2. **A** — Clearance **darbe gerilimine** (OVC'den gelir) bağlıdır: 2,5 kV → 1,5 mm, 4 kV → 3,0 mm. Creepage **çalışma gerilimine (rms), kirlilik derecesine ve malzeme grubuna** bağlıdır. Havada ark gerilime bağlıdır; yüzeyde iz ise kir, nem ve malzeme ile ilgilidir. İkisi farklı mekanizmadır (D yanlış).

3. **C** — Tablo: 250 V, PD2, IIIa/IIIb → **2,5 mm** (temel). Güçlendirilmişte creepage **iki katı = 5,0 mm**. 1,25 mm grup I değeridir (A), 1,0 mm baskı devre sütunudur ve FR-4 için güvenli kural değildir (B), 4,0 mm ise PD3 değeridir (D).

4. **B** — Güçlendirilmişte clearance, temel yalıtımın **bir üst darbe basamağından** bulunur: OVC III temel 4 kV → 3,0 mm; güçlendirilmiş **6 kV → 5,5 mm**. "İki katı" kuralı clearance için değil, **creepage** içindir (C: 6,0 mm yanlış). Aynı kalmaz (A), iki basamak da çıkılmaz (D).

5. **C** — `I = 2π × 60 × (2,2 nF × 1,2) × 264 = 0,26 mA` > 0,25 mA. Nominalde 264 V/60 Hz'de 0,22 mA (B) sınırın altındadır ama **tolerans** unutulmuştur; 0,16 mA (A) 230 V/50 Hz'in nominal hesabıdır; 2,6 mA (D) nF/µF karışıklığıdır. Çözüm: 1–1,5 nF'a inmek ve gürültüyü CMC ile çözmek.

6. **D** — Seri dirençler toplanır: `R = 1 + 1 = 2 MΩ`; `τ = R·C = 2 × 10⁶ × 220 × 10⁻⁹ = 0,44 s`. 0,22 s tek direnci almaktır (A); 0,11 s dirençleri paralel sanmaktır (C); 4,4 s ise nF'ı yanlış çevirmektir (B). τ ≈ 0,44 s, 373 V tepeden 1 s'de yaklaşık 38 V'a indirir.

7. **C** — Güçlendirilmiş (veya çift) yalıtımı **Y1** köprüleyebilir (darbe 8 kV). Ürün standardı kabul ederse **seri iki Y2** de kullanılır. Y2 tek başına yalnızca **temel/ek** yalıtımı köprüler (B). X2 hat–nötr içindir ve arızada kısa devre olur (A). Sertifikasız parça şebekeye bağlanmaz (D).

8. **B** — Sigortanın kırma kapasitesi, o noktadaki **beklenen kısa devre akımından büyük** olmalıdır. Düşük kırma kapasiteli cam tüp (L) 250 VAC'ta yalnızca 35 A veya 10·In keser (A, D); kısa devrede ark yapar, patlar. **Gecikmeli (T)** olması bulk kapasitörün inrush'ı içindir. PTC şebekede güvenlik elemanı olarak kullanılmaz (C).

9. **A** — `I_tepe = V_tepe / R = (230 × √2) / 10 = 325 / 10 = 32,5 A`. 23 A rms değerle bölmektir (B), 3,25 A ondalık hatasıdır (C), 65 A 5 Ω'la hesaplamaktır (D). NTC olmasa akım sadece hat ve köprü direncine bağlı kalır ve çok daha büyük olur.

10. **D** — Class II = **çift veya güçlendirilmiş yalıtım**, **PE yok**. Temel yalıtım + PE'ye bağlı kasa Class I'dir (A, C). SELV besleme Class III'tür (B). Class II ürüne ihtiyaten PE bağlamak sınıfı bozar.

11. **A** — IEC 60664-1 mantığında dar yarık (PD2'de 1 mm altı) kirle dolar ve yolu **uzatmış sayılmaz**; yarık **≥ 1 mm** olmalıdır (PD3'te daha geniş alt sınır). Yarık yalnızca **yüzey yolunu** uzatır, hava mesafesini değiştirmez (C yanlış); her iki katmanda da bakır kenarları ve yarığın tüm yüzeyleri değerlendirilir (D yanlış).

12. **D** — İzolasyon trafosu kartı PE'den yüzdürür; diferansiyel prob prob toprağı sorununu ortadan kaldırır; seri ampul ilk açılışta hatayı **ışıkla** gösterir ve akımı sınırlar. A tehlikelidir: PE ucunu kesmek osiloskop kasasını elektriklendirir. B: Variac **yalıtmaz**. C: prob toprağı PE'ye bağlıdır, primer GND'ye takmak şebekeyi toprağa kısa devre eder.

</details>
