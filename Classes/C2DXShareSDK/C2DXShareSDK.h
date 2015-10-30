//
//  C2DXShareSDK.h
//  C2DXShareSDKSample
//
//  Created by 冯 鸿杰 on 13-12-17.
//
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
            static void rigisterAppAndSetPlatformConfig(const char *appKey, __Dictionary *configInfo);
            
            /**
             *	@brief	用户授权
             *
             *	@param 	platType 	平台类型
             *	@param 	callback 	回调方法
             */
            static void authorize(int reqID, C2DXPlatType platType, C2DXAuthResultEvent callback);
            
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

			static bool isClientValid(C2DXPlatType platType);
            
            /**
             *	@brief	获取用户信息
             *
             *	@param 	platType 	平台类型
             *	@param 	callback 	回调方法
             */
            static void getUserInfo(int reqID, C2DXPlatType platType, C2DXGetUserInfoResultEvent callback);


            static __Dictionary* getAuthInfo(C2DXPlatType platType);

            /**
             *	@brief	分享内容
             *
             *	@param 	platType 	平台类型
             *	@param 	content 	分享内容
             *	@param  isSSO       是否SSO授权
             *	@param 	callback 	回调方法
             */
            static void shareContent(int reqID, C2DXPlatType platType, __Dictionary *content, C2DXShareResultEvent callback);
            
            /**
             *	@brief	一键分享内容
             *
             *	@param 	platTypes 	平台类型列表
             *	@param 	content 	分享内容
             *	@param 	callback 	回调方法
             */
            static void shareContent(int reqID, __Array *platTypes, __Dictionary *content, C2DXShareResultEvent callback);
            
            /**
             *	@brief	显示分享菜单
             *
             *	@param 	platTypes 	平台类型列表
             *	@param 	content 	分享内容
             *	@param 	callback 	回调方法
             */
            static void showShareMenu(int reqID, __Array *platTypes, __Dictionary *content, int x, int y, C2DXShareResultEvent callback);
            
           
            /**
             *	@brief	显示分享视图
             *
             *	@param 	platType 	平台类型
             *	@param 	content 	分享内容
             *	@param 	callback 	回调方法
             */
            static void showShareView(int reqID, C2DXPlatType platType, __Dictionary *content, C2DXShareResultEvent callback);

            /**
             *	@brief	获得好友列表
             *
             *	@param 	platType 	平台类型
             *	@param 	count 	              每页数量
             *	@param 	page 		页数
             *	@param  account     用户名
             */
            static void getFriendList(int reqID, C2DXPlatType platType, int count, int page, C2DXGetFriendsResultEvent callback);

            /**
             *	@brief	关注好友
             *
             *	@param 	platType 	平台类型
             *	@param 	account 	呢称
             */
            static void addFriend(int reqID, C2DXPlatType platType, const char* account, C2DXAddFriendResultEvent callback);

            /**
             * @brief 显示一个消息
             * @param msg 消息内容
             */
            static void toast(const char *msg);

        };
    }
}

#endif /* defined(__C2DXShareSDKSample__C2DXShareSDK__) */
