#pragma once

#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "../Model/Rect.h"

class Shape
{
public:
    //责判断一个点是否在一个矩形的范围内。
    //CheckInterSect函数负责判断两个矩形是否重合。
    static bool CheckPointInRect(Point point, Rect rect);
    static bool CheckIntersect(Rect rectA,Rect rectB);
};

#endif