# Kaynaklar · Aliasing ve anti-aliasing filtresi

| Tür | Kaynak | Bölüm / Dakika | Not |
|---|---|---|---|
| PDF / App note | [MT-002: What the Nyquist Criterion Means to Your Sampled Data System Design – Analog Devices](https://www.analog.com/media/en/training-seminars/tutorials/MT-002.pdf) | Tamamı | **Ana kaynak** (Walt Kester). Nyquist kriteri, temel bant anti-aliasing filtresi, undersampling |
| Kitap (ücretsiz) | [The Scientist and Engineer's Guide to DSP – Steven W. Smith](https://www.dspguide.com/ch3.htm) | Bölüm 3 (ADC and DAC) | Örnekleme teoremi ve anti-alias filtre seçimi; sezgisel anlatım |
| Web (üretici) | [ADC measurements recommendations – ST Wiki](https://wiki.st.com/stm32mcu/wiki/ADC_measurements_recommendations) | DC ölçüm, post-processing | STM32'de ortalama, filtreleme ve kaynak empedansı (R_AIN) önerileri |
| PDF / App note | AN2834 (ST) – STM32'de ADC doğruluğunu artırma | Dış etkenler, ortalama | Gürültü kaynakları ve donanım/yazılım önlemleri. st.com'da "AN2834" diye arat |
| Web | [IEC 61000-4-3 özeti – ATEC](https://atecorp.com/compliance-standards/iec/iec-61000-4-3) · [IEC 61000-4-6 özeti – ATEC](https://www.atecorp.com/compliance-standards/iec/iec-61000-4-6) | Test sinyali | RF bağışıklık testlerinde %80 AM, 1 kHz modülasyon |
| Datasheet | Kullandığın MCU/ADC | "ADC characteristics", "I/O characteristics" | Örnekleme süresi, R_AIN, kaçak akım (I_lkg). **Son söz datasheet'indir** |
