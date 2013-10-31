//
// Created by kanedong on 13-9-20.
//



#ifndef __CocosUtils_H_
#define __CocosUtils_H_

#include "cocos2d.h"


class CocosUtils {
public:
    // Geometry helper function
    static inline bool isEmptySize(const cocos2d::CCSize& size) {
        return (0 >= size.width && 0 >= size.height);
    }

    static inline bool isEmptyRect(const cocos2d::CCRect& rect) {
        return isEmptySize(rect.size);
    }

    static cocos2d::CCRect unionRect(const cocos2d::CCRect& lrc,
            const cocos2d::CCRect& rrc);

    static cocos2d::CCPoint releativePosOfNode(const cocos2d::CCNode* node,
            float rx, float ry);
    // Control helper function
    static cocos2d::CCRect getMenuMinBounding(cocos2d::CCMenu* node);
    static cocos2d::CCRect getBoundRect(cocos2d::CCNode* node);
    static cocos2d::CCPoint getRealAnchorPoint(cocos2d::CCNode *node);
};


#endif //__CocosUtils_H_
