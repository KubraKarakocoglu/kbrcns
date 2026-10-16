# Quiz · Op-amp ve sensör ön ucu

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 10 soru, 5'i hesap.

## Sorular

1. **(Hesap)** Evirmeyen bir yükselteçte Rf = 99 kΩ, Rg = 1 kΩ. Girişe 10 mV uygulanırsa çıkış kaç olur?
   - A) 99 mV
   - B) 0,1 V
   - C) 1,0 V
   - D) 10 V

2. **(Hesap)** Ofset gerilimi 2 mV olan bir op-amp 50 kazançla kullanılıyor. Çıkıştaki ofset hatası kaçtır?
   - A) 100 mV
   - B) 2 mV
   - C) 25 mV
   - D) 1 V

3. **(Hesap)** GBW'si 1 MHz olan bir op-amp 100 kazançla kullanılıyor. Bant genişliği yaklaşık kaçtır?
   - A) 1 MHz
   - B) 100 kHz
   - C) 100 Hz
   - D) 10 kHz

4. **(Hesap)** 2,5 V ile beslenen dengeli bir köprüde bir direnç %0,4 değişiyor. Köprü çıkışı yaklaşık kaç olur?
   - A) 10 mV
   - B) 2,5 mV
   - C) 0,25 mV
   - D) 25 mV

5. **(Hesap)** Bir sensör girişine arıza durumunda 24 V gelebilir. Kenetleme 3,6 V'ta, girişin dayanabileceği en yüksek akım 5 mA. Seri koruma direnci en az kaç olmalıdır?
   - A) 720 Ω
   - B) 4,8 kΩ
   - C) yaklaşık 4,1 kΩ
   - D) 41 kΩ

6. Oransal (ratiometric) ölçümün asıl faydası nedir?
   - A) ADC'nin bit sayısını artırır
   - B) Gürültüyü tamamen yok eder
   - C) Referans IC'si gerektirir
   - D) Sensör beslemesi ile ADC referansı aynı kaynaktan geldiği için beslemedeki kayma ve tolerans ölçümde birbirini götürür

7. Ölçüm yükseltecinin (INA) REF pini doğrudan iki dirençli bir bölücüye bağlanmış. Sorun nedir?
   - A) Bölücünün direnci INA'nın iç dirençlerine eklenir; kazanç ve CMRR bozulur. REF pini bir tamponla sürülmelidir
   - B) Hiçbir sorun yoktur
   - C) INA'nın kazancı sıfır olur
   - D) REF pini yalnızca GND'ye bağlanabilir

8. Gaz dedektöründe sıfır noktası ortam sıcaklığıyla saatler içinde yavaşça kayıyor. Hangi çözüm doğrudur?
   - A) Daha güçlü bir alçak geçiren RC filtre
   - B) Kayma, bilgi kadar yavaş olduğu için filtre ayıramaz; kompanzatör eleman, sıcaklık kompanzasyonu ve kalibrasyon kullanılır
   - C) Yüksek geçiren filtre
   - D) Örnekleme frekansını artırmak

9. Tek beslemeli (0–3,3 V) bir op-amp'ın girişindeki sensör sinyali gaz yokken 0 V'a çok yakın. Olası sorun nedir?
   - A) Op-amp aşırı ısınır
   - B) Kazanç sonsuz olur
   - C) Çıkış 0 V'a tam inemez; küçük sinyaller doyumda kaybolur. RRIO op-amp, sanal toprak veya ofsetle sinyal raydan uzaklaştırılır
   - D) Hiçbir sorun olmaz

10. Yüksek empedanslı bir sensör çıkışıyla ADC arasına tampon (gerilim izleyici) koymanın amacı nedir?
    - A) Kaynağı, ADC'nin örnekleme kapasitörünün çektiği akımdan ayırmak; sinyali yükseltmeden düşük empedanslı hâle getirmek
    - B) Sinyali 10 kat yükseltmek
    - C) Sinyali evirmek
    - D) Gürültüyü artırmak

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **C** — `G = 1 + 99k/1k = 100`; `10 mV × 100 = 1,0 V`.

2. **A** — `2 mV × 50 = 100 mV`. Bir gaz dedektöründe bu, ölçüm aralığının ciddi bir kısmı olabilir. Başlangıç ofseti kalibrasyonla silinir ama sıcaklıkla kayması silinmez.

3. **D** — `BW ≈ 1 MHz / 100 = 10 kHz`. Saniyeler mertebesindeki gaz sinyali için fazlasıyla yeterlidir.

4. **B** — `ΔV ≈ Vb × ΔR / (4R) = 2,5 × 0,004 / 4 = 2,5 mV`. Bu kadar küçük bir sinyal, ölçümden önce yükseltilmelidir.

5. **C** — `R ≥ (24 − 3,6) / 0,005 ≈ 4,08 kΩ`. Standart değer olarak bir üstteki 4,7 kΩ seçilir.

6. **D** — Köprü veya bölücünün çıkışı beslemeyle orantılıdır. ADC referansı aynı beslemeden gelirse, besleme %1 arttığında hem sinyal hem cetvel %1 artar; oran değişmez.

7. **A** — INA'nın içindeki fark katı, REF pininin düşük empedanslı bir kaynaktan sürüldüğünü varsayar. Bölücünün Thevenin direnci bu dengeyi bozar; kazanç hatası oluşur ve CMRR düşer.

8. **B** — Filtre ancak gürültü bilgiden çok farklı bir hızdaysa işe yarar. Sıcaklık kayması bilgi kadar yavaştır. Pellistordaki kompanzatör boncuk, sıcaklık sensörüyle yazılım kompanzasyonu ve periyodik kalibrasyon bu yüzden vardır.

9. **C** — Rail-to-rail çıkış bile raya tam ulaşamaz. Gaz yokken sıfıra yakın olan sinyal, çıkışın inebildiği en düşük değerin altında kalır ve ilk ppm'ler kaybolur.

10. **A** — ADC'nin örnekleme kapasitörü her örnekte kaynaktan kısa bir akım çeker. Yüksek empedanslı kaynak bu akımı veremez ve ölçüm hatalı olur. Tampon kaynağı yüklemez ve ADC'yi düşük empedansla sürer.

</details>
