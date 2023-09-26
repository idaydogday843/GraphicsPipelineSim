#include <iostream>
#include "DataStructure.h"
#include "WindowsGUI.h"
#include "Algorithms.h"

using namespace std;

bool test_dot_product()
{
	Vector3D test_vector1 = Vector3D(3.0, 5.0, 4.0);
	Vector3D test_vector2 = Vector3D(2.0, 4.0, 1.0);
	if (test_vector1.dot_product(test_vector2) != 30)
	{
		return false;
	}
	if (test_vector2.dot_product(test_vector1) != 30)
	{
		return false;
	}
	if (test_vector1.dot_product(test_vector1) != 50)
	{
		return false;
	}
	if (test_vector2.dot_product(test_vector2) != 21)
	{
		return false;
	}
	return true;
}

bool test_cross_product()
{
	Vector3D test_vector1 = Vector3D(3.0, 5.0, 4.0);
	Vector3D test_vector2 = Vector3D(2.0, 4.0, 1.0);
	Vector3D vec1_cross_vec2 = test_vector1 * test_vector2;
	if (vec1_cross_vec2.x != -11 || vec1_cross_vec2.y != 5 || vec1_cross_vec2.z != 2)
	{
		return false;
	}
	Vector3D vec2_cross_vec1 = test_vector2 * test_vector1;
	if (vec2_cross_vec1.x != 11 || vec2_cross_vec1.y != -5 || vec2_cross_vec1.z != -2)
	{
		return false;
	}
	return true;
}

bool test_transform()
{
	double elements[4][4] = { {4.0, 0.0, 0.0, 2.0}, {0.0, 4.0, 0.0, -4.0}, {0.0, 0.0, 4.0, 1.0}, {0.0, 0.0, 0.0, 1.0} };
	double* first_element = elements[0];
	Vector3D test_vector1 = Vector3D(2.0, 4.0, 1.0);
	TransformMatrix4D test_matrix1 = TransformMatrix4D(first_element);
	Vector3D transformed_vec = test_vector1.transform(test_matrix1);
	if (transformed_vec.x != 10 || transformed_vec.y != 12 || transformed_vec.z != 5)
	{
		return false;
	}
	return true;
}

bool test_matrix_format()
{
	double elements[4][4] = { {4.0, 0.0, 0.0, 2.0}, {0.0, 4.0, 0.0, -4.0}, {0.0, 0.0, 4.0, 1.0}, {0.0, 0.0, 0.0, 1.0} };
	double* first_element = elements[0];
	TransformMatrix4D test_matrix1 = TransformMatrix4D(first_element);
	double* elements1 = test_matrix1.get_matrix_elements();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (elements1[i * 4 + j] != elements[i][j])
			{
				return false;
			}
		}
	}
	delete[] elements1;
	return true;
}

bool test_matrix_constructors()
{
	double elements[4][4] = { {4.0, 0.0, 0.0, 2.0}, {0.0, 4.0, 0.0, -4.0}, {0.0, 0.0, 4.0, 1.0}, {0.0, 0.0, 0.0, 1.0} };
	TransformMatrix4D test_matrix1 = TransformMatrix4D(elements[0]);
	TransformMatrix4D test_matrix2 = TransformMatrix4D(test_matrix1);
	TransformMatrix4D matrix_mult = test_matrix1 * test_matrix2;
	matrix_mult.get_matrix_elements();
	double* elements1 = test_matrix2.get_matrix_elements();
	return true;
}

int main()
{

	WinMain(0, 0, 0, 0);
	/*cout << "Dot Product: " << test_dot_product() << endl;
	cout << "Cross Product: " << test_cross_product() << endl;
	cout << "Transformation: " << test_transform() << endl;
	cout << "Matrix Format: " << test_matrix_format() << endl;
	cout << "Matrix Constructors: " << test_matrix_constructors() << endl;*/
}