# Quiz · Direnç

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 11 soru, 5'i hesap.

## Sorular

1. **(Hesap)** 50 mΩ'luk bir şanttan 2 A geçiyor. %50 derating kuralına göre hangi paket uygundur?
   - A) 0603 (0,1 W)
   - B) 0805 (0,125 W)
   - C) 1206 (0,25 W)
   - D) 2512 (1 W)

2. **(Hesap)** 3,3 V'luk bir GPIO, ileri gerilimi 2,0 V olan bir LED'i 5 mA ile sürecek. E24 serisinden hangi direnç seçilir?
   - A) 68 Ω
   - B) 270 Ω
   - C) 680 Ω
   - D) 2,7 kΩ

3. **(Hesap)** 400 kHz I²C hattının kapasitansı 200 pF; izin verilen yükselme süresi 300 ns. Pull-up direncinin üst sınırı yaklaşık kaçtır?
   - A) 590 Ω
   - B) 1,77 kΩ
   - C) 5,9 kΩ
   - D) 17,7 kΩ

4. **(Hesap)** TCR'si 100 ppm/°C olan bir direnç 25 °C'den 75 °C'ye ısınıyor. Değeri yaklaşık yüzde kaç değişir?
   - A) %0,05
   - B) %0,5
   - C) %5
   - D) %50

5. **(Hesap)** R1 = 30 kΩ ve R2 = 10 kΩ'luk bir bölücü %1'lik dirençlerle kuruluyor. Çıkış oranındaki en kötü durum hatası yaklaşık kaçtır?
   - A) ±%0,5
   - B) ±%1
   - C) ±%1,5
   - D) ±%2

6. 0603 paketli 1 MΩ bir dirençte (0,1 W, 75 V) hangi limit önce dolar?
   - A) Güç limiti
   - B) Maksimum çalışma gerilimi
   - C) İkisi aynı anda dolar
   - D) Akım limiti

7. Bir direncin değeri 4 katına çıkarsa termal gürültü gerilimi nasıl değişir?
   - A) Değişmez
   - B) 2 katına çıkar
   - C) 4 katına çıkar
   - D) 16 katına çıkar

8. Akım ölçme şantında Kelvin (4 telli) bağlantı neden kullanılır?
   - A) Şantın gücünü artırmak için
   - B) Pad, lehim ve iz dirençlerinin ölçüme eklenmemesi için
   - C) Gürültüyü artırmak için
   - D) Şantı soğutmak için

9. Kükürtlü bir endüstriyel ortamda standart kalın film dirençler neden arızalanır?
   - A) Kükürt, direncin seramik gövdesini eritir
   - B) Gümüş elektrot kükürtle tepkimeye girip iletken olmayan gümüş sülfür oluşturur; direnç artar ve açık devre olur
   - C) Kükürt direnci kısa devre yapar
   - D) Kükürt TCR'yi sıfırlar

10. Yüksek değerli bir geri besleme direncinde (1 MΩ) yaklaşık 0,1 pF parazitik kapasitans var. Empedans hangi frekansın üstünde belirgin şekilde düşmeye başlar?
    - A) ~16 kHz
    - B) ~160 kHz
    - C) ~1,6 MHz
    - D) ~160 MHz

11. Bir MOSFET'in gate'ine pull-down direnç koymanın temel nedeni nedir?
    - A) MOSFET'i daha hızlı açmak
    - B) MCU reset veya boot sırasında pin yüksek empedanstayken gate'in tanımsız kalıp yükü açmasını önlemek
    - C) Gate kapasitansını artırmak
    - D) Drain akımını ölçmek

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **D** — `P = I²·R = 2² × 0,05 = 0,2 W`. %50 derating ile en az 0,4 W anma gücü gerekir; seçenekler içinde yalnızca 2512 (1 W) bunu karşılar.

2. **B** — `R = (3,3 − 2,0) / 0,005 = 260 Ω`. E24'teki en yakın üst değer 270 Ω; akım 4,8 mA olur.

3. **B** — `R_max = t_r / (0,8473 × C_b) = 300 ns / (0,8473 × 200 pF) ≈ 1,77 kΩ`. Alt sınır `(3,3 − 0,4) / 3 mA ≈ 967 Ω`; tipik seçim 1,5 kΩ.

4. **B** — `ΔR/R = 100×10⁻⁶ × 50 = 0,005` → %0,5. 25 ppm/°C'lik ince film olsaydı %0,125 olurdu.

5. **C** — Oran hatası ≈ `(R1/(R1+R2)) × (ΔR1 + ΔR2) = 0,75 × %2 = %1,5`.

6. **B** — `R_kritik = 75² / 0,1 ≈ 56 kΩ`. 1 MΩ bu değerin üstünde olduğu için gerilim limiti (75 V) önce dolar; güç hesabı 316 V'a izin verir gibi görünse de geçerli değildir.

7. **B** — `v_n = √(4kTRB)`; gürültü √R ile orantılıdır. R 4 katına çıkınca gürültü √4 = 2 katına çıkar.

8. **B** — Akım yolu ile ölçüm yolu ayrılır. Ölçüm izleri şantın iç uçlarından alındığı için pad ve lehim dirençleri ölçüme girmez. mΩ'luk şantta bu dirençler ölçümün önemli bir kısmı olabilir.

9. **B** — Kalın film dirençlerin elektrotlarında gümüş bulunur. Kükürtlü gazlarla tepkimeye girerek iletken olmayan gümüş sülfüre dönüşür. Direnç yavaşça artar, sonunda açık devre olur. Çözüm anti-sülfür dirençtir.

10. **C** — `f = 1 / (2π × 1 MΩ × 0,1 pF) ≈ 1,6 MHz`. Bu frekansın üstünde kapasitif empedans dirençten küçük olur ve direnci atlar.

11. **B** — Reset ve boot sırasında MCU pinleri yüksek empedanslıdır. Gate tanımsız kalırsa kaçak akımlar veya kuplaj MOSFET'i yarı açık hale getirebilir. Pull-down, yükü güvenli durumda (kapalı) tutar.

</details>
