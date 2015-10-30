//
//  C2DXShareSDKTypeDef.h
//  C2DXShareSDKSample
//

#ifndef C2DXShareSDKSample_C2DXShareSDKTypeDef_h
#define C2DXShareSDKSample_C2DXShareSDKTypeDef_h

#include "cocos2d.h"
#include <stdint.h>

USING_NS_CC;

namespace cn
{
    namespace sharesdk
    {
        /**
         *	@brief	平台类型
         */
        enum C2DXPlatType
        {
        	Unknown : 0,
            SinaWeibo = 1,         /**< 新浪微博 */
            TencentWeibo = 2,      /**< 腾讯微博 */
            DouBan = 5,            /**< 豆瓣社区 */
            QZone = 6,             /**< QQ空间 */
            Renren = 7,            /**< 人人网 */
            Kaixin = 8,            /**< 开心网 */
            Pengyou = 9,           /**< 朋友网 */
            Facebook = 10,         /**< Facebook */
            Twitter = 11,          /**< Twitter */
            Evernote = 12,         /**< 印象笔记 */
            Foursquare = 13,       /**< Foursquare */
            GooglePlus = 14,       /**< Google＋ */
            Instagram = 15,        /**< Instagram */
            LinkedIn = 16,         /**< LinkedIn */
            Tumblr = 17,           /**< Tumbir */
            Mail = 18,             /**< 邮件分享 */
            SMS = 19,              /**< 短信分享 */
            AirPrint = 20,         /**< 打印 */
            Copy = 21,             /**< 拷贝 */
            WeixiSession = 22,     /**< 微信好友 */
            WeixiTimeline = 23,    /**< 微信朋友圈 */
            QQ = 24,               /**< QQ */
            Instapaper = 25,       /**< Instapaper */
            Pocket = 26,           /**< Pocket */
            YouDaoNote = 27,       /**< 有道云笔记 */
            SohuKan = 28,          /**< 搜狐随身看 */
            Pinterest = 30,        /**< Pinterest */
            Flickr = 34,           /**< Flickr */
            Dropbox = 35,          /**< Dropbox */
            VKontakte = 36,        /**< VKontakte */
            WeixiFav = 37,         /**< 微信收藏 */
            YiXinSession = 38,     /**< 易信好友 */
            YiXinTimeline = 39,    /**< 易信朋友圈 */
            YiXinFav = 40,         /**< 易信收藏 */
            MingDao : 41,          /**< 明道 */
    		Line : 42,             /**< Line */
    		WhatsApp : 43,         /**< Whats App */
    		KakaoTalk : 44,        /**< KakaoTalk */
    		KakaoStory : 45,       /**< KakaoStory */ 
    		FacebookMessenger : 46,/**< FacebookMessenger */
    		Bluetooth : 48,        /**< Bluetooth */
    		Alipay : 50,           /**< Alipay */
    		WechatPlatform : 997,  /**< Wechat Series */
    		QQPlatform : 998,	   /**< QQ Series */
    		Any : 999 			   /**< 任意平台 */
        };
        
        /**
         *	@brief	内容类型
         */
        enum C2DXContentType
        {
            C2DXContentTypeText = 0, /**< 文本 */
            C2DXContentTypeImage = 1, /**< 图片 */
            C2DXContentTypeNews = 2, /**< 新闻 */
            C2DXContentTypeMusic = 3, /**< 音乐 */
            C2DXContentTypeVideo = 4, /**< 视频 */
            C2DXContentTypeApp = 5, /**< 应用,仅供微信使用 */
            C2DXContentTypeNonGif = 6, /**< 非Gif消息,仅供微信使用 */
            C2DXContentTypeGif = 7, /**< Gif消息,仅供微信使用 */
            C2DXContentTypeFile = 8 /**< 文件消息,仅供微信使用 */
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
        typedef void(*C2DXAuthResultEvent) (int reqID, C2DXResponseState state, C2DXPlatType platType, __Dictionary *res);
        
        /**
         *	@brief	获取用户信息回调事件
         */
        typedef void(*C2DXGetUserInfoResultEvent) (int reqID, C2DXResponseState state, C2DXPlatType platType, __Dictionary *res);
        
        /**
         *	@brief	分享回调事件
         */
        typedef void(*C2DXShareResultEvent) (int reqID, C2DXResponseState state, C2DXPlatType platType, __Dictionary *res);

        /**
         *	@brief	关注好友回调事件
         */
        typedef void(*C2DXAddFriendResultEvent) (int reqID, C2DXResponseState state, C2DXPlatType platType,  __Dictionary *res);
		
        /**
         *	@brief	获取好友列表回调事件
         */
        typedef void(*C2DXGetFriendsResultEvent) (int reqID, C2DXResponseState state, C2DXPlatType platType,  __Dictionary *res);
    }
}

#endif
