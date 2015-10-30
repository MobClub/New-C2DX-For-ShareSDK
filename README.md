# Getting Started Guide

## Step1: Download the cocos2d-x components of the ShareSDK

Open Github download the [C2DXShareSDKSample](https://github.com/ShareSDKPlatform/C2DXShareSDKSample/archive/master.zip) projects. The project C2DXShareSDK folder copy to your project.

## Step2: Modify AppDelegate file

Open the "AppDelegate.cpp" file, import the header file "C2DXShareSDK.h". Such as:

```
#include "C2DXShareSDK.h"
```

In AppDelegate :: applicationDidFinishLaunching method, add the following code to initialize ShareSDK and configure the social platform information.

```
bool AppDelegate::applicationDidFinishLaunching() {

        //……        
        C2DXShareSDK::open(CCString::create("api20"), false);
        
        CCDictionary *sinaConfigDict = CCDictionary::create();
        sinaConfigDict -> setObject(CCString::create("568898243"), "app_key");
        sinaConfigDict -> setObject(CCString::create("38a4f8204cc784f81f9f0daaf31e02e3"), "app_secret");
        sinaConfigDict -> setObject(CCString::create("http://www.mob.com"), "redirect_uri");
        C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSinaWeibo, sinaConfigDict);

        //……
}
```

**Note**: where the configuration items in social platform configuration information, refer to "[Social Platform Configuration Item Description](http://wiki.sharesdk.cn/%E7%A4%BE%E4%BA%A4%E5%B9%B3%E5%8F%B0%E9%85%8D%E7%BD%AE%E9%A1%B9%E8%AF%B4%E6%98%8E)" document.

## Share

First, create a structure to share content, as follows:

```
CCDictionary *content = CCDictionary::create();
content -> setObject(CCString::create("This is a test content"), "content");
content -> setObject(CCString::create("http://img0.bdstatic.com/img/image/308342ac65c10385343da168d569113b07ecb8088ef.jpg"), "image");
content -> setObject(CCString::create("Test title"), "title");
content -> setObject(CCString::create("Test description"), "description");
content -> setObject(CCString::create("http://www.mob.com"), "url");
content -> setObject(CCInteger::create(C2DXContentTypeNews), "type");
```

Then the content object incoming share interfaces. such as:

```
C2DXShareSDK::showShareMenu(NULL, content, shareResultHandler);
```

shareResultHandler is callback method, which is defined as follows:

```
void shareResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *shareInfo, CCDictionary *error)
{
    switch (state) {
        case C2DXResponseStateSuccess:
            CCLog("share success!");
            break;
        case C2DXResponseStateFail:
            CCLog("share fail!");
            break;
        default:
            break;
    }
}
```

## User Authorization

To get the authorized users information by call the C2DXShareSDK::geUserInfo method . Code is as follows:

```
C2DXShareSDK::getUserInfo(C2DXPlatTypeSinaWeibo, getUserResultHandler);
```

getUserResultHandler is callback method, which is defined as follows:

```
void getUserResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *userInfo, CCDictionary *error)
{
    if (state == C2DXResponseStateSuccess)
    {
        //Output user information
        CCArray *allKeys = userInfo -> allKeys();
        for (int i = 0; i < allKeys -> count(); i++)
        {
            CCString *key = (CCString *)allKeys -> objectAtIndex(i);
            CCObject *obj = userInfo -> objectForKey(key -> getCString());
            
            CCLog("key = %s", key -> getCString());
            if (dynamic_cast<CCString *>(obj))
            {
                CCLog("value = %s", dynamic_cast<CCString *>(obj) -> getCString());
            }
            else if (dynamic_cast<CCInteger *>(obj))
            {
                CCLog("value = %d", dynamic_cast<CCInteger *>(obj) -> getValue());
            }
            else if (dynamic_cast<CCDouble *>(obj))
            {
                CCLog("value = %f", dynamic_cast<CCDouble *>(obj) -> getValue());
            }
        }
    }
}
```

# Integration for iOS (Not released iOS version of the application can skip this section)

## Step1: The iOS version of ShareSDK into the project:

Login ShareSDK [official website](http://sharesdk.cn) to download and extract the latest version of the SDK. If you have not downloaded yet, please [click here to download](http://sharesdk.cn/Download) or access http://sharesdk.cn/Download. After extracting the following diagram:

![pic](http://wiki.sharesdk.cn/images/3/37/c2dx_doc_004.png)

The ShareSDK_vX.XX (XXX represents SDK version number) directory are copied to your cocos2d-x project. Figure:

![pic](http://wiki.sharesdk.cn/images/0/0b/c2dx_doc_005.png)

The ShareSDK into the project, and add the appropriate dependencies. This step can refer to: "[iOS Quick Integration Guide](http://wiki.sharesdk.cn/iOS%E5%BF%AB%E9%80%9F%E9%9B%86%E6%88%90%E6%8C%87%E5%8D%97)" in the first, the second step. After execution, as shown below:

![pic](http://wiki.sharesdk.cn/images/a/ad/c2dx_doc_006.png)

## Step2: Modify AppController file

Open the "AppController.mm" file, add ShareSDK.h header file:

```
#import <ShareSDK/ShareSDK.h>
```

Add handleOpenURL method, as follows:

```
@implementation AppController

//……

- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url
{
    return [ShareSDK handleOpenURL:url sourceApplication:nil annotation:nil wxDelegate:nil];
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    return [ShareSDK handleOpenURL:url sourceApplication:sourceApplication annotation:annotation wxDelegate:nil];
}
```

In the integrated WeChat, QQ, Google+, Pinterest, RenRen platform, you need to import the relevant type. Code is shown below:

```
#import "WXApi.h"      //WeChat
#import "WBApi.h"      //Tencent Weibo
#import <TencentOpenAPI/QQApiInterface.h>     //QQ Connect
#import <TencentOpenAPI/TencentOAuth.h>      //QQ Connect
#import <RennSDK/RennSDK.h>     //人人网
#import <Pinterest/Pinterest.h>     //Pinterest
#import <GoogleOpenSource/GoogleOpenSource.h>    //Google+
#import <GooglePlus/GooglePlus.h>     //Google+

@implementation AppController

//……

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
    
    //……
    
    //Import WeChat Class
    [ShareSDK importWeChatClass:[WXApi class]];
    
    //Import Tencent Weibo Class
    [ShareSDK importTencentWeiboClass:[WBApi class]];
    
    //Import QQ Class
    [ShareSDK importQQClass:[QQApiInterface class] tencentOAuthCls:[TencentOAuth class]];
    
    //Import RenRen Class
    [ShareSDK importRenRenClass:[RennClient class]];
    
    //Import Pinterest Class
    [ShareSDK importPinterestClass:[Pinterest class]];
    
    //Import Google+ Class
    [ShareSDK importGooglePlusClass:[GPPSignIn class] shareClass:[GPPShare class]];

    //……
}
```

# Integration for Android (Not released Android version of the application can skip this section)

**Note**
This section describes how to integrate ShareSDK into coco2d-x with **custom JNI codes**, if you want to find **”how to integrate ShareSDK with pure Java codes”**, please click [HERE](http://wiki.sharesdk.cn/Android_%E7%A4%BA%E4%BE%8B%E9%A1%B9%E7%9B%AE#.E7.BA.AFjava.E4.BB.A3.E7.A0.81). And if you want to find **”how to integrate ShareSDK with plugin-x”**, please click [HERE](http://wiki.sharesdk.cn/Android_%E7%A4%BA%E4%BE%8B%E9%A1%B9%E7%9B%AE#plugin-x).

## Integration Steps

1 Download the latest version of ShareSDK from our [official website](http://sharesdk.cn/) and extract it.

2 Refer to the "[Five Steps to Integrate ShareSDK](https://github.com/ShareSDKPlatform/ShareSDK-for-Android/wiki/Five-Steps-to-Integrate-ShareSDK)" chapter, use **“copy jars and resources into your project”** way to import ShareSDK to your project. After these two steps, your project should include the followings:
(1) Java source codes of OnekeyShare.
(2) If you integrate Wechat or Yixin, your project should include the package wxapi or yxapi.
(3) Resources of ShareSDK and OnekeyShare must have been added into your “res” directory.
(4) Jars of ShareSDK must have been copied into your “libs” directory.
(5) Besides resources of cocos2d-x, there is a SahreSDK.xml file in your “assets” directory.

3 Refer to the "[Five Steps to Integrate ShareSDK](https://github.com/ShareSDKPlatform/ShareSDK-for-Android/wiki/Five-Steps-to-Integrate-ShareSDK)" chapter, modify the “AndroidManifest.xml” file.

4 Applications information in "ShareSDK.xml" are public keys for demonstration. Please change the information of each platform in this file to your application’s refering to the "[Five Steps to Integrate ShareSDK](https://github.com/ShareSDKPlatform/ShareSDK-for-Android/wiki/Five-Steps-to-Integrate-ShareSDK)" chapter.

5 Pull the [source codes on Github](https://github.com/ShareSDKPlatform/C2DXShareSDKSample), and copy the followings into your project:
(1) Copy “cn.sharesdk.ShareSDKUtils” into your “src”.
(2) Copy “libs/armeabi” to your “libs”.

6 Open the class you extend from Cocos2dxActivity, add the following line into its onCreate method:
```` java
ShareSDKUtils.prepare();
```

## Explanation of Java Codes

Basically there is only a ShareSDKUtils Java class, and what you have to do in Java codes is adding the **prepare** in your subclass of Cocos2dxActivity. However, if you want to add more parameters of sharing (the example on github only provides very few parameters to share), you may have to modify the following methods:

```` java
nativeMapToJavaMap(HashMap<String, String>)
```
This method is to transfer the name of the parameters to share from the JNI type to the Java types. If you add the share parameter in native codes, you need to modify this method, add a new rule to translate the name of this parameter to ShareSDK. [HERE](http://wiki.sharesdk.cn/Android_%E5%88%86%E4%BA%AB%E5%88%B0%E6%8C%87%E5%AE%9A%E5%B9%B3%E5%8F%B0#ShareParams.E5.AD.97.E6.AE.B5.E9.87.8A.E4.B9.89) is the table lists the name of the share parameters in ShareSDK.

```` java
onekeyShare(HashMap<String, String>)
```
This method calls OnekeyShare module of ShareSDK, like the method above, if you want to modify the share parameters in native codes, you may need to modify this method.

It is important to note that ShareSDKUtils.prepare() must be called in the **main thread**, and before any operation of ShareSDK. Otherwise it will result in an error in ShareSDKUtils initializing.

## Explanation of Native Codes

**Using custom JNI codes is not an encouraged way of Android platform to integrating ShareSDK**, since you have to add a ton of native-java reflection code which is inefficient and prone to errors. But this method can shield the differences between the platforms by c/c++ codes, and also be complementary to the plugin-x.

Native codes are basically the reflection between native and java codes. However, like Java codes, if you want to modify the native codes, you may need to be carefully with the following methods:

```` c
Java_cn_sharesdk_ShareSDKUtils_onCancel
Java_cn_sharesdk_ShareSDKUtils_onComplete
Java_cn_sharesdk_ShareSDKUtils_onError
```
These three methods are java to native action callbacks, don’t change their names.

```` c
hashmapToCCDictionary
CCDictionaryToHashMap
```
These two methods process the transform between HashMap and CCDictionary.

```` c
setPlatformDevInfo
```
This is not a necessary method in Android, since we have a more convenient way to configure your applications information in the file “ShareSDK.xml”.

**View Chinese Integration Guide, please click [here](http://wiki.sharesdk.cn/iOS%E5%BF%AB%E9%80%9F%E9%9B%86%E6%88%90%E6%8C%87%E5%8D%97)**


