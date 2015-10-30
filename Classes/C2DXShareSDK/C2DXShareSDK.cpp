//
//  C2DXShareSDK.cpp
//  C2DXShareSDKSample
//
//  Created by 冯 鸿杰 on 13-12-17.
//
//

#include "C2DXShareSDK.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "C2DXiOSShareSDK.h"

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "ShareSDKUtils.h"

#endif


using namespace cn::sharesdk;


void C2DXShareSDK::rigisterAppAndSetPlatformConfig(const char *appKey, __Dictionary *configInfo)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //TODO: Andorid
    // This is not a necessary method for Android, you can setup your platform configs more efficiently in "assets/ShareSDK.xml"
    rigisterAppAndSetPlatformConfig(appKey, configInfo);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

void C2DXShareSDK::authorize(int reqID, C2DXPlatType platType, C2DXAuthResultEvent callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //TODO: Andorid
    authorize(reqID, (int)platType, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

void C2DXShareSDK::cancelAuthorize(C2DXPlatType platType)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //TODO: Andorid
    cancelAuthorize((int)platType);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

bool C2DXShareSDK::isAuthorizedValid(C2DXPlatType platType)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //TODO: Andorid
    return isAuthorizedValid((int)platType);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
    
    return false;
}

bool C2DXShareSDK::isClientValid(C2DXPlatType platType)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //TODO: Andorid
    return isClientValid((int)platType);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS    
    //TODO: iOS
    
#endif
    
    return false;
}


void C2DXShareSDK::getUserInfo(int reqID, C2DXPlatType platType, C2DXGetUserInfoResultEvent callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //TODO: Andorid
    getUserInfo(reqID, (int)platType, callback);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

__Dictionary* C2DXShareSDK::getAuthInfo(C2DXPlatType platType)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //TODO: Andorid
    //return getAuthInfo((int)platType);
    return getAuthInfo((int)platType);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

    //TODO: iOS


#endif
}

void C2DXShareSDK::shareContent(int reqID, C2DXPlatType platType, __Dictionary *content, C2DXShareResultEvent callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //TODO: Andorid
    __Array *platTypes = __Array::create();
	platTypes.addObject(platType);
    shareContent(reqID, platTypes, content, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

void C2DXShareSDK::shareContent(int reqID, __Array *platTypes, __Dictionary *content, C2DXShareResultEvent callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //TODO: Andorid
    shareContent(reqID, platTypes, content, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

void C2DXShareSDK::showShareMenu(int reqID, __Array *platTypes, __Dictionary *content, int x, int y, C2DXShareResultEvent callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //TODO: Android
    onekeyShare(reqID, 0, content, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

void C2DXShareSDK::showShareView(int reqID, C2DXPlatType platType, __Dictionary *content, C2DXShareResultEvent callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //TODO: Android
    onekeyShare(reqID, (int) platType, content, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

void C2DXShareSDK::getFriendList(int reqID, C2DXPlatType platType, int count, int page, C2DXGetFriendsResultEvent callback){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //TODO: Android
	getFriendList(reqID, (int) platType, count, page, callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

    //TODO: iOS
    //

#endif
}

void C2DXShareSDK::addFriend(int reqID, C2DXPlatType platType, const char* account, C2DXAddFriendResultEvent callback){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //TODO: Android
	addFriend(reqID, (int) platType, account, callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

    //TODO: iOS
    //

#endif
}

void C2DXShareSDK::toast(const char *msg)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //TODO: Android
    toastShow(msg);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

    //TODO: iOS

#endif
}
