#include "HilberLine.h"
#include "framework.h"
#include "SetConfig.h"

#include <cmath>

#define HALFPI 1.5707963
#define PI 3.1415926

SquareSide* SquareSide::instance = nullptr;

ZjhDirection HilberLine::GetDirection()
{
	return mDirection;
}

void HilberLine::DrawLine(const HWND& hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	HPEN hpen = CreatePen(PS_SOLID, 3, RGB(250, 100, 20));
	SelectObject(hdc, hpen);
	int pts[] = { round(mStartPoint.X),round(mStartPoint.Y),round(mEndPoint.X),round(mEndPoint.Y) };//四舍五入
	Polyline(hdc, (POINT*)pts, 2);
	EndPaint(hWnd, &ps);
}

SquareSide::SquareSide()
{
	if (SetConfig::zjhScreenWidth >= 1026) {//如果屏幕大于1026,方框就按照1024来设置
		mPoint1 = ZjhPoint2D((SetConfig::zjhScreenWidth - 1024) / 2.0f, (SetConfig::zjhScreenHeight - 1024) / 2.0f);
		mPoint2 = ZjhPoint2D(mPoint1.X + 1024, mPoint1.Y);
		mPoint3 = ZjhPoint2D(mPoint2.X, mPoint1.Y + 1024);
	}
	else if (SetConfig::zjhScreenWidth >= 514) {//如果屏幕大于514,方框就按照512来设置
		mPoint1 = ZjhPoint2D((SetConfig::zjhScreenWidth - 512) / 2.0f, (SetConfig::zjhScreenHeight - 512) / 2.0f);
		mPoint2 = ZjhPoint2D(mPoint1.X + 512, mPoint1.Y);
		mPoint3 = ZjhPoint2D(mPoint2.X, mPoint1.Y + 512);
	}
	else if (SetConfig::zjhScreenWidth >= 258) {//如果屏幕大于258,方框就按照256来设置
		mPoint1 = ZjhPoint2D((SetConfig::zjhScreenWidth - 256) / 2.0f, (SetConfig::zjhScreenHeight - 256) / 2.0f);
		mPoint2 = ZjhPoint2D(mPoint1.X + 256, mPoint1.Y);
		mPoint3 = ZjhPoint2D(mPoint2.X, mPoint1.Y + 256);
	}
	else if (SetConfig::zjhScreenWidth >= 130) {//如果屏幕大于130,方框就按照128来设置
		mPoint1 = ZjhPoint2D((SetConfig::zjhScreenWidth - 128) / 2.0f, (SetConfig::zjhScreenHeight - 128) / 2.0f);
		mPoint2 = ZjhPoint2D(mPoint1.X + 128, mPoint1.Y);
		mPoint3 = ZjhPoint2D(mPoint2.X, mPoint1.Y + 128);
	}
	else if(SetConfig::zjhScreenWidth >= 66) {//如果屏幕大于66,方框就按照64来设置
		mPoint1 = ZjhPoint2D((SetConfig::zjhScreenWidth - 64) / 2.0f, (SetConfig::zjhScreenHeight - 64) / 2.0f);
		mPoint2 = ZjhPoint2D(mPoint1.X + 64, mPoint1.Y);
		mPoint3 = ZjhPoint2D(mPoint2.X, mPoint1.Y + 64);
	}
	else
	{
		throw("too small!");
	}
	mPoint4 = ZjhPoint2D(mPoint1.X, mPoint3.Y);
	hilberUs.clear();
}

void SquareSide::Draw(const HWND& hWnd, ZjhColor incolor)
{
	//设置边框线宽
	HDC hdc = GetDC(hWnd);
	int edgewidth = 1;
	if ((SetConfig::zjhScreenWidth - 1024) >= 2) {//如果屏幕宽高都大于1024
		edgewidth = (SetConfig::zjhScreenWidth - 1024) / 2;
	}
	HPEN hpen = CreatePen(PS_SOLID, edgewidth, RGB(incolor.R, incolor.G, incolor.B));
	SelectObject(hdc, hpen);
	int pts[] = { round(mPoint1.X),round(mPoint1.Y),round(mPoint2.X),round(mPoint2.Y),round(mPoint3.X),round(mPoint3.Y),round(mPoint4.X),round(mPoint4.Y),round(mPoint1.X),round(mPoint1.Y) };//四舍五入
	Polyline(hdc, (POINT*)pts, 5);
}

SquareSide* SquareSide::GetInstance()
{
	if (instance != nullptr) return instance;
	instance = new SquareSide();
	return instance;
}

HilberU::HilberU(ZjhPoint2D inP1, ZjhPoint2D inP2, ZjhPoint2D inP3, ZjhPoint2D inP4)
{
	mPoint1 = inP1;	mPoint2 = inP2; mPoint3 = inP3; mPoint4 = inP4;
	mCenter = (mPoint1 + mPoint3) * 0.5;
	mEdgeLen = (mPoint3 - mPoint2).Length();
	mDirection = (mPoint1 + mPoint2).GetDirection();
}

HilberU::HilberU(ZjhPoint2D center, ZjhDirection inDir, double inLen)
{
	mCenter = center; mDirection = inDir; mEdgeLen = inLen;
	double halfEdgeLen = inLen * 0.5;
	ZjhPoint2D LU_point = ZjhPoint2D(center.X - halfEdgeLen, center.Y - halfEdgeLen);//左上角
	ZjhPoint2D RU_point = ZjhPoint2D(center.X + halfEdgeLen, center.Y - halfEdgeLen);//右上角
	ZjhPoint2D RD_point = ZjhPoint2D(center.X + halfEdgeLen, center.Y + halfEdgeLen);//右下角
	ZjhPoint2D LD_point = ZjhPoint2D(center.X - halfEdgeLen, center.Y + halfEdgeLen);//左下角
	switch (inDir)
	{
	case Up:
		mPoint1 = RU_point;
		mPoint2 = RD_point;
		mPoint3 = LD_point;
		mPoint4 = LU_point;
		break;
	case Left:
		mPoint1 = LU_point;
		mPoint2 = RU_point;
		mPoint3 = RD_point;
		mPoint4 = LD_point;
		break;
	case Down:
		mPoint1 = LD_point;
		mPoint2 = LU_point;
		mPoint3 = RU_point;
		mPoint4 = RD_point;
		break;
	case Right:
		mPoint1 = RD_point;
		mPoint2 = LD_point;
		mPoint3 = LU_point;
		mPoint4 = RU_point;
		break;
	default:
		break;
	}
}

void HilberU::Draw(const HWND& hWnd, ZjhColor incolor)
{
	HDC hdc = GetDC(hWnd);
	HPEN hpen = CreatePen(PS_SOLID, 1, RGB(incolor.R, incolor.G, incolor.B));
	SelectObject(hdc, hpen);
	int pts[] = { round(mPoint1.X),round(mPoint1.Y),round(mPoint2.X),round(mPoint2.Y),round(mPoint3.X),round(mPoint3.Y),round(mPoint4.X),round(mPoint4.Y) };//四舍五入
	Polyline(hdc, (POINT*)pts, 4);
}

void HilberU::DrawLine(const HWND& hWnd, ZjhColor incolor,ZjhPoint2D point1,ZjhPoint2D point2)
{
	HDC hdc = GetDC(hWnd);
	HPEN hpen = CreatePen(PS_SOLID, 1, RGB(incolor.R, incolor.G, incolor.B));
	SelectObject(hdc, hpen);
	int pts[] = { round(point1.X),round(point1.Y),round(point2.X),round(point2.Y) };//四舍五入
	Polyline(hdc, (POINT*)pts, 2);
}

std::vector<HilberU> HilberU::Split(const HWND& hWnd, ZjhColor inC)
{
	std::vector<HilberU> hilbertUs;
	ZjhPoint2D dirPoint = ZjhPoint2D::GetPoint2D(mDirection);
	hilbertUs.push_back(HilberU(mPoint1, dirPoint.Rotate(HALFPI).GetDirection(), 0.5 * mEdgeLen));
	hilbertUs.push_back(HilberU(mPoint2, mDirection, 0.5 * mEdgeLen));
	hilbertUs.push_back(HilberU(mPoint3, mDirection, 0.5 * mEdgeLen));
	hilbertUs.push_back(HilberU(mPoint4, dirPoint.Rotate(-HALFPI).GetDirection(), 0.5 * mEdgeLen));
	for (HilberU var : hilbertUs)
	{
		var.Draw(hWnd, inC);
	}
	DrawLine(hWnd, inC, hilbertUs[0].mPoint1, hilbertUs[1].mPoint1);
	DrawLine(hWnd, inC, hilbertUs[1].mPoint4, hilbertUs[2].mPoint1);
	DrawLine(hWnd, inC, hilbertUs[2].mPoint4, hilbertUs[3].mPoint4);
	return hilbertUs;
}

double ZjhPoint2D::Length()
{
	return sqrt(SquLength());
}

ZjhDirection ZjhPoint2D::GetDirection()
{
	if (X > 0 && abs(Y) < 0.001) return ZjhDirection::Right;
	if (X < 0 && abs(Y) < 0.001)return ZjhDirection::Left;
	if (Y > 0 && abs(X) < 0.001)return ZjhDirection::Down;
	if (Y < 0 && abs(X) < 0.001)return ZjhDirection::Up;
}

ZjhPoint2D ZjhPoint2D::GetPoint2D(ZjhDirection inDir)
{
	switch (inDir)
	{
	case Up:
		return ZjhPoint2D(0, -1);
	case Left:
		return ZjhPoint2D(-1, 0);
	case Down:
		return ZjhPoint2D(0, 1);
	case Right:
		return ZjhPoint2D(1, 0);
	default:
		break;
	}
}


ZjhPoint2D ZjhPoint2D::Rotate(double rad)
{
	return ZjhPoint2D(X * cos(rad) - Y * sin(rad), X * sin(rad) + Y * cos(rad));
}
