#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    //授权
    void authBtnClickHandler(cocos2d::Ref* pSender);
    
    //是否授权
    void isAuthValidBtnClickHandler(cocos2d::Ref* pSender);
    
    //取消授权
    void cancelAuthBtnClickHandler(cocos2d::Ref* pSender);
    
    //客户端是否安装
    void isClientValidBtnClickHandler(cocos2d::Ref* pSender);
    
    //获取用户信息
    void getUserInfoBtnClickHandler(cocos2d::Ref* pSender);
    
    //获取授权信息
    void getAuthInfoBtnClickHandler(cocos2d::Ref* pSender);
    
    //直接分享
    void shareContentClickHandler(cocos2d::Ref* pSender);
    
    //一键分享
    void oneKeyShareContentClickHandler(cocos2d::Ref* pSender);
    
    //分享菜单
    void showShareMenuClickHandler(cocos2d::Ref* pSender);
    
    //显示分享编辑页面
    void showShareViewClickHandler(cocos2d::Ref* pSender);
    
    //获取好友列表
    void getFriendListBtnClickHandler(cocos2d::Ref* pSender);
    
    //加为好友
    void addFriendBtnClickHandler(cocos2d::Ref* pSender);
    
    CREATE_FUNC(HelloWorld);
};

#endif 
