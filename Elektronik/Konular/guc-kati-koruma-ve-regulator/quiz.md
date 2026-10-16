# Quiz · Güç katı: koruma ve regülatör seçimi

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 10 soru, 5'i hesap.

## Sorular

1. **(Hesap)** Bir LDO 12 V'u 3,3 V'a düşürüyor ve 100 mA veriyor. Isıya çevirdiği güç yaklaşık kaçtır?
   - A) 0,33 W
   - B) 1,2 W
   - C) 0,87 W
   - D) 0,087 W

2. **(Hesap)** Bir parça 0,5 W harcıyor; θJA = 80 °C/W, ortam sıcaklığı 60 °C. Junction sıcaklığı yaklaşık kaçtır?
   - A) 40 °C
   - B) 100 °C
   - C) 140 °C
   - D) 80 °C

3. **(Hesap)** Bir buck regülatör 5 V'ta 300 mA veriyor; verimi %85, girişi 24 V. Girişten çektiği akım yaklaşık kaçtır?
   - A) 300 mA
   - B) 62,5 mA
   - C) 18,4 mA
   - D) 73,5 mA

4. **(Hesap)** Regülatörün FB gerilimi 0,8 V, alt direnç 10 kΩ. Çıkışın 3,3 V olması için üst direnç teorik olarak kaç olmalıdır?
   - A) 31,25 kΩ
   - B) 41,25 kΩ
   - C) 3,125 kΩ
   - D) 26,4 kΩ

5. **(Hesap)** 2 A'lik bir girişte ters polarite koruması için iki seçenek var: 0,45 V düşümlü Schottky diyot ve R_DS(on) = 30 mΩ olan P-MOSFET. Kayıpları sırasıyla yaklaşık kaçtır?
   - A) 0,45 W / 0,06 W
   - B) 0,9 W / 0,12 W
   - C) 0,9 W / 0,06 W
   - D) 1,8 W / 0,12 W

6. 24 V girişli bir kartta TVS diyotun darbe sırasındaki kenetleme gerilimi (VC) 53 V. Arkadaki buck regülatörün giriş gerilimi dayanımı en az ne olmalıdır?
   - A) 28 V
   - B) 36 V
   - C) 60 V
   - D) 40 V

7. Giriş sigortası neden genelde gecikmeli (T) tip seçilir?
   - A) Daha ucuz olduğu için
   - B) Kısa devrede daha hızlı açtığı için
   - C) Gerilim düşümü olmadığı için
   - D) Açılışta bulk kapasitörün çektiği kısa ama büyük inrush akımında gereksiz yere atmaması için

8. P-MOSFET'li ters polarite devresinde gate ile source arasına neden Zener diyot konur?
   - A) Giriş gerilimi MOSFET'in Vgs dayanımını (tipik ±20 V) aşabileceği için gate'i korumak
   - B) MOSFET'i daha hızlı açmak için
   - C) Ters bağlantıda akımı artırmak için
   - D) Gerilim düşümünü artırmak için

9. Bir LDO'nun PSRR'si için hangisi doğrudur?
   - A) Frekansla artar; MHz'lerde en iyi bastırmayı yapar
   - B) Sadece DC'de anlamlıdır
   - C) Düşük frekansta iyidir ama MHz'lerde zayıflar; buck'ın yüksek frekans gürültüsü için ferrit veya LC filtre eklenir
   - D) Çıkış kapasitörüne bağlı değildir

10. Hassas bir ADC ölçümü yapan kartta buck regülatör az yükte "PFM / skip" moduna geçiyor. Olası sorun nedir?
    - A) Verim düşer
    - B) Anahtarlama frekansı kHz'lere, hatta duyulabilir bölgeye iner; ripple ölçüm bandına karışabilir
    - C) Çıkış gerilimi iki katına çıkar
    - D) Bobin doyar

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **C** — `P = (12 − 3,3) × 0,1 = 0,87 W`. SOT-23 pakette (θJA ≈ 200 °C/W) bu, ortamın 174 °C üstü demektir; LDO yerine buck tercih edilir.

2. **B** — `Tj = 60 + 0,5 × 80 = 100 °C`. Çoğu parçanın sınırı 125–150 °C'dir; marj var ama bakır alanı küçükse θJA büyür.

3. **D** — `I_in = (5 × 0,3) / (0,85 × 24) = 1,5 / 20,4 ≈ 73,5 mA`. Buck, gücü aktarır: çıkış akımı 300 mA iken giriş akımı çok daha küçüktür. LDO olsaydı giriş akımı 300 mA olurdu.

4. **A** — `R_üst = R_alt × (Vout/V_FB − 1) = 10k × (3,3/0,8 − 1) = 10k × 3,125 = 31,25 kΩ`. Standart değer olarak 31,6 kΩ (%1) seçilir → Vout ≈ 3,33 V.

5. **B** — Schottky: `0,45 V × 2 A = 0,9 W`, küçük bir pakette ciddi ısınma. P-MOSFET: `2² × 0,03 = 0,12 W`. Akım büyüdükçe MOSFET'in avantajı karesel olarak artar.

6. **C** — TVS gerilimi sıfıra indirmez, VC'ye kenetler. Darbe sırasında regülatörün girişi 53 V görür. 40 V'luk bir regülatör hasar görür; 60 V'luk seçilir.

7. **D** — Bulk kapasitör ilk anda çok büyük akım çeker (`I = C·dV/dt`). Hızlı sigorta bu kısa darbede atabilir. Gecikmeli sigorta kısa darbelere dayanır, sürekli aşırı akımda açar. Seçim sigortanın I²t değeriyle doğrulanır.

8. **A** — Doğru bağlantıda gate toprakta, source yaklaşık Vin'dedir; yani |Vgs| ≈ Vin. 24 V'luk (ve darbede daha yüksek) bir girişte ±20 V'luk Vgs dayanımı aşılır. Zener, |Vgs|'yi güvenli bir değerde (ör. 12 V) tutar.

9. **C** — LDO'nun iç kontrol döngüsünün bant genişliği sınırlıdır. PSRR düşük frekansta yüksektir (tipik 60–70 dB), MHz'lerde ciddi düşer. Buck'ın anahtarlama gürültüsünü LDO tek başına temizleyemez.

10. **B** — PFM modunda frekans yüke göre değişir ve kHz'lere inebilir. Bu ripple ölçüm bandına, hatta aliasing ile başka frekanslara karışabilir; bobin ve seramik kapasitörler de ses çıkarabilir. Hassas ölçümde zorlanmış PWM (FPWM) seçeneği tercih edilir.

</details>
