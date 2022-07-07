
// cursova16.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы

#include <string>
#include <fstream>
// Ccursova16App:
// Сведения о реализации этого класса: cursova16.cpp
//
using namespace std;
class Ccursova16App : public CWinApp
{
public:
	Ccursova16App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};
class Point
{
	int x, y;
public:
	Point() {}
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	int GetX() { return x; }
	int GetY() { return y; }
	void SetXY(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

};
class RectAngle
{
	int Index = 0;


	byte R = 0, G = 0, B = 0;
	Point Pnt1, Pnt2, Pnt3, Pnt4;
	int* Arr;
public:

	int GetIndex() { return Index; }
	RectAngle() {}
	void SetRect(Point A, Point B, Point C, Point D)
	{
		Pnt1 = A;
		Pnt2 = B;
		Pnt3 = C;
		Pnt4 = D;
	}

	void SetArr(int* OldArr, int value)
	{
		Arr = new int[value];
		for (int i = 0; i < value; i++)
		{
			Arr[i] = OldArr[i];
		}
		Index = value;
	}

	void SetRGB(byte R, byte G, byte B)
	{
		this->R = R;
		this->G = G;
		this->B = B;
	}
	Point GetPoint1() { return Pnt1; }
	Point GetPoint2() { return Pnt2; }
	Point GetPoint3() { return Pnt3; }
	Point GetPoint4() { return Pnt4; }
	void SetColorAll(RectAngle* RectArr)
	{

		for (int i = 0; i < Index; i++)
		{
			RectArr[Arr[i]].SetRGB(153, 0, 255);
		}

	}
	void Drawing(CPaintDC& dc)
	{
		CPen Pen(PS_SOLID, 2, RGB(R, G, B));
		dc.SelectObject(Pen);
		dc.MoveTo(Pnt1.GetX(), Pnt1.GetY());
		dc.LineTo(Pnt2.GetX(), Pnt2.GetY());
		dc.LineTo(Pnt3.GetX(), Pnt3.GetY());
		dc.LineTo(Pnt4.GetX(), Pnt4.GetY());
		dc.LineTo(Pnt1.GetX(), Pnt1.GetY());
	}
	void WriteToFile(ofstream& fout, RectAngle* arrRect)
	{
		for (int i = 0; i < Index; i++)
		{
			fout << "Quadrangle" << i + 2 << " x1=" << arrRect[Arr[i]].GetPoint1().GetX() << ", y1=" << arrRect[Arr[i]].GetPoint1().GetY()
				<< ", x2=" << arrRect[Arr[i]].GetPoint2().GetX() << ", y2=" << arrRect[Arr[i]].GetPoint2().GetY()
				<< ", x3=" << arrRect[Arr[i]].GetPoint3().GetX() << ", y3=" << arrRect[Arr[i]].GetPoint3().GetY()
				<< ", x4=" << arrRect[Arr[i]].GetPoint4().GetX() << ", y4=" << arrRect[Arr[i]].GetPoint4().GetY() << ";\n";
		}
	}
	~RectAngle()
	{
		delete Arr;
	}
};
class SystemProgram
{
private:
	string name;
	ofstream fout;
	int  x, y, ValueOfRect = 0;
	Point Pnt1, Pnt2, Pnt3, Pnt4;
	ifstream ifs;
	RectAngle* RectArr;

public:
	SystemProgram() {}
	void Init()
	{
		ifs.open("RectAngel.txt");
		if (!ifs.is_open()) {}
		else
		{
			while (!ifs.eof())
			{
				ifs >> name;
				ifs >> x;
				ifs >> y;
				ifs >> x;
				ifs >> y;
				ifs >> x;
				ifs >> y;
				ifs >> x;
				ifs >> y;
				ValueOfRect++;
			}
		}
		ifs.close();

		RectArr = new RectAngle[ValueOfRect];

		ifs.open("RectAngel.txt");
		if (!ifs.is_open()) {}
		else
		{
			int i = 0;
			while (!ifs.eof())
			{
				ifs >> name;
				ifs >> x;

				ifs >> y;
				Pnt1 = Point(x, y);
				ifs >> x;

				ifs >> y;
				Pnt2 = Point(x, y);

				ifs >> x;

				ifs >> y;
				Pnt3 = Point(x, y);

				ifs >> x;

				ifs >> y;
				Pnt4 = Point(x, y);
				RectArr[i].SetRect(Pnt1, Pnt2, Pnt3, Pnt4);
				i++;
			}
		}
		ifs.close();
	}

	void Run()
	{
		for (int i = 0; i < ValueOfRect; i++)
		{
			int* Arr = new int[ValueOfRect];
			int it = 0;

			for (int j = 0; j < ValueOfRect; j++)
			{
				if (i != j)
				{
					if (RectArr[i].GetPoint1().GetX() < RectArr[j].GetPoint1().GetX() && RectArr[i].GetPoint1().GetY() < RectArr[j].GetPoint1().GetY())
					{
						if (RectArr[i].GetPoint2().GetX() > RectArr[j].GetPoint2().GetX() && RectArr[i].GetPoint2().GetY() < RectArr[j].GetPoint2().GetY())
						{
							if (RectArr[i].GetPoint3().GetX() > RectArr[j].GetPoint3().GetX() && RectArr[i].GetPoint3().GetY() > RectArr[j].GetPoint3().GetY())
							{
								if (RectArr[i].GetPoint4().GetX() < RectArr[j].GetPoint4().GetX() && RectArr[i].GetPoint4().GetY() > RectArr[j].GetPoint4().GetY())
								{
									Arr[it] = j;
									it++;
									RectArr[i].SetRGB(255, 0, 153);
									RectArr[j].SetRGB(255, 0, 153);

								}
							}
						}
					}
				}
			}
			RectArr[i].SetArr(Arr, it);
			delete[] Arr;


		}

		int maxIndex = 0;
		int maxI = 0;
		for (int i = 0; i < ValueOfRect; i++)
		{
			if (maxIndex < RectArr[i].GetIndex())
			{
				maxIndex = RectArr[i].GetIndex();
				maxI = i;
			}
		}


		RectArr[maxI].SetRGB(153, 0, 255);
		RectArr[maxI].SetColorAll(RectArr);
		fout.open("NewCoord.txt");
		fout << "Quadrangle" << 1 << " x1=" << RectArr[maxI].GetPoint1().GetX() << ", y1=" << RectArr[maxI].GetPoint1().GetY()
			<< ", x2=" << RectArr[maxI].GetPoint2().GetX() << ", y2=" << RectArr[maxI].GetPoint2().GetY()
			<< ", x3=" << RectArr[maxI].GetPoint3().GetX() << ", y3=" << RectArr[maxI].GetPoint3().GetY()
			<< ", x4=" << RectArr[maxI].GetPoint4().GetX() << ", y4=" << RectArr[maxI].GetPoint4().GetY() << ";\n";
		if (!fout.is_open()) {}

		else
		{
			RectArr[maxI].WriteToFile(fout, RectArr);
		}
		fout.close();

	}
	void Draw(CPaintDC& dc)
	{
		for (int i = 0; i < ValueOfRect; i++)
		{
			RectArr[i].Drawing(dc);
		}

	}
	~SystemProgram()
	{
		for (int i = 0; i < ValueOfRect; i++)
		{
			RectArr[i].~RectAngle();
		}
		delete[] RectArr;

	}

};
extern SystemProgram program;
extern Ccursova16App theApp;
