LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,/Users/lixiang/Downloads/CHAJIAN/Cocos2d_SDK)
$(call import-add-path,/Users/lixiang/Downloads/CHAJIAN/Cocos2d_SDK/external)
$(call import-add-path,/Users/lixiang/Downloads/CHAJIAN/Cocos2d_SDK/cocos)


LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../Classes/HelloWorldScene.cpp \

				   ../../../Classes/C2DXShareSDK/Android/ShareSDKUtils.cpp \
				   ../../../Classes/C2DXShareSDK/Android/MobSDKUtils.cpp \

				   ../../../Classes/C2DXShareSDK/C2DXShareSDK.cpp \
				   ../../../Classes/C2DXShareSDK/C2DXMobSDK.cpp \

				   ../../../Classes/C2DXShareSDK/Android/JSON/CCJSONConverter.cpp \
				   ../../../Classes/C2DXShareSDK/Android/JSON/cJSON/cJSON.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
                    $(LOCAL_PATH)/../../../Classes/C2DXShareSDK \
                    $(LOCAL_PATH)/../../../Classes/C2DXShareSDK/Android \

					$(LOCAL_PATH)/../../../Classes/C2DXShareSDK/Android/JSON \
					$(LOCAL_PATH)/../../../Classes/C2DXShareSDK/Android/JSON/cJSON



# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
