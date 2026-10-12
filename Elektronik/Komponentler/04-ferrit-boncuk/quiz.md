# Quiz · Ferrit boncuk

> Önce kendin çöz, sonra en alttaki cevap anahtarını aç. Hesap sorularında işlemi kâğıda yaz. 11 soru, 4'ü hesap.

## Sorular

1. **(Hesap)** Bir boncuğun empedans eğrisinde, endüktif bölgedeki 10 MHz noktasında X ≈ 30 Ω okunuyor. Yaklaşık endüktansı nedir?
   - A) 0,048 µH
   - B) 0,48 µH
   - C) 4,8 µH
   - D) 48 µH

2. **(Hesap)** 0,48 µH'lik boncuk, 1 µF kapasitörle bir LC filtre oluşturuyor. Rezonans frekansı yaklaşık kaçtır?
   - A) 23 kHz
   - B) 230 kHz
   - C) 2,3 MHz
   - D) 23 MHz

3. **(Hesap)** Aynı filtrenin karakteristik empedansı (Z0) yaklaşık kaçtır?
   - A) 0,07 Ω
   - B) 0,69 Ω
   - C) 6,9 Ω
   - D) 69 Ω

4. **(Hesap)** DCR'si 0,1 Ω olan bir boncuktan 0,5 A geçiyor. Üzerindeki gerilim düşümü kaçtır?
   - A) 5 mV
   - B) 50 mV
   - C) 0,5 V
   - D) 5 V

5. Ferrit boncuk yüksek frekanslı gürültüyü esas olarak nasıl yok eder?
   - A) Gürültüyü kaynağa geri yansıtarak
   - B) Gürültü enerjisini ısıya çevirerek
   - C) Gürültüyü depolayıp sonra bırakarak
   - D) Gürültüyü toprağa kısa devre ederek

6. Boncuktan geçen DC akım arttıkça ne olur?
   - A) Empedans artar
   - B) Empedans belirgin şekilde düşer
   - C) Empedans değişmez
   - D) Boncuk kapasitöre dönüşür

7. Kartta 500 kHz'de çalışan bir buck regülatör var. VDDA filtresindeki boncuk ve kapasitörün rezonansı 230 kHz. Risk nedir?
   - A) Hiçbir risk yoktur
   - B) Rezonans tepesi regülatörün ripple'ına yakın olduğu için filtre ripple'ı bastırmak yerine büyütebilir
   - C) Boncuk hemen yanar
   - D) Regülatörün frekansı değişir

8. USB D+/D− hatlarının ortak mod gürültüsünü bastırmak için hangisi doğrudur?
   - A) Her hatta ayrı bir ferrit boncuk
   - B) Ortak mod bobini (CMC)
   - C) Her hatta 100 nF'lık kapasitör
   - D) Hatlara seri 1 kΩ direnç

9. Kablonun tamamını saran geçme (clamp-on) bir ferrit hangi akımı etkiler?
   - A) Yalnızca diferansiyel mod akımını
   - B) Yalnızca ortak mod akımını
   - C) Yalnızca DC akımı
   - D) Hiçbir akımı

10. Toprak (GND) hattına ferrit boncuk koymaktan neden kaçınılır?
    - A) Boncuk toprakta çalışmaz
    - B) Dönüş yolunu bozar, devrelerin toprak gerilimini oynatır ve EMC'yi kötüleştirir
    - C) Boncuk pahalıdır
    - D) Toprakta akım yoktur

11. Bir filtrenin girişi ve çıkışı kartta yan yana paralel izlerle gidiyor. Sonuç ne olur?
    - A) Filtre daha iyi çalışır
    - B) Gürültü kapasitif ve endüktif kuplajla boncuğu atlayıp çıkışa geçer
    - C) Hiçbir etkisi olmaz
    - D) Boncuk ısınır

## Sonuç

| Tarih | Skor | Zayıf kalan konu |
|---|---|---|
|  |  |  |

<details>
<summary>Cevap anahtarı</summary>

1. **B** — `L ≈ X / (2πf) = 30 / (2π × 10×10⁶) ≈ 0,48 µH`.

2. **B** — `f = 1 / (2π √(0,48×10⁻⁶ × 1×10⁻⁶)) ≈ 230 kHz`.

3. **B** — `Z0 = √(0,48×10⁻⁶ / 1×10⁻⁶) ≈ 0,69 Ω`. Devredeki toplam direnç bundan çok küçükse Q yüksektir ve rezonansta tepe oluşur.

4. **B** — `ΔV = 0,5 × 0,1 = 50 mV`. Isınma `0,5² × 0,1 = 25 mW`.

5. **B** — Boncuğun yutma bölgesinde empedansın baskın kısmı dirençseldir (R). Gürültü enerjisi ısıya dönüşür.

6. **B** — DC akım ferrit çekirdeğin geçirgenliğini düşürür; endüktans ve kayıp direnci birlikte azalır. Anma akımında empedans katalog değerinin çok altında olabilir.

7. **B** — LC filtre rezonans civarında gürültüyü azaltmak yerine büyütebilir. Rezonans tepesi 230 kHz'de, regülatörün temel frekansı 500 kHz'de; tepe ripple'a yakın kalır. Sönümleme veya farklı değerler gerekir.

8. **B** — Her hatta ayrı boncuk, diferansiyel sinyali de zayıflatır ve bozar. CMC ise diferansiyel sinyali geçirip yalnızca ortak modu bastırır.

9. **B** — Kablodaki sinyal akımı gidiş-dönüş olarak zıt yönlüdür; ferrit içinde akıları birbirini götürür. Yalnızca ortak mod akımı (tüm iletkenlerde aynı yönde) ferritten etkilenir.

10. **B** — Toprak, tüm akımların dönüş yoludur. Araya boncuk girerse yüksek frekanslı dönüş akımları empedans görür, devreler arasında toprak gerilim farkı oluşur ve EMC kötüleşir.

11. **B** — Paralel giden izler arasında kuplaj oluşur. Yüksek frekanslı gürültü boncuktan geçmek yerine bu kuplaj yoluyla doğrudan çıkışa geçer; filtre işe yaramaz.

</details>
