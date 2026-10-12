# Script'ler

Tüm komutlar repo kök klasöründen çalıştırılır: `cd $HOME\kbrcns`

## Senkron.ps1

Yerel değişiklikleri commit'ler, diğer bilgisayardaki değişiklikleri alır ve gönderir. Çalışmaya **başlarken** ve **bitirirken** aynı komutu çalıştır.

```powershell
.\scriptler\Senkron.ps1
.\scriptler\Senkron.ps1 -Mesaj "Op-amp konusu özeti eklendi"
```

| Çıkış kodu | Anlamı | Ne yapmalı |
|---|---|---|
| 0 | Başarılı | — |
| 1 | Ön kontrol hatası | Mesajdaki talimatı uygula (git kimliği, yarım işlem...) |
| 2 | Uzak repoya erişilemedi | Değişikliklerin yerel commit'te güvende. İnternet/GitHub erişimi gelince tekrar çalıştır |
| 3 | Çakışma | Rebase otomatik iptal edildi, iş kaybı yok. Çıktıyı Claude'a gönder |
| 4 | Push başarısız | Yerel commit güvende; sonra tekrar dene |
| 9 | Beklenmeyen hata | Çıktıyı Claude'a gönder |

Ne yapmaz: `--force` push, commit edilmemiş işi silme, 50 MB üstü dosyayı commit'e alma.

## Yeni-Kayit.ps1

Şablondan yeni kayıt klasörü oluşturur ve `ilerleme.md` tablosuna satır ekler. Var olan hiçbir dosyanın üzerine yazmaz.

```powershell
.\scriptler\Yeni-Kayit.ps1 -Tur Ders  -Baslik "Değişkenler ve veri tipleri" -Link "https://..."
.\scriptler\Yeni-Kayit.ps1 -Tur Konu  -Baslik "Op-amp temelleri"
.\scriptler\Yeni-Kayit.ps1 -Tur Komponent -Baslik "MOSFET"
.\scriptler\Yeni-Kayit.ps1 -Tur EMC   -Baslik "ESD koruması"
.\scriptler\Yeni-Kayit.ps1 -Tur Proje -Baslik "GPIO buton"
```

| Tür | Oluşan klasör | Dosyalar |
|---|---|---|
| Ders | `C-Programlama/NN-baslik/` | ozet.md, quiz.md, notlarim.md |
| Konu | `Elektronik/Konular/baslik/` | ozet.md, quiz.md, kaynaklar.md |
| Komponent | `Elektronik/Komponentler/NN-baslik/` | ozet.md, quiz.md, kaynaklar.md |
| EMC | `Elektronik/EMC/NN-baslik/` | ozet.md, quiz.md, kaynaklar.md |
| Proje | `Elektronik/Projeler/NN-baslik/` | README.md, sematik-review.md |

## Sık karşılaşılan sorunlar

**"running scripts is disabled on this system" / "betiklerin çalıştırılması devre dışı"**
Bir kez çalıştır: `Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy RemoteSigned`
Şirket bilgisayarında Group Policy ile kilitliyse IT'den izin iste; aşmaya çalışma.

**Türkçe karakterler bozuk görünüyor**
Script dosyaları *UTF-8 with BOM* olmalı (Windows PowerShell 5.1 bunu gerektirir). VS Code'da bu repo açıkken `.vscode/settings.json` bunu otomatik sağlar; başka editörle kaydedersen kodlamayı kontrol et.

**"SSL certificate problem: unable to get local issuer certificate" (şirket ağında)**
Git'in Windows sertifika deposunu kullanmasını sağla: `git config --global http.sslBackend schannel`
`http.sslVerify false` **asla** kullanma.
