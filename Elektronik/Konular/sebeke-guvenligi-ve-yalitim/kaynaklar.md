# Kaynaklar · Şebeke güvenliği ve yalıtım

| Tür | Kaynak | Bölüm / Dakika | Not |
|---|---|---|---|
| Standart | IEC 60664-1 – *Insulation coordination for equipment within low-voltage supply systems* | Tablo F.1 (darbe gerilimi), F.2 (clearance), F.4 (creepage), yarık genişlikleri | Ücretli; mesafelerin kökü. Elindeki kopyayı `Yerel/` klasöründe tut, repoya koyma |
| Standart | IEC/EN 62368-1 – *Audio/video, information and communication technology equipment* | ES1/ES2 sınıfları, X kapasitör deşarjı, dokunma akımı | Ücretli; güncel baskıyı kontrol et |
| Standart | IEC/EN 60335-1 – *Household and similar electrical appliances* | Tablo 15–16 (darbe ve clearance), dokunma akımı | Ücretli; ev aletleri ve çoğu şebekeli tüketici ürünü |
| Standart | IEC 60384-14 – *Fixed capacitors for electronic equipment: capacitors for suppression of radio interference and connection to the supply mains* | X1/X2/Y1/Y2 sınıfları | Ücretli; kapasitör sertifikasının kaynağı |
| Standart | IEC 60127 – *Miniature fuses* | Kırma kapasitesi (L, H), zaman karakteristikleri | Ücretli; sigorta etiketleri bunu izler |
| Standart | IEC 60479-1 – *Effects of current on human beings and livestock* | Algılama, bırakamama ve fibrilasyon eşikleri | Ücretli; dokunma akımı limitlerinin dayanağı |
| App note | [TI SLUAAR5 – Isolation glossary and reference](https://www.ti.com/document-viewer/lit/html/SLUAAR5/GUID-B1A84E91-DDEE-4C92-A54D-03C5F8DE95DD) | Clearance ve creepage tabloları, güçlendirilmiş yalıtım kuralı, rakım çarpanı | IEC 60664-1'e dayanır; 4000 m'de ×1,29 |
| Üretici notu | [Vishay – Safety capacitors (introris)](https://www.vishay.com/docs/27623/introris.pdf) | X1–X3, Y1–Y4 alt sınıf tablosu | Darbe gerilimleri, "çift/güçlendirilmiş yalıtımı köprüler" |
| Blog | [Knowles – Safety capacitor classes](https://blog.knowlescapacitors.com/blog/safety-capacitor-classes) | X ve Y sınıfları | Arıza modu (X kısa devre, Y açık devre); iki Y2'nin seri kullanımı |
| Blog | [Power Electronic Tips – FAQ on X and Y capacitors](https://www.powerelectronictips.com/faq-on-x-and-y-capacitors/) | X deşarjı | Zaman sabiti ≤ 1 s; 230 V'ta 100 nF için ≈ 5,3 mW bleeder kaybı |
| Blog | [TDK-Lambda – IEC 62368-1 vs 60950-1](https://www.us.lambda.tdk.com/resources/blogs/201806.html) | X kapasitör deşarjı, ES sınıfları, geçiş tarihi | 60950-1: 1 s'de 42,4 V tepe; 62368-1: ≥ 300 nF için 2 s'de 60 V |
| Teknik makale | [Bel Fuse – Power supply safety standards, agencies and marks](https://www.belfuse.com/resource-library/tech-paper/power-supply-safety-standards-agencies-and-marks) | Dokunma akımı, hi-pot, clearance | Class II 0,25 mA; el tipi Class I 0,75 mA; diğer Class I 3,5 mA; 3000/1500 Vrms |
| Teknik not | [UL – Energy sources: ES vs SELV](https://japan.ul.com/wp-content/uploads/sites/27/2014/06/1_techbrief_ESvsSELV.pdf) | ES1 ve SELV limitleri | 30 V rms / 42,4 V tepe / 60 V DC; 0,5 mA rms |
| Tablo | [EMA – PCB clearance and creepage table](https://www.ema-eda.com/ema-resources/blog/pcb-clearance-and-creepage-distance-table/) | 250 V ve 320 V creepage tabloları | PD ve malzeme grubuna göre mm; CTI grupları |
| Blog | [Philip McGaw – Creepage and clearance](https://philipmcgaw.com/creepage-and-clearance/) | EN 60335-1 Tablo 15–16 | 2,5 kV → 1,5 mm; temel/çift-güçlendirilmiş örnek tablosu |
| Makale | [EMSNow – Clearance and creepage rules for PCB assembly](https://emsnow.com/clearance-and-creepage-rules-for-pcb-assembly/) | Yarık ve V-oluk, kaplama | Yarık ≥ 1 mm; kaplamayla clearance azaltmayı bazı standartlar kabul etmez |
| Üretici notu | [PTR Hartmann – Overvoltage categories](https://www.ptr-hartmann.com/know-how/connection-technology/approvals-standards/overvoltage-categories-i-v/) | OVC I–IV tanımları | Tanımlar ve örnekler |
| Bilgi sayfası | [Schurter – Fuse-link knowledge](https://www.schurter.com/en/knowledge/fuse-link) | Kırma kapasitesi, zaman karakteristikleri, I²t | L ve H değerleri; ön-ark I²t seçim kuralı |
| Makale | [Techniques de l'Ingénieur – Electrical hazards](https://www.techniques-ingenieur.fr/en/resources/article/ti674/electrical-safety-testers-r1040/electrical-hazards-1) | Akımın vücuda etkisi | 0,5 mA / ≈ 10 mA / 30 mA (1 s) |
| App note | Microchip AN954 – *Transformerless Power Supplies* | Güvenlik uyarıları | Şebekeli devrede deney için izolasyon trafosu önerisi |
| Datasheet | Kullandığın sigorta, MOV ve X2/Y1/Y2 kapasitör datasheet'i | Anma gerilimi, sertifikalar, darbe dayanımı | **Son söz datasheet ve ürün standardındır** |

## Doğrulama notu

- **Doğrulanan** (en az bir açık kaynakta): clearance 0,5/1,5/3,0/5,5/8,0 mm (1,5/2,5/4,0/6,0/8,0 kV); OVC I–III darbe gerilimleri; creepage 250 V ve 320 V tabloları; güçlendirilmiş yalıtım kuralı (clearance bir basamak, creepage ×2); rakım çarpanı (4000 m ×1,29; 5000 m ×1,48); X/Y sınıfları ve darbe gerilimleri; kaçak akım sınırları (0,25/0,75/3,5 mA); ES1 limitleri; sigorta L/H değerleri; vücut eşikleri.
- **Standart metninden teyit edilmesi gerekenler:** OVC IV için 6 kV (IEC 60664-1 ve tesisat standartlarının tablosundan bilinir, açık kaynakta ayrıca alıntılanmadı); PD3 için 2,5 kV üstü clearance; PD3'te yarık genişliği alt sınırı (PD2: 1 mm); PE bağlantı direncinde ≈ 0,1 Ω (test akımı ve süresi ürün standardına bağlı); Y kapasitörlerin anma AC gerilimi (baskıya ve üreticiye göre değişir).
- **X kapasitör deşarj gereksinimi** kaynaklarda farklı biçimde verilir (zaman sabiti veya "t süre sonra V"). Derste **daha sıkı** olanı (1 s'de 42,4 V tepe → τ ≤ 0,46 s) esas alındı.
- Hesaplanan sayılar (tepe değer, kaçak akım, deşarj zaman sabiti, bleeder kaybı, inrush, seri ampul) bir betikle yeniden hesaplandı; tablolardaki değerler betik çıktısıyla aynıdır.
- Standartlar ücretlidir ve baskıları değişir; ürünün tabi olduğu standardın **güncel** baskısı esastır. Bu notlar sertifikasyon yerine geçmez.
