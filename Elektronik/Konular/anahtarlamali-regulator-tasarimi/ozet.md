# Anahtarlamalı regülatör tasarımı: buck, boost ve ters buck-boost

- **Oluşturma:** 2026-11-20
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Bağlantılı:** [Güç katı: koruma ve regülatör](../guc-kati-koruma-ve-regulator/ozet.md) · [Şebekeli güç kaynakları](../sebekeli-guc-kaynaklari/ozet.md) · [MOSFET, transistör ve yük sürme](../mosfet-transistor-ve-yuk-surme/ozet.md) · [PCB yerleşim ve iz çizimi](../pcb-yerlesim-ve-iz-cizimi/ozet.md) · [Kapasitör](../../Komponentler/02-kapasitor/ozet.md) · [Bobin](../../Komponentler/03-bobin-induktor/ozet.md) · [Ferrit boncuk](../../Komponentler/04-ferrit-boncuk/ozet.md) · [EMC için kart tasarımı](../../EMC/02-emc-icin-kart-tasarimi/ozet.md) · Sonraki: LED sürücü (Ders 5, hazırlanıyor)

> Sayısal değerler **tipik başlangıç noktalarıdır**. Buck, boost ve ters buck-boost formülleri TI uygulama notlarındaki (SLVA477, SLVA372C, SLVA059) ifadelerle karşılaştırıldı; bütün örnekler betikle ve **zaman alanı benzetimiyle** (ideal anahtarlı devrenin kararlı hâl çözümü) yeniden hesaplandı. IC'ye ait değerler (akım limiti, `g_m`, minimum açık kalma süresi, `Q_g` gibi) **varsayımdır**: **kendi parçanın datasheet'i esastır**. **Kapsam dışı:** izolasyonlu topolojiler ([Ders 3](../sebekeli-guc-kaynaklari/ozet.md)), PFC, çok fazlı ve dijital kontrol, 100 W üstü, harici FET kapı sürücüsü tasarımı, EMC sertifikasyonu.
>
> **Okuma planı:** 1. oturum: bölüm 1–4 (neden, topoloji, temel fikir, buck tasarımı) · 2. oturum: 5–8 (boost, ters buck-boost, kayıplar, hafif yük) · 3. oturum: 9–11 (döngü, koruma, giriş hattı) · 4. oturum: 12–18 (iş yeri, şematik, PCB, EMC, ölçüm, hatalar, sözlük).

---

## ⚡ Hızlı tekrar

1. LDO fazla gerilimi **ısıya** çevirir, anahtarlamalı regülatör **paketler hâlinde** taşır. 24 V → 5 V, 1 A: LDO'da **19,0 W** ısı (verim %20,8), buck'ta **0,42 W** (verim %92,3).
2. Üç temel topoloji aynı hücrenin üç yerleşimidir: **buck** `V_out = D·V_in`, **boost** `V_out = V_in/(1−D)`, **ters buck-boost** `V_out = −V_in·D/(1−D)`. Hepsi tek kuraldan çıkar: kararlı hâlde **indüktör geriliminin ortalaması sıfırdır** (volt-saniye dengesi).
3. İndüktör **volan**, kapasitör **su deposudur**: akım ve gerilim ani değişmez. `ΔI_L = V_L·t/L`; tasarım hedefi `ΔI_L = 0,2–0,4 · I_out` (boost'ta `I_L,ort`).
4. Örnek A (24 V → 5 V / 1 A / 500 kHz): `L ≥ 27,8 µH` → **33 µH**, `ΔI_L = 0,25 A` (30 V'ta en kötü), tepe `1,13 A`, `I_MAXOUT = 1,57 A`; indüktör `I_sat ≥ 2,64 A` (IC akım limiti üst sınırı + %10).
5. Seramik kapasitörün etkin değeri DC bias'la düşer: 44 µF nominal → **24,2 µF** (%55 varsayımı). Çıkış dalgalanması `ΔV = ΔI/(8·f_s·C) + ESR·ΔI` = **3,4 mV**; belirleyici olan genelde **yük bırakma aşımıdır**, dalgalanma değil.
6. Giriş kapasitörü darbeli akım çeker: `I_Cin,rms = I_out·√(D(1−D))`, en kötü **`I_out/2`** (D = 0,5). Giriş kapasitörü yalnız "gerilim filtresi" değil, **akım deposudur**.
7. **Minimum açık kalma süresi** frekansı sınırlar: `V_in,maks ≤ V_out/(f_s·t_on,min)`. 5 V çıkış, 100 ns için 500 kHz'te **100 V**, 2 MHz'te **25 V**: 30 V girişte 2 MHz çalışmaz.
8. **Boost'un RHPZ'si** vardır: `f_RHPZ = R_L·(1−D)²/(2π·L)` = **88 kHz** (3,0 V → 5 V / 0,5 A). Döngü `f_c ≤ f_RHPZ/5` = **18 kHz**'e iner: boost **yavaştır**. Boost'ta kapalıyken giriş çıkışa bağlı kalır, kısa devre izolasyonu yoktur.
9. Kayıp: iletim + anahtarlama + sabit. Örnek A'da **419 mW**; en büyük kalemler indüktör DCR (%24), LS iletim (%23), HS anahtarlama (%21). Hafif yükte verimi **sabit kayıp tabanı** (85 mW) belirler: 10 mA'de verim %36,7.
10. Kompanzasyon (peak-current-mode buck, Tip II): `f_c = f_s/10` = **48 kHz**, `R_c = 9,5 kΩ`, `C_c = 1,67 nF`, faz payı **55°**. `f_c` arttıkça faz payı hızla düşer (55° → 14°, `f_c/f_s` %10 → %30).
11. Giriş hattı bir **LC devresidir**: 24 V adım, kablo + seramik kapasitörde **43 V**'a (×1,79) çıkar; Al-elektrolitik **damper** ile 28 V. Anahtarlamalı regülatör giriş filtresine **negatif direnç** gibi görünür: `|R_in| = V_in²/P_in`.
12. Yerleşimde en önemli şey **sıcak döngü**dür (C_in–HS–LS): 20 nH/inç kuralıyla 3 inçlik iz **60 nH** ve 30 ns'de 1 A için **2,0 V** demektir. Küçük döngü = az zil, az EMI, IC'nin mutlak maksimumuna uzak.

## 🧮 Formül kartı

| Formül | Ne zaman kullanılır | Örnek |
|---|---|---|
| `D = V_out/(V_in·η)` | Buck görev oranı | 24 V: **0,231** (ideal 0,208) |
| `ΔI_L = (V_in − V_out)·D/(L·f_s)` | Buck indüktör dalgalanması | 33 µH, 500 kHz: **0,24 A** (24 V), **0,25 A** (30 V) |
| `L = V_out·(V_in,maks − V_out)/(ΔI_L·V_in,maks·f_s)` | Buck indüktör seçimi | `ΔI_L = 0,3 A` → **27,8 µH** |
| `I_pk = I_out + ΔI_L/2`, `I_MAXOUT = I_LIM,min − ΔI_L/2` | Doyma akımı, çıkış akımı sınırı | **1,13 A**, **1,57 A** |
| `ΔV_out ≈ ΔI_L/(8·f_s·C_eff) + ESR·ΔI_L` | Çıkış dalgalanması | **3,4 mV** |
| `C_out ≥ L·ΔI_yük²/(2·V_out·V_aşım)` | Yük bırakma aşımı | 1 A, %5 → **13,2 µF** |
| `I_Cin,rms = I_out·√(D·(1−D))` | Buck giriş kapasitörü | 18 V: **0,448 A**; en çok `I_out/2` |
| `V_in,maks = V_out/(f_s·t_on,min)` | Minimum açık kalma | 500 kHz: **100 V** |
| `D = 1 − V_in,min·η/V_out` | Boost görev oranı | **0,49** (η = %85) |
| `I_L,ort = I_out/(1−D)`, `ΔI_L = V_in·D/(f_s·L)` | Boost indüktör akımı | **0,98 A**, **0,31 A** (4,7 µH, 1 MHz) |
| `I_MAXOUT = (I_LIM,min − ΔI_L/2)·(1−D)` | Boost çıkış akımı sınırı | **0,79 A** |
| `f_RHPZ = R_L·(1−D)²/(2π·L)` | Boost `f_c` sınırı | **88,1 kHz** → `f_c ≤` **17,6 kHz** |
| `D = V_out/(V_in+V_out)`, `I_L,ort = I_out/(1−D)` | Ters buck-boost | +5 V → −5 V: **0,50**, **0,40 A** |
| `P_iletim = I_rms²·R`, `P_sw ≈ ½·V·I·t_sw·f_s`, `P_g = Q_g·V_drv·f_s` | Kayıp bütçesi | **41,9 mW**, **90 mW**, **5 mW** |
| `η = P_out/(P_out + P_kayıp)` | Verim | **%92,3** (24 V, 1 A) |
| `f_p = 1/(2π·R_L·C_eff)` | Peak-current-mode tek kutup | 5 Ω, 24,2 µF: **1315 Hz** |
| `R_c = f_c/(f_p·g_m·A_fb·A_dc)`, `C_c = 5/(2π·f_c·R_c)` | Tip II kompanzasyon | **9,5 kΩ**, **1,67 nF** |
| `V_on = V_EN·(1 + R_t/R_b)` | UVLO bölücüsü | 124 k / 10 k: **16,1 V** |
| `R_t = R_b·(V_out/V_ref − 1)` | Geri besleme bölücüsü | 0,8 V ref: **52,5 kΩ** |
| `I_açılış = C_out·V_out/t_ss` | Soft-start akımı | 44 µF, 2 ms: **110 mA** |
| `ζ = (R_s/2)·√(C/L)`, `V_tepe = V·(1 + e^(−π·ζ/√(1−ζ²)))` | Hot-plug tepe gerilimi | **43,0 V** (24 V adım) |
| `\|R_in\| = V_in²/P_in`, marj `20·log₁₀(\|R_in\|/\|Z_out\|) ≥ 6 dB` | Giriş filtresi kararlılığı | **60 Ω** (18 V) |
| `V = L_loop·dI/dt` | Sıcak döngü gerilim sıçraması | 60 nH, 1 A/30 ns: **2,0 V** |

---

## 1. Neden anahtarlamalı regülatör?

Bir yokuş aşağı bisikletin hızı 24 km/s, sen ise 5 km/s ile gitmek istiyorsun:
- **LDO (doğrusal regülatör) = fren.** Fazla hızı fren balatasında **ısıya** çevirir. Sessiz, basit, temizdir; ama giden enerji boşa gider.
- **Anahtarlamalı regülatör = pedalı zamanlı itmek.** Enerjiyi küçük **paketler** hâlinde verirsin; paketler arasında **volan** (indüktör) hızı düzgün tutar. Fazla enerji ısıya değil, kaynakta **kalır**.

Aynı iş, 24 V → 5 V, 1 A:

| | LDO | Buck (bölüm 7 modeli) |
|---|---|---|
| Kayıp | (24 − 5) · 1 = **19,0 W** | **0,42 W** |
| Verim | %20,8 | %92,3 |
| 30 V girişte | 25,0 W, %16,7 | verim bölüm 7'de |
| Isınma, `θ_JA = 50 °C/W` varsayımıyla | ≈ **950 °C** (imkânsız) | IC'de ≈ **14,7 °C** |

LDO **kötü** değildir; doğru yerde en iyi seçimdir:
- **Fark küçükse:** Li-ion 4,2 V → 3,3 V'ta `η = V_out/V_in` = %78,6; akım küçükse bu ısı kabul edilir.
- **Akım µA–mA'sa:** anahtarlamalının kendi kayıpları (bölüm 7) bu akımda LDO'dan kötü olabilir.
- **Gürültü kritikse:** LDO'da anahtarlama dalgalanması ve EMI yoktur. Hassas analog (ADC referansı, sensör köprüsü) için sık görülen çözüm **buck + LDO** zinciridir: buck verimi, LDO temizliği getirir. LDO'nun besleme reddi (PSRR) anahtarlama frekansında genelde düşüktür; buck ile LDO arasına LC ya da ferrit filtre koy.

| Ölçüt | LDO | Anahtarlamalı |
|---|---|---|
| Verim | `V_out/V_in` (fark büyüdükçe kötü) | %85–95 (örnekte %92,3) |
| Gürültü / EMI | Çok düşük | Dalgalanma + anahtarlama harmonikleri |
| Parça sayısı / yer | Az (2 kapasitör) | İndüktör, daha çok kapasitör, bölücüler |
| Yükseltme (boost) / ters çevirme | Yapamaz | Yapar |
| Tasarım ve yerleşim hassasiyeti | Düşük | Yüksek (sıcak döngü, kararlılık) |
| Isı | `(V_in − V_out)·I_out` | Küçük, ama indüktör de ısınır |

**Pratik kural:** `(V_in − V_out)·I_out` kaybı paketin ısı sınırını (`θ_JA` ile) zorluyorsa anahtarlamalı seç. Bu ders o noktadan sonrasının tasarımıdır.

## 2. Topoloji seçimi

Üç temel hücre aynı üç parçayı kullanır (anahtar, diyot, indüktör); **indüktörün yeri** fark yaratır:

```
BUCK (V_out < V_in)             BOOST (V_out > V_in)            TERS BUCK-BOOST
          SW                              SW                              SW
Vin ──[S]───┬──[L]──┬── Vout    Vin ──[L]───┬──[D]──┬── Vout    Vin ──[S]───┬──[D]──┬── Vout(−)
            │       │                       │       │                       │       │
           [D]     [C]                     [S]     [C]                     [L]     [C]
            │       │                       │       │                       │       │
GND ────────┴───────┘           GND ────────┴───────┘           GND ────────┴───────┘

V_out = D·V_in                  V_out = V_in/(1−D)              V_out = −V_in·D/(1−D)
giriş akımı DARBELİ             giriş akımı sürekli             iki akım da DARBELİ
çıkış akımı sürekli             çıkış akımı DARBELİ             S gerilimi V_in+|V_out|
RHPZ yok                        RHPZ var                        RHPZ var
D: anot GND'de, katot SW'de     D: anot SW'de, katot Vout'ta    D: anot Vout'ta, katot SW'de

S: anahtar (MOSFET) · D: diyot ya da senkron FET · L: indüktör · C: çıkış kapasitörü
SW: anahtarlama düğümü. Fark yalnız indüktörün yeri; darbeli akım tarafı ve RHPZ ondan gelir.
```

| Topoloji | `V_out` | Giriş akımı | Çıkış akımı | RHPZ | Anahtar gerilimi | Tipik kullanım |
|---|---|---|---|---|---|---|
| **Buck** | `< V_in` | Darbeli | Sürekli | Yok | `V_in` | 24 V → 5 V, 12 V → 3,3 V |
| **Boost** | `> V_in` | Sürekli | Darbeli | Var | `V_out` | Li-ion → 5 V, LED zinciri |
| **Ters buck-boost** | Negatif (genliği `V_in`'den küçük ya da büyük olabilir) | Darbeli | Darbeli | Var | `V_in + \|V_out\|` | −5 V analog besleme |
| SEPIC (nitel) | Pozitif, `V_in`'in altında ya da üstünde | Sürekli | Darbeli | Var | `V_in + V_out` | Aralık `V_out`'u kesiyor, tek anahtar |
| 4 anahtarlı buck-boost (nitel) | Pozitif, altında ya da üstünde | Bölgeye göre | Bölgeye göre | Boost bölgesinde var | `max(V_in, V_out)` | Li-ion 3,0–4,2 V → 3,3 V |

**Bu tablodan çıkan üç sonuç:**
- **Darbeli akımın hangi tarafta olduğu**, kapasitör derecesini belirler: buck'ta **giriş** kapasitörü, boost'ta **çıkış** kapasitörü zorlanır.
- **RHPZ'si olan** topolojilerde (boost, ters buck-boost, SEPIC) döngü hızı sınırlıdır (bölüm 5, 9).
- **Sürekli** akım tarafı gürültüsüzdür: boost'ta giriş, buck'ta çıkış. EMI'yi giriş filtresi mi, çıkış filtresi mi çözecek, buna göre seç.

**Karar ağacı:**

```
 1) LDO kaybı (V_in − V_out)·I_out pakete sığıyor ve gürültü kritik mi? ───► evet: LDO (bölüm 1)
 │
 2) Dokunulabilir parça ya da şebeke var; izolasyon şart mı? ──────────────► evet: flyback (Ders 3)
 │
 3) V_out, V_in aralığına göre nerede?
    ├─ her zaman V_in,min'in altında ─────────────────► BUCK (≤ 3 A: tümleşik, senkron IC)
    ├─ her zaman V_in,maks'ın üstünde ────────────────► BOOST (kapalıyken V_out = V_in kalır)
    ├─ aralık V_out'u kesiyor (Li-ion → 3,3 V) ───────► 4 anahtarlı buck-boost ya da SEPIC
    └─ negatif çıkış gerekli (−5 V analog besleme) ───► ters buck-boost
```

Li-ion pil (3,0–4,2 V) → 3,3 V sistemi tipik bir "aralık V_out'u kesiyor" örneğidir. LDO yalnız `V_in > 3,3 V + dropout` iken çalışır (4,2 V'ta verim %78,6); pil 3,3 V'a yaklaşınca LDO regülasyonu bırakır ve pilin kalan kapasitesi kullanılmaz. Çözüm 4 anahtarlı buck-boost ya da boost + LDO'dur.

**IC mi, kontrolör mü?** Birkaç A'e kadar **FET'leri içeren IC** en kolay yoldur (sıcak döngü IC içinde kısadır). Daha yüksek akımlarda **kontrolör + harici FET** gerekir; bu, [MOSFET dersindeki](../mosfet-transistor-ve-yuk-surme/ozet.md) kapı sürme ve ölü zaman konularını da içerir ve bu dersin kapsamı dışındadır.

## 3. Temel fikir: volan ve su deposu

İki parça her şeyi açıklar:
- **İndüktör = volan.** Akım (dönme hızı) ani değişmez. Uçlarına gerilim (itme) uygularsan akım artar ya da azalır: `dI/dt = V_L/L`. Büyük `L` = ağır volan = yumuşak akım.
- **Kapasitör = su deposu.** Gerilim (su seviyesi) ani değişmez. Akım farkı seviyeyi değiştirir: `dV/dt = I_C/C`. Büyük `C` = geniş depo = düz gerilim.
- **Anahtar = vana görevlisi.** Vanayı saniyede yüz binlerce kez açıp kapatır; **açık kalma oranı** `D` (duty cycle) ortalamayı belirler.

### 3.1 Volt-saniye dengesi

Kararlı hâlde volanın hızı bir çevrimin sonunda **başladığı yere** dönmelidir; yani çevrim boyunca "itme × süre" toplamı sıfırdır. Anahtar kapalıyken (`D·T`) indüktör gerilimini `V_on`, açıkken (`(1−D)·T`) `V_off` diyelim: `V_on·D + V_off·(1−D) = 0`.

| Topoloji | `V_L` (anahtar iletirken) | `V_L` (anahtar kapalıyken) | Sonuç |
|---|---|---|---|
| Buck | `V_in − V_out` | `−V_out` | `V_out = D·V_in` |
| Boost | `V_in` | `V_in − V_out` | `V_out = V_in/(1−D)` |
| Ters buck-boost | `V_in` | `V_out` (negatif) | `V_out = −V_in·D/(1−D)` |

Kapasitör için de aynı mantık: kararlı hâlde ortalama kapasitör akımı sıfırdır; yani **diyot (ya da LS) akımının ortalaması çıkış akımına eşittir**. Buradan indüktör ortalama akımı çıkar:

| Topoloji | `I_L,ort` | `ΔI_L` (tepeden tepeye) | Giriş akımı (ort.) |
|---|---|---|---|
| Buck | `I_out` | `(V_in − V_out)·D/(L·f_s)` | `D·I_out` |
| Boost | `I_out/(1−D)` | `V_in·D/(L·f_s)` | `I_out/(1−D)` |
| Ters buck-boost | `I_out/(1−D)` | `V_in·D/(L·f_s)` | `I_out·D/(1−D)` |

(Bunlar kayıpsız, sürekli iletim (CCM) formülleridir; η düzeltmesi bölüm 4 ve 5'te gelir. Üç satır da zaman alanı benzetimiyle doğrulandı.)

### 3.2 CCM ve DCM

İndüktör akımı çevrim boyunca **hiç sıfıra inmiyorsa** dönüştürücü **CCM**'dedir (continuous conduction mode); sıfırda bir süre kalıyorsa **DCM**'dedir. Sınır, ortalama akımın dalgalanmanın yarısına eşit olduğu yerdir:
- **Buck:** `I_out,kritik = ΔI_L/2`. Örnek A'da 24 V'ta `ΔI_L = 0,24 A` → sınır **0,12 A** (yükün %12,0'si).
- **Boost:** `I_out,kritik = (1−D)·ΔI_L/2`. Örnek B'de **80 mA** (yükün %16,0'ı).

Neden önemli? CCM'de dönüştürücü "temiz bir ayarlı ortalama" gibi davranır ve formüller geçerlidir. **DCM'de** akım her çevrimde sıfırdan başlar ve sıfıra iner, dönüşüm oranı yüke bağlı hâle gelir, indüktör tepe akımı yükselir, kontrol döngüsünün modeli değişir. Aşağıdaki şekil aynı devrenin üç durumunu gösterir:

```
(a) CCM, I_out = 1 A: ΔI_L = 0,24 A; indüktör akımı hiç sıfıra inmez
         ┌─────────────────────────────────────────────────────────────┐
  +1,15 A│               :              :              :               │
  +1,10 A│      ••••••   :              :     ••••••   :               │
  +1,05 A│    •••    ••••••             :   •••    ••••••              │
  +1,00 A│   ••          :••••••        :  ••          :••••••         │
  +0,95 A│  ••           :     ••••••   : ••           :     ••••••    │
  +0,90 A│•••            :          •••••••            :          •••••│
  +0,85 A│               :              :              :               │
         └─────────────────────────────────────────────────────────────┘
          0              1 µs           2 µs           3 µs           4 µs

(b) DCM, I_out = 50 mA (asenkron ya da diyot emülasyonu): I_pk = 0,155 A
    t_on = 269 ns · t_off = 1,02 µs · akımın sıfır kaldığı süre ≈ 0,71 µs ('-' = 0 A)
         ┌─────────────────────────────────────────────────────────────┐
  +0,20 A│               :              :              :               │
  +0,15 A│    ••••       :              :   ••••       :               │
  +0,10 A│  •••  ••••••  :              : •••  ••••••  :               │
  +0,05 A│ ••         ••••••            :••         ••••••             │
   0,00 A│••---------------•••••••••••••••---------------••••••••••••••│
  −0,05 A│               :              :              :               │
  −0,10 A│               :              :              :               │
         └─────────────────────────────────────────────────────────────┘
          0              1 µs           2 µs           3 µs           4 µs

(c) FPWM, I_out = 50 mA (senkron, zorlamalı): aynı ΔI_L; vadi −0,070 A (NEGATİF), tepe 0,170 A
         ┌─────────────────────────────────────────────────────────────┐
  +0,20 A│               :              :              :               │
  +0,15 A│      ••••••   :              :     ••••••   :               │
  +0,10 A│    •••    ••••••             :   •••    ••••••              │
  +0,05 A│   ••          :••••••        :  ••          :••••••         │
   0,00 A│--••-----------------••••••-----••-----------------••••••----│
  −0,05 A│•••            :          •••••••            :          •••••│
  −0,10 A│               :              :              :               │
         └─────────────────────────────────────────────────────────────┘
          0              1 µs           2 µs           3 µs           4 µs

V_in = 24 V, V_out = 5 V, L = 33 µH, f_s = 500 kHz
akım eğimi: yükselme (V_in−V_out)/L = 0,576 A/µs, düşme V_out/L = 0,152 A/µs
```

- **(a) CCM:** 1 A'de akım 0,88–1,12 A arasında salınır; sıfıra hiç yaklaşmaz.
- **(b) DCM:** 50 mA'de aynı `L` ile akım her çevrimde sıfırdan 0,155 A tepeye çıkar, düşer ve **0,71 µs** boyunca sıfırda kalır (çevrimin %35'si).
- **(c) FPWM:** Senkron dönüştürücü zorla anahtarlarsa akım **negatif** olur (−0,070 A): enerji çıkıştan girişe geri akar. Zararsız ve çıkış dalgalanması aynıdır, ama bu enerji bir kayıp döngüsüdür (bölüm 8).

**Senkron / asenkron:** Düşük taraftaki anahtar diyotsa (**asenkron**), akım sıfıra inince diyot kendiliğinden kapanır ve DCM doğal olarak oluşur. Düşük taraf bir FET ise (**senkron**), IC akımın sıfıra indiğini ölçüp FET'i kapatabilir (**diyot emülasyonu**) ya da kapatmayıp akımın negatif olmasına izin verebilir (**FPWM**). Senkron daha verimlidir (diyotun `V_F` kaybı yoktur, bölüm 7) ve bugün küçük/orta güçte standarttır.

## 4. Buck tasarımı: Örnek A (24 V → 5 V, 1 A)

Bu bölüm bir **tasarım sırasıdır**: gereksinim → görev oranı → indüktör → akım sınırları → çıkış kapasitörü → giriş kapasitörü → minimum açık kalma. Sayıların hepsi kayıpsız devrede zaman alanı benzetimiyle doğrulandı.

### 4.1 Gereksinim ve varsayımlar

| Parametre | Değer | Not |
|---|---|---|
| `V_in` | 18–30 V (nominal 24 V) | Endüstriyel 24 V hat |
| `V_out`, `I_out` | 5 V, 1 A | |
| `f_s` | 500 kHz | FET'leri içeren IC |
| Verim tahmini η | %90 | Görev oranı için (SLVA477'nin örnekte kullandığı tahmin) |
| IC akım limiti | 1,7 A (min) / 2,0 A (tip.) / 2,4 A (maks) | **Varsayım**; kendi IC'ni oku |
| `t_on,min` | 100 ns | **Varsayım** |
| Çıkış kapasitörü | 2 × 22 µF seramik, ESR 3 mΩ | Etkin değer: nominalin %55'i (DC bias) |
| Giriş kapasitörü | 20 µF seramik (nominal) | Etkin değer: %55 |
| İndüktör DCR | 100 mΩ | **Varsayım** |

```
                                    SW
V_in ───┬───────────[HS]────────────┬─────[L]───────────┬─────── ► V_out
        │  ░░░░░░░░░░░░░░░░░░░░░░░  │                   │
     [C_in]░░ sıcak döngü alanı ░░[LS]               [C_out]
        │  ░░░░░░░░░░░░░░░░░░░░░░░  │                   │
 GND ───┴───────────────────────────┴───────────────────┘

t_on  (D·T)     : HS iletir → V_in'den L'ye akım; giriş akımı = I_L (darbe), C_in sağlar
t_off ((1−D)·T) : LS iletir → L akımı LS üzerinden döner; giriş akımı 0, C_in yeniden dolar
ölü zaman       : ikisi de kapalı → akım LS gövde diyodundan akar (kayıp, bölüm 7)
```

### 4.2 Görev oranı

SLVA477 görev oranını verimle birlikte yazar: `D = V_out/(V_in,maks·η)` (belge formülü `V_in,maks` için yazar; bu derste her `V_in` noktasında uyguluyorum). Her iki değeri de veriyorum:

| `V_in` | İdeal `D = V_out/V_in` | η'lı `D` (η = %90) |
|---|---|---|
| 18 V | 0,278 | 0,309 |
| 24 V | 0,208 | 0,231 |
| 30 V | 0,167 | 0,185 |

Kayıplar anahtarı biraz **daha uzun** iletmeyi gerektirir (≈ %11). Aşağıdaki dalgalanma ve minimum açık kalma hesaplarında **ideal `D`** kullanıldı: benzetim ideal devrede doğrulandı ve minimum açık kalma için en küçük `D` en kötü durumdur.

### 4.3 İndüktör

Buck'ta dalgalanma `V_in` ile artar; bu yüzden `L` **`V_in,maks`'ta** seçilir. Tasarım hedefi `ΔI_L = 0,2–0,4 · I_out` (SLVA477'nin önerdiği aralık; bu derste %30):

`L = V_out·(V_in,maks − V_out)/(ΔI_L·V_in,maks·f_s)` = 5 · 25/(0,30 · 30 · 500 000) = **27,78 µH**

Hesaplanan değerden **büyük** standart değer: **33 µH**. Üç giriş gerilimindeki dalgalanma:

| `V_in` | `ΔI_L = (V_in − V_out)·D/(L·f_s)` | `I_out`'a oranı |
|---|---|---|
| 18 V | **0,22 A** | %21,9 |
| 24 V | **0,24 A** | %24,0 |
| 30 V | **0,25 A** | %25,3 |

**`L` büyürse:** dalgalanma ve çekirdek kaybı azalır, ama aynı boyutta DCR artar, `I_sat` düşer, yük geçişinde akım daha yavaş değişir. **`L` küçülürse:** dalgalanma, tepe akım ve çıkış gürültüsü artar, DCM'ye daha erken geçilir.

### 4.4 Akım sınırları ve doyma

En kötü durum `V_in = 30 V`:
- **Tepe akım:** `I_pk = I_out + ΔI_L/2` = **1,13 A**, vadi `0,87 A`.
- **Çıkış akımı sınırı:** IC'nin tepe akım limiti `I_LIM`'dir. Garanti edilen en küçük limitle `I_MAXOUT = I_LIM,min − ΔI_L/2 = 1,7 − 0,126` = **1,57 A** ≥ 1 A ✓ (limit ortalamayı değil **tepeyi** keser, bu yüzden dalgalanmanın yarısı çıkarılır).
- **Doyma akımı:** Kısa devrede ya da yük geçişinde akım limite kadar çıkabilir. Bobin bunu **doymadan** taşımalı: `I_sat ≥ I_LIM,maks`; %10 marjla **2,64 A** (marj tasarım tercihidir). Bobin doyarsa `L` çöker, `dI/dt` artar ve akım IC'nin limit gecikmesi içinde kontrolsüz tırmanır: FET ve bobin zarar görür.
- **Isınma akımı:** Üreticiler iki akım verir: `I_sat` (`L`'nin belirli oranda düştüğü akım; oran üreticiye göre %10–30) ve `I_rms` (belirli ısınmada, tipik 20–40 K). **İkisini de** geç. `I_L,rms = √(I_out² + ΔI_L²/12)` = **1,003 A** (dalgalanma etkisi önemsiz), `P_DCR = I_rms²·DCR` = **0,101 W**.

### 4.5 Çıkış kapasitörü

Seramik kapasitör gerçekte nominal değerin **altındadır**: DC bias ve tolerans etkin değeri düşürür. Bu derste **%55** varsayıldı (Hegarty'nin makalesi seramik çıkış kapasitörü için %45 kapasite kaybı kullanır: tabloda 100 µF, şemada 55 µF etkin; bölüm 9.8); kendi parçanın eğrisini oku. 44 µF nominal → **24,2 µF** etkin.

- Kapasitif kısım: `ΔV_C = ΔI_L/(8·f_s·C)` = **2,61 mV**
- ESR kısmı: `ΔV_ESR = ESR·ΔI_L` = **0,76 mV**
- Toplam (üst sınır): **3,37 mV** (%0,067 `V_out`); zaman alanı benzetiminde tepeden tepeye **2,71 mV** (iki bileşen farklı fazdadır, toplamları fazla kötümserdir).
- %1 dalgalanma (50 mV) için gereken en az etkin kapasite: **1,26 µF**. Dalgalanma **kolayca** karşılanır.

Kapasiteyi asıl belirleyen **yük bırakma aşımıdır.** Yük aniden 1 A'den 0'a düşünce indüktördeki `½·L·ΔI²` enerjisi kapasitöre gider: `ΔV_aşım ≈ √(V_out² + L·ΔI²/C) − V_out`. Aşımı `V_out`'un %5'iyle (250 mV) sınırlamak için:

`C_out ≥ L·ΔI_yük²/(2·V_out·V_aşım)` = 33 µ · 1² / (2 · 5 · 0,25) = **13,2 µF** (etkin)

Seçilen 24,2 µF bunun üstündedir ✓. (Bu hesap kontrol döngüsünün tepkisini saymaz: gerçek aşım genellikle daha küçüktür. Doğrulama için yük geçişi ölçülür, bölüm 16.)

### 4.6 Giriş kapasitörü

Buck'ta giriş akımı **darbelidir**: anahtar iletirken `I_L`, değilken 0. Bu darbeyi kaynak değil **giriş kapasitörü** sağlar:

`I_Cin,rms = I_out·√(D·(1−D))`

| `V_in` | `D` | `I_Cin,rms` |
|---|---|---|
| 18 V | 0,278 | **0,448 A** |
| 24 V | 0,208 | **0,406 A** |
| 30 V | 0,167 | **0,373 A** |
| `D = 0,5` (en kötü) | 0,5 | **0,50 A** (`I_out/2`) |

(Dalgalanmayı da içeren tam ifade `√(D(1−D)·I_out² + D·ΔI_L²/12)` sade formülden %1'den az farklıdır; benzetimle doğrulandı.) Kapasitörün **ripple akımı derecesi** bu değerin üstünde olmalıdır. Dalgalanma gerilimi: `ΔV_in = I_out·D·(1−D)/(f_s·C_in)`; 18 V'ta (en büyük `D(1−D)`) 20 µF nominal, **11 µF etkin** ile **36,5 mV**. Aynı akım için 2 × 4,7 µF (9,4 µF nominal, etkin %55) kullansaydın dalgalanma **77,6 mV** olurdu.

Giriş kapasitörü iki parçadan oluşur: IC pinlerine **bitişik** küçük HF seramik (0,1–0,47 µF, sıcak döngü, bölüm 14) ve onun yanında **bulk** kapasitör (burada 20 µF seramik). Giriş kapasitörünün hot-plug ve giriş filtresi etkileşimi de ayrı bir konudur: bölüm 11.

### 4.7 Minimum açık kalma süresi ve maksimum görev oranı

IC, anahtarı belirli bir süreden **kısa** açamaz (`t_on,min`: akım sezme sönümü, kapı sürme gecikmeleri). `V_in` yüksek ve `V_out` düşükse gereken süre bundan kısa olur ve IC **darbe atlar** (pulse skipping): çıkış dalgalanması ve ses gürültüsü artar.

`t_on = D/f_s` → 30 V'ta **333 ns** ≥ 100 ns ✓ (500 kHz'te marj 3×).

| | Formül | Sonuç |
|---|---|---|
| 500 kHz'te izin verilen en yüksek `V_in` | `V_out/(f_s·t_on,min)` | **100 V** |
| 2 MHz'te izin verilen en yüksek `V_in` | aynı | **25 V** (30 V'ta ✗, `t_on` = 83 ns) |
| 30 V'ta izin verilen en yüksek `f_s` | `D/t_on,min` | **1,67 MHz** |

**Sonuç:** küçük bobin ve kapasitör için frekansı yükseltmek cazip, ama yüksek `V_in/V_out` oranı frekansı **sınırlar**. 24 V → 1,2 V gibi büyük oranlarda ya düşük frekans ya da çok küçük `t_on,min`'li IC gerekir. Öbür uçta, `V_in` `V_out`'a yaklaşırsa görev oranı %100'e yaklaşır: IC'nin **dropout / %100 görev** davranışını kontrol et. Örnek A'da en büyük `D` 0,278'dir; sorun yok.

### 4.8 Örnek A: tasarım özeti

| Parça | Değer | Dayanak |
|---|---|---|
| İndüktör | **33 µH**, `I_sat ≥ 2,64 A`, `I_rms ≥ 1,0 A`, DCR ≤ 100 mΩ | Bölüm 4.3–4.4 |
| Çıkış kapasitörü | 2 × 22 µF seramik, ≥ 10 V | 24,2 µF etkin; yük bırakma ≥ 13 µF |
| Giriş kapasitörü | 20 µF seramik (2 × 10 µF, 50 V) + 0,1 µF HF | `I_rms ≥ 0,50 A` |
| Geri besleme / UVLO / soft-start | Bölüm 10 | |
| Kompanzasyon | Bölüm 9 | |

50 V sınıfı seramikte 24–30 V bias'ta kapasite kaybı **%55'ten fazla** olabilir (özellikle küçük kılıfta); kendi parçanın eğrisini oku.

## 5. Boost: Örnek B (Li-ion 3,0–4,2 V → 5 V, 0,5 A)

Boost'ta indüktör **girişe** bağlıdır; bu yüzden giriş akımı sürekli, çıkış (diyot ya da senkron FET) akımı **darbelidir**. Anahtar iletirken indüktör enerji doldurur; anahtar kapanınca indüktör akımı çıkışa **iter** ve gerilim giriştekinden yüksek olur: sıkıştırılmış yay.

### 5.1 Gereksinim, görev oranı ve indüktör

Varsayımlar: `V_in = 3,0–4,2 V` (nominal 3,7 V), `V_out = 5 V`, `I_out = 0,5 A`, `f_s = 1 MHz`, η = %85, IC akım limiti 1,7 A (min).

- **Görev oranı** (en düşük `V_in`, SLVA372C): `D = 1 − V_in,min·η/V_out` = **0,49** (kayıpsız 0,40).
- **İndüktör ortalama akımı:** `I_L,ort = I_out/(1−D)` = **0,980 A**. Çapraz kontrol: `I_out·V_out/(V_in·η)` = 0,980 A ✓ (giriş gücünden aynı değer).
- **İndüktör:** Hedef `ΔI_L = 0,3·I_L,ort` = 0,29 A için `L = V_in,min·D/(f_s·ΔI_L)` = **5,00 µH** → standart **4,7 µH**. Sonuçta `ΔI_L = V_in·D/(f_s·L)` = **0,31 A** (%31,9).
- **Tepe/vadi:** `I_pk = I_L,ort + ΔI_L/2` = **1,14 A**, vadi 0,82 A.
- **Çıkış akımı sınırı:** `I_MAXOUT = (I_LIM,min − ΔI_L/2)·(1−D)` = **0,79 A** ≥ 0,5 A ✓. Boost'ta anahtar akımı çıkıştan **büyüktür** (`I_L = I_out/(1−D)`), bu yüzden `(1−D)` çarpanı gelir.

**Dalgalanma en kötü nerede?** Kayıpsız boost'ta `ΔI_L` `V_in = V_out/2` (2,5 V) iken en büyüktür ve değeri `V_out/(4·f_s·L)` = 0,27 A'dir. Gerçekte kayıplar `D`'yi büyütür; η = %85 ile 3,0 V'ta **0,31 A** olur ve 4,2 V'ta (`D` = 0,29) 0,26 A'e iner. Sabit `L` için en kötü durum **düşük `V_in`**'dir: `L`'yi orada seç. (SLVA372C'nin tahmin formülü `0,3·I_out·V_out/V_in` 0,25 A verir: giriş akımı üzerinden aynı mantığın kaba hâli.)

**Kritik akım:** `I_out,kritik = (1−D)·ΔI_L/2` = **80 mA** (yükün %16,0'ı): bunun altında DCM.

### 5.2 Kapasitörler

- **Çıkış kapasitörü:** 22 µF nominal → **12,1 µF** etkin. Anahtar iletirken yükü **kapasitör** besler: `ΔV_C = I_out·D/(f_s·C)` = **20,2 mV**. ESR kısmı **tepe diyot akımıyla** hesaplanır (`ΔI_L` ile değil): `ESR·I_pk` = 5 mΩ · 1,14 A = **5,7 mV**. Toplam **25,9 mV** (%0,52); benzetimde 24,3 mV.
- **Çıkış ripple akımı** (boost'un zayıf noktası): `I_Cout,rms = I_out·√(D/(1−D))` = **0,490 A** (dalgalanma dahil tam ifade 0,494 A). Buck'ta bu akım **giriş** kapasitöründeydi; boost'ta **çıkış** kapasitörü yükü taşır.
- **Giriş kapasitörü:** Akım sürekli ve üçgendir: `I_Cin,rms = ΔI_L/√12` = **0,090 A**. Giriş tarafı rahat.
- **Diyot kaybı:** Asenkron boost'ta `V_F·I_out` = 0,45 V · 0,5 A = **225 mW**, çıkış gücünün **%9,0'ı**. Bu yüzden boost'ta senkron (FET'li) doğrultma yaygındır.

### 5.3 Boost'un sağ yarı düzlem sıfırı (RHPZ)

Boost'ta (ve ters buck-boost'ta) bir **sağ yarı düzlem sıfırı** vardır. Sezgi: yük artınca kontrol döngüsü görev oranını **artırır**; ama `D` artınca diyot iletim süresi (`1−D`) **kısalır**, yani çıkışa giden akım **önce azalır**, sonra artar. Çıkış ilk anda **ters yöne** gider. Bu, kazancı yükseltirken fazı **düşüren** bir sıfırdır: döngü bu frekansın üstünde kararlı kapatılamaz.

`f_RHPZ = R_L·(1−D)²/(2π·L)`

| Durum | `R_L` | `D` | `f_RHPZ` |
|---|---|---|---|
| 3,0 V, 0,5 A (en kötü) | 10 Ω | 0,49 | **88,1 kHz** |
| 4,2 V, 0,5 A | 10 Ω | 0,29 | 172,6 kHz |
| 3,0 V, 50 mA (hafif yük) | 100 Ω | 0,49 | 881 kHz |

RHPZ **tam yükte ve düşük `V_in`'de en düşüktür**: döngüyü orada tasarla. Kural: **`f_c ≤ f_RHPZ/5`** (bazı kaynaklar /3 der: 29,4 kHz) = **17,6 kHz**. 1 MHz'lik bir boost'ta çapraz frekans yalnız **18 kHz**'e çıkabilir (`f_s`'nin %1,8'i). RHPZ'nin faz bedeli `arctan(f_c/f_RHPZ)`:

| `f_c/f_RHPZ` | 0,1 | 0,2 | 1/3 | 0,5 | 1 |
|---|---|---|---|---|---|
| Faz kaybı | 5,7° | 11,3° | 18,4° | 26,6° | 45,0° |

`f_c = f_RHPZ/5` ≈ 11° kayıp demektir ve tek başına kabul edilebilir; `f_RHPZ`'ye yaklaştıkça faz payı erir. (RHPZ formülü ortalanmış durum uzayı modelinin sıfırından benzetimle doğrulandı.)

### 5.4 Boost'a özgü tuzaklar

- **`V_in,maks < V_out` olmalı.** `V_in` `V_out`'u aşarsa diyot iletir ve çıkış girişi takip eder; regülasyon kaybolur. Li-ion 4,2 V → 5 V uygundur; 9–16 V → 12 V gibi **kesişen** aralıklar için boost değil buck-boost gerekir.
- **Kısa devre izolasyonu yoktur.** Giriş, indüktör ve diyot üzerinden **doğrudan** çıkışa bağlıdır; çıkış kısa devre olursa akımı anahtar değil **diyot yolu** taşır ve IC'nin akım limiti bunu kesemez. Girişe sigorta/akım sınırı ya da yük anahtarı koy.
- **Kapalıyken `V_out ≈ V_in − V_F`.** IC devre dışıyken yük pilden beslenmeye devam eder: uyku modunda sızıntı ve "kapalı ama enerjili" yük. **True-shutdown** (çıkışı girişten ayıran) boost IC'si ya da harici yük anahtarı kullan.
- **Açılış akımı:** Giriş verildiğinde `C_out` indüktör ve diyot üzerinden `V_in`'e kadar **sınırsız** dolar (inrush). Pil kaynağında bu, UVLO'yu tetikleyip yeniden başlatma döngüsü yaratabilir. IC'nin **ön yükleme (pre-charge)** ya da yumuşak başlatma modunu kontrol et.
- **Zil / çıkış gürültüsü:** Darbeli çıkış akımı yüzünden çıkış tarafı sıcak döngüdür (bölüm 14); diyot ve `C_out` çok yakın olmalı.

## 6. Ters buck-boost, SEPIC ve 4 anahtarlı buck-boost

### 6.1 Ters buck-boost: Örnek C (+5 V → −5 V, 0,2 A)

Çıkışı **negatif** üretir; analog besleme (−5 V, op-amp, ADC girişi) için yaygındır. Anahtar iletirken indüktör `V_in`'den enerji alır; anahtar kapanınca akım çıkış kapasitörünü **ters** doldurur. Buck ve boost'un karışımıdır: çıkış `V_in`'den büyük ya da küçük olabilir (|V_out| için).

| Büyüklük | Formül | Örnek C |
|---|---|---|
| Görev oranı | `D = \|V_out\|/(V_in + \|V_out\|)` | **0,50** |
| İndüktör ortalama akımı | `I_out/(1−D)` | **0,40 A** |
| Giriş ortalama akımı | `I_out·D/(1−D)` | **0,20 A** |
| Dalgalanma (10 µH, 1 MHz) | `V_in·D/(L·f_s)` | **0,25 A** |
| Tepe akım | `I_L,ort + ΔI_L/2` | **0,525 A** |
| Anahtar gerilimi | `V_in + \|V_out\|` | **10 V** |
| `f_RHPZ` | `R_L·(1−D)²/(2π·D·L)` | **198,9 kHz** (`R_L` = 25 Ω) |

**Dikkat edilecekler:**
- **Her iki akım da darbeli:** giriş de çıkış da kapasitörlerden zorlanır.
- **Gerilim biner:** anahtar ve diyot `V_in + |V_out|` görür; IC'nin gerilim derecesini buna göre seç.
- **Referans kayar:** Pratikte bir buck IC'yi ters buck-boost olarak kullanmak yaygındır: IC'nin GND pini negatif çıkışa bağlanır, IC'ye `V_in + |V_out|` uygulanır. Bu durumda **EN, PG ve geri besleme** referansı IC'nin kendi GND'sine (yani −5 V hattına) göre olur; kontrol sinyallerini seviye kaydırmak gerekir. Uygulama notunu kendi IC'n için oku.
- **RHPZ:** `D` paydadadır; `D` büyüdükçe RHPZ düşer.

### 6.2 SEPIC (nitel)

Tek anahtar, **iki indüktör** (ya da bağlı indüktör) ve bir **bağlama kapasitörü** kullanır; pozitif çıkışı `V_in`'in altında ya da üstünde üretir. Giriş akımı **sürekli**dir (girişte indüktör), kapalıyken çıkış kısa devre izolasyonludur (bağlama kapasitörü DC'yi keser). Bedeli: iki indüktör (ya da bağlı parça), bağlama kapasitöründe büyük ripple akımı, boost gibi **RHPZ** ve daha düşük verim. `V_in` aralığı `V_out`'u keserken ve tek anahtarlı basit çözüm istendiğinde seçilir. Bu derste sayısal olarak çözülmedi.

### 6.3 4 anahtarlı buck-boost (nitel)

Tek indüktör ve dört FET: `V_in > V_out` iken buck, `V_in < V_out` iken boost gibi çalışır; ikisinin yakın olduğu bölgede özel geçiş modu kullanılır. Tipik örnek **Li-ion 3,0–4,2 V → 3,3 V**'tur: tek IC, tek indüktör, pil boşalana kadar regülasyon. Bedeli: kontrol karmaşıklığı, geçiş bölgesinde ek kayıp ve gürültü, boost modunda RHPZ. Bu derste sayısal olarak çözülmedi; IC datasheet'indeki mod geçiş eşiklerini ve verim eğrilerini oku.

## 7. Kayıp bütçesi, verim ve ısı

Verim tek bir sayı değil, bir **bütçedir**. Aylık maaşın nereye gittiğini (kira, fatura, market) yazmadan "tasarruf et" denmez: önce kalemleri yazarsın, sonra **en büyüğünü** küçültürsün. Aynı şey burada geçerli: kaybın nereye gittiğini bilmeden "verimi artır" demek tahmindir.

### 7.1 Kalemler ve formüller

Örnek A, 24 V → 5 V / 1 A, 500 kHz. IC değerleri **varsayımdır** (kendi IC'nin datasheet'inden al): `R_HS` = 200 mΩ, `R_LS` = 120 mΩ, `t_sw` = 15 ns (gerilim-akım örtüşme süresi, yükselme + düşme toplamı), `Q_g` = 2 nC (5 V sürüşte), `Q_oss` = 1,5 nC, `Q_rr` = 2 nC, `V_SD` = 0,7 V, `t_ölü` = 10 ns, `I_q` = 0,5 mA, indüktör çekirdek kaybı 25 mW. `I_rms² = I_out² + ΔI_L²/12`.

| Kalem | Formül | Örnek A | Pay | Küçültme yolu |
|---|---|---|---|---|
| İndüktör DCR | `I_rms²·DCR` | **100,5 mW** | %24,0 | Daha düşük DCR'li bobin (daha büyük ya da ekranlı) |
| LS iletim | `(1−D)·I_rms²·R_LS` | **95,5 mW** | %22,8 | Düşük `R_DS(on)`'lu IC |
| HS anahtarlama | `½·V_in·I_out·t_sw·f_s` | **90,0 mW** | %21,5 | Düşük `f_s`; hızlı kenar (EMI ile ödünleşir, bölüm 15) |
| HS iletim | `D·I_rms²·R_HS` | 41,9 mW | %10,0 | Düşük `R_DS(on)` |
| İndüktör çekirdek | üretici aracı ya da eğrisi | 25,0 mW | %6,0 | Küçük `ΔI_L` (büyük `L`), uygun malzeme |
| Ters toparlanma | `Q_rr·V_in·f_s` | 24,0 mW | %5,7 | Düşük `f_s` |
| Coss | `2·½·Q_oss·V_in·f_s` | 18,0 mW | %4,3 | Düşük `f_s`, düşük `V_in` |
| IC `I_q` | `V_in·I_q` | 12,0 mW | %2,9 | Düşük `I_q`'lu IC, hafif yük modu |
| Ölü zaman | `V_SD·I_out·2·t_ölü·f_s` | 7,0 mW | %1,7 | Uyarlamalı ölü zamanlı IC |
| Kapı sürücü | `Q_g·V_drv·f_s` | 5,0 mW | %1,2 | Düşük `f_s` |
| **Toplam** | | **419 mW** | %100 | `η = 5 W/(5 W + 0,419 W)` = **%92,3** |

**Nasıl okunur:**
- En büyük üç kalem (bobin DCR, LS iletim, HS anahtarlama) toplamın **%68'ini** oluşturur. FET'lerin üç kalemi (HS iletim, LS iletim, HS örtüşme) %54,3, indüktör (DCR + çekirdek) %30,0'dır: **bobin en az FET kadar önemlidir** ve çoğu zaman gözden kaçar.
- Frekansla orantılı kalemler (örtüşme, kapı, Coss, ters toparlanma, ölü zaman) `f_s` yarıya inince yarıya iner. Ama aynı `ΔI_L` için `L`'yi ikiye katlamak gerekir ya da `ΔI_L` ikiye katlanır: ödünleşim yine bobinde ve çıkış kapasitöründedir.
- Hesap bir **bütçedir, ölçüm değil**. IC değerlerini datasheet'ten oku; bobin kaybı için üreticinin DCR ve çekirdek kaybı verisini kullan; sonunda kendi kartında ölç (bölüm 16).

### 7.2 Kaynak örnekle karşılaştırma

Kalem listesi TI SLPA009A'nın senkron buck kayıp modelindeki biçimleri izler. Örtüşme formülü (`½·V·I·t_sw·f_s`) bu derste **kaba bir yaklaşım** olarak kullanıldı; belgedeki ortak kaynak indüktansını içeren ayrıntılı model daha gerçekçidir. Belgenin kendi örneği, 12 V → 1,3 V, 25 A, 500 kHz: hesaplanan **3,50 W**, ölçülen **3,45 W**, sapma **%1,4**. İki uyarı: belge **indüktör ve PCB kaybını içermez** ve model **CCM** içindir. Yani yukarıdaki toplam, bobinin kaybını ayrıca eklediğimiz için belgenin "FET kaybı" tanımından geniştir.

### 7.3 Senkron mu, asenkron mu?

Aynı devrede LS FET'i bir Schottky diyotla değiştirirsek (`V_F` = 0,45 V, **varsayım**):

| | Senkron (LS FET) | Asenkron (Schottky) |
|---|---|---|
| Alt anahtar kaybı | 95,5 mW (iletim) | `V_F·(1−D)·I_out` = **356 mW** (3,7 kat) |
| Toplam kayıp (24 V, 1 A) | 0,42 W | **0,64 W** (+221 mW) |
| Verim | %92,3 | **%88,7** |

LS FET'e ait kalemler (iletim, Coss, ters toparlanma, ölü zaman) çıkar, diyot kaybı eklenir; net sonuç **221 mW fazla kayıp**. Isıyı artık IC değil, harici diyot yayar (356 mW). Asenkronun artıları: daha sade IC, hafif yükte kendiliğinden DCM (negatif akım yok), ters toparlanma sorunu yok. `V_out` düştükçe `V_F`'nin çıkış gerilimine oranı büyür (`V_F·(1−D)/V_out`), bu yüzden düşük çıkış gerilimi ve büyük akımda senkron fiilen zorunludur.

### 7.4 Verim yüke göre nasıl değişir?

```
Kayıp bütçesi, 24 V → 5 V / 1 A, 500 kHz (1 karakter ≈ 5 mW; yüzde = toplam kaybın payı)

 İndüktör DCR       ████████████████████   100,5 mW  %24,0
 LS iletim          ███████████████████     95,5 mW  %22,8
 HS anahtarlama     ██████████████████      90,0 mW  %21,5
 HS iletim          ████████                41,9 mW  %10,0
 İndüktör çekirdek  █████                   25,0 mW  %6,0
 Ters toparlanma    █████                   24,0 mW  %5,7
 Coss (HS+LS)       ████                    18,0 mW  %4,3
 IC Iq              ██                      12,0 mW  %2,9
 Ölü zaman diyodu   █                        7,0 mW  %1,7
 Kapı sürücü        █                        5,0 mW  %1,2
 TOPLAM                                      419 mW  → verim %92,3

Verim - yük, FPWM (1 karakter ≈ %4):

   10 mA █████████░░░░░░░░░░░░░░░░  %36,7   (kayıp 86 mW)
  100 mA █████████████████████░░░░  %83,7   (kayıp 97 mW)
  500 mA ███████████████████████░░  %92,8   (kayıp 193 mW)
     1 A ███████████████████████░░  %92,3   (kayıp 419 mW)

 Yükten bağımsız kayıp tabanı ≈ 85 mW: hafif yükte verimi iletim kaybı değil bu taban belirler.
```

- **Yüksek yük:** İletim kayıpları `I²` ile büyür; verim 500 mA'de tepe yapar (%92,8), 1 A'de hafifçe düşer (%92,3).
- **Düşük yük:** Çıkış gücü küçülür, yükten bağımsız **sabit taban** (85 mW: kapı, Coss, ters toparlanma, `I_q`, çekirdek) olduğu gibi kalır. 10 mA'de çıkış gücü yalnız 50 mW iken kayıp 86 mW'tır: verim **%36,7**. 100 mA'de %83,7.
- Eğri **FPWM** (her çevrimde zorla anahtarlama) içindir. Hafif yükte tabanı küçülten mod bölüm 8'dedir.

### 7.5 Giriş gerilimi ve ısınma

| `V_in` | Toplam kayıp (1 A) | Verim |
|---|---|---|
| 18 V | 388 mW | %92,8 |
| 24 V | 419 mW | %92,3 |
| 30 V | 452 mW | %91,7 |

`V_in` arttıkça `V_in`'e bağlı kalemler (örtüşme, Coss, ters toparlanma) büyür; iletim payı azalır. Net etki küçüktür ama **en kötü ısı yüksek `V_in`'dedir**.

IC'nin kendi içinde ısıttığı güç, toplam kayıptan bobin kaybının (DCR + çekirdek) çıkarılmasıyla bulunur: 24 V'ta **293 mW**. `θ_JA` = 50 °C/W (**varsayım**) ile `ΔT = P·θ_JA` = **14,7 °C**; 30 V'ta **16,3 °C**. `T_j = T_a + ΔT` datasheet'teki sınırın altında kalmalıdır (derating: Güvenilirlik ve derating, Ders 16, hazırlanıyor). Datasheet'teki `θ_JA` çoğunlukla standart bir test kartında ölçülür; kendi kartında bakır alanı ve termal via'lara göre farklıdır (bölüm 14 ve 16).

### 7.6 Verimi artırma sırası

1. **Bütçeyi yaz**, en büyük kalemi bul (Örnek A: bobin DCR).
2. **`f_s` ile `L` arasındaki dengeyi** gözden geçir: frekansla orantılı beş kalem `f_s` ile iner, ama bobin büyür.
3. **Bobini yeniden seç:** DCR, `I_sat` ve boyut birbirine bağlıdır.
4. **Asenkron yerine senkron** (bölüm 7.3).
5. **Hafif yük için doğru mod** (bölüm 8).

## 8. Hafif yük modları: FPWM, DCM ve PFM

Hafif yükte iki istek çatışır: **düşük gürültü ve sabit frekans** ya da **yüksek verim**. Arabayla benzetirsek: FPWM, durmadan aynı devirde dönen motordur (yakıt harcar ama ses sabittir); PFM ise "dur-kalk" (start-stop) sistemidir (tasarruf eder ama kesik kesik çalışır). Birçok IC mod seçimi için bir pin ya da sürüm kodu sunar.

| Mod | Nasıl çalışır | Hafif yük verimi | Gürültü ve frekans | Ne zaman? |
|---|---|---|---|---|
| **FPWM** (zorla PWM) | Her çevrimde anahtarlar; akım negatif olabilir | Düşük: sabit taban 85 mW (10 mA'de %36,7) | Sabit `f_s`; temiz spektrum, düşük çıkış dalgalanması | ADC, ses, RF beslemesi; sabit frekans şart |
| **DCM, diyot emülasyonu** | Akım sıfıra inince LS kapanır; çevrim yine `f_s`'te | Orta: kapı, Coss, ters toparlanma her çevrimde ödenir | Sabit `f_s`; dalgalanma biraz büyür | Verim ve gürültü arasında orta yol |
| **PFM / darbe atlama** (auto) | Çıkış alt eşiğe inince bir darbe gelir; darbe sayısı yükle orantılı | Yüksek: kayıplar darbe sayısıyla azalır, `I_q` düşük | **Değişken frekans**; darbe başına büyük dalgalanma | Pille çalışan, bekleme akımı kritik ürünler |

**Sayılarla (Örnek A, 50 mA):** Bölüm 3.2'deki DCM darbesi (tepe 0,155 A, 269 ns açık + 1,02 µs boşalma) yüke **100 nC** taşır. Sabit tepe akımlı bir PFM IC (varsayımsal) aynı darbeyi kullanırsa darbe frekansı `f = I_out/Q_darbe` olur: 50 mA'de 500 kHz (= `f_s`), 10 mA'de **100 kHz**, 1 mA'de **10 kHz**. Frekansla orantılı kayıplar (kapı, Coss, ters toparlanma, ölü zaman) 10 mA'de beşte birine iner. Üst sınır: yalnız `I_q` kalsaydı (25 µA, **varsayım**, 0,6 mW) 10 mA'de verim **%98,8**'yi aşamazdı. Bu bir **üst sınırdır**; darbelerin kendi iletim kayıpları nedeniyle gerçek değer daha düşüktür, datasheet'teki verim eğrisine bak.

**Yan etkiler:**
- **Duyulabilir gürültü.** Darbe frekansı işitilebilir banda (≈ 20 kHz) düşebilir; örnekte **2,0 mA** altında olur. Bobin ve seramik kapasitörler "ötebilir". (Genel mühendislik bilgisi; bu derste bir kaynakta doğrulanmadı.)
- **Değişken frekans = dağınık spektrum.** EMC ölçümünü yalnız tam yükte değil, **bütün yük aralığında** tara (bölüm 15).
- **Mod geçişi.** Yük arttığında IC PFM'den PWM'e geçer; geçiş noktasında çıkış gerilimi geçici sapabilir. Yük adımını **her iki modda ve geçiş noktasında** ölç (bölüm 16).
- **Çıkış dalgalanması ve ortalaması FPWM'den farklıdır.** Datasheet'teki PFM çıkış toleransını oku.

> **Seçim kuralı:** Bekleme akımı kritikse **auto-PFM**; gürültü kritikse **FPWM**; ikisi birden kritikse buck + LDO (bölüm 1) ya da modu ölçüme göre seç. Bu mod için kendi IC'nin datasheet bölümünü oku (örnek doküman: TI LM76002/LM76003, §7.4.6 Light Load Mode). Otomatik PFM/PWM ile zorla PWM karşılaştırması için TI SLVAF55 §4.4; PFM'de verim tahmini için Electronic Design (2007) "Determine buck converter efficiency in PFM mode" ek okumadır.

## 9. Kontrol döngüsü ve kompanzasyon

Duştaki sıcaklık ayarını düşün: su gecikmeyle gelir. Musluğu çok hızlı çevirirsen sıcak-soğuk arasında **salınırsın**; çok yavaş çevirirsen suyun ısınması beklemekle geçer. Regülatör döngüsünde de ödünleşim aynıdır: **hız** (çapraz frekans `f_c`) ile **kararlılık** (faz payı) arasında.

### 9.1 Döngünün parçaları ve ölçütler

| Blok | Görevi | Örnek A (tepe akım modlu buck) |
|---|---|---|
| Güç katı | Kontrol büyüklüğünü `V_out`'a çevirir | `A_dc = g_m,ps·R_L` = 5 A/V · 5 Ω = **25** (≈ 28 dB); kutup `f_p` = **1315 Hz** |
| Geri besleme bölücü | `V_out`'u `V_ref` seviyesine indirir | `A_fb = V_ref/V_out` = 0,8/5 = **0,16** |
| Hata amplifikatörü + kompanzatör | Hatayı kuvvetlendirir, eğriyi şekillendirir | `g_m,ea` = 1,0 mS, `R_c`, `C_c`, `C_hf` |
| Örnekleme | Akım bilgisi çevrimde bir kez güncellenir | `f_sw/2`'de çift kutup (`Q` = 0,7, **varsayım**) |

Döngü kazancı `T = A_fb · g_m,ea · Z_c · G_vc`. Üç ölçüt:
- **Çapraz frekans `f_c`:** `|T| = 1` (0 dB) olduğu frekans; yük adımına tepki hızını belirler.
- **Faz payı (PM):** `PM = 180° + ∠T(f_c)`; zil sesini ve aşımı belirler.
- **Kazanç payı (GM):** `∠T = −180°` iken `−|T|` (dB); kazanç değişirse ne kadar tolerans var.

Hedefler (tasarım tercihi, yaygın uygulama): `f_c` ≈ `f_sw/10` (en çok `f_sw/5`), **PM ≥ 45°** (hedef 50–60°), GM ≥ 6 dB (tercihen ≈ 10 dB).

### 9.2 Kontrol modu: tepe akım mı, gerilim modu mu?

| | Tepe akım modu (PCM) | Gerilim modu (VM) |
|---|---|---|
| Güç katı | Tek kutup `f_p = 1/(2π·R_L·C_out)` + örnekleme çift kutbu | LC çift kutup `f_o = 1/(2π√(L·C))`, yüksek `Q` |
| Örnek A | `f_p` = 1315 Hz | `f_o` = 5,6 kHz, `Q` = 4,3 |
| ESR sıfırı | 2,19 MHz (seramikte çok yüksek, işe yaramaz) | aynı |
| Kompanzatör | **Tip II** (1 sıfır, 1 yüksek frekans kutbu) | **Tip III** (2 sıfır, 2 kutup) |
| Akım limiti | Çevrim başına doğal olarak vardır | Ayrı devre gerekir |

VM'de çift kutup fazı hızla −180°'ye çeker ve Tip II yetmez; seramik çıkışta ESR sıfırı da yardım etmez (`f_ESR` = 2,19 MHz). Entegre buck IC'lerin çoğu PCM'dir; bu yüzden örnek PCM'dir.

### 9.3 Tip II reçetesi (Örnek A)

1. **Güç katı:** `f_p = 1/(2π·R_L·C_out,eff)` = 1/(2π · 5 Ω · 24,2 µF) = **1315 Hz**. Etkin kapasite kullanılır (bölüm 4.5).
2. **Çapraz frekans hedefi:** `f_c = f_sw/10` = **50 kHz**.
3. **`R_c`:** `f_p`'nin üstünde güç katı −20 dB/dek iner, kompanzatör ortası düzdür; `|T| = 1` koşulundan `R_c = f_c/(f_p·g_m,ea·A_fb·A_dc)` = **9,5 kΩ**.
4. **`C_c`:** `C_c = 5/(2π·f_c·R_c)` = **1,67 nF**. Sıfır `f_z = 1/(2π·R_c·C_c)` = **10,0 kHz** (= `f_c/5`); `f_c`'de sıfır ≈ 79° faz yükseltir (`arctan 5`).
5. **`C_hf`:** `C_hf = 1/(2π·R_c·f_sw/2)` = **67 pF**: kutbu `f_sw/2`'ye koyar, anahtarlama gürültüsünü bastırır.
6. Değerleri standart seriye (E96, E12) yuvarla, **etkisini yeniden hesapla ya da ölç**.

```
Döngü kazancı |T| (üst) ve fazı (alt), Tip II, PCM buck, bölüm 9 örneği

         ┌─────────────────────────────────────────────────────────────┐
   +60 dB│                    :             :     :                    │
   +55 dB│                    :             :     :                    │
   +50 dB│•••                 :             :     :                    │
   +45 dB│  ••••              :             :     :                    │
   +40 dB│     ••••           :             :     :                    │
   +35 dB│        ••••        :             :     :                    │
   +30 dB│           ••••     :             :     :                    │
   +25 dB│              ••••  :             :     :                    │
   +20 dB│                 ••••             :     :                    │
   +15 dB│                    ••••          :     :                    │
   +10 dB│                    :  •••••      :     :                    │
    +5 dB│                    :      •••••• :     :                    │
     0 dB│--------------------------------•••••------------------------│
    −5 dB│                    :             : ••••••                   │
   −10 dB│                    :             :     :•••••               │
   −15 dB│                    :             :     :    •••             │
   −20 dB│                    :             :     :      •••           │
   −25 dB│                    :             :     :        •••         │
   −30 dB│                    :             :     :          •••       │
   −35 dB│                    :             :     :            ••      │
   −40 dB│                    :             :     :             •••••••│
         └─────────────────────────────────────────────────────────────┘
          1 kHz               10 kHz              100 kHz             1 MHz
                                            ▲ f_c = 48,2 kHz

         ┌─────────────────────────────────────────────────────────────┐
       0°│                    :             :     :                    │
     −15°│                    :             :     :                    │
     −30°│                    :             :     :                    │
     −45°│                    :             :     :                    │
     −60°│                    :             :     :                    │
     −75°│                    :             :     :                    │
     −90°│                    :             :     :                    │
    −105°│                    :             :     :                    │
    −120°│••••                :  •••••••••••••    :                    │
    −135°│---•••••••••••••••••••••-----------••••••--------------------│
    −150°│                    :             :     •••                  │
    −165°│                    :             :     : •••                │
    −180°│════════════════════════════════════════════•••••••••••••••••│
         └─────────────────────────────────────────────────────────────┘
          1 kHz               10 kHz              100 kHz             1 MHz

 faz payı ≈ 55° (f_c'de faz −125°) · kazanç payı ≈ 13 dB (164 kHz'te faz −180°)
 '-' = −135° (45° faz payı sınırı) · '═' = −180° (daha düşük fazlar bu satıra kırpılır)
```

Sonuç (güç katı + ESR sıfırı + örnekleme çift kutbu + Tip II): `f_c` = **48,2 kHz**, **PM = 55°**, **GM = 13 dB** (164 kHz'te faz −180°). Hedef 50 kHz'ten biraz düşük çıktı: kutuplar birbirini etkiler. Reçete, hedefe yakın ve yeterli faz payıyla bir **başlangıç noktasıdır**; son ayar ölçümle yapılır (bölüm 16).

### 9.4 Plant değişirse ne olur?

Aynı kompanzatörle, güç katı değiştirildi:

| Durum | `f_c` | PM |
|---|---|---|
| Nominal (1 A, 24,2 µF) | 48,2 kHz | 55° |
| `C_out` −%20 | 59 kHz | 51° |
| `C_out` +%20 | 41 kHz | 57° |
| Hafif yük 0,1 A (`f_p` = 132 Hz) | 48 kHz | 53° |

PCM'de `f_p`'nin üstünde kazanç `R_L`'den bağımsızdır, **`C_out` ile ters orantılıdır**: yük `f_c`'yi taşımaz, kapasite taşır. Seramiğin DC bias ve sıcaklıkla kapasite kaybı tam bu yüzden önemlidir: döngüyü **etkin değerle** tasarla, ±%20'de PM'e bak. Örnekte PM hep 51–57° bandındadır.

### 9.5 `f_c` nasıl seçilir?

Her satırda reçete yeniden uygulandı:

| `f_c/f_sw` | `f_c` | PM |
|---|---|---|
| %5 | 25 kHz | 69° |
| %10 | 48 kHz | 55° |
| %20 | 89 kHz | 32° |
| %30 | 122 kHz | 14° |

`f_c` yükseldikçe `f_sw/2`'deki örnekleme çift kutbu faz payını yer: %20'de PM 32°, %30'da 14°. Düşük `f_c` güvenlidir ama yük adımına yavaş tepki verir. **Bu yüzden `f_c` ≈ `f_sw/10` ile başlanır.**

### 9.6 Faz payı ne demek?

Standart ikinci derece modelde faz payı, sönüm oranı `ζ` ve adım yanıtı aşımı birbirine bağlıdır:

| PM | `ζ` | Aşım |
|---|---|---|
| 30° | 0,27 | %42 |
| 45° | 0,42 | %23 |
| 60° | 0,61 | %9 |
| 70° | 0,80 | %1 |

Gerçek devrede başka kutuplar vardır; tablo kaba bir göstergedir. **PM < 45°'de yük adımında çıkış zil çalar**; 30°'de neredeyse osilasyondur.

### 9.7 Boost ve ters buck-boost için not

Bu iki topolojide **RHPZ** (bölüm 5.3) `f_c`'yi `f_RHPZ/5` ile sınırlar. Çıkış kapasitörünü büyütmek RHPZ'yi taşımaz; yalnız `f_c`'yi aşağı çeker. Sonuç: aynı yük adımı için boost'un çıkışı buck'a göre daha çok sapar ve daha yavaş toparlanır. Boost kompanzasyonunda yüksek `f_c` hedefleme.

### 9.8 Kaynaklarla çapraz kontrol

Reçete iki yayımlanmış örnekle sınandı:
- **Hegarty (How2Power Today, Temmuz 2014):** aynı formüller `R_c` = **8,4 kΩ**, `C_c` = **1,57 nF**, `C_hf` = **7,8 pF** verir; makalenin değerleri 8,4 kΩ / 1,6 nF / 8 pF (fark en çok %5).
- **Richtek AN028:** belgedeki bileşen değerleriyle `f_p` ≈ **3,29 kHz**, ESR sıfırı **723 kHz**, kompanzatör sıfırı **4,33 kHz** ve kutbu **171 kHz** çıkar; hepsi belgedeki sayılarla uyumludur.

## 10. UVLO, geri besleme bölücüsü, soft-start ve koruma

### 10.1 UVLO: IC'yi ne zaman açacağını söyle

Sabit güçle çalışan bir regülatör, `V_in` düşünce **daha çok akım çeker** (`I = P/V`). Kaynak (adaptör, kablo, pil) bu akımda biraz daha çökerse: `V_in` düşer, akım artar, daha çok çöker. Bir de IC dropout bölgesinde sürekli açılıp kapanırsa **titreme (hiccup)** olur. Çözüm: EN pinindeki bölücüyle **açılma eşiği** koymak ve histerezisle geri dönüşü zorlaştırmak.

`V_on = V_EN·(1 + R_t/R_b)`, `R_t = R_b·(V_on/V_EN − 1)`. Örnek A: `V_on` = 16 V (hat en az 18 V; marj), `V_EN` yükselirken 1,2 V, düşerken 1,1 V (**varsayım**), `R_b` = 10 kΩ:
- `R_t` hesabı **123,3 kΩ** → E96 **124 kΩ**.
- Gerçek eşikler: `V_on` = **16,08 V**, `V_off` = **14,74 V**, histerezis **1,34 V**.
- `V_in` = 30 V iken EN pininde **2,24 V** oluşur: IC'nin EN pini mutlak azami gerilimini kontrol et.

Histerezis, kaynağın yük altındaki çökmesinden **büyük** olmalıdır; yoksa açılır, çöker, kapanır, toparlanır, tekrar açılır.

### 10.2 Geri besleme bölücüsü

`V_out = V_ref·(1 + R_t/R_b)`; `R_b` = 10 kΩ, `V_ref` = 0,8 V → `R_t` hesabı **52,5 kΩ** → E96 **52,3 kΩ** → `V_out` = **4,984 V** (%−0,32).
- **Akım:** bölücü 80 µA çeker (0,40 mW). Büyük direnç gürültüye ve FB pini kaçak akımına duyarlılık getirir; küçük direnç hafif yükte bile kayıp demektir.
- **Tolerans:** %1 dirençle yalnız bölücüden gelen en kötü durum hatası ±**%1,7**; `V_ref` toleransı ayrıca eklenir. Hassas çıkış için %0,1 direnç ya da trim.
- **FB yolu:** bölücüyü IC'nin FB pinine **bitişik** koy, `V_out` sensing hattını bobinden uzak ve sıcak düğümlerden izole yönlendir (bölüm 14).

### 10.3 Soft-start

Soft-start, `V_ref`'i rampalayarak `V_out`'u yavaş yükseltir. Aksi hâlde boş `C_out` bir anda dolmak ister ve akım limitine çarpar. Çıkış kapasitörünü dolduran akım `I_açılış = C_out·V_out/t_ss` = 44 µF · 5 V/2 ms = **110 mA** (yükün akımı bunun üstüne biner; toplam `I_LIM` altında kalmalı).
- **Çok kısa `t_ss`:** inrush akım limitine çıkar, giriş çöker, UVLO tetiklenir.
- **Çok uzun `t_ss`:** sıralama (sequencing) ve reset zamanlamaları gecikir.
- **Ön yüklü (pre-bias) başlangıç:** çıkış açılışta zaten doluysa IC alt FET'i **kapalı tutmalı**; aksi hâlde doluyu boşaltıp zarar verir. IC'nin pre-bias davranışını datasheet'ten oku.

### 10.4 Akım limiti ve kısa devre

- **Çevrim başına tepe limiti:** `I_LIM` = 1,7 / 2,0 / 2,4 A (min/tip/maks, **varsayım**). Bobin `I_sat` ≥ `I_LIM,maks` (bölüm 4.4).
- **Kısa devrede aşım:** `V_out ≈ 0` iken bobin açık kalma süresince `V_in` ile dolar, kapalı kalmada **neredeyse hiç boşalmaz** (`V_out/L ≈ 0`): akım çevrimden çevrime merdiven gibi tırmanır. IC tepe limitinde keser ama algılama ve kapı gecikmesi (`t_gecikme` = 100 ns, **varsayım**) boyunca akım `V_in·t_gecikme/L` = **0,091 A** daha çıkar. Gerçek tepe `I_LIM,maks` + aşım = **2,49 A**; bobin bunun üstünde doyuma girmemelidir (2,64 A ✓).
- **Kısa devre davranışı:** IC'ler genelde frekansı düşürür (foldback) ya da **hiccup** moduna girer (kısa süre dener, bekler, yeniden dener). Davranış IC'ye bağlıdır: datasheet'ten oku ve kısa devreyi **ölç**.
- **Boost'ta** çıkış kısa devresi IC limitiyle kesilemez (bölüm 5.4).

### 10.5 Diğer korumalar

| Koruma | Ne yapar | Tasarımda kontrol |
|---|---|---|
| UVLO | Düşük `V_in`'de açılmayı engeller | Eşik, histerezis (10.1) |
| OVP | Çıkış yükselirse anahtarlamayı keser | Eşik, çıkış kapasitörünün gerilim derecesi |
| Akım limiti, hiccup | Aşırı akımı ve kısa devreyi sınırlar | `I_sat`, kısa devrede ölçüm (10.4) |
| Termal kapanma | `T_j` sınırı aşarsa durur | Ölçülen `T_j` payı (bölüm 16) |
| PG (power good) | Çıkışın hazır olduğunu bildirir | Eşik, açılış sırası, pull-up gerilimi |

## 11. Giriş tarafı: sıcak takma, damper ve negatif empedans

### 11.1 Sıcak takma (hot-plug) tepesi

Su borusunda vanayı ani kapatınca **su darbesi** olur: akan suyun kütlesi durmak istemez ve basıncı sıçratır. Kablo da böyledir: akım indüktansta saklıdır, seramik giriş kapasitörü dolarken akım **durmak istemez** ve gerilim kaynağın üstüne çıkar.

Kablo indüktansı `L` ile seramik `C_in` bir **LC rezonatör** kurar; direnç küçükse sönüm zayıftır. Seri RLC adım yanıtının tepesi `V_in·(1 + e^(−πζ/√(1−ζ²)))`, `ζ = ½·R_s·√(C_in/L)`: `ζ` küçüldükçe **2×V_in**'e yaklaşır, ideal durumda aşmaz.

Örnek: 24 V adaptör, `L` = 5 µH, `R_s` = 0,10 Ω, `C_in` = 11 µF (etkin). `Z0 = √(L/C)` = **0,67 Ω**, `ζ` = **0,07**, tepe **43,0 V (×1,79)**, tepe zamanı `π·√(L·C)` = **23,3 µs**. Benzetim (zaman alanı) ideal formülle %0,5 içinde uyuşur.

Kablo ve kaynak direncinin etkisi (yine 24 V, 11 µF etkin):

| Kablo `L` | `R_s` = 0,05 Ω | `R_s` = 0,30 Ω |
|---|---|---|
| 1 µH | 42,5 V (×1,77) | 28,0 V (×1,17) |
| 5 µH | 45,4 V (×1,89) | 35,7 V (×1,49) |
| 10 µH | 46,1 V (×1,92) | 38,5 V (×1,61) |

Seri direnç tepeyi düşürür ama **sıfırlamaz**; en kötü durum **kısa, kalın kablo ve düşük çıkış empedanslı kaynaktır**.

**Kaynak ölçümü (Linear/ADI AN88):** 24 V adaptör, ~1 µH kablo, korumasız girişte:

| Giriş kapasitörü ve koruma | Ölçülen tepe |
|---|---|
| 10 µF seramik | **57,2 V** (×2,38) |
| 22 µF seramik | **40,8 V** (×1,70) |
| 22 µF seramik + 30 V TVS (P6KE30A) | **32,0 V** |
| 22 µF seramik + 47 µF Al-elektrolitik (ESR 0,44 Ω) | **25,0 V** |

AN88 "tepe, giriş adımının kolayca iki katı olabilir" der; 10 µF'lık ölçüm bu çıtayı da aşmıştır (×2,38). Metin bu aşımın nedenini türetmez; doğrusal olmayan etkiler (örneğin seramiğin gerilimle kapasite kaybı) olası nedenlerdir, bu derste doğrulanmadı. **Sonuç:** ideal formüldeki 2× sınırına güvenme. Korumasız girişte `V_in,nom`'un **2,5×**'u kadar marj düşün (AN88'in ×2,38 ölçümünden türetilmiş ders kuralı); 24 V'lık bir hat için bu **60 V**'tur. IC'nin mutlak azami gerilimi ve giriş kapasitörlerinin gerilim derecesi bunun altında kalıyorsa damper ya da TVS ekle.

### 11.2 Damper: R_D–C_D kolu

Seramik `C_in`'e **seri R + büyük C** kolu paralel koyulur: `R_D` rezonansı sönümler, `C_D` kolu ağır tutar. Pratikte `C_D` **alüminyum elektrolitiktir** ve `R_D` kapasitörün kendi ESR'sidir (AN88'in çözümü tam budur: 47 µF, ESR 0,44 Ω).

```
adaptör + kablo → regülatör girişi

24 V ──[R_s]───[L_kablo]────────────┬───────────┬────────────── ► V_in (IC girişi)
adım                                │         [R_D]
                                 [C_in]         │
                                    │         [C_D]
                                    │           │
 GND ───────────────────────────────┴───────────┴──────────────
                             seramik      damper (Al-elektrolitik)

V_in(t):  • damper yok, tepe 43,0 V (×1,79)     o damper var, tepe 28,2 V (×1,17)
         ┌─────────────────────────────────────────────────────────────────┐
     50 V│-----------------------------------------------------------------│
     45 V│               •••   :                     :                     │
     40 V│            •••• ••••:                     :                     │
     35 V│           ••       •••                    •••••••••             │
     30 V│         •••         oooooooooooo        •••       ••••          │
     25 V│········••····oooooooo·•••······ooooooooooooooooooooooooooooooooo│
     20 V│       ••  oooo      :   ••          •••   :            ••••     │
     15 V│      ••oooo         :    •••      •••     :               ••••••│
     10 V│     •ooo            :      ••••••••       :                     │
      5 V│   oooo              :                     :                     │
      0 V│oooo                 :                     :                     │
         └─────────────────────────────────────────────────────────────────┘
          0                    32 µs                 64 µs                96 µs

'·' çizgisi 24 V (adım) · '-' çizgisi 48 V (2× sınırı)
C_in = 11 µF (etkin), L = 5 µH, R_s = 0,10 Ω, C_D = 47 µF, R_D = 0,44 Ω
```

Örnek (`C_D` = 47 µF, `R_D` = 0,44 Ω): tepe **43,0 V → 28,2 V** (×1,17). AN88'in ölçümü (25 V) aynı mertebededir; devreler birebir aynı değildir.

**`R_D` nasıl seçilir?** `n = C_D/C_in` olsun. Seri `R_D–C_D` kolunun çıkış empedansı tepesini en aza indiren optimum, Middlebrook'un klasik sonucudur:

`R_D,opt = Z0·√((2+n)(4+3n)/(2n²(4+n)))`

| `n = C_D/C_in` | `R_D,opt/Z0` | Tepe `\|Z\|/Z0` |
|---|---|---|
| 1 | 1,45 | 2,45 |
| 2 | 0,91 | 1,41 |
| 4 | 0,61 | 0,87 |
| 10 | 0,38 | 0,49 |

`n` büyüdükçe tepe küçülür; `n ≥ 4` makul bir başlangıçtır. Örnekte `n` = 4,3, optimum `R_D` = **0,40 Ω** (seçilen 0,44 Ω, tepe empedans 0,45 Ω). Formül literatürden alındı ve bu derste sayısal olarak doğrulandı (taramayla bulunan optimum formülle %2 içinde uyuştu).

### 11.3 Negatif giriş empedansı ve Middlebrook kriteri

Sabit güçlü yük **negatif direnç** gibi davranır: `V_in` düşünce akım artar. Küçük sinyal giriş direnci `R_in = −V_in²/P_in`. Örnek A: `P_in` = 5,42 W; `|R_in|` 18 V'ta **60 Ω**, 24 V'ta 106 Ω.

Kaynağın (kablo + giriş filtresi) çıkış empedansı `Z_out`'un tepesi `|R_in|`'in **çok altında** olmalıdır; kural: **en az 6 dB marj**, yani `|Z_out,tepe| ≤ |R_in|/2`. (TI Power Tip #4'ün örneği: 12 V, 12 W → `|R_in|` = 12 Ω → `Z_out` ≤ 6 Ω.)

| Durum | `Z_out` tepe | Marj |
|---|---|---|
| Örnek A, damper yok (`f` ≈ 21 kHz) | 4,6 Ω | **22,3 dB** |
| Örnek A, damperli | 0,45 Ω | **42,5 dB** |
| Aynı filtre, 12 V / 50 W (`\|R_in\|` = 2,9 Ω), damper yok | 4,6 Ω | **−4,1 dB** (kararsız) |
| Aynı filtre, 12 V / 50 W, damperli | 0,45 Ω | **16,1 dB** |

Örnek A (5,4 W) rahattır. Ama güç artarsa ve gerilim düşerse `|R_in|` çöker ve **aynı filtre kararsız hâle gelir**: damper sadece hot-plug için değil, kararlılık için de gereklidir.

## 12. 💼 İş yerinde

Yeni bir regülatör bloğu başlarken **aynı sırayla** sor: (1) `V_in` aralığı ve geçici olaylar (hot-plug, kesinti)? (2) `V_out`, akım ve yük adımı? (3) Verim ve ısı bütçesi? (4) Gürültüye duyarlı ne var (ADC, sensör, ses, RF)? (5) Bekleme ve pil ömrü? (6) Boyut ve maliyet?

| Ürün tipi | Tipik regülatör yolu | İlk sorular |
|---|---|---|
| Gaz dedektörü (pellistor/LEL köprü) | 12–24 V → buck → **LDO** (köprü ve referans için temiz hat) | Köprü beslemesi ve ADC referansı gürültüye çok duyarlıdır: buck + LDO (bölüm 1), `f_s`'i ölçüm bandının dışına koy; kesinti ve düşük gerilim alarmı için UVLO ve PG |
| İnterkom, kapı paneli | 12–24 V adaptör → buck (5 V, 3,3 V); ses katı için ayrı temiz hat | Hot-plug (kablo) tepesi, adaptör seçimi, ses gürültüsü (`f_s`, hafif yük modu), uzun kablo indüktansı |
| Dimmer, sensörlü LED lamba, varlık sensörü | Şebekeden küçük DC ([Ders 3](../sebekeli-guc-kaynaklari/ozet.md)), kartta buck ya da LDO | Şebeke bölümünün güvenliği Ders 1–3'tedir; kart içinde MCU ve sensör gürültüsü, bekleme akımı |
| Pil beslemeli sensör/etiket | Li-ion → buck-boost, boost ya da buck | Bekleme akımı (`I_q`, PFM), pil boşalırken `V_in` aralığı `V_out`'u kesiyor mu? |

**Yeni regülatör kartının ilk açılış sırası:**
1. **Yük yok**, akım sınırlı laboratuvar kaynağı: `V_in`'i yavaşça yükselt; giriş akımına ve UVLO eşiklerine bak (bölüm 10.1).
2. `V_out`, soft-start eğrisi ve **SW düğümü** (kısa toprak yayıyla); zil ve tepe değerleri (bölüm 16).
3. Yük adımı ve döngü kazancı (bölüm 9, 16); etkin kapasite ±%20.
4. Verim taraması ve ısı (kapalı kasa, yüksek ortam sıcaklığı).
5. Kısa devre ve **gerçek adaptör + kabloyla hot-plug**.

> Bu iş yeri tablosu genel örnektir; şirketin gerçek ürün şemaları ve değerleri bu notlara girmez. Bu ders SELV/DC tarafı içindir; şebeke bölgesinde [Ders 1](../sebeke-guvenligi-ve-yalitim/ozet.md)'in güvenlik kuralları geçerlidir.

## 13. Şematikte

- **Blok başlığı:** `V_in` aralığı, `V_out`, `I_out`, `f_s`, topoloji. Hesapları şematik notuna yaz: `D`, `ΔI_L`, `I_pk`, `I_MAXOUT`, `ΔV_out`, `I_Cin,rms`.
- **İndüktör:** `L`, `I_sat`, `I_rms`, DCR yazılı. **Kapasitörlerde** gerilim derecesi ve **etkin** (DC bias sonrası) kapasite notu.
- **Bölücüler:** UVLO (`V_on`, `V_off`, EN pini limiti), FB (`V_out` hesabı, direnç toleransı), soft-start, PG ve mod pini (FPWM/PFM) açıkça çizilsin.
- **Kompanzasyon:** `R_c`, `C_c`, `C_hf` değerleri ve "ölçümle ayarlanır" notu; döngü ölçümü için FB bölücüsünün üstünde enjeksiyon direnci için yer bırak (yaygın uygulama: 10–50 Ω, ölçüm sonrası 0 Ω'a çevrilir ya da kalır).
- **Giriş:** TVS ve damper yeri, giriş filtresi (varsa `Z_out` notu), ters polarite koruması.
- **Boost:** kapalıyken çıkışın girişi izlediği (yük anahtarı), kısa devre için giriş koruması. **Ters buck-boost:** referans düğümü (IC GND'si negatif çıkışta) ve seviye kaydırma notu.
- **Test noktaları:** SW, `V_out` (kısa toprak yayı için GND yanında), FB, EN, PG.

## 14. PCB / layout

Anahtarlamalı regülatörde şematik aynı olsa da **yerleşim** çalışıp çalışmayacağını belirler: aynı devre, kötü yerleşimle EMC testinde kalır ya da FB gürültüsüyle titrer. Kural basit: **yüksek `dI/dt`'li döngü küçük, yüksek `dV/dt`'li düğüm küçük, hassas iz bunlardan uzak.**

### 14.1 Sıcak döngü

Sıcak döngü: **C_in → HS → LS → C_in**. Bu halkada akım her çevrimde sıfırdan `I_L`'ye sıçrar; halka indüktansı `L_loop` bu `dI/dt`'yi gerilim sıçramasına çevirir (`V = L_loop·dI/dt`). AN-1229'daki kural: iz yaklaşık **20 nH/inç**.

```
KÖTÜ: C_in uzakta                             İYİ: C_in pinlere bitişik

        ┌─────────────────────────┐                   ┌───────┐
        │░░░░░░░░░░░░░░░░░░░░░░░░░│                   │░░░░░░░│
   [C_in]░░░░ geniş döngü alanı ░[IC]            [C_in]░░░░░░[IC] ◄ küçük döngü
        │░░░░░░░░░░░░░░░░░░░░░░░░░│                   │░░░░░░░│
        └─────────────────────────┘                   └───────┘

L_loop = 20 nH/in × 3 in = 60 nH              L_loop ≈ 5 nH
30 ns'de 1 A → V = L·di/dt = 2,0 V            aynı akımda V ≈ 0,17 V

Halka frekansı f = 1/(2π√(L_loop·C_oss)) = 225 MHz (L_loop = 5 nH, C_oss = 100 pF)
```

3 inçlik halka 60 nH eder; 30 ns'de 1 A, **2,0 V** sıçrama demektir. 5 nH'lik küçük halka aynı akımda **0,17 V** verir. Bu sıçrama IC'nin mutlak maksimum gerilimine binerse parça zarar görür; EMI olarak da yayılır. `L_loop` ile FET çıkış kapasitansı `C_oss` (100 pF, varsayım) bir **zil devresi** kurar: `f = 1/(2π√(L_loop·C_oss))` = **225 MHz** (5 nH ile).

### 14.2 Beş kural

```
    (1)
  ┌─────────┐       ┌───────────────────┐   (3)   ┌─────────┐         ┌─────────┐
  │         ├───────┤VIN             SW ├─────────┤    L    ├─────────┤         ├─► V_out
  │         │       │                   │         └─────────┘         │         │
  │ C_in    │       │        IC         │                             │  C_out  │
  │ (HF)    │       │                   │                             │         │
  │         ├───────┤GND             FB ├─────┐                       │         │
  └────┬────┘       └─────────┬─────────┘     │                       └────┬────┘
       │                      │               │     (4)                    │
       │                      │               │   ┌───────────┐            │
       │      (2) termal via  │               └───┤ FB bölücü │            │
       │                      │                   └─────┬─────┘            │
       │                      │                         │                  │
══════════════════════════════════════════════════════════════════════════════════════════
  (5) GND düzlemi kesintisiz
```

| # | Kural | Neden |
|---|---|---|
| (1) | **C_in HF (0,1–0,47 µF, X7R) VIN ve GND pinlerine bitişik**, aynı katmanda, yoldaki via'lar yok | Sıcak döngüyü kapatan en kısa yol |
| (2) | IC'nin ısı pedinin altına **termal via'lar**, geniş bakır | Isı yolu: `θ_JA` (bölüm 7.5) |
| (3) | **SW düğümü bakırını minimumda tut** | Yüksek `dV/dt`: anten ve kapasitif kuplaj |
| (4) | **FB bölücüsü** IC'ye bitişik; FB izi kısa, SW ve bobinden uzak; alt ucu temiz GND'ye | Gürültü FB'ye girerse çıkışta jitter ve kararsızlık |
| (5) | **Kesintisiz GND düzlemi**, anahtarlama döngüsünün altında bölünmemiş | Dönüş akımı altından akar; kesinti anten yapar |

- **Bobin:** SW düğümüne yakın; ekranlı (shielded) tip dış alanı azaltır; altında ve yakınında hassas iz ve FB hattı yok.
- **C_out ve algılama:** `C_out` bobinin çıkışına yakın; FB bölücüsünü yük noktasına yakın bir yerden besle (V_out sensing).
- **Akım yolları:** iz genişliği için başlangıç değeri AN-1229'da **12 mil/A**; IPC-2221 ile kendi bakır kalınlığına göre doğrula.
- Genel iz kuralları: [PCB yerleşim ve iz çizimi](../pcb-yerlesim-ve-iz-cizimi/ozet.md).

## 15. EMC açısından

Anahtarlamalı regülatörün gürültü kaynakları: SW düğümünün **hızlı gerilim kenarı** (24 V, nanosaniyeler), sıcak döngünün **darbeli akımı** ve diyot/LS toparlanma **zili** (14.1). Giriş akımı darbeli olduğundan (`I_Cin,rms` ≈ 0,37 A (30 V) ile 0,45 A (18 V) arasında, en kötü 0,50 A; bölüm 4.6) iletilen gürültü girişte öne çıkar.

- **Kaynağı küçült:** sıcak döngüyü küçült (bölüm 14); SW bakırını küçük tut; bazı IC'lerde kenar hızını ayarlayan pin ya da boot direnci vardır (hızı düşürür, kaybı artırır: bölüm 7.1); gerekirse SW'de RC **snubber** ile zili sönümle.
- **Frekansı seç:** `f_s` ve düşük harmonikleri ürünün hassas olduğu bantlara (radyo, alıcı, ADC örnekleme bandı) düşmemeli. Frekans titreşimi (spread spectrum) sunan IC'lerde zirveler yayılır.
- **Giriş filtresi:** LC ya da ferrit boncuk + kapasitör; ama filtre `Z_out` tepesi **`|R_in|`'in altında kalmalı** (bölüm 11.3). EMC filtresi eklemek kararlılığı bozabilir.
- **Hafif yükte** PFM değişken frekans demektir: EMC taramasını **bütün yük aralığında** yap (bölüm 8).
- Ön-test: yakın alan probu, **LISN**, filtreli/filtresiz karşılaştırma. Standartlar ürün ailesine göre (ör. EN 55032, EN 55015) ücretlidir; [EMC dersleri](../../EMC/03-emc-testleri-ve-standartlar/ozet.md) yöntemi anlatır. Devre notu: [EMC 02: anahtarlamalı kaynak gürültüsü](../../EMC/02-emc-icin-kart-tasarimi/ozet.md).

## 16. Ölçüm ve doğrulama

| Ölçüm | Nasıl | Beklenen |
|---|---|---|
| **Çıkış dalgalanması** | 20 MHz bant sınırı, **kısa toprak yayı** (tip-and-barrel), kısa toprak | ≈ 2,7–3,4 mV (bölüm 4.5); uzun toprak klipsi sıçramayı **şişirir** |
| **SW düğümü** | Kısa toprak yayı, yüksek bant genişlikli prob | Tepe IC'nin SW mutlak limitinin altında; zil sönümlü |
| **Yük adımı** | %10 ↔ %90, hızlı kenarlı elektronik yük | Aşım ve sapma bölüm 4.5 ile uyumlu, zil yok |
| **Döngü kazancı** | FB bölücüsünde seri enjeksiyon direnci + ağ analizörü; `C_out` ±%20 | `f_c` ≈ `f_s/10`, **PM ≥ 45°**, GM ≥ 6 dB |
| **Soft-start, UVLO** | `V_in` rampa ↑/↓, EN | Eşikler bölüm 10.1 ile uyumlu; çıkış monoton, aşım yok |
| **Akım limiti, kısa devre** | `V_out` → GND, akım probu | Tepe ≤ 2,49 A (hesap); hiccup/foldback IC'nin tarif ettiği gibi |
| **Hot-plug** | **Gerçek adaptör + kabloyla** tak, `V_in` tepesini yakala | Tepe IC ve kapasitör derecesinin altında (bölüm 11) |
| **Verim** | `V_in·I_in` ve `V_out·I_out` (4 telli), 10 mA–1 A | Bütçe ile uyum (bölüm 7.4) |
| **Hafif yük** | 0–100 mA tara; `V_out` ve SW frekansı; kulakla dinle | Mod geçişinde sapma küçük; işitilebilir ses yok |
| **Isı** | Termal kamera ya da termokupl; kapalı kasa, yüksek ortam | IC ve bobin `T_j` marjlı |
| **Giriş kararlılığı** | Giriş filtresi varsa düşük `V_in`, yüksek yükte | Osilasyon yok; `Z_out` ≤ `\|R_in\|/2` |
| **EMC ön-test** | Yakın alan probu, LISN | Limit altı, bütün yüklerde |

## 17. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| Buck'ta `L`'yi `V_in,min`'de hesaplamak | `ΔI_L` en büyük `V_in,maks`'ta | `L`'yi `V_in,maks` ile hesapla (bölüm 4.3) |
| Seramiğin DC bias kaybını unutmak | Etkin kapasite nominalin %55'i; dalgalanma ve PM değişir | Etkin değerle hesapla, ±%20'de kontrol et |
| `I_sat`'ı `I_out`'a göre seçmek | Kısa devrede `I_LIM`'e çıkar, bobin doyar | `I_sat ≥ 1,1·I_LIM,maks` (2,64 A) |
| Yalnız `I_sat`'a bakıp `I_rms`'i atlamak | Bobin ısınır | İkisini birden kontrol et (bölüm 4.4) |
| `t_on,min`'i hesaba katmamak | 24 V → 1,2 V, 2 MHz'te darbe atlama | `V_in,maks ≤ V_out/(f_s·t_on,min)` (bölüm 4.7) |
| Giriş kapasitörü ripple akımını atlamak | `I_Cin,rms` ≈ `I_out/2`'ye kadar çıkar; ısınır, ömür kısalır | Ripple derecesi ≥ `I_Cin,rms` |
| Hot-plug tepesini ideal 2× ile sınırlı sanmak | AN88: 24 V → **57,2 V** (×2,38) ölçüldü | 2,5× marj ya da damper/TVS (bölüm 11) |
| Giriş filtresi eklenip `\|R_in\|` kontrolü yapılmamak | Negatif direnç filtreyle osilasyon | `Z_out,tepe ≤ \|R_in\|/2` (bölüm 11.3) |
| Boost'ta kapalı hâli ve kısa devreyi unutmak | `V_out = V_in − V_F`; kısa devre IC limitiyle kesilmez | Yük anahtarı, giriş sigortası (bölüm 5.4) |
| Boost döngüsünü RHPZ'nin üstüne kapatmak | Faz payı erir, osilasyon | `f_c ≤ f_RHPZ/5` (bölüm 5.3) |
| Kompanzasyonu nominal `C_out` ile yapmak | Etkin değer düşünce `f_c` kayar | Etkin değer ve ±%20 (bölüm 9.4) |
| Sıcak döngüyü büyük bırakmak (C_in uzak, via'lı) | Zil, EMI, IC'ye sıçrama | C_in pinlere bitişik, viasız (bölüm 14) |
| FB izini bobin ya da SW yakınından geçirmek | Gürültü FB'ye girer: jitter | FB kısa, uzak, temiz GND'ye referanslı |
| UVLO koymamak | İnce kablo ya da pilde titreme (hiccup) | EN bölücüsü + histerezis (bölüm 10.1) |
| Soft-start süresini inrush hesabı olmadan seçmek | Akım limiti, giriş çökmesi | `C_out·V_out/t_ss` + yük < `I_LIM` |
| Hafif yük modunu gürültüye bakmadan seçmek | PFM'de işitilebilir ses; FPWM'de %36,7 verim (10 mA) | Önceliğe göre seç, ölç (bölüm 8) |
| Çıkış dalgalanmasını uzun toprak klipsiyle ölçmek | Sahte sıçrama | Kısa toprak yayı (tip-and-barrel) |
| Datasheet `θ_JA`'sına güvenmek | Kendi kartında farklı | Kartta ölç; bakır ve via ile iyileştir |

## 18. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Buck / boost / ters buck-boost** | Girişi düşüren / yükselten / ters kutuplu çıkış üreten anahtarlamalı dönüştürücü |
| **SEPIC, 4 anahtarlı buck-boost** | Girişin altında ve üstünde pozitif çıkış üreten topolojiler |
| **D (duty cycle)** | Üst anahtarın açık kalma oranı |
| **CCM / DCM** | Sürekli / kesintili iletim: indüktör akımı sıfıra iniyor mu? |
| **FPWM / PFM / darbe atlama** | Zorla sabit frekans / darbe sayısını yükle ayarlama / bazı çevrimleri atlama |
| **Senkron / asenkron** | Alt anahtar FET / diyot |
| **Diyot emülasyonu** | Akım sıfıra inince LS FET'i kapatma |
| **ΔI_L** | İndüktör akımı dalgalanması (tepeden tepeye) |
| **I_sat / I_rms** | İndüktörün doyma akımı / ısınma akımı |
| **ESR** | Kapasitörün eşdeğer seri direnci |
| **DC bias** | Seramikte gerilimle kapasite kaybı |
| **t_on,min** | IC'nin üretebildiği en kısa açık kalma süresi |
| **UVLO** | Düşük gerilimde açılmayı engelleyen eşik |
| **Soft-start** | Çıkışı yavaş yükseltme rampası |
| **Pre-bias** | Açılışta çıkışın zaten dolu olması |
| **Hiccup / foldback** | Kısa devrede kesik deneme / frekans düşürme |
| **PCM / VM** | Tepe akım modu / gerilim modu kontrol |
| **f_c, PM, GM** | Çapraz frekans, faz payı, kazanç payı |
| **Tip II / Tip III** | 1 sıfırlı / 2 sıfırlı kompanzatör |
| **RHPZ** | Sağ yarı düzlem sıfırı (boost, ters buck-boost) |
| **SW düğümü** | Bobin, HS ve LS'nin buluştuğu hızlı anahtarlanan düğüm |
| **Sıcak döngü** | C_in–HS–LS yüksek `dI/dt` halkası |
| **Hot-plug** | Beslemenin çalışırken takılması |
| **Damper** | Giriş LC rezonansını sönümleyen R–C kolu |
| **Negatif giriş direnci** | Sabit güçlü yükün küçük sinyal direnci: `R_in = −V_in²/P_in` |
| **Middlebrook kriteri** | Kaynağın çıkış empedansı tepesi, giriş direncinin mutlak değerinin altında kalmalı (≥ 6 dB marj) |
| **θ_JA** | Eklemden ortama ısıl direnç (°C/W) |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (bölüm 3, Regülatörler):

- [x] **Topoloji ve aralık:** topoloji `V_in` aralığına göre seçildi (buck: `V_in > V_out`; boost: `V_in,maks < V_out`; aralık `V_out`'u kesiyorsa ya da çıkış negatifse ters buck-boost, SEPIC veya 4 anahtarlı buck-boost); `D = V_out/(V_in·η)` en düşük ve en yüksek `V_in`'de hesaplandı; `V_in,maks ≤ V_out/(f_s·t_on,min)` sağlanıyor
- [x] **İndüktör:** `L = V_out·(V_in,maks − V_out)/(ΔI_L·V_in,maks·f_s)` ile `ΔI_L` ≈ 0,2–0,4·I_out (boost'ta `I_L,ort`) seçildi; `I_sat ≥ I_LIM,maks` (%10 marjla) ve kısa devrede algılama gecikmesi aşımı `V_in,maks·t_gecikme/L` eklenince de doymuyor; `I_rms` (ısınma) ve DCR kaybı (`I_rms²·DCR`) hesaplandı
- [x] **Çıkış kapasitörü:** seramiğin DC bias sonrası **etkin** değeri kullanıldı; `ΔV = ΔI_L/(8·f_s·C) + ESR·ΔI_L` hesaplandı; yük bırakma aşımı (`C_out ≥ L·ΔI²/(2·V_out·V_aşım)`) sınırı sağlanıyor; boost'ta ESR kısmı `ESR·I_pk` ile ve çıkış ripple akımı `I_out·√(D/(1−D))` kapasitörün akım derecesiyle karşılaştırıldı
- [x] **Giriş kapasitörü:** buck'ta `I_Cin,rms = I_out·√(D·(1−D))` (en kötü `I_out/2`) kapasitörün ripple akımı derecesinin altında; IC pinlerine bitişik HF seramik (0,1–0,47 µF) ve bulk kapasitör birlikte var; `ΔV_in = I_out·D·(1−D)/(f_s·C_in)` etkin kapasiteyle hesaplandı
- [x] **Kontrol döngüsü:** `f_c` ≈ `f_s/10`, faz payı ≥ 45° (hedef 50–60°), GM ≥ 6 dB; `C_out` ±%20 ve hafif yükte de kontrol edilecek; boost ve ters buck-boost'ta `f_c ≤ f_RHPZ/5` (en kötü durum: tam yük, düşük `V_in`); FB bölücüsünün üstünde döngü ölçümü için enjeksiyon direnci yeri (10–50 Ω) bırakıldı
- [x] **UVLO, FB ve soft-start:** EN bölücüsüyle `V_on`, `V_off` ve histerezis ayarlandı (histerezis kaynağın yük altındaki çökmesinden büyük); en yüksek `V_in`'de EN pini gerilimi mutlak azami değerin altında; FB bölücü hatası (%1 dirençle ≈ ±%1,7 + `V_ref` toleransı) kabul edilebilir; soft-start inrush akımı `C_out·V_out/t_ss` + yük akımı `I_LIM` altında; pre-bias açılış davranışı datasheet'ten okundu
- [x] **Akım limiti ve kısa devre:** `I_MAXOUT = I_LIM,min − ΔI_L/2 ≥ I_out,maks`; kısa devre davranışı (foldback ya da hiccup) datasheet'ten okundu ve ölçüldü; boost'ta çıkış kısa devresini IC kesemez ve kapalıyken `V_out ≈ V_in − V_F` olur: giriş sigortası/akım sınırı ya da yük anahtarı (true-shutdown) var
- [x] **Giriş hattı etkileşimi:** hot-plug tepesi gerçek adaptör ve kabloyla ölçüldü; korumasız girişte `V_in,nom`'un 2,5×'u (AN88: 24 V girişte 57,2 V ölçüldü) IC'nin mutlak azami gerilimi ve kapasitör derecesinin altında, değilse damper (Al-elektrolitik, `C_D ≥ 4·C_in`) ya da TVS var; giriş filtresi varsa `Z_out` tepesi ≤ `|R_in|/2` (`|R_in| = V_in²/P_in`, ≥ 6 dB marj)
- [x] **Kayıp, ısı ve hafif yük:** kayıp bütçesi (iletim + anahtarlama + sabit) çıkarıldı; `T_j = T_a + P·θ_JA` marjlı; hafif yükte verimi sabit kayıp tabanı belirler: 10 mA ile tam yük arasındaki yük aralığı değerlendirildi; PFM/FPWM seçimi hassas analog ve işitilebilir ses (< 20 kHz) açısından yapıldı
- [x] **Yerleşim:** sıcak döngü (C_in–HS–LS) en küçük; HF C_in VIN ve GND pinlerine bitişik, aynı katmanda, via'sız; SW bakırı minimum; FB bölücü IC'ye bitişik ve FB izi SW ile bobinden uzak; kesintisiz GND düzlemi; IC ısı pedi altında termal via; bobinin altında ve yakınında hassas iz yok

## Kontrol soruları

→ [quiz.md](quiz.md) · 12 soru, 8'i hesap
