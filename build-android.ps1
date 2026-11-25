param([ValidateSet('arm64-v8a','armeabi-v7a','x86','x86_64')][string]$Abi='arm64-v8a', [int]$Jobs=[Environment]::ProcessorCount, [switch]$Install)
. "$PSScriptRoot/scripts/qt-common.ps1"
Initialize-Tools
Initialize-Qt 'android' 'android' 'android'
$jdk17 = Get-Jdk 17
$jdk8 = Get-Jdk 8
$sdk = if ($env:UNTITLED_ANDROID_SDK) { $env:UNTITLED_ANDROID_SDK } else { Join-Path $Tools 'AndroidSdk' }
$manager = Join-Path $sdk 'cmdline-tools/latest/bin/sdkmanager.bat'
if (-not (Test-Path $manager)) {
    $zip = Join-Path $Tools 'android-tools.zip'
    $stage = Join-Path $Tools 'android-tools-extract'
    if (Test-Path $stage) { Remove-Item $stage -Recurse -Force }
    Invoke-WebRequest -UseBasicParsing 'https://dl.google.com/android/repository/commandlinetools-win-11076708_latest.zip' -OutFile $zip
    Expand-Archive $zip $stage -Force
    New-Item -ItemType Directory -Force -Path "$sdk/cmdline-tools" | Out-Null
    if (Test-Path "$sdk/cmdline-tools/latest") { throw 'Remove incomplete cmdline-tools/latest directory first.' }
    Move-Item "$stage/cmdline-tools" "$sdk/cmdline-tools/latest"
    Remove-Item $zip -Force
    Remove-Item $stage -Recurse -Force
}
$env:JAVA_HOME = $jdk17
$env:ANDROID_HOME = $sdk
$env:ANDROID_SDK_ROOT = $sdk
Invoke-Checked $manager @("--sdk_root=$sdk",'--licenses')
Invoke-Checked $manager @("--sdk_root=$sdk",'platform-tools','platforms;android-29','build-tools;29.0.3','ndk;21.3.6528147')
$env:ANDROID_NDK_ROOT = Join-Path $sdk 'ndk/21.3.6528147'
$env:ANDROID_NDK_HOME = $env:ANDROID_NDK_ROOT
$env:ANDROID_NDK_HOST = 'windows-x86_64'
$env:JAVA_HOME = $jdk8
$env:Path = "$jdk8/bin;$sdk/platform-tools;" + $env:Path
$build = Join-Path $Repo "build-android-$Abi"
$package = Join-Path $build 'package'
New-Item -ItemType Directory -Force -Path $package | Out-Null
$template = Join-Path $Qt 'src/android/templates'
$manifest = Get-Content "$template/AndroidManifest.xml" -Raw
$manifest = $manifest.Replace('package="org.qtproject.example"','package="com.wds.untitled"')
$manifest = $manifest.Replace('android:name="org.qtproject.qt5.android.bindings.QtActivity"','android:name="com.wds.untitled.MyActivity" android:exported="true"')
if ($manifest -notmatch 'com\.wds\.untitled\.MyActivity') { throw 'Unexpected Qt manifest template.' }
$utf8 = New-Object System.Text.UTF8Encoding($false)
[IO.File]::WriteAllText("$package/AndroidManifest.xml",$manifest,$utf8)
Copy-Item "$Repo/app/android/src" $package -Recurse -Force
New-Item -ItemType Directory -Force -Path "$package/res/values" | Out-Null
Copy-Item "$Repo/app/android/res/values/styles.xml" "$package/res/values/styles.xml" -Force
$helper = "$package/src/com/wds/untitled/UntitledNative.java"
$java = (Get-Content $helper -Raw).Replace('intent = activity.getParentActivityIntent();','activity.moveTaskToBack(true); return;')
[IO.File]::WriteAllText($helper,$java,$utf8)
if (Test-Path "$template/build.gradle") {
    $gradle = (Get-Content "$template/build.gradle" -Raw).Replace('jcenter()', 'mavenCentral()')
    [IO.File]::WriteAllText("$package/build.gradle",$gradle,$utf8)
}
Push-Location $build
try {
    Invoke-Checked "$Qt/bin/qmake.exe" @("$Repo/standalone.pro","ANDROID_ABIS=$Abi",'ANDROID_PLATFORM=android-23','CONFIG+=release')
    Invoke-Checked $Make @("-j$Jobs")
    Invoke-Checked $Make @('apk')
    $apk = Get-ChildItem "$build/android-build" -Filter '*.apk' -Recurse -File | Sort-Object LastWriteTime -Descending | Select-Object -First 1
    if (-not $apk) { throw 'APK missing.' }
    Write-Host "APK: $($apk.FullName)"
    if ($Install) { Invoke-Checked "$sdk/platform-tools/adb.exe" @('install','-r',$apk.FullName) }
} finally { Pop-Location }
