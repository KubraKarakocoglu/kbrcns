# Quiz · Triyak ve faz kontrolü (dimmer)

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 12 soru, 7'si hesap.

## Sorular

1. **(Hesap)** 230 V / 50 Hz şebekede dirençli yük, tetik açısı α = 60° (sıfır geçişten tetiğe). Tetik gecikmesi ve yüke giden güç (tam güce oranla) nedir?
   - A) 3,33 ms; %80,4
   - B) 6,67 ms; %19,6
   - C) 3,33 ms; %66,7
   - D) 6,67 ms; %80,4

2. Optotriyakla sürülen bir triyakın kapısı hangi kadranlarda çalışır?
   - A) QII ve QIV: kapı, MT2'nin tersi polaritede sürülür
   - B) Yalnız QI: opto yalnızca pozitif yarım periyotta akım verebilir
   - C) QI ve QIII: kapı MT2 ile aynı polaritede sürülür; QIV en az hassas kadrandır (I_GT ≤ 25 mA, dI/dt 10 A/µs)
   - D) Dört kadranın hepsi aynı hassasiyettedir; kadran seçimi önemsizdir

3. **(Hesap)** Optotriyak çıkışı (I_TSM = 1 A) ile triyak kapısı arasına bir R_g konacak. En kötü hat 264 V (tepe 373 V). R_g için en küçük uygun E12 değeri hangisidir?
   - A) 330 Ω
   - B) 390 Ω
   - C) 180 Ω
   - D) 39 Ω

4. Faz kontrollü bir dimmer'da MOC3043 gibi **sıfır geçişli** (zero-cross) bir optotriyak kullanılırsa ne olur?
   - A) Fark olmaz; sıfır geçişli tip yalnızca EMI'yi azaltır, dimleme yine yapılır
   - B) Dimleme çalışır ama kapı akımı yetmediği için I_L'ye ulaşılamaz
   - C) Optotriyak her yarım periyotta yalnızca bir kez tetiklenebildiği için dimleme aralığı yarıya iner
   - D) Opto yalnızca hat gerilimi sıfıra çok yakınken açar; tetik açısı seçilemez, yük ya tam güçte ya kapalı olur

5. **(Hesap)** İki telli bir dimmer kapalıyken 47 nF'lık snubber üzerinden 230 V / 50 Hz'de kaçak akım akar. Bu akım 5 W'lık bir LED lambadan geçiyor (direnç modeli: 10,6 kΩ). Kaçak akım ve lamba uçlarındaki gerilim yaklaşık kaçtır?
   - A) 0,34 mA; 3,6 V
   - B) 7,2 mA; 76 V
   - C) 3,4 mA; 36 V
   - D) 2,4 mA; 25 V

6. **(Hesap)** Mandallamayı garanti etmek için 230 V'ta LED lambaya paralel, sürekli 30 mA çeken bir bleeder direnci konuyor. Direnç değeri ve sürekli ısı kaybı nedir?
   - A) 7,7 kΩ; 6,9 W
   - B) 7,7 kΩ; 0,69 W
   - C) 7,7 kΩ; 9,8 W
   - D) 10,8 kΩ; 4,9 W

7. **(Hesap)** 400 W'lık dirençli yükü (230 V) süren triyakın kaybı ≈ 1,65 W'tır (V_TO = 1,0 V, R_d = 0,027 Ω). Serbest havada R_th(j-a) = 60 K/W, ortam 50 °C, mutlak sınır T_j = 125 °C; tasarım hedefi T_j ≤ 110 °C. Doğru değerlendirme hangisidir?
   - A) Soğutucu gerekmez; akım (1,74 A), I_T(RMS) = 12 A değerinin çok altındadır
   - B) Soğutucu gerekmez; 1,65 W kayıp ihmal edilebilir, T_j ≈ 52 °C
   - C) Soğutucu yalnızca ortam 70 °C'nin üstüne çıkarsa gerekir
   - D) Soğutucu gerekir: serbest havada T_j ≈ 149 °C; toplam R_th ≤ 36 K/W (soğutucu + arayüz ≤ 34 K/W) olmalı

8. LED lamba ve elektronik düşük gerilim trafosu (ELV) yükleri için neden **geri kenar** (trailing edge, MOSFET'li) dimmer tercih edilir?
   - A) Geri kenar dimmer triyaklıdan ucuzdur ve her zaman iki telli yapılır
   - B) Gerilim sıfır geçişte yumuşakça uygulanır, geç kesilir: kapasitif girişe ani 325 V adımı binmez; tepe akım, titreme ve duyulur gürültü azalır
   - C) Geri kenar, manyetik trafo (MLV) için de aynı derecede uygundur; yük tipi önemsizdir
   - D) Geri kenarda da triyak kullanılır, ama I_L sorunu ortadan kalkar

9. **(Hesap)** ZC darbesi 1,3 ms geniştir (50 Hz). %50 güç (α = 90°) için, darbenin **yükselen kenarından** tetiğe kadar beklenecek süre kaçtır?
   - A) 5,00 ms
   - B) 4,35 ms
   - C) 5,65 ms
   - D) 6,30 ms

10. Güç → tetik gecikmesi eşlemesinde neden güçten açıya **ters tablo** yerine açıya göre **ileri tablo** (güç saklanır, tersi aralıkta çözülür) tercih edilir?
    - A) P(α) uçlarda yataylaşan düzgün bir eğridir: doğrusal ara değer hatası küçük kalır (N = 32'de ≈ %0,08). Ters fonksiyon uçlarda küp kök gibi dikleşir (%1,18): aynı bellekle ≈ 15× fark
    - B) İleri tablo daha az bellek kullanır; doğruluk aynıdır
    - C) Ters tabloda bölme gerekir, ileri tabloda gerekmez; asıl fark hızdır
    - D) Ters tablo yalnızca 60 Hz'de çalışır

11. Çalışan bir dimmer'da ZC devresindeki direnç açık devre olur ve ZC darbeleri kaybolur. Doğru fail-safe davranış hangisidir?
    - A) Son bilinen gecikmeyle tetiklemeye devam et; ışık sönmesin
    - B) Zaman aşımından sonra ölçümü geçersiz say ve tetik verme; ZC dönünce dört iyi ölçüm bekleyip yeniden başla
    - C) Tam güce geç; yük kontrolsüz kalmasın
    - D) Kapı pinini yüksek tut; triyak sürekli iletimde kalsın

12. **(Hesap)** Dimmer girişinde 1 mH seri indüktör, triyakta 100 nF snubber kapasitörü var. Bu L–C rezonansının karakteristik empedansı Z₀ ve frekansı f₀ nedir?
    - A) 10 kΩ; 15,9 kHz
    - B) 100 Ω; 100 kHz
    - C) 3,16 Ω; 503 Hz
    - D) 100 Ω; 15,9 kHz

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **A** — `t_α = 60/180 × 10 ms = 3,33 ms`; `P/P_max = 1 − 60°/180° + sin(120°)/(2π) = 0,667 + 0,138 = 0,804`. B, α'yı iletim açısı sanmaktır (α = 120° olurdu: 6,67 ms ve %19,6). C, gücü açıyla doğrusal sanar: güç eğrisi doğrusal değildir (ortada hızlı, uçlarda yavaş değişir). D, 10 ms yerine tam periyodu (20 ms) bölmektir.

2. **C** — Optotriyak kapı akımını **MT2 ile aynı polaritede** verir (MT2 + iken kapı +, MT2 − iken kapı −): bu QI ve QIII'tür. QIV (MT2 −, kapı +) en az hassas kadrandır: BT138Y-600E'de I_GT ≤ 25 mA (diğerlerinde 10 mA) ve dI/dt sınırı 10 A/µs (diğerlerinde 50 A/µs). QII ve QIV kapının MT2'nin **tersi** polaritede olduğu kadranlardır (A). Opto negatif yarım periyotta da akım verir (B). Kadranlar farklı hassasiyettedir (D).

3. **B** — `R_g ≥ V_tepe / I_TSM = 373 V / 1 A = 373 Ω`; E12'de bir üst değer 390 Ω'dur (tepe akım 373/390 = 0,96 A). 330 Ω nominal 230 V'a (tepe 325 V) göre seçilmiş değerdir: 264 V'ta 1,13 A geçirir ve I_TSM'i aşar (A). 180 Ω, Fairchild AN-3006'nın 115 V örneğidir; 264 V'ta 2,07 A geçirir (C). 39 Ω ondalık kaymasıdır: 9,6 A (D).

4. **D** — Sıfır geçişli tip, hat gerilimi küçük bir eşiğin üstündeyken açmayı engeller. MCU 90°'de tetik istese bile opto o anda açmaz; ilk sıfır geçişte açar: faz kontrolü olmaz, yalnız aç-kapa kalır. Faz kontrolü için **rastgele faz** tip (MOC302x, MOC305x) gerekir. A ve B sıfır geçişli tipin bu kısıtını görmez; C yanlıştır: opto her yarım periyotta tetiklenir, ama yalnız sıfır geçişte.

5. **C** — `I = 2π·f·C·V = 2π × 50 × 47 nF × 230 V = 3,40 mA`; `V = 3,40 mA × 10,6 kΩ ≈ 36 V`. Bu, LED sürücüsünün uyanıp kapalı dimmerde göz kırpmasına yeter (hayalet parlama). Lambayı doğrusal dirençle modellemek kabaca bir tahmindir. A ondalık kaymasıdır (0,34 mA). B 100 nF'lık klasik snubber'ın değeridir (7,2 mA; 76 V). D, rms değeri √2'ye bölmektir (2,4 mA).

6. **A** — `R = 230 V / 30 mA = 7,67 kΩ`; `P = V·I = 230 × 0,030 = 6,9 W`. Bu yüzden **sürekli** bleeder olmaz: yalnız tetikten sonra ≈ 0,5 ms açılan bir aktif yük kullanılır (ortalama ≈ 0,3 W). B ondalık kaymasıdır. C, tepe gerilimi rms akımla çarpar (325 × 0,030 = 9,8 W). D direnci tepe gerilimden hesaplar (325 V / 30 mA = 10,8 kΩ): bu dirençten 230 V rms'te yalnız 21 mA akar, hedef akım tutmaz.

7. **D** — `T_j = T_a + P·R_th = 50 + 1,65 × 60 = 149 °C` > 125 °C: soğutucu şart. Hedef T_j ≤ 110 °C ise `R_th,toplam ≤ (110 − 50)/1,65 = 36 K/W`; R_th(j-mb) = 2,3 K/W düşülünce soğutucu + arayüz ≤ 34 K/W. A klasik tuzaktır: asıl sınır **akım değil, ısıdır** (I_T(RMS) = 12 A ancak T_mb ≤ 85 °C ile geçerlidir). B, `T_j = T_a + P` yapar ve R_th ile çarpmayı unutur (51,7 °C). C yanlıştır: ortam 50 °C iken sınır zaten aşılıyor.

8. **B** — Geri kenar dimmer MOSFET'lidir: sıfır geçişte açar, geç keser. Kapasitif/elektronik giriş yumuşak yükselen gerilimi görür; ani 325 V adımı olmadığı için tepe akım, titreme ve duyulur gürültü azalır (Leviton: ELV için geri kenar gerekir, LED için daha iyi sonuç verebilir). A yanlıştır: geri kenar genellikle daha pahalıdır ve çoğu zaman **nötr** ister. C yanlıştır: MLV'de geri kenar "geri tepme" gerilimi doğurur ve dimmer veya yük zarar görebilir (MLV için ileri kenar). D yanlıştır: geri kenarda triyak değil MOSFET kullanılır.

9. **C** — Yükselen kenar gerçek sıfır geçişten `t_w = darbe/2 = 0,65 ms` önce gelir: `gecikme = t_w + t_α = 0,65 + 5,00 = 5,65 ms`. A, t_w'yu unutur: tetik gerçekte 4,35 ms'de (78,3°) olur ve güç %50 yerine **%62,8**'e çıkar. B, t_w'yu çıkarır: gerçek gecikme 3,70 ms (66,6°), güç %74,6. D darbenin tamamını (1,3 ms) ekler: gerçek gecikme 5,65 ms (101,7°), güç %37,2.

10. **A** — `P(α)` uçlarda yataydır ve düzgündür; açıyı eşit aralıklara bölüp **gücü** saklarsan doğrusal ara değer hatası `π/(4N²)` olur (N = 32 için %0,077). Tersi `α(P)` uçlarda küp kök gibi dikleşir (α = π − x için `P ≈ 2x³/(3π)`); eşit **güç** aralıklarında doğrusal ara değer N = 32'de %1,18 hata verir. Aynı bellekle ≈ 15× fark. B yanlıştır: bellek aynıdır (33 giriş, 66 bayt) ama doğruluk aynı değildir. C yanlıştır: ileri tabloda da bir bölme vardır (kesir hesabı). D yanlıştır: tablo frekanstan bağımsızdır, zaman ölçülen yarım periyoda ölçeklenir.

11. **B** — ZC yoksa **faz referansı yoktur**: tetik fazı bilinmez. Yanlış fazda tetik kontrolsüz güce, DC bileşene ve manyetik trafoda doymaya yol açar. Doğrusu: zaman aşımı → `dim_zc_kayip` → `DIM_KAPALI`; ZC dönünce dört iyi ölçümle yeniden kilitlen. A referanssız tetikler (açı kayar). C ve D, kontrolsüz veya sürekli iletimi "güvenli" sanar: güvenli durum **kapalıdır**. Kapı seviyesi de yazılımla yüksekte tutulmaz; donanım zamanlayıcıyla sabit genişlikte darbe verilir.

12. **D** — `Z₀ = √(L/C) = √(1 mH / 100 nF) = √10⁴ = 100 Ω`; `f₀ = 1/(2π√(LC)) = 15,9 kHz`. Sönümleme faktörü `F = R/(2·Z₀)`: R = 100 Ω → F = 0,5; R = 200 Ω → F = 1 (kritik sönüm). A, Z₀'ı `L/C` olarak hesaplar (10 kΩ). B, 2π'yi unutur: `1/√(LC) = 10⁵ rad/s` değeri Hz sanılmıştır. C, 100 nF yerine 100 µF alır.

</details>
