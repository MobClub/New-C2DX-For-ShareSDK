//
//  C2DXShareSDK.cpp
//  C2DXShareSDKSample
//
//  Copyright © 2015年 mob.com. All rights reserved.
//

#include "C2DXShareSDK.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "C2DXiOSShareSDK.h"

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "ShareSDKUtils.h"

#endif

using namespace cn::sharesdk;

const char* PlatId::Unknown = "0";
const char* PlatId::SinaWeibo = "1";         /**< 新浪微博 */
const char* PlatId::TencentWeibo = "2";      /**< 腾讯微博 */
const char* PlatId::DouBan = "5";            /**< 豆瓣社区 */
const char* PlatId::QZone = "6";             /**< QQ空间 */
const char* PlatId::Renren = "7";            /**< 人人网 */
const char* PlatId::Kaixin = "8";            /**< 开心网 */
const char* PlatId::Pengyou = "9";           /**< 朋友网 */
const char* PlatId::Facebook = "10";         /**< Facebook */
const char* PlatId::Twitter = "11";          /**< Twitter */
const char* PlatId::Evernote = "12";         /**< 印象笔记 */
const char* PlatId::Foursquare = "13";       /**< Foursquare */
const char* PlatId::GooglePlus = "14";       /**< Google＋ */
const char* PlatId::Instagram = "15";        /**< Instagram */
const char* PlatId::LinkedIn = "16";         /**< LinkedIn */
const char* PlatId::Tumblr = "17";           /**< Tumbir */
const char* PlatId::Mail = "18";             /**< 邮件分享 */
const char* PlatId::SMS = "19";              /**< 短信分享 */
const char* PlatId::AirPrint = "20";         /**< 打印 */
const char* PlatId::Copy = "21";             /**< 拷贝 */
const char* PlatId::WeixiSession = "22";     /**< 微信好友 */
const char* PlatId::WeixiTimeline = "23";    /**< 微信朋友圈 */
const char* PlatId::QQ = "24";               /**< QQ */
const char* PlatId::Instapaper = "25";       /**< Instapaper */
const char* PlatId::Pocket = "26";           /**< Pocket */
const char* PlatId::YouDaoNote = "27";       /**< 有道云笔记 */
const char* PlatId::Pinterest = "30";        /**< Pinterest */
const char* PlatId::Flickr = "34";           /**< Flickr */
const char* PlatId::Dropbox = "35";          /**< Dropbox */
const char* PlatId::VKontakte = "36";        /**< VKontakte */
const char* PlatId::WeixiFav = "37";         /**< 微信收藏 */
const char* PlatId::YiXinSession = "38";     /**< 易信好友 */
const char* PlatId::YiXinTimeline = "39";    /**< 易信朋友圈 */
const char* PlatId::YiXinFav = "40";         /**< 易信收藏 */
const char* PlatId::MingDao = "41";          /**< 明道 */
const char* PlatId::Line = "42";             /**< Line */
const char* PlatId::WhatsApp = "43";         /**< Whats App */
const char* PlatId::KakaoTalk = "44";        /**< KakaoTalk */
const char* PlatId::KakaoStory = "45";       /**< KakaoStory */ 
const char* PlatId::FacebookMessenger = "46";/**< FacebookMessenger */
const char* PlatId::Bluetooth = "48";        /**< Bluetooth */
const char* PlatId::Alipay = "50";           /**< Alipay */
const char* PlatId::KakaoPlatform = "995";   /**< Kakao Series */
const char* PlatId::EvernotePlatform = "996";/**< Evernote Series */
const char* PlatId::WechatPlatform = "997";  /**< Wechat Series */
const char* PlatId::QQPlatform = "998";	     /**< QQ Series */
const char* PlatId::Any = "999"; 			 /**< 任意平台 */

int reqID = 0;

void C2DXShareSDK::registerAppAndSetPlatformConfig(const char *appKey, C2DXDictionary *configInfo)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid
    // This is not a necessary method for Android, you can setup your platform configs more efficiently in "assets/ShareSDK.xml"
    registerAppAndSetPlatformConfigJNI(appKey, configInfo);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSShareSDK::registerAppAndSetPlatformConfig(appKey, configInfo);
    
#endif
}

int C2DXShareSDK::authorize(C2DXPlatType platType, C2DXAuthResultEvent callback)
{
	reqID ++;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid
    authorizeJNI(reqID, (int)platType, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSShareSDK::authorize(reqID, platType, callback);
    
#endif
	return reqID;
}

void C2DXShareSDK::cancelAuthorize(C2DXPlatType platType)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid
    cancelAuthorizeJNI((int)platType);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSShareSDK::cancelAuthorize(platType);
    
#endif
}

bool C2DXShareSDK::isAuthorizedValid(C2DXPlatType platType)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid
    return isAuthorizedValidJNI((int)platType);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    return C2DXiOSShareSDK::hasAutorized(platType);
    
#endif
    
    return false;
}

bool C2DXShareSDK::isClientValid(C2DXPlatType platType)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid
    return isClientValidJNI((int)platType);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS    
    //iOS
    return C2DXiOSShareSDK::isClientInstalled(platType);
    
#endif
    
    return false;
}

int C2DXShareSDK::getUserInfo(C2DXPlatType platType, C2DXGetUserInfoResultEvent callback)
{
	reqID ++;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid
    getUserInfoJNI(reqID, (int)platType, callback);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSShareSDK::getUserInfo(reqID, platType, callback);
    
#endif
	return reqID;
}

C2DXDictionary* C2DXShareSDK::getAuthInfo(C2DXPlatType platType)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //Andorid
    //return getAuthInfo((int)platType);
    return getAuthInfoJNI((int)platType);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

    //iOS
    //Use C2DXShareSDK::getUserInfo(int reqID, C2DXPlatType platType, C2DXGetUserInfoResultEvent callback) method to get the authorize infomation.
    return NULL;

#endif
}

int C2DXShareSDK::shareContent(C2DXPlatType platType, C2DXDictionary *content, C2DXShareResultEvent callback)
{
    reqID ++;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid
    C2DXArray *platTypes = C2DXArray::create();
    platTypes->addObject(C2DXInteger::create(platType));
    shareContentJNI(reqID, platTypes, content, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXArray *platTypes = C2DXArray::create();
    platTypes->addObject(C2DXInteger::create(platType));
    C2DXiOSShareSDK::shareContent(reqID,platType, content, true, callback);
    
#endif
    return reqID;
}

int C2DXShareSDK::shareContent(C2DXPlatType platType, C2DXDictionary *content,bool useClientShare,C2DXShareResultEvent callback)
{
	reqID ++;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid
    C2DXArray *platTypes = C2DXArray::create();
	platTypes->addObject(C2DXInteger::create(platType));
    shareContentJNI(reqID, platTypes, content, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXArray *platTypes = C2DXArray::create();
    platTypes->addObject(C2DXInteger::create(platType));
    C2DXiOSShareSDK::shareContent(reqID,platType, content, useClientShare, callback);
    
#endif
	return reqID;
}

int C2DXShareSDK::oneKeyShareContent(C2DXArray *platTypes, C2DXDictionary *content, C2DXShareResultEvent callback)
{
	reqID ++;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid
    shareContentJNI(reqID, platTypes, content, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSShareSDK::oneKeyShareContent(reqID, platTypes, content, callback);
    
#endif
	return reqID;

}

int C2DXShareSDK::showShareMenu(C2DXArray *platTypes, C2DXDictionary *content, int x, int y, C2DXShareResultEvent callback)
{
    reqID ++;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Android
    onekeyShareJNI(reqID, 0, content, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSShareSDK::showShareMenu(reqID,platTypes, content, C2DXPointMake(x,y), true , callback);
    
#endif
    return reqID;
}

int C2DXShareSDK::showShareMenu(C2DXArray *platTypes, C2DXDictionary *content, int x, int y, bool useClientShare, C2DXShareResultEvent callback)
{
	reqID ++;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //Android
    onekeyShareJNI(reqID, 0, content, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSShareSDK::showShareMenu(reqID,platTypes, content, C2DXPointMake(x,y),useClientShare , callback);

#endif
	return reqID;
}


int C2DXShareSDK::showShareView(C2DXPlatType platType, C2DXDictionary *content, C2DXShareResultEvent callback)
{
    reqID ++;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Android
    onekeyShareJNI(reqID, (int) platType, content, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSShareSDK::showShareEditView(reqID,platType, content, true, callback);
    
#endif
    return reqID;
}


int C2DXShareSDK::showShareView(C2DXPlatType platType, C2DXDictionary *content, bool useClientShare, C2DXShareResultEvent callback)
{
	reqID ++;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //Android
    onekeyShareJNI(reqID, (int) platType, content, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSShareSDK::showShareEditView(reqID,platType, content, useClientShare, callback);
    
#endif
	return reqID;
}

int C2DXShareSDK::getFriendList(C2DXPlatType platType, int count, int page, C2DXGetFriendsResultEvent callback)
{
	reqID ++;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //Android
	getFriendListJNI(reqID, (int) platType, count, page, callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

    //iOS
    C2DXiOSShareSDK::getFriendList(reqID, platType,count, page, callback);

#endif
	return reqID;
}

int C2DXShareSDK::addFriend(C2DXPlatType platType, const char* account, C2DXAddFriendResultEvent callback)
{
	reqID ++;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //Android
	addFriendJNI(reqID, (int) platType, account, callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

    //iOS
    C2DXiOSShareSDK::addFriend(reqID, platType, account,callback);

#endif
	return reqID;
}

void C2DXShareSDK::toast(const char *msg)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //Android
    toastShowJNI(msg);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

    //iOS
//    C2DXiOSShareSDK::alertLog(msg);
    
#endif
}

int C2DXShareSDK::shareWithConfigurationFile(const char *contentName, C2DXPlatType platType, C2DXDictionary *customFields, C2DXShareResultEvent callback)
{
    reqID ++;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSShareSDK::shareWithConfigurationFile(reqID, contentName, platType, customFields, callback);
    
#endif
    return reqID;
}

int C2DXShareSDK::showShareMenuWithConfigurationFile(C2DXArray *platTypes, int x, int y, const char* contentName,C2DXDictionary *customFields, C2DXShareResultEvent callback)
{
    reqID ++;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSShareSDK::showShareMenuWithConfigurationFile(reqID, platTypes, C2DXPointMake(x,y), contentName, customFields, callback);
    
#endif
    return reqID;
}

int C2DXShareSDK::showShareViewWithConfigurationFile(C2DXPlatType platType,const char* contentName,C2DXDictionary *customFields, C2DXShareResultEvent callback)
{
    reqID ++;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSShareSDK::showShareEditViewWithConfigurationFile(reqID,platType,contentName, customFields, callback);
    
#endif
    return reqID;
}
