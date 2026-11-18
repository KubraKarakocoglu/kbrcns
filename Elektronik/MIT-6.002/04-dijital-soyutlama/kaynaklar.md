# Kaynaklar · MIT 6.002 Ders 4: Dijital soyutlama

| Tür | Kaynak | Bölüm / Dakika | Not |
|---|---|---|---|
| Ders slaytı | [MIT OCW 6.002, Ders 4: The Digital Abstraction (6002_l4)](https://www.ocw.mit.edu/courses/6-002-circuits-and-electronics-spring-2007/resources/6002_l4/) | 20 slayt | **Ana kaynak.** Agarwal ve Lang, CC BY-NC-SA 4.0. PDF repoya girmez, `Yerel/` klasöründe durur. Slayt altbilgisi "Fall 2000"; iki baskı hatası var (slayt 12 ve 20, bkz. [ozet.md](ozet.md)) |
| Ders sayfası | [MIT OCW 6.002, Lecture Notes](https://www.ocw.mit.edu/courses/6-002-circuits-and-electronics-spring-2007/pages/lecture-notes/) · [ders ana sayfası](https://www.ocw.mit.edu/courses/6-002-circuits-and-electronics-spring-2007) | Ders 1–5 | Sayfa şunu yazar: "This section contains lecture notes from the Fall 2000 version of the course." Başlıklar: 1 Introduction and lumped abstraction · 2 Basic circuit analysis method · 3 Superposition, Thévenin and Norton · 4 The digital abstraction · 5 Inside the digital gate |
| Kitap | Anant Agarwal, Jeffrey Lang – *Foundations of Analog and Digital Electronic Circuits* | Bölüm 5 | Slayt 3'ün önerdiği okuma ("Reading: Chapter 5") |
| Datasheet | onsemi **MM74HC00** (dörtlü 2 girişli NAND) | "Electrical characteristics" | 74HC seviyeleri: V_IH = 3,15 V, V_IL = 1,35 V (V_CC = 4,5 V, 25 °C); V_OH / V_OL 20 µA ve 4 mA için. onsemi.com'da parça numarasıyla ara |
| Datasheet | TI **SN74HCT00** | "Electrical characteristics" | TTL uyumlu giriş: V_IH = 2 V, V_IL = 0,8 V (V_CC = 4,5–5,5 V); 4 mA'de V_OH = 3,84 V, V_OL = 0,33 V (−40…85 °C). ti.com'da parça numarasıyla ara |
| Web | [Euresys: TTL and LVTTL levels](https://documentation.euresys.com/Products/Coaxlink/Coaxlink_10_4/Content/03_Using_Coaxlink/application-notes/connecting-ttl-to-isolated-ports/TTL_and_LVTTL_levels.htm) | Seviye tablosu | 5 V TTL ve 3,3 V LVTTL için aynı dört sayı: 0,8 / 2,0 / 0,4 / 2,4 V. Sayfa bir standart numarası vermiyor |
| Web | [Microchip: 3.3V LVTTL](https://onlinedocs.microchip.com/oxy/GUID-DAFD9EF4-C157-47D1-BD7C-1934D43D152B-en-US-1/GUID-4C636B30-CDDD-43C8-ACFD-FA6F2A2C36CC.html) | Seviye tablosu | LVTTL: V_IL ≤ 0,8 V, V_IH ≥ 2,0 V, V_OL ≤ 0,4 V, V_OH ≥ 2,4 V (I_OL = 24 mA, I_OH = −24 mA koşulunda) |
| Datasheet | Kullandığın her dijital IC ve MCU | "Electrical characteristics" / "I/O characteristics" | **Son söz datasheet'indir:** V_IH / V_IL çoğu zaman V_DD oranı, V_OH / V_OL belirli bir yük akımı için verilir |
| Ders | [Ders 5: Dijital kapının içi](../05-dijital-kapinin-ici/ozet.md) | Tamamı | Bu dersin devamı: kapının içi, anahtar modeli, MOSFET |
| Ders | [Haberleşme arayüzleri](../../Konular/haberlesme-arayuzleri/ozet.md) | Bölüm 6 | 3,3 V ↔ 5 V seviye çevirme |
| Ders | [Mikrodenetleyici donanımı](../../Komponentler/05-mikrodenetleyici-donanimi/ozet.md) | Bölüm 6 (GPIO) | Pin akım limitleri, 5 V tolerans, kullanılmayan pinler |
| Ders | [Direnç](../../Komponentler/01-direnc/ozet.md) | Bölüm 5.1 | Pull-up / pull-down değer seçimi |

> **Atıf (OCW'nin istediği biçim):** Anant Agarwal and Jeffrey Lang, course materials for 6.002 Circuits and Electronics, Spring 2007. MIT OpenCourseWare (http://ocw.mit.edu/), Massachusetts Institute of Technology. Lisans: [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/).
>
> **Doğrulama notu:** Aile tablosundaki sayılar 2026-11-18'de yukarıdaki kaynaklarla karşılaştırıldı. Tasarımda her zaman kendi parçanın güncel datasheet'ini kullan.
