# MIT 6.002 · Ders 4: Dijital soyutlama

- **Oluşturma:** 2026-11-18
- **Kaynak slaytlar:** MIT OpenCourseWare, 6.002 *Circuits and Electronics* (Spring 2007), Ders 4 "The Digital Abstraction"; Anant Agarwal ve Jeffrey Lang · [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/)
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Bağlantılı:** [Ders 5: Dijital kapının içi](../05-dijital-kapinin-ici/ozet.md) · [Haberleşme arayüzleri, bölüm 6 (seviye çevirme)](../../Konular/haberlesme-arayuzleri/ozet.md#6-seviye-çevirme-33-v--5-v) · [Mikrodenetleyici donanımı, GPIO](../../Komponentler/05-mikrodenetleyici-donanimi/ozet.md#6-gpio) · [Direnç, pull-up / pull-down](../../Komponentler/01-direnc/ozet.md#51-pull-up--pull-down) · Kontrol listesi bölüm 7

> Bu dosya slaytların **Türkçe çalışma notudur**: çeviri değil, uyarlamadır (yeniden anlatım, düzeltmeler, ek örnekler). Aynı lisansla (CC BY-NC-SA 4.0) paylaşılır; ticari kullanım yoktur. Slayt PDF'i repoda tutulmaz.
>
> Anlatım slayt sırasını izler ve her bölümün başında slayt numaralarını yazar. Slaytlarda **iki baskı hatası** var; yerinde **⚠️ Slayt hatası** kutusuyla düzeltildi. Slaytlar 2000'lerin 5 V dünyasından gelir; **bölüm 8** aynı fikri bugünkü gerçek parçalara (74HC/HCT, TTL, 3,3 V LVTTL) bağlar. Parça değerleri tipik başlangıç noktasıdır, **datasheet esastır**.
>
> **Okuma planı:** 1. oturum: bölüm 1–4 (neden dijital, seviyeler, yasak bölge, marj) · 2. oturum: 5–7 (statik disiplin, kapı soyutlaması, Boole) · 3. oturum: 8–15.

| Bölüm | Slayt | İçerik |
|---|---|---|
| 1 | 2–5 | Hatırlatma, analog toplayıcı, gürültü problemi |
| 2 | 6–8 | İki seviyeli ayrıklaştırma, ilk gürültü marjı |
| 3 | 9–10 | Eşik sorunu ve yasak bölge |
| 4 | 11–12 | V_OH / V_OL / V_IH / V_IL ve gürültü marjları |
| 5 | 13, 17–18 | Statik disiplin, gürültü demosu |
| 6 | 14, 16 | Kombinasyonel kapı soyutlaması |
| 7 | 15, 19–20 | Boole mantığı, OR/NOT/NAND, kimlikler, örnek devre |

---

## ⚡ Hızlı tekrar

1. **Analogda bilgi gerilimin kendisidir**, bu yüzden gürültü bilgiyi doğrudan bozar (3,1 V mu 3,2 V mu?). **Dijitalde bilgi iki geniş aralıktır** (0 ve 1); küçük gürültü hiçbir şeyi değiştirmez.
2. İki seviye: **yüksek = DOĞRU = 1**, **alçak = YANLIŞ = 0**. 5 V / 0 V yalnızca örnektir; 3,3 V ve 1,8 V aynı mantıktır. Çok bit = sayı (101₂ = 5).
3. Tek bir eşik yetmez: eşik civarında alıcı rastgele karar verir. Bu yüzden iki eşik ve aralarında **yasak bölge** vardır. Sinyal bu bölgeden **geçer**, ama orada **beklememelidir**.
4. **Gönderen sıkı, alıcı hoşgörülü:** gönderen V_OL / V_OH, alıcı V_IL / V_IH söyler. Sıra her zaman **V_OL < V_IL < V_IH < V_OH**.
5. **Gürültü marjı** = gönderenin sözü − alıcının isteği: `NM_H = V_OH − V_IH`, `NM_L = V_IL − V_OL`. İkisi de pozitif olmalı. (Slayt 12'de NM_H ters yazılmış.)
6. **Statik disiplin:** giriş geçerliyse çıkış geçerli olmak **zorundadır**. Her kapı sinyali **yeniler**; gürültü zincirde birikmez.
7. **Kombinasyonel kapı:** çıkış yalnızca o anki girişlerin fonksiyonudur; içi bilinmeden kullanılır. Mantık = Boole cebri (AND, OR, NOT, NAND) ve doğruluk tabloları. `X·0 = 0` (slayt 20'de yanlış basılmış).
8. **İş yerinde:** iki parçayı bağlamadan önce datasheet'ten **dört sayıyı** (V_OH(min), V_OL(max), V_IH(min), V_IL(max)) bul, iki marjı hesapla; ikisi de pozitif ve yeterli olsun. Şüphede en kötü durum (yük akımı, sıcaklık, besleme) sütununu kullan.

## 🧮 Cep kartı

| Formül / kural | Ne zaman | Örnek |
|---|---|---|
| `NM_H = V_OH(min) − V_IH(min)` | "1" için gürültü payı | 74HC, 4 mA yük: 3,98 − 3,15 = **0,83 V** |
| `NM_L = V_IL(max) − V_OL(max)` | "0" için gürültü payı | 74HC, 4 mA yük: 1,35 − 0,26 = **1,09 V** |
| `V_OL < V_IL < V_IH < V_OH` | Eşik sırası doğru mu? | TTL: 0,4 < 0,8 < 2,0 < 2,4 ✓ |
| CMOS (HC): `V_IH ≈ 0,7·V_CC`, `V_IL ≈ 0,3·V_CC` | Alıcı eşiği beslemeyle kayar | 5 V'ta ≈ **3,5 V / 1,5 V** · 3,3 V'ta ≈ 2,31 V / 0,99 V |
| Garantili "1": `V ≥ V_IH(min)` · garantili "0": `V ≤ V_IL(max)` | Alıcıya gelen gerilimin durumu | HC @ 4,5 V: ≥ 3,15 V ve ≤ 1,35 V; arası **yasak bölge** |
| `X·1 = X` · `X·0 = 0` · `X+1 = 1` · `X+0 = X` | Sadeleştirme | `A·0 + B = B` |
| De Morgan: `¬(A·B) = ¬A + ¬B` · `¬(A+B) = ¬A·¬B` | NAND ↔ OR dönüşümü | `A + ¬(B·C) = ¬(¬A·B·C)` |
| Aktif-düşük sinyal (`nCS`, `/CS`) | Şematikte okuma | 0 V = **etkin** |

---

## 1. Neden dijital? (slayt 2–5)

İlk üç derste **toplu eleman soyutlamasını** öğrendin: devreyi KVL/KCL, düğüm yöntemi, süperpozisyon, Thévenin ve Norton ile çözüyorsun. Bu ders ikinci soyutlamayı ekler: **değeri ayrıklaştırmak**. İyi haber (slayt 3): yeni bir çözüm aracı gerekmiyor; ilk üç dersin araçları basit dijital devreleri çözmeye yeter.

**Eski yöntem: analog işleme (slayt 4).** İki direnç iki gerilimi tek düğümde birleştirir:

```
V1 ──[R1]──┬── V0            süperpozisyonla:
           │                 V0 = R2/(R1+R2)·V1 + R1/(R1+R2)·V2
V2 ──[R2]──┘                 R1 = R2 ise:  V0 = (V1 + V2) / 2
(iki kaynağın da eksi ucu GND'de)
```

Bu bir **toplayıcıdır** (ortalama verir, ×2 ile toplam olur). V1 ve V2 iki sensörün çıkışı olabilir. Sayı: V1 = 1,0 V, V2 = 3,0 V → V0 = 2,0 V.

**Sorun (slayt 5): gürültü.** Analog sinyalde bilgi gerilimin **kendisidir**. V1 hattına 0,1 V gürültü binerse V0 = 2,05 V olur. Alıcı bunun "gerçek değer" mi "gürültü" mü olduğunu **bilemez**, çünkü her gerilim geçerli bir değerdir. Slaytın dediği gibi: gürültü, 3,1 V ile 3,2 V gibi küçük farkları ayırt etmemizi engeller.

> **Benzetme:** Işık anahtarı ve ışık kısıcı (dimmer). Anahtar iki konumludur; biri hafifçe sallansa da "açık" yine "açık"tır. Kısıcıda ise potun konumu **bilgidir**: titrerse parlaklık oynar. Dijital sinyal anahtar gibi, analog sinyal kısıcı gibidir. Bir de **fotokopinin fotokopisi**: her kopyada biraz kir birikir (analog); metni her seferinde temiz yeniden yazmak kirin birikmesini önler (dijital, bölüm 5).

**Analog tamamen ortadan kalkmaz.** Sensörün kendisi analogtur (gaz sensörü köprüsü, NTC, mikrofon). Bu yüzden [ADC dersi](../../Konular/adc-ile-olcum/ozet.md) vardır: ölçüm bir kez sayıya çevrildikten sonra taşıma, saklama ve işleme dijital yapılır ve gürültü **birikmez**.

## 2. İki seviyeli ayrıklaştırma (slayt 6–8)

Değeri yalnızca **iki** seviyeye indir:

| Fiziksel | Mantıksal | Boole | İkilik rakam |
|---|---|---|---|
| 5 V (HIGH, yüksek) | TRUE, doğru | 1 | 1 |
| 0 V (LOW, alçak) | FALSE, yanlış | 0 | 0 |

- 5 V / 0 V slaytların seçimidir. Bugün 3,3 V, 1,8 V, 1,2 V aynı mantıkla çalışır; yalnızca sayılar değişir.
- **Pozitif mantık:** yüksek = 1. Tersi de olur: **aktif-düşük** sinyal (`nCS`, `/CS`, `nRESET`) 0 V'ta **etkindir** (bölüm 8.6).
- Yalnızca 0 ve 1 yetmez mi? Yeter, çünkü **çok bit** her sayıyı yazar (slayt 6): `101₂ = 1·4 + 0·2 + 1·1 = 5`. 8 bit = 2⁸ = 256 değer.

**Neden işe yarar? (slayt 7).** Gönderen yalnızca 5 V veya 0 V yollar; alıcı **2,5 V'a** bakıp karar verir. Hatta 0,2 V'a kadar gürültü olsa bile:

```
 zaman →             t1       t2       t3       t4
 gönderilen         5,0 V    0,0 V    5,0 V    5,0 V     bitler: 1 0 1 1
 hattaki gürültü   +0,2 V   −0,2 V   +0,1 V   −0,2 V
 alıcıya gelen      5,2 V   −0,2 V    5,1 V    4,8 V
 alıcı kararı        "1"      "0"      "1"      "1"      eşik 2,5 V → hepsi doğru ✓
```

Aynı 0,2 V analogda değeri doğrudan bozardı. Dijitalde gürültü, **marjı aşana kadar** bilgiyi değiştirmez.

**Gürültü marjı (slayt 8):** "1" için 5 V ile eşik 2,5 V arası `5 − 2,5 =` **2,5 V**; "0" için `2,5 − 0 =` **2,5 V**. Gürültü bu kadar büyüyene kadar bilgi korunur.

> **Gürültü nereden gelir?** Komşu hatlar (crosstalk), anahtarlamalı regülatörler, röleler, ortak toprak empedansı (ground bounce), ESD, kablodan giren RF. Kaynaklar ve önlemler: [EMC için kart tasarımı](../../EMC/02-emc-icin-kart-tasarimi/ozet.md).

## 3. Yasak bölge (slayt 9–10)

**Slayt 9'un sorusu: 2,5 V gelirse?** Tek eşikte (2,5 V) eşiğe yakın bir gerilimde alıcı **rastgele** karar verir: en küçük gürültü kararı çevirir. Çözüm: eşiği bir çizgi değil **bant** yap. Bant içindeki gerilimler "tanımsızdır" (slayt 10: "no man's land", yasak bölge).

```
  5 V ┬──────────────────────────  geçerli "1"   (örnekte ≥ 3 V)
      │
  3 V ┼ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─  V_H
      │    ░░░░░ yasak bölge ░░░░░   alıcı garanti vermez
  2 V ┼ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─  V_L
      │
  0 V ┴──────────────────────────  geçerli "0"   (örnekte ≤ 2 V)
```

Slayt 10'un sayıları: **3 V ve üstü → 1**, **2 V ve altı → 0**, arası **yasak**.

> **Yasak ≠ sinyal orada bulunamaz.** Her 0 ↔ 1 geçişi bu bölgeden **geçer**. Yasak olan orada **beklemektir**. Gerilim burada kalırsa alıcının çıkışı belirsiz olur; CMOS'ta üst ve alt transistör aynı anda kısmen iletip besleme akımını artırabilir. **Boşta bırakılmış (floating) giriş** tam olarak böyle bir yerde kalır (bölüm 8.4).

> **Benzetme:** Işık anahtarını yarıya basılı bırakmak. Anahtar ya tam açık ya tam kapalı olmalı; ortada ne yanar ne söner, kimse de güvenilir bir şey söyleyemez.

## 4. Gönderen ve alıcı için ayrı eşikler (slayt 11–12)

**Hâlâ bir açık var (slayt 11):** gönderen tam V_H'yi (örnekte 3 V) yollarsa en küçük gürültü onu yasak bölgeye iter. Çözüm: **göndereni alıcıdan daha sıkı standartlara bağla.** Gönderen "1" için *en az* V_OH, "0" için *en çok* V_OL vereceğine söz verir; alıcı "1" saymak için *en az* V_IH, "0" saymak için *en çok* V_IL ister.

| Sembol | Anlamı | Kim söz verir? |
|---|---|---|
| **V_OH** | Çıkışın "1" iken vereceği **en düşük** gerilim | Gönderen |
| **V_OL** | Çıkışın "0" iken vereceği **en yüksek** gerilim | Gönderen |
| **V_IH** | Girişin "1" sayması için gereken **en düşük** gerilim | Alıcı |
| **V_IL** | Girişin "0" sayabileceği **en yüksek** gerilim | Alıcı |

(O = Output, I = Input; H = High, L = Low.) Sıralama: **V_OL < V_IL < V_IH < V_OH**.

```
   V
 4,50 ┐                                  V_CC = 4,5 V
      │
 3,98 ┤ ━━ V_OH(min)   gönderen "1" için söz verir
      │       ↕ NM_H = 3,98 − 3,15 = 0,83 V
 3,15 ┤ ── V_IH(min)   alıcı "1" saymak için ister
      │       ░░░░ yasak bölge ░░░░
 1,35 ┤ ── V_IL(max)   alıcı "0" saymaya razı
      │       ↕ NM_L = 1,35 − 0,26 = 1,09 V
 0,26 ┤ ━━ V_OL(max)   gönderen "0" için söz verir
      │
 0,00 ┘
```

(Sayılar: 74HC, V_CC = 4,5 V, 4 mA yük, 25 °C; bölüm 8.2.)

**Gürültü marjları (slayt 12):**

```
NM_H = V_OH − V_IH      "1" için pay
NM_L = V_IL − V_OL      "0" için pay
```

Marj = **gönderenin sözü − alıcının isteği**. İkisi de **pozitif** olmalı; ne kadar büyükse gürültüye o kadar dayanıklı. Ders 5'teki örnek (slayt 16): V_OL = 0,5 V, V_OH = 4,5 V, V_IL = 0,9 V, V_IH = 4,1 V → `NM_H = 4,5 − 4,1 = 0,4 V`, `NM_L = 0,9 − 0,5 = 0,4 V`.

> ⚠️ **Slayt hatası (slayt 12):** "1" marjı `V_IH − V_OH` olarak yazılmış; V_OH > V_IH olduğu için bu **negatif** çıkar. Doğrusu **V_OH − V_IH**. "0" marjı (`V_IL − V_OL`) doğru yazılmış. **Kolay hatırlama:** gerilim merdiveninde iki komşu basamağın farkıdır; **üsttekinden alttakini çıkar**, sonuç hep pozitif olur.

**Marj yüke bağlıdır.** V_OH(min) ve V_OL(max) belirli bir **yük akımında** garantilidir; akım çektikçe V_OH düşer, V_OL yükselir. 74HC, 4,5 V: hafif yükte (20 µA) V_OH ≥ 4,4 V ve V_OL ≤ 0,1 V → `NM_H = NM_L = 1,25 V`. 4 mA yükte V_OH ≥ 3,98 V ve V_OL ≤ 0,26 V → `NM_H = 0,83 V`, `NM_L = 1,09 V`. Marjı **gerçek yük akımında** hesapla.

> **Kural: gönderen sıkı, alıcı hoşgörülü.** Gönderen eşiklerden uzak durur, alıcı geniş bir aralığı kabul eder. İki tarafın sözü de datasheet'te yazılıdır.

## 5. Statik disiplin (slayt 13, 17, 18)

Dijital sistemin tek kuralı (slayt 13):

> **Statik disiplin:** Girişler geçerli eşikleri sağlıyorsa (≥ V_IH veya ≤ V_IL), sistem **çıkışların da geçerli eşikleri sağlayacağını garanti eder** (≥ V_OH veya ≤ V_OL).

Sonucu: kapı **yenileyicidir** (regenerative). Bozulmuş ama hâlâ geçerli bir girişi alır ve **tam seviyede** yeni bir çıkış üretir.

| Nokta | Gerilim | Durum |
|---|---|---|
| 1. kapı çıkışı (74HC, hafif yük) | 4,40 V | V_OH: tam seviye "1" |
| 2. kapı girişi (hat kaybı ve gürültü sonrası) | 3,50 V | ≥ V_IH (3,15 V) → **geçerli "1"**, ama marjın çoğu gitti |
| 2. kapı çıkışı (evirici) | ≤ 0,10 V | **taze "0"**: marj yeniden tam |

(Örnek sayılardır.) Zincirde 10 kapı olsa da her biri seviyeyi yeniler; **gürültü birikmez** (analog yükselteç zincirinde birikir). Sinyal ancak bir kapı **marjı tamamen bitirirse** bozulur.

**Slayt 17 (demo):** AND kapısının girişlerine gürültü bindirilir; çıkış yine temizdir. **Slayt 18:** X ve Y dalga biçimleri verilir, `Z = X·Y` çizilir. Kendin dene: X ve Y'nin ikisi de 1 olduğu aralıklarda Z = 1, diğer her yerde 0.

> **Giriş yasak bölgedeyse** kapı hiçbir şey garanti etmez: çıkış 0, 1 ya da arada bir gerilim olabilir. Statik disiplin sözü yalnızca **geçerli** girişler içindir.

## 6. Kombinasyonel kapı soyutlaması (slayt 14, 16)

Slayt 14: yalnızca iki değerimiz var (1 ve 0); bunlar doğal olarak mantığa (T, F) eşlenir ve sayıları da temsil edebilir. Slayt 16'daki **kombinasyonel kapı** tanımı:

- **Statik disipline uyar** (bölüm 5).
- **Çıkış yalnızca o anki girişlerin fonksiyonudur:** geçmişi hatırlamaz, bellek yoktur. Bellekli devreler (flip-flop, kayıtçı) ayrı bir sınıftır.
- **Dijital mantık tasarımcısı kapının içini bilmek zorunda değildir.** Elinde doğruluk tablosu ve Boole denklemi yeter. İçini [Ders 5](../05-dijital-kapinin-ici/ozet.md) açar.

> **Soyutlamanın bedeli:** Gerçek kapıda çıkış girişle aynı anda değişmez; **yayılım gecikmesi** (t_pd) vardır ve datasheet'te yazılıdır. Boole denklemi bunu göstermez; hızlı devrede ve zamanlama hesabında ayrıca hesaba katılır.

## 7. Boole mantığı (slayt 15, 19, 20)

**AND (slayt 15):** "X doğru **ve** Y doğruysa Z doğrudur, değilse yanlıştır." Denklem `Z = X·Y`. **Doğruluk tablosu** tüm giriş kombinasyonlarını sayar. **OR (slayt 19):** "A **veya** B doğruysa C doğrudur", `C = A + B`. Slayt ayrıca **evirici** (NOT) ve **NAND** kapılarını gösterir. Slaytlarda tersleme üst çizgiyle yazılır; bu notta `¬` kullanıldı.

| X | Y | AND `X·Y` | OR `X+Y` | NAND `¬(X·Y)` |
|---|---|---|---|---|
| 0 | 0 | 0 | 0 | 1 |
| 0 | 1 | 0 | 1 | 1 |
| 1 | 0 | 0 | 1 | 1 |
| 1 | 1 | 1 | 1 | 0 |

NOT (evirici): `¬0 = 1`, `¬1 = 0`.

**Boole kimlikleri (slayt 20):**

| Kimlik | Not |
|---|---|
| `X·1 = X` | 1, AND'de etkisiz elemandır |
| `X·0 = 0` | ⚠️ **Slayt hatası:** slaytta `X·0 = X` basılmış. Doğrusu 0: 0 ile VE'lenen her şey 0'dır |
| `X + 1 = 1` | 1 ile VEYA'lanan her şey 1'dir |
| `X + 0 = X` | 0, OR'da etkisiz elemandır |
| `¬1 = 0` · `¬0 = 1` | Tersleme |
| `A·B + A·C = A·(B + C)` | Ortak çarpan |
| `¬(A·B) = ¬A + ¬B` · `¬(A+B) = ¬A·¬B` | **De Morgan** (slaytta yok; aşağıdaki örnekte kullanılır) |

**Örnek devre (slayt 20): `çıkış = A + ¬(B·C)`**. B·C'nin tamamı terslenmiş (NAND), sonra A ile OR'lanıyor: **iki kapı**.

```
 B ──┐
     ├─ NAND ─ X ──┐
 C ──┘             ├─ OR ── çıkış
 A ────────────────┘
```

| A | B | C | X = ¬(B·C) | çıkış = A + X |
|---|---|---|---|---|
| 0 | 0 | 0 | 1 | 1 |
| 0 | 0 | 1 | 1 | 1 |
| 0 | 1 | 0 | 1 | 1 |
| 0 | 1 | 1 | 0 | **0** |
| 1 | 0 | 0 | 1 | 1 |
| 1 | 0 | 1 | 1 | 1 |
| 1 | 1 | 0 | 1 | 1 |
| 1 | 1 | 1 | 0 | 1 |

Çıkış **yalnızca A = 0, B = 1, C = 1'de 0** olur. De Morgan ile kontrol: `A + ¬(B·C) = ¬(¬A·B·C)`; çıkışın 0 olması için `¬A·B·C = 1` gerekir, yani A = 0, B = 1, C = 1 ✓. Aynı işlev, girişi terslenmiş **tek bir 3 girişli NAND** ile de yapılır.

> **NAND neden önemli?** NAND tek başına her mantık işlevini kurabilir (evrensel kapı). Ders 5'te NAND'ın neden en doğal kapı olduğunu göreceksin: iki anahtarın **seri** bağlanması.

## 8. 💼 İş yerinde: iki dijital parça birbirine uyar mı?

### 8.1 Beş adımlık kontrol

1. **Sürücünün** V_OH(min) ve V_OL(max) değerlerini datasheet'ten bul. Sayıların yanındaki **test koşuluna** (I_OH, I_OL, V_CC) bak: o yük akımında geçerlidirler.
2. **Alıcının** V_IH(min) ve V_IL(max) değerlerini bul. CMOS'ta bunlar genelde **alıcının kendi V_CC'sinin** oranıdır (0,7·V_CC / 0,3·V_CC): kaynağın değil, alıcının beslemesiyle hesapla.
3. İki marjı hesapla: `NM_H = V_OH(min) − V_IH(min)` ve `NM_L = V_IL(max) − V_OL(max)`.
4. **Biri bile ≤ 0 ise** bağlantı garantili değildir: seviye uyumlu aile (HCT), seviye çevirici veya karşılaştırıcı kullan.
5. İkisi de pozitif ama küçükse (TTL/LVTTL'de 0,4 V): gürültü bütçesini (bölüm 11) ve kenar hızını (8.5) kontrol et.

### 8.2 Aile tablosu

| Aile (besleme) | V_IL(max) | V_IH(min) | V_OL(max) | V_OH(min) | Koşul ve kaynak |
|---|---|---|---|---|---|
| **74HC** (4,5 V) | 1,35 V (0,3·V_CC) | 3,15 V (0,7·V_CC) | 0,26 V @ 4 mA · 0,1 V @ 20 µA | 3,98 V @ 4 mA · 4,4 V @ 20 µA | onsemi MM74HC00, 25 °C |
| **74HCT** (4,5–5,5 V) | 0,8 V | 2,0 V | 0,33 V @ 4 mA | 3,84 V @ 4 mA | TI SN74HCT00, −40…85 °C, V_CC = 4,5 V |
| **5 V TTL** | 0,8 V | 2,0 V | 0,4 V | 2,4 V | Standart TTL seviyeleri |
| **3,3 V LVTTL** | 0,8 V | 2,0 V | 0,4 V | 2,4 V | Standart LVTTL seviyeleri |

Kendi ailesiyle marjlar (sürücü ve alıcı aynı aile):

| Aile | NM_H | NM_L |
|---|---|---|
| 74HC, 20 µA yük | 4,4 − 3,15 = **1,25 V** | 1,35 − 0,1 = **1,25 V** |
| 74HC, 4 mA yük | 3,98 − 3,15 = **0,83 V** | 1,35 − 0,26 = **1,09 V** |
| 74HCT, 4 mA yük | 3,84 − 2,0 = **1,84 V** | 0,8 − 0,33 = **0,47 V** |
| 5 V TTL ve 3,3 V LVTTL | 2,4 − 2,0 = **0,4 V** | 0,8 − 0,4 = **0,4 V** |

> HC sütunu 25 °C, HCT sütunu −40…85 °C değerleridir; koşullar karışık olduğu için bu tablo **yaklaşıktır**. Tasarımda hep **kendi sıcaklık aralığının** ve gerçek yük akımının sütununu kullan. TTL ve LVTTL'nin dört sayısı aynıdır; fark yalnızca besleme gerilimidir.

### 8.3 Aileler arası bağlantı

| Sürücü → alıcı | NM_H | NM_L | Sonuç |
|---|---|---|---|
| 3,3 V LVTTL → 74HC (V_CC = 4,5 V) | 2,4 − 3,15 = **−0,75 V** | 1,35 − 0,4 = 0,95 V | ✗ "1" garantili değil |
| 3,3 V LVTTL → 74HCT (V_CC = 4,5 V) | 2,4 − 2,0 = 0,4 V | 0,8 − 0,4 = 0,4 V | ✓ marj küçük |
| 5 V TTL → 74HC (V_CC = 4,5 V) | 2,4 − 3,15 = **−0,75 V** | 1,35 − 0,4 = 0,95 V | ✗ (HCT'nin varlık nedeni) |
| 74HC (4 mA) → TTL veya HCT girişi | 3,98 − 2,0 = 1,98 V | 0,8 − 0,26 = 0,54 V | ✓ |
| 74HCT (4 mA) → 74HC | 3,84 − 3,15 = 0,69 V | 1,35 − 0,33 = 1,02 V | ✓ |

- V_CC = 5 V olunca HC'nin V_IH'ı ≈ 3,5 V'a çıkar; 3,3 V'luk bir çıkış için durum **daha da kötüdür**.
- Garantili V_OH(min) **en kötü durumdur**; hafif yükte gerçek çıkış besleme gerilimine çok yakındır. Ama garantiye dayanmayan tasarım sıcaklık ve parti değişiminde bozulur.
- 3,3 V ↔ 5 V çözümleri (HCT tampon, seviye çevirici, I²C için özel çevirici): [Haberleşme dersi, bölüm 6](../../Konular/haberlesme-arayuzleri/ozet.md#6-seviye-çevirme-33-v--5-v).

### 8.4 Boşta (floating) giriş = yasak bölge

CMOS girişi neredeyse hiç akım çekmez; hiçbir şeye bağlı değilse gerilimi çevreden gelen gürültüyle **yasak bölgede dolaşır**. Sonuç: çıkış rastgele döner ve kapı ara gerilimde fazla besleme akımı çeker (üst ve alt transistör birlikte kısmen iletir). Kural: **hiçbir giriş boşta kalmaz.** Kullanılmayan girişi 0 V'a veya V_CC'ye bağla; bazen kimsenin sürmediği hatlara (açık-drenaj çıkış, buton, reset sırasında MCU pini) **pull-up / pull-down** koy. Değer seçimi: [Direnç dersi, 5.1](../../Komponentler/01-direnc/ozet.md#51-pull-up--pull-down) (tipik 10 kΩ).

### 8.5 Yavaş kenar: Schmitt-trigger giriş

Yasak bölgeden **yavaş** geçen bir sinyalde (yavaş yükselen RC çıkışı, mekanik kontak, optokuplör çıkışı) gürültü kararı arka arkaya çevirir: giriş eşiğin etrafında gezinirken çıkış titrer (çift tetikleme). **Schmitt-trigger** girişte iki eşik vardır: yükselirken V_T+, düşerken V_T−. Aradaki fark **histerezistir** ve girişi eşik civarındaki gürültüden korur. Histerezis değeri V_DD'ye bağlıdır ve datasheet'te yazılıdır; değeri varsayma. Birçok MCU'nun dijital girişinde Schmitt-trigger bulunur, ama pin ve moda göre değişir: kendi MCU'nun "I/O characteristics" tablosuna bak.

### 8.6 Aktif-düşük sinyaller

`nCS`, `/CS`, `nRESET`, `nINT` gibi adlar sinyalin **0 V'ta etkin** olduğunu söyler. Şematikte ad tutarlı yazılır; pull-up ile **etkin olmayan** (yüksek) duruma çekilir. Bu yüzden SPI CS hatlarına pull-up konur: boot sırasında hiçbir slave seçili olmamalıdır (kontrol listesi bölüm 7).

### 8.7 Kendi ürünlerinde nerede?

Aşağıdakiler **tipik** yerlerdir; kendi şemandaki parçanın datasheet'ine göre doğrula.

| Blok | Dijital sınırdaki bağlantı | Bu dersten kontrol |
|---|---|---|
| Dimmer: şebeke sıfır geçiş girişi | Optokuplör veya dedektör çıkışı → MCU pini; kenar çoğunlukla yavaş | Histerezisli giriş (8.5); pull-up/down ile tanımlı seviye; MCU'nun V_IH / V_IL değerine göre eşik |
| Varlık sensörü çıkışı | Modül çıkışı → MCU; seviye modüle göre değişir, bazı modüller açık-kolektör verir | V_OH(min) ≥ MCU V_IH(min) mi? Açık-kolektörse pull-up ([Ders 5](../05-dijital-kapinin-ici/ozet.md)) |
| Gaz dedektörü: alarm ve röle çıkışları | MCU → transistör/MOSFET → röle; ya da harici sisteme açık-kolektör çıkış | V_OL, sink akımı ve pull-up (Ders 5); [MOSFET dersi](../../Konular/mosfet-transistor-ve-yuk-surme/ozet.md) |
| Kapı paneli / interkom: buton ve kontak girişleri | Mekanik kontak → pin, uzun kablo | pull-up/down, RC + histerezis, ESD; yarım açık kontak = yasak bölge |

## 9. Şematikte

- Her IC'nin **besleme domaini** (3V3, 5V, 1V8) yazılı; domainler arası her dijital hat için bölüm 8.1'in "uyar mı?" sorusu cevaplanmış.
- Seviye uyumsuzluğu olan hatta **çevirici** veya uyumlu aile (HCT) konmuş ve nedeni not edilmiş.
- Aktif-düşük sinyaller `n` veya `/` önekiyle adlandırılmış; etkin olmayan durumda pull-up/down ile tanımlı.
- Hiçbir giriş boşta değil; kullanılmayan kapı girişleri 0 V'a veya V_CC'ye bağlı.
- Yavaş veya gürültülü kaynaklı girişlerde (kontak, optokuplör, sıfır geçiş) histerezisli giriş notu var.

## 10. PCB / layout

- Yüksek empedanslı, boşta kalabilen girişleri **gürültü kaynaklarından** (anahtarlamalı regülatör, bobin, röle) uzak tut.
- Pull-up / pull-down dirençlerini **girişin yanına** koy.
- Hızlı kenarlı hatlara seri direnç yeri bırak (22–33 Ω; [Haberleşme dersi, bölüm 7](../../Konular/haberlesme-arayuzleri/ozet.md#7-hızlı-kenarlar-ve-seri-sonlandırma)).
- Sürekli GND düzlemi kullan: dönüş akımı yolu kısa kalır, ground bounce küçülür; marjdan yenilen pay azalır.

## 11. EMC açısından

- **Marj bir bütçedir:** komşu hat kuplajı, ground bounce, RF ve ESD/EFT hepsi marjdan pay alır. TTL/LVTTL'deki 0,4 V'luk marj, 74HC'nin ~1 V'luk marjından çok daha kolay tükenir.
- **Gereğinden hızlı kenar** geniş bantlı gürültü üretir; hıza ihtiyaç yoksa yavaşlat (seri direnç, düşük hızlı çıkış modu).
- EMC testinde (EFT, RF bağışıklık) bir giriş **yasak bölgeye** girip çıkıyorsa tek kenar iki kenar gibi okunabilir. Kritik girişte histerezis + küçük RC + yazılım süzgeci birlikte kullanılır. Testte girişin ne kadar bozulduğu **performans kriterini** belirler ([EMC 03](../../EMC/03-emc-testleri-ve-standartlar/ozet.md)).

## 12. Ölçüm ve doğrulama

1. **Statik seviyeler:** Çıkışı "1" ve "0" yapıp **gerçek yük bağlıyken** multimetre ile V_OH ve V_OL'yi ölç; datasheet'teki min/max ile karşılaştır.
2. **Yasak bölgede geçirilen süre:** Osiloskopta bir kenarın **V_IL ile V_IH arasında** kaç ns kaldığını ölç. Datasheet'in verdiği en yavaş giriş kenar süresini (Δt/Δv) aşıyorsa Schmitt-trigger gerekir.
3. **Gerçek gürültü marjı:** Giriş sabit "0" iken röle, PWM veya motor çalışırken girişteki tepe-tepe gürültüyü ölç; NM_L'den (ve "1" için NM_H'den) **küçük** olmalı.
4. **Boşta giriş taraması:** Şematikte her giriş için "kim sürüyor, sürmediği an var mı?" diye sor (reset, boot, kablo çıkık).

## 13. Kendin dene

1. Sürücü: V_OH(min) = 2,4 V, V_OL(max) = 0,4 V. Alıcı: V_IH(min) = 2,0 V, V_IL(max) = 0,8 V. NM_H ve NM_L kaç volt?
2. Alıcı CMOS, V_CC = 3,3 V, `V_IH = 0,7·V_CC`. Sürücünün V_OH(min) değeri 2,9 V. NM_H kaç volt?
3. Sürücü V_OH(min) = 3,0 V, alıcı V_IH(min) = 3,15 V. Bağlantı garantili mi?
4. A = 0, B = 1, C = 1 iken `A + ¬(B·C)` kaçtır? A = 1 iken?
5. 74HC, V_CC = 5 V: V_IH yaklaşık kaç volttur? 3,3 V'luk bir MCU çıkışı bunu garantili sürebilir mi?
6. Slayt 12'deki "1" marjı formülünü (V_IH − V_OH) kullansaydın T1000 örneğinde (V_OH = 4,5 V, V_IH = 4,1 V) kaç bulurdun, doğrusu kaç?

<details>
<summary>Cevaplar</summary>

1. `NM_H = 2,4 − 2,0 =` **0,4 V** · `NM_L = 0,8 − 0,4 =` **0,4 V**
2. `V_IH = 0,7 × 3,3 = 2,31 V` → `2,9 − 2,31 =` **0,59 V**
3. `3,0 − 3,15 =` **−0,15 V**: negatif, **garantili değil** ("1" yasak bölgede kalabilir)
4. A = 0, B = 1, C = 1: `0 + ¬(1·1) = 0 + 0 =` **0**. A = 1 ise çıkış her zaman **1**
5. `V_IH ≈ 0,7 × 5 = 3,5 V` → 3,3 V < 3,5 V: **garantili değil**; HCT/AHCT tampon veya seviye çevirici gerekir
6. Yanlış formül: `4,1 − 4,5 =` **−0,4 V** (negatif marj anlamsız); doğrusu `4,5 − 4,1 =` **+0,4 V**

</details>

## 14. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| 3,3 V MCU çıkışını 5 V'luk 74HC girişine doğrudan bağlamak | HC'nin V_IH'ı ≈ 3,5 V; 3,3 V'luk "1" garantili değil | HCT/AHCT tampon veya seviye çevirici |
| Tipik V_OH / V_OL'ye güvenip marj hesaplamak | Garanti min/max değerlerindedir; yükte ve sıcaklıkta kayar | Min/max ve gerçek yük akımı |
| Alıcı eşiğini kaynağın V_CC'sine göre hesaplamak | Eşik alıcının beslemesine bağlıdır | Alıcının V_CC'si × 0,7 / 0,3 |
| Boşta giriş | Yasak bölgede dolaşır, çıkış rastgele olur, besleme akımı artar | Pull-up/down veya sabit bağlantı |
| Yavaş kenarı standart girişe vermek | Yasak bölgede uzun kalır, çift tetikleme | Schmitt-trigger giriş |
| Marjı yalnızca DC'de hesaplayıp bırakmak | Komşu hat kuplajı, ground bounce, ESD marjdan yer | Osiloskopla gerçek gürültüyü ölç |
| Aktif-düşük sinyalde pull-up'ı unutmak | Hat boşta kalır, etkin/etkisiz durumu belirsizleşir | `n` / `/` adlandırma, tanımlı pasif seviye |
| Slayt hatalarını kopyalamak (`NM_H = V_IH − V_OH`, `X·0 = X`) | Negatif marj ve yanlış sadeleştirme | `NM_H = V_OH − V_IH`, `X·0 = 0` |
| "Dijital = ideal" sanmak | Sinyal geçişte yasak bölgeden geçer, kapıda gecikme (t_pd) vardır | Kenar süresini ve t_pd'yi hesaba kat |

## 15. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Dijital soyutlama** | Sürekli gerilimi iki seviyeye (0/1) indirgeyip gürültüden bağımsız çalışma |
| **Yüksek / alçak (HIGH / LOW)** | İki geçerli gerilim bölgesi; mantıkta 1 ve 0 |
| **Yasak bölge** | V_IL ile V_IH arası; alıcı bu aralıkta karar garantisi vermez |
| **V_OH / V_OL** | Çıkışın "1" / "0" iken garanti ettiği en düşük / en yüksek gerilim |
| **V_IH / V_IL** | Girişin "1" / "0" saymak için kabul ettiği en düşük / en yüksek gerilim |
| **Gürültü marjı (NM_H, NM_L)** | Sinyalin bozulmadan yutabileceği gürültü: V_OH − V_IH ve V_IL − V_OL |
| **Statik disiplin** | Geçerli giriş → geçerli çıkış garantisi |
| **Yenileme (regeneration)** | Kapının bozuk ama geçerli girişten tam seviyeli çıkış üretmesi |
| **Kombinasyonel kapı** | Çıkışı yalnızca anlık girişlere bağlı, belleksiz kapı |
| **Boole cebri** | AND (·), OR (+), NOT (¬) ile mantık denklemleri |
| **Doğruluk tablosu** | Tüm giriş kombinasyonları ve çıkışların listesi |
| **NAND** | AND'in tersi; evrensel kapı |
| **De Morgan** | `¬(A·B) = ¬A + ¬B` ve `¬(A+B) = ¬A·¬B` |
| **Aktif-düşük** | 0 V'ta etkin olan sinyal (`nCS`, `/CS`) |
| **Histerezis / Schmitt-trigger** | Yükselirken ve düşerken farklı eşik kullanan giriş |
| **Boşta (floating) giriş** | Hiçbir şeyin sürmediği, gerilimi tanımsız giriş |
| **Yayılım gecikmesi (t_pd)** | Girişteki değişimin çıkışa yansıma süresi |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.6, bölüm 7):

- [x] Her dijital bağlantıda sürücünün V_OH(min) / V_OL(max) değerleri ile alıcının V_IH(min) / V_IL(max) değerleri datasheet'ten (yük akımı, besleme ve sıcaklık uçlarında) karşılaştırıldı; iki gürültü marjı da pozitif ve yeterli
- [x] Yavaş veya gürültülü kenarlı girişler (sıfır geçiş, optokuplör çıkışı, mekanik kontak, uzun kablo) histerezisli (Schmitt-trigger) girişe veya karşılaştırıcıya bağlandı

Üçüncü madde (açık-drenaj pull-up hesabı) [Ders 5](../05-dijital-kapinin-ici/ozet.md) ile gelir.

## Kontrol soruları

→ [quiz.md](quiz.md) · 12 soru, 5'i hesap
