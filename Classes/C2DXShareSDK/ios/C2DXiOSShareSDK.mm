//
//  C2DXiOSShareSDK.cpp
//  HelloWorldDemo
//
//  Created by 刘 靖煌 on 15-11-27.
//  Copyright © 2015年 mob.com. All rights reserved.
//

#include "C2DXiOSShareSDK.h"

#import <ShareSDK/ShareSDK.h>
#import <ShareSDKConnector/ShareSDKConnector.h>
#import <ShareSDKUI/ShareSDKUI.h>
#import <ShareSDKExtension/ShareSDK+Extension.h>
#import <ShareSDKExtension/SSEShareHelper.h>
#import <ShareSDKExtension/SSEFriendsPaging.h>
#import <MOBFoundation/MOBFRegex.h>
#import <ShareSDK/NSMutableDictionary+SSDKShare.h>

#import <ShareSDK/ShareSDK+Base.h>
#import <ShareSDKConfigFile/ShareSDK+XML.h>


static UIView *_refView = nil;

using namespace cn::sharesdk;

#pragma mark - tools

/**
 *	@brief	转换NSDictionary为C2DXDictionary类型
 *
 *	@param 	dict 	字典
 *
 *	@return	字典类型
 */
C2DXDictionary* convertNSDictToCCDict(NSDictionary *dict);

/**
 *	@brief	转换C2DXDictionary为NSDictionary类型
 *
 *	@param 	dict 	字典
 *
 *	@return	字典类型
 */
NSMutableDictionary* convertC2DXDictionaryToNSDictionary(C2DXDictionary *Dictionary);

/**
 *	@brief	转换NSString为C2DXString类型
 *
 *	@param 	string 	字符串
 *
 *	@return	字符类型
 */
C2DXString* convertNSStringToC2DXString(NSString *string);

/**
 *	@brief	转换C2DXString为NSString类型
 *
 *	@param 	string 	字符串
 *
 *	@return	字符类型
 */
NSString* convertC2DXStringToNSString(C2DXString *String);

/**
 *	@brief	转换NSArray为C2DXArray类型
 *
 *	@param 	array 	数组
 *
 *	@return	数组类型
 */
C2DXArray* convertNSArrayToC2DXArray(NSArray *array);

/**
 *	@brief	转换C2DXArray为NSArray类型
 *
 *	@param 	array 	数组
 *
 *	@return	数组类型
 */
NSArray* convertC2DXArrayToNSArray(C2DXArray *Array);

C2DXDictionary* convertNSDictToCCDict(NSDictionary *dict)
{
    if (dict)
    {
        C2DXDictionary *ccDict = C2DXDictionary::create();
        NSArray *allKeys = [dict allKeys];
        for (int i = 0; i < [allKeys count]; i++)
        {
            NSString *key = [allKeys objectAtIndex:i];
            id value = [dict objectForKey:key];
            
            if ([value isKindOfClass:[NSString class]])
            {
                C2DXString *strValue = convertNSStringToC2DXString(value);
                if (strValue)
                {
                    ccDict -> setObject(strValue, [key UTF8String]);
                }
            }
            else if ([value isKindOfClass:[NSNumber class]])
            {
                C2DXString *strValue = convertNSStringToC2DXString([NSString stringWithFormat:@"%@", value]);
                if (strValue)
                {
                    ccDict -> setObject(strValue, [key UTF8String]);
                }
            }
            else if ([value isKindOfClass:[NSDate class]])
            {
                ccDict -> setObject(C2DXDouble::create([value timeIntervalSince1970] * 1000), [key UTF8String]);
            }
            else if ([value isKindOfClass:[NSDictionary class]])
            {
                C2DXDictionary *dictValue = convertNSDictToCCDict(value);
                if (dictValue)
                {
                    ccDict -> setObject(dictValue, [key UTF8String]);
                }
            }
            else if ([value isKindOfClass:[NSArray class]])
            {
                C2DXArray *arrValue = convertNSArrayToC2DXArray(value);
                if (arrValue)
                {
                    ccDict -> setObject(arrValue, [key UTF8String]);
                }
            }
        }
        return ccDict;
    }
    
    return NULL;
}

NSMutableDictionary * convertC2DXDictionaryToNSDictionary(C2DXDictionary * Dictionary)
{
    if (Dictionary)
    {
        NSMutableDictionary *dict = [NSMutableDictionary dictionary];
        C2DXArray *allkeys = Dictionary -> allKeys();
        
        if (allkeys != NULL)
        {
            for (int i = 0; i < allkeys -> count(); i ++)
            {
                C2DXString * key = dynamic_cast<C2DXString *> (allkeys -> C2DXObjectAtIndex(i));
                C2DXObject * value = Dictionary -> objectForKey(key -> getCString());
                
                if (dynamic_cast<C2DXString*>(value) != NULL)
                {
                    NSString *strValue = convertC2DXStringToNSString(dynamic_cast<C2DXString*>(value) );
                    if (strValue)
                    {
                        [dict setObject:strValue
                                 forKey:[NSString stringWithCString:key -> getCString()
                                                           encoding:NSUTF8StringEncoding]];
                    }
                }
                else if (dynamic_cast<C2DXDictionary*>(value) != NULL)
                {
                    NSMutableDictionary *dictValue = convertC2DXDictionaryToNSDictionary(dynamic_cast<C2DXDictionary*>(value));
                    if (dictValue)
                    {
                        [dict setObject:dictValue
                                 forKey:[NSString stringWithCString:key -> getCString()
                                                           encoding:NSUTF8StringEncoding]];
                    }
                }
                else if (dynamic_cast<C2DXArray*>(value) != NULL)
                {
                    NSArray *arrayValue = convertC2DXArrayToNSArray(dynamic_cast<C2DXArray*>(value));
                    if (arrayValue)
                    {
                        [dict setObject:arrayValue
                                 forKey:[NSString stringWithCString:key -> getCString()
                                                           encoding:NSUTF8StringEncoding]];
                    }
                }
            }
        }
        return  dict;
    }
    return NULL;
}

C2DXString* convertNSStringToC2DXString(NSString *string)
{
    if (string)
    {
        return C2DXString::create([string cStringUsingEncoding:NSUTF8StringEncoding]);
    }
    
    return NULL;
}

NSString* convertC2DXStringToNSString(C2DXString *string)
{
    if (string)
    {
        return [NSString stringWithCString:string -> getCString() encoding:NSUTF8StringEncoding];
    }
    return NULL;
}

C2DXArray* convertNSArrayToC2DXArray(NSArray *array)
{
    if (array)
    {
        C2DXArray *ccArray = C2DXArray::create();
        
        for (int i = 0; i < [array count]; i++)
        {
            id value = [array objectAtIndex:i];
            if ([value isKindOfClass:[NSString class]])
            {
                C2DXString *strValue = convertNSStringToC2DXString(value);
                if (strValue)
                {
                    ccArray -> addObject(strValue);
                }
            }
            else if ([value isKindOfClass:[NSNumber class]])
            {
                C2DXString *strValue = convertNSStringToC2DXString([NSString stringWithFormat:@"%@", value]);
                if (strValue)
                {
                    ccArray -> addObject(strValue);
                }
            }
            else if ([value isKindOfClass:[NSDate class]])
            {
                ccArray -> addObject(C2DXDouble::create([value timeIntervalSince1970] * 1000));
            }
            else if ([value isKindOfClass:[NSDictionary class]])
            {
                C2DXDictionary *dictValue = convertNSDictToCCDict(value);
                if (dictValue)
                {
                    ccArray -> addObject(dictValue);
                }
            }
            else if ([value isKindOfClass:[NSArray class]])
            {
                C2DXArray *arrayValue = convertNSArrayToC2DXArray(value);
                if (arrayValue)
                {
                    ccArray -> addObject(arrayValue);
                }
            }
        }
        
        return ccArray;
    }
    
    return NULL;
}

NSArray* convertC2DXArrayToNSArray(C2DXArray *array)
{
    if (array)
    {
        NSMutableArray *nsArray = [NSMutableArray array];
        for (int i = 0; i < array -> count(); i++)
        {
            C2DXObject * value = array -> C2DXObjectAtIndex(i);
            if (dynamic_cast<C2DXString*>(value) != NULL)
            {
                NSString *strValue = convertC2DXStringToNSString(dynamic_cast<C2DXString*>(value) );
                if (strValue)
                {
                    [nsArray addObject:strValue];
                }
            }
            else if (dynamic_cast<C2DXDictionary*>(value) != NULL)
            {
                NSMutableDictionary *dictValue = convertC2DXDictionaryToNSDictionary(dynamic_cast<C2DXDictionary*>(value));
                if (dictValue)
                {
                    [nsArray addObject:dictValue];
                }
            }
            else if (dynamic_cast<C2DXArray*>(value) != NULL)
            {
                NSArray *arrayValue = convertC2DXArrayToNSArray(dynamic_cast<C2DXArray*>(value));
                if (arrayValue)
                {
                    [nsArray addObject:arrayValue];
                }
            }
        }
        return nsArray;
    }
    return NULL;
}

#pragma mark - ShareSDK 接口
#pragma mark 注册

void C2DXiOSShareSDK::registerAppAndSetPlatformConfig(const char *appKey, C2DXDictionary *configInfo)
{
    //4.0.0 之后appkey请在 info.plist 中添加 MOBAppKey MOBAppSecret 字段并进行设置
    
    //    NSString* appKeyStr = [NSString stringWithCString:appKey
    //                                             encoding:NSUTF8StringEncoding];
    NSMutableDictionary* platformsDic = [NSMutableDictionary dictionary];
    
    if(configInfo)
    {
        platformsDic = convertC2DXDictionaryToNSDictionary(configInfo);
    }
    
    NSArray *platforms = [platformsDic allKeys];
    NSMutableArray *activePlatforms = [NSMutableArray array];
    
    for (id platformStr in platforms)
    {
        if ([platformStr isKindOfClass:[NSString class]])
        {
            [activePlatforms addObject:@([platformStr integerValue])];
        }
    }
    
    [ShareSDK registPlatforms:^(SSDKRegister *platformsRegister) {
        
        NSMutableDictionary *platformInfos = platformsRegister.platformsInfo;
        [platformInfos addEntriesFromDictionary:platformsDic];
    }];
}

id convertPublishContent(C2DXDictionary *content)
{
    NSString *text = nil;
    NSString *title = nil;
    NSString *url = nil;
    SSDKImage *thumbImg = nil;
    SSDKImage *image = nil;
    
    NSString *musicFileUrl = nil;
    NSString *extInfo = nil;
    NSData *fileData = nil;
    NSData *emoData = nil;
    
    SSDKContentType contentType = SSDKContentTypeAuto;
    C2DXContentType temContentType = C2DXContentTypeText;
    
    NSMutableDictionary *shareContentPara = [NSMutableDictionary dictionary];
    
    if (content)
    {
        //text
        C2DXString *textStr = dynamic_cast<C2DXString *>(content -> objectForKey("text"));
        if (textStr)
        {
            text = [NSString stringWithCString:textStr -> getCString() encoding:NSUTF8StringEncoding];
        }
        
        //title
        C2DXString *titleStr = dynamic_cast<C2DXString *>(content -> objectForKey("title"));
        if (titleStr)
        {
            title = [NSString stringWithCString:titleStr -> getCString() encoding:NSUTF8StringEncoding];
        }
        
        //url
        C2DXString *urlStr = dynamic_cast<C2DXString *>(content -> objectForKey("url"));
        if (urlStr)
        {
            url = [NSString stringWithCString:urlStr -> getCString() encoding:NSUTF8StringEncoding];
        }
        
        //thumbImg
        C2DXString *thumbImagePath = dynamic_cast<C2DXString *>(content -> objectForKey("thumbImg"));
        if (thumbImagePath)
        {
            NSString *imgPath = [NSString stringWithCString:thumbImagePath -> getCString() encoding:NSUTF8StringEncoding];
            
            if ([MOBFRegex isMatchedByRegex:@"\\w://.*"
                                    options:MOBFRegexOptionsNoOptions
                                    inRange:NSMakeRange(0, 10)
                                 withString:imgPath])
            {
                thumbImg = [[SSDKImage alloc]initWithURL:[NSURL URLWithString:imgPath]];
            }else
            {
                thumbImg = [[SSDKImage alloc] initWithImage:[UIImage imageNamed:imgPath]
                                                     format:SSDKImageFormatJpeg settings:nil];
            }
        }
        
        //image
        C2DXString *imagePath = dynamic_cast<C2DXString *>(content -> objectForKey("image"));
        if (imagePath)
        {
            NSString *imgPath = [NSString stringWithCString:imagePath -> getCString() encoding:NSUTF8StringEncoding];
            
            if ([MOBFRegex isMatchedByRegex:@"\\w://.*"
                                    options:MOBFRegexOptionsNoOptions
                                    inRange:NSMakeRange(0, 10)
                                 withString:imgPath])
            {
                image = [[SSDKImage alloc]initWithURL:[NSURL URLWithString:imgPath]];
            }else
            {
                image = [[SSDKImage alloc] initWithImage:[UIImage imageNamed:imgPath]
                                                  format:SSDKImageFormatJpeg settings:nil];
            }
        }
        
        //Music url
        C2DXString *musicUrl = dynamic_cast<C2DXString *>(content -> objectForKey("musicFileUrl"));
        if (musicUrl)
        {
            musicFileUrl = [NSString stringWithCString:musicUrl -> getCString() encoding:NSUTF8StringEncoding];
        }
        
        //extInfo
        C2DXString *extInfoUrl = dynamic_cast<C2DXString *>(content -> objectForKey("extInfo"));
        if (extInfoUrl)
        {
            extInfo = [NSString stringWithCString:extInfoUrl -> getCString() encoding:NSUTF8StringEncoding];
        }
        
        //fileData
        C2DXString *fileDataStr = dynamic_cast<C2DXString *>(content -> objectForKey("fileData"));
        
        if (fileDataStr)
        {
            fileData = [NSData dataWithContentsOfFile:[NSString stringWithCString:fileDataStr -> getCString() encoding:NSUTF8StringEncoding]];
            //            NSString *str = [NSString stringWithCString:fileDataStr -> getCString() encoding:NSUTF8StringEncoding];
            //            fileData = [str dataUsingEncoding:NSUTF8StringEncoding];
        }
        
        //emoticonData
        C2DXString *emoticonDataStr = dynamic_cast<C2DXString *>(content -> objectForKey("emoticonData"));
        
        if (emoticonDataStr)
        {
            emoData = [NSData dataWithContentsOfFile:[NSString stringWithCString:emoticonDataStr -> getCString() encoding:NSUTF8StringEncoding]];
        }
        
        //type
        C2DXString *typeValue = dynamic_cast<C2DXString *>(content -> objectForKey("type"));
        if (typeValue)
        {
            temContentType = (C2DXContentType)typeValue -> intValue();
            
            switch (temContentType)
            {
                case C2DXContentTypeText:
                    contentType = (SSDKContentType)SSDKContentTypeText;
                    break;
                case C2DXContentTypeImage:
                case C2DXContentTypeEmoji:
                    contentType = (SSDKContentType)SSDKContentTypeImage;
                    break;
                case C2DXContentTypeWebPage:
                    contentType = (SSDKContentType)SSDKContentTypeWebPage;
                    break;
                case C2DXContentTypeMusic:
                    contentType = (SSDKContentType)SSDKContentTypeAudio;
                    break;
                case C2DXContentTypeVideo:
                    contentType = (SSDKContentType)SSDKContentTypeVideo;
                    break;
                case C2DXContentTypeApp:
                    contentType = (SSDKContentType)SSDKContentTypeApp;
                    break;
                case C2DXContentTypeAuto:
                case C2DXContentTypeFile:
                    contentType = (SSDKContentType)SSDKContentTypeAuto;
                default:
                    break;
            }
        }
        
        [shareContentPara SSDKSetupShareParamsByText:text
                                              images:image
                                                 url:[NSURL URLWithString:url]
                                               title:title
                                                type:contentType];
        //应用消息类型
        if(fileData && contentType == SSDKContentTypeApp)
        {
            [shareContentPara SSDKSetupWeChatParamsByText:text
                                                    title:@"App消息"
                                                      url:[NSURL URLWithString:url]
                                               thumbImage:thumbImg
                                                    image:image
                                             musicFileURL:nil
                                                  extInfo:nil
                                                 fileData:fileData
                                             emoticonData:nil
                                      sourceFileExtension:nil
                                           sourceFileData:nil
                                                     type:SSDKContentTypeApp
                                       forPlatformSubType:SSDKPlatformSubTypeWechatSession];
        }
        
        return shareContentPara;
    }
    
    return NULL;
}

#pragma mark 分享平台授权
void C2DXiOSShareSDK::authorize(int reqID, C2DXPlatType platType, C2DXAuthResultEvent callback)
{
    [ShareSDK authorize:(SSDKPlatformType)platType
               settings:nil
         onStateChanged:^(SSDKResponseState state, SSDKUser *user, NSError *error) {
             
             C2DXDictionary *userInfoDict = C2DXDictionary::create();
             switch (state)
             {
                 case SSDKResponseStateSuccess:
                     userInfoDict = convertNSDictToCCDict([user rawData]);
                     if (user)
                     {
                         userInfoDict = convertNSDictToCCDict([user rawData]);
                     }
                     
                     break;
                 case SSDKResponseStateFail:
                     
                     if (error)
                     {
                         NSInteger errCode = [error code];
                         NSString *errDesc = [NSString stringWithFormat:@"%@",[error userInfo]];
                         
                         userInfoDict->setObject(C2DXInteger::create((int)errCode), "error_code");
                         
                         if (errDesc)
                         {
                             userInfoDict->setObject(C2DXString::create([errDesc UTF8String]), "error_msg");
                         }
                     }
                     break;
                     
                 default:
                     break;
             }
             
             if (callback)
             {
                 callback(reqID,(C2DXResponseState)state,platType,userInfoDict);
             }
         }];
}

#pragma mark 取消授权
void C2DXiOSShareSDK::cancelAuthorize(C2DXPlatType platType)
{
    [ShareSDK cancelAuthorize:(SSDKPlatformType)platType result:nil];
}

#pragma mark 用户是否授权
bool C2DXiOSShareSDK::hasAutorized(C2DXPlatType platType)
{
    return [ShareSDK hasAuthorized:(SSDKPlatformType)platType] ? true :false;
}

bool C2DXiOSShareSDK::isClientInstalled(C2DXPlatType platType)
{
    return [ShareSDK isClientInstalled:(SSDKPlatformType)platType];
}

#pragma mark 获取授权用户信息
void C2DXiOSShareSDK::getUserInfo(int reqID,C2DXPlatType platType, C2DXGetUserInfoResultEvent callback)
{
    [ShareSDK getUserInfo:(SSDKPlatformType)platType
           onStateChanged:^(SSDKResponseState state, SSDKUser *user, NSError *error)
     {
         C2DXDictionary *userInfoDict = C2DXDictionary::create();
         switch (state)
         {
             case SSDKResponseStateSuccess:
                 userInfoDict = convertNSDictToCCDict([user rawData]);
                 if ([[user credential] rawData])
                 {
                     userInfoDict->setObject(convertNSDictToCCDict([[user credential] rawData]), "credential");
                 }
                 
                 break;
             case SSDKResponseStateFail:
                 
                 if (error)
                 {
                     NSInteger errCode = [error code];
                     NSString *errDesc = [NSString stringWithFormat:@"%@",[error userInfo]];
                     
                     userInfoDict->setObject(C2DXInteger::create((int)errCode), "error_code");
                     
                     if (errDesc)
                     {
                         userInfoDict->setObject(C2DXString::create([errDesc UTF8String]), "error_msg");
                     }
                 }
                 break;
                 
             default:
                 break;
         }
         
         if(callback)
         {
             callback(reqID,(C2DXResponseState)state,platType,userInfoDict);
         }
     }];
}

#pragma mark 简单分享
void C2DXiOSShareSDK::shareContent(int reqID,C2DXPlatType platType, C2DXDictionary *content,bool useClientShare, C2DXShareResultEvent callback)
{
    NSMutableDictionary *parameters = convertPublishContent(content);
    
    [ShareSDK share:(SSDKPlatformType)platType
         parameters:parameters
     onStateChanged:^(SSDKResponseState state, NSDictionary *userData, SSDKContentEntity *contentEntity, NSError *error) {
         
         C2DXDictionary *userInfoDict = C2DXDictionary::create();
         switch (state)
         {
             case SSDKResponseStateSuccess:
                 userInfoDict = convertNSDictToCCDict(userData);
                 break;
             case SSDKResponseStateFail:
                 
                 if (error)
                 {
                     NSInteger errCode = [error code];
                     NSString *errDesc = [NSString stringWithFormat:@"%@",[error userInfo]];
                     
                     userInfoDict->setObject(C2DXInteger::create((int)errCode), "error_code");
                     
                     if (errDesc)
                     {
                         userInfoDict->setObject(C2DXString::create([errDesc UTF8String]), "error_msg");
                     }
                 }
                 break;
                 
             default:
                 break;
         }
         
         if (callback)
         {
             callback(reqID,(C2DXResponseState)state,(C2DXPlatType)platType,userInfoDict);
         }
     }];
}

#pragma mark 一键分享
void C2DXiOSShareSDK::oneKeyShareContent(int reqID,C2DXArray *platTypes, C2DXDictionary *content, C2DXShareResultEvent callback)
{
    NSLog(@"[ShareSDK Warning]: Method deprecate !");
}

#pragma mark 弹出分享菜单进行分享
void C2DXiOSShareSDK::showShareMenu(int reqID,C2DXArray *platTypes, C2DXDictionary *content, C2DXPoint pt, bool useClientShare , C2DXShareResultEvent callback)
{
    NSMutableArray *shareList = nil;
    if (platTypes && platTypes -> count() > 0)
    {
        shareList = [NSMutableArray array];
        for (int i = 0; i < platTypes -> count(); i++)
        {
            C2DXInteger *type = (C2DXInteger *)platTypes -> C2DXObjectAtIndex(i);
            [shareList addObject:[NSNumber numberWithInteger:type -> getValue()]];
        }
    }
    
    //设置iPad菜单位置
    //    pt = CCDirector::sharedDirector() -> convertToUI(pt);
    if (!_refView)
    {
        _refView = [[UIView alloc] initWithFrame:CGRectMake(pt.x, pt.y, 1, 1)];
    }
    _refView.frame = CGRectMake(pt.x, pt.y, 1, 1);
    [[UIApplication sharedApplication].keyWindow.rootViewController.view addSubview:_refView];
    
    NSMutableDictionary *shareParams;
    //构造分享参数
    shareParams = convertPublishContent(content);
    
    [ShareSDK showShareActionSheet:_refView
                       customItems:shareList
                       shareParams:shareParams
                sheetConfiguration:nil
                    onStateChanged:^(SSDKResponseState state,
                                     SSDKPlatformType platformType,
                                     NSDictionary *userData,
                                     SSDKContentEntity *contentEntity,
                                     NSError *error,
                                     BOOL end)
     {
         C2DXDictionary *userInfoDict = C2DXDictionary::create();
         
         switch (state)
         {
             case SSDKResponseStateSuccess:
                 userInfoDict = convertNSDictToCCDict(userData);
                 break;
             case SSDKResponseStateFail:
                 
                 if (error)
                 {
                     NSInteger errCode = [error code];
                     NSString *errDesc = [NSString stringWithFormat:@"%@",[error userInfo]];
                     
                     userInfoDict->setObject(C2DXInteger::create((int)errCode), "error_code");
                     
                     if (errDesc)
                     {
                         userInfoDict->setObject(C2DXString::create([errDesc UTF8String]), "error_msg");
                     }
                 }
                 break;
             default:
                 break;
         }
         
         if (callback)
         {
             callback(reqID,(C2DXResponseState)state,(C2DXPlatType)platformType,userInfoDict);
         }
         
         if (_refView)
         {
             //移除视图
             [_refView removeFromSuperview];
         }
     }];
}

#pragma mark 弹出分享编辑框

void C2DXiOSShareSDK::showShareEditViewWithConfigurationFile(int reqID,C2DXPlatType platType, const char *contentName, C2DXDictionary *customFields,C2DXShareResultEvent callback)
{
    NSString *aContentName = convertC2DXStringToNSString(C2DXString::create(contentName));
    NSDictionary *aCustomFields = convertC2DXDictionaryToNSDictionary(customFields);
    NSDictionary *params = [ShareSDK getShareParamsWithContentName:aContentName customFields:aCustomFields];
    [ShareSDK showShareEditor:(SSDKPlatformType)platType
               otherPlatforms:nil
                  shareParams:params.mutableCopy
          editorConfiguration:nil
               onStateChanged:^(SSDKResponseState state,
                                SSDKPlatformType platformType,
                                NSDictionary *userData,
                                SSDKContentEntity *contentEntity,
                                NSError *error,
                                BOOL end)
     {
         C2DXDictionary *userInfoDict = C2DXDictionary::create();
         
         switch (state)
         {
             case SSDKResponseStateSuccess:
                 userInfoDict = convertNSDictToCCDict(userData);
                 break;
             case SSDKResponseStateFail:
                 if (error)
                 {
                     NSInteger errCode = [error code];
                     NSString *errDesc = [NSString stringWithFormat:@"%@",[error userInfo]];
                     
                     userInfoDict->setObject(C2DXInteger::create((int)errCode), "error_code");
                     
                     if (errDesc)
                     {
                         userInfoDict->setObject(C2DXString::create([errDesc UTF8String]), "error_msg");
                     }
                 }
                 break;
             default:
                 break;
         }
         
         if (callback)
         {
             callback(reqID,(C2DXResponseState)state,(C2DXPlatType)platformType,userInfoDict);
         }
     }];
    
}

void C2DXiOSShareSDK::showShareEditView(int reqID,C2DXPlatType platType, C2DXDictionary *content, bool useClientShare, C2DXShareResultEvent callback)
{
    NSMutableDictionary *shareParams;
    //构造分享参数
    shareParams = convertPublishContent(content);
    [ShareSDK showShareEditor:(SSDKPlatformType)platType
               otherPlatforms:nil
                  shareParams:shareParams
          editorConfiguration:nil
               onStateChanged:^(SSDKResponseState state,
                                SSDKPlatformType platformType,
                                NSDictionary *userData,
                                SSDKContentEntity *contentEntity,
                                NSError *error,
                                BOOL end)
     {
         C2DXDictionary *userInfoDict = C2DXDictionary::create();
         
         switch (state)
         {
             case SSDKResponseStateSuccess:
                 userInfoDict = convertNSDictToCCDict(userData);
                 break;
             case SSDKResponseStateFail:
                 if (error)
                 {
                     NSInteger errCode = [error code];
                     NSString *errDesc = [NSString stringWithFormat:@"%@",[error userInfo]];
                     
                     userInfoDict->setObject(C2DXInteger::create((int)errCode), "error_code");
                     
                     if (errDesc)
                     {
                         userInfoDict->setObject(C2DXString::create([errDesc UTF8String]), "error_msg");
                     }
                 }
                 break;
             default:
                 break;
         }
         
         if (callback)
         {
             callback(reqID,(C2DXResponseState)state,(C2DXPlatType)platformType,userInfoDict);
         }
     }];
}

void C2DXiOSShareSDK::getFriendList(int reqID,C2DXPlatType platType,int count, int page, C2DXAddFriendResultEvent callback)
{
    [ShareSDK getFriends:(SSDKPlatformType)platType
                  cursor:page
                    size:count
          onStateChanged:^(SSDKResponseState state, SSEFriendsPaging *paging, NSError *error) {
              
              C2DXDictionary *userInfoDict = C2DXDictionary::create();
              NSMutableDictionary *useDic = [NSMutableDictionary dictionary];
              
              switch (state)
              {
                  case SSDKResponseStateSuccess:
                      if (paging.users)
                      {
                          [useDic setObject:paging.users forKey:@"data"];
                      }
                      break;
                  case SSDKResponseStateFail:
                      if (error)
                      {
                          NSInteger errCode = [error code];
                          NSString *errDesc = [NSString stringWithFormat:@"%@",[error userInfo]];
                          
                          if (@(errCode))
                          {
                              [useDic setObject:@(errCode) forKey:@"error_code"];
                          }
                          
                          if (errDesc)
                          {
                              [useDic setObject:errDesc forKey:@"error_msg"];
                          }
                      }
                      break;
                  default:
                      break;
              }
              
              userInfoDict = convertNSDictToCCDict(useDic);
              
              if (callback)
              {
                  callback(reqID,(C2DXResponseState)state,(C2DXPlatType)platType,userInfoDict);
              }
          }];
}

void C2DXiOSShareSDK::addFriend(int reqID,C2DXPlatType platType,const char* account ,C2DXGetFriendsResultEvent callback)
{
    SSDKPlatformType type = (SSDKPlatformType)platType;
    SSDKUser *user = [[SSDKUser alloc] init];
    
    if (type == SSDKPlatformTypeTencentWeibo)
    {
        user.nickname = convertC2DXStringToNSString(C2DXString::create(account));
    }
    else
    {
        user.nickname = convertC2DXStringToNSString(C2DXString::create(account));
    }
    
    [ShareSDK addFriend:(SSDKPlatformType)platType
                   user:user
         onStateChanged:^(SSDKResponseState state, SSDKUser *user, NSError *error) {
             
             C2DXDictionary *userInfoDict = C2DXDictionary::create();;
             NSMutableDictionary *temDic = [NSMutableDictionary dictionary];
             
             if (user)
             {
                 [temDic setObject:user forKey:@"data"];
             }
             
             if (error)
             {
                 NSInteger errCode = [error code];
                 NSString *errDesc = [NSString stringWithFormat:@"%@",[error userInfo]];
                 
                 [temDic setObject:@(errCode) forKey:@"error_code"];
                 [temDic setObject:errDesc forKey:@"error_msg"];
             }
             userInfoDict = convertNSDictToCCDict(temDic);
             
             if (callback)
             {
                 callback(reqID,(C2DXResponseState)state,(C2DXPlatType)platType,userInfoDict);
             }
         }];
}

void C2DXiOSShareSDK::alertLog(const char *msg)
{
    //    NSString *message = convertC2DXStringToNSString((C2DXString *)msg);
    //
    //    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@""
    //                                                        message:message
    //                                                       delegate:nil
    //                                              cancelButtonTitle:@"OK"
    //                                              otherButtonTitles:nil, nil];
    //    [alertView show];
}

void C2DXiOSShareSDK::showShareMenuWithConfigurationFile(int reqID,C2DXArray *platTypes, C2DXPoint pt, const char *contentName, C2DXDictionary *customFields, C2DXShareResultEvent callback)
{
    NSMutableArray *shareList = nil;
    if (platTypes && platTypes -> count() > 0)
    {
        shareList = [NSMutableArray array];
        for (int i = 0; i < platTypes -> count(); i++)
        {
            C2DXInteger *type = (C2DXInteger *)platTypes -> C2DXObjectAtIndex(i);
            [shareList addObject:[NSNumber numberWithInteger:type -> getValue()]];
        }
    }
    
    //设置iPad菜单位置
    //    pt = CCDirector::sharedDirector() -> convertToUI(pt);
    if (!_refView)
    {
        _refView = [[UIView alloc] initWithFrame:CGRectMake(pt.x, pt.y, 1, 1)];
    }
    _refView.frame = CGRectMake(pt.x, pt.y, 1, 1);
    [[UIApplication sharedApplication].keyWindow.rootViewController.view addSubview:_refView];
    
    NSString *aContentName = convertC2DXStringToNSString(C2DXString::create(contentName));
    NSDictionary *aCustomFields = convertC2DXDictionaryToNSDictionary(customFields);
    
    NSDictionary *params = [ShareSDK getShareParamsWithContentName:aContentName customFields:aCustomFields];
    
    [ShareSDK showShareActionSheet:_refView
                       customItems:shareList
                       shareParams:params.mutableCopy
                sheetConfiguration:nil
                    onStateChanged:^(SSDKResponseState state,
                                     SSDKPlatformType platformType,
                                     NSDictionary *userData,
                                     SSDKContentEntity *contentEntity,
                                     NSError *error,
                                     BOOL end)
     {
         C2DXDictionary *userInfoDict = C2DXDictionary::create();
         
         switch (state)
         {
             case SSDKResponseStateSuccess:
                 userInfoDict = convertNSDictToCCDict(userData);
                 break;
             case SSDKResponseStateFail:
                 
                 if (error)
                 {
                     NSInteger errCode = [error code];
                     NSString *errDesc = [NSString stringWithFormat:@"%@",[error userInfo]];
                     
                     userInfoDict->setObject(C2DXInteger::create((int)errCode), "error_code");
                     
                     if (errDesc)
                     {
                         userInfoDict->setObject(C2DXString::create([errDesc UTF8String]), "error_msg");
                     }
                 }
                 break;
             default:
                 break;
         }
         
         if (callback)
         {
             callback(reqID,(C2DXResponseState)state,(C2DXPlatType)platformType,userInfoDict);
         }
         
         if (_refView)
         {
             //移除视图
             [_refView removeFromSuperview];
         }
     }];
}

void C2DXiOSShareSDK::shareWithConfigurationFile(int reqID, const char *contentName, C2DXPlatType platType, C2DXDictionary *customFields, C2DXShareResultEvent callback)
{
    NSString *aContentName = convertC2DXStringToNSString(C2DXString::create(contentName));
    NSDictionary *aCustomFields = convertC2DXDictionaryToNSDictionary(customFields);
    
    NSDictionary *params = [ShareSDK getShareParamsWithContentName:aContentName customFields:aCustomFields];
    
    [ShareSDK showShareActionSheet:_refView
                       customItems:nil
                       shareParams:params.mutableCopy
                sheetConfiguration:nil
                    onStateChanged:^(SSDKResponseState state,
                                     SSDKPlatformType platformType,
                                     NSDictionary *userData,
                                     SSDKContentEntity *contentEntity,
                                     NSError *error,
                                     BOOL end)
     {
         C2DXDictionary *userInfoDict = C2DXDictionary::create();
         switch (state)
         {
             case SSDKResponseStateSuccess:
                 userInfoDict = convertNSDictToCCDict(userData);
                 break;
             case SSDKResponseStateFail:
                 
                 if (error)
                 {
                     NSInteger errCode = [error code];
                     NSString *errDesc = [NSString stringWithFormat:@"%@",[error userInfo]];
                     
                     userInfoDict->setObject(C2DXInteger::create((int)errCode), "error_code");
                     
                     if (errDesc)
                     {
                         userInfoDict->setObject(C2DXString::create([errDesc UTF8String]), "error_msg");
                     }
                 }
                 break;
                 
             default:
                 break;
         }
         
         if (callback)
         {
             callback(reqID,(C2DXResponseState)state,(C2DXPlatType)platType,userInfoDict);
         }
     }];
}

