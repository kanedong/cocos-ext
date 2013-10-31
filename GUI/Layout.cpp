//
// Created by kanedong on 13-9-24.
//


#include "Layout.h"
#include "CocosUtils.h"

USING_NS_CC;

Layout::Layout() :
mBg(NULL)
{

}

/*
* override add:
*/
void Layout::addChild(CCNode *child) {
    CCLayerColor::addChild(child);
}

void Layout::addChild(CCNode *child, int zOrder) {
    CCLayerColor::addChild(child, zOrder);
}

void Layout::addChild(CCNode *child, int zOrder, int tag) {
    CCLayerColor::addChild(child, zOrder, tag);
    measure();
}

void Layout::removeChild(CCNode *child) {
    CCLayerColor::removeChild(child);
}

void Layout::removeChild(cocos2d::CCNode *child, bool cleanup) {
    CCLayerColor::removeChild(child, cleanup);
    measure();
}

cocos2d::CCRect Layout::rect() {
    return CocosUtils::getBoundRect(this);
}

void Layout::layout(const cocos2d::CCRect& rect) {
    bool changed = setFrame(rect);
//    if (changed) {
        onLayout(changed, rect);
//    }
}

void Layout::invalidate() {
    measure();
}

bool Layout::setFrame(const cocos2d::CCRect& rect) {
    CCRect rc = this->rect();
    if (!rc.equals(rect)) {
        const CCPoint& anchor = getRealAnchorPoint();
        setPosition(rect.origin.x + rect.size.width * getScaleX() * anchor.x,
                rect.origin.y + rect.size.height * getScaleY() * anchor.y);
        setContentSize(rect.size);
        return true;
    }
    return false;
}

void Layout::measure() {
    onMeasure();
    layout(rect());
}

void Layout::setBackground(cocos2d::CCNode *bg) {
    if (NULL != mBg) {
        removeChild(mBg, true);
        mBg = NULL;
    }

    if (NULL != bg) {
        mBg = bg;
        measure();
    }
}

const cocos2d::CCPoint& Layout::getRealAnchorPoint() {
    if (isIgnoreAnchorPointForPosition()) {
        return mZeroPoint;
    } else {
        return getAnchorPoint();
    }
}
