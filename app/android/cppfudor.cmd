@echo off
set build=%cd%\
set passets=S:\pfudor\Assets\Plugins\Android\
set dassets=S:\divisors\Assets\Plugins\Android\

set plibs=%passets%libs\
set dlibs=%dassets%libs\

gradle -p %build% build
xcopy %build%build\outputs\aar\android-build-release.aar %plibs%untitled.aar /y
xcopy /e /y %build%libs\*.so %plibs%
xcopy /e /y %build%assets %passets%assets\

xcopy %build%build\outputs\aar\android-build-release.aar %dlibs%untitled.aar /y
xcopy /e /y %build%libs\*.so %dlibs%
xcopy /e /y %build%assets %dassets%assets\
