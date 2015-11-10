#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;
using namespace cn::sharesdk;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {

    //初始化社交平台信息
    __Dictionary *allPlatformConfigs = this->initPlatformConfig();
	
    //初始化ShareSDK
    C2DXShareSDK::rigisterAppAndSetPlatformConfig("api20", allPlatformConfigs);
	
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

CCLOG("HELLO INIT");
    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();
CCLOG("SCENE INIT");
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

__Dictionary *AppDelegate::initPlatformConfig()
{	
	
    __Dictionary *allPlatformConfigs = __Dictionary::create();
	
    //新浪微博
    __Dictionary *sinaConfigDict = __Dictionary::create();
    sinaConfigDict -> setObject(String::create("568898243"), "app_key");
    sinaConfigDict -> setObject(String::create("38a4f8204cc784f81f9f0daaf31e02e3"), "app_secret");
    sinaConfigDict -> setObject(String::create("http://www.sharesdk.cn"), "redirect_uri");
    allPlatformConfigs -> setObject(sinaConfigDict,  PlatId::SinaWeibo);

    //腾讯微博
    __Dictionary *tcConfigDict = __Dictionary::create();
    tcConfigDict -> setObject(String::create("801307650"), "app_key");
    tcConfigDict -> setObject(String::create("ae36f4ee3946e1cbb98d6965b0b2ff5c"), "app_secret");
    tcConfigDict -> setObject(String::create("http://www.sharesdk.cn"), "redirect_uri");
    allPlatformConfigs -> setObject(tcConfigDict,  PlatId::TencentWeibo);

    //短信
    //allPlatformConfigs -> setObject(C2DXPlatTypeSMS, NULL);

    //QQ空间
    __Dictionary *qzConfigDict = __Dictionary::create();
    qzConfigDict -> setObject(String::create("100371282"), "app_id");
    qzConfigDict -> setObject(String::create("aed9b0303e3ed1e27bae87c33761161d"), "app_key");
    allPlatformConfigs -> setObject(qzConfigDict,  PlatId::QZone);

    //微信
    __Dictionary *wcConfigDict = __Dictionary::create();
    wcConfigDict -> setObject(String::create("wx4868b35061f87885"), "app_id");
    allPlatformConfigs -> setObject(wcConfigDict, PlatId::WeixiSession);
    allPlatformConfigs -> setObject(wcConfigDict, PlatId::WeixiTimeline);
    allPlatformConfigs -> setObject(wcConfigDict, PlatId::WeixiFav);

    //QQ
    __Dictionary *qqConfigDict = __Dictionary::create();
    qqConfigDict -> setObject(String::create("100371282"), "app_id");
    allPlatformConfigs -> setObject(qqConfigDict, PlatId::QQ);

    //Facebook
    __Dictionary *fbConfigDict = __Dictionary::create();
    fbConfigDict -> setObject(String::create("107704292745179"), "api_key");
    fbConfigDict -> setObject(String::create("38053202e1a5fe26c80c753071f0b573"), "app_secret");
    allPlatformConfigs -> setObject(fbConfigDict, PlatId::Facebook);

    //Twitter
    __Dictionary *twConfigDict = __Dictionary::create();
    twConfigDict -> setObject(String::create("mnTGqtXk0TYMXYTN7qUxg"), "consumer_key");
    twConfigDict -> setObject(String::create("ROkFqr8c3m1HXqS3rm3TJ0WkAJuwBOSaWhPbZ9Ojuc"), "consumer_secret");
    twConfigDict -> setObject(String::create("http://www.sharesdk.cn"), "redirect_uri");
    allPlatformConfigs -> setObject(twConfigDict, PlatId::Twitter);

    //Google+
    __Dictionary *gpConfigDict = __Dictionary::create();
    gpConfigDict -> setObject(String::create("232554794995.apps.googleusercontent.com"), "client_id");
    gpConfigDict -> setObject(String::create("PEdFgtrMw97aCvf0joQj7EMk"), "client_secret");
    gpConfigDict -> setObject(String::create("http://localhost"), "redirect_uri");
    allPlatformConfigs -> setObject(gpConfigDict, PlatId::GooglePlus);

    //人人网
    __Dictionary *rrConfigDict = __Dictionary::create();
    rrConfigDict -> setObject(String::create("226427"), "app_id");
    rrConfigDict -> setObject(String::create("fc5b8aed373c4c27a05b712acba0f8c3"), "app_key");
    rrConfigDict -> setObject(String::create("f29df781abdd4f49beca5a2194676ca4"), "secret_key");
    allPlatformConfigs -> setObject(rrConfigDict, PlatId::Renren);

    //开心网
    __Dictionary *kxConfigDict = __Dictionary::create();
    kxConfigDict -> setObject(String::create("358443394194887cee81ff5890870c7c"), "api_key");
    kxConfigDict -> setObject(String::create("da32179d859c016169f66d90b6db2a23"), "secret_key");
    kxConfigDict -> setObject(String::create("http://www.sharesdk.cn/"), "redirect_uri");
    allPlatformConfigs -> setObject(kxConfigDict, PlatId::Kaixin);

    //邮件
    //allPlatformConfigs -> setObject(C2DXPlatTypeMail, NULL);

    //打印
    //allPlatformConfigs -> setObject(C2DXPlatTypeAirPrint, NULL);

    //拷贝
    //allPlatformConfigs -> setObject(C2DXPlatTypeCopy, NULL);

    //豆瓣
    __Dictionary *dbConfigDict = __Dictionary::create();
    dbConfigDict -> setObject(String::create("02e2cbe5ca06de5908a863b15e149b0b"), "api_key");
    dbConfigDict -> setObject(String::create("9f1e7b4f71304f2f"), "secret");
    dbConfigDict -> setObject(String::create("http://www.sharesdk.cn"), "redirect_uri");
    allPlatformConfigs -> setObject(dbConfigDict, PlatId::DouBan);

    //印象笔记
    __Dictionary *enConfigDict = __Dictionary::create();
    enConfigDict -> setObject(String::create("sharesdk-7807"), "consumer_key");
    enConfigDict -> setObject(String::create("d05bf86993836004"), "consumer_secret");
    enConfigDict -> setObject(String::create("0"), "host_type");
    allPlatformConfigs -> setObject(enConfigDict, PlatId::Evernote);

    //LinkedIn
    __Dictionary *liConfigDict = __Dictionary::create();
    liConfigDict -> setObject(String::create("ejo5ibkye3vo"), "api_key");
    liConfigDict -> setObject(String::create("cC7B2jpxITqPLZ5M"), "secret_key");
    liConfigDict -> setObject(String::create("http://sharesdk.cn"), "redirect_url");
    allPlatformConfigs -> setObject(liConfigDict, PlatId::LinkedIn);

    //Pinterest
    __Dictionary *piConfigDict = __Dictionary::create();
    piConfigDict -> setObject(String::create("1432928"), "client_id");
    allPlatformConfigs -> setObject(piConfigDict, PlatId::Pinterest);

    //Pocket
    __Dictionary *poConfigDict = __Dictionary::create();
    poConfigDict -> setObject(String::create("11496-de7c8c5eb25b2c9fcdc2b627"), "consumer_key");
    poConfigDict -> setObject(String::create("pocketapp1234"), "redirect_uri");
    allPlatformConfigs -> setObject(poConfigDict, PlatId::Pocket);

    //Instapaper
    __Dictionary *ipConfigDict = __Dictionary::create();
    ipConfigDict -> setObject(String::create("4rDJORmcOcSAZL1YpqGHRI605xUvrLbOhkJ07yO0wWrYrc61FA"), "consumer_key");
    ipConfigDict -> setObject(String::create("GNr1GespOQbrm8nvd7rlUsyRQsIo3boIbMguAl9gfpdL0aKZWe"), "consumer_secret");
    allPlatformConfigs -> setObject(ipConfigDict, PlatId::Instapaper);

    //有道云笔记
    __Dictionary *ydConfigDict = __Dictionary::create();
    ydConfigDict -> setObject(String::create("dcde25dca105bcc36884ed4534dab940"), "consumer_key");
    ydConfigDict -> setObject(String::create("d98217b4020e7f1874263795f44838fe"), "consumer_secret");
    ydConfigDict -> setObject(String::create("http://www.sharesdk.cn/"), "oauth_callback");
    ydConfigDict -> setObject(String::create("1"), "host_type");
    allPlatformConfigs -> setObject(ydConfigDict, PlatId::YouDaoNote);

    //搜狐随身看
    __Dictionary *shkConfigDict = __Dictionary::create();
    shkConfigDict -> setObject(String::create("e16680a815134504b746c86e08a19db0"), "app_key");
    shkConfigDict -> setObject(String::create("b8eec53707c3976efc91614dd16ef81c"), "app_secret");
    shkConfigDict -> setObject(String::create("http://sharesdk.cn"), "redirect_uri");
    allPlatformConfigs -> setObject(shkConfigDict, PlatId::SohuKan);

    //Flickr
    __Dictionary *flickrConfigDict = __Dictionary::create();
    flickrConfigDict -> setObject(String::create("33d833ee6b6fca49943363282dd313dd"), "api_key");
    flickrConfigDict -> setObject(String::create("3a2c5b42a8fbb8bb"), "api_secret");
    allPlatformConfigs -> setObject(flickrConfigDict, PlatId::Flickr);

    //Tumblr
    __Dictionary *tumblrConfigDict = __Dictionary::create();
    tumblrConfigDict -> setObject(String::create("2QUXqO9fcgGdtGG1FcvML6ZunIQzAEL8xY6hIaxdJnDti2DYwM"), "consumer_key");
    tumblrConfigDict -> setObject(String::create("3Rt0sPFj7u2g39mEVB3IBpOzKnM3JnTtxX2bao2JKk4VV1gtNo"), "consumer_secret");
    tumblrConfigDict -> setObject(String::create("http://sharesdk.cn"), "callback_url");
    allPlatformConfigs -> setObject(tumblrConfigDict, PlatId::Tumblr);

    //Dropbox
    __Dictionary *dropboxConfigDict = __Dictionary::create();
    dropboxConfigDict -> setObject(String::create("7janx53ilz11gbs"), "app_key");
    dropboxConfigDict -> setObject(String::create("c1hpx5fz6tzkm32"), "app_secret");
    allPlatformConfigs -> setObject(dropboxConfigDict, PlatId::Dropbox);

    //Instagram
    __Dictionary *instagramConfigDict = __Dictionary::create();
    instagramConfigDict -> setObject(String::create("ff68e3216b4f4f989121aa1c2962d058"), "client_id");
    instagramConfigDict -> setObject(String::create("1b2e82f110264869b3505c3fe34e31a1"), "client_secret");
    instagramConfigDict -> setObject(String::create("http://sharesdk.cn"), "redirect_uri");
    allPlatformConfigs -> setObject(instagramConfigDict, PlatId::Instagram);

    //VK
    __Dictionary *vkConfigDict = __Dictionary::create();
    vkConfigDict -> setObject(String::create("3921561"), "application_id");
    vkConfigDict -> setObject(String::create("6Qf883ukLDyz4OBepYF1"), "secret_key");
    allPlatformConfigs -> setObject(vkConfigDict, PlatId::VKontakte);

	return allPlatformConfigs;
}
