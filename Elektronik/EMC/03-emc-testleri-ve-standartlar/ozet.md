# 03 · EMC testleri ve standartlar

- **Oluşturma:** 2026-10-12
- **İlk kaynak:** [BSI – EN 50270 (gaz algılama cihazları için EMC)](https://knowledge.bsigroup.com/products/electromagnetic-compatibility-electrical-apparatus-for-the-detection-and-measurement-of-combustible-gases-toxic-gases-or-oxygen)
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Önceki dersler:** [01 · Temeller](../01-emc-temelleri/ozet.md) · [02 · Kart tasarımı](../02-emc-icin-kart-tasarimi/ozet.md)

> ⚠️ Standartlar güncellenir. Test seviyeleri, frekans aralıkları ve performans kriterleri için **ürününe uygulanan standardın güncel sürümü** esastır. Bu ders yapıyı ve mantığı anlatır.

---

## ⚡ Hızlı tekrar

1. AB'de satış için **CE** işareti gerekir; EMC tarafında **2014/30/EU** direktifine uyulur ve uyumlaştırılmış standartlar kullanılır.
2. **Standart hiyerarşisi:** Ürün (aile) standardı varsa o uygulanır; yoksa **genel (generic)** standartlar (EN 61000-6-x) kullanılır.
3. Gaz algılama cihazları için EMC ürün standardı **EN 50270**'tir.
4. Bağışıklık testleri **IEC 61000-4-x** serisidir: ESD (-2), ışınımlı RF (-3), EFT (-4), surge (-5), iletimli RF (-6), manyetik alan (-8), gerilim çukurları (-11 AC, -29 DC).
5. Her bağışıklık testi bir **performans kriteriyle** değerlendirilir: **A** etkilenmez, **B** geçici bozulur ve kendiliğinden düzelir, **C** müdahale gerekir.
6. Emisyon iki türlü ölçülür: **iletimli** (tipik 150 kHz–30 MHz, LISN ile) ve **ışınımlı** (30 MHz ve üstü, anten ile).
7. Laboratuvara gitmeden önce **ön uyumluluk** (pre-compliance) ölçümleri yap: yakın alan probu, kablo akım probu, ESD tabancası.
8. Teste **test modu yazılımı** ve bir **izleme yöntemiyle** git: cihazın "geçti/kaldı" durumu dışarıdan görülebilmeli.

## 🧮 Tablo kartı: bağışıklık testleri

| Test | Standart | Neyi simüle eder? | Tipik seviyeler (seviye 1–4) |
|---|---|---|---|
| **ESD** | IEC 61000-4-2 | İnsan dokunuşuyla statik deşarj | Kontak: 2 / 4 / 6 / 8 kV · Hava: 2 / 4 / 8 / 15 kV |
| **Işınımlı RF** | IEC 61000-4-3 | Telsiz, telefon, verici alanları | 1 / 3 / 10 / 30 V/m; 80 MHz'den başlayarak (güncel sürümlerde 6 GHz'e kadar), %80 AM 1 kHz |
| **EFT / burst** | IEC 61000-4-4 | Röle, kontaktör gibi endüktif yüklerin anahtarlanması | Güç: 0,5 / 1 / 2 / 4 kV · Sinyal: 0,25 / 0,5 / 1 / 2 kV |
| **Surge** | IEC 61000-4-5 | Yıldırım, büyük yük anahtarlama | 0,5 / 1 / 2 / 4 kV; 1,2/50 µs gerilim, 8/20 µs akım dalgası |
| **İletimli RF** | IEC 61000-4-6 | Kablolara indüklenen RF | 1 / 3 / 10 V; 150 kHz–80 MHz |
| **Manyetik alan** | IEC 61000-4-8 | Trafo ve güç hatlarının 50/60 Hz alanı | 1 / 3 / 10 / 30 A/m |
| **Gerilim çukurları** | IEC 61000-4-11 (AC), -4-29 (DC) | Şebeke veya DC besleme kesintileri | Ürün standardına göre |

**Hangi testin hangi seviyede uygulanacağını ürün standardı belirler.**

---

## 1. Neden test?

- **Yasal:** CE işareti olmadan ürün AB pazarına giremez.
- **Güvenilirlik:** Sahada yaşanan açıklanamayan arızaların önemli bir kısmı EMC kaynaklıdır.
- **Güvenlik:** Bir gaz dedektörü telsiz yanında yanlış alarm veriyorsa güven kaybedilir; alarm vermiyorsa can güvenliği tehlikeye girer.

## 2. Yasal çerçeve

- **AB EMC Direktifi 2014/30/EU:** Üretici, ürünün temel gereksinimleri karşıladığını **uygunluk beyanı (DoC)** ile beyan eder. Bunun en yaygın yolu **uyumlaştırılmış (harmonised) standartlara** göre test etmek ve teknik dosya hazırlamaktır. Testler akredite bir laboratuvarda yaptırılabilir; bu çoğu durumda zorunlu değildir ama güçlü bir kanıttır.
- **Diğer pazarlar:** ABD'de FCC, diğer ülkelerde kendi düzenlemeleri.

### Gaz algılama cihazlarında ilgili standartlar

EMC yalnızca bir parçadır. Bir yanıcı gaz dedektöründe genellikle şu standart aileleri birlikte gündeme gelir:

| Konu | Standart (örnek) | Kapsam |
|---|---|---|
| **EMC** | EN 50270 | Gaz algılama cihazlarının emisyon ve bağışıklık gereksinimleri |
| **Performans** | EN / IEC 60079-29-1 | Yanıcı gaz dedektörlerinin ölçüm performansı |
| **Yazılım ve dijital teknoloji** | EN 50271 | Yazılım ve dijital teknoloji kullanan gaz algılama cihazlarının gereksinimleri ve testleri |
| **Patlayıcı ortam** | ATEX (2014/34/EU), IECEx | Cihazın patlamaya yol açmaması |

Hangi standartların, hangi sürümleriyle uygulanacağını ürünün hedef pazarına ve kullanım alanına göre belirle; güncel sürümleri doğrula.

## 3. Standart yapısı

| Tür | Örnek | Ne tanımlar? |
|---|---|---|
| **Temel (basic)** | IEC 61000-4-x, CISPR 16 | Test **yöntemlerini**: düzenek, dalga şekli, kalibrasyon |
| **Genel (generic)** | EN 61000-6-1 / -6-2 (bağışıklık: konut / endüstri) · EN 61000-6-3 / -6-4 (emisyon: konut / endüstri) | Ürün standardı olmayan cihazlar için hangi testlerin hangi seviyede yapılacağını |
| **Ürün (aile)** | EN 50270 (gaz algılama) | O ürün ailesine özel testleri, seviyeleri ve **performans kriterlerini** |

**Kural:** Ürün standardı varsa genel standarttan önce gelir. Ürün standardı da çoğu zaman test yöntemi için temel standartlara atıf yapar.

**Bir standart tablosunu okumak:** Testler genellikle **port** bazında listelenir:
- **Kasa portu** (enclosure): ESD, ışınımlı RF, manyetik alan
- **AC veya DC güç portu:** EFT, surge, iletimli RF, gerilim çukurları
- **Sinyal / kontrol portu:** EFT, surge, iletimli RF

Her satırda test, seviye ve performans kriteri yazar.

## 4. Bağışıklık testleri: ne olur, nerede kalınır, nasıl çözülür?

| Test | Tipik zayıf nokta | Tasarım önlemi |
|---|---|---|
| **ESD (-2)** | Korumasız konnektörler, reset hattı, plastik kasa aralıkları | TVS konnektörde, kısa GND bağlantısı, NRST kapasitörü, watchdog |
| **Işınımlı RF (-3)** | Analog ön kat: **op-amp girişleri RF'yi doğrultup DC kaymaya çevirir**; sensör okuması kayar | Op-amp girişlerinde RC filtre, kısa analog izler, ekranlama, yazılımla ortalama. 1 kHz AM'nin DC'ye katlanmaması için f_s seçimi: [Aliasing dersi, bölüm 12](../../Konular/aliasing-ve-anti-aliasing-filtresi/ozet.md#12-emc-açısından) |
| **EFT (-4)** | Güç girişi ve uzun kablolar; MCU kilitlenmesi | Giriş filtresi, CMC, TVS, iyi toprak, watchdog |
| **Surge (-5)** | Güç girişi ve dış ortama giden uzun hatlar; yüksek enerji | TVS / varistör / gaz deşarj tüpü, sigorta, yalıtım mesafeleri |
| **İletimli RF (-6)** | Kablolara bağlı analog ve haberleşme devreleri | Kablo girişinde filtre, CMC |
| **Manyetik alan (-8)** | Hall sensörleri, endüktif algılayıcılar, büyük döngüler | Mesafe, yönelim, küçük döngü |
| **Gerilim çukuru (-11 / -29)** | Besleme kesintisinde reset ve veri kaybı | Hold-up kapasitörü, BOR, güvenli yeniden başlama |

**Dalga şekilleri hakkında:**
- **EFT:** Nanosaniye kenarlı darbelerden oluşan "patlamalar"; tekrar frekansı 5 kHz veya 100 kHz. Enerjisi düşük ama frekans içeriği yüksektir; kuplaj ile her yere ulaşır.
- **Surge:** 1,2/50 µs gerilim ve 8/20 µs akım dalgası. Yavaş ama yüksek enerjilidir; koruma elemanının enerji kapasitesi önemlidir.

## 5. Performans kriterleri

| Kriter | Anlamı |
|---|---|
| **A** | Test sırasında ve sonrasında cihaz belirtilen sınırlar içinde normal çalışır |
| **B** | Test sırasında geçici bozulma olabilir; test sonrası cihaz **kendiliğinden** normale döner, kalıcı durum veya veri kaybı olmaz |
| **C** | Geçici işlev kaybı olabilir; normale dönmek için **kullanıcı müdahalesi** (reset, yeniden açma) gerekebilir |

Ürün standardı bu kriterleri ürüne özgü, ölçülebilir hale getirir. Bir gaz dedektöründe bu, örneğin **gaz okumasının belirli bir tolerans içinde kalması** ve **yanlış alarm veya arıza sinyali üretmemesi** gibi koşullar demektir. Kesin tanımları standardın güncel sürümünden doğrula.

## 6. Emisyon testleri

| | İletimli emisyon | Işınımlı emisyon |
|---|---|---|
| Tipik frekans | 150 kHz – 30 MHz | 30 MHz – 1 GHz (cihazın en yüksek iç frekansına göre daha yukarı) |
| Ölçüm | Güç portunda **LISN / AMN** ile | Yarı yansımasız oda veya açık alanda **anten** ile, 3 m veya 10 m mesafeden |
| Dedektör | Quasi-peak ve ortalama | Quasi-peak (üst bantlarda tepe ve ortalama) |
| Tipik suçlu | Anahtarlamalı regülatörün f_sw harmonikleri | Saat harmonikleri, kablolardaki ortak mod akımı |

**Class A ve Class B:** Class A endüstriyel, Class B konut ortamı içindir. Class B sınırları yaklaşık **10 dB daha sıkıdır**.

**Marj:** Sınırın hemen altında geçmek risklidir; üretim farklılıkları ve ölçüm belirsizliği yüzünden bir sonraki ölçüm kalabilir. Ön testlerde birkaç dB marj hedefle. 6 dB marj, ölçülen değerin sınırın yaklaşık yarısı olması demektir.

## 7. Ön uyumluluk: masada yapılabilecek ölçümler

| Araç | Ne işe yarar? | Maliyet |
|---|---|---|
| **Yakın alan probları (H ve E) + spektrum analizörü** | Kart üstünde gürültü kaynağını bulmak | Düşük – orta |
| **RF akım probu (current clamp)** | Kablodaki ortak mod akımını ölçmek; **ışınımlı emisyonun en iyi göstergesi** | Orta |
| **LISN** | İletimli emisyonu laboratuvara yakın koşulda ölçmek | Orta |
| **ESD tabancası** (kiralanabilir) | ESD bağışıklık ön testi | Orta – yüksek |
| **Basit araçlar** | Röle ile burst üretmek; yasal frekans ve güçte bir el telsiziyle kaba RF testi | Düşük |

**Yöntem:**
- Ön ölçüm **mutlak** değil **göreceli** düşünülür: "değişiklikten önce ve sonra ne kadar düştü?"
- Ölçüm düzeneğini (kablo boyu, yerleşim, cihaz modu) her seferinde aynı tut ve fotoğrafla kaydet.
- Basit bir H alanı probu, yarı sert bir koaksiyel kablonun ucunu küçük bir halka yaparak bile yapılabilir.

## 8. Test laboratuvarına hazırlık

1. **Test planı:** Hangi standart, hangi portlar, hangi seviyeler, hangi performans kriteri, hangi çalışma modları?
2. **Test edilen cihazın (EUT) yapılandırması:** Kablo tipleri ve boyları, aksesuarlar, besleme, montaj şekli. Gerçek kullanımı temsil etmeli.
3. **Test modu yazılımı:** Tüm fonksiyonları aynı anda çalıştırsın: sensör ölçümü, haberleşme, ekran, röle çıkışları.
4. **İzleme yöntemi:** Cihazın durumunu test odasının dışından izleyebilmelisin. Örnekler: haberleşme üzerinden log, durum LED'leri, analog çıkış. Gaz dedektöründe sensör okumasını sabit bir koşulda (ör. temiz hava veya sabit test gazı) izleyip sapmayı ölçmek gerekir.
5. **Düzeltme kiti:** Geçme ferritler, çeşitli kapasitörler, TVS diyotlar, bakır bant, havya. Sorun çıktığında yerinde deneme yapabilmek, ikinci bir laboratuvar randevusunu önleyebilir.
6. **Ön tarama:** Laboratuvarda tam test öncesi hızlı bir ön tarama (prescan) iste. Sorunları erken görür, zaman ve para kazanırsın.

## 9. Sık görülen başarısızlıklar ve ilk denenecekler

| Belirti | Olası neden | İlk denenecek |
|---|---|---|
| Saat harmoniğinde ışınımlı tepe | Hızlı kenarlar, kablodaki ortak mod akımı | GPIO hızını düşürmek, seri direnç, kablo ferriti, spread spectrum |
| 150 kHz – birkaç MHz arası iletimli tepeler | Buck regülatörün f_sw harmonikleri | Giriş LC filtresi, sıcak döngü düzeltmesi |
| ESD'de reset | NRST veya besleme bozuluyor | TVS yerleşimi, NRST kapasitörü, watchdog ile güvenli toparlanma |
| ESD'de ekran veya haberleşme donması | Çevre birimi kilitleniyor | Yeniden başlatma mantığı, register'ları periyodik yazma, CRC |
| RF alanında sensör okuması kayıyor | Op-amp girişlerinde doğrultma | Giriş RC filtresi, ekranlama, yazılımla filtreleme |
| EFT'de kilitlenme | Bozucu güç girişinden içeri giriyor | CMC, TVS, giriş filtresi, watchdog |

## 10. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **CE / DoC** | AB uygunluk işareti / uygunluk beyanı |
| **Uyumlaştırılmış standart** | Uyulduğunda direktife uygunluk varsayımı sağlayan standart |
| **Generic / ürün standardı** | Genel amaçlı / belirli ürün ailesine özel standart |
| **EUT** | Equipment Under Test: test edilen cihaz |
| **Port** | Cihazın dış dünyaya arayüzü: kasa, güç, sinyal |
| **CDN** | Coupling/Decoupling Network: bozucuyu kabloya uygulayan devre |
| **LISN / AMN** | İletimli emisyon ölçümünde kullanılan hat empedans ağı |
| **SAC / OATS** | Yarı yansımasız oda / açık alan test sahası |
| **QP / AV** | Quasi-peak / ortalama dedektör |
| **Class A / B** | Endüstriyel / konut emisyon sınıfı |
| **Performans kriteri** | Bağışıklık testinde kabul koşulu (A, B, C) |
| **Ön uyumluluk (pre-compliance)** | Laboratuvar öncesi masada yapılan ölçümler |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki madde [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.2, bölüm 11):

- [x] Hedef EMC standardı (ör. gaz algılama için EN 50270) ve test seviyeleri tasarım başında belirlendi

## Kontrol soruları

→ [quiz.md](quiz.md) · 12 soru, 2'si hesap
