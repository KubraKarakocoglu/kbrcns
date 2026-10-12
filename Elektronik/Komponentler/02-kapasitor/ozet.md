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

### 5.4 Zamanlama ve gecikme

- `τ = RC`. 1τ'da %63, 5τ'da ~%99'a ulaşır.
- **Buton debounce:** 10 kΩ, 100 nF → τ = 1 ms.
- Hassas zamanlama gerekiyorsa C0G veya film kullan. Class 2 kapasitörle zaman sıcaklıkla kayar.

### 5.5 AC kuplaj (yüksek geçiren)

- DC seviyesini engelleyip sinyali geçirmek için kullanılır.
- Yük 10 kΩ, istenen kesim 10 Hz → `C = 1/(2π × 10 kΩ × 10 Hz) ≈ 1,6 µF`.
- Hassas analog sinyalde Class 2'nin mikrofonik gürültüsüne ve DC bias'a dikkat et; film tercih edilir.

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

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.2, bölüm 10):

- [x] Elektrolitik: çalışma gerilimi ≤ %80 anma; ömür hesabı (sıcaklık + ripple); polarite işareti net
- [x] Zamanlama, filtre ve osilatör kapasitörleri C0G (veya film)
- [x] Şebeke tarafında yalnızca sertifikalı X/Y kapasitörler; Y kaçak akımı hesaplandı
- [x] Büyük bulk kapasitörlerin inrush akımı değerlendirildi
- [x] MLCC'ler kart kenarı, vida deliği, konnektör ve kırma çizgilerinden uzak

## Kontrol soruları

→ [quiz.md](quiz.md) · 12 soru, 5'i hesap
