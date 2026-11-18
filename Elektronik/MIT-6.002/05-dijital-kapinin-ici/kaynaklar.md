# Kaynaklar · MIT 6.002 Ders 5: Dijital kapının içi

| Tür | Kaynak | Bölüm / Dakika | Not |
|---|---|---|---|
| Ders slaytı | [MIT OCW 6.002, Ders 5: Inside the Digital Gate (6002_l5)](https://www.ocw.mit.edu/courses/6-002-circuits-and-electronics-spring-2007/resources/6002_l5/) | 20 slayt | **Ana kaynak.** Agarwal ve Lang, CC BY-NC-SA 4.0. PDF repoya girmez, `Yerel/` klasöründe durur. Slayt altbilgisi "Fall 2000"; slayt 8'de bir baskı hatası var (bkz. [ozet.md](ozet.md)) |
| Ders sayfası | [MIT OCW 6.002, Lecture Notes](https://www.ocw.mit.edu/courses/6-002-circuits-and-electronics-spring-2007/pages/lecture-notes/) · [ders ana sayfası](https://www.ocw.mit.edu/courses/6-002-circuits-and-electronics-spring-2007) | Ders 1–5 | Sayfa şunu yazar: "This section contains lecture notes from the Fall 2000 version of the course." Başlıklar: 1 Introduction and lumped abstraction · 2 Basic circuit analysis method · 3 Superposition, Thévenin and Norton · 4 The digital abstraction · 5 Inside the digital gate |
| Kitap | Anant Agarwal, Jeffrey Lang – *Foundations of Analog and Digital Electronic Circuits* | MOSFET ve dijital kapılar bölümleri | Dersin ders kitabı (Ders 4 slaytı Bölüm 5'i önerir) |
| Spesifikasyon | NXP **UM10204** – I²C-bus specification | Pull-up hesabı (R_p) | `R_min = (V_DD − V_OL) / I_OL`, `R_max = t_r / (0,8473·C_b)`; bu notta 3 mA / 0,4 V değerleri kullanıldı. nxp.com'da numarayla ara |
| Datasheet | Kullandığın MOSFET'in datasheet'i | "Electrical characteristics" | `V_GS(th)` ile `R_DS(on)`'un **hangi V_GS'te** verildiğine bak; gövde diyotu parametreleri |
| Datasheet | Kullandığın MCU | "I/O characteristics" ve pin tablosu | Açık-drenaj modu, 5 V tolerans (FT), `V_OL @ I_OL`, histerezis |
| Ders | [Ders 4: Dijital soyutlama](../04-dijital-soyutlama/ozet.md) | Tamamı | Bu dersin öncesi: eşikler, marj, statik disiplin, Boole |
| Ders | [MOSFET, transistör ve yük sürme](../../Konular/mosfet-transistor-ve-yuk-surme/ozet.md) | Bölüm 3–4 | MOSFET seçimi (logic-level), gate direnci ve pull-down |
| Ders | [Haberleşme arayüzleri](../../Konular/haberlesme-arayuzleri/ozet.md) | Bölüm 4 ve 6 | I²C pull-up, BSS138 tipi seviye çevirme |
| Ders | [Direnç](../../Komponentler/01-direnc/ozet.md) | Bölüm 5.1 | Pull-up değer tablosu ve I²C hesabı |
| Ders | [Mikrodenetleyici donanımı](../../Komponentler/05-mikrodenetleyici-donanimi/ozet.md) | Bölüm 6 (GPIO) | 5 V tolerans (açık savak modu), pin akım limitleri |

> **Atıf (OCW'nin istediği biçim):** Anant Agarwal and Jeffrey Lang, course materials for 6.002 Circuits and Electronics, Spring 2007. MIT OpenCourseWare (http://ocw.mit.edu/), Massachusetts Institute of Technology. Lisans: [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/).
>
> **Doğrulama notu:** Bölüm 8–10'daki hesaplar 2026-11-18'de ayrıca bir betikle yeniden hesaplandı. Tasarımda her zaman kendi parçanın güncel datasheet'ini kullan.
