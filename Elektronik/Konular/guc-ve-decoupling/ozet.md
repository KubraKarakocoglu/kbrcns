# Güç ve decoupling

- **Oluşturma:** 2026-10-12 · **Güncelleme:** 2026-10-12 (detaylı sürüm)
- **İlk kaynak:** https://www.analog.com/media/en/training-seminars/tutorials/MT-101.pdf
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)

> Birden fazla kaynaktan derlendi. Sayısal değerler **tipik başlangıç noktalarıdır**; tasarım değeri için her zaman kullandığın IC'nin datasheet'i esastır.

---

## ⚡ Hızlı tekrar

1. Dijital IC'ler akımı **nanosaniyelik darbelerle** çeker. Uzaktaki regülatör ve iz endüktansı bu hıza yetişemez.
2. Yerel kapasitör bu darbeyi karşılar ve IC'nin gürültüsünün besleme ağına yayılmasını keser.
3. Gerçek kapasitör = **C + ESR + ESL**. Self-rezonans frekansının (SRF) üstünde endüktör gibi davranır.
4. Yüksek frekansta kapasitörün değeri değil, **montaj endüktansı** (yerleşim) belirleyicidir.
5. Katmanlı yapı: rayda **bulk** (µF) + **her besleme pinine 100 nF** + datasheet'in özel istekleri.
6. **X7R/X5R** kullan, **Y5V** kullanma. Yüksek değerli MLCC'de **DC bias** kaybını eğriden kontrol et.
7. Decoupling **ilk EMC önlemidir**: küçük akım döngüsü daha az ışıma yapar ve daha az gürültü alır.

## 🧮 Formül kartı

| Formül | Ne zaman kullanılır | Örnek |
|---|---|---|
| `I = C · dV/dt` | Bir yükün (pin, kapı) şarj akımı | 20 pF, 3,3 V, 2 ns → 33 mA |
| `V = L · di/dt` | Endüktans üzerindeki ani gerilim düşümü | 10 nH, 100 mA / 5 ns → 0,2 V |
| `C = I · Δt / ΔV` | Darbeyi karşılamak için gereken minimum kapasite | 200 mA, 10 ns, 50 mV → 40 nF |
| `X_L = 2πfL` · `X_C = 1/(2πfC)` | Belirli bir frekanstaki empedans | 10 nH @100 MHz → 6,3 Ω |
| `f_SRF = 1/(2π√(ESL·C))` | Kapasitörün etkili olduğu üst sınır | 100 nF, 1 nH → ≈16 MHz |
| `Z_hedef = ΔV_izin / ΔI` | Besleme ağının (PDN) empedans hedefi | 3,3 V, %3, 0,5 A → ≈0,2 Ω |

---

## 1. Problem: Dijital devre akımı neden darbeli çeker?

Bir CMOS kapı her anahtarlandığında, çıkışındaki yük kapasitansını (sonraki kapıların girişi, iz kapasitansı, dış yük) şarj veya deşarj eder. Bu akım `I = C · dV/dt` ile hesaplanır ve yalnızca **kenar anında** akar.

Bir mikrodenetleyicide binlerce iç kapı aynı saat kenarında anahtarlanır. Sonuç: ortalama akım mA seviyesindeyken, kenar anlarındaki **tepe akım bunun çok katı** olabilir.

**Örnek: aynı anda anahtarlanan çıkış pinleri**
- 8 GPIO pini aynı anda 0 → 3,3 V'a çıkıyor; her pinin yükü 20 pF; kenar süresi 2 ns.
- Tek pin: `I = 20 pF × 3,3 V / 2 ns = 33 mA`
- 8 pin: **264 mA tepe akım**, sadece 2 ns boyunca.

Bu akım bir yerden gelmek zorunda. Uzaktaki regülatörden gelemez (bkz. bölüm 2). Gelmesi gereken yer, pinin hemen yanındaki kapasitördür.

## 2. Akımın yolu: endüktans ve ground bounce

Regülatörden IC'ye giden her yolun (iz, via, konnektör, IC'nin bacak teli) **endüktansı** vardır. Sezgi için: düzlemden uzak ince bir iz veya tel, milimetre başına yaklaşık 1 nH civarındadır. Altında kesintisiz GND düzlemi olan bir izde bu değer çok daha düşüktür. Gerçek değer geometriye bağlıdır.

Endüktans yüksek frekansta büyük empedans demektir:

| Eleman | 1 MHz'de | 100 MHz'de |
|---|---|---|
| 10 nH iz | 0,06 Ω | **6,3 Ω** |
| İdeal 100 nF kapasitör | 1,6 Ω | 0,016 Ω |

100 MHz'de 10 nH'lik bir iz, kapasitörden yaklaşık 400 kat daha "zor" bir yoldur. Bu yüzden akım darbesi uzaktaki regülatörden değil, yakındaki kapasitörden gelir. Tabii kapasitör gerçekten **yakınsa**.

**Regülatör neden yetişemez?** LDO veya buck regülatörün kontrol döngüsü mikrosaniyeler mertebesinde tepki verir. Nanosaniyelik bir darbeyi o sürede fark edemez bile.

**Ground bounce (toprak sıçraması):** Aynı endüktans **dönüş yolunda** (GND) da vardır. Örnekteki 264 mA, 2 nH'lik ortak GND bağlantısından 2 ns'de geçerse:
`V = 2 nH × 264 mA / 2 ns ≈ 0,26 V`

Yani IC'nin "sıfır volt" referansı anlık olarak 0,26 V yükselir. Sonuçları: lojik seviyeler kayar, ADC ölçümleri bozulur, hassas girişler yanlış tetiklenir.

## 3. Çözüm: Decoupling'in iki görevi

1. **Yük deposu:** Darbe anında gereken yükü verir. Miktarı `C = I · Δt / ΔV` ile hesaplanır.
2. **Yerel dönüş yolu:** Yüksek frekanslı akım, kapasitör → IC → GND arasındaki **küçük döngüde** kalır. Bu sayede kartın geri kalanına (besleme hattı, kablolar) yayılmaz.

> **Decoupling ve bypass:** İki terim pratikte birbirinin yerine kullanılır. *Bypass*, gürültüyü toprağa kısa devre etmeyi; *decoupling* ise devreleri ortak besleme ağı üzerinden birbirinden ayırmayı vurgular. Aynı kapasitör iki işi birden yapar.

**Benzetme:** Regülatör uzaktaki baraj, iz endüktansı ince ve uzun bir boru, decoupling kapasitörü evin çatısındaki su deposu. Musluğu aniden açtığında suyu baraj değil depo verir. Baraj depoyu daha sonra yavaşça doldurur.

## 4. Gerçek kapasitör: C + ESR + ESL

```
Gerçek kapasitörün modeli:

  ──[ ESR ]──[ ESL ]──| |──
    direnç   endüktans  C
```

Empedans: `|Z| = √( ESR² + (X_L − X_C)² )`

```
|Z|
 │ \                         /
 │  \   kapasitif           /   endüktif
 │   \                     /
 │    \___________________/  ← en düşük empedans ≈ ESR
 └─────────────┬──────────────── frekans
              SRF  (X_L = X_C)
```

| Parametre | Neyi belirler |
|---|---|
| **C** | Düşük frekanslı davranış ve depolanan yük |
| **ESR** | Eğrinin dibi (minimum empedans) ve rezonans sönümlemesi |
| **ESL** | Yüksek frekanslı davranış. SRF üstünde empedans `2πf·ESL` olur |

**Kritik çıkarım:** SRF'nin üstünde kapasitans değeri artık önemsizdir. 100 nF ile 1 µF aynı ESL'e sahipse, 100 MHz'de aşağı yukarı aynı empedansı gösterirler. Yüksek frekansta kazanmanın tek yolu **ESL'i düşürmektir**: küçük paket, kısa montaj, pad'e bitişik via.

ESL iki parçadan oluşur:
- **Paket ESL'i:** Tipik olarak birkaç yüz pH ile ~1 nH arası.
- **Montaj endüktansı:** İz ve via'lar. Paketinkine eşit, hatta daha büyük olabilir.

Bu yüzden kötü yerleştirilmiş iyi bir kapasitör, iyi yerleştirilmiş sıradan bir kapasitörden daha kötü çalışır.

**SRF örnekleri** (montaj dahil ESL ile):

| Kapasitör | ESL | SRF |
|---|---|---|
| 100 nF | 1 nH | ≈ 16 MHz |
| 100 nF | 2 nH | ≈ 11 MHz |
| 10 µF | 2 nH | ≈ 1,1 MHz |

## 5. Katmanlı decoupling: hangi frekansı kim karşılar?

| Frekans aralığı (yaklaşık) | Kim karşılar |
|---|---|
| DC – birkaç kHz | Regülatörün kontrol döngüsü |
| kHz – ~1 MHz | **Bulk** kapasitörler (µF seviyesi) |
| ~1 MHz – ~100 MHz | **Yerel** 100 nF seramikler (pine yakın) |
| ~100 MHz üstü | IC paketinin içindeki kapasitans ve kartın güç/toprak düzlemleri. Kart üstündeki kapasitörler burada büyük ölçüde etkisizdir |

Mikrodenetleyici seviyesindeki tasarımlarda bu katmanları datasheet reçetesi zaten sağlar. FPGA ve hızlı işlemcilerde ise hedef empedans (`Z_hedef`) ile **PDN analizi** yapılır: besleme empedansının ilgili frekans bandının tamamında hedefin altında kalması gerekir.

## 6. Kapasitör seçimi

### Dielektrik kodları

| Kod | Sıcaklık aralığı | Sıcaklıkla değişim | Kullanım |
|---|---|---|---|
| **C0G / NP0** | −55…+125 °C | 0 ±30 ppm/°C (pratikte sabit) | Osilatör, filtre, zamanlama |
| **X7R** | −55…+125 °C | ±%15 | Decoupling için genel tercih |
| **X5R** | −55…+85 °C | ±%15 | Yüksek değerli decoupling (sıcaklık sınırına dikkat) |
| **Y5V** | −30…+85 °C | +%22 / −%82 | **Kullanma** |

> ⚠️ **Tuzak:** X7R'deki "±%15" yalnızca **sıcaklık** değişimidir. **DC bias** kaybı bunun üstüne ayrıca eklenir ve çok daha büyük olabilir.

### DC bias

- Yüksek dielektrik sabitli seramikler (X5R, X7R) DC gerilim altında **kapasite kaybeder**. C0G'de bu etki yoktur.
- Kayıp şu durumlarda büyür: **küçük paket**, **yüksek değer** ve çalışma gerilimi **nominal gerilime yakın**. Bu koşullarda efektif kapasite nominalin yarısının altına inebilir.
- **Önlem:** Gerilim derecesini çalışma geriliminin belirgin üstünde seç (ör. 3,3 V ray için 10 V veya 16 V) ya da bir büyük paket kullan. Efektif değeri üreticinin aracından kontrol et (Murata SimSurfing; diğer üreticilerin de benzer araçları var).

### Paket boyutu

| Paket | Artı | Eksi |
|---|---|---|
| 0402 | Düşük ESL, pine çok yakın konabilir | Elle lehimlemesi zor, aynı değerde DC bias kaybı daha fazla |
| 0603 | Elle lehimlenebilir, iyi bir denge | ESL biraz daha yüksek |
| 0805+ | Kolay lehim, düşük DC bias kaybı | Daha yüksek ESL, daha çok yer kaplar |

Prototip kartında elle lehim yapacaksan **0603** iyi bir başlangıçtır.

### Bulk kapasitör türleri

| Tür | Artı | Eksi / Dikkat |
|---|---|---|
| **Seramik (µF)** | Çok düşük ESR ve ESL | DC bias kaybı. Kart eğilirse **çatlayabilir**. Bazı devrelerde duyulabilir ses ("şarkı söyleme") çıkarır |
| **Alüminyum elektrolitik** | Ucuz, yüksek kapasite | Yüksek ESR. Ömrü sıcaklığa bağlıdır ve zamanla kurur; 105 °C dereceli olanı tercih et |
| **Polimer** (alüminyum veya tantal) | Düşük ESR, uzun ömür | Daha pahalı |
| **Tantal (MnO₂)** | Küçük hacimde yüksek kapasite | Arıza modu **kısa devre** olabilir (ısınma, yanma). Ani akıma hassastır. Yaygın öneri: çalışma gerilimi nominalin ~%50'si |

> **MLCC çatlaması:** Kart eğildiğinde (vida sıkma, konnektör takma, kartı panelden kırma) seramik kapasitör çatlayabilir ve **kısa devreye** dönüşebilir. Büyük MLCC'leri kart kenarından, vida deliklerinden ve konnektörlerden uzak tut.

## 7. Şematikte: kapasitör planı nasıl çıkarılır?

**Yöntem (her kart için uygula):**
1. Her IC'nin datasheet'inden **tüm besleme pinlerini** listele: VDD, VDDA, VREF+, VBAT, VCAP...
2. Her besleme pini çiftine **yerel kapasitör** ata.
3. Her raya **bulk** kapasitör ekle.
4. **Özel pinler** için datasheet'in istediğini birebir uygula.
5. Regülatörlerin **giriş ve çıkış** kapasitörlerini kendi datasheet'lerine göre seç; LDO'da çıkış kapasitörünün ESR aralığı kararlılık için kritiktir.
6. Her kapasitör için **DC bias** ve **gerilim derecesini** kontrol et.
7. Planı proje kartına tablo olarak yaz.

**Örnek: STM32F4 + LDO + sensör içeren 3,3 V kart**

| Nokta | Kapasitör | Kaynak |
|---|---|---|
| LDO girişi | Datasheet önerisi (tipik 1–10 µF) | LDO datasheet |
| LDO çıkışı | Datasheet'in **ESR aralığına** uygun değer ve tip | LDO datasheet |
| MCU VDD, her pin çifti | 100 nF X7R, 0402 veya 0603 | AN4488 |
| MCU 3,3 V rayı | En az 4,7 µF (tipik 10 µF) | AN4488 |
| MCU VDDA | VDD'den ferrit boncuk ile ayrılır, yerel kapasitörler eklenir | AN4488, MCU datasheet |
| MCU VCAP (varsa) | Datasheet'teki değer, düşük ESR'li seramik | MCU datasheet |
| Sensör VDD | 100 nF + datasheet'in istediği ekler | Sensör datasheet |

**Şematik çizim ipuçları:**
- Kapasitörü şematikte **besleyeceği IC pininin yanına** çiz ve notunu düş (ör. "U1 pin 24'e yakın"). Layout yapan kişi (veya ileride sen) hangi kapasitörün hangi pine ait olduğunu bilmeli.
- Kapasitör değerine dielektrik, gerilim ve paket bilgisini de yaz: `100n / X7R / 16V / 0402`.

## 8. PCB yerleşimi: en kritik bölüm

Amaç, **akım döngüsünün alanını** en küçük yapmaktır:

```
IC VDD pini → kapasitör → GND via → GND düzlemi → IC GND pini → (IC içinden) → VDD
```

Döngünün endüktansı alanıyla orantılıdır.

```
KÖTÜ                                 İYİ

 IC ┌──┐                              IC ┌──┐
VDD │  ├──────────────┐             VDD │  ├─┬──
    │  │   uzun iz    │                 │  │ █  ← 100 nF, pine bitişik
GND │  ├──┐          [C]            GND │  ├─●  ← via, pad'e bitişik
    └──┘  │           │                 └──┘
          ●  via      └─── uzun iz ── ●  via
```

**Kurallar:**
- **En küçük değerli / en küçük paketli** kapasitör pine en yakın olur; bulk biraz daha uzakta durabilir.
- **Via'yı pad'in hemen yanına** koy. Pad ile via arasındaki her milimetre endüktans demektir.
- **Her kapasitörün kendi GND via'sı** olsun; birkaç kapasitörü tek bir via'ya bağlama.
- IC'nin altında **kesintisiz GND düzlemi** olmalı. Düzlemi yarıklar veya sinyal izleriyle bölme.
- **4 katmanlı kart:** Önerilen dizilim *Sinyal / GND / Güç / Sinyal*. GND düzlemi komponent katmanına bitişik olmalı.
- **2 katmanlı kart:** Alt katmanı mümkün olduğunca kesintisiz GND yap. Beslemeyi önce kapasitörün pad'ine, oradan IC pinine götürmek yaygın bir uygulamadır.
- Kapasitörü IC'nin **arka yüzüne**, pinin tam altına koymak (kısa via'larla) yoğun kartlarda geçerli bir yöntemdir.

## 9. Analog besleme: ferrit boncuk ve filtre

**Neden gerekli?** ADC ve referans gerilimi, dijital gürültüye çok duyarlıdır. VDDA'ya gelen her mV gürültü, ölçüme doğrudan hata olarak eklenir.

**Ferrit boncuk nasıl çalışır?**
- Düşük frekansta (~100 kHz altı) endüktör gibi, yüksek frekansta **direnç gibi** davranır. Gürültüyü yansıtmaz, **ısıya çevirerek** yok eder.
- Datasheet'te genellikle **"Z @ 100 MHz"** değeriyle verilir (ör. 600 Ω @ 100 MHz). Ayrıca **DCR** (DC direnci) ve **anma akımı** vardır.

**Dikkat edilecekler:**
- **DC akımda doyma:** Boncuktan DC akım geçtikçe empedansı düşer. Datasheet'teki "impedance vs. DC bias" eğrisine bak.
- **LC rezonansı:** Boncuk ve kapasitör bir LC devresi oluşturur. Örnek değerlerle, ~1 µH ve 1 µF ≈ 160 kHz'de rezonansa girer. Rezonans frekansı civarında gürültü azalmak yerine **büyüyebilir**. Sönümleme gerekebilir (kapasitörün ESR'i veya küçük bir seri direnç). Mutlaka ölçerek ya da simüle ederek doğrula.
- **Yerleşim:** Boncuk iki ray arasına konur; yerel kapasitörler **IC tarafında** olur.
- **Boncuğu GND'ye koyma:** Toprağı boncukla bölmek genellikle dönüş yolunu bozar ve EMC'yi kötüleştirir.

**STM32F4 örneği (AN4488):** VDDA, VDD'ye ferrit boncuk üzerinden bağlanabilir.

## 10. EMC açısından decoupling

Decoupling, kartın **elektromanyetik uyumluluğu** (EMC) için atılan ilk ve en ucuz adımdır.

**Emisyon (ışıma):**
- Yüksek frekanslı akım taşıyan her döngü bir **anten** gibi davranır. Küçük bir döngünün ışıması kabaca **döngü alanı × akım × frekansın karesi** ile orantılıdır.
- İyi decoupling ile akım küçük yerel döngüde kalır, alan küçülür, ışıma azalır.
- Kötü decoupling'de gürültü besleme hattından **kablolara** ulaşır. Kablo, kartın en etkili antenidir.
- Emisyon testinde çıkan tepeler genellikle **saat frekansının harmonikleridir**. Decoupling bunları azaltır, sinyal kenarlarını gereksiz yere hızlı tutmamak da yardımcı olur.

**Bağışıklık (immunity):**
- ESD veya hızlı geçici darbeler (EFT) beslemeyi anlık olarak bozar. İyi decoupling ve bulk kapasite, MCU'nun bu sırada **resetlenmesini** veya kilitlenmesini önler.

**Dışarı açılan besleme hatları:** Kablodan gelen beslemeye girişte ferrit ve kapasitör ile filtre koymak, hem dışarı giden emisyonu hem de içeri giren bozucuları azaltır.

> EMC ayrı bir ders olarak ayrıntılı işlenecek.

## 11. Ölçüm ve doğrulama

**Osiloskopla besleme gürültüsü ölçerken:**
- Probun **uzun timsah GND kablosunu kullanma.** O kablo bir döngü oluşturur; manyetik alan toplar ve prob kapasitansıyla rezonansa girerek **sahte çınlama** gösterir. Bunun yerine probun **GND yayını** (ground spring) kullan.
- Ölçümü doğrudan **kapasitörün pad'lerinden** al.
- Rippleyi ölçerken **AC kuplaj** ve gerekirse **20 MHz bant genişliği sınırı** kullan. Hızlı gürültüye bakarken sınırı kapat.

**Decoupling sorununun belirtileri:**
- MCU'nun rastgele resetlenmesi veya brown-out
- ADC okumalarında açıklanamayan gürültü
- Haberleşme hataları (I²C, SPI, UART)
- EMC testinde saat harmoniklerinde tepeler
- Belirli bir yük açılınca (röle, LED, motor) sistemin bozulması

## 12. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| Kapasitör şematikte doğru, layout'ta uzak | Montaj endüktansı SRF'yi düşürür; kapasitör yüksek frekansta etkisiz kalır | Pine bitişik, via pad'in yanında |
| Tüm 100 nF'ler tek köşede ("kapasitör bankası") | Uzaktaki pinler fiilen decoupling'siz kalır | Her pinin kendi kapasitörü |
| Nominal değere güvenmek | DC bias ile efektif değer çok daha düşük olabilir | Üretici eğrisinden efektif değeri kontrol et |
| Y5V/Z5U kullanmak | Sıcaklık ve gerilimle kapasitansın çoğu kaybolur | X7R/X5R, gerekirse C0G |
| GND bağlantısı ince, uzun iz | Döngü alanı ve endüktans artar | Kısa yoldan doğrudan GND düzlemine |
| Birden fazla kapasitöre tek GND via'sı | Ortak endüktans oluşur | Her kapasitöre kendi via'sı |
| Ferrit boncuğu DC akıma bakmadan seçmek | Doyar ve filtre işe yaramaz | Akım derecesi ve DC bias eğrisi |
| Yalnızca bulk ya da yalnızca 100 nF | Frekans bantlarından biri açıkta kalır | İkisi birlikte |
| LDO çıkışına yanlış ESR'li kapasitör | Regülatör osilasyona girebilir | LDO datasheet'indeki ESR aralığı |
| MLCC'yi kart kenarına veya vida deliğine yakın koymak | Eğilmede çatlar, kısa devre olur | Gerilme bölgelerinden uzak yerleşim |

## 13. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Decoupling / Bypass** | IC'nin yanındaki yerel kapasitörle besleme ağından ayrılması / gürültünün toprağa kısa devre edilmesi |
| **ESR** | Equivalent Series Resistance: kapasitörün iç direnci |
| **ESL** | Equivalent Series Inductance: kapasitörün ve montajının endüktansı |
| **SRF** | Self-Resonant Frequency: kapasitörün kapasitif davranmayı bıraktığı frekans |
| **PDN** | Power Distribution Network: regülatörden IC'ye kadar tüm besleme ağı |
| **Droop** | Ani akımda beslemenin anlık çökmesi |
| **Ground bounce** | Dönüş yolundaki endüktans yüzünden toprak referansının anlık sıçraması |
| **DC bias** | Seramik kapasitörün DC gerilim altında kapasite kaybetmesi |
| **Derating** | Bir komponenti anma değerinin altında kullanarak güvenlik payı bırakmak |
| **Bulk** | Düşük frekanslı, büyük akım değişimleri için yüksek değerli kapasitör |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.1, bölüm 4):

- [x] Decoupling dielektriği X7R/X5R (küçük değerlerde C0G); Y5V/Z5U yok
- [x] Layout notu: pin → kapasitör → GND via döngüsü minimum; via pad'e bitişik
- [x] Analog besleme ferrit boncuğu: DC akım derecesi yeterli, LC rezonansı değerlendirildi
- [x] Tantal kullanıldıysa gerilim derating üretici önerisine uygun

## Kontrol soruları

→ [quiz.md](quiz.md) · 13 soru, 4'ü hesap
