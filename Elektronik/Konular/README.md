# Elektronik Konuları

Birden fazla komponenti birleştiren **uygulama konuları** (ör. decoupling, sinyal koşullandırma). Tek bir komponentin temelleri için [Komponentler](../Komponentler/README.md), EMC için [EMC](../EMC/README.md) klasörüne bak.

Her konu bir klasör:

| Dosya | İçerik |
|---|---|
| `ozet.md` | Can alıcı bilgiler: kavram, formül, pratik kural, sık hata |
| `quiz.md` | Kontrol soruları (hesap soruları dahil) |
| `kaynaklar.md` | Hangi video / kitap / PDF'in hangi bölümünden |

Yeni konu:

```powershell
.\scriptler\Yeni-Kayit.ps1 -Tur Konu -Baslik "Gaz sensörü türleri"
```

## Önerilen çalışma sırası

| # | Konu | Neden bu sırada |
|---|---|---|
| 1 | [Şematik çizim ve dokümantasyon](sematik-cizim-ve-dokumantasyon/ozet.md) | Her tasarımın belgesi; review ve üretim bunu okur |
| 2 | [Güç ve decoupling](guc-ve-decoupling/ozet.md) | Her IC'nin temeli; hataların çoğu burada başlar |
| 3 | [Güç katı: koruma ve regülatör seçimi](guc-kati-koruma-ve-regulator/ozet.md) | Kartın girişi: sigorta, ters polarite, TVS, LDO/buck, güç bütçesi |
| 4 | [MOSFET, transistör ve yük sürme](mosfet-transistor-ve-yuk-surme/ozet.md) | Röle, buzzer, LED, kapı otomatiği; açılışta güvenli durum |
| 5 | [Op-amp ve sensör ön ucu](op-amp-ve-sensor-on-ucu/ozet.md) | Sensörden ADC'ye: köprü, kazanç, ofset, referans |
| 6 | [ADC ile ölçüm: pratik rehber](adc-ile-olcum/ozet.md) | İş başvuru kitabı: tablolar, hata bütçesi, giriş reçeteleri, testli C kodu |
| 7 | [Aliasing ve anti-aliasing filtresi](aliasing-ve-anti-aliasing-filtresi/ozet.md) | Örnekleme ve filtre; ölçüm zincirinin devamı |
| 8 | [Haberleşme arayüzleri](haberlesme-arayuzleri/ozet.md) | UART, RS-485, I²C, SPI'nin elektriksel tarafı |
| 9 | [PCB yerleşim ve iz çizimi](pcb-yerlesim-ve-iz-cizimi/ozet.md) | Şematiğin fiziksel karşılığı: yerleşim, iz, mesafe, toprak |
| 10 | [Üretilebilirlik ve test için tasarım](uretilebilirlik-ve-test/ozet.md) | Kartın üretilip test edilebilmesi; üretim paketi |
| 11 | [Şebeke güvenliği ve yalıtım](sebeke-guvenligi-ve-yalitim/ozet.md) | Şebekeli her kartın temeli: clearance/creepage, X/Y kapasitör, sigorta, PE, güvenli ölçüm |
| 12 | [Triyak ve faz kontrolü (dimmer)](triyak-ve-faz-kontrolu/ozet.md) | Şebekede güç ayarı: triyak, tetik devresi, sıfır geçiş, LED sorunları, testli C zamanlama modülü |
| 13 | [Şebekeli güç kaynakları](sebekeli-guc-kaynaklari/ozet.md) | Şebekeden küçük DC: kapasitif düşürücü (30 mA) ve izolasyonlu flyback; clamp, TL431 geri besleme, bekleme gücü |
| 14 | [Anahtarlamalı regülatör tasarımı](anahtarlamali-regulator-tasarimi/ozet.md) | Kart içi DC-DC: buck, boost ve ters buck-boost; `L` ve `C` seçimi, kayıp bütçesi, döngü kompanzasyonu, hot-plug, sıcak döngü yerleşimi |

Her dersin başında bir **okuma planı** var (genelde 3 oturum). Bir ders için önerilen akış:

1. Okuma planına göre `ozet.md`'yi oku; "Hızlı tekrar" bölümünü en sona tekrar oku.
2. `quiz.md`'yi cevap anahtarına bakmadan çöz; skoru tabloya yaz, zayıf konuyu not et.
3. Aşağıdaki **iş yerinde uygula** görevini yap.
4. [ilerleme.md](../../ilerleme.md) dosyasında durumu güncelle.

## İş yerinde uygula

Her ders için bir pratik görev. **Şirkete ait şematik, değer veya doküman bu repoya girmez**; notlarını genel hâlde yaz (ör. "röle sürme devresinde pull-down yoktu" gibi).

| Ders | Görev |
|---|---|
| Şematik çizim | Üzerinde çalıştığın bir kartın şematiğini kontrol listesi bölüm 1 ile incele. ERC'yi çalıştır ve uyarıları oku |
| Güç katı | Kartın güç bütçesi tablosunu çıkar; her LDO için `P = ΔV × I` ve sıcaklık hesabı yap |
| Yük sürme | Röle, buzzer ve kilit çıkışlarında gate/baz pull-down var mı bak; kartı defalarca aç-kapa, açılışta bir şey tıklıyor mu? |
| Op-amp ve sensör | Sensör ön ucunun her test noktasında beklenen gerilimi hesapla, sonra ölç ve karşılaştır |
| ADC ile ölçüm | Kartında bir ADC kanalına sabit gerilim ver, 1000 örnek al; σ'yı ve gürültüsüz bit sayısını hesapla. Bir pil veya besleme ölçümünün hata bütçesini çıkar |
| Haberleşme | RS-485 hattında osiloskopla A − B farkını ölç; boşta fark ≥ 200 mV mi, sonlandırma yalnızca uçlarda mı? |
| PCB yerleşim | Mevcut bir kartta güç izlerinin genişliğini tabloyla kontrol et; GND düzleminde yarık ve ısıtıcı/röle dönüş yollarını izle |
| Üretilebilirlik | Bir kartın üretim paketini dersteki tabloyla karşılaştır; eksik dosya veya revizyon karışıklığı var mı? |
| Şebeke güvenliği | Şebekeli bir kartın şematiğinde şebeke bölgesini işaretle; en yakın iki iletken arasındaki mesafeyi clearance/creepage tablosuyla karşılaştır; Y kapasitörün kaçak akımını `I = 2π·f·C·V` ile hesapla |
| Triyak ve faz kontrolü | Sıfır geçiş darbesini hat ile aynı ekranda ölç (izolasyon trafosu ve seri ampulle): genişlik ve merkez hesapla uyumlu mu? Snubber kaçağını hesapla, en küçük LED lambada kapalıyken hayalet parlama var mı bak |
| Şebekeli güç kaynakları | Sertifikalı bir adaptörün **çıkışında** (şebeke tarafına dokunmadan) dalgalanmayı kısa toprak yayıyla ölç; yükü %10–100 değiştirip `ΔV`'yi dersteki formülle karşılaştır. Bir flyback şemasında trafo, opto ve Y1'den oluşan bariyeri işaretle; `V_DC,min`, `I_pk` ve `P_sn` hesabını kendi örneğinle yap |
| Anahtarlamalı regülatör | Kartındaki bir buck ya da boost'ta çıkış dalgalanmasını ve SW düğümünü kısa toprak yayıyla ölç; `ΔI_L`, `I_Cin,rms` ve `I_MAXOUT`'u dersteki formüllerle hesaplayıp datasheet ile karşılaştır. Yük adımında (%10 ↔ %90) çıkış sapmasına bak; gerçek adaptör ve kabloyla `V_in` tepesini yakala |

Bulduğun her hatayı ve dersi [hatalar-dersler.md](../Sematik-Tasarim/hatalar-dersler.md) dosyasına, yeni kontrol maddelerini [kontrol-listesi.md](../Sematik-Tasarim/kontrol-listesi.md) dosyasına ekle.

## Sonraki konu adayları

| Konu | Neden |
|---|---|
| Gaz sensörü türleri (pellistor, MOS, NDIR, elektrokimyasal) | Hangi sensör nerede; ön uç ve kalibrasyon farkları |
| Ex (ATEX/IECEx) temelleri ve kendinden güvenlik | Patlayıcı ortam cihazlarında tasarım kuralları |
| Fonksiyonel güvenlik (SIL) temelleri | Güvenlik fonksiyonlarının arıza davranışı ve teşhisi |
| Gerilim referansları ve hassas ölçüm | Ölçüm doğruluğunun temeli |
| Termal tasarım | Isı hesabı, soğutma, sıcaklığa bağlı ömür |
| Düşük güç ve pil tasarımı | Pilli/taşınabilir cihazlar için |

> Her konu bittiğinde "Şematik kontrol listesine eklenenler" bölümünü [kontrol-listesi.md](../Sematik-Tasarim/kontrol-listesi.md) dosyasına işle.
