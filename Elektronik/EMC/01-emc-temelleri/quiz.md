# Quiz · EMC temelleri

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 12 soru, 5'i hesap.

## Sorular

1. **(Hesap)** Yükselme süresi 1 ns olan bir dijital sinyalin spektrumunun önemli kısmı yaklaşık hangi frekansa kadar uzanır?
   - A) 32 MHz
   - B) 100 MHz
   - C) 318 MHz
   - D) 1 GHz

2. **(Hesap)** 100 MHz'de çeyrek dalga boyu kaçtır?
   - A) 75 cm
   - B) 7,5 cm
   - C) 25 cm
   - D) 3 m

3. **(Hesap)** İki iz arasında 1 pF parazitik kapasitans var. Kaynak izindeki gerilim 1 ns'de 3,3 V değişiyor. Kurban ize akan kuplaj akımı yaklaşık kaçtır?
   - A) 3,3 µA
   - B) 33 µA
   - C) 33 mA
   - D) 3,3 mA

4. **(Hesap)** Bir emisyon tepesi bir iyileştirmeden sonra 20 dB düştü. Alan şiddeti kaç kat azalmıştır?
   - A) 2 kat
   - B) 4 kat
   - C) 20 kat
   - D) 10 kat

5. **(Hesap)** 30 MHz'de yakın alan / uzak alan sınırı yaklaşık kaç metredir?
   - A) 0,16 m
   - B) 1,6 m
   - C) 10 m
   - D) 16 m

6. Kaynak – kuplaj yolu – kurban modelinde genellikle en ucuz ve en etkili müdahale nerede yapılır?
   - A) Kaynakta
   - B) Kurbanda
   - C) Her zaman ekranlamada
   - D) Test laboratuvarında

7. Aynı akım genliğinde, hangisi tipik olarak çok daha verimli ışır?
   - A) Kartın içindeki küçük diferansiyel mod döngüsü
   - B) DC besleme akımı
   - C) Bir kablodaki ortak mod akımı
   - D) İkisi aynı verimde ışır

8. Yüksek frekansta bir sinyalin dönüş akımı GND düzleminde nereden akar?
   - A) Sinyal izinin hemen altından (en düşük endüktanslı yol)
   - B) En kısa düz çizgiden, kaynağa doğru
   - C) Düzlemin tamamına eşit dağılarak
   - D) Kartın kenarından

9. 1 kHz'lik bir kontrol sinyali 1 ns'lik kenarlarla sürülüyor. Emisyon açısından hangisi doğrudur?
   - A) Frekansı düşük olduğu için sorun çıkarmaz
   - B) Yalnızca 1 kHz'de emisyon yapar
   - C) Yalnızca DC bileşeni vardır
   - D) Keskin kenarları yüzünden yüzlerce MHz'e kadar enerji taşır

10. Endüktif kuplajı azaltmanın en etkili yolu hangisidir?
    - A) Kenarları hızlandırmak
    - B) Kurbanın empedansını artırmak
    - C) Akım döngülerinin alanını küçültmek, mesafeyi artırmak, bükümlü kablo kullanmak
    - D) Daha ince iz kullanmak

11. Bir emisyon ölçümünde tepe (peak), quasi-peak (QP) ve ortalama (AV) dedektör değerleri arasındaki ilişki nedir?
    - A) AV ≥ QP ≥ tepe
    - B) Tepe ≥ QP ≥ AV
    - C) Hepsi her zaman eşittir
    - D) QP her zaman en büyüktür

12. EMC önlem hiyerarşisinde ekranlama neden son çare olarak görülür?
    - A) Ekranlama hiç işe yaramaz
    - B) Pahalıdır, mekanik tasarımı zorlaştırır ve yarıklar ile kablolar ekranın etkisini azaltır; kaynakta ve yerleşimde çözmek daha ucuzdur
    - C) Ekranlama yasaktır
    - D) Ekranlama yalnızca bağışıklığı etkiler

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **C** — `f ≈ 1 / (π × 1 ns) ≈ 318 MHz`. 10 ns'lik kenarlarla bu sınır ~32 MHz'e iner.

2. **A** — `λ = 3×10⁸ / 100×10⁶ = 3 m`; `λ/4 = 75 cm`. Tipik bir cihaz kablosu bu boydadır.

3. **D** — `i = C · dV/dt = 1×10⁻¹² × 3,3 / 1×10⁻⁹ = 3,3 mA`. Yüksek empedanslı bir girişte bu akım büyük bir gerilim yaratır.

4. **D** — Alan şiddeti (gerilim benzeri büyüklük) için `20 dB = 10 kat`.

5. **B** — `λ = 10 m`; `λ/(2π) ≈ 1,6 m`.

6. **A** — Kaynakta yapılan bir iyileştirme (kenar hızı, döngü alanı) tüm kuplaj yollarını ve tüm kurbanları aynı anda etkiler; çoğu zaman bir direnç veya yazılım ayarı kadar ucuzdur.

7. **C** — Ortak mod akımı dönüş yolunu çevre üzerinden büyük bir döngüyle tamamlar ve kablo anten olur. Diferansiyel moddaki alanlar ise büyük ölçüde birbirini götürür.

8. **A** — Yüksek frekansta endüktans baskındır. En düşük endüktans, döngü alanını en küçük yapan yoldur: izin hemen altı.

9. **D** — Spektrumun üst sınırını kenar süresi belirler. Sinyalin tekrar frekansı düşük olsa da her kenar yüzlerce MHz'e uzanan enerji içerir.

10. **C** — Endüktif kuplaj `v = M · di/dt` ile oluşur; M döngü alanları ve aradaki mesafe ile belirlenir. Bükümlü kablo, komşu döngülerin indüklenen gerilimlerini birbirini götürecek şekilde ters çevirir.

11. **B** — QP dedektörü sinyalin tekrar sıklığına göre ağırlıklandırır; tepe değerden büyük olamaz. Ortalama değer de QP'den büyük olamaz.

12. **B** — Ekran ancak bütünlüğü korunursa işe yarar; yarıklar, kapaklar ve kablo girişleri onu deler. Kaynakta ve kart yerleşiminde alınan önlemler çok daha ucuzdur.

</details>
