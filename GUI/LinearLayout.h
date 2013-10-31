//
// Created by kanedong on 13-9-24.
//



#ifndef __LinearLayout_H_
#define __LinearLayout_H_

#include "Layout.h"

class LinearLayoutParams : public PaddingLayoutParams {
public:
    LinearLayoutParams(int w,  int h) :
    PaddingLayoutParams(w, h) {}

    LinearLayoutParams(int w,  int h, float weight) :
    PaddingLayoutParams(w, h)  { this->weight = weight;}

    LinearLayoutParams(const LinearLayoutParams& rhs) :
    PaddingLayoutParams(rhs.leftPadding, rhs.topPadding, rhs.rightPadding, rhs.bottomPadding),
    gravity(rhs.gravity), weight(rhs.weight) {}
    int gravity;
    float weight;
};

class LinearLayout : public Layout {
public:
    enum Orientation {HORIZONTAL, VERTICAL};
    enum Gravity {
        LEFT = 0x01,
        TOP = 0x02,
        RIGHT = 0x04,
        BOTTOM = 0x08,
        CENTER_VERTICAL = 0x10,
        CENTER_HORIZONTAL = 0x20,
        CENTER = 0x30,
        FILL = 0xFF};
    CREATE_FUNC(LinearLayout);

    LinearLayout();
    void setOrientation(Orientation orientation);
    Orientation getOrientation() const { return mOrientation; }
    void setGravity(Gravity gravity);
    Gravity getGravity() const { return mGravity; }

protected:
    Orientation mOrientation;
    Gravity mGravity;

    virtual void onMeasure();

    virtual void onLayout(bool changed, const cocos2d::CCRect& rect);

    void vMeasure();
    void hMeasure();
    void vLayout();
    void hLayout();

};


#endif //__LinearLayout_H_
