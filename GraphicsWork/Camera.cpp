#include "DataStructure.h"
#include "Algorithms.h"

Camera::Camera(Vector3D position)		// ������Ĺ��캯��������Ϊ3D����: ���꣬���㷽����ͼ����
{
	Camera::position = position;
	Camera::direction = Vector3D(0.0, 0.0, -1.0);
	Camera::view_up = Vector3D(0.0, 1.0, 0.0);
}

Camera::Camera()
{
	Camera::position = Vector3D();
	Camera::direction = Vector3D(0.0, 0.0, -1.0);
	Camera::view_up = Vector3D(0.0, 1.0, 0.0);
}

