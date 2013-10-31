//
// Created by kanedong on 13-9-24.
//


#include "LinearLayout.h"
#include "CocosUtils.h"

USING_NS_CC;

LinearLayout::LinearLayout() :
mOrientation(HORIZONTAL),
mGravity(CENTER) {
    setOpacity(128);
}


void LinearLayout::setGravity(LinearLayout::Gravity gravity) {
    if (gravity != mGravity) {
        mGravity = gravity;
        measure();
    }
}

void LinearLayout::setOrientation(LinearLayout::Orientation orientation) {
    if (orientation != mOrientation) {
        mOrientation = orientation;
        measure();
    }
}

void LinearLayout::onMeasure() {
    if (HORIZONTAL == mOrientation) {
        hMeasure();
    } else {
        vMeasure();
    }
}

void LinearLayout::hMeasure() {
    float width = 0;
    float height = 0;
    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
            {
                Layout* layout = dynamic_cast<Layout*>(pObject);
                if (NULL != layout) {
                    layout->measure();
                }

                CCNode* pChild = dynamic_cast<CCNode*>(pObject);
                if (NULL != pChild)
                {
                    width += pChild->getContentSize().width * pChild->getScaleX();
                    height = MAX(height, pChild->getContentSize().height * pChild->getScaleX());
                }
            }
        setContentSize(CCSizeMake(width, height));
    }
}

void LinearLayout::vMeasure() {
    float width = 0;
    float height = 0;
    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
            {
                Layout* layout = dynamic_cast<Layout*>(pObject);
                if (NULL != layout) {
                    layout->measure();
                }

                CCNode* pChild = dynamic_cast<CCNode*>(pObject);
                if (NULL != pChild)
                {
                    height += pChild->getContentSize().height * pChild->getScaleY();
                    width = MAX(width, pChild->getContentSize().width * pChild->getScaleY());
                }
            }
        setContentSize(CCSizeMake(width, height));
    }
}

void LinearLayout::onLayout(bool changed, const cocos2d::CCRect& rect) {
    if (HORIZONTAL == mOrientation) {
        hLayout();
    } else {
        vLayout();
    }
}

void LinearLayout::hLayout() {
    if (m_pChildren && m_pChildren->count() > 0)
    {
        int x = 0;
        CCObject* pObject = NULL;
        CCRect prc = rect(); // Get rect of Parent.
        CCARRAY_FOREACH(m_pChildren, pObject)
            {
                CCRect crc; // Rect of child.
                Layout* layoutChild = dynamic_cast<Layout*>(pObject);
                if (NULL != layoutChild) {
                    crc = layoutChild->rect();
                    crc.origin.x = x;
                    crc.origin.y = 0;
                    layoutChild->layout(crc);
                } else {
                    CCNode* pChild = dynamic_cast<CCNode*>(pObject);
                    if (NULL != pChild)
                    {
                        crc = CocosUtils::getBoundRect(pChild);
                        CCPoint anchor = CocosUtils::getRealAnchorPoint(pChild);
                        float offset = 0;
                        if ((TOP & mGravity) == TOP) {
                            offset = prc.size.height - crc.size.height;
                        } else if ((CENTER_VERTICAL & mGravity) == CENTER_VERTICAL) {
                            offset = (prc.size.height - crc.size.height) / 2;
                        }
                        pChild->setPosition(x + anchor.x * crc.size.width,
                                offset + anchor.y * crc.size.height);
                    }
                }
                x += crc.size.width;
            }
    }
}

void LinearLayout::vLayout() {
    if (m_pChildren && m_pChildren->count() > 0)
    {
        int y = 0;
        CCObject* pObject = NULL;
        CCRect prc = rect(); // Get rect of Parent.
        CCARRAY_FOREACH_REVERSE(m_pChildren, pObject)
            {
                CCRect crc;
                Layout* layoutChild = dynamic_cast<Layout*>(pObject);
                if (NULL != layoutChild) {
                    crc = layoutChild->rect();
                    CCPoint anchor = CocosUtils::getRealAnchorPoint(layoutChild);
                    crc.origin.x = (prc.size.width - crc.size.width) * anchor.x;
                    crc.origin.y = y;
                    layoutChild->layout(crc);
                } else {
                    CCNode* pChild = dynamic_cast<CCNode*>(pObject);
                    if (NULL != pChild)
                    {
                        crc = CocosUtils::getBoundRect(pChild);
                        CCPoint anchor = CocosUtils::getRealAnchorPoint(pChild);
                        float offset = 0;
                        if ((TOP & mGravity) == TOP) {
                            offset = prc.size.width - crc.size.width;
                        } else if ((CENTER_VERTICAL & mGravity) == CENTER_VERTICAL) {
                            offset = (prc.size.width - crc.size.width) / 2;
                        }
//                        float xOffset = (prc.size.width - crc.size.width) * anchor.x;
                        pChild->setPosition(offset + anchor.x * crc.size.width,
                                y + anchor.y * crc.size.height);
                    }
                }
                y += crc.size.height;
            }
    }
}
