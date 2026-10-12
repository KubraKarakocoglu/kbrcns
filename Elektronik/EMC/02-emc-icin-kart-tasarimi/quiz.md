# Quiz · EMC için kart tasarımı

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 12 soru, 4'ü hesap.

## Sorular

1. **(Hesap)** IEC 61000-4-2'ye göre ilk tepe akımı yaklaşık 3,75 A/kV'tur. 8 kV kontak deşarjında tepe akım yaklaşık kaçtır?
   - A) 3 A
   - B) 30 A
   - C) 8 A
   - D) 300 A

2. **(Hesap)** Bu 30 A'lik akım 0,8 ns'de yükseliyor ve TVS'in GND bağlantısının endüktansı 1 nH. Bağlantı üzerinde oluşan ek gerilim yaklaşık kaçtır?
   - A) 37,5 V
   - B) 0,4 V
   - C) 3,75 V
   - D) 375 V

3. **(Hesap)** 50 Ω'luk bir izi, çıkış direnci yaklaşık 20 Ω olan bir sürücü sürüyor. Seri sonlandırma için hangi standart değer uygundur?
   - A) 4,7 Ω
   - B) 330 Ω
   - C) 33 Ω
   - D) 3,3 kΩ

4. **(Hesap)** "Dikiş via'ları arası mesafe ≤ λ/20" kaba kuralına göre 1 GHz için en fazla aralık yaklaşık kaçtır?
   - A) 1,5 mm
   - B) 1,5 cm
   - C) 15 cm
   - D) 1,5 m

5. Hızlı bir sinyal GND düzlemindeki bir yarığın üzerinden geçerse ne olur?
   - A) Hiçbir şey; GND her yerde aynıdır
   - B) Sinyal hızlanır
   - C) Dönüş akımı yarığın etrafından dolaşır, döngü alanı büyür; emisyon ve bozucu alma artar
   - D) Yarık bir filtre gibi gürültüyü engeller

6. 4 katmanlı bir kart için önerilen klasik dizilim hangisidir?
   - A) Sinyal / GND / Güç / Sinyal
   - B) Sinyal / Sinyal / GND / Güç
   - C) GND / Güç / Sinyal / Sinyal
   - D) Güç / Sinyal / Sinyal / GND

7. Konnektörleri kartın tek bir kenarında toplamanın EMC açısından nedeni nedir?
   - A) Montaj kolaylığı
   - B) Kartın daha ucuz olması
   - C) Isınmayı azaltmak
   - D) Karşılıklı kenarlardaki konnektörlere bağlı kablolar, aradaki toprak gerilim farkıyla bir dipol antenin iki kolu gibi davranır

8. Bir harici hattaki TVS diyot nereye yerleştirilmelidir?
   - A) Konnektörden sonraki ilk komponent olarak, GND bağlantısı kısa olacak şekilde
   - B) Korunan IC'nin yanına
   - C) Kartın ortasına
   - D) Nereye konduğu önemli değildir

9. USB 2.0 veri hatlarını ESD'ye karşı korumak için hangisi uygundur?
   - A) Her hatta 100 nF kapasitör
   - B) Her hatta ayrı ferrit boncuk
   - C) Hatlara seri 1 kΩ direnç
   - D) Düşük kapasitanslı (<1 pF) ESD koruma dizisi, gerekirse ortak mod bobini

10. Bir hızlı sinyal L1'den L4'e via ile geçiyor (L2 GND, L3 Güç). Sinyal via'sının yanına ne eklenmelidir?
    - A) Hiçbir şey
    - B) Dönüş akımı için bir dikiş kapasitörü (GND–Güç) veya uygun dönüş via'sı
    - C) Seri ferrit boncuk
    - D) Bir test noktası

11. Kablo ekranı konnektörde nasıl sonlandırılmalıdır?
    - A) Tek bir telle (pigtail) devre GND'sine
    - B) Hiç bağlanmamalıdır
    - C) Bir direnç üzerinden
    - D) Kasaya 360° (çepeçevre) bağlantıyla

12. Gaz dedektöründe ESD testi sırasında okunan değer anlık olarak sıçrıyor ve yanlış alarm oluşuyor. Hangi yazılım önlemi en doğrudan yardımcı olur?
    - A) Saat frekansını artırmak
    - B) Watchdog'u kapatmak
    - C) Alarmı birden fazla ardışık örnekle onaylamak, değerlerde makul aralık ve değişim hızı kontrolü yapmak
    - D) ADC çözünürlüğünü düşürmek

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **B** — `8 kV × 3,75 A/kV = 30 A`.

2. **A** — `V = L · di/dt = 1×10⁻⁹ × 30 / 0,8×10⁻⁹ ≈ 37,5 V`. TVS ne kadar iyi kenetlerse kenetlesin, bu gerilim korunan pine eklenir. GND bağlantısı bu yüzden kısa olmalıdır.

3. **C** — `R ≈ Z0 − R_sürücü = 50 − 20 = 30 Ω`; en yakın standart değer 33 Ω. Direnç sürücü pininin hemen yanına konur.

4. **B** — `λ = 30 cm`; `λ/20 = 1,5 cm`. Bu yalnızca kaba bir kuraldır.

5. **C** — Yüksek frekanslı dönüş akımı izin altından akmak ister. Yarık bunu engeller; akım yarığın etrafından dolaşır ve döngü büyür. Büyük döngü hem anten olarak ışır hem dışarıdan alan toplar.

6. **A** — L1 sinyalleri L2'deki GND'yi, L4 sinyalleri L3'teki güç düzlemini referans alır. En hızlı sinyaller GND'ye bitişik L1'de yönlendirilmelidir.

7. **D** — İki konnektörün GND noktaları arasında küçük de olsa yüksek frekanslı bir gerilim farkı vardır. Bu fark iki kabloyu dipol antenin iki kolu gibi sürer.

8. **A** — TVS konnektöre en yakın yerde olursa ESD akımı karta girmeden GND'ye veya kasaya yönlendirilir. GND bağlantısının kısa olması kenetlemenin etkinliği için şarttır.

9. **D** — USB 2.0 yüksek hızlı bir hattır. Büyük kapasitör ve ayrı boncuklar sinyali bozar. Düşük kapasitanslı ESD dizileri bu iş için tasarlanmıştır.

10. **B** — Sinyalin referansı GND'den güç düzlemine değişir; dönüş akımının da bir düzlemden diğerine geçmesi gerekir. Yakında bir dikiş kapasitörü (veya iki taraf da GND ise GND–GND via'sı) bu yolu sağlar.

11. **D** — Pigtail yüksek frekansta endüktans ekler ve ekran akımının kasaya kısa yoldan ulaşmasını engeller. 360° bağlantı en düşük empedanslı yoldur.

12. **C** — Donanım önlemleri bozucunun etkisini azaltır, ama tamamen yok edemeyebilir. Alarmı ardışık örneklerle onaylamak ve fiziksel olarak imkânsız sıçramaları reddetmek, kısa süreli bozucuların yanlış alarma dönüşmesini engeller.

</details>
