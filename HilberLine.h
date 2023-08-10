#pragma once
#include <wtypes.h>
#include <vector>

//ϣ���������ߵķ����Ǹ�����SquareCenter(��������)�жϵ�,��������ڵķ���ĸ�����
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
	//���������
	ZjhPoint2D operator+(ZjhPoint2D other) {
		return ZjhPoint2D(X + other.X, Y + other.Y);
	}
	ZjhPoint2D operator-(ZjhPoint2D other) {
		return ZjhPoint2D(X - other.X, Y - other.Y);
	}
	ZjhPoint2D operator*(double scalar) {
		return ZjhPoint2D(X * scalar, Y * scalar);
	}
	//ģ��
	double SquLength() {
		return X * X + Y * Y;
	}
	double Length();
	//����������÷���
	ZjhDirection GetDirection();
	//���ݷ����ȡ����
	static ZjhPoint2D GetPoint2D(ZjhDirection inDir);
	//������ת(�涨˳ʱ�뷽��Ϊ��������ת,��ʱ�뷽��Ϊ��������ת,������ǻ���)
	ZjhPoint2D Rotate(double rad);
};

//��ɫ,����Ⱦɫ
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

//ÿ��ϣ������U�����߶�����4����˳��ĵ����,Ҳ��������һ�����ĵ��һ�����ڷ���ʹ�С(�߶εĳ���)���
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

//�����α߿�(����ģʽ)
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
	std::vector<HilberU> hilberUs;//Ҫ������������ϣ������U������HilberU
};