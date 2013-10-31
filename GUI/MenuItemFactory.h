//
// Created by kanedong on 13-9-23.
//



#ifndef __MenuItemFacotry_H_
#define __MenuItemFacotry_H_

namespace cocos2d {
    class CCMenuItem;
    class CCNode;
    class CCSpriteFrame;
}

class MenuItemFactory {
public:
    static cocos2d::CCMenuItem *createZoomMenu(cocos2d::CCSpriteFrame *skin,  float zoomFactor);
	static cocos2d::CCMenuItem *createZoomMenu(cocos2d::CCNode *skin,
            cocos2d::CCNode *skin2, float zoomFactor);
};


#endif //__MenuItemFacotry_H_
