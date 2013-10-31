
#ifndef __DIALOG_H__
#define __DIALOG_H__

#include "cocos2d.h"
#include "Utils.h"

class Dialog;

INTERFACE_BEGIN(OnClickListener)
    virtual bool onClick(Dialog * dialog, int which) = 0;
INTERFACE_END

INTERFACE_BEGIN(OnShowListener)
    virtual void onShow(Dialog * dialog) = 0;
INTERFACE_END

INTERFACE_BEGIN(OnDismissListener)
    virtual void onDismiss(Dialog * dialog) = 0;
INTERFACE_END

class Dialog : public cocos2d::CCLayerColor {
public:
    enum Orientation {HORIZONTAL, VERTICAL};
    enum {BUTTON_POSITIVE, BUTTON_NEGATIVE, BUTTON_NEUTRAL, BUTTON_TOTAL};
    enum Item {TITLE, MESSAGE, BUTTON_GROUP, ITEM_TOTAL};
    enum Order {LEFT_TO_RIGHT, RIGHT_TO_LEFT };

    CREATE_FUNC(Dialog);
    static Dialog* create(
            cocos2d::CCNode *parent,
            cocos2d::CCMenuItem *btnPositive = NULL,
            cocos2d::CCMenuItem *btnNegative = NULL,
            cocos2d::CCMenuItem *btnNeutral = NULL);
    static int baseZOrder() { return USHRT_MAX; }

    virtual bool initWithMenuItem(
            cocos2d::CCNode *parent,
            cocos2d::CCMenuItem *btnPositive,
            cocos2d::CCMenuItem *btnNegative,
            cocos2d::CCMenuItem *btnNeutral);
    virtual void setTitle(CCNode *title);
    CCNode *getTitle() { return mItems[TITLE]; }
    virtual void setBackground(cocos2d::CCNode *bg);
    void show(bool disposable);
    virtual void show();
    virtual void dismiss();
    void setOnClickListener(OnClickListener* listener) { mOnClickListener = listener; }
    void setOnShowListener(OnShowListener* listener) { mOnShowListener = listener; }
    void setOnDismissListener(OnDismissListener* listener) { mOnDismissListener = listener; }
    virtual void setButton(cocos2d::CCMenuItem *btn, int which);
    cocos2d::CCMenuItem* getButton(int which);
    void alignButtonVertically(float padding = 0);
    void alignButtonHorizontally(float padding = 0);
    void setButtonGroupReleativePosition(const cocos2d::CCPoint& pos);
    const cocos2d::CCPoint* getButtonGroupReleativePosition() const {
        return mItemsPos[BUTTON_GROUP];
    }
    void setTitleReleativePosition(const cocos2d::CCPoint& pos);
    const cocos2d::CCPoint* getTitleReleativePosition() const {
        return mItemsPos[TITLE];
    }
    void setMessageReleativePosition(const cocos2d::CCPoint& pos);
    const cocos2d::CCPoint* getMessageReleativePosition() const {
        return mItemsPos[MESSAGE];
    }
    virtual void setMessage(CCNode* custom);
    CCNode *getMessage() { return mItems[MESSAGE]; }

    void setItemPadding(float padding);
    virtual void setVisible(bool visible);

    virtual ~Dialog();

protected:
    enum { DEFAULT_PADDING =  5 };

    Dialog() :
        mOnClickListener(NULL),
        mOnShowListener(NULL),
        mOnDismissListener(NULL),
        mBg(NULL),
        mParent(NULL),
        mButtonAlignOrientation(HORIZONTAL),
        mButtonAlignPadding(DEFAULT_PADDING),
        mItemAlignPadding(DEFAULT_PADDING),
        mDisposable(false)
    {
        memset(mButtons, 0, sizeof(mButtons));
        memset(mItems, 0, sizeof(mItems));
        memset(mItemsPos, 0, sizeof(mItemsPos));
    }

    virtual bool init();
    virtual void layout();
    void onButtonClick(cocos2d::CCObject* pSender);

    OnClickListener* mOnClickListener;
    OnShowListener* mOnShowListener;
    OnDismissListener* mOnDismissListener;

private:

    cocos2d::CCPoint* mItemsPos[ITEM_TOTAL];
    cocos2d::CCMenuItem* mButtons[BUTTON_TOTAL];
    cocos2d::CCNode* mItems[ITEM_TOTAL];
    cocos2d::CCNode* mBg;
    cocos2d::CCNode* mParent;
    Orientation mButtonAlignOrientation;
    float   mButtonAlignPadding;
    float   mItemAlignPadding;
    bool mDisposable;

};

#endif
