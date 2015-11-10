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
const char* PlatId::QQ = "24";              /**< QQ */
const char* PlatId::Instapaper = "25";       /**< Instapaper */
const char* PlatId::Pocket = "26";           /**< Pocket */
const char* PlatId::YouDaoNote = "27";       /**< 有道云笔记 */
const char* PlatId::SohuKan = "28";          /**< 搜狐随身看 */
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
const char* PlatId::WechatPlatform = "997";  /**< Wechat Series */
const char* PlatId::QQPlatform = "998";	   /**< QQ Series */
const char* PlatId::Any = "999"; 			   /**< 任意平台 */


void C2DXShareSDK::rigisterAppAndSetPlatformConfig(const char *appKey, __Dictionary *configInfo)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //TODO: Andorid
    // This is not a necessary method for Android, you can setup your platform configs more efficiently in "assets/ShareSDK.xml"
    rigisterAppAndSetPlatformConfigJNI(appKey, configInfo);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

void C2DXShareSDK::authorize(int reqID, C2DXPlatType platType, C2DXAuthResultEvent callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //TODO: Andorid
    authorizeJNI(reqID, (int)platType, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

void C2DXShareSDK::cancelAuthorize(C2DXPlatType platType)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //TODO: Andorid
    cancelAuthorizeJNI((int)platType);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

bool C2DXShareSDK::isAuthorizedValid(C2DXPlatType platType)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //TODO: Andorid
    return isAuthorizedValidJNI((int)platType);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
    
    return false;
}

bool C2DXShareSDK::isClientValid(C2DXPlatType platType)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //TODO: Andorid
    return isClientValidJNI((int)platType);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS    
    //TODO: iOS
    
#endif
    
    return false;
}


void C2DXShareSDK::getUserInfo(int reqID, C2DXPlatType platType, C2DXGetUserInfoResultEvent callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //TODO: Andorid
    getUserInfoJNI(reqID, (int)platType, callback);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

__Dictionary* C2DXShareSDK::getAuthInfo(C2DXPlatType platType)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //TODO: Andorid
    //return getAuthInfo((int)platType);
    return getAuthInfoJNI((int)platType);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

    //TODO: iOS


#endif
}

void C2DXShareSDK::shareContent(int reqID, C2DXPlatType platType, __Dictionary *content, C2DXShareResultEvent callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //TODO: Andorid
    __Array *platTypes = __Array::create();
	platTypes->addObject(Integer::create(platType));
    shareContentJNI(reqID, platTypes, content, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

void C2DXShareSDK::shareContent(int reqID, __Array *platTypes, __Dictionary *content, C2DXShareResultEvent callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //TODO: Andorid
    shareContentJNI(reqID, platTypes, content, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

void C2DXShareSDK::showShareMenu(int reqID, __Array *platTypes, __Dictionary *content, int x, int y, C2DXShareResultEvent callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //TODO: Android
    onekeyShareJNI(reqID, 0, content, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

void C2DXShareSDK::showShareView(int reqID, C2DXPlatType platType, __Dictionary *content, C2DXShareResultEvent callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //TODO: Android
    onekeyShareJNI(reqID, (int) platType, content, callback);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //TODO: iOS
    
#endif
}

void C2DXShareSDK::getFriendList(int reqID, C2DXPlatType platType, int count, int page, C2DXGetFriendsResultEvent callback){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //TODO: Android
	getFriendListJNI(reqID, (int) platType, count, page, callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

    //TODO: iOS
    //

#endif
}

void C2DXShareSDK::addFriend(int reqID, C2DXPlatType platType, const char* account, C2DXAddFriendResultEvent callback){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //TODO: Android
	addFriendJNI(reqID, (int) platType, account, callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

    //TODO: iOS
    //

#endif
}

void C2DXShareSDK::toast(const char *msg)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    //TODO: Android
    toastShowJNI(msg);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

    //TODO: iOS

#endif
}
