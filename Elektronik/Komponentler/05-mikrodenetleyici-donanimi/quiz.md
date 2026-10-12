# Quiz · Mikrodenetleyici donanımı

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 12 soru, 4'ü hesap.

## Sorular

1. **(Hesap)** Kristalin yük kapasitansı C_L = 12,5 pF, devrenin parazitik kapasitansı C_stray = 5 pF. Her bir yük kapasitörü kaç olmalıdır?
   - A) 7,5 pF
   - B) 12,5 pF
   - C) 15 pF
   - D) 25 pF

2. **(Hesap)** 3,3 V referanslı 12 bitlik bir ADC'nin 1 LSB'si yaklaşık kaçtır?
   - A) 0,08 mV
   - B) 0,81 mV
   - C) 8,1 mV
   - D) 81 mV

3. **(Hesap)** ADC'nin örnekleme kapasitörü 5 pF; pine 100 nF'lık harici kapasitör konmuş. 12 bitte yük paylaşım hatası yaklaşık kaç LSB'dir?
   - A) 0,002 LSB
   - B) 0,02 LSB
   - C) 0,2 LSB
   - D) 2 LSB

4. **(Hesap)** 12 bitlik ölçümde ½ LSB'ye oturmak için yaklaşık 9 zaman sabiti gerekir. Kaynak 10 kΩ, örnekleme kapasitörü 5 pF ise (ADC'nin iç direncini ihmal et) en az örnekleme süresi yaklaşık kaçtır?
   - A) 45 ns
   - B) 450 ns
   - C) 4,5 µs
   - D) 45 µs

5. Kristal osilatörün frekansını ölçmenin doğru yolu hangisidir?
   - A) Osiloskop probunu doğrudan OSC_OUT pinine değdirmek
   - B) Saati MCU'nun MCO pininden dışarı verip orada ölçmek
   - C) Kristalin gövdesine dokunmak
   - D) Multimetrenin frekans kademesini OSC_IN'e bağlamak

6. NRST'yi debug konnektörüne bağlamanın en önemli faydası nedir?
   - A) Kartın daha hızlı çalışması
   - B) Firmware SWD pinlerini başka işe atasa bile "connect under reset" ile MCU'ya bağlanabilmek
   - C) Güç tüketiminin azalması
   - D) Kristalin daha hızlı başlaması

7. BOOT0 pini boşta bırakılırsa ne olabilir?
   - A) Hiçbir şey olmaz
   - B) MCU rastgele şekilde flash yerine dahili bootloader'dan başlayabilir
   - C) MCU yanar
   - D) Saat frekansı iki katına çıkar

8. "Back-powering" nedir?
   - A) MCU'nun pilden beslenmesi
   - B) MCU kapalıyken bir girişe gelen gerilimin, pinin clamp diyotları üzerinden VDD rayını beslemesi
   - C) Regülatörün çıkıştan girişe akım vermesi
   - D) Debugger'ın MCU'yu beslemesi

9. Kullanılmayan GPIO pinleri için en doğru yazılım ayarı hangisidir?
   - A) Pull-up'sız dijital giriş
   - B) Analog mod (veya çıkış-alçak)
   - C) En yüksek hızda çıkış
   - D) Alternatif fonksiyon

10. USB full-speed neden genellikle kristal (veya saat kurtarma özelliği) gerektirir?
    - A) USB yalnızca kristalle çalışan pinlere bağlanabildiği için
    - B) USB full-speed yaklaşık ±%0,25 saat doğruluğu ister; dahili RC osilatör bunu garanti etmez
    - C) Kristal USB hattını korur
    - D) USB'nin gerilim seviyesi kristale bağlıdır

11. GPIO çıkış hızını (slew rate) gereken en düşük seviyeye ayarlamanın EMC faydası nedir?
    - A) Pinin akım kapasitesini artırır
    - B) Kenarları yumuşatarak yüksek frekanslı harmonikleri ve emisyonu azaltır
    - C) Saat frekansını artırır
    - D) ADC doğruluğunu düşürür

12. Sinyalde yeterli gürültü varken 16 kat aşırı örnekleme ve ortalama ile çözünürlük kaç bit artar?
    - A) 1 bit
    - B) 2 bit
    - C) 4 bit
    - D) 16 bit

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **C** — `C = 2·(C_L − C_stray) = 2 × (12,5 − 5) = 15 pF`. Dielektrik C0G olmalıdır.

2. **B** — `3,3 V / 4096 ≈ 0,81 mV`.

3. **C** — Hata ≈ `C_ADC / C_harici = 5 pF / 100 nF = 5×10⁻⁵`. 12 bitte `4096 × 5×10⁻⁵ ≈ 0,2 LSB`.

4. **B** — `τ = 10 kΩ × 5 pF = 50 ns`; `~9τ ≈ 450 ns`. Gerçekte ADC'nin iç direnci de eklenir; datasheet'teki R_AIN tablosu esastır.

5. **B** — Probun kapasitansı osilatörü yükler, frekansı kaydırır, hatta durdurabilir. MCO saati tamponlanmış olarak dışarı verir; ölçüm osilatörü etkilemez.

6. **B** — Firmware SWDIO/SWCLK pinlerini GPIO olarak ayarlarsa debugger normal yolla bağlanamaz. NRST'yi tutarak bağlanmak (connect under reset), firmware çalışmaya başlamadan kontrolü almayı sağlar.

7. **B** — BOOT0'ın seviyesi tanımsız kalırsa MCU her açılışta farklı kaynaktan başlayabilir. Pull-down ile flash'tan başlatma garanti edilir.

8. **B** — MCU kapalıyken VDD ~0 V'tur. Girişe gelen gerilim, pinin VDD'ye bağlı clamp diyotunu iletime sokar ve rayı besler. MCU yarım çalışır, latch-up olabilir.

9. **B** — Boşta bırakılan CMOS giriş ara gerilimde kalabilir; hem akım çeker hem gürültü kapar. Analog mod girişi devre dışı bırakır ve en düşük tüketimi sağlar.

10. **B** — USB full-speed ±%0,25 doğruluk ister. Dahili RC osilatörlerin sıcaklıkla sapması bunun çok üstündedir. Bazı MCU'lar USB'nin kendi sinyalinden saati düzelten bir özellikle (clock recovery) kristalsiz çalışabilir.

11. **B** — Emisyon spektrumunu saat frekansından çok kenar süresi belirler. Yumuşak kenarlar yüksek frekanslı harmonikleri azaltır.

12. **B** — Her 4 kat aşırı örnekleme 1 bit kazandırır: `16 = 4²` → 2 bit. Bunun çalışması için sinyalde en az birkaç LSB gürültü olmalıdır.

</details>
