#include "HelloWorldScene.h"

#include "C2DXShareSDK.h"

USING_NS_CC;

using namespace std;
using namespace cn::sharesdk;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //使用分享编辑页面＋配置文件分享
    MenuItemLabel *showShareViewWithConFile = MenuItemLabel::create(LabelTTF::create("Show share view with configuration file(iOS Only)", "Arial", 10),
                                                                    CC_CALLBACK_1(HelloWorld::showShareViewWithConFileBtnClickHandler, this));
    showShareViewWithConFile->setPosition(winSize.width/2 , winSize.height / 10 * 9);
    auto showShareViewWithConFileMenu = Menu::create(showShareViewWithConFile,NULL);
    showShareViewWithConFileMenu->setPosition(Vec2::ZERO);
    this->addChild(showShareViewWithConFileMenu);
    
    //使用配置文件＋分享菜单栏分享(可选-自定义字段)
    MenuItemLabel *showActionMenuWithConFile = MenuItemLabel::create(LabelTTF::create("Show action menu with configuration file(iOS Only)", "Arial", 10),
                                                                     CC_CALLBACK_1(HelloWorld::showShareMenuWithConFileBtnClickHandler, this));
    showActionMenuWithConFile->setPosition(winSize.width/2 , winSize.height / 10 * 8);
    auto showActionMenuWithConFileMenu = Menu::create(showActionMenuWithConFile,NULL);
    showActionMenuWithConFileMenu->setPosition(Vec2::ZERO);
    this->addChild(showActionMenuWithConFileMenu);
    
    //根据配置文件分享
    MenuItemLabel *shareWithConFile = MenuItemLabel::create(LabelTTF::create("Share with Configuration file(iOS Only)", "Arial", 10),
                                                            CC_CALLBACK_1(HelloWorld::shareWithConFileBtnClickHandler, this));
    shareWithConFile->setPosition(winSize.width/2 , winSize.height / 10 * 7);
    auto shareWithConFileMenu = Menu::create(shareWithConFile,NULL);
    shareWithConFileMenu->setPosition(Vec2::ZERO);
    this->addChild(shareWithConFileMenu);

    //授权
    MenuItemLabel *authItem = MenuItemLabel::create(LabelTTF::create("Authorize", "Arial", 10),
                                                    CC_CALLBACK_1(HelloWorld::authBtnClickHandler, this));
    authItem->setPosition(authItem->getContentSize().width / 2 + winSize.width / 6 * 1 , winSize.height / 10 * 6);
    auto authMenu = Menu::create(authItem,NULL);
    authMenu->setPosition(Vec2::ZERO);
    this->addChild(authMenu);
    
    //是否授权
    MenuItemLabel *isAuthValid = MenuItemLabel::create(LabelTTF::create("is Auth Valid", "Arial", 10),
                                                       CC_CALLBACK_1(HelloWorld::isAuthValidBtnClickHandler, this));
    isAuthValid->setPosition(isAuthValid->getContentSize().width / 2 + winSize.width / 6 * 4 , winSize.height / 10 * 6);
    auto isAuthValidMenu = Menu::create(isAuthValid,NULL);
    isAuthValidMenu->setPosition(Vec2::ZERO);
    this->addChild(isAuthValidMenu);
    
    //取消授权
    MenuItemLabel *cancelAuthItem = MenuItemLabel::create(LabelTTF::create("Cancel Authorize", "Arial", 10),
                                                          CC_CALLBACK_1(HelloWorld::cancelAuthBtnClickHandler, this));
    cancelAuthItem->setPosition(cancelAuthItem->getContentSize().width / 2 + winSize.width / 6 * 1, winSize.height / 10 * 5);
    auto cancelAuthMenu = Menu::create(cancelAuthItem,NULL);
    cancelAuthMenu->setPosition(Vec2::ZERO);
    this->addChild(cancelAuthMenu);
    
    //客户端是否安装
    MenuItemLabel *isClientInstalledItem = MenuItemLabel::create(LabelTTF::create("Is Client Installed", "Arial", 10),
                                                                 CC_CALLBACK_1(HelloWorld::isClientValidBtnClickHandler, this));
    isClientInstalledItem->setPosition(isClientInstalledItem->getContentSize().width / 2 + winSize.width / 6 * 4, winSize.height / 10 * 5);
    auto isClientInstalledMenu = Menu::create(isClientInstalledItem,NULL);
    isClientInstalledMenu->setPosition(Vec2::ZERO);
    this->addChild(isClientInstalledMenu);
    
    //获取用户信息
    MenuItemLabel *getUserInfoItem = MenuItemLabel::create(LabelTTF::create("Get User Info", "Arial", 10),
                                                           CC_CALLBACK_1(HelloWorld::getUserInfoBtnClickHandler, this));
    getUserInfoItem->setPosition(getUserInfoItem->getContentSize().width / 2 + winSize.width / 6 * 1, winSize.height / 10 * 4);
    auto getUserInfoMenu = Menu::create(getUserInfoItem,NULL);
    getUserInfoMenu->setPosition(Vec2::ZERO);
    this->addChild(getUserInfoMenu);
    
    //获取授权信息
    MenuItemLabel *getAuthInfoItem = MenuItemLabel::create(LabelTTF::create("Get Auth Info", "Arial", 10),
                                                           CC_CALLBACK_1(HelloWorld::getAuthInfoBtnClickHandler, this));
    getAuthInfoItem->setPosition(getAuthInfoItem->getContentSize().width / 2 + winSize.width / 6 * 4, winSize.height / 10 * 4);
    auto getAuthInfoMenu = Menu::create(getAuthInfoItem,NULL);
    getAuthInfoMenu->setPosition(Vec2::ZERO);
    this->addChild(getAuthInfoMenu);
    
    //直接分享
    auto shareItem = MenuItemLabel::create(LabelTTF::create("Share Directly", "Arial", 10),
                                           CC_CALLBACK_1(HelloWorld::shareContentClickHandler, this));
    shareItem->setPosition(shareItem->getContentSize().width / 2 + winSize.width / 6 * 1, winSize.height / 10 * 3);
    
    auto itemsMenu = Menu::create(shareItem,NULL);
    itemsMenu->setPosition(Vec2::ZERO);
    this->addChild(itemsMenu);
    
    //分享菜单
    MenuItemLabel *shareMenuItem = MenuItemLabel::create(LabelTTF::create("Show Share Menu", "Arial", 10),
                                                         CC_CALLBACK_1(HelloWorld::showShareMenuClickHandler, this));
    shareMenuItem->setPosition(shareMenuItem->getContentSize().width / 2 + winSize.width / 6 * 4, winSize.height / 10 * 3);
    auto shareMenu = Menu::create(shareMenuItem,NULL);
    shareMenu->setPosition(Vec2::ZERO);
    this->addChild(shareMenu);
    
    //显示分享编辑页面
    MenuItemLabel *shareEditItem = MenuItemLabel::create(LabelTTF::create("Show Share Edit View", "Arial", 10),
                                                         CC_CALLBACK_1(HelloWorld::showShareViewClickHandler, this));
    shareEditItem->setPosition(shareEditItem->getContentSize().width / 2 + winSize.width / 6 * 1, winSize.height / 10 * 2);
    auto shareEditItemMenu = Menu::create(shareEditItem,NULL);
    shareEditItemMenu->setPosition(Vec2::ZERO);
    this->addChild(shareEditItemMenu);
    
    //获取好友列表
    MenuItemLabel *getFriendList = MenuItemLabel::create(LabelTTF::create("Get Friend List", "Arial", 10),
                                                         CC_CALLBACK_1(HelloWorld::getFriendListBtnClickHandler, this));
    getFriendList->setPosition(getFriendList->getContentSize().width / 2 + winSize.width / 6 * 4, winSize.height / 10 * 2);
    auto getFriendListMenu = Menu::create(getFriendList,NULL);
    getFriendListMenu->setPosition(Vec2::ZERO);
    this->addChild(getFriendListMenu);
    
    //添加好友
    MenuItemLabel *addFriend = MenuItemLabel::create(LabelTTF::create("Add Friend", "Arial", 10),
                                                     CC_CALLBACK_1(HelloWorld::addFriendBtnClickHandler, this));
    addFriend->setPosition(addFriend->getContentSize().width / 2 + winSize.width / 6 * 1, winSize.height / 10 * 1);
    auto addFriendMenu = Menu::create(addFriend,NULL);
    addFriendMenu->setPosition(Vec2::ZERO);
    this->addChild(addFriendMenu);

    //添加好友
        MenuItemLabel *smsAuthorize = MenuItemLabel::create(LabelTTF::create("SMS Authorize", "Arial", 10),
                                                         CC_CALLBACK_1(HelloWorld::authToSMS, this));
        smsAuthorize->setPosition(smsAuthorize->getContentSize().width / 2 + winSize.width / 6 * 4, winSize.height / 10 * 1);
        auto smsAuthorizeMenu = Menu::create(smsAuthorize,NULL);
        smsAuthorizeMenu->setPosition(Vec2::ZERO);
        this->addChild(smsAuthorizeMenu);

    return true;
}

//分享回调
void shareContentResultHandler(int seqId, cn::sharesdk::C2DXResponseState state, cn::sharesdk::C2DXPlatType platType, __Dictionary *result)
{
    switch (state)
    {
        case cn::sharesdk::C2DXResponseStateSuccess:
        {
            log("Success");
        }
            break;
        case cn::sharesdk::C2DXResponseStateFail:
        {
            log("Fail");
            //回调错误信息
            __Array *allKeys = result->allKeys();
            allKeys->retain();
            for (int i = 0; i < allKeys-> count(); i++)
            {
                __String *key = (__String*)allKeys->getObjectAtIndex(i);
                Ref *obj = result->objectForKey(key->getCString());
                
                log("key = %s", key -> getCString());
                if (dynamic_cast<__String *>(obj))
                {
                    log("value = %s", dynamic_cast<__String *>(obj) -> getCString());
                }
                else if (dynamic_cast<__Integer *>(obj))
                {
                    log("value = %d", dynamic_cast<__Integer *>(obj) -> getValue());
                }
                else if (dynamic_cast<__Double *>(obj))
                {
                    log("value = %f", dynamic_cast<__Double *>(obj) -> getValue());
                }
            }
        }
            break;
        case cn::sharesdk::C2DXResponseStateCancel:
        {
            log("Cancel");
        }
            break;
        default:
            break;
    }
}

//授权回调
void authResultHandler(int seqId, cn::sharesdk::C2DXResponseState state, cn::sharesdk::C2DXPlatType platType, __Dictionary *result)
{
    switch (state)
    {
        case cn::sharesdk::C2DXResponseStateSuccess:
        {
            log("Success");
            
            //输出信息
            try
            {
                __Array *allKeys = result -> allKeys();
                allKeys->retain();
                for (int i = 0; i < allKeys -> count(); i++)
                {
                    __String *key = (__String *)allKeys -> getObjectAtIndex(i);
                    Ref *obj = result -> objectForKey(key -> getCString());
                    
                    log("key = %s", key -> getCString());
                    if (dynamic_cast<__String *>(obj))
                    {
                        log("value = %s", dynamic_cast<__String *>(obj) -> getCString());
                    }
                    else if (dynamic_cast<__Integer *>(obj))
                    {
                        log("value = %d", dynamic_cast<__Integer *>(obj) -> getValue());
                    }
                    else if (dynamic_cast<__Double *>(obj))
                    {
                        log("value = %f", dynamic_cast<__Double *>(obj) -> getValue());
                    }
                }
                allKeys->release();
            }
            catch(...)
            {
                log("==============error");
            }
        }
            break;
        case cn::sharesdk::C2DXResponseStateFail:
        {
            log("Fail");
            //回调错误信息
            __Array *allKeys = result->allKeys();
            allKeys->retain();
            for (int i = 0; i < allKeys-> count(); i++)
            {
                __String *key = (__String*)allKeys->getObjectAtIndex(i);
                Ref *obj = result->objectForKey(key->getCString());
                
                log("key = %s", key -> getCString());
                if (dynamic_cast<__String *>(obj))
                {
                    log("value = %s", dynamic_cast<__String *>(obj) -> getCString());
                }
                else if (dynamic_cast<__Integer *>(obj))
                {
                    log("value = %d", dynamic_cast<__Integer *>(obj) -> getValue());
                }
                else if (dynamic_cast<__Double *>(obj))
                {
                    log("value = %f", dynamic_cast<__Double *>(obj) -> getValue());
                }
            }
        }
            break;
        case cn::sharesdk::C2DXResponseStateCancel:
        {
            log("Cancel");
        }
            break;
        default:
            break;
    }
}

//获取用户信息结果回调
void getUserResultHandler(int reqID, C2DXResponseState state, C2DXPlatType platType, __Dictionary *result)
{
    switch (state)
    {
        case cn::sharesdk::C2DXResponseStateSuccess:
        {
            log("Success");
            
            //输出信息
            try
            {
                __Array *allKeys = result -> allKeys();
                allKeys->retain();
                for (int i = 0; i < allKeys -> count(); i++)
                {
                    __String *key = (__String *)allKeys -> getObjectAtIndex(i);
                    Ref *obj = result -> objectForKey(key -> getCString());
                    
                    log("key = %s", key -> getCString());
                    if (dynamic_cast<__String *>(obj))
                    {
                        log("value = %s", dynamic_cast<__String *>(obj) -> getCString());
                    }
                    else if (dynamic_cast<__Integer *>(obj))
                    {
                        log("value = %d", dynamic_cast<__Integer *>(obj) -> getValue());
                    }
                    else if (dynamic_cast<__Double *>(obj))
                    {
                        log("value = %f", dynamic_cast<__Double *>(obj) -> getValue());
                    }
                }
                allKeys->release();
            }
            catch(...)
            {
                log("==============error");
            }
        }
            break;
        case cn::sharesdk::C2DXResponseStateFail:
        {
            log("Fail");
            //回调错误信息
            __Array *allKeys = result->allKeys();
            allKeys->retain();
            for (int i = 0; i < allKeys-> count(); i++)
            {
                __String *key = (__String*)allKeys->getObjectAtIndex(i);
                Ref *obj = result->objectForKey(key->getCString());
                
                log("key = %s", key -> getCString());
                if (dynamic_cast<__String *>(obj))
                {
                    log("value = %s", dynamic_cast<__String *>(obj) -> getCString());
                }
                else if (dynamic_cast<__Integer *>(obj))
                {
                    log("value = %d", dynamic_cast<__Integer *>(obj) -> getValue());
                }
                else if (dynamic_cast<__Double *>(obj))
                {
                    log("value = %f", dynamic_cast<__Double *>(obj) -> getValue());
                }
            }
        }
            break;
        case cn::sharesdk::C2DXResponseStateCancel:
        {
            log("Cancel");
        }
            break;
        default:
            break;
    }
}

void getFriendListResultHandler(int reqID, C2DXResponseState state, C2DXPlatType platType, __Dictionary *result)
{
    switch (state)
    {
        case cn::sharesdk::C2DXResponseStateSuccess:
        {
            log("Success");
            
            //输出信息
            try
            {
                __Array *allKeys = result -> allKeys();
                allKeys->retain();
                for (int i = 0; i < allKeys -> count(); i++)
                {
                    __String *key = (__String *)allKeys -> getObjectAtIndex(i);
                    Ref *obj = result -> objectForKey(key -> getCString());
                    
                    log("key = %s", key -> getCString());
                    if (dynamic_cast<__String *>(obj))
                    {
                        log("value = %s", dynamic_cast<__String *>(obj) -> getCString());
                    }
                    else if (dynamic_cast<__Integer *>(obj))
                    {
                        log("value = %d", dynamic_cast<__Integer *>(obj) -> getValue());
                    }
                    else if (dynamic_cast<__Double *>(obj))
                    {
                        log("value = %f", dynamic_cast<__Double *>(obj) -> getValue());
                    }
                }
                allKeys->release();
            }
            catch(...)
            {
                log("==============error");
            }
        }
            break;
        case cn::sharesdk::C2DXResponseStateFail:
        {
            log("Fail");
            //回调错误信息
            __Array *allKeys = result->allKeys();
            allKeys->retain();
            for (int i = 0; i < allKeys-> count(); i++)
            {
                __String *key = (__String*)allKeys->getObjectAtIndex(i);
                Ref *obj = result->objectForKey(key->getCString());
                
                log("key = %s", key -> getCString());
                if (dynamic_cast<__String *>(obj))
                {
                    log("value = %s", dynamic_cast<__String *>(obj) -> getCString());
                }
                else if (dynamic_cast<__Integer *>(obj))
                {
                    log("value = %d", dynamic_cast<__Integer *>(obj) -> getValue());
                }
                else if (dynamic_cast<__Double *>(obj))
                {
                    log("value = %f", dynamic_cast<__Double *>(obj) -> getValue());
                }
            }
        }
            break;
        case cn::sharesdk::C2DXResponseStateCancel:
        {
            log("Cancel");
        }
            break;
        default:
            break;
    }
}

void addFriendResultHandler(int reqID, C2DXResponseState state, C2DXPlatType platType, __Dictionary *result)
{
    switch (state)
    {
        case cn::sharesdk::C2DXResponseStateSuccess:
        {
            log("Success");
        }
            break;
        case cn::sharesdk::C2DXResponseStateFail:
        {
            log("Fail");
            //回调错误信息
            __Array *allKeys = result->allKeys();
            allKeys->retain();
            for (int i = 0; i < allKeys-> count(); i++)
            {
                __String *key = (__String*)allKeys->getObjectAtIndex(i);
                Ref *obj = result->objectForKey(key->getCString());
                
                log("key = %s", key -> getCString());
                if (dynamic_cast<__String *>(obj))
                {
                    log("value = %s", dynamic_cast<__String *>(obj) -> getCString());
                }
                else if (dynamic_cast<__Integer *>(obj))
                {
                    log("value = %d", dynamic_cast<__Integer *>(obj) -> getValue());
                }
                else if (dynamic_cast<__Double *>(obj))
                {
                    log("value = %f", dynamic_cast<__Double *>(obj) -> getValue());
                }
            }
        }
            break;
        case cn::sharesdk::C2DXResponseStateCancel:
        {
            log("Cancel");
        }
            break;
        default:
            break;
    }
}

void HelloWorld::showShareMenuClickHandler(cocos2d::Ref* pSender)
{    
    __Dictionary *content = __Dictionary::create();

    __Array *imageArray = __Array::create();
    imageArray ->addObject(__String::create("/sdcard/test.jpg"));
    imageArray ->addObject(__String::create("http://f1.webshare.mob.com/dimgs/1c950a7b02087bf41bc56f07f7d3572c11dfcf36.jpg"));
    imageArray ->addObject(__String::create("/sdcard/test.jpg"));

    content -> setObject(imageArray, "imageArray");
    content -> setObject(__String::create("分享文本"), "text");
    content -> setObject(__String::create("http://f1.webshare.mob.com/dimgs/1c950a7b02087bf41bc56f07f7d3572c11dfcf36.jpg"), "image");
    content -> setObject(__String::create("测试标题"), "title");
    content -> setObject(__String::create("http://www.mob.com"), "url");
    content -> setObject(__String::createWithFormat("%d", cn::sharesdk::C2DXContentTypeAuto), "type");
    //iOS 启用客户端分享接口
    //content -> setObject(__String::createWithFormat("%d", true), "client_share");
    //iOS 启用微博高级分享接口 3.6.3以后版本支持
    //content -> setObject(__String::createWithFormat("%d", true), "advanced_share");
    
    C2DXShareSDK::showShareMenu(NULL,content,100,100, shareContentResultHandler);
    
}

void HelloWorld::authBtnClickHandler(cocos2d::Ref* pSender)
{
	C2DXShareSDK::disableSSOWhenAuthorize(false);
    C2DXShareSDK::authorize(cn::sharesdk::C2DXPlatTypeSinaWeibo, authResultHandler);
}

void HelloWorld::isAuthValidBtnClickHandler(cocos2d::Ref *pSender)
{
    bool isAuthValid = C2DXShareSDK::isAuthorizedValid(cn::sharesdk::C2DXPlatTypeSinaWeibo);
    log("isAuthValid: %i",isAuthValid);
}

void HelloWorld::cancelAuthBtnClickHandler(cocos2d::Ref *pSender)
{
    C2DXShareSDK::cancelAuthorize(cn::sharesdk::C2DXPlatTypeSinaWeibo);
}

void HelloWorld::isClientValidBtnClickHandler(cocos2d::Ref *pSender)
{
    bool isClientValid = C2DXShareSDK::isClientValid(cn::sharesdk::C2DXPlatTypeSinaWeibo);
    log("isAuthValid: %i",isClientValid);
}

void HelloWorld::getUserInfoBtnClickHandler(cocos2d::Ref *pSender)
{
    C2DXShareSDK::getUserInfo(cn::sharesdk::C2DXPlatTypeSinaWeibo, getUserResultHandler);
}

void HelloWorld::getAuthInfoBtnClickHandler(cocos2d::Ref *pSender)
{
    log("Use getUserInfo method instead.");
}

void HelloWorld::shareContentClickHandler(cocos2d::Ref *pSender)
{    
//    //分享内容
//    __Dictionary *content = __Dictionary::create();
//    content -> setObject(__String::create("分享文本"), "text");
//    content -> setObject(__String::create("http://www.mob.com/mob/img/navproducts_03.png"), "image");
//    content -> setObject(__String::create("测试标题"), "title");
//    content -> setObject(__String::create("http://www.mob.com"), "url");
//    content -> setObject(__String::createWithFormat("%d", cn::sharesdk::C2DXContentTypeAuto), "type");
//    //iOS 启用客户端分享接口
//    content -> setObject(__String::createWithFormat("%d", true), "client_share");
//    //iOS 启用微博高级分享接口 3.6.3以后版本支持
//    content -> setObject(__String::createWithFormat("%d", true), "advanced_share");
//
//    C2DXShareSDK::shareContent(cn::sharesdk::C2DXPlatTypeFacebook, content, shareContentResultHandler);
    
    
    // 新浪微博LinkCard分享 其他分享请使用上面👆方式
    __Dictionary *content = __Dictionary::create();
    content -> setObject(__String::create("测试微博LinkCard功能"), "text");
    content -> setObject(__String::create("http://www.mob.com/assets/images/ShareSDK_pic_1-09d293a6.png"), "image");
    content -> setObject(__String::createWithFormat("%d", true), "sina_linkCard");
    content -> setObject(__String::create("这是Title"), "sina_cardTitle");
    content -> setObject(__String::create("这是Summary"), "sina_cardSummary");
    content -> setObject(__String::createWithFormat("%d", cn::sharesdk::C2DXContentTypeWebPage), "type");
    C2DXShareSDK::shareContent(cn::sharesdk::C2DXPlatTypeSinaWeibo, content, shareContentResultHandler);
}

void HelloWorld::oneKeyShareContentClickHandler(cocos2d::Ref *pSender)
{    
    //分享内容
    __Dictionary *content = __Dictionary::create();
    content -> setObject(__String::create("分享文本"), "text");
    content -> setObject(__String::create("http://f1.webshare.mob.com/dimgs/1c950a7b02087bf41bc56f07f7d3572c11dfcf36.jpg"), "image");
    content -> setObject(__String::create("测试标题"), "title");
    content -> setObject(__String::create("http://www.mob.com"), "url");
    content -> setObject(__String::createWithFormat("%d", cn::sharesdk::C2DXContentTypeImage), "type");
    
    //分享平台
    C2DXArray *platforms = C2DXArray::create();
    __Integer *sina = new __Integer(cn::sharesdk::C2DXPlatTypeSinaWeibo);
    platforms->addObject(sina);
    __Integer *tencent = new __Integer(cn::sharesdk::C2DXPlatTypeTencentWeibo);
    platforms->addObject(tencent);
    
    //一键分享
    C2DXShareSDK::oneKeyShareContent(platforms, content, shareContentResultHandler);
}

void HelloWorld::showShareViewClickHandler(cocos2d::Ref *pSender)
{    
    //分享内容
    __Dictionary *content = __Dictionary::create();
    content -> setObject(__String::create("分享文本"), "text");
    content -> setObject(__String::create("http://f1.webshare.mob.com/dimgs/1c950a7b02087bf41bc56f07f7d3572c11dfcf36.jpg"), "image");
    content -> setObject(__String::create("测试标题"), "title");
    content -> setObject(__String::create("http://www.mob.com"), "url");
    content -> setObject(__String::createWithFormat("%d", cn::sharesdk::C2DXContentTypeImage), "type");
    //iOS 启用客户端分享接口
    content -> setObject(__String::createWithFormat("%d", true), "client_share");
    
    //    //iOS 启用微博高级分享接口 3.6.3以后版本支持 v4.0.1弃用
    //    content -> setObject(__String::createWithFormat("%d", true), "advanced_share");
    
    //iOS 启用微博API接口进行分享
    content -> setObject(__String::createWithFormat("%d", true), "api_share");
    
    C2DXShareSDK::showShareView(cn::sharesdk::C2DXPlatTypeSinaWeibo, content, shareContentResultHandler);
    
    
    
}

void HelloWorld::getFriendListBtnClickHandler(cocos2d::Ref *pSender)
{    
    C2DXShareSDK::getFriendList(cn::sharesdk::C2DXPlatTypeSinaWeibo, 5, 1, getFriendListResultHandler);
}

void HelloWorld::addFriendBtnClickHandler(cocos2d::Ref *pSender)
{    
    C2DXShareSDK::addFriend(cn::sharesdk::C2DXPlatTypeTencentWeibo, "ShareSDK", addFriendResultHandler);
}

void HelloWorld::shareWithConFileBtnClickHandler(cocos2d::Ref *pSender)
{
    C2DXShareSDK::shareWithConfigurationFile("ShareSDK", cn::sharesdk::C2DXPlatTypeQQ, NULL, shareContentResultHandler);
}

void HelloWorld::showShareMenuWithConFileBtnClickHandler(cocos2d::Ref *pSender)
{
    __Dictionary *customFields = __Dictionary::create();
    customFields -> setObject(__String::create("http://www.mob.com/mob/images/sharesdk/analysis-logo.png"), "imgUrl");
    
    C2DXShareSDK::showShareMenuWithConfigurationFile(NULL,100,100, "ShareSDK", customFields, shareContentResultHandler);
}

void HelloWorld::showShareViewWithConFileBtnClickHandler(cocos2d::Ref *pSender)
{
    __Dictionary *customFields = __Dictionary::create();
    customFields -> setObject(__String::create("http://www.mob.com/mob/images/sharesdk/analysis-logo.png"), "imgUrl");
    
    C2DXShareSDK::showShareViewWithConfigurationFile(cn::sharesdk::C2DXPlatTypeSinaWeibo, "ShareSDK", customFields, shareContentResultHandler);
}

void HelloWorld::authToSMS(cocos2d::Ref* pSender)
{
    C2DXShareSDK::authorize(cn::sharesdk::C2DXPlatTypeSMS, authResultHandler);
}
