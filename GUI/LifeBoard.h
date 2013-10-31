// Created by kanedong on 13-9-13.
//



#ifndef __LIFEBOARD_H_
#define __LIFEBOARD_H_

#include "cocos2d.h"

USING_NS_CC;

struct LifeBoardStateListener;

class LifeBoard : public CCLayerColor {
public:
    enum Orientation {HORIZONTAL, VERTICAL};
    static LifeBoard* create(int maxLife, CCSpriteFrame* indicator, CCSpriteFrame* slot = NULL);

    void setLifeIndicator(CCSpriteFrame* indicator);
    void setOrientation(Orientation orientation);
    // Set max life num, but don't change current life num.
    void setMaxLifeNum(int num);
    int  getMaxLifeNum() const { return mLifeIndicator.size(); }
    void setIncreaseAction(CCAction* action) { mIncreaseAction = action; }
    void setDecreaseAction(CCAction* action) { mDecreaseAction = action; }
    int lifeIncrease(int direction = 0);
    int lifeDecrease(int direction = 0);
    void setLifeNum(int num);
    int  getLifeNum() const { return mLifeNum; }
    void reset();
    void clear();
    void addStateListener(LifeBoardStateListener* listener);
    void removeStateListener(LifeBoardStateListener* listener);
    void setPadding(float padding);

private:
    CREATE_FUNC(LifeBoard);
    LifeBoard();
    void layout();

    std::vector<CCSprite*> mLifeIndicator;
    std::vector<CCSprite*> mLifeSlot;
    std::set<LifeBoardStateListener*> mListeners;
    CCSpriteFrame* mIndicator, *mSlot;
    CCAction* mIncreaseAction;
    CCAction*mDecreaseAction;
    Orientation mOrientation;
    int mLifeNum;
    float mPadding;
};

struct LifeBoardStateListener {
    // If callback will change visibility of indicator, please return true.
    virtual bool onLifeIncrease(CCNode* indicator) = 0;
    virtual bool onLifeDecrease(CCNode* indicator) = 0;

    virtual void onLifeChanged(int oldLife, int newLife) = 0;
};

#endif //__LIFEBOARD_H_
