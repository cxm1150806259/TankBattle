//
//  Props.cpp
//  Tank
//
//  Created by cstlab on 14-3-10.
//
//

#include "Props.h"

Props::Props()
{
}

Props::~Props()
{
}

void Props::initPropsWithPropsType(TileMapInfo* tileMapInfo)
{
    mTileMapInfo = tileMapInfo;
    moneySprit = CCSprite::create("flag.png");
    //初始化出现地点
    CCSize mapSize = mTileMapInfo->getTileMap()->getContentSize();
    CCSize tileSize = mTileMapInfo->getTileMap()->layerNamed("layer_0")->getMapTileSize();
    bornPoint[0] = ccp(tileSize.width+50, mapSize.height-tileSize.height);
    moneySprit->setPosition(bornPoint[0]);
    mTileMapInfo->getTileMap()->addChild(moneySprit);
    //动作结束监听
    CCMoveTo* moveAction = CCMoveTo::create(1.0f, bornPoint[0]);
    //回调对象，CCCallFunc也是一个动作，只不过这个动作是个回调函数
    CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Props::removeProps));
    CCSequence* action = CCSequence::create(moveAction,callFunc,NULL);
    moneySprit->runAction(action);
}

Props* Props::createPropsWithPropsType(TileMapInfo* tileMapInfo)
{
    Props* money = new Props();
    money->initPropsWithPropsType(tileMapInfo);
    money->autorelease();
    
    return money;
}

//移除道具
void Props::removeProps()
{
    mTileMapInfo->getTileMap()->removeChild(moneySprit);
    printf("remove money\n");
}