# Quiz · Şebekeli güç kaynakları: kapasitif düşürücü ve flyback

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 12 soru, 9'u hesap.

## Sorular

1. **(Hesap)** 230 V / 50 Hz şebekede 470 nF'lık X2 kapasitörle kurulan bir kapasitif düşürücüde kapasitörden geçen rms akım nedir?
   - A) 5,4 mA
   - B) 34,0 mA
   - C) 48,0 mA
   - D) 21,3 mA

2. **(Hesap)** Köprülü bir kapasitif düşürücüde (C1 = 470 nF, 5,1 V Zener, `V_on = 5,1 + 1,4 = 6,5 V`) hat ±%10 (207…253 V) ve kapasitör ±%20 oynayabiliyor. Yük akımını, yüke verilebilen **en küçük** ortalama DC akıma göre sınırlayacaksın. Bu değer yaklaşık kaçtır?
   - A) 34,0 mA
   - B) 30,0 mA
   - C) 15,1 mA
   - D) 21,5 mA

3. **(Hesap)** Aynı düşürücüde kapasitör akımı 34,0 mA ve seri direnç R1 = 470 Ω. R1'in sürekli ısı kaybı nedir?
   - A) 0,54 W
   - B) 0,42 W
   - C) 0,21 W
   - D) 0,12 W

4. Şebekeden beslenen bir sensör kartında servis için dışarı çıkan bir USB portu var. Besleme için ≈ 30 mA'lik kapasitif düşürücü (köprü + 5,1 V Zener) düşünülüyor. Hangi değerlendirme doğrudur?
   - A) C1 X2 sınıfı olduğu için kart şebekeden izoledir; port serbestçe kullanılabilir
   - B) Köprü doğrultucu kullanıldığı için çıkış şebekeden izole olur
   - C) Uygun değil: devre izolasyonsuzdur; porta dokunan ya da bağlanan kişiden ≈ 34 mA'e kadar akım geçebilir (Class II dokunma akımı sınırının ≈ 136 katı). İzolasyonlu flyback ya da sertifikalı modül gerekir
   - D) Çıkış 5,1 V olduğu için dokunma tehlikesi yoktur (SELV)

5. **(Hesap)** Flyback girişi: 85 VAC, `P_in = 14,12 W`, `C_bulk = 47 µF`, bulk'ın şarj olduğu hat periyodu oranı `D_ch = 0,2`, `f_L = 50 Hz`. `V_DC,min = √(2·V_hat² − P_in·(1 − D_ch)/(C·f_L))` ile bulk geriliminin dibi nedir?
   - A) 120 V
   - B) 92 V
   - C) 85 V
   - D) 98 V

6. **(Hesap)** Flyback'te `V_o = 12 V`, `V_F = 0,5 V`, sarım oranı `n = 6`, `V_DC,min = 90 V`. Sınırdaki görev oranı `D` nedir?
   - A) 0,545
   - B) 0,455
   - C) 0,444
   - D) 0,833

7. **(Hesap)** DCM flyback: `P_in = 14,12 W`, `L_m = 820 µH`, `f_s = 65 kHz`. Primer tepe akımı `I_pk` kaç amperdir?
   - A) 0,728 A
   - B) 0,671 A
   - C) 0,515 A
   - D) 0,690 A

8. RCD clamp'te `V_sn`'yi `V_RO`'ya yaklaştırırsan (örneğin 2,0× yerine 1,5×) ne olur?
   - A) Clamp kaybı azalır; MOSFET gerilimi artar
   - B) Clamp kaybı da MOSFET gerilimi de artar
   - C) Clamp kaybı artar; MOSFET gerilimi azalır
   - D) Clamp kaybı da MOSFET gerilimi de azalır

9. **(Hesap)** `L_lk = 12,3 µH`, `I_pk = 0,728 A`, `f_s = 65 kHz`, `V_RO = 75 V`, `V_sn = 150 V`. Clamp'in harcadığı güç `P_sn` nedir?
   - A) 0,21 W
   - B) 0,42 W
   - C) 0,64 W
   - D) 0,14 W

10. **(Hesap)** TL431 geri besleme bölücüsünde `V_ref = 2,495 V`, üst direnç `R1 = 38,3 kΩ`, alt direnç `R2 = 10 kΩ`. `I_ref` ihmal edilirse çıkış gerilimi `V_o` nedir?
    - A) 9,56 V
    - B) 3,15 V
    - C) 12,46 V
    - D) 12,05 V

11. Flyback'te geri besleme yolunda (opto ya da TL431) lehim hatasıyla **açık devre** oluşursa ne olur ve savunma nedir?
    - A) Kontrolcü darbeyi keser, çıkış sıfıra düşer; ek bir koruma gerekmez
    - B) Çıkış gerilimi sabit kalır, çünkü tepe akım modu çıkışı kendisi regüle eder
    - C) FB girişi "çıkış düşük" bilgisi görür; kontrolcü maksimum güce çıkar ve çıkış yükselir. Aux sargı ya da ikincilden çalışan bir OVP şarttır
    - D) Yalnız çıkış kapasitörü ısınır; gerilim değişmez

12. **(Hesap)** Bulk gerilimi 325 V iken dirençli start-up (2 MΩ) **sürekli** ne kadar güç harcar?
    - A) 52,8 mW
    - B) 26,5 mW
    - C) 79,3 mW
    - D) 105,6 mW

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>


1. **B** — `X_C = 1/(2π·50·470 nF) = 6,77 kΩ`; `I = 230 V / 6,77 kΩ = 34,0 mA`. A, 2π'yi unutur (`f·C·V = 5,4 mA`). C, rms yerine tepe gerilimi kullanır (`325 V / 6,77 kΩ = 48,0 mA`). D, aynı kapasitörün 120 V / 60 Hz'deki akımıdır (21,3 mA; AN954'ün R1 hesabındaki akım): 230 V / 50 Hz'de akım 1,6× fazladır.

2. **D** — Yük akımı **en kötü** koşula göre sınırlanır: 207 V ve C −%20 (376 nF). `I_ort = 4·f·C·(V_tepe − V_on) = 4 × 50 × 376 nF × (292,7 V − 6,5 V) = 21,5 mA`; %10 marjla yük ≈ 19 mA'in altında kalmalı. A, nominal kapasitör rms akımıdır (34,0 mA): rms değeri DC akım değildir. B, nominal ortalama akımdır (30,0 mA): düşük hatta ya da yaşlanmış kapasitörde çıkış çöker. C, yarım dalga devrenin nominal değeridir (15,1 mA): köprü ortalama akımı yarım dalganın 2 katı yapar.

3. **A** — `P = I_rms²·R1 = (34,0 mA)² × 470 Ω = 0,54 W` (en kötü hatta 0,94 W): ½ W'lık direnç yetmez. B, ısıyı ortalama DC akımla (30,0 mA) hesaplar; ısı **rms** akıma göre hesaplanır. C, 120 V / 60 Hz'deki akımla (21,3 mA) hesaplanmış değerdir: AN954'ün ½ W'lık R1'i o koşul içindir. D, R1 = 100 Ω'un değeridir (0,12 W); ama onun açılış tepe akımı 3,19 A'dir.

4. **C** — Dropper izolasyonsuzdur: kartın tamamı kapasitörle şebekeye bağlıdır. Dokunulabilir iletken (port, bağlayıcı, düğme, anten) varsa ≈ 34 mA'e kadar akım kişiden geçebilir; Class II dokunma akımı sınırı 0,25 mA'dir (≈ 136 kat). A yanlıştır: X2 sertifikası kapasitörün hat–nötr arasındaki arıza davranışı içindir, izolasyon bariyeri sağlamaz. B yanlıştır: köprü doğrultucu şebekeden ayırmaz. D yanlıştır: 5,1 V yalnız yük gerilimidir; akım şebekeden kapasitörle gelir, SELV için güvenli bir yalıtım gerekir.

5. **D** — `2·85² = 14450`; `P_in·(1 − D_ch)/(C·f_L) = 14,12 × 0,8 / (47 µF × 50 Hz) = 4807`; `V_DC,min = √(14450 − 4807) = 98,2 V`. A, tepe gerilimidir (120 V): kapasitör hiç boşalmıyor sanılmıştır. B, `(1 − D_ch)` çarpanını unutur (91,9 V): şarj süresinde kapasitöre giren enerjiyi saymaz. C, hat rms değeridir (85 V): bulk'ın tepe şarjını yok sayar. Tasarımda C −%20 ve parazitik düşümler için 90 V kullanıldı.

6. **B** — `V_RO = n·(V_o + V_F) = 6 × 12,5 = 75 V`; `D = V_RO/(V_DC,min + V_RO) = 75/165 = 0,455`. A, oranı ters alır (`V_DC,min/(V_DC,min + V_RO) = 0,545`). C, `V_F`'yi unutur (`V_RO = 72 V`, D = 0,444): diyot düşümü yansıyan gerilime dahildir. D, `V_RO/V_DC,min`'dir (0,833): payda iki gerilimin toplamıdır. D_maks 0,45–0,5 sınırı için 0,455 uygundur.

7. **A** — DCM'de `P_in = ½·L_m·I_pk²·f_s`, yani `I_pk = √(2·14,12 / (820 µH × 65 kHz)) = 0,728 A`. B, giriş gücü yerine çıkış gücünü (12 W) kullanır (0,671 A): kayıplar da trafodan geçer. C, `½` çarpanını unutur, yani `√(P/(L·f))` hesaplar (0,515 A). D, DCM sınırındaki `L_m = 912 µH` ile hesaplanır (0,690 A); seçilen `L_m` 820 µH'tır.

8. **C** — `P_sn = ½·L_lk·I_pk²·f_s · V_sn/(V_sn − V_RO)`: çarpan 2,0×'te 2, 1,5×'te 3 olur; kayıp 0,42 W'tan 0,64 W'a çıkar (clamp diyodu daha uzun iletir ve ana enerjiden de çalar). `V_DS = V_DC,maks + V_sn` olduğundan MOSFET gerilimi 524,8 V'tan 487,3 V'a iner (%80,7 → %75,0). A ve B kaybın yönünü ters alır; D ödünleşimi görmez: ikisi aynı anda iyileşmez.

9. **B** — `½·L_lk·I_pk²·f_s = 0,212 W`; çarpan `V_sn/(V_sn − V_RO) = 150/75 = 2` → `P_sn = 0,42 W`. A, çarpanı unutur: yalnız kaçak enerji sayılır, clamp diyodunun uzun iletimi hesaba girmez. C, `V_sn = 112,5 V` (1,5×) değeridir (çarpan 3). D, çarpanı `V_sn/(V_sn + V_RO) = 0,67` alır: payda `V_sn − V_RO`'dur.

10. **D** — `V_o = V_ref·(1 + R1/R2) = 2,495 × (1 + 3,83) = 12,05 V`. A, `1 +` terimini unutur (`V_ref·R1/R2 = 9,56 V`). B, oranı ters alır (`V_ref·(1 + R2/R1) = 3,15 V`). C, en kötü üst değerdir (B sınıfı `V_ref` = 2,507 V, R1 +%1, R2 −%1, `I_ref` = 4 µA ile 12,46 V, +%3,8); nominal değildir.

11. **C** — Opto ya da TL431 yolu açıkken FB girişi "çıkış düşük" bilgisi görür; kontrolcü maksimum güce çıkar ve çıkış kontrolsüz yükselir. Bu yüzden geri besleme yolundan bağımsız bir **OVP** (aux sargı ya da ikincil) şarttır. A, bu arızanın tersidir: opto **kısa devre** olursa FB aşağı çekilir, darbe durur ve hiccup yeniden dener. B yanlıştır: tepe akım modu yalnız akımı sınırlar (OCP), gerilimi regüle etmez. D yanlıştır: aşırı gerilim yüklere ve çıkış kapasitörüne zarar verir; yalnız ısınma değildir.

12. **A** — `V_DC²/R = 325² / 2 MΩ = 52,8 mW`: start-up direnci bulk'tan beslenir ve **sürekli** akım çeker. Dış güç kaynağı sınırı ≤ 0,100 W olduğundan tek başına %53'ünü yer. B, hat rms gerilimini (230 V) kullanır (26,5 mW: bu, 2 MΩ'luk X2 deşarj direncinin kaybıdır). C, X2 deşarjı ile start-up'ın toplamıdır (79,3 mW); sorulan yalnız start-up. D, 1 MΩ ile hesaplanır (105,6 mW). Çözüm: HV pin'li kontrolcü (start-up sonrası akımı keser).

</details>
