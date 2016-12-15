CONFIG += c++14

linux: {
  PLATFORM = linux
}

win32: {
  DEFINES += WIN32
  PLATFORM = win32
  EXT = exe
}

android: {
  PLATFORM = android
}

MOC_DIR = ../build/$$PLATFORM/obj
OBJECTS_DIR = ../build/$$PLATFORM/obj
DESTDIR = ../build/$$PLATFORM
RCC_DIR = ../build/$$PLATFORM/obj

# SSL_LIB_PATH = '../libs/android-openssl/openssl-1.0.2/'

# contains(QMAKESPEC, .+armv7.+) {
  # SSL_LIB_PATH = $$join(SSL_LIB_PATH, , , armeabi-v7a/lib)
# }

# contains(QMAKESPEC, .+x86.+){
  # SSL_LIB_PATH = $$join(SSL_LIB_PATH, , , x86/lib)
# }
