# kbrcns · Öğrenme Sistemi

C programlama ve elektronik öğrenimi için kişisel bilgi deposu. Ev ve iş bilgisayarı arasında Git ile senkron çalışır.

## Klasör yapısı

```
kbrcns/
├── C-Programlama/          Ders bazlı: her ders bir klasör (NN-ders-adi)
├── Elektronik/
│   ├── Komponentler/       Komponent dersleri: direnç, kapasitör, bobin... (NN-ad)
│   ├── EMC/                EMC dersleri: temeller, kart tasarımı, testler (NN-ad)
│   ├── Konular/            Uygulama konuları: decoupling, op-amp, ADC...
│   ├── Sematik-Tasarim/    Kontrol listesi + hatalar ve dersler
│   └── Projeler/           Proje kartları (NN-proje-adi)
├── Kaynaklar/              Kütüphane: video / kitap / PDF listesi
├── sablonlar/              Ders, konu, quiz, proje şablonları + Claude istemleri
├── scriptler/              Senkron.ps1, Yeni-Kayit.ps1
├── Yerel/                  Git'e GİRMEZ: PDF, video, transkript (yalnızca o PC'de kalır)
└── ilerleme.md             Genel ilerleme tablosu
```

## İlk kurulum (her bilgisayarda bir kez)

1. Repoyu klonla. OneDrive, Masaüstü veya Belgeler gibi **senkronize edilen klasörlere koyma**; iki senkron sistemi aynı dosyalar üzerinde çakışır.
   ```powershell
   git clone https://github.com/KubraKarakocoglu/kbrcns.git $HOME\kbrcns
   cd $HOME\kbrcns
   ```
2. Git kimliğini ayarla (daha önce ayarlamadıysan):
   ```powershell
   git config --global user.name  "Adın Soyadın"
   git config --global user.email "eposta@adresin.com"
   ```
3. Script çalıştırma iznini yalnızca kendi kullanıcın için aç:
   ```powershell
   Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy RemoteSigned
   ```
   > Şirket bilgisayarında bu ayar Group Policy ile kilitliyse değiştirmeye çalışma; IT'den izin iste.

## Günlük akış

Komutlar repo klasöründe (`cd $HOME\kbrcns`) çalıştırılır.

| Ne zaman | Komut |
|---|---|
| Çalışmaya başlarken | `.\scriptler\Senkron.ps1` |
| Yeni C dersi | `.\scriptler\Yeni-Kayit.ps1 -Tur Ders -Baslik "Pointerlar" -Link "https://..."` |
| Yeni elektronik konusu | `.\scriptler\Yeni-Kayit.ps1 -Tur Konu -Baslik "Op-amp temelleri"` |
| Yeni proje | `.\scriptler\Yeni-Kayit.ps1 -Tur Proje -Baslik "GPIO buton"` |
| Çalışmayı bitirirken | `.\scriptler\Senkron.ps1 -Mesaj "Pointer dersi özeti eklendi"` |

Ayrıntılar ve hata durumları: [scriptler/README.md](scriptler/README.md)

## Kurallar

- **Aynı dosyayı iki bilgisayarda aynı anda düzenleme.** Bir bilgisayarda bitir → `Senkron.ps1` → diğerinde `Senkron.ps1` ile başla.
- **Repoda yalnızca kendi ürettiğin içerik olur:** özet, quiz, not, kod, proje kartı. PDF, video ve transkriptler `Yerel/` klasörüne.
- **Şirkete ait hiçbir doküman, şematik veya bilgi bu repoya girmez.**
- **Asla `git push --force` kullanma.** `Senkron.ps1` bunu hiçbir durumda yapmaz.

## Claude ile çalışma

Özet, quiz ve şematik review için hazır istemler: [sablonlar/claude-istemleri.md](sablonlar/claude-istemleri.md)
