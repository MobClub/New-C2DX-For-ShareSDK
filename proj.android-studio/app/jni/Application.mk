# 确保NDK版本是r9以上
APP_STL := gnustl_static

APP_CPPFLAGS := -frtti -fexceptions -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -fsigned-char -std=gnu++11 -pthread # -std=c++11
APP_LDFLAGS := -latomic
APP_ABI := armeabi

APP_DEBUG := $(strip $(NDK_DEBUG))
ifeq ($(APP_DEBUG),1)
  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
  APP_OPTIM := debug
else
  APP_CPPFLAGS += -DNDEBUG
  APP_OPTIM := release
endif