
#include "Dialog.h"
#include "CocosUtils.h"
#include "VisibleRect.h"

USING_NS_CC;

Dialog* Dialog::create(
        CCNode *parent,
        CCMenuItem *btnPositive,
        CCMenuItem *btnNegative,
        CCMenuItem *btnNeutral) {
    Dialog* pRet = new Dialog();
    if (pRet && pRet->initWithMenuItem(parent, btnPositive, btnNegative, btnNeutral)) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

bool Dialog::init() {
    return initWithMenuItem(NULL, NULL, NULL, NULL);
}

bool Dialog::initWithMenuItem(
        CCNode *parent,
        cocos2d::CCMenuItem *btnPositive,
        cocos2d::CCMenuItem *btnNegative,
        cocos2d::CCMenuItem *btnNeutral) {
    if (!CCLayerColor::init()) {
        return false;
    }
    setAnchorPoint(ccp(0.5, 0.5));
    ignoreAnchorPointForPosition(false);
    mParent = parent;
    if (NULL != parent) {
        const CCSize& size = parent->getContentSize();
        // Display the dialog in center of parent.
        setPosition(ccp(size.width / 2, size.height / 2));
    } else {
        // If no parent was set, make dialog in center of screen.
        setPosition(ccp(VisibleRect::getVisibleRect().getMidX(),
            VisibleRect::getVisibleRect().getMidY()));
    }

    setVisible(false);

    mItems[BUTTON_GROUP] = CCMenu::create();
    mItems[BUTTON_GROUP]->setPosition(CCPointZero);
    addChild(mItems[BUTTON_GROUP]);

    setButton(btnPositive, BUTTON_POSITIVE);
    setButton(btnNegative, BUTTON_NEGATIVE);
    setButton(btnNeutral, BUTTON_NEUTRAL);
    ((CCMenu *) mItems[BUTTON_GROUP])->alignItemsHorizontally();
    return true;
}

void Dialog::setBackground(CCNode *bg) {
    if (NULL != mBg) {
        removeChild(mBg);
        mBg = NULL;
    }
    if (NULL != bg) {
        mBg = bg;
        setContentSize(mBg->getContentSize());
        layout();
        addChild(mBg, -1);
    }
}

void Dialog::layout() {
    const CCSize& bgSize = getContentSize();
    float height = -mItemAlignPadding;
    float h = 0;

    if (NULL != mBg) {
        mBg->ignoreAnchorPointForPosition(false);
        mBg->setAnchorPoint(ccp(0.5f, 0.5f));
        mBg->setPosition(getContentSize().width / 2, getContentSize().height / 2);
    }

    for (int i = 0; i < ITEM_NUM(mItems); ++i) {
        CCNode* pChild = mItems[i];
        if (NULL != pChild) {
            if (BUTTON_GROUP == i) { // CCMenu size need recalcurate.
                CCRect rc = CocosUtils::getMenuMinBounding((CCMenu *) pChild);
                h = rc.size.height;
            } else {
                h = pChild->getContentSize().height;
            }
            height += h * pChild->getScaleY() + mItemAlignPadding;
        }
    }

    float y = bgSize.height / 2.0f + height / 2.0f;
    for (int i = 0; i < ITEM_NUM(mItems); ++i) {
        CCNode* pChild = mItems[i];
        if (NULL != pChild) {
            if (BUTTON_GROUP == i) { // CCMenu size need recalcurate.
                h = CocosUtils::getMenuMinBounding((CCMenu *) pChild).size.height;
            } else {
                h = pChild->getContentSize().height;
            }
            if (NULL != mItemsPos[i]) { // Releative position over write layout.
                pChild->setPosition(ccp(bgSize.width * mItemsPos[i]->x, bgSize.height * mItemsPos[i]->y));
            } else {
                pChild->setPosition(ccp(bgSize.width * 0.5,
                y - h * pChild->getScaleY() / 2.0f));
            }
            y -= h * pChild->getScaleY() + mItemAlignPadding;
        }
    }
}

void Dialog::setItemPadding(float padding) {
    mItemAlignPadding = padding;
    layout();
}

void Dialog::alignButtonVertically(float padding) {
    mButtonAlignPadding = padding;
    mButtonAlignOrientation = VERTICAL;
    ((CCMenu *) mItems[BUTTON_GROUP])->alignItemsVerticallyWithPadding(mButtonAlignPadding);
}

void Dialog::alignButtonHorizontally(float padding) {
    mButtonAlignPadding = padding;
    mButtonAlignOrientation = HORIZONTAL;
    ((CCMenu *) mItems[BUTTON_GROUP])->alignItemsHorizontallyWithPadding(mButtonAlignPadding);
}

void Dialog::setButtonGroupReleativePosition(const cocos2d::CCPoint& pos) {
    if (NULL == mItemsPos[BUTTON_GROUP]) {
        mItemsPos[BUTTON_GROUP] = new CCPoint(pos);
        if (NULL != mItems[BUTTON_GROUP]) layout();
    }
}

void Dialog::setTitleReleativePosition(const cocos2d::CCPoint& pos) {
    if (NULL == mItemsPos[TITLE]) {
        mItemsPos[TITLE] = new CCPoint(pos);
        if (NULL != mItems[TITLE]) layout();
    }
}

void Dialog::setMessageReleativePosition(const cocos2d::CCPoint& pos) {
    if (NULL == mItemsPos[MESSAGE]) {
        mItemsPos[MESSAGE] = new CCPoint(pos);
        if (NULL != mItems[MESSAGE]) layout();
    }
}

void Dialog::setTitle(CCNode *title) {
    if (NULL != mItems[TITLE]) {
        removeChild(mItems[TITLE]);
        mItems[TITLE] = NULL;
    }
    if (NULL != title) {
        mItems[TITLE] = dynamic_cast<CCNode*>(title);
        if (NULL != mItems[TITLE]) {
            addChild(mItems[TITLE]);
        }
    }
    layout();
}

Dialog::~Dialog() {
    for (int i = 0; i < ITEM_NUM(mItemsPos); ++i) {
        delete mItemsPos[i];
    }
}

void Dialog::setMessage(CCNode *custom) {
    if (NULL != mItems[MESSAGE]) {
        removeChild(mItems[MESSAGE]);
        mItems[MESSAGE] = NULL;
    }
    if (NULL != custom) {
        mItems[MESSAGE] = custom;
        addChild(mItems[MESSAGE]);
    }
    layout();
}

void Dialog::setButton(cocos2d::CCMenuItem *btn, int which) {
    if (which >= 0 && which < BUTTON_TOTAL) {
        if (NULL != mButtons[which]) {
            mButtons[which]->setTarget(NULL, NULL);
            mItems[BUTTON_GROUP]->removeChild(mButtons[which], true);
            mButtons[which] = NULL;
        }
        if (NULL != btn) {
            mButtons[which] = btn;
            mItems[BUTTON_GROUP]->addChild(btn);
            btn->setTarget(this, menu_selector(Dialog::onButtonClick));
        }
        switch (mButtonAlignOrientation) {
            case VERTICAL:
                ((CCMenu *) mItems[BUTTON_GROUP])->alignItemsVerticallyWithPadding(mButtonAlignPadding);
                break;
            case HORIZONTAL:
            default:
                ((CCMenu *) mItems[BUTTON_GROUP])->alignItemsHorizontallyWithPadding(mButtonAlignPadding);
                break;
        }
        layout();
    }
}

cocos2d::CCMenuItem *Dialog::getButton(int which) {
    if (which >= 0 && which < BUTTON_TOTAL) {
        return mButtons[which];
    }
    return NULL;
}

void Dialog::onButtonClick(cocos2d::CCObject* pSender) {
    assert(NULL != pSender);
    if (NULL != mOnClickListener) {
        for (int i = 0; i < ITEM_NUM(mButtons); ++i) {
            if (pSender == mButtons[i]) {
                if (mOnClickListener->onClick(this, i)) {
                    dismiss();
                }
                break;
            }
        }
    } else {
        CCLOGWARN("No OnClickListener set in Dialog %p.", pSender);
        dismiss();
    }
}

void Dialog::show() {
    show(false);
}

void Dialog::show(bool disposable) {
    if (getParent() == NULL && NULL != mParent) {
        mParent->addChild(this, Dialog::baseZOrder());
    }
    setVisible(true);
    mDisposable = disposable;
}

void Dialog::setVisible(bool visible) {
    CCLayerColor::setVisible(visible);
    if (visible) {
        if (NULL != mOnShowListener) {
            mOnShowListener->onShow(this);
        }
    } else {
        if (NULL != mOnDismissListener) {
            mOnDismissListener->onDismiss(this);
        }
    }
}

void Dialog::dismiss() {
    setVisible(false);
    if (mDisposable && getParent() != NULL) {
        removeFromParent();
    }
}
