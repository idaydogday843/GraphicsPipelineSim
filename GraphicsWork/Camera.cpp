#include "DataStructure.h"
#include "Algorithms.h"

Camera::Camera(Vector3D position)		// 摄像机的构造函数，参数为3D向量: 坐标，拍摄方向，视图方向
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

