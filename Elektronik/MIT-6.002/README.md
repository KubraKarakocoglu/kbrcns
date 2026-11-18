# MIT 6.002: Devreler ve Elektronik (Türkçe çalışma notları)

MIT OpenCourseWare **6.002 Circuits and Electronics** (Spring 2007; Anant Agarwal ve Jeffrey Lang) ders slaytlarının Türkçe çalışma notları. Notlar slayt sırasını izler, slayt hatalarını düzeltir ve her derse bir **iş yerinde** bölümü (gerçek parçalar, datasheet değerleri, şematik kontrolleri) ekler.

> **Lisans ve atıf:** Kaynak materyal [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/) lisanslıdır. Bu klasördeki notlar kaynağın **uyarlamasıdır**: Türkçeleştirme, yeniden anlatım, düzeltmeler ve ek örnekler içerir (değişiklik yapılmıştır). Aynı lisansla paylaşılır; ticari kullanım yoktur.
>
> Atıf: *Anant Agarwal and Jeffrey Lang, course materials for 6.002 Circuits and Electronics, Spring 2007. MIT OpenCourseWare (http://ocw.mit.edu/), Massachusetts Institute of Technology.*
>
> **Slayt PDF'leri repoya girmez** (`.gitignore` `*.pdf` dosyalarını dışarıda tutar); kendi bilgisayarında `Yerel/` klasöründe dursun.

## Dersler

| No | Ders | Slayt | Konu |
|---|---|---|---|
| 04 | [Dijital soyutlama](04-dijital-soyutlama/ozet.md) | 20 | Gürültü, iki seviye, yasak bölge, V_OH / V_OL / V_IH / V_IL, gürültü marjı, statik disiplin, Boole mantığı |
| 05 | [Dijital kapının içi](05-dijital-kapinin-ici/ozet.md) | 20 | Anahtar modeli, evirici, NAND / NOR, bileşik kapı, MOSFET (S ve SR modeli), yük direnci seçimi, açık-drenaj |

Numara, OCW'deki ders (Lecture) numarasıdır. Ders 1–3 (Introduction and lumped abstraction · Basic circuit analysis method · Superposition, Thévenin and Norton) bu klasörde yoktur; Ders 4'ün giriş slaytları bunları kısaca hatırlatır. Diğer dersler eklendikçe tabloya girer. OCW'nin ders notları sayfası, notların dersin **Fall 2000 sürümünden** olduğunu belirtir; slayt altbilgilerindeki "Fall 2000" bu yüzdendir.

## İşaretler ve gösterim

| İşaret | Anlamı |
|---|---|
| 💼 | **İş yerinde** bölümü: gerçek parçalar, datasheet değerleri, ürün örnekleri |
| ⚠️ **Slayt hatası** | Slaytta basılı bir hata ve düzeltilmiş hâli |
| `¬X` | X'in tersi (slaytlardaki üst çizgi) |
| `X·Y` · `X + Y` | AND · OR |

## Bu notlar iş yerindeki konularla nasıl bağlanır?

| MIT dersi | Pratikteki karşılığı |
|---|---|
| 4: Dijital soyutlama | Mantık seviyesi uyumu, gürültü marjı, 3,3 V ↔ 5 V: [Haberleşme arayüzleri](../Konular/haberlesme-arayuzleri/ozet.md), [MCU GPIO](../Komponentler/05-mikrodenetleyici-donanimi/ozet.md#6-gpio) |
| 5: Dijital kapının içi | Açık-drenaj çıkış, pull-up hesabı, MOSFET anahtar: [MOSFET ve yük sürme](../Konular/mosfet-transistor-ve-yuk-surme/ozet.md), I²C |

Bu iki dersten çıkan 3 madde [şematik kontrol listesine](../Sematik-Tasarim/kontrol-listesi.md) işlendi (v1.6, bölüm 7).

## Yeni ders ekleme

1. OCW "Lecture Notes" sayfasından PDF'i indir ve `Yerel/` klasörüne koy.
2. `NN-kisa-ad/` klasörü aç (NN = OCW ders numarası) ve üç dosya yaz: `ozet.md`, `quiz.md`, `kaynaklar.md` ([şablonlar](../../sablonlar/)). Mevcut dersleri örnek al: başlık bloğunda kaynak ve lisans satırı, slayt haritası, "Hızlı tekrar", "Cep kartı", slayt sırasıyla bölümler, 💼 iş yerinde bölümü, ⚠️ slayt hataları, "Kendin dene", sözlük.
3. Sayıları ve hesapları bir betikle yeniden hesapla; slayt hatalarını sayfayı görüntü olarak açıp kontrol et (metin çıkarımı üst çizgileri kaybeder).
4. [ilerleme.md](../../ilerleme.md) içindeki "MIT 6.002" tablosuna ve bu dosyadaki tabloya satır ekle.
5. Yeni bir kontrol listesi maddesi çıkarsa [kontrol-listesi.md](../Sematik-Tasarim/kontrol-listesi.md) dosyasına ekle ve sürümü artır.
