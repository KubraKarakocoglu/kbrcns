# Quiz · Güç ve decoupling

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 13 soru, 4'ü hesap.

## Sorular

1. Decoupling kapasitörünün temel görevi nedir?
   - A) Besleme gerilimini yükseltmek
   - B) IC'nin ani akım ihtiyacını yerelden karşılamak ve gürültünün besleme hattına yayılmasını azaltmak
   - C) Ters polariteye karşı koruma sağlamak
   - D) Regülatörün verimini artırmak

2. **(Hesap)** Regülatör ile IC arasındaki bağlantının endüktansı 10 nH. IC'nin çektiği akım 5 ns içinde 100 mA artıyor. Bu endüktans üzerinde oluşan anlık gerilim düşümü yaklaşık kaçtır?
   - A) 2 mV
   - B) 20 mV
   - C) 0,2 V
   - D) 2 V

3. **(Hesap)** Bir MCU 10 ns boyunca 200 mA ek akım çekiyor. Beslemede izin verilen düşüm (droop) 50 mV. Bu darbeyi yalnızca yerel kapasitörle karşılamak için gereken **minimum efektif** kapasite nedir?
   - A) 4 nF
   - B) 40 nF
   - C) 400 nF
   - D) 4 µF

4. **(Hesap)** 100 nF bir kapasitörün montaj dahil toplam ESL'i 1 nH. Self-rezonans frekansı (SRF) yaklaşık kaçtır?
   - A) 1,6 MHz
   - B) 16 MHz
   - C) 160 MHz
   - D) 1,6 GHz

5. SRF'nin üstündeki frekanslarda bir kapasitör nasıl davranır?
   - A) Kapasitansı artar, daha iyi decoupling yapar
   - B) Endüktör gibi davranır; empedansı frekansla artar
   - C) Açık devre gibi davranır
   - D) Frekanstan bağımsız, sabit bir direnç gibi davranır

6. 5 V'luk bir rayda 10 µF, 6,3 V, 0603 paket X5R kapasitör kullanıyorsun. Hangisi doğrudur?
   - A) Efektif kapasite 10 µF'ye çok yakındır
   - B) Efektif kapasite ciddi ölçüde düşebilir; üreticinin DC bias eğrisinden kontrol edilmelidir
   - C) X5R dielektrikte DC bias etkisi yoktur
   - D) DC gerilim uygulandıkça kapasite artar

7. Aşağıdakilerden hangisi decoupling etkinliğini **en çok** bozar?
   - A) 0402 yerine 0603 paket kullanmak
   - B) Kapasitörü IC'den 3 cm uzağa, ince bir izle bağlamak
   - C) X7R dielektrik kullanmak
   - D) GND via'sını kapasitör pad'inin hemen yanına koymak

8. Kristal osilatörün 12 pF'lık yük kapasitörleri için en uygun dielektrik hangisidir?
   - A) Y5V
   - B) X5R
   - C) C0G / NP0
   - D) Tantal

9. **(Hesap)** 8 çıkış pini aynı anda 0 V'tan 3,3 V'a anahtarlanıyor. Her pinin yükü 20 pF, kenar süresi 2 ns. Toplam tepe akım yaklaşık kaçtır?
   - A) 33 mA
   - B) 132 mA
   - C) 264 mA
   - D) 2,6 A

10. Yaklaşık 100 MHz'in üstündeki besleme gürültüsünü esas olarak ne karşılar?
    - A) Bulk elektrolitik kapasitör
    - B) Regülatörün kontrol döngüsü
    - C) IC paketinin içindeki kapasitans ve kartın güç/toprak düzlemleri
    - D) 10 µF seramik kapasitör

11. Bir kapasitörün üzerindeki "X7R" kodu neyi garanti eder?
    - A) Uygulanan DC gerilimden bağımsız olarak kapasitenin %15 içinde kalmasını
    - B) −55…+125 °C aralığında, sıcaklıkla kapasite değişiminin ±%15 içinde kalmasını
    - C) Kapasitörün 7 V'a kadar dayanmasını
    - D) ESR'nin 7 mΩ'un altında olmasını

12. Osiloskopla besleme gürültüsünü ölçerken probun 15 cm'lik timsah GND kablosunu kullanmak neden yanıltıcıdır?
    - A) Kablo direnci gerilimi düşürür
    - B) Kablonun oluşturduğu döngü manyetik alan toplar ve prob kapasitansıyla rezonansa girerek sahte çınlama gösterir
    - C) Timsah kablo DC kuplajı engeller
    - D) Osiloskobun bant genişliğini artırır

13. Büyük bir MLCC'yi kartın vida deliğinin hemen yanına yerleştirmenin en ciddi riski nedir?
    - A) Kapasitansın sıcaklıkla artması
    - B) Kart eğildiğinde kapasitörün çatlayıp kısa devreye dönüşmesi
    - C) ESL'in düşmesi
    - D) Lehimlemenin kolaylaşması

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **B** — Decoupling kapasitörü IC'nin yanındaki yerel enerji deposudur. Regülatörün ve bağlantı endüktansının yetişemediği hızlı akım değişimlerini karşılar, IC'nin gürültüsünü de besleme ağından ayırır.

2. **C** — `V = L · di/dt = 10 nH × (0,1 A / 5 ns) = 10×10⁻⁹ × 2×10⁷ = 0,2 V`. 3,3 V'luk bir rayda bu %6'lık bir çöküş demek. Kapasitörü pine yakın koymanın nedeni bu endüktansı devreden çıkarmaktır.

3. **B** — `C = I · Δt / ΔV = 0,2 A × 10 ns / 0,05 V = 40 nF`. Pratikte 100 nF seçilir, çünkü DC bias, tolerans ve sıcaklık efektif değeri düşürür ve marj gerekir.

4. **B** — `f = 1 / (2π √(1×10⁻⁹ × 100×10⁻⁹)) = 1 / (2π × 10⁻⁸) ≈ 15,9 MHz`. Montaj endüktansı 2 nH'ye çıkarsa SRF yaklaşık 11 MHz'e düşer; yerleşimin önemi buradan gelir.

5. **B** — SRF üstünde ESL baskın hale gelir ve empedans `2πf·L` ile artar. Kapasitör artık kapasitör gibi değil, endüktör gibi davranır.

6. **B** — X5R/X7R (yüksek dielektrik sabitli) seramiklerde DC gerilim kapasiteyi düşürür. Küçük paket ve çalışma gerilimi nominal gerilime yakın olduğunda kayıp büyüktür. Daha yüksek gerilim dereceli veya daha büyük paketli parça seç; değeri üretici eğrisinden doğrula.

7. **B** — Uzun ve ince iz, kapasitörün ESL'inden çok daha büyük bir endüktans ekler. Kapasitör yüksek frekansta etkisiz kalır. A ve C'nin etkisi küçüktür, D ise doğru uygulamadır.

8. **C** — C0G/NP0 sıcaklık ve gerilimle neredeyse hiç değişmez ve DC bias etkisi yoktur. Osilatör frekansı yük kapasitesine bağlı olduğu için kararlılık şarttır.

9. **C** — Tek pin: `I = C · dV/dt = 20 pF × 3,3 V / 2 ns = 33 mA`. Sekiz pin aynı anda: `8 × 33 mA = 264 mA`. Ortalama akım düşük olsa bile kenar anındaki tepe akım bu kadar yüksek olabilir.

10. **C** — Bu frekanslarda kart üstündeki kapasitörler, montaj endüktansları yüzünden endüktör gibi davranır. Gürültüyü IC paketinin içindeki kapasitans ve güç/toprak düzlemleri arasındaki kapasitans karşılar.

11. **B** — X7R yalnızca sıcaklık davranışını tanımlar: X = −55 °C, 7 = +125 °C, R = ±%15. DC bias kaybı bu koda dahil değildir ve ayrıca kontrol edilmelidir.

12. **B** — Uzun GND kablosu bir döngü anteni gibi davranır ve probun kendi kapasitansıyla rezonansa girer. Ekranda devrede olmayan bir çınlama görürsün. Bunun yerine probun GND yayını kullanılmalı ve ölçüm doğrudan kapasitör pad'lerinden alınmalıdır.

13. **B** — Seramik kapasitör kırılgandır. Vida sıkılırken veya kart panelden ayrılırken oluşan eğilme kapasitörü çatlatabilir. Çatlak, zamanla kısa devreye dönüşebilen gizli bir arızadır.

</details>
