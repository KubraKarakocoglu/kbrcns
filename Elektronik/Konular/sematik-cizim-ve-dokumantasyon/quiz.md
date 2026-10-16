# Quiz · Şematik çizim ve dokümantasyon

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. 10 soru.

## Sorular

1. Sayfa 2'de `I2C_SDA`, sayfa 3'te `I2C_SDA1` yazan iki etiket var. Kart üretilince ne olur?
   - A) İki nokta birbirine bağlanmaz; ERC'deki "tek pinli net" uyarısı bunu gösterebilirdi
   - B) Araç benzer isimleri otomatik birleştirir
   - C) Layout aşamasında iz otomatik çekilir
   - D) Kart çalışır, çünkü etiketler sadece görsel bilgidir

2. Şematikte dört telin aynı noktada buluştuğu kavşak neden önerilmez?
   - A) ERC dört yollu kavşağı hata olarak verir
   - B) Bakır iz dört yöne çizilemez
   - C) Nokta silik basılırsa bağlantı mı kesişme mi olduğu anlaşılmaz; iki T kullanmak belirsizliği kaldırır
   - D) Dört yollu kavşak daha fazla akım taşır

3. Eski bir kütüphaneden alınan bir IC sembolünde VCC ve GND pinleri gizli. Kartta besleme rayının adı `+3V3`. Olası sonuç nedir?
   - A) Araç gizli pinleri her zaman doğru raya bağlar
   - B) Gizli pinler `VCC` isimli nete bağlanır; `+3V3` ile bağlantı kurulmaz ve IC beslemesiz kalabilir
   - C) Gizli pinler sadece simülasyonda kullanılır
   - D) Hiçbir etkisi olmaz

4. Komponent değerinde neden `4,7k` yerine `4k7` yazılır?
   - A) Daha kısa olduğu için
   - B) Standartlar virgül kullanımını yasaklar
   - C) Dizgi makinesi virgülü okuyamaz
   - D) Silik baskıda ya da küçük fontta virgül kaybolursa 4,7k, 47k olarak okunabilir; harf ondalık yerini güvenle gösterir

5. ERC aşağıdakilerden hangisini **yakalamaz**?
   - A) Bağlanmamış bir giriş pinini
   - B) İki push-pull çıkışın aynı nete bağlanmasını
   - C) 10 kΩ olması gereken direncin 1 kΩ yazılmasını
   - D) Hiçbir kaynağa bağlı olmayan güç pinini

6. Bir trimere paralel 0 Ω direnç var ve şematikte hangisinin takılı olduğu yazmıyor. Doğru çözüm hangisidir?
   - A) Takılmayacak parçaya DNP işareti koymak, gerekiyorsa varyant tanımlamak ve seçeneğin nedenini not etmek
   - B) İkisini de takmak
   - C) Üretimdeki operatöre sözlü bilgi vermek
   - D) 0 Ω direnci şematikten silmek

7. Kartta "R412" yazan bir parça arıyorsun. Sayfaya göre numaralandırma yapılmışsa nereye bakarsın?
   - A) Sayfa 1'e
   - B) BOM'un son satırına
   - C) Rastgele tüm sayfalara
   - D) Sayfa 4'e

8. BOM'da bir parçanın durumu "NRND" görünüyor. Ne anlama gelir?
   - A) Parça stokta yok
   - B) Parça hâlâ üretiliyor ama yeni tasarımlarda kullanılması önerilmiyor; yakında üretimden kalkabilir
   - C) Parça RoHS uyumlu değil
   - D) Parça sadece numune olarak satılıyor

9. Bir revizyonda R7 silindi. Kalan parçaların numaraları için doğru yaklaşım hangisidir?
   - A) Numaralar kalıcıdır; R7 boş kalır, diğer parçalar yeniden numaralanmaz
   - B) Tüm parçalar baştan numaralanır ki boşluk kalmasın
   - C) R8, R7 olarak değiştirilir
   - D) Fark etmez

10. Yeni bir buton ve konnektör footprint'ini doğrulamanın pratik yolu hangisidir?
    - A) Footprint adına bakmak yeterlidir
    - B) 3D görünüm yeterlidir
    - C) Layout'u 1:1 ölçekte yazdırıp gerçek parçayı kâğıdın üstüne koymak ve datasheet land pattern'i ile karşılaştırmak
    - D) Kart gelince denemek

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **A** — Araç için `I2C_SDA` ve `I2C_SDA1` tamamen farklı adreslerdir. İki ayrı net oluşur ve kartta bağlantı yoktur. Her nette tek pin kaldığı için ERC'nin "tek pinli net" uyarısı bu hatayı yakalar; bu yüzden o uyarı asla bastırılmaz.

2. **C** — Bağlantı noktası (junction) yazıcıda veya düşük çözünürlüklü PDF'te kaybolabilir. İki T kullanıldığında her kavşakta yalnızca üç tel buluşur ve "bağlı mı?" sorusu doğmaz.

3. **B** — Gizli pinler, kütüphanenin varsaydığı isimli nete (`VCC`, `GND`) otomatik bağlanır. Senin rayın farklı isimdeyse bağlantı kurulmaz ve şematikte bunu gösteren hiçbir şey yoktur. Güç pinleri her zaman görünür olmalıdır.

4. **D** — `4k7` gösteriminde harf, ondalık noktanın yerini alır. Küçük font, silik baskı veya fotokopi virgülü kaybettirebilir; harf kaybolmaz. Aynı mantık: `2R2` = 2,2 Ω, `1n5` = 1,5 nF.

5. **C** — ERC tutarlılığı kontrol eder, anlamı değil. 1 kΩ yazılmış bir direnç elektriksel olarak tutarlıdır. Yanlış değeri ancak hesap notu ve review yakalar.

6. **A** — Takılmayacak parça DNP ile işaretlenir; birden fazla ürün çeşidi varsa varyant tanımlanır ve her varyantın kendi BOM'u çıkar. Seçeneğin neden var olduğu nota yazılır. Sözlü bilgi kaybolur, silmek ise esnekliği yok eder.

7. **D** — Sayfaya göre numaralandırmada ilk rakam sayfa numarasıdır: R412 → sayfa 4. Kartta parça ararken zaman kazandırır.

8. **B** — NRND (Not Recommended for New Designs): parça hâlâ üretiliyor ama üretici yeni tasarımda kullanılmasını önermiyor; genelde EOL'un habercisidir. Yeni tasarımda kullanılmaz.

9. **A** — Referans numaraları eski BOM'lar, servis notları ve test dokümanlarıyla eşleşir. Yeniden numaralandırma bütün bu belgeleri geçersiz kılar. Boşluk kalması sorun değildir.

10. **C** — Mekanik parçalarda (buton, konnektör, ekran) footprint hatası çok yaygındır. 1:1 kâğıt testi ped aralığı, pin 1 ve gövde boyutu hatalarını kart siparişinden önce yakalar. 3D model de yanlış olabilir, footprint adı ise hiçbir şeyi garanti etmez.

</details>
