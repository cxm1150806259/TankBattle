//
//  GameOver.cpp
//  Tank
//
//  Created by zyf on 14-3-5.
//
//

#include "GameOver.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
CCScene *GameOver::scene()
{
    CCScene *scene=CCScene::create();
    GameOver *layer=GameOver::create();
    if (scene&&layer) {
        scene->addChild(layer);
    }
    return scene;
}

bool GameOver::init()
{
    if (!CCLayer::init())
        return false;
    SimpleAudioEngine::sharedEngine()->playEffect("gameover.wav");
    CCSize wSize=CCDirector::sharedDirector()->getWinSize();
//    CCSprite *pSprite=CCSprite::create("over.png");
//    pSprite->setPosition(ccp(szWin.width/2, szWin.height/2));
//    CCSize szSprite=pSprite->getContentSize();
//    pSprite->setScaleX(0.5*szWin.width/szSprite.width);
//    pSprite->setScaleY(0.5*szWin.height/szSprite.height);
//    this->addChild(pSprite,0);
    CCSprite *logoSprite=CCSprite::create("BattleCity.png");
    
    
    logoSprite->setPosition(ccp(wSize.width/2, wSize.height/2+100));
    
    logoSprite->setScale(2.0f);
    this->addChild(logoSprite, 1);
    //创建菜单
    CCMenuItemFont *startItem=CCMenuItemFont::create("游戏结束", this,menu_selector(GameOver::backToScene));
    
    startItem->setPosition(ccp(wSize.width/2, wSize.height/2-100));
    startItem->setFontSizeObj(55);
    startItem->setFontNameObj("Georgia-Bold");
    
    CCMenu *pMenu = CCMenu::create(startItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    
    
    return true;
}
void GameOver::backToScene()
{
    //场景转换
    CCScene *pScene = HelloWorld::scene();
    //跳跃式动画
    CCDirector::sharedDirector()->replaceScene(CCTransitionJumpZoom::create(1.2f, pScene));
}