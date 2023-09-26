#include "DataStructure.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <windows.h>
#include "Algorithms.h"

using namespace std;

TransformMatrix4D::TransformMatrix4D(double* matrix_elements)			// 变换矩阵构造函数，参数为4*4的二维数组
{
	double* element = matrix_elements;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			TransformMatrix4D::elements[i][j] = *(element + 4 * i + j);
			//cout << "Element at row " << i << " column " << j << " inserted" << endl;
		}
	}
}

TransformMatrix4D::TransformMatrix4D()									// 变换矩阵默认构造函数，结果为4*4单位矩阵
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{
				TransformMatrix4D::elements[i][j] = 1;
			}
			else
			{
				TransformMatrix4D::elements[i][j] = 0;
			}
		}
	}
}

TransformMatrix4D::TransformMatrix4D(const TransformMatrix4D& copy_matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			TransformMatrix4D::elements[i][j] = copy_matrix.elements[i][j];

		}
	}
}

double* TransformMatrix4D::get_matrix_elements()							// 获取变换矩阵中的元素
{
	double* matrix_element = new double[16];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix_element[i * 4 + j] = elements[i][j];
			//if (j == 3)
			//{
			//	cout << elements[i][j] << endl;
			//}
			//else
			//{
			//	cout << elements[i][j] << ',';
			//}
		}
	}
	return matrix_element;
}

TransformMatrix4D TransformMatrix4D::operator*(TransformMatrix4D mat)
{
	double result[4][4] = {
			{elements[0][0] * mat.elements[0][0] + elements[0][1] * mat.elements[1][0] + elements[0][2] * mat.elements[2][0] + elements[0][3] * mat.elements[3][0],
			elements[0][0] * mat.elements[0][1] + elements[0][1] * mat.elements[1][1] + elements[0][2] * mat.elements[2][1] + elements[0][3] * mat.elements[3][1],
			elements[0][0] * mat.elements[0][2] + elements[0][1] * mat.elements[1][2] + elements[0][2] * mat.elements[2][2] + elements[0][3] * mat.elements[3][2],
			elements[0][0] * mat.elements[0][3] + elements[0][1] * mat.elements[1][3] + elements[0][2] * mat.elements[2][3] + elements[0][3] * mat.elements[3][3]},

			{elements[1][0] * mat.elements[0][0] + elements[1][1] * mat.elements[1][0] + elements[1][2] * mat.elements[2][0] + elements[1][3] * mat.elements[3][0],
			elements[1][0] * mat.elements[0][1] + elements[1][1] * mat.elements[1][1] + elements[1][2] * mat.elements[2][1] + elements[1][3] * mat.elements[3][1],
			elements[1][0] * mat.elements[0][2] + elements[1][1] * mat.elements[1][2] + elements[1][2] * mat.elements[2][2] + elements[1][3] * mat.elements[3][2],
			elements[1][0] * mat.elements[0][3] + elements[1][1] * mat.elements[1][3] + elements[1][2] * mat.elements[2][3] + elements[1][3] * mat.elements[3][3]},

			{elements[2][0] * mat.elements[0][0] + elements[2][1] * mat.elements[1][0] + elements[2][2] * mat.elements[2][0] + elements[2][3] * mat.elements[3][0],
			elements[2][0] * mat.elements[0][1] + elements[2][1] * mat.elements[1][1] + elements[2][2] * mat.elements[2][1] + elements[2][3] * mat.elements[3][1],
			elements[2][0] * mat.elements[0][2] + elements[2][1] * mat.elements[1][2] + elements[2][2] * mat.elements[2][2] + elements[2][3] * mat.elements[3][2],
			elements[2][0] * mat.elements[0][3] + elements[2][1] * mat.elements[1][3] + elements[2][2] * mat.elements[2][3] + elements[2][3] * mat.elements[3][3]},

			{elements[3][0] * mat.elements[0][0] + elements[3][1] * mat.elements[1][0] + elements[3][2] * mat.elements[2][0] + elements[3][3] * mat.elements[3][0],
			elements[3][0] * mat.elements[0][1] + elements[3][1] * mat.elements[1][1] + elements[3][2] * mat.elements[2][1] + elements[3][3] * mat.elements[3][1],
			elements[3][0] * mat.elements[0][2] + elements[3][1] * mat.elements[1][2] + elements[3][2] * mat.elements[2][2] + elements[3][3] * mat.elements[3][2],
			elements[3][0] * mat.elements[0][3] + elements[3][1] * mat.elements[1][3] + elements[3][2] * mat.elements[2][3] + elements[3][3] * mat.elements[3][3]}
	};
	return TransformMatrix4D(*result);
}
