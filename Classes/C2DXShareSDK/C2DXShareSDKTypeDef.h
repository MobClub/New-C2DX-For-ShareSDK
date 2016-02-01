//
//  C2DXShareSDKTypeDef.h
//  C2DXShareSDKSample
//
//  Copyright © 2015年 mob.com. All rights reserved.
//

#ifndef C2DXShareSDKSample_C2DXShareSDKTypeDef_h
#define C2DXShareSDKSample_C2DXShareSDKTypeDef_h

#include "cocos2d.h"
#include <stdint.h>

USING_NS_CC;

#if COCOS2D_VERSION < 0x00030000

#define C2DXDictionary CCDictionary
#define C2DXArray CCArray
#define C2DXString CCString
#define C2DXPoint CCPoint
#define C2DXDouble CCDouble

#define C2DXInteger CCInteger
#define C2DXObject CCObject
#define C2DXPointMake(x,y) CCPointMake(x, y)
#define C2DXObjectAtIndex(i) objectAtIndex(i)

#else

#define C2DXDictionary __Dictionary
#define C2DXArray __Array
#define C2DXString __String
#define C2DXPoint cocos2d::Point
#define C2DXDouble __Double

#define C2DXInteger __Integer
#define C2DXObject Ref
#define C2DXPointMake(x,y) cocos2d::Point{static_cast<float>(x), static_cast<float>(y)}
#define C2DXObjectAtIndex(i) getObjectAtIndex(i)

#endif

namespace cn
{
    namespace sharesdk
    {
        /**
         *	@brief	平台类型
         */
        enum C2DXPlatType
        {
        	C2DXPlatTypeUnknown = 0,
            C2DXPlatTypeSinaWeibo = 1,         /**< 新浪微博 */
            C2DXPlatTypeTencentWeibo = 2,      /**< 腾讯微博 */
            C2DXPlatTypeDouBan = 5,            /**< 豆瓣社区 */
            C2DXPlatTypeQZone = 6,             /**< QQ空间 */
            C2DXPlatTypeRenren = 7,            /**< 人人网 */
            C2DXPlatTypeKaixin = 8,            /**< 开心网 */
            C2DXPlatTypePengyou = 9,           /**< 朋友网 */
            C2DXPlatTypeFacebook = 10,         /**< Facebook */
            C2DXPlatTypeTwitter = 11,          /**< Twitter */
            C2DXPlatTypeEvernote = 12,         /**< 印象笔记 */
            C2DXPlatTypeFoursquare = 13,       /**< Foursquare */
            C2DXPlatTypeGooglePlus = 14,       /**< Google＋ */
            C2DXPlatTypeInstagram = 15,        /**< Instagram */
            C2DXPlatTypeLinkedIn = 16,         /**< LinkedIn */
            C2DXPlatTypeTumblr = 17,           /**< Tumbir */
            C2DXPlatTypeMail = 18,             /**< 邮件分享 */
            C2DXPlatTypeSMS = 19,              /**< 短信分享 */
            C2DXPlatTypeAirPrint = 20,         /**< 打印 */
            C2DXPlatTypeCopy = 21,             /**< 拷贝 */
            C2DXPlatTypeWeChat = 22,           /**< 微信好友 */
            C2DXPlatTypeWeChatMoments = 23,    /**< 微信朋友圈 */
            C2DXPlatTypeQQ = 24,               /**< QQ */
            C2DXPlatTypeInstapaper = 25,       /**< Instapaper */
            C2DXPlatTypePocket = 26,           /**< Pocket */
            C2DXPlatTypeYouDaoNote = 27,       /**< 有道云笔记 */
            C2DXPlatTypeSohuKan = 28,          /**< 搜狐随身看 */
            C2DXPlatTypePinterest = 30,        /**< Pinterest */
            C2DXPlatTypeFlickr = 34,           /**< Flickr */
            C2DXPlatTypeDropbox = 35,          /**< Dropbox */
            C2DXPlatTypeVKontakte = 36,        /**< VKontakte */
            C2DXPlatTypeWeChatFavorites = 37,  /**< 微信收藏 */
            C2DXPlatTypeYiXinSession = 38,     /**< 易信好友 */
            C2DXPlatTypeYiXinTimeline = 39,    /**< 易信朋友圈 */
            C2DXPlatTypeYiXinFav = 40,         /**< 易信收藏 */
            C2DXPlatTypeMingDao = 41,          /**< 明道 */
    		C2DXPlatTypeLine = 42,             /**< Line */
    		C2DXPlatTypeWhatsApp = 43,         /**< Whats App */
    		C2DXPlatTypeKakaoTalk = 44,        /**< KakaoTalk */
    		C2DXPlatTypeKakaoStory = 45,       /**< KakaoStory */ 
    		C2DXPlatTypeFacebookMessenger = 46,/**< FacebookMessenger */
    		C2DXPlatTypeBluetooth = 48,        /**< Bluetooth */
    		C2DXPlatTypeAlipay = 50,           /**< Alipay */
    		C2DXPlatTypeWechatPlatform = 997,  /**< Wechat Series */
    		C2DXPlatTypeQQPlatform = 998,	   /**< QQ Series */
    		C2DXPlatTypeAny = 999 			   /**< 任意平台 */
        };

        /**
         *	@brief	内容类型
         */
        enum C2DXContentType
        {
            C2DXContentTypeAuto = 0,  /**< 自动判断发送类型，避免部分平台不支持某些类型，仅供iOS端使用 */
            C2DXContentTypeText = 1, /**< 文本 */
            C2DXContentTypeImage = 2, /**< 图片 */
            C2DXContentTypeWebPage = 4, /**< 网页 */
            C2DXContentTypeMusic = 5, /**< 音乐 */
            C2DXContentTypeVideo = 6, /**< 视频 */
            C2DXContentTypeApp = 7, /**< 应用,仅供微信使用 */
            C2DXContentTypeFile = 8, /**< 文件消息,仅供微信使用 */
            C2DXContentTypeEmoji = 9 /**< 表情消息,仅供微信使用 */
        };
        
        /**
         *	@brief	返回状态
         */
        enum C2DXResponseState
        {
            C2DXResponseStateBegin = 0, /**< 开始 */
            C2DXResponseStateSuccess = 1, /**< 成功 */
            C2DXResponseStateFail = 2, /**< 失败 */
            C2DXResponseStateCancel = 3 /**< 取消 */
        };
                
        /**
         *	@brief	授权回调事件
         */
        typedef void(*C2DXAuthResultEvent) (int reqID, C2DXResponseState state, C2DXPlatType platType, C2DXDictionary *res);
        
        /** 
         *	@brief	获取用户信息回调事件
         */
        typedef void(*C2DXGetUserInfoResultEvent) (int reqID, C2DXResponseState state, C2DXPlatType platType, C2DXDictionary *res);
        
        /**
         *	@brief	分享回调事件
         */
        typedef void(*C2DXShareResultEvent) (int reqID, C2DXResponseState state, C2DXPlatType platType, C2DXDictionary *res);

        /**
         *	@brief	关注好友回调事件
         */
        typedef void(*C2DXAddFriendResultEvent) (int reqID, C2DXResponseState state, C2DXPlatType platType,  C2DXDictionary *res);
		
        /**
         *	@brief	获取好友列表回调事件
         */
        typedef void(*C2DXGetFriendsResultEvent) (int reqID, C2DXResponseState state, C2DXPlatType platType,  C2DXDictionary *res);
    }
}

#endif
