#include "AppDelegate.h"
#include "HelloWorldScene.h"

using namespace std;

#include "C2DXShareSDK.h"
#include <string>
#include <sstream>

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {}
AppDelegate::~AppDelegate() {}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
    return 0;
}

bool AppDelegate::applicationDidFinishLaunching()
{
    //初始化ShareSDK
    this->initShareSDKConfig();
    
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview)
    {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    Size frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }
    
    register_all_packages();
    
    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();
    
    // run
    director->runWithScene(scene);
    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}

void AppDelegate::initShareSDKConfig()
{
    //设置平台配置
    //Platforms
    __Dictionary *totalDict = __Dictionary::create();
    
    //新浪微博
    __Dictionary *sinaWeiboConf= __Dictionary::create();
    sinaWeiboConf->setObject(__String::create("568898243"), "app_key");
    sinaWeiboConf->setObject(__String::create("38a4f8204cc784f81f9f0daaf31e02e3"), "app_secret");
    sinaWeiboConf->setObject(__String::create("http://www.sharesdk.cn"), "redirect_uri");
    stringstream sina;
    sina << cn::sharesdk::C2DXPlatTypeSinaWeibo;
    totalDict->setObject(sinaWeiboConf, sina.str());
    
    //微信
    __Dictionary *wechatConf = __Dictionary::create();
    wechatConf->setObject(__String::create("wx4868b35061f87885"), "app_id");
    wechatConf->setObject(__String::create("64020361b8ec4c99936c0e3999a9f249"), "app_secret");
    stringstream wechat;
    wechat << cn::sharesdk::C2DXPlatTypeWechatPlatform;
    totalDict->setObject(wechatConf, wechat.str());
    
    //QQ
    __Dictionary *qqConf = __Dictionary::create();
    qqConf->setObject(__String::create("100371282"), "app_id");
    qqConf->setObject(__String::create("aed9b0303e3ed1e27bae87c33761161d"), "app_key");
    stringstream qq;
    qq << cn::sharesdk::C2DXPlatTypeQQPlatform;
    totalDict->setObject(qqConf, qq.str());
    
    //腾讯微博
    __Dictionary *tencentConf = __Dictionary::create();
    tencentConf->setObject(__String::create("801307650"), "app_key");
    tencentConf->setObject(__String::create("ae36f4ee3946e1cbb98d6965b0b2ff5c"), "app_secret");
    tencentConf->setObject(__String::create("http://www.sharesdk.cn"), "redirect_uri");
    stringstream tencent;
    tencent << cn::sharesdk::C2DXPlatTypeTencentWeibo;
    totalDict->setObject(tencentConf, tencent.str());
    
    //Facebook
    __Dictionary *fbConf = __Dictionary::create();
    fbConf->setObject(__String::create("107704292745179"), "api_key");
    fbConf->setObject(__String::create("38053202e1a5fe26c80c753071f0b573"), "app_secret");
    fbConf->setObject(__String::create("ShareSDK"), "display_name");
    stringstream facebook;
    facebook << cn::sharesdk::C2DXPlatTypeFacebook;
    totalDict->setObject(fbConf, facebook.str());
    
    //Twitter
    __Dictionary *twConf = __Dictionary::create();
    twConf->setObject(__String::create("LRBM0H75rWrU9gNHvlEAA2aOy"), "consumer_key");
    twConf->setObject(__String::create("gbeWsZvA9ELJSdoBzJ5oLKX0TU09UOwrzdGfo9Tg7DjyGuMe8G"), "consumer_secret");
    twConf->setObject(__String::create("http://www.mob.com"), "redirect_uri");
    stringstream twitter;
    twitter << cn::sharesdk::C2DXPlatTypeTwitter;
    totalDict->setObject(twConf, twitter.str());
    
    //Mail
    __Dictionary *mailConf = __Dictionary::create();
    stringstream mail;
    mail << cn::sharesdk::C2DXPlatTypeMail;
    totalDict->setObject(mailConf, mail.str());
    
    
    //Facebook Messenger
    /*
     iOS 需在info.plist 中增加
     <key>FacebookAppID</key>
     <string>107704292745179</string>
     */
    __Dictionary *fbMessengerConf = __Dictionary::create();
    stringstream messenger;
    messenger << cn::sharesdk::C2DXPlatTypeFacebookMessenger;
    totalDict -> setObject(fbMessengerConf, messenger.str());
    
    //钉钉（Ding Talk）
    __Dictionary *dingTalkConf = __Dictionary::create();
    dingTalkConf->setObject(__String::create("dingoanxyrpiscaovl4qlw"), "app_id");
    stringstream dingTalk;
    dingTalk << cn::sharesdk::C2DXPlatTypeDingTalk;
    totalDict -> setObject(dingTalkConf, dingTalk.str());
    
    //Mai Pai
    /*
     iOS 需要在 info.plist 配置 授权相册权限
     <key>NSPhotoLibraryUsageDescription</key>
     <string>从手机相册中选择</string>
     */
    __Dictionary *meiPaiConf = __Dictionary::create();
    meiPaiConf->setObject(__String::create("1089867596"), "app_key");
    stringstream meiPai;
    meiPai << cn::sharesdk::C2DXPlatTypeMeiPai;
    totalDict -> setObject(meiPaiConf, meiPai.str());
    
    //line
    /*
    ios 需要在 info.plist 配置
    <key>LineSDKConfig</key>
    <dict>
    <key>ChannelID</key>
    <string>1502330683</string>
    </dict>
     设置 URL Scheme : line3rdp.$(PRODUCT_BUNDLE_IDENTIFIER)
     LSApplicationQueriesSchemes : lineauth line line3rdp.$(PRODUCT_BUNDLE_IDENTIFIER)
     */
    __Dictionary *lineConf = __Dictionary::create();
    stringstream line;
    line << cn::sharesdk::C2DXPlatTypeLine;
    totalDict->setObject(lineConf, line.str());
    
    /*
    //Youtube
    __Dictionary *youTubeConf = __Dictionary::create();
    youTubeConf->setObject(__String::create("906418427202-jinnbqal1niq4s8isbg2ofsqc5ddkcgr.apps.googleusercontent.com"), "client_id");
    youTubeConf->setObject(__String::create("http://localhost"), "redirect_uri");
    stringstream youTube;
    youTube << cn::sharesdk::C2DXPlatTypeYouTube;
    totalDict -> setObject(youTubeConf, youTube.str());
     */
    
    cn::sharesdk::C2DXShareSDK::registerAppAndSetPlatformConfig("8e3320a36606", totalDict);
}
