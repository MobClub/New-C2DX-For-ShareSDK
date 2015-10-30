#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:	
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    void authMenuItemClick(cocos2d::Ref* pSender);

    void cancelAuthMenuItemClick(cocos2d::Ref* pSender);

    void hasAuthMenuItemClick(cocos2d::Ref* pSender);

    void followFriendMenuItemClick(cocos2d::Ref* pSender);

    void getUserInfoMenuItemClick(cocos2d::Ref* pSender);

    void getFriendListMenuItemClick(cocos2d::Ref* pSender);

    void shareMenuItemClick(cocos2d::Ref* pSender);

    void shareForWechatTimeLineMenuItemClick(cocos2d::Ref* pSender);

    void getAuthInfoMenuItemClick(cocos2d::Ref* pSender);
};

#endif // __HELLOWORLD_SCENE_H__
