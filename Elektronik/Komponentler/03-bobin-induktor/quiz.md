# Quiz · Bobin (indüktör)

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 12 soru, 5'i hesap.

## Sorular

1. **(Hesap)** Bir buck regülatör 12 V'u 3,3 V'a düşürüyor; f_sw = 500 kHz, L = 22 µH. Bobin ripple akımı (ΔI) yaklaşık kaçtır?
   - A) 0,22 A
   - B) 0,022 A
   - C) 2,2 A
   - D) 22 A

2. **(Hesap)** Aynı devrede L = 10 µH ve çıkış akımı 1 A olsaydı bobinin tepe akımı yaklaşık kaç olurdu?
   - A) 1,00 A
   - B) 1,05 A
   - C) 1,48 A
   - D) 1,24 A

3. **(Hesap)** Aynı devrede %30 ripple (1 A çıkışta 0,3 A) için gereken endüktans yaklaşık kaçtır?
   - A) 1,6 µH
   - B) 16 µH
   - C) 160 µH
   - D) 1,6 mH

4. **(Hesap)** 10 µH'lik bir bobinin 1 MHz'deki empedansı yaklaşık kaçtır?
   - A) 0,63 Ω
   - B) 6,3 Ω
   - C) 63 Ω
   - D) 630 Ω

5. **(Hesap)** DCR'si 50 mΩ olan bobinden 1 A rms akım geçiyor. Bakır kaybı kaçtır?
   - A) 50 mW
   - B) 5 mW
   - C) 500 mW
   - D) 5 W

6. Bir buck regülatörün bobinini seçerken Isat neden regülatörün akım limitine göre seçilmelidir?
   - A) Akım limiti her zaman yük akımına eşittir
   - B) Kısa devre veya ilk açılış sırasında bobin akımı regülatörün akım limitine kadar çıkabilir; bu sırada bobin doymamalıdır
   - C) Isat'ın akım limitiyle bir ilgisi yoktur
   - D) Isat yalnızca verimi etkiler

7. Ferrit çekirdekli ve toz demir/kompozit çekirdekli bobinlerin doyma davranışı için hangisi doğrudur?
   - A) Ferrit keskin doyar; kompozit endüktansını yavaşça kaybeder
   - B) İkisi de hiç doymaz
   - C) Kompozit keskin doyar; ferrit yavaşça
   - D) İkisi de aynı şekilde doyar

8. Bir röle bobinini MOSFET ile sürüyorsun. Flyback diyotu nasıl bağlanır ve ne işe yarar?
   - A) MOSFET'in gate'ine seri; açma hızını artırır
   - B) Bobine seri; akımı sınırlar
   - C) Röle bobinine paralel, katodu besleme (+) tarafında; kapanışta bobin akımına dolaşım yolu verip gerilim sıçramasını kenetler
   - D) GND'ye seri; kaçak akımı engeller

9. Flyback diyotuna seri bir Zener eklemenin amacı nedir?
   - A) Diyotu korumak
   - B) Röleyi daha hızlı çekmek
   - C) Rölenin daha hızlı bırakması için akımın daha yüksek kenetleme geriliminde daha hızlı sönmesini sağlamak
   - D) Bobin direncini düşürmek

10. Buck regülatör layout'unda alanı en küçük tutulması gereken döngü hangisidir?
    - A) Çıkış kapasitörü ile yük arasındaki döngü
    - B) FB bölücü döngüsü
    - C) Bobin ile çıkış kapasitörü arasındaki döngü
    - D) Giriş kapasitörü, üst anahtar ve alt anahtardan oluşan sıcak döngü

11. SW düğümünün bakır alanı neden mümkün olduğunca küçük tutulur?
    - A) Bakırdan tasarruf etmek için
    - B) Çok yüksek dV/dt taşıdığı için kapasitif kuplajla gürültü yayan bir anten gibi davranır
    - C) Akım taşımadığı için
    - D) Isınmayı artırmak için

12. Ortak mod bobini (CMC) bir USB veri çiftinde nasıl çalışır?
    - A) Hem diferansiyel hem ortak mod akımını eşit bastırır
    - B) Yalnızca DC akımı geçirir
    - C) Sinyali yükseltir
    - D) Diferansiyel sinyal akımının akıları birbirini götürür ve sinyal geçer; ortak mod akımında akılar toplanır ve gürültü bastırılır

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **A** — `D = 3,3/12 = 0,275`. `ΔI = (12 − 3,3) × 0,275 / (22×10⁻⁶ × 500×10³) ≈ 0,22 A` (%22 ripple).

2. **D** — `ΔI = 8,7 × 0,275 / (10×10⁻⁶ × 500×10³) ≈ 0,48 A`. `I_tepe = 1 + 0,48/2 ≈ 1,24 A`. Küçük L, daha yüksek tepe akım demektir.

3. **B** — `L = (12 − 3,3) × 0,275 / (500×10³ × 0,3) ≈ 16 µH`. Standart değer olarak 15 µH veya 22 µH seçilir.

4. **C** — `X_L = 2π × 10⁶ × 10×10⁻⁶ ≈ 62,8 Ω`.

5. **A** — `P = I² × DCR = 1² × 0,05 = 50 mW`.

6. **B** — Normal yükte tepe akım düşük olsa da kısa devre, ilk açılış ve yük sıçramalarında akım regülatörün limitine kadar çıkar. Bobin bu sırada doyarsa akım daha da fırlar ve anahtar yanabilir.

7. **A** — Ferrit belirli bir akımda endüktansını aniden kaybeder. Toz demir ve metal kompozit çekirdekler ise yavaşça kaybeder, bu yüzden aşırı yüke karşı daha affedicidir.

8. **C** — Diyot bobine paralel, katodu + tarafında bağlanır. MOSFET kapanınca bobin akımı diyot üzerinden dolaşır ve gerilim V_cc + ~0,7 V'ta kenetlenir.

9. **C** — Diyot tek başına akımı yavaş söndürür; röle geç bırakır. Seri Zener kenetleme gerilimini yükseltir, böylece `di/dt = V/L` büyür ve akım hızlı söner. MOSFET'in gerilim derecesi bu kenetleme gerilimine dayanmalıdır.

10. **D** — Sıcak döngüdeki akım her anahtarlamada aniden değişir. Döngü alanı büyüdükçe endüktans, gerilim sıçraması ve emisyon artar.

11. **B** — SW düğümü her anahtarlamada volt seviyesinde gerilimi nanosaniyeler içinde değiştirir. Geniş bakır alanı, komşu izlere ve dışarıya kapasitif kuplajla gürültü taşır.

12. **D** — İki sargı aynı çekirdek üzerindedir. Diferansiyel akımda akılar zıt yönde olduğu için birbirini götürür; ortak mod akımında aynı yönde olduğu için toplanır ve yüksek empedans oluşur.

</details>
