# Şematik Kontrol Listesi · v1.8

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
- [ ] Blok diyagram sayfası ve revizyon/değişiklik tablosu var
- [ ] Sembollerde gizli güç pini yok; pin numaraları datasheet pin tablosuyla karşılaştırıldı
- [ ] Footprint'ler datasheet land pattern'ine göre kontrol edildi; mekanik parçalar 1:1 kâğıt testinden geçti
- [ ] DNP ve montaj seçenekleri açıkça işaretli; varyant BOM'ları ayrı
- [ ] Kritik değerlerin hesabı, test noktalarında beklenen gerilimler ve layout kuralları şematikte not olarak yazılı

## 2. Güç girişi ve koruma

- [ ] Ters polarite koruması var (seri Schottky diyot veya P-MOSFET)
- [ ] Aşırı akım koruması var (sigorta veya PTC); değeri nominal akımın üstünde, kablo/iz kapasitesinin altında
- [ ] Geçici gerilime karşı TVS diyot: VRWM ≥ en yüksek normal giriş gerilimi, kenetleme gerilimi (VC) ≤ korunan devrenin mutlak maksimum değeri
- [ ] Hot-plug riski değerlendirildi: uzun kablo endüktansı + düşük ESR'li seramik giriş kapasitörü gerilim sıçraması üretebilir
- [ ] Sigorta gecikmeli tip; I²t değeri açılıştaki inrush'a göre kontrol edildi
- [ ] P-MOSFET ters koruma kullanıldıysa gate–source Zener ile korunuyor
- [ ] PTC kullanıldıysa en yüksek ortam sıcaklığındaki tutma akımı yük akımının üstünde

## 3. Regülatörler

> İlk 9 madde genel regülatör kontrolleridir; son 10 madde anahtarlamalı regülatör (buck, boost, ters buck-boost) tasarımı içindir ([Anahtarlamalı regülatör tasarımı](/Elektronik/Konular/anahtarlamali-regulator-tasarimi/ozet.md)).

- [ ] **LDO dropout:** en düşük giriş geriliminde Vin − Vout ≥ dropout (tüm sıcaklık ve yük aralığında)
- [ ] **LDO ısı:** P = (Vin − Vout) × I_yük; Tj = Ta + P × θJA < Tj_max (marjlı)
- [ ] **LDO kararlılık:** çıkış kapasitörünün tipi ve ESR aralığı datasheet'e uygun (bazı LDO'lar düşük ESR'li seramikle kararsızdır)
- [ ] **Buck:** indüktör doyma akımı > tepe akım; giriş kapasitörünün RMS akım derecesi yeterli
- [ ] **Seramik kapasitör DC bias:** yüksek değerli, küçük paketli MLCC'ler çalışma geriliminde nominal kapasitesinin büyük kısmını kaybedebilir; efektif değer üretici eğrisinden kontrol edildi
- [ ] Enable / power-good sıralaması gerekiyorsa tanımlı
- [ ] Analog besleme dijitalden ayrılması gerekiyor mu? (ferrit boncuk veya LC filtre)
- [ ] Güç bütçesi tablosu şematikte; her rayın gerilimi ve en yüksek akımı yazılı
- [ ] Hassas analog varsa buck'ın hafif yük modu (PFM) değerlendirildi; gerekirse FPWM
- [ ] **Topoloji ve aralık:** topoloji `V_in` aralığına göre seçildi (buck: `V_in > V_out`; boost: `V_in,maks < V_out`; aralık `V_out`'u kesiyorsa ya da çıkış negatifse ters buck-boost, SEPIC veya 4 anahtarlı buck-boost); `D = V_out/(V_in·η)` en düşük ve en yüksek `V_in`'de hesaplandı; `V_in,maks ≤ V_out/(f_s·t_on,min)` sağlanıyor
- [ ] **İndüktör:** `L = V_out·(V_in,maks − V_out)/(ΔI_L·V_in,maks·f_s)` ile `ΔI_L` ≈ 0,2–0,4·I_out (boost'ta `I_L,ort`) seçildi; `I_sat ≥ I_LIM,maks` (%10 marjla) ve kısa devrede algılama gecikmesi aşımı `V_in,maks·t_gecikme/L` eklenince de doymuyor; `I_rms` (ısınma) ve DCR kaybı (`I_rms²·DCR`) hesaplandı
- [ ] **Çıkış kapasitörü:** seramiğin DC bias sonrası **etkin** değeri kullanıldı; `ΔV = ΔI_L/(8·f_s·C) + ESR·ΔI_L` hesaplandı; yük bırakma aşımı (`C_out ≥ L·ΔI²/(2·V_out·V_aşım)`) sınırı sağlanıyor; boost'ta ESR kısmı `ESR·I_pk` ile ve çıkış ripple akımı `I_out·√(D/(1−D))` kapasitörün akım derecesiyle karşılaştırıldı
- [ ] **Giriş kapasitörü:** buck'ta `I_Cin,rms = I_out·√(D·(1−D))` (en kötü `I_out/2`) kapasitörün ripple akımı derecesinin altında; IC pinlerine bitişik HF seramik (0,1–0,47 µF) ve bulk kapasitör birlikte var; `ΔV_in = I_out·D·(1−D)/(f_s·C_in)` etkin kapasiteyle hesaplandı
- [ ] **Kontrol döngüsü:** `f_c` ≈ `f_s/10`, faz payı ≥ 45° (hedef 50–60°), GM ≥ 6 dB; `C_out` ±%20 ve hafif yükte de kontrol edilecek; boost ve ters buck-boost'ta `f_c ≤ f_RHPZ/5` (en kötü durum: tam yük, düşük `V_in`); FB bölücüsünün üstünde döngü ölçümü için enjeksiyon direnci yeri (10–50 Ω) bırakıldı
- [ ] **UVLO, FB ve soft-start:** EN bölücüsüyle `V_on`, `V_off` ve histerezis ayarlandı (histerezis kaynağın yük altındaki çökmesinden büyük); en yüksek `V_in`'de EN pini gerilimi mutlak azami değerin altında; FB bölücü hatası (%1 dirençle ≈ ±%1,7 + `V_ref` toleransı) kabul edilebilir; soft-start inrush akımı `C_out·V_out/t_ss` + yük akımı `I_LIM` altında; pre-bias açılış davranışı datasheet'ten okundu
- [ ] **Akım limiti ve kısa devre:** `I_MAXOUT = I_LIM,min − ΔI_L/2 ≥ I_out,maks`; kısa devre davranışı (foldback ya da hiccup) datasheet'ten okundu ve ölçüldü; boost'ta çıkış kısa devresini IC kesemez ve kapalıyken `V_out ≈ V_in − V_F` olur: giriş sigortası/akım sınırı ya da yük anahtarı (true-shutdown) var
- [ ] **Giriş hattı etkileşimi:** hot-plug tepesi gerçek adaptör ve kabloyla ölçüldü; korumasız girişte `V_in,nom`'un 2,5×'u (AN88: 24 V girişte 57,2 V ölçüldü) IC'nin mutlak azami gerilimi ve kapasitör derecesinin altında, değilse damper (Al-elektrolitik, `C_D ≥ 4·C_in`) ya da TVS var; giriş filtresi varsa `Z_out` tepesi ≤ `|R_in|/2` (`|R_in| = V_in²/P_in`, ≥ 6 dB marj)
- [ ] **Kayıp, ısı ve hafif yük:** kayıp bütçesi (iletim + anahtarlama + sabit) çıkarıldı; `T_j = T_a + P·θ_JA` marjlı; hafif yükte verimi sabit kayıp tabanı belirler: 10 mA ile tam yük arasındaki yük aralığı değerlendirildi; PFM/FPWM seçimi hassas analog ve işitilebilir ses (< 20 kHz) açısından yapıldı
- [ ] **Yerleşim:** sıcak döngü (C_in–HS–LS) en küçük; HF C_in VIN ve GND pinlerine bitişik, aynı katmanda, via'sız; SW bakırı minimum; FB bölücü IC'ye bitişik ve FB izi SW ile bobinden uzak; kesintisiz GND düzlemi; IC ısı pedi altında termal via; bobinin altında ve yakınında hassas iz yok

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
- [ ] Sinyal bandı (B), f_s ve filtre f_c'si şematikte not edildi; k·f_s ± B bölgelerindeki bozucular hata bütçesinin (ör. ½ LSB) altına iniyor
- [ ] Anti-aliasing RC'si ADC pinine bitişik; 2. kademe filtre için yer (DNP) bırakıldı
- [ ] Filtresiz, düşük f_s yok; şebeke için tam periyotluk ortalama planlandı (50 Hz → 20 ms; 60 Hz pazarı da varsa 100 ms)
- [ ] 1 kHz, f_s'nin tam katı değil (RF bağışıklık testindeki 1 kHz AM DC'ye katlanmaz; ör. f_s = 1,2 kHz)
- [ ] Firmware notu: ADC timer ile tetikleniyor; seyreltme ve loglama öncesinde ortalama var
- [ ] ADC referansının kararlılığı ve gürültüsü ölçüm hassasiyetine yetiyor; mümkünse oransal (ratiometric) ölçüm tercih edildi
- [ ] Dış dünyaya açılan sensör girişlerinde seri direnç + kenetleme (clamp) koruması var
- [ ] Gerilim bölücüde empedans ↔ akım tüketimi ↔ ADC yüklemesi dengelendi
- [ ] Yüksek kazançlı DC yolda ofset × kazanç hesaplandı; gerekiyorsa zero-drift op-amp
- [ ] Kazanç ve köprü dirençleri yan yana, ısı kaynaklarından uzak (layout notu)
- [ ] INA'nın REF pini düşük empedanslı (tamponlu) bir kaynaktan sürülüyor
- [ ] Köprü/sensör beslemesi sensör datasheet'ine göre kararlı (duyarlılık beslemeye bağlı)
- [ ] Op-amp/INA girişlerinde RF'e karşı küçük RC (C0G) var
- [ ] Kenetleme diyotlarının arıza akımı besleme rayını yükseltmiyor
- [ ] Her ADC ölçümü için hata bütçesi hesaplandı ve gereken etkin bit sayısıyla karşılaştırıldı
- [ ] VDDA referans olarak kullanılıyorsa VREFINT ile besleme düzeltmesi planlandı (veya harici referans / oransal ölçüm)
- [ ] Pin kapasitörü yük paylaşımı kuralına göre (12 bit için ≥ ~100 nF); yüksek kaynak direncinde örnekleme hızı buna göre düşük
- [ ] Pil/besleme bölücüsünün sürekli akımı pil ömrüne göre kontrol edildi; MΩ'luk bölücü yerine gerekirse anahtarlı bölücü
- [ ] Firmware: açılışta ADC kalibrasyonu; kanal değişiminde ilk örnek atılıyor
- [ ] Firmware: her kanalda makul aralık kontrolü; aralık dışı ölçüm arıza olarak raporlanıyor
- [ ] 4–20 mA girişlerinde şant gücü ve koruması yanlış bağlantıya (ör. 24 V) göre; NAMUR arıza sınırları uygulanıyor
- [ ] Şebeke potansiyelindeki ölçümlerde yüksek gerilim direnç dizisi; debug için izolasyon planı

## 7. Dijital arayüzler

- [ ] I²C pull-up değeri hız ve hat kapasitansına göre seçildi (tipik 2,2 kΩ – 10 kΩ); hatta yalnızca bir set pull-up var
- [ ] Farklı gerilim domainleri arasında seviye dönüştürücü var
- [ ] UART bağlantısı çaprazlandı: TX → RX, RX → TX
- [ ] SPI CS hatlarında pull-up var (boot sırasında hiçbir slave seçili olmasın)
- [ ] Hızlı kenarlı hatlarda seri sonlandırma direnci yeri bırakıldı (tipik 22–33 Ω)
- [ ] RS-485: 120 Ω sonlandırma yalnızca uç cihazlarda (jumper/DNP); bias hesabı ile boşta fark ≥ 200 mV; GND referansı veya yalıtım
- [ ] RS-485 DE/RE kontrolü firmware'de son stop bitinden sonra bırakılıyor
- [ ] UART'ta saat kaynağı sıcaklık aralığında yeterli (kristal veya kalibrasyon); RX'te pull-up
- [ ] I²C cihaz adresleri listelendi; hat uzunluğu ve kapasitansı kart içiyle sınırlı
- [ ] Çok sayıda SPI slave'inde kod çözücü kullanıldıysa enable'ı açılışta kapalı
- [ ] Debug UART başlığı veya test pedi var
- [ ] Her dijital bağlantıda sürücünün V_OH(min) / V_OL(max) değerleri ile alıcının V_IH(min) / V_IL(max) değerleri datasheet'ten (yük akımı, besleme ve sıcaklık uçlarında) karşılaştırıldı; iki gürültü marjı da pozitif ve yeterli
- [ ] Yavaş veya gürültülü kenarlı girişler (sıfır geçiş, optokuplör çıkışı, mekanik kontak, uzun kablo) histerezisli (Schmitt-trigger) girişe veya karşılaştırıcıya bağlandı
- [ ] Açık-drenaj / açık-kolektör hatlarda (I²C, alarm, interrupt, kablolu-AND) pull-up, alt sınır (`R ≥ (V_DD − V_OL) / I_OL`) ile yükselme süresinden gelen üst sınır arasında seçildi; hatta tek set pull-up var

## 8. Konnektörler ve dış dünya

- [ ] Dışarı açılan her hatta ESD koruması var
- [ ] Konnektör pin sırası mekanik çizim ve karşı taraf ile karşılaştırıldı; ters takılmaya karşı önlem var
- [ ] Kabloyla gelen hatlarda EMC filtresi gerekip gerekmediği değerlendirildi

## 9. Test ve üretim

- [ ] Test noktaları var: tüm güç rayları, GND, kritik sinyaller
- [ ] Programlama ve kalibrasyon arayüzü üretimde erişilebilir
- [ ] Durum LED'i var (güç + MCU kontrollü)
- [ ] BOM: tüm parçalar aktif üretimde, stokta ve mümkünse ikinci kaynaklı
- [ ] Test noktaları tek yüzde, Ø ≥ 1 mm; programlama pogo pedleri; kalibrasyon arayüzü kutu kapalıyken erişilebilir
- [ ] Firmware self-test: raylar, ısıtıcı/yük akımı, sensör açık/kısa devre

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

## 12. Yük sürme

> Logic-level MOSFET ve gate pull-down maddeleri bölüm 5'te, flyback diyotu bölüm 10'da.

- [ ] MCU'nun pin başına ve toplam port akımı sınırları aşılmıyor
- [ ] BJT'ler doyumda (Ib ≈ Ic/10); her anahtarın kaybı ve sıcaklığı hesaplandı
- [ ] ULN2003 tipi dizilerde COM pini röle beslemesine bağlı
- [ ] Röle kontak değeri yük türüne (AC/DC, endüktif) uygun; rölenin enerjili/enerjisiz çalışma şekli bilinçli seçildi
- [ ] Buzzer tipi doğru sürülüyor (transducer → rezonans frekansında PWM); ses seviyesi standarda göre doğrulanacak
- [ ] Solenoid/kilit çıkışlarında firmware zaman aşımı ve kablo tarafında TVS var

## 13. PCB layout ve üretim

> Bu bölüm layout aşamasında ve üretim dosyaları hazırlanırken işaretlenir.

- [ ] Mekanik (kutu, konnektör, buton, montaj delikleri) yerleşimden önce sabitlendi
- [ ] Güç izleri akım ve gerilim düşümüne göre hesaplandı; net sınıfları tanımlı
- [ ] Yüksek akım dönüşleri (ısıtıcı, röle, buck girişi) analog ölçüm bölgesinin altından geçmiyor
- [ ] Yüksek gerilim/şebeke ve Ex gereksinimleri için clearance ve creepage standarttan alındı
- [ ] Küçük pasiflerin pedinde açık via yok; alt pedli parçalarda termal via dizisi
- [ ] Bağlanmamış bakır ada yok; DRC sıfır hata; Gerber görüntüleyicide kontrol edildi
- [ ] Tasarım kuralları üreticinin kabiliyetinin bir kademe üstünde; kaplama türü parçalara uygun
- [ ] Fiducial'lar: en az 3, asimetrik, çevresi boş
- [ ] QFN termal pedi pasta penceresi %50–80
- [ ] Üretim paketi tek revizyon adıyla; pick & place dönüş açısı dizgi firmasıyla teyit edildi

## 14. Şebeke ve yalıtım

> Şebekeye bağlı ürünlerde işaretlenir. İlk 10 madde her şebekeli ürün içindir ([Şebeke güvenliği ve yalıtım](/Elektronik/Konular/sebeke-guvenligi-ve-yalitim/ozet.md)); sonraki 9 madde triyaklı faz kontrolü (dimmer) içeren ürünler içindir ([Triyak ve faz kontrolü](/Elektronik/Konular/triyak-ve-faz-kontrolu/ozet.md)); son 10 madde şebekeden beslenen güç kaynağı içeren ürünler içindir: ilk 3'ü kapasitif düşürücü, sonraki 7'si flyback için ([Şebekeli güç kaynakları](/Elektronik/Konular/sebekeli-guc-kaynaklari/ozet.md)).

- [ ] Şebekeye bağlı bölge şematikte ve kartta çizgiyle işaretli; yalıtım türü (temel/çift/güçlendirilmiş), aşırı gerilim kategorisi ve kirlilik derecesi şematik notunda yazılı
- [ ] Clearance ve creepage standart tablosundan (çalışma gerilimi, aşırı gerilim kategorisi, kirlilik derecesi, malzeme grubu) alındı; güçlendirilmiş yalıtımda bir üst darbe basamağı ve ikiye katlanmış creepage uygulandı
- [ ] Şebeke girişinde sigorta var: gecikmeli (T), 250 V AC, kırma kapasitesi hattın kısa devre akımının üstünde (H); I²t açılış inrush'ına göre kontrol edildi
- [ ] Hat–nötr arası kapasitörler X2, hat/nötr–toprak ve primer–sekonder kapasitörleri Y sınıfında ve sertifikalı (IEC 60384-14); güçlendirilmiş bariyeri köprüleyen kapasitör Y1 (veya seri Y2)
- [ ] X kapasitörün deşarj direnci var; şebeke çekilince gerilim ürün standardının süresi içinde güvenli seviyeye iniyor (τ = R·C hesaplandı)
- [ ] Y kapasitörlerin kaçak akımı I = 2π·f·C·V ile en kötü hat gerilimi ve kapasitör toleransında hesaplandı; dokunma akımı sınırının altında
- [ ] Class I üründe koruma toprağı (PE) dokunulabilir iletkenlere düşük dirençle bağlı; PE hattında sigorta veya anahtar yok
- [ ] Varistör (MOV) sigortanın arkasında; ömür sonu kısa devre için sigorta veya termal koruma var
- [ ] İnrush sınırlayıcı (NTC) varsa enerji (½·C·V²) ve sıcakken kayıp kontrol edildi
- [ ] İlk enerjilendirme ve ölçüm planı yazıldı: izolasyon trafosu, akım sınırlama (seri ampul veya akım sınırlı kaynak), diferansiyel prob
- [ ] Triyak V_DRM ≥ 600 V (230 V hat); I_TSM soğuk lamba akımının ≥ 2 katı; kayıp hesaplandı ve T_j ≤ 110 °C (ortam 50 °C) sağlanıyor ya da soğutucu seçildi
- [ ] Tetik devresi QI/QIII'e göre kuruldu: rastgele faz (non-zero-cross) optotriyak; R_g ≥ V_tepe / I_TSM(opto); opto LED akımı ≥ 2 × I_FT
- [ ] Optotriyakın V_DRM marjı (264 V hatta tepe 373 V için), V_IORM/V_IOTM ve kriper/klirensi şebeke–SELV bariyeri gereksinimine göre kontrol edildi
- [ ] Mandallama (I_L) ve tutma (I_H) akımı en küçük yük akımına göre kontrol edildi; en küçük yük, kapı darbe genişliği ve gerekirse aktif yük belirlendi
- [ ] Snubber kaçak akımı (I = 2π·f·C·V), yükte oluşan hayalet gerilim ve direnç gücü (≤ 2·C·V²·f) hesaplandı; LED yükü destekleniyorsa C küçültüldü
- [ ] Sıfır geçiş algılamada eşik, darbe genişliği (t_w) ve opto gecikmesi ölçüldü; tetik gecikmesi darbenin yükselen kenarına göre t_w kadar düzeltildi; 50 ve 60 Hz'de doğrulandı
- [ ] Fail-safe: sıfır geçiş yoksa tetik yok; kapı darbesi donanım zamanlayıcıyla sabit genişlikte; açılışta ve watchdog sonrası kapalı başlıyor; geçersiz giriş (frekans, güç, darbe genişliği) kapalıya gidiyor
- [ ] İki telli (şebeke potansiyelinde yüzen) elektroniğe debugger veya ölçüm yalnızca izolasyonla bağlanıyor; soğutucu/sekme (MT2) dokunulabilir değil veya yalıtımlı
- [ ] Seri filtre indüktörünün doyma akımı yük tepe akımının üstünde; indüktör–snubber rezonansı (f₀, Z₀) hesaplandı ve sönümleme (F = R/(2·Z₀)) kontrol edildi
- [ ] Kapasitif düşürücü yalnızca dokunulabilir iletken parçası olmayan, tamamen kapalı ve yalıtkan gövdeli üründe kullanıldı (şematikte "⚠ tüm devre şebeke potansiyelinde" notu; bağlayıcı, düğme, anten, programlama portu yok); aksi hâlde flyback ya da sertifikalı modül seçildi
- [ ] Kapasitif düşürücünün yük akımı en düşük ortalama akıma göre sınırlandı (207 V, C −%20: 4·f·C·(V_tepe − V_on)) ve %10 marj bırakıldı; Zener gücü (V_Z·I_ort,maks) ve R1 gücü (I_rms²·R1, en kötü hat ve C) hesaplandı
- [ ] Dropper C1 X2 sınıfı; paralel boşaltma direnci R_b ≤ τ/C ile seçildi ve sürekli kaybı hesaplandı; R1'in açılış darbesi (tepe akım (V_tepe − V_on)/R1, enerji ½·C·(V_tepe − V_on)²) direnç, köprü (I_FSM) ve Zener için karşılandı
- [ ] Flyback girişi: P_in = P_out/η, bulk 2–3 µF/W; V_DC,min en kötü durumda (düşük hat, C −%20, tam yük) hesaplandı ve şematik notuna yazıldı; V_DC,maks = √2·V_hat,maks ile bulk ve köprü gerilim marjı kontrol edildi
- [ ] Flyback sarım oranı: V_RO = n·(V_o + V_F), D_maks ≤ 0,45–0,5; L_m DCM sınırının ≈ %10 altında seçildi (L_m toleransı dahil); I_pk, OCP eşiği (≈ 1,2·I_pk) ve trafo doyma akımı (> OCP eşiği) hesaplandı
- [ ] MOSFET V_DSS ≥ (V_DC,maks + V_sn)/0,9 (sürekli ≤ %80 önerisi de kontrol edildi); çıkış diyodu V_RRM > 1,3·V_D ve I_F > 1,5·I_D,rms; çıkış kapasitörünün ripple akımı ve ESR'si hesaplandı
- [ ] RCD clamp: V_sn = 2–2,5·V_RO, P_sn = ½·L_lk·I_pk²·f_s·V_sn/(V_sn − V_RO), R_sn gücü (≥ 2× marj), C_sn ve ultra hızlı clamp diyodu (V_RRM ≥ V_DSS) hesaplandı; L_lk trafo şartnamesinde üst sınırla belirtildi ve ölçüldü
- [ ] Trafo çizimi güvenlik belgesi olarak tamamlandı: L_m (±%), L_lk üst sınırı, doyma akımı, sarım sayıları, pin numarası ve nokta (polarite), güçlendirilmiş yalıtım (TIW/margin bant, 3000 Vac, kriper/klirens); bariyer (T1, opto, Y1) şematikte işaretli
- [ ] Geri besleme: TL431 bölücüsünün toleransı (V_ref, I_ref·R1, direnç) hesaplandı; katot akımı ≥ I_min (R_bias); opto akımı CTR_min ve yaşlanmayla boyutlandı; kararlılık CTR_min/CTR_maks, hat ve yük uçlarında ölçülecek; geri besleme yolu açık devre olursa çıkışı sınırlayan OVP (aux sargı ya da ikincil) var
- [ ] Korumalar ve bekleme: OCP (LEB dahil), hiccup, OTP, brown-out ve soft-start davranışı tanımlı; X2 deşarj ve start-up kayıpları dahil yüksüz giriş gücü bütçesi çıkarıldı (dış güç kaynağında ≤ 0,100 W; ürün grubuna göre yönetmeliği kontrol et)

## 15. Kapanış

- [ ] Şematik bu listeyle ikinci bir göz tarafından (kişi veya Claude) review edildi
- [ ] Bu tasarımdan çıkan dersler [hatalar-dersler.md](/Elektronik/Sematik-Tasarim/hatalar-dersler.md) dosyasına işlendi

## Sürüm geçmişi

| Sürüm | Tarih | Değişiklik |
|---|---|---|
| v1.8 | 2026-11-20 | "Anahtarlamalı regülatör tasarımı" dersinden 10 madde (bölüm 3, Regülatörler) |
| v1.7 | 2026-11-19 | "Şebeke güvenliği ve yalıtım" (10 madde), "Triyak ve faz kontrolü" (9 madde) ve "Şebekeli güç kaynakları" (10 madde) derslerinden yeni bölüm 14 (Şebeke ve yalıtım); Kapanış bölüm 15 oldu |
| v1.6 | 2026-11-18 | "MIT 6.002 Ders 4–5" notlarından 3 madde (bölüm 7: seviye uyumu ve marj, histerezis, açık-drenaj pull-up) |
| v1.5 | 2026-10-30 | "ADC ile ölçüm" konusundan 8 madde (bölüm 6) |
| v1.4 | 2026-10-16 | Şematik ve PCB konularından (7 ders): bölüm 1, 2, 3, 6, 7, 9'a maddeler; yeni bölüm 12 (Yük sürme) ve 13 (PCB layout ve üretim); Kapanış bölüm 14 oldu |
| v1.3 | 2026-10-14 | "Aliasing ve anti-aliasing filtresi" konusundan 5 madde (bölüm 6) |
| v1.2 | 2026-10-12 | Komponent ve EMC derslerinden maddeler: bölüm 5'e 6 madde, yeni bölüm 10 (Pasif komponentler) ve 11 (EMC) |
| v1.1 | 2026-10-12 | "Güç ve decoupling" konusundan 4 madde eklendi (bölüm 4) |
| v1 | 2026-10-09 | İlk sürüm |
