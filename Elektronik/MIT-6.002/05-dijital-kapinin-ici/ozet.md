# MIT 6.002 · Ders 5: Dijital kapının içi

- **Oluşturma:** 2026-11-18
- **Kaynak slaytlar:** MIT OpenCourseWare, 6.002 *Circuits and Electronics* (Spring 2007), Ders 5 "Inside the Digital Gate"; Anant Agarwal ve Jeffrey Lang · [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/)
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Bağlantılı:** [Ders 4: Dijital soyutlama](../04-dijital-soyutlama/ozet.md) · [MOSFET, transistör ve yük sürme (bölüm 3–4)](../../Konular/mosfet-transistor-ve-yuk-surme/ozet.md#3-n-mosfet-seçimi) · [Haberleşme arayüzleri, I²C](../../Konular/haberlesme-arayuzleri/ozet.md#4-ic) · [Direnç, pull-up / pull-down](../../Komponentler/01-direnc/ozet.md#51-pull-up--pull-down) · Kontrol listesi bölüm 7 ve 12

> Bu dosya slaytların **Türkçe çalışma notudur**: çeviri değil, uyarlamadır (yeniden anlatım, düzeltmeler, ek örnekler). Aynı lisansla (CC BY-NC-SA 4.0) paylaşılır; ticari kullanım yoktur. Slayt PDF'i repoda tutulmaz.
>
> Anlatım slayt sırasını izler ve her bölümün başında slayt numaralarını yazar. Slaytlarda **bir baskı hatası** var (slayt 8); yerinde **⚠️ Slayt hatası** kutusuyla düzeltildi. Slaytlardaki kapı sayıları ve MOSFET sayıları 2000 dönemine aittir. **Bölüm 10** aynı fikirleri bugünkü gerçek devrelere (açık-drenaj çıkış, pull-up, gerçek MOSFET) bağlar. Sayısal değerler tipik başlangıç noktasıdır, **datasheet esastır**.
>
> **Okuma planı:** 1. oturum: bölüm 1–5 (anahtar mantığı ve kapılar) · 2. oturum: 6–9 (MOSFET, statik disiplin, SR modeli) · 3. oturum: 10–17.

| Bölüm | Slayt | İçerik |
|---|---|---|
| 1 | 2–4 | Hatırlatma, NAND, 3 kapılı örnek devre |
| 2 | 5–7 | Su musluğu ve ampul benzetmesi (AND / OR) |
| 3 | 8 | Anahtar (switch) elemanı |
| 4 | 9 | Anahtar + yük direnci = evirici |
| 5 | 10–11 | Seri = NAND, paralel = NOR, bileşik kapı |
| 6 | 12–14 | MOSFET ve anahtar modeli (S modeli) |
| 7 | 15 | MOSFET evirici |
| 8 | 16–17 | Statik disiplin kontrolü (T1000 örneği) |
| 9 | 18–20 | SR modeli ve yük direnci seçimi |

---

## ⚡ Hızlı tekrar

1. Her dijital kapı bir **anahtar ağıdır**: çıkışla GND (veya V_S) arasında kontrol sinyalleriyle açılıp kapanan yollar. Benzetme: **su muslukları**; seri musluk = AND, paralel musluk = OR.
2. Anahtar modeli: kontrol **C = 1 → kapalı (iletir)**, **C = 0 → açık**. (Slayt 8'in metni ters basılmış; şekil ve sonraki slaytlar böyle.)
3. **Anahtar + yük direnci R_L = evirici:** anahtar iletirse çıkış GND'ye iner (0), iletmezse R_L çıkışı V_S'ye çeker (1).
4. **Seri anahtarlar = NAND, paralel anahtarlar = NOR.** Kural: *çıkış, GND'ye iletken bir yol varsa 0'dır*; yol yoksa 1. Seri/paralel karışımı **bileşik kapıdır**: `D = ¬(A·B + C)`.
5. **MOSFET** gerilimle kontrol edilen anahtardır (G, D, S). S modeli: `v_GS < V_T` → açık, `v_GS ≥ V_T` → kapalı; `V_T ≈ 1 V`.
6. Gerçek anahtarın iletim direnci vardır: **SR modeli** (R_ON, örnekte 5 kΩ). Düşük çıkış `V_OL = V_S·R_ON/(R_ON + R_L)`; bunu sınırda tutmak için `R_L ≥ R_ON·(V_S − V_OL)/V_OL`.
7. S modelli eviricinin statik disiplini: `V_IL < V_T ≤ V_IH`, `V_OH ≤ V_S`, `V_OL ≥ 0`. Marj büyük olsa da bu üç koşul sağlanmazsa kapı sözünü tutamaz.
8. **İş yerinde:** bu evirici tam olarak **açık-drenaj / açık-kolektör çıkıştır**. Pull-up alt sınırı `R_min = (V_DD − V_OL)/I_OL`, yukarıdaki formülün aynısıdır (I²C, 3,3 V: **967 Ω**).

## 🧮 Cep kartı

| Formül / kural | Ne zaman | Örnek |
|---|---|---|
| `V_OUT(düşük) = V_S·R_ON/(R_ON + R_L)` | Yük dirençli eviricide düşük seviye | 5 V, 5 kΩ, 45 kΩ → **0,5 V** |
| `R_L(min) = R_ON·(V_S − V_OL)/V_OL` | Yük direnci alt sınırı | 5 kΩ, 5 V, V_OL = 0,5 V → **45 kΩ** |
| `R_L(min) = (V_S − V_OL)/I_OL` | Aynısı, datasheet diliyle (`V_OL = I_OL·R_ON`) | I²C, 3,3 V, 0,4 V, 3 mA → **967 Ω** |
| `I = V_S/(R_ON + R_L)` · `P = V_S·I` | Düşük durumda statik akım ve güç | 5 V / 50 kΩ → **0,1 mA, 0,5 mW** |
| `t_r(10–90 %) ≈ 2,2·R_L·C_L` | R_L ile yükselme süresi | 45 kΩ, 10 pF → **≈ 1 µs** |
| Seri anahtar = NAND · paralel = NOR | Kapı türü | `¬(A·B)` · `¬(A+B)` |
| Çıkış 0 ⇔ GND'ye iletken yol var | Bileşik kapı çözümü | `D = ¬(A·B + C)` |
| `V_IL < V_T ≤ V_IH`, `V_OH ≤ V_S`, `V_OL ≥ 0` | S modelli eviricide statik disiplin | T1000: 0,9 < 1 ≤ 4,1 ✓ |
| S modeli: `v_GS ≥ V_T` → iletir | Anahtar durumu | V_T = 1 V, v_GS = 1,2 V → **iletir** |

---

## 1. Hatırlatma ve hedef (slayt 2–4)

[Ders 4](../04-dijital-soyutlama/ozet.md)'ten üç fikir (slayt 2–3):

- **Değeri ayrıklaştır:** yalnızca 0 ve 1.
- **Statik disiplin:** gönderen V_OL / V_OH, alıcı V_IL / V_IH sözünü tutar; arası yasak bölgedir. Bu, **kapıların nasıl tasarlanacağını** belirler.
- **Kombinasyonel kapı:** çıkış yalnızca girişlerin fonksiyonudur. Örnek NAND (A, B → C): 00 → 1, 01 → 1, 10 → 1, 11 → 0.

Bugünkü soru: **kapı içeriden nasıl yapılır** ve gerçekten statik disiplini sağlar mı?

**Örnek devre (slayt 4): `D = ¬(¬C · ¬(A·B))`.** İki NAND ve bir evirici, yani **3 kapı**:

```
 A ──┐
     ├─ NAND ─ X ──┐
 B ──┘             ├─ NAND ── D        D = ¬(¬C·X) = A·B + C
 C ── NOT ─ ¬C ────┘
```

| A | B | C | D = A·B + C |
|---|---|---|---|
| 0 | 0 | 0 | 0 |
| 0 | 0 | 1 | 1 |
| 0 | 1 | 0 | 0 |
| 0 | 1 | 1 | 1 |
| 1 | 0 | 0 | 0 |
| 1 | 0 | 1 | 1 |
| 1 | 1 | 0 | 1 |
| 1 | 1 | 1 | 1 |

Slayt, Pentium III sınıfı bir işlemcinin 4 milyondan fazla, MIT'nin RAW çipinin yaklaşık 3 milyon kapısı olduğunu söyler. Bu sayılar **2000 dönemine** aittir; bugün işlemcilerde milyarlarca transistör vardır. Fikir aynı kalır: büyük sistem = çok sayıda **aynı tür basit kapı**.

## 2. Benzetme: su muslukları ve ampul (slayt 5–7)

**Slayt 5:** Bir su kaynağından (güç kaynağı) A ve B muslukları üzerinden bir kaba (C) su akıtılıyor. Musluklar **art arda (seri)** ise C'ye su ancak **A açık VE B açık** ise gelir: **AND**. **Slayt 6:** Musluklar **yan yana (paralel)** ise A açık **VEYA** B açık olması yeter: **OR**.

**Slayt 7 (elektrik):** Pil, A ve B anahtarları ve C lambası. Anahtarlar seri ise lamba ancak A ve B ikisi de iletirken yanar. Slaytın anahtar kelimesi: "Key: switch device".

| Düzen | Su | Elektrik | Mantık |
|---|---|---|---|
| Seri | A açık **ve** B açık → C'de su var | A ve B iletirse lamba yanar | AND |
| Paralel | A açık **veya** B açık → C'de su var | A veya B iletirse lamba yanar | OR |

> Bu benzetmede sonuç, yolun **iletip iletmediğidir**. Gerçek kapıda çıkış bir **gerilimdir**; bunu bölüm 4'te bir direnç ekleyince elde edeceksin.

## 3. Anahtar elemanı (slayt 8)

Anahtar üç uçlu bir elemandır: **in**, **out** ve **kontrol (C)**. C, in ile out arasının **kısa devre** (iletir) ya da **açık devre** (iletmez) olmasına karar verir. Mekanik anahtarda kontrol "mekanik basınçtır"; MOSFET'te **gerilimdir** (bölüm 6).

| C | in – out arası | Eşdeğeri |
|---|---|---|
| 1 | **kapalı**, kısa devre | tel |
| 0 | **açık**, açık devre | kopuk |

> ⚠️ **Slayt hatası (slayt 8):** Slaytın metni "C = 0 ise kısa devre, değilse açık devre" diyor. Slaytın şekli ve 9. slayttan itibaren **her yer** tersini kullanır: **C = 1 → kapalı**. Bu notta da C = 1 kapalıdır.

## 4. Anahtar + yük direnci = evirici (slayt 9)

Anahtarı çıkışla GND arasına koy, çıkışı da bir **yük direnci R_L** ile V_S'ye bağla:

```
      V_S  (= "1")
       │
      [R_L]
       │
       ├────── V_OUT
       │
    anahtar ◄── C (kontrol)
       │
      GND
```

| C | Anahtar | V_OUT | Neden |
|---|---|---|---|
| 0 | açık | **V_S** → "1" | Akım yok, R_L'de gerilim düşmez; çıkış V_S'ye çıkar |
| 1 | kapalı | **0 V** → "0" | Çıkış GND'ye kısa devre |

Doğruluk tablosu (slayt 9): C = 0 → V_OUT = 1; C = 1 → V_OUT = 0. Bu bir **eviricidir** (NOT).

**Okuma:** R_L çıkışı yukarı çekmeye çalışır (pull-up), anahtar aşağı çeker (pull-down). Çıkış, "yol bulan" tarafın gerilimine gider. Anahtar iletirken yol vardır ve **anahtar kazanır**.

> **Benzetme:** Çıkış bir su deposu. Üstte ince bir musluk (R_L) depoyu doldurur, altta büyük bir vana (anahtar) boşaltma yolunu açabilir. Vana yolu açarsa depo boşalır (0); kapatırsa ince musluk depoyu doldurur (1).

Bedeli: anahtar iletirken R_L üzerinden V_S'den GND'ye **sürekli akım** akar (bölüm 9 ve 10.4).

## 5. Seri, paralel ve bileşik kapılar (slayt 10–11)

İki anahtar (kontroller c1, c2) koyunca iki yeni kapı çıkar:

```
   NAND (seri)               NOR (paralel)

       V_S                        V_S
        │                          │
       [R_L]                      [R_L]
        │                          │
        ├───── OUT                 ├───── OUT
        │                    ┌─────┴─────┐
       [c1]                 [c1]        [c2]
        │                    └─────┬─────┘
       [c2]                        │
        │                         GND
       GND
```

| c1 | c2 | NAND (seri) | NOR (paralel) |
|---|---|---|---|
| 0 | 0 | 1 | 1 |
| 0 | 1 | 1 | 0 |
| 1 | 0 | 1 | 0 |
| 1 | 1 | 0 | 0 |

**Kural:** *Çıkışla GND arasında iletken bir yol varsa çıkış 0'dır; hiç yol yoksa R_L çıkışı 1'e çeker.*

- **Seri:** yol için **ikisinin de** iletmesi gerekir → ikisi 1 olunca çıkış 0 → **NAND**.
- **Paralel:** yol için **birinin** iletmesi yeter → biri 1 olunca çıkış 0 → **NOR**.

**Bileşik kapı (slayt 11): `D = ¬(A·B + C)`.** A ve B seri, bu kol C ile paralel:

```
         V_S
          │
         [R_L]
          │
          ├────── D
    ┌─────┴──────┐
   [A]          [C]
    │            │
   [B]           │
    └─────┬──────┘
          │
         GND
```

GND'ye yol: **(A ve B) veya C**; bu durumda D = 0. Yani `D = ¬(A·B + C)`. Bu bir **AOI** (AND-OR-INVERT) kapısıdır: tek kapıda üç işlev.

| A | B | C | A·B + C | D |
|---|---|---|---|---|
| 0 | 0 | 0 | 0 | 1 |
| 0 | 0 | 1 | 1 | 0 |
| 0 | 1 | 0 | 0 | 1 |
| 0 | 1 | 1 | 1 | 0 |
| 1 | 0 | 0 | 0 | 1 |
| 1 | 0 | 1 | 1 | 0 |
| 1 | 1 | 0 | 1 | 0 |
| 1 | 1 | 1 | 1 | 0 |

> **Neden hep NAND, NOR, AOI?** Anahtarlar çıkışı **aşağı** çeker; yol varsa çıkış 0 olur. Bu yüzden bu yapıda her kapı doğal olarak **terslemelidir**. AND ve OR istersen sonuna bir evirici eklersin. Slayt 4'teki `A·B + C` işlevi 3 kapıyla (NAND, NOT, NAND) yapılmıştı; bileşik kapı + evirici ile **2 kapıda** da çıkar. Bileşik kapı eleman sayısını azaltır.

## 6. MOSFET ve anahtar modeli (slayt 12–14)

Anahtarın elektronik hâli **MOSFET**'tir (Metal-Oxide-Semiconductor Field-Effect Transistor). Üç uçlu, toplu bir elemandır:

| Uç | Adı | Görevi |
|---|---|---|
| **G** | Gate (kapı) | Kontrol ucu |
| **D** | Drain (savak) | Anahtarın bir ucu |
| **S** | Source (kaynak) | Anahtarın öbür ucu |

Bizim amaçlarımız için D ve S **simetrik** davranır (slayt 12). Gate yalıtkandır: DC'de gate akımı `i_G ≈ 0`; kontrol bir **gerilimdir**. Elemanı iki kapılı gibi gör (slayt 13): kontrol tarafı `v_GS`, anahtar tarafı `v_DS` ve `i_DS`.

**Anahtar modeli (S modeli):**

| Koşul | Durum | D–S arası |
|---|---|---|
| `v_GS < V_T` | kapalı (off) | açık devre: `i_DS = 0` |
| `v_GS ≥ V_T` | iletir (on) | kısa devre: `v_DS = 0` |

`V_T` **eşik gerilimidir**; slayta göre tipik ≈ **1 V**.

**Slayt 14 (osiloskop demosu)** MOSFET'in `i_DS – v_DS` eğrisini gösterir. S modelinde iletirken eğri `v_DS = 0` çizgisidir (dikey), kapalıyken yatay eksendir (`i_DS = 0`); bölüm 9'daki SR modeli bunu gerçeğe yaklaştırır.

> **Slaytta olmayan not:** Gerçek MOSFET'in eğrileri `v_DS` büyüdükçe doyuma gider (akım sabitlenir); S ve SR modelleri bu bölgeyi yok sayar. Dijital anahtarlamada MOSFET ya tam kapalıdır ya da küçük `v_DS` ile iletir; doyum bölgesi yükselteç derslerinin konusudur.

## 7. MOSFET evirici (slayt 15)

Bölüm 4'teki anahtar yerine MOSFET koy: G = giriş, D = çıkış düğümü, S = GND.

```
       V_S = 5 V
         │
        [R_L]
         │
         ├────── v_OUT   (B)
         │ D
 v_IN ───┤G   N-MOSFET
 (A)     │ S
        GND
```

| v_IN (A) | MOSFET (S modeli) | v_OUT (B) |
|---|---|---|
| 0 ≤ v_IN < V_T (≈ 1 V) | kapalı | **5 V** → "1" |
| v_IN ≥ V_T | iletir | **0 V** → "0" |

> **Soyutlamanın gücü (slayt 15):** Eviricinin sembolü (`A → B`) iç ayrıntıları gizler: besleme bağlantısı, R_L, GND. Dijital devre çizerken **besleme ve toprak tüm kapılarda ortaktır**, her kapıya tek tek çizilmez. Çoğu EDA kütüphanesinde 74HC00 gibi bir IC'nin dört kapısı ayrı semboller, V_CC ve GND ise ayrı bir **güç birimi** olarak bu yüzden çizilir.

## 8. Statik disiplin kontrolü: T1000 örneği (slayt 16–17)

**Soru (slayt 16):** "T1000 model dizüstü bilgisayar" statik disipline uyan kapılar istiyor. Eviricimiz (V_S = 5 V, V_T = 1 V, S modeli) verilen eşikleri sağlar mı?

**Koşulları çıkaralım.**

- Giriş geçerli **alçaksa** (`v_IN ≤ V_IL`) MOSFET **kapalı** olmalı: `V_IL < V_T`. Çıkış `V_S` olur ve `V_OH`'dan az olmamalı: `V_OH ≤ V_S`.
- Giriş geçerli **yüksekse** (`v_IN ≥ V_IH`) MOSFET **iletmeli**: `V_IH ≥ V_T`. S modelinde çıkış 0 V olur ve `V_OL`'dan fazla olmamalı: `V_OL ≥ 0`.

Birlikte: **`V_IL < V_T ≤ V_IH`**, **`V_OH ≤ V_S`**, **`V_OL ≥ 0`** (ve her zamanki sıra `V_OL < V_IL < V_IH < V_OH`).

| Eşik seti (V) | V_IL < V_T ≤ V_IH | V_OH ≤ V_S | V_OL ≥ 0 | Sonuç | NM_H / NM_L |
|---|---|---|---|---|---|
| **T1000** (slayt 16): V_OL 0,5 · V_OH 4,5 · V_IL 0,9 · V_IH 4,1 | 0,9 < 1 ≤ 4,1 ✓ | 4,5 ≤ 5 ✓ | ✓ | ✓ **sağlar** | 0,4 / 0,4 V |
| Slayt 17 (üst): V_OL 0,2 · V_OH 4,8 · V_IL 0,5 · V_IH 4,5 | 0,5 < 1 ≤ 4,5 ✓ | 4,8 ≤ 5 ✓ | ✓ | ✓ **sağlar** | 0,3 / 0,3 V |
| Slayt 17 (alt): V_OL 0,5 · V_OH 4,5 · V_IL 1,5 · V_IH 3,5 | 1,5 < 1 ✗ | ✓ | ✓ | ✗ **sağlamaz** | 1,0 / 1,0 V |

> **Dikkat:** Üçüncü satırın marjları en büyük olduğu hâlde kapı **sözünü tutamaz**. Alıcı 1,2 V'u geçerli "0" saymaya razıdır (`V_IL = 1,5 V`), oysa bizim MOSFET 1 V'ta iletmeye başlar ve çıkışı 0'a çeker. **Marj, eşiklerin bir özelliğidir; kapının o eşikleri gerçekten sağlayıp sağlamadığı ayrı bir sorudur.**

S modeli çıkışı tam 0 V ve tam V_S verir; gerçek devrede bu böyle değildir. Bunun nedeni R_ON'dur (bölüm 9).

## 9. SR modeli ve yük direnci seçimi (slayt 18–20)

**Sorun:** S modeli iletirken direnci tam sıfır, kapalıyken sonsuz sayar. Daha gerçekçi **SR modeli (switch-resistor)** iletirken anahtara **seri bir R_ON** koyar (slayttaki örnek: R_ON = 5 kΩ). Kapalıyken hâlâ açık devredir.

```
 i_DS                                i_DS
  │ ┃  v_GS ≥ V_T                     │       ╱  v_GS ≥ V_T
  │ ┃  (v_DS = 0)                     │     ╱    eğim = 1/R_ON
  │ ┃                                 │   ╱
  └─┸────────────── v_DS              └─╱────────────── v_DS
       S modeli                           SR modeli
 (v_GS < V_T: iki modelde de yatay eksen, i_DS = 0)
```

SR modelinde iletirken `i_DS = v_DS / R_ON` (Ohm yasası); örneğin R_ON = 5 kΩ ve v_DS = 0,25 V ise i_DS = 50 µA.

**Evirici yeniden (slayt 20):** Anahtar iletirken R_L ve R_ON gerilim bölücü olur:

```
V_OUT(düşük) = V_S · R_ON / (R_ON + R_L)        ve bu  ≤ V_OL  olmalı
        ⇒   R_L ≥ R_ON · (V_S − V_OL) / V_OL
```

**Örnek:** R_ON = 5 kΩ, V_S = 5 V, V_OL = 0,5 V → `R_L ≥ 5 kΩ × 4,5 / 0,5 =` **45 kΩ**.

**R_L'yi seçmenin bedeli** (R_ON = 5 kΩ, V_S = 5 V):

| R_L | V_OUT (düşük) | Akım I | Güç P = V_S·I | Not |
|---|---|---|---|---|
| 10 kΩ | 1,67 V | 0,333 mA | 1,67 mW | V_OL = 0,5 V sınırını **aşar** ✗ |
| 20 kΩ | 1,00 V | 0,200 mA | 1,00 mW | Yine aşar ✗ |
| **45 kΩ** | **0,50 V** | **0,100 mA** | **0,50 mW** | Tam sınırda ✓ (R_L'de 0,45 mW, MOSFET'te 0,05 mW) |
| 95 kΩ | 0,25 V | 0,050 mA | 0,25 mW | Marj var ✓ |
| 495 kΩ | 0,05 V | 0,010 mA | 0,05 mW | Güç çok düşük, ama kenar çok yavaş (aşağıda) |

- **R_L küçük:** V_OL kötüleşir (alt sınır) ve statik güç artar.
- **R_L büyük:** güç düşer ama çıkış "1"e **yavaş** çıkar: `t_r(10–90 %) ≈ 2,2·R_L·C_L`. 45 kΩ ve 10 pF yük için ≈ 1 µs.
- **Statik güç:** Düşük durumdaki her kapı 0,5 mW çeker. Bir milyon kapı düşükteyse `10⁶ × 0,5 mW =` **500 W** (slaytta yok; bizim hesabımız). Modern kapılar (CMOS) bu yüzden yük direnci yerine **tamamlayıcı bir üst transistör** kullanır; durağan durumda neredeyse akım çekmezler. Bu dersin kapsamı dışında, ama motivasyonu budur.

## 10. 💼 İş yerinde: açık-drenaj, pull-up ve gerçek MOSFET

### 10.1 Bu evirici gerçekte ne?

Bölüm 4–9'daki devre (MOSFET alta, direnç üstte) bir **açık-drenaj (open-drain)** çıkıştır; transistör bipolar ise **açık-kolektör**. İçeride yalnızca çıkışı **aşağı çeken** transistör vardır; "1" seviyesini üreten R_L **dışarıdadır** ve adı **pull-up**'tır. Kitaptaki R_L, şemandaki pull-up direncidir.

### 10.2 Pull-up değeri: iki sınır

Alt sınır, bölüm 9'daki formülün datasheet diliyle yazılmışıdır. Datasheet R_ON yerine **V_OL(max) ve I_OL** verir; `V_OL = I_OL·R_ON` olduğundan:

```
R_min = R_ON · (V_DD − V_OL) / V_OL  =  (V_DD − V_OL) / I_OL
```

| V_DD | V_OL(max) | I_OL | R_min | Nerede |
|---|---|---|---|---|
| 3,3 V | 0,4 V | 3 mA | `2,9 V / 3 mA =` **967 Ω** (R_ON eşdeğeri ≈ 133 Ω) | I²C |
| 5 V | 0,4 V | 4 mA (varsayım) | `4,6 V / 4 mA =` **1,15 kΩ** | Örnek hat |

Üst sınır **yükselme süresinden** gelir: I²C için `R_max = t_r / (0,8473·C_b)` ([Direnç dersi, 5.1](../../Komponentler/01-direnc/ozet.md#51-pull-up--pull-down): 400 kHz, 200 pF → 1,77 kΩ). Yani pull-up, **alt sınır (V_OL ve sink akımı)** ile **üst sınır (hız)** arasında seçilir; aralık yoksa hat kapasitansını veya hızı düşür. Hatta **tek set** pull-up olsun: paralel setler direnci `R_min`'in altına çeker.

### 10.3 Kablolu-AND (wired-AND)

Birden çok açık-drenaj çıkış aynı hatta bağlanırsa bölüm 5'teki **paralel anahtarlar** olur: **en az biri** hattı çekerse hat 0'dır; hiçbiri çekmiyorsa pull-up 1 yapar. Aynı hatta çok cihazın güvenle konuşabilmesinin (I²C'de çok-master, clock stretching, ortak interrupt hattı) sebebi budur: iki çıkış **birbirine zıt sürülse bile kısa devre olmaz**; çekmeyen taraf zaten yüksek empedanstadır.

### 10.4 Statik güç ve hız dengesi

- Hat düşükken pull-up'tan **sürekli akım** akar: `I = V_DD / R`. 3,3 V ve 10 kΩ → 0,33 mA; sürekli düşük tutulan bir hat pilli üründe günde `24 h × 0,33 mA ≈` **7,9 mAh** harcar.
- `R` büyütülürse güç düşer, ama `t_r ≈ 2,2·R·C` büyür ve hat gürültüye daha açık olur (yüksek empedanslı "1").
- Pilli üründe uzun süre düşük kalan hatlara pull-up akımını **güç bütçesine** yaz.

### 10.5 Gerçek MOSFET, S modeli değildir

- **V_GS(th) yalnızca iletimin başlangıcıdır.** Slayttaki "v_GS ≥ V_T → kısa devre" bir idealleştirmedir. Datasheet R_DS(on)'u belirli bir V_GS'te verir (2,5 V, 3,3 V, 4,5 V veya 10 V); anahtarı o gerilimde sür. 3,3 V'luk bir MCU için **logic-level** MOSFET seç ([MOSFET dersi, bölüm 3](../../Konular/mosfet-transistor-ve-yuk-surme/ozet.md#3-n-mosfet-seçimi)).
- **R_ON her yerde 5 kΩ değildir.** Slayttaki sayı bir çip içindeki küçük transistör içindir. Küçük sinyal MOSFET'lerinde R_DS(on) Ω mertebesinde, güç MOSFET'lerinde mΩ mertebesindedir.
- **D–S tam simetrik değildir.** Güç MOSFET'lerinde **gövde diyotu** (body diode) ters yönde iletir; ters polarite koruması ve high-side anahtarlamada yön ve diyot hesaba katılır.
- **Gate yalıtkan ama kapasitiftir:** DC'de i_G ≈ 0, ama açıp kapatırken gate şarj/deşarj akımı gerekir; gate'e seri direnç ve pull-down bu yüzden vardır ([MOSFET dersi, bölüm 4](../../Konular/mosfet-transistor-ve-yuk-surme/ozet.md#4-gate-direnci-ve-pull-down)).

### 10.6 MCU pini açık-drenaj modunda

Çoğu MCU'da bir GPIO "açık-drenaj çıkış" moduna alınabilir: **0 yazmak** alt MOSFET'i açar (hat alçak), **1 yazmak** onu kapatır (hat yüksek empedans, yükselmeyi pull-up yapar). 5 V toleranslı (FT) pinler açık-drenaj modunda 5 V'a pull-up kabul edebilir ([MCU dersi, bölüm 6](../../Komponentler/05-mikrodenetleyici-donanimi/ozet.md#6-gpio)); bu, tek hat için basit bir seviye çevirmedir, ama "1" seviyesi `R·C` ile **yavaş** yükselir. Pinin tolerans tablosunu datasheet'ten doğrula.

### 10.7 Nerede göreceksin?

| Yer | Açık-drenaj / kolektör ne iş yapıyor? | Kontrol |
|---|---|---|
| I²C (SDA, SCL) | Çok cihaz tek hatta; hat = kablolu-AND | `R_min` ve `R_max`, tek set pull-up ([Haberleşme dersi, I²C](../../Konular/haberlesme-arayuzleri/ozet.md#4-ic)) |
| Alarm, arıza, interrupt, reset hatları (ürünündeki parçalar açık-kolektör / açık-drenaj çıkış veriyorsa) | Birden çok kaynak tek hatta; hat, en az biri çekerse alçak | Pull-up değeri, V_OL ve sink akımı; hat boşta kalmasın |
| Röle / valf sürücüleri (ULN2003 gibi açık-kolektör diziler) | Sürücü yükü GND'ye çeker; yük beslemesi dışarıda | Sink akımı, flyback diyotu ([MOSFET dersi](../../Konular/mosfet-transistor-ve-yuk-surme/ozet.md)) |
| 3,3 V ↔ 5 V seviye çevirme (BSS138 tipi) | MOSFET + iki pull-up | [Haberleşme dersi, bölüm 6](../../Konular/haberlesme-arayuzleri/ozet.md#6-seviye-çevirme-33-v--5-v) |

## 11. Şematikte

- Açık-drenaj / açık-kolektör hatların yanında **pull-up değeri ve hangi rayda olduğu** yazılı; I²C gibi hatlarda **tek set** pull-up var.
- Kendi tasarladığın MOSFET anahtarlarda gate pull-down ve seri direnç var; MOSFET'in R_DS(on)'u **kullandığın V_GS'te** belirtilmiş.
- Çok kapılı IC'lerde (ör. 74HC00) kullanılmayan kapıların girişleri tanımlı seviyeye bağlı ([Ders 4, 8.4](../04-dijital-soyutlama/ozet.md)); güç birimi (V_CC, GND ve dekuplaj) çizilmiş.

## 12. PCB / layout

- Pull-up dirençlerini hattın **alıcı tarafında, tek noktada** topla; her modülde ayrı pull-up bırakma.
- Açık-drenaj hatları (yavaş yükselen kenar) hızlı anahtarlamalı hatlardan ve regülatörlerden uzak tut; yüksek empedanslı "1" kuplajı kolay yakalar.
- MOSFET'in gate direnci ve pull-down'ı gate pinine **yakın** olsun; akım döngüsü (drain–source–GND) kısa kalsın.

## 13. EMC açısından

- Pull-up'tan yükselen kenar yavaştır (`R·C`): kenar kaynaklı yayılım küçüktür, ama **"1" seviyesi yüksek empedanslıdır** ve gürültüyü kolay kapar. Uzun kabloda `R`'yi alt sınıra yakın seç ve girişte küçük RC/histerezis kullan ([Ders 4, 8.5](../04-dijital-soyutlama/ozet.md)).
- "0" seviyesi düşük empedanslıdır (transistör çekiyor): gürültüye daha dayanıklıdır. Açık-drenaj hatlarda aktif seviyenin **düşük** olması (`nINT`, `nRESET`) hem kablolu-AND'e uyar hem de aktif durumu düşük empedanslı, yani gürültüye daha dayanıklı yapar.

## 14. Ölçüm ve doğrulama

1. **V_OL kontrolü:** Hattı düşük tutup V_OL'yi ölç. Datasheet'in `V_OL(max)` değerinin üstündeyse pull-up çok küçük (sink akımı aşılıyor) ya da hatta fazladan pull-up seti var.
2. **Yükselme süresi:** Osiloskopta kenarı ölç ve **hat kapasitansını** çıkar. %10–%90 ölçtüysen `C ≈ t_r / (2,2·R)`; I²C'deki gibi %30–%70 ölçtüysen `C ≈ t_r / (0,8473·R)`. Beklenenden çok büyükse kablo/modül sayısını düşür.
3. **Pull-up akımı:** Hat düşükken `V_DD / R_eş`; pil bütçesiyle karşılaştır.
4. **Paralel pull-up taraması:** Hattaki tüm modüllerin pull-up'larını listele; eşdeğer paralel direnç `R_min`'in üstünde mi?

## 15. Kendin dene

1. R_ON = 2 kΩ, V_S = 3,3 V, V_OL(max) = 0,4 V. R_L en az kaç kΩ olmalı?
2. R_ON = 5 kΩ, R_L = 45 kΩ, V_S = 5 V. Düşük durumda I ve P kaç? 10 000 kapı aynı anda düşükse toplam güç kaç W?
3. Slayt 11'deki `D = ¬(A·B + C)` kapısında A = 1, B = 0, C = 0 iken D kaçtır?
4. V_S = 5 V, V_T = 1 V. Eşik seti (V_OL 0,3 · V_OH 4,7 · V_IL 1,2 · V_IH 4,2) statik disipline uyar mı? Neden?
5. Açık-drenaj bir I²C hattında V_DD = 3,3 V, V_OL(max) = 0,4 V, I_OL = 3 mA. R_min kaç Ω? Hatta iki modülün 1,5 kΩ'luk pull-up'ı paralel bağlıysa sonuç ne olur?
6. Pull-up 10 kΩ, hat kapasitansı 100 pF. Kenarın 10–90 % yükselme süresi yaklaşık kaç µs?

<details>
<summary>Cevaplar</summary>

1. `R_L ≥ 2 kΩ × (3,3 − 0,4) / 0,4 = 2 kΩ × 7,25 =` **14,5 kΩ**
2. `I = 5 V / 50 kΩ =` **0,1 mA**; `P = 5 V × 0,1 mA =` **0,5 mW**; `10 000 × 0,5 mW =` **5 W**
3. A·B = 0 ve C = 0 → GND'ye yol yok → `D =` **1**
4. **Uymaz:** `V_IL = 1,2 V > V_T = 1 V`. 1,2 V'luk "geçerli 0" girişinde MOSFET iletir ve çıkışı 0'a çeker, oysa çıkışın "1" olması gerekirdi. (Diğer koşullar sağlanıyor: 4,7 ≤ 5, 0,3 ≥ 0.)
5. `R_min = (3,3 − 0,4) V / 3 mA =` **967 Ω**. İki 1,5 kΩ paralel = **750 Ω** < 967 Ω → hat `R_min`'in altına düşer, V_OL 0,4 V'u aşabilir ve sink akımı sınırı zorlanır; hatta tek set pull-up bırak.
6. `t_r ≈ 2,2 × 10 kΩ × 100 pF = 2,2 µs`

</details>

## 16. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| Slayt 8'in "C = 0 → kısa devre" metnini ezberlemek | Şekil ve sonraki slaytlarla çelişir | C = 1 → kapalı (iletir) |
| Açık-drenaj hatta pull-up koymamak | "1" seviyesini kimse üretmez, hat boşta kalır | `R_min ≤ R ≤ R_max` aralığında pull-up |
| Birden çok modülde ayrı pull-up bırakmak | Paralel direnç `R_min`'in altına düşer; V_OL yükselir | Hatta tek set pull-up; eşdeğeri hesapla |
| Pull-up'ı çok büyük seçmek | Kenar yavaş (`≈ 2,2·R·C`), hat gürültüye açık | `R_max` sınırı; osiloskopla ölç |
| Statik disiplinde yalnızca marja bakmak | Marj büyük olsa da kapı eşiği tutturamayabilir (`V_IL > V_T`) | `V_IL < V_T ≤ V_IH` kontrolü |
| MOSFET'i `V_GS(th)`'de "tam açık" saymak | `V_GS(th)` iletimin yalnızca başlangıcıdır; `R_DS(on)` o gerilimde büyüktür | `R_DS(on)`'un belirtildiği V_GS'te sür (logic-level) |
| D–S'yi her yönde simetrik sanmak (güç MOSFET'i) | Gövde diyotu ters yönde iletir | Yönü ve diyotu hesaba kat |
| Yük dirençli yapının statik akım çekmediğini varsaymak | Düşük durumda sürekli akım akar | Pull-up akımını güç bütçesine yaz |

## 17. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Anahtar (switch)** | Kontrol girişiyle in–out arasını kısa/açık devre yapan üç uçlu eleman |
| **Yük direnci R_L / pull-up** | Çıkışı V_S'ye çeken direnç |
| **Pull-down** | Çıkışı GND'ye çeken direnç veya anahtar |
| **Evirici (NOT)** | Anahtar + yük direnci; girişin tersini verir |
| **NAND / NOR** | Seri / paralel anahtarlı kapı; `¬(A·B)` / `¬(A+B)` |
| **Bileşik kapı / AOI** | Seri-paralel karışımı kapı; `¬(A·B + C)` |
| **MOSFET** | Gerilimle kontrol edilen anahtar (G, D, S uçlu) |
| **V_T / V_GS(th)** | MOSFET'in iletmeye başladığı eşik gerilimi |
| **S modeli** | `v_GS ≥ V_T` → kısa devre, aksi halde açık devre |
| **SR modeli** | İletirken seri R_ON bulunan anahtar modeli |
| **R_ON / R_DS(on)** | İletim durumundaki D–S direnci |
| **Açık-drenaj / açık-kolektör** | Yalnızca aşağı çeken çıkış; "1"i harici pull-up üretir |
| **Kablolu-AND (wired-AND)** | Açık-drenaj çıkışları aynı hatta bağlayınca "en az biri çekerse 0" davranışı |
| **Gövde diyotu (body diode)** | Güç MOSFET'inin D–S arasındaki iç diyodu |
| **CMOS** | Tamamlayıcı MOSFET'lerle yapılan kapı; durağan durumda neredeyse akım çekmez |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki madde [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.6, bölüm 7; ilk iki madde [Ders 4](../04-dijital-soyutlama/ozet.md)'te):

- [x] Açık-drenaj / açık-kolektör hatlarda (I²C, alarm, interrupt, kablolu-AND) pull-up, alt sınır (`R ≥ (V_DD − V_OL) / I_OL`) ile yükselme süresinden gelen üst sınır arasında seçildi; hatta tek set pull-up var

## Kontrol soruları

→ [quiz.md](quiz.md) · 12 soru, 6'sı hesap
