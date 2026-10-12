# EMC (Elektromanyetik Uyumluluk)

Üç bölümlük ders. Sırayla çalış; her bölüm bir öncekinin üzerine kurulur.

| # | Ders | İçerik |
|---|---|---|
| 01 | EMC temelleri | Emisyon ve bağışıklık, kaynak–yol–kurban, kuplaj türleri, diferansiyel ve ortak mod, kenar hızı ve spektrum |
| 02 | EMC için kart tasarımı | Dönüş akımları, katman dizilimi, yerleşim, anahtarlamalı regülatörler, kablo ve konnektör filtreleri, ESD koruması, yazılımla bağışıklık |
| 03 | EMC testleri ve standartlar | CE ve standart yapısı, IEC 61000-4-x testleri, emisyon ölçümleri, gaz algılama için EN 50270, laboratuvar öncesi ölçümler |

**Ön koşul:** Komponentler bölümündeki kapasitör, bobin ve ferrit boncuk dersleri, ayrıca [Güç ve decoupling](../Konular/guc-ve-decoupling/ozet.md).

Yeni EMC dersi açmak için:

```powershell
.\scriptler\Yeni-Kayit.ps1 -Tur EMC -Baslik "ESD koruması"
```
