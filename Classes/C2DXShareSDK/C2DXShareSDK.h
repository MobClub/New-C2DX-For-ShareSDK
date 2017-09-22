//
//  C2DXShareSDK.h
//  C2DXShareSDKSample
//
//  Copyright © 2015年 mob.com. All rights reserved.
//

#ifndef __C2DXShareSDKSample__C2DXShareSDK__
#define __C2DXShareSDKSample__C2DXShareSDK__

#include <iostream>
#include "cocos2d.h"
#include "C2DXShareSDKTypeDef.h"

USING_NS_CC;

namespace cn
{
    namespace sharesdk
    {
		class PlatId
		{
			public:
				static const char* Unknown;
            	static const char* SinaWeibo;         
            	static const char* TencentWeibo;  
            	static const char* DouBan;
           		static const char* QZone; 
            	static const char* Renren;
            	static const char* Kaixin;
            	static const char* Pengyou;
            	static const char* Facebook;
            	static const char* Twitter;
            	static const char* Evernote;
            	static const char* Foursquare;
            	static const char* GooglePlus;
            	static const char* Instagram;
            	static const char* LinkedIn;
            	static const char* Tumblr;        
           		static const char* Mail;             
            	static const char* SMS;              
            	static const char* AirPrint;         
            	static const char* Copy;             
            	static const char* WeixiSession;     
            	static const char* WeixiTimeline; 
            	static const char* QQ;            
            	static const char* Instapaper;       
            	static const char* Pocket;           
            	static const char* YouDaoNote;
            	static const char* Pinterest;   
            	static const char* Flickr;      
            	static const char* Dropbox;    
            	static const char* VKontakte;   
            	static const char* WeixiFav;     
            	static const char* YiXinSession;    
            	static const char* YiXinTimeline; 
            	static const char* YiXinFav;  
            	static const char* MingDao;    
    			static const char* Line;      
    			static const char* WhatsApp;  
    			static const char* KakaoTalk;   
    			static const char* KakaoStory;   
    			static const char* FacebookMessenger;
    			static const char* Bluetooth;
    			static const char* Alipay;
                static const char* KakaoPlatform;
                static const char* EvernotePlatform;
    			static const char* WechatPlatform;
    			static const char* QQPlatform;
    			static const char* Any; 
		};

        /**
         *	@brief	ShareSDK
         */
        class C2DXShareSDK
        {
        public:
            /**
             *	@brief	设置平台配置信息
             *
             *	@param 	platType 	平台类型
             *	@param 	configInfo 	配置信息
             */
            static void registerAppAndSetPlatformConfig(const char *appKey, C2DXDictionary *configInfo);
            
            /**
             *	@brief	用户授权
             *
             *	@param 	platType 	平台类型
             *	@param 	callback 	回调方法
             *	@return 	reqID 	流水号
             */
            static int authorize(C2DXPlatType platType, C2DXAuthResultEvent callback);
            
            /**
             *	@brief	取消用户授权
             *
             *	@param 	platType 	平台类型
             */
            static void cancelAuthorize(C2DXPlatType platType);

            /**
             *	@brief	用户是否授权
             *
             *	@param 	platType 	平台类型
             *
             *	@return	true 已授权， false 尚未授权
             */
            static bool isAuthorizedValid(C2DXPlatType platType);
            
            /**
             *	@brief	是否安装客户端
             *
             *	@param 	platType 	平台类型
             *
             *	@return	true 已安装客户端， false 尚未安装客户端
             */
			static bool isClientValid(C2DXPlatType platType);
            
            /**
             *	@brief	获取用户信息
             *
             *	@param 	platType 	平台类型
             *	@param 	callback 	回调方法
             *	@return 	reqID 	流水号
             */
            static int getUserInfo(C2DXPlatType platType, C2DXGetUserInfoResultEvent callback);

            /**
             *	@brief	获取用户授权信息
             *
             *	@param 	platType 	平台类型
             *	@param 	callback 	回调方法
             */
            static C2DXDictionary* getAuthInfo(C2DXPlatType platType);
            
            
            /**
             *	@brief	分享内容
             *
             *	@param 	platType 	平台类型
             *	@param 	content 	分享内容
             *	@param 	callback 	回调方法
             *	@return 	reqID 	流水号
             */
            static int shareContent(C2DXPlatType platType, C2DXDictionary *content, C2DXShareResultEvent callback);

            /**
             *	@brief	分享内容
             *
             *	@param 	platType 	平台类型
             *	@param 	content 	分享内容
             *  @param  useClientShare 是否优先使用客户端分享
             *	@param 	callback 	回调方法
             *	@return 	reqID 	流水号
             */
            static int shareContent(C2DXPlatType platType, C2DXDictionary *content,bool useClientShare, C2DXShareResultEvent callback);
            
            
            /**
             *	@brief	分享内容
             *
             *	@param 	platType 	平台类型
             *	@param 	content 	分享内容
             *	@param 	callback 	回调方法
             *	@return 	reqID 	流水号
             */
            static int oneKeyShareContent(C2DXArray *platTypes, C2DXDictionary *content, C2DXShareResultEvent callback);
            
            /**
             *	@brief	显示分享菜单
             *
             *	@param 	platTypes 	平台类型列表，值可以为NULL，此时显示所有初始化的平台
             *	@param 	content 	分享内容
             *	@param 	callback 	回调方法
             *	@return 	reqID 	流水号
             */
            static int showShareMenu(C2DXArray *platTypes, C2DXDictionary *content, int x, int y, C2DXShareResultEvent callback);
            
            /**
             *	@brief	显示分享菜单
             *
             *	@param 	platTypes 	平台类型列表，值可以为NULL，此时显示所有初始化的平台
             *	@param 	content 	分享内容
             *  @param  useClientShare 是否优先使用客户端进行分享
             *	@param 	callback 	回调方法
             *	@return 	reqID 	流水号
             */
            static int showShareMenu(C2DXArray *platTypes, C2DXDictionary *content, int x, int y, bool useClientShare, C2DXShareResultEvent callback);
            
            /**
             *	@brief	显示分享视图
             *
             *	@param 	platType 	平台类型
             *	@param 	content 	分享内容
             *	@param 	callback 	回调方法
             *	@return 	reqID 	流水号
             */
            static int showShareView(C2DXPlatType platType, C2DXDictionary *content, C2DXShareResultEvent callback);
            
            /**
             *	@brief	显示分享视图
             *
             *	@param 	platType 	平台类型
             *	@param 	content 	分享内容
             *  @param  useClientShare 是否优先使用客户端分享
             *	@param 	callback 	回调方法
             *	@return 	reqID 	流水号
             */
            static int showShareView(C2DXPlatType platType, C2DXDictionary *content, bool useClientShare, C2DXShareResultEvent callback);

            /**
             *	@brief	获得好友列表
             *
             *	@param 	platType 	平台类型
             *	@param 	count 	              每页数量
             *	@param 	page 		页数
             *	@param  account     用户名
             *	@return 	reqID 	流水号
             */
            static int getFriendList(C2DXPlatType platType, int count, int page, C2DXGetFriendsResultEvent callback);

            /**
             *	@brief	关注好友
             *
             *	@param 	platType 	平台类型
             *	@param 	account 	呢称
             *	@return 	reqID 	流水号
             */
            static int addFriend(C2DXPlatType platType, const char* account, C2DXAddFriendResultEvent callback);

            /**
             * @brief 显示一个消息
             * @param msg 消息内容
             */
            static void toast(const char *msg);
            
            /**
             *  使用配置文件的方式分享
             *
             *  @param contentName  ShareContent.xml内<Content>标签name属性的值
             *  @param platType     平台类型
             *  @param customFields 自定义字段
             *  @param callback     状态变更回调处理
             *
             *  @return reqID 	流水号
             */
            static int shareWithConfigurationFile(const char* contentName, C2DXPlatType platType, C2DXDictionary *customFields, C2DXShareResultEvent callback);
            
            /**
             *	@brief	显示分享菜单
             *
             *	@param 	platTypes 	平台类型列表，值可以为NULL，此时显示所有初始化的平台
             *  @param contentName  ShareContent.xml内<Content>标签name属性的值
             *  @param customFields 自定义字段
             *	@param 	callback 	回调方法
             *	@return 	reqID 	流水号
             */
            static int showShareMenuWithConfigurationFile(C2DXArray *platTypes, int x, int y, const char* contentName,C2DXDictionary *customFields, C2DXShareResultEvent callback);
            
            /**
             *	@brief	显示分享视图
             *
             *	@param 	platType 	平台类型
             *  @param contentName  ShareContent.xml内<Content>标签name属性的值
             *  @param customFields 自定义字段
             *	@param 	callback 	回调方法
             *	@return 	reqID 	流水号
             */
            static int showShareViewWithConfigurationFile(C2DXPlatType platType, const char* contentName,C2DXDictionary *customFields, C2DXShareResultEvent callback);
        };
    }
}

#endif
