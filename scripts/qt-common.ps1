$ErrorActionPreference = 'Stop'
$Repo = Split-Path -Parent $PSScriptRoot
$Tools = if ($env:UNTITLED_TOOLS) { $env:UNTITLED_TOOLS } else { Join-Path $env:LOCALAPPDATA 'UntitledTools' }
$QtRoot = Join-Path $Tools 'Qt'
New-Item -ItemType Directory -Force -Path $Tools | Out-Null
function Invoke-Checked([string]$Exe, [string[]]$Arguments) {
    & $Exe @Arguments
    if ($LASTEXITCODE -ne 0) { throw "$Exe failed with exit code $LASTEXITCODE" }
}
function Initialize-Tools {
    Invoke-Checked git @('-C',$Repo,'submodule','update','--init','--recursive')
    $venv = Join-Path $Tools 'aqt-venv'
    $script:Python = Join-Path $venv 'Scripts/python.exe'
    if (-not (Test-Path $script:Python)) {
        if (Get-Command py -ErrorAction SilentlyContinue) { Invoke-Checked py @('-3','-m','venv',$venv) }
        elseif (Get-Command python -ErrorAction SilentlyContinue) { Invoke-Checked python @('-m','venv',$venv) }
        else { throw 'Install Python 3: winget install -e --id Python.Python.3.12 ; then reopen terminal.' }
    }
    & $script:Python -m pip show aqtinstall | Out-Null
    if ($LASTEXITCODE -ne 0) { Invoke-Checked $script:Python @('-m','pip','install','aqtinstall==3.1.16') }
    $script:Make = Join-Path $QtRoot 'Tools/mingw810_64/bin/mingw32-make.exe'
    if (-not (Test-Path $script:Make)) {
        Invoke-Checked $script:Python @('-m','aqt','install-tool','--outputdir',$QtRoot,'windows','desktop','tools_mingw','qt.tools.win64_mingw810')
    }
    if (-not (Test-Path $script:Make)) { throw 'MinGW installation incomplete.' }
    $env:Path = (Split-Path $script:Make) + ';' + $env:Path
}
function Initialize-Qt([string]$Target, [string]$Arch, [string]$Folder) {
    $script:Qt = Join-Path $QtRoot "5.15.2/$Folder"
    if (-not (Test-Path "$script:Qt/bin/qmake.exe")) {
        Invoke-Checked $script:Python @('-m','aqt','install-qt','--outputdir',$QtRoot,'windows',$Target,'5.15.2',$Arch)
    }
    if (-not (Test-Path "$script:Qt/bin/qmake.exe")) { throw 'Qt installation incomplete.' }
    $env:Path = "$script:Qt/bin;" + $env:Path
}
function Get-Jdk([int]$Version) {
    $home = Join-Path $Tools "jdk-$Version"
    if (-not (Test-Path "$home/bin/java.exe")) {
        $zip = Join-Path $Tools "jdk-$Version.zip"
        $stage = Join-Path $Tools "jdk-$Version-extract"
        if (Test-Path $stage) { Remove-Item $stage -Recurse -Force }
        Invoke-WebRequest -UseBasicParsing "https://api.adoptium.net/v3/binary/latest/$Version/ga/windows/x64/jdk/hotspot/normal/eclipse" -OutFile $zip
        Expand-Archive $zip $stage -Force
        $dir = Get-ChildItem $stage -Directory | Where-Object { Test-Path "$($_.FullName)/bin/java.exe" } | Select-Object -First 1
        if (-not $dir) { throw 'JDK extraction failed.' }
        if (Test-Path $home) { throw "Remove incomplete JDK directory $home" }
        Move-Item $dir.FullName $home
        Remove-Item $zip -Force
        Remove-Item $stage -Recurse -Force
    }
    return $home
}
