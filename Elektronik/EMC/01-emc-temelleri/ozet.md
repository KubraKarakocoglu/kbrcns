# 01 · EMC temelleri

- **Oluşturma:** 2026-10-12
- **İlk kaynak:** Henry W. Ott – *Electromagnetic Compatibility Engineering* (Wiley)
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Sonraki ders:** [02 · EMC için kart tasarımı](../02-emc-icin-kart-tasarimi/ozet.md)

> Bu ders kavramları kurar; sayılar sezgi kazandırmak içindir. Tasarım kararları için ilgili standart ve ölçüm esastır.

---

## ⚡ Hızlı tekrar

1. **EMC = iki yönlü uyum:** Cihaz çevresini bozmamalı (**emisyon**) ve çevresinden bozulmamalı (**bağışıklık**).
2. Her EMC problemi üç parçadan oluşur: **kaynak → kuplaj yolu → kurban**. Birini kır, problem biter.
3. Dört kuplaj yolu vardır: **iletim** (ortak empedans), **kapasitif** (dV/dt), **endüktif** (dI/dt) ve **ışıma**.
4. Spektrumu saat frekansı değil, **kenar süresi** belirler: `f ≈ 1/(π·t_r)`.
5. Kablolardaki **ortak mod** akımları, diferansiyel mod akımlarından çok daha verimli ışır; mikroamper seviyesi bile sorun çıkarır.
6. Bir kablo, boyu dalga boyunun çeyreğine yaklaşınca iyi bir antendir: 100 MHz'de λ/4 = **75 cm**.
7. Yüksek frekansta dönüş akımı en düşük **endüktanslı** yolu izler: sinyal izinin hemen altından.
8. EMC tasarım aşamasında çözülür. Test laboratuvarında çözmek çok daha pahalıdır.

## 🧮 Formül kartı

| Formül | Ne zaman kullanılır | Örnek |
|---|---|---|
| `f_knee ≈ 1 / (π · t_r)` | Kenarın ürettiği spektrumun önemli kısmının üst sınırı | 1 ns → 318 MHz · 10 ns → 32 MHz |
| `λ = c / f` | Dalga boyu | 100 MHz → 3 m, λ/4 = 75 cm |
| `i = C · dV/dt` | Kapasitif kuplaj akımı | 1 pF, 3,3 V / 1 ns → 3,3 mA |
| `v = M · di/dt` | Endüktif kuplaj gerilimi | 10 nH, 100 mA / 1 ns → 1 V |
| `r ≈ λ / (2π)` | Yakın alan / uzak alan sınırı | 30 MHz → 1,6 m · 1 GHz → 4,8 cm |
| `dB = 20 · log10(V2 / V1)` | Gerilim oranı | 6 dB ≈ 2× · 20 dB = 10× · 40 dB = 100× |
| `E_DM ∝ f² · A · I` · `E_CM ∝ f · ℓ · I` | Diferansiyel / ortak mod ışıması | Alan A, kablo boyu ℓ |

---

## 1. EMC nedir, neden önemli?

| | Emisyon | Bağışıklık |
|---|---|---|
| Soru | Cihazım çevreyi bozuyor mu? | Çevre cihazımı bozuyor mu? |
| İletimli | Kablolardan dışarı giden gürültü (tipik ölçüm 150 kHz–30 MHz) | Kablolardan giren bozucular (EFT, surge, iletimli RF) |
| Işınımlı | Havaya yayılan alan (tipik ölçüm 30 MHz ve üstü) | Havadan gelen alanlar (telsiz, telefon), ESD |

**Neden önemli?**
- **Yasal zorunluluk:** Avrupa'da CE işareti için EMC direktifine uyum şarttır (bkz. [03 · Testler ve standartlar](../03-emc-testleri-ve-standartlar/ozet.md)).
- **Güvenilirlik:** Bağışıklığı zayıf bir cihaz sahada açıklanamayan arızalar verir.
- **Güvenlik:** Gaz dedektörü gibi bir güvenlik cihazının telsiz yanında yanlış alarm vermesi, daha kötüsü alarm vermemesi kabul edilemez. Bu tür cihazlarda bağışıklık doğrudan güvenlik konusudur.

## 2. Kaynak – kuplaj yolu – kurban

```
 ┌──────────┐      kuplaj yolu       ┌──────────┐
 │  KAYNAK  │ ─────────────────────► │  KURBAN  │
 └──────────┘                        └──────────┘
  saat sinyalleri    iletim (ortak empedans)    ADC girişi
  SW düğümü          kapasitif (elektrik alan)  reset hattı
  hızlı kenarlar     endüktif (manyetik alan)   sensör ön katı
  röle, motor        ışıma (uzak alan)          radyo alıcısı
  ESD, telsiz                                   komşu cihaz
```

| Strateji | Örnek | Maliyet |
|---|---|---|
| **Kaynakta azalt** | Kenarları yavaşlat, akım döngüsünü küçült, spread spectrum | En ucuz |
| **Yolu kes** | Yerleşim, kesintisiz toprak, filtre, ekran | Orta |
| **Kurbanı güçlendir** | Giriş filtresi, yazılımla filtreleme, watchdog | Değişken |

Her zaman önce kaynağa bak: kaynaktaki bir değişiklik birden fazla kurbanı aynı anda korur.

## 3. Kuplaj mekanizmaları

| Mekanizma | Fizik | Örnek | Çözüm |
|---|---|---|---|
| **İletim / ortak empedans** | İki devre aynı dönüş yolunu paylaşır: `V = I · Z_ortak` | Röle akımı ile sensör aynı GND izinden dönüyor; sensör ölçümüne röle akımının yarattığı gerilim eklenir | Ayrı dönüş yolları, kesintisiz GND düzlemi |
| **Kapasitif (elektrik alan)** | `i = C · dV/dt` | 1 pF parazitik kapasitans, 1 ns'de 3,3 V değişim → **3,3 mA**. Yüksek empedanslı bir girişte bu büyük bir gerilim demektir | Mesafe, arada GND, kurbanın empedansını düşürmek, kenarları yavaşlatmak |
| **Endüktif (manyetik alan)** | `v = M · di/dt` | 10 nH karşılıklı endüktans, 1 ns'de 100 mA değişim → **1 V** | Döngü alanlarını küçültmek, mesafe, dik yerleşim, bükümlü kablo |
| **Işıma (uzak alan)** | Anten gibi davranan yapılar | Kablolar, uzun izler, kasa yarıkları | Filtre, ekranlama, kablo yönetimi |

## 4. Diferansiyel mod ve ortak mod

```
 DİFERANSİYEL MOD (DM)                ORTAK MOD (CM)

  ───► I  ──────────►                  ───► I/2 ─────────►
 [kaynak]           [yük]             [kart]            [kablo ucu]
  ◄─── I  ◄──────────                  ───► I/2 ─────────►
                                              ⇣
                                     dönüş: parazitik kapasitans
                                     üzerinden çevreye (toprak, kasa)
```

| | Diferansiyel mod | Ortak mod |
|---|---|---|
| Akım yönü | Bir iletkenden gider, diğerinden döner | Tüm iletkenlerde aynı yönde |
| Dönüş yolu | Kablonun kendisi | Parazitik kapasitans, çevre |
| Işıma | Alanlar büyük ölçüde birbirini götürür; ∝ döngü alanı × f² | Döngü çok büyük; ∝ kablo boyu × f |
| Kaynağı | İstenen sinyal ve güç akımı | Toprak gerilim farkları, dengesizlik, karttan kabloya kuplaj |
| Tipik çözüm | Döngüyü küçültmek, filtre | Ortak mod bobini, kablo ferriti, ekran sonlandırma |

**Ana fikir:** Ortak mod akımı genellikle çok küçüktür, ama çok verimli ışır. Ott'un kitabındaki klasik örnekte, 1 m'lik bir kablodaki birkaç mikroamperlik ortak mod akımının emisyon sınırını aşmaya yettiği gösterilir. Işınımlı emisyon testinde kalan kartların çoğunda sorun kartın kendisi değil, **kablolardır**.

## 5. Dijital sinyallerin spektrumu

Kare dalga, temel frekansın tek harmoniklerinden oluşur. Gerçek bir dijital sinyal ise yükselme süresi sonlu olan bir yamuk dalgadır. Spektrumunun zarfı (Ott ve Paul'ün klasik modeli):

```
 dB
  │─────────────┐
  │              \    −20 dB/dekad
  │               \
  │                \______
  │                       \    −40 dB/dekad
  │                        \
  └─────────────┬──────────┬─────────── log f
            1/(π·τ)    1/(π·t_r)
            τ: darbe genişliği   t_r: yükselme süresi
```

**Sonuçları:**
- `1/(π·t_r)` noktasının üstünde enerji hızla düşer. Kenar ne kadar keskinse bu nokta o kadar yüksektedir:
  - t_r = 1 ns → **318 MHz**
  - t_r = 10 ns → **32 MHz**
- **Sorun saat frekansı değil, kenar hızıdır.** 1 kHz'lik bir sinyal bile 1 ns'lik kenarlarla yüzlerce MHz'de enerji taşır.
- **Pratik:** GPIO hızını düşürmek, seri sonlandırma direnci ve kenar kontrollü sürücüler en ucuz emisyon iyileştirmeleridir.

## 6. Antenler, dalga boyu ve kablolar

Bir yapı, boyu dalga boyunun çeyreğine veya yarısına yaklaşınca verimli bir anten olur.

| Frekans | λ | λ/4 | Kim anten olur? |
|---|---|---|---|
| 30 MHz | 10 m | 2,5 m | Uzun kablolar |
| 100 MHz | 3 m | 75 cm | Tipik cihaz kabloları |
| 300 MHz | 1 m | 25 cm | Kısa kablolar, büyük kartlar |
| 1 GHz | 30 cm | 7,5 cm | Kart izleri, kasa yarıkları |

- Tipik kablo boyları (0,5–2 m) **30–300 MHz** bandında verimli antendir. Işınımlı emisyon hatalarının en sık görüldüğü bant da budur.
- Metal kasadaki **yarıklar** da boyları yarım dalga boyuna yaklaşınca anten gibi ışır (yarık anteni).

## 7. Dönüş akımı: akım nereden geri döner?

- **DC ve düşük frekansta:** Dönüş akımı en düşük **dirençli** yoldan akar ve GND düzlemine yayılır.
- **Yüksek frekansta** (kabaca onlarca kHz'in üstünde): Dönüş akımı en düşük **endüktanslı** yolu izler. Bu da döngü alanını en küçük yapan yoldur: **sinyal izinin hemen altındaki düzlem.**

```
 Kesitten bakış:

   ═══ sinyal izi (gidiş akımı) ═══
   ─────────────────────────────────  dielektrik
   ▓▓▓▓▓ dönüş akımı izin altında yoğunlaşır ▓▓▓▓▓   GND düzlemi

 Üstten bakış, GND düzleminde yarık varsa:

   sinyal ════════════════════════════►
   GND    ▓▓▓▓▓▓▓▓▓│ YARIK │▓▓▓▓▓▓▓▓▓
   dönüş  ◄═══════╗         ╔═════════
                  ╚═════════╝  ← yarığın etrafından dolaşır → döngü büyür
```

**Sonuç:** Hızlı bir sinyalin altındaki düzlemdeki her kesinti, dönüş akımını dolambaçlı bir yola zorlar. Döngü büyür, hem emisyon hem bozucu alma artar. Kart tasarımının temel kuralı buradan çıkar (bkz. [02 · Kart tasarımı](../02-emc-icin-kart-tasarimi/ozet.md)).

## 8. Yakın alan ve uzak alan

| | Yakın alan (r < λ/2π) | Uzak alan (r > λ/2π) |
|---|---|---|
| Yapı | Elektrik **veya** manyetik alan baskın | Düzlem dalga, E/H = 377 Ω |
| Kaynak örneği | Yüksek dV/dt düğümü (E alanı), yüksek akım döngüsü (H alanı) | Kablolar ve antenler |
| Ölçüm | Yakın alan probları (E veya H) | Test odasında anten |

- **30 MHz'de sınır ~1,6 m, 1 GHz'de ~4,8 cm.** Kart üstündeki ölçümler neredeyse her zaman yakın alandadır.
- **Pratik sonuçlar:**
  - Yakın alan probuyla E ve H kaynaklarını ayrı ayrı bulabilirsin.
  - Düşük frekanslı manyetik alanları ekranlamak zordur; mesafe ve döngü küçültme daha etkilidir.

## 9. Desibel ve birimler

| Birim | Anlamı | Örnek |
|---|---|---|
| **dBµV** | 1 µV'a göre gerilim | 1 mV = 60 dBµV · 1 V = 120 dBµV |
| **dBµV/m** | 1 µV/m'ye göre alan şiddeti | 100 µV/m = 40 dBµV/m |
| **dBµA** | 1 µA'e göre akım | Kablo akımı ölçümünde |
| **dBm** | 1 mW'a göre güç | Spektrum analizöründe |

- **Neden dB?** Çok geniş bir dinamik aralığı tek ölçekte gösterir; kazanç ve kayıplar toplanır.
- **Akılda tut:** Gerilimde 6 dB ≈ 2 kat, 20 dB = 10 kat, 40 dB = 100 kat.
- **Dedektörler:** Emisyon sınırları genellikle **quasi-peak (QP)** ve **ortalama (AV)** dedektörlerle tanımlanır. Ölçülen değerler arasında her zaman **tepe ≥ QP ≥ ortalama** ilişkisi vardır. Tepe ölçümü sınırın altındaysa QP de altındadır; bu yüzden ön taramada hızlı olan tepe dedektörü kullanılır.

## 10. Tasarım felsefesi

**EMC önlem hiyerarşisi** (en ucuzdan en pahalıya):
1. **Kaynakta azalt:** Kenar hızı, döngü alanı, saat frekansı, spread spectrum
2. **Kart yerleşimi ve toprak:** Kesintisiz düzlem, bölgeleme, kısa dönüş yolları
3. **Filtre:** Konnektörlerde ve güç girişinde
4. **Ekranlama:** Metal kasa, kablo ekranı. En pahalı ve en son çare

**Maliyet zamanla katlanır:** Tasarımda bir via veya kapasitör eklemek bedavaya yakındır. Prototipte yeni bir kart turu gerekir. Test laboratuvarında hem kart turu hem tekrar test parası ödenir. Üretimdeki bir üründe ise geri çağırma riski vardır.

## 11. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| EMC'yi test laboratuvarında düşünmek | Pahalı kart turları | Tasarımda düşün, ön test yap |
| Saat frekansını düşürüp sorunun çözüleceğini sanmak | Spektrumu kenar hızı belirler | Kenarları yavaşlat |
| Hızlı sinyalin altındaki GND'yi bölmek | Dönüş akımı dolanır, döngü büyür | Kesintisiz düzlem |
| Kabloları göz ardı etmek | Ortak mod akımıyla en güçlü anten olurlar | Konnektörde filtre, CMC, ekran |
| Yalnızca ekranlamaya güvenmek | Pahalı; yarıklar ve kablolar ekranı deler | Önce kaynak ve yerleşim |
| Analog ve dijital GND'yi rastgele bölmek | Dönüş yolları bozulur | Tek düzlem, bölgeleme ile yerleşim |

## 12. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **EMC** | Electromagnetic Compatibility: elektromanyetik uyumluluk |
| **EMI** | Electromagnetic Interference: elektromanyetik girişim |
| **Emisyon / bağışıklık** | Yaydığı gürültü / dış gürültüye dayanıklılık |
| **İletimli / ışınımlı** | Kablo üzerinden / havadan yayılan |
| **DM / CM** | Diferansiyel mod / ortak mod |
| **Kuplaj** | Gürültünün kaynaktan kurbana geçiş yolu |
| **Yakın / uzak alan** | Kaynağa λ/2π'den yakın / uzak bölge |
| **Dönüş akımı** | Sinyalin kaynağına geri dönen akımı |
| **QP / AV** | Quasi-peak / ortalama dedektör |
| **dBµV/m** | Alan şiddeti birimi |

---

## Şematik kontrol listesine eklenecekler

Bu dersin uygulamaları [02 · Kart tasarımı](../02-emc-icin-kart-tasarimi/ozet.md) ile birlikte [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasının **bölüm 11 (EMC)** kısmına işlendi.

## Kontrol soruları

→ [quiz.md](quiz.md) · 12 soru, 5'i hesap
