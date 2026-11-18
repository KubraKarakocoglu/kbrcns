# Quiz · MIT 6.002 Ders 5: Dijital kapının içi

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 12 soru, 6'sı hesap.

## Sorular

1. Slayt 5'teki su musluğu benzetmesinde A ve B muslukları art arda (seri) bağlıysa, kaba su gelmesi hangi mantık işlevine karşılık gelir?
   - A) OR: musluklardan en az biri açıksa su gelir
   - B) NOT: musluk açıldıkça su azalır
   - C) AND: ancak A ve B ikisi de açıksa su gelir
   - D) XOR: musluklardan yalnızca biri açıksa su gelir

2. Bu notta ve slaytların çoğunda kullanılan anahtar modeline göre C = 1 iken anahtar nasıl davranır? (Slayt 8'in metni bu konuda ters basılmıştır.)
   - A) Kapalıdır: in ve out arası kısa devredir
   - B) Açıktır: in ve out arası açık devredir
   - C) Yalnızca in'den out'a doğru iletir (diyot gibi)
   - D) Direnç gibi davranır; değeri C'nin gerilimine bağlıdır

3. Çıkışla GND arasına bir anahtar, çıkışla V_S arasına bir R_L konmuş (slayt 9). C = 0 iken V_OUT nedir?
   - A) 0 V; çıkış GND'ye çekilmiştir
   - B) V_S/2; R_L ve anahtar gerilim bölücü oluşturur
   - C) Tanımsız; çıkış havada kalır
   - D) V_S; akım akmaz, R_L'de gerilim düşmez (çıkış "1")

4. İki anahtar çıkışla GND arasına **seri** bağlanmış, çıkış R_L ile V_S'ye çekilmiş. c1 = 1, c2 = 0 iken çıkış nedir?
   - A) 0; c1 iletiyorsa çıkış GND'ye iner
   - B) 1; yol tamamlanmadığı için R_L çıkışı V_S'ye çeker
   - C) V_S/2; iki anahtar gerilimi paylaşır
   - D) Tanımsız; iki anahtar birbirine zıt

5. **(Hesap)** Slayt 11'deki bileşik kapıda (`D = ¬(A·B + C)`) A = 1, B = 0, C = 0 iken D kaçtır?
   - A) 0, çünkü A = 1
   - B) 0, çünkü A·B + C = 1
   - C) Tanımsız
   - D) 1, çünkü GND'ye yol yok (A·B = 0 ve C = 0)

6. **(Hesap)** R_ON = 2 kΩ, V_S = 3,3 V ve V_OL(max) = 0,4 V olan yük dirençli bir eviricide R_L en az kaç kΩ olmalıdır?
   - A) 2,9 kΩ
   - B) 7,25 kΩ
   - C) 14,5 kΩ
   - D) 16,5 kΩ

7. **(Hesap)** R_ON = 5 kΩ, R_L = 45 kΩ, V_S = 5 V. Düşük durumdaki tek kapı ne kadar güç harcar ve 10 000 kapı aynı anda düşükse toplam güç ne olur?
   - A) 0,5 mW; 5 W
   - B) 0,5 mW; 0,5 W
   - C) 0,1 mW; 1 W
   - D) 5 mW; 50 W

8. **(Hesap)** V_S = 5 V ve V_T = 1 V olan S modelli eviriciyle hangi eşik seti statik disipline uyar? (Sıra: V_OL / V_OH / V_IL / V_IH)
   - A) 0,5 / 4,5 / 1,5 / 3,5 V
   - B) 0,2 / 4,8 / 0,5 / 4,5 V
   - C) 0,3 / 5,3 / 0,8 / 4,0 V
   - D) −0,2 / 4,5 / 0,8 / 4,0 V

9. **(Hesap)** SR modelinde R_ON = 5 kΩ olan, iletim durumundaki bir MOSFET'in D–S gerilimi 0,25 V ise i_DS kaçtır?
   - A) 1,25 mA
   - B) 0 A
   - C) 50 µA
   - D) 5 mA

10. Datasheet'te V_GS(th) = 1 V olan bir MOSFET'i 1,2 V'luk gate gerilimiyle sürmek neden kötü bir fikirdir?
    - A) Gate gerilimi V_GS(th)'yi aştığında gate oksidi hasar görür; bu yüzden hep altında kalınmalıdır
    - B) V_GS(th)'nin üstündeki gerilimlerde D–S yön değiştirir ve MOSFET ters çalışır
    - C) V_GS(th), gate akımının akmaya başladığı gerilimdir; MOSFET ancak bu akımla iletir
    - D) V_GS(th) iletimin yalnızca başladığı gerilimdir; R_DS(on) o gerilimde büyüktür, MOSFET ısınır ve gerilim düşürür

11. Açık-drenaj bir çıkış neden harici pull-up ister?
    - A) İçinde yalnızca çıkışı aşağı çeken bir transistör vardır; "1" seviyesini pull-up üretir
    - B) Pull-up olmazsa MOSFET'in gate'i boşta kalır ve çıkış aşırı akımdan hasar görür
    - C) Pull-up, çıkışın akım verme kapasitesini artırmak için gerekir
    - D) Açık-drenaj çıkış yalnızca 0 V ile 1 V arasında çalışır; pull-up bu aralığı genişletir

12. **(Hesap)** Bir I²C hattında V_DD = 3,3 V, V_OL(max) = 0,4 V, I_OL = 3 mA. Pull-up direncinin alt sınırı kaç Ω'dur?
    - A) 133 Ω
    - B) 967 Ω
    - C) 1,1 kΩ
    - D) 7,25 kΩ

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **C** — Seri musluklarda su yalnızca **iki musluk da açıkken** gelir: AND. Paralel olsaydı biri yeterdi (OR, A şıkkı). Slayt 7'deki elektrik karşılığı: seri anahtarlar, ikisi de iletirse lamba yanar.

2. **A** — Anahtar modelinde **C = 1 → kapalı (kısa devre)**, C = 0 → açık devre. Slayt 8'in metni tersini yazar, ama şekil ve 9. slayttan itibaren tüm devreler (evirici, NAND, MOSFET) C = 1'i kapalı kabul eder. Anahtar yön ayırmaz (C şıkkı diyot tarifidir) ve ideal modelde direnç gibi davranmaz (D); direnç SR modelinde gelir.

3. **D** — C = 0 → anahtar açık → R_L'den akım akmaz → `V_R_L = 0` ve `V_OUT = V_S` ("1"). C = 1 olsaydı çıkış 0 V olurdu; devre bir **eviricidir**. Çıkış havada kalmaz (C), çünkü R_L onu V_S'ye bağlar; gerilim bölücü ancak anahtar iletirken ve R_ON varken oluşur (B).

4. **B** — Seri kolda GND'ye yol için **iki anahtar da** iletmeli; c2 = 0 olduğu için yol yok ve R_L çıkışı V_S'ye çeker: "1". Bu bir **NAND**'dır (1 NAND 0 = 1). Kural: çıkış, GND'ye iletken bir yol varsa 0'dır.

5. **D** — `A·B + C = 1·0 + 0 = 0` → GND'ye iletken yol yok → R_L çıkışı yukarı çeker → `D = ¬0 = 1`. A = 1 tek başına yol oluşturmaz, çünkü A, B ile **seridir** (A şıkkı); `A·B + C = 1` değildir (B şıkkı).

6. **C** — `R_L ≥ R_ON·(V_S − V_OL)/V_OL = 2 kΩ × (3,3 − 0,4) / 0,4 = 2 kΩ × 7,25 =` **14,5 kΩ**. 7,25 oranın kendisidir (R_ON ile çarpılmamış, B). 16,5 kΩ, `V_S/V_OL` kullanıp V_OL'yi çıkarmayı unutmaktır (D); 2,9 kΩ ise yalnızca `V_S − V_OL` sayısıdır (A).

7. **A** — `I = V_S/(R_ON + R_L) = 5 V / 50 kΩ = 0,1 mA`; `P = V_S·I = 5 V × 0,1 mA = 0,5 mW`; `10 000 × 0,5 mW = 5 W`. 0,1 mW şıkkı akımın (mA) güç sanılmasıdır (C).

8. **B** — Koşullar: `V_IL < V_T ≤ V_IH`, `V_OH ≤ V_S`, `V_OL ≥ 0`. B (0,2 / 4,8 / 0,5 / 4,5) hepsini sağlar (slayt 17, "yes"). A: `V_IL = 1,5 V > V_T = 1 V` (slayt 17, "no"). C: `V_OH = 5,3 V > V_S = 5 V`, devre V_S'nin üstünü üretemez. D: `V_OL = −0,2 V < 0`, S modelli evirici negatif gerilim üretemez.

9. **C** — `i_DS = v_DS / R_ON = 0,25 V / 5 kΩ =` **50 µA**. 1,25 mA, çarpma hatasıdır (A); 5 mA, R_ON'u 50 Ω sanmaktır (D); 0 A, MOSFET'in kapalı olduğu durumdur (B), ama soruda iletim durumunu istiyor.

10. **D** — V_GS(th) yalnızca iletimin **başladığı** gerilimdir; datasheet R_DS(on)'u çok daha yüksek bir V_GS'te (2,5–10 V) verir. 1,2 V'ta direnç büyüktür, MOSFET ısınır ve gerilim düşürür. Gate oksidinin zarar görmesi, gate'in V_GS(max) sınırını **aşmasıyla** ilgilidir (A yanlış); D–S yön değiştirmez (B); gate akımı DC'de yaklaşık sıfırdır (C yanlış).

11. **A** — Açık-drenaj çıkışta yalnızca çıkışı **aşağı** çeken transistör vardır; "1" seviyesini dışarıdaki pull-up (bölüm 4–9'daki R_L) üretir. Pull-up akım verme kapasitesi için değil, **seviye üretmek** içindir (C); gate boşta kalması ayrı bir konudur (B); çıkış aralığı V_DD'ye kadardır (D).

12. **B** — `R_min = (V_DD − V_OL) / I_OL = (3,3 − 0,4) V / 3 mA =` **967 Ω**. 133 Ω, R_ON eşdeğeridir (`V_OL/I_OL`, A); 1,1 kΩ, V_OL'yi çıkarmayı unutmaktır (`V_DD/I_OL`, C); 7,25 oranın kendisidir (D). Bu, bölüm 9'daki `R_L ≥ R_ON·(V_S − V_OL)/V_OL` formülünün aynısıdır.

</details>
