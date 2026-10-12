#Requires -Version 5.1
<#
.SYNOPSIS
    Şablondan yeni bir C dersi, elektronik konusu, komponent dersi, EMC dersi veya
    proje klasörü oluşturur ve ilerleme.md tablosuna satır ekler.

.DESCRIPTION
    Ders      → C-Programlama/NN-baslik/          ozet.md, quiz.md, notlarim.md
    Konu      → Elektronik/Konular/baslik/        ozet.md, quiz.md, kaynaklar.md
    Komponent → Elektronik/Komponentler/NN-baslik/ ozet.md, quiz.md, kaynaklar.md
    EMC       → Elektronik/EMC/NN-baslik/          ozet.md, quiz.md, kaynaklar.md
    Proje     → Elektronik/Projeler/NN-baslik/    README.md (proje kartı), sematik-review.md

    Güvenlik:
      - Var olan hiçbir dosyanın üzerine yazılmaz.
      - Tüm şablonlar dosya oluşturulmadan ÖNCE doğrulanır.
      - Yazma sırasında hata olursa yeni oluşturulan klasör geri alınır.
      - Dosyalar BOM'suz UTF-8 yazılır (Windows PowerShell 5.1 ve 7 aynı sonucu üretir).

.PARAMETER Tur
    Ders | Konu | Komponent | EMC | Proje

.PARAMETER Baslik
    Kaydın başlığı (2-80 karakter). Klasör adı bundan üretilir (Türkçe karakterler sadeleştirilir).

.PARAMETER Link
    İsteğe bağlı kaynak linki (http veya https).

.EXAMPLE
    .\scriptler\Yeni-Kayit.ps1 -Tur Ders -Baslik "Değişkenler ve veri tipleri" -Link "https://cs50.harvard.edu/x/2026/weeks/1/"

.EXAMPLE
    .\scriptler\Yeni-Kayit.ps1 -Tur Konu -Baslik "Op-amp temelleri"

.EXAMPLE
    .\scriptler\Yeni-Kayit.ps1 -Tur Komponent -Baslik "MOSFET"

.EXAMPLE
    .\scriptler\Yeni-Kayit.ps1 -Tur EMC -Baslik "ESD koruması"

.EXAMPLE
    .\scriptler\Yeni-Kayit.ps1 -Tur Proje -Baslik "GPIO buton"

.NOTES
    Çıkış kodları: 0 başarılı | 1 hata (yeni klasör oluşturulmadı)
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [ValidateSet('Ders', 'Konu', 'Komponent', 'EMC', 'Proje')]
    [string]$Tur,

    [Parameter(Mandatory)]
    [ValidateLength(2, 80)]
    [string]$Baslik,

    [string]$Link
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$Utf8Bomsuz = New-Object System.Text.UTF8Encoding($false)
$BosDurum   = [string][char]0x2B1C   # ⬜ (kaynak kodda ASCII dışı karakter kullanmamak için)

function Read-Utf8  ([string]$Yol) { [System.IO.File]::ReadAllText($Yol, [System.Text.Encoding]::UTF8) }
function Write-Utf8 ([string]$Yol, [string]$Icerik) { [System.IO.File]::WriteAllText($Yol, $Icerik, $Utf8Bomsuz) }

function ConvertTo-Slug {
    param([string]$Metin)
    # ı (U+0131) ayrıştırılamadığı için elle; diğer aksanlar (ç ş ğ ü ö İ) FormD ile ayrılıp atılır.
    $s = $Metin.Replace([string][char]0x0131, 'i')
    $s = $s.Normalize([System.Text.NormalizationForm]::FormD)
    $s = [regex]::Replace($s, '\p{Mn}', '')
    $s = $s.ToLowerInvariant()
    $s = [regex]::Replace($s, '[^a-z0-9]+', '-').Trim('-')
    if ($s.Length -gt 50) { $s = $s.Substring(0, 50).TrimEnd('-') }
    return $s
}

function Get-SonrakiNo {
    param([string]$Dizin)
    $enBuyuk = 0
    if (Test-Path -LiteralPath $Dizin -PathType Container) {
        foreach ($klasor in @(Get-ChildItem -LiteralPath $Dizin -Directory)) {
            if ($klasor.Name -match '^(\d{2,3})-') {
                $n = [int]$Matches[1]
                if ($n -gt $enBuyuk) { $enBuyuk = $n }
            }
        }
    }
    if ($enBuyuk -ge 999) { throw 'Numara sınırına (999) ulaşıldı.' }
    return '{0:D2}' -f ($enBuyuk + 1)
}

function Add-IlerlemeSatiri {
    param([string]$RepoKoku, [string]$Isaret, [string]$Satir)
    $yol = Join-Path $RepoKoku 'ilerleme.md'
    if (-not (Test-Path -LiteralPath $yol -PathType Leaf)) {
        Write-Warning 'ilerleme.md bulunamadı; tablo güncellenmedi.'
        return
    }
    $icerik = Read-Utf8 $yol
    $konum  = $icerik.IndexOf($Isaret, [System.StringComparison]::Ordinal)
    if ($konum -lt 0) {
        Write-Warning "ilerleme.md içinde '$Isaret' işareti yok; tablo güncellenmedi."
        return
    }
    $satirSonu = if ($icerik.Contains("`r`n")) { "`r`n" } else { "`n" }
    Write-Utf8 $yol ($icerik.Substring(0, $konum) + $Satir + $satirSonu + $icerik.Substring($konum))
}

try {
    if (-not $PSScriptRoot) { throw 'Script dosya olarak çalıştırılmalı: .\scriptler\Yeni-Kayit.ps1' }
    $RepoKoku     = Split-Path -Path $PSScriptRoot -Parent
    $SablonDizini = Join-Path $RepoKoku 'sablonlar'

    # --- Girdi doğrulama ---------------------------------------------------------
    $Baslik = ($Baslik -replace '\s+', ' ').Trim()
    $slug   = ConvertTo-Slug $Baslik
    if ($slug.Length -lt 2) { throw "Başlıktan geçerli bir klasör adı üretilemedi: '$Baslik'" }

    if ($Link) {
        $uri = $null
        $gecerli = [System.Uri]::TryCreate($Link.Trim(), [System.UriKind]::Absolute, [ref]$uri)
        if (-not $gecerli -or $uri.Scheme -notin @('http', 'https')) {
            throw "Geçersiz link: '$Link' (http:// veya https:// ile başlamalı)"
        }
        $Link = $uri.AbsoluteUri
    }

    # Markdown tablosunu bozacak karakterler (| [ ]) ilerleme satırında temizlenir.
    $baslikTablo = ($Baslik -replace '\|', '/') -replace '[\[\]]', ''
    $linkMetni   = if ($Link) { $Link } else { '-' }
    $tarih       = Get-Date -Format 'yyyy-MM-dd'
    $no          = ''

    # --- Türe göre hedef ---------------------------------------------------------
    switch ($Tur) {
        'Ders' {
            $ust    = Join-Path $RepoKoku 'C-Programlama'
            $no     = Get-SonrakiNo $ust
            $klasor = "$no-$slug"
            $goreli = "C-Programlama/$klasor"
            $dosyalar = [ordered]@{
                'ozet.md'     = Join-Path $SablonDizini 'ders-ozeti.md'
                'quiz.md'     = Join-Path $SablonDizini 'quiz.md'
                'notlarim.md' = Join-Path $SablonDizini 'notlarim.md'
            }
            $isaret = '<!-- C-DERS-EKLE -->'
            $satir  = "| $no | [$baslikTablo]($goreli/ozet.md) | $BosDurum | - |"
        }
        'Konu' {
            $ust    = Join-Path $RepoKoku 'Elektronik/Konular'
            $klasor = $slug
            $goreli = "Elektronik/Konular/$klasor"
            $dosyalar = [ordered]@{
                'ozet.md'      = Join-Path $SablonDizini 'konu-ozeti.md'
                'quiz.md'      = Join-Path $SablonDizini 'quiz.md'
                'kaynaklar.md' = Join-Path $SablonDizini 'kaynaklar.md'
            }
            $isaret = '<!-- KONU-EKLE -->'
            $satir  = "| [$baslikTablo]($goreli/ozet.md) | $BosDurum | - |"
        }
        'Komponent' {
            $ust    = Join-Path $RepoKoku 'Elektronik/Komponentler'
            $no     = Get-SonrakiNo $ust
            $klasor = "$no-$slug"
            $goreli = "Elektronik/Komponentler/$klasor"
            $dosyalar = [ordered]@{
                'ozet.md'      = Join-Path $SablonDizini 'komponent-dersi.md'
                'quiz.md'      = Join-Path $SablonDizini 'quiz.md'
                'kaynaklar.md' = Join-Path $SablonDizini 'kaynaklar.md'
            }
            $isaret = '<!-- KOMPONENT-EKLE -->'
            $satir  = "| $no | [$baslikTablo]($goreli/ozet.md) | $BosDurum | - |"
        }
        'EMC' {
            $ust    = Join-Path $RepoKoku 'Elektronik/EMC'
            $no     = Get-SonrakiNo $ust
            $klasor = "$no-$slug"
            $goreli = "Elektronik/EMC/$klasor"
            $dosyalar = [ordered]@{
                'ozet.md'      = Join-Path $SablonDizini 'konu-ozeti.md'
                'quiz.md'      = Join-Path $SablonDizini 'quiz.md'
                'kaynaklar.md' = Join-Path $SablonDizini 'kaynaklar.md'
            }
            $isaret = '<!-- EMC-EKLE -->'
            $satir  = "| $no | [$baslikTablo]($goreli/ozet.md) | $BosDurum | - |"
        }
        'Proje' {
            $ust    = Join-Path $RepoKoku 'Elektronik/Projeler'
            $no     = Get-SonrakiNo $ust
            $klasor = "$no-$slug"
            $goreli = "Elektronik/Projeler/$klasor"
            $dosyalar = [ordered]@{
                'README.md'         = Join-Path $SablonDizini 'proje-karti.md'
                'sematik-review.md' = Join-Path $RepoKoku 'Elektronik/Sematik-Tasarim/kontrol-listesi.md'
            }
            $isaret = '<!-- PROJE-EKLE -->'
            $satir  = "| $no | [$baslikTablo]($goreli/README.md) | $BosDurum |"
        }
    }

    $hedef = Join-Path $ust $klasor
    if (Test-Path -LiteralPath $hedef) { throw "Bu kayıt zaten var, üzerine yazılmadı: $goreli" }

    # Tüm kaynaklar, herhangi bir dosya oluşturulmadan önce doğrulanır.
    foreach ($kaynak in $dosyalar.Values) {
        if (-not (Test-Path -LiteralPath $kaynak -PathType Leaf)) { throw "Şablon bulunamadı: $kaynak" }
    }

    $degerler = @{ BASLIK = $Baslik; TARIH = $tarih; LINK = $linkMetni; NO = $no }

    # --- Oluştur (hata olursa geri al) ---------------------------------------------
    $null = New-Item -ItemType Directory -Path $hedef -Force
    try {
        foreach ($hedefAd in $dosyalar.Keys) {
            $icerik = Read-Utf8 $dosyalar[$hedefAd]
            foreach ($anahtar in $degerler.Keys) {
                $icerik = $icerik.Replace("{{$anahtar}}", [string]$degerler[$anahtar])
            }
            if ($hedefAd -eq 'sematik-review.md') {
                $icerik = "> Ana kontrol listesinin $tarih tarihli kopyası. Review'u bu dosyada işaretle.`n`n" + $icerik
            }
            Write-Utf8 (Join-Path $hedef $hedefAd) $icerik
        }
    }
    catch {
        Remove-Item -LiteralPath $hedef -Recurse -Force -ErrorAction SilentlyContinue
        throw
    }

    # Klasör oluştu; tablo güncellemesi başarısız olsa bile kayıt geçerlidir.
    try {
        Add-IlerlemeSatiri -RepoKoku $RepoKoku -Isaret $isaret -Satir $satir
    }
    catch {
        Write-Warning "ilerleme.md güncellenemedi: $($_.Exception.Message)"
    }

    Write-Host "Oluşturuldu: $goreli/" -ForegroundColor Green
    foreach ($hedefAd in $dosyalar.Keys) { Write-Host "  - $hedefAd" }
    Write-Host ''
    Write-Host 'Sonraki adım: kaynağı Claude''a ver (istemler: sablonlar/claude-istemleri.md), bitince .\scriptler\Senkron.ps1' -ForegroundColor Cyan
    exit 0
}
catch {
    Write-Host "HATA: $($_.Exception.Message)" -ForegroundColor Red
    exit 1
}
