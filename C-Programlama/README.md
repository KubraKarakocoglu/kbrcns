# C Programlama

**Ana kaynak:** _seçilecek_ — adaylar ve linkler: [Kaynaklar/kutuphane.md](../Kaynaklar/kutuphane.md)

## Ders klasörü

Her ders `NN-ders-adi/` klasöründe tutulur:

| Dosya | İçerik | Kim yazar |
|---|---|---|
| `ozet.md` | Dersin yapılandırılmış özeti | Claude (transkriptten); sen gözden geçirirsin |
| `quiz.md` | Çoktan seçmeli sorular + cevap anahtarı | Claude |
| `notlarim.md` | Kendi notların, takıldığın yerler | Sen |
| `*.c` | Derste yazdığın kodlar | Sen |

Yeni ders:

```powershell
.\scriptler\Yeni-Kayit.ps1 -Tur Ders -Baslik "Degiskenler ve veri tipleri" -Link "https://..."
```

## Ders başına akış

1. Videoyu izle, `notlarim.md` dosyasına not al.
2. Transkripti Claude'a ver → `ozet.md` + `quiz.md` (istem: [claude-istemleri.md](../sablonlar/claude-istemleri.md), madde 1).
3. Quiz'i çöz, skoru `quiz.md` ve `ilerleme.md` dosyalarına yaz.
4. **Dersteki kodu kendin yaz ve derle.** İzlemek öğrenmek değildir; kodu yazmadan dersi bitmiş sayma.
5. `.\scriptler\Senkron.ps1`

> Derleyici kurulumu ana kaynak seçilince eklenecek.
