# 02 · Kapasitör

- **Oluşturma:** 2026-10-12
- **İlk kaynak:** [Murata – MLCC DC bias SSS](https://www.murata.com/en-us/support/faqs/products/capacitor/mlcc/char/0005)
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Uygulama dersi:** [Güç ve decoupling](../../Konular/guc-ve-decoupling/ozet.md)

> Sayısal değerler **tipik başlangıç noktalarıdır**; tasarım değeri için her zaman kullandığın parçanın datasheet'i esastır.

---

## ⚡ Hızlı tekrar

1. Kapasitör bir yük deposudur: `Q = C·V`, `I = C·dV/dt`. Üzerindeki gerilim **aniden değişemez**.
2. Türü doğru seç: MLCC (C0G, X7R/X5R), alüminyum elektrolitik, polimer, tantal, film, süperkapasitör. Her birinin güçlü ve zayıf yanı farklıdır.
3. Class 2 MLCC'de (X7R/X5R) kapasite **sıcaklık, DC bias ve yaşlanma** ile düşer. C0G kararlıdır.
4. Elektrolitik kapasitörün ömrü sıcaklığa bağlıdır: **her 10 °C düşüş ömrü kabaca iki katına** çıkarır.
5. Polarize kapasitörlerde (elektrolitik, tantal) **ters gerilim arıza** demektir.
6. Şebekeye bağlı devrelerde yalnızca sertifikalı **X/Y güvenlik kapasitörleri** kullanılır.
7. MLCC, kart eğilince **çatlar** ve kısa devreye dönüşebilir; yerleşimde gerilme bölgelerinden uzak dur.
8. Büyük kapasitörler ilk enerjilemede **çok büyük inrush akımı** çeker.
9. **C toprağa → alçak geçiren** (yavaşı tutar); **C yolda, seri → yüksek geçiren** (hızlıyı tutar). Gaz dedektöründe neredeyse hep alçak geçiren gerekir.

## 🧮 Formül kartı

| Formül | Ne zaman kullanılır | Örnek |
|---|---|---|
| `I = C · dV/dt` | Şarj akımı, inrush | 1000 µF, 100 µs'de 12 V → **120 A** |
| `E = ½·C·V²` | Depolanan enerji | 1000 µF, 25 V → 0,31 J |
| `τ = R·C` | Zaman sabiti (1τ'da %63, 5τ'da ~%99) | 10 kΩ, 10 µF → 0,1 s |
| `f_c = 1 / (2π·R·C)` | RC filtre kesim frekansı | 1 kΩ, 100 nF → 1,59 kHz |
| `t = C·(V1² − V2²) / (2P)` | Besleme kesilince tutma süresi (hold-up) | 100 µF, 12→9 V, 1 W → 3,15 ms |
| `L = L0 · 2^((T0 − T)/10)` | Elektrolitik ömrü | 2000 h @105 °C → 65 °C'de 32 000 h (~3,7 yıl) |
| `I = 2π·f·C·V` | Y kapasitörün kaçak akımı | 4,7 nF, 230 V, 50 Hz → 0,34 mA |
| `C1 = C2 = 2·(C_L − C_stray)` | Kristal yük kapasitörleri | C_L 12 pF, stray 3 pF → 18 pF |
| `f_görünen = \|f − f_s'nin en yakın katı\|` | Aliasing: f > f_s/2 ise sinyal hangi frekansta görünür | 60 Hz, f_s 100 Hz → **40 Hz** |

---

## 1. Ne işe yarar? Temel fizik

İki iletken levha ve aralarında bir yalıtkan (dielektrik). Kapasite: `C = ε·A / d`, yani levha alanı ile artar, levha aralığı ile azalır, dielektrik malzemenin geçirgenliği (ε) ile artar.

**Davranışı:**
- **DC'yi engeller, AC'yi geçirir.** Empedansı `X_C = 1/(2πfC)`; frekans arttıkça düşer.
- **Gerilim aniden değişemez:** Ani değişim için sonsuz akım gerekir. Bu özellik filtrelemenin, beslemeyi yumuşatmanın ve gerilim tutmanın temelidir.
- **Enerji depolar:** `E = ½CV²`.

**Neden bazı seramikler sorunlu?** Class 2 seramiklerde (X7R, X5R) çok yüksek ε elde etmek için baryum titanat gibi ferroelektrik malzeme kullanılır. Bu malzemenin geçirgenliği sıcaklığa, uygulanan DC gerilime ve zamana bağlıdır. Class 1 (C0G) seramikler paraelektriktir, bu yüzden kararlıdırlar ama aynı hacimde çok daha düşük kapasite verirler.

## 2. Türleri ve seçim

| Tür | Değer aralığı | Artı | Eksi | Tipik kullanım |
|---|---|---|---|---|
| **MLCC Class 1 (C0G/NP0)** | pF – ~100 nF | Kararlı, düşük kayıp, DC bias yok | Düşük kapasite | Osilatör, filtre, zamanlama, RF |
| **MLCC Class 2 (X7R/X5R)** | nF – 100 µF | Küçük, ucuz, çok düşük ESR/ESL | DC bias, sıcaklık, yaşlanma, piezo etki, çatlama | Decoupling, bulk, genel amaçlı |
| **Alüminyum elektrolitik** | µF – F | Ucuz, yüksek kapasite × gerilim | Yüksek ESR, sınırlı ömür, polarize, büyük | Giriş bulk, düşük frekans |
| **Alüminyum polimer** | µF – mF | Düşük ESR, uzun ömür, kurumaz | Pahalı | Regülatör çıkışı, yüksek ripple akımı |
| **Tantal (MnO₂)** | µF – yüzlerce µF | Küçük hacimde yüksek kapasite, kararlı | Arıza modu kısa devre ve yanma, inrush'a hassas | Eski tasarımlar; dikkatle |
| **Tantal polimer** | µF – yüzlerce µF | Daha güvenli arıza, düşük ESR | Pahalı | Kompakt güç katları |
| **Film (PP, PET)** | nF – µF | Düşük kayıp, kendini onarma, yüksek gerilim, AC'ye uygun | Büyük | Şebeke filtresi (X/Y), snubber, hassas zamanlama, ses |
| **Süperkapasitör** | 0,1 F – kF | Çok yüksek kapasite | Hücre başına düşük gerilim (~2,7 V), yüksek ESR, kaçak | RTC yedekleme, kısa süreli enerji tutma |

### Class 2 MLCC'nin üç kaybı

| Etki | Ne olur | Önlem |
|---|---|---|
| **Sıcaklık** | X7R: −55…+125 °C'de ±%15 | Kodun sıcaklık aralığına uy |
| **DC bias** | Gerilim arttıkça kapasite düşer; küçük paket + yüksek değerde nominalin yarısının altına inebilir | Yüksek gerilim derecesi, büyük paket, üretici eğrisi |
| **Yaşlanma** | Kapasite zamanla logaritmik olarak azalır; lehim ısısı bu süreci sıfırlar | Hassas uygulamada C0G veya film |

Dielektrik kodlarının ayrıntıları: [Güç ve decoupling, bölüm 6](../../Konular/guc-ve-decoupling/ozet.md).

## 3. Datasheet'te nelere bakılır?

| Parametre | Anlamı | Tuzak |
|---|---|---|
| Kapasite ve tolerans | Class 2'de tipik ±%10 veya ±%20 | DC bias ve sıcaklık bunun üstüne eklenir |
| Anma gerilimi | Sürekli uygulanabilecek DC | Elektrolitikte çalışma gerilimini anma değerinin ~%80'inde tut |
| Dielektrik kodu | Sıcaklık davranışı | DC bias'ı kapsamaz |
| ESR / empedans eğrisi | Kayıp ve filtreleme performansı | Elektrolitikte soğukta ESR artar |
| **Ripple akımı** (elektrolitik) | Isınmadan taşıyabileceği AC akım | Aşılırsa ömür hızla kısalır |
| **Ömür (endurance)** | ör. 2000 h @ 105 °C | Gerçek ömür sıcaklık ve ripple ile hesaplanır |
| Kaçak akım | DC'de sızan akım | Pil ile çalışan cihazlarda ve zamanlamada önemli |
| DC bias eğrisi (MLCC) | Gerilim altında efektif kapasite | Üretici aracında kontrol et |
| Güvenlik sınıfı (X1, X2, Y1, Y2) | Şebeke kapasitörü sertifikası | Yalnızca sertifikalı parça |
| Esnek terminasyon | Eğilmeye dayanıklı uç yapısı | Kenara yakın yerleşimde tercih et |

### Elektrolitik ömür hesabı

Kural (Arrhenius yaklaşımı): Her 10 °C düşüş ömrü kabaca iki katına çıkarır. `L = L0 · 2^((T0 − T)/10)`

| Çalışma sıcaklığı | 2000 h @ 105 °C'lik kapasitörün beklenen ömrü |
|---|---|
| 105 °C | 2 000 h (~3 ay) |
| 65 °C | 32 000 h (~3,7 yıl) |
| 45 °C | 128 000 h (~14,6 yıl) |

Ripple akımı kapasitörü içeriden ısıttığı için gerçek çekirdek sıcaklığı ortamdan yüksektir. Hesabı ortam sıcaklığıyla değil, çekirdek sıcaklığıyla yap. Uzun ömürlü bir üründe **105 °C dereceli ve yüksek ömürlü (ör. 5000–10 000 h)** seri seç, kapasitörü ısı kaynaklarından uzak tut.

## 4. Gerçek model (parazitikler)

```
          ┌──────── R_kaçak ─────────┐
   ───────┤                            ├───────
          └── ESR ── ESL ── C ─────────┘
```

| Parazitik | Etkisi |
|---|---|
| **ESR** | Kayıp ve ısınma; filtrenin en düşük empedansı |
| **ESL** | SRF üstünde kapasitör endüktör gibi davranır (bkz. [decoupling](../../Konular/guc-ve-decoupling/ozet.md)) |
| **Kaçak direnç** | Zamanla yükün boşalması; elektrolitikte belirgindir |
| **Dielektrik soğurma** | Kapasitör boşaltıldıktan sonra üzerinde gerilim yeniden belirir. Örnekle-tut (sample & hold) ve hassas integratörlerde hataya yol açar. C0G ve polipropilen film en iyisidir |
| **Piezoelektrik etki** (Class 2) | Titreşim gerilime dönüşür (**mikrofonik gürültü**). Tersi de olur: AC gerilim kapasitörü titreştirir ve duyulabilir ses çıkar ("şarkı söyleyen kapasitör") |

## 5. Şematikte kullanım ve tipik devreler

### 5.1 Decoupling ve bulk

Ayrı derste ayrıntılı: [Güç ve decoupling](../../Konular/guc-ve-decoupling/ozet.md).

### 5.2 Enerji tutma (hold-up)

**Senaryo:** Besleme kesildiğinde MCU'nun son verileri flash'a yazması için zaman kazanmak.
- `t = C·(V1² − V2²) / (2P)`
- 100 µF, 12 V → 9 V (regülatörün çalışabildiği en düşük giriş), 1 W yük: **3,15 ms**
- Yazılım tarafı: Düşük gerilim algılama (ör. STM32 PVD) kesintiyi erken haber verir, BOR ise gerilim çok düşünce temiz reset sağlar.

### 5.3 RC alçak geçiren filtre

- `f_c = 1/(2πRC)`. 1 kΩ, 100 nF → 1,59 kHz.
- ADC girişinde **anti-aliasing** filtresi olarak kullanılır: kesim frekansı örnekleme frekansının yarısının altında olmalı.
- Kararlı bir kesim frekansı istiyorsan C0G veya X7R kullan (Y5V asla).
- → Alçak mı yüksek mi, ne zaman hangisi, aliasing ve gaz sensörü örneği: [bölüm 10](#10-derinleştirme-rc-filtre-ve-aliasing)

### 5.4 Zamanlama ve gecikme

- `τ = RC`. 1τ'da %63, 5τ'da ~%99'a ulaşır.
- **Buton debounce:** 10 kΩ, 100 nF → τ = 1 ms.
- Hassas zamanlama gerekiyorsa C0G veya film kullan. Class 2 kapasitörle zaman sıcaklıkla kayar.

### 5.5 AC kuplaj (yüksek geçiren)

- DC seviyesini engelleyip sinyali geçirmek için kullanılır.
- Yük 10 kΩ, istenen kesim 10 Hz → `C = 1/(2π × 10 kΩ × 10 Hz) ≈ 1,6 µF`.
- Hassas analog sinyalde Class 2'nin mikrofonik gürültüsüne ve DC bias'a dikkat et; film tercih edilir.
- → Adım adım anlatım ve "ne zaman yüksek geçiren?" sorusu: [bölüm 10.4](#104-yüksek-geçiren-ac-kuplaj)

### 5.6 Kristal yük kapasitörleri

- `C1 = C2 = 2·(C_L − C_stray)`. C_L = 12 pF, C_stray = 3 pF → **18 pF**.
- **Mutlaka C0G.** Ayrıntılar: [Mikrodenetleyici donanımı](../05-mikrodenetleyici-donanimi/ozet.md).

### 5.7 Snubber

- Röle kontakları veya anahtarlama elemanları üzerinde seri RC, çınlamayı ve ark oluşumunu azaltır.
- Darbe ve yüksek dV/dt'ye dayanıklı **film** kapasitör kullanılır.

### 5.8 Şebeke filtresi: X ve Y kapasitörler

```
  L ──┬───┤ CMC ├───┬──────── cihaz
      │             │
     [X2]          [Y2]
      │             │
      │             ├──────── PE (koruma toprağı)
      │             │
      │            [Y2]
      │             │
  N ──┴───┤ CMC ├───┴──────── cihaz

  X2: hat ile nötr arasında · Y2: hat ve nötrden toprağa · CMC: ortak mod bobini
```

| Sınıf | Nereye bağlanır | Arıza modu gereksinimi |
|---|---|---|
| **X (X1, X2)** | Hat ile nötr arasına | Arızada yangın çıkarmamalı |
| **Y (Y1, Y2)** | Hat/nötr ile koruma toprağı (PE) arasına | Arızada **açık devre** olmalı; aksi halde kasa elektriklenir |

- Y kapasitörleri toprağa **kaçak akım** akıtır: 4,7 nF, 230 V, 50 Hz → **0,34 mA**. Ürün standardındaki dokunma akımı sınırını aşmamalı.
- **Asla sertifikasız kapasitör kullanma.** Sertifika sınıfı kapasitörün gövdesinde yazar (IEC 60384-14).

### 5.9 Inrush akımı

- `I = C·dV/dt`. 1000 µF, 100 µs içinde 12 V'a şarj olursa → **120 A** tepe akım.
- Sonuçları: sigorta atar, konnektör ve anahtar kontakları aşınır, tantal kapasitör patlayabilir, besleme anlık çöker.
- Çözümler: NTC termistör, soft-start özellikli regülatör veya yük anahtarı, hot-swap denetleyici.

## 6. PCB / layout

- **Decoupling yerleşimi:** [Güç ve decoupling, bölüm 8](../../Konular/guc-ve-decoupling/ozet.md).
- **Elektrolitik:**
  - Kutup işaretini silkscreen'de net göster (+ ve şerit tarafı).
  - Isı kaynaklarından (regülatör, güç direnci, işlemci) uzak tut; ömür doğrudan buna bağlı.
  - Büyük kutu tiplerinde üstteki basınç tahliye (vent) yarığının açılabilmesi için üstünü kapatma.
- **MLCC çatlamasına karşı:**
  - Kart kenarından, vida deliklerinden, konnektörlerden ve panel kırma çizgilerinden (V-cut) uzak tut.
  - Kırma çizgisine yakın kalmak zorundaysan uzun kenarını çizgiye **paralel** yerleştir (gerilmeyi azaltır).
  - Riskli bölgelerde **esnek terminasyonlu** (soft termination) MLCC kullan.
  - Bataryaya veya kritik bir raya doğrudan bağlı büyük MLCC'lerde kısa devre riskini azaltmak için seri iki kapasitör veya "open-mode" tip MLCC düşünülebilir.
  - Büyük MLCC'yi havyayla lehimlerken ani ısıl şok çatlatabilir; önce kartı ısıt.
- **Hassas analog yol:** Titreşim olan yerlerde sinyal yolunda Class 2 yerine C0G veya film kullan.
- **Şebeke kapasitörleri:** Giriş konnektörüne yakın; creepage ve clearance mesafelerine uy.

## 7. EMC açısından

- **Konnektörde filtre kapasitörü:** Küçük değerli (100 pF – 10 nF) kapasitörler yüksek frekanslı gürültüyü toprağa kısa devre eder. Etkinliği montaj endüktansına bağlıdır; GND bağlantısı çok kısa olmalı.
- **Üç uçlu ve feedthrough kapasitörler** çok düşük ESL sayesinde yüksek frekansta normal kapasitörlerden çok daha iyi filtreler.
- **X/Y kapasitörler** şebekeye iletilen emisyonu bastırır: X diferansiyel modu, Y ortak modu hedefler.
- **Hızlı sinyal hatlarına büyük kapasitör koyma:** Sinyal kenarlarını bozar ve sürücüyü zorlar.
- **Reset hattındaki kapasitör** (STM32'de tipik 100 nF) ESD ve hızlı bozucuların istenmeyen reset üretmesini azaltır.

## 8. Arıza modları ve sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| MLCC'yi kart kenarına, vida deliğine yakın koymak | Eğilmede çatlar, kısa devre ve yanma | Gerilme bölgelerinden uzak, esnek terminasyon |
| Elektrolitiği ısı kaynağının yanına koymak | Kurur: ESR artar, kapasite düşer | Uzak yerleşim, ömür hesabı |
| Ters polarite | Şişme, patlama | Net silkscreen, montaj kontrolü |
| Tantalı derating'siz kullanmak | Kısa devre, yanma | ~%50 derating, inrush sınırlama veya polimer tantal |
| DC bias kaybını unutmak | Filtre ve decoupling yetersiz kalır | Üretici eğrisi |
| Zamanlamada Class 2 kapasitör | Sıcaklıkla zaman kayar | C0G veya film |
| Şebekede sertifikasız kapasitör | Yangın ve elektrik çarpması riski | Sertifikalı X2/Y2 |
| Büyük bulk kapasitörün inrush'ını hesaba katmamak | Sigorta atar, kontaklar yıpranır | Soft-start, NTC |
| Analog yolda mikrofonik gürültü | Titreşime bağlı sinyal gürültüsü | C0G veya film |
| Elektrolitiği soğukta düşünmemek | ESR artar, regülatör kararsızlaşabilir | Sıcaklık aralığında ESR'yi kontrol et |

**Arıza modu özeti:** MLCC çatlayınca genellikle **kısa devre** olur. Elektrolitik yaşlandıkça yavaşça bozulur (ESR artar). MnO₂ tantal ise ani **kısa devre** ve yanma ile arızalanabilir.

## 9. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Class 1 / Class 2** | Kararlı paraelektrik (C0G) / yüksek ε'lu ferroelektrik (X7R, X5R) seramik |
| **DC bias** | DC gerilim altında kapasite kaybı |
| **Yaşlanma (aging)** | Class 2 seramikte kapasitenin zamanla azalması |
| **Ripple akımı** | Kapasitörden geçen AC akım; ısınmaya yol açar |
| **Endurance** | Belirtilen sıcaklıkta garanti edilen ömür |
| **Dielektrik soğurma** | Boşaltıldıktan sonra gerilimin kısmen geri gelmesi |
| **Kendini onarma (self-healing)** | Film kapasitörde delinen noktanın buharlaşarak yalıtılması |
| **X / Y kapasitör** | Şebekede hat-nötr / hat-toprak arası güvenlik kapasitörü |
| **Inrush** | İlk enerjilemedeki ani şarj akımı |
| **Mikrofonik etki** | Titreşimin elektriksel gürültüye dönüşmesi |
| **Esnek terminasyon** | Eğilmeye dayanıklı MLCC uç yapısı |
| **Örnekleme frekansı (f_s)** | ADC'nin saniyede aldığı ölçüm sayısı |
| **Nyquist frekansı** | f_s/2; bunun üstündeki frekanslar sahte frekansa dönüşür |
| **Aliasing** | Hızlı bir sinyalin örneklemede yavaş, sahte bir sinyal gibi görünmesi |
| **Anti-aliasing filtresi** | ADC'den önce f_s/2 üstünü bastıran analog filtre (çoğunlukla RC) |

## 10. Derinleştirme: RC filtre ve aliasing

> Bu bölüm [5.3](#53-rc-alçak-geçiren-filtre) ve [5.5](#55-ac-kuplaj-yüksek-geçiren)'i adım adım açar. Okuma sırası: temel fikir (10.1–10.2) → iki filtre ayrı ayrı (10.3–10.4) → ADC ve aliasing (10.5–10.8) → gerçek tasarım örneği (10.9) → alıştırmalar (10.10).
>
> Aliasing'in tamamı (katlanma, DC'ye katlanma, firmware, EMC testi) ayrı derste: [Aliasing ve anti-aliasing filtresi](../../Konular/aliasing-ve-anti-aliasing-filtresi/ozet.md).

### 10.1 Temel fikir: yavaş kısım, hızlı kısım

Her sinyal iki parçadan oluşur: **yavaş** değişen kısım ve **hızlı** değişen kısım. Filtre bir elek gibidir:
- **Alçak geçiren** yavaş kısmı tutar, hızlı kısmı atar.
- **Yüksek geçiren** hızlı kısmı tutar, yavaş kısmı atar.

**Kapasitörün tek kuralı:** Yavaş değişime karşı **duvar**, hızlı değişime karşı **tel** gibidir. Filtrenin türünü kapasitörün **nerede durduğu** belirler:

```
Alçak geçiren                          Yüksek geçiren (AC kuplaj)

giriş ──[R]──┬── çıkış                 giriş ──[C]──┬── çıkış
             │                                      │
            [C]  ← C toprağa                       [R]  ← R toprağa (çoğu zaman
             │                                      │       sonraki katın girişi)
            GND                                    GND
```

- **C toprağa bağlıysa:** Hızlı kısım "tel" üzerinden toprağa kaçar, yavaş kısım kalır → **alçak geçiren**.
- **C yolun üstündeyse:** Yavaş kısım "duvara" çarpar, sadece hızlı kısım geçer → **yüksek geçiren**.

**Örnek:** Giriş = 1,5 V sabit seviye + yavaş dalga (bilgi, ör. gaz seviyesi) + hızlı tırtıklar (gürültü, ör. 50 Hz).

| | Sabit seviye | Yavaş dalga | Hızlı tırtıklar |
|---|---|---|---|
| Alçak geçiren çıkışı | Kalır | Kalır | **Gider** |
| Yüksek geçiren çıkışı | **Gider** | **Gider** | Kalır |

### 10.2 Hangisini ne zaman koyarım? (3 soru)

1. **Bilgi** yavaş mı değişiyor, hızlı mı?
2. **Gürültü** yavaş mı, hızlı mı?
3. Bilgiyi tutan filtreyi seç. f_c'yi bilgi ile gürültünün **arasına** koy.

| Sinyal | Bilgi | Gürültü | Filtre |
|---|---|---|---|
| Gaz sensörü → ADC | Yavaş (saniyeler) | Hızlı (50 Hz, regülatör) | **Alçak geçiren** |
| NTC sıcaklık | Yavaş | Hızlı | **Alçak geçiren** |
| Buton | Yavaş (basma) | Hızlı (kontak sıçraması) | **Alçak geçiren** |
| Besleme hattı | Sabit DC | Hızlı | **Alçak geçiren** (decoupling kapasitörü aslında budur) |
| Mikrofon | Hızlı (ses) | Yavaş (DC seviye) | **Yüksek geçiren** |

- **Gaz dedektöründe neredeyse her yerde alçak geçiren** kullanılır, çünkü ölçülen her şey (gaz, sıcaklık, besleme) yavaş değişir. Yüksek geçiren nadiren gerekir.
- **f_c'nin yeri:** Gaz bilgisi 1 Hz'in altında, gürültü 50 Hz ve üstünde → arada **~10 Hz** iyi bir seçimdir (bkz. 10.9).
- **Kartta yeri:** Alçak geçirenin kapasitörü **ADC pininin dibine** konur. Böylece filtreden sonra iz üzerinden yeni gürültü binmez.

### 10.3 Alçak geçiren: RC filtre ne yapar?

**Benzetme:** R dar bir boru, C bir kova. Giriş gerilimi kovayı doldurmaya çalışan sudur.
- **Yavaş değişim:** Kova dolup boşalmaya yetişir; çıkış girişi takip eder.
- **Hızlı değişim:** Kova dar borudan dolup boşalmaya yetişemez; çıkış neredeyse düz kalır.

**Gerilim bölücü bakışı:** R ve C seri bir gerilim bölücüdür. Kapasitörün "direnci" `X_C = 1/(2πfC)` frekans arttıkça düşer.
- Düşük frekansta C açık devre gibidir → çıkış ≈ giriş.
- Yüksek frekansta C kısa devre gibidir → çıkış ≈ 0.
- **f_c**, `X_C = R` olduğu frekanstır. Burada çıkış girişin **%70,7**'sidir (−3 dB).

| Frekans | Çıkışa geçen |
|---|---|
| f_c / 10 | %99,5 |
| f_c | %70,7 |
| 10 × f_c | %10 |
| 100 × f_c | %1 |

**Kural:** f_c'nin üstünde frekans 10 katına çıkınca çıkış 10'da 1'e düşer (−20 dB/dekad).

**Bedeli:** `τ = RC`. Filtre güçlendikçe (f_c düştükçe) sinyal yavaşlar. Ani bir değişimin %99'una oturmak ~5τ sürer.

### 10.4 Yüksek geçiren: AC kuplaj

Kapasitör **sabit kısmı (DC) durdurur, değişen kısmı (AC) geçirir**:

| | Giriş | Çıkış |
|---|---|---|
| DC kısım | 2,5 V | **0 V** (engellendi) |
| AC kısım | ±0,1 V, 1 kHz | **±0,1 V, 1 kHz** (geçti) |

**Benzetme:** Kapasitör, borunun ortasına gerilmiş lastik bir zardır.
- **Sabit akış (DC):** Su zarı bir kez gerer, sonra akış durur.
- **İleri-geri itme (AC):** Zar ileri geri esner. Su karşıya geçmese de hareket karşı tarafa aktarılır.

Davranış, alçak geçirenin tam aynasıdır:

| Frekans | Çıkışa geçen |
|---|---|
| f_c / 10 | %10 |
| f_c | %70,7 |
| 10 × f_c | %99,5 |

**Hesap: R neden "yük"?** Ayrı bir R koymazsın; kapasitörden sonra gelen katın (ör. op-amp girişi) giriş direnci R'nin yerini tutar.
- Yük 10 kΩ, f_c 10 Hz → `C = 1/(2π × 10 kΩ × 10 Hz) ≈ 1,6 µF`.
- 1,6 µF standart değer değil. **Bir üst değeri** seç: 2,2 µF → f_c ≈ 7,2 Hz. Kesim aşağı kayar; güvenli taraf budur.
- **Yük değişirse f_c de değişir:** Aynı 1,6 µF, 1 kΩ'luk bir kata bağlanırsa f_c ≈ 100 Hz olur.

**Neden film kapasitör?** Kapasitör sinyal yolunda seri durur; kusurları doğrudan sinyale karışır.
- **Mikrofonik etki:** X7R titreşimi gerilime çevirir; karta vurunca sinyalde gürültü görürsün.
- **DC bias:** X7R'nin kapasitesi DC gerilimle düşer. 1,6 µF yarıya inerse f_c 10 Hz'den 20 Hz'e çıkar ve sinyalin alt frekansları da kesilir.
- Film kapasitör bu iki sorunu göstermez.

**Dikkat — gaz sensörüne AC kuplaj konmaz:** Gaz seviyesi tam da **DC bilgidir**; gaz arttıkça çıkış yükselir ve orada kalır. Seri kapasitör bu bilgiyi siler, cihaz kalıcı gazı göremez. AC kuplaj yalnızca bilginin değişen kısımda olduğu sinyallerde (mikrofon, titreşim) kullanılır.

### 10.5 Aliasing nedir? Tekerlek örneği

ADC bir fotoğraf makinesidir. **f_s**, saniyede çektiği fotoğraf sayısıdır.

1. Tekerlek saniyede **50 tur** dönüyor. Sen saniyede **40 fotoğraf** çekiyorsun.
2. İki fotoğraf arasında tekerlek `50 / 40 = 1,25 tur` döner.
3. Tam turu fotoğrafta göremezsin; tekerlek aynı yerde duruyor gibi görünür. Yalnızca artan **0,25 turu** görürsün.
4. Saniyede 40 fotoğraf × 0,25 tur = **10 tur/s**.

Fotoğrafları art arda izleyen biri tekerleğin saniyede 10 tur döndüğünü sanır. Yani **50 Hz sinyal, 40 Hz örneklemede 10 Hz gibi görünür.** Bu sahte frekansa **alias** denir. Filmlerde araba tekerleklerinin yavaş ya da geri dönüyor görünmesi aynı olaydır.

**Sınır (Nyquist):** Bir periyotta en az 2 fotoğraf gerekir. Bu yüzden ancak **f_s/2'nin altındaki** frekanslar doğru görünür.

### 10.6 Hesap tarifi (2 adım)

1. **Kontrol et:** `f < f_s/2` mi? Evet → sorun yok, sinyal kendi frekansında görünür.
2. **Değilse:** f'ye **en yakın f_s katını** bul (f_s, 2·f_s, 3·f_s…). Görünen frekans = `|f − o kat|`.

**Çözümlü örnek:** f_s = 100 Hz, girişte 60 Hz gürültü var.
- f_s/2 = 50 Hz. 60 > 50 → aliasing var.
- 60'a en yakın 100'ün katı: **100**.
- `|60 − 100| = 40 Hz`. Gürültü kayıtlı veride **40 Hz** gibi görünür.

| f_s | Gerçek f | f_s/2 | En yakın kat | Görünen |
|---|---|---|---|---|
| 40 Hz | 50 Hz | 20 Hz | 40 | **10 Hz** |
| 100 Hz | 60 Hz | 50 Hz | 100 | **40 Hz** |
| 100 Hz | 210 Hz | 50 Hz | 200 | **10 Hz** |
| 1 kHz | 950 Hz | 500 Hz | 1000 | **50 Hz** (şebeke gürültüsü sanırsın!) |
| 100 Hz | 30 Hz | 50 Hz | — | **30 Hz** (alias yok) |

### 10.7 Filtre ADC'den önce mi, sonra mı?

**Aliasing'e karşı filtre mutlaka ADC'den önce** konur. Nedeni sayılarla görülür: f_s = 100 Hz iken 10 Hz'lik gerçek sinyal ile 110 Hz'lik gürültünün ADC'den çıkan değerleri:

| Ölçüm no | 10 Hz gerçek sinyal | 110 Hz gürültü |
|---|---|---|
| 0 | 0,00 | 0,00 |
| 1 | 0,59 | 0,59 |
| 2 | 0,95 | 0,95 |
| 3 | 0,95 | 0,95 |
| 4 | 0,59 | 0,59 |

İki sütun **birebir aynıdır**. Yazılım yalnızca bu sayıları görür; hangisinin gerçek olduğunu bilemez. Çorbaya düşen tuz gibi: karıştıktan sonra ayıklanamaz, düşmeden önce durdurulmalıdır. Bu işi yapan RC filtreye **anti-aliasing filtresi** denir.

**ADC'den sonraki (yazılım) filtre ne işe yarar?** f_s/2'nin **altındaki** gürültü karışmaz, kendi frekansında kalır; yazılım onu ayırabilir. Örnek: f_s = 1 kHz iken 50 Hz şebeke gürültüsü 500 Hz'in altındadır; 20 ms ortalama onu tamamen siler. Yazılım filtresi ucuzdur, sonradan değiştirilebilir ve sıcaklıkla kaymaz.

| | ADC'den **önce** (RC) | ADC'den **sonra** (yazılım) |
|---|---|---|
| Neye karşı | f_s/2'nin **üstündeki** gürültü | f_s/2'nin **altındaki** gürültü |
| Neden orada | Karıştıktan sonra ayrılamaz | Karışmadığı için ayrılabilir |
| Gaz sensörü örneği | 10 kΩ + 1,5 µF | 20 ms ortalama (50 Hz için) |

İkisi birbirinin yerine geçmez; gerçek kartta ikisi birlikte kullanılır.

### 10.8 f_c neden f_s/2'nin çok altında seçilir?

Tek RC yumuşak keser (10.3 tablosu).
- **Kötü seçim:** f_s = 1 kHz, f_c = 500 Hz. 900 Hz'lik gürültünün **%49'u** geçer ve 100 Hz'e alias olur.
- **Pratik kural:** `ölçmek istediğin sinyal < f_c ≪ f_s/2`. f_c'yi f_s/2'nin en az 10'da biri seç; daha sert kesim gerekiyorsa f_s'yi artır veya 2. kademe filtre ekle.

### 10.9 Tasarım örneği: gaz sensörü girişi

LEL dedektöründe sensör sinyali saniyeler mertebesinde değişir; asıl düşman 50 Hz şebeke kuplajı ve anahtarlamalı regülatör gürültüsüdür.

- **Seçim:** f_s = 1 kHz (f_s/2 = 500 Hz), R = 10 kΩ, C = 1,5 µF
- `f_c = 1/(2π × 10 kΩ × 1,5 µF) ≈ 10,6 Hz`
- `τ = 15 ms`, `5τ = 75 ms`; sensörün kendi tepki süresi yanında ihmal edilebilir.

| Frekans | Ne? | Çıkışa geçen |
|---|---|---|
| 1 Hz | Gaz sinyali | %99,6 |
| 10 Hz | Hızlı değişim | %73 |
| 50 Hz | Şebeke gürültüsü | %21 |
| 500 Hz | f_s/2, alias sınırı | %2 |

- **50 Hz alias değildir** (500 Hz'in altında), ama yine de gürültüdür. RC onu %21'e indirir. Yazılımda **20 ms (20 örnek) ortalama** almak 50 Hz'i ve tüm katlarını sıfırlar, çünkü bir tam periyodun ortalaması sıfırdır.
- **Yük deposu:** 1,5 µF, ADC'nin ~5 pF örnekleme kapasitörünün yanında çok büyüktür. 10 kΩ kaynak empedansına rağmen ADC doğru okur. Bkz. [MCU dersi – ADC örnekleme](../05-mikrodenetleyici-donanimi/ozet.md).
- **Kapasitör türü:** 1,5 µF C0G büyük ve pahalıdır. 3,3 V'ta, ≥ 16 V dereceli X7R yeterlidir; f_c'nin ±%20 kayması bu uygulamada sorun değildir. Y5V kullanma.
- **EMC notu:** RF bağışıklık testindeki 1 kHz AM modülasyonu, f_s = 1 kHz'de DC'ye katlanır ve ortalama onu silemez. Bu yüzden **f_s = 1,2 kHz + 24 örnek ortalama** (yine 20 ms) daha güvenlidir. Bkz. [Aliasing dersi, bölüm 8](../../Konular/aliasing-ve-anti-aliasing-filtresi/ozet.md#8-tasarım-örneği-lel-dedektörü-girişi).

### 10.10 Kendin dene

1. f_s = 100 Hz, girişte 90 Hz gürültü. Kayıtta hangi frekansta görünür?
2. f_s = 100 Hz, girişte 30 Hz sinyal. Hangi frekansta görünür?
3. f_s = 200 Hz, girişte 190 Hz gürültü. Hangi frekansta görünür?
4. 10 kΩ direnç ile f_c ≈ 16 Hz istiyorsun. Kapasitör kaç olmalı?
5. Pil gerilimini ölçüyorsun (saatler içinde değişir). Kartta 500 kHz'lik regülatör gürültüsü var. Hangi filtreyi koyarsın?
6. 1,6 µF'lık AC kuplaj kapasitörünü 10 kΩ yerine 1 kΩ giriş dirençli bir kata bağlarsan f_c kaç olur?
7. f_s = 1 kHz. 50 Hz şebeke gürültüsünü yazılımla temizleyebilir misin? Neden?

<details>
<summary>Cevaplar</summary>

1. 90 > 50 → en yakın kat 100 → `|90 − 100| =` **10 Hz**
2. 30 < 50 → alias yok → **30 Hz**
3. 190 > 100 → en yakın kat 200 → `|190 − 200| =` **10 Hz**
4. `C = 1/(2π × 10 kΩ × 16 Hz) ≈` **1 µF**
5. **Alçak geçiren.** Bilgi yavaş, gürültü hızlı. C, ADC pininin dibinde toprağa.
6. `f_c = 1/(2π × 1 kΩ × 1,6 µF) ≈` **100 Hz**. R 10 kat küçüldü, f_c 10 kat büyüdü.
7. **Evet.** 50 < 500 (f_s/2) olduğu için alias olmaz; gürültü kendi frekansında kalır ve 20 ms ortalama onu siler.

</details>

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.2, bölüm 10):

- [x] Elektrolitik: çalışma gerilimi ≤ %80 anma; ömür hesabı (sıcaklık + ripple); polarite işareti net
- [x] Zamanlama, filtre ve osilatör kapasitörleri C0G (veya film)
- [x] Şebeke tarafında yalnızca sertifikalı X/Y kapasitörler; Y kaçak akımı hesaplandı
- [x] Büyük bulk kapasitörlerin inrush akımı değerlendirildi
- [x] MLCC'ler kart kenarı, vida deliği, konnektör ve kırma çizgilerinden uzak

## Kontrol soruları

→ [quiz.md](quiz.md) · 16 soru, 6'sı hesap
