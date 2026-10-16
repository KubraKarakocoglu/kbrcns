# Quiz · PCB yerleşim ve iz çizimi

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 10 soru, 4'ü hesap.

## Sorular

1. **(Hesap)** 1 oz bakırda 0,5 mm genişliğinde ve 100 mm uzunluğunda bir iz var (kare direnci 0,49 mΩ). İzden 1 A geçerse gerilim düşümü yaklaşık kaçtır?
   - A) 9,8 mV
   - B) 0,98 V
   - C) 98 mV
   - D) 49 mV

2. **(Hesap)** IPC-2221 tablosuna göre 1 oz dış katmanda 2 A'i 10 °C sıcaklık artışıyla taşıyacak iz yaklaşık ne genişlikte olmalıdır?
   - A) 0,2 mm
   - B) 0,78 mm
   - C) 2,77 mm
   - D) 0,08 mm

3. **(Hesap)** Isıtıcının 300 mA'lik dönüş akımı, sensör ölçümünün referans aldığı GND yolunun 20 mΩ'luk bir kısmından geçiyor. Ölçüme eklenen hata gerilimi kaçtır?
   - A) 0,6 mV
   - B) 60 mV
   - C) 15 mV
   - D) 6 mV

4. **(Hesap)** 25 °C'de 82 mΩ olan bir bakır iz 75 °C'ye ısınıyor (bakırın sıcaklık katsayısı ≈ %0,39/°C). Direnci yaklaşık kaç olur?
   - A) 98 mΩ
   - B) 82 mΩ
   - C) 164 mΩ
   - D) 66 mΩ

5. Clearance ile creepage arasındaki fark nedir?
   - A) İkisi aynı şeydir
   - B) Clearance iki iletken arasındaki havadan en kısa mesafe, creepage ise kartın yüzeyi boyunca en kısa mesafedir
   - C) Clearance yalnızca iç katmanlarda, creepage yalnızca dış katmanlarda geçerlidir
   - D) Creepage via'lar arasındaki mesafedir

6. Analog ve dijital devrenin olduğu bir kartta toprak için genelde en iyi yaklaşım hangisidir?
   - A) GND düzlemini ortadan bir yarıkla AGND ve DGND diye ikiye bölmek
   - B) Her IC'ye ayrı bir toprak izi çekmek
   - C) Tek ve kesintisiz bir GND düzlemi kullanıp analog ve dijital parçaları yerleşimle ayrı bölgelere koymak; dönüş akımlarının kendi bölgelerinde kalmasını sağlamak
   - D) Toprak düzlemi hiç kullanmamak

7. Hiçbir nete bağlı olmayan bir bakır ada kartta neden sorun olur?
   - A) Anten gibi davranarak gürültü toplar ve yayar; ya GND'ye bağlanmalı ya da silinmelidir
   - B) Kartı ağırlaştırır
   - C) DRC'yi yavaşlatır
   - D) Hiçbir sorun yoktur

8. Pad'lerin bakır döküme termal rölyef ile bağlanmasının amacı nedir?
   - A) Akım taşıma kapasitesini artırmak
   - B) EMI'yi azaltmak
   - C) Parçayı daha iyi soğutmak
   - D) Lehimleme sırasında ısının bakıra hızla kaçmasını önleyerek lehimlemeyi kolaylaştırmak

9. 0402 bir kapasitörün pedinin içine dolgusuz bir via konmuş. Olası sorun nedir?
   - A) Kapasitörün değeri değişir
   - B) Via'nın endüktansı sıfıra iner
   - C) Lehim via'dan aşağı kaçar; parçanın bir ucu kalkıp dikilebilir (tombstoning) veya lehim zayıf kalır
   - D) Hiçbir sorun olmaz

10. Kartı üreticiye göndermeden önceki son kontrollerden biri neden Gerber dosyalarını ayrı bir görüntüleyicide açmaktır?
    - A) Gerber dosyaları EDA aracında açılamadığı için
    - B) Üretici EDA ekranını değil, bu dosyaları görür; dışa aktarımda kaybolan katman, yanlış ofset veya eksik delik ancak böyle fark edilir
    - C) Dosya boyutunu küçültmek için
    - D) Renkleri kontrol etmek için

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **C** — Kare sayısı `100 / 0,5 = 200`; direnç `200 × 0,49 mΩ ≈ 98 mΩ`; düşüm `1 A × 98 mΩ ≈ 98 mV`. 3,3 V'luk bir rayda bu %3'tür.

2. **B** — Tablodaki değer ≈ 0,78 mm. 0,2 mm 1 A'in de altında kalır; 2,77 mm ise 5 A içindir.

3. **D** — `V = 0,3 A × 0,02 Ω = 6 mV`. 12 bitlik, 3,3 V referanslı bir ADC'de bu yaklaşık 7 LSB demektir. Isıtıcı dönüşü, ölçümün referans aldığı topraktan ayrı ve kısa bir yoldan güç girişine dönmelidir.

4. **A** — `82 × (1 + 0,0039 × 50) ≈ 82 × 1,195 ≈ 98 mΩ`. Isınan iz daha çok gerilim kaybettirir ve daha da ısınır.

5. **B** — Clearance, ark atlamasına karşı havadan mesafedir. Creepage, yüzeydeki kir ve nem nedeniyle oluşan kaçak akım yoluna karşı yüzey mesafesidir. Yüzeye yarık açmak creepage'i artırır, clearance'ı değiştirmeyebilir.

6. **C** — Bölünmüş düzlemlerin arasından geçen her iz, dönüş akımını uzun bir yoldan dolaşmaya zorlar ve büyük bir döngü (anten) oluşturur. Tek düzlemde dönüş akımı izin hemen altından döner; ayırmayı yerleşim yapar.

7. **A** — Bağlı olmayan bakır, alanlardan gerilim toplayan ve yeniden yayan bir yapıdır. Dökümden sonra kalan adalar via ile GND'ye bağlanır veya silinir.

8. **D** — Geniş bakır alan, havyanın veya fırının ısısını hızla çeker; pad yeterince ısınmaz ve soğuk lehim oluşur. Termal rölyef, pad ile bakır arasındaki ısı yolunu daraltır. Yüksek akım veya ısı aktarımı gereken pad'lerde doğrudan bağlantı tercih edilebilir.

9. **C** — Erimiş lehim kılcal etkiyle via'dan aşağı akar. Bir pad'de daha az lehim kalınca yüzey gerilimleri dengesizleşir ve parça dikilebilir. Via pedin dışına alınır ya da dolgulu ve kapatılmış (filled & capped) via kullanılır.

10. **B** — EDA'dan dışa aktarım sırasında bir katmanın unutulması, delik dosyasının farklı ofsetle çıkması veya maske açıklıklarının hatalı olması olur. Üretici yalnızca bu dosyaları üretir; son kontrol de bu dosyalar üzerinde yapılmalıdır.

</details>
