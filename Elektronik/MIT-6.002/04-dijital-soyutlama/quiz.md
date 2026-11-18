# Quiz · MIT 6.002 Ders 4: Dijital soyutlama

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 12 soru, 5'i hesap.

## Sorular

1. Dijital sinyalin analog sinyale göre gürültüye daha dayanıklı olmasının temel nedeni nedir?
   - A) Dijital hatlarda akım çok küçük olduğu için gürültü hiç oluşmaz
   - B) Bilgi iki geniş gerilim aralığında taşınır; gürültü, değeri karar bölgesinin dışına itmedikçe bilgiyi değiştirmez
   - C) Dijital devreler daha yüksek gerilimle çalıştığı için gürültünün oranı küçülür
   - D) Dijital kapılar giriş gürültüsünü içlerindeki kapasitörle süzüp yok eder

2. **(Hesap)** Gönderen "1" için 5 V, "0" için 0 V yolluyor. Alıcı 3 V ve üstünü "1", 2 V ve altını "0" sayıyor (arası yasak bölge). "1" ve "0" için gürültü marjları sırasıyla kaçtır?
   - A) 2,5 V ve 2,5 V
   - B) 3 V ve 2 V
   - C) 2 V ve 2 V
   - D) 1 V ve 1 V

3. Gönderen ve alıcı eşikleri küçükten büyüğe sıralanınca doğru sıra hangisidir?
   - A) V_IL < V_OL < V_IH < V_OH
   - B) V_OL < V_IL < V_IH < V_OH
   - C) V_OL < V_IH < V_IL < V_OH
   - D) V_IL < V_OL < V_OH < V_IH

4. **(Hesap)** Bir çıkışın V_OL(max) değeri 0,5 V, bağlandığı girişin V_IL(max) değeri 0,8 V. "0" için gürültü marjı kaçtır?
   - A) 1,3 V
   - B) 0,8 V
   - C) 0,5 V
   - D) 0,3 V

5. Slayt 12'de "1" için gürültü marjı `V_IH − V_OH` olarak yazılmıştır. Doğru ifade hangisidir?
   - A) V_OH − V_IH
   - B) V_IL − V_OL
   - C) V_OH − V_IL
   - D) V_IH − V_IL

6. Statik disiplin kuralı hangisidir?
   - A) Kapının çıkış gerilimi, giriş geriliminin kopyası olmalıdır
   - B) Kapı yalnızca V_CC ve GND gerilimlerini girişte kabul etmelidir
   - C) Girişler geçerli eşikleri sağlıyorsa çıkışlar da geçerli eşikleri sağlamak zorundadır
   - D) Çıkıştaki gürültü, girişteki gürültüden küçük olmalıdır ama sıfır olmak zorunda değildir

7. Yasak bölge (V_IL ile V_IH arası) için hangisi doğrudur?
   - A) Sinyal bu aralıkta hiçbir zaman bulunmamalıdır; bulunursa devre hasar görür
   - B) Alıcı bu aralıktaki her gerilimi "0" olarak okur
   - C) Bu aralıktaki gerilimler "1" sayılır, ancak marjı küçüktür
   - D) Her 0 ↔ 1 geçişi buradan geçer; sorun sinyalin burada beklemesidir, çünkü alıcının kararı garanti edilmez

8. **(Hesap)** 3,3 V LVTTL bir çıkış (V_OH(min) = 2,4 V), V_CC = 4,5 V ile beslenen bir 74HC girişini (V_IH = 0,7·V_CC) sürüyor. "1" için marj ve sonuç nedir?
   - A) −0,75 V → garantili değil; HCT veya seviye çevirici gerekir
   - B) +0,75 V → garantili; doğrudan bağlanabilir
   - C) +0,4 V → garantili; yalnızca marj küçüktür
   - D) 0 V → tam sınırda; yine de çalışır

9. **(Hesap)** `çıkış = A + ¬(B·C)` devresinde çıkış hangi giriş kombinasyonunda 0 olur?
   - A) A = 1, B = 1, C = 1
   - B) A = 0, B = 1, C = 1
   - C) A = 0, B = 0, C = 1
   - D) A = 1, B = 0, C = 0

10. Slayt 20'deki Boole kimliklerinden biri yanlış basılmıştır. Doğru kimlik hangisidir?
    - A) X·0 = X
    - B) X + 1 = X
    - C) X·0 = 0
    - D) X + 0 = 1

11. Bir CMOS kapısının kullanılmayan girişi boşta bırakılırsa ne olabilir?
    - A) Gerilimi yasak bölgede dolaşır; çıkış rastgele döner ve kapı fazladan besleme akımı çekebilir
    - B) Giriş otomatik olarak "0" kabul edilir; bu nedenle boşta bırakmak güvenlidir
    - C) Giriş otomatik olarak "1" kabul edilir; bu nedenle boşta bırakmak güvenlidir
    - D) Kapı bu girişi yok sayar ve çıkış diğer girişlere göre sorunsuz çalışır

12. **(Hesap)** 74HC (V_CC = 4,5 V, V_IH = 3,15 V) bir çıkış hafif yükte (20 µA) V_OH ≥ 4,4 V verirken 4 mA yük çektiğinde V_OH ≥ 3,98 V veriyor. 4 mA'de "1" marjı kaçtır ve hafif yüke göre ne olmuştur?
    - A) 1,25 V; yük akımı marjı etkilemez
    - B) 0,42 V; marj yarıya inmiştir
    - C) 0,83 V; hafif yüke göre artmıştır
    - D) 0,83 V; hafif yükteki 1,25 V'tan azalmıştır

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **B** — Dijitalde bilgi tek bir değer değil, iki geniş **aralıktır**. Gürültü, gerilimi alıcının karar bölgesinin dışına itecek kadar büyük olmadıkça bit değişmez; analogda ise her gerilim geçerli bir değerdir ve gürültü bilgiyi doğrudan kaydırır. Gürültü dijital hatta da vardır (A yanlış); yüksek gerilim değil **marj** belirleyicidir (C); kapılar gürültüyü süzmez, geçerli girişten **taze çıkış üretir** (D).

2. **C** — `NM_H = V_OH − V_IH = 5 − 3 = 2 V`, `NM_L = V_IL − V_OL = 2 − 0 = 2 V`. 2,5 V, tek eşikli ideal durumun marjıdır (slayt 8); 1 V ise yasak bölgenin genişliğidir (`3 − 2`).

3. **B** — Gönderen alıcıdan sıkı olmalıdır: gönderenin "0" seviyesi (V_OL) alıcının V_IL'sinin **altında**, gönderenin "1" seviyesi (V_OH) alıcının V_IH'ının **üstünde** durur. Aksi halde marj negatif olur.

4. **D** — `NM_L = V_IL − V_OL = 0,8 − 0,5 = 0,3 V`. 1,3 V iki sayının toplamıdır (anlamsız); 0,8 V ve 0,5 V ise tek bir eşiğin değeridir, marj değil.

5. **A** — Gerilim merdiveninde komşu iki basamağın farkı alınır: üstteki (V_OH) − alttaki (V_IH). V_IL − V_OL "0" marjıdır; V_IH − V_IL yasak bölgenin genişliğidir.

6. **C** — Statik disiplin, geçerli girişe karşılık **geçerli çıkış garantisidir**; kapının sinyali yenilemesinin dayanağı budur. Çıkış girişin kopyası değildir (evirici tersler), gürültünün sıfır olması da şart değildir; şart, çıkışın geçerli eşiklerde kalmasıdır.

7. **D** — Yasak olan bölgede **bulunmak** değil, **beklemektir**: her geçiş oradan geçer. Alıcı bu aralıkta karar garantisi vermez (rastgele "0" ya da "1" okuyabilir, CMOS'ta besleme akımı artabilir); devre hasar görmez (A yanlış), her zaman "0" da (B) ya da "1" de (C) okunmaz.

8. **A** — `V_IH = 0,7 × 4,5 = 3,15 V`; `NM_H = 2,4 − 3,15 = −0,75 V`. Negatif marj, "1" seviyesinin garanti edilmediği anlamına gelir. 74HCT'de V_IH = 2,0 V olduğu için marj `2,4 − 2,0 = +0,4 V` olur; ya da seviye çevirici kullanılır.

9. **B** — A = 1 ise `1 + ... = 1`, yani çıkış 1'dir. A = 0 ise çıkış `¬(B·C)`'dir ve bunun 0 olması için `B·C = 1`, yani B = 1 ve C = 1 gerekir. Tek satır: **A = 0, B = 1, C = 1** (De Morgan ile `¬(¬A·B·C)`).

10. **C** — `X·0 = 0`: 0 ile VE'lenen her şey 0'dır. Slaytta `X·0 = X` basılmış. Diğer kimlikler: `X + 1 = 1` (B yanlış), `X + 0 = X` (D yanlış).

11. **A** — Boşta CMOS girişi çevreden gürültü toplar ve gerilimi yasak bölgede dolaşır; çıkış rastgele döner, üst ve alt transistör birlikte kısmen iletip besleme akımını artırabilir. Giriş kendiliğinden "0" ya da "1" olmaz (B, C yanlış) ve yok sayılmaz (D). Kullanılmayan girişi 0 V'a veya V_CC'ye bağla; sürülmeyebilen hatlara pull-up/down koy.

12. **D** — `NM_H = 3,98 − 3,15 = 0,83 V`; hafif yükte `4,4 − 3,15 = 1,25 V` idi. Akım çektikçe V_OH düşer, marj **azalır**. Bu yüzden marj, çıkışın **gerçek yük akımında** hesaplanır.

</details>
