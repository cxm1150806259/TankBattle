//
//  Bomb.h
//  Tank
//
//  Created by zyf on 14-3-14.
//
//

#ifndef __Tank__Bomb__
#define __Tank__Bomb__

#include <iostream>
#include "cocos2d.h"
#include "TileMapInfo.h"
using namespace cocos2d;

class Bomb:public CCSprite {
    
public:
    Bomb();
    ~Bomb();
    static CCAnimation * createAnimWithFrameNameAndNum(const char * name,int iNum,float delay,unsigned int iLoops);//炸弹爆炸效果
    static Bomb* createTankWithBomb(TileMapInfo* tileMapInfo);
    void initTankWithBomb(TileMapInfo* tileMapInfo);
    void remove();
    void setBlock(bool isBlock);  //监测是否发生碰撞
    bool getBlock();
    void bombEffect(CCPoint bornP);
private:
    bool mIsBlock;
    CCPoint bornPoint[3];
    CC_SYNTHESIZE(TileMapInfo*, mTileMapInfo, TileMapInfo);
    CC_SYNTHESIZE(float, mBulletDelta, BulletDelta);
};

#endif /* defined(__Tank__Bomb__) */
