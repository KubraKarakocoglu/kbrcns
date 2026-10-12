# 02 · EMC için kart tasarımı

- **Oluşturma:** 2026-10-12
- **İlk kaynak:** [Rick Hartley – How to Achieve Proper Grounding](https://resources.altium.com/p/us-how-to-achieve-proper-grounding-rick-hartley-expert-live-training)
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Önceki ders:** [01 · EMC temelleri](../01-emc-temelleri/ozet.md) · **Sonraki:** [03 · Testler ve standartlar](../03-emc-testleri-ve-standartlar/ozet.md)

> Değerler **tipik başlangıç noktalarıdır**. Komponent seçimi için datasheet'ler, test seviyeleri için ürün standardı esastır.

---

## ⚡ Hızlı tekrar

1. **Kesintisiz GND düzlemi:** Hızlı sinyallerin altında yarık veya bölme olmasın.
2. **Katman dizilimi:** 4 katmanda *Sinyal / GND / Güç / Sinyal*. Her sinyal katmanı bir referans düzleme bitişik olmalı.
3. **Yerleşim:** Konnektörler bir kenarda; gürültülü bloklar (regülatör, saat) I/O'dan uzakta; analog devre ayrı bir bölgede ama **aynı GND düzleminde**.
4. **Katman değiştiren hızlı sinyalin** yanına dönüş via'sı (GND–GND) veya dikiş kapasitörü (GND–Güç) koy.
5. **Konnektördeki her hat filtrelenir ve korunur:** TVS + seri R/ferrit + kapasitör. Diferansiyel hatlarda ortak mod bobini.
6. **TVS'in GND bağlantısı çok kısa olmalı:** 8 kV'luk ESD ~30 A tepe akım demektir; 1 nH bile ~37 V ekler.
7. **Anahtarlamalı regülatör:** Sıcak döngü en küçük, SW düğümü küçük, girişte filtre.
8. **Yazılım da EMC'nin parçasıdır:** Watchdog, BOR, giriş doğrulama, periyodik yeniden yapılandırma, düşük GPIO hızı.

## 🧮 Formül kartı

| Formül | Ne zaman kullanılır | Örnek |
|---|---|---|
| `I_ESD ≈ 3,75 A/kV` (IEC 61000-4-2, ilk tepe) | ESD tepe akımı | 8 kV → 30 A |
| `V = L · di/dt` | Koruma yolundaki endüktansın eklediği gerilim | 1 nH, 30 A / 0,8 ns → 37,5 V |
| `R_seri ≈ Z0 − R_sürücü` | Seri sonlandırma direnci | 50 Ω iz, 20 Ω sürücü → 30 Ω (33 Ω) |
| `f_c = 1 / (2π·R·C)` | Giriş RC filtresi | 1 kΩ, 1 nF → 159 kHz |
| `aralık ≤ λ / 20` | Dikiş via'ları arası mesafe (kaba kural) | 1 GHz → 1,5 cm |
| `V_RWM ≥ V_çalışma,max` · `V_C ≤ korunan pinin mutlak maks.` | TVS seçimi | 3,3 V hat → V_RWM ≥ 3,3 V |

---

## 1. Toprak düzlemi ve dönüş yolu

Temel kural [01 · EMC temelleri](../01-emc-temelleri/ozet.md)'nden gelir: Yüksek frekansta dönüş akımı sinyal izinin hemen altından akar. Düzlemdeki her kesinti akımı dolambaçlı yola zorlar.

```
 KÖTÜ: hızlı sinyal GND yarığını geçiyor

   sinyal ══════════════════════════════►
   GND    ▓▓▓▓▓▓▓▓▓▓▓│  YARIK  │▓▓▓▓▓▓▓▓▓▓
   dönüş  ◄══════════╗           ╔════════
                     ╚═══════════╝  ← büyük döngü: anten

 İYİ: sinyal kesintisiz düzlem üzerinden gidiyor

   sinyal ══════════════════════════════►
   GND    ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
   dönüş  ◄══════════════════════════════  ← izin hemen altında, küçük döngü
```

**Kurallar:**
- Hızlı sinyali asla bir düzlem yarığının veya bölmenin üzerinden geçirme.
- Düzlemde gereksiz yarık açma. Via'ların etrafındaki boşluklar (anti-pad) yan yana dizilince farkında olmadan uzun bir yarık oluşturabilir; via sıralarına dikkat et.
- **"Analog GND ve dijital GND'yi ayır" tavsiyesi:** Bugünkü yaygın uzman görüşü (Ott, Hartley), çoğu tasarımda **tek, kesintisiz bir GND düzlemi** kullanmak ve ayrımı **yerleşimle** (bölgeleme) yapmaktır. Bölmek, sinyaller bölmenin üzerinden geçtiği anda sorunu büyütür. Bazı ADC datasheet'leri farklı bir öneri yapabilir; o durumda datasheet'in gerekçesini dikkatle oku.

## 2. Katman dizilimi (stackup)

| Katman sayısı | Önerilen dizilim | Not |
|---|---|---|
| **2** | Üst: sinyal ve güç · Alt: mümkün olduğunca kesintisiz GND | EMC açısından en zoru; alt katmana iz atmaktan kaçın, döngüleri küçük tut |
| **4** | L1 Sinyal · L2 GND · L3 Güç · L4 Sinyal | En yaygın. Hızlı sinyalleri GND'ye bitişik L1'de yönlendir |
| **6** | ör. Sinyal · GND · Sinyal · Güç · GND · Sinyal | Daha fazla referans düzlemi, iç katmanlarda korunan sinyaller |

- **Güç düzlemine referanslanan sinyaller** (4 katmanda L4): Dönüş akımı güç düzleminde akar ve GND'ye kapasitörler üzerinden geçer. Bu yüzden en hızlı sinyalleri GND'ye bitişik katmanda yönlendir.
- **2 katmandan 4 katmana geçiş,** EMC açısından atılabilecek en etkili adımlardan biridir. Fiyat farkı günümüzde genellikle küçüktür.

## 3. Yerleşim: bölgeleme

```
 ┌───────────────────────────────────────────────┐
 │ [Konnektörler]  ← I/O kenarı: filtre + koruma │
 │  TVS  RC  CMC                                  │
 │ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─  │
 │  [Analog ön kat]        [MCU + kristal]        │
 │  sensör, ADC            kısa saat izleri       │
 │                                                │
 │                         [Buck regülatör]       │
 │                         köşede, I/O'dan uzak   │
 └───────────────────────────────────────────────┘
        Tek ve kesintisiz GND düzlemi altta
```

- **Konnektörleri bir kenarda topla.** Karşılıklı kenarlarda konnektör olursa, aralarındaki küçük toprak gerilim farkı iki kabloyu bir **dipol antenin** iki koluna dönüştürür.
- **Gürültülü blokları** (anahtarlamalı regülatör, saat, MCU) I/O kenarından uzak tut. Konnektör bölgesi "temiz bölge" olmalı.
- **Analog ön katı** regülatörden ve hızlı dijitalden uzakta, ADC'ye yakın yerleştir.
- **Kristali** MCU'ya yakın, kart kenarından ve konnektörlerden uzak koy.

## 4. Hızlı sinyaller ve saat hatları

- **Kısa ve doğrudan** yönlendir; GND'ye bitişik katmanda tut.
- **Kart kenarına yakın geçirme.** Kenarda alan saçılması artar, ESD'ye de daha açıktır.
- **I/O izlerine paralel yürütme.** Saatin gürültüsü kuplajla kablolara taşınır.
- **Seri sonlandırma:** Sürücü pinine yakın 22–33 Ω. Örnek: 50 Ω iz, sürücü çıkış direnci ~20 Ω → ~30 Ω → 33 Ω.
- **Katman değiştirirken dönüş yolu ver:**

```
 Sinyal L1'den L4'e geçiyor:

  L1 sinyal ──●─────          L2 GND ▓▓▓▓●▓▓▓▓   ← dönüş via'sı (GND–GND)
              │                          │          sinyal via'sının hemen yanında
  L4 sinyal ──●─────          L3 Güç ▓▓▓▓┴▓▓▓▓   ← ya da dikiş kapasitörü (GND–Güç)
```

  Sinyalin referans düzlemi değişirse dönüş akımı da düzlem değiştirmek zorundadır. Yakınında bir yol yoksa uzaktan dolaşır.
- **GPIO hızı:** Yazılımda gereken en düşük çıkış hızını seç (bkz. [Mikrodenetleyici donanımı](../../Komponentler/05-mikrodenetleyici-donanimi/ozet.md)).

## 5. Anahtarlamalı regülatörler

Ayrıntılar: [Bobin (indüktör), bölüm 6–7](../../Komponentler/03-bobin-induktor/ozet.md). Özet:
- **Sıcak döngü** (giriş kapasitörü – anahtarlar) en küçük alanda olmalı.
- **SW düğümü** bakırı küçük tutulmalı; FB izi uzakta olmalı.
- **Girişe LC (π) filtre** koymak, f_sw harmoniklerinin iletimli emisyonunu azaltır.
- **Ekranlı bobin** kullan; destekleniyorsa **spread spectrum**'ı aç.
- Gerekirse SW düğümüne **RC snubber** ekle (çınlamayı sönümler).
- Regülatörü kartın bir köşesine, I/O ve analog bölgeden uzağa koy.

## 6. Konnektörler, kablolar ve filtreler

**Kural:** Karttan çıkan her hat hem bir **anten** hem de bozucular için bir **giriş kapısıdır**. Konnektörün hemen arkasında filtrelenmeli ve korunmalıdır.

| Hat türü | Tipik filtre / koruma |
|---|---|
| **Yavaş dijital** (buton, röle sürme, LED) | ESD diyotu/TVS + seri R (100 Ω–1 kΩ) + kapasitör (1–10 nF) GND'ye |
| **Analog sensör girişi** | TVS/clamp + seri R + C (kesim, sinyal bandının üstünde) |
| **UART (düşük hız)** | ESD koruma + seri R veya ferrit + küçük kapasitör |
| **RS-485 / CAN** | Bus gerilimine uygun TVS + ortak mod bobini; CAN'de isteğe bağlı bölünmüş sonlandırma (2 × 60 Ω + kapasitör GND'ye) |
| **USB 2.0** | Düşük kapasitanslı ESD dizisi (<1 pF) + isteğe bağlı CMC. Hatlara ayrı boncuk veya büyük kapasitör koyma |
| **DC güç girişi** | Ters polarite koruması + TVS + LC/π filtre + gerekirse CMC |

**Kablo ekranı:**
- Ekranı konnektörde kasaya **360°** (çepeçevre) bağla.
- "Pigtail" (ekranı tek bir telle bağlamak) yüksek frekansta endüktans ekler ve ekranın etkisini büyük ölçüde yok eder.

**Kasa (chassis):** Metal kasa varsa, devre GND'sini kasaya **I/O bölgesinde**, düşük empedansla (doğrudan veya kapasitörlerle) bağla. Böylece kablolardan gelen bozucular karttan geçmeden kasaya akar.

## 7. ESD koruması

**IEC 61000-4-2 ESD darbesi:** İlk tepe akımı yaklaşık **3,75 A/kV**, yükselme süresi ~1 ns.
- 8 kV kontak deşarj → **~30 A** tepe akım
- Bu akım 1 nH'lik bir bağlantıdan 0,8 ns'de geçerse: `V = 1 nH × 30 A / 0,8 ns ≈ 37,5 V` ek gerilim

**Sonuç:** TVS'in kenetleme gerilimi ne kadar iyi olursa olsun, GND bağlantısı uzunsa korunan pin yine de yüksek gerilim görür.

```
 KÖTÜ                                 İYİ

 Konn ─────────────[MCU]              Konn ──┬──[R/ferrit]──[MCU]
            │                                │
           [TVS]  ← uzakta                 [TVS]  ← konnektöre bitişik
            │                                │
            └──── uzun iz ──── GND           ● ← GND via'sı TVS pad'inin yanında
```

**Kurallar:**
- **TVS konnektörden sonraki ilk komponent** olmalı.
- TVS'in GND bağlantısı **kısa ve geniş**, via pad'in hemen yanında olmalı.
- TVS'ten sonra seri direnç veya ferrit eklemek **iki kademeli** koruma sağlar; IC'ye ulaşan akımı daha da sınırlar.
- **ESD akımının yolu:** Akım konnektörde kasaya veya GND'ye akmalı; kartın içinden geçip MCU'nun GND'sine ulaşmamalı.
- **TVS seçimi:** V_RWM ≥ hattın en yüksek çalışma gerilimi; V_C (kenetleme) ≤ korunan pinin mutlak maksimumu; hızlı hatlarda düşük kapasitans; tek veya çift yönlü.
- **Hassas hatlar:** NRST, osilatör, kart kenarına yakın uzun izler. Bunları kenardan uzak tut.
- **Plastik kasa:** Kasa birleşim yerlerindeki aralıklar havadan deşarjın girdiği noktalardır; iç tarafta bu noktalara yakın iz veya komponent bırakma.

## 8. Güç girişi

```
 DC giriş ──[Sigorta/PTC]──[Ters polarite]──┬──[ CMC ]──[ L ]──┬──► Regülatöre
                                            │                  │
                                          [TVS]              [C bulk + C seramik]
                                            │                  │
 GND ───────────────────────────────────────┴──────────────────┴──
```

- **Ters polarite:** Seri Schottky diyot (basit, kayıplı) veya P-MOSFET (düşük kayıp).
- **TVS:** Surge ve EFT darbelerini kenetler.
- **LC / π filtre:** İletimli emisyonu (150 kHz–30 MHz) ve içeri giren bozucuları azaltır. Sönümlemeyi unutma (bkz. [Ferrit boncuk](../../Komponentler/04-ferrit-boncuk/ozet.md)).
- **CMC:** Ortak mod iletimli emisyon ve bağışıklık için.

## 9. Yazılımla bağışıklık

Donanım bozucuyu tamamen engelleyemez. Yazılım, bozucu geçtiğinde sistemin güvenle toparlanmasını sağlar.

| Tehdit | Yazılım önlemi |
|---|---|
| ESD veya EFT sonrası kilitlenme | Bağımsız watchdog (IWDG); daha sıkı denetim için pencereli watchdog |
| Besleme çöküşü | BOR eşiği; düşük gerilim algılama (PVD) ile güvenli kapanış |
| Bozuk sensör okuması | Ortalama veya medyan filtre, makul aralık kontrolü (plausibility), değişim hızı sınırı |
| Haberleşme hatası | CRC, zaman aşımı, yeniden deneme |
| Çevre birimi register'larının bozulması | Ayarları periyodik olarak yeniden yazma, kritik değişkenleri kopya ile doğrulama |
| Yanlış alarm | Alarmı birden fazla ardışık örnekle onaylama; alarm eşiğinde histerezis |

## 10. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| Hızlı sinyali GND yarığının üzerinden geçirmek | Dönüş akımı dolanır, döngü büyür | Kesintisiz düzlem |
| Konnektörleri karşılıklı kenarlara koymak | Kablolar dipol anten olur | Tek kenar |
| TVS'i IC'nin yanına, konnektörden uzağa koymak | ESD akımı kartın içinden geçer | Konnektöre bitişik |
| TVS'in GND bağlantısını uzun izle yapmak | Endüktans kenetlemeyi bozar | Kısa ve geniş, via pad'in yanında |
| USB hatlarına ayrı boncuk veya büyük kapasitör | Sinyal bozulur | Düşük kapasitanslı ESD dizisi, CMC |
| Kablo ekranını pigtail ile bağlamak | Yüksek frekansta ekran işe yaramaz | 360° bağlantı |
| Katman değiştiren sinyale dönüş yolu vermemek | Dönüş akımı uzaktan dolaşır | Dönüş via'sı veya dikiş kapasitörü |
| Saat izini I/O izlerine paralel yürütmek | Saat gürültüsü kablolara taşınır | Ayrı yönlendir |
| Watchdog kullanmamak | Bozucu sonrası kilitlenme kalıcı olur | IWDG |

## 11. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Stackup** | Kart katmanlarının dizilimi |
| **Referans düzlem** | Sinyalin dönüş akımını taşıyan komşu düzlem |
| **Dikiş via'sı / kapasitörü** | Düzlemler arasında dönüş akımına yol veren via / kapasitör |
| **Bölgeleme** | Devreleri işlevine göre kart üzerinde ayrı bölgelere yerleştirmek |
| **TVS** | Transient Voltage Suppressor: geçici gerilim bastırıcı diyot |
| **V_RWM / V_C** | TVS'in ters çalışma gerilimi / kenetleme gerilimi |
| **CMC** | Ortak mod bobini |
| **Bölünmüş sonlandırma** | CAN'de sonlandırma direncinin ortasından kapasitörle GND'ye bağlanması |
| **Pigtail** | Kablo ekranının tek bir telle bağlanması |
| **Kasa (chassis)** | Cihazın metal gövdesi |
| **IWDG / PVD** | Bağımsız watchdog / programlanabilir gerilim dedektörü |
| **Plausibility** | Ölçülen değerin fiziksel olarak makul olup olmadığının kontrolü |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.2, bölüm 11):

- [x] Kesintisiz GND düzlemi; hızlı sinyaller yarık veya bölme üzerinden geçmiyor
- [x] Katman dizilimi: her sinyal katmanı bir referans düzleme bitişik
- [x] Konnektörler mümkünse tek kenarda; I/O bölgesinde filtre ve koruma
- [x] Her dış hatta TVS konnektöre en yakın, GND bağlantısı kısa
- [x] Diferansiyel hatlarda (USB, CAN, RS-485) uygun ESD koruması ve CMC
- [x] Hızlı sinyallerde seri sonlandırma; katman değişiminde dönüş via'sı
- [x] Anahtarlamalı regülatör: sıcak döngü en küçük, SW düğümü küçük, giriş filtresi
- [x] Kablo ekranı konnektörde 360° sonlandırılıyor

## Kontrol soruları

→ [quiz.md](quiz.md) · 12 soru, 4'ü hesap
