# Komponentler

Her komponent dersi `NN-ad/` klasöründe, aynı yapıda:

| Dosya | İçerik |
|---|---|
| `ozet.md` | Hızlı tekrar, formül kartı ve 9 bölüm: temel fizik, türler, datasheet, parazitikler, şematik, PCB, EMC, arıza modları, sözlük |
| `quiz.md` | Kontrol soruları (hesap soruları dahil), açıklamalı cevap anahtarı |
| `kaynaklar.md` | Kullanılan uygulama notları, kitaplar, videolar |

## Ders sırası

| # | Ders | Neden bu sırada |
|---|---|---|
| 01 | Direnç | En temel komponent; güç, tolerans ve parazitik kavramları burada oturur |
| 02 | Kapasitör | Tüm türler ve kullanımlar. Uygulaması: [Güç ve decoupling](../Konular/guc-ve-decoupling/ozet.md) |
| 03 | Bobin (indüktör) | Anahtarlamalı regülatörlerin kalbi; manyetik alan ve doyma |
| 04 | Ferrit boncuk | İndüktöre benzer ama amacı farklı: gürültüyü ısıya çevirmek |
| 05 | Mikrodenetleyici donanımı | Önceki tüm komponentlerin bir araya geldiği yer |

Sonraki adaylar: diyot ve TVS, MOSFET, op-amp, regülatörler (LDO ve buck), konnektörler.

Yeni komponent dersi açmak için:

```powershell
.\scriptler\Yeni-Kayit.ps1 -Tur Komponent -Baslik "MOSFET"
```
