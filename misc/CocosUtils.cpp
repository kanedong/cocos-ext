//
// Created by kanedong on 13-9-20.
//


#include "CocosUtils.h"

USING_NS_CC;

cocos2d::CCRect CocosUtils::unionRect(const cocos2d::CCRect& lrc, const cocos2d::CCRect& rrc) {
    cocos2d::CCRect ret;
    if (!isEmptyRect(lrc) && !isEmptyRect(rrc)) {
        ret.origin.x = MIN(lrc.getMinX(), rrc.getMinX());
        ret.origin.y = MIN(lrc.getMinY(), rrc.getMinY());
        ret.size.width = MAX(lrc.getMaxX(), rrc.getMaxX()) - ret.origin.x;
        ret.size.height = MAX(lrc.getMaxY(), rrc.getMaxY()) - ret.origin.y;
    }
    return ret;
}

cocos2d::CCPoint CocosUtils::releativePosOfNode(const cocos2d::CCNode* node, float rx, float ry) {
    CCPoint result;
    if (NULL != node) {
        const CCSize& size = node->getContentSize();
        result.setPoint(rx * size.width, ry * size.height);
    }
    return result;
}

cocos2d::CCRect CocosUtils::getMenuMinBounding(cocos2d::CCMenu *menu) {
    cocos2d::CCRect ret;
    bool needInit = true;

    if (NULL != menu) {
        CCArray* children = menu->getChildren();
        if (children && children->count() > 0)
        {
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(children, pObject)
                {
                    CCMenuItem* pChild = dynamic_cast<CCMenuItem*>(pObject);
                    if (NULL != pChild)
                    {
                        CCRect rc = pChild->rect();
                        if (needInit) {
                            ret.setRect(rc.origin.x, rc.origin.y, rc.size.width, rc.size.height);
                            needInit = false;
                            continue;
                        }
                        ret = CocosUtils::unionRect(ret, rc);
                    }
                }
        }
    }
    return ret;
}

cocos2d::CCRect CocosUtils::getBoundRect(cocos2d::CCNode *node) {
    CCAssert(NULL != node, "Invalid param");
    const CCPoint& pos = node->getPosition();
    const CCSize& size = node->getContentSize();
    CCPoint anchor = getRealAnchorPoint(node);
    CCRect rc(pos.x - size.width * node->getScaleX() * anchor.x,
            pos.y - size.height * node->getScaleY() * anchor.y,
            size.width, size.height);
    return rc;
}

cocos2d::CCPoint CocosUtils::getRealAnchorPoint(cocos2d::CCNode* node) {
    CCAssert(NULL != node, "Invalid param");
    if (node->isIgnoreAnchorPointForPosition()) {
        return CCPointZero;
    } else {
        return node->getAnchorPoint();
    }
}
