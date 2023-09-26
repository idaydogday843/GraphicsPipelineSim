#include "DataStructure.h"
#include <WinUser.h>
#include "WindowsGUI.h"
#include <iostream>
#include "Algorithms.h"

Point2D::Point2D(double x, double y)
{
	Point2D::x = x;
	Point2D::y = y;
	Point2D::color = Vector3D(255.0, 255.0, 255.0);
}

Point2D::Point2D()
{
	Point2D::x = 0.0;
	Point2D::y = 0.0;
	Point2D::color = Vector3D(255.0, 255.0, 255.0);
}