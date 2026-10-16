# Op-amp ve sensör ön ucu

- **Oluşturma:** 2026-10-16
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Bağlantılı:** [Aliasing ve anti-aliasing filtresi](../aliasing-ve-anti-aliasing-filtresi/ozet.md) · [Kapasitör, bölüm 10 (RC filtre)](../../Komponentler/02-kapasitor/ozet.md#10-derinleştirme-rc-filtre-ve-aliasing) · [Mikrodenetleyici, ADC girişi](../../Komponentler/05-mikrodenetleyici-donanimi/ozet.md#7-adc-girişi) · [Direnç (bölücü, ince film)](../../Komponentler/01-direnc/ozet.md#53-gerilim-bölücü-ve-adc) · Kontrol listesi bölüm 6

> Sayısal değerler **tipik başlangıç noktalarıdır**; tasarım değeri için kullandığın op-amp, sensör ve ADC'nin datasheet'i esastır. Pellistor değerleri sensör modeline göre çok değişir.
>
> **Okuma planı:** 1. oturum: bölüm 1–4 (op-amp temeli) · 2. oturum: 5–9 (hatalar, köprü, referans) · 3. oturum: 10–17.

---

## ⚡ Hızlı tekrar

1. Sensör sinyali çoğu zaman **küçük** (mV) veya **zayıftır** (yüksek empedans). ADC'ye doğrudan bağlanmaz; arada bir **ön uç** vardır: koruma → köprü/bölücü → yükseltme → filtre → ADC.
2. Negatif geri beslemeli op-amp'ın iki kuralı: **girişlerine akım akmaz** ve çıkışını **iki girişi eşit tutacak** şekilde ayarlar.
3. Kazanç: evirmeyen `1 + Rf/Rg`, eviren `−Rf/Rin`, tampon `1`.
4. Op-amp sinyalle birlikte **hatasını da yükseltir**: `ofset × kazanç`. 1 mV ofset, 100 kazançla 100 mV hata demektir. DC hassas ölçümde düşük ofsetli veya **zero-drift** op-amp.
5. Tek beslemede girişler ve çıkış raylara ne kadar yaklaşabiliyor? Sinyal 0 V'a iniyorsa **rail-to-rail** ve çıkış salınımı kontrol edilir.
6. **Köprü (Wheatstone)**, küçük direnç değişimini ölçmenin standart yoludur. Pellistor buna dayanır. Köprü ve ADC aynı referanstan beslenirse besleme hatası iptal olur (**oransal ölçüm**).
7. ADC referansı ölçümün **cetvelidir**: referans %1 kayarsa ölçüm de %1 kayar.
8. Hızlı gürültüyü **filtre**, yavaş kaymayı (sıcaklık, yaşlanma) **kalibrasyon ve kompanzasyon** çözer. Dış dünyaya açık girişte **seri direnç + kenetleme**.

## 🧮 Formül kartı

| Formül | Ne zaman kullanılır | Örnek |
|---|---|---|
| `G = 1 + Rf/Rg` | Evirmeyen yükselteç | 99k / 1k → **G = 100** |
| `G = −Rf/Rin` | Eviren yükselteç | 10k / 1k → **−10** |
| `V_hata = Vos × G` | Ofsetin çıkıştaki etkisi | 2 mV × 50 → **100 mV** |
| `BW ≈ GBW / G` | Kazançla kalan bant genişliği | 1 MHz / 100 → **10 kHz** |
| `ΔV ≈ Vb × ΔR / (4R)` | Köprüde küçük değişimin çıkışı | 2,5 V, %1 → **6,25 mV** |
| `V_hata = I_bias × R_kaynak` | Bias akımının ek ofseti | 1 nA × 1 MΩ → **1 mV** |
| `R_koruma ≥ (V_arıza − V_kenet) / I_max` | Giriş koruma direnci | (24 − 3,6) V / 5 mA → **≥ 4,1 kΩ** |
| `G = 1 + 50 kΩ / R_G` | INA128 tipi ölçüm yükselteci (datasheet'e bak) | G = 100 → R_G ≈ **505 Ω** |

---

## 1. Sensör ön ucunun görevi

Sensörü **fısıldayan bir konuşmacı** gibi düşün. Sesi duymak için mikrofon ve yükselteç gerekir. Ama yükselteç, yan odadaki fan sesini de yükseltir. Ön ucun işi: fısıltıyı **doğru** yükseltmek, fanı yükseltmemek.

```
 Sensör ──[Koruma]──[Köprü / bölücü]──[Yükseltme]──[Filtre]──[ADC]── MCU
           seri R      küçük değişimi     op-amp       RC        referans
           kenetleme   gerilime çevirir   / INA     (anti-alias)  = cetvel
```

| Halka | Yanlış yapılırsa |
|---|---|
| Koruma | Kablodaki darbe op-amp'ı veya ADC'yi yakar |
| Köprü / bölücü | Besleme gürültüsü sinyalle karışır |
| Yükseltme | Ofset ve kayma sinyali gömer |
| Filtre | Aliasing, şebeke gürültüsü ölçüme karışır |
| Referans | Bütün ölçüm toplu hâlde kayar |

## 2. Op-amp'ın iki kuralı

Op-amp'ı **çok hevesli bir terazi görevlisi** gibi düşün: iki kefeyi (+ ve − girişleri) her zaman eşit tutmak için çıkışını ayarlar. Bunu ancak çıkış, geri besleme ile − girişe bağlıysa yapabilir.

1. **Girişlere akım akmaz** (gerçekte pA–nA mertebesinde akar).
2. **İki giriş eşit gerilimde tutulur** (negatif geri besleme varken ve çıkış sınıra dayanmamışken).

Bütün temel devreler bu iki kuralla hesaplanır.

## 3. Temel devreler

**Tampon (gerilim izleyici), G = 1:**

```
 Vin ──┤+ \
       │   >──┬── Vout = Vin
    ┌──┤- /   │
    └─────────┘
```

Yüksek empedanslı bir sensörü ya da bölücüyü, ADC'nin akım çeken örnekleme kapasitöründen **ayırır**. Sinyali yükseltmez ama "güçlendirir".

**Evirmeyen yükselteç:**

```
 Vin ─────────┤+ \
              │   >──┬── Vout = Vin × (1 + Rf/Rg)
         ┌────┤- /   │
         │           │
         ├───[Rf]────┘
         │
       [Rg]
         │
        GND
```

**Örnek:** Rf = 99 kΩ, Rg = 1 kΩ → G = 100. 10 mV'luk sinyal → 1,0 V.

**Fark yükselteci ve ölçüm yükselteci (INA):** İki noktanın **farkını** yükseltir, ikisinde ortak olan gerilimi (ortak mod) atar. Köprü çıkışları için kullanılır (bölüm 7–8).

## 4. Tek besleme ve rail-to-rail

MCU'lu kartların çoğunda op-amp yalnızca **0 V ve +3,3 V (veya +5 V)** ile beslenir. Bu durumda:

- **Giriş ortak mod aralığı:** Girişler hangi gerilim aralığında doğru çalışır? Bazı op-amp'lar, girişler pozitif raya 1–2 V yaklaşınca çalışmaz.
- **Çıkış salınımı:** "Rail-to-rail çıkış" bile raylara tam ulaşamaz; yüke göre 10 mV – 100 mV kadar yaklaşır.
- **Sorun nerede çıkar?** Sensör çıkışı **0 V civarındaysa** (ör. gaz yokken), op-amp çıkışı 0 V'a inemez ve küçük sinyaller ölçülemez.

**Çözümler:**
- Giriş ve çıkışı **rail-to-rail (RRIO)** bir op-amp seç ve sinyal aralığını raylardan biraz uzakta tasarla.
- **Sanal toprak:** Sinyali besleme ortasına (ör. 1,65 V) kaydır. İki yönlü sinyaller için standart yöntemdir. Bu orta gerilimi bir tamponla sür.
- Kullanılmayan op-amp kanalını boşta bırakma; tampon olarak bağla, girişini ortak mod aralığında bir gerilime çek (kontrol listesi bölüm 1).

## 5. DC hatalar: ofset, bias akımı, direnç toleransı

Gaz ölçümü gibi **yavaş (DC) sinyallerde** en büyük düşman op-amp'ın kendi DC hatalarıdır. Çünkü bu hatalar da sinyal gibi yükselir.

| Hata | Nedir | Etkisi |
|---|---|---|
| **Ofset gerilimi (Vos)** | Girişler arasındaki küçük dengesizlik | `Vos × G` kadar çıkış hatası |
| **Ofset kayması (µV/°C)** | Vos'un sıcaklıkla değişmesi | Kalibrasyonla silinmez, sıcaklıkla gelir |
| **Bias akımı** | Girişlerden akan küçük akım | `I_bias × R_kaynak` kadar ek ofset |
| **Direnç toleransı** | Rf ve Rg'nin değer hatası | Kazanç hatası (iki %1 direnç → ~%2) |
| **Direnç TCR'si** | Direncin sıcaklıkla değişmesi | Kazanç sıcaklıkla kayar |

**Örnek (G = 100):**

| Op-amp sınıfı | Tipik Vos | Çıkıştaki hata |
|---|---|---|
| Genel amaçlı | 1–5 mV | 100–500 mV ✗ |
| Hassas | 10–100 µV | 1–10 mV |
| Zero-drift (chopper) | < 10 µV | < 1 mV ✓ |

- Kalibrasyon **başlangıç ofsetini** siler; **kaymayı** silmez. Sıcaklıkla çalışan bir cihazda düşük kaymalı (zero-drift) op-amp seç.
- Kazanç yolunda **%0,1–%1 ince film** dirençler kullan; dirençler aynı sıcaklıkta kalsın diye yan yana yerleştir.
- Yüksek empedanslı kaynakta bias akımı düşük (CMOS girişli) op-amp seç.

## 6. AC tarafı: bant genişliği ve kararlılık

- **GBW (kazanç-bant genişliği çarpımı):** Kazanç arttıkça bant genişliği düşer: `BW ≈ GBW / G`. 1 MHz'lik bir op-amp 100 kazançta ~10 kHz'e kadar çalışır. Gaz sinyali için fazlasıyla yeterli.
- **Kapasitif yük:** Op-amp çıkışına doğrudan büyük bir kapasitör (ör. ADC'nin RC filtresindeki C) bağlanırsa **salınabilir**. Çıkışa 10–100 Ω seri **izolasyon direnci** koy; RC filtrenin R'si zaten bu işi görür (kontrol listesi bölüm 6).
- Yavaş sinyallerde gereğinden hızlı op-amp seçmek yarar getirmez; gürültüyü ve RF hassasiyetini artırabilir.

## 7. Köprü devresi ve pellistor

**Wheatstone köprüsü**, iki gerilim bölücünün yan yana konmasıdır. Çıkış, iki bölücünün orta noktaları arasındaki **farktır**.

```
          Vb (köprü beslemesi)
        ┌────┴────┐
       [R1]      [R3]
        │         │
        A ── Vout ── B        Vout = V_A − V_B
        │         │
       [R2]      [R4]
        └────┬────┘
            GND
```

- Dört direnç eşitse Vout = 0 (köprü **dengede**).
- Bir direnç küçük bir ΔR kadar değişirse: `Vout ≈ Vb × ΔR / (4R)`.
- **Örnek:** Vb = 2,5 V, direnç %1 değişiyor → `2,5 × 0,01 / 4 = 6,25 mV`. Küçük bir sinyal; yükseltme gerekir.

**Neden köprü?** Tek bir bölücüde %1'lik değişim, 1,25 V'luk büyük bir gerilimin üstünde 6 mV'luk bir oynama olarak görünürdü. Köprüde ise dengede **sıfırdan** başlar; yalnızca değişim yükseltilir.

**Pellistor (katalitik sensör):**
- İki boncuk vardır: **dedektör** (aktif) ve **kompanzatör** (pasif). İkisi köprünün bir kolunda seri bağlıdır, diğer kolda iki sabit direnç (ve sıfır ayarı) bulunur.
- Dedektör, yanıcı gazı yüzeyinde yakar, ısınır ve direnci artar → köprü dengesi bozulur → çıkış gazla orantılı.
- **Kompanzatör** aynı sıcaklıkta ama gaza duyarsızdır. Ortam sıcaklığı ve nem gibi **yavaş** değişimleri iki boncuk aynı şekilde gördüğü için köprüde birbirini götürür. Bu, "yavaş gürültüyü filtre değil yapı çözer" ilkesinin örneğidir (bölüm 10).
- Boncuklar ısıtılarak çalışır; köprü beslemesi tipik olarak **birkaç volt ve onlarca–yüzlerce mA**'dir. Duyarlılık besleme akımına bağlı olduğu için **köprü beslemesi kararlı** olmalı. Değerler sensörün datasheet'inden alınır.
- Tam skala çıkış tipik olarak onlarca–birkaç yüz mV'tur; sıfır ve span **kalibrasyonla** ayarlanır.

**Yarı iletken (MOS) sensörlerde** genelde köprü yerine sensör ile bir yük direncinden oluşan basit bir **bölücü** kullanılır; çıkış volt seviyesindedir ve çoğu zaman yükseltme gerekmez.

## 8. Ölçüm yükselteci (INA)

Köprünün iki çıkışı da yaklaşık Vb/2'dedir (ortak mod); ölçülecek olan ikisinin arasındaki birkaç mV'luk farktır. **INA**, bu farkı yüksek doğrulukla yükseltir, ortak modu atar.

- **Kazanç tek dirençle** ayarlanır (ör. INA128 tipinde `G = 1 + 50 kΩ / R_G`; kendi parçanın formülüne bak).
- **CMRR yüksektir:** Ortak moddaki gürültü (ör. köprü beslemesinin dalgalanması) çıkışa geçmez.
- **REF pini:** Çıkışın sıfır noktasını belirler. Tek beslemede genelde orta gerilime bağlanır. **REF pinini doğrudan bir direnç bölücüyle sürme**: bölücünün direnci INA'nın iç dirençlerine eklenir ve kazanç/CMRR bozulur. Bölücü kullanılacaksa araya bir **tampon** koy.
- **Giriş ve çıkış aralığı:** Tek beslemeli INA'larda girişlerin ve çıkışın hangi kombinasyonda doğru çalıştığı datasheet'teki bir grafikte verilir. Köprü çıkışı bu bölgenin içinde mi, kontrol et.

## 9. Referans gerilimi: ölçümün cetveli

ADC her ölçümü referans gerilimine göre yapar: `sayı = (V_giriş / V_ref) × 2ⁿ`. Cetvel uzarsa her şey kısa görünür.

| Seçenek | Doğruluk | Not |
|---|---|---|
| VDD'yi referans almak | Regülatör toleransı (ör. ±%2) | Ucuz; gürültü ve sıcaklıkla kayma ölçüme geçer |
| Ayrı referans IC'si | ±%0,05–0,5, düşük kayma (ppm/°C) | Hassas mutlak ölçüm için |
| **Oransal (ratiometric) ölçüm** | Besleme hatası **iptal olur** | Sensör beslemesi = ADC referansı |

**Örnek:** 3,3 V'luk bir LDO'nun ±%2 toleransı ±66 mV demektir; 12 bitte bu, tam skalada ±82 LSB hatadır.

**Oransal ölçüm neden iptal eder?** Köprü veya bölücünün çıkışı beslemeyle orantılıdır: besleme %1 artarsa çıkış da %1 artar. ADC referansı da aynı beslemeden geliyorsa cetvel de %1 uzar. Oran değişmez. Sensör beslemesi ile ADC referansı **aynı noktadan** alınmalı (veya ikisi birden ölçülmeli).

Referans pininin datasheet'teki dekuplaj önerisine uy; gürültülü bir referans her ölçüme gürültü ekler.

## 10. Gürültü: hızlı mı, yavaş mı?

"Hızlı" ve "yavaş" frekansı anlatır: gürültünün saniyede kaç kez gidip geldiği. Karar, gürültünün **bilgiye göre** hızına bağlıdır.

| Kaynak | Tipik frekans | Çözüm |
|---|---|---|
| Sıcaklık kayması, sensör yaşlanması, sıfır kayması | Dakikalar – saatler (bilgi kadar yavaş) | **Filtre çözemez** → kalibrasyon, sıcaklık kompanzasyonu, kompanzatör eleman |
| Gaz sinyali (karşılaştırma için) | Saniyeler | — |
| Şebeke ve harmonikleri | 50 Hz, 100 Hz… | RC + yazılımda 20 ms'lik ortalama |
| Anahtarlamalı regülatör | 100 kHz – 2 MHz | RC, ferrit, LDO, layout |
| Dijital hatlar, telsiz, GSM | MHz – GHz | Girişte küçük C, ferrit, ekran |

**Nasıl anlarsın?**
1. **Kaynağını bil:** Regülatörün datasheet'indeki anahtarlama frekansı, şebeke frekansı, MCU saati.
2. **Osiloskopla ölç:** Tırtıklar arası süre T → `f = 1/T`. FFT modu frekansları tepe olarak gösterir. Tetiklemeyi "Line" yap; gürültü ekranda sabit duruyorsa şebeke kaynaklıdır.
3. **Şüpheli kaynağı kapat:** Regülatörü devre dışı bırak, kartı pille besle. Gürültü kayboluyorsa kaynağı buldun.
4. Hızlı gürültüyü **ADC verisinden teşhis etme**: aliasing yüzünden yavaş görünür ([Aliasing dersi](../aliasing-ve-anti-aliasing-filtresi/ozet.md)).

## 11. Giriş koruması

Kabloyla dışarıdan gelen her sensör girişi bir gün yanlış gerilim, ESD veya darbe görür.

```
 Kablo ──[R_koruma]──┬──[R]──┬── op-amp / ADC girişi
                     │       │
              kenetleme     [C]  (RC: anti-aliasing + RF)
              (diyot/TVS)    │
                     │      GND
                    GND
```

- **Seri direnç** arıza akımını sınırlar. Op-amp ve ADC girişlerinin mutlak maksimum akımı tipik olarak birkaç mA'dir (datasheet).
- **Örnek:** Girişe yanlışlıkla 24 V geliyor, kenetleme 3,6 V, en çok 5 mA → `R ≥ (24 − 3,6) / 5 mA ≈ 4,1 kΩ` → **4,7 kΩ**.
- **Dikkat – rayı şişirme:** Kenetleme diyotları arıza akımını +3,3 V rayına akıtır. Ray az yüklüyse bu akım rayın gerilimini yükseltebilir. TVS/Zener ile GND'ye kenetlemek veya akımı küçük tutmak daha güvenlidir.
- Seri direnç gürültü ve (bias akımıyla) ofset ekler; yavaş sinyallerde birkaç kΩ genellikle sorun değildir.

## 12. Şematikte

- Her katın **kazancını, f_c'sini ve beklenen çıkış gerilimini** not et: `Gaz yok: TP5 ≈ 0,50 V; tam skala: ≈ 2,8 V`.
- Kazanç yolundaki dirençlerin tolerans ve türü (ince film, %0,1–%1) yazılı.
- INA'nın REF pini tamponla sürülüyor; köprü beslemesi kararlı ve **ADC referansıyla ilişkisi** (oransal mı, ayrı referans mı) not edilmiş.
- Her katın çıkışında bir **test noktası**.
- Kullanılmayan op-amp kanalı tampon olarak bağlı.

## 13. PCB / layout

- Analog ön uç kartın **sessiz bölgesinde**: buck, bobin, röle ve dijital hatlardan uzak.
- **Geri besleme direnci** op-amp'ın − girişine yakın; − girişindeki iz kısa (parazitik kapasitans salınıma ve gürültüye yol açar).
- Köprü ve kazanç dirençleri **yan yana ve simetrik**: aynı sıcaklıkta kalsınlar. Isıtıcıdan, regülatörden ve güç dirençlerinden uzak.
- Yüksek empedanslı düğümler (MΩ) kısa; çok hassassa **koruma halkası (guard ring)**. Lehim pastası ve flux kalıntısı yüksek empedansta kaçak akım yaratır; kart temizlenmeli.
- Yüksek akımlı dönüşler (ısıtıcı, röle, buzzer) analog ölçüm bölgesinin altından geçmemeli ([PCB yerleşim dersi](../pcb-yerlesim-ve-iz-cizimi/ozet.md)).

## 14. EMC açısından

- **RF doğrultma:** Op-amp girişleri, MHz–GHz'lik RF'i doğrultarak **DC kaymaya** çevirebilir. RF bağışıklık testinde gaz okumasının kayması bu yüzden olur.
- Önlem: op-amp/INA girişlerine küçük RC (ör. birkaç yüz Ω + 100 pF – 1 nF, C0G), INA'larda hem iki giriş arasına hem her girişten GND'ye kapasitör; kablo girişinde ferrit.
- RF testindeki 1 kHz AM modülasyonunun ADC'de DC'ye katlanmaması için örnekleme frekansı seçimi: [Aliasing dersi, bölüm 12](../aliasing-ve-anti-aliasing-filtresi/ozet.md#12-emc-açısından).

## 15. Ölçüm ve doğrulama

1. **Sensör yerine bilinen bir giriş:** Köprüyü dirençlerle taklit et veya hassas bir gerilim kaynağı uygula. Her katın çıkışı hesapla tutuyor mu?
2. **Sıfır ve tam skala:** Gaz yokken ve kalibrasyon gazıyla çıkışlar; çıkış raylara dayanıyor mu (doyum)?
3. **Gürültü tabanı:** Gaz yokken birkaç yüz ADC okumasının standart sapması kaç LSB?
4. **Sıcaklık testi:** Kartı ısıtıp soğut (fırın/iklim kabini); sıfır ne kadar kayıyor?
5. **Besleme değişimi:** Besleme gerilimini toleransın iki ucuna götür; oransal ölçümde okuma değişmemeli.

## 16. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| Genel amaçlı op-amp ile yüksek kazançlı DC ölçüm | Ofset sinyali gömer | Zero-drift / hassas op-amp |
| Tek beslemede 0 V'a inen sinyal | Çıkış 0 V'a ulaşamaz | RRIO, sanal toprak, ofset |
| INA REF pinini dirençle sürmek | Kazanç ve CMRR bozulur | Tampon |
| VDD'yi referans alıp mutlak ölçüm beklemek | Regülatör toleransı ölçüme geçer | Oransal ölçüm veya referans IC |
| Op-amp çıkışına doğrudan büyük C | Salınım | Seri izolasyon direnci |
| Yavaş kaymayı filtreyle çözmeye çalışmak | Filtre ayıramaz | Kalibrasyon, kompanzasyon |
| Korumasız kablo girişi | ESD/darbe op-amp'ı yakar | Seri R + kenetleme |
| Kazanç dirençleri ısı kaynağının yanında | Sıcaklıkla kazanç kayar | Simetrik, sıcaklıktan uzak yerleşim |
| Girişte RF filtresi yok | RF testinde okuma kayar | Küçük RC (C0G), ferrit |

## 17. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Op-amp** | Yüksek kazançlı fark yükselteci; geri beslemeyle kullanılır |
| **Tampon (buffer)** | Kazancı 1 olan, kaynağı yükten ayıran op-amp devresi |
| **Ofset gerilimi (Vos)** | Girişler eşitken çıkışta görülen hatanın giriş eşdeğeri |
| **Zero-drift / chopper** | Ofsetini sürekli düzelten, çok düşük kaymalı op-amp |
| **Bias akımı** | Op-amp girişlerinden akan küçük akım |
| **Rail-to-rail (RRIO)** | Girişi ve çıkışı besleme raylarına yakın çalışabilen op-amp |
| **GBW** | Kazanç × bant genişliği çarpımı |
| **Wheatstone köprüsü** | İki bölücünün farkını ölçen dört dirençli devre |
| **INA** | Ölçüm yükselteci; farkı yükseltir, ortak modu atar |
| **CMRR** | Ortak mod gerilimini bastırma oranı |
| **Oransal (ratiometric) ölçüm** | Sensör beslemesi ile ADC referansının aynı olduğu ölçüm |
| **Pellistor** | Katalitik yanma ile yanıcı gazı ölçen, dedektör + kompanzatör boncuklu sensör |
| **Sanal toprak** | Tek beslemede besleme ortasına kurulan referans gerilimi |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.4, bölüm 6):

- [x] Yüksek kazançlı DC yolda ofset × kazanç hesaplandı; gerekiyorsa zero-drift op-amp
- [x] Kazanç ve köprü dirençleri yan yana, ısı kaynaklarından uzak (layout notu)
- [x] INA'nın REF pini düşük empedanslı (tamponlu) bir kaynaktan sürülüyor
- [x] Köprü/sensör beslemesi sensör datasheet'ine göre kararlı (duyarlılık beslemeye bağlı)
- [x] Op-amp/INA girişlerinde RF'e karşı küçük RC (C0G) var
- [x] Kenetleme diyotlarının arıza akımı besleme rayını yükseltmiyor

## Kontrol soruları

→ [quiz.md](quiz.md) · 10 soru, 5'i hesap
