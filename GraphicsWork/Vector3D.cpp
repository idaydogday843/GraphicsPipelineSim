#include "DataStructure.h"
#include <iostream>
#include "Algorithms.h"

using namespace std;

Vector3D::Vector3D(double x, double y, double z)	// 3D�������캯��������Ϊx���꣬y���꣬z����
{
	Vector3D::x = x;
	Vector3D::y = y;
	Vector3D::z = z;
}

Vector3D::Vector3D()								// 3D����Ĭ�Ϲ��캯����������Ϊx�ᵥλ����
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

Vector3D Vector3D::operator+(Vector3D v)		// 3D�����ӷ�����ȡ���������ĺ�
{
	return Vector3D(v.x + x, v.y + y, v.z + z);
}

Vector3D Vector3D::operator-(Vector3D v)		// 3D������������ȡ�����ľ���
{
	return Vector3D(x - v.x, y - v.y, z - v.z);
}

double Vector3D::dot_product(Vector3D v)	// 3D������ˣ������ڻ�ȡ��������ļн�
{
	return v.x * x + v.y * y + v.z * z;
}

Vector3D Vector3D::operator*(Vector3D v)	// 3D�������
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

Vector3D Vector3D::transform(TransformMatrix4D transform_matrix)	// 3D������任����ĳ˻������Ϊ�任��ĵ�����
{
	double* element = transform_matrix.get_matrix_elements();
	double x_prime = *(element + 0 * 4) * x + *(element + 0 * 4 + 1) * y + *(element + 0 * 4 + 2) * z + *(element + 0 * 4 + 3);
	double y_prime = *(element + 1 * 4) * x + *(element + 1 * 4 + 1) * y + *(element + 1 * 4 + 2) * z + *(element + 1 * 4 + 3);
	double z_prime = *(element + 2 * 4) * x + *(element + 2 * 4 + 1) * y + *(element + 2 * 4 + 2) * z + *(element + 2 * 4 + 3);
	double denominator = *(element + 3 * 4) * x + *(element + 3 * 4 + 1) * y + *(element + 3 * 4 + 2) * z + *(element + 3 * 4 + 3);
	return Vector3D(x_prime / denominator, y_prime / denominator, z_prime / denominator);
}

