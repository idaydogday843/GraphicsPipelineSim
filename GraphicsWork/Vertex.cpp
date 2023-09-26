#include "DataStructure.h"
#include "Algorithms.h"

Vertex::Vertex(Vector3D position)			// ����Ĺ��캯��������Ϊ���������
{
	Vertex::position = position;
	Vertex::color = Vector3D(255.0, 255.0, 255.0);
	Vertex::surfaceNormals = new Vector3D[16]();
	Vertex::cSurface = 0;
	Vertex::normal = averageNormal();
	uv[0] = 0.0;
	uv[1] = 0.0;
}

Vertex::Vertex(double x, double y, double z)
{
	Vertex::position = Vector3D(x, y, z);
	Vertex::color = Vector3D(255.0, 255.0, 255.0);
	Vertex::surfaceNormals = new Vector3D[16]();
	Vertex::surfaceNormals[0] = Vector3D();
	Vertex::cSurface = 0;
	Vertex::normal = averageNormal();
	uv[0] = 0.0;
	uv[1] = 0.0;
}

Vertex::Vertex()							// �����Ĭ�Ϲ��캯����Ĭ�϶���Ϊ����ϵԭ��
{
	Vertex::position = Vector3D(0.0, 0.0, 0.0);
	Vertex::color = Vector3D(255.0, 255.0, 255.0);
	Vertex::surfaceNormals = new Vector3D[16]();
	Vertex::surfaceNormals[0] = Vector3D();
	Vertex::cSurface = 0;
	Vertex::normal = averageNormal();
	uv[0] = 0.0;
	uv[1] = 0.0;
}

Vector3D Vertex::averageNormal()
{
	if (cSurface == 0)
	{
		return Vector3D(0.0, 0.0, 0.0);
	}
	Vector3D average = surfaceNormals[0];
	for (int i = 1; i < cSurface; i++)
	{
		average = (average + surfaceNormals[i]).normalize();
	}
	return average;
}

void Vertex::updateNormal()
{
	normal = averageNormal();
}
