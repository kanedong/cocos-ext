//
// Created by kanedong on 13-9-24.
//



#ifndef __AbstractLayout_H_
#define __AbstractLayout_H_

#include "cocos2d.h"
#include "Utils.h"

class LayoutParams {
public:
    enum {MATCH_PARENT = -1, WRAP_CONTENT = -2};

    LayoutParams() : width(MATCH_PARENT), height(MATCH_PARENT) {}

    LayoutParams(int w, int h) :
    width(w), height(h)  {}

    LayoutParams(const LayoutParams& rhs) :
    width(rhs.width), height(rhs.height) {}

    int width;
    int height;
};

class PaddingLayoutParams : public LayoutParams {
public:
    PaddingLayoutParams(int lp, int tp, int rp, int bp) :
    leftPadding(lp), topPadding(tp), rightPadding(rp), bottomPadding(bp) {}

    PaddingLayoutParams(int w, int h) :
    LayoutParams(w, h), leftPadding(0), topPadding(0), rightPadding(0), bottomPadding(0) {}

    PaddingLayoutParams(const PaddingLayoutParams& rhs) :
    LayoutParams(rhs.width, rhs.height),
    leftPadding(rhs.leftPadding), topPadding(rhs.topPadding),
    rightPadding(rhs.rightPadding), bottomPadding(rhs.bottomPadding) {}

    int leftPadding;
    int topPadding;
    int rightPadding;
    int bottomPadding;
};

INTERFACE_BEGIN(BackgroundAdjustPolicy )
    virtual void onAdjust(cocos2d::CCNode* bg, const cocos2d::CCRect rc) = 0;
INTERFACE_END

// TODO: Some preset policy.
//class BackgroundFill : public BackgroundAdjustPolicy {
//
//};

class Layout : public cocos2d::CCLayerColor {
    public:

    Layout();
    virtual void addChild(CCNode* child, int zOrder, int tag);
    virtual void removeChild(CCNode* child, bool cleanup);
    virtual void addChild(CCNode *child);
    virtual void addChild(CCNode *child, int zOrder);
    virtual void removeChild(CCNode *child);

    void layout(const cocos2d::CCRect& rect);
    void invalidate();
    virtual bool setFrame(const cocos2d::CCRect& rect);
    virtual void onLayout(bool changed, const cocos2d::CCRect& rect) = 0;
    virtual void onMeasure() = 0;
    virtual void setBackground(cocos2d::CCNode* bg);
    virtual cocos2d::CCNode* getBackground() { return mBg; }
    void setLayoutParams(const LayoutParams& lp);
    virtual cocos2d::CCRect rect();
    virtual const cocos2d::CCPoint& getRealAnchorPoint();
    void setBackgroundAdjustPrority(BackgroundAdjustPolicy* prority);

    void measure();

protected:
    cocos2d::CCNode* mBg;
    LayoutParams* mLayoutParam;
    cocos2d::CCPoint mZeroPoint;
    BackgroundAdjustPolicy* mBgPrority;
};


#endif //__AbstractLayout_H_
