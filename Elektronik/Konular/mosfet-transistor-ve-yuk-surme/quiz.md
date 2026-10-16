# Quiz · MOSFET, transistör ve yük sürme

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 10 soru, 4'ü hesap.

## Sorular

1. **(Hesap)** 3,3 V'luk bir pinden kırmızı LED (V_F = 2,0 V) 5 mA ile sürülecek. Seri direnç teorik olarak kaç olmalıdır?
   - A) 660 Ω
   - B) 260 Ω
   - C) 26 Ω
   - D) 400 Ω

2. **(Hesap)** 3,3 V'luk MCU pini, NPN transistörle 30 mA'lik bir röle bobinini sürecek. Zorlanmış β = 10, V_BE = 0,7 V. Baz direnci teorik olarak kaç olmalıdır?
   - A) 8,7 kΩ
   - B) 87 Ω
   - C) 867 Ω
   - D) 110 Ω

3. **(Hesap)** R_DS(on) = 40 mΩ olan bir MOSFET'ten 2 A geçiyor. İletim kaybı kaçtır?
   - A) 0,16 W
   - B) 0,08 W
   - C) 0,32 W
   - D) 1,6 W

4. **(Hesap)** Gate yükü Qg = 20 nC olan bir MOSFET'i yaklaşık 10 mA verebilen bir MCU pini sürüyor. Gate'in dolma süresi kabaca ne kadardır?
   - A) 0,2 µs
   - B) 20 µs
   - C) 2 ms
   - D) 2 µs

5. Datasheet'te Vgs(th) = 1,5 V yazan bir MOSFET'i 3,3 V'luk MCU ile sürmek istiyorsun. Doğru yaklaşım hangisidir?
   - A) 3,3 V > 1,5 V olduğu için MOSFET kesin tam açılır
   - B) Vgs(th) R_DS(on)'a eşittir
   - C) Vgs(th) MOSFET'in çok küçük bir akım geçirmeye başladığı gerilimdir; datasheet'te 2,5 V veya 3,3 V için belirtilmiş R_DS(on) değeri aranmalıdır
   - D) Vgs(th) ne kadar yüksekse MOSFET o kadar iyi açılır

6. MOSFET gate'inden GND'ye konan 100 kΩ'luk pull-down direncinin asıl görevi nedir?
   - A) Reset ve açılış sırasında MCU pini boştayken gate'i kapalı tutmak; yükün kendiliğinden çalışmasını önlemek
   - B) MOSFET'i daha hızlı açmak
   - C) Gate akımını artırmak
   - D) R_DS(on)'u düşürmek

7. Röle bobinine flyback diyotu nasıl bağlanır?
   - A) Bobine seri, katot GND tarafında
   - B) MOSFET'in gate'ine seri
   - C) Bobine paralel, katot GND tarafında
   - D) Bobine paralel, katot besleme (+) tarafında

8. Datasheet'inde "10 A 250 VAC / 10 A 30 VDC" yazan bir röle ile 48 VDC, 5 A'lik bir yük anahtarlanacak. Hangisi doğrudur?
   - A) Uygundur, çünkü 5 A < 10 A
   - B) Uygun değildir; DC'de ark kendiliğinden sönmez ve röle 48 VDC için belirtilmemiş. DC değeri yeterli bir röle seçilmelidir
   - C) Uygundur, çünkü 48 V < 250 V
   - D) Kontaklara seri direnç konursa uygundur

9. Dahili osilatörü olmayan bir piezo buzzer (transducer) nasıl sürülür?
   - A) Rezonans frekansında (datasheet'teki, tipik birkaç kHz) bir PWM sinyaliyle; ses için iki pinden ters fazda sürmek salınımı iki katına çıkarır
   - B) DC gerilim vererek
   - C) Flyback diyotu ile DC vererek
   - D) Sadece 50 Hz ile

10. Bir kapı otomatiği (12 V solenoid) MCU'dan bir MOSFET ile sürülüyor. Güvenlik açısından hangisi doğrudur?
    - A) Firmware çalıştığı sürece başka önlem gerekmez
    - B) Solenoid sürekli enerjili kalabilir, süre sınırı gerekmez
    - C) Gate pull-down ile açılışta kilit kapalı kalmalı; firmware'de en uzun açık kalma süresi ve watchdog olmalı; kablo tarafına flyback diyotu ve TVS konmalı
    - D) Flyback diyotu yalnızca AC kilitlerde gerekir

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **B** — `R = (3,3 − 2,0) / 0,005 = 260 Ω`. Standart değer olarak 270 Ω seçilir → yaklaşık 4,8 mA.

2. **C** — `Ib = 30 mA / 10 = 3 mA`; `Rb = (3,3 − 0,7) / 3 mA ≈ 867 Ω`. Standart değer olarak bir alttaki 820 Ω seçilir; baz akımı biraz artar ve doyum garantilenir.

3. **A** — `P = I² × R = 2² × 0,04 = 0,16 W`. Akım iki katına çıkınca kayıp dört katına çıkar.

4. **D** — `t ≈ Qg / I = 20 nC / 10 mA = 2 µs`. Birkaç kHz'lik PWM için kabul edilebilir; yüksek frekansta geçiş kaybı büyür ve gate sürücü gerekir.

5. **C** — Vgs(th), ör. 250 µA gibi çok küçük bir akımın aktığı gerilimdir. MOSFET bu gerilimde neredeyse kapalıdır. Datasheet'teki R_DS(on) tablosunda MCU gerilimine uygun (2,5 V / 3,3 V) bir satır yoksa MOSFET yarı açık kalır ve ısınır.

6. **A** — Reset ve açılış sırasında MCU pinleri yüksek empedanstadır. Boştaki gate gürültü kapar ve MOSFET kendiliğinden ya da yarı açılabilir. Pull-down, firmware çalışmaya başlamadan önce de yükün kapalı kalmasını donanımla garanti eder.

7. **D** — Diyot bobine paralel ve ters yönde bağlanır: katot + tarafta. Normal çalışmada iletmez. Anahtar kapanınca bobin akımı diyot üzerinden dolaşır ve gerilim sıçraması kenetlenir. Ters bağlanırsa bobini kısa devre eder.

8. **B** — AC akım her yarım periyotta sıfırdan geçer ve ark söner; DC'de sıfır geçişi yoktur ve ark devam edip kontağı yakar. Bu yüzden DC kontak değeri çok daha düşük bir gerilimde verilir. 48 VDC için belirtilmiş bir röle (veya yarı iletken anahtar) seçilir.

9. **A** — Transducer'ın kendi osilatörü yoktur; DC verince yalnızca "tık" sesi çıkarır. Rezonans frekansında sürüldüğünde en yüksek sesi verir. İki pinden ters fazda sürmek (köprü), uçlar arasındaki salınımı iki katına çıkarır.

10. **C** — Kilit bir güvenlik elemanıdır: açılışta, reset'te veya firmware takıldığında kendiliğinden açılmamalıdır. Gate pull-down açılışı, watchdog ve zaman aşımı takılmayı, flyback diyotu ve TVS kablodaki darbeleri karşılar. Solenoidler sürekli enerjiye göre tasarlanmamış olabileceği için süre sınırı ayrıca ısınmayı önler.

</details>
