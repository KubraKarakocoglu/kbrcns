# Aliasing ve anti-aliasing filtresi

- **Oluşturma:** 2026-10-14
- **İlk kaynak:** https://www.analog.com/media/en/training-seminars/tutorials/MT-002.pdf
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Ön bilgi:** RC filtre → [Kapasitör, bölüm 10](../../Komponentler/02-kapasitor/ozet.md#10-derinleştirme-rc-filtre-ve-aliasing) · ADC girişi → [Mikrodenetleyici donanımı, bölüm 7](../../Komponentler/05-mikrodenetleyici-donanimi/ozet.md#7-adc-girişi) · RF testleri → [EMC testleri, bölüm 4](../../EMC/03-emc-testleri-ve-standartlar/ozet.md#4-bağışıklık-testleri-ne-olur-nerede-kalınır-nasıl-çözülür)

> Birden fazla kaynaktan derlendi. Sayısal değerler **tipik başlangıç noktalarıdır**; tasarım değeri için her zaman kullandığın MCU/ADC'nin datasheet'i ve ilgili standart esastır. **Varsayım** diye işaretlenen bozucu genlikleri kartında ölçülerek doğrulanmalıdır.
>
> **Okuma planı:** 1. oturum: bölüm 1–4 ve "Kendin dene" · 2. oturum: 5–9 (nerede zarar verir, tasarım, firmware) · 3. oturum: 10–14 (şematik, PCB, EMC, ölçüm, hatalar).

---

## ⚡ Hızlı tekrar

1. ADC sinyali sürekli izlemez; saniyede **f_s** kez anlık değerini (**örnek**) kaydeder. İki örnek arasında olanı göremez.
2. ADC yalnızca **0 … f_s/2** aralığını doğru görür. f_s/2'ye **Nyquist frekansı** denir.
3. f_s/2'nin üstündeki her frekans bu aralığa **katlanır** ve sahte bir frekans (**alias**) olarak görünür: `f_a = |f − k·f_s|` (k·f_s: f'ye en yakın f_s katı).
4. Alias, gerçek bir sinyalle **aynı sayıları** üretir. Ölçtüğün bandın içine düşen alias hiçbir yazılımla ayrılamaz.
5. f_s'nin tam katındaki bir bozucu **DC'ye** katlanır ve sabit ofset gibi görünür; katına çok yakın olan ise **çok yavaş bir kayma** gibi. Gaz dedektöründe "sıfır kayması" sanılır.
6. Çözüm ADC'den **önce**: analog alçak geçiren (**anti-aliasing**) filtre. Kural: `B < f_c ≪ f_s/2` (B: ölçtüğün sinyal bandı).
7. Pratik reçete: **RC filtre + hızlı örnekleme + yazılımda ortalama.** Hızlı örnekleme, tehlikeli bölgeyi (f_s ± B) RC'nin rahatça bastırabileceği kadar yukarı iter.
8. Yazılımda örnek atlamak da örneklemedir: **önce ortala, sonra seyrelt.** ADC'yi timer tetiklesin; f_s titrememeli.

## 🧮 Formül kartı

| Formül | Ne zaman kullanılır | Örnek |
|---|---|---|
| `f_N = f_s / 2` | Doğru görülebilecek en yüksek frekans (Nyquist) | f_s 1 kHz → 500 Hz |
| `f_a = \|f − k·f_s\|` · k: f/f_s'ye en yakın tam sayı | Bir frekansın örneklemeden sonra göründüğü yer | 60 Hz, f_s 100 Hz → k = 1 → **40 Hz** |
| `x = f/f_s` → kesirli kısım r → `f_a = r·f_s` (r ≤ 0,5) veya `(1 − r)·f_s` | Aynı hesap, tur mantığıyla (bölüm 3) | 110 Hz, f_s 100 Hz → r = 0,1 → **10 Hz** |
| `f_s > 2·B` (teorik) · pratikte `f_s ≫ 2·B` | Örnekleme hızının alt sınırı | B = 20 Hz → f_s > 40 Hz; pratikte ≥ 200 Hz |
| `f_c = 1/(2πRC)` | RC filtrenin kesim frekansı | 10 kΩ, 1,5 µF → 10,6 Hz |
| `\|H\| = 1/√(1 + (f/f_c)²)` · f ≫ f_c'de `≈ f_c/f` | RC'nin f frekansında geçirdiği oran | 1 kHz, f_c 10,6 Hz → %1,06 (≈ 1/94) |
| `A_gerekli = V_bozucu / V_izin` | Filtrenin sağlaması gereken zayıflatma | 50 mV / 0,40 mV → ≈ 124 kat |
| `N = f_s / 50 Hz` örneklik ortalama | 50 Hz'i ve tüm harmoniklerini sıfırlayan pencere (20 ms) | f_s 1,2 kHz → N = 24 |
| `LSB = V_ref / 2ⁿ` | ADC adımı (hata bütçesi için) | 3,3 V, 12 bit → 0,81 mV |
| `dB = 20·log10(oran)` | Oranı dB'ye çevirme | 1/100 → −40 dB |

---

## 1. Örnekleme: ADC aslında ne görüyor?

ADC bir **fotoğraf makinesidir**, video kamerası değil. Sinyali sürekli izlemez; belirli aralıklarla anlık değerini kaydeder. Bu kayda **örnek**, saniyedeki örnek sayısına **örnekleme frekansı (f_s)** denir. İki örnek arası süre `T_s = 1/f_s`'dir.

```
Gerçek sinyal : her an bir değeri olan sürekli bir eğri
ADC'nin elinde: x[0]      x[1]      x[2]      x[3]      …
                |<- T_s ->|
                0 ms      1 ms      2 ms      3 ms           (f_s = 1 kHz)
```

- Örnek anları arasında olan her şey **kaybolur**. ADC'den sonra elinde yalnızca bir sayı listesi vardır.
- Firmware'deki her şey (ortalama, kalibrasyon, alarm kararı) bu listeyle çalışır. Listede olmayan bilgiyi hiçbir algoritma geri getiremez.

**Günlük hayattan iki örnek:**
- **Video:** Kamera saniyede ~25–30 kare çeker. Hızlı dönen bir tekerlek videoda yavaş, hatta geriye dönüyor görünür.
- **Stroboskop:** Dönen bir pervaneyi, dönme hızıyla aynı frekansta yanıp sönen ışıkla aydınlatırsan pervane **duruyor** görünür.

İkisinde de örnekleme (kareler, flaşlar) hızlı bir hareketi olduğundan farklı gösterir. Bu dersin tamamı, bu iki gözlemin elektronikteki karşılığıdır.

## 2. Aliasing: aynı sayılar, farklı sinyaller

**Deney:** f_s = 100 Hz (her 10 ms'de bir örnek). Girişe sırayla 10 Hz, 110 Hz ve 90 Hz'lik, genliği 1 olan sinüs veriyoruz. ADC'nin kaydettiği sayılar:

| Örnek | Zaman | 10 Hz | 110 Hz | 90 Hz |
|---|---|---|---|---|
| 0 | 0 ms | 0,000 | 0,000 | 0,000 |
| 1 | 10 ms | +0,588 | +0,588 | −0,588 |
| 2 | 20 ms | +0,951 | +0,951 | −0,951 |
| 3 | 30 ms | +0,951 | +0,951 | −0,951 |
| 4 | 40 ms | +0,588 | +0,588 | −0,588 |
| 5 | 50 ms | 0,000 | 0,000 | 0,000 |
| 6 | 60 ms | −0,588 | −0,588 | +0,588 |

- **110 Hz, 10 Hz ile birebir aynı sayıları üretiyor.** ADC'nin elinde yalnızca bu sayılar var; girişte hangisinin olduğunu bilemez.
- **90 Hz** de 10 Hz gibi görünüyor, yalnızca işareti ters: dalga ters yönde ilerliyor (videodaki "geri dönen tekerlek").
- Bu sahte 10 Hz'e **alias**, olayın kendisine **aliasing** denir.

> **Aliasing bir arıza değil, matematiktir.** f_s = 100 Hz ile örnekleyen her sistemde 10, 90, 110, 190, 210 … Hz **aynı veriyi** üretir. Hangi ADC'yi kullanırsan kullan, hangi algoritmayı yazarsan yaz, bu değişmez.

## 3. Neden olur? Tam turlar görünmez

Sinüsü dönen bir saat ibresi gibi düşün: **frekans = saniyedeki tur sayısı.** ADC her örnekte ibrenin fotoğrafını çeker.

**110 Hz, f_s = 100 Hz:**
1. İki fotoğraf arasında ibre `110 / 100 = 1,1 tur` döner.
2. Fotoğrafta **tam turlar görünmez**: 1,1 tur dönmüş ibre ile 0,1 tur dönmüş ibre aynı yerdedir.
3. Her fotoğrafta ibre 0,1 tur ilerlemiş görünür: `0,1 tur × 100 fotoğraf/s = 10 tur/s` → **10 Hz**.

**90 Hz, f_s = 100 Hz:**
1. İki fotoğraf arasında ibre `0,9 tur` döner.
2. 0,9 tur ileri gitmiş bir ibre, fotoğrafta **0,1 tur geri** gitmiş gibi görünür (iki fotoğrafı birleştiren en kısa yol budur).
3. Sonuç yine **10 Hz**, ama ters yönde (tablodaki ters işaret bu).

### 3.1 Tur yöntemi: her soruda aynı 3 adım

1. **Fotoğraf başına tur:** `x = f / f_s`
2. **Tam kısmı at,** kesirli kısmı al: `r` (ör. x = 1,1 → r = 0,1)
3. **Karar ver:**
   - `r ≤ 0,5` → ileri gidiyor görünür: `f_a = r · f_s`
   - `r > 0,5` → geri gidiyor görünür: `f_a = (1 − r) · f_s`

| Gerçek f | f_s | x = f / f_s | r | Görünen f_a | Yorum |
|---|---|---|---|---|---|
| 30 Hz | 100 Hz | 0,3 | 0,3 | **30 Hz** | x < 0,5: alias yok, gerçek frekans |
| 60 Hz | 100 Hz | 0,6 | 0,6 → 1 − 0,6 = 0,4 | **40 Hz** | Geri yönde |
| 110 Hz | 100 Hz | 1,1 | 0,1 | **10 Hz** | |
| 50 Hz | 40 Hz | 1,25 | 0,25 | **10 Hz** | Kapasitör dersindeki tekerlek örneği |
| 950 Hz | 1 kHz | 0,95 | 0,95 → 0,05 | **50 Hz** | Şebeke gürültüsü sanırsın! |
| 2000 Hz | 1 kHz | 2,0 | 0 | **0 Hz (DC)** | İbre hep aynı yerde: stroboskop |

### 3.2 Kısayol: en yakın kat

Aynı sonucu tek satırda verir: **f'ye en yakın f_s katını bul, farkı al.**

`f_a = |f − k·f_s|` (k: f/f_s'ye en yakın tam sayı)

- 60 Hz, f_s = 100 Hz → en yakın kat 100 → `|60 − 100| = 40 Hz`
- 1950 Hz, f_s = 1 kHz → en yakın kat 2000 → `|1950 − 2000| = 50 Hz`

Tur yöntemindeki "tam turları atmak", bu formüldeki "k·f_s'yi çıkarmak" ile aynı şeydir. Hangisi kolayına gelirse onu kullan; ikisi her zaman aynı sonucu verir.

## 4. Katlanma ve Nyquist frekansı

Tur yöntemini tüm frekanslar için uygularsan bir **zikzak** çıkar (f_s = 100 Hz):

```
Görünen f (Hz)
50 ┤    /\        /\        /\
   │   /  \      /  \      /  \
   │  /    \    /    \    /    \
   │ /      \  /      \  /      \
 0 ┼/        \/        \/        \
   └────┴────┴────┴────┴────┴────┴─▶ gerçek f (Hz)
   0   50   100  150  200  250  300
```

- **0 … 50 Hz (0 … f_s/2):** Birinci Nyquist bölgesi. Buradaki frekanslar olduğu gibi görünür.
- **50 … 100 Hz:** Ters dönerek bu bölgeye katlanır (90 Hz → 10 Hz).
- **100 … 150 Hz:** Düz katlanır (110 Hz → 10 Hz). Ve böyle devam eder.
- Frekans eksenini f_s/2'nin her katından kâğıt gibi katlayıp üst üste kapattığını düşün: hepsi birinci bölgenin üstüne biner. "Katlanma" (folding) adı buradan gelir.

**Bir alias'ın tek bir kaynağı yoktur.** Kayıtta 10 Hz görüyorsan, zikzağı 10 Hz yüksekliğinde kesen her nokta suçlu olabilir: 10, 90, 110, 190, 210, 290 … Hz.

### 4.1 Neden "2 kat"? Sınırda ne olur?

Bir periyotta 2'den az örnek alırsan ibre iki fotoğraf arasında yarım turdan fazla döner ve yönü bile belirsizleşir. Tam sınırda (f = f_s/2, periyot başına tam 2 örnek) bile sonuç **örnekleme anına** bağlıdır:

```
f = 50 Hz, f_s = 100 Hz (periyot başına tam 2 örnek)

Tepelerden yakalarsan:          +1, −1, +1, −1 …   → sinyal görünür
Sıfır geçişlerinden yakalarsan:  0,  0,  0,  0 …   → sinyal HİÇ görünmez
```

Bu yüzden örnekleme teoremi `f_s > 2·B` der; eşitlik yetmez. Pratikte f_s, B'nin **çok** üstünde seçilir, çünkü gerçek filtreler keskin değildir (bölüm 7).

### 4.2 Kendin dene

1. f_s = 100 Hz, girişte 70 Hz. Kayıtta kaç Hz görünür?
2. f_s = 100 Hz, girişte 130 Hz. Kaç Hz görünür?
3. f_s = 1 kHz, girişte 1050 Hz. Kaç Hz görünür?
4. f_s = 100 Hz, kayıtta 25 Hz görüyorsun. Girişte hangi frekanslar olabilir? İlk dördünü yaz.
5. f_s = 1 kHz, girişte 3 kHz'lik bir bozucu var. Kayıtta ne görürsün?

<details>
<summary>Cevaplar</summary>

1. x = 0,7 → r = 0,7 > 0,5 → `(1 − 0,7) × 100 =` **30 Hz** · kısayol: `|70 − 100| = 30`
2. x = 1,3 → r = 0,3 → `0,3 × 100 =` **30 Hz** · kısayol: `|130 − 100| = 30`
3. x = 1,05 → r = 0,05 → `0,05 × 1000 =` **50 Hz** · kısayol: `|1050 − 1000| = 50` (yine şebeke kılığında!)
4. `k·100 ± 25`: **25, 75, 125, 175 Hz** (sonra 225, 275 …)
5. x = 3,0 → r = 0 → **0 Hz**: sabit bir ofset (bölüm 6)

</details>

## 5. Alias nereye düşerse zarar verir?

Kapasitör dersinde "aliasing yazılımla düzeltilemez" dedik. Daha doğrusu şu: **Her alias'ın bir iniş noktası (f_a) vardır ve zararı bu noktanın nereye düştüğüne bağlıdır.**

- **Ölçtüğün bandın (B) içine düşerse:** Gerçek sinyalle aynı frekansta, aynı sayılar → **ayrılamaz.** Hiçbir yazılım düzeltemez.
- **Bandın dışına düşerse:** Kendi frekansında durur; yazılımdaki dijital filtre (ortalama) onu atabilir.

**Örnek:** Gaz sinyali B = 0 … 1 Hz, f_s = 40 Hz, girişte filtre yok.
- **50 Hz şebeke** → `|50 − 40| = 10 Hz`'e düşer. 10 Hz gaz bandının dışında → yazılımdaki ortalama siler. **Zararsız.**
- **200 Hz'lik bir PWM** (ör. LED parlaklık kontrolü) → `200 / 40 = 5,0` tur → **0 Hz.** Gaz bandının tam ortası → **ayrılamaz**, okumada sabit bir ofset olarak kalır.

Yani asıl soru "aliasing var mı?" değil, **"hangi frekanslar benim bandıma düşer?"** sorusudur.

### 5.1 Tehlikeli bölgeler: k·f_s ± B

Bandına düşebilecek frekanslar, f_s'nin her katının ±B çevresidir:

```
ölçtüğün              tehlikeli bölge            tehlikeli bölge
  bant                   (1. kat)                   (2. kat)
├──────┤              ├──────┼──────┤            ├──────┼──────┤
0      B            f_s−B   f_s   f_s+B       2f_s−B   2f_s  2f_s+B  → frekans
```

Arada kalan her şey bandın dışına düşer ve dijital filtreye bırakılabilir. **Analog filtrenin asıl görevi bu tehlikeli bölgeleri bastırmaktır.** En kritiği en alçaktaki, yani `f_s − B` civarıdır.

### 5.2 Aşırı örneklemenin sırrı

f_s'yi büyüttükçe ilk tehlikeli bölge yukarı kayar ve basit bir RC orada çok daha güçlü olur. Aynı RC (10 kΩ + 1,5 µF, f_c ≈ 10,6 Hz) ve B = 1 Hz için:

| f_s | İlk tehlikeli bölge | RC'nin orada geçirdiği |
|---|---|---|
| 40 Hz | 39 – 41 Hz | ≈ %25: neredeyse filtre yok |
| 1 kHz | 999 – 1001 Hz | ≈ %1,06 (≈ 1/94) |
| 4 kHz | 3999 – 4001 Hz | ≈ %0,27 (≈ 1/377) |

"RC + hızlı örnekleme + yazılımda ortalama" reçetesinin neden çalıştığının cevabı budur: **Hızlı örneklemek ucuz, keskin analog filtre pahalıdır.** Hızlı örnekle, kalan işi yazılıma devret.

## 6. DC'ye katlanma: sabit ofset ve yavaş kayma

Tur yönteminde `r = 0` çıkarsa ibre her fotoğrafta **aynı yerdedir**: dönüyor ama duruyor görünür. Stroboskop budur. ADC'deki karşılığı: **f_s'nin tam katındaki bir bozucu DC'ye (0 Hz) katlanır.**

**Senaryo:** Firmware ADC'yi filtresiz olarak f_s = 10 Hz ile okuyor (her 100 ms'de bir). Girişte 50 Hz şebeke kuplajı var.

1. `50 / 10 = 5,0` tur → r = 0 → **0 Hz.** Şebeke gürültüsü **sabit bir ofset** olarak okunur.
2. Ofsetin değeri, ilk örneğin şebeke dalgasının **hangi anına** denk geldiğine bağlıdır. Cihaz her açıldığında başka bir değer çıkar: "sıfır noktası her resette farklı."
3. Şebeke frekansı da tam 50,000 Hz değildir; sürekli birkaç on mHz oynar. 50,02 Hz için `|50,02 − 50| = 0,02 Hz` → **50 saniye** periyotla yavaşça inip çıkan bir sinyal.

Sonuç, gaz konsantrasyonu yavaşça değişiyormuş ya da sensörün sıfırı kayıyormuş (drift) gibi görünür. Bu hata **sinyal bandının tam ortasındadır**; hiçbir yazılım ayıramaz. Kalibrasyonu ve alarm eşiğini doğrudan bozar.

**DC'ye katlanmanın diğer kaynakları**, f_s ile senkron çalışan her şeydir:
- Frekansı f_s'nin tam katı olan bir PWM, LED tarama veya DC/DC anahtarlaması
- Örnekleme anına hep aynı noktada denk gelen bir dijital olay (radyo modülünün gönderimi, röle sürme)

> **Bilerek kullanıldığı yer:** Motor sürücülerde ADC, PWM periyodunun anahtarlama gürültüsünden uzak bir anına (ör. ortasına) senkron tetiklenir; böylece geçişler hiç örneklenmez. Senkron örnekleme bir tasarım aracıdır; sorun, **farkında olmadan** senkron olmaktır.

**Kural:** Filtresiz, yavaş örnekleme yapma. Yavaş veri istiyorsan bile **hızlı örnekle, filtrele, sonra seyrelt** (bölüm 9).

## 7. Anti-aliasing filtresi: adım adım tasarım

1. **Sinyal bandını (B) belirle.** Ölçmek istediğin en hızlı anlamlı değişim. Gaz ≈ 1 Hz, sıcaklık ≈ 0,1 Hz, ses ≈ 20 kHz.
2. **Bozucuları listele** (frekans + tahmini genlik): 50 Hz şebeke ve harmonikleri (100, 150 … Hz), DC/DC anahtarlama frekansı (yüzlerce kHz – birkaç MHz), MCU saati ve dijital kenarlar, röle/LED PWM'i, RF (EMC testleri, telsiz, GSM).
3. **Hata bütçesini belirle.** Ör. ½ LSB: 12 bit, 3,3 V → LSB = 0,81 mV → **½ LSB ≈ 0,40 mV.**
4. **f_s'yi seç:** B'nin çok üstünde. MCU ADC'leri kHz'ler mertebesinde zahmetsizce örnekler.
5. **Gerekli zayıflatmayı hesapla:** Tehlikeli bölgelerdeki (k·f_s ± B) her bozucu için `A_gerekli = V_bozucu / V_izin`.
6. **Filtreyi seç ve kontrol et:** Tek RC, f ≫ f_c'de yaklaşık `f / f_c` kat zayıflatır. Yetmiyorsa: **(a)** f_s'yi artır (en ucuzu), **(b)** 2. derece filtre kullan (iki RC arka arkaya veya op-amp'li Sallen-Key).
7. **Yan koşulları kontrol et** (aşağıda).

**Filtre derecesinin etkisi:**

| f / f_c | 1. derece (tek RC) | 2. derece (iki kat, ideal) |
|---|---|---|
| 10 | ≈ %10 (−20 dB) | ≈ %1 (−40 dB) |
| 100 | ≈ %1 (−40 dB) | ≈ %0,01 (−80 dB) |

> İki pasif RC'yi arka arkaya koyarken ikinci katın R'sini ilkinin ~10 katı seç (ya da araya tampon koy). Yoksa katlar birbirini yükler ve hesapladığın eğriyi alamazsın.

**Yan koşullar:**
- **Tepki süresi:** `τ = RC`; %99'a oturma ≈ 5τ. Güvenlik cihazında alarm gecikmesine doğrudan eklenir.
- **Kaynak empedansı:** Sensörün veya op-amp'in çıkış direnci R'ye seri eklenir; gerçek f_c hesapladığından düşük çıkar.
- **ADC örnekleme yükü:** Filtre kapasitörü, ADC'nin örnekleme kapasitörüne yük deposu olur. Değer seçimi için [MCU dersi, bölüm 7](../../Komponentler/05-mikrodenetleyici-donanimi/ozet.md#7-adc-girişi).
- **Kaçak akım:** ADC pininin kaçak akımı R üzerinde ofset yaratır. Örnek: 100 nA × 10 kΩ = 1 mV (≈ 1,2 LSB). Datasheet'teki I_lkg ile hesapla. Kaçak akım sıcaklıkla arttığı için sıfır kalibrasyonu bunu tam düzeltmez.
- **Kapasitör:** f_c kararlı olsun: C0G veya X7R; Y5V asla. Büyük değerli, küçük paketli MLCC'de DC bias kaybını eğriden kontrol et ([Kapasitör dersi](../../Komponentler/02-kapasitor/ozet.md)).

> **Sigma-delta ADC'ler** (hassas ve yavaş ölçümlerde yaygın) aşırı örneklemeyi içeride çok yüksek hızda yapar; dijital filtreleri 50/60 Hz'e çentik koyabilir. Ama onların da modülatör frekansının katlarında tehlikeli bölgeleri vardır: datasheet'in önerdiği giriş RC'sini atlama.

## 8. Tasarım örneği: LEL dedektörü girişi

Bölüm 7'deki adımları gaz dedektörüne uygulayalım: önce ilk tasarımı kuracağız, sonra **test edip** zayıf noktasını bulacağız.

**Gereksinimler:**
- Gaz sinyali bandı: **B ≈ 1 Hz**
- ADC: 12 bit, V_ref = 3,3 V → hata bütçesi **½ LSB ≈ 0,40 mV**
- Bozucular (**varsayım**, kartta ölçülerek doğrulanmalı):
  - 50 Hz şebeke kuplajı: filtre girişinde 20 mV
  - RF bağışıklık testi: analog ön kat RF'i doğrultuyor; ortaya çıkan 1 kHz'lik zarf filtre girişinde 50 mV (bölüm 12)

**Adım 1 — İlk tasarım:** R = 10 kΩ, C = 1,5 µF → `f_c ≈ 10,6 Hz` · f_s = 1 kHz · yazılımda 20 örnek ortalama (20 ms)

| Bileşen | RC geçirir | ADC'ye ulaşan | Örneklemede nereye düşer? | 20 örnek ortalama sonrası |
|---|---|---|---|---|
| Gaz sinyali (1 Hz) | %99,6 | — | 1 Hz (gerçek) | %99,9 geçer ✓ |
| Şebeke 50 Hz, 20 mV | %20,8 | 4,2 mV | 50 Hz (alias yok) | **0** ✓ (tam periyot) |
| RF testinin 1 kHz zarfı, 50 mV | %1,06 | 0,53 mV | **0 Hz (DC!)** | **0,53 mV kalır** ✗ |

**Adım 2 — Sorunu gör:** 1 kHz, f_s'nin tam katı → DC'ye katlanır. Ortalama DC'yi silemez; çünkü DC, korumak istediğin gaz sinyalinin ta kendisidir. Test boyunca okuma 0,53 mV (≈ 0,7 LSB) kayar ve bütçeyi (0,40 mV) aşar. Modülasyon tam 1000 Hz değil de 999 Hz olursa kayma 1 Hz'lik bir dalgalanmaya dönüşür: yine gaz bandının içinde.

**Adım 3 — Revize et:** f_s = **1,2 kHz**, ortalama **N = 24** (yine tam 20 ms)

- 1 kHz → `|1000 − 1200| = 200 Hz`'e düşer. 200 Hz, 50 Hz'in katıdır → 20 ms ortalaması onu **sıfırlar.**
- Modülasyon 999 Hz olsa bile 201 Hz'e düşer; ortalama onu ≈ %0,5'e indirir (0,53 mV → ≈ 3 µV).
- 50 Hz ve tüm harmonikleri hâlâ sıfırlanır (24 örnek = 20 ms).
- Yeni ilk tehlikeli bölge 1199–1201 Hz; RC orada %0,88 geçirir ve orada bilinen bir bozucu yok.

**Adım 4 — Diğer kontroller:**
- **Tepki süresi:** τ = 15 ms, 5τ = 75 ms; ortalama 20 ms ekler. Toplam ≈ 0,1 s, sensörün kendi tepki süresinin (saniyeler) yanında ihmal edilebilir.
- **Kapasitör:** 1,5 µF C0G büyük ve pahalıdır → X7R, ≥ 16 V, 0805 (DC bias kaybı düşük). f_c'nin ±%20 kayması bu tasarımda sorun değil.
- **Kaçak akım:** I_lkg × 10 kΩ ofsetini datasheet'ten hesapla (bölüm 7).
- **Yer bırak:** 2. kademe RC için şematikte DNP footprint koy; test sonucuna göre takılır.

```
Sensör ön katı ──[ R 10 kΩ ]──┬──────► ADC pini (f_s = 1,2 kHz, timer tetiklemeli)
                              │
                       [ C 1,5 µF X7R ]           f_c ≈ 10,6 Hz
                              │
                            AGND

Firmware: 24 örnek ortalama (20 ms) → 50 örnek/s → kalibrasyon → alarm kararı
```

> **Kapasitör dersine not:** [Bölüm 10.9](../../Komponentler/02-kapasitor/ozet.md#109-tasarım-örneği-gaz-sensörü-girişi)'daki f_s = 1 kHz önerisi şebeke açısından doğrudur; EMC testi de hesaba katılınca 1,2 kHz daha güvenlidir.

## 9. Firmware tarafı

### 9.1 f_s sabit olmalı: ADC'yi timer tetiklesin

- Döngü içinde `delay(1)` ile okumak f_s'yi titretir (**jitter**): kesmeler ve diğer işler araya girer.
- 20 ms'lik ortalamanın 50 Hz'i sıfırlaması **tam 20 ms**'ye bağlıdır. Örnek: f_s %1 kayarsa (1000 yerine 990 Hz), 50 Hz'in ≈ %1'i geçmeye başlar.
- **Doğrusu:** Timer → ADC tetikleme → DMA ile tampona yazma. CPU'nun ne kadar meşgul olduğu örnekleme anını değiştirmez.

### 9.2 Ortalama: basit ve güçlü bir dijital filtre

- N örneklik ortalama, `f_s / N`'nin tüm katlarını **sıfırlar** (f_s'nin katları hariç; onlar zaten DC'ye düşer).
  - f_s = 1,2 kHz, N = 24 → 50, 100, 150 … Hz → 0
- 60 Hz şebekeli bir pazar da varsa pencereyi **100 ms** yap (1,2 kHz'de N = 120): 50 ve 60 Hz'in tüm harmonikleri birlikte sıfırlanır; 1 Hz'lik gaz sinyali %98,4 geçer.

### 9.3 Seyreltme tuzağı: önce ortala, sonra seyrelt

Örnek hızını 1,2 kHz'den 10 Hz'e düşürmek istiyorsun:

- ❌ **Yanlış:** Her 120 örnekten birini al. Bu, 10 Hz ile **yeniden örneklemektir**: 50 Hz → `50 / 10 = 5,0` tur → **DC.** Bölüm 6'daki sorunu bu sefer yazılımda üretmiş olursun.
- ✅ **Doğru:** 120 örneği **ortala**, her blok için tek çıkış üret. Ortalama, 10 Hz'in katlarını (50 Hz dahil) zaten sıfırlar.

Aynı tuzak **veri kaydında** da var: Saniyede bir **tek** örneği loga yazmak, 1 Hz ile örneklemektir. Loga o saniyenin **ortalamasını** yaz.

### 9.4 Örnek kod: blok ortalama (C)

```c
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* 1,2 kHz'de timer tetiklemeli ADC'den gelen örnekleri 24'erli bloklarda ortalar.
 * 24 örnek = 20 ms = 50 Hz'in tam bir periyodu → 50 Hz ve tüm harmonikleri sıfırlanır.
 * Çıkış hızı: 1200 / 24 = 50 örnek/s. */
#define ADC_MAKS  4095u   /* 12 bit */
#define ORT_N     24u     /* = f_s / 50 Hz */

_Static_assert((ORT_N > 0u) && (ORT_N <= UINT8_MAX), "ORT_N, sayac tipine sigmali");
_Static_assert(((uint64_t)ORT_N * ADC_MAKS) <= UINT32_MAX, "toplam, uint32_t'ye sigmali");

typedef enum { ORT_DEVAM = 0, ORT_HAZIR, ORT_HATA } ort_durum_t;

typedef struct {
    uint32_t toplam;
    uint8_t  sayac;
} blok_ort_t;

void blok_ort_sifirla(blok_ort_t *b)
{
    if (b != NULL) {
        b->toplam = 0u;
        b->sayac  = 0u;
    }
}

/* Yeni örneği ekler. Blok dolunca yuvarlanmış ortalamayı *cikis'a yazar, ORT_HAZIR döner.
 * Aralık dışı örnek veya bozuk durum bloğu atar ve ORT_HATA döner: güvenlik
 * cihazında bozuk veri sessizce ortalamaya karışmamalı. */
ort_durum_t blok_ort_ekle(blok_ort_t *b, uint16_t ornek, uint16_t *cikis)
{
    if ((b == NULL) || (cikis == NULL)) {
        return ORT_HATA;
    }
    if ((ornek > ADC_MAKS) || (b->sayac >= ORT_N)) {
        blok_ort_sifirla(b);
        return ORT_HATA;
    }

    b->toplam += ornek;
    b->sayac++;
    if (b->sayac < ORT_N) {
        return ORT_DEVAM;
    }

    *cikis = (uint16_t)((b->toplam + (ORT_N / 2u)) / ORT_N);
    blok_ort_sifirla(b);
    return ORT_HAZIR;
}
```

**Kullanım notları:**
- Fonksiyonu DMA'nın yarım/tam tampon kesmesinde, tampondaki örnekler üzerinde döngüyle çağır. Sonucu ana döngüye bir kuyrukla (veya `volatile` bayrak + kopya ile) aktar; kesme ve ana döngü aynı `blok_ort_t` yapısına birlikte dokunmasın.
- `ORT_HATA` dönerse hata sayacını artır; tekrarlıyorsa cihazı **arıza durumuna** al. Gaz dedektöründe bozuk bir ölçüm sessizce "gaz yok" diye okunmamalı.

## 10. Şematikte

- RC'yi ADC pininin hemen önüne çiz ve amacını yaz: `R12 10k 1% · C15 1µ5 X7R 16V 0805 — AA filtre, f_c ≈ 10,6 Hz, f_s = 1,2 kHz`. Altı ay sonra sen (ya da review yapan kişi) değerlerin nereden geldiğini bilmelisin.
- C'nin GND'sini ADC'nin referans aldığı toprağa bağla (VSSA / analog GND tarafı).
- **2. kademe için yer bırak:** İkinci bir RC'yi DNP olarak çiz. Ölçümde veya EMC testinde gerekirse takarsın; kart revizyonu gerekmez.
- Yüksek empedanslı bir kaynak (büyük dirençli bölücü, zayıf sensör çıkışı) varsa R'yi büyütmek yerine **op-amp tampon + RC** kullan. Tampon filtre kapasitörünü sürecekse çıkışına seri izolasyon direnci koy ([kontrol listesi, bölüm 6](../../Sematik-Tasarim/kontrol-listesi.md#6-analog-ve-sensör)).
- RF'e karşı ayrı önlem: Pine en yakın noktaya küçük bir C0G (100 pF – 10 nF) koymak ve konnektör girişinde ferrit + kapasitör kullanmak yaygın uygulamalardır (bölüm 12).

## 11. PCB / layout

- RC, ADC pinine **bitişik** olsun. Filtreden **sonraki** iz ne kadar uzunsa, filtreyi atlayarak o kadar gürültü toplar.
- Filtreden **önceki** iz uzun olabilir; topladığı gürültüyü filtre süzer.
- C'nin GND via'sı pad'e bitişik, altında kesintisiz GND düzlemi olsun (decoupling dersindeki küçük döngü mantığı aynen geçerli).
- Analog izi DC/DC'nin SW düğümünden ve bobininden, kristalden ve hızlı dijital hatlardan uzak tut; onlara paralel uzun yürütme.
- **İki görev, iki yer:** Konnektörde RF filtresi (kablodan gelen RF'i karta girer girmez durdurur), ADC pininde anti-aliasing RC (örneklemeyi korur).

## 12. EMC açısından

**RF, düşük frekanslı bir hataya dönüşebilir.** Op-amp girişleri, ESD diyotları ve ADC girişi doğrusal değildir; üzerlerine gelen RF'i **doğrultur** (demodüle eder). Geriye RF'in **zarfı**, yani modülasyonu kalır. [EMC testleri dersi](../../EMC/03-emc-testleri-ve-standartlar/ozet.md#4-bağışıklık-testleri-ne-olur-nerede-kalınır-nasıl-çözülür) bunu "sensör okuması kayar" diye anlatır; aliasing, bu kaymanın neden her zaman yazılımla silinemediğini açıklar.

- RF bağışıklık temel standartlarında (IEC 61000-4-3 ışınımlı, IEC 61000-4-6 iletimli) taşıyıcı **1 kHz sinüsle %80 AM** modüle edilir. Ürün standardının (gaz algılama için EN 50270) ve laboratuvarın test planındaki modülasyonu ayrıca kontrol et.
- Doğrultma olursa girişte **1 kHz'lik** bir sinyal belirir.
- **1 kHz, f_s'nin tam katıysa** (f_s = 1 kHz, 500 Hz, 250 Hz …) bu sinyal **DC'ye** katlanır. Ortalama onu silemez; test boyunca okuma kayar ve performans kriterini zorlar.

**Savunma sırası:**
1. **RF'i doğrultma noktasına ulaşmadan durdur:** konnektörde ferrit + kapasitör, op-amp girişlerinde küçük RC, pine yakın küçük C0G, kısa analog izler. EMI'ye dayanıklı op-amp seç (bazı üreticiler datasheet'te **EMIRR** değeri verir).
2. **f_s'yi akıllı seç:** 50 Hz'in katı olsun (20 ms ortalaması için), ama **1 kHz, f_s'nin tam katı olmasın.** Ör. 1,2 kHz: 1 kHz → 200 Hz'e düşer ve 20 ms ortalaması onu sıfırlar (bölüm 8).
3. **Laboratuvardan önce dene:** Ön uyumluluk denemesinde bir RF kaynağıyla okumanın kaymadığını kontrol et.

**Emisyon tarafı:** Anti-aliasing filtresi doğrudan bir emisyon önlemi değildir. Ama sensör kablosu iyi bir antendir; konnektördeki filtre hem dışarı ışımayı hem içeri gireni azaltır.

## 13. Ölçüm ve doğrulama

### 13.1 Bir tepe alias mı? Örnekleme hızını biraz değiştir

- Gerçek bir sinyalin frekansı f_s'ye bağlı değildir; f_s'yi değiştirsen de **yerinde kalır.**
- Alias'ın frekansı f_s'ye bağlıdır; f_s'yi %1–2 değiştirince **kayar.**
- Örnek: f_s = 1000 Hz'de 50 Hz'te bir tepe var. f_s'yi 1010 Hz yap:
  - Gerçek 50 Hz şebekeyse → yine **50 Hz**
  - 950 Hz'lik bir bozucunun alias'ıysa → `|950 − 1010| =` **60 Hz**'e kayar

### 13.2 Ham veriyi kaydet, spektruma bak

Geliştirme sırasında ortalamasız, tam hızdaki ham ADC verisini UART/USB ile bilgisayara al ve spektrumuna bak. Kayıt en az birkaç saniye olsun; frekans çözünürlüğü `f_s / örnek sayısı`'dır.

```python
import numpy as np

fs = 1200.0                                    # firmware'deki örnekleme hızı
x = np.loadtxt("ham_adc.csv")                  # ham örnekler (LSB), tek sütun
X = np.abs(np.fft.rfft(x - x.mean())) * 2 / len(x)
f = np.fft.rfftfreq(len(x), d=1 / fs)
for i in np.argsort(X)[-5:][::-1]:             # en büyük 5 tepe
    print(f"{f[i]:8.2f} Hz   genlik ≈ {X[i]:.2f} LSB")
```

Beklemediğin her tepe için 13.1'deki testi yap.

### 13.3 Filtreyi sinyal jeneratörüyle doğrula

Girişe bilinen genlikte sinüs ver, frekansı tehlikeli bölgede süpür (ör. 1150 – 1250 Hz) ve ADC verisine bak. Kâğıttaki zayıflatmayı kartta görürsün; parazitik kuplajlar ancak böyle ortaya çıkar.

### 13.4 Osiloskop da aliasing yapar

Dijital osiloskop da örnekleyerek çalışır ve yavaş time/div ayarında örnekleme hızını düşürür. Hızlı bir sinyal ekranda **yavaş, sahte bir dalga** gibi görünebilir. Şüphelenince time/div'i değiştir (gerçek sinyalin frekansı değişmez, alias'ınki değişir) ve **peak detect** modunu aç.

### 13.5 Şebeke testi

Cihazı önce pil veya laboratuvar kaynağından, sonra şebeke adaptöründen besle; girişin yakınında bir şebeke kablosu gezdir. Okumadaki fark, şebeke kuplajının göstergesidir.

## 14. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| f_c'yi f_s/2'ye eşit seçmek | Tek RC, f_c'de %70,7 geçirir; f_s/2 civarı neredeyse süzülmez | `B < f_c ≪ f_s/2`; yetmezse f_s'yi artır |
| Filtresiz, yavaş örnekleme (ör. 10 Hz) | Şebeke DC'ye veya yavaş bir kaymaya katlanır | RC + hızlı örnekleme + ortalama |
| Her N örnekten birini alarak seyreltmek | Yazılımda yeniden aliasing | Önce ortala/filtrele, sonra seyrelt |
| Loga saniyede bir tek örnek yazmak | 1 Hz ile örneklemektir; şebeke DC'ye düşer | Loga o aralığın ortalamasını yaz |
| `delay()` ile örnekleme | f_s titrer; 20 ms ortalaması 50 Hz'i sıfırlayamaz | Timer tetiklemeli ADC + DMA |
| 1 kHz'in f_s'nin tam katı olması (f_s = 500 Hz, 1 kHz) | RF testindeki 1 kHz AM DC'ye katlanır | Ör. f_s = 1,2 kHz, N = 24 |
| RC'yi ADC'den uzağa koymak | Filtre sonrası iz gürültü toplar | RC pine bitişik |
| Büyük R seçip kaçak akımı unutmak | I_lkg × R kadar ofset, sıcaklıkla kayar | Hesapla; gerekirse tampon op-amp |
| Y5V veya DC bias kaybı yüksek küçük MLCC | f_c sıcaklık ve gerilimle kayar | X7R/C0G, DC bias eğrisi |
| Ekranda gördüğüne körü körüne güvenmek | Osiloskop da aliasing yapar | Time/div'i değiştir, peak detect |
| Her alias'ı "düzeltilemez" sanmak | Bandın dışına düşen alias dijital filtreyle atılır; asıl tehlike banda düşenlerdir | Tehlikeli bölgeleri (k·f_s ± B) hesapla |

## 15. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Örnekleme (sampling)** | Sürekli bir sinyalin belirli anlardaki değerlerini kaydetmek |
| **f_s / T_s** | Örnekleme frekansı / iki örnek arası süre (`T_s = 1/f_s`) |
| **Nyquist frekansı** | f_s/2; doğru görülebilecek en yüksek frekans |
| **Nyquist bölgesi** | f_s/2 genişliğindeki frekans dilimleri; hepsi birinci bölgeye (0 … f_s/2) katlanır |
| **Alias** | f_s/2 üstündeki bir frekansın örneklemede göründüğü sahte frekans |
| **Katlanma (folding)** | Yüksek frekansların 0 … f_s/2 aralığına zikzak çizerek kapanması |
| **Sinyal bandı (B)** | Ölçmek istediğin frekans aralığı (gaz için ≈ 0 … 1 Hz) |
| **Tehlikeli bölge** | Örneklemede bandına düşecek frekanslar: k·f_s ± B |
| **Anti-aliasing filtresi** | ADC'den önce tehlikeli frekansları bastıran analog alçak geçiren filtre |
| **Aşırı örnekleme (oversampling)** | Gerekenden çok daha hızlı örnekleme; filtre yükünü yazılıma kaydırır |
| **Seyreltme (decimation)** | Filtreledikten sonra örnek hızını düşürme |
| **Blok / hareketli ortalama (boxcar)** | N örneğin ortalaması; f_s/N'nin katlarını sıfırlayan basit dijital filtre |
| **Jitter** | Örnekleme anlarının titremesi; f_s'nin sabit olmaması |
| **RF doğrultma (rectification)** | Doğrusal olmayan bir girişin RF'i düşük frekanslı veya DC bir hataya çevirmesi |
| **Undersampling** | Aliasing'in bilerek kullanılması: yüksek frekanslı dar bir bandı düşük f_s ile örnekleyip aşağı katlamak (radyo alıcılarında) |
| **dB/dekad** | Frekans 10 katına çıktığında zayıflatmanın kaç dB arttığı (1. derece filtre: 20) |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.3, bölüm 6):

- [x] Sinyal bandı (B), f_s ve filtre f_c'si şematikte not edildi; k·f_s ± B bölgelerindeki bozucular hata bütçesinin (ör. ½ LSB) altına iniyor
- [x] Anti-aliasing RC'si ADC pinine bitişik; 2. kademe filtre için yer (DNP) bırakıldı
- [x] Filtresiz, düşük f_s yok; şebeke için tam periyotluk ortalama planlandı (50 Hz → 20 ms; 60 Hz pazarı da varsa 100 ms)
- [x] 1 kHz, f_s'nin tam katı değil (RF bağışıklık testindeki 1 kHz AM DC'ye katlanmaz; ör. f_s = 1,2 kHz)
- [x] Firmware notu: ADC timer ile tetikleniyor; seyreltme ve loglama öncesinde ortalama var

## Kontrol soruları

→ [quiz.md](quiz.md) · 13 soru, 5'i hesap
