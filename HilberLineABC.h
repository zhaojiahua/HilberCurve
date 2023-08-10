#pragma once
#include "HilberLine.h"

//希尔伯特曲线都是由三条线组成的,其缺口向下的时候,左边的那条线段
class HilberLineA : public HilberLine
{
public:
    HilberLineA() {}
    HilberLineA(ZjhPoint2D startPoint, ZjhPoint2D endPoint, ZjhPoint2D squCenter, ZjhDirection dirction) :HilberLine(startPoint, endPoint, squCenter, dirction) {}
    void ShearMove() override;
};
//希尔伯特曲线都是由三条线组成的,其缺口向下的时候,上边的那条线段
class HilberLineB :    public HilberLine
{
public:
    void ShearMove() override;
};
//希尔伯特曲线都是由三条线组成的,其缺口向下的时候,右边的那条线段
class HilberLineC :    public HilberLine
{
public:
    void ShearMove() override;
};
