#include "HelloWorldScene.h"

#include "C2DXShareSDK.h"

USING_NS_CC;

using namespace std;
using namespace cn::sharesdk;

int reqID = 0;

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
    
    //授权
    MenuItemLabel *authItem = MenuItemLabel::create(LabelTTF::create("Authorize", "Arial", 10),
                                                    CC_CALLBACK_1(HelloWorld::authBtnClickHandler, this));
    authItem->setPosition(winSize.width/2 , 300);
    auto authMenu = Menu::create(authItem,NULL);
    authMenu->setPosition(Vec2::ZERO);
    this->addChild(authMenu);
    
    //是否授权
    MenuItemLabel *isAuthValid = MenuItemLabel::create(LabelTTF::create("is Auth Valid", "Arial", 10),
                                                       CC_CALLBACK_1(HelloWorld::isAuthValidBtnClickHandler, this));
    isAuthValid->setPosition(winSize.width/2 , 275);
    auto isAuthValidMenu = Menu::create(isAuthValid,NULL);
    isAuthValidMenu->setPosition(Vec2::ZERO);
    this->addChild(isAuthValidMenu);
    
    //取消授权
    MenuItemLabel *cancelAuthItem = MenuItemLabel::create(LabelTTF::create("Cancel Authorize", "Arial", 10),
                                                          CC_CALLBACK_1(HelloWorld::cancelAuthBtnClickHandler, this));
    cancelAuthItem->setPosition(winSize.width/2 , 250);
    auto cancelAuthMenu = Menu::create(cancelAuthItem,NULL);
    cancelAuthMenu->setPosition(Vec2::ZERO);
    this->addChild(cancelAuthMenu);
    
    //客户端是否安装
    MenuItemLabel *isClientInstalledItem = MenuItemLabel::create(LabelTTF::create("Is Client Installed", "Arial", 10),
                                                                 CC_CALLBACK_1(HelloWorld::isClientValidBtnClickHandler, this));
    isClientInstalledItem->setPosition(winSize.width/2 , 225);
    auto isClientInstalledMenu = Menu::create(isClientInstalledItem,NULL);
    isClientInstalledMenu->setPosition(Vec2::ZERO);
    this->addChild(isClientInstalledMenu);
    
    //获取用户信息
    MenuItemLabel *getUserInfoItem = MenuItemLabel::create(LabelTTF::create("Get User Info", "Arial", 10),
                                                           CC_CALLBACK_1(HelloWorld::getUserInfoBtnClickHandler, this));
    getUserInfoItem->setPosition(winSize.width/2 , 200);
    auto getUserInfoMenu = Menu::create(getUserInfoItem,NULL);
    getUserInfoMenu->setPosition(Vec2::ZERO);
    this->addChild(getUserInfoMenu);
    
    //获取授权信息
    MenuItemLabel *getAuthInfoItem = MenuItemLabel::create(LabelTTF::create("Get Auth Info", "Arial", 10),
                                                           CC_CALLBACK_1(HelloWorld::getAuthInfoBtnClickHandler, this));
    getAuthInfoItem->setPosition(winSize.width/2 , 175);
    auto getAuthInfoMenu = Menu::create(getAuthInfoItem,NULL);
    getAuthInfoMenu->setPosition(Vec2::ZERO);
    this->addChild(getAuthInfoMenu);
    
    //直接分享
    auto shareItem = MenuItemLabel::create(LabelTTF::create("Share Directly", "Arial", 10),
                                           CC_CALLBACK_1(HelloWorld::shareContentClickHandler, this));
    shareItem->setPosition(winSize.width/2 , 150);
    
    auto itemsMenu = Menu::create(shareItem,NULL);
    itemsMenu->setPosition(Vec2::ZERO);
    this->addChild(itemsMenu);
    
    //分享菜单
    MenuItemLabel *shareMenuItem = MenuItemLabel::create(LabelTTF::create("Show Share Menu", "Arial", 10),
                                                         CC_CALLBACK_1(HelloWorld::showShareMenuClickHandler, this));
    shareMenuItem->setPosition(Director::getInstance()->getWinSize().width/2 , 125);
    auto shareMenu = Menu::create(shareMenuItem,NULL);
    shareMenu->setPosition(Vec2::ZERO);
    this->addChild(shareMenu);
    
    //显示分享编辑页面
    MenuItemLabel *shareEditItem = MenuItemLabel::create(LabelTTF::create("Show Share Edit View", "Arial", 10),
                                                         CC_CALLBACK_1(HelloWorld::showShareViewClickHandler, this));
    shareEditItem->setPosition(winSize.width/2 , 100);
    auto shareEditItemMenu = Menu::create(shareEditItem,NULL);
    shareEditItemMenu->setPosition(Vec2::ZERO);
    this->addChild(shareEditItemMenu);
    
    //获取好友列表
    MenuItemLabel *getFriendList = MenuItemLabel::create(LabelTTF::create("Get Friend List", "Arial", 10),
                                                         CC_CALLBACK_1(HelloWorld::getFriendListBtnClickHandler, this));
    getFriendList->setPosition(winSize.width/2 , 75);
    auto getFriendListMenu = Menu::create(getFriendList,NULL);
    getFriendListMenu->setPosition(Vec2::ZERO);
    this->addChild(getFriendListMenu);
    
    //添加好友
    MenuItemLabel *addFriend = MenuItemLabel::create(LabelTTF::create("Add Friend", "Arial", 10),
                                                     CC_CALLBACK_1(HelloWorld::addFriendBtnClickHandler, this));
    addFriend->setPosition(winSize.width/2 , 50);
    auto addFriendMenu = Menu::create(addFriend,NULL);
    addFriendMenu->setPosition(Vec2::ZERO);
    this->addChild(addFriendMenu);
    
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
    reqID += 1;
    
    __Dictionary *content = __Dictionary::create();
    content -> setObject(__String::create("分享文本"), "text");
    content -> setObject(__String::create("HelloWorld.png"), "image");
    content -> setObject(__String::create("测试标题"), "title");
    content -> setObject(__String::create("http://www.mob.com"), "url");
    content -> setObject(__String::createWithFormat("%d", cn::sharesdk::C2DXContentTypeAuto), "type");
    
//可以自定义分享平台，如果平台传入NULL，此时显示所有初始化的平台
//    C2DXArray *platforms = C2DXArray::create();
//    __Integer *sina = new __Integer(cn::sharesdk::C2DXPlatTypeSinaWeibo);
//    __Integer *tencent = new __Integer(cn::sharesdk::C2DXPlatTypeTencentWeibo);
//    __Integer *wechat = new __Integer(cn::sharesdk::C2DXPlatTypeWechatPlatform);
//    __Integer *qq = new __Integer(cn::sharesdk::C2DXPlatTypeQQPlatform);
//    __Integer *fb = new __Integer(cn::sharesdk::C2DXPlatTypeFacebook);
//    __Integer *tw = new __Integer(cn::sharesdk::C2DXPlatTypeTwitter);
//    __Integer *mail = new __Integer(cn::sharesdk::C2DXPlatTypeMail);
//
//    platforms->addObject(sina);
//    platforms->addObject(tencent);
//    platforms->addObject(wechat);
//    platforms->addObject(qq);
//    platforms->addObject(fb);
//    platforms->addObject(tw);
//    platforms->addObject(mail);
    
    C2DXShareSDK::showShareMenu(reqID,NULL,content,100,100,shareContentResultHandler);
}

void HelloWorld::authBtnClickHandler(cocos2d::Ref* pSender)
{
    reqID += 1;
    C2DXShareSDK::authorize(reqID,cn::sharesdk::C2DXPlatTypeFacebook, authResultHandler);
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
    reqID += 1;
    C2DXShareSDK::getUserInfo(reqID, cn::sharesdk::C2DXPlatTypeSinaWeibo, getUserResultHandler);
}

void HelloWorld::getAuthInfoBtnClickHandler(cocos2d::Ref *pSender)
{
    log("Use getUserInfo method instead.");
}

void HelloWorld::shareContentClickHandler(cocos2d::Ref *pSender)
{
    reqID += 1;
    
    //分享内容
    __Dictionary *content = __Dictionary::create();
    content -> setObject(__String::create("分享文本"), "text");
    content -> setObject(__String::create("HelloWorld.png"), "image");
    content -> setObject(__String::create("测试标题"), "title");
    content -> setObject(__String::create("http://www.mob.com"), "url");
    content -> setObject(__String::createWithFormat("%d", cn::sharesdk::C2DXContentTypeWebPage), "type");
    
    C2DXShareSDK::shareContent(reqID, cn::sharesdk::C2DXPlatTypeSinaWeibo, content, shareContentResultHandler);
}

void HelloWorld::oneKeyShareContentClickHandler(cocos2d::Ref *pSender)
{
    reqID += 1;
    
    //分享内容
    __Dictionary *content = __Dictionary::create();
    content -> setObject(__String::create("分享文本"), "text");
    content -> setObject(__String::create("HelloWorld.png"), "image");
    content -> setObject(__String::create("测试标题"), "title");
    content -> setObject(__String::create("http://www.mob.com"), "url");
    content -> setObject(__String::createWithFormat("%d", cn::sharesdk::C2DXContentTypeWebPage), "type");
    
    //分享平台
    C2DXArray *platforms = C2DXArray::create();
    __Integer *sina = new __Integer(cn::sharesdk::C2DXPlatTypeSinaWeibo);
    platforms->addObject(sina);
    __Integer *tencent = new __Integer(cn::sharesdk::C2DXPlatTypeTencentWeibo);
    platforms->addObject(tencent);
    
    //一键分享
    C2DXShareSDK::oneKeyShareContent(reqID, platforms, content, shareContentResultHandler);
}

void HelloWorld::showShareViewClickHandler(cocos2d::Ref *pSender)
{
    reqID += 1;
    
    //分享内容
    __Dictionary *content = __Dictionary::create();
    content -> setObject(__String::create("分享文本"), "text");
    content -> setObject(__String::create("HelloWorld.png"), "image");
    content -> setObject(__String::create("测试标题"), "title");
    content -> setObject(__String::create("http://www.mob.com"), "url");
    content -> setObject(__String::createWithFormat("%d", cn::sharesdk::C2DXContentTypeWebPage), "type");
    
    C2DXShareSDK::showShareView(reqID, cn::sharesdk::C2DXPlatTypeSinaWeibo, content, shareContentResultHandler);
}

void HelloWorld::getFriendListBtnClickHandler(cocos2d::Ref *pSender)
{
    reqID += 1;
    
    C2DXShareSDK::getFriendList(reqID, cn::sharesdk::C2DXPlatTypeSinaWeibo, 5, 1, getFriendListResultHandler);
}

void HelloWorld::addFriendBtnClickHandler(cocos2d::Ref *pSender)
{
    reqID += 1;
    
    C2DXShareSDK::addFriend(reqID, cn::sharesdk::C2DXPlatTypeTencentWeibo, "ShareSDK", addFriendResultHandler);
}
