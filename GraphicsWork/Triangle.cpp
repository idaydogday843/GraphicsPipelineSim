#include "DataStructure.h"
#include <WinUser.h>
#include "WindowsGUI.h"
#include <iostream>
#include "Algorithms.h"

using namespace std;

Triangle::Triangle(Vertex& v1, Vertex& v2, Vertex& v3)		// 三角形的构造函数，参数为三角形的三个顶点
{
	v[0] = v1;
	v[1] = v2;
	v[2] = v3;
	normal = ((v1.position - v2.position) * (v2.position - v3.position)).normalize();
	diffuse = 0.5;
	specular = 0.5;
	phong = 128;
	addSurface(v1);
	addSurface(v2);
	addSurface(v3);
}

Triangle::Triangle(const Triangle& copy_t)
{
	for (int i = 0; i < 3; i++)
	{
		v[i] = copy_t.v[i];
	}
	phong = 128;
	specular = 0.5;
	diffuse = 0.5;
	normal = ((v[0].position - v[1].position) * (v[1].position - v[2].position)).normalize();
}

void Triangle::addSurface(Vertex& v)
{
	v.surfaceNormals[v.cSurface] = normal;
	v.cSurface++;
	v.updateNormal();
}