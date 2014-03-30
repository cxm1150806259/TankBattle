//
//  CityScene.h
//  Tank
//
//  Created by zyf on 14-2-12.
//
//

#ifndef __Tank__CityScene__
#define __Tank__CityScene__

#include <iostream>
#include "Panel.h"
#include "Tank.h"
#include "cocos2d.h"
#include "EnemyAI.h"
#include "Bomb.h"
#include "Props.h"
using namespace cocos2d;

class CityScene : public cocos2d::CCLayer
{
public:
	CityScene();
	~CityScene();
	virtual bool  init();
    virtual void onEnter();
    virtual void update(float delta);
    virtual void propsUpdate(float dalta);
    virtual void bombUpdate(float delta);
    
	static cocos2d::CCScene *scene();
	static cocos2d::CCScene *scene(int round);
	CREATE_FUNC(CityScene);
	static CityScene *create(int round);
    CCLabelTTF* moneyLabel;
    CCLabelTTF* lifeLabel;
	CC_SYNTHESIZE(int, m_nRound, Round);
    void remove();
private:
    //显示虚拟手柄
    Panel* mLayerPanel;
    Tank* mPlayerTank[2];
    EnemyAI* mEnemyAI;
    Bomb* mBomb;
    Props* mprops;
    TileMapInfo* tileMapInfo;
    CCSize mapSize;
    CCPoint bombBorn[3];
    int count;
};
#endif /* defined(__Tank__CityScene__) */
