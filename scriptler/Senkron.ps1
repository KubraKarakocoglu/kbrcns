#Requires -Version 5.1
<#
.SYNOPSIS
    Yerel değişiklikleri commit'ler ve uzak repoyla güvenli şekilde senkronize eder.

.DESCRIPTION
    Çalışmaya başlarken ve bitirirken aynı komut çalıştırılır.

    Akış: ön kontroller → yerel commit → uzak kontrol → pull --rebase → push

    Fail-safe tasarım:
      - Değişiklikler ÖNCE yerel commit'e alınır; ağ veya çakışma hatasında iş kaybolmaz.
      - Çakışmada rebase iptal edilir, repo senkron öncesi haline döner, çakışan dosyalar listelenir.
      - Asla --force kullanılmaz.
      - Sınırın üzerindeki dosyalar commit'e alınmaz (GitHub tek dosya sınırı 100 MB).
      - Git çıktısı yalnızca çıkış kodlarıyla değerlendirilir; dil/sürüm farkından etkilenmez.

.PARAMETER Mesaj
    Commit mesajı. Verilmezse "Senkron: <bilgisayar adı> <tarih saat>" kullanılır.

.EXAMPLE
    .\scriptler\Senkron.ps1

.EXAMPLE
    .\scriptler\Senkron.ps1 -Mesaj "Pointer dersi özeti eklendi"

.NOTES
    Çıkış kodları:
      0  Başarılı
      1  Ön kontrol hatası (git yok, kimlik yok, yarım kalmış işlem...)
      2  Uzak repoya erişilemedi (ağ / kimlik doğrulama) — yerel commit güvende
      3  Çakışma — rebase iptal edildi, yerel commit güvende
      4  Push başarısız — yerel commit güvende
      9  Beklenmeyen hata
#>
[CmdletBinding()]
param(
    [ValidateLength(1, 200)]
    [ValidatePattern('\S')]
    [string]$Mesaj
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

# --- Ayarlar -----------------------------------------------------------------
$BuyukDosyaSiniriMB = 50
$UzakAd             = 'origin'

# --- Durum -------------------------------------------------------------------
$script:CikisKodu = 0
$script:RepoKoku  = $null
$script:GitDizini = $null

# --- Yardımcılar ---------------------------------------------------------------
function Write-Adim  ([string]$Metin) { Write-Host "==> $Metin" -ForegroundColor Cyan }
function Write-Tamam ([string]$Metin) { Write-Host "    $Metin" -ForegroundColor Green }
function Write-Uyari ([string]$Metin) { Write-Host "    UYARI: $Metin" -ForegroundColor Yellow }

function Stop-Senkron {
    param([string]$Metin, [int]$Kod)
    $script:CikisKodu = $Kod
    throw $Metin
}

function Invoke-Git {
    <#
        git'i repo kökünde çalıştırır, stdout+stderr'i metin olarak ve çıkış kodunu döndürür.
        PowerShell 5.1'de stderr satırları ErrorRecord'a dönüşür; ErrorActionPreference
        geçici olarak 'Continue' yapılarak bunun script'i durdurması engellenir.
    #>
    param([Parameter(Mandatory)][string[]]$Argumanlar)

    $oncekiTercih = $ErrorActionPreference
    $ErrorActionPreference = 'Continue'
    try {
        $satirlar = @(& git -C $script:RepoKoku @Argumanlar 2>&1 | ForEach-Object { "$_" })
        $kod = $LASTEXITCODE
    }
    finally {
        $ErrorActionPreference = $oncekiTercih
    }

    [pscustomobject]@{
        Kod   = $kod
        Cikti = ($satirlar -join [Environment]::NewLine).Trim()
    }
}

function Test-YarimIslem {
    foreach ($isaret in 'rebase-merge', 'rebase-apply', 'MERGE_HEAD', 'CHERRY_PICK_HEAD') {
        if (Test-Path -LiteralPath (Join-Path $script:GitDizini $isaret)) { return $isaret }
    }
    return $null
}

function Test-HeadVar {
    (Invoke-Git @('rev-parse', '--verify', '-q', 'HEAD')).Kod -eq 0
}

function Invoke-GuvenliCekme {
    param([string]$Dal)

    # --autostash: commit dışında kalan (ör. sınır üstü) değiştirilmiş dosyalar rebase'i engellemesin.
    $cek = Invoke-Git @('pull', '--rebase', '--autostash', $UzakAd, $Dal)
    if ($cek.Kod -eq 0) { return }

    $yarim = Test-YarimIslem
    if ($yarim -and $yarim -like 'rebase-*') {
        $cakisan = (Invoke-Git @('-c', 'core.quotePath=false', 'diff', '--name-only', '--diff-filter=U')).Cikti
        $iptal   = Invoke-Git @('rebase', '--abort')
        $durum   = if ($iptal.Kod -eq 0) {
            'Rebase iptal edildi; repo senkron öncesi haline döndü.'
        } else {
            "Rebase iptal EDİLEMEDİ, elle müdahale gerekli:`n$($iptal.Cikti)"
        }
        Stop-Senkron -Kod 3 -Metin (
            "Çakışma: aynı dosya iki bilgisayarda farklı değiştirilmiş.`n" +
            "Çakışan dosyalar:`n$cakisan`n$durum`n" +
            "Yerel commit'in güvende. Çözüm için bu çıktıyı Claude'a gönder."
        )
    }

    Stop-Senkron -Kod 2 -Metin "Uzak değişiklikler alınamadı. Yerel commit'in güvende.`nGit çıktısı:`n$($cek.Cikti)"
}

# --- Ana akış ------------------------------------------------------------------
function Invoke-Senkron {

    # 1) Ön kontroller
    Write-Adim 'Ön kontroller'

    if (-not $PSScriptRoot) {
        Stop-Senkron -Kod 1 -Metin 'Script dosya olarak çalıştırılmalı: .\scriptler\Senkron.ps1'
    }
    $script:RepoKoku = Split-Path -Path $PSScriptRoot -Parent

    if (-not (Get-Command git -ErrorAction SilentlyContinue)) {
        Stop-Senkron -Kod 1 -Metin "git bulunamadı. Git for Windows kurulu ve PATH'te olmalı."
    }

    $gitDizin = Invoke-Git @('rev-parse', '--absolute-git-dir')
    if ($gitDizin.Kod -ne 0) {
        Stop-Senkron -Kod 1 -Metin "Script bir Git reposunun içinde değil: $script:RepoKoku"
    }
    $script:GitDizini = $gitDizin.Cikti

    $yarim = Test-YarimIslem
    if ($yarim) {
        Stop-Senkron -Kod 1 -Metin "Yarım kalmış bir git işlemi var ($yarim). Önce çözülmeli: 'git status' çıktısını Claude'a gönder."
    }

    $ad     = (Invoke-Git @('config', 'user.name')).Cikti
    $eposta = (Invoke-Git @('config', 'user.email')).Cikti
    if (-not $ad -or -not $eposta) {
        Stop-Senkron -Kod 1 -Metin (
            "Git kimliği ayarlı değil. Bir kez çalıştır:`n" +
            "  git config --global user.name  ""Adın Soyadın""`n" +
            "  git config --global user.email ""eposta@adresin.com"""
        )
    }

    if ((Invoke-Git @('remote', 'get-url', $UzakAd)).Kod -ne 0) {
        Stop-Senkron -Kod 1 -Metin "'$UzakAd' adlı uzak repo tanımlı değil."
    }

    $dal = (Invoke-Git @('symbolic-ref', '--short', '-q', 'HEAD')).Cikti
    if (-not $dal) {
        Stop-Senkron -Kod 1 -Metin "HEAD bir dala bağlı değil (detached HEAD). 'git status' çıktısını Claude'a gönder."
    }
    Write-Tamam "Repo: $script:RepoKoku  |  Dal: $dal"

    # 2) Yerel değişiklikleri commit'e al
    Write-Adim 'Yerel değişiklikler'

    $ekle = Invoke-Git @('add', '--all')
    if ($ekle.Kod -ne 0) { Stop-Senkron -Kod 1 -Metin "git add başarısız:`n$($ekle.Cikti)" }

    # Büyük dosya koruması: sınırı aşanlar commit'ten çıkarılır, dosyanın kendisi diskte kalır.
    $headVar  = Test-HeadVar
    $asamali  = Invoke-Git @('-c', 'core.quotePath=false', 'diff', '--cached', '--name-only', '--diff-filter=AM')
    if ($asamali.Kod -eq 0 -and $asamali.Cikti) {
        foreach ($goreli in ($asamali.Cikti -split "`r?`n")) {
            if (-not $goreli) { continue }
            $tam = Join-Path $script:RepoKoku $goreli
            if (-not (Test-Path -LiteralPath $tam -PathType Leaf)) { continue }

            $mb = (Get-Item -LiteralPath $tam).Length / 1MB
            if ($mb -le $BuyukDosyaSiniriMB) { continue }

            $geriAl = if ($headVar) { @('reset', '-q', '--', $goreli) } else { @('rm', '--cached', '-q', '--', $goreli) }
            if ((Invoke-Git $geriAl).Kod -ne 0) {
                Stop-Senkron -Kod 1 -Metin "Büyük dosya commit'ten çıkarılamadı: $goreli"
            }
            Write-Uyari ("{0} ({1:N1} MB) commit'e alınmadı: {2} MB sınırı. Yerel/ klasörüne taşı." -f $goreli, $mb, $BuyukDosyaSiniriMB)
        }
    }

    $fark = Invoke-Git @('diff', '--cached', '--quiet')
    switch ($fark.Kod) {
        0 { Write-Tamam 'Commit edilecek değişiklik yok.' }
        1 {
            if (-not $Mesaj) {
                $Mesaj = "Senkron: $env:COMPUTERNAME $(Get-Date -Format 'yyyy-MM-dd HH:mm')"
            }
            # Windows PowerShell 5.1, native argümanlardaki çift tırnağı bozabilir.
            $Mesaj  = $Mesaj.Trim() -replace '"', "'"
            $commit = Invoke-Git @('commit', '-q', '-m', $Mesaj)
            if ($commit.Kod -ne 0) { Stop-Senkron -Kod 1 -Metin "Commit başarısız:`n$($commit.Cikti)" }
            Write-Tamam "Commit oluşturuldu: $Mesaj"
        }
        default { Stop-Senkron -Kod 1 -Metin "git diff başarısız:`n$($fark.Cikti)" }
    }

    # 3) Uzak repo erişimi ve dal kontrolü
    Write-Adim 'Uzak repo kontrolü'

    $uzak = Invoke-Git @('ls-remote', '--heads', $UzakAd, $dal)
    if ($uzak.Kod -ne 0) {
        Stop-Senkron -Kod 2 -Metin (
            "Uzak repoya ulaşılamadı (ağ veya kimlik doğrulama sorunu).`n" +
            "Değişikliklerin yerel commit olarak güvende; bağlantı gelince tekrar çalıştır.`n" +
            "Git çıktısı:`n$($uzak.Cikti)"
        )
    }
    $desen      = '\srefs/heads/' + [regex]::Escape($dal) + '$'
    $uzakDalVar = @($uzak.Cikti -split "`r?`n" | Where-Object { $_ -match $desen }).Count -gt 0

    # 4) Uzak değişiklikleri al
    if ($uzakDalVar) {
        Write-Adim 'Uzak değişiklikler alınıyor (pull --rebase)'
        Invoke-GuvenliCekme -Dal $dal
        Write-Tamam 'Güncel.'
    } else {
        Write-Tamam "Uzakta '$dal' dalı henüz yok; ilk gönderim yapılacak."
    }

    # 5) Gönder
    Write-Adim 'Gönderiliyor (push)'

    if (-not (Test-HeadVar)) {
        Write-Tamam 'Henüz hiç commit yok; gönderilecek bir şey yok.'
        return
    }

    $upstreamVar = (Invoke-Git @('rev-parse', '--abbrev-ref', '--symbolic-full-name', '@{u}')).Kod -eq 0
    $pushArg     = if ($upstreamVar) { @('push', $UzakAd, $dal) } else { @('push', '-u', $UzakAd, $dal) }

    $gonder = Invoke-Git $pushArg
    if ($gonder.Kod -ne 0) {
        # En olası neden: diğer bilgisayar bu arada push etti. Bir kez daha çek ve gönder.
        Write-Uyari 'Push reddedildi; uzak repo bu arada değişmiş olabilir. Bir kez daha senkronize ediliyor...'
        Invoke-GuvenliCekme -Dal $dal
        $gonder = Invoke-Git $pushArg
        if ($gonder.Kod -ne 0) {
            Stop-Senkron -Kod 4 -Metin "Push başarısız. Yerel commit'in güvende; daha sonra tekrar dene.`nGit çıktısı:`n$($gonder.Cikti)"
        }
    }
    Write-Tamam 'Gönderildi.'

    # 6) Özet
    $son   = (Invoke-Git @('log', '-1', '--format=%h  %s')).Cikti
    $kalan = (Invoke-Git @('-c', 'core.quotePath=false', 'status', '--short')).Cikti
    Write-Host "`nSenkron tamamlandı. Son commit: $son" -ForegroundColor Green
    if ($kalan) { Write-Uyari "Commit dışında kalan dosyalar var:`n$kalan" }
}

# --- Giriş noktası -------------------------------------------------------------
$eskiKodlama = $null
try {
    # git UTF-8 yazar; Türkçe dosya adlarının doğru okunması için konsol kodlaması geçici olarak UTF-8.
    try {
        $eskiKodlama = [Console]::OutputEncoding
        [Console]::OutputEncoding = New-Object System.Text.UTF8Encoding($false)
    } catch {
        $eskiKodlama = $null
    }

    Invoke-Senkron
}
catch {
    if ($script:CikisKodu -eq 0) { $script:CikisKodu = 9 }
    Write-Host "`nHATA: $($_.Exception.Message)" -ForegroundColor Red
}
finally {
    if ($null -ne $eskiKodlama) {
        try { [Console]::OutputEncoding = $eskiKodlama } catch { }
    }
}
exit $script:CikisKodu
