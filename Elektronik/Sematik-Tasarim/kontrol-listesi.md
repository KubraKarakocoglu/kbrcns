# Şematik Kontrol Listesi · v1.2

> **Kullanım:** Bu ana liste. Her projede `Yeni-Kayit.ps1 -Tur Proje` bunu `sematik-review.md` olarak proje klasörüne kopyalar; işaretlemeyi orada yap.
> Bir konu veya hatadan yeni madde çıktığında **buraya** ekle ve sürüm numarasını artır.
>
> Her maddede son söz komponentin datasheet'idir. Buradaki değerler tipik başlangıç noktalarıdır, tasarım değeri değil.

## 1. Genel ve dokümantasyon

- [ ] Her sayfada başlık bloğu var: proje, revizyon, tarih, sayfa no
- [ ] Net isimleri anlamlı (`3V3`, `VBAT`, `I2C1_SDA`); otomatik isimli kritik net yok
- [ ] Her komponentte değer, tolerans, gerilim/güç derecesi ve paket bilgisi var
- [ ] ERC (Electrical Rule Check) temiz; bastırılan her uyarının gerekçesi not edilmiş
- [ ] Her IC, datasheet'teki "Typical Application" devresiyle karşılaştırıldı
- [ ] Kullanılmayan pinler datasheet önerisine göre bağlandı (boşta bırakılan giriş yok)
- [ ] Kullanılmayan op-amp kanalı tampon (buffer) olarak bağlandı, girişi ortak mod aralığında bir gerilime çekildi

## 2. Güç girişi ve koruma

- [ ] Ters polarite koruması var (seri Schottky diyot veya P-MOSFET)
- [ ] Aşırı akım koruması var (sigorta veya PTC); değeri nominal akımın üstünde, kablo/iz kapasitesinin altında
- [ ] Geçici gerilime karşı TVS diyot: VRWM ≥ en yüksek normal giriş gerilimi, kenetleme gerilimi (VC) ≤ korunan devrenin mutlak maksimum değeri
- [ ] Hot-plug riski değerlendirildi: uzun kablo endüktansı + düşük ESR'li seramik giriş kapasitörü gerilim sıçraması üretebilir

## 3. Regülatörler

- [ ] **LDO dropout:** en düşük giriş geriliminde Vin − Vout ≥ dropout (tüm sıcaklık ve yük aralığında)
- [ ] **LDO ısı:** P = (Vin − Vout) × I_yük; Tj = Ta + P × θJA < Tj_max (marjlı)
- [ ] **LDO kararlılık:** çıkış kapasitörünün tipi ve ESR aralığı datasheet'e uygun (bazı LDO'lar düşük ESR'li seramikle kararsızdır)
- [ ] **Buck:** indüktör doyma akımı > tepe akım; giriş kapasitörünün RMS akım derecesi yeterli
- [ ] **Seramik kapasitör DC bias:** yüksek değerli, küçük paketli MLCC'ler çalışma geriliminde nominal kapasitesinin büyük kısmını kaybedebilir; efektif değer üretici eğrisinden kontrol edildi
- [ ] Enable / power-good sıralaması gerekiyorsa tanımlı
- [ ] Analog besleme dijitalden ayrılması gerekiyor mu? (ferrit boncuk veya LC filtre)

## 4. Decoupling

- [ ] Her IC besleme pinine 100 nF seramik kapasitör (layout notu: pine en yakın konum)
- [ ] Datasheet'in istediği ek kapasitörler eklendi (ör. MCU VCAP pinleri, VDDA için ek filtre)
- [ ] Her güç rayında bulk kapasitör var
- [ ] Referans gerilim pinleri (VREF+) için datasheet'in filtre önerisi uygulandı
- [ ] Decoupling dielektriği X7R/X5R (küçük değerlerde C0G); Y5V/Z5U yok
- [ ] Layout notu: pin → kapasitör → GND via döngüsü minimum; via pad'e bitişik, uzun ince iz yok
- [ ] Analog besleme ferrit boncuğu: DC akım derecesi yeterli (doyma yok), LC rezonansı değerlendirildi
- [ ] Tantal kullanıldıysa gerilim derating üretici önerisine uygun

## 5. Mikrodenetleyici

- [ ] NRST: datasheet önerisine göre kapasitör / pull-up; gerekiyorsa reset butonu
- [ ] BOOT0 (STM32): pull-down ile tanımlı seviyede, boşta değil
- [ ] **Kristal yük kapasitörleri:** C1 = C2 ≈ 2 × (CL − C_stray); CL kristalin datasheet değeri, C_stray tipik 2–5 pF
- [ ] Debug konnektörü erişilebilir (SWD: SWDIO, SWCLK, NRST, GND, VTref)
- [ ] Pin ataması bir araçla (ör. STM32CubeMX) doğrulandı; alternate function çakışması yok
- [ ] 5 V toleranslı olmayan pinlere 5 V sinyal gelmiyor
- [ ] **Fail-safe başlangıç:** reset ve boot sırasında MCU pinleri yüksek empedanstadır; MOSFET gate, röle, enable gibi hatlar pull-up/down ile güvenli duruma çekildi
- [ ] Debug konnektöründe NRST var (connect under reset); saat MCO veya test noktasından ölçülebilir
- [ ] MCU kapalıyken gerilim gelebilecek girişlerde back-powering önlemi (seri R, Ioff'lu tampon)
- [ ] Kullanılmayan pinlerin yazılımda analog moda alınacağı not edildi
- [ ] ADC girişlerinde kaynak empedansı ve örnekleme süresi uyumlu (veya pin kapasitörü / tampon)
- [ ] Watchdog ve BOR kullanımı planlandı
- [ ] MOSFET'ler MCU gerilimine uygun (R_DS(on), 2,5 V veya 3,3 V gate'te belirtilmiş)

## 6. Analog ve sensör

- [ ] Op-amp giriş ortak mod aralığı ve çıkış salınımı besleme ile uyumlu (rail-to-rail gerekli mi?)
- [ ] Op-amp kapasitif yük sürüyorsa çıkışa izolasyon direnci eklendi
- [ ] ADC girişinde anti-aliasing RC filtre var; kaynak empedansı ADC örnekleme süresine uygun
- [ ] ADC referansının kararlılığı ve gürültüsü ölçüm hassasiyetine yetiyor; mümkünse oransal (ratiometric) ölçüm tercih edildi
- [ ] Dış dünyaya açılan sensör girişlerinde seri direnç + kenetleme (clamp) koruması var
- [ ] Gerilim bölücüde empedans ↔ akım tüketimi ↔ ADC yüklemesi dengelendi

## 7. Dijital arayüzler

- [ ] I²C pull-up değeri hız ve hat kapasitansına göre seçildi (tipik 2,2 kΩ – 10 kΩ); hatta yalnızca bir set pull-up var
- [ ] Farklı gerilim domainleri arasında seviye dönüştürücü var
- [ ] UART bağlantısı çaprazlandı: TX → RX, RX → TX
- [ ] SPI CS hatlarında pull-up var (boot sırasında hiçbir slave seçili olmasın)
- [ ] Hızlı kenarlı hatlarda seri sonlandırma direnci yeri bırakıldı (tipik 22–33 Ω)

## 8. Konnektörler ve dış dünya

- [ ] Dışarı açılan her hatta ESD koruması var
- [ ] Konnektör pin sırası mekanik çizim ve karşı taraf ile karşılaştırıldı; ters takılmaya karşı önlem var
- [ ] Kabloyla gelen hatlarda EMC filtresi gerekip gerekmediği değerlendirildi

## 9. Test ve üretim

- [ ] Test noktaları var: tüm güç rayları, GND, kritik sinyaller
- [ ] Programlama ve kalibrasyon arayüzü üretimde erişilebilir
- [ ] Durum LED'i var (güç + MCU kontrollü)
- [ ] BOM: tüm parçalar aktif üretimde, stokta ve mümkünse ikinci kaynaklı

## 10. Pasif komponentler

**Direnç**
- [ ] Direnç gücü ≤ %50 anma; yüksek ortam sıcaklığında derating eğrisi kontrol edildi
- [ ] Yüksek gerilimli dirençlerde paket çalışma gerilimi ve creepage kontrol edildi (gerekirse seri dirençler)
- [ ] Akım ölçme şantı Kelvin bağlantılı; gücü ve TCR'si uygun
- [ ] Hassas ölçüm yolunda ince film / düşük TCR; bölücü oran hatası hesaplandı
- [ ] Kükürtlü ortam riski varsa anti-sülfür dirençler

**Kapasitör**
- [ ] Elektrolitik: çalışma gerilimi ≤ %80 anma; ömür hesabı (sıcaklık + ripple); polarite işareti net
- [ ] Zamanlama, filtre ve osilatör kapasitörleri C0G (veya film)
- [ ] Şebeke tarafında yalnızca sertifikalı X/Y kapasitörler; Y kaçak akımı hesaplandı
- [ ] Büyük bulk kapasitörlerin inrush akımı değerlendirildi
- [ ] MLCC'ler kart kenarı, vida deliği, konnektör ve kırma çizgilerinden uzak

**Bobin ve ferrit**
- [ ] Bobin: Isat ≥ regülatör akım limiti (sıcak durumda); Irms marjlı; L datasheet aralığında
- [ ] Hassas devre yakınında ekranlı bobin
- [ ] Endüktif yüklerde (röle, solenoid, motor) flyback diyotu
- [ ] Ferrit boncuk: gürültü frekansında Z ve çalışma akımında DC bias kontrol edildi; LC rezonansı hesaplandı ve sönümlendi

## 11. EMC

- [ ] Hedef EMC standardı (ör. gaz algılama için EN 50270) ve test seviyeleri tasarım başında belirlendi
- [ ] Kesintisiz GND düzlemi; hızlı sinyaller yarık veya bölme üzerinden geçmiyor
- [ ] Katman dizilimi: her sinyal katmanı bir referans düzleme bitişik
- [ ] Konnektörler mümkünse tek kenarda; I/O bölgesinde filtre ve koruma
- [ ] Her dış hatta TVS konnektöre en yakın, GND bağlantısı kısa
- [ ] Diferansiyel hatlarda (USB, CAN, RS-485) uygun ESD koruması ve CMC
- [ ] Hızlı sinyallerde seri sonlandırma; katman değişiminde dönüş via'sı veya dikiş kapasitörü
- [ ] Anahtarlamalı regülatör: sıcak döngü en küçük, SW düğümü küçük, giriş filtresi
- [ ] Kablo ekranı konnektörde 360° sonlandırılıyor

## 12. Kapanış

- [ ] Şematik bu listeyle ikinci bir göz tarafından (kişi veya Claude) review edildi
- [ ] Bu tasarımdan çıkan dersler [hatalar-dersler.md](/Elektronik/Sematik-Tasarim/hatalar-dersler.md) dosyasına işlendi

## Sürüm geçmişi

| Sürüm | Tarih | Değişiklik |
|---|---|---|
| v1.2 | 2026-10-12 | Komponent ve EMC derslerinden maddeler: bölüm 5'e 6 madde, yeni bölüm 10 (Pasif komponentler) ve 11 (EMC) |
| v1.1 | 2026-10-12 | "Güç ve decoupling" konusundan 4 madde eklendi (bölüm 4) |
| v1 | 2026-10-09 | İlk sürüm |
