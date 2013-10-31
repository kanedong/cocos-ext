// Created by kanedong on 13-9-23.
//

#include "cocos2d.h"
#include "MenuItemFactory.h"
#include "AssertHelper.h"

USING_NS_CC;

CCMenuItem *MenuItemFactory::createZoomMenu(cocos2d::CCSpriteFrame *skin,
        float zoomFactor) {
    CCSprite* normal = CCSprite::createWithSpriteFrame(skin);
    CCSprite* pressed = CCSprite::createWithSpriteFrame(skin);
    CCMenuItemSprite *pCloseItem = CCMenuItemSprite::create(normal, pressed);
    pressed->ignoreAnchorPointForPosition(false);
    pressed->setAnchorPoint(ccp(0.5f, 0.5f));
    CCPoint original = normal->getPosition();
    pressed->setScale(zoomFactor);
    const CCSize& scaledSize = pressed->getContentSize();
    original.x = original.x + (scaledSize.width) * 0.5f;
    original.y = original.y + (scaledSize.height) * 0.5f;
    pressed->setPosition(original);
    return pCloseItem;
}

CCMenuItem *MenuItemFactory::createZoomMenu(CCNode *normal, CCNode *pressed,
        float zoomFactor) {
    IF_EQUAL_RETURN_VALUE(NULL, normal, NULL);
    IF_EQUAL_RETURN_VALUE(NULL, pressed, NULL);

    CCMenuItemSprite *pCloseItem = CCMenuItemSprite::create(normal, pressed);
    pressed->ignoreAnchorPointForPosition(false);
    pressed->setAnchorPoint(ccp(0.5f, 0.5f));
    CCPoint original = normal->getPosition();
    pressed->setScale(zoomFactor);
    const CCSize& scaledSize = pressed->getContentSize();
    original.x = original.x + (scaledSize.width) * 0.5f;
    original.y = original.y + (scaledSize.height) * 0.5f;
    pressed->setPosition(original);
    return pCloseItem;
}

