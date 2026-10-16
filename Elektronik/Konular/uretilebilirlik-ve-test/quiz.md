# Quiz · Üretilebilirlik ve test için tasarım

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. 10 soru, 1'i hesap.

## Sorular

1. DFM, DFA ve DFT kısaltmaları sırasıyla neyi anlatır?
   - A) Kartın üretilebilmesi, monte edilebilmesi (dizgi ve lehim) ve test edilebilmesi için tasarım
   - B) Dijital, analog ve test katmanları
   - C) Üç farklı dosya formatı
   - D) Üç IPC sınıfı

2. Üreticinin en küçük iz/boşluk değeri 0,1 mm. Neden tasarımda mümkünse 0,15 mm ve üstü kullanılır?
   - A) 0,1 mm iz akım taşımaz
   - B) Standart buna izin vermez
   - C) Sınırda tasarım üretim verimini düşürür ve fiyatı artırır; bir kademe üstü daha güvenilir ve ucuzdur
   - D) DRC 0,1 mm'yi kabul etmez

3. Kartta QFN ve ince aralıklı IC'ler var. Hangi yüzey kaplama daha uygundur?
   - A) HASL, çünkü en ucuzdur
   - B) ENIG, çünkü yüzeyi düzdür ve ince aralıklı/QFN parçaların lehimlenmesi için daha uygundur
   - C) Kaplamasız bakır
   - D) Fark etmez

4. Panel V-kesimle ayrılacak. Büyük bir MLCC'yi nereye koymak en risklidir?
   - A) Kartın ortasına
   - B) Bir IC'nin yanına
   - C) Alt yüze
   - D) Kırma çizgisinin hemen yanına ve çizgiye dik olarak; kart ayrılırken eğilme MLCC'yi çatlatabilir

5. Fiducial'lar için hangisi doğrudur?
   - A) Tek bir fiducial yeterlidir
   - B) Fiducial'ların üstüne referans yazılmalıdır
   - C) En az 3 tane, köşelere yakın ve simetrik olmayan konumda olmalı; çevresi bakır ve maskeden boş bırakılmalıdır
   - D) Fiducial'lar delik olmalıdır

6. Üretim testi için test noktalarının yerleşiminde hangisi doğrudur?
   - A) Tek yüzden erişilebilir, Ø ≥ 1 mm, aralarında yeterli mesafe olan, parça altında ve maske altında olmayan noktalar
   - B) İki yüze rastgele dağıtılmış küçük via'lar
   - C) Yalnızca GND'ye bir test noktası
   - D) Test noktaları parçaların altına gizlenmeli

7. **(Hesap)** 4 × 4 mm'lik bir QFN termal pedi için şablonda 4 adet 1,5 × 1,5 mm pencere açılmış. Pasta kapsaması yaklaşık yüzde kaçtır ve önerilen aralıkta mıdır?
   - A) %100; önerilen aralıkta
   - B) %56; önerilen %50–80 aralığında
   - C) %14; çok az
   - D) %37; çok az

8. İlk dizgi kartlarında bazı parçalar 90° dönük takılmış. En olası neden nedir?
   - A) Parçaların datasheet'i yanlış
   - B) Lehim pastası eksik
   - C) Fırın sıcaklığı yüksek
   - D) EDA aracının pick & place dosyasındaki dönüş açısı tanımı ile dizgi firmasının kabulü farklı; ilk ürün kontrolüyle yakalanır

9. Firmware'deki kendi kendini test (self-test) özelliklerinin üretime faydası nedir?
   - A) Kartın daha hızlı çalışmasını sağlar
   - B) EMC testini gereksiz kılar
   - C) Rayları, ısıtıcı/yük akımını ve sensörün açık/kısa devre durumunu kendisi kontrol ederek üretim testini hızlandırır ve sahada arızanın kendini göstermesini sağlar
   - D) Kalibrasyonu gereksiz kılar

10. Üretim paketi hazırlanırken en yaygın ve en pahalı hatalardan biri hangisidir?
    - A) Farklı revizyonlara ait BOM, Gerber ve pick & place dosyalarının karışması; bu yüzden hepsi tek klasörde ve aynı revizyon adıyla gönderilir
    - B) Gerber'in PDF olarak da gönderilmesi
    - C) Silkscreen renginin belirtilmesi
    - D) Firmware sürümünün yazılması

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **A** — DFM (Design for Manufacturing) kart üretimi, DFA (Design for Assembly) dizgi ve lehim, DFT (Design for Test) test edilebilirlik içindir. Üçü de hataları ucuz oldukları tasarım aşamasında yakalamayı amaçlar.

2. **C** — Üreticinin en küçük değeri "yapabildiği" sınırdır; o sınırda üretilen kartlarda hatalı oran artar. Bir kademe geniş tasarlamak hem verimi artırır hem fiyatı düşürür.

3. **B** — HASL'de yüzey lehim tepecikleri yüzünden düz değildir; ince aralıklı ve alt pedli parçalarda pasta baskısı ve yerleşim zorlaşır. ENIG düz ve uzun raf ömürlüdür.

4. **D** — Panel kırılırken kart kırma çizgisi boyunca eğilir. Çizgiye dik duran ve yakın olan bir MLCC bu eğilmeyi doğrudan taşır ve çatlar. Çatlak kısa devreye dönüşebilen gizli bir arızadır.

5. **C** — Makine en az üç noktayla konumu ve dönüklüğü hesaplar. Noktalar simetrik olursa kartın 180° ters yerleştirildiği anlaşılamaz. Kameranın noktayı net görmesi için çevresi boş olmalıdır.

6. **A** — Fikstür iğneleri tek taraftan gelir ve belirli bir boyut ile aralığa ihtiyaç duyar. Parça veya maske altındaki noktaya iğne değemez.

7. **B** — Ped alanı 16 mm², pencerelerin toplamı `4 × 2,25 = 9 mm²` → `9 / 16 ≈ %56`. Tam pasta parçayı yüzdürür; çok az pasta ise termal bağlantıyı zayıflatır.

8. **D** — Her EDA aracı ve her dizgi makinesi "0°" yönünü kendi kütüphanesine göre tanımlar. Bu fark ilk kartlarda dönük parçalar olarak ortaya çıkar. İlk ürün kontrolü ve dizgi firmasıyla açı tanımının teyidi bunu önler.

9. **C** — Kart kendi beslemesini, yük akımlarını ve sensör bağlantısını kontrol edebiliyorsa üretim testi kısalır. Sahada da sensör kopukluğu gibi tehlikeli bir arıza "temiz hava" olarak değil, arıza olarak görünür.

10. **A** — Eski revizyonun BOM'u yeni revizyonun Gerber'i ile birleşirse kart yanlış parçalarla dizilir; sorun genelde ancak test aşamasında fark edilir. Bütün dosyalar tek klasörde, aynı revizyon adıyla tutulur.

</details>
