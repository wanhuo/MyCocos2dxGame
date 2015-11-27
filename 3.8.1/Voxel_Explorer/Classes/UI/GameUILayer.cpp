//
//  GameUILayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/16.
//
//

#include "GameUILayer.h"
#include "UtilityHelper.h"
#include "GameConfig.h"
#include "PopupUILayerManager.h"
#include "PlayerProperty.hpp"
#include "GameFormula.hpp"
#include "VoxelExplorer.h"
#include "EventConst.h"
#include "ui/CocosGUI.h"
#include "RandomDungeon.hpp"
#include "StandardMonster.hpp"
#include "InfoPopupUI.h"
#include "BaseDoor.hpp"
#include "PotionsProperty.hpp"
#include "ScrollProperty.hpp"
#include "RolePopupUI.h"
#include "LevelResourceManager.h"
#include "PromptLayer.hpp"
#include "GameInfoLayer.hpp"
#include "GameToolbarLayer.hpp"
#include "RolePropLayer.hpp"
#include "MonsterPropLayer.hpp"
USING_NS_CC;
GameUILayer::GameUILayer()
{
    m_pGameInfoLayer = nullptr;
    m_pGameToolBarLayer = nullptr;
    m_pRolePropLayer = nullptr;
    m_pMonsterPropLayer = nullptr;
}
GameUILayer::~GameUILayer()
{
    
}
bool GameUILayer::initUi()
{
    if (!registerTouchEvent())
        return false;
    
    m_pGameInfoLayer = GameInfoLayer::create();
    m_pGameInfoLayer->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
    m_pGameInfoLayer->setPosition(cocos2d::Vec2(m_pRootLayer->getContentSize().width*0.5,m_pRootLayer->getContentSize().height));
    m_pRootLayer->addChild(m_pGameInfoLayer);
    
    m_pGameToolBarLayer = GameToolbarLayer::create();
    m_pGameToolBarLayer->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
    m_pGameToolBarLayer->setPosition(cocos2d::Vec2(m_pRootLayer->getContentSize().width*0.5,0));
    m_pRootLayer->addChild(m_pGameToolBarLayer);
    
    m_pRolePropLayer = RolePropLayer::create();
    m_pRolePropLayer->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    m_pRolePropLayer->setPosition(cocos2d::Vec2::ZERO);
    m_pGameInfoLayer->addChild(m_pRolePropLayer);
    
    m_pMonsterPropLayer = MonsterPropLayer::create();
    m_pMonsterPropLayer->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
    m_pMonsterPropLayer->setPosition(cocos2d::Vec2(m_pGameInfoLayer->getContentSize().width,0));
    m_pGameInfoLayer->addChild(m_pMonsterPropLayer);
    m_pMonsterPropLayer->setVisible(false);
    
    return true;
}


bool GameUILayer::registerTouchEvent()
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    if(touchListener == nullptr)
        return false;
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameUILayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameUILayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameUILayer::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}
bool GameUILayer::onTouchBegan(Touch *touch, Event *event)
{

    return m_pGameToolBarLayer->isOpenDist();
}
void GameUILayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return;
}
void GameUILayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!touch)
        return;
    if(m_pGameToolBarLayer->isOpenDist())
    {
        std::string iconRes;
        std::string desc = VoxelExplorer::getInstance()->getScreenPickDesc(touch->getLocation(), iconRes);
        InfoPopupUI* infoUi = static_cast<InfoPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupInfo));
        if(infoUi)
        {
           m_pGameToolBarLayer->onClickDistTipsFrame();
            infoUi->setDarkLayerVisble(false);
            infoUi->setInfoData(iconRes, desc);
        }
        CCLOG("Pick Desc : %s, Icon Res: %s", desc.c_str(), iconRes.c_str());
    }
    return;
}

void GameUILayer::onEventFoundHidderDoor(cocos2d::EventCustom *sender) //发现隐藏门
{
    CCLOG("onEventFoundHidderDoor");
}
void GameUILayer::onEventFoundHidderTrapToxic(cocos2d::EventCustom *sender)//发现隐藏中毒机关
{
    CCLOG("onEventFoundHidderTrapToxic");
}
void GameUILayer::onEventFoundHidderTrapFire(cocos2d::EventCustom *sender)//发现隐藏火机关
{
    CCLOG("onEventFoundHidderTrapFire");
}
void GameUILayer::onEventFoundHidderTrapParalyic(cocos2d::EventCustom *sender)//发现隐藏麻痹机关
{
    CCLOG("onEventFoundHidderTrapParalyic");
}
void GameUILayer::onEventFoundHidderTrapGripping(cocos2d::EventCustom *sender)//发现隐藏夹子机关
{
     CCLOG("onEventFoundHidderTrapGripping");
}
void GameUILayer::onEventFoundHidderTrapSummoning(cocos2d::EventCustom *sender)//发现隐藏召唤机关
{
     CCLOG("onEventFoundHidderTrapSummoning");
}
void GameUILayer::onEventFoundHidderTrapWeak(cocos2d::EventCustom *sender)//发现隐藏虚弱机关
{
    CCLOG("onEventFoundHidderTrapWeak");
}
void GameUILayer::onEventFoundHidderMsg(cocos2d::EventCustom *sender)
{
    CCLOG("onEventFoundHidderMsg");
}
void GameUILayer::onEventFoundHidderItem(cocos2d::EventCustom *sender)
{
    CCLOG("onEventFoundHidderItem");
}

void GameUILayer::onEventGoUpStairs(cocos2d::EventCustom *sender)
{
     CCLOG("onEventGoUpStairs");
}
void GameUILayer::onEventGoUpStairsForbidden(cocos2d::EventCustom *sender)
{
     CCLOG("onEventGoUpStairsForbidden");
}
void GameUILayer::onEventGoDownStairs(cocos2d::EventCustom *sender)
{
    CCLOG("onEventGoDownStairs");
}
void GameUILayer::onEventGoBossRoom(cocos2d::EventCustom *sender)
{
    CCLOG("onEventGoBossRoom");
}

void GameUILayer::onEventTriggerToxic(cocos2d::EventCustom *sender) //中毒机关
{
    CCLOG("onEventTriggerToxic");
    std::string msg = UtilityHelper::getLocalStringForUi("TRIGGER_MESSAGE_TOXIC_TRAP");
    PopupUILayerManager::getInstance()->showStatusImport(TIP_WARNING, msg);
    m_pGameToolBarLayer->sendMessage(msg);
    
}
void GameUILayer::onEventTriggerFire(cocos2d::EventCustom *sender) //火机关
{
    CCLOG("onEventTriggerFire");
    std::string msg = UtilityHelper::getLocalStringForUi("TRIGGER_MESSAGE_FIRE_TRAP");
    PopupUILayerManager::getInstance()->showStatusImport(TIP_WARNING, msg);
     m_pGameToolBarLayer->sendMessage(msg);
    
}
void GameUILayer::onEventTriggerParalyic(cocos2d::EventCustom *sender)//麻痹机关
{
    CCLOG("onEventTriggerParalyic");
    std::string msg = UtilityHelper::getLocalStringForUi("TRIGGER_MESSAGE_PARALYTIC_TRAP");
    PopupUILayerManager::getInstance()->showStatusImport(TIP_WARNING, msg);
     m_pGameToolBarLayer->sendMessage(msg);
    
}
void GameUILayer::onEventTriggerGripping(cocos2d::EventCustom *sender)//夹子机关
{
    CCLOG("onEventTriggerGripping");
    std::string msg = UtilityHelper::getLocalStringForUi("TRIGGER_MESSAGE_GRIPPING_TRAP");
    PopupUILayerManager::getInstance()->showStatusImport(TIP_WARNING, msg);
     m_pGameToolBarLayer->sendMessage(msg);
    
}
void GameUILayer::onEventTriggerSummoning(cocos2d::EventCustom *sender)//召唤机关
{
    CCLOG("onEventTriggerSummoning");
    std::string msg = UtilityHelper::getLocalStringForUi("TRIGGER_MESSAGE_SUMMONING_TRAP");
    PopupUILayerManager::getInstance()->showStatusImport(TIP_WARNING, msg);
     m_pGameToolBarLayer->sendMessage(msg);
    
}
void GameUILayer::onEventTriggerWeak(cocos2d::EventCustom *sender) //虚弱机关
{
    CCLOG("onEventTriggerWeak");
    std::string msg = UtilityHelper::getLocalStringForUi("TRIGGER_MESSAGE_WEAK_TRAP");
    PopupUILayerManager::getInstance()->showStatusImport(TIP_WARNING, msg);
     m_pGameToolBarLayer->sendMessage(msg);
   
}
void GameUILayer::onEventUserPotion(cocos2d::EventCustom *sender)
{
    CCLOG("onEvenetUserPotion");
    //关闭ItemPopup窗口
    PopupUILayerManager::getInstance()->closeCurrentPopup();
    
    //窗口都未关闭,回调后来判断是否关闭
    Vec2 pt = VoxelExplorer::getInstance()->getMainCamera()->projectGL(VoxelExplorer::getInstance()->getPlayer()->getPosition3D());
    pt = Vec2(pt.x, pt.y+TerrainTile::CONTENT_SCALE*2.5);
    PotionsProperty* potionsProperty = static_cast<PotionsProperty*>(sender->getUserData());
    PickableItem::PickableItemType itemType = potionsProperty->getPickableItemType();
    switch (itemType) {
        case PickableItem::PIT_POTION_MINORHEALTH:
        case PickableItem::PIT_POTION_LESSERHEALTH:
        case PickableItem::PIT_POTION_HEALTH:
            CCLOG("使用治疗药水 恢复HP");
            PopupUILayerManager::getInstance()->showStatus(TIP_POSITIVE, StringUtils::format(UtilityHelper::getLocalStringForUi("USE_POTION_ TREAT").c_str(),int(potionsProperty->getValue())),pt);
            break;
        case PickableItem::PIT_POTION_MINORMANA:
        case PickableItem::PIT_POTION_LESSERMANA:
        case PickableItem::PIT_POTION_MANA:
            CCLOG("使用魔法药水 恢复MP");
            PopupUILayerManager::getInstance()->showStatus(TIP_BLUE, StringUtils::format(UtilityHelper::getLocalStringForUi("USE_POTION_ MAGIC").c_str(),int(potionsProperty->getValue())),pt);
            break;
        case PickableItem::PIT_POTION_MINORRECOVERY:
        case PickableItem::PIT_POTION_LESSERRECOVERY:
        case PickableItem::PIT_POTION_RECOVERY:
            CCLOG("恢复药水 恢复HP+MP");
            break;
        case PickableItem::PIT_POTION_DETOXIFICATION:
            CCLOG("解除中毒");
            break;
        case PickableItem::PIT_POTION_SPECIFIC:
            CCLOG("解除冰冻、麻痹、火");
            break;
        case PickableItem::PIT_POTION_HEALING:
            CCLOG("解除虚弱");
            break;
        case PickableItem::PIT_POTION_UNIVERSAL:
            CCLOG("万能药水,解除中毒，冰冻，麻痹，虚弱，着火");
            break;
        default:
            break;
    }
    //关闭角色对话框
    PopupUILayerManager::getInstance()->closeCurrentPopup();

}
void GameUILayer::onEventUserScroll(cocos2d::EventCustom *sender)
{
    //关闭ItemPopup窗口
    PopupUILayerManager::getInstance()->closeCurrentPopup();
    //窗口都未关闭,回调后来判断是否关闭
    CCLOG("onEvenetUserScroll");
    ScrollProperty* scrollProperty = static_cast<ScrollProperty*>(sender->getUserData());
    
    if (scrollProperty->getPickableItemType() == PickableItem::PIT_SCROLL_INDENTIFY)
    {
        CCLOG("鉴定卷轴");
        PopupUILayer* popup = nullptr;
        RolePopupUI* rolePopup = nullptr;
        if(PopupUILayerManager::getInstance()->isOpenPopup(ePopupRole, popup)){
            rolePopup = static_cast<RolePopupUI*>(popup);
        }else{
            rolePopup = static_cast<RolePopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupRole));
        }
        if (rolePopup) {
            rolePopup->updateItems(true);
        }
        return;
    }else if(scrollProperty->getPickableItemType() == PickableItem::PIT_SCROLL_TELEPORT)
    {
        CCLOG("传送卷轴");
    }else if(scrollProperty->getPickableItemType() == PickableItem::PIT_SCROLL_SPEED)
    {
        CCLOG("速度卷轴");
        
    }else if(scrollProperty->getPickableItemType() == PickableItem::PIT_SCROLL_STEALTH)
    {
        CCLOG("隐身卷轴");
    }else if(scrollProperty->getPickableItemType() == PickableItem::PIT_SCROLL_DESTINY)
    {
        CCLOG("命运卷轴");
    }
    //关闭角色对话框
    PopupUILayerManager::getInstance()->closeCurrentPopup();
}
void GameUILayer::refreshUIView()
{
    if (m_pGameInfoLayer) {
        m_pGameInfoLayer->refreshUIView();
    }
    
    if (m_pGameToolBarLayer) {
        m_pGameToolBarLayer->refreshUIView();
    }
    
    if (m_pRolePropLayer) {
        m_pRolePropLayer->refreshUIView();
    }
    
    if (m_pMonsterPropLayer) {
        m_pMonsterPropLayer->refreshUIView();
    }
}
void GameUILayer::onEventRoleLevelUp(cocos2d::EventCustom *sender)
{
    CCLOG("onEventRoleLevelUp");
    refreshUIView();
    PopupUILayerManager::getInstance()->showStatusImport(TIP_DEFAULT, UtilityHelper::getLocalStringForUi("GAME_MESSAGE_LEVEL_UP"));
    m_pGameToolBarLayer->sendMessage(UtilityHelper::getLocalStringForUi("GAME_MESSAGE_LEVEL_UP"),PopupUILayerManager::getInstance()->getTipsColor(TIP_NEUTRAL));
}

void GameUILayer::onEventRoleUpdateProp(cocos2d::EventCustom *sender)
{
    CCLOG("onEventUpdateProp");
    refreshUIView();

}

void GameUILayer::onEventRoleDead(cocos2d::EventCustom *sender)
{
    CCLOG("onEventRoleDead");
    refreshUIView();
    CallFunc* func = CallFunc::create([]{
        PopupUILayer* pausePopup = PopupUILayerManager::getInstance()->openPopup(ePopupPause);
        if (pausePopup) {
            pausePopup->setDarkLayerVisble(false);
            pausePopup->setBlankClose(false);
        }

    });
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(3.0F),func ));
   }
void GameUILayer::onEventRoleHud(cocos2d::EventCustom *sender)
{
       CCLOG("onEvenetRoleHud");
    HurtData* hurData = static_cast<HurtData*>(sender->getUserData());
    Vec2 pt = VoxelExplorer::getInstance()->getMainCamera()->projectGL(hurData->m_vPos);
    pt = Vec2(pt.x, pt.y+TerrainTile::CONTENT_SCALE*2.5);
     if (hurData->m_bDodge) {
        
        PopupUILayerManager::getInstance()->showStatus(TIP_DODGE,  StringUtils::format(UtilityHelper::getLocalStringForUi("STATUS_TEXT_DODGE").c_str(),hurData->m_nDamage),pt);
        CCLOG("monster 闪避");
    }else {
        if((hurData->m_bBlocked && hurData->m_bCriticalStrike) || hurData->m_bBlocked)
        {
            PopupUILayerManager::getInstance()->showStatus(TIP_BOLOCK, StringUtils::format(UtilityHelper::getLocalStringForUi("STATUS_TEXT_BOLOCK").c_str(),hurData->m_nDamage),pt);
            CCLOG("monster 格挡");
        }else if (hurData->m_bCriticalStrike)
        {
            PopupUILayerManager::getInstance()->showStatus(TIP_CRITICAL_STRIKE, StringUtils::format(UtilityHelper::getLocalStringForUi("STATUS_TEXT_CRITICAL_STRIKE").c_str(),hurData->m_nDamage),pt);
            CCLOG("monster 暴击");
        }else{
            PopupUILayerManager::getInstance()->showStatus(TIP_NEGATIVE, Value(hurData->m_nDamage).asString(),pt);
            CCLOG("pt x:%f y%f",pt.x,pt.y);
        }
        
    }
    
}
void GameUILayer::onEventMonsterDead(cocos2d::EventCustom *sender)
{
    CCLOG("onEvenetMonsterDead");
    BaseMonster* monster = static_cast<BaseMonster*>(sender->getUserData());
    if (!monster)
        return;
    Vec2 pt = VoxelExplorer::getInstance()->getMainCamera()->projectGL(monster->getPosition3D());
    pt = Vec2(pt.x, pt.y+TerrainTile::CONTENT_SCALE*2.5);
    if (monster->getState() == BaseMonster::MonsterState::MS_DEATH) {
        int roleLevel = PlayerProperty::getInstance()->getLevel();
        int monsterLevel = monster->getMonsterProperty()->getLevel();
        int exp = GameFormula::getKillNormalMonsterExp(roleLevel, monsterLevel);
        if (monster->getMonsterProperty()->isElite()) {
            exp = GameFormula::getKillEliteMonsterExp(roleLevel, monsterLevel);
        }
        PopupUILayerManager::getInstance()->showStatus(TIP_POSITIVE, StringUtils::format(UtilityHelper::getLocalStringForUi("STATUS_TEXT_EXP").c_str(),exp),pt);
        if (m_pMonsterPropLayer) {
            m_pMonsterPropLayer->setVisible(false);
            m_pMonsterPropLayer->setMonster(monster);
        }

    }
 

}

void GameUILayer::onEventMonsterHud(cocos2d::EventCustom *sender)
{
        CCLOG("onEventMonsterHud");
    HurtData* hurData = static_cast<HurtData*>(sender->getUserData());
    Vec2 pt = VoxelExplorer::getInstance()->getMainCamera()->projectGL(hurData->m_vPos);
    pt = Vec2(pt.x, pt.y+TerrainTile::CONTENT_SCALE*2.5);
    if (hurData->m_bDodge) {
       
        PopupUILayerManager::getInstance()->showStatus(TIP_DODGE,  StringUtils::format(UtilityHelper::getLocalStringForUi("STATUS_TEXT_DODGE").c_str(),hurData->m_nDamage),pt);
        CCLOG("monster 闪避");
    }else {
        if((hurData->m_bBlocked && hurData->m_bCriticalStrike) || hurData->m_bBlocked)
        {
            PopupUILayerManager::getInstance()->showStatus(TIP_BOLOCK, StringUtils::format(UtilityHelper::getLocalStringForUi("STATUS_TEXT_BOLOCK").c_str(),hurData->m_nDamage),pt);
            CCLOG("monster 格挡");
        }else if (hurData->m_bCriticalStrike)
        {
            PopupUILayerManager::getInstance()->showStatus(TIP_CRITICAL_STRIKE, StringUtils::format(UtilityHelper::getLocalStringForUi("STATUS_TEXT_CRITICAL_STRIKE").c_str(),hurData->m_nDamage),pt);
             CCLOG("monster 暴击");
        }else{
            PopupUILayerManager::getInstance()->showStatus(TIP_NEUTRAL, Value(hurData->m_nDamage).asString(),pt);
            CCLOG("pt x:%f y%f",pt.x,pt.y);
        }
    }
    
}
void GameUILayer::onEventMonsterUpdateProp(cocos2d::EventCustom *sender)
{
    CCLOG("onEventUpdateMonsterProp");
    BaseMonster* monster = static_cast<BaseMonster*>(sender->getUserData());
    if (m_pMonsterPropLayer)
        m_pMonsterPropLayer->setMonster(monster);
    refreshUIView();
}
void GameUILayer::onEventMonsterAlert(cocos2d::EventCustom *sender)
{
    CCLOG("onEventMonsterAlert");
    BaseMonster* monster = static_cast<BaseMonster*>(sender->getUserData());
    PromptLayer* promptLayer = PromptLayer::create(PromptLayer::PT_AWAKE);
    if (monster) {
        promptLayer->setDisplayPt(monster->getPosition3D());
    }
    m_pRootLayer->addChild(promptLayer);

}
void GameUILayer::onEventMonsterConfusing(cocos2d::EventCustom *sender)
{
    CCLOG("onEventMonsterConfusing");
    BaseMonster* monster = static_cast<BaseMonster*>(sender->getUserData());
    if (m_pMonsterPropLayer) {
         m_pMonsterPropLayer->setVisible(false);
    }
   
}

void GameUILayer::onEnter()
{
    WrapperUILayer::onEnter();
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PLAYER_PROPERTY_DIRTY, CC_CALLBACK_1(GameUILayer::onEventRoleUpdateProp,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PLAYER_LEVEL_UP, CC_CALLBACK_1(GameUILayer::onEventRoleLevelUp,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PLAYER_DEATH, CC_CALLBACK_1(GameUILayer::onEventRoleDead,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PLAYER_HURT, CC_CALLBACK_1(GameUILayer::onEventRoleHud,this));

    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PLAYER_USE_POTION, CC_CALLBACK_1(GameUILayer::onEventUserPotion,this));
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PLAYER_USE_SCROLL, CC_CALLBACK_1(GameUILayer::onEventUserScroll,this));
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MONSTER_HURT, CC_CALLBACK_1(GameUILayer::onEventMonsterHud,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MONSTER_PROPERTY_DIRTY, CC_CALLBACK_1(GameUILayer::onEventMonsterUpdateProp,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MONSTER_DEATH, CC_CALLBACK_1(::GameUILayer::onEventMonsterDead,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MONSTER_ALERT, CC_CALLBACK_1(::GameUILayer::onEventMonsterAlert,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MONSTER_CONFUSING, CC_CALLBACK_1(::GameUILayer::onEventMonsterConfusing,this));
    

    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_TRIGGER_TOXIC_TRAP, CC_CALLBACK_1(GameUILayer::onEventTriggerToxic,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_TRIGGER_FIRE_TRAP, CC_CALLBACK_1(GameUILayer::onEventTriggerFire,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_TRIGGER_PARALYTIC_TRAP, CC_CALLBACK_1(GameUILayer::onEventTriggerParalyic,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_TRIGGER_GRIPPING_TRAP, CC_CALLBACK_1(GameUILayer::onEventTriggerGripping,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_TRIGGER_SUMMONING_TRAP, CC_CALLBACK_1(GameUILayer::onEventTriggerSummoning,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_TRIGGER_WEAK_TRAP, CC_CALLBACK_1(GameUILayer::onEventTriggerWeak,this)) ;
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_FOUND_HIDDEN_DOOR, CC_CALLBACK_1(GameUILayer::onEventFoundHidderDoor,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_FOUND_HIDDEN_TOXIC_TRAP, CC_CALLBACK_1(GameUILayer::onEventFoundHidderTrapToxic,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_FOUND_HIDDEN_FIRE_TRAP, CC_CALLBACK_1(GameUILayer::onEventFoundHidderTrapFire,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_FOUND_HIDDEN_PARALYTIC_TRAP, CC_CALLBACK_1(GameUILayer::onEventFoundHidderTrapParalyic,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_FOUND_HIDDEN_GRIPPING_TRAP, CC_CALLBACK_1(GameUILayer::onEventFoundHidderTrapGripping,this));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_FOUND_HIDDEN_SUMMONING_TRAP, CC_CALLBACK_1(GameUILayer::onEventFoundHidderTrapSummoning,this)) ;
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_FOUND_HIDDEN_WEAK_TRAP, CC_CALLBACK_1(GameUILayer::onEventFoundHidderTrapWeak,this)) ;
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_FOUND_HIDDEN_MSG, CC_CALLBACK_1(GameUILayer::onEventFoundHidderMsg,this)) ;
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_FOUND_HIDDEN_ITEM, CC_CALLBACK_1(GameUILayer::onEventFoundHidderItem,this)) ;
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_GO_UPSTAIRS, CC_CALLBACK_1(GameUILayer::onEventGoUpStairs,this)) ;
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_GO_UPSTAIRS_FORBIDDEN, CC_CALLBACK_1(GameUILayer::onEventGoUpStairsForbidden,this)) ;
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_GO_DOWNSTAIRS, CC_CALLBACK_1(GameUILayer::onEventGoDownStairs,this)) ;
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_GO_BOSSROOM, CC_CALLBACK_1(GameUILayer::onEventGoBossRoom,this));
    
}
void GameUILayer::onExit()
{
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PLAYER_PROPERTY_DIRTY);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PLAYER_LEVEL_UP);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PLAYER_DEATH);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PLAYER_HURT);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PLAYER_USE_POTION);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PLAYER_USE_SCROLL);
    
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MONSTER_HURT);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MONSTER_PROPERTY_DIRTY);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MONSTER_DEATH);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MONSTER_ALERT);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MONSTER_CONFUSING);
    
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_TRIGGER_TOXIC_TRAP);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_TRIGGER_FIRE_TRAP);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_TRIGGER_PARALYTIC_TRAP);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_TRIGGER_GRIPPING_TRAP);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_TRIGGER_SUMMONING_TRAP);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_TRIGGER_WEAK_TRAP);
    
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_FOUND_HIDDEN_DOOR);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_FOUND_HIDDEN_TOXIC_TRAP);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_FOUND_HIDDEN_FIRE_TRAP);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_FOUND_HIDDEN_PARALYTIC_TRAP);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_FOUND_HIDDEN_GRIPPING_TRAP);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_FOUND_HIDDEN_SUMMONING_TRAP);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_FOUND_HIDDEN_WEAK_TRAP);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_FOUND_HIDDEN_MSG);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_FOUND_HIDDEN_ITEM);
    
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_GO_UPSTAIRS);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_GO_UPSTAIRS_FORBIDDEN);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_GO_DOWNSTAIRS);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_GO_BOSSROOM);
    
    WrapperUILayer::onExit();
}
