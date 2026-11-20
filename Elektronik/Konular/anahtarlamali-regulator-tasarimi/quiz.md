# Quiz · Anahtarlamalı regülatör tasarımı: buck, boost ve ters buck-boost

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 12 soru, 8'i hesap.

## Sorular

1. **(Hesap)** Buck: `V_in` = 24 V, `V_out` = 5 V, verim tahmini η = %90. Görev oranı `D = V_out/(V_in·η)` nedir?
   - A) 0,208
   - B) 0,231
   - C) 0,188
   - D) 0,792

2. **(Hesap)** Buck: `V_in` = 18–30 V, `V_out` = 5 V, `f_s` = 500 kHz, `I_out` = 1 A; hedef `ΔI_L` = 0,3·`I_out`. `L = V_out·(V_in − V_out)/(ΔI_L·V_in·f_s)` ifadesini hangi `V_in` ile uygulamalı ve sonuç ne olur?
   - A) 24,1 µH (`V_in` = 18 V ile)
   - B) 26,4 µH (`V_in` = 24 V ile)
   - C) 27,8 µH (`V_in` = 30 V ile)
   - D) 55,6 µH (`V_in` = 30 V ile, ama `ΔI_L` hedefi yarıya indirilerek)

3. **(Hesap)** Aynı buck: IC'nin garanti edilen en küçük tepe akım limiti `I_LIM,min` = 1,7 A, `L` = 33 µH, `V_in,maks` = 30 V. Çıkışta sürekli verilebilecek akım `I_MAXOUT = I_LIM,min − ΔI_L/2` yaklaşık kaçtır?
   - A) 1,57 A
   - B) 1,70 A
   - C) 1,45 A
   - D) 1,83 A

4. **(Hesap)** Aynı buck'ta `V_in` = 18 V, `V_out` = 5 V, `I_out` = 1 A (`ΔI_L` ihmal). Giriş kapasitöründen geçen rms akım yaklaşık nedir?
   - A) 1,00 A
   - B) 0,50 A
   - C) 0,28 A
   - D) 0,45 A

5. `V_in` = 30 V, `V_out` = 5 V, `f_s` = 2 MHz ve IC'nin `t_on,min` = 100 ns olan bir buck tasarımında ne olur?
   - A) Sorun yok: görev oranı %16,7 olduğundan yeterince büyüktür
   - B) Yalnız verim düşer; çıkış dalgalanması ve gürültü etkilenmez
   - C) `t_on = D/f_s` = 83 ns < 100 ns: IC bu kısa darbeyi üretemez ve darbe atlar (dalgalanma ve duyulabilir gürültü artar). Çözüm: frekansı ≤ 1,67 MHz'e indirmek ya da `t_on,min`'i küçük IC seçmek
   - D) Bobin yüksek frekansta doyar; `L`'yi büyütmek sorunu çözer

6. **(Hesap)** Boost: `V_in,min` = 3,0 V, `V_out` = 5 V, `I_out` = 0,5 A, η = %85. `D = 1 − V_in,min·η/V_out` ile hesaplayıp indüktörün ortalama akımı `I_L,ort = I_out/(1−D)` nedir?
   - A) 0,50 A
   - B) 0,98 A
   - C) 0,83 A
   - D) 0,71 A

7. **(Hesap)** Aynı boost: `f_s` = 1 MHz, `L` = 4,7 µH, `D` = 0,49, `R_L = V_out/I_out` = 10 Ω. `f_RHPZ = R_L·(1−D)²/(2π·L)` ve bu derste kullanılan `f_c ≤ f_RHPZ/5` kuralıyla döngü çapraz frekansının üst sınırı nedir?
   - A) 17,6 kHz
   - B) 88,1 kHz
   - C) 100 kHz
   - D) 29,4 kHz

8. **(Hesap)** 24 V adaptör, kablo `L` = 5 µH, seri direnç `R_s` = 0,10 Ω, giriş seramiği etkin 11 µF. Seri RLC adım yanıtının tepesi `V·(1 + e^(−πζ/√(1−ζ²)))`, `ζ = ½·R_s·√(C/L)` ile bulunur. Korumasız `V_in` tepesi yaklaşık kaç volttur?
   - A) 48,0 V
   - B) 35,7 V
   - C) 57,2 V
   - D) 43,0 V

9. Bir buck 10 mA hafif yükte FPWM'de yaklaşık %37 verimle çalışıyor. PFM (auto) modu verimi neden yükseltir ve bedeli nedir?
   - A) PFM, FET'lerin `R_DS(on)`'unu düşürür; bedeli yoktur
   - B) Çıkış ihtiyaç duyana kadar darbe atılmaz: kapı, Coss, ters toparlanma gibi frekansla orantılı kayıplar ve `I_q` azalır. Bedeli: değişken frekans (işitilebilir ses, dağınık EMI), darbe başına büyük dalgalanma ve mod geçişinde sapma
   - C) İndüktör akımı negatif olur ve enerji girişe geri verilir; bedeli çıkış dalgalanmasının artmasıdır
   - D) Frekans sabit kalır ama bobin küçülür; bedeli yalnız kart alanıdır

10. Peak-current-mode buck'ın Tip II kompanzatörü nominal etkin `C_out` ile tasarlandı (`f_c` ≈ 48 kHz, PM ≈ 55°). Seramik `C_out`'un etkin değeri DC bias ve sıcaklıkla %20 düşerse ne olur?
    - A) `f_c` düşer (≈ 41 kHz), PM artar (≈ 57°): kapasite azalınca döngü yavaşlar
    - B) `f_c` ve PM değişmez: PCM'de güç katı yük ve kapasiteden bağımsızdır
    - C) `f_c` yükselir (≈ 59 kHz), PM azalır (≈ 51°): `f_p`'nin üstünde kazanç `C_out` ile ters orantılıdır
    - D) PM 30°'nin altına çöker ve döngü osilasyona girer

11. **(Hesap)** 12 V girişli, sabit güçlü bir regülatör `P_in` = 50 W çekiyor. Giriş filtresinin çıkış empedansı tepesi `Z_out,tepe` = 4,6 Ω. `|R_in| = V_in²/P_in` ile marj `20·log10(|R_in|/Z_out,tepe)` kaç dB'dir ve sonuç ne anlama gelir?
    - A) −4,1 dB: negatif marj; filtre ve regülatör birlikte kararsız olur (damper gerekir)
    - B) +4,1 dB: 6 dB kuralının altında ama kararlı
    - C) +22,3 dB: rahat marj
    - D) +16,1 dB: rahat marj

12. Li-ion (3,0–4,2 V) → 5 V standart (true-shutdown olmayan) bir boost IC'si EN pininden devre dışı bırakıldı ve yük bağlı kaldı. Çıkış ne olur?
    - A) Çıkış 0 V'a düşer ve yük kapanır
    - B) Çıkış 5 V'ta kalır; IC yalnız anahtarlamayı bırakmıştır
    - C) Çıkış yüzer (floating), gerilimi belirsizdir ve yüke bağlı değildir
    - D) Çıkış, indüktör ve diyot üzerinden yaklaşık `V_in − V_F`'ye iner; yük pilden beslenmeye devam eder. Gerçek kapatma için true-shutdown IC ya da yük anahtarı gerekir

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>


1. **B** — `D = V_out/(V_in·η) = 5/(24 · 0,90) = 0,231`. Kayıplar anahtarı biraz daha uzun iletmeyi gerektirir. A, η'yı unutur (`5/24 = 0,208`: kayıpsız ideal). C, η'yı paya koyar (`5 · 0,90/24 = 0,188`). D, `1 − V_out/V_in = 0,792`'dir: bu alt anahtarın iletim oranıdır (`1 − D`), `D` değil.

2. **C** — `ΔI_L` en büyük `V_in,maks`'ta olduğundan `L` orada seçilir: `L = 5 · 25/(0,3 · 30 · 500 000) = 27,8 µH`; standart değer 33 µH. A, `V_in,min` = 18 V ile hesaplar (24,1 µH): 30 V'ta `ΔI_L` hedefin üstüne çıkar. B, nominal 24 V ile hesaplar (26,4 µH): aynı hata, daha küçük. D, `ΔI_L` hedefini yarıya indirir (55,6 µH): gereksiz büyük `L`; DCR ve boyut artar, doyma akımı düşer.

3. **A** — `ΔI_L = (30 − 5) · (5/30)/(33 µH · 500 kHz) = 0,2525 A`; `I_MAXOUT = 1,7 − 0,2525/2 = 1,57 A`. IC **tepe** akımı sınırlar, bu yüzden dalgalanmanın yarısı çıkarılır. B, dalgalanmayı unutur (1,70 A). C, dalgalanmanın tamamını çıkarır (1,45 A). D, yarısını ekler (1,83 A): yön ters.

4. **D** — `I_Cin,rms = I_out·√(D(1−D))`, `D = 5/18 = 0,278` → `√(0,278 · 0,722) = 0,448 A`. A, `I_out`'u (1,00 A) kullanır: giriş akımı darbelidir ve rms değeri `I_out`'tan küçüktür. B, `D` = 0,5'teki en kötü değerdir (`I_out/2`); bu `D` için değil. C, `D·I_out` = 0,28 A'dir: bu ortalama giriş akımıdır, rms değil.

5. **C** — `D = 5/30 = 0,167`; `t_on = D/f_s` = 83 ns < `t_on,min`. IC darbe atlar: çıkış dalgalanması ve duyulabilir gürültü artar. İzin verilen en yüksek frekans `D/t_on,min` = 1,67 MHz'dir. A, `D`'nin büyüklüğüne bakar: önemli olan açık kalma **süresidir**. B, darbe atlamanın çıkışı etkilemeyeceğini sanır: dalgalanma artar ve spektrum bozulur. D, doyma ile ilgisizdir: yüksek frekans `ΔI_L`'yi küçültür.

6. **B** — `D = 1 − 3,0 · 0,85/5 = 0,49`; `I_L,ort = 0,5/(1 − 0,49) = 0,98 A` (`I_out·V_out/(V_in·η)` ile aynı). A, buck'taki gibi `I_out`'u alır: boost'ta indüktör **girişte**dir ve giriş akımını taşır. C, η'yı unutur (`0,5 · 5/3 = 0,83 A`). D, η'yı ters yöne uygular (`0,83 · 0,85 = 0,71 A`): kayıplar giriş akımını **artırır**.

7. **A** — `f_RHPZ = 10 · (1 − 0,49)²/(2π · 4,7 µH) = 88,1 kHz`; `f_c ≤ 88,1/5 = 17,6 kHz`. B, `f_RHPZ`'nin kendisidir: orada faz payı erir. C, buck alışkanlığıdır (`f_s/10` = 100 kHz): boost'ta RHPZ sınırlar. D, daha gevşek `f_RHPZ/3` kuralıdır (29,4 kHz); bu ders `/5` kullanır.

8. **D** — `Z0 = √(5 µH/11 µF) = 0,67 Ω`, `ζ = 0,5 · 0,10 · √(11/5) = 0,074`; tepe `= 24 · (1 + e^(−π·0,074/√(1−0,074²))) = 43,0 V` (×1,79). A, sönümsüz ideal sınırdır (2·`V_in` = 48 V): `ζ` > 0 olduğu için tepe bunun altında kalır. B, `R_s` = 0,30 Ω'luk satırdır (35,7 V). C, AN88'in 10 µF ve 1 µH'lık **ölçümüdür** (57,2 V); devre farklıdır.

9. **B** — PFM'de çıkış ihtiyaç duyana kadar darbe atılmaz: kapı, Coss, ters toparlanma ve ölü zaman gibi frekansla orantılı kayıplar ile `I_q` azalır. Bedeli: değişken frekans (işitilebilir ses, dağınık EMI), darbe başına büyük dalgalanma ve mod geçişinde sapma. A, FET direncini değiştirmez; bedelsiz verim yoktur. C, FPWM'i anlatır (akım negatif, enerji girişe geri akar): verimin düşük olmasının nedeni budur. D, frekansı sabit tutmak FPWM ya da DCM'dir ve bobin küçülmez.

10. **C** — PCM'de `f_p`'nin üstünde döngü kazancı `R_L`'den bağımsızdır ve `C_out` ile **ters orantılıdır**: kapasite %20 düşünce kazanç artar, `f_c` ≈ 59 kHz'e çıkar ve faz payı ≈ 51°'ye iner (kapasite %20 artarsa ≈ 41 kHz ve 57°). A, +%20 durumunun sonucudur: yön ters. B, yük bağımsızlığını kapasiteye de genişletir: `f_c` kapasiteye bağlıdır. D, bu değişim PM'i 51°'de bırakır: marj erir ama osilasyon yoktur; yine de etkin değerle tasarla ve ±%20'de ölç.

11. **A** — `|R_in| = V_in²/P_in = 12²/50 = 2,88 Ω`; `20·log10(2,88/4,6) = −4,1 dB`: negatif. `Z_out` tepesi `|R_in|`'i aşıyor, filtre ve regülatör birlikte **kararsız** olur (damper gerekir). B, işareti ters alır ve 6 dB kuralının altında kalsa bile kararlı sanır. C, +22,3 dB Örnek A'nın marjıdır (18 V, 5,4 W): `P_in` küçük, `|R_in|` büyük. D, +16,1 dB damperli durumdur: damper `Z_out` tepesini 0,45 Ω'a indirir.

12. **D** — Standart boost'ta indüktör ve diyot girişten çıkışa doğrudan yol bırakır: IC durunca çıkış yaklaşık `V_in − V_F`'ye iner ve yük pilden beslenmeye devam eder (sızıntı, "kapalı ama enerjili" yük). Çözüm: **true-shutdown** boost IC'si ya da yük anahtarı. A, çıkışın 0 V'a düşeceğini sanır: diyot yolu bunu engeller. B, regülasyonun IC durunca da süreceğini sanır: anahtarlama biter, regülasyon da biter. C, çıkışın yüzdüğünü sanır: iletim yolu vardır, gerilim belirsiz değildir.

</details>
