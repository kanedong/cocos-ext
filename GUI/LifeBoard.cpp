// Created by kanedong on 13-9-13.
//


#include "LifeBoard.h"

#define Z_INDICATOR 2
#define Z_SLOT 1

LifeBoard* LifeBoard::create(int maxLife, CCSpriteFrame *indicator, CCSpriteFrame* slot) {
    LifeBoard* lifeBoard = LifeBoard::create();
    lifeBoard->mIndicator = indicator;
    lifeBoard->mSlot = slot;
    lifeBoard->setMaxLifeNum(maxLife);
    lifeBoard->setLifeNum(maxLife);
    return lifeBoard;
}

LifeBoard::LifeBoard() :
    mIndicator(NULL), mSlot(NULL), mIncreaseAction(NULL),
    mDecreaseAction(NULL), mOrientation(HORIZONTAL), mLifeNum(0),
    mPadding(0) {

}

void LifeBoard::addStateListener(LifeBoardStateListener *listener) {
    if (NULL != listener) {
        mListeners.insert(listener);
    }
}

void LifeBoard::removeStateListener(LifeBoardStateListener *listener) {
    if (NULL != listener) {
        mListeners.erase(listener);
    }
}

void LifeBoard::setOrientation(LifeBoard::Orientation orientation) {
    mOrientation = orientation;
    layout();
}

void LifeBoard::setLifeIndicator(CCSpriteFrame *indicator) {
    if (NULL != indicator && indicator != mIndicator) {
        mIndicator = indicator;
        int s = mLifeIndicator.size();
        for (int i = 0; i < s; ++i) {
            mLifeIndicator.at(i)->setDisplayFrame(indicator);
        }
        layout();
    }
}

void LifeBoard::setMaxLifeNum(int num) {
    assert(NULL != mIndicator);
    int s = mLifeIndicator.size();
    if (num > s) {
        while (mLifeIndicator.size() < num) {
            CCSprite* indicator = CCSprite::createWithSpriteFrame(mIndicator);
            if (NULL != indicator) {
                mLifeIndicator.push_back(indicator);
                addChild(indicator, Z_INDICATOR);
                indicator->setVisible(false);
            }
            if (NULL != mSlot) {
                CCSprite *slot = CCSprite::createWithSpriteFrame(mSlot);
                if (NULL != slot) {
                    mLifeSlot.push_back(slot);
                    addChild(slot, Z_SLOT);
                }
            }
        }
    } else if (num < s) {
        if (mLifeNum > num) mLifeNum = num;

        while (mLifeIndicator.size() > num) {
            removeChild(mLifeIndicator.back());
            mLifeIndicator.pop_back();
        }
        while (mLifeSlot.size() > num) {
            removeChild(mLifeSlot.back());
            mLifeSlot.pop_back();
        }
    }

    layout();
}

int LifeBoard::lifeIncrease(int direction) {
    int maxLife = mLifeIndicator.size();
    if (mLifeNum >= 0 && mLifeNum < maxLife) {
        CCSprite* indicator = mLifeIndicator.at(0 == direction ? mLifeNum : maxLife - mLifeNum - 1);
        bool changeVisible = true;
        assert(NULL != indicator);
        if (!mListeners.empty()) {
            std::set<LifeBoardStateListener*>::iterator itr = mListeners.begin();
            std::set<LifeBoardStateListener*>::iterator end = mListeners.end();
            for (; itr != end; ++itr) {
                ++mLifeNum;
                (*itr)->onLifeChanged(mLifeNum - 1, mLifeNum);
                // If callback will change visibility, then means event was consume.
                if (changeVisible && (*itr)->onLifeIncrease(indicator)) {
                    changeVisible = false;
                }
            }
        }
        if (changeVisible) indicator->setVisible(false);
    }
    return mLifeNum;
}

int LifeBoard::lifeDecrease(int direction) {
    int maxLife = mLifeIndicator.size();
    if (mLifeNum > 0) {
        --mLifeNum;
        CCSprite* indicator = mLifeIndicator.at(0 == direction ? mLifeNum : maxLife - mLifeNum - 1);
        bool changeVisible = true;
        assert(NULL != indicator);
        if (!mListeners.empty()) {
            std::set<LifeBoardStateListener*>::iterator itr = mListeners.begin();
            std::set<LifeBoardStateListener*>::iterator end = mListeners.end();
            for (; itr != end; ++itr) {
                (*itr)->onLifeChanged(mLifeNum + 1, mLifeNum);
                // If callback will change visibility, then means event was consume.
                if (changeVisible && (*itr)->onLifeDecrease(indicator)) {
                    changeVisible = false;
                }
            }
        }
        if (changeVisible) indicator->setVisible(false);
    }
    return mLifeNum;
}

void LifeBoard::reset() {
    mLifeNum = mLifeIndicator.size();
    setLifeNum(mLifeNum);
}

void LifeBoard::clear() {
    mLifeNum = 0;
    setLifeNum(mLifeNum);
}

void LifeBoard::setLifeNum(int num) {
    int maxLife = mLifeIndicator.size();
    if (num > maxLife) num = maxLife;
    if (mLifeNum != num && num >= 0) {
        if (!mListeners.empty()) {
            std::set<LifeBoardStateListener*>::iterator itr = mListeners.begin();
            std::set<LifeBoardStateListener*>::iterator end = mListeners.end();
            for (; itr != end; ++itr) {
                (*itr)->onLifeChanged(mLifeNum, num);
            }
        }
        mLifeNum = num;

        for (int i = 0; i < maxLife; ++i) {
            CCSprite* sprite = mLifeIndicator.at(i);
            if (i < num) {
                sprite->setVisible(true);
            } else {
                sprite->setVisible(false);
            }
        }
    }
}

void LifeBoard::setPadding(float padding) {
    mPadding = padding;
    layout();
}

void LifeBoard::layout() {
    assert(NULL != mIndicator);
    if (!mLifeIndicator.empty() && !mLifeSlot.empty()) {
        CCAssert(mLifeIndicator.size() == mLifeSlot.size(), "One indicator match one slot!");
    }
    int maxLife = mLifeIndicator.size();
    const CCRect indicatorRect = mIndicator->getRectInPixels();
    float realWidth = indicatorRect.size.width + mPadding;
    float realHeight = indicatorRect.size.height + mPadding;
    CCSize boardSize;
    if (HORIZONTAL == mOrientation) {
        boardSize.width = realWidth * maxLife;
        boardSize.height = realHeight;
    } else {
        boardSize.width = realWidth;
        boardSize.height = realHeight * maxLife;
    }
    setContentSize(boardSize);
    CCPoint anchor(0.5f, 0.5f);
    for (int i = 0; i < maxLife; ++i) {
        CCSprite* indicator = mLifeIndicator.at(i);
        indicator->setAnchorPoint(anchor);
        int h = HORIZONTAL == mOrientation ? i : 0;
        int v = HORIZONTAL == mOrientation ? 0 : i;
        indicator->setPosition(
                ccp((h + 1) * realWidth
                        - realWidth * anchor.x,
                (v + 1) * realHeight
                        - realHeight * anchor.y));
        if (NULL != mSlot) {
            CCSprite *slot = mLifeSlot.at(i);
            slot->setAnchorPoint(anchor);
            slot->setPosition(indicator->getPosition());
        }
    }
}
