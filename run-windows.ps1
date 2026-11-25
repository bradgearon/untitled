param([switch]$BuildOnly, [switch]$Deploy, [int]$Jobs = [Environment]::ProcessorCount)
. "$PSScriptRoot/scripts/qt-common.ps1"
Initialize-Tools
Initialize-Qt 'desktop' 'win64_mingw81' 'mingw81_64'
Write-Host "Qt SDK: $Qt"
Write-Host "MinGW: $(Split-Path $Make)"
Invoke-Checked "$Qt/bin/qmake.exe" @('-v')
$env:QT_PLUGIN_PATH = Join-Path $Qt 'plugins'
$env:QT_QPA_PLATFORM_PLUGIN_PATH = Join-Path $Qt 'plugins/platforms'
$env:QML2_IMPORT_PATH = Join-Path $Qt 'qml'
$build = Join-Path $Repo 'build-windows'
New-Item -ItemType Directory -Force -Path $build | Out-Null
Push-Location $build
try {
    Invoke-Checked "$Qt/bin/qmake.exe" @("$Repo/standalone.pro",'CONFIG+=release')
    Invoke-Checked $Make @("-j$Jobs")
    $exe = Join-Path $build 'release/untitled.exe'
    if (-not (Test-Path $exe)) { $exe = Join-Path $build 'untitled.exe' }
    if (-not (Test-Path $exe)) { throw 'Executable missing.' }
    Write-Host "Executable: $exe"
    if ($Deploy -or -not $BuildOnly) {
        $platform = Join-Path $env:QT_QPA_PLATFORM_PLUGIN_PATH 'qwindows.dll'
        if (-not (Test-Path -LiteralPath $platform -PathType Leaf)) {
            throw "Qt Windows platform plugin missing: $platform. Verify the Qt installation."
        }
    }
    if ($Deploy) {
        Invoke-Checked "$Qt/bin/windeployqt.exe" @('--release','--qmldir',"$Repo/untitled",$exe)
    }
    if (-not $BuildOnly) { Start-Process -FilePath $exe -WorkingDirectory (Split-Path $exe) }
} finally { Pop-Location }
