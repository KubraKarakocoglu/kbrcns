# Claude İstemleri

Kopyala → köşeli parantezleri doldur → Claude'a gönder. Çıktıyı ilgili dosyaya yapıştır, sonra `Senkron.ps1`.

---

## 1. Ders özeti + quiz (video transkripti)

```
Aşağıda "[Kurs adı] – [Ders adı]" dersinin transkripti var.

1) sablonlar/ders-ozeti.md formatında Türkçe bir özet çıkar:
   - Anahtar kavramları tabloya koy.
   - Her kod örneğini satır satır yorumla.
   - "Gömülü sistemler açısından" bölümünde bu konunun mikrodenetleyicide
     neyi değiştirdiğini yaz.
   - Transkriptte olmayan bir bilgi eklersen başına [EK] yaz.
2) quiz.md için 8 soruluk çoktan seçmeli quiz üret:
   - En az 3 soru kod okuma/çıktı tahmini olsun.
   - Cevap anahtarı en altta, her cevap açıklamalı.

<transkript>
[transkripti buraya yapıştır]
</transkript>
```

## 2. Elektronik konu özeti (PDF / kitap bölümü / video)

```
"[Konu]" için ekteki [PDF / bölüm / transkript] kaynağından
sablonlar/konu-ozeti.md formatında Türkçe özet çıkar.
- Hedefim: şematik tasarlarken bilmem gereken can alıcı bilgiler.
- Formülleri "ne zaman kullanılır" ve "dikkat" sütunlarıyla ver.
- "Şematik kontrol listesine eklenecekler" bölümünü mutlaka doldur.
- Kaynakta olmayan bilgiyi [EK] ile işaretle.
- Metni kopyalama; kendi cümlelerinle özetle.
Ardından 6 soruluk quiz üret (en az 2 hesap sorusu).
```

## 3. Zayıf konuya odaklı yeni quiz

```
[Ders/konu] quiz'inde şu sorularda yanıldım: [soru numaraları ve verdiğim cevaplar].
Neden yanıldığımı açıkla, sonra yalnızca bu zayıf noktalara odaklanan
5 yeni soru üret (cevap anahtarı en altta).
```

## 4. Şematik review

```
Ekteki şematiği Elektronik/Sematik-Tasarim/kontrol-listesi.md maddelerine göre review et.
Her madde için: Uygun / Sorunlu / Kontrol edilemedi + kısa gerekçe.
Sonunda "en kritik 3 risk" listesi ver.
Komponent değerlerini datasheet önerileriyle karşılaştır; emin olmadığın yerde tahmin yürütme, "datasheet'ten doğrula" yaz.
```

## 5. Hatadan ders çıkarma

```
Şu hatayı yaptım: [belirti, ne oldu, nasıl fark ettim].
1) Kök nedeni analiz et.
2) hatalar-dersler.md tablosu için bir satır yaz.
3) Bu hatayı bir daha yapmamak için kontrol-listesi.md'ye eklenecek maddeyi öner.
```
