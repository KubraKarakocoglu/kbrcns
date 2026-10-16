# Üretilebilirlik ve test için tasarım

- **Oluşturma:** 2026-10-16
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Bağlantılı:** [PCB yerleşim ve iz çizimi](../pcb-yerlesim-ve-iz-cizimi/ozet.md) · [Şematik çizim (BOM, revizyon)](../sematik-cizim-ve-dokumantasyon/ozet.md#11-bom-hijyeni) · [Kapasitör (MLCC çatlaması)](../../Komponentler/02-kapasitor/ozet.md) · [Mikrodenetleyici (bring-up, bölüm 8)](../../Komponentler/05-mikrodenetleyici-donanimi/ozet.md) · Kontrol listesi bölüm 9 ve 13

> Değerler **tipik** standart üretim kabiliyetleridir; her zaman kendi kart üreticinin ve dizgi firmanın kurallarını esas al.
>
> **Okuma planı:** 1. oturum: bölüm 1–5 (kart üretimi ve dizgi) · 2. oturum: 6–8 (test, üretim paketi) · 3. oturum: 9–13.

---

## ⚡ Hızlı tekrar

1. Kart yalnızca çalışmakla kalmamalı; **üretilebilmeli (DFM), monte edilebilmeli (DFA) ve test edilebilmeli (DFT).**
2. Tasarım kurallarını **üreticinin kabiliyetinden** al ve sınırlara dayanma. Sınırda tasarım = düşük verim, yüksek fiyat.
3. Footprint datasheet'e veya IPC-7351'e uygun; polariteli parçalar **aynı yöne**; parçalar arasında muayene ve tamir için boşluk.
4. **Panelleme:** V-kesim veya tırnaklı (mouse bite) freze. MLCC'ler ve konnektörler kırma çizgisinden uzak.
5. **Fiducial**'lar dizgi makinesinin gözüdür: kartta/panelde en az 3 tane, simetrik olmayan konumda.
6. Her önemli nete **test noktası**; tek yüzden erişilebilir; programlama ve kalibrasyon arayüzü üretimde ulaşılabilir.
7. **Üretim paketi:** Gerber + delik dosyası + üretim notu + BOM + pick & place + montaj çizimi. Hepsi **aynı revizyonda**.
8. İlk kartlarda kademeli **bring-up** ve ilk ürün kontrolü; bulunan her şey [hatalar-dersler.md](../../Sematik-Tasarim/hatalar-dersler.md) dosyasına.

## 🧮 Tablo kartı: tipik standart üretim değerleri

| Konu | Tipik standart değer | Not |
|---|---|---|
| En küçük iz / boşluk | 0,10–0,15 mm | Mümkünse 0,15 mm ve üstü kullan |
| En küçük delik | 0,20–0,30 mm | 0,3 mm ucuz ve güvenli |
| Halka (annular ring) | ≥ 0,10–0,15 mm | Delik kaçıklığına tolerans |
| Bakır – kart kenarı | ≥ 0,3 mm | V-kesimde daha fazla (≥ 0,4–0,5 mm) |
| Kart kalınlığı | 1,6 mm | Standart, en ucuz |
| Bakır | 1 oz (35 µm) | Yüksek akımda 2 oz |
| Yüzey kaplama | HASL veya ENIG | İnce aralıklı/QFN parçada ENIG |
| Test noktası | Ø ≥ 1 mm, aralık ≥ 2,54 mm | Fikstür iğnesi için |
| Fiducial | Ø 1 mm bakır, Ø 2–3 mm maske açıklığı | Çevresi boş |

---

## 1. Neden DFM, DFA, DFT?

Bir yemek tarifini düşün: evde 4 kişilik çok lezzetli olabilir. Ama 1000 kişilik bir mutfakta aynı tarif yapılamıyorsa, malzemesi bulunamıyorsa ya da pişip pişmediği kontrol edilemiyorsa işe yaramaz.

| Kısaltma | Soru | Kim etkilenir |
|---|---|---|
| **DFM** (Design for Manufacturing) | Bu kart **üretilebilir** mi? | Kart üreticisi |
| **DFA** (Design for Assembly) | Parçalar **dizilebilir ve lehimlenebilir** mi? | Dizgi firması |
| **DFT** (Design for Test) | Kartın doğru yapıldığı **test edilebilir** mi? | Üretim testi, servis |

**Maliyet kuralı (kabaca 1–10–100):** Bir hatayı tasarımda bulmak 1 birimse, üretimde bulmak 10, sahada bulmak 100 birime mal olur. DFM/DFA/DFT, hataları ucuz olduğu yerde yakalamaktır.

## 2. DFM: kart üretimi

- **Kuralları üreticiden al:** Üreticinin "capabilities" sayfasındaki en küçük iz/boşluk, delik, halka ve kenar mesafesini EDA aracına gir. Bu değerlerin bir kademe üstünde tasarla.
- **Delik çeşidini azalt:** Her farklı delik çapı bir matkap değişimidir. Via'lar için tek boyut, bacaklı parçalar için birkaç standart boyut kullan.
- **Kaplamalı (PTH) ve kaplamasız (NPTH) delikler:** Montaj delikleri ve kutuya oturma pimleri genelde kaplamasızdır. Montaj deliği GND'ye bağlanacaksa kaplamalı ve pedli olur; bu bir tasarım kararıdır.
- **Yüzey kaplama:**

| Kaplama | Artısı | Eksisi | Ne zaman |
|---|---|---|---|
| HASL (kurşunsuz) | Ucuz, yaygın | Yüzey düz değil | Büyük paketli, basit kartlar |
| ENIG | Düz yüzey, uzun raf ömrü | Daha pahalı | QFN, ince aralıklı IC, BGA, temas pedleri |

- **Lehim maskesi:** İnce aralıklı IC pinleri arasında maske köprüsü (dam) kalabilmesi için pinler arası boşluk yeterli olmalı. Yeşil maske en ucuz ve en hızlıdır; ayrıca gözle ve AOI ile muayenede en iyi kontrastı verir.
- **Malzeme:** Standart FR-4 çoğu iş için yeterlidir. Yüksek ortam sıcaklığı veya çok sayıda kurşunsuz lehim döngüsü varsa daha yüksek Tg'li malzeme belirtilir.
- **Empedans kontrolü** yalnızca gerekiyorsa (ör. USB, hızlı fark çiftleri) istenir; ek maliyettir.

## 3. DFA: dizgi ve montaj

**SMT akışı:** şablonla (stencil) lehim pastası basılır → dizgi makinesi parçaları yerleştirir → reflow fırınında lehimlenir → AOI ile gözle muayene edilir.

- **Bacaklı (THT) parçaları azalt:** Her THT parça ek bir süreç demektir (dalga, seçici lehim veya el lehimi). Mümkünse SMD seç.
- **Tek yüz dizgi** çift yüzden ucuzdur. Çift yüz gerekiyorsa ağır parçalar üst yüze.
- **Yön birliği:** Diyot, LED, elektrolitik ve IC'ler mümkün olduğunca aynı yöne bakar; dizgi programı ve gözle kontrol kolaylaşır, ters takma azalır.
- **Boşluk:** Parçalar arasında AOI kamerasının görebileceği ve havyanın girebileceği boşluk bırak. Uzun parçaları ince aralıklı IC'lerin dibine koyma (gölge yapar).
- **Mezar taşı (tombstoning):** Küçük pasiflerin iki pad'i farklı hızda ısınırsa parça dikilir. Pad'leri simetrik bağla; bir pad büyük bakıra doğrudan, diğeri ince izle bağlıysa termal rölyef kullan.
- **QFN termal pedi:** Pedin tamamına pasta basılırsa parça pasta üstünde yüzer ve kenar pinleri lehimlenmez. Şablonda ped **pencerelere** bölünür; kapsama tipik olarak **%50–80**. Örnek: 4 × 4 mm ped (16 mm²) içinde 4 adet 1,5 × 1,5 mm pencere = 9 mm² → **%56**.
- **Konnektörler** kablo çekilmesine dayanmalı: bacaklı tutunma pinleri veya mekanik sabitleme pedleri.
- **MLCC çatlaması:** Kart kenarı, vida deliği, konnektör ve kırma çizgisinin yanındaki büyük MLCC'ler kart eğildiğinde çatlar ([Kapasitör dersi](../../Komponentler/02-kapasitor/ozet.md)). Uzak tut; zorunluysa kırma çizgisine **paralel** yerleştir.
- **Yükseklik:** Parça yükseklikleri kutuya göre kontrol edildi mi (3D)?

## 4. Panelleme

Küçük kartlar tek tek değil, bir **panel** içinde üretilir ve dizilir; sonra ayrılır.

| Yöntem | Nasıl | Artısı | Dikkat |
|---|---|---|---|
| **V-kesim (V-score)** | Panelin iki yüzüne V şeklinde çentik | Hızlı, temiz kenar | Yalnızca düz çizgiler; parçalar çizgiden uzak |
| **Tırnaklı freze (mouse bite)** | Kartlar ince delikli köprülerle bağlı | Her şekil olur | Kopma yerinde küçük çıkıntılar kalır |

- **Kenar rayları (rails):** Dizgi makinesinin kartı tutacağı boş şeritler; üzerinde fiducial ve kılavuz delikleri bulunur.
- **Ayırma gerilmesi:** Panel kırılırken kart eğilir. MLCC ve konnektörleri kırma çizgisinden uzak tut (tipik ≥ 1 mm, büyük MLCC için daha fazla).
- Paneli kimin tasarlayacağını (sen mi, üretici mi) baştan netleştir; dizgi firmasının panel ölçü sınırlarını sor.

## 5. Fiducial'lar

Fiducial, dizgi makinesinin kamerasının kartın tam konumunu ve dönüklüğünü bulduğu işaretlerdir.

- **Global fiducial:** Kartta (ve panel raylarında) **en az 3 tane**, köşelere yakın ve **simetrik olmayan** konumda. Simetrik olursa kartın ters dönmüş olduğu anlaşılamaz.
- **Yerel fiducial:** İnce aralıklı bir IC'nin iki çapraz köşesinde (ihtiyaç varsa).
- **Ölçü:** Ø 1 mm bakır nokta, çevresinde Ø 2–3 mm maskesiz ve bakırsız boş alan. Üstünde silkscreen olmaz.

## 6. DFT: test için tasarım

**Test türleri:**

| Test | Nasıl | Ne bulur |
|---|---|---|
| **ICT (iğneli fikstür)** | Kart, test noktalarına değen iğneler üzerine basılır | Kısa devre, açık devre, yanlış değer |
| **Uçan prob** | Hareketli problar test noktalarına sırayla değer | Aynısı; fikstür gerekmez, yavaştır |
| **Fonksiyonel test** | Kart çalıştırılır, girişlere sinyal verilir, çıkışlar ölçülür | Kartın işini yapıp yapmadığı |
| **Kalibrasyon** | Bilinen bir girişle (ör. kalibrasyon gazı) katsayılar hesaplanıp kaydedilir | Ölçüm doğruluğu |

**Test noktaları:**
- **Hangi netler?** Tüm güç rayları, birkaç GND noktası, reset, saat (MCO çıkışı), haberleşme hatları, analog ön ucun her katının çıkışı, referans gerilimi, ısıtıcı veya yük akımı ölçüm noktaları.
- **Ölçü:** Ø ≥ 1 mm (mümkünse), aralarında ≥ 2,54 mm.
- **Tek yüzden erişim:** Tüm test noktaları genelde alt yüzde, fikstür iğneleri tek taraftan gelsin.
- Parça altında, maske veya silkscreen altında olmasın; yüksek parçalara çok yakın olmasın.

**Programlama ve kalibrasyon erişimi:**
- MCU'yu programlamak için SWD hatlarını (SWDIO, SWCLK, NRST, GND, VTref) **yaylı iğnelerle** (pogo pin) temas edilebilecek pedlere çıkar; konnektör maliyeti olmaz.
- Kalibrasyon, kutu kapalıyken yapılacaksa haberleşme arayüzü (UART, RS-485) **kutunun dışından erişilebilir** olmalı.
- Her kartın **seri numarası** ve kalibrasyon verileri kalıcı bellekte (Flash/EEPROM) saklanır; hangi kartın hangi testten geçtiği izlenebilir olsun.

**Firmware'de kendi kendini test (self-test):**
- Rayların gerilimini ADC ile ölçmek, sensör ısıtıcısının akımını izlemek, sensörün açık veya kısa devre olup olmadığını kontrol etmek.
- Hem üretim testini hızlandırır hem de sahada arızanın **kendini göstermesini** sağlar (fail-safe).

## 7. Üretim paketi

| Dosya | İçerik | Dikkat |
|---|---|---|
| **Gerber** (RS-274X / X2) | Her bakır katman, maske, silkscreen, pasta, kart sınırı | Kart sınırı ayrı bir katman olarak |
| **Delik dosyası** (Excellon) | Delik konumları ve çapları | Kaplamalı ve kaplamasız ayrı |
| **Üretim notu / çizimi** | Malzeme, kalınlık, bakır, kaplama, maske/silk rengi, Tg, IPC sınıfı, panel | PDF olarak |
| **BOM** | Referanslar, adet, üretici, MPN, DNP | [Şematik dersi, bölüm 11](../sematik-cizim-ve-dokumantasyon/ozet.md#11-bom-hijyeni) |
| **Pick & place** (centroid) | Her parçanın X, Y, dönüş açısı, yüz | Dönüş açısı tanımı dizgi firmasıyla aynı mı? |
| **Montaj çizimi** | Üst/alt yüz, polarite, DNP'ler işaretli | PDF |
| **Firmware** | Hex dosyası ve sürüm numarası | Kartın revizyonuyla eşleşmeli |
| **Test talimatı** | Test noktaları, beklenen değerler, sınırlar | Şematikteki notlardan |

- **Tek dosya alternatifleri:** ODB++ ve IPC-2581, tüm bilgiyi tek bir akıllı pakette taşır; dizgi firması destekliyorsa hata riskini azaltır.
- **Pick & place tuzağı:** EDA aracının "0°" kabulü ile dizgi firmasınınki farklı olabilir; ilk kartlarda bazı parçalar 90° veya 180° dönük takılır. İlk ürünü (first article) mutlaka kontrol et.
- **Revizyon:** Bütün dosyalar **aynı revizyon** adıyla klasörlenir (ör. `KART-ADI_RevB_2026-10-16.zip`). Farklı revizyonların dosyalarının karışması yanlış kart üretiminin en yaygın nedenidir.

## 8. IPC sınıfları

**IPC-A-610**, monte edilmiş kartın kabul kriterlerini (lehim nasıl görünmeli, hangi kusur kabul edilir) tanımlar.

| Sınıf | Kapsam |
|---|---|
| Class 1 | Genel tüketici ürünleri |
| Class 2 | Kesintisiz çalışması beklenen, adanmış hizmet ürünleri (endüstriyel cihazların çoğu) |
| Class 3 | Yüksek güvenilirlik: arızanın kabul edilmediği ürünler |

Hangi sınıfta üretileceğini üretim notuna yaz; sınıf yükseldikçe fiyat da yükselir.

## 9. Prototip ve bring-up

1. **Kartı gözle incele:** Ters takılı parça, köprü, eksik parça var mı?
2. **Güç vermeden önce** raylar ile GND arasındaki direnci ölç (kısa devre kontrolü).
3. **Akım sınırlı** güç kaynağıyla, düşük akım sınırında enerji ver; akımı izle.
4. Rayları tek tek ölç; beklenen değerlerle (şematikteki notlar) karşılaştır.
5. MCU'yu programla; sonra blok blok test et (haberleşme, analog ön uç, çıkışlar). Ayrıntı: [MCU dersi, bölüm 8 (bring-up)](../../Komponentler/05-mikrodenetleyici-donanimi/ozet.md).
6. Bulduğun her sorunu şematiğin bir kopyasına **kırmızı kalemle** işle; düzeltmeleri bir sonraki revizyona taşı.
7. Dersleri [hatalar-dersler.md](../../Sematik-Tasarim/hatalar-dersler.md) dosyasına yaz.

## 10. Üretim testine hazırlık

- Test talimatını **tasarım sırasında** yaz: hangi test noktasında hangi değer, hangi sınırlarla.
- Her test için **geçti/kaldı** kriteri ve kaydı: seri numarası, tarih, ölçülen değerler.
- Kalibrasyon verilerinin kaydı ve yedeği; kart değişirse ne olacağı (servis süreci).
- Test fikstürü gerekiyorsa kartın **montaj delikleri** fikstüre hizalama için kullanılabilir; fikstürün baskı yapacağı yerleri parçasız bırak.

## 11. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| Üreticinin en küçük değerlerinde tasarlamak | Düşük verim, yüksek fiyat | Bir kademe üstü |
| QFN termal pedine tam pasta | Parça yüzer, pinler lehimlenmez | Pencereli pasta (%50–80) |
| MLCC kırma çizgisinin dibinde | Panel ayrılırken çatlar | Uzak tut, paralel yerleştir |
| Simetrik fiducial | Ters dönmüş kart anlaşılmaz | En az 3, asimetrik |
| Test noktası yok veya parça altında | Üretimde ölçülemez | Tek yüzde, Ø ≥ 1 mm |
| Programlama konnektörü kutu kapanınca erişilemez | Sahada güncelleme ve kalibrasyon zor | Pogo pedleri ve dış arayüz |
| Pick & place dönüş açısını kontrol etmemek | Parçalar dönük takılır | İlk ürün kontrolü |
| Farklı revizyon dosyalarını karıştırmak | Yanlış kart üretilir | Tek klasör, tek revizyon adı |
| Self-test yok | Arızalı kart sahaya gider | Ray, ısıtıcı, sensör kontrolü |
| Polariteli parçalar farklı yönlerde | Ters takma, yavaş muayene | Yön birliği |

## 12. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **DFM / DFA / DFT** | Üretim / montaj / test için tasarım |
| **Stencil (şablon)** | Lehim pastasını pedlere basan delikli metal levha |
| **Reflow** | Pastanın fırında eritilerek lehim yapılması |
| **AOI** | Otomatik optik muayene |
| **Fiducial** | Dizgi makinesinin konum referans işareti |
| **Panel** | Birden fazla kartın birlikte üretildiği levha |
| **V-kesim / mouse bite** | Panelden ayırma yöntemleri |
| **ENIG / HASL** | Altın kaplama / sıcak hava lehim kaplama yüzey işlemleri |
| **ICT** | İğneli fikstürle devre içi test |
| **Pogo pin** | Yaylı test iğnesi |
| **Pick & place (centroid)** | Parçaların konum ve dönüş dosyası |
| **First article** | Seri üretimden önce detaylı kontrol edilen ilk ürün |
| **IPC-A-610** | Monte edilmiş kart kabul kriterleri standardı |
| **Tg** | Kart malzemesinin camsı geçiş sıcaklığı |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.4, bölüm 9 ve 13):

> MLCC'lerin kart kenarı ve kırma çizgisinden uzak olması maddesi zaten bölüm 10'da.

- [x] Tasarım kuralları üreticinin kabiliyetinin bir kademe üstünde; kaplama türü parçalara uygun
- [x] Fiducial'lar: en az 3, asimetrik, çevresi boş
- [x] QFN termal pedi pasta penceresi %50–80
- [x] Test noktaları tek yüzde, Ø ≥ 1 mm; programlama pogo pedleri; kalibrasyon arayüzü kutu kapalıyken erişilebilir
- [x] Üretim paketi tek revizyon adıyla; pick & place dönüş açısı dizgi firmasıyla teyit edildi
- [x] Firmware self-test: raylar, ısıtıcı/yük akımı, sensör açık/kısa devre

## Kontrol soruları

→ [quiz.md](quiz.md) · 10 soru, 1'i hesap
