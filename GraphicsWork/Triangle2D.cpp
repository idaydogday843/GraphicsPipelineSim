#include "DataStructure.h"
#include <WinUser.h>
#include "WindowsGUI.h"
#include <iostream>
#include "Algorithms.h"

Triangle2D::Triangle2D(Point2D a, Point2D b, Point2D c)
{
	Triangle2D::p[0] = a;
	Triangle2D::p[1] = b;
	Triangle2D::p[2] = c;
}

Triangle2D::Triangle2D()
{
	Triangle2D::p[0] = Point2D();
	Triangle2D::p[1] = Point2D();
	Triangle2D::p[2] = Point2D();
}