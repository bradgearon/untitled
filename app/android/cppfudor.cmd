@echo off
set build=S:\unity-ads-qt\build-main-Android_for_armeabi_v7a_GCC_4_9_Qt_5_8_0-Debug\android-build\
set plibs=S:\pfudor\Assets\Plugins\Android\libs\
set dlibs=S:\divisors\Assets\Plugins\Android\libs\
gradle -p %build% build
xcopy %build%build\outputs\aar\android-build-release.aar %plibs%untitled.aar /y 
xcopy /e /y %build%libs\*.so %plibs%

xcopy %build%build\outputs\aar\android-build-release.aar %dlibs%untitled.aar /y 
xcopy /e /y %build%libs\*.so %dlibs%
