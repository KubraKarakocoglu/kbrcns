# Şebekeli güç kaynakları: kapasitif düşürücü ve flyback

- **Oluşturma:** 2026-11-19
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)
- **Bağlantılı:** [Şebeke güvenliği ve yalıtım](../sebeke-guvenligi-ve-yalitim/ozet.md) · [Triyak ve faz kontrolü](../triyak-ve-faz-kontrolu/ozet.md) · [Güç katı: koruma ve regülatör](../guc-kati-koruma-ve-regulator/ozet.md) · [MOSFET, transistör ve yük sürme](../mosfet-transistor-ve-yuk-surme/ozet.md) · [PCB yerleşim ve iz çizimi](../pcb-yerlesim-ve-iz-cizimi/ozet.md) · [Kapasitör](../../Komponentler/02-kapasitor/ozet.md) · [Bobin](../../Komponentler/03-bobin-induktor/ozet.md) · [EMC için kart tasarımı](../../EMC/02-emc-icin-kart-tasarimi/ozet.md) · [EMC testleri ve standartlar](../../EMC/03-emc-testleri-ve-standartlar/ozet.md) · Sonraki: Anahtarlamalı regülatör tasarımı (Ders 4, hazırlanıyor)

> Sayısal değerler **tipik başlangıç noktalarıdır**. Kapasitif düşürücü akımları yük dengesi ve zaman simülasyonuyla, flyback sayıları onsemi **AN-4137**, **AN-4147**, ADI makalesi ve TI **TL431** datasheet'indeki formül ve değerlerle betikle yeniden hesaplandı. **Kendi parçanın datasheet'i esastır.** Şebekeli güç kaynağı bir güvenlik ürünüdür: ürün standartları (ör. EN 62368-1, EN 60335-1, EN 60598-1) ve EMC standartları ücretlidir ve bu notlarda yoktur. Ders hesabı ve doğru soruları öğretir; sertifikasyonun yerine geçmez. **Kapsam dışı:** PFC, LLC/rezonanslı dönüştürücüler, senkron doğrultma, 100 W üstü.
>
> **Uyarı:** Bu derste anlatılan devrelerde **kapasitif düşürücünün tamamı, flyback'in primer tarafı şebeke potansiyelindedir**. Enerjilendirmeden önce [Şebeke güvenliği dersinin](../sebeke-guvenligi-ve-yalitim/ozet.md) bölüm 14'ünü oku: izolasyon trafosu, seri ampul, diferansiyel prob, deşarj kontrolü.
>
> **Okuma planı:** 1. oturum: bölüm 1–3 (seçenekler, kapasitif düşürücü, flyback çalışması) · 2. oturum: 4–7 (tasarım adımları, clamp, geri besleme, koruma) · 3. oturum: 8–16 (giriş, bekleme gücü, iş yeri, PCB, EMC, ölçüm, hatalar).

---

## ⚡ Hızlı tekrar

1. Şebekeden küçük bir DC için üç yol var: **kapasitif düşürücü** (izolasyonsuz, ≈ 20–30 mA), **izolasyonsuz anahtarlamalı** (izolasyonsuz, yüzlerce mA) ve **flyback** (izolasyonlu, W'lar). Kullanıcı bir yere dokunabiliyorsa seçenek **flyback ya da hazır sertifikalı modüldür**.
2. Kapasitör bir **akım musluğudur**: `I_rms = V·2π·f·C`. 470 nF, 230 V / 50 Hz → **34,0 mA**. Köprüyle yüke giden **ortalama** akım `4·f·C·(V_tepe − V_on)` = **30,0 mA**, yarım dalgada **15,1 mA** (yarısı).
3. Dropper'da R1 hem açılış akımını sınırlar hem ısınır: 470 Ω için `(V_tepe − V_on)/R1 = 0,68 A`, ama `I²·R1 = 0,54 W` (en kötü hatta **0,94 W**). AN954'ün ½ W'lık R1 hesabı 21,3 mA'e dayanır (120 V / 60 Hz için uyar); 230 V'ta **yetmez**.
4. Kapasitif düşürücü **izolasyonsuzdur**: akım kısılır, ama ≈ 34 mA insan için tehlikelidir (Class II dokunma akımı sınırının **≈ 136 katı**). Dokunulabilir iletken parçası olan ürüne konmaz.
5. Flyback'te trafo bir **depodur**: MOSFET iletimde enerjiyi depolar, kapanınca sekondere boşaltır. DCM'de `P = ½·L_m·I_pk²·f_s`.
6. 12 V / 1 A örneği: `P_in = 14,1 W`, `V_DC,min = 90 V`, `n = 6`, `V_RO = 75 V`, `D = 0,45`, `L_m = 820 µH`, `I_pk = 0,728 A`, `N_p : N_s = 66 : 11`.
7. `V_DC,min` bulk kapasitörden gelir: `√(2·V_hat² − P_in·(1 − D_ch)/(C·f_L))`, `D_ch ≈ 0,2`. 47 µF'ta **98 V**; C −%20'de **92 V** → tasarımda **90 V**.
8. MOSFET gerilimi `V_DS = V_DC,maks + V_sn`: 375 + 150 = **525 V** (%81, 650 V parça). Clamp kaybı `½·L_lk·I_pk²·f_s·V_sn/(V_sn − V_RO)` = **0,42 W**; `V_sn` düştükçe kayıp **artar**.
9. Geri besleme `V_o = V_ref·(1 + R1/R2)`: 38,3 k / 10 k → **12,05 V**; en kötü **−%1,6 … +%3,8**. TL431'e **≥ 1 mA** katot akımı ver; opto'yu **CTR_min** ile boyutla. Geri besleme yolu **açık devre** olursa çıkış yükselir: OVP şart.
10. Dış güç kaynağında bekleme sınırı **≤ 0,100 W** (≤ 49 W AC-DC). X2 deşarj direnci (2 MΩ → **26,5 mW**) ve dirençli start-up (2 MΩ → **52,8 mW**) bütçenin **%79'unu** yer.
11. Trafo ve opto, **güçlendirilmiş yalıtım bariyerinin** parçasıdır (Ders 1): 3000 Vac, kriper/klirens, TIW veya margin bant, Y1 kapasitör. Trafo çizimi bir güvenlik belgesidir.

## 🧮 Formül kartı

| Formül | Ne zaman kullanılır | Örnek |
|---|---|---|
| `X_C = 1/(2π·f·C)`, `I_rms = V/X_C` | Kapasitif düşürücü: kapasitör akımı | 470 nF, 230 V, 50 Hz → 6,77 kΩ, **34,0 mA** |
| `I_ort,köprü = 4·f·C·(V_tepe − V_on)`, `V_on = V_Z + 1,4 V` | Yüke giden en çok DC akım (köprü) | 5,1 V Zener → **30,0 mA** |
| `I_ort,yarım = f·C·(2·V_tepe − V_Z − 1,4 V)` | Aynısı, yarım dalga | **15,1 mA** |
| `P_R1 = I_rms²·R1` | Seri direncin sürekli ısısı | (34,0 mA)²·470 Ω = **0,54 W** |
| `I_açılış = (V_tepe − V_on)/R1`, `E = ½·C·(V_tepe − V_on)²` | Tepede bağlanma darbesi | 0,68 A (470 Ω), 3,19 A (100 Ω); **23,9 mJ** |
| `P_in = P_out/η` | Giriş gücü | 12 W / 0,85 = **14,1 W** |
| `V_DC,min = √(2·V_hat² − P_in·(1 − D_ch)/(C·f_L))` | Bulk gerilimin dibi | 85 V, 47 µF, D_ch 0,2 → **98,2 V** |
| `V_RO = n·(V_o + V_F)`, `D = V_RO/(V_DC,min + V_RO)` | Yansıyan gerilim, görev oranı | 6·12,5 = **75 V**, D = **0,4545** |
| `L_m,maks = (V_DC,min·D)²/(2·P_in·f_s)` | DCM sınırı | **912 µH** |
| `I_pk = √(2·P_in/(L_m·f_s))` | DCM tepe akımı | 820 µH → **0,728 A** |
| `I_rms,pri = I_pk·√(D/3)` | Primer rms akımı | 0,728·√(0,431/3) = **0,276 A** |
| `N_p = L_m·I_pk/(B_maks·A_e)` | Primer sarım sayısı | 820 µH, 0,3 T, 30 mm² → **66** |
| `V_DS = V_DC,maks + V_sn` | MOSFET gerilimi | 374,8 + 150 = **524,8 V** |
| `P_sn = ½·L_lk·I_pk²·f_s·V_sn/(V_sn − V_RO)` | Clamp kaybı | 12,3 µH, V_sn = 2·V_RO → **0,42 W** |
| `V_o = V_ref·(1 + R1/R2) + I_ref·R1` | TL431 bölücü | 38,3 k, 10 k → **12,05 V** |
| `P = V²/R` | Bleeder, start-up direnci kaybı | 230 V, 2 MΩ → **26,5 mW** |

---

## 1. Şebekeden küçük bir DC nasıl üretilir?

230 V şebekeyi bir **şelale** düşün; 5 V'luk küçük bir bardağı doldurmak istiyorsun:
- **Dirençli düşürücü:** bardağı şelalenin altına tutup fazlasını **boşa dökmek**. 20 mA için ≈ 10 W ısı: fiilen kullanılmaz.
- **Kapasitif düşürücü:** şelaleye bir **kısma vanası** takmak. Akım kısılır ama bardak hâlâ şelaleye bağlıdır: **izolasyon yok**.
- **İzolasyonsuz anahtarlamalı (off-line buck):** suyu **küçük kovalarla** taşımak. Verimli, ama yine şelaleye bağlı.
- **Flyback:** kovaları **duvarın üzerinden** aktarmak. Verimli ve duvarın öbür tarafındaki bardak şelaleden **ayrı** (izolasyon).

| Yöntem | İzolasyon | Verim (tipik) | Güç aralığı (tipik) | Artı | Eksi |
|---|---|---|---|---|---|
| Dirençli düşürücü | Yok | ≈ %1 (20 mA, 5,1 V için ≈ 10 W ısı) | ≤ 100 mW | En ucuz | Isı |
| **Kapasitif düşürücü** | **Yok** | %13–28 (bölüm 2.6) | ≈ 20–30 mA | Çok ucuz, küçük, EMI az | İzolasyon yok; akım hat ve C'ye bağlı; ısı |
| 50 Hz trafo + doğrultucu | Var | Düşük–orta | W'lar | Basit, sağlam | Büyük, ağır, pahalı |
| İzolasyonsuz buck (şebekeden) | Yok | Yüksek (IC verisine bak) | Onlarca–yüzlerce mA | Küçük, verimli | İzolasyon yok; kısa devre ve kaçak yönetimi |
| **Flyback** | **Var** | %80–90 (örnekte hedef %85) | Birkaç W – birkaç on W | Tek trafoyla izolasyon, geniş giriş | Trafo, EMI, clamp, geri besleme |
| Hazır AC-DC modül / adaptör | Var (sertifikalı) | Üreticiye göre | W'lar | Sertifika ve EMC hazır | Birim maliyet, hacim, esneklik yok |

**Karar soruları (bu sırayla):**
1. **Kullanıcı bir parçaya dokunabilir mi?** (bağlayıcı, düğme, USB, metal gövde, anten, kablo) Evet → izolasyon şart: flyback ya da hazır modül/adaptör.
2. **Ne kadar akım/güç?** ≤ ≈ 20 mA ve gövde tamamen kapalı/yalıtkan → kapasitif düşürücü düşünülebilir (laboratuvarla birlikte). Yüzlerce mA ve izolasyonsuz kabul → off-line buck. W'lar → flyback.
3. **Bekleme ve verimlilik düzenlemesi var mı?** Dış güç kaynağı satıyorsan evet (bölüm 9).
4. **Hacim ve sertifikasyon bütçesi?** Düşük hacimde hazır sertifikalı modül çoğu zaman en ucuz yoldur; kendi flyback'in ürün onayı, hi-pot, EMC ve trafo tedarik zinciri maliyeti taşır.

## 2. Kapasitif düşürücü

### 2.1 Nasıl çalışır?

Kapasitör, bir **akım musluğudur**: gerilimi değil **akımı** kısar. Kapasitörden geçen akım yalnızca gerilimin değişim hızına bağlıdır; arkasına 5 V ya da 12 V yükü bağlaman fark etmez, yaklaşık aynı akım akar. Yük bu akımdan azını çekerse fazlası **Zener'e** gider ve çıkış gerilimi sabit kalır. AN954'ün ifadesi: çıkış akımı giriş akımından **küçük ya da eşit** olduğu sürece yük gerilimi sabit kalır.

```
X_C = 1 / (2π·f·C)        I_rms = V_hat / X_C = V_hat · 2π·f·C
470 nF, 50 Hz: X_C = 6,77 kΩ       230 V → I_rms = 34,0 mA
```

Aynı 470 nF, 120 V / 60 Hz'de 21,3 mA verir: AN954'ün R1 güç hesabındaki akım budur (metin V, f ve C'yi yazmaz; 21,3 mA bu değerlerle uyuşur). 230 V / 50 Hz'de akım **1,6×**, R1'deki ısı **2,6×** fazladır: Amerikan uygulama notundaki parça değerleri doğrudan taşınmaz.

### 2.2 Yarım dalga ve köprü

Kapasitör akımı bir **sinüs**tür. Yarım dalga devrede (seri diyot + Zener) akımın yalnız bir yönü yüke gider; öbür yönde Zener ileri yönde iletir ve akım boşa gider. **Köprü** her iki yönü de yüke verir.

- **Yük dengesi (charge balance):** kapasitör her çevrimde gerilimini `2·V_tepe` kadar salar; bunun `V_on` kadarı kenetleme gerilimine gider, kalan yük yüke geçer. Köprüde çevrim başına iki kez yük taşınır: `I_ort = 4·f·C·(V_tepe − V_on)`. Yarım dalgada bir kez: `I_ort = f·C·(2·V_tepe − V_Z − 1,4 V)`. Köprü **ortalama akımda 2×** verir.
- **İdeal sınır** (`V_on → 0`): `4·f·C·V_tepe = 0,9 · I_rms = 30,6 mA`. Gerçek değer 30,0 mA'dir.
- **AN954 ile ilişki:** AN954 yarım dalga devre için `I_IN = V_HF,rms/(X_C1 + R1)` ve `V_HF,rms = (√2·V_rms − V_Z)/2` kullanır; bu, yarım dalga gerilimin **rms** değeridir. Metin köprü için "akım **141%** artırılabilir" der (*increased by 141%*); bunu **rms** büyüklüklerde √2 oranı olarak okuyorum (yorum: metin bunu açıkça yazmaz). Yüke giden **ortalama** DC akımda köprü yarım dalganın **2 katıdır** (30,0 mA'ye karşı 15,1 mA). İki ifade çelişmez; farklı büyüklükleri anlatır.
- **Çapraz kontrol:** AN954 Örnek 2 (120 V, 60,1 Hz, 0,56 µF, V_Z = 5 V, R1 = 423 Ω) formülle **15,99 mA** verir (kaynakta 16,0 mA). Örnek 1'i metindeki 110 V ile hesaplayınca 9,96 mA çıkar (kaynakta 10,4 mA); 115 V ile 10,42 mA çıkar: kaynakta küçük bir tutarsızlık var, formülün kendisi Örnek 2 ile doğrulanıyor.

### 2.3 Çalışılmış örnek: 230 V / 50 Hz, 470 nF, Zener 5,1 V

```
  köprülü kapasitif düşürücü (230 V / 50 Hz)
                                              ┌─────────┐
L ────[F1]───[R1 100 Ω]──┬──[C1 470 nF X2]─┬──┤ ~    +  ├─────┬─────┬─────► +5,1 V
                         │                 │  │  KÖPRÜ  │  [Cout] [D_Z]
                         └─[R_b 2×470 kΩ]──┘  │         │     │     │
N ────────────────────────────────────────────┤ ~    −  ├─────┴─────┴─────► GND
                                              └─────────┘
  R1 = 100 Ω gösterildi; 470 Ω seçeneği bölüm 2.4'te karşılaştırılıyor.
```

R1 ile köprüdeki iki diyot ve Zener `V_on = 5,1 + 1,4 = 6,5 V` düşürür. Zaman simülasyonu (R1 = 470 Ω ve 100 Ω) ile analitik formül:

| Devre | Analitik `I_ort` | Simülasyon | Kapasitör `I_rms` |
|---|---|---|---|
| Yarım dalga | 15,13 mA | 15,10–15,13 mA | 33,8–33,9 mA |
| **Köprü** | **29,96 mA** | 29,89–29,96 mA | 33,8–33,9 mA |

Kapasitörün rms akımı (yani R1'in gördüğü akım) devre türünden bağımsız ≈ **34 mA**'dır; yüke giden DC kısım ise devreye bağlıdır.

### 2.4 R1, Zener ve C1

R1 iki işi birden yapar: **açılış akımını sınırlar** ve **ısınır**. Bu iki ihtiyaç zıttır.

| R1 | Açılış tepe akımı `(V_tepe − V_on)/R1` | Sürekli ısı (nominal) | En kötü hat (253 V, C +%20) | Yorum |
|---|---|---|---|---|
| 470 Ω | 0,68 A | **0,54 W** | **0,94 W** | ½ W direnç **yetmez**; ≥ 2 W, ya da R1'i küçült |
| 100 Ω | 3,19 A | 0,12 W | 0,20 W | 1 W, **darbeye dayanıklı** (pulse-withstanding) tip; köprünün `I_FSM` ve Zener'in `I_ZSM` değeri ≈ 3 A'i karşılamalı |

- **Açılış darbesi:** gerilimin tepesinde bağlanırsan (en kötü faz) kapasitör boştur; R1'de `½·C·(V_tepe − V_on)² =` **23,9 mJ** ısınır. **R1'den bağımsızdır** (R1 yalnız tepe akımı ve süreyi belirler). Direncin darbe enerjisi (datasheet'te darbe eğrisi) bunu karşılamalıdır.
- **AN954'ün sayısı:** `(21,3 mA)² · (470 Ω·1,1 = 517 Ω) = 0,23 W`, "iki katı 0,46 W, ½ W yeterli" (21,3 mA, 120 V · 2π·60 Hz · 0,47 µF ile uyuşur). 230 V / 50 Hz'de aynı hesap `(34,0 mA)² · 517 Ω = 0,60 W` verir: ½ W **yetmez**.
- **Zener:** yük akımı 0'a düşünce Zener bütün ortalama akımı yutar: en kötü hatta `5,1 V · 39,6 mA = 0,20 W` (bölüm 2.5). 1 W'lık Zener seç.
- **C1 X2 olmalıdır** (hat–nötr arası bağlı; arızada kısa devre, sigorta atar: Ders 1, bölüm 7). Toleransı ±%10, yaşlanmayla kapasite kaybı olur; AN954 en kötü durum için **±%20** kullanır.

### 2.5 En kötü durum

Hat ±%10 (207…253 V; bu dersin tercihi), C ±%20 (AN954 gibi):

| Durum | `I_rms` (C) | `I_ort` (köprü) | P_R1 (470 Ω) | P_R1 (100 Ω) | Zener (yük yokken) |
|---|---|---|---|---|---|
| 207 V, C −%20 (376 nF) | 24,5 mA | **21,5 mA** | 0,28 W | 0,06 W | 110 mW |
| 230 V, nominal | 34,0 mA | 30,0 mA | 0,54 W | 0,12 W | 153 mW |
| 253 V, C +%20 (564 nF) | 44,8 mA | 39,6 mA | **0,94 W** | 0,20 W | **202 mW** |

**Kural:** yük akımını **en düşük** `I_ort`'a göre sınırla: 21,5 mA, %10 marjla ≈ **19 mA**. Nominal 30 mA'e göre tasarlarsan düşük hatta/yaşlanmış kapasitörde çıkış çöker (kontrolcü reset atar).

### 2.6 Boşaltma ve verim

Fişi çektiğinde C1 tepeye yakın (≈ 319 V) şarjlı kalabilir ve bu gerilim fiş pinlerinde durur. C1'e paralel **boşaltma direnci** `R_b` gerekir (Ders 1, bölüm 7.1: 373 V → 42,4 V ≤ 1 s, `τ ≤ 0,46 s`):

- `R_b ≤ τ/C1 = 0,46 s / 470 nF =` **0,98 MΩ** → 2 × 470 kΩ: `τ = 0,44 s`, 42,4 V'a **0,96 s**'de iner.
- Sürekli kayıp: `230² / 0,94 MΩ =` **56 mW** (264 V'ta 74 mW). Çıkış gücü 102 mW (20 mA, 5,1 V) olduğundan **boşaltma direnci çıkışın yarısından fazlasını** yer.

Verim örneği (20 mA yük, 5,1 V, nominal):

| Kalem | R1 = 470 Ω | R1 = 100 Ω |
|---|---|---|
| Çıkış | 102 mW | 102 mW |
| Zener (fazla akım) | 50 mW | 51 mW |
| Köprü diyotları | 42 mW | 42 mW |
| R1 | 536 mW | 115 mW |
| Boşaltma direnci | 56 mW | 56 mW |
| **Giriş (toplam)** | **786 mW** | **366 mW** |
| **Verim** | **%13** | **%28** |

### 2.7 Ne zaman kullanılır, ne zaman kullanılmaz?

| Kullanılabilir | Kullanılmaz |
|---|---|
| Gövde **tamamen kapalı ve yalıtkan**; dokunulabilir iletken parça yok | Bağlayıcı, düğme, USB, metal parça, anten, dışarı çıkan kablo |
| Küçük, **sabit** yük (MCU + küçük sensör + LED gösterge), ≤ ≈ 20 mA | Röle, buzzer, motor gibi darbeli veya değişken yük (akım sabittir; çekilen artarsa gerilim çöker) |
| Maliyet/hacim kritik, bekleme gücü düzenlemesi yok | Hassas ADC/analog ölçüm (çıkış gürültülü), bekleme/verim düzenlemesine tabi ürün |
| Laboratuvar onayı alınmış tasarım | Programlama/test portu olan, çocuğun erişebildiği ürün |

AN954 de açıktır: devre **şebekeden izole değildir**; denemelerde **izolasyon trafosu** kullan ve ürünler **sertifikalı laboratuvarda** test edilmelidir. Köprülü devrede çıkış hat/nötre göre referanssızdır; bu **güvenli** demek değildir: kart kapasitörle şebekeye bağlıdır ve topraklı bir kişi çıkış düğümüne dokunursa ≈ 34 mA'e kadar akım geçebilir. Ders 1'deki Class II dokunma akımı sınırı 0,25 mA'dir: **≈ 136 kat** fazla. İki telli dimmerin "güç hırsızlığı" beslemesi aynı fikrin ürünüdür ([Ders 2, bölüm 4.3](../triyak-ve-faz-kontrolu/ozet.md)).

## 3. Flyback nasıl çalışır?

**Yay benzetmesi:** MOSFET iletimdeyken primer akımı artar ve çekirdek enerji depolar: **yay sıkışır**. MOSFET açılınca akım aniden kesilemez; trafo polaritesini çevirir, sekonder diyot iletir ve enerji çıkışa boşalır: **yay açılır**. Flyback "trafosu" aslında bir **bağlı indüktördür**: önce depolar, sonra aktarır. Bu yüzden çekirdekte **hava aralığı (gap)** vardır; enerji gap'te saklanır. Bir ileri (forward) trafo gibi eş zamanlı iletmez.

### 3.1 Çalışma evreleri

```
 I_p  (primer)  ▁▁▂▂▃▄▄▅▆▆▇▇█                 ▁▁▂▂▃▄▄▅▆▆▇▇█
 I_s  (sekonder)             ██▇▆▆▆▅▄▄▄▃▂▂▂▁▁              ██▇▆▆▆▅▄▄▄▃▂▂▂▁▁
 V_DS (drain)   ▁▁▁▁▁▁▁▁▁▁▁▁▁████████████████▅▁▁▁▁▁▁▁▁▁▁▁▁▁████████████████▅
                |----t_on----|----t_demag----d|----t_on----|----t_demag----d

 düşük hat (90 V), tam yük · 1 karakter ≈ 0,5 µs · 2 çevrim gösterildi
 t_on = 6,6 µs · t_demag = 8,0 µs · d (ölü zaman) ≈ 0,8 µs · T = 15,4 µs (65 kHz)
 ▁ = MOSFET iletimde (V_DS ≈ 0)      █ = diyot iletimde (V_DS = V_DC + V_RO)
 ▅ = ölü zaman (V_DS, V_DC çevresinde zil yapar)
```

- `t_on`: MOSFET iletimde, sekonder diyot kapalı. `I_pk = V_DC·t_on/L_m`.
- `t_demag`: MOSFET kapalı, diyot iletimde. Drain gerilimi `V_DC + V_RO`; sekonder akım tepeden sıfıra iner: `t_demag = L_m·I_pk/V_RO`.
- **Ölü zaman:** akım sıfır; drain gerilimi `L_m` ve `C_oss` ile çınlar (DCM).
- DCM'de her çevrimde tepe enerji `½·L_m·I_pk²` aktarılır: **`P = ½·L_m·I_pk²·f_s`**. Güç yalnız `I_pk` ve `f_s`'e bağlıdır; hat değişince `t_on` değişir, `I_pk` sabit kalır.

### 3.2 Çalışma modları

| Mod | Tanım | Artı | Eksi |
|---|---|---|---|
| **DCM** (kesintili) | Akım her çevrimde sıfıra iner | Diyot sıfır akımda kapanır (ters toparlanma kaybı yok); kontrol kolay (RHPZ çok yüksek) | Büyük `I_pk` ve rms; çıkış kapasitörü ripple akımı büyük |
| **BCM / QR** (sınır, vadi anahtarlama) | Akım sıfıra inince (ya da vadide) yeniden açar | Düşük anahtarlama kaybı, yayılmış EMI | Frekans yük ve hatla değişir; hafif yükte burst |
| **CCM** (sürekli) | Akım sıfıra inmez | Düşük `I_pk` ve rms; yüksek güçte verimli | Diyot ters toparlanma kaybı; **RHPZ** kararlılığı zorlaştırır |

Bu derste örnek **DCM**'dir.

### 3.3 Blok şeması

```
  BİRİNCİL (şebeke potansiyeli)                         İKİNCİL (SELV)
───────────────────────────────────────────────────┬──────────────────────────────────────────────
                                                   │
      ┌──────┐  ┌──────┐  ┌─────┐  ┌──────┐        │
AC───►┤F1 NTC├─►┤X2 CMC├─►┤KÖPRÜ├─►┤C_bulk│        │
      └──────┘  └──────┘  └─────┘  └──┬───┘        │
                                +V_DC │     T1     │
                                      │    ┌───────┼───────┐   ┌─────┐   ┌───────┐
                                      └────┤       │       ├──►┤Diyot├──►┤Co + LC├────► +12 V
      ┌──────┐        ┌─────────┐          │Np (66)│Ns (11)│   └─────┘   └───┬───┘
      │PWM IC├───────►┤MOSFET Rs├────────◄─┤       │       ├───────────GND   │
      └───┬──┘        └─────────┘          └───────┼───────┘                 │
          ▲                                        │        ┌───────┐        │
          └─────────────────────────────────────[opto]──────┤ TL431 ├────────┘
                                                   │        └───────┘
───────────────────────────────────────────────────┴──────────────────────────────────────────────
  T1 + opto + Y1 (şemada yok) güçlendirilmiş yalıtım bariyerini oluşturur (Ders 1)
  Şemada yok: clamp (RCD), aux sargı + VCC, gate direnci, OVP ve ayrıntılı EMI filtresi.
```

| Eleman | Görevi | Nereye bak |
|---|---|---|
| F1, NTC, MOV | Koruma, açılış akımı | Ders 1, bölüm 6 |
| X2 + CMC + Y1 | EMI filtresi, bariyer köprüsü | Ders 1, bölüm 7–8 |
| Köprü + C_bulk | Doğrultma, enerji deposu | Bölüm 4.2 |
| **T1** | Enerji deposu **ve** izolasyon bariyeri | Bölüm 4.5 |
| MOSFET + R_s | Anahtar + akım algılama | Bölüm 4.6 |
| Clamp (RCD, şemada yok) | Kaçak indüktans enerjisini yutar | Bölüm 5 |
| Diyot + Co + LC | Doğrultma, filtre | Bölüm 4.7 |
| TL431 + opto | Çıkışı ölç, bariyerin ötesine ilet | Bölüm 6 |
| PWM IC + aux sargı | Darbe genişliği, koruma, VCC | Bölüm 7 |

## 4. Tasarım adımları: 12 V / 1 A, 85–265 VAC

### 4.1 Girdiler

| Girdi | Değer | Not |
|---|---|---|
| Çıkış | 12 V, 1 A → `P_out = 12 W` | |
| Giriş | 85–265 VAC, 50 Hz (evrensel) | `V_DC,maks = √2·265 = 374,8 V` |
| Verim hedefi | `η = 0,85` | AN-4137: yüksek çıkış gerilimlerinde 0,8–0,85 |
| Giriş gücü | `P_in = 12/0,85 = 14,12 W` | |
| Anahtarlama frekansı | `f_s = 65 kHz` | |
| Mod | DCM, tepe akım modu | |
| MOSFET | 650 V sınıfı | AN-4137: D_maks 0,45–0,5 (650 V) |

### 4.2 Bulk kapasitör ve `V_DC,min`

AN-4137: bulk kapasitör için **85–265 V girişte 2–3 µF/W** → 28–42 µF; **47 µF** (3,3 µF/W) seçildi. Kapasitör yalnız hat tepelerinde şarj olur (hat periyodunun ≈ %20'si, `D_ch`); aradaki sürede `P_in`'i tek başına verir ve gerilimi düşer. Enerji dengesinden:

```
½·C·(V_tepe² − V_DC,min²) = P_in · (1 − D_ch) / (2·f_L)
V_DC,min = √( 2·V_hat² − P_in·(1 − D_ch) / (C·f_L) )      (V_tepe² = 2·V_hat²)
```

| Durum (85 VAC, `P_in` = 14,12 W) | Formül (D_ch = 0,2) | İdeal simülasyon (D_ch) |
|---|---|---|
| C = 47 µF (nominal) | **98,2 V** | 98,4 V (0,20) |
| C = 37,6 µF (−%20) | **91,9 V** | 93,1 V (0,23) |

Simülasyon seri direnci ve diyot düşümünü içermez; gerçek değer biraz daha düşüktür. **Tasarım değeri: `V_DC,min = 90 V`.** Formül ve simülasyon birbirini tutuyor (D_ch ≈ 0,2).

### 4.3 Sarım oranı, `V_RO` ve görev oranı

```
V_RO = n·(V_o + V_F)           (V_F = 0,5 V Schottky)
D    = V_RO / (V_DC,min + V_RO)
```

AN-4137: `D_maks` 0,45–0,5. `D = 0,45` hedefiyle `V_RO = 0,45/0,55 · 90 = 73,6 V` → `n = 73,6/12,5 = 5,9` → **n = 6**, `V_RO = 6 · 12,5 =` **75 V**, `D = 75/(90 + 75) =` **0,4545**.

`n`'i neden büyütmüyoruz? Karşılaştır (aynı `V_DC,min`, `P_in`, `f_s`; her `n` için DCM sınırı):

| n | V_RO | D | L_m,maks | I_pk | I_sec,pk | V_DS (sıçramasız) | Diyot V_D |
|---|---|---|---|---|---|---|---|
| 5 | 62,5 V | 0,410 | 741 µH | 0,766 A | 3,83 A | 437,3 V | 87,0 V |
| **6** | **75,0 V** | **0,455** | **912 µH** | **0,690 A** | **4,14 A** | **449,8 V** | **74,5 V** |
| 7 | 87,5 V | 0,493 | 1072 µH | 0,637 A | 4,46 A | 462,3 V | 65,5 V |

`I_pk` ve `I_sec,pk` sütunları `L_m = L_m,maks` (DCM sınırı) içindir; seçilen `L_m = 820 µH`'ta `I_pk = 0,728 A` olur (bölüm 4.4).

`n` büyüdükçe diyot gerilimi düşer, ama MOSFET gerilimi ve `D` artar (`n = 7`'de D = 0,49 sınıra dayanır). `n = 6` dengeli bir orta noktadır.

### 4.4 `L_m` ve akımlar

DCM sınırı (`K_RF = 1`): `L_m,maks = (V_DC,min·D)² / (2·P_in·f_s) = (90·0,4545)²/(2·14,12·65 kHz) =` **912 µH**. `L_m` toleransı (±%10) yüzünden sınırın **altında** bir değer seç: **820 µH** (+%10 = 902 µH < 912 µH, DCM korunur).

```
I_pk = √( 2·P_in / (L_m·f_s) ) = √(2·14,12 / (820 µH · 65 kHz)) = 0,728 A
E    = ½·L_m·I_pk² = 217 µJ    →   E·f_s = 14,12 W  ✔
```

| Hat | t_on | D | t_demag | Ölü zaman | I_pri,rms |
|---|---|---|---|---|---|
| 90 V (düşük) | 6,63 µs | 0,431 | 7,96 µs | %5,2 | 0,276 A |
| 374,8 V (yüksek) | 1,59 µs | 0,104 | 7,96 µs | %37,9 | 0,135 A |

Sekonder: `I_sec,pk = n·I_pk =` **4,37 A**; `I_sec,rms = I_sec,pk·√(D₂/3) =` **1,81 A** (`D₂ = t_demag/T = 0,517`); çıkış kapasitörü akımı `I_cap,rms = √(I_sec,rms² − I_o²) =` **1,51 A**. Gerilimler: `V_DS` (sıçramasız) `= 374,8 + 75 =` **449,8 V** (%69, 650 V).

### 4.5 Trafo

Çekirdek verisi **varsayımdır** (`A_e = 30 mm²`, `B_maks = 0,3 T`); kendi çekirdeğinin datasheet'iyle yeniden hesapla.

| Büyüklük | Formül | Sonuç |
|---|---|---|
| Primer sarım | `N_p = L_m·I_pk/(B_maks·A_e)` | 66,3 → **66** |
| Sekonder sarım | `N_s = N_p/n` | **11** |
| Yardımcı (VCC ≈ 15 V) | `N_aux = N_s·(V_aux + V_F)/(V_o + V_F)` | 13,8 → **14** |
| `A_L` | `L_m/N_p²` | **188 nH/N²** |
| Gerçek tepe akı | `B_pk = L_m·I_pk/(N_p·A_e)` | 0,301 T |
| Hava aralığı | `l_g = μ₀·N_p²·A_e/L_m` | ≈ **0,20 mm** (saçak akı ve çekirdek relüktansı ihmal) |
| Primer tel | `J = 4 A/mm²` → 0,069 mm² | ≈ ⌀ 0,30 mm |
| Sekonder tel | 0,45 mm² | ≈ ⌀ 0,76 mm; ten derinliği 65 kHz'de 0,26 mm: **paralel ince teller** ya da TIW |

**Trafo çizimi bir güvenlik belgesidir.** Üreticiye verilecek şartnamede şunlar yazılı olmalı:
- `L_m` (±%), `L_lk` üst sınırı (**%1,5·L_m ≈ 12 µH**; ADI: tipik %1–2), sarım oranı, doyma akımı **> OCP eşiği** (`1,2·I_pk = 0,87 A`; ADI) ve `B_maks`.
- **Sandviç (interleaved) sarım:** primerin yarısı – sekonder – primerin yarısı; `L_lk` düşer, clamp kaybı azalır.
- Primer–sekonder **güçlendirilmiş yalıtım**: TIW (üç kat yalıtımlı tel) ya da **margin bant**, bobin pimleri arası kriper/klirens, vernik; test gerilimi **3000 Vac** (Ders 1, bölüm 4–5).
- Yalıtım sınıfı (ısı), sıcaklık yükselmesi, hi-pot ve `L_m`/`L_lk` ölçüm koşulları (kısa devre sekonderle `L_lk`).
- Enerji: 217 µJ + marj; çekirdek **seçim tablosu**ndan doğrula.

### 4.6 MOSFET

- `V_DSS ≥ V_DS,tepe/0,9` (AN-4137: `V_ds,maks ≤ %90·BV_DSS`). 525 V → 583 V ⇒ **650 V** parça (%81).
- `I_rms = 0,276 A`: iletim kaybı küçüktür (`R_ds(on),sıcak = 3 Ω` varsayımıyla 0,23 W). Asıl kayıp **C_oss** enerjisidir: `½·C_oss·V²·f_s`, örneğin 40 pF (varsayım), 450 V, 65 kHz için ≈ **0,26 W** (vadide açan QR bunu azaltır).
- Gate: seri direnç (EMI ↔ kayıp dengesi) ve **gate–source pull-down** (yüzen gate yok): [MOSFET dersi](../mosfet-transistor-ve-yuk-surme/ozet.md).
- Akım algılama `R_s = V_CS/I_LIM` (`V_CS` IC'nin eşiği), `I_LIM = 1,2·I_pk = 0,87 A`.

### 4.7 Çıkış

- **Diyot:** `V_D = V_o + V_DC,maks·(V_o + V_F)/V_RO = 12 + 374,8·12,5/75 =` **74,5 V**. AN-4137: `V_RRM > 1,3·V_D = 96,8 V`; ADI: `1,25·(K·V_DC,maks + V_o) = 93 V`. **100 V** parça bu ölçütü (96,8 V) ancak geçer; diyot üzerindeki zil için marj dardır: **120–150 V** sınıfı ya da diyot RC snubber'ı değerlendir. `I_F > 1,5·I_D,rms =` **2,7 A**; `t_rr < 50 ns` (ADI): Schottky uygundur.
- **Co:** `ΔV = I_o·(1 − D₂)/(C_o·f_s) + I_sec,pk·ESR`. **2 × 470 µF** düşük ESR (eşdeğer 15 mΩ): `7,9 mV + 4,37 A·15 mΩ =` **≈ 73 mV**. ESR belirleyicidir. Her kapasitör ≈ **0,76 A** ripple akımı taşır: 105 °C ripple akımı anma değerini en sıcak noktada kontrol et.
- **LC son filtre:** 2,2 µH + 100 µF → `f_c = 10,7 kHz ≈ f_s/6` (AN-4137: `f_s/10 … f_s/5`); `f_s`'te teorik ≈ −31 dB. Gerçek sıçrama parazitiklerle sınırlıdır. Geri besleme noktasını filtre **öncesinden** almak döngüyü basit tutar (LC'nin faz gecikmesi girmez), ama bobin DCR'sindeki düşüm düzenlenmez; filtre sonrasından alırsan `f_c`'yi döngü çapraz frekansının çok üstünde tut.

### 4.8 Kayıp bütçesi

`η = %85` hedefi `P_in − P_out =` **2,12 W** kayıp demektir. Bunu önceden dağıt:

| Kalem | Kayıp | Varsayım |
|---|---|---|
| Çıkış diyotu | 0,50 W | `V_F·I_o = 0,5 V·1 A` |
| Clamp | 0,42 W | Bölüm 5 |
| MOSFET iletim | 0,23 W | `R_ds(on),sıcak = 3 Ω` |
| Çıkış C ESR | 0,03 W | `1,51² · 15 mΩ` |
| **Toplam (bunlar)** | **≈ 1,19 W** | |
| **Kalan** | **≈ 0,93 W** | `C_oss` (≤ 0,26 W, 40 pF varsayımı), trafo (bakır + çekirdek), köprü (≈ 0,2–0,3 W, tahmin), start-up, IC |

Kalan 0,93 W'ın bu kalemlere yetmesi gerekir; yetmiyorsa ilk bakılacak yerler **diyot** (senkron doğrultma, Schottky `V_F`) ve **clamp**'tir.

## 5. Clamp (RCD)

Trafonun **kaçak indüktansı** `L_lk` sekondere bağlanmaz. MOSFET kapanınca bu indüktanstaki akım gidecek yer bulamaz ve drain'de **sıçrama** oluşturur. Clamp, bu enerjiyi bir **tahliye kanalı** gibi toplar: `E = ½·L_lk·I_pk²`. Örnekte `L_lk = %1,5·L_m = 12,3 µH`: çevrim başına **3,26 µJ**, saniyede **0,212 W**. Clamp'in kenetlediği gerilim `V_sn` ise bu enerjinin gerçek kaybını belirler: `V_sn`, `V_RO`'ya ne kadar yakınsa clamp diyodu o kadar uzun iletir ve **ana enerjiden de çalar** (AN-4147):

```
P_sn = ½·L_lk·I_pk²·f_s · V_sn / (V_sn − V_RO)
R_sn = V_sn² / P_sn          C_sn = V_sn / (ΔV_sn·R_sn·f_s)      (ΔV_sn ≈ %5–10·V_sn)
V_sn = 2–2,5 × V_RO          (AN-4147)
```

```
 V_sn/V_RO   V_sn      clamp kaybı P_sn                 V_DS (650 V'a göre)
 1,5×        112,5 V   ██████████████████ 0,64 W    ███████████████░░░░░  %75,0
 2,0×        150,0 V   ████████████       0,42 W    ████████████████░░░░  %80,7
 2,5×        187,5 V   ██████████         0,35 W    █████████████████░░░  %86,5

 1 karakter ≈ 0,035 W (kayıp) ve %5 (V_DS). Sonuç: V_sn, V_RO'ya yaklaştıkça kayıp artar, V_DS azalır.
```

- **V_sn = 2·V_RO = 150 V:** `P_sn =` **0,42 W**, `R_sn = 150²/0,424 =` **53 kΩ** (2–3 seri direnç: gerilim ve güç bölüşülür; güç marjı ≥ 2×), `C_sn = 150/(15 V·53 kΩ·65 kHz) =` **2,9 nF** → 4,7 nF/630 V. Clamp diyodu **ultra hızlı**, `V_RRM ≥ V_DSS`.
- **V_DS kontrolü:** AN-4147: geçici ≤ %90, sürekli ≤ %80 `BV_DSS`. `V_sn = 2,0×` seçimde `V_DS = 524,8 V = %80,7`: sürekli öneriyi biraz aşar, geçici sınırın altındadır. Marj için `V_sn = 1,8×` (135 V → %78,4, kayıp 0,48 W) ya da daha yüksek `V_DSS` seç.
- **AN-4147 çapraz kontrol:** `V_sn = 150 V`, `V_RO = 75 V`, `L_lk = 150 µH`, `I_pk = 0,4 A`, `f_s = 67 kHz` → betikle **1,61 W, 14,0 kΩ, 10,7 nF** (kaynakta ≈ 1,6 W, ≈ 14 kΩ, ≈ 10 nF).
- **ADI:** `V_DSNUB = V_IN,maks + 2,5·V_OUT/K`, `P_SNUB = 0,833·L_LK·I_PRIPEAK²·F_SW`; **0,833 = ½ × 1,667** (V_sn = 2,5×V_RO durumu, yukarıdaki son satır).
- Alternatif: **TVS + ultra hızlı diyot** (sabit V_sn, enerji TVS'de ısı) ya da aktif clamp (verimli, karmaşık).
- `L_lk`'yı ölç (sekonder kısa devre iken primerden); şartnamedeki sınırı aşan trafoyu kabul etme.

## 6. Geri besleme: TL431 + opto

Çıkıştaki bir **bekçi**: TL431 çıkışı kendi hassas referansıyla karşılaştırır; fark, opto LED akımını değiştirir. Opto bu bilgiyi **ışıkla** bariyerin ötesine, primerdeki PWM IC'nin FB girişine taşır; IC darbeyi daraltır ya da genişletir.

### 6.1 TL431 (TI datasheet, C sıcaklık sınıfı, `T_A` = 25 °C)

| Parametre | Standart | A sınıfı | B sınıfı |
|---|---|---|---|
| `V_ref` (min/tip/maks) | 2,440 / 2,495 / 2,550 V | 2,470 / 2,495 / 2,520 V | 2,483 / 2,495 / 2,507 V |
| `I_min` (tip/maks) | 0,4 / 1 mA | 0,4 / 0,6 mA | 0,4 / 0,6 mA |
| `I_ref` (tip/maks) | 2 / 4 µA | aynı | aynı |
| `\|Z_KA\|` | 0,2 / 0,5 Ω | aynı | aynı |
| `V_KA` aralığı | `V_ref` … 36 V (mutlak maks. 37 V) | | |
| Sürekli katot akımı | 1–100 mA önerilen | | |

A/B sınıfı parçalarda I ve Q sıcaklık sınıflarının `I_min` üst sınırı **0,7 mA**'dir; `V_ref` sıcaklık kayması da ayrıca eklenir. **Kendi parçanın** sınıfını datasheet'ten oku.

### 6.2 Bölücü ve doğruluk

```
V_o = V_ref · (1 + R1/R2) + I_ref · R1          R1 = R2·(V_o/V_ref − 1) = 38,1 kΩ  →  E96: 38,3 kΩ
V_o = 2,495 · (1 + 38,3k/10k) = 12,05 V
```

| Durum | V_ref | Dirençler | I_ref | V_o |
|---|---|---|---|---|
| Üst | 2,507 V (B maks.) | R1 +%1, R2 −%1 | 4 µA (R1'de 0,15 V) | **12,46 V (+%3,8)** |
| Nominal | 2,495 V | nominal | — | 12,05 V |
| Alt | 2,483 V (B min.) | R1 −%1, R2 +%1 | ≈ 0 | **11,80 V (−%1,6)** |

`I_ref·R1` (≈ 0,15 V, %1,3) yüksek değerli bölücülerde **ihmal edilemez**. Tablo 25 °C içindir; sıcaklık kayması ayrıca eklenir. Daha dar tolerans için %0,1 direnç ya da bölücü akımını yükselt (bölücü akımı `12 V/48,3 kΩ = 0,248 mA`, **3 mW**).

### 6.3 Opto akım hattı

- TL431 **`I_min`** akım olmadan regüle etmez: standartta **≥ 1 mA**. Opto LED'ine **paralel `R_bias`** koy: `R_bias = V_F/1 mA = 1,1 V/1 mA ≈ 1 kΩ` (`I_bias = 1,1 mA`).
- Gereken opto akımı: kontrolcünün FB pini en çok **`I_C,maks = 1 mA`** çeksin (varsayım), `CTR_min = %50` (yaşlanma dahil varsayımı) → `I_F,maks = 1 mA/0,5 = 2 mA`.
- Seri direnç: `R_led,maks = (V_o − V_F − V_KA,min)/(I_F,maks + I_bias) = (12 − 1,1 − 2,5)/3,1 mA = 2,71 kΩ` → **2,2 kΩ**. Doyumda `I_R = 3,8 mA`; boşta `V_KA = 8,5 V`.
- **Bekleme maliyeti:** `12 V · 1,1 mA = 13,2 mW`. A/B sınıfı (C sıcaklık sınıfı) `I_min ≤ 0,6 mA` olduğundan `R_bias = 1,8 kΩ` (`I_bias` = 0,61 mA) → **≈ 7 mW** (≈ 6 mW kazanç). Bekleme gücü kritikse düşük `I_min`'li referans ve düşük akımlı opto dizilimi ara.
- **CTR yaşlanır** (sıcaklık, akım, süre) ve parçadan parçaya geniş yayılır: kararlılığı **CTR_min ve CTR_maks** ile test et; CTR_min'de regülasyon, CTR_maks'ta kararlılık bozulabilir.
- Opto bariyerin parçasıdır: yalıtım gerilimi ve **kriper/klirens** (Ders 1, Ders 2'deki MOC notları gibi) kontrol edilir.

### 6.4 Çevre ve kararlılık

- **DCM + tepe akım modu:** güç katı kabaca **tek baskın kutuplu** davranır (yük ve `C_o` ile yer değiştirir) ve ESR sıfırı vardır; telafi kolaydır.
- **CCM'de RHPZ** (sağ yarı düzlem sıfırı): `ω_RHPZ = R_L·(1 − D)²/[D·L_m·(N_s/N_p)²]` (AN-4137). Sınır tasarımı için (R_L = 12 Ω, D = 0,4545, L_m = 912 µH): **≈ 49 kHz** → `f_c < f_RHPZ/3 ≈ 16 kHz` ve **faz payı ≥ 45°** (AN-4137). Pratikte `f_c` birkaç kHz seçilir; opto kutbu (kolektör direnci büyüdükçe düşer) `f_c`'yi ayrıca sınırlar.
- **Test:** hat (85/230/265 V) × yük (%10–100) × **CTR_min/CTR_maks** için kazanç–faz ölçümü (enjeksiyon direnciyle) ve **yük adımı** (%10 ↔ %90). Düşük hat, tam yük (CCM'e en yakın) en kötü durumdur.
- **Alternatif — birincil taraf regülasyonu (PSR):** çıkış gerilimi aux sargıdan dolaylı ölçülür; **opto ve TL431 yok** (maliyet, bekleme gücü, güvenilirlik); karşılığında regülasyon daha gevşektir ve kablo/yük düşümü telafisi gerekir.

## 7. Kontrol IC, start-up ve korumalar

| Seçenek | Ne | Ne zaman |
|---|---|---|
| Anahtar entegre (off-line switcher) | MOSFET IC'nin içinde | Düşük güç; az parça, hızlı tasarım |
| Kontrolcü + harici MOSFET | Tepe akım modu PWM IC | Güç/verim/ısı esnekliği |
| QR/vadi anahtarlama | Frekans değişir, vadide açar | Verim ve EMI; hafif yük burst |
| PSR | Opto yok | Maliyet/bekleme gücü kritik, gevşek regülasyon kabul |

**Start-up.** IC'nin çalışması için VCC'ye ihtiyaç vardır; ilk enerjiyi bulk'tan alırsın:
- **Dirençli start-up:** `V_DC²/R`: 2 MΩ → **52,8 mW** (325 V) / 69,6 mW (373 V), **sürekli**. Bekleme bütçesini ilk bu bozar.
- **HV pin (IC içindeki akım kaynağı):** start-up sonrası kapanır → sürekli kayıp çok küçüktür (IC verisine bak).
- **Aux sargı:** çalışırken VCC'yi verir: `V_aux = 14/11·(12 + 0,5) − 0,7 = 15,2 V` (15 V hedefi).

**Korumalar:**

| Koruma | Nasıl | Hedef |
|---|---|---|
| **OCP** (cycle-by-cycle) | `R_s` gerilimi eşiği aşınca darbeyi keser; **LEB** (leading-edge blanking) açılış sıçramasını yok sayar | `I_LIM = 1,2·I_pk = 0,87 A`; **trafo doymaz** |
| **OVP** | Aux sargı ya da ikincil Zener/TVS | Geri besleme koparsa çıkışı sınırlar |
| **Kısa devre / aşırı yük** | Hiccup (kesik çalışma, yeniden deneme) | Ortalama giriş gücü düşük kalır |
| **OTP** | IC veya NTC | Isıl kaçak |
| **Brown-out** | Hat UVLO | Düşük hatta yarım çalışma yok |
| **Soft-start** | `I_pk` rampası | Açılış taşması, trafo doyması |
| **VCC UVLO / OVP** | IC içinde | Belirsiz sürüş yok |

**Fail-safe düşüncesi (arıza modları):**

| Arıza | Ne olur | Savunma |
|---|---|---|
| TL431/opto **açık devre** | FB pini yukarı çekilir → **maksimum güç** → çıkış yükselir | **OVP şart** (aux sargı veya ikincil) |
| Opto **kısa devre** | FB pini aşağı → darbe durur, çıkış düşer | Hiccup yeniden dener |
| Çıkış kısa devre | `I_pk` sınırda, VCC düşer | Hiccup, aşırı ısınma önlenir |
| Clamp diyodu açık devre | Drain sıçraması MOSFET'i patlatır | Marj (`V_DSS`), ömür testi |
| Bulk kapasitör açık devre | Kenarda gürültü, yüksek I_pk | Sigorta, kontrol |

## 8. Giriş katı

Şebeke girişi sırasıyla: sigorta (F1) → varistör (MOV) → X2 → ortak mod bobini (CMC) → X2 → NTC → köprü → bulk ([Ders 1, bölüm 6–7](../sebeke-guvenligi-ve-yalitim/ozet.md)). Bu ders için sayılar:

- **Bulk enerjisi:** `½·C·V² = ½·47 µF·374,8² =` **3,30 J**. NTC 10 Ω (soğuk) ile ilk tepe `374,8/10 = 37,5 A`: sigortanın `I²t`'si ve köprünün `I_FSM`'i buna göre seçilir (Ders 1, bölüm 6.3).
- **Köprü:** `V_RRM ≥ 600 V` (tepe 375 V ×1,6).
- **Bulk gerilimi:** 400 V parça 374,8 V'ta **%93,7** yüklenir (marj ince); **450 V** → %83,3.
- **X2 deşarjı:** 220 nF için `R_b ≤ 0,46 s/220 nF = 2,09 MΩ` → 2 × 1 MΩ: `τ = 0,44 s`, 42,4 V'a 0,96 s; sürekli kayıp **26,5 mW** (230 V) / 34,8 mW (264 V). Bekleme bütçesinde yer alır (bölüm 9).
- **Y1 (primer–sekonder):** 2,2 nF için 264 V'ta `I = 2π·f·C·V` = 0,18 mA (50 Hz) / 0,22 mA (60 Hz): Class II sınırı 0,25 mA, **diğer Y kapasitörlerle toplanır** (Ders 1, bölüm 8).
- **Köprü + bulk akımı darbelidir**: güç faktörü düşük (≈ 0,5–0,6, tipik). Güç büyüdükçe harmonik sınırları (EN 61000-3-2 gibi) PFC gerektirebilir; kapsam ve eşikler ürün sınıfına göre değişir, standardı kontrol et.

## 9. Bekleme gücü ve verimlilik

| Düzenleme | Kapsam | ≤ 49 W AC-DC | 49–250 W | Not |
|---|---|---|---|---|
| **DOE VI** (ABD, Şubat 2016) | Dış güç kaynakları | **≤ 0,100 W** | ≤ 0,210 W | Çok çıkışlı: ≤ 0,300 W |
| **AB 2019/1782** (1 Nisan 2020) | Dış güç kaynakları | **≤ 0,10 W** | ≤ 0,21 W | |
| CoC Tier 2 (gönüllü) | Dış güç kaynakları | ≤ 0,075 W | — | Diğer güç aralıkları bu notta doğrulanmadı |

Bu sınırlar **dış güç kaynakları** (adaptör) içindir. Ürünün içine gömülü besleme için ürün ailesine özel kurallar vardır: hangi yönetmeliğin geçerli olduğunu ürün grubuna göre kontrol et.

**Bekleme bütçesi (230 V, yüksüz):** hedef 100 mW'ın altında kalmak için her kalem hesaplanır. `V²/R` satırları hesaplanmıştır; diğerleri **varsayımdır**.

| Kalem | Naif tasarım | Optimize tasarım | Not |
|---|---|---|---|
| X2 deşarj direnci (220 nF) | 26,5 mW | ≤ 1 mW | `230²/2 MΩ`; aktif deşarj (varsayım) |
| Start-up | 52,8 mW | ≤ 1 mW | `325²/2 MΩ`; HV pin (varsayım) |
| Geri besleme zinciri | 16,2 mW | ≈ 10 mW | naif: 13,2 (bias, 1,1 mA) + 3,0 (bölücü); optimize: 7,3 (bias, A/B sınıfı) + 3,0 |
| IC + VCC | 15 mW | 10 mW | varsayım |
| Burst anahtarlama, trafo, clamp | 15 mW | 15 mW | varsayım |
| **Toplam** | **≈ 125 mW** | **≈ 37 mW** | Limit: 100 mW |

**Mesaj:** naif tasarım limiti **aşar**; ilk iki kalem (79 mW) tek başına bütçenin %79'unu yer. Bekleme gücü sonradan düzeltilebilen bir ayar değil, **mimari bir karardır**: HV start-up, aktif X-cap deşarjı ve düşük akımlı geri besleme baştan seçilir.

Yüksüz ölçüm için mW çözünürlüklü **güç analizörü** ve uzun ortalama süresi gerekir; ölçüm yöntemi için standart (IEC 62301) ücretlidir ve bu notlarda yoktur.

## 10. 💼 İş yerinde

Şebekeli bir ürün başlarken **aynı sırayla** sor: (1) kullanıcı bir yere dokunabilir mi? (2) akım/güç bütçesi? (3) izolasyon ve ürün standardı? (4) bekleme/verim hedefi? (5) ortam sıcaklığı ve ömür? (6) maliyet ve hacim?

| Ürün tipi | Tipik besleme yolu | İlk sorular |
|---|---|---|
| Sensörlü LED lamba, hareket/varlık sensörü (şebekeli) | Kapasitif düşürücü, izolasyonsuz buck, küçük flyback ya da hazır modül | Tüm devre şebekede mi? Dokunulabilir iletken, bağlayıcı, programlama portu var mı? Akım bütçesi (MCU + sensör + radyo) ≤ 20 mA mı? Bekleme gücü hedefi? |
| Dimmer (iki telli) | Yükten "güç hırsızlığı" ([Ders 2, bölüm 4.3](../triyak-ve-faz-kontrolu/ozet.md)) | En küçük yük, hayalet parlama, elektronik şebeke potansiyelinde |
| İnterkom, kapı paneli | Genelde SELV adaptör (12–24 V); kartta DC-DC | **Adaptör seçimi:** sertifika, ripple, hold-up, bekleme gücü, kısa devre davranışı |
| Gaz dedektörü (şebekeli sürüm) | İzolasyonlu flyback + LC son filtre | Köprü beslemesi ve referans besleme gürültüsüne duyarlı; **brown-out ve güç kaybı alarmı** |

**Flyback kartı ilk açılış sırası:**
1. İzolasyon trafosu ve **seri ampul** (Ders 1, bölüm 14.2); önce **yük yok**.
2. Düşük gerilimden başla (ayarlanabilir kaynakla): start-up, VCC, çıkış gerilimi ve OVP.
3. 85 V ve 265 V'ta start-up, sonra yük adımı; **primer akımı ve V_DS** osiloskopta (clamp sıçraması).
4. Kısa devre (hiccup) ve geri besleme koparma (OVP) testi: **yük bağlıyken değil**, ölçülü ve korumalı.
5. Isıl (1 saat, kapalı kasa), sonra EMI ön-testi, hi-pot, bekleme gücü.

> Bu iş yeri tablosu genel örnektir; şirketin gerçek ürün şemaları ve değerleri bu notlara girmez.

## 11. Şematikte

- **Kapasitif düşürücü:** "⚠ Tüm devre şebeke potansiyelinde" uyarısı; `I_ort,min`, `P_R1`, Zener gücü ve açılış darbesi hesabı not; C1 (X2) ve `R_b`.
- **Flyback:** şebeke bölgesini kutuyla ayır; bariyeri (T1, opto, Y1) işaretle; `V_DC,min/maks`, `V_RO`, `L_m`, `I_pk`, `V_sn` değerlerini şematik notuna yaz.
- Trafo pin numarası ve **nokta (polarite)**: primer/sekonder/aux ters bağlanırsa devre çalışmaz ya da yanar.
- **TL431 bölücü ve opto akımı** (`R_bias`, `R_led`, `I_min`) hesabı notla.
- OCP (`R_s`, LEB), OVP yolu ve start-up (HV pin ya da direnç) açıkça çizilsin.
- Her elemana gerilim anma değeri ve sınıf: X2, Y1, MOV, 450 V bulk, 650 V MOSFET, clamp diyodu `V_RRM`.

## 12. PCB / layout

- **Primer anahtarlama döngüsü:** C_bulk(+) → T1 primer → MOSFET → `R_s` → C_bulk(−). Alanı **küçük** tut; en yüksek `dI/dt` burada.
- **Sekonder döngüsü:** T1 sekonder → diyot → Co → T1; kısa ve geniş.
- **Clamp döngüsü:** MOSFET drain düğümüne yakın ve kısa; **drain düğümü en küçük bakır** (yüksek `dV/dt`, EMI anteni).
- **Y1** bariyerin **üstünde**, kısa izle; X2 girişte; CMC'nin altında/yakınında bakır yok (EMC 02).
- **Bariyer:** primer–sekonder arası kriper/klirens ([Ders 1, bölüm 4.4–5](../sebeke-guvenligi-ve-yalitim/ozet.md)); opto ve trafo altında bakır ve **yarık**; trafo pinleri arasındaki kriperi ölç.
- **Kontrol IC referansı:** `R_s`'nin GND ucuna yıldız bağla; FB, CS ve VCC hassas izlerini drain düğümünden uzak tut.
- **TL431 ve opto yakın;** `V_ref` pini yüksek empedanslıdır, izi kısa tut.
- **Isı:** MOSFET, diyot, clamp direnci, NTC ve trafo ısıtıcıdır; **elektrolitik kapasitörleri bunlardan uzak** yerleştir (ömür sıcaklıkla üstel düşer).
- Genel kurallar: [PCB yerleşim ve iz çizimi](../pcb-yerlesim-ve-iz-cizimi/ozet.md).

## 13. EMC açısından

Flyback'in gürültü kaynakları: drain'in **yüksek `dV/dt`**'si, primer ve sekonder **`dI/dt` döngüleri**, diyot toparlanması ve `L_lk`–`C_oss` **zili**.

- **Çözümler:** X2 + CMC + Y1; clamp'te sönümleme; **frekans jitter'ı** ya da QR; trafo içinde **kalkan (shield) sargısı**; döngü alanını küçültme; gerekirse sekonder çıkışına LC.
- **Y1 ve kaçak akım:** Y1 gürültüyü bariyerin üstünden geri döndürür; kaçak akımla ödünleşir (bölüm 8).
- **Kapasitif düşürücü** anahtarlamaz; EMI'si düşüktür, ama köprü diyotları ve X2 yine EMC testine girer.
- Ön-test: yakın alan probu, **LISN**, filtreli/filtresiz karşılaştırma. Standartlar ürün ailesine göre (ör. EN 55032, EN 55015); ücretlidir, [EMC dersleri](../../EMC/03-emc-testleri-ve-standartlar/ozet.md) yöntemi anlatır.
- Devre notu: [EMC 02 bölüm 5 (anahtarlamalı kaynak gürültüsü)](../../EMC/02-emc-icin-kart-tasarimi/ozet.md).

## 14. Ölçüm ve doğrulama

| Ölçüm | Nasıl | Beklenen |
|---|---|---|
| **V_DC dibi** | Bulk üstünde, 85 VAC, tam yük | ≥ 90 V (hesap 92–98 V) |
| **Start-up süresi** | 85 ve 265 VAC | Çıkış monoton yükselir, aşım yok |
| **Hat/yük regülasyonu** | 85–265 V × %0, 10, 50, 100 yük | Çıkış toleransı içinde (bölüm 6.2: −%1,6 … +%3,8) |
| **Çıkış dalgalanması** | 20 MHz bant sınırı, **kısa toprak yayıyla (tip-and-barrel) prob**, kısa toprak | ≈ 73 mV (LC ile çok daha az); uzun toprak klipsi sıçramayı **şişirir** |
| **V_DS tepe** | Diferansiyel yüksek gerilim probu, izolasyonlu | ≤ %90·V_DSS (650 V → 585 V) |
| **Primer akımı** | `R_s` üzerinde | `I_pk ≈ 0,73 A`; OCP 0,87 A |
| **Yük adımı / kararlılık** | %10 ↔ %90 adım; kazanç–faz ölçümü | Aşım küçük; faz payı ≥ 45°; CTR_min/CTR_maks'ta |
| **Kısa devre, aşırı yük** | Hiccup davranışı | Yeniden dener, ısınmaz |
| **Geri besleme koparma** | Opto veya TL431'i yok say | OVP devreye girer |
| **Verim ve bekleme** | %25/50/75/100 yük, ve yüksüz mW | Hedef tutar (bölüm 4.8, 9) |
| **Isıl** | 1 saat, kapalı kasa, yüksek ortam; trafo, MOSFET, diyot, elektrolitik | Anma değerleri altında |
| **Hi-pot** | Primer–sekonder **3000 Vac**, 1 dk (DC testte ×1,414) | Atlama yok, kaçak sınır altında |
| **Hat bozulmaları** | Brown-out, kesinti, hızlı hat değişimi | Güvenli kapanma ve geri gelme |

Şebeke güvenliği için Ders 1'deki ölçüm kurallarının **tümü** geçerlidir: izolasyon trafosu, seri ampul, diferansiyel prob, tek el, deşarj kontrolü. Dropper kartında **her düğüm şebeke potansiyelindedir**: prob toprağını karta bağlama.

## 15. Sık yapılan hatalar

| Hata | Neden sorun | Doğrusu |
|---|---|---|
| Dropper'ı dokunulabilir ürüne koymak | ≈ 34 mA tehlikeli, izolasyon yok | İzolasyonlu flyback ya da sertifikalı modül |
| R1 = 470 Ω / ½ W'ı 230 V'ta kullanmak | 0,54–0,94 W ısı | ≥ 2 W ya da R1 küçük + darbeye dayanıklı |
| Yükü nominal akıma göre belirlemek | Düşük hat/yaşlı C'de çıkış çöker | `I_ort,min`'e göre (≈ 19 mA) |
| Zener'in boştaki ısısını unutmak | 0,20 W; ½ W Zener ısınır | 1 W Zener, ısı hesabı |
| X2 yerine sıradan film kapasitör | Arızada yangın | Sertifikalı X2 |
| C1'e boşaltma direnci koymamak | Fişte ≈ 319 V kalır | `R_b ≤ τ/C1` |
| Küçük bulk, `V_DC,min`'i hesaplamamak | `I_pk`, `D` artar, regülasyon kaybı | 2–3 µF/W, C −%20 ile hesap |
| `L_m`'yi DCM sınırında seçmek | Tolerans CCM'e iter, `I_pk` ve kararlılık değişir | Sınırın ≈ %10 altı |
| `V_sn`'yi `V_RO`'ya yakın seçmek | Clamp kaybı artar (1,5×'te 0,64 W; 2×'te 0,42 W) | `V_sn = 2–2,5×V_RO` |
| Trafoda doyma payı yok | `I_pk` fırlar, MOSFET yanar | Doyma akımı > OCP eşiği; `B_maks` marjı |
| TL431 `I_min`'in altında çalıştırmak | Regülasyon kaybı, çıkış yükselir | `R_bias` ile ≥ 1 mA |
| CTR yaşlanmasını hesaba katmamak | Yıllar sonra çıkış düşer/salınır | `CTR_min` ile tasarla, CTR_maks'ta test et |
| OVP yok, geri besleme açık devre | Çıkış kontrolsüz yükselir | Aux/ikincil OVP |
| Start-up direncini sürekli bırakmak | 52,8 mW bekleme | HV pin |
| Çıkış ripple'ını uzun toprak klipsiyle ölçmek | Sahte sıçrama | Tip-and-barrel prob |
| Trafo primer–sekonder kriperini ölçmemek | Pimler arası kriper yetmez | Bobin ve pin aralığı, margin bant |
| İlk açılışı doğrudan şebekeden yapmak | Hatada parça yanar | Seri ampul + izolasyon trafosu (Ders 1) |

## 16. Terimler sözlüğü

| Terim | Anlamı |
|---|---|
| **Kapasitif düşürücü** | Şebekeye seri kapasitörle akımı sınırlayan izolasyonsuz besleme |
| **X2 / Y1** | Hat–nötr / bariyer köprüleyen sertifikalı kapasitör sınıfları |
| **V_on** | Kenetleme gerilimi: `V_Z` + diyot düşümleri |
| **Flyback** | Enerjiyi önce trafoda depolayıp sonra aktaran izolasyonlu dönüştürücü |
| **DCM / BCM / QR / CCM** | Kesintili / sınır / yarı rezonanslı (vadi) / sürekli iletim |
| **L_m, L_lk** | Mıknatıslanma ve kaçak indüktans |
| **V_RO** | Sekonder geriliminin primere yansıması: `n·(V_o + V_F)` |
| **n** | Sarım oranı `N_p/N_s` |
| **D, D_max** | Görev oranı ve sınırı |
| **I_pk** | Primer tepe akımı |
| **V_DC,min / V_DC,maks** | Bulk kapasitör geriliminin dibi / tepesi |
| **D_ch** | Bulk'ın şarj olduğu hat periyodu oranı (≈ 0,2) |
| **Clamp / RCD snubber** | Kaçak indüktans enerjisini yutan R–C–D devresi |
| **V_sn** | Clamp'in kenetlediği gerilim |
| **TL431** | Ayarlanabilir hassas shunt referans/hata yükselticisi |
| **CTR** | Opto akım transfer oranı (`I_C/I_F`) |
| **PSR** | Birincil taraf regülasyonu (opto yok) |
| **Hiccup** | Arızada kesik çalışma/yeniden deneme |
| **Burst modu** | Hafif yükte darbe grupları, bekleme gücünü düşürür |
| **LEB** | Akım algılamada açılış sıçramasını yok sayma |
| **RHPZ** | Sağ yarı düzlem sıfırı (CCM) |
| **TIW** | Üç kat yalıtımlı tel |
| **SELV** | Çok düşük güvenlik gerilimi (güvenli, yalıtımlı çıkış) |
| **EPS** | Dış güç kaynağı (adaptör) |

---

## Şematik kontrol listesine eklenenler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (bölüm 14):

- [x] Kapasitif düşürücü yalnızca dokunulabilir iletken parçası olmayan, tamamen kapalı ve yalıtkan gövdeli üründe kullanıldı (şematikte "⚠ tüm devre şebeke potansiyelinde" notu; bağlayıcı, düğme, anten, programlama portu yok); aksi hâlde flyback ya da sertifikalı modül seçildi
- [x] Kapasitif düşürücünün yük akımı en düşük ortalama akıma göre sınırlandı (207 V, C −%20: 4·f·C·(V_tepe − V_on)) ve %10 marj bırakıldı; Zener gücü (V_Z·I_ort,maks) ve R1 gücü (I_rms²·R1, en kötü hat ve C) hesaplandı
- [x] Dropper C1 X2 sınıfı; paralel boşaltma direnci R_b ≤ τ/C ile seçildi ve sürekli kaybı hesaplandı; R1'in açılış darbesi (tepe akım (V_tepe − V_on)/R1, enerji ½·C·(V_tepe − V_on)²) direnç, köprü (I_FSM) ve Zener için karşılandı
- [x] Flyback girişi: P_in = P_out/η, bulk 2–3 µF/W; V_DC,min en kötü durumda (düşük hat, C −%20, tam yük) hesaplandı ve şematik notuna yazıldı; V_DC,maks = √2·V_hat,maks ile bulk ve köprü gerilim marjı kontrol edildi
- [x] Flyback sarım oranı: V_RO = n·(V_o + V_F), D_maks ≤ 0,45–0,5; L_m DCM sınırının ≈ %10 altında seçildi (L_m toleransı dahil); I_pk, OCP eşiği (≈ 1,2·I_pk) ve trafo doyma akımı (> OCP eşiği) hesaplandı
- [x] MOSFET V_DSS ≥ (V_DC,maks + V_sn)/0,9 (sürekli ≤ %80 önerisi de kontrol edildi); çıkış diyodu V_RRM > 1,3·V_D ve I_F > 1,5·I_D,rms; çıkış kapasitörünün ripple akımı ve ESR'si hesaplandı
- [x] RCD clamp: V_sn = 2–2,5·V_RO, P_sn = ½·L_lk·I_pk²·f_s·V_sn/(V_sn − V_RO), R_sn gücü (≥ 2× marj), C_sn ve ultra hızlı clamp diyodu (V_RRM ≥ V_DSS) hesaplandı; L_lk trafo şartnamesinde üst sınırla belirtildi ve ölçüldü
- [x] Trafo çizimi güvenlik belgesi olarak tamamlandı: L_m (±%), L_lk üst sınırı, doyma akımı, sarım sayıları, pin numarası ve nokta (polarite), güçlendirilmiş yalıtım (TIW/margin bant, 3000 Vac, kriper/klirens); bariyer (T1, opto, Y1) şematikte işaretli
- [x] Geri besleme: TL431 bölücüsünün toleransı (V_ref, I_ref·R1, direnç) hesaplandı; katot akımı ≥ I_min (R_bias); opto akımı CTR_min ve yaşlanmayla boyutlandı; kararlılık CTR_min/CTR_maks, hat ve yük uçlarında ölçülecek; geri besleme yolu açık devre olursa çıkışı sınırlayan OVP (aux sargı ya da ikincil) var
- [x] Korumalar ve bekleme: OCP (LEB dahil), hiccup, OTP, brown-out ve soft-start davranışı tanımlı; X2 deşarj ve start-up kayıpları dahil yüksüz giriş gücü bütçesi çıkarıldı (dış güç kaynağında ≤ 0,100 W; ürün grubuna göre yönetmeliği kontrol et)

## Kontrol soruları

→ [quiz.md](quiz.md) · 12 soru, 9'u hesap
