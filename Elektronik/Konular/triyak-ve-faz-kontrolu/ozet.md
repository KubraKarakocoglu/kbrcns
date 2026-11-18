# Triyak ve faz kontrolü (dimmer)

- **Oluşturma:** 2026-11-18
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Kod:** [kod/dim_faz.c](kod/dim_faz.c) (derlenebilir, testli) · [kod/dim_faz.h](kod/dim_faz.h) · [kod/test_dim_faz.c](kod/test_dim_faz.c)
- **Bağlantılı:** [Şebeke güvenliği ve yalıtım](../sebeke-guvenligi-ve-yalitim/ozet.md) · [MOSFET, transistör ve yük sürme](../mosfet-transistor-ve-yuk-surme/ozet.md) · [Güç katı: koruma ve regülatör](../guc-kati-koruma-ve-regulator/ozet.md) · [Direnç](../../Komponentler/01-direnc/ozet.md) · [Kapasitör](../../Komponentler/02-kapasitor/ozet.md) · [Bobin](../../Komponentler/03-bobin-induktor/ozet.md) · [EMC için kart tasarımı](../../EMC/02-emc-icin-kart-tasarimi/ozet.md) · [EMC testleri ve standartlar](../../EMC/03-emc-testleri-ve-standartlar/ozet.md) · Sonraki: Şebekeli güç kaynakları (Ders 3, hazırlanıyor)

> Sayısal değerler **tipik başlangıç noktalarıdır**. Triyak sayıları WeEn **BT138Y-600E** (E serisi, 4 kadranlı, hassas kapılı) datasheet'inden, optotriyak sayıları onsemi **MOC3023M** ve **MOC3051M/52M/53M** datasheet'lerinden alındı ve hesaplar betikle yeniden yapıldı. **Kendi parçanın datasheet'i esastır.** Dimmer bir şebeke ürünüdür; ürün standardı (EN 60669-2-1) ve EMC standartları (EN 55015, EN 61000-3-2, EN 61000-3-3) ücretlidir ve bu notlarda yoktur. Bu ders hesabı ve doğru soruları öğretir; sertifikasyonun yerine geçmez.
>
> **Uyarı:** Triyak devresi doğrudan şebekededir. Enerjilendirmeden önce [Şebeke güvenliği dersinin](../sebeke-guvenligi-ve-yalitim/ozet.md) bölüm 14'ünü oku. **İki telli bir dimmerin elektroniği şebeke potansiyelinde yüzer**; bilgisayara, debugger'a ya da osiloskop toprağına izolasyonsuz bağlanmaz.
>
> **Okuma planı:** 1. oturum: bölüm 1–3 (neden, triyak, matematik) · 2. oturum: 4–7 (yükler, tetik devresi, sıfır geçiş, yazılım) · 3. oturum: 8–15.

---

## ⚡ Hızlı tekrar

1. Triyak, şebekede bir **AC anahtardır**: kapıdan **bir kez tetiklenir**, akım **tutma akımının (I_H) altına** düşünce kendiliğinden söner (şebekede her yarım periyodun sonunda). Gücü **tetik gecikmesi** belirler; buna **faz kontrolü** denir.
2. Direnç yükte güç oranı: `P/P_max = 1 − α/π + sin(2α)/(2π)`. **90°'de %50**, 60°'de %80,4, 120°'de %19,6. Doğrusal değildir: ortada hızlı, uçlarda yavaş değişir.
3. 50 Hz'de `t_α = α/180° × 10 ms` (90° = 5 ms); 60 Hz'de yarım periyot 8,33 ms'dir.
4. Optotriyakla sürülen kapı **QI ve QIII**'te çalışır (en hassas, I_GT ≤ 10 mA). **QIV** en az hassastır (I_GT ≤ 25 mA, dI/dt 10 A/µs).
5. Küçük yükte iki eşik belirleyicidir: tetik sonrası akım **I_L'yi (≈ 30–40 mA)** aşmalı, sonra **I_H'nin (≈ 30 mA)** altına düşmemeli. 5 W'lık bir LED lamba yalnız **≈ 22 mA** çeker: sorun burada başlar.
6. **Snubber** triyakı dV/dt'den korur ama kapalıyken **kaçak akım** akıtır (`I = 2π·f·C·V`): 100 nF → 7,2 mA. Akkor lambada görünmez, LED lambada **hayalet parlama** yapar.
7. Faz kontrolünde **rastgele faz (non-zero-cross)** optotriyak kullan (MOC302x, MOC305x). Sıfır geçişli tip yalnız aç-kapa içindir. Kapı direnci `R_g ≥ V_tepe / I_TSM` → 373 Ω → **390 Ω**.
8. Sıfır geçiş darbesinin **yükselen kenarı gerçek geçişten t_w önce** gelir (örnekte 0,65 ms). Tetik gecikmesi `t_w + t_α`; darbe genişliğini ölç ve hesaba kat.
9. Güç → açı eşlemesinde **ileri tablo** (açı eşit aralıklı, güç saklı) ters tabloya göre **≈ 15× daha doğrudur** (N = 32: %0,08'e karşı %1,18).
10. Fail-safe: **sıfır geçiş yoksa tetik yok**; kapı darbesi donanım zamanlayıcıyla **sabit genişlikte**; açılışta ve watchdog sonrası **kapalı başla**; geçersiz giriş → kapalı.

## 🧮 Formül kartı

| Formül | Ne zaman kullanılır | Örnek |
|---|---|---|
| `P/P_max = 1 − α/π + sin(2α)/(2π)` | Faz kontrolünde güç oranı (direnç yük) | α = 90° → **0,50** |
| `V_yük = V_hat · √(P/P_max)` | Yük gerilimi (rms) | 90° → **162,6 V** |
| `t_α = (α/π) · T_yarım` | Tetik gecikmesi | 90°, 50 Hz → **5,00 ms** |
| `PF = √(P/P_max)` | Direnç yükte güç faktörü | 90° → **0,707** |
| `t_gecikme = t_w + t_α`, `t_w = darbe/2` | ZC darbesinin yükselen kenarından tetiğe süre | 0,65 + 5,00 = **5,65 ms** |
| `R_g ≥ V_tepe / I_TSM` | Optotriyak çıkışı kapı direnci | 373 V / 1 A → 373 Ω → **390 Ω** |
| `R_LED = (V_MCU − V_F) / I_F` | Opto LED direnci | (3,3 − 1,5) / 10 mA = **180 Ω** |
| `I_snub = 2π·f·C·V` | Snubber kaçak akımı | 47 nF, 230 V, 50 Hz → **3,40 mA** |
| `V_hayalet = I_kaçak · R_yük` | Kapalı dimmerde LED lambanın gördüğü gerilim | 3,40 mA × 10,6 kΩ = **36 V** |
| `P_R,snub ≤ 2·C·V_tepe²·f` | Snubber direncinin güç üst sınırı | 47 nF → **0,50 W** |
| `P_triyak ≈ V_TO·I_ort + R_d·I_rms²` | Triyak kaybı | 400 W → **1,65 W** |
| `R_th,maks = (T_j − T_a) / P_triyak` | Soğutucu ihtiyacı | (110 − 50) / 1,65 = **36 K/W** |
| `dI/dt = V / L` | Seri indüktansın akım artışını sınırlaması | 325 V / 1 mH = **0,33 A/µs** |
| `Z₀ = √(L/C)`, `f₀ = 1/(2π√(LC))` | Seri L ile snubber C'nin rezonansı | 1 mH, 100 nF → **100 Ω**, **15,9 kHz** |

---

## 1. Neden faz kontrolü?

Şebekenin gücünü ayarlamanın en kolay yolu enerjiyi **zamanla dilimlemektir**. Elindeki muslukta düşün: musluk saniyede 100 kez (50 Hz'de her yarım periyotta) **kendiliğinden kapanıyor**. Sen yalnızca **her seferinde ne zaman açacağını** seçersin. Erken açarsan çok su, geç açarsan az su geçer. Açtıktan sonra kapatamazsın: musluk, akış sıfıra inene kadar açık kalır. Triyak tam böyle bir muslukla aynıdır.

| Yöntem | Nasıl çalışır | Artı | Eksi | Tipik yük |
|---|---|---|---|---|
| Seri direnç / Variac | Gerilimi düşürür | Gürültüsüz | Isı (direnç) veya boyut ve maliyet (Variac) | Laboratuvar |
| **Faz kontrolü, ileri kenar** (triyak) | Yarım periyotta geç tetikler | Ucuz, basit; kayıp %1'in altında | Geniş bantlı EMI, harmonik, düşük güç faktörü | Akkor, halojen, ısıtıcı; özel "triyak uyumlu" LED lamba |
| **Faz kontrolü, geri kenar** (MOSFET) | Sıfır geçişte açar, geç keser | Kapasitif yükte sessiz, daha az EMI | Pahalı; genelde nötr ister | LED, elektronik trafo (ELV) |
| **Tam periyot (burst) kontrolü** | Tüm yarım periyotları sıfır geçişte açar-kapar | Neredeyse EMI yok | Işıkta titreme; yalnız ısıl ataletli yükte | Isıtıcı, fırın |
| Röle / SSR aç-kapa | Ya tam ya hiç | Basit | Dimleme yok | Genel anahtarlama |

Triyakın verimi yüksektir: iletimde üzerinde yalnızca ≈ 1,4 V düşer; 400 W'lık yükte kayıp **1,65 W (%0,4)** olur (bölüm 8).

## 2. Triyak: ne yapar, nasıl tutulur?

### 2.1 Üç bacak, iki yön

Triyak, birbirine ters bağlı iki tristörün tek gövdede birleşmesidir. **MT1** ve **MT2** ana uçlardır, **G** kapıdır. İki yönde de akım taşır. Kapıya küçük bir akım darbesi verince açılır.

**Gaz ocağı benzetmesi:** Kibriti (kapı akımı) bir an tutarsın; alev tutununca kibriti çekersin, ocak **gaz (akım) bitene kadar** yanar. Kibriti geç yakmakla alevi söndüremezsin; ancak gazı kesersin.

| Geçiş | Koşul |
|---|---|
| KAPALI → AÇIK | Kapı akımı ≥ **I_GT** ve ana akım, kapı darbesi bitmeden **I_L**'yi (mandallama) aşar |
| AÇIK → KAPALI | Ana akım **I_H**'nin (tutma) altına düşer; şebekede bu her yarım periyodun sonunda, sıfır geçişte olur |

Bu yüzden açmak kolaydır (kapı), kapatmak elinde değildir (akım sıfırı bekler). Gücü, "**ne zaman açtığın**" belirler.

### 2.2 Dört kadran

Kadran, MT2 ve kapının MT1'e göre polaritesidir. Aynı triyak her kadranda aynı hassasiyette değildir (WeEn BT138Y-600E, 25 °C):

| Kadran | MT2 | Kapı | I_GT (maks) | I_L (maks) | Not |
|---|---|---|---|---|---|
| QI | + | + | 10 mA | 30 mA | En hassas |
| QII | + | − | 10 mA | 40 mA | |
| QIII | − | − | 10 mA | 30 mA | |
| QIV | − | + | **25 mA** | 40 mA | **En az hassas**; dI/dt sınırı 10 A/µs (diğerleri 50 A/µs) |

Optotriyak kapıyı **MT2 ile aynı polaritede** sürer (MT2 + iken kapı +, MT2 − iken kapı −): çalışma **QI ve QIII**'te olur. QIV'e güvenme.

### 2.3 Datasheet parametreleri

| Parametre | Değer (BT138Y-600E) | Ne için bakılır |
|---|---|---|
| **V_DRM** | 600 V | 264 V hatta tepe 373 V; darbe marjı için ≥ 1,6× |
| **I_T(RMS)** | 12 A (T_mb ≤ 85 °C) | Sürekli akım; asıl sınır **ısıl**dır (bölüm 8) |
| **I_TSM** | 95 A (20 ms), 105 A (16,7 ms) | Soğuk lamba akımı, kısa devre darbesi |
| **I²t** | 45 A²s | Sigorta koordinasyonu |
| **dI_T/dt** | 50 A/µs (QI–QIII), 10 A/µs (QIV) | Açılırken akım artış hızı (I_G = 100 mA) |
| **I_GT** | ≤ 10 mA (QI–QIII), ≤ 25 mA (QIV) | Kapı sürme |
| **I_L** / **I_H** | ≤ 30–40 mA / ≤ 30 mA | Küçük yükte tutunma (bölüm 2.4) |
| **V_T** | 1,4 V tipik, ≤ 1,65 V (15 A) | İletim kaybı |
| **dV_D/dt** | 50 V/µs tipik (T_j = 125 °C, 67 % V_DRM, kapı açık) | Kapalıyken kendiliğinden tetiklenmeme |
| **T_j,maks** | 125 °C | Isıl sınır |
| **R_th(j-mb)** / **R_th(j-a)** | 2,3 K/W (yalıtımlı gövde, tam periyot) / 60 K/W (serbest hava, tipik) | Isıl hesap |
| **V_isol** | 2500 V_rms (yalıtımlı gövde, bacaklar–soğutucu) | Soğutucuya yalıtım |

> **Dikkat:** Yalıtımlı gövdenin 2500 V_rms değeri **soğutucuya** yalıtımdır. Ders 1'deki güçlendirilmiş bariyer testi **3000 Vac**'tir; 2500 V_rms bunu karşılamaz. Dokunulabilir bir soğutucu için ürün standardına bak. Ayrıca TO-220AB gövdelerde **metal sekme genellikle MT2'ye bağlıdır** (hat potansiyeli): datasheet'te kontrol et.

**Seçim kuralları:**
- **V_DRM ≥ 600 V** (230 V şebeke). 400 V'luk parça 373 V tepeyle %93 yüklenir, marj yoktur.
- **I_TSM**, soğuk lamba akımının (bölüm 4.1) **en az 2 katı** olmalı.
- **I_T(RMS)** değil, **T_j hesabı** belirleyicidir; önce ısıl hesabı yap.

### 2.4 Mandallama ve tutma: küçük yükün sorunu

Alevin tutunması için kapı darbesi bitmeden akımın **I_L**'yi geçmesi gerekir. Tutunduktan sonra söner mi? Akım **I_H**'nin altına inerse söner. Akkor lamba bunlara takılmaz; **küçük LED lamba** takılır:

| Yük (230 V, PF ≈ 1) | Akım (rms) | I_L ≤ 30–40 mA ile |
|---|---|---|
| 60 W akkor | 261 mA | Çok üstünde |
| 15 W LED | 65,2 mA | Üstünde |
| 10 W LED | 43,5 mA | Sınırda |
| 8 W LED | 34,8 mA | Sınırda |
| 5 W LED | **21,7 mA** | **Altında: tutunma garanti değil** |
| 3 W LED | **13,0 mA** | **Altında** |

rms akım yalnızca kabaca fikir verir. Asıl karar, **tetik anındaki anlık akıma** bağlıdır: tetik sıfır geçişe yakınken (çok düşük ve çok yüksek parlaklıkta) gerilim küçüktür, akım I_L'ye yetişemez. Sonuç: parlaklığın uçlarında **titreme** ve yarım dalga çalışma. Çözümler: kapı darbesini akım I_L'yi geçene kadar uzatmak, en küçük yükü sınırlamak ya da aktif yük eklemek (bölüm 4.2).

## 3. Faz kontrolünün matematiği

Tetik açısı **α**, yarım periyodun başından (sıfır geçiş) tetiğe kadar olan açıdır; **iletim açısı** `180° − α`'dır. Direnç yükte yük geriliminin rms değeri:

```
V_yük² = (1/π) ∫ V_tepe² · sin²θ dθ   (θ: α ... π)
       = V_hat² · [ (π − α)/π + sin(2α)/(2π) ]
```

Direnç yükte güç gerilimin karesiyle orantılı olduğu için güç oranı doğrudan köşeli parantezdir: `P/P_max = 1 − α/π + sin(2α)/(2π)`. Güç faktörü `PF = P/(V_hat · I_rms) = √(P/P_max)`.

| α | t_α (50 Hz) | t_α (60 Hz) | Güç | V_rms | 60 W lamba akımı | PF |
|---|---|---|---|---|---|---|
| 0° | 0,00 ms | 0,00 ms | %100,0 | 230,0 V | 260,9 mA | 1,000 |
| 30° | 1,67 ms | 1,39 ms | %97,1 | 226,7 V | 257,1 mA | 0,985 |
| 60° | 3,33 ms | 2,78 ms | %80,4 | 206,3 V | 234,0 mA | 0,897 |
| 90° | 5,00 ms | 4,17 ms | **%50,0** | 162,6 V | 184,5 mA | 0,707 |
| 120° | 6,67 ms | 5,56 ms | %19,6 | 101,7 V | 115,3 mA | 0,442 |
| 150° | 8,33 ms | 6,94 ms | %2,9 | 39,1 V | 44,3 mA | 0,170 |
| 180° | 10,00 ms | 8,33 ms | %0,0 | 0 V | 0 mA | 0,000 |

Çubukta iletim açısını görürsün; sağdaki güç doğrusal değildir:

```
 α       yarım periyot (1 karakter = 10°)   güç
   0°    ██████████████████   %100,0
  30°    ░░░███████████████   % 97,1
  60°    ░░░░░░████████████   % 80,4
  90°    ░░░░░░░░░█████████   % 50,0
 120°    ░░░░░░░░░░░░██████   % 19,6
 150°    ░░░░░░░░░░░░░░░███   %  2,9
 180°    ░░░░░░░░░░░░░░░░░░   %  0,0

 ░ = triyak kapalı (tetik gecikmesi t_α)    █ = iletimde
```

**Sonuçlar:**
- **90° = %50 güç.** Güç açıyla doğrusal değildir: 0°–60° arası yalnızca %20 düşer, 90°–150° arası %47 düşer. Kaydırıcıyı doğrudan açıya bağlarsan orta noktada hızlı, uçlarda yavaş bir ayar elde edersin; bu yüzden güç → açı eşlemesi gerekir (bölüm 7).
- Göz ışığı doğrusal algılamaz. Pratikte kaydırıcıdan **parlaklığa** (ör. kare eğri), parlaklıktan **güce**, güçten **açıya** üç basamaklı eşleme yapılır. Eğri seçimi lamba tipine ve zevke bağlıdır.
- Tetik açısı **hat frekansından bağımsız** değildir: 60 Hz'de aynı açı daha kısa süredir (90° = 4,17 ms). Zamanlayıcı **ölçülen** yarım periyottan hesap yapmalıdır (bölüm 7).

### 3.1 İleri kenar ve geri kenar

```
 ileri kenar (triyak)   α = 90°   ░░░░░░░░░█████████   geç AÇ, akım sıfırda kendiliğinden kesilir
 geri kenar (MOSFET)    90° iletim █████████░░░░░░░░░   ZC'de AÇ, geç KES (zorla)
```

| Yük | İleri kenar (triyak) | Geri kenar (MOSFET) | Not |
|---|---|---|---|
| Akkor, halojen | Uygun | Uygun | Direnç yük |
| Manyetik düşük gerilim trafosu (MLV) | **Uygun** | **Uygun değil** | Geri kenar "geri tepme" gerilimi doğurur, dimmer veya yük zarar görebilir (Leviton) |
| Elektronik düşük gerilim trafosu (ELV) | **Zayıf** | **Uygun** | İleri kenar kötü performans verebilir (Leviton) |
| LED, CFL | Yalnız "triyak uyumlu" lambalarla, çoğu kez sorunlu | **Genellikle daha iyi** | Geri kenar titremeyi, duyulur gürültüyü azaltabilir ve dimleme aralığını iyileştirebilir (Leviton); triyak dimmer elektronik yükler için genelde zayıf bir seçimdir: lamba tetik anında çok yüksek tepe akım çeker (ESP) |
| Isıtıcı (direnç) | Uygun | Uygun | Burst kontrolü EMI açısından daha temiz |
| Fırçalı (universal) motor | Dikkatle | — | Endüktif yük: snubber şart (bölüm 4.4) |

Geri kenar dimmer genellikle **nötr** ister (MOSFET ve kendi beslemesi için). Triyak dimmer iki telli yapılabilir; bu avantajı ve maliyeti yüzünden hâlâ yaygındır.

## 4. Yük tipleri ve zorlukları

### 4.1 Akkor ve halojen lamba

En kolay yüktür: saf dirençtir, akım gerilimle aynı fazdadır, triyak her yarım periyodun sonunda sıfır geçişte rahatça kapanır. Tek tuzak **soğuk filaman**dır: direnci sıcağın kabaca **onda biri** olduğu için lamba soğukken akım ≈ 10 katı çeker.

| Lamba | R_sıcak | R_soğuk (≈ 1/10) | İlk tepe akım | I_TSM / ilk akım (I_TSM = 95 A) |
|---|---|---|---|---|
| 60 W | 882 Ω | ≈ 88 Ω | ≈ 3,7 A | ≈ 26× |
| 600 W | 88 Ω | ≈ 8,8 Ω | ≈ 36,9 A | ≈ 2,6× |
| 1000 W | 52,9 Ω | ≈ 5,3 Ω | ≈ 61,5 A | ≈ 1,5× |

Kural: soğuk akımın **≥ 2 katı** I_TSM istenir. 1000 W'ta oran 1,5×'tir: kural **sağlanmaz**; daha yüksek I_TSM'li triyak, yumuşak başlangıç (güç rampası) veya akım sınırlama gerekir. Akım artış hızını (dI/dt) seri indüktans da sınırlar (bölüm 12).

### 4.2 LED lamba

LED lamba, akkor lambanın tersidir: **küçük akım, doğrusal olmayan giriş, kapasitif/elektronik sürücü.** Dört ayrı sorun üretir:

| Sorun | Belirti | Neden | Çözüm |
|---|---|---|---|
| **Mandallama / tutma** | Düşük parlaklıkta titreme, yarım dalga | Lamba akımı I_L ve I_H'den küçük | Uzun kapı darbesi, en küçük yük sınırı, aktif yük |
| **Hayalet parlama** | Dimmer **kapalıyken** lamba hafif yanar veya göz kırpar | Snubber ve dimmer besleme akımı lambadan geçer | Küçük snubber C, besleme akımını düşür, lambaya paralel direnç |
| **Titreme / uyumsuzluk** | Dimleme aralığında dalgalanma | Sürücünün faz kesmeyi yanlış yorumlaması, tetik jitter'ı | Lamba uyum listesi, kararlı ZC ve zamanlama |
| **Açılış akımı darbesi** | "Tık" sesi, çınlama | Kapasitif giriş + ileri kenar (ani 325 V adım) | Seri indüktör, geri kenar dimmer |

**Snubber damlayan musluktur.** Kapalı triyak ideal anahtar değildir; snubber kapasitörü üzerinden sürekli küçük bir akım akar. Büyük bir bardak (60 W akkor lamba, 882 Ω) damlayı fark etmez; küçük bir bardak (5 W LED lamba, ≈ 10,6 kΩ) taşar:

| C (snubber) | Kaçak (230 V, 50 Hz) | 60 W akkorda gerilim | 5 W LED'de gerilim (R = 10,6 kΩ modeli) | R_snub güç üst sınırı |
|---|---|---|---|---|
| 10 nF | 0,72 mA | 0,6 V | 7,6 V | 0,11 W |
| 22 nF | 1,59 mA | 1,4 V | 16,8 V | 0,23 W |
| 47 nF | 3,40 mA | 3,0 V | **35,9 V** | 0,50 W |
| 100 nF | 7,23 mA | 6,4 V | **76,4 V** | 1,06 W |
| 220 nF | 15,9 mA | 14,0 V | 168 V | 2,33 W |

LED lambayı **dirençle modellemek kabaca** fikir verir: gerçek sürücü doğrusal değildir. Yine de sonuç nettir: **100 nF'lık klasik snubber** akkorda uygundur, LED'e uygun değildir. LED'i destekleyen dimmerler **≤ 22 nF** kullanır veya snubber'ı tamamen kaldırır (bölüm 5.3).

**Aktif yük (bleeder) ekonomisi.** Mandallamayı garanti etmek için lambaya paralel **sürekli** 30 mA'lik direnç koymak: `230 V / 30 mA = 7,7 kΩ` ve `230 V × 30 mA =` **6,9 W** ısı. Olmaz. Çözüm **aktif yük**: yalnız tetikten sonraki ≈ 0,5 ms boyunca 30 mA çeken küçük bir devre (transistör + direnç). Tahmini ortalama güç: `200 V × 30 mA × (0,5 ms × 100 / s) ≈` **0,3 W**. Bu yaklaşık bir tahmindir; devreni ölç.

### 4.3 İki telli dimmer

İki telli dimmerde **nötr yoktur**; elektronik yükle **seri** bağlıdır. Triyak kapalıyken elektronik, yük üzerinden küçük bir akımla beslenir ("güç hırsızlığı"). Triyak açıkken üzerinde yalnız ≈ 1,4 V düşer: bu pencerede besleme akımı yok, kapasitör ayakta tutar.

Sonuçlar: (1) besleme akımı lambadan geçer → LED'de hayalet parlama; (2) yük çok küçükse besleme yetmez ya da akım tutma eşiğinin altında kalır → **en küçük yük** sınırı olur; (3) elektronik şebeke potansiyelinde yüzer. Nötrlü (3 telli) dimmer bu üç sorunu çözer ama her anahtar kutusunda nötr yoktur.

### 4.4 Endüktif yükler (motor, manyetik trafo)

Akım gerilimden geridedir. Sıfır geçişte akım henüz sıfır değildir; triyak kapanırken ters yönde **yeniden uygulanan gerilimin eğimi (dV/dt)** kendiliğinden tetiklenme riski doğurur. Bu yüzden endüktif yükte **snubber gerekir** ve (dV/dt)c, (dI/dt)c değerleri önemlidir (ST AN437). Manyetik trafoda iki yarım periyodun **asimetrik tetiklenmesi** DC bileşeni oluşturur ve çekirdeği doyurur: açıları simetrik tut, kapı darbesini akım oluşana kadar yeterince uzun (veya darbe dizisi) seç ve DC bileşeni test et.

## 5. Tetik devresi

### 5.1 Optotriyak

MCU triyakın kapısını **doğrudan** sürmez: kapı hat potansiyelindedir. Araya **optotriyak** girer: LED (MCU tarafı) ışıkla küçük bir triyakı (şebeke tarafı) tetikler. Hem yalıtım sağlar hem kapı akımını verir.

**Rastgele faz (non-zero-cross) tip şart.** Sıfır geçişli tipler (MOC304x, MOC306x, MOC308x, MOC316x) yalnız sıfır geçişte açar; **tetik açısını seçemezsin**, faz kontrolü yapılamaz. Fairchild AN-3006 da faz kontrolünün AC dalgasının istenen noktasında tetikleme gerektirdiğini söyler ve bunun için rastgele faz tipi (MOC301x/302x/305x) kullanır; sıfır geçişli tipleri (MOC308x/316x) ise açma-kapama kontrolüne ayırır.

| Parametre | MOC3020/21/22/23M | MOC3051/52/53M |
|---|---|---|
| Tür | Rastgele faz | Rastgele faz |
| **V_DRM** | 400 V | 600 V |
| **I_FT** (3 V) | 30 / 15 / 10 / **5 mA** | 15 / **10** / 6 mA (51/52/53) |
| **I_TSM** | 1 A (tekrarlı darbe, 100 µs, 120 pps) | 1 A (tek periyot, 60 Hz sinüs) |
| V_ISO (1 dk, UL1577) | 4170 V_rms | 4170 V_rms |
| Dış kriper / klirens (DIP-6) | ≥ 7 mm | ≥ 7 mm |

MOC3023M ayrıntıları: LED V_F 1,15 V tipik / 1,50 V maks (10 mA), sürekli I_F maks 60 mA, V_R maks 3 V; çıkış V_TM 1,8 V tipik / 3,0 V maks (100 mA); I_H 100 µA; V_IORM 850 V tepe, V_IOTM 6000 V tepe.

**V_DRM marjı:** 400 V'luk parça 264 V hatta tepenin **%93'ünü** taşır; darbe marjı yoktur. 230 V ürünlerde **600 V sınıfı** (MOC305x) tercih et veya darbe kenetlemesini (MOV) iyi tasarla.

**Yalıtım:** DIP-6'nın ≥ 7 mm kriper/klirensi Ders 1'deki güçlendirilmiş bariyer hedefini (≥ 6 mm) karşılar. **Küçük gövdeli (SOP/mini-flat) optotriyaklarda mesafe daha kısa olabilir**: datasheet'ten kriper/klirens ve V_IORM'a bak. Opto bu kartta **şebeke–SELV bariyeridir**; V_IORM/V_IOTM ve mesafeler ürün standardıyla karşılaştırılır.

### 5.2 Devre ve hesaplar

```
              MOC3023                         TRİYAK
              ┌────────────┐                  ┌─────────┐
              │ LED        │                  │ (şebeke)│
GPIO ─[180 Ω]─┤1          6├──────────────────┤ MT2     ├──[YÜK]── hat (L)
              │            │                  │         │
GND ──────────┤2          4├──[390 Ω]─────────┤ G       │
              │ çıkış      │                  │         │
              │            │                  │ MT1     ├────────── nötr (N)
              └────────────┘                  └─────────┘
```

Snubber MT2 ile MT1 arasına **seri R + C** olarak bağlanır (bölüm 5.3).

| Bileşen | Hesap | Seçim |
|---|---|---|
| **R_LED** | `(3,3 V − 1,5 V) / 10 mA = 180 Ω` (I_F = 2 × I_FT,maks) | **180 Ω**; tipik V_F'de I_F = 11,9 mA: MCU pini ≥ 12 mA vermeli, yoksa transistörle sür |
| **R_g** | `V_tepe / I_TSM = 325 V / 1 A = 325 Ω` (230 V); 264 V'ta **373 Ω** | **390 Ω** (E12); darbe dayanımlı direnç |
| **Ölü bölge** | `V_min = I_GT,maks·R_g + V_GT,maks + V_TM,maks = 10 mA·390 Ω + 1,0 V + 3,0 V = 7,9 V` → `asin(7,9/325,3) =` **1,39° (0,077 ms)** | Önemsiz; ama darbe bu bölgeden sonra sürmeli |
| **Kapı akımı** | Tipik V_TM = 1,8 V ve V_GT = 0,7 V ile: V = 10 V'ta `(10 − 1,8 − 0,7)/390 ≈` **19 mA**; 20 V'ta ≈ 45 mA | I_GT,maks'ın ≥ 1,9 katı |

**R_g neden zorunlu?** Optotriyakın çıkışı hat gerilimine doğrudan bağlıdır. Tetik anında akımı yalnızca R_g sınırlar: tepede `V_tepe / R_g`. Bu tepe akım optonun I_TSM'sini (1 A) aşmamalıdır. Fairchild AN-3006 aynı kuralı verir: `V_tepe / I_tepe`; 115 V hat örneğinde `180 V / 1 A = 180 Ω` (180 V, +%10 toleranslı 115 V hattın tepesidir). Bu derste en kötü hat **264 V** (tepe 373 V) alındığı için `373 V / 1 A = 373 Ω` çıkar. Nominal 230 V'a göre seçilen 330 Ω, 264 V'ta 1,13 A geçirir ve I_TSM'i aşar.

LED'i **ters gerilimden** koru: V_R maks 3 V'tur. MCU pini düşüğe çekildiğinde 0 V, kabul edilebilir; ama LED'e başka kaynaktan ters gerilim gelebiliyorsa ters paralel diyot ekle.

### 5.3 Snubber

Snubber, triyak kapanırken yeniden uygulanan gerilimin eğimini **(dV/dt)c** altında tutar ve kapalıyken hattan gelen hızlı gerilim sıçramalarında kendiliğinden tetiklenmeyi önler. ST AN437'ye göre:

- Direnç **≥ 50 Ω** olmalı; açılırken kapasitör boşalma akımı **dI/dt < 20 A/µs** kalmalı. Tipik dimmer snubber'ı `100 Ω + 47…100 nF`; boşalma tepe akımı `325 V / 100 Ω ≈ 3,25 A`.
- Direnç gücü `P_R ≤ 2·C·V_tepe²·f`; tabloda (bölüm 4.2) 100 nF için **1,06 W**: 2 W'lık darbe dayanımlı direnç seç.
- ST iki yöntem verir: **F > 0,5** ve **F < 0,1** (`F = (R/2)·√(C/L)`). Modern 600 V'luk triyaklar için F < 0,1 yöntemi, ST'nin ifadesiyle yaklaşık dört kat küçük C verir. ST'nin örneği: 2000 VA, cosφ 0,6, 220 V/50 Hz, (dV/dt)c = 10 V/µs, L = 100 mH, r = 40 Ω yük için **10 nF + 300 Ω** (F < 0,1 yöntemi) karşısında **30 nF + 3,5 kΩ** (F > 0,5 yöntemi).
- **Snubberless** triyaklarda (iyi (dI/dt)c) komütasyon yardımcısı olarak snubber **kaldırılabilir**; kapalı durum bağışıklığı veya mandallama için gerekebilir.
- **Snubber kapalı durumu bozar:** kaçak "birkaç mA"dır ve küçük yüklerde sorun çıkarır (ST AN437). LED destekliyorsan C'yi küçült, kaçağı ölç.
- Snubber **aşırı gerilim korumasında zayıftır**; hat darbesi için filtre ve MOV kullan (Ders 1).

## 6. Sıfır geçiş algılama ve zamanlama

### 6.1 Devre

Tetik gecikmesi **sıfır geçişten** sayılır; bu yüzden MCU hatta bir "saat" gerekir. Köprü + direnç + optokuplör, her sıfır geçişte kısa bir darbe üretir:

```
 hat (L) ─[330 kΩ]─[330 kΩ]─┐
                            ├─ köprü ─► opto LED ═ opto ═ transistör ─► MCU ZC pini
 nötr (N) ──────────────────┘                                    (10 kΩ pull-up → 3,3 V)
```

**Çalışma:** Opto LED akımı (köprü ve LED düşümleri ihmal) `|v(t)| / R_toplam`'dır. Gerilim büyükken akım büyük, opto iletimde, ZC pini düşük. Gerilim sıfıra yaklaşınca akım eşik değerin (**I_th**) altına düşer, opto kesilir ve pin yüksek olur: **darbe**. Darbe genişliği eşiğe ve dirence bağlıdır (I_th = 100 µA varsayımı; kendi optonda ölç):

| R_toplam | Tepe akım | Direnç kaybı | Eşik gerilimi | Darbe (toplam) | Yorum |
|---|---|---|---|---|---|
| 66 kΩ (2 × 33 k) | 4,93 mA | **0,80 W** | 6,6 V | 0,13 ms | Dar ve doğru; 1 W'lık dirençler gerekir (Renesas APN-1124 örneği de 2 × 33 kΩ, 1 W kullanır) |
| 220 kΩ | 1,48 mA | 0,24 W | 22 V | 0,43 ms | |
| 330 kΩ | 0,99 mA | 0,16 W | 33 V | 0,65 ms | |
| **660 kΩ (2 × 330 k)** | **0,49 mA** | **80 mW** | **66 V** | **1,30 ms** | **Seçilen** |
| 1 MΩ | 0,33 mA | 53 mW | 100 V | 1,99 ms | Geniş; opto akımı çok düşük |

Gerçek ZC'ye en yakın dar darbe için direnç küçük olmalıdır ama **ısı** artar; 660 kΩ iyi bir uzlaşmadır. Direnç **iki seri** olmalı: her biri tepede 163 V görür (0805 yetmez: 1206 veya üç seri direnç), ve tek direnç açılırsa ZC kaybolur → **tetik yok** (güvenli durum); kısa devre olursa akım `325 V / 330 kΩ ≈ 1 mA` ile yine sınırlı kalır.

Opto çıkışındaki **pull-up** (kolektör direnci) darbe genişliğini etkiler: çok küçükse opto yanabilir, çok büyükse ZC sinyali genişler (Renesas APN-1124). 100 µA'lik LED akımında opto CTR'si de düşüktür; değeri **kendi devrende ölçerek** seç.

İzole olmayan (MCU hat potansiyelinde) tasarımda opto yerine direnç + MCU pin diyotları da kullanılabilir; ama MCU hatta bağlı olur: debugger izolasyonsuz bağlanmaz.

### 6.2 Zaman çizelgesi: yükselen kenar gerçek geçişten önce gelir

**Tren anonsu benzetmesi:** "Tren geliyor" anonsu başlar, tren tam **anonsun ortasında** geçer, anons biter. Süreyi anonsun başlangıcından sayarsan, trenin geçiş anına kadar **anonsun yarısını** eklemen gerekir. Darbe, gerçek sıfır geçişin etrafında **yaklaşık simetriktir** (eşikler iki yönde aynıysa): yükselen kenar geçişten `t_w = darbe/2` önce gelir.

```
 t [ms]     0         2,5       5         7,5       10
            |---------|---------|---------|---------|
 ZC pini    █████                                   █████
 gerçek ZC    ▲                                       ▲
 kapı                             █
 triyak     ███                   █████████████████████

 ZC darbesi yükselir (t = 0)  →  t_w = 0,65 ms  →  gerçek sıfır geçiş
 gerçek sıfır geçiş           →  t_α = 5,00 ms  →  tetik (α = 90°)
 toplam gecikme = t_w + t_α = 5,65 ms (yükselen kenardan)
```

Bu yüzden **gecikme = t_w + t_α**. t_w'yu datasheet'ten **değil, ölçülen darbe genişliğinden** al (`darbe_us / 2`): hat gerilimi, opto ve direnç toleransı ile değişir; 50/60 Hz farkını da kendiliğinden yakalar. Optonun açılma/kapanma gecikmeleri darbe **merkezini** kaydırabilir (µs mertebesinde, parçaya ve pull-up'a bağlı); osiloskopta hat ile ZC pinini **aynı ekranda** ölç ve kayma varsa sabit bir ofset olarak düş.

**Ölçüm kurulumu:** Kanal 1: hat (diferansiyel prob veya izolasyon trafosu ile, Ders 1 bölüm 14.2). Kanal 2: ZC pini. Gerçek geçişten darbenin yükselen kenarına kadar süre `t_w`'dur; yükselen ve düşen kenarların ortası geçişle çakışmalıdır.

## 7. Yazılım çekirdeği

### 7.1 Akış

[kod/dim_faz.c](kod/dim_faz.c) donanımdan bağımsızdır: zamanlayıcı ve GPIO bu modülün **dışındadır** (ISR'den çağrılır). Akış:

1. **ZC yükselen kenarı** (giriş yakalama): `yarim = t_şimdi − t_önceki`; **düşen kenar**: `darbe = t_düşen − t_yükselen`.
2. `dim_olcum_ekle(&d, yarim, darbe)`: aralık denetimi, sapma kontrolü, IIR süzme (1/8). Dört art arda iyi ölçümden sonra `gecerli`.
3. `D = dim_gecikme_us(&d, guc_binde, marj_us)`. `D == DIM_KAPALI` ise **tetik verme**. Değilse tek atımlık zamanlayıcıyı D'ye kur; zamanlayıcı kesmesi kapı darbesini başlatır, ikinci kanal 100–300 µs sonra bitirir (**donanım** çıkış karşılaştırma ile sabit genişlik).
4. **Zaman aşımı zamanlayıcısı:** 1,5 × yarım periyot içinde yeni ZC gelmezse `dim_zc_kayip(&d)`.
5. `marj_us` = kapı darbesi + ≈ 100 µs (örnek 300 µs): çok düşük güçte tetik yarım periyodun sonuna çok yakınsa tetik **verilmez**.

### 7.2 Güç → gecikme: ileri tablo, ters değil

Güç eşlemesi için ilk akla gelen **ters tablodur**: eşit aralıklı güç noktaları için açıyı sakla, arada doğrusal ara değer. Sorun: `P(α)` uçlarda yataydır (`dP/dα → 0`); tersi `α(P)` uçlarda **küp kök gibi dikleşir** (α = π − x için `P ≈ 2x³/(3π)`). Eşit güç aralıklarında doğrusal ara değer bu diklikte büyük hata yapar.

**İleri tablo** düzgün fonksiyonu örnekler: açıyı eşit aralıklara böl, her noktada **gücü** sakla; ters çözümde bulunduğu aralığı bul ve içinde doğrusal ara değer al. Hata `≤ max|P''|·h²/8 = (2/π)·(π/N)²/8` olur (N = 32 için **0,077 %**).

| N (aralık) | Bayt (uint16) | Ters tablo, en büyük güç hatası | **İleri tablo**, en büyük güç hatası |
|---|---|---|---|
| 16 | 34 | %2,33 | **%0,30** |
| 32 | 66 | %1,18 | **%0,08** |
| 64 | 130 | %0,59 | **%0,02** |

Aynı bellekle N = 32'de **≈ 15× daha doğru**. (Hata, tam güce göre mutlak yüzdedir.)

**Yürüme benzetmesi:** Dik bir tepeyi eşit adımlarla çıkmak yerine, düz yolu eşit adımlarla ölçüp haritayı tersine okumak.

Tablo (Q16, 65535 = tam güç; formülden betikle üretildi, testte formülle ±1 uyumu doğrulandı):

```c
/* P(alfa_k) = 1 - k/N + sin(2*pi*k/N) / (2*pi), Q16 (65535 = tam güç) */
static const uint16_t k_guc_tab[N_ARALIK + 1u] = {
    65535u, 65522u, 65431u, 65186u, 64718u, 63968u, 62883u, 61429u, 59581u,
    57333u, 54692u, 51680u, 48335u, 44706u, 40855u, 36850u, 32768u, 28685u,
    24680u, 20829u, 17200u, 13855u, 10843u,  8202u,  5954u,  4106u,  2652u,
     1567u,   817u,   349u,   104u,    13u,     0u};
```

Çekirdek fonksiyon (dönüş: yükselen kenardan tetiğe µs veya `DIM_KAPALI`):

```c
/* Dönüş: darbenin YÜKSELEN KENARINDAN tetiğe kadar geçecek süre (µs) ya da DIM_KAPALI.
 * guc_binde: 1..1000 (binde). marj_us: yarım periyodun sonundan önce bırakılacak süre
 * (kapı darbesi + mandallama payı). Geçersiz her durumda sonuç DIM_KAPALI'dır. */
uint32_t dim_gecikme_us(const dim_t *d, uint16_t guc_binde, uint32_t marj_us)
{
    if ((d == NULL) || !d->gecerli) { return DIM_KAPALI; }
    if ((guc_binde == 0u) || (guc_binde > 1000u)) { return DIM_KAPALI; } /* geçersiz -> kapalı */
    if (marj_us >= d->yarim_us) { return DIM_KAPALI; }

    const uint32_t p = (((uint32_t)guc_binde * 65535u) + 500u) / 1000u; /* Q16 */

    uint32_t k = 0u; /* k_guc_tab[k] >= p >= k_guc_tab[k+1] */
    while ((k < (N_ARALIK - 1u)) && (p < k_guc_tab[k + 1u])) { k++; }

    const uint32_t ust    = k_guc_tab[k];
    const uint32_t alt    = k_guc_tab[k + 1u];
    const uint32_t aralik = ust - alt;
    if (aralik == 0u) { return DIM_KAPALI; } /* tablo bozulduysa güvenli durum */

    const uint32_t kesir    = ((ust - p) << 16) / aralik;       /* Q16, 0..65536 */
    const uint32_t alfa_q16 = ((k << 16) + kesir) / N_ARALIK;   /* alfa/pi, Q16  */
    const uint32_t t_alfa   = (d->yarim_us * alfa_q16) >> 16;   /* µs            */

    if (t_alfa > (d->yarim_us - marj_us)) { return DIM_KAPALI; }
    return (d->darbe_us / 2u) + t_alfa;
}
```

**Savunmacı noktalar:** NULL ve `gecerli` denetimi; `guc_binde` 0 veya 1000 üstü → **kapalı** (taşan değeri "tam güç"e kırpmak güvensizdir); `marj_us ≥ yarım periyot` → kapalı; tablo bozulursa (`aralik == 0`) → kapalı; tüm ara değerler 32 bite sığar (`yarim_us ≤ 12000`, `alfa_q16 ≤ 65536`), 64 bit bölme/çarpma yok; bölme yalnızca ikinin kuvveti ve bir tamsayı bölmedir.

### 7.3 Fail-safe kuralları

1. **ZC yoksa tetik yok.** Zaman aşımı → `dim_zc_kayip` → `DIM_KAPALI`.
2. **Açılışta kapalı başla.** `gecerli = false`; dört iyi ölçüm bekle.
3. **Kapı darbesi donanım zamanlayıcıyla, sabit genişlikte.** Yazılım seviyeyi yüksekte bırakıp kilitlenirse yük sürekli açılmasın (seviye değil, darbe).
4. **Watchdog** sonrası ve **GPIO başlangıç durumu** kapalı (pull-down). Kapı sürme pini reset sırasında yüksek empedans veya düşük olmalı.
5. **Geçersiz giriş → kapalı:** hat frekansı 41,7–71,4 Hz dışı, darbe genişliği 100–4000 µs dışı, güç 0 veya > 1000 binde.
6. **Aşırı sıcaklık:** triyak veya kart sıcaklığı sensörü (NTC) eşik üstünde → güç sınırla/kapat (bölüm 8).

Modül **tek** kötü ölçümü (ör. kayıp bir darbe: 20 ms'lik aralık) tolere eder. **Fazladan** bir parazit darbesi ise iki kötü ölçüm üretir (kısa aralık + kalan aralık) ve modülü geçersiz kılar; 4 iyi ölçümle (≈ 40 ms) yeniden başlar. Kısa bir sönme olabilir: bu bir tercihtir (kuşkuda tetik verme). Parazit darbesini baştan elemek için aşağıdaki karartma penceresini ekle.

### 7.4 Test ve geliştirme

Kod `gcc -std=c11 -Wall -Wextra -pedantic -Werror -Wconversion -Wshadow` ile uyarısız derlendi; [kod/test_dim_faz.c](kod/test_dim_faz.c) 11 senaryoyu geçti (ASan ve UBSan altında da): tablonun formülle uyumu, NULL güvenliği, açılışta kapalı, 4 ölçümle kilitlenme, %50'de `650 + 5000 µs`, geçersiz giriş, marj, **tüm 1000 güç değerinde en büyük sapma 50 Hz'de %0,089, 60 Hz'de %0,090**, tekdüzelik, tek/çift kötü ölçüm, ZC kaybı ve dönüş, 50 → 60 Hz yeniden kilitlenme, süzgeç yakınsaması ve sınır değerler. MCU'ya taşırken yalnızca zamanlayıcı/GPIO sargısını yaz; modüle dokunma.

Geliştirme fikirleri:
- **Karartma (blanking) penceresi:** son kabul edilen kenardan `0,75 × yarım periyot` içinde gelen kenarı yok say: parazit darbesi sönmeye yol açmaz.
- **Yarım periyot tahmini (PLL benzeri):** bir ZC darbesi kayıpsa tahmin edilen zamanla devam et.
- **Algısal eğri:** kaydırıcı → parlaklık → güç için ikinci tablo.
- **Yumuşak başlangıç:** akkor lambada soğuk filaman akımı için güç rampası.

## 8. Isıl tasarım

Triyakın kaybı **eşik gerilimi** ve **dinamik direnç** modeliyle: `P ≈ V_TO · I_ort + R_d · I_rms²`. BT138-E için V_T = 1,4 V @ 15 A verisinden `V_TO = 1,0 V`, `R_d = 0,027 Ω` (model 15 A'de 1,405 V verir). Direnç yükte `I_ort = I_rms · 2√2/π`.

| Yük (230 V) | I_rms | P_triyak | Serbest havada ΔT (60 K/W) | R_th,maks (T_j ≤ 110 °C, T_a = 50 °C) | Soğutucu + arayüz ≤ |
|---|---|---|---|---|---|
| 100 W | 0,43 A | 0,40 W | 24 K | 151 K/W | 149 K/W |
| 200 W | 0,87 A | 0,80 W | 48 K | 75 K/W | 72 K/W |
| **400 W** | 1,74 A | **1,65 W** | **99 K** | **36 K/W** | 34 K/W |
| 600 W | 2,61 A | 2,53 W | 152 K | 24 K/W | 21 K/W |
| 1000 W | 4,35 A | 4,42 W | 265 K | 14 K/W | 11 K/W |

**Okuma:**
- Serbest havada `T_j ≤ 110 °C`, `T_a = 50 °C` ile izin verilen kayıp `(110 − 50)/60 = 1,0 W`: bu **≈ 250 W**'lık yüke denk gelir. Üstünde **soğutucu** gerekir. (Mutlak sınır T_j = 125 °C ile 1,25 W.)
- **400 W** örneği: serbest havada 1,65 W × 60 K/W = 99 K → `T_j = 50 + 99 = 149 °C` > 125 °C. Soğutucu şart: toplam `R_th ≤ 36 K/W`, yani soğutucu + arayüz `≤ 36 − 2,3 = 34 K/W`.
- **Kapalı kutu serbest havadan çok daha kötüdür.** Duvar tipi dimmer bir kutuda, yanındaki dimmerlerle birlikte çalışır: ortamı 50 °C ya da üstü varsay ve **ölç** (bölüm 13).
- R_th(j-mb) bu yalıtımlı (IITO220) gövde için **2,3 K/W**'tır; yalıtımsız sekmeli gövdelerde değer genellikle daha düşüktür. Kendi parçanın datasheet değerini kullan.

## 9. 💼 İş yerinde

Dimmer ürününde **aynı sırayla** sor: (1) iki telli mi, üç telli mi? (2) hangi yük tipleri ve güç aralığı? (3) ortam ve montaj (duvar kutusu)? (4) hangi ürün standardı ve EMC testleri?

| Soru | Neden önemli | Nereden |
|---|---|---|
| İki/üç telli | Nötr yoksa besleme yükten geçer: hayalet parlama, en küçük yük | Bölüm 4.3 |
| Yük listesi (akkor, LED, ELV…) | Kadran, snubber C, kapı darbesi, aktif yük | Bölüm 3.1, 4 |
| En küçük ve en büyük yük | Mandallama ve ısıl sınır | Bölüm 2.4, 8 |
| Ortam sıcaklığı, kutu | T_j hesabı ve soğutucu | Bölüm 8 |
| Standart | Mesafeler, testler, kaçak akım | EN 60669-2-1; Ders 1 |

**Bring-up sırası (kart ilk kez açılırken):**
1. İzolasyon trafosu ve **seri ampul** (Ders 1, bölüm 14.2). Önce yük **yok**.
2. Yalnız ZC devresi: hat ile ZC pinini aynı ekranda gör; darbe genişliği ve merkezini ölç.
3. Kapı darbesi: yük bağlı değilken optodaki akımı ve darbe genişliğini ölç.
4. **60 W akkor lamba** bağla (en kolay yük): 90°'de ışık yarı parlaklıkta olmalı, kaydırıcıda titreme olmamalı.
5. Hat frekansı değişimini (varsa ayarlanabilir frekanslı AC kaynakla, 47,5–63 Hz) dene; zamanlama ölçülen yarım periyotla doğru kalmalı.
6. Hattı kes–ver: kapalı başlamalı, 4 yarım periyot sonra tetiklemeli.
7. Sonra en küçük LED lamba: en düşük parlaklıkta titreme, kapalıyken hayalet parlama.
8. Tam yük ve ısıl: 1 saat, T_sekme ölç.
9. En sona EMI ön-testi.

> Bu işyeri tablosu genel örnektir; şirketin gerçek ürün şemaları ve değerleri bu notlara girmez.

## 10. Şematikte

- Triyakın V_DRM, I_T(RMS), I_TSM ve kadranını şematik notuna yaz; **soğutucu ve sekme (MT2)** için not: "sekme hat potansiyelinde".
- Optotriyak çıkışını ve R_g'yi (390 Ω) göster; **R_LED** hesabını notla (`(3,3 − 1,5)/10 mA`).
- Snubber değerleri ve **kaçak akım hesabı** (`I = 2π·f·C·V`) şematikte.
- ZC devresinde iki seri direnç ve opto; **darbe genişliği** hesabı ve I_th varsayımı not.
- Şebeke bölgesini kutuyla ayır; bariyeri (opto) işaretle; yalıtım değerlerini ve OVC/PD'yi yaz (Ders 1).
- "⚠ Elektronik şebeke potansiyelinde" uyarısı (iki telli ürün).

## 11. PCB / layout

- **Güç yolu:** yük akımı için geniş iz/bakır; triyak bacaklarına kısa. MT2–kontrol bölgesi arasında Ders 1'deki mesafeler.
- **Kapı yolu kısa:** R_g triyakın kapısına yakın; kapı dönüşü **MT1'e** yakın ve gürültülü yoldan ayrı bağla (MT1 referansı).
- **Snubber** triyakın MT2 ve MT1 bacaklarına doğrudan; döngü alanı küçük.
- **Opto bariyeri:** altında bakır yok; gerekirse yarık (≥ 1 mm). DIP-6'da 7 mm, SMD'de datasheet'e bak.
- **Soğutucu ve sekme:** TO-220AB'de sekme MT2'dir; ya yalıtımlı gövde ya da yalıtım pedi + dokunulmazlık. Montaj vidasının kriperini de ölç.
- **Filtre indüktörü** girişe yakın; ZC dirençleri hat tarafında, creepage'e uygun aralıkta.
- Isı için triyak altı bakır alanı (termal) ve **komşu ısıtıcı parçalardan** (NTC, bleeder, düşürücü) uzak yerleşim.

## 12. EMC açısından

Faz kontrolü **dI/dt**'si büyük bir anahtarlamadır: tetik anında hat gerilimi (örneğin tepede 325 V) aniden yüke uygulanır. Sonuç geniş bantlı **iletilen** ve **yayılan** girişimdir.

- **Seri indüktör** akım artışını sınırlar: `dI/dt = V/L`; 1 mH için `325 V / 1 mH = 0,33 A/µs` (triyak sınırı 50 A/µs; ST'nin snubber boşalma sınırı 20 A/µs).
- Seri L ile snubber C bir **rezonans** kurar: 1 mH ve 100 nF için `f₀ = 15,9 kHz`, `Z₀ = √(L/C) = 100 Ω`. ST'nin sönümleme faktörü `F = (R/2)·√(C/L) = R/(2·Z₀)`: `R = 100 Ω → F = 0,5`, `R = 200 Ω → F = 1` (kritik sönüm). Sönümsüz bırakırsan devre **çınlar** ve EMI artar.
- İndüktörün **doyma akımı** yük tepe akımının ≥ 1,5 katı olmalı: 400 W için `1,74 A × √2 × 1,5 ≈ 3,7 A`. Doyan indüktör filtre etkisini kaybeder.
- **Darbeli akım** indüktörde mekanik titreşim yapar (duyulabilir çınlama). Büyük L dI/dt'yi azaltır ama çınlamayı ve boyutu artırır: uzlaşma.
- Hızlı kapanma filtre indüktörlerinde **ringing** yaratabilir (ESP); sönümleme (R–C) ve yerleşim önemlidir.
- X2 kapasitör, Y kapasitör ve CMC için Ders 1 (bölüm 7, 8, 13) ve [EMC 02](../../EMC/02-emc-icin-kart-tasarimi/ozet.md).
- Standartlar: **EN 55015** (aydınlatma ekipmanı iletilen emisyon), **EN 61000-3-2** (harmonik), **EN 61000-3-3** (flicker). Faz kontrolünün güç faktörü ve harmonikleri bu testlerin konusudur.

## 13. Ölçüm ve doğrulama

| Ölçüm | Nasıl | Beklenen |
|---|---|---|
| **ZC darbesi** | Hat (diferansiyel prob / izolasyon trafosu) ve ZC pini aynı ekranda | Genişlik ≈ hesap (1,3 ms); merkez ≈ geçiş (birkaç on µs); 47,5–63 Hz'de kararlı |
| **Tetik zamanlaması** | ZC pini ve kapı akımı | Gecikme = t_w + t_α ± birkaç µs; kapı darbesi sabit genişlikte |
| **Kapı akımı** | Küçük şant direnci veya akım probu | ≥ 2 × I_GT,maks; I_GM (2 A) aşılmaz |
| **Kapalı durum kaçağı** | Yükte (veya lamba ucunda) rms gerilim | `I = 2π·f·C·V` ile uyumlu; LED'de görünür parlama yok |
| **En küçük yük** | En küçük desteklenen lamba, en düşük parlaklık | Her yarım periyotta tetik, titreme yok |
| **Açılış akımı** | Soğuk lamba, akım probu | < I_TSM / 2 |
| **Isıl** | Triyak sekmesi, 1 saat, tam yük, kutu içinde, yüksek ortam | T_j (hesap) ≤ 110 °C |
| **Hat kesintisi** | Hattı kes–ver | Kapalı başlar, 4 yarım periyot sonra doğru tetik |
| **Hat frekansı** | 50 Hz −%5 … 60 Hz +%5 (47,5–63 Hz) | Zamanlama ölçülen yarım periyotla doğru kalır |
| **EMI ön-test** | Yakın alan probu, LISN | Filtreli ve filtresiz karşılaştırma |

Şebeke güvenliği için Ders 1'deki ölçüm kurallarının **tümü** geçerlidir: izolasyon trafosu, seri ampul, diferansiyel prob, tek el, deşarj kontrolü. İki telli dimmerde **karttaki her düğüm şebeke potansiyelindedir**: prob toprağını karta bağlama.

## 14. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| Sıfır geçişli optotriyakla faz kontrolü | Yalnız sıfır geçişte açar; dimleme yok | Rastgele faz (MOC302x/305x) |
| R_g koymamak veya çok küçük seçmek | Optonun I_TSM'si (1 A) aşılır | `V_tepe / I_TSM` → 390 Ω |
| 400 V'luk opto ile 230 V ürün | 264 V'ta tepe %93; darbe marjı yok | 600 V sınıfı |
| 100 nF snubber + LED lamba | Hayalet parlama, titreme | ≤ 22 nF veya snubber'sız; kaçağı ölç |
| En küçük yükü düşünmemek | I_L, I_H altında: titreme | Min yük sınırı, aktif yük, uzun kapı darbesi |
| Güç ile açıyı doğrusal eşlemek | Ortada sıçrama, uçlarda ölü bölge | `P(α)` formülü + ileri tablo |
| Gecikmeyi yükselen kenardan, t_w'yu eklemeden saymak | Tüm kademeler t_w kadar erken | `t_w + t_α`, darbeyi ölç |
| Ters tabloyla uçlarda %1+ hata | Küp kök diklik | İleri tablo + ters ara değer |
| ZC yokken tetiklemeye devam | Yanlış fazda yük, belirsiz davranış | ZC yoksa tetik yok |
| Kapı seviyesini yazılımla yüksekte tutmak | Kilitlenmede yük sürekli açık | Donanım zamanlayıcı, sabit darbe |
| Soğutucunun şebekede olduğunu unutmak | TO-220AB sekmesi MT2'dir | Yalıtımlı gövde veya yalıtım pedi |
| LC filtreyi sönümsüz bırakmak | Çınlama, EMI artışı | Snubber R ≈ Z₀ |
| İlk açılışı doğrudan şebekeden yapmak | Hatada parça yanar | Seri ampul + izolasyon trafosu (Ders 1) |
| Dimlenemeyen LED lambayı dimmer'a takmak | Titreme, ısınma, lamba hasarı | Lamba etiketinde "dimlenebilir" ve uyumlu tip |

## 15. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Faz kontrolü** | Her yarım periyotta yükün bir kısmını geç tetikleyerek gücü ayarlama |
| **α (tetik açısı)** | Sıfır geçişten tetiğe kadar olan açı |
| **İletim açısı** | `180° − α` |
| **İleri kenar** | Geç açar, sıfır geçişte kendiliğinden keser (triyak) |
| **Geri kenar** | Sıfır geçişte açar, geç keser (MOSFET) |
| **Triyak** | İki yönlü, kapıdan tetiklenen AC anahtar |
| **MT1 / MT2 / G** | Ana uçlar ve kapı |
| **Kadran (QI–QIV)** | MT2 ve kapı polaritesinin kombinasyonu |
| **I_GT** | Kapı tetik akımı |
| **I_L (mandallama)** | Kapı darbesi bitince açık kalmak için gereken en küçük ana akım |
| **I_H (tutma)** | Açık kalmak için gereken en küçük ana akım |
| **dV/dt, (dV/dt)c** | Kapalıyken gerilim artış hızı, komütasyon sırasında artış hızı |
| **Snubber** | MT2–MT1 arası R–C; dV/dt'yi sınırlar |
| **Optotriyak** | LED ile tetiklenen küçük triyak (yalıtım + tetik) |
| **Rastgele faz** | Herhangi bir anda tetiklenebilen optotriyak (non-zero-cross) |
| **Sıfır geçiş (ZC)** | Gerilimin 0 V'tan geçtiği an |
| **t_w** | ZC darbesinin yarı genişliği; yükselen kenar ile gerçek ZC arası |
| **Hayalet parlama** | Kapalı dimmerde kaçak akımla LED lambanın hafif yanması |
| **Aktif yük (bleeder)** | Mandallama için tetik sonrası kısa süre akım çeken devre |
| **Burst kontrolü** | Tam yarım periyotları aç-kapa; ısıl yüklerde kullanılır |
| **MLV / ELV** | Manyetik / elektronik düşük gerilim trafosu |
| **PF** | Güç faktörü; direnç yük faz kontrolünde `√(P/P_max)` |
| **Q16** | 16 bitlik sabit nokta: 65535 = 1,0 |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.7, bölüm 14):

- [x] Triyak V_DRM ≥ 600 V (230 V hat); I_TSM soğuk lamba akımının ≥ 2 katı; kayıp hesaplandı ve T_j ≤ 110 °C (ortam 50 °C) sağlanıyor ya da soğutucu seçildi
- [x] Tetik devresi QI/QIII'e göre kuruldu: rastgele faz (non-zero-cross) optotriyak; R_g ≥ V_tepe / I_TSM(opto); opto LED akımı ≥ 2 × I_FT
- [x] Optotriyakın V_DRM marjı (264 V hatta tepe 373 V için), V_IORM/V_IOTM ve kriper/klirensi şebeke–SELV bariyeri gereksinimine göre kontrol edildi
- [x] Mandallama (I_L) ve tutma (I_H) akımı en küçük yük akımına göre kontrol edildi; en küçük yük, kapı darbe genişliği ve gerekirse aktif yük belirlendi
- [x] Snubber kaçak akımı (I = 2π·f·C·V), yükte oluşan hayalet gerilim ve direnç gücü (≤ 2·C·V²·f) hesaplandı; LED yükü destekleniyorsa C küçültüldü
- [x] Sıfır geçiş algılamada eşik, darbe genişliği (t_w) ve opto gecikmesi ölçüldü; tetik gecikmesi darbenin yükselen kenarına göre t_w kadar düzeltildi; 50 ve 60 Hz'de doğrulandı
- [x] Fail-safe: sıfır geçiş yoksa tetik yok; kapı darbesi donanım zamanlayıcıyla sabit genişlikte; açılışta ve watchdog sonrası kapalı başlıyor; geçersiz giriş (frekans, güç, darbe genişliği) kapalıya gidiyor
- [x] İki telli (şebeke potansiyelinde yüzen) elektroniğe debugger veya ölçüm yalnızca izolasyonla bağlanıyor; soğutucu/sekme (MT2) dokunulabilir değil veya yalıtımlı
- [x] Seri filtre indüktörünün doyma akımı yük tepe akımının üstünde; indüktör–snubber rezonansı (f₀, Z₀) hesaplandı ve sönümleme (F = R/(2·Z₀)) kontrol edildi

## Kontrol soruları

→ [quiz.md](quiz.md) · 12 soru, 7'si hesap
