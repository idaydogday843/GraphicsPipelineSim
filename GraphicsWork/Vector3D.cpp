#include "DataStructure.h"
#include <iostream>
#include "Algorithms.h"

using namespace std;

Vector3D::Vector3D(double x, double y, double z)	// 3D向量构造函数，参数为x坐标，y坐标，z坐标
{
	Vector3D::x = x;
	Vector3D::y = y;
	Vector3D::z = z;
}

Vector3D::Vector3D()								// 3D向量默认构造函数，构造结果为x轴单位向量
{
	Vector3D::x = 1.0;
	Vector3D::y = 0.0;
	Vector3D::z = 0.0;
}

Vector3D::Vector3D(const Vector3D& copy_vec)
{
	Vector3D::x = copy_vec.x;
	Vector3D::y = copy_vec.y;
	Vector3D::z = copy_vec.z;
}

Vector3D Vector3D::operator+(Vector3D v)		// 3D向量加法，获取两个向量的和
{
	return Vector3D(v.x + x, v.y + y, v.z + z);
}

Vector3D Vector3D::operator-(Vector3D v)		// 3D向量减法，获取两点间的距离
{
	return Vector3D(x - v.x, y - v.y, z - v.z);
}

double Vector3D::dot_product(Vector3D v)	// 3D向量点乘，可用于获取两向量间的夹角
{
	return v.x * x + v.y * y + v.z * z;
}

Vector3D Vector3D::operator*(Vector3D v)	// 3D向量叉乘
{
	return Vector3D(y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y);
}

Vector3D Vector3D::operator*(double n)
{
	return Vector3D(x * n, y * n, z * n);
}

Vector3D Vector3D::operator-()
{
	return Vector3D(x * -1, y * -1, z * -1);
}

Vector3D Vector3D::normalize()
{
	double length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	Vector3D n = Vector3D(x / length, y / length, z / length);
	return n;
}

Vector3D Vector3D::transform(TransformMatrix4D transform_matrix)	// 3D向量与变换矩阵的乘积，结果为变换后的点坐标
{
	double* element = transform_matrix.get_matrix_elements();
	double x_prime = *(element + 0 * 4) * x + *(element + 0 * 4 + 1) * y + *(element + 0 * 4 + 2) * z + *(element + 0 * 4 + 3);
	double y_prime = *(element + 1 * 4) * x + *(element + 1 * 4 + 1) * y + *(element + 1 * 4 + 2) * z + *(element + 1 * 4 + 3);
	double z_prime = *(element + 2 * 4) * x + *(element + 2 * 4 + 1) * y + *(element + 2 * 4 + 2) * z + *(element + 2 * 4 + 3);
	double denominator = *(element + 3 * 4) * x + *(element + 3 * 4 + 1) * y + *(element + 3 * 4 + 2) * z + *(element + 3 * 4 + 3);
	return Vector3D(x_prime / denominator, y_prime / denominator, z_prime / denominator);
}

