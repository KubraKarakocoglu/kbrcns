# PCB yerleşim ve iz çizimi

- **Oluşturma:** 2026-10-16
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Bağlantılı:** [EMC için kart tasarımı](../../EMC/02-emc-icin-kart-tasarimi/ozet.md) (toprak düzlemi, katman dizilimi, bölgeleme) · [Güç ve decoupling, bölüm 8](../guc-ve-decoupling/ozet.md#8-pcb-yerleşimi-en-kritik-bölüm) · [Mikrodenetleyici, PCB](../../Komponentler/05-mikrodenetleyici-donanimi/ozet.md#9-pcb--layout) · [Üretilebilirlik ve test](../uretilebilirlik-ve-test/ozet.md) · Kontrol listesi bölüm 13

> Sayısal değerler **tipik başlangıç noktalarıdır**. Üretici kabiliyetleri, ürünün güvenlik standardı ve (gaz dedektörlerinde) Ex standardı her zaman önce gelir.
>
> **Okuma planı:** 1. oturum: bölüm 1–4 (akış, katman, yerleşim, toprak) · 2. oturum: 5–9 (iz, mesafe, via, döküm, ısı) · 3. oturum: 10–15.

---

## ⚡ Hızlı tekrar

1. Sıra: **mekanik → yerleşim → kritik izler → diğer izler → bakır döküm → DRC → review.** Yerleşim doğruysa çizim kolaylaşır; yerleşim yanlışsa hiçbir çizim kurtaramaz.
2. Yerleşim önceliği: **konnektörler ve mekanik parçalar → güç katı → MCU + decoupling + kristal → analog ön uç → geri kalanı.**
3. Kartı **bölgelere** ayır: gürültülü (güç, röle, buzzer, dijital) ve sessiz (analog). Gürültülü akımlar sessiz bölgenin içinden geçmesin.
4. **Akım geri döner.** Her hızlı izin altında kesintisiz GND düzlemi; GND'yi yarıklarla bölme. Analog ve dijitali bakırı keserek değil, **yerleşimle** ayır.
5. İz genişliği akıma göre: 1 oz dış katmanda kabaca **1 A ≈ 0,3 mm** (10 °C artış). Güç izlerini hesapla; gerilim düşümünü de unutma.
6. Gerilim farkı olan iletkenler arasında **mesafe**: clearance (havadan) ve creepage (yüzeyden). Şebeke veya Ex varsa değerler standarttan gelir.
7. Via küçük bir direnç ve **~1 nH**'lik bir bobindir: güç ve GND'de birden fazla; decoupling via'sı pad'e bitişik.
8. Bitirmeden: **DRC sıfır hata**, 1:1 çıktı, kontrol listesi, ikinci göz, Gerber görüntüleyicide son bakış.

## 🧮 Tablo kartı: iz genişliği ve akım (IPC-2221, dış katman)

| Akım | 1 oz, +10 °C | 1 oz, +20 °C | 2 oz, +10 °C | 1 oz **iç** katman, +10 °C |
|---|---|---|---|---|
| 0,5 A | 0,12 mm | 0,08 mm | 0,06 mm | 0,30 mm |
| 1 A | **0,30 mm** | 0,20 mm | 0,15 mm | 0,78 mm |
| 2 A | 0,78 mm | 0,51 mm | 0,39 mm | 2,03 mm |
| 3 A | 1,37 mm | 0,90 mm | 0,68 mm | 3,56 mm |
| 5 A | 2,77 mm | 1,82 mm | 1,38 mm | 7,19 mm |

- 1 oz = 35 µm bakır. Tablo, IPC-2221 formülüyle hesaplandı: `I = k × ΔT^0,44 × A^0,725` (A: mil², dış k = 0,048, iç k = 0,024).
- IPC-2221 iç katmanlar için **çok tutucudur**; daha doğru sonuç için IPC-2152 tabanlı bir hesaplayıcı (ör. Saturn PCB Toolkit) kullan.
- Üreticinin en küçük iz genişliği (tipik 0,1–0,15 mm) her zaman alt sınırdır.

| Diğer | Değer |
|---|---|
| 1 oz bakırın kare direnci | ≈ **0,49 mΩ/kare** (25 °C) |
| İz direnci | `R = 0,49 mΩ × (uzunluk / genişlik)` → 0,3 mm × 50 mm ≈ **82 mΩ** |
| Via endüktansı (1,6 mm kart) | ≈ **1 nH** |
| Bakırın sıcaklık katsayısı | ≈ **+%0,39 / °C** |

---

## 1. İş akışı

1. **Mekanik:** Kart sınırı, montaj delikleri, kutunun iç ölçüleri, konnektör, buton, LED, ekran ve sensör konumları **kutu çizimine göre** sabitlenir ve kilitlenir.
2. **Katman sayısı ve dizilim** seçilir (bölüm 2).
3. **Tasarım kuralları** üreticinin kabiliyetine göre girilir: en küçük iz/boşluk, via boyutu, bakır–kart kenarı mesafesi. Güç, yüksek gerilim ve analog için **net sınıfları** tanımlanır (ör. `POWER` en az 0,8 mm, `HV` en az 2,5 mm boşluk).
4. **Yerleşim** (bölüm 3). İşin en uzun süren ve en önemli kısmı.
5. **Kritik izler:** güç döngüleri, decoupling, kristal, analog, hızlı saatler, fark çiftleri.
6. **Diğer izler.**
7. **Bakır döküm** ve dikiş via'ları.
8. **Silkscreen** düzenlemesi.
9. **DRC** ve son kontroller (bölüm 12).
10. **Review** ve üretim dosyaları ([Üretilebilirlik ve test](../uretilebilirlik-ve-test/ozet.md)).

## 2. Katman sayısı

| | 2 katman | 4 katman |
|---|---|---|
| Maliyet | Düşük | Daha yüksek (ama çoğu zaman sanıldığı kadar değil) |
| GND düzlemi | Alt katmanda, izlerle bölünmüş | İç katmanda, **kesintisiz** |
| EMC | Zor, dikkat ister | Çok daha kolay |
| Ne zaman | Basit, yavaş, az parçalı kartlar | MCU + anahtarlamalı regülatör + hassas analog bir aradaysa |

**4 katmanda tipik dizilim:** Üst sinyal / **GND** / güç / alt sinyal. Her sinyal katmanı bir referans düzleme bitişik ([EMC 02, bölüm 2](../../EMC/02-emc-icin-kart-tasarimi/ozet.md#2-katman-dizilimi-stackup)).

**2 katmanda kurallar:**
- Alt katmanı mümkün olduğunca **kesintisiz GND** bırak; izleri üstte çiz.
- Alt katmanda iz gerekiyorsa **kısa** tut ve GND'yi boydan boya kesecek uzun izlerden kaçın.
- GND dökümündeki adaları via'larla birbirine bağla.

## 3. Yerleşim

Kartı bir **şehir planı** gibi düşün: sanayi bölgesi (güç, röle, buzzer) ile konut bölgesi (analog ölçüm) ayrı yerlerde olur; ağır kamyonlar (yüksek akımlar) konutların içinden geçmez; ana yollar (güç izleri) geniştir.

```
┌──────────────────────────────────────────────────────┐
│ J1 GÜÇ → koruma → BUCK + bobin   │  röle   buzzer    │ ← gürültülü bölge
│                                  │  (dış kablolar)   │
│- - - - - - - - - - - - - - - - - - - - - - - - - - - │
│   MCU + decoupling + kristal     │  RS-485 + TVS → J3│
│- - - - - - - - - - - - - - - - - - - - - - - - - - - │
│ J2 SENSÖR → koruma → analog ön uç → ADC pini         │ ← sessiz bölge
└──────────────────────────────────────────────────────┘
   GND düzlemi tüm kartın altında kesintisiz (bölgeler yerleşimle ayrılır)
```

**Sıra ve kurallar:**
1. **Konnektörler ve mekanik parçalar** önce: konumları kutu belirler. Mümkünse konnektörleri **tek kenarda** topla ([EMC 02, bölüm 3](../../EMC/02-emc-icin-kart-tasarimi/ozet.md#3-yerleşim-bölgeleme)).
2. **Koruma elemanları** konnektörün hemen arkasına: TVS, sigorta, filtre.
3. **Güç katı:** giriş akışı konnektörden içeri doğru; buck'ın sıcak döngüsü küçük; bobin sensörden ve kristalden uzak.
4. **MCU:** önce **decoupling kapasitörleri** pinlerin dibine, sonra **kristal** MCU'nun hemen yanına; kristalin altından başka sinyal geçmez.
5. **Analog ön uç:** sensör konnektörü ile ADC pini arasında, kısa ve düz bir hat üzerinde; ısı kaynaklarından uzak.
6. **Isı kaynakları** (LDO, güç direnci, MOSFET, ısıtıcılı sensör) elektrolitik kapasitörden, kristalden, referanstan ve analog dirençlerden uzak.
7. **Yönler:** Polariteli parçalar (diyot, LED, elektrolitik) mümkünse **aynı yöne** baksın; montaj ve gözle kontrol kolaylaşır.
8. **Erişim:** Test noktaları, programlama konnektörü ve ayar elemanları kutu içinde erişilebilir yerde; tamir (rework) için parçalar arasında yer.

## 4. Toprak ve dönüş akımı (pratik özet)

**Temel gerçek:** Akım bir yere giderse **aynı miktarda geri döner**. Dönüş yolu, DC'de en düşük dirençli yoldur; yüksek frekansta ise gidiş izinin **hemen altındaki** yoldur (döngü alanı en küçük olan yol). Ayrıntı: [EMC 01, bölüm 7](../../EMC/01-emc-temelleri/ozet.md#7-dönüş-akımı-akım-nereden-geri-döner) ve [EMC 02, bölüm 1](../../EMC/02-emc-icin-kart-tasarimi/ozet.md#1-toprak-düzlemi-ve-dönüş-yolu).

**Kurallar:**
- **Tek, kesintisiz GND düzlemi** çoğu kart için en iyi çözümdür.
- **AGND/DGND'yi bakırı keserek ayırma.** Ayrı düzlemlerin arasından geçen her iz büyük bir döngü ve anten oluşturur. Ayırmayı **yerleşimle** yap: analog parçalar ve izleri bir bölgede, dijital diğerinde; dönüş akımları kendi bölgelerinde kalır.
- **Büyük dönüş akımları** (ısıtıcı, röle, buzzer, buck girişi) güç girişine **kısa** yoldan dönmeli; yolları analog ölçüm bölgesinin altından geçmemeli. Örnek: ısıtıcılı bir sensörde ısıtıcının yüzlerce mA'lik dönüş akımı, sensör sinyalinin referans aldığı GND'nin üstünden geçerse ölçüme milivoltlar ekler (`V = I × R_bakır`).
- **2 katmanlı kartta** yüksek akım dönüşleri için ayrı geniş izler çizip tek bir noktada (güç girişinde) birleştirmek (yıldız nokta) gerekebilir.
- **Gerçekten ayrı toprak gerektiren yerler:** galvanik yalıtım bariyeri (izoleli RS-485, trafo, optokuplör) ve şasi/koruma toprağı. Bu durumlarda bariyerin altından bakır geçmez.
- **Şasi toprağı:** Metal kutu veya kablo ekranı konnektör bölgesinde şasiye bağlanır; devre GND'si ile bağlantısı tasarım kararıdır (doğrudan, kapasitörle veya hiç). Kararı şematikte not et.

## 5. İz genişliği, akım ve gerilim düşümü

İz bir **su borusu** gibidir: dar boru ısınır (direnç → ısı) ve basınç kaybettirir (gerilim düşümü).

- **Isınma:** Tablo kartındaki değerler izin belirli bir sıcaklık artışında (10 °C veya 20 °C) taşıyabileceği akımdır.
- **Gerilim düşümü:** Isınma sorun olmasa bile uzun ince iz gerilim kaybettirir.
  - **Örnek:** 0,3 mm genişliğinde, 50 mm uzunluğunda 1 oz iz: `50 / 0,3 ≈ 167 kare × 0,49 mΩ ≈ 82 mΩ`. 1 A'de **82 mV**, 150 mA'de 12 mV düşüm.
  - Aynı iz 1 mm genişlikte olsaydı 25 mΩ olurdu.
- **Pratik değerler:**
  - Sinyal izleri: 0,15–0,25 mm.
  - Güç izleri: tablodan hesapla, sonra mümkünse bir kademe genişlet.
  - Büyük akımlarda iz yerine **bakır alan (polygon)** kullan.
- **Darboğaz yapma:** Geniş bir güç izi, bir pad'e girerken ya da via'dan geçerken incelirse en zayıf nokta orasıdır. Pad girişleri ve via sayısı da akımı taşıyabilmeli.
- **Ölçme hatlarını** (şant direnci, Kelvin) akım yolundan ayır: ölçüm izlerini şantın pad'lerinin iç kenarından al ([Direnç dersi](../../Komponentler/01-direnc/ozet.md#54-akım-ölçme-şantı)).

## 6. Mesafeler: clearance ve creepage

İki iletken arasında gerilim varsa aralarında yeterli mesafe olmalı; yoksa ark atlar veya yüzeyde kaçak akım oluşur.

- **Clearance:** İki iletken arasındaki **havadan** en kısa mesafe. Kuşun uçarak gittiği yol.
- **Creepage:** İki iletken arasındaki **yüzey boyunca** en kısa mesafe. Karıncanın kartın üstünde yürüyerek gittiği yol. Kir ve nem bu yolda kaçak akım oluşturur.

**Düşük gerilimli kartlarda (≤ 30 V):** Üreticinin en küçük boşluğu (0,1–0,15 mm) elektriksel olarak yeterlidir. 24 V'luk giriş hatlarında biraz daha geniş boşluk (ör. 0,3 mm) bırakmak iyi bir alışkanlıktır.

**Örnek işlevsel boşluklar** (IPC-2221B, dış katman, kaplamasız, deniz seviyesi):

| Gerilim (DC veya AC tepe) | En küçük boşluk |
|---|---|
| 0–30 V | 0,1 mm |
| 31–150 V | 0,6 mm |
| 151–300 V | 1,25 mm |
| 301–500 V | 2,5 mm |

> **Dikkat:** Bu tablo **işlevsel** boşluktur, **güvenlik** boşluğu değildir. Şebeke gerilimi (230 V) ile kullanıcının dokunabileceği düşük gerilim arasındaki yalıtım için değerler ürünün **güvenlik standardından** gelir (ör. IEC 62368-1, IEC 61010-1). Çalışma gerilimi, kirlilik derecesi ve malzeme grubuna göre değişir. Güçlendirilmiş yalıtımda creepage tipik olarak **birkaç mm** (5–8 mm mertebesi) olabilir.

**Şebeke veya röle kontağı olan kartlarda:**
- Yüksek gerilim bölgesini kartta **çizgiyle işaretle** ve bu bölgeye düşük gerilim izi sokma.
- Creepage yetmiyorsa iletkenler arasına **yarık (slot)** aç: karıncanın yolu uzar.
- Röle, optokuplör ve trafolar yalıtım bariyerinin **üzerine oturur**; altlarından iz geçmez.

**Gaz dedektörlerinde Ex (patlayıcı ortam) onayı varsa:** Kendinden güvenli (Ex i) tasarımlarda iletkenler arası mesafeler, bileşen değerleri ve kapasitans/endüktans sınırları **IEC 60079-11**'den gelir ve sıradan kurallardan daha katıdır. Kartı çizmeden önce bu gereksinimleri öğren.

## 7. Via'lar

| Konu | Pratik |
|---|---|
| Standart boyut | Delik 0,3 mm / ped 0,6 mm civarı yaygın ve ucuzdur; daha küçüğü maliyeti artırır |
| Akım | Bir standart via kabaca **1 A mertebesinde** taşır; güç yolunda birden fazla via kullan ve hesaplayıcıyla doğrula |
| Endüktans | ~1 nH; decoupling'de **pad'e bitişik** via, mümkünse iki tane |
| Termal via | QFN gibi alt pedli parçaların altında **via dizisi** ısıyı alt katmana taşır |
| Lehim kaçması | Ped içindeki açık via lehimi emer; **dolgulu ve kapatılmış (filled & capped)** via gerekir ya da via pede konmaz |
| Dikiş (stitching) via'ları | GND dökümlerini katmanlar arası bağlar; kart kenarı boyunca ve fark sinyali katman değiştirdiğinde |

- Küçük pasiflerin (0402, 0603) pedine açık via koyma: lehim kaçar, parça **mezar taşı** gibi dikilebilir (tombstoning).
- Hızlı bir sinyal katman değiştiriyorsa yanına bir **GND via'sı** koy; dönüş akımının da katman değiştirmesine yol aç.

## 8. Bakır döküm

- Boş alanları **GND'ye bağlı** bakırla doldur; hem dönüş yolu hem ekran olur.
- **Ada bırakma:** Hiçbir yere bağlı olmayan bakır parçası (floating copper) bir antendir. Ya via ile GND'ye bağla ya da sil.
- **Termal rölyef (thermal relief):** Pad'i bakıra dört ince köprüyle bağlar; havya ve reflow'da ısının dağılmasını yavaşlatır, lehimlemeyi kolaylaştırır. Yüksek akım veya ısı aktarımı gereken pad'lerde doğrudan bağlantı kullanılır; ama o pad'in lehimlenmesi zorlaşır.
- İki katmanda da döküm varsa aralarını **dikiş via'larıyla** bağla.
- Bakırı iki yüzde **dengeli** dağıtmak, kartın fırında eğilmesini (warpage) azaltır.
- Döküm ile kart kenarı arasında mesafe bırak (bölüm 12).

## 9. Isı

- **Bakır alan = soğutucu.** LDO, MOSFET ve güç dirençlerinin pad'lerini mümkün olduğunca geniş bakıra bağla; alt katmana **termal via'larla** taşı.
- θJA değerleri datasheet'te genelde belirli bir test kartı için verilir; senin kartın bakır alanı küçükse gerçek değer daha kötüdür.
- **Isıdan etkilenen parçalar:** elektrolitik kapasitör (her 10 °C ömrü yarıya indirir), kristal, gerilim referansı, analog dirençler, sensörler. Isı kaynaklarından uzak yerleştir.
- Prototipte termal kamera veya termokupl ile **ölç**; hesapla karşılaştır.

## 10. Özel durumlar

| Durum | Kural | Ayrıntı |
|---|---|---|
| Kristal | MCU'nun dibinde, kısa iz, altında başka sinyal yok, çevresi GND | [MCU dersi](../../Komponentler/05-mikrodenetleyici-donanimi/ozet.md#9-pcb--layout) |
| Anahtarlamalı regülatör | Sıcak döngü en küçük, SW düğümü küçük, FB izi SW'den uzak | [Bobin dersi](../../Komponentler/03-bobin-induktor/ozet.md), [EMC 02](../../EMC/02-emc-icin-kart-tasarimi/ozet.md#5-anahtarlamalı-regülatörler) |
| Decoupling | Pin → kapasitör → via döngüsü en küçük | [Güç ve decoupling](../guc-ve-decoupling/ozet.md#8-pcb-yerleşimi-en-kritik-bölüm) |
| Yüksek empedanslı analog | Kısa iz, gerekirse koruma halkası, temiz kart | [Op-amp dersi](../op-amp-ve-sensor-on-ucu/ozet.md#13-pcb--layout) |
| Fark çiftleri (RS-485, USB) | Yan yana, eşit uzunluk, aynı katman | [Haberleşme dersi](../haberlesme-arayuzleri/ozet.md#10-pcb--layout) |
| Konnektör ve ESD | TVS konnektörün dibinde, GND bağlantısı kısa | [EMC 02, bölüm 7](../../EMC/02-emc-icin-kart-tasarimi/ozet.md#7-esd-koruması) |
| Şant ölçümü | Kelvin bağlantı: ölçüm izleri pad'in iç kenarından | [Direnç dersi](../../Komponentler/01-direnc/ozet.md#54-akım-ölçme-şantı) |

## 11. Silkscreen

- **Referans tanımlayıcılar** okunur boyutta, mümkünse aynı yönde; **pad ve via üstüne gelmez** (üretici zaten keser, okunmaz hâle gelir).
- **Polarite ve pin 1** işaretleri: diyot, LED, elektrolitik, IC, konnektör. Parça takıldıktan sonra da görünür olsun.
- **Konnektör pinlerinin işlevi:** `+24V GND A B`, `SENS+ SENS−`. Sahada kablolayan kişi bunu okur.
- **Kart adı, revizyon, tarih.** Ayrıca seri numarası veya etiket için **boş bir alan**.
- Yüksek gerilim bölgesinde **uyarı işareti**.

## 12. DRC ve son kontroller

1. **DRC sıfır hata:** Üreticinin kurallarıyla (iz/boşluk, via, delik, maske). Bastırılan her uyarının gerekçesi olsun.
2. **Bağlanmamış net sayısı = 0** (ratsnest kalmamalı).
3. **Bakır – kart kenarı mesafesi:** Tipik ≥ 0,3–0,5 mm; V-kesimli (V-score) panellerde daha fazla.
4. **3D kontrol:** Parça yükseklikleri kutuya sığıyor mu, konnektörler kutu deliğine denk geliyor mu?
5. **1:1 çıktı:** Mekanik parçaları kâğıdın üstüne koy.
6. **Katman katman bakış:** Her katmanı tek başına aç; GND düzleminde istemediğin yarık var mı?
7. **Gerber görüntüleyici:** Üreticiye giden dosyaları ayrı bir görüntüleyicide aç. Üretici senin EDA ekranını değil, **bu dosyaları** görür.
8. **Kontrol listesi** ve **ikinci göz.**

## 13. EMC açısından

- Layout, EMC'nin **en ucuz** olduğu yerdir; kart üretildikten sonra her çözüm daha pahalıdır.
- Özet kurallar: kesintisiz dönüş yolu, küçük döngüler, gürültülü ve sessiz bölgelerin ayrılması, konnektörde filtre ve koruma, hızlı sinyallerin kısa ve düzlem üstünde gitmesi.
- Ayrıntılar: [EMC için kart tasarımı](../../EMC/02-emc-icin-kart-tasarimi/ozet.md).

## 14. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| Mekaniği sona bırakmak | Konnektör kutuya denk gelmez, baştan yerleşim | Önce mekanik, sonra kilitle |
| GND düzlemini AGND/DGND diye kesmek | Yarık üstü izler anten olur | Tek düzlem, yerleşimle ayırma |
| Güç izini sinyal genişliğinde çizmek | Isınma ve gerilim düşümü | Tablodan hesapla |
| Yüksek akım dönüşü analog bölgenin altından | Ölçüme mV'lar eklenir | Dönüşü kısa yoldan güç girişine |
| Şebeke ile düşük gerilim arasında yetersiz mesafe | Güvenlik testinden kalır, tehlike | Güvenlik standardının değerleri, slot |
| Küçük pasifin pedine açık via | Lehim kaçar, mezar taşı | Via'yı pedin dışına veya dolgulu via |
| Bağlanmamış bakır ada | Anten | GND'ye bağla veya sil |
| Kristalin altından sinyal geçirmek | Saat bozulur, EMI | Altı boş, çevresi GND |
| Silkscreen pad üstünde | Okunmaz, lehimi bozabilir | Pad'lerden uzak |
| Gerber'i görüntüleyicide kontrol etmemek | EDA'da görünmeyen hata karta gider | Her siparişten önce |

## 15. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Yerleşim (placement)** | Parçaların karttaki konumlarının belirlenmesi |
| **İz çizimi (routing)** | Bağlantıların bakır izlerle yapılması |
| **Katman dizilimi (stackup)** | Bakır ve yalıtkan katmanların sırası ve kalınlığı |
| **oz (ons)** | Bakır kalınlığı: 1 oz ≈ 35 µm |
| **Net sınıfı** | Aynı kuralları (genişlik, boşluk) paylaşan net grubu |
| **Clearance** | İki iletken arasındaki havadan en kısa mesafe |
| **Creepage** | İki iletken arasındaki yüzey boyunca en kısa mesafe |
| **Via** | Katmanlar arası bağlantı deliği |
| **Termal via** | Isıyı alt katmana taşıyan via |
| **Termal rölyef** | Pad'i bakıra ince köprülerle bağlayan, lehimlemeyi kolaylaştıran yapı |
| **Dikiş via'sı** | Katmanlardaki GND dökümlerini birbirine bağlayan via'lar |
| **Tombstoning** | Küçük pasifin reflow'da bir ucunun kalkıp dikilmesi |
| **DRC** | Design Rule Check; layout kural denetimi |
| **Gerber** | Üreticiye giden katman çizim dosyaları |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.4, yeni bölüm 13 "PCB layout ve üretim"):

- [x] Mekanik (kutu, konnektör, buton, montaj delikleri) yerleşimden önce sabitlendi
- [x] Güç izleri akım ve gerilim düşümüne göre hesaplandı; net sınıfları tanımlı
- [x] GND düzlemi kesintisiz; yüksek akım dönüşleri analog bölgenin altından geçmiyor
- [x] Yüksek gerilim/şebeke ve Ex gereksinimleri için clearance ve creepage standarttan alındı
- [x] Küçük pasiflerin pedinde açık via yok; alt pedli parçalarda termal via dizisi
- [x] Bağlanmamış bakır ada yok; DRC sıfır hata; Gerber görüntüleyicide kontrol edildi

## Kontrol soruları

→ [quiz.md](quiz.md) · 10 soru, 4'ü hesap
