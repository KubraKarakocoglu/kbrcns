# 03 · Bobin (indüktör)

- **Oluşturma:** 2026-10-12
- **İlk kaynak:** [TI SLVA477 – Basic Calculation of a Buck Converter's Power Stage](https://ti.com/lit/pdf/SLVA477)
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)

> Sayısal değerler **tipik başlangıç noktalarıdır**; tasarım değeri için her zaman regülatörün ve bobinin datasheet'i esastır.

---

## ⚡ Hızlı tekrar

1. Bobin, akımın değişimine karşı koyar: `V = L·di/dt`. Akımı **aniden kesemezsin**; kesmeye çalışırsan gerilim fırlar.
2. Enerjiyi manyetik alanda depolar: `E = ½·L·I²`.
3. Güç bobini üç akımla seçilir: **Isat** (doyma), **Irms** (ısınma) ve devredeki **tepe akım**.
4. Doyan bobin endüktansını kaybeder, akım fırlar, anahtar yanabilir. Isat'ı regülatörün **akım limitine** göre seç, yük akımına göre değil.
5. **Isat tanımı üreticiye göre değişir** (endüktansta %10, %20 veya %30 düşüş). Karşılaştırırken aynı tanıma bak.
6. **Ekranlı** bobin manyetik alanı içinde tutar; hassas devrelerin yakınında ekranlı tip kullan.
7. Röle, solenoid, motor gibi **endüktif yükleri** keserken **flyback diyotu** şarttır.
8. Buck regülatörde en kritik şey bobin değil, **sıcak döngü** (giriş kapasitörü ve anahtarlar) ile **SW düğümüdür**.

## 🧮 Formül kartı

| Formül | Ne zaman kullanılır | Örnek |
|---|---|---|
| `V = L · di/dt` | Akım değişim hızı | 12 V, 100 mH → 120 A/s |
| `E = ½·L·I²` | Depolanan enerji | 100 mH, 30 mA → 45 µJ |
| `X_L = 2π·f·L` | Empedans | 10 µH @ 1 MHz → 62,8 Ω |
| `D = V_out / V_in` | Buck görev oranı (ideal) | 3,3 / 12 = 0,275 |
| `ΔI = (V_in − V_out) · D / (L · f_sw)` | Buck ripple akımı | 12→3,3 V, 500 kHz, 22 µH → 0,22 A |
| `L = (V_in − V_out) · D / (f_sw · ΔI)` | Gereken endüktans | %30 ripple, 1 A → ~16 µH |
| `I_tepe = I_out + ΔI/2` | Tepe akım | 1 A + 0,11 A = 1,11 A |
| `I_rms ≈ √(I_out² + ΔI²/12)` | Isınma akımı | ≈ 1,00 A |
| `P = I_rms² · DCR` | Bakır kaybı | 1 A, 50 mΩ → 50 mW |

---

## 1. Ne işe yarar? Temel fizik

Sargıdan akım geçince manyetik akı oluşur. Akım değişirse akı değişir ve sargıda bu değişime **karşı koyan** bir gerilim indüklenir (Lenz yasası).

**Kapasitörle ikiz:**

| | Kapasitör | Bobin |
|---|---|---|
| Neye karşı koyar? | Gerilim değişimine | Akım değişimine |
| Temel denklem | `I = C·dV/dt` | `V = L·di/dt` |
| Enerji | `½CV²` (elektrik alan) | `½LI²` (manyetik alan) |
| Empedans | Frekansla düşer | Frekansla artar |

**Benzetme:** Bobin, ağır bir su çarkı gibidir. Suyu (akımı) hızlandırmak da durdurmak da zaman alır. Akışı aniden kesersen (vanayı çarparsan) borularda basınç darbesi (koç darbesi) oluşur. Bobindeki karşılığı gerilim sıçramasıdır.

**Çekirdek ve doyma:**
- Manyetik çekirdek endüktansı büyük ölçüde artırır, ama taşıyabileceği akının bir sınırı vardır.
- Akım bu sınırı geçince çekirdek **doyar**, geçirgenliği düşer ve endüktans çöker.
- Endüktans çökünce `di/dt = V/L` büyür, akım çok hızlı yükselir. Anahtarlama elemanı aşırı akımla yanabilir.

**Kayıplar:**
- **Bakır kaybı:** `I²·DCR`. Yüksek frekansta deri (skin) ve yakınlık etkileri yüzünden artar.
- **Çekirdek kaybı:** Histerezis ve girdap akımları. Ripple akımının genliği ve frekansla artar.

## 2. Türleri ve seçim

| Tür | Özellik | Nerede |
|---|---|---|
| **Ekransız (drum core)** | Ucuz, yüksek Isat, manyetik alanı dışarı saçar | Maliyet önemli ve yakında hassas devre yoksa |
| **Yarı ekranlı** (manyetik reçine kaplı) | Orta düzey saçılma | Genel amaçlı |
| **Ekranlı / kalıplı (molded composite)** | Saçılma alanı düşük, yumuşak doyma, mekanik olarak sağlam | DC/DC regülatörler, yoğun kartlar |
| **RF / yüksek frekans** (seramik, hava çekirdekli) | Yüksek Q, yüksek SRF, düşük akım | RF eşleşme ve filtreler |
| **Ortak mod bobini (CMC)** | İki sargı: diferansiyel akımı geçirir, ortak modu bastırır | USB, CAN, RS-485, güç girişi (EMC) |
| **Kuplajlı bobin / trafo** | Birden fazla sargı | Flyback, SEPIC, izolasyon |

### Çekirdek malzemeleri

| Malzeme | Doyma davranışı | Kayıp | Not |
|---|---|---|---|
| **Ferrit** | **Keskin**: belirli akımda endüktans aniden düşer | Düşük çekirdek kaybı | Isat sıcaklıkla düşer |
| **Toz demir / metal kompozit** | **Yumuşak**: endüktans yavaşça düşer | Yüksek frekansta daha yüksek | Aşırı yükte daha affedici |
| **Hava** | Doymaz | Yok | Düşük endüktans; RF |

## 3. Datasheet'te nelere bakılır?

| Parametre | Anlamı | Tuzak |
|---|---|---|
| **L** (test frekansı, 0 A) | Nominal endüktans, tipik ±%20 | DC akım altında düşer |
| **Isat** | Endüktansın belirli bir yüzde düştüğü akım | Tanım üreticiye göre %10–30 değişir; ferritte sıcaklıkla düşer |
| **Irms** (Itemp) | Bobini belirli bir derece ısıtan akım; çoğu üreticide 40 °C artış | Ortam sıcaklığı bunun üstüne eklenir |
| **DCR** | Sargının DC direnci | Kayıp; sıcaklıkla artar |
| **SRF** | Self-rezonans frekansı | Anahtarlama frekansının çok üstünde olmalı |
| **Çekirdek kaybı** | Frekans ve ripple'a bağlı | Bazı üreticiler hesap aracı verir (ör. Würth REDEXPERT) |
| **Ekranlama** | Ekranlı / yarı ekranlı / ekransız | Hassas devre yakınında önemli |

## 4. Gerçek model (parazitikler)

```
        ┌────── C_par (sargılar arası) ──────┐
   ─────┤                                     ├─────
        └── DCR ──── L(I, T) ─────────────────┘
                (çekirdek kaybı: L'ye paralel bir R olarak modellenir)
```

- **L(I, T):** Endüktans DC akım ve sıcaklıkla değişir. Datasheet'teki "L vs. DC current" eğrisi Isat'ı gösterir.
- **C_par:** Sargılar arası kapasitans. SRF'nin üstünde bobin **kapasitör gibi** davranır.
- **Doyma eğrisi:** Ferritte keskin bir dirsek, kompozitte yumuşak bir eğim görürsün.

## 5. Şematikte kullanım ve tipik devreler

### 5.1 Buck regülatör bobini: adım adım seçim

**Örnek:** 12 V → 3,3 V, 1 A çıkış, f_sw = 500 kHz. `D = 3,3 / 12 = 0,275`.

1. **Ripple hedefi:** Çıkış akımının %20–40'ı. %30 için `L = (12 − 3,3) × 0,275 / (500 kHz × 0,3 A) ≈ 16 µH`. Standart değer olarak 15 µH veya 22 µH seç.
2. **Ripple'ı hesapla:**

   | L | ΔI | Ripple oranı | I_tepe |
   |---|---|---|---|
   | 10 µH | 0,48 A | %48 | 1,24 A |
   | 15 µH | 0,32 A | %32 | 1,16 A |
   | 22 µH | 0,22 A | %22 | 1,11 A |

3. **Isat:** Yalnızca 1,11 A'e göre değil, regülatörün **anahtar akım limitine** göre seç. Kısa devre veya ilk açılış sırasında akım bu limite kadar çıkar. Örneğin regülatörün akım limiti 1,6 A ise Isat bunun üstünde, marjlı olmalı; ferrit çekirdekte sıcak durumdaki Isat'a bak.
4. **Irms:** Yaklaşık 1,0 A + marj. Ortam sıcaklığını ekle.
5. **DCR kaybı:** 50 mΩ ile ~50 mW. Verim ve ısınma için kabul edilebilir mi?
6. **Ekranlı tip** tercih et.
7. **Son söz regülatörün datasheet'inde:** Önerilen L aralığı kompanzasyonla ilişkilidir. Aralık dışına çıkarsan regülatör kararsızlaşabilir.

**Çok küçük L:** Ripple ve tepe akım yükselir, çıkış gürültüsü ve EMI artar.
**Çok büyük L:** Geçici tepki yavaşlar, bobin büyür, DCR kaybı artar.

### 5.2 LC filtre

- Giriş filtresi (iletimli emisyonu azaltmak için) ve π filtre (C–L–C).
- LC devresinin bir rezonans frekansı vardır: `f = 1/(2π√(LC))`. Sönümleme yoksa rezonansta gürültü büyür. Ayrıntılar: [Ferrit boncuk](../04-ferrit-boncuk/ozet.md).

### 5.3 Endüktif yük sürme: flyback diyotu

Röle bobinini süren transistör kapandığında, bobin akımı sürdürmeye çalışır: `V = L·di/dt`. Akım çok hızlı kesildiği için gerilim **yüzlerce volta** sıçrayabilir ve transistörü yakar.

```
   +12 V ────┬───────────┐
             │           │
         ┌───┴───┐     ──┴──  ← katot (+12 V tarafı)
         │ Röle  │       ▲    ← D: flyback diyotu
         │ bobini│       │    ← anot (drain tarafı)
         └───┬───┘       │
             ├───────────┘
             │
           Drain
         ┌───┴────┐
  MCU ───┤ MOSFET │   (gate: seri R + pull-down)
         └───┬────┘
            GND
```

- **Diyot:** Bobin akımına bir dolaşım yolu verir; gerilimi V_cc + ~0,7 V'a kenetler.
- **Bedeli:** Akım yavaş söner, röle **geç bırakır**.
- **Hızlı bırakma gerekiyorsa:** Diyota seri bir Zener (veya TVS) ekle. Kenetleme gerilimi yükselir, akım daha hızlı söner. Transistörün gerilim derecesi bu kenetleme gerilimine dayanmalı.
- Aynı kural solenoid, motor ve endüktif sensör sürücüleri için de geçerlidir.

### 5.4 Ortak mod bobini

- Diferansiyel sinyal akımı (bir hattan gidip diğerinden dönen) iki sargıda zıt yönde akar; akılar birbirini götürür ve sinyal neredeyse etkilenmez.
- Ortak mod akımı (iki hatta aynı yönde) akıları toplar; bobin yüksek empedans gösterir ve gürültüyü bastırır.
- Kullanım: USB, CAN, RS-485, Ethernet ve güç girişleri. Ayrıntılar: [EMC için kart tasarımı](../../EMC/02-emc-icin-kart-tasarimi/ozet.md).

## 6. PCB / layout (buck regülatör)

**İlk kural:** Regülatörün datasheet'indeki örnek layout'u temel al.

```
  VIN ──┬──────────────┐
        │              │
      [C_in]      ┌────┴────┐  SW düğümü   ┌─────┐
        │         │  Üst    ├──────●──────┤  L  ├──┬── VOUT
        │         │ anahtar │      │       └─────┘  │
        │         ├─────────┤      │              [C_out]
        │         │  Alt    ├──────┘                │
        │         │ anahtar │                       │
        └─────────┴────┬────┴───────────────────────┘
                      GND
   SICAK DÖNGÜ: C_in → üst anahtar → alt anahtar → C_in (en küçük alan!)
```

- **Sıcak döngü:** Giriş kapasitörü → üst anahtar → alt anahtar (veya diyot) → kapasitör. Bu döngüdeki akım her anahtarlamada aniden değişir. Alanı **en küçük** olmalı; giriş kapasitörü IC'nin VIN ve GND pinlerine bitişik olmalı.
- **SW düğümü:** Çok yüksek dV/dt taşır ve kapasitif kuplajla gürültü yayar. Bakır alanı akımı taşıyacak kadar geniş ama mümkün olduğunca **küçük** olsun.
- **FB (geri besleme) izi:** SW düğümünden ve bobinden uzak tut. Bölücüyü IC'nin FB pinine yakın koy.
- **Bobin yönü:** Bazı üreticiler sargı başlangıcını (nokta işaretli uç) SW düğümüne bağlamayı önerir; böylece dış sargılar sakin çıkış düğümünde kalır ve elektrik alan saçılması azalır.
- **Manyetik kuplaj:** Ekransız bobinleri diğer bobinlerden, Hall sensörlerinden, kristalden ve hassas analog devrelerden uzak tut. İki bobini birbirine dik yönde yerleştirmek kuplajı azaltır.
- **Toprak:** Kesintisiz GND düzlemi. Isınma için bakır alan bırak.

## 7. EMC açısından

- **Anahtarlamalı regülatör kartın en büyük gürültü kaynaklarından biridir.** f_sw'nin harmonikleri iletimli emisyon bandına (150 kHz–30 MHz) düşer. Nanosaniyelik kenarlar ise yüzlerce MHz'e kadar ışınımlı emisyon üretir.
- **Azaltma yolları:**
  - Sıcak döngüyü küçültmek (en etkili adım)
  - Ekranlı bobin kullanmak
  - Girişe LC (π) filtre koymak
  - Regülatör destekliyorsa **spread spectrum** (frekans yayma) özelliğini açmak
  - Gerekirse SW düğümüne RC snubber eklemek (çınlamayı sönümler)
- **Ortak mod bobinleri** kablolardan çıkan ve kablolara giren ortak mod gürültüsünü bastırır.
- **Yakın alan probuyla** (H alanı) bobinin ve sıcak döngünün etrafını tararsan manyetik gürültü kaynağı hemen görünür.

## 8. Arıza modları ve sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| Isat'ı yük akımına göre seçmek | Kısa devre ve ilk açılışta doyma, akım fırlar | Regülatörün akım limiti + marj |
| Farklı üreticilerin Isat'ını doğrudan karşılaştırmak | %10 ile %30 tanımı farklı akımlar verir | Aynı tanımı kullan |
| Ferritte sıcaklıkla Isat düşüşünü unutmak | Sıcakta doyar | Sıcak durumdaki Isat |
| Ekransız bobini analog devrenin yanına koymak | Manyetik kuplaj, gürültü | Ekranlı tip, mesafe |
| FB izini SW düğümünün yanından geçirmek | Gürültü, kararsızlık | Uzak tut, bölücüyü FB pinine yakın koy |
| Röleye flyback diyotu koymamak | Transistör yanar | Diyot (hızlı bırakma için + Zener) |
| Çok küçük L | Yüksek ripple, tepe akım ve EMI | %20–40 ripple |
| Datasheet aralığı dışında L | Regülatör kararsız | Önerilen aralık |
| Irms'yi ortam sıcaklığıyla birlikte düşünmemek | Aşırı ısınma | Marj bırak |
| Bobinden gelen vızıltı | Manyetostriksiyon; hafif yükte burst modda duyulur | Kalıplı bobin, regülatörün çalışma modunu değiştir |
| Ferrit çekirdeğin mekanik darbeyle çatlaması | Endüktans düşer | Kalıplı bobin, montaj kontrolü |

## 9. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Isat** | Doyma akımı: endüktansın belirli bir yüzde düştüğü akım |
| **Irms / Itemp** | Bobini belirli bir sıcaklık artışına getiren akım |
| **DCR** | Sargının DC direnci |
| **Ripple akımı (ΔI)** | Bobin akımındaki tepeden tepeye dalgalanma |
| **Görev oranı (D)** | Anahtarın iletimde kaldığı sürenin periyoda oranı |
| **Sıcak döngü (hot loop)** | Buck'ta akımı aniden değişen giriş döngüsü |
| **SW düğümü** | Anahtarlar ile bobin arasındaki yüksek dV/dt'li nokta |
| **Flyback diyotu** | Endüktif yükte akıma dolaşım yolu veren diyot |
| **CMC** | Common Mode Choke: ortak mod bobini |
| **Spread spectrum** | Anahtarlama frekansını yayarak emisyon tepesini düşürme |
| **Ekranlı bobin** | Manyetik alanı çekirdeğin içinde tutan yapı |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.2, bölüm 10):

- [x] Bobin: Isat ≥ regülatör akım limiti (sıcak durumda); Irms marjlı; L datasheet aralığında
- [x] Hassas devre yakınında ekranlı bobin
- [x] Endüktif yüklerde (röle, solenoid, motor) flyback diyotu

## Kontrol soruları

→ [quiz.md](quiz.md) · 12 soru, 5'i hesap
