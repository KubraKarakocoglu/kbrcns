# Güç ve decoupling

- **Oluşturma:** 2026-10-12
- **İlk kaynak:** https://www.analog.com/media/en/training-seminars/tutorials/MT-101.pdf
- **Tüm kaynaklar:** [kaynaklar.md](kaynaklar.md)

> Birden fazla kaynaktan derlendi. Sayısal değerler **tipik başlangıç noktalarıdır**; tasarım değeri için her zaman kullandığın IC'nin datasheet'i esastır.

## Temel kavram

Dijital bir IC (ör. MCU) akımı sabit çekmez. Her saat kenarında transistörler anahtarlanır ve nanosaniyeler süren **akım darbeleri** oluşur.

Regülatör ile IC arasındaki iz ve bağlantıların **endüktansı** vardır. Akım hızla değiştiğinde bu endüktans üzerinde `V = L · di/dt` kadar gerilim düşer: besleme anlık olarak çöker (*droop*) ve gürültü oluşur. Regülatör de bu hıza yetişemez; kontrol döngüsü nanosaniyeler değil, mikrosaniyeler mertebesinde tepki verir.

**Decoupling kapasitörü**, IC'nin hemen yanındaki yerel enerji deposudur:
- Ani akımı regülatör yerine **o** karşılar.
- IC'nin ürettiği gürültünün besleme hattı üzerinden diğer devrelere yayılmasını azaltır. Adı da buradan gelir: IC'yi besleme ağından "ayırır".

**Benzetme:** Regülatör uzaktaki baraj, iz endüktansı ince ve uzun bir boru, decoupling kapasitörü evin çatısındaki su deposu. Musluğu aniden açtığında suyu baraj değil depo verir.

### Gerçek kapasitör ideal değildir

Gerçek bir kapasitör, seri bağlı üç elemandan oluşur: **C + ESR + ESL**.

```
|Z|
 │ \                         /
 │  \   kapasitif           /   endüktif
 │   \                     /
 │    \___________________/  ← en düşük empedans ≈ ESR
 └─────────────┬──────────────── frekans
              SRF (self-rezonans)
```

- **SRF altı:** Kapasitör gibi davranır, empedansı frekansla düşer.
- **SRF üstü:** **Endüktör gibi** davranır; artık decoupling yapmaz.
- ESL yalnızca paketin değil, **montajın** (pad, iz, via) toplamıdır. Bu yüzden yerleşim, değerden daha önemlidir.

Tek bir kapasitör tüm frekansları kapsayamaz. Bu yüzden iki katman kullanılır:

| Katman | Tipik | Görevi |
|---|---|---|
| **Bulk** | 4,7–100 µF (seramik, elektrolitik, polimer) | Düşük frekanslı, büyük akım değişimleri için yük deposu |
| **Yerel** | 100 nF seramik, her besleme pininde | Yüksek frekanslı akım darbeleri ve gürültü |

## Kritik formüller

| Formül | Ne zaman kullanılır | Dikkat |
|---|---|---|
| `V = L · di/dt` | Bağlantı endüktansının ani akımda yarattığı düşümü tahmin etmek | 10 nH ve 5 ns'de 100 mA değişim → **0,2 V**. Küçük L bile ciddi sorun yaratır |
| `C = I · Δt / ΔV` | Yerel kapasitörün bir akım darbesini ne kadar droop ile karşılayacağını bulmak | Nominal değil **efektif** C kullan (DC bias ve tolerans sonrası) |
| `f_SRF = 1 / (2π √(ESL · C))` | Kapasitörün etkili olduğu üst frekansı bulmak | 100 nF, 1 nH → ≈ **16 MHz**. Montaj endüktansı arttıkça SRF düşer |
| `Z_hedef = ΔV_izin / ΔI` | Güç dağıtım ağı (PDN) hedefi: ilgili frekanslarda besleme empedansı bunun altında kalmalı | 3,3 V, %3 tolerans, 0,5 A adım → 99 mV / 0,5 A ≈ **0,2 Ω** |

## Pratik kurallar (rule of thumb)

**Değer ve sayı**
- Her besleme pini çifti (VDD/GND) için bir **100 nF** seramik kapasitör (0402 veya 0603).
- Her güç rayında en az bir **bulk** kapasitör: regülatör çıkışında ve yük grubunun yakınında.
- **STM32F4 örneği (AN4488):** Her VDD çiftine 100 nF, rayda bir adet **en az 4,7 µF (tipik 10 µF)**. VDDA, VDD'ye ferrit boncuk üzerinden bağlanabilir. MCU'nun datasheet'inde ayrıca VCAP gibi özel pinler için istenen kapasitörler olabilir; mutlaka kontrol et.

**Yerleşim (değerden daha önemli)**
- Kapasitör **pine en yakın** konumda olmalı.
- Akım döngüsünün alanı **en küçük** olmalı: IC besleme pini → kapasitör → GND via → IC GND pini. Bu döngünün endüktansı, kapasitörün kendi ESL'inden büyük olabilir.
- GND bağlantısı **kısa ve doğrudan** toprak düzlemine gitmeli. Via'yı pad'in hemen yanına koy; ince ve uzun iz kullanma.

**Dielektrik seçimi**

| Dielektrik | Kullanım |
|---|---|
| **X7R / X5R** | Decoupling için standart |
| **C0G / NP0** | Küçük değerler (pF–nF) ve kararlılık gereken yerler: osilatör yük kapasitörü, filtre. DC bias etkisi yoktur |
| **Y5V / Z5U** | **Kullanma.** Sıcaklık ve gerilimle kapasitansın büyük kısmı kaybolur |

**DC bias etkisi**
- X5R/X7R kapasitörler uygulanan DC gerilimle **kapasite kaybeder**. C0G'de bu etki yoktur.
- Kayıp en büyük şu durumda olur: küçük paket + yüksek değer + çalışma gerilimi nominal gerilime yakın.
- Önlem: daha yüksek gerilim dereceli veya daha büyük paketli kapasitör seç. Efektif değeri üreticinin eğrisinden kontrol et (ör. Murata SimSurfing).

**Analog besleme (VDDA, referans)**
- Ferrit boncuk + kapasitör ile dijital gürültüden ayrılır.
- Boncuk **DC akımda doyabilir**; doyunca empedansı düşer ve filtre işe yaramaz. Akım derecesini kontrol et.
- Boncuk ve kapasitör bir LC devresi oluşturur; rezonans tepesi oluşmamalı. Prototipte ölçerek doğrula.

**İleri not: paralel farklı değerler**
- Büyük ve küçük değerli kapasitörleri paralel kullanmak yaygın bir yöntemdir.
- Ancak iki SRF arasında bir empedans tepesi (**anti-rezonans**) oluşabilir.
- Başlangıç seviyesinde datasheet önerisine uy. İleri seviyede empedans eğrisini simüle et.

**Tantal kapasitör**
- Klasik (MnO₂) tantalda yaygın öneri, çalışma gerilimini nominalin yaklaşık **yarısında** tutmaktır.
- Arıza modu kısa devre olabilir.
- Polimer tantalın derating ihtiyacı daha azdır. Her durumda üretici önerisine uy.

## Sık yapılan hatalar

- Şematikte doğru kapasitörü koyup layout'ta IC'den **uzağa** yerleştirmek. Şematik doğru görünür ama kapasitör işe yaramaz.
- Tüm 100 nF'leri tek bir köşede toplamak ("kapasitör bankası"). Her pinin kendi kapasitörü olmalı.
- Nominal değere güvenmek: 6,3 V'luk küçük paketli 10 µF X5R, 5 V rayda çok daha düşük efektif değer verir.
- Y5V/Z5U dielektrik kullanmak.
- Kapasitörün GND bağlantısını ince ve uzun bir izle yapmak.
- Ferrit boncuğu DC akım derecesine bakmadan seçmek.
- Yalnızca bulk ya da yalnızca 100 nF kullanmak. İkisi farklı frekans bantlarını kapsar, ikisi de gerekir.

## Şematik kontrol listesine eklenecekler

Aşağıdaki maddeler [kontrol-listesi.md](../../Sematik-Tasarim/kontrol-listesi.md) dosyasına işlendi (v1.1, bölüm 4):

- [x] Decoupling kapasitörlerinin dielektriği X7R/X5R (küçük değerlerde C0G); Y5V/Z5U yok
- [x] Layout notu: pin → kapasitör → GND via döngüsü minimum; via pad'e bitişik
- [x] Analog besleme ferrit boncuğu: DC akım derecesi yeterli, LC rezonansı değerlendirildi
- [x] Tantal kullanıldıysa gerilim derating üretici önerisine uygun

## Kontrol soruları

→ [quiz.md](quiz.md)
