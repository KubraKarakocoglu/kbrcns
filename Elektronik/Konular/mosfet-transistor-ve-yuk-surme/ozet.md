# MOSFET, transistör ve yük sürme

- **Oluşturma:** 2026-10-16
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Bağlantılı:** [Bobin (flyback diyotu)](../../Komponentler/03-bobin-induktor/ozet.md) · [Direnç (LED akım sınırlama, pull-down)](../../Komponentler/01-direnc/ozet.md#52-led-akım-sınırlama) · [Mikrodenetleyici donanımı (GPIO)](../../Komponentler/05-mikrodenetleyici-donanimi/ozet.md#6-gpio) · Kontrol listesi bölüm 5 ve 12

> Sayısal değerler **tipik başlangıç noktalarıdır**; tasarım değeri için kullandığın MCU'nun ve anahtarın datasheet'i esastır.
>
> **Okuma planı:** 1. oturum: bölüm 1–6 (anahtarlar) · 2. oturum: 7–11 (röle, buzzer, LED, solenoid, PWM) · 3. oturum: 12–17.

---

## ⚡ Hızlı tekrar

1. MCU pini **zayıftır** (tipik birkaç mA – 20 mA, datasheet'e bak). Röle, buzzer, solenoid gibi yükleri doğrudan süremez; araya bir **anahtar** girer: transistör veya MOSFET.
2. En basit yöntem **low-side** anahtardır: yük artı ile anahtar arasında, anahtar GND tarafında. N-MOSFET veya NPN.
3. MOSFET seçerken **Vgs(th)'e değil**, MCU geriliminde belirtilmiş **R_DS(on)**'a bak (2,5 V veya 4,5 V'ta belirtilmiş "logic level" MOSFET).
4. Gate'e **seri direnç** (10–100 Ω) ve gate'ten GND'ye **pull-down** (10–100 kΩ). Pull-down, açılışta MCU pini boştayken yükü **kapalı** tutar (fail-safe).
5. Transistör (BJT) **doyuma** sokulmalı: `Ib ≈ Ic / 10`. Datasheet'teki büyük β'ya güvenme.
6. **Endüktif yük** (röle, solenoid, manyetik buzzer, motor) = **flyback diyotu**. Yoksa kapanışta oluşan gerilim sıçraması anahtarı öldürür.
7. Kayıp: MOSFET'te `I² × R_DS(on)`, BJT'de `Vce(sat) × I`. Her anahtarın ısısını hesapla.
8. Güvenlik çıkışlarında (alarm, kapı kilidi) **arıza ve enerji kesintisinde ne olacağını** bilinçli seç. Açılış anında hiçbir yük kendiliğinden çalışmamalı.

## 🧮 Formül kartı

| Formül | Ne zaman kullanılır | Örnek |
|---|---|---|
| `R_LED = (V_kaynak − V_F) / I_LED` | LED seri direnci | (3,3 − 2,0) V / 5 mA → **260 Ω** → 270 Ω |
| `I_bobin = V_bobin / R_bobin` | Röle/solenoid akımı | 12 V / 400 Ω → **30 mA** |
| `Ib = Ic / β_zorlanmış` (β_z ≈ 10) | BJT'yi doyuma sokmak | 30 mA / 10 → **3 mA** |
| `Rb = (V_pin − 0,7 V) / Ib` | BJT baz direnci | (3,3 − 0,7) / 3 mA → **867 Ω** → 820 Ω |
| `P = I² × R_DS(on)` | MOSFET iletim kaybı | 1 A, 50 mΩ → **50 mW** |
| `P = Vce(sat) × I` | BJT iletim kaybı | 0,2 V × 0,1 A → **20 mW** |
| `t_geçiş ≈ Qg / I_gate` | Gate'in dolma süresi (kaba) | 10 nC / 10 mA → **1 µs** |

---

## 1. Neden araya bir anahtar girer?

MCU pini bir **parmak** gibidir: düğmeye basabilir ama ağır bir kapıyı itemez. Kapıyı **kapı otomatiği** (motor) açar; parmak sadece onun düğmesine basar. Transistör ve MOSFET, MCU'nun parmağıyla büyük yükü çalıştıran o "otomatik"tir.

| Yük | Tipik akım | MCU pini sürebilir mi? |
|---|---|---|
| Gösterge LED'i | 1–5 mA | Evet (seri dirençle) |
| Röle bobini (12 V) | 20–40 mA, 12 V | Hayır (gerilim de akım da yüksek) |
| Buzzer | 10–100 mA | Hayır |
| Kapı otomatiği / solenoid | 0,3–2 A | Kesinlikle hayır |
| Sensör ısıtıcısı | 50–300 mA | Hayır |

**Ayrıca:** MCU'nun **toplam port akımı** sınırlıdır (tek tek pinler sınırın altında olsa bile toplamı aşmamalı). Datasheet'te "total current into VDD / out of VSS" satırına bak.

## 2. Low-side ve high-side

```
Low-side (en yaygın)                 High-side

 +V ──┬──                             +V ── [ANAHTAR] ──┬──
     [YÜK]                                               [YÜK]
      │                                                   │
  [ANAHTAR] ← MCU                                        GND
      │
     GND
```

| | Low-side | High-side |
|---|---|---|
| Anahtar | N-MOSFET veya NPN | P-MOSFET veya özel "load switch" IC |
| Sürmesi | Kolay: gate/baz doğrudan MCU'dan | Daha zor: seviye çevirici gerekir |
| Yükün durumu | Kapalıyken yük +V'ta kalır | Kapalıyken yük GND'de kalır |
| Ne zaman | Röle, buzzer, LED, solenoid | Yükün bir ucu GND'ye bağlı olmak zorundaysa; kablo dışarı gidiyor ve kısa devrede yükün beslenmemesi isteniyorsa |

## 3. N-MOSFET seçimi

MOSFET'i bir **musluk** gibi düşün: gate'e uygulanan gerilim musluğu açar; R_DS(on) musluk tam açıkken kalan küçük dirençtir.

| Parametre | Anlamı | Seçim kuralı |
|---|---|---|
| **V_DS** | Drain–source dayanımı | ≥ 1,5–2 × besleme (endüktif yükte sıçramaları da düşün) |
| **I_D** | Sürekli akım | Gerçek akımın rahatça üstü (datasheet'teki değer ideal soğutmalıdır) |
| **R_DS(on) @ Vgs** | Açıkken direnç | **MCU gerilimindeki** değere bak: 3,3 V MCU → 2,5 V'ta belirtilmiş R_DS(on) |
| **Vgs(th)** | Açılmaya **başladığı** gerilim | Tek başına seçim kriteri değildir (aşağıya bak) |
| **Vgs(max)** | Gate dayanımı (tipik ±8 V, ±12 V veya ±20 V) | Gate'e gelecek en yüksek gerilimin üstünde |
| **Qg** | Gate'i doldurmak için gereken yük | PWM'de anahtarlama hızını belirler |
| **Paket / θJA** | Isıyı ne kadar atabildiği | `P = I² × R_DS(on)` ile kontrol |

> **En yaygın tuzak – Vgs(th):** Datasheet'te "Vgs(th) = 1,5 V" yazıyorsa bu, MOSFET'in **çok küçük bir akım** (ör. 250 µA) geçirmeye başladığı gerilimdir; tam açık olduğu gerilim değildir. 3,3 V'luk bir MCU ile sürülecek MOSFET'te datasheet'in R_DS(on) tablosunda **2,5 V veya 3,3 V** satırı olmalı. Yoksa MOSFET yarı açık kalır, ısınır ve yanar.

**Örnek:** 3,3 V MCU, 12 V / 0,5 A solenoid.
- V_DS ≥ 30 V (12 V × 2 + sıçrama marjı).
- R_DS(on) @2,5 V ≤ 100 mΩ → `P = 0,5² × 0,1 = 25 mW`. SOT-23 rahat taşır.

## 4. Gate direnci ve pull-down

```
 MCU pin ──[ R_G 100 Ω ]──┬──── G
                          │         Q1 (N-MOSFET)
                       [ R_PD 100 kΩ ]
                          │
                         GND
```

- **R_G (seri, 10–100 Ω):** Gate bir kapasitör gibidir; ilk anda büyük akım çeker. R_G bu akımı sınırlar, MCU pinini korur ve kenarı biraz yumuşatarak çınlamayı (ringing) ve EMI'yi azaltır.
- **R_PD (pull-down, 10–100 kΩ):** Reset ve açılış sırasında MCU pinleri **yüksek empedanstadır** (boşta). Boştaki gate gürültü kapar; MOSFET yarı açılabilir (ısınır) veya röle açılışta "tık" diye çeker. Pull-down gate'i kesin olarak kapalı tutar. **Gate tarafına** (R_G'nin MOSFET tarafına) koy.

> **Fail-safe başlangıç:** Kart enerjilendiği anda, firmware daha çalışmadan, hiçbir yük kendiliğinden çalışmamalı. Kapı kilidi açılmamalı, alarm çalmamalı, ısıtıcı yarım açık kalmamalı. Bunun donanımsal garantisi pull-down/pull-up dirençleridir.

## 5. Transistör (NPN) ile sürme

Küçük akımlarda (yaklaşık 200 mA'e kadar) NPN transistör ucuz ve yeterli bir anahtardır.

```
 +12V ──┬────────────┐
      [RÖLE]        [D]   flyback diyotu, katot +12V tarafında
        ├────────────┘
        │
        C
        Q1 (NPN)
        B ◄── baz devresi (aşağıda)
        E
        │
       GND

 Baz devresi:  MCU ──[Rb 820 Ω]── B      B ──[10 kΩ]── GND
```

**Hesap (12 V, 400 Ω röle bobini):**
1. Bobin akımı: `Ic = 12 / 400 = 30 mA`.
2. Doyuma sokmak için: `Ib = Ic / 10 = 3 mA`. Datasheet'teki β (ör. 100–300) **doyumu garanti etmez**; doyumda transistör "anahtar" gibi davranır ve Vce(sat) küçük kalır (≈ 0,1–0,3 V).
3. `Rb = (3,3 − 0,7) / 3 mA ≈ 867 Ω` → **820 Ω** (bir alt standart değer, biraz daha fazla baz akımı).
4. Baz ile emiter arasına **10 kΩ pull-down**: açılışta transistörü kapalı tutar.

**Çok sayıda röle:** ULN2003 gibi Darlington dizileri 7 kanalı tek pakette verir ve flyback diyotlarını içinde barındırır; **COM pinini röle beslemesine** bağlamak şarttır, yoksa diyotlar devre dışı kalır. Dezavantajı: Darlington'ın doyum gerilimi ~1 V'tur, ısınır.

## 6. High-side sürme

Yükün bir ucunun GND'ye bağlı kalması gerekiyorsa (ör. kablo ile dışarı giden bir besleme) high-side anahtar gerekir.

```
 +V ──────┬────────────┐
          │            S
       [R1 10k]        Q2 (P-MOSFET)
          │            G
          ├────────────┘
          │
       [R2 1k]
          │
          C
          Q1 (NPN)
 MCU ─[1k]─ B
          E
          │
         GND

 Q2'nin D ucu → yük → GND
```

- Q1 kapalıyken R1, gate'i source'a çeker → Vgs = 0 → P-MOSFET **kapalı** (fail-safe).
- MCU Q1'i açınca gate GND'ye yaklaşır → Vgs ≈ −V → P-MOSFET açılır.
- **V, gate dayanımını aşıyorsa** (24 V'ta ±20 V aşılır) R1–R2'yi bölücü olarak boyutlandır veya gate–source arasına Zener koy (güç katı dersindeki gibi).
- Alternatif: **load switch IC.** Akım sınırlama, yumuşak açılış ve termal koruma içinde gelir; sensör beslemesini aç/kapa yapmak için idealdir.

## 7. Röle

| Parametre | Dikkat |
|---|---|
| Bobin gerilimi / direnci | Akım = V / R. Bobin gücü ısı demektir |
| Kontak değeri | **AC ve DC değerleri farklıdır**: "10 A 250 VAC" yazan röle DC'de çoğu zaman yalnızca 30 VDC'ye kadar 10 A taşır |
| Yük türü | Endüktif ve lamba yükleri kontakları daha hızlı aşındırır; datasheet'teki ömür eğrisine bak |
| Yalıtım | Bobin (düşük gerilim) ile kontak (şebeke olabilir) arası mesafe kartta da korunmalı |

**Neden DC'de kontak değeri düşer?** AC akım her yarım periyotta sıfırdan geçer ve kontak açılırken oluşan ark kendiliğinden söner. DC'de sıfır geçişi yoktur; ark devam eder ve kontağı yakar.

**Bobin tarafı:** Flyback diyotu bobine paralel, katodu artı tarafta ([Bobin dersi](../../Komponentler/03-bobin-induktor/ozet.md)). Diyot, rölenin bırakmasını yavaşlatır; hızlı bırakma gerekirse diyota seri Zener eklenir.

**Kontak tarafı:** AC endüktif yükleri (kontaktör, motor) kesen kontaklarda **RC snubber** veya varistör kontak ömrünü uzatır ve EMI'yi azaltır.

**Güvenlik röleleri (alarm, arıza):** Rölenin **normalde enerjili mi, enerjisiz mi** çalışacağı bilinçli bir karardır.
- **Normalde enerjili** röle: Kart enerjisini kaybederse veya bobin kopar ise röle bırakır → arıza **kendini gösterir** (fail-safe). Arıza (fault) rölelerinde yaygın.
- **Normalde enerjisiz** röle: Az enerji tüketir; ama besleme kesilirse alarm verilemez.
- Hangisinin kullanılacağını ürün standardı ve müşteri şartnamesi belirler; seçimi şematikte not et.

## 8. Buzzer

| Tür | Nasıl çalışır | Nasıl sürülür |
|---|---|---|
| **Gösterge (indicator), dahili osilatörlü** | DC verince kendi frekansında öter | Low-side anahtar ile aç/kapa |
| **Dönüştürücü (transducer), piezo** | Kendi osilatörü yok; ses frekansında sürülmeli | MCU timer'ından **rezonans frekansında** PWM (tipik 2–4 kHz; datasheet) |
| **Dönüştürücü, manyetik** | Küçük bir bobin; endüktif | PWM + **flyback diyotu** |

- **Ses seviyesi** sürme gerilimiyle artar. Piezo'yu tek uçtan değil, **iki pinden ters fazda** (köprü) sürmek gerilim salınımını iki katına çıkarır ve sesi belirgin artırır.
- Alarm ürünlerinde gereken ses seviyesi (ör. 1 m'de belirli bir dB(A)) ürün standardında yazar; buzzer'ı bu değere göre seç ve ölç.
- Rezonans frekansının dışında sürülen piezo çok kısık çıkar. Frekansı datasheet'ten al, gerekirse ölçerek ayarla.

## 9. LED

`R = (V_kaynak − V_F) / I_LED`

| Renk | Tipik V_F | 3,3 V'tan sürülünce |
|---|---|---|
| Kırmızı, sarı | 1,8–2,2 V | Rahat: 5 mA → ~270 Ω |
| Yeşil (yeni tip), mavi, beyaz | 2,7–3,3 V | **Sorunlu:** baş boşluğu çok az, akım V_F'ye göre çok değişir |

- Modern LED'ler **1–5 mA** ile yeterince parlaktır; 20 mA çoğu zaman gereksizdir.
- Mavi/beyaz LED'i 3,3 V'tan sürmek yerine 5 V'tan ve bir transistörle sür, veya sabit akım kaynağı kullan.
- Çok sayıda LED için tarama (multiplexing) yapılabilir; kod çözücü ya da shift register ile pin tasarrufu sağlanır ([Haberleşme arayüzleri dersi](../haberlesme-arayuzleri/ozet.md)).
- Ayrıntılı hesap: [Direnç dersi](../../Komponentler/01-direnc/ozet.md#52-led-akım-sınırlama).

## 10. Solenoid ve kapı otomatiği

Diafon ve kartlı geçiş sistemlerindeki kapı otomatiği bir **solenoiddir**: güçlü bir bobin.

- **Akım:** 12 V'luk tipik bir kilit 0,3–1,5 A çeker. Besleme bu darbeyi kaldırmalı; uzun kabloda gerilim düşümünü hesapla.
- **Sürme:** DC kilit → N-MOSFET (low-side) + **flyback diyotu**. AC kilit (ör. 12 VAC) → röle veya triyak.
- **Isı:** Solenoidler sürekli enerjilenmeye göre tasarlanmamış olabilir. Firmware'de **en uzun açık kalma süresi** (ör. birkaç saniye) olsun.
- **Güvenlik:** Açılışta, reset'te veya firmware takıldığında kilit **kendiliğinden açılmamalı**. Gate pull-down + watchdog + zaman aşımı birlikte kullanılır.
- **Kablo dışarı gidiyorsa:** Flyback diyotu kartta, konnektörün yanında; ayrıca TVS. Kablo bir anten ve darbe giriş yoludur.

## 11. PWM ile sürme

PWM, anahtarı çok hızlı açıp kapayarak ortalama gücü ayarlar: LED parlaklığı, buzzer tonu, ısıtıcı gücü.

- **Anahtarlama hızı:** Gate bir kapasitördür. `t ≈ Qg / I_gate`: 10 nC'lik bir MOSFET'i ~10 mA verebilen bir MCU pini ~1 µs'de açar. Birkaç kHz'lik PWM için yeterli; 100 kHz ve üstü için **gate sürücü** IC gerekir.
- **Yavaş geçiş = ek kayıp:** Geçiş sırasında MOSFET ne tam açık ne tam kapalıdır; hem gerilim hem akım vardır. Frekans arttıkça bu kayıp artar.
- **EMC dengesi:** Yumuşak kenar daha az gürültü üretir ama daha çok ısınır. Gerekenden hızlı kenar kullanma (R_G ile ayarlanır).

## 12. Isı ve güvenli çalışma alanı

- Her anahtar için `P = I² × R_DS(on)` (MOSFET) veya `P = Vce(sat) × I` (BJT) hesapla; paketin θJA'sıyla sıcaklığı bul.
- **Lineer bölge tehlikesi:** Gate gerilimi yetersizse MOSFET yarı açık kalır; üzerinde hem gerilim hem akım olur ve hızla ısınır. Bu, R_DS(on) hesabının geçersiz olduğu durumdur.
- **Kapasitif ve lamba yükleri:** İlk anda çok büyük akım çekerler (inrush). Datasheet'teki **SOA** (güvenli çalışma alanı) grafiğiyle kontrol et.

## 13. Şematikte

- Her sürme devresinin yanına **yük akımı, anahtarın R_DS(on)/Vce(sat) değeri ve kaybı** notu.
- Gate ve baz pull-down'ları **"kaldırma: açılışta yük kapalı"** notu ile.
- Endüktif her yükte flyback diyotu; dışarı giden hatlarda TVS.
- Röle kontaklarının akım/gerilim değeri (AC/DC) ve rölenin enerjili/enerjisiz çalışma şekli yazılı.
- Buzzer tipi (indicator / transducer) ve sürme frekansı yazılı.

## 14. PCB / layout

- **Yüksek akım döngüsü küçük:** besleme → yük → MOSFET → GND → besleme döngüsünün alanı küçük olsun; GND dönüşü hassas analog bölgeden geçmesin.
- **Flyback diyotu yüke yakın** (kart üstündeki röle için bobinin dibinde).
- Akım taşıyan izlerin genişliği ve röle kontak tarafının izolasyon mesafeleri: [PCB yerleşim dersi](../pcb-yerlesim-ve-iz-cizimi/ozet.md).
- Isınan MOSFET ve dirençlere bakır alan; sensörden ve elektrolitikten uzak.

## 15. EMC açısından

- Endüktif yük kapanışındaki sıçrama, en güçlü gürültü kaynaklarından biridir; flyback diyotu ve snubber bu gürültüyü kaynağında keser.
- Hızlı kenarlar geniş spektrum üretir; R_G ile kenarı ihtiyaç kadar yavaşlat.
- Kablo ile dışarı giden çıkışlarda (röle kontağı, kilit, buzzer kablosu) EFT ve surge testlerini düşün: TVS, ferrit, gerekiyorsa RC ([EMC 03](../../EMC/03-emc-testleri-ve-standartlar/ozet.md)).

## 16. Ölçüm ve doğrulama

1. **Kapanış sıçraması:** Osiloskopla MOSFET drain'ine bak, yükü kapat. Tepe gerilim V_DS dayanımının güvenli altında mı?
2. **Açılış testi:** Kartı defalarca aç-kapa; röle tıklıyor mu, buzzer ötüyor mu, kilit açılıyor mu? Gate'i osiloskopla izle.
3. **Sıcaklık:** En yüksek yük ve ortam sıcaklığında anahtarın sıcaklığını ölç.
4. **Ses seviyesi:** Buzzer'ı standarttaki mesafeden ölç (ses ölçer).
5. **Reset sırasında:** Firmware'i debug'da durdur veya MCU'yu reset'te tut; yükler kapalı kalıyor mu?

## 17. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| Vgs(th)'ye bakıp MOSFET seçmek | 3,3 V'ta yarı açık kalır, ısınır | R_DS(on) @2,5 V / 3,3 V |
| Gate pull-down yok | Açılışta yük kendiliğinden çalışır | 10–100 kΩ gate–GND |
| Flyback diyotu yok veya ters | Kapanışta anahtar yanar / diyot kısa devre gibi davranır | Bobine paralel, katot artıda |
| BJT'yi β ile hesaplamak | Doyuma girmez, ısınır | `Ib = Ic/10` |
| ULN2003'te COM bağlı değil | İç flyback diyotları çalışmaz | COM → röle beslemesi |
| Röleyi AC değeriyle DC yükte kullanmak | Kontak arkla yanar | DC kontak değerine bak |
| Piezo transducer'a DC vermek | Ses çıkmaz | Rezonans frekansında PWM |
| Mavi/beyaz LED'i 3,3 V'tan dirençle sürmek | Parlaklık parçadan parçaya çok değişir | 5 V'tan sür veya sabit akım |
| Solenoide süre sınırı koymamak | Firmware takılırsa bobin yanar | Firmware'de zaman aşımı + watchdog |
| MCU toplam port akımını aşmak | MCU ısınır, kararsızlaşır | Datasheet'teki toplam akım sınırı |

## 18. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Low-side / high-side** | Anahtarın yükün GND tarafında / besleme tarafında olması |
| **R_DS(on)** | MOSFET tam açıkken drain–source direnci |
| **Vgs(th)** | MOSFET'in çok küçük akım geçirmeye başladığı gate gerilimi |
| **Logic level MOSFET** | R_DS(on)'u düşük gate geriliminde (2,5 V / 4,5 V) belirtilmiş MOSFET |
| **Qg** | Gate'i tam doldurmak için gereken toplam yük |
| **Doyum (saturation)** | BJT'nin tam açık, Vce'nin en küçük olduğu durum |
| **Zorlanmış β** | Doyumu garantilemek için seçilen Ic/Ib oranı (≈ 10) |
| **Flyback diyotu** | Endüktif yük kapanınca akıma yol vererek sıçramayı kenetleyen diyot |
| **Snubber** | Kontak veya anahtar üzerindeki sıçramayı sönümleyen RC devresi |
| **Load switch** | Akım sınırlamalı, hazır high-side anahtar IC'si |
| **SOA** | Güvenli çalışma alanı: gerilim–akım–süre sınırları |
| **Fail-safe** | Arıza veya enerji kesintisinde güvenli duruma düşen tasarım |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.4, yeni bölüm 12 "Yük sürme"):

> Logic-level MOSFET ve gate pull-down maddeleri zaten bölüm 5'te, flyback diyotu bölüm 10'da.

- [x] MCU'nun pin başına ve toplam port akımı sınırları aşılmıyor
- [x] BJT'ler doyumda (Ib ≈ Ic/10); her anahtarın kaybı ve sıcaklığı hesaplandı
- [x] ULN2003 tipi dizilerde COM pini röle beslemesine bağlı
- [x] Röle kontak değeri yük türüne (AC/DC, endüktif) uygun; rölenin enerjili/enerjisiz çalışma şekli bilinçli seçildi
- [x] Buzzer tipi doğru sürülüyor (transducer → rezonans frekansında PWM); ses seviyesi standarda göre doğrulanacak
- [x] Solenoid/kilit çıkışlarında firmware zaman aşımı ve kablo tarafında TVS var

## Kontrol soruları

→ [quiz.md](quiz.md) · 10 soru, 4'ü hesap
