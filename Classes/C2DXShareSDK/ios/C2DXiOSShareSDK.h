//
//  C2DXiOSShareSDK.h
//  HelloWorldDemo
//
//  Created by 刘 靖煌 on 15-11-27.
//  Copyright © 2015年 mob.com. All rights reserved.
//

#ifndef __HelloWorldDemo__C2DXiOSShareSDK__
#define __HelloWorldDemo__C2DXiOSShareSDK__

#include <stdio.h>
#include "cocos2d.h"
#include "C2DXShareSDKTypeDef.h"

namespace cn
{
    namespace sharesdk
    {
        /**
         *	@brief	ShareSDK 简洁版(iOS)
         */
        class C2DXiOSShareSDK
        {
        
        public:
            /**
             *	@brief	初始化ShareSDK
             *
             *	@param 	appKey 	appKey
             *	@param 	configInfo 	平台配置信息
             */
            static void registerAppAndSetPlatformConfig(const char *appKey, C2DXDictionary *configInfo);
            
            /**
             *	@brief	用户授权
             *
             *	@param 	reqID 	流水号
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
            static bool hasAutorized(C2DXPlatType platType);
            
            /**
             *	@brief	是否安装客户端
             *
             *	@param 	platType 	平台类型
             *
             *	@return	true 已安装， false 尚未安装
             */
            static bool isClientInstalled(C2DXPlatType platType);
            
            /**
             *	@brief	获取用户信息
             *
             *	@param 	platType 	平台类型
             *	@param 	callback 	回调方法
             */
            static void getUserInfo(int reqID,C2DXPlatType platType, C2DXGetUserInfoResultEvent callback);
            
//            /**
//             *	@brief	获取用户授权信息
//             *
//             *	@param 	platType 	平台类型
//             *	@param 	callback 	回调方法
//             */
//            static void getAuthInfo(C2DXPlatType platType);
            
            /**
             *	@brief	分享内容
             *
             *	@param 	platType 	平台类型
             *	@param 	content 	分享内容
             *	@param 	callback 	回调方法
             */
            static void shareContent(int reqID,C2DXPlatType platType, C2DXDictionary *content, C2DXShareResultEvent callback);

            /**
             *	@brief	一键分享内容
             *
             *	@param 	reqID 	流水号
             *	@param 	platTypes 	平台类型列表
             *	@param 	content 	分享内容
             *	@param 	callback 	回调方法
             */
            static void oneKeyShareContent(int reqID,C2DXArray *platTypes, C2DXDictionary *content, C2DXShareResultEvent callback);
            
            /**
             *	@brief	显示分享菜单
             *
             *	@param 	reqID 	流水号
             *	@param 	platTypes 	平台类型列表
             *	@param 	content 	分享内容
             *	@param 	pt          弹出分享菜单参位置，仅用于设置iPad分享菜单弹出
             *	@param 	callback 	回调方法
             */
            static void showShareMenu(int reqID,C2DXArray *platTypes, C2DXDictionary *content, C2DXPoint pt, C2DXShareResultEvent callback);
            
            /**
             *	@brief	显示分享编辑框
             *
             *	@param 	reqID 	流水号
             *	@param 	platType 	平台类型
             *	@param 	content 	分享内容
             *	@param 	callback 	回调方法
             */
            static void showShareEditView(int reqID,C2DXPlatType platType, C2DXDictionary *content, C2DXShareResultEvent callback);
            
            /**
             *	@brief	获取好友列表
             *
             *	@param 	reqID 	流水号
             *	@param 	platType 	平台类型
             *	@param 	content 	分享内容
             *	@param 	callback 	回调方法
             */
            static void getFriendList(int reqID,C2DXPlatType platType,int count, int page, C2DXAddFriendResultEvent callback);
            
            /**
             *	@brief	显示分享编辑框
             *
             *	@param 	reqID 	流水号
             *	@param 	platType 	平台类型
             *	@param 	content 	分享内容
             *	@param 	callback 	回调方法
             */
            static void addFriend(int reqID,C2DXPlatType platType,const char* account,C2DXGetFriendsResultEvent callback);
            
            /**
             *	@brief	显示分享编辑框
             */
            static void alertLog(const char *msg);
            
            /**
             *  使用配置文件的方式分享
             *
             *  @param contentName  ShareContent.xml内<Content>标签name属性的值
             *  @param platType     平台类型
             *  @param customFields 自定义字段
             *  @param callback     状态变更回调处理
             */
            static void shareWithConfigurationFile(int reqID, const char *contentName, C2DXPlatType platType, C2DXDictionary *customFields, C2DXShareResultEvent callback);
            
            /**
             *	@brief	显示分享菜单
             *
             *	@param 	reqID 	流水号
             *	@param 	platTypes 	平台类型列表
             *	@param 	content 	分享内容
             *	@param 	pt          弹出分享菜单参位置，仅用于设置iPad分享菜单弹出
             *  @param contentName  ShareContent.xml内<Content>标签name属性的值
             *  @param customFields 自定义字段
             *	@param 	callback 	回调方法
             */
            static void showShareMenuWithConfigurationFile(int reqID,C2DXArray *platTypes, C2DXPoint pt, const char *contentName, C2DXDictionary *customFields, C2DXShareResultEvent callback);
            
            /**
             *	@brief	显示分享编辑框
             *
             *	@param 	reqID 	流水号
             *	@param 	platType 	平台类型
             *	@param 	content 	分享内容
             *  @param contentName  ShareContent.xml内<Content>标签name属性的值
             *  @param customFields 自定义字段
             *	@param 	callback 	回调方法
             */
            static void showShareEditViewWithConfigurationFile(int reqID,C2DXPlatType platType, const char *contentName, C2DXDictionary *customFields,C2DXShareResultEvent callback);
        };
    }
}

#endif /* defined(__HelloWorldDemo__C2DXiOSShareSDK__) */


