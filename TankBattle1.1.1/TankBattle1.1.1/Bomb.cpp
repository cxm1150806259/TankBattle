//
//  Bomb.cpp
//  Tank
//
//  Created by zyf on 14-3-14.
//
//

#include "Bomb.h"

Bomb::Bomb():mIsBlock(false)
{}

Bomb::~Bomb()
{}

//根据炸弹类型生成炸弹
void Bomb::initTankWithBomb(TileMapInfo* tileMapInfo)
{
    
//    initWithSpriteFrameName("bomb1.png");
    initWithFile("bomb.png");
    this->setScale(0.5f);
    mTileMapInfo=tileMapInfo;
    this->setVisible(false);
    
    mTileMapInfo->getTileMap()->addChild(this);

//    //缩放到合适的大小
//    CCTMXTiledMap* tmxTileMap=mTileMapInfo->getTileMap();
//    CCSize tileSize=tmxTileMap->getTileSize();
//    CCSize tankSize=getContentSize();
}

//来返回一个Tank实例
//可以看到我们添加了plist文件，然后从中加载了tankTypeName类型的Tank精灵，然后初始化，最后加入自动释放列表。
Bomb* Bomb::createTankWithBomb(TileMapInfo* tileMapInfo)
{
//    CCSpriteFrameCache* pCache=CCSpriteFrameCache::sharedSpriteFrameCache();
//    pCache->addSpriteFramesWithFile("bombTool.plist");
    
    Bomb* bomb=new Bomb();
    bomb->initTankWithBomb(tileMapInfo);
    //bomb->boundingBox();
    bomb->autorelease();
    return bomb;
}

CCAnimation * Bomb::createAnimWithFrameNameAndNum(const char *name, int iNum, float delay, unsigned int iLoops)
{
    CCSpriteFrameCache * frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    //frameCache-> addSpriteFramesWithFile("tank.plist","tank.png");
    int iFrameNum = iNum;
    CCSpriteFrame * frame = NULL;
    CCArray *frameArray = CCArray::create();
    for (int i=1; i<=iFrameNum; i++) {
        frame = frameCache->spriteFrameByName(CCString::createWithFormat("%s%d.png",name,i)->getCString());
        if (frame == NULL) {
            break;
        }
        frameArray->addObject(frame);
    }
    
    CCAnimation * animation = CCAnimation::createWithSpriteFrames(frameArray);
    animation->setLoops(iLoops);
    animation->setRestoreOriginalFrame(true);
    animation->setDelayPerUnit(delay);
    return animation;
}

void Bomb::remove()
{
    mTileMapInfo->getTileMap()->removeChild(this);
     printf("炸弹消失\n");
}

void Bomb::setBlock(bool isBlock)   //
{
    mIsBlock=isBlock;
    
}

bool Bomb::getBlock()
{
    return mIsBlock;
}

void Bomb::bombEffect(CCPoint bornP)
{
    //****************cxm*********************
    CCSpriteFrameCache * frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile("tank.plist", "tank.png");
    
    CCSprite * spBomb = CCSprite::create();
    spBomb->setPosition(bornP);
    //--------------爆炸效果------------------
    CCAnimation * animation = Bomb::createAnimWithFrameNameAndNum("born", 4, 0.1f, 1);
    spBomb->runAction(CCAnimate::create(animation));
    //-------------------------------------------
    //*************************************
}