# 04 · Ferrit boncuk

- **Oluşturma:** 2026-10-12
- **İlk kaynak:** [Analog Devices AN-1368 – Ferrite Bead Demystified](https://www.analog.com/en/resources/app-notes/an-1368.html)
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)

> Sayısal değerler **tipik başlangıç noktalarıdır**; tasarım değeri için her zaman boncuğun empedans ve DC bias eğrileri esastır.

---

## ⚡ Hızlı tekrar

1. Ferrit boncuk bir **kayıplı indüktördür**: yüksek frekanslı gürültüyü geri yansıtmaz, **ısıya çevirerek** yok eder.
2. Datasheet'te `Z @ 100 MHz` ile anılır, ama asıl bilgi **empedans–frekans eğrisindedir** (R, X ve Z).
3. **DC akım** boncuğun empedansını ciddi şekilde düşürür. Anma akımı bir ısınma sınırıdır; o akımda filtreleme performansı çok düşük olabilir.
4. Boncuk ve kapasitör bir **LC filtre** oluşturur. Rezonans frekansında gürültüyü azaltmak yerine **büyütebilir**; sönümleme gerekir.
5. Tipik kullanımlar: analog beslemeyi ayırmak (VDDA), I/O hatlarını filtrelemek, kablo ferritleri (ortak mod).
6. Hızlı diferansiyel hatlarda (USB, Ethernet) her hatta ayrı boncuk değil, **ortak mod bobini** kullan.
7. **Toprağı (GND) boncukla bölme.**

## 🧮 Formül kartı

| Formül | Ne zaman kullanılır | Örnek |
|---|---|---|
| `L ≈ X / (2π·f)` | Endüktif bölgeden yaklaşık endüktans | 30 Ω @ 10 MHz → 0,48 µH |
| `f_res = 1 / (2π·√(L·C))` | Boncuk + kapasitör rezonansı | 0,48 µH + 1 µF → 230 kHz |
| `Z0 = √(L / C)` | Karakteristik empedans; sönümleme direncinin mertebesi | 0,48 µH, 1 µF → 0,69 Ω |
| `ΔV = I · DCR` · `P = I² · DCR` | Gerilim düşümü ve ısınma | 0,5 A, 0,1 Ω → 50 mV, 25 mW |

---

## 1. Ne işe yarar? Temel fizik

Ferrit malzemenin manyetik kayıpları frekansla artar. Bu yüzden boncuğun davranışı frekansa göre üç bölgeye ayrılır:

```
 Empedans
   │                 ___ Z
   │              _/    \__
   │            _/  R      \__   (kapasitif bölge:
   │          _/  ___         \__  sargı kapasitansı)
   │        _/  _/   \__
   │      _/  _/  X      \__
   │    _/  _/              \
   │  _/  _/
   └──────────┬──────────────────── log f
     endüktif │  dirençsel (yutma)
              R = X kesişimi
```

| Bölge | Davranış | Anlamı |
|---|---|---|
| Düşük frekans | **Endüktif** (X baskın) | Enerjiyi depolar, gürültüyü yansıtır |
| Orta-yüksek frekans | **Dirençsel** (R baskın) | Gürültüyü **ısıya çevirir**; boncuğun asıl çalıştığı yer |
| Çok yüksek frekans | **Kapasitif** | Parazitik kapasitans yüzünden empedans düşer |

R'nin X'i geçtiği frekans boncuğa göre değişir ve eğriden okunur.

### Boncuk ile bobin arasındaki fark

| | Bobin (indüktör) | Ferrit boncuk |
|---|---|---|
| Amaç | Enerji depolamak | Gürültüyü yutmak |
| Q (kalite) | Yüksek | Bilerek düşük |
| Datasheet'te | L (µH), Isat | Z @ 100 MHz, empedans eğrisi |
| Tipik kullanım | Regülatör, LC filtre | EMI bastırma, ray ayırma |

## 2. Türleri ve seçim

| Tür | Nerede |
|---|---|
| **Genel amaçlı çip boncuk** (geniş bant) | Sinyal hatları, düşük akımlı besleme |
| **Yüksek akım çip boncuğu** (düşük DCR) | Güç rayları |
| **GHz tipi boncuk** (yüksek frekansta keskin) | RF ve çok hızlı gürültü |
| **Boncuk dizisi (array)** | Paralel veri hatları |
| **Kablo ferriti** (geçme, toroid) | Kablodaki ortak mod akımı; EMC testinde hızlı çözüm |
| **Ortak mod bobini** (ilgili ama farklı) | Diferansiyel hatlar |

### Seçim adımları

1. Bastırmak istediğin **gürültünün frekans bandını** belirle.
2. O banttaki **Z'ye** eğriden bak; sadece 100 MHz değerine değil.
3. **DC akım** ve **DCR**: gerilim düşümü ve ısınma kabul edilebilir mi?
4. **DC bias eğrisi:** Çalışma akımında empedans ne kadar kalıyor?
5. Yükteki kapasitörlerle **LC rezonansını** hesapla.
6. Paketi seç.

## 3. Datasheet'te nelere bakılır?

| Parametre | Anlamı | Tuzak |
|---|---|---|
| **Z @ 100 MHz** | Tek noktadaki empedans | Gürültün başka frekansta olabilir |
| **Z–f eğrisi (R, X, Z)** | Tüm frekanslardaki davranış | R'nin baskın olduğu bölge yutma bölgesidir |
| **DCR** | DC direnci | Gerilim düşümü ve ısınma |
| **Anma akımı** | Isınma sınırı | O akımda empedans çok düşük olabilir |
| **DC bias eğrisi** | Akım altında empedans | Anma akımında empedans büyük ölçüde düşebilir |
| **Sıcaklık** | Çalışma aralığı | Empedans sıcaklıkla değişir |

## 4. Gerçek model

```
   ── R_DC ──┬──── L ────┬──
             ├── R_AC ───┤
             └── C_par ──┘
```

- **R_DC:** Sargının DC direnci (DCR).
- **L:** Düşük frekanstaki endüktans.
- **R_AC:** Frekansla artan manyetik kayıp; boncuğun "yutma" kısmı.
- **C_par:** Çok yüksek frekansta empedansı düşüren parazitik kapasitans.
- **DC akım** çekirdeğin geçirgenliğini düşürür; L ve R_AC birlikte azalır.

**Endüktansı eğriden tahmin etmek:** Endüktif bölgede bir nokta seç, `L ≈ X/(2πf)` hesapla. Örnek: 10 MHz'de X ≈ 30 Ω ise L ≈ **0,48 µH**.

## 5. Şematikte kullanım ve tipik devreler

### 5.1 Analog beslemeyi ayırma (VDDA)

```
  VDD ──[ Boncuk ]──┬──────┬──── VDDA (MCU)
                    │      │
                  [1 µF] [100 nF]
                    │      │
  GND ──────────────┴──────┴────
```

**Rezonans kontrolü (en çok atlanan adım):**
- Boncuk ≈ 0,48 µH, toplam kapasite 1 µF → `f_res ≈ 230 kHz`.
- `Z0 = √(L/C) ≈ 0,69 Ω`. Devredeki toplam direnç (seramiğin ESR'i birkaç mΩ + boncuğun DCR'si) Z0'dan çok küçükse **Q yüksektir** ve rezonansta gürültü büyür.
- **Asıl tehlike:** Kartta 500 kHz'de çalışan bir buck regülatör varsa, 230 kHz'lik rezonans tepesi onun ripple'ına çok yakındır. Filtre ripple'ı bastırmak yerine büyütebilir.

**Sönümleme yöntemleri (AN-1368):**
- Kapasitöre seri, Z0 mertebesinde küçük bir direnç (bulk kapasitör kolunda)
- Yüksek ESR'li bir bulk kapasitör (elektrolitik veya tantal) kullanmak
- Boncuğa paralel bir direnç
- Rezonans frekansını gürültü kaynağından uzağa taşıyacak değerler seçmek

**Kural:** Boncuklu filtreyi tasarladıktan sonra simüle et veya ölç.

### 5.2 I/O hat filtresi

```
 Konnektör ──[TVS]──[ Boncuk ]──┬──── MCU girişi
              │                 │
             GND             [100 pF]
                                │
                               GND
```

- Buton, LED, düşük hızlı UART gibi yavaş hatlar için uygundur.
- Filtre sinyalin yükselme süresini bozmamalı; hızlı hatlarda kenarları kontrol et.

### 5.3 Güç girişi filtresi

- Birkaç amperlik DC girişte yüksek akımlı boncuk veya güç bobini ile **π filtre** (C – L/boncuk – C) kullanılır.
- Büyük akımda boncuk ısınır ve doyar; o durumda güç bobini daha doğru seçimdir.

### 5.4 Kablo ferritleri

- Kablonun tamamını saran geçme (clamp-on) ferrit yalnızca **ortak mod akımını** etkiler. Kablodaki sinyal (diferansiyel akım) geçerken akılar birbirini götürür.
- EMC testinde sorunu teşhis etmek ve hızlı çözüm için çok kullanışlıdır. Kalıcı çözüm olarak kartta filtre veya CMC tercih edilir.

### 5.5 Kullanmaman gereken yerler

- **Toprak (GND) hattında:** Dönüş yolunu bozar, toprak gerilimi oynar, EMC kötüleşir.
- **Hızlı diferansiyel hatlarda tek tek:** USB D+/D− gibi hatlara ayrı boncuk koymak sinyali bozar; ortak mod bobini kullan.
- **Yüksek akımlı anahtarlamalı rayda:** Boncuk doyar ve işe yaramaz.

## 6. PCB / layout

- **Sınıra yerleştir:** Boncuk, gürültülü bölge ile temiz bölge arasına veya konnektör girişine konur.
- **Kapasitörler korunan tarafta,** yük pinine yakın olmalı; GND bağlantıları kısa olmalı.
- **Filtrenin girişini ve çıkışını yan yana götürme:** Gürültülü giriş izi, temiz çıkış izinin yanından paralel geçerse gürültü kapasitif ve endüktif kuplajla boncuğu **atlar**.

```
 KÖTÜ:  giriş ════════[B]════════ çıkış     (iki iz yan yana: kuplaj!)
        ═══════════════════════════════

 İYİ:   giriş ════[B]
                    ║
                    ╚═════════ çıkış        (giriş ve çıkış ayrı yönlerde)
```

- Yüksek akımlı boncuklarda ısınmaya dikkat et; bakır alan bırak.

## 7. EMC açısından

- Ferrit boncuk temelde bir **EMC komponentidir**. En etkili olduğu yer, kartın dış dünyaya açıldığı **konnektör girişleridir**.
- **Ortak mod ve diferansiyel mod:**
  - Tek bir hattaki boncuk, o hattan geçen her yüksek frekanslı akımı etkiler.
  - Kablonun tamamını saran ferrit yalnızca ortak mod akımını etkiler.
  - Bir çiftin iki hattına ayrı boncuk koymak, diferansiyel sinyali de zayıflatır. Diferansiyel hatlarda bu yüzden CMC kullanılır.
- **Ön test ipucu:** Işınımlı emisyonda bir tepe görüyorsan kabloya geçme ferrit tak. Tepe belirgin şekilde düşüyorsa sorunun kaynağı kablodaki ortak mod akımıdır.

## 8. Arıza modları ve sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| Yalnızca Z @ 100 MHz'e bakmak | Gürültü frekansında empedans düşük olabilir | Empedans eğrisi |
| DC bias'ı unutmak | Çalışma akımında empedans çok düşer | DC bias eğrisi, akım marjı |
| LC rezonansını hesaplamamak | Rezonansta gürültü büyür | Rezonansı hesapla, sönümle |
| Buck çıkışına boncuk + yalnız seramik | Rezonans f_sw'ye yakın düşebilir | Rezonansı f_sw'den uzaklaştır, sönümle |
| Diferansiyel hatta tek tek boncuk | Sinyal bozulur | Ortak mod bobini |
| GND'yi boncukla bölmek | Dönüş yolu bozulur, EMC kötüleşir | Kesintisiz GND |
| Filtre giriş ve çıkış izlerini yan yana çizmek | Kuplaj filtreyi atlar | İzleri ayır |
| Yüksek akımda boncuk | Isınma, gerilim düşümü, doyma | Düşük DCR'li tip veya güç bobini |

## 9. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Ferrit boncuk** | Yüksek frekansta dirençsel davranan kayıplı indüktör |
| **Z @ 100 MHz** | Boncuğun 100 MHz'deki empedansı; katalog değeri |
| **R / X kesişimi** | Boncuğun dirençsel (yutma) bölgesinin başladığı frekans |
| **DC bias** | DC akımın empedansı düşürmesi |
| **DCR** | DC direnci |
| **Q** | Kalite faktörü; rezonans tepesinin sivriliği |
| **Sönümleme (damping)** | Rezonans tepesini düşürmek için kayıp eklemek |
| **Z0** | LC devresinin karakteristik empedansı, √(L/C) |
| **π filtre** | C – L – C yapısındaki filtre |
| **Kablo ferriti** | Kabloyu saran, ortak mod akımını bastıran ferrit |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki madde [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.2, bölüm 10):

- [x] Ferrit boncuk: gürültü frekansında Z ve çalışma akımında DC bias kontrol edildi; LC rezonansı hesaplandı ve sönümlendi

## Kontrol soruları

→ [quiz.md](quiz.md) · 11 soru, 4'ü hesap
