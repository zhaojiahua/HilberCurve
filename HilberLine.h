#pragma once
#include <wtypes.h>
#include <vector>

//希尔伯特曲线的方向是根据其SquareCenter(矩形中心)判断的,其矩心所在的方向的负方向
enum ZjhDirection
{
	Up = 1,
	Left = 2,
	Down = 3,
	Right = 4
};

struct ZjhPoint2D
{
	ZjhPoint2D() :X(0), Y(0) {}
	ZjhPoint2D(double inx, double iny) : X(inx), Y(iny) {}
	double X;
	double Y;
public:
	//重载运算符
	ZjhPoint2D operator+(ZjhPoint2D other) {
		return ZjhPoint2D(X + other.X, Y + other.Y);
	}
	ZjhPoint2D operator-(ZjhPoint2D other) {
		return ZjhPoint2D(X - other.X, Y - other.Y);
	}
	ZjhPoint2D operator*(double scalar) {
		return ZjhPoint2D(X * scalar, Y * scalar);
	}
	//模长
	double SquLength() {
		return X * X + Y * Y;
	}
	double Length();
	//根据向量获得方向
	ZjhDirection GetDirection();
	//根据方向获取向量
	static ZjhPoint2D GetPoint2D(ZjhDirection inDir);
	//向量旋转(规定顺时针方向为正方向旋转,逆时针方向为负方向旋转,传入的是弧度)
	ZjhPoint2D Rotate(double rad);
};

//颜色,用于染色
struct ZjhColor
{
	int R = 0;
	int G = 0;
	int B = 0;
	ZjhColor() {}
	ZjhColor(int inR, int inG, int inB) :R(inR), G(inG), B(inB) {}
};

class HilberLine
{
protected:
	ZjhPoint2D mSquareCenter;
	ZjhPoint2D mStartPoint;
	ZjhPoint2D mEndPoint;
	ZjhDirection mDirection;

public:
	HilberLine() {}
	HilberLine(ZjhPoint2D startPoint, ZjhPoint2D endPoint, ZjhPoint2D squCenter, ZjhDirection dirction)
		:mStartPoint(startPoint), mEndPoint(endPoint), mSquareCenter(squCenter), mDirection(dirction) {}
	ZjhDirection GetDirection();
	void DrawLine(const HWND& hWnd);
	virtual void ShearMove() = 0;
};

//每个希尔伯特U型折线都是由4个有顺序的点组成,也可以是由一个中心点和一个开口方向和大小(线段的长度)组成
class HilberU
{
	ZjhPoint2D mPoint1;
	ZjhPoint2D mPoint2;
	ZjhPoint2D mPoint3;
	ZjhPoint2D mPoint4;
	ZjhPoint2D mCenter;
	ZjhDirection mDirection = ZjhDirection::Down;
	double mEdgeLen;
public:
	HilberU(ZjhPoint2D inP1, ZjhPoint2D inP2, ZjhPoint2D inP3, ZjhPoint2D inP4);
	HilberU(ZjhPoint2D center, ZjhDirection inDir, double inLen);
	void Draw(const HWND& hWnd, ZjhColor incolor);
	void DrawLine(const HWND& hWnd, ZjhColor incolor, ZjhPoint2D point1, ZjhPoint2D point2);
	std::vector<HilberU> Split(const HWND& hWnd,ZjhColor inC);
};

//正方形边框(单例模式)
class SquareSide
{
	ZjhPoint2D mPoint1;
	ZjhPoint2D mPoint2;
	ZjhPoint2D mPoint3;
	ZjhPoint2D mPoint4;
private:
	SquareSide();
	SquareSide(ZjhPoint2D inP1, ZjhPoint2D inP2, ZjhPoint2D inP3, ZjhPoint2D inP4)
		:mPoint1(inP1), mPoint2(inP2), mPoint3(inP3), mPoint4(inP4) {}
public:
	void Draw(const HWND& hWnd, ZjhColor incolor);
	static SquareSide* instance;
	static SquareSide* GetInstance();

	ZjhColor backgroundC = ZjhColor(100, 200, 250);
	std::vector<HilberU> hilberUs;//要被遍历的所有希尔伯特U型折线HilberU
};