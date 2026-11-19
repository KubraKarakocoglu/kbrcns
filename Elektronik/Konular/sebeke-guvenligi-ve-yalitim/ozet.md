# Şebeke güvenliği ve yalıtım

- **Oluşturma:** 2026-11-18
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Bağlantılı:** [PCB yerleşim, bölüm 6 (clearance/creepage)](../pcb-yerlesim-ve-iz-cizimi/ozet.md#6-mesafeler-clearance-ve-creepage) · [Kapasitör (X/Y)](../../Komponentler/02-kapasitor/ozet.md) · [Güç katı: koruma ve regülatör](../guc-kati-koruma-ve-regulator/ozet.md) · [EMC için kart tasarımı, bölüm 8](../../EMC/02-emc-icin-kart-tasarimi/ozet.md#8-güç-girişi) · [EMC testleri ve standartlar](../../EMC/03-emc-testleri-ve-standartlar/ozet.md) · Sonraki: [Triyak ve faz kontrolü](../triyak-ve-faz-kontrolu/ozet.md) · [Şebekeli güç kaynakları](../sebekeli-guc-kaynaklari/ozet.md)

> Sayısal değerler **tipik başlangıç noktalarıdır**; tasarım değeri için ürünün **güvenlik standardı** ve onun **güncel baskısı** esastır. Bu derste standart tablolarından alınan sayılar açık kaynaklardan (TI, üretici notları) karşılaştırılarak doğrulandı; standartların ücretli tam metinleri bu notlarda yoktur. Sertifikaya giden bir üründe standardı temin et ve tabloyu **oradan** oku. Bu ders doğru soruları sormayı ve hesabı yapmayı öğretir; sertifikanın yerine geçmez.
>
> **Uyarı:** Şebeke gerilimi ölümcüldür. Şebekeli bir kartı enerjilendirmeden önce bölüm 14'ü oku.
>
> **Okuma planı:** 1. oturum: bölüm 1–4 (neden, dört parametre, yalıtım türleri, rakamlar) · 2. oturum: 5–9 (PCB uygulaması, sigorta/MOV/NTC, X-Y kapasitör, kaçak akım, PE) · 3. oturum: 10–16.

---

## ⚡ Hızlı tekrar

1. 230 V şebekenin **tepe değeri 325 V**'tur (253 V'ta 358 V). Üstüne **2,5–4 kV'luk geçici darbeler** biner. Şebeke tasarımı "normal çalışma"dan çok **arıza ve darbe** tasarımıdır.
2. Dört soru her şeyi belirler: **çalışma gerilimi**, **aşırı gerilim kategorisi (OVC)**, **kirlilik derecesi (PD)**, **yalıtım türü** (temel / güçlendirilmiş). Mesafeler bu dördünden tablodan çıkar.
3. **Clearance** (havadan) darbe gerilimine; **creepage** (yüzeyden) çalışma gerilimi, kirlilik ve malzeme grubuna bağlıdır. Her ikisini ayrı ayrı sağla.
4. 230 V, OVC II, PD2, FR-4 için **temel** yalıtımda clearance **1,5 mm** (ITE'de çoğu kez 2,0 mm), creepage **2,5 mm**; **güçlendirilmiş** yalıtımda clearance **3,0 mm** (ITE'de 4,0 mm), creepage **5,0 mm**.
5. **Güçlendirilmiş = clearance için bir üst darbe basamağı, creepage için iki katı.** Test gerilimi 1500 Vac'tan 3000 Vac'a çıkar.
6. **X kapasitör** hat–nötr arasındadır, arızada **kısa devre** olur (sigorta atar). **Y kapasitör** hat–toprak (veya primer–sekonder) arasındadır, arızada **açık devre** olmalıdır. İkisi de **sertifikalı** olmalı.
7. Y kapasitörün **kaçak akımı** `I = 2π·f·C·V`. Sınırlar: Class II **0,25 mA**, el tipi Class I **0,75 mA**, diğer Class I **3,5 mA**.
8. Şebekeye ilk girişte: **izolasyon trafosu + akım sınırlama (seri ampul) + diferansiyel prob**. Osiloskop toprağını şebekeli bir düğüme asla doğrudan bağlama.

## 🧮 Formül kartı

| Formül | Ne zaman kullanılır | Örnek |
|---|---|---|
| `V_tepe = √2 · V_rms` | Tepe gerilim | 230 V → **325 V**; 264 V → **373 V** |
| `I_kaçak = 2π · f · C · V` | Y kapasitör kaçak akımı | 2,2 nF, 230 V, 50 Hz → **0,16 mA** |
| `C_max = I_sınır / (2π · f · V)` | Kaçak akım limitinden en büyük Y kapasitör | 0,25 mA, 264 V, 60 Hz → **2,5 nF** |
| `τ = R · C`, `V(t) = V₀ · e^(−t/τ)` | X kapasitör deşarjı | 220 nF, 2 MΩ → τ = **0,44 s** |
| `P_bleeder = V² / R` | Deşarj direncinin sürekli kaybı | 230 V, 3,6 MΩ → **14,7 mW** |
| `E = ½ · C · V²` | Bulk kapasitörün ilk şarj enerjisi (NTC seçimi) | 100 µF, 325 V → **5,3 J** |
| `I_tepe = V_tepe / R_NTC,soğuk` | İlk açılış tepe akımı | 325 V / 10 Ω → **32,5 A** |
| `I_sigorta ≥ I_max / 0,75` | Sigorta değeri (tipik derating) | 1,74 A → ≥ 2,32 A → **2,5 A T** |
| Güçlendirilmiş: `CL → bir üst basamak`, `CR × 2` | Temelden güçlendirilmişe geçiş | 1,5 mm → **3,0 mm**; 2,5 mm → **5,0 mm** |
| `V_DC = √2 · V_AC` | Hi-pot'ta AC test gerilimini DC'ye çevirme | 3000 Vac → **4243 Vdc** |

---

## 1. Neden şebeke ayrı bir dünya?

Şebekeyi bir **yangın hattı** gibi düşün. Basınç sabit görünür; ama biri vanayı aniden kapatınca borudan **su darbesi** geçer. Elektrikte vana, büyük bir yükün ya da yıldırımın devreye girip çıkmasıdır: sabit 230 V'un üstüne mikrosaniyelik kilovolt darbeleri biner.

| | 5 V mantık kartı | 230 V şebeke |
|---|---|---|
| Tepe gerilim | 5 V | **325 V** (253 V'ta 358 V) |
| Geçici darbe | Birkaç volt | **2,5–4 kV** (OVC II–III) |
| Kısa devre akımı | Besleme sınırlar | Hat ve sigortaya bağlı: **yüzlerce amper ve üstü** |
| Hatanın sonucu | Parça yanar | **Yangın, elektrik çarpması** |
| Yanlış tasarımın bedeli | Bir kart | **Bir insan** |

**Vücut için eşikler** (50/60 Hz AC, IEC 479 değerleri):

| Akım | Etki |
|---|---|
| **0,5 mA** | Algılama eşiği: karıncalanma |
| **≈ 10 mA** | Bırakamama eşiği: kas kasılır, el iletkeni bırakamaz |
| **≈ 30 mA** (1 s) | Ventriküler fibrilasyon (kalp ritmi bozulması) riski; süre kısaldıkça eşik yükselir (50 ms'de ≈ 300 mA) |

Değerler akımın vücutta izlediği yola göre bir katsayıyla düzeltilir. Bölüm 8'deki dokunma akımı sınırları (0,25–3,5 mA) bu eşiklerin çok altında tutulur: amaç **hissettirmemek** ve arızada bile güvenli kalmaktır.

**Güvenlik tasarımının mantığı:** tek bir önleme güvenme; **üst üste katmanlar** kur. Yalıtım (temel), ikinci katman (ek yalıtım veya koruma toprağı), korumayı kesen eleman (sigorta), ve erişimi kapatan kutu. Bir katman bozulursa diğeri insanı korur.

## 2. Dört parametre: tablolar nereden okunur?

Clearance ve creepage tablosuna girmeden önce dört şeyi bilmen gerekir.

### 2.1 Çalışma gerilimi

- **Creepage** için **RMS çalışma gerilimi**, **clearance** için **tepe değer ve darbe gerilimi** esastır (TI SLUAAR5).
- Çalışma gerilimi, ürünün **anma gerilim aralığının üst ucudur** (100–240 V ürün → 240 V) ve tablolarda **250 V satırına** denk gelir.
- Toleransı (%10) ayrıca hesaba katarsan 264 V olur ve **320 V satırına** çıkarsın. Hangisinin geçerli olduğunu ürün standardı söyler; emin değilsen **büyük satırı** kullan.

### 2.2 Aşırı gerilim kategorisi (OVC)

Binanın su tesisatında darbeler **ana vananın yanında en büyük**, musluğun ucunda en küçüktür. Elektrikte de aynısı: tesisatın girişine yakın yerde darbe büyüktür.

| Kategori | Tanım | Örnek | 230/400 V'ta anma darbe gerilimi |
|---|---|---|---|
| **I** | Geçici aşırı gerilimin uygun seviyeye sınırlandığı devreler | Korumalı elektronik devre (şebekeye doğrudan bağlanmaz) | 1,5 kV |
| **II** | Sabit tesisattan beslenen, enerji tüketen cihazlar | Ev aletleri, el aletleri, **prize takılan** cihazlar | **2,5 kV** |
| **III** | Sabit tesisatın kendisindeki ekipman | **Sabit tesisata bağlanan** cihazlar, tesisattaki anahtarlar | **4 kV** |
| **IV** | Tesisatın girişi | Sayaç, ana aşırı akım koruması | 6 kV |

**Kural:** Hangi kategori olduğunu **ürün standardı** söyler (prizli cihaz çoğunlukla II, sabit tesisata bağlanan cihaz çoğunlukla III). Emin değilsen **bir üst kategoriyi** al; maliyeti birkaç milimetre, kazancı güvenliktir.

### 2.3 Kirlilik derecesi (PD)

Kartın çevresindeki **toz ve nem** ne kadar? Kir yüzeyde iletken bir film oluşturur ve creepage'i fiilen kısaltır.

| PD | Ortam | Örnek |
|---|---|---|
| **PD1** | Kirlilik yok ya da yalnızca kuru, iletken olmayan | Mühürlü, kaplanmış veya dolgulu devre |
| **PD2** | İletken olmayan kirlilik; ara sıra yoğuşmayla iletken olabilir | Ofis, ev, laboratuvar |
| **PD3** | İletken kirlilik ya da yoğuşmayla iletken olacak kuru kirlilik | Fabrika, endüstriyel saha |
| **PD4** | Kalıcı iletkenlik (iletken toz, yağmur, ıslaklık) | Açık dış ortam |

**Başlangıç varsayımı:** Ev/ofis içi ürün **PD2**; endüstriyel sahada veya dışarıda çalışan ürün **PD3**. Kaplama, potting veya mühürlü kutu PD'yi düşürebilir, ama standart bunu **açıkça** kabul ediyorsa ve sertifikasyon bunu onaylıyorsa.

### 2.4 Malzeme grubu ve CTI

**CTI (Comparative Tracking Index)**, malzemenin kirli suyla ıslatılmış yüzeyinde **iz (karbon yolu) oluşmadan** dayandığı gerilimdir. Yüksek CTI → malzeme "izlenmeye" dayanıklı → creepage küçülür.

| Malzeme grubu | CTI aralığı |
|---|---|
| I | ≥ 600 |
| II | 400 ≤ CTI < 600 |
| IIIa | 175 ≤ CTI < 400 |
| IIIb | 100 ≤ CTI < 175 |

- Yaygın **FR-4**'ün CTI'sı genellikle **175** civarındadır (IIIa/IIIb sınırı). **CTI bilinmiyorsa IIIb** varsay.
- Kart malzemesinin CTI'sını üreticinin malzeme datasheet'inden öğren; "FR-4" yazması yetmez.

### 2.5 Rakım

Standart tablolar **2000 m**'ye kadar geçerlidir. Havanın yoğunluğu düştükçe ark daha kolay atlar: clearance **çarpanla büyütülür**: 4000 m'de **×1,29** (3 mm → 3,87 mm), 5000 m'de **×1,48**. Ürün 2000 m üstünde kullanılacaksa bu çarpanı uygula.

## 3. Yalıtım türleri ve cihaz sınıfları

Kapı kilidi benzetmesi:

| Yalıtım | Benzetme | Ne yapar |
|---|---|---|
| **Fonksiyonel** | Kilit yok, yalnızca çerçeve | Cihazın **çalışması** için; güvenlik sağlamaz |
| **Temel (basic)** | Tek kilit | Elektrik çarpmasına karşı **tek kademe** koruma |
| **Ek (supplementary)** | İkinci kilit | Temel bozulursa devreye giren **ek** katman |
| **Çift (double)** | Temel + ek | İki ayrı kademe |
| **Güçlendirilmiş (reinforced)** | Tek ama çift kilide eşdeğer kilit | **Tek katman**, çift yalıtıma eşdeğer (ör. trafoda üçlü yalıtımlı tel) |

**Cihaz sınıfları:**

| Sınıf | Koruma | Koruma toprağı (PE) | Örnek |
|---|---|---|---|
| **Class I** | Temel yalıtım **+ PE'ye bağlı kasa** | **Var, zorunlu** | Metal kasalı güç kaynağı, ısıtıcı |
| **Class II** | Çift veya güçlendirilmiş yalıtım | Yok | Plastik kasalı adaptör |
| **Class III** | **SELV** besleme | Gerekmez | SELV adaptörle çalışan cihaz |

Class I'de emniyet halatı vardır: temel yalıtım bozulursa kasa elektriklenir ama PE akımı toprağa taşır ve sigortayı attırır. Class II'de halat yoktur; bunun yerine **iki kilit** vardır.

**SELV ve ES1:** Dokunulabilir alçak gerilim devresinin "güvenli" sayılması için sınırlar (IEC 62368-1 gösterimiyle):

| Büyüklük | ES1 sınırı (normal koşul) | Tek arıza |
|---|---|---|
| Dokunma gerilimi (AC, < 1 kHz) | 30 V rms (= 42,4 V tepe) | 50 V rms |
| Dokunma gerilimi (DC) | 60 V | 120 V |
| Dokunma akımı (AC) | 0,5 mA rms | 5 mA rms |

SELV devresi, şebekeden **çift/güçlendirilmiş yalıtımla** ayrılır; bu yüzden bariyer her zaman bir "yalıtım bütçesi" sorusudur:

```
  ŞEBEKE tarafı (tehlikeli)   ┌── BARİYER ──┐   SELV tarafı (dokunulabilir)
                              │             │
  primer sargı ───────────────┤ trafo       ├─────────────── sekonder sargı
  primer GND ─────────────────┤ Y1 kapasitör├─────────────── sekonder GND
  opto LED ───────────────────┤ optokuplör  ├─────────────── opto transistörü
  röle kontağı ───────────────┤ röle        ├─────────────── röle bobini
                              │             │
                              └─────────────┘
          clearance + creepage + elektriksel dayanım bu kutuyu kapsar
```

Bariyeri geçen **her** eleman (trafo, optokuplör, Y kapasitör, röle) aynı yalıtım seviyesine uymalıdır. Zincir en zayıf halkası kadar güvenlidir.

## 4. Clearance ve creepage: rakamlar

PCB dersinde iki kavramı tanımlamıştık ([PCB yerleşim, bölüm 6](../pcb-yerlesim-ve-iz-cizimi/ozet.md#6-mesafeler-clearance-ve-creepage)): clearance kuşun **uçarak**, creepage karıncanın **yürüyerek** gittiği yoldur. Orada IPC-2221 **işlevsel** boşlukları verildi; burada **güvenlik** mesafeleri.

### 4.1 Clearance (IEC 60664-1, PD1–PD2, homojen olmayan alan)

| Anma darbe gerilimi | Clearance |
|---|---|
| 1,5 kV | 0,5 mm |
| **2,5 kV** (OVC II) | **1,5 mm** |
| **4,0 kV** (OVC III) | **3,0 mm** |
| **6,0 kV** (güçlendirilmiş OVC III veya OVC IV) | **5,5 mm** |
| 8,0 kV | 8,0 mm |

Daha düşük gerilimlerde (≤ 1,5 kV) PD3 için değer 0,8 mm'ye çıkar; PD3'ün 230 V şebeke basamaklarındaki değerlerini ürün standardının tablosundan oku.

### 4.2 Creepage (250 V ve 320 V rms çalışma gerilimi, mm)

| Çalışma gerilimi | PD | Baskı devre malzemesi (I, II, IIIa) | Diğer: I | Diğer: II | Diğer: IIIa / IIIb |
|---|---|---|---|---|---|
| **250 V** | PD1 | 0,56 | 0,56 | 0,56 | 0,56 |
| **250 V** | **PD2** | **1,0** | 1,25 | 1,8 | **2,5** |
| **250 V** | PD3 | – | 3,2 | 3,6 | 4,0 |
| **320 V** | PD1 | 0,75 | 0,75 | 0,75 | 0,75 |
| **320 V** | **PD2** | 1,6 | 1,6 | 2,2 | **3,2** |
| **320 V** | PD3 | – | 4,0 | 4,5 | 5,0 |

**"Baskı devre malzemesi" sütunu:** IEC 60664-1 baskı devre için ayrı ve daha küçük değerler verir (250 V, PD2: 1,0 mm). Ancak bunu kullanıp kullanamayacağını ürün standardı ve kartın üretim koşulları belirler. **Güvenli kural:** FR-4 için "Diğer" sütunundaki **IIIa/IIIb** değerini (250 V, PD2: **2,5 mm**) kullan; 1,0 mm'ye yalnızca standart açıkça izin veriyorsa dayan.

### 4.3 Temelden güçlendirilmişe

- **Clearance:** temel yalıtımın **bir üst darbe basamağı** alınır (2,5 kV → 4 kV).
- **Creepage:** temel yalıtım değerinin **iki katı**.
- **Yalıtım içi mesafe:** Güçlendirilmiş yalıtımda tipik olarak **≥ 0,4 mm** katı yalıtım gerekir (ince tabaka kuralları ayrıdır).

### 4.4 Çalışılmış örnek: 230 V ürün, PD2, FR-4 (IIIb)

| | Temel | Güçlendirilmiş |
|---|---|---|
| Darbe gerilimi (OVC II) | 2,5 kV | 4 kV (bir üst basamak) |
| **Clearance** (IEC 60664-1 tablosu) | **1,5 mm** | **3,0 mm** |
| **Creepage** (250 V, PD2, IIIb) | **2,5 mm** | 2 × 2,5 = **5,0 mm** |
| ITE güç ürünlerinde yaygın kural (ürün standardına bağlı) | clearance 2,0 mm | clearance 4,0 mm |
| Elektriksel dayanım testi (tip, 1 dk) | 1500 Vac | 3000 Vac |

**OVC III ürün** (sabit tesisata bağlanan) için aynı hesap: temel **3,0 mm**, güçlendirilmiş **5,5 mm** clearance; creepage aynı kalır (çalışma gerilimine bağlıdır).

> **Can alıcı nokta:** İki tablo vardır ve sonuç **büyük olandır**. Bir yerde 1,5 mm clearance görüp onunla yetinme; ürün standardı 2,0 mm istiyorsa o geçerlidir. Belirsizse büyüğünü seç.

**Pratik tasarım kuralı (başlangıç, standart yerine geçmez):**
- Şebeke ile SELV arasındaki **güçlendirilmiş** bariyerde **≥ 6 mm** hedefle (tablodaki 5,0–5,5 mm'nin üstüne ~%10–20 marj); yer varsa 8 mm.
- Aynı şebeke devresinde (temel yalıtım) iz–iz ve pad–pad mesafesi **≥ 2,5–3 mm**.

## 5. PCB'de uygulama: yüzey yolu, yarık, kaplama

```
   L pad                              SELV pad
  ┌──────┐     ┌──────────────┐     ┌──────┐
  │      │     │              │     │      │
  │      │     │     YARIK    │     │      │
  │      │     │ (kartı keser)│     │      │
  └──────┘     └──────────────┘     └──────┘

  Clearance : düz hava çizgisi, yarıktan geçer (yarık bunu DEĞİŞTİRMEZ)
  Creepage  : yüzey yolu yarığın ucundan dolaşır (yol UZAR)
```

- **Yarık (slot)** yüzey yolunu uzatır, hava mesafesini değiştirmez. Bu yüzden slot **creepage** sorununu çözer, clearance sorununu çözmez.
- Yarığın **genişliği ≥ 1 mm** (PD2) olmalıdır; daha dar yarık yolu uzatmış sayılmaz. PD3'te daha geniş alt sınır istenir. V-oluk için ölçüm, oluk genişliği 1 mm'ye inene kadar oluğun yüzeyi boyunca yapılır.
- **Mesafe tüm katmanlarda** sağlanmalıdır; üst ve alt yüzeyde, iç katmanlarda bakır kenarları arası ve prepreg kalınlığı birlikte düşünülür.
- **Kaplama (conformal coating):** Bazı standartlar kaplamayla clearance azaltmaya izin verir, bazıları vermez. Kaplamaya **güvenme**: önce kaplamasız sağla; kaplama yalnızca standart açıkça izin veriyorsa ve onaylıysa kullan.
- **Altitude** (bölüm 2.5) clearance'a çarpan olarak biner.
- PCB CAD'inin **DRC (tasarım kuralı kontrolü)** değerine güvenme: yarık geometrisini, bariyeri aşan parçaları (opto, röle, trafo) ve katmanlar arası mesafeyi **elle ölç**.

## 6. Giriş zinciri: sigorta, varistör, NTC

```
 şebeke ─►[F1 sigorta]─►[RV1 MOV]─►[X2]─►[CMC]─►[X2]─►[NTC]─► köprü ─► bulk ─► SMPS
 (L, N)    T, H           L–N       L–N   ortak   L–N   inrush
                                          mod

           Y2: L–PE ve N–PE arasında (CMC'den sonra) ─► kasa / PE
           Bleeder R_b: her X2'ye paralel
```

### 6.1 Sigorta

| | Düşük kırma kapasiteli (L) | Yüksek kırma kapasiteli (H) |
|---|---|---|
| Kırma kapasitesi (IEC 60127) | 250 VAC'ta **35 A** veya **10·In** (büyük olan) | 250 VAC'ta **1500 A**, cosφ 0,7–0,8 |
| Yapı | Şeffaf **cam** tüp; ark söndürücü dolgu yok | Çoğunlukla **seramik**, dolgulu |
| Nerede | Düşük enerjili, kısa devre akımı sınırlı devre | **Şebekenin hat tarafı** |

- **Kırma kapasitesi**, sigortanın bulunduğu noktada oluşabilecek **beklenen kısa devre akımından büyük** olmalıdır. Aksi halde sigorta açarken **ark** yapar, patlar, yangın çıkarır. Prizden beslenen ev tesisatında bu akım yüzlerce ampere ulaşabileceğinden **şebekede H** seçilir.
- **Zaman karakteristiği:** F (hızlı), **T (gecikmeli)**, TT (süper gecikmeli). Şebeke girişinde bulk kapasitörün inrush'ı olduğundan genelde **T**.
- **I²t:** Sigortanın **ön-ark I²t**'si inrush'ın I²t'sinden büyük olmalı; yoksa her açılışta yıpranır ve atar.
- **Değer:** `I_sigorta ≥ I_max / 0,75`. Örnek: 400 W'lık yük → `I = 400 / 230 = 1,74 A` → `1,74 / 0,75 = 2,32 A` → **2,5 A T, 250 V AC, H (1500 A)**.

### 6.2 Varistör (MOV)

- Hat ile nötr arasına **paralel** bağlanır; darbe geldiğinde direnci çöker ve darbeyi **kenetler**.
- Seçim: sürekli çalışma gerilimi (AC rms) en yüksek şebeke geriliminin üstünde olmalı: 253 V için **275 V AC sınıfı** tipik.
- **Ömrü sınırlıdır:** Her darbe malzemeyi yıpratır. Ömür sonunda **kısa devre** olur, ısınır ve yangın çıkarabilir. Bu yüzden MOV **sigortanın arkasında** durur ve ideal olarak **termal sigortalı** (TMOV) veya seri termal koruma ile kullanılır.
- Daha büyük enerji gerekiyorsa (dış ortam, uzun hat) MOV'a GDT eklenir; seviye ürün standardındaki surge testine (EMC 03) göre seçilir.

### 6.3 NTC ile inrush sınırlama

Boş bulk kapasitör açılışta kısa devre gibi davranır (`I = V/R`, direnç yalnızca hat ve köprü direnci).

- **Enerji:** `E = ½·C·V²`. 100 µF için 325 V'ta **5,3 J**, 373 V'ta 7,0 J.
- **Tepe akım:** 10 Ω'luk soğuk NTC ile `325 / 10 =` **32,5 A**; NTC yoksa yüzlerce amper.
- **Sıcakken:** NTC ısınınca direnci düşer (ör. 0,5 Ω) ama **sürekli kayıp** `P = I²·R` olur; 1 A'de 0,5 W. Isı ve yerleşimi hesapla.
- **Tuzak:** Şebeke kısa kesilip hemen geri gelirse NTC **sıcaktır** ve direnci düşüktür; inrush korumasız kalır. Kritik tasarımda röle ile bypass veya aktif soft-start kullan.

## 7. X ve Y kapasitörler

Kapasitör dersindeki ([bölüm 5.8](../../Komponentler/02-kapasitor/ozet.md)) şemanın güvenlik tarafı:

- **X:** Hat–nötr arası. Arızada **kısa devre** olabilir → sigorta atar → **şok riski yok** (yangın riski ayrıdır; bu yüzden sertifikalı olmalı).
- **Y:** Hat/nötr–PE arası veya primer–sekonder köprüsü. Arızada **kısa devre olursa kasa elektriklenir**; bu yüzden Y'nin arıza modu **açık devre** olacak şekilde tasarlanır ve daha sıkı test edilir.

| Sınıf | Bağlanır | Darbe (kV) | Arıza modu | Köprüleyebildiği yalıtım |
|---|---|---|---|---|
| **X1** | Hat–nötr | > 2,5 ve ≤ 4 | Kısa devre | Yok (hat arası) |
| **X2** | Hat–nötr | ≤ 2,5 | Kısa devre | Yok; **en yaygını** |
| **X3** | Hat–nötr | ≤ 1,2 | Kısa devre | Yok |
| **Y1** | Hat/nötr–PE, **primer–sekonder** | **8** | **Açık devre** | **Çift veya güçlendirilmiş** |
| **Y2** | Hat/nötr–PE | **5** | Açık devre | **Temel veya ek** |
| **Y4** | Düşük gerilim | 2,5 | Açık devre | Temel veya ek |

- **Anma AC gerilimi** (Y2 için tipik 250–300 V AC) üreticiye ve standart baskısına göre değişir: datasheet'e bak.
- **Güçlendirilmiş bariyeri köprülüyorsan Y1** (veya ürün standardı kabul ediyorsa **seri iki Y2**) kullan.
- Y kapasitörlerin tipik değeri 1 nF–4,7 nF aralığındadır; sınırı bölüm 8 koyar.
- **Sertifikasız kapasitörü şebekeye bağlama.** Sertifika (IEC 60384-14) gövdede yazar.

### 7.1 X kapasitör deşarjı

Fişi çektiğinde X kapasitör, **tepe değerinde** (325 V) şarjlı kalabilir ve fiş pinlerine dokunan kişiye çarpar. Bu yüzden X kapasitöre paralel bir **deşarj (bleeder) direnci** konur.

Kaynaklara göre gereksinim:
- IEC 60950-1: gerilim **1 s içinde 42,4 V tepeye** inmeli.
- IEC 62368-1: X kapasitör ≥ 300 nF ise **2 s** sonra normal koşulda **60 V**, tek arızada 120 V.

Hesap (en kötü durum: 264 V → tepe 373 V, kapasitör +%10, direnç +%5):
- 1 s'de 373 V → 42,4 V için `τ ≤ 1 / ln(373/42,4) =` **0,46 s**; 2 s'de 60 V için τ ≤ 1,09 s. İlk koşul daha sıkı.

| X2 | Gereken R (en kötü durumda) | Seçim | Sürekli kayıp (264 V) |
|---|---|---|---|
| 100 nF | ≤ 3,98 MΩ | 2 × 1,8 MΩ = 3,6 MΩ → τ_en kötü = **0,42 s**, 1 s'de **34 V** | **19 mW** |
| 470 nF | ≤ 0,85 MΩ | 750 kΩ → τ_en kötü = **0,41 s**, 1 s'de **32 V** | **93 mW** |

Büyük X kapasitörün bleeder'ı **sürekli ısı** üretir (bekleme gücü). Pil ve bekleme gücü hassas üründe X kapasitörü küçük tut ya da deşarjı **aktif devreyle** (IC içindeki X-cap deşarj fonksiyonu) çöz.

**Dirençler:** 100 nF örneğinde her direnç **187 V tepe** görür. 0805 (tipik 150 V) yetmez; **1206 (200 V)** veya MELF kullan ve **ikiden fazla seri** bölmeyi düşün. Direnç gövdesinin creepage'i de bir tasarım sorusudur.

## 8. Kaçak (dokunma) akımı

Y kapasitörler hat gerilimini PE'ye (veya Class II'de kasaya) **küçük bir akımla** bağlar: `I = 2π·f·C·V`.

| C (Y kapasitör) | 230 V, 50 Hz | 264 V, 60 Hz (en kötü) |
|---|---|---|
| 1 nF | 0,07 mA | 0,10 mA |
| 2,2 nF | 0,16 mA | 0,22 mA |
| 4,7 nF | 0,34 mA | 0,47 mA |
| 10 nF | 0,72 mA | 1,00 mA |
| 100 nF | 7,2 mA | 10,0 mA |

**Sınırlar** (ürün standardına göre değişir; kaynak değerleri):

| Cihaz | Dokunma akımı sınırı |
|---|---|
| **Class II** | **0,25 mA** |
| **El tipi Class I** | **0,75 mA** |
| **Diğer Class I** | **3,5 mA** |
| ES1 (IEC 62368-1), normal koşul | 0,5 mA rms |

Class II ölçümü, erişilebilir yalıtkan yüzeye uygulanan **en çok 10 × 20 cm'lik iletken folyo** ile ve **en elverişsiz besleme geriliminde** yapılır.

**Çalışılmış örnek (Class II, flyback):**
- Primer–sekonder köprüsünde 2,2 nF Y1 var. Hat 264 V/60 Hz; kapasitör toleransı +%20.
- `I = 2π · 60 · (2,2 nF · 1,2) · 264 =` **0,26 mA** → limit **0,25 mA aşıldı**.
- Nominal 2,2 nF, 264 V/60 Hz'de 0,22 mA verir (sınırın altı), ama **tolerans ve en kötü hat** birlikte düşünülünce marj kalmaz.
- Çözüm: 1,5 nF veya 1 nF'a in (0,10–0,15 mA), sonra **EMI'yi ölç**; gürültü artarsa filtreyi ortak mod bobiniyle güçlendir. Sınırı bir kez de **fiilen ölç** (parazitik kuplajlar hesapta yoktur).
- **Class I** üründe sınır daha rahattır: 3,5 mA için 230 V/50 Hz'de `C_max = 48 nF`, ama **bütün** kaçak kaynakları (diğer Y'ler, parazitikler) toplanır.

> **Can alıcı nokta:** Y kapasitör EMC ile güvenlik arasında bir pazarlıktır. EMC için büyütmek istersin, kaçak akım sınırı seni durdurur. Kaçak akımı **tasarım aşamasında hesapla**, prototipte ölç.

## 9. Koruma toprağı (PE)

- **Class I** üründe tüm **dokunulabilir iletken** parçalar PE'ye bağlanır.
- PE bağlantı direnci **düşük** olmalıdır (sahada tipik geçme sınırı ≈ **0,1 Ω** mertebesi; test akımı ve süresi ürün standardında yazar). Vida ve rondela bağlantısında **boya, anodize, oksit** dirençtir: temas yüzeyini temizle, **dişli (yıldız) rondela** kullan.
- **PE hattında sigorta veya anahtar olmaz.** PE kesintisiz olmalıdır.
- Konnektörde PE pini **ilk bağlanan, son ayrılan** olmalıdır (en uzun pin).
- PE izinin veya telinin kesiti arıza akımını sigortayı attırana kadar taşıyabilmeli: hat iletkenini örnek al, **inceltme**.
- Class II üründe PE **yoktur**; yalıtım iki katmandır. Class II ürüne "ihtiyaten" PE bağlamak sınıfı değiştirir ve ek gereksinimler getirir; yapma.

## 10. 💼 İş yerinde: ürüne göre ilk sorular

Her üründe **aynı sırayla** sor: (1) hangi ürün standardı? (2) şebeke-SELV bariyeri nerede? (3) Class I mı II mi? (4) OVC ve PD? (5) mesafeler ve testler.

| Ürün | Tipik durum | İlk sorular |
|---|---|---|
| Duvar tipi **dimmer** | Şebekeye doğrudan bağlı; kullanıcı düğmeye dokunur → güçlendirilmiş bariyer; kaçak akım yük üzerinden akar | Standart EN 60669-2-1; OVC III varsay; snubber kaçağı ([Ders 2](../triyak-ve-faz-kontrolu/ozet.md)) |
| Şebekeli **sensörlü lamba / hareket sensörü** | Kapasitif düşürücü ya da flyback; dış ortam → **PD3** | Tüm devre şebekede mi (düşürücü)? Dokunulabilir parça var mı? ([Ders 3](../sebekeli-guc-kaynaklari/ozet.md)) |
| **Kapı paneli / interkom** | Şebekeden güç kaynağı modülü, dışarıda SELV; kablo uzun | Modül sertifikalı mı? Şebekeyi kart üzerine mi taşıyoruz? |
| **Gaz dedektörü** (24 V DC) | Çoğu SELV; şebekeli versiyonda modül veya trafo | Ev tipi dedektör standardı **EN 50194-1**; Ex gereksinimi ayrı ([PCB, bölüm 6](../pcb-yerlesim-ve-iz-cizimi/ozet.md#6-mesafeler-clearance-ve-creepage)) |
| **Röleli çıkış** (230 V yük) | Kontaklar şebekede, bobin MCU tarafında | Röle bobin–kontak yalıtımı; kontak–PCB mesafeleri |

**Ürün ailesi → tipik standart** (kesinleştirmek senin işin):
- Elektronik anahtar/dimmer: **EN 60669-2-1** · Ev aletleri: **EN 60335-1** (+ ilgili 2-x kısmı) · Ses-video/bilişim: **EN 62368-1** · Ölçüm/laboratuvar: **EN 61010-1** · Otomatik kontroller: **EN 60730-1** · Ev tipi yanıcı gaz dedektörü: **EN 50194-1**.
- Mesafe mantığının ortak kökü **IEC 60664-1**'dir.

> Bu işyeri tablosu genel örnektir; şirketin gerçek ürün şemaları ve değerleri bu notlara girmez.

## 11. Şematikte

- Şebeke bölgesini şematikte **ayrı bir sayfada veya kutu içinde** göster; üstüne yalıtım türünü, OVC ve PD'yi yaz: `Güçlendirilmiş · OVC II · PD2 · 250 V`.
- Her elemana **gerilim anma değeri** ve **sınıfı** (X2, Y1, MOV 275 V AC, 250 V AC T H) ekle.
- **Bariyeri geçen** elemanları (trafo, opto, Y1, röle) işaretle ve yalıtım değerlerini not et.
- PE'yi sembolle ve kalın izle göster; PE hattında sigorta/anahtar çizme.
- X kapasitörün **bleeder** değerini ve `τ = R·C` hesabını notla.
- Y kapasitörlerin **kaçak akım hesabını** (`I = 2π·f·C·V`) şematik notuna yaz.
- Test noktası: şebeke tarafında test noktası **koyma** veya "⚠ ŞEBEKE" olarak işaretle.

## 12. PCB / layout

- Şebeke bölgesini **kartta çizgiyle** (silkscreen + bakır yasak bölge) çevir; düşük gerilim izi bu bölgeye **girmez**.
- Bariyeri geçen parçaların (trafo, opto, röle) **altında bakır yok**; creepage için gerekirse **yarık** aç (bölüm 5).
- Sigorta ve NTC **girişe yakın**; X kapasitör sigortanın hemen arkasında (kablo gürültüsünü erken yakalar).
- Y kapasitörün PE bağlantısı **kısa ve geniş**; PE vidası/ayağı PE izine temiz bağlansın.
- Montaj vidaları ve metal ayaklar: vida başı ile şebeke bakırı arasındaki creepage'i de ölç (vida başı bir iletkendir).
- Kenar ve kablo: kart kenarına yakın şebeke bakırı kasaya değebilir; kenardan iç mesafe bırak.
- Mesafeleri **CAD'de kural olarak tanımla** (şebeke net sınıfı → SELV net sınıfı = 6 mm), ama üretim öncesi elle ölç.
- İz genişliği: şebeke akımına göre ([PCB yerleşim dersi](../pcb-yerlesim-ve-iz-cizimi/ozet.md)); sigorta ve MOV izleri kısa ve geniş.

## 13. EMC açısından

- **X2 + ortak mod bobini (CMC) + Y** şebeke girişindeki klasik filtredir ([EMC 02, bölüm 8](../../EMC/02-emc-icin-kart-tasarimi/ozet.md#8-güç-girişi)). X diferansiyel modu, Y ortak modu bastırır.
- Y kapasitörü büyütmek **kaçak akımı** büyütür (bölüm 8). Ortak mod gürültü için önce **CMC** ve yerleşimi iyileştir.
- **Surge** (IEC 61000-4-5) ve **EFT** testleri şebeke girişini zorlar; MOV/GDT ve sigorta bu teste göre seçilir ([EMC 03](../../EMC/03-emc-testleri-ve-standartlar/ozet.md)).
- X kapasitörün deşarj direnci **EMC filtresini bozmaz**, ama bekleme gücüne eklenir (bölüm 7.1).
- Şebeke kablosu iyi bir anten gibidir: filtreyi **girişe** koy, filtre ile konnektör arasındaki izi kısa tut.

## 14. Ölçüm ve doğrulama

### 14.1 Güvenlik testleri

| Test | Ne kontrol eder | Tipik değer |
|---|---|---|
| **Hi-pot** (dielektrik dayanım) | Bariyerin gerilim dayanımı | Güçlendirilmiş (primer–sekonder): **3000 Vac**; temel (primer–PE): **1500 Vac**; tip testte 1 dk. DC testinde `×1,414` |
| **PE bağlantı direnci** | Dokunulabilir iletken ↔ PE | ≈ ≤ 0,1 Ω |
| **Dokunma (kaçak) akımı** | Y kapasitör ve parazitikler | 0,25 / 0,75 / 3,5 mA |
| **Fiziksel mesafe** | Clearance / creepage | Kumpas, mesafe mastarı |
| **Isı** | Sigorta, NTC, MOV, trafo, bleeder | En sıcak ortamda |
| **Anormal koşullar** | Bir elemanın kısa/açık devre olması | Ürün standardına göre |

Hi-pot'u **yalnızca** yetkili kişi, eğitimli ve kurallı alanda yapar; test sırasında ürüne dokunulmaz.

### 14.2 Şebekeli kartı güvenle ölçme

**Neden tehlikeli?** Şebekeli bir kartın "GND"si çoğu zaman **şebekeye bağlıdır** (primer GND'si ya da bulk kapasitörün eksi ucu hattın potansiyelindedir). Osiloskobun probu da **PE'ye bağlıdır**. Bu ikisini birleştirmek şebekeyi toprağa **kısa devre** eder.

1. **İzolasyon trafosu** (şebeke → kart): kartı PE'den yüzdürür. Variac (ototransformatör) **yalıtmaz**; izolasyon trafosunun yerine geçmez.
2. **Diferansiyel prob** (en az 1000 V CAT II/III) veya **izole kanallı osiloskop**; ikisi de yoksa izolasyon trafosuyla besle ve prob toprağını yine de dikkatle bağla.
3. **Osiloskobun PE'sini asla kesme** ("toprak ucu kırma"): kasa elektriklenir.
4. **İlk enerjilendirmede akım sınırla:** kartın şebeke girişine **seri bir akkor ampul** koy.
   - 60 W/230 V lamba: sıcak direnç `230² / 60 =` **882 Ω** → kısa devrede akım **≈ 0,26 A** ile sınırlanır.
   - Soğuk filaman direnci sıcağın kabaca onda biri olduğu için ilk anda ≈ 2–3 A geçer; yine de bir hatada kartı **yakmaz**.
   - Kart normal çalışıyorsa ampul **sönük kalır**; hatalıysa ampul parlar. Böylece hatayı **ışıkla** görürsün.
5. **Tek el kuralı:** Güç açıkken yalnızca **bir el** kartta; diğer el cebinde. Akım elden ele geçip kalbi kat etmesin.
6. **Önce güç kapat, sonra bekle, sonra dokun:** X kapasitörün gerilimini ve bulk kapasitörü **multimetreyle** doğrula (deşarj olmuş mu?).
7. **Yukarı akışta RCD (kaçak akım rölesi)** olan bir prizden çalış.
8. Yalnız çalışma; yanında bilgili biri olsun. Islak/yağlı zeminde çalışma.

## 15. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| Yalnızca RMS ile düşünmek ("230 V, 300 V yeter") | Tepe 325–373 V ve 2,5–4 kV darbe var | Çalışma gerilimi (creepage) ve darbe (clearance) için ayrı tablo satırı |
| Creepage ile clearance'ı karıştırmak | Yüzey yolu kısa kalır, iz atlar | İkisini ayrı ölç, büyüğünü uygula |
| 0,5 mm'lik dar yarıkla creepage "uzattığını" sanmak | PD2'de 1 mm altı yarık yolu uzatmaz | Yarık ≥ 1 mm |
| Güçlendirilmiş yalıtımda temel mesafeyi kullanmak | Bir basamak ve iki kat unutulur | Clearance bir üst basamak, creepage ×2 |
| Sertifikasız kapasitörü şebekeye bağlamak | X kısa devre olup yangın; Y açık devre değilse kasa elektriklenir | Sertifikalı X2/Y1/Y2 |
| Y kapasitörü EMI için büyütmek | Kaçak akım sınırı aşılır | `I = 2π·f·C·V`; CMC ile güçlendir |
| X kapasitöre deşarj direnci koymamak | Fiş çıkınca 325 V pinlerde durur | `τ = R·C` ≤ ~0,4 s |
| Şebekede cam tüp (L) sigorta | Düşük kırma kapasitesi; ark, yangın | H tip (1500 A) |
| MOV'u sigortanın önüne koymak | MOV ömür sonunda kısa devre → hat kısa devre | Sigorta MOV'dan önce |
| Variac'ı izolasyon trafosu saymak | Variac yalıtmaz | İzolasyon trafosu ayrı |
| Osiloskop prob toprağını primer GND'ye takmak | PE üzerinden kısa devre, patlama, kasa elektriklenir | Diferansiyel prob veya izolasyon trafosu |
| İlk açılışı doğrudan şebekeden yapmak | Hata varsa parça patlar, yangın çıkar | Seri ampul + izolasyon trafosu |
| Kaplamayla mesafeyi kısaltmak | Çoğu standart izin vermez | Önce kaplamasız sağla |
| PE hattına sigorta/anahtar koymak | PE kesilince koruma kalmaz | PE kesintisiz |

## 16. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Clearance** | İki iletken arasındaki havadan en kısa mesafe |
| **Creepage** | İki iletken arasındaki yüzey boyunca en kısa mesafe |
| **OVC** | Aşırı gerilim kategorisi (I–IV); darbe gerilimini belirler |
| **PD** | Kirlilik derecesi (1–4) |
| **CTI** | Karşılaştırmalı iz oluşum indeksi; malzeme grubunu belirler |
| **Malzeme grubu** | I, II, IIIa, IIIb; CTI aralığına göre |
| **Fonksiyonel yalıtım** | Yalnızca çalışma için; güvenlik sağlamaz |
| **Temel yalıtım** | Çarpmaya karşı tek kademe |
| **Ek yalıtım** | Temelin bozulmasına karşı ikinci katman |
| **Çift yalıtım** | Temel + ek |
| **Güçlendirilmiş yalıtım** | Tek katman, çift yalıtıma eşdeğer |
| **Class I / II / III** | Koruma toprağı / çift yalıtım / SELV |
| **SELV** | Çift/güçlendirilmiş yalıtımla şebekeden ayrılmış, sınırlı gerilimli devre |
| **ES1** | IEC 62368-1'de dokunulabilir enerji sınıfı (30 V rms, 0,5 mA rms) |
| **PE** | Koruma toprağı |
| **X / Y kapasitör** | Hat–nötr (arıza: kısa devre) / hat–toprak (arıza: açık devre) |
| **Bleeder** | X kapasitörü boşaltan direnç |
| **MOV** | Metal oksit varistör; darbe kenetler |
| **NTC (inrush)** | Soğukken yüksek, ısınınca düşük dirençli inrush sınırlayıcı |
| **Hi-pot** | Yüksek gerilimli elektriksel dayanım testi |
| **Kırma kapasitesi** | Sigortanın güvenle açabileceği en büyük kısa devre akımı |
| **I²t** | Sigortanın açması için gereken enerji ölçüsü |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.7, bölüm 14):

- [x] Şebekeye bağlı bölge şematikte ve kartta çizgiyle işaretli; yalıtım türü (temel/çift/güçlendirilmiş), aşırı gerilim kategorisi ve kirlilik derecesi şematik notunda yazılı
- [x] Clearance ve creepage standart tablosundan (çalışma gerilimi, aşırı gerilim kategorisi, kirlilik derecesi, malzeme grubu) alındı; güçlendirilmiş yalıtımda bir üst darbe basamağı ve ikiye katlanmış creepage uygulandı
- [x] Şebeke girişinde sigorta var: gecikmeli (T), 250 V AC, kırma kapasitesi hattın kısa devre akımının üstünde (H); I²t açılış inrush'ına göre kontrol edildi
- [x] Hat–nötr arası kapasitörler X2, hat/nötr–toprak ve primer–sekonder kapasitörleri Y sınıfında ve sertifikalı (IEC 60384-14); güçlendirilmiş bariyeri köprüleyen kapasitör Y1 (veya seri Y2)
- [x] X kapasitörün deşarj direnci var; şebeke çekilince gerilim ürün standardının süresi içinde güvenli seviyeye iniyor (τ = R·C hesaplandı)
- [x] Y kapasitörlerin kaçak akımı I = 2π·f·C·V ile en kötü hat gerilimi ve kapasitör toleransında hesaplandı; dokunma akımı sınırının altında
- [x] Class I üründe koruma toprağı (PE) dokunulabilir iletkenlere düşük dirençle bağlı; PE hattında sigorta veya anahtar yok
- [x] Varistör (MOV) sigortanın arkasında; ömür sonu kısa devre için sigorta veya termal koruma var
- [x] İnrush sınırlayıcı (NTC) varsa enerji (½·C·V²) ve sıcakken kayıp kontrol edildi
- [x] İlk enerjilendirme ve ölçüm planı yazıldı: izolasyon trafosu, akım sınırlama (seri ampul veya akım sınırlı kaynak), diferansiyel prob

## Kontrol soruları

→ [quiz.md](quiz.md) · 12 soru, 5'i hesap
