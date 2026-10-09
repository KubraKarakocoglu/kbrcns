# Elektronik Konuları

Konu bazlı özetler. Her konu bir klasör:

| Dosya | İçerik |
|---|---|
| `ozet.md` | Can alıcı bilgiler: kavram, formül, pratik kural, sık hata |
| `quiz.md` | Kontrol soruları (hesap soruları dahil) |
| `kaynaklar.md` | Hangi video / kitap / PDF'in hangi bölümünden |

Yeni konu:

```powershell
.\scriptler\Yeni-Kayit.ps1 -Tur Konu -Baslik "Op-amp temelleri"
```

## Önerilen konu sırası

| # | Konu | Neden bu sırada |
|---|---|---|
| 1 | Güç ve decoupling | Her devrenin temeli; hataların çoğu burada başlar |
| 2 | Pasif komponentlerin gerçek davranışı | ESR, DC bias, tolerans, sıcaklık katsayısı — datasheet okumanın temeli |
| 3 | Op-amp temelleri | Analog sinyal zincirinin merkezi |
| 4 | ADC ve sinyal koşullandırma | Sensörden sayıya giden yol; C tarafıyla birleştiği nokta |
| 5 | Topraklama ve akım dönüş yolları | Gürültü ve EMC sorunlarının kök nedeni |
| 6 | Koruma devreleri | ESD, TVS, ters polarite, aşırı akım |
| 7 | MOSFET ile anahtarlama | Yük sürme, gate sürme, güvenli başlangıç durumu |
| 8 | Haberleşme arayüzleri | UART, I²C, SPI: elektriksel taraf |
| 9 | PCB layout temelleri | Şematiğin fiziksel karşılığı |

> Her konu bittiğinde "Şematik kontrol listesine eklenecekler" bölümünü [kontrol-listesi.md](../Sematik-Tasarim/kontrol-listesi.md) dosyasına işle.
