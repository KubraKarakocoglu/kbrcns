# Donanım Tasarımı Yol Haritası

- **Oluşturma:** 2026-11-20
- **Durum:** Blok 1 tamam (Ders 1–4); Blok 2–6 planlı
- **Bağlantılı:** [Konular](Konular/README.md) · [Komponentler](Komponentler/README.md) · [EMC](EMC/README.md) · [MIT 6.002](MIT-6.002/README.md) · [Şematik kontrol listesi](Sematik-Tasarim/kontrol-listesi.md) · [ilerleme.md](../ilerleme.md)

> Bu dosya donanım derslerinin **sırasını, ön koşullarını ve kapsamını** gösteren haritadır. Hazır dersler bağlantılıdır; **planlı** derslerin kapsamı bir plandır ve ders yazılırken değişebilir. Ders yazıldıkça ilgili satır güncellenir.
>
> **Kapsam dışı:** FPGA, RF ve mikrodalga tasarımı, motor sürücüler, kW düzeyinde güç elektroniği. Ücretli EN/IEC standartlarının metni repoda yoktur: dersler herkese açık kaynaklara dayanır ve her yerde "güncel standardı kontrol et" der.

## ⚡ Hızlı bakış

| Grup | Ders sayısı | Durum |
|---|---|---|
| Donanım serisi (Ders 1–25) | 25 | 4 hazır, 21 planlı |
| Seri öncesi dersler (Komponentler, EMC, Konular, MIT 6.002) | 20 | Hazır |
| **Toplam** | **45** | **24 hazır, 21 planlı** |

Seri 6 bloğa bölünür; **her blok sonunda** geri bildirim istenir ve sonraki blok ona göre ayarlanır:

| Blok | Dersler | Tema | Durum |
|---|---|---|---|
| 1 | 1–4 | Şebeke ve güç dönüşümü | ✅ Tamam |
| 2 | 5–9 | Uygulama blokları: LED, pil, sensör, ses, gaz dedektörü | 🟦 Planlı |
| 3 | 10–13 | Laboratuvar, bring-up, termal, hassas ölçüm | 🟦 Planlı |
| 4 | 14–17 | İleri topraklama, düşük güç, güvenilirlik, sistem tasarımı | 🟦 Planlı |
| 5 | 18–21 | Diyot, izolasyon elemanları, SPICE, filtre ve karşılaştırıcı | 🟦 Planlı |
| 6 | 22–25 | Haberleşme modülleri, standartlar, fonksiyonel güvenlik, üretim | 🟦 Planlı |

## 1. Seri: 25 ders

Simgeler: ✅ hazır (bağlantılı) · 🟦 planlı. "Kontrol listesi" sütunu, dersin maddelerinin işlendiği [şematik kontrol listesi](Sematik-Tasarim/kontrol-listesi.md) bölümünü gösterir; planlı derslerde (—) ders yazılırken belirlenir.

| # | Ders | Blok | Durum | Ön koşul | Kontrol listesi | Planlanan kapsam |
|---|---|---|---|---|---|---|
| 1 | [Şebeke güvenliği ve yalıtım](Konular/sebeke-guvenligi-ve-yalitim/ozet.md) | 1 | ✅ | Direnç, Kapasitör | Bölüm 14 (10 madde) | Clearance ve creepage, X/Y kapasitör, sigorta, PE, güvenli ölçüm |
| 2 | [Triyak ve faz kontrolü](Konular/triyak-ve-faz-kontrolu/ozet.md) | 1 | ✅ | 1 | Bölüm 14 (9 madde) | Triyak, tetik devresi, sıfır geçiş, LED sorunları, testli C zamanlama modülü |
| 3 | [Şebekeli güç kaynakları](Konular/sebekeli-guc-kaynaklari/ozet.md) | 1 | ✅ | 1, Güç katı | Bölüm 14 (10 madde) | Kapasitif düşürücü, izolasyonlu flyback, clamp, TL431 geri besleme, bekleme gücü |
| 4 | [Anahtarlamalı regülatör tasarımı](Konular/anahtarlamali-regulator-tasarimi/ozet.md) | 1 | ✅ | 3, Bobin, Kapasitör, MOSFET | Bölüm 3 (10 madde) | Buck, boost, ters buck-boost; `L` ve `C`, kayıp bütçesi, döngü, hot-plug, yerleşim |
| 5 | LED sürücü | 2 | 🟦 | 2, 4 | — | Sabit akım (lineer ve anahtarlamalı), dimleme (PWM, analog), titreme, LED ısısı, seri zincir marjı, açık LED arızası |
| 6 | Pil ve şarj | 2 | 🟦 | 4 | — | Li-ion ve LiFePO4 kimyası, CC-CV şarj, güç yolu, pil koruması, NTC, yakıt göstergesi |
| 7 | Sensör teknolojileri | 2 | 🟦 | Op-amp ve sensör ön ucu, ADC | — | Gaz (pellistor, elektrokimyasal, NDIR, MOS), PIR ve radar, sıcaklık ve nem, akım sensörü; sürüklenme ve kalibrasyon |
| 8 | Ses devreleri ve interkom | 2 | 🟦 | Op-amp, 4 | — | Mikrofon, ses kodeği ve D sınıfı yükselteç, hoparlör, yankı, hat arayüzü, ses gürültüsü ve güç |
| 9 | Yanıcı gaz dedektörü donanımı | 2 | 🟦 | 4, 7 | — | Pellistor köprüsü, ısıtıcı sürme, sıfır ve span, sıcaklık telafisi, alarm çıkışları, sensör hatası tespiti |
| 10 | Laboratuvar ve ölçüm | 3 | 🟦 | 1, Ders 4 (bölüm 16) | — | Osiloskop ve prob, multimetre sınırları, elektronik yük, ölçüm belirsizliği, LISN ve ön-test |
| 11 | Bring-up ve hata ayıklama | 3 | 🟦 | 10, 4 | — | İlk açılış sırası, kısa devre arama, güç rayı sırası, SWD, hata ağacı, ısı kamerası |
| 12 | Termal tasarım | 3 | 🟦 | 4 | — | `θ_JA`, bakır alan ve termal via, kapalı kasa, termal RC modeli, derating |
| 13 | Hassas ölçüm devreleri | 3 | 🟦 | 7, ADC, Op-amp | — | Gerilim referansı, düşük ofset, enstrümantasyon yükselteci, köprü sensörü, hata ve gürültü bütçesi |
| 14 | Sinyal bütünlüğü ve topraklama (ileri) | 4 | 🟦 | EMC 02, PCB yerleşim | — | İletim hattı, sonlandırma, yansıma, çapraz konuşma, dönüş yolu, yıldız ve düzlem topraklama |
| 15 | Düşük güç tasarımı | 4 | 🟦 | 4, 6 | — | Enerji bütçesi, uyku akımı, kaçak akım, regülatör `I_q`, pil ömrü hesabı ve ölçümü |
| 16 | Güvenilirlik ve derating | 4 | 🟦 | 12 | — | Derating kuralları, Arrhenius ve ömür, kapasitör ve LED ömrü, MTBF ve FIT, FMEA temelleri |
| 17 | Gereksinimden blok şemaya | 4 | 🟦 | 1–13 | — | Gereksinim yazımı, güç ve hata bütçeleri, blok şema, komponent seçimi, risk listesi |
| 18 | Diyotlar | 5 | 🟦 | 1 | — | Si, Schottky, Zener, TVS, LED; `V_F`, kaçak, toparlanma, OR-ing, ters polarite |
| 19 | Optokuplör, izolatör, röle ve SSR | 5 | 🟦 | 1, 2, 3 | — | CTR ve yaşlanma, dijital izolatör, röle sürme ve kontak koruma, SSR |
| 20 | SPICE | 5 | 🟦 | 4 | — | LTspice, DC/AC/geçici analiz, parametre taraması, model bulma, buck ve hot-plug benzetimi |
| 21 | Karşılaştırıcı ve filtre devreleri | 5 | 🟦 | Op-amp, Aliasing | — | Histerezis, pencere karşılaştırıcı, Sallen-Key, RC ve LC filtre |
| 22 | USB, CAN ve kablosuz modül donanımı | 6 | 🟦 | Haberleşme, EMC 02 | — | USB (VBUS, CC, ESD), CAN fiziksel katmanı, hazır RF modül yerleşimi (RF tasarımı hariç) |
| 23 | Ürün güvenliği ve standartlar | 6 | 🟦 | 1, EMC 03 | — | CE yapısı, ürün standardı seçimi, test raporu okuma, teknik dosya; Ex ve gaz alarm standartlarına kavramsal giriş |
| 24 | Fonksiyonel güvenlik ve self-test | 6 | 🟦 | 9, 23 | — | Arıza modları, teşhis kapsamı, watchdog, açılış ve çalışma testi, güvenli durum; sertifikasyon yerine geçmez |
| 25 | Üretim süreçleri ve test jigi | 6 | 🟦 | Üretilebilirlik ve test, 11 | — | SMT ve reflow, lehim kusurları, panelizasyon, ICT ve FCT, test noktaları, jig tasarımı, izlenebilirlik |

## 2. Seri öncesi dersler (hazır)

Bunlar serinin temelidir. "Seri ile bağı" sütunu, hangi seri dersinin bu derse yaslandığını gösterir.

| Grup | Ders | Seri ile bağı |
|---|---|---|
| Komponentler | [01 Direnç](Komponentler/01-direnc/ozet.md) | 4 (DCR, bölücü), 5, 13 |
| Komponentler | [02 Kapasitör](Komponentler/02-kapasitor/ozet.md) | 1, 3, 4 (etkin `C`, ripple), 16 |
| Komponentler | [03 Bobin (indüktör)](Komponentler/03-bobin-induktor/ozet.md) | 3, 4, 5 |
| Komponentler | [04 Ferrit boncuk](Komponentler/04-ferrit-boncuk/ozet.md) | 4 (giriş filtresi), 14 |
| Komponentler | [05 Mikrodenetleyici donanımı](Komponentler/05-mikrodenetleyici-donanimi/ozet.md) | 11, 15, 24 |
| EMC | [01 EMC temelleri](EMC/01-emc-temelleri/ozet.md) | 14, 23 |
| EMC | [02 EMC için kart tasarımı](EMC/02-emc-icin-kart-tasarimi/ozet.md) | 4, 14, 22 |
| EMC | [03 EMC testleri ve standartlar](EMC/03-emc-testleri-ve-standartlar/ozet.md) | 10, 23 |
| Konular | [Şematik çizim ve dokümantasyon](Konular/sematik-cizim-ve-dokumantasyon/ozet.md) | 17 |
| Konular | [Güç ve decoupling](Konular/guc-ve-decoupling/ozet.md) | 4, 15 |
| Konular | [Güç katı: koruma ve regülatör seçimi](Konular/guc-kati-koruma-ve-regulator/ozet.md) | 3, 4, 6, 18 |
| Konular | [MOSFET, transistör ve yük sürme](Konular/mosfet-transistor-ve-yuk-surme/ozet.md) | 4, 5, 19 |
| Konular | [Op-amp ve sensör ön ucu](Konular/op-amp-ve-sensor-on-ucu/ozet.md) | 7, 8, 13, 21 |
| Konular | [ADC ile ölçüm: pratik rehber](Konular/adc-ile-olcum/ozet.md) | 7, 13 |
| Konular | [Aliasing ve anti-aliasing filtresi](Konular/aliasing-ve-anti-aliasing-filtresi/ozet.md) | 21 |
| Konular | [Haberleşme arayüzleri](Konular/haberlesme-arayuzleri/ozet.md) | 22 |
| Konular | [PCB yerleşim ve iz çizimi](Konular/pcb-yerlesim-ve-iz-cizimi/ozet.md) | 4, 14 |
| Konular | [Üretilebilirlik ve test için tasarım](Konular/uretilebilirlik-ve-test/ozet.md) | 11, 25 |
| MIT 6.002 | [04 Dijital soyutlama](MIT-6.002/04-dijital-soyutlama/ozet.md) | 21 (eşik, histerezis), 22 |
| MIT 6.002 | [05 Dijital kapının içi](MIT-6.002/05-dijital-kapinin-ici/ozet.md) | 5, 19 (MOSFET anahtar modeli) |

## 3. Ürün tipine göre okuma sırası

Aşağıdaki sıralar, ürün tipinin **gerektirdiği** konulara göre önerilir. Tablo genel örnektir; şirketin gerçek ürün şemaları ve değerleri bu notlara girmez.

| Ürün tipi | Önerilen sıra |
|---|---|
| Gaz dedektörü (pellistor/LEL) | Güç katı → Ders 4 → Op-amp ve sensör ön ucu → ADC ile ölçüm → 7 → 9 → 13 → 24 → 23 → 25 |
| İnterkom, kapı paneli | Güç katı → Ders 4 → Haberleşme arayüzleri → 8 → 14 → 22 → 23 |
| Dimmer (triyaklı) | Ders 1 → 2 → 3 → 19 → 23 |
| Sensörlü LED lamba | Ders 1 → 3 → 4 → 5 → 6 → 7 → 15 |
| Varlık sensörü | 7 → 13 → 15 → 14 → 22 → 23 |

## 4. Kapsam denetimi: konu ve ders eşlemesi

| Konu | Hazır | Planlı |
|---|---|---|
| Şebeke güvenliği, yalıtım, mesafeler | Ders 1 | 23 |
| Faz kontrolü, dimmer | Ders 2 | 19 |
| AC-DC güç kaynakları | Ders 3, Güç katı | — |
| DC-DC dönüştürücüler | Ders 4, Güç katı | 12, 15 |
| LED sürme | MOSFET, Ders 3, Ders 4 | 5 |
| Pil ve şarj | yok | 6, 15 |
| Sensörler | Op-amp ve sensör ön ucu | 7, 9, 13 |
| Hassas analog ve ölçüm | ADC, Aliasing, Op-amp | 13, 21 |
| Ses | yok | 8 |
| Yanıcı gaz dedektörü | Ders 4 (iş yerinde), Güç katı | 9, 24 |
| Haberleşme | Haberleşme arayüzleri, Mikrodenetleyici | 22 |
| Diyot ve koruma | Güç katı (TVS, ters polarite) | 18 |
| İzolasyon elemanları, röle | Ders 1, MOSFET | 19 |
| Termal | Ders 4 (bölüm 7.5) | 12 |
| Güvenilirlik | yok | 16 |
| EMC ve topraklama | EMC 01–03 | 14 |
| Laboratuvar, ölçüm, bring-up | Ders 4 (bölüm 16) | 10, 11 |
| SPICE ve benzetim | yok | 20 |
| Gereksinim ve sistem tasarımı | Şematik çizim ve dokümantasyon | 17 |
| Üretim ve test | Üretilebilirlik ve test | 25 |
| Standartlar, fonksiyonel güvenlik | EMC 03 | 23, 24 |

`yok`: bu konuda hazır ders yok; `—`: ek ders planlı değil. Bir konunun **hazır** sütununda ders olması, konunun tamamen kapandığı anlamına gelmez: ayrıntı için dersin kapsamına bak.

## 5. Her ders nasıl hazırlanır

- **Biçim:** `ozet.md` (hızlı tekrar, formül kartı, benzetmeler, 💼 iş yerinde, şematik, PCB, EMC ve ölçüm bölümleri), `quiz.md` (12 soru; hesap soruları dahil; doğru şıklar eşit dağılır) ve `kaynaklar.md` ("Doğrulama notu" ile).
- **Sayılar:** her ders için hesap betiğiyle üretilir; ayrı bir betik bağımsız yeniden hesaplar; quiz sayıları da ayrıca doğrulanır.
- **Kaynak:** herkese açık uygulama notları, datasheet'ler ve ders kitapları. Kaynakta olmayan değerler **varsayım** olarak işaretlenir. Ücretli standartlar için "güncel standardı kontrol et" notu düşülür.
- **Kontrol listesi:** her dersten çıkan maddeler [kontrol-listesi.md](Sematik-Tasarim/kontrol-listesi.md) dosyasına, dersteki metinle **birebir** aynı işlenir; sürüm numarası artar.
- **Gizlilik:** şirkete ait şematik, değer veya doküman repoya girmez; iş yeri bölümleri genel örnektir.

## 6. Sıradaki adım

Blok 1 tamamlandı. Blok 2 (Ders 5–9: LED sürücü, Pil ve şarj, Sensör teknolojileri, Ses devreleri ve interkom, Yanıcı gaz dedektörü donanımı) için önce Blok 1 hakkında geri bildirim alınır; ardından sırayla yazılır.
