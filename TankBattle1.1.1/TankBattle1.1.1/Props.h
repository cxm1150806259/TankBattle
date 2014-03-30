//
//  Props.h
//  Tank
//
//  Created by cstlab on 14-3-10.
//
//

#ifndef __Tank__Props__
#define __Tank__Props__

#include <iostream>
#include "cocos2d.h"
#include "TileMapInfo.h"
using namespace cocos2d;

class Props:public CCSprite
{
public:
    Props();
    ~Props();
    static Props* createPropsWithPropsType(TileMapInfo* tileMapInfo);
    void initPropsWithPropsType(TileMapInfo* tileMapInfo);
    //virtual void update(float dt);
    void removeProps();
    CREATE_FUNC(Props);
private:
    TileMapInfo* mTileMapInfo;
    CCPoint bornPoint[3];
    CCSprite* moneySprit;
};

#endif /* defined(__Tank__Props__) */
