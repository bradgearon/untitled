param([switch]$BuildOnly, [int]$Jobs = [Environment]::ProcessorCount)
. "$PSScriptRoot/scripts/qt-common.ps1"
Initialize-Tools
Initialize-Qt 'desktop' 'win64_mingw81' 'mingw81_64'
$build = Join-Path $Repo 'build-windows'
New-Item -ItemType Directory -Force -Path $build | Out-Null
Push-Location $build
try {
    Invoke-Checked "$Qt/bin/qmake.exe" @("$Repo/standalone.pro",'CONFIG+=release')
    Invoke-Checked $Make @("-j$Jobs")
    $exe = Join-Path $build 'release/untitled.exe'
    if (-not (Test-Path $exe)) { $exe = Join-Path $build 'untitled.exe' }
    if (-not (Test-Path $exe)) { throw 'Executable missing.' }
    Invoke-Checked "$Qt/bin/windeployqt.exe" @('--release','--qmldir',"$Repo/untitled",$exe)
    Write-Host "Executable: $exe"
    if (-not $BuildOnly) { Start-Process $exe -WorkingDirectory (Split-Path $exe) }
} finally { Pop-Location }
