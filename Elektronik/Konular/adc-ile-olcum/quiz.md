# Quiz · ADC ile ölçüm: pratik rehber

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 13 soru, 10'u hesap.

## Sorular

1. **(Hesap)** Referansı 2,5 V olan 12 bitlik bir ADC'nin 1 LSB'si yaklaşık kaçtır?
   - A) 2,44 mV
   - B) 0,61 mV
   - C) 0,81 mV
   - D) 6,1 mV

2. **(Hesap)** V_ref = 3,3 V, 12 bit. Girişte 1,20 V varken beklenen kod yaklaşık kaçtır (4095 ölçeği)?
   - A) 1200
   - B) 1365
   - C) 2482
   - D) 1489

3. **(Hesap)** VREFINT_CAL değeri 3,0 V'luk VDDA'da 1650 olarak kaydedilmiş. Kartta VREFINT kanalı şu anda 1500 okunuyor. VDDA kaçtır?
   - A) 3,30 V
   - B) 2,73 V
   - C) 3,00 V
   - D) 3,60 V

4. **(Hesap)** Li-ion pil (4,2 V) 100 kΩ + 220 kΩ'luk bir bölücüyle ölçülüyor. Bölücünün sürekli akımı ve yılda pilden çektiği yük yaklaşık ne kadardır?
   - A) 131 µA; 1150 mAh
   - B) 1,3 µA; 11,5 mAh
   - C) 13 µA; ~115 mAh
   - D) 13 mA; 115 Ah

5. **(Hesap)** 12 bitlik ADC'de örnekleme süresi 1 µs, örnekleme kapasitörü 8 pF, ADC'nin iç direnci 1 kΩ. ½ LSB'ye oturmak için ~9 zaman sabiti gerekiyorsa en büyük kaynak direnci yaklaşık kaçtır?
   - A) 1,3 kΩ
   - B) 12,9 kΩ
   - C) 125 kΩ
   - D) 13,9 MΩ

6. **(Hesap)** 12 bitlik ADC'nin örnekleme kapasitörü 8 pF. Yük paylaşım hatası ½ LSB'nin altında kalsın diye pine konacak dış kapasitör en az ne olmalıdır?
   - A) ≥ 66 nF → pratikte 100 nF
   - B) ≥ 66 pF → pratikte 100 pF
   - C) ≥ 33 nF → pratikte 47 nF
   - D) ≥ 1 µF

7. **(Hesap)** Bir kanalın gürültüsü σ = 2 LSB. 16 örneğin ortalaması alınırsa gürültü yaklaşık kaç LSB olur?
   - A) 0,125 LSB
   - B) 1,0 LSB
   - C) 0,25 LSB
   - D) 0,5 LSB

8. **(Hesap)** 12 bitlik ADC'den aşırı örnekleme ile 14 bit elde edilecek; ADC 8 kHz'de örnekliyor. Kaç örnek toplanmalı ve çıkış hızı ne olur?
   - A) 4 örnek, 2 kHz
   - B) 8 örnek, 1 kHz
   - C) 16 örnek, 500 Hz
   - D) 64 örnek, 125 Hz

9. **(Hesap)** 4–20 mA girişinde 150 Ω şant kullanılıyor. 20 mA'de şant gerilimi ve gücü nedir? Girişe yanlışlıkla doğrudan 24 V gelirse şantta ne kadar güç harcanır?
   - A) 3,0 V ve 60 mW; 24 V'ta 3,84 W
   - B) 3,0 V ve 6 mW; 24 V'ta 0,38 W
   - C) 1,8 V ve 60 mW; 24 V'ta 160 mW
   - D) 3,3 V ve 66 mW; 24 V'ta 24 W

10. **(Hesap)** Bir gaz köprüsünün çıkışı 100 %LEL'de 60 mV. Bu sinyal yükseltmeden 3,3 V referanslı 12 bitlik ADC'ye bağlanırsa tam skala kaç LSB'ye karşılık gelir ve 1 LSB kaç %LEL eder?
    - A) 744 LSB; 0,13 %LEL/LSB
    - B) 7,4 LSB; 13,4 %LEL/LSB
    - C) 74 LSB; 1,34 %LEL/LSB
    - D) 2979 LSB; 0,034 %LEL/LSB

11. 12 bitlik ADC ile sabit bir gerilim ölçülürken okumaların standart sapması σ = 1,5 LSB. Hangisi doğrudur?
    - A) Ölçüm tam 12 bit çözünürlüktedir
    - B) Titremeden duran bit sayısı yaklaşık 8,7'dir; ortalama alınarak etkin çözünürlük artırılabilir
    - C) σ yalnızca ADC'nin bozuk olduğunu gösterir
    - D) Gürültü ortalamayla azaltılamaz

12. NTC'li bir sıcaklık girişinde NTC kopuyor ve ADC kodu ~4095'e çıkıyor. Firmware ne yapmalıdır?
    - A) Hesaplanan değeri, örneğin "−40 °C", göstermeli
    - B) Son geçerli değeri sessizce göstermeye devam etmeli
    - C) Kodu 4095'te sınırlayıp sıcaklığı hesaplamaya devam etmeli
    - D) Makul aralığın dışındaki kodu (ör. > 4000) ölçüm değil arıza saymalı ve arıza olarak raporlamalı

13. ADC birden fazla kanalı sırayla ölçüyor. Yüksek dirençli bir kanala geçince ilk örneğin atılması neden önerilir?
    - A) Örnekleme kapasitörü önceki kanalın gerilimini taşır; yüksek dirençli kanalda ilk örnek bu gerilime doğru çekilir. İlk örnek atılır veya o kanalın örnekleme süresi uzatılır
    - B) ADC ilk örnekte kendini kalibre ettiği için
    - C) İlk örnek her zaman 0 olduğu için
    - D) DMA ilk örneği kaybettiği için

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **B** — `2,5 V / 4096 ≈ 0,61 mV`. Aynı ADC 3,3 V referansla 0,81 mV'luk adım verir; küçük referans daha ince bir cetveldir ama ölçülebilen en büyük gerilim de küçülür.

2. **D** — `1,20 / 3,3 × 4095 ≈ 1489`. Bu hesap, test sırasında "beklenen kod" ile okunan kodu karşılaştırmanın en hızlı yoludur.

3. **A** — `VDDA = 3,0 × 1650 / 1500 = 3,30 V`. VREFINT sabit kaldığı hâlde kod küçüldüyse cetvel (VDDA) büyümüş demektir.

4. **C** — `I = 4,2 V / 320 kΩ ≈ 13 µA`; yılda `13 µA × 8760 h ≈ 115 mAh`. 2 Ah'lik bir pilde bu yılda ~%6'dır. 10k/22k olsaydı 131 µA ve yılda ~1,15 Ah olurdu.

5. **B** — `R_maks = 1 µs / (9 × 8 pF) − 1 kΩ ≈ 13,9 kΩ − 1 kΩ ≈ 12,9 kΩ`. Kaynak daha yüksek dirençliyse örnekleme süresi uzatılır, pine kapasitör konur veya tampon kullanılır.

6. **A** — `C_ext ≥ C_s × (2^13 − 1) = 8 pF × 8191 ≈ 66 nF` → pratik değer 100 nF. Bu durumda kalan hata en kötü durumda ~0,33 LSB'dir.

7. **D** — `σ / √16 = 2 / 4 = 0,5 LSB`. Ortalama yalnızca rastgele gürültüyü azaltır; ofset ve kazanç hatasını azaltmaz.

8. **C** — 2 ek bit için `4² = 16` örnek toplanır ve 2 bit sağa kaydırılır. Çıkış hızı `8 kHz / 16 = 500 Hz`. Girişte ~1 LSB gürültü olmalıdır; yoksa örneklerin hepsi aynı çıkar ve bit kazanılmaz.

9. **A** — `V = 20 mA × 150 Ω = 3,0 V`, `P = (0,02)² × 150 = 60 mW`. 24 V doğrudan gelirse `P = 24² / 150 = 3,84 W`; küçük bir şant yanar. Girişte PTC veya akım sınırlayıcı ve TVS kullanılır.

10. **C** — `60 mV / 0,806 mV ≈ 74 LSB`; `100 / 74 ≈ 1,34 %LEL/LSB`. ±1–2 LSB'lik gürültü ±2 %LEL'e karşılık gelir; ±2,5 %LEL kabul toleransıyla çalışan bir üretim testinde bu kabul edilemez. Kazanç (ör. ×40 → 2979 LSB) veya PGA'lı Σ-Δ ADC gerekir.

11. **B** — Gürültüsüz bit `= 12 − log₂(6,6 × 1,5) ≈ 8,7`. Etkin (rms) çözünürlük `12 − log₂(1,5) ≈ 11,4` bittir. Gürültü rastgele olduğu için ortalama ile azalır.

12. **D** — Kopuk bir NTC "çok soğuk" gibi görünür; bu değer gösterilirse yanlış karar verilir. Her kanalın makul aralığı tanımlanır ve aralık dışı ölçüm arıza olarak raporlanır. Kısa devre için alt sınır da aynı şekilde kontrol edilir.

13. **A** — Örnekleme kapasitörü kanallar arasında boşaltılmaz; önceki kanalın yükünü taşır. Kaynak yüksek dirençliyse kapasitör kısa sürede yeni değere ulaşamaz ve ilk örnek kayar. İlk örneği atmak veya o kanalın örnekleme süresini uzatmak bu hatayı giderir.

</details>
