# Şematik çizim ve dokümantasyon

- **Oluşturma:** 2026-10-16
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Bağlantılı:** [Şematik kontrol listesi](../../Sematik-Tasarim/kontrol-listesi.md) · [Direnç, 0 Ω jumper](../../Komponentler/01-direnc/ozet.md#56-0-ω-direnç-jumper)

> Kurallar EDA aracından bağımsızdır (Altium, KiCad, OrCAD…). Araca özel ayarlar ayrıca belirtildi. Şirketin kendi çizim standardı varsa o önce gelir.
>
> **Okuma planı:** 1. oturum: bölüm 1–5 · 2. oturum: 6–9 · 3. oturum: 10–14.

---

## ⚡ Hızlı tekrar

1. Şematik bir **belgedir**: onu sen, review yapan kişi, layout'çu, üretim ve 2 yıl sonra arıza arayan servis okur. "Çalışıyor" yetmez, **okunmalı**.
2. Sayfa düzeni: ilk sayfa **blok diyagram**, sonra **her fonksiyona bir sayfa** (güç, MCU, sensör, haberleşme, I/O).
3. Akış kuralı: **giriş solda, çıkış sağda; yüksek gerilim yukarıda, GND aşağıda.** Çizgiler mümkün olduğunca kesişmesin.
4. **Aynı isimli etiketler birbirine bağlıdır.** Etiketteki tek harflik yazım hatası (`SDA` / `SDA1`) iki ayrı net yaratır ve hiçbir hata vermez. Bunu **ERC**'nin "tek pinli net" uyarısı yakalar.
5. Her komponentte **değer + tolerans + gerilim/güç + paket** yazılı olsun (ör. `100n 50V X7R 0603`). Üretim yalnızca şematikteki/BOM'daki bilgiyi bilir.
6. Kararlarını şematiğe **not** olarak yaz: neden bu değer, hangi hesap, hangi layout kuralı.
7. Montaj seçenekleri (DNP, 0 Ω, trimer) **açıkça** işaretlenmeli; "hangisi takılı?" sorusu üretimde sorulmamalı.
8. Kütüphane güvenilir değilse her şey boşa gider: **pin numarası ↔ datasheet** ve **footprint ↔ gerçek parça** kontrol edilmeden kart sipariş edilmez.

## 🧮 Kural kartı

| Kural | Neden | Örnek |
|---|---|---|
| Dört yollu kavşak yok; iki T kullan | Nokta (junction) silik basılırsa bağlantı mı, kesişme mi anlaşılmaz | `─┼─` yerine iki ayrı `─┬─` |
| Net ismi büyük harf, boşluksuz, anlamlı | Arama, BOM ve layout'ta okunur | `I2C1_SDA`, `VIN_24V`, `RESET_N` |
| Aktif-düşük sinyale sonek | Mantığı ters okumayı önler | `CS_N`, `nRESET`, `/EN` |
| Referans numarası sayfaya göre | Kartta parçayı bulmak kolaylaşır | Sayfa 2 → R201, C205 |
| Komponent etiketi tam | Yanlış parça takılmasını önler | `4k7 1% 0603`, `10u 25V X5R 0805` |
| Her bastırılan ERC uyarısına gerekçe | Gerçek hatanın gizlenmesini önler | "U3.7 kasıtlı NC – datasheet s.12" |
| Her IC'yi "Typical Application" ile karşılaştır | Eksik pin/komponent en çok burada yakalanır | Regülatör FB, BOOT, EN pinleri |

---

## 1. Şematik kimin için çizilir?

Şematiği bir **tarif** gibi düşün: sen yemeği yaptın ama tarifi başkası okuyacak.

| Okuyucu | Şematikten ne ister? |
|---|---|
| Sen, 6 ay sonra | "Bu direnci neden 4,7 kΩ seçmiştim?" → **not** |
| Review yapan mühendis | Akışı hızlı takip etmek → **düzen** |
| Layout yapan kişi | Hangi parça kritik, nereye yakın olmalı → **layout notu** |
| Üretim / satın alma | Tam parça tanımı, seçenekler → **BOM alanları, DNP** |
| Test ve servis | Ölçüm noktaları, beklenen gerilimler → **TP ve değer notları** |

> **Altın kural:** Şematiği yalnızca sen anlayabiliyorsan, şematik henüz bitmemiştir.

## 2. Sayfa düzeni

**İlk sayfa: blok diyagram.** Kutular ve oklarla kartın bütün resmi: güç girişi → regülatörler → MCU → sensör ön ucu → haberleşme → çıkışlar. Her kutunun yanına hangi sayfada olduğunu yaz.

**Sonra her fonksiyona bir sayfa:**

```
Sayfa 1  Blok diyagram, revizyon geçmişi
Sayfa 2  Güç girişi ve koruma, regülatörler
Sayfa 3  MCU, kristal, debug konnektörü
Sayfa 4  Sensör ön ucu (analog)
Sayfa 5  Haberleşme (RS-485, UART)
Sayfa 6  Çıkışlar (röle, buzzer, LED)
Sayfa 7  Konnektörler, test noktaları, montaj delikleri
```

- **Düz (flat) yapı:** Sayfalar etiket/port ile birbirine bağlanır. Küçük ve orta kartlar için yeterli.
- **Hiyerarşik yapı:** Bir sayfa, diğer sayfayı tek bir "kutu" (sheet symbol) olarak kullanır. Aynı devre birkaç kez tekrarlanıyorsa (ör. 4 kanal sensör girişi) çok kullanışlıdır: devreyi bir kez çizer, dört kez kullanırsın.

**Başlık bloğu** her sayfada: proje adı, kart adı, revizyon, tarih, sayfa no / toplam, çizen.

## 3. Akış ve okunabilirlik

**Yön kuralı:**
- Sinyal **soldan sağa** akar: konnektör/sensör solda, MCU ortada, çıkışlar sağda.
- Gerilim **yukarıdan aşağıya**: besleme sembolleri yukarıda, GND sembolleri aşağıda. GND oku hiçbir zaman yukarı bakmaz.

**Kavşaklar:**

```
Kötü (dört yollu)         İyi (iki T)

      │                        │
  ────●────                ────●────
      │                            │
                               ────●────
                                   │
```

Dört yollu kavşakta nokta silik basılırsa ya da yazıcıda kaybolursa "bağlı mı, sadece kesişiyor mu?" sorusu doğar. İki T'de soru yoktur.

**Diğer kurallar:**
- Çizgi bir pinin **ortasından** değil ucundan bağlanır; parçanın üstünden geçmez.
- Bir pine birden fazla tel gelecekse nokta ile birleştir, telleri pin ucunda üst üste bindirme.
- Yazılar (değer, referans) parçanın yanında, tellerin üstünde değil.
- Uzun teller yerine **etiket** kullan; ama 3–4 parçalık küçük bir devreyi etiketlere bölme. Tel, okuyucuya "buradan buraya gidiyor" bilgisini gözle verir.
- Benzer devreler aynı şekilde çizilir (4 sensör kanalı birbirinin kopyası gibi görünmeli).

## 4. Net isimleri ve etiketler

**Temel fikir:** Etiket, bir **adres** gibidir. Aynı adresi taşıyan bütün noktalar birbirine bağlıdır; hiç tel çizilmese de.

| Etiket türü | Kapsam | Kullanım |
|---|---|---|
| Yerel etiket (net label) | Genelde yalnızca o sayfa | Sayfa içinde uzak noktaları bağlamak |
| Global etiket / port | Tüm sayfalar | Sayfalar arası sinyaller (`I2C1_SDA`) |
| Hiyerarşik pin/port | Üst sayfadaki kutu ile alt sayfa arası | Hiyerarşik tasarım |
| Güç sembolü | Tüm proje | `+3V3`, `GND`, `VIN_24V` |

> **Araca dikkat:** Kapsam kuralları araçtan araca değişir. Altium'da etiketlerin sayfalar arası bağlanıp bağlanmayacağını proje ayarlarındaki **Net Identifier Scope** belirler. Yeni projede ilk iş bu ayarı kontrol et.

**İsimlendirme alışkanlıkları:**
- Büyük harf, boşluk ve Türkçe karakter yok: `SENS_OUT`, `HEATER_I`.
- Raylar gerilimiyle: `+3V3`, `+5V`, `VIN_24V`, `+3V3_A` (analog ray).
- Aktif-düşük: `RESET_N` / `nRESET` / `/RESET`. Projede **tek bir** biçim seç.
- Arayüz + numara + sinyal: `UART2_TX`, `SPI1_SCK`, `RS485_A`.
- Yön bildiren isimlerde **kimin bakışından** olduğunu netleştir: MCU'nun `UART2_TX`'i, karşı tarafın RX'ine gider.

**En sinsi hata: yazım farkı.** `SDA` ile `SDA1`, `+3.3V` ile `+3V3`, `GND` ile `GNDA`. Araç bunları **farklı netler** olarak görür, kart üretilir, bağlantı yoktur. Korunma: ERC'deki **"tek pinli net"** ve **"bağlanmamış etiket"** uyarılarını asla bastırma.

**Analog ve dijital toprak isimleri:** `GND` ve `AGND` gibi iki ayrı net açıyorsan, nerede ve nasıl birleşeceğini (tek nokta, 0 Ω, net-tie) şematikte açıkça göster. Çoğu tasarımda **tek GND** daha iyidir; ayrıntı [PCB yerleşim dersi](../pcb-yerlesim-ve-iz-cizimi/ozet.md).

## 5. Referans tanımlayıcılar

| Harf | Parça | Harf | Parça |
|---|---|---|---|
| R | Direnç | J / P | Konnektör (J: sabit taraf, P: fiş) |
| RV / TR | Ayarlı direnç, trimer | SW | Anahtar, buton |
| C | Kapasitör | F | Sigorta, PTC |
| L | Bobin | K | Röle |
| FB | Ferrit boncuk | Y / X | Kristal, rezonatör |
| D | Diyot, LED, TVS | T | Trafo |
| Q | Transistör, MOSFET | BZ / LS | Buzzer, hoparlör |
| U | Entegre (IC) | TP | Test noktası |
| MH / H | Montaj deliği | FID | Fiducial (dizgi makinesi işareti) |

- **Sayfaya göre numaralandır:** Sayfa 3'teki parçalar R301, C305, U301… Kartın üstünde "R412" görünce hangi sayfaya bakacağını bilirsin.
- **Numaralar kalıcıdır:** Bir revizyonda parça silinirse numarası boş kalabilir; kalan parçaları baştan numaralama. Aksi hâlde eski BOM, servis notları ve test dokümanları birbirini tutmaz.

## 6. Komponent bilgileri

Şematikte görünen yazı ile BOM'a giden bilgi aynı kaynaktan gelmeli: komponentin **alanları (parameters)**.

| Alan | Örnek | Neden |
|---|---|---|
| Değer | `4k7`, `100n`, `10u` | Ondalık virgül yerine harf: `4k7` = 4,7 kΩ. Silik baskıda virgül kaybolmaz |
| Tolerans | `1%`, `10%` | Hassas devrede kritik |
| Gerilim / güç | `50V`, `0.25W` | Kapasitör DC bias, direnç gücü |
| Dielektrik / tür | `X7R`, `C0G`, `ince film` | Davranışı belirler |
| Paket | `0603`, `SOT-23`, `SOIC-8` | Footprint ile eşleşmeli |
| Üretici + MPN | `Murata GRM188R71H104KA93D` | Satın alma tam olarak bunu alır |
| İkinci kaynak | Alternatif MPN | Tedarik sorunu olunca hat durmasın |
| DNP | `DNP` veya varyant bilgisi | Takılmayacak parça |

**Görünen etiket kısa, BOM bilgisi tam olsun:** şematikte `100n 50V X7R 0603` yeter; MPN, BOM ve kütüphanede durur.

## 7. Sembol ve footprint kütüphanesi

Kütüphane hatası şematikte görünmez, kart gelince ortaya çıkar. En pahalı hatalar buradadır.

**Sembol kontrolü:**
1. Pin **numaraları** datasheet'in pin tablosu ile birebir. Pin **isimleri** doğru olsa bile numarası yanlışsa kart yanlış bağlanır.
2. **Gizli güç pini olmasın.** Bazı eski kütüphaneler VCC/GND pinlerini gizler ve onları otomatik olarak `VCC`/`GND` isimli netlere bağlar. Senin rayının adı `+3V3` ise bağlantı hiç kurulmaz ve şematikte hiçbir şey görünmez.
3. **Pin türleri** doğru (giriş, çıkış, açık kolektör, güç, pasif). ERC bu bilgiyle çalışır.
4. Exposed pad (alttaki termal ped) sembolde ayrı bir pin olarak var ve bağlı.
5. Çok parçalı IC'lerde (ör. 4 op-amp'lı paket) **kullanılmayan parça** da yerleştirilmiş ve bağlanmış.

**Footprint kontrolü:**
1. Ped boyutları ve aralığı datasheet'in "recommended land pattern" çizimine uygun (yoksa IPC-7351).
2. **Pin 1** yeri ve işareti doğru; diyot, LED, elektrolitik kapasitörde **polarite** işareti var.
3. **1:1 kâğıt testi:** Layout'u gerçek ölçekte yazdır, parçaları kâğıdın üstüne koy. Konnektör, buton, ekran gibi mekanik parçalarda çok hata yakalar.
4. Bacak sırası farklı paketlere dikkat: aynı isimli SOT-23 MOSFET'lerin G-S-D sırası üreticiye göre değişebilir.

## 8. ERC: elektriksel kural kontrolü

ERC, şematiğin "yazım denetimi"dir. Anlamı kontrol etmez; **tutarlılığı** kontrol eder.

| ERC ne yakalar? | Örnek |
|---|---|
| Tek pinli net | Etiket yazım hatası (`SDA` / `SDA1`) |
| Bağlanmamış giriş pini | Boşta bırakılan CMOS girişi |
| Çıkış–çıkış çakışması | İki push-pull çıkış aynı nette |
| Sürülmeyen güç pini | Ray adı yanlış; IC'nin besleme pini hiçbir kaynağa bağlı değil |
| Kopuk tel ucu | Pine değmeyen çizgi |

| ERC ne **yakalamaz**? | Nasıl yakalarsın? |
|---|---|
| Yanlış değer (10 kΩ yerine 1 kΩ) | Hesap notu + review |
| Ters bağlı diyot / UART TX–TX | Review, kontrol listesi |
| Yanlış footprint | 1:1 kâğıt testi, datasheet |
| Eksik komponent (ör. FB'ye giden bölücü) | "Typical Application" karşılaştırması |
| Gerilim uyumsuzluğu (5 V → 3,3 V pin) | Kontrol listesi bölüm 5 |

**Kurallar:**
- ERC sonucunu **sıfır uyarıya** indir. Kasıtlı olanları "No ERC" işaretiyle bastır ve yanına gerekçe yaz.
- "Sürülmeyen güç" uyarısı için güç girişine **power flag** koy (araçtan araca adı değişir).
- 300 uyarılık bir liste, içindeki tek gerçek hatayı gizler.

## 9. Tasarım notları

Şematiğe yazılan küçük notlar, review süresini yarıya indirir.

```
NOT: R16 = RL. Sensör datasheet önerisi 5–20 kΩ.
NOT: C12 + R12 → f_c ≈ 10 Hz (anti-aliasing). C12 U3.5 pinine bitişik.
NOT: Q4 gate pull-down (R40) açılışta röleyi kapalı tutar. Kaldırma.
NOT: F1 1 A slow-blow. Kablo ve iz 2 A'ye göre boyutlandırıldı.
LAYOUT: U1 sıcak döngüsü (C1–U1–D1) en küçük alan, aynı katmanda.
```

**Ne yazılır?**
- **Neden** bu değer (hesap, datasheet önerisi).
- **Layout kuralları:** yakınlık, kısa dönüş yolu, iz genişliği, izolasyon mesafesi.
- **Beklenen değerler:** test noktasında hangi gerilim ölçülmeli (`TP3: 3,30 V ±2%`).
- **Uyarılar:** "Bu parçayı kaldırma", "Bu net kartın dışına çıkıyor, ESD".

## 10. Seçenekler ve varyantlar

Bazen bir yere iki farklı parça takılabilecek şekilde tasarım yapılır. Bu esneklik iyidir, ama **belgelenmezse** üretimde karışıklık yaratır.

**Örnek:** Bir trimere paralel 0 Ω direnç. 0 Ω takılıysa trimer kısa devredir ve çevirmenin hiçbir etkisi yoktur. 0 Ω sökülürse trimer devreye girer. Şematikte hangisinin takılı olduğu yazmıyorsa, üretimde biri trimeri boşuna ayarlamaya çalışır.

**Doğru yöntem:**
- Takılmayacak parçaya **DNP** (Do Not Place / Populate) işareti koy.
- Birden fazla ürün çeşidi varsa EDA aracının **varyant** özelliğini kullan: her varyantın kendi BOM'u çıkar.
- Seçeneğin **neden** var olduğunu not et: "R18 takılı = sabit RL. Ayarlı RL gerekirse R18 DNP, TR1 takılı."
- 0 Ω yerine **net-tie** kullanılabilecek yerler: iki netin tek noktada birleşmesi (ör. AGND–GND). 0 Ω bir BOM kalemi ve montaj adımıdır; net-tie ise sadece bakırdır.

## 11. BOM hijyeni

**BOM (Bill of Materials)**, kartın malzeme listesidir. Satın alma ve üretim yalnızca BOM'u görür.

| Sütun | Neden |
|---|---|
| Referanslar (R1, R5, R7) | Hangi konumlara takılacak |
| Adet | Satın alma miktarı |
| Değer + açıklama | İnsan okuması için |
| Üretici + MPN | Tam olarak hangi parça |
| Paket | Footprint kontrolü |
| DNP / varyant | Takılmayacaklar |
| Alternatif MPN | İkinci kaynak |

**Kontrol et:**
- **Yaşam döngüsü:** Parça "Active" mi? **NRND** (yeni tasarımda önerilmez) veya **EOL** (üretimi bitiyor) olan parçayla yeni tasarım başlatma.
- **Tek kaynak riski:** Yalnızca bir üreticinin yaptığı parça, o üretici sorun yaşarsa hattı durdurur. Kritik olmayan pasifler için onaylı alternatif listesi tut.
- **Stok ve teslim süresi:** Tasarım bitmeden distribütörlerde kontrol et.
- **Paket tutarlılığı:** Aynı değerdeki dirençler mümkünse aynı pakette olsun; dizgi makinesinde besleyici (feeder) sayısı azalır.

## 12. Revizyon ve review süreci

**Revizyon:**
- Her sipariş edilen kart bir revizyondur: Rev A, Rev B… (veya 1.0, 1.1). Revizyon **bakır üstünde** (silkscreen veya bakır yazı) de yazsın.
- Şematiğin ilk sayfasında **değişiklik tablosu:** revizyon, tarih, ne değişti, neden.
- Footprint, pin ataması veya bağlantı değişikliği → yeni revizyon. "Küçük bir değişiklik" diye aynı revizyon numarasıyla kart basılmaz.

**Review akışı:**
1. **Kendi review'ün:** [Kontrol listesi](../../Sematik-Tasarim/kontrol-listesi.md) baştan sona.
2. **Fosforlu kalem yöntemi:** Şematiğin PDF'ini yazdır, kontrol ettiğin her teli boya. Boyanmamış tel kalmayınca bitti.
3. **Her IC için datasheet:** "Typical Application" devresi ve pin tablosu karşılaştırması.
4. **İkinci göz:** Başka bir mühendis veya Claude. Sorular not alınır, cevaplar şematiğe not olarak eklenir.
5. Bulunan hatalar [hatalar-dersler.md](../../Sematik-Tasarim/hatalar-dersler.md) dosyasına işlenir; bir sonraki projede tekrar yaşanmaz.

## 13. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| Etiket yazım farkı (`SDA` / `SDA1`) | Sessizce iki ayrı net oluşur | ERC "tek pinli net" uyarısını oku |
| Gizli güç pinli eski sembol | IC beslemesiz kalır, şematikte görünmez | Tüm güç pinleri görünür ve bağlı |
| Dört yollu kavşak | Bağlantı belirsiz | İki T |
| Komponentte sadece değer var (`10u`) | Yanlış gerilim/paket takılır | `10u 25V X5R 0805` + MPN |
| Pin ismine güvenip numarayı kontrol etmemek | Kart yanlış bağlanır | Pin tablosu ile numara numara karşılaştır |
| DNP belirsiz | Üretimde yanlış montaj | DNP işareti, varyant, not |
| ERC uyarılarını toptan bastırmak | Gerçek hata gizlenir | Sıfır uyarı; her bastırmaya gerekçe |
| Not yok | 6 ay sonra kimse "neden" bilmez | Hesap ve layout notları şematikte |
| Revizyon artırmadan değişiklik | Sahada iki farklı kart aynı isimle | Her değişiklikte revizyon + tablo |
| Kullanılmayan op-amp kanalı boşta | Salınım, akım tüketimi | Tampon olarak bağla (kontrol listesi bölüm 1) |

## 14. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Net** | Birbirine elektriksel olarak bağlı noktaların tümü |
| **Net label / etiket** | Teli çizmeden aynı isimli noktaları bağlayan isim |
| **Port / global etiket** | Sayfalar arası bağlantı etiketi |
| **Hiyerarşik şematik** | Sayfaların kutu (sheet symbol) olarak iç içe kullanıldığı yapı |
| **ERC** | Electrical Rule Check; şematik tutarlılık denetimi |
| **Power flag** | Bir netin güç kaynağı tarafından sürüldüğünü ERC'ye bildiren işaret |
| **Referans tanımlayıcı** | R12, C5, U3 gibi parça kimliği |
| **MPN** | Manufacturer Part Number; üreticinin parça numarası |
| **BOM** | Bill of Materials; malzeme listesi |
| **DNP** | Do Not Place/Populate; takılmayacak parça |
| **Varyant** | Aynı kartın farklı parça takımıyla üretilen çeşidi |
| **Net-tie** | İki ayrı neti tek noktada birleştiren bakır parça (BOM kalemi değildir) |
| **NRND / EOL** | Yeni tasarımda önerilmez / üretimi sona eriyor |
| **Land pattern** | Footprint'teki ped düzeni |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.4, bölüm 1):

> BOM'daki parçaların yaşam döngüsü ve ikinci kaynak maddesi zaten bölüm 9'da.

- [x] Blok diyagram sayfası ve revizyon/değişiklik tablosu var
- [x] Sembollerde gizli güç pini yok; pin numaraları datasheet pin tablosuyla karşılaştırıldı
- [x] Footprint'ler datasheet land pattern'ine göre kontrol edildi; mekanik parçalar 1:1 kâğıt testinden geçti
- [x] DNP ve montaj seçenekleri açıkça işaretli; varyant BOM'ları ayrı
- [x] Kritik değerlerin hesabı, test noktalarında beklenen gerilimler ve layout kuralları şematikte not olarak yazılı

## Kontrol soruları

→ [quiz.md](quiz.md) · 10 soru
