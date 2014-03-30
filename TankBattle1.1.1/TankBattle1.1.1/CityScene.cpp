//
//  CityScene.cpp
//  Tank
//
//  Created by zyf on 14-2-12.
//
//

#include "CityScene.h"
#include "Tank.h"
#include "EnemyAI.h"
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;
CityScene::CityScene()
{
    
}

CityScene::~CityScene()
{
    
}

CCScene *CityScene::scene()
{
	CCScene* scene = CCScene::create();
	CityScene* layer = CityScene::create();
    
	scene->addChild(layer);
    
	return scene;
}

CCScene *CityScene::scene(int round)
{
	CCScene* scene = CCScene::create();
	CityScene* layer = CityScene::create(round);
    
	scene->addChild(layer);
    
	return scene;
}

CityScene *CityScene::create(int round)
{
	CityScene* pRet = new CityScene();
	if (pRet)
	{
		pRet->setRound(round);
		if (pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
	}
    
	return NULL;
}

bool  CityScene::init()
{
	CCLayer::init();
    //初始化地图信息
    char szRound[260];
    sprintf(szRound, "Round%d.tmx",m_nRound);
    tileMapInfo=TileMapInfo::createMapInfoWithFile(szRound);
    CCTMXTiledMap* tmxTileMap=tileMapInfo->getTileMap();
    this->addChild(tmxTileMap);
    //***************yq******************
    //创建金币label
    CCString* strMoneyScore = CCString::createWithFormat("金币：0");//格式化为字符串
    moneyLabel = CCLabelTTF::create(strMoneyScore->m_sString.c_str(),"Arial",20);//从CCString中获得char*,更新金币
    moneyLabel->setAnchorPoint(ccp(0, 0));
    moneyLabel->setColor(ccc3(255, 255, 255));
    moneyLabel->setPosition(ccp(0,580));
    addChild(moneyLabel);
    
    //创建生命label
    CCString* strLifeScore = CCString::createWithFormat("生命：3");//格式化为字符串
    lifeLabel = CCLabelTTF::create(strLifeScore->m_sString.c_str(),"Arial",20);//从CCString中获得char*,更新生命
    lifeLabel->setAnchorPoint(ccp(0, 0));
    lifeLabel->setColor(ccc3(255, 255, 255));
    lifeLabel->setPosition(ccp(0,560));
    addChild(lifeLabel);    //*********************************

    
    //在已有的地图上，创建玩家坦克
    mPlayerTank[0]=Tank::createTankWithTankType("player2U.png", tileMapInfo);
    
    //放到地图中初始化位置
    CCSize tileSize=tmxTileMap->getTileSize();
    mapSize=tmxTileMap->getContentSize();
    mPlayerTank[0]->setPosition(ccp(mapSize.width/2-tileSize.width*3, tileSize.height));
    CCPoint xx=mPlayerTank[0]->getPosition();
    //显示虚拟手柄
    mLayerPanel=Panel::create();
    addChild(mLayerPanel,3);
    
//    /*******************cxm*******************/
    mBomb=Bomb::createTankWithBomb(tileMapInfo);
    
//    /*****************************************/
    

    //创建坦克的AI
    mEnemyAI=EnemyAI::createEnemyAIWithTank(mPlayerTank[0],mBomb);
    //调用炸弹
    this->bombUpdate(10);
    count= 0;

	return true;
}

//在onEnter中设置一个定时器，
void CityScene::onEnter()
{
    CCLayer::onEnter();
    this->scheduleUpdate();   //显示坦克
    this->schedule(schedule_selector(CityScene::propsUpdate), 5.0f);  //显示金币
//    if (!mBomb->getBlock()) {
        this->schedule(schedule_selector(CityScene::bombUpdate),5.0f);
//        printf(" ***********Bomb count:%d********\n",5);}
    
}

void CityScene::update(float delta)
{
    CCLayer::update(delta);
    //简单的向前运动。测试使用
    //mLayerTank[0]->setPositionY(mLayerTank[0]->getPositionY()+1);
    //将控制面板中的mLayerPanel获取的命令传给坦克
    mPlayerTank[0]->command(mLayerPanel->getOrder());
    
    //调用敌人AI的update
    mEnemyAI->update(delta);
    
    //************yq************************
    int score = mEnemyAI->getScore();
    CCString* strScore = CCString::createWithFormat("金币：%d",score);
    moneyLabel->setString(strScore->m_sString.c_str());
    
    int life = mEnemyAI->getLife();
    CCString* strLife = CCString::createWithFormat("生命：%d",life);
    lifeLabel->setString(strLife->m_sString.c_str());
    //************************************
}
void CityScene::propsUpdate(float dalta)
{
    //创建道具金币
    mprops = Props::createPropsWithPropsType(tileMapInfo);

}
void CityScene::bombUpdate(float delta)
{
    /*******************cxm*******************/
//    mBomb=Bomb::createTankWithBomb("bullet.png", tileMapInfo);
//     int y = CCRANDOM_0_1()*(mapSize.height);
    if (delta >2) {
        float c1=(arc4random()%(int)(mapSize.width-10))+10;
        float c2=(arc4random()%(int)(mapSize.height-10))+10;
        bombBorn[0] =ccp(c1,c2);
        mBomb->setPosition(bombBorn[0]);
        mBomb->setVisible(true);
        CCActionInterval * blinkAction = CCBlink::create(20, 30); //first duration,second iBlinkNum
        CCCallFunc * callAction = CCCallFunc::create(this, callfunc_selector(CityScene::remove));
        CCSequence * action = CCSequence::create(blinkAction,callAction,NULL);
        mBomb->runAction(action);
        
        if (mBomb) {
            printf("***CityScene:bombUpdate*******Tank 没有消失***\n");
        }
    }
    
    
    
    /*****************************************/
}
void CityScene::remove()
{
    mBomb->remove();
    this->removeChild(mBomb);
    //tileMapInfo->getTileMap()->removeChild(mBomb);
    if (mBomb) {
        printf("*******remove**********Tank 没有消失了**********\n");
    }

}