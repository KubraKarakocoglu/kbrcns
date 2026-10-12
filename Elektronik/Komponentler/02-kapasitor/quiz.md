# Quiz · Kapasitör

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 12 soru, 5'i hesap.

## Sorular

1. **(Hesap)** 1 kΩ ve 100 nF'lık bir RC alçak geçiren filtrenin kesim frekansı yaklaşık kaçtır?
   - A) 159 Hz
   - B) 1,59 kHz
   - C) 15,9 kHz
   - D) 159 kHz

2. **(Hesap)** 105 °C'de 2000 saat ömürlü bir elektrolitik kapasitör 65 °C'de çalışıyor. Beklenen ömür yaklaşık ne kadardır?
   - A) 4 000 saat
   - B) 8 000 saat
   - C) 128 000 saat
   - D) 32 000 saat

3. **(Hesap)** 100 µF'lık bir kapasitör 12 V'tan 9 V'a düşene kadar 1 W'lık bir yükü besliyor. Tutma süresi yaklaşık kaçtır?
   - A) 0,3 ms
   - B) 31,5 ms
   - C) 3,15 ms
   - D) 315 ms

4. **(Hesap)** 1000 µF'lık bir kapasitör 100 µs içinde 0'dan 12 V'a şarj oluyor. Ortalama şarj akımı kaçtır?
   - A) 120 A
   - B) 1,2 A
   - C) 12 A
   - D) 1200 A

5. **(Hesap)** 230 V, 50 Hz şebekede hat ile koruma toprağı arasına bağlı 4,7 nF'lık Y kapasitörden geçen kaçak akım yaklaşık kaçtır?
   - A) 3,4 µA
   - B) 34 µA
   - C) 0,34 mA
   - D) 3,4 mA

6. Sıcaklık değişse de 10 ms'lik bir gecikmenin hassas kalması gerekiyor. Hangi kapasitör türü uygundur?
   - A) C0G MLCC veya film
   - B) Y5V MLCC
   - C) X5R MLCC
   - D) Alüminyum elektrolitik

7. Class 2 MLCC'nin (X7R/X5R) efektif kapasitesini aşağıdakilerden hangisi düşürür?
   - A) Sıcaklık, DC bias ve yaşlanma
   - B) Yalnızca sıcaklık
   - C) Yalnızca DC bias
   - D) Hiçbiri; kapasite sabittir

8. Yaşlanan bir alüminyum elektrolitik kapasitörde en tipik belirti hangisidir?
   - A) ESR'nin düşmesi
   - B) Kapasitenin artması
   - C) Polaritesinin tersine dönmesi
   - D) ESR'nin artması ve kapasitenin düşmesi

9. MnO₂ tantal kapasitör için hangisi doğrudur?
   - A) Arıza modu her zaman açık devredir
   - B) Arızada kısa devre olup yanabilir; çalışma gerilimi anma değerinin yaklaşık yarısında tutulur
   - C) Inrush akımından etkilenmez
   - D) Ters gerilime dayanıklıdır

10. Şebekede hat ile nötr arasına hangi kapasitör bağlanır?
    - A) Herhangi bir 400 V'luk MLCC
    - B) Sertifikalı X sınıfı (ör. X2)
    - C) Sertifikalı Y sınıfı
    - D) Elektrolitik

11. Dielektrik soğurma en çok hangi devrede sorun yaratır?
    - A) Decoupling
    - B) Röle snubber'ı
    - C) Bulk filtre
    - D) Örnekle-tut (sample & hold) ve hassas integratör

12. Titreşimli bir ortamdaki hassas analog sinyal yolunda neden Class 2 MLCC'den kaçınılır?
    - A) Çok pahalı olduğu için
    - B) Kapasitesi çok düşük olduğu için
    - C) Piezoelektrik etki ile titreşimi gürültüye çevirdiği için (mikrofonik etki)
    - D) Polarize olduğu için

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **B** — `f_c = 1 / (2π × 1000 × 100×10⁻⁹) ≈ 1,59 kHz`.

2. **D** — 105 − 65 = 40 °C → 4 adet 10 °C → `2⁴ = 16` kat → `2000 × 16 = 32 000 saat` (~3,7 yıl). Ripple akımının iç ısınması bu süreyi kısaltır.

3. **C** — `t = C·(V1² − V2²) / (2P) = 100×10⁻⁶ × (144 − 81) / 2 = 3,15 ms`.

4. **A** — `I = C · dV/dt = 1000×10⁻⁶ × 12 / 100×10⁻⁶ = 120 A`. Inrush sınırlaması bu yüzden gereklidir.

5. **C** — `I = 2π·f·C·V = 2π × 50 × 4,7×10⁻⁹ × 230 ≈ 0,34 mA`. Ürün standardının dokunma akımı sınırıyla karşılaştırılmalıdır.

6. **A** — C0G ve film kapasitörler sıcaklık ve gerilimle neredeyse hiç değişmez. Class 2 MLCC'ler ve elektrolitikler değişir.

7. **A** — Üç etki de vardır ve birbirine eklenir. X7R kodundaki ±%15 yalnızca sıcaklık etkisini tanımlar.

8. **D** — Elektrolit kurudukça ESR artar ve kapasite düşer. Regülatör çıkışında bu, ripple artışı ve kararsızlık olarak görülür.

9. **B** — MnO₂ tantal kısa devre olup yanabilir. Yaygın öneri çalışma gerilimini anma değerinin ~%50'sinde tutmak ve inrush akımını sınırlamaktır. Polimer tantal daha güvenlidir.

10. **B** — Hat-nötr arasına sertifikalı X kapasitör bağlanır. Y kapasitörler hat/nötr ile toprak arasına bağlanır ve arızada açık devre olmalıdır.

11. **D** — Boşaltılan kapasitörde gerilim kısmen geri gelir; örnekle-tut devresinde önceki örneğin izi kalır. C0G ve polipropilen film bu açıdan en iyisidir.

12. **C** — Class 2 seramikler piezoelektriktir: mekanik titreşimi gerilime çevirir. Hassas analog yolda C0G veya film tercih edilir.

</details>
