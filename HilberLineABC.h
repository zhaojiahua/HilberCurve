#pragma once
#include "HilberLine.h"

//ϣ���������߶�������������ɵ�,��ȱ�����µ�ʱ��,��ߵ������߶�
class HilberLineA : public HilberLine
{
public:
    HilberLineA() {}
    HilberLineA(ZjhPoint2D startPoint, ZjhPoint2D endPoint, ZjhPoint2D squCenter, ZjhDirection dirction) :HilberLine(startPoint, endPoint, squCenter, dirction) {}
    void ShearMove() override;
};
//ϣ���������߶�������������ɵ�,��ȱ�����µ�ʱ��,�ϱߵ������߶�
class HilberLineB :    public HilberLine
{
public:
    void ShearMove() override;
};
//ϣ���������߶�������������ɵ�,��ȱ�����µ�ʱ��,�ұߵ������߶�
class HilberLineC :    public HilberLine
{
public:
    void ShearMove() override;
};
