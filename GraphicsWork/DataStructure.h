#ifndef MY_H_FILE
#define MY_H_FILE
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
class TransformMatrix4D					// 变换矩阵的声明
{
public:
	double elements[4][4];				// 变换矩阵的元素
	TransformMatrix4D(double*);			// 变换矩阵构造函数，参数为4*4的二维数组
	TransformMatrix4D();				// 变换矩阵默认构造函数，结果为4*4单位矩阵
	TransformMatrix4D(const TransformMatrix4D&);
	//~TransformMatrix4D();
	double* get_matrix_elements();		// 获取变换矩阵中的元素
	TransformMatrix4D operator*(TransformMatrix4D);		// 矩阵叉乘
	//TransformMatrix4D view_transform(Camera);
	//TransformMatrix4D world_transform(Vector3D);
	//TransformMatrix4D ortho_projection(double, double, double, double, double, double);
	//TransformMatrix4D pers_projection(double, double, double, double);
};

class Vector3D							// 3D向量的声明
{
public:
	double x, y, z;						// 3D向量的x,y,z坐标
	Vector3D(double, double, double);	// 3D向量构造函数，参数为x坐标，y坐标，z坐标
	Vector3D(const Vector3D&);
	Vector3D();							// 3D向量默认构造函数，构造结果为x
	//~Vector3D();
	Vector3D operator+(Vector3D);		// 3D向量加法，获取两个向量的和
	Vector3D operator-(Vector3D);		// 3D向量减法，获取两点间的距离
	double dot_product(Vector3D);		// 3D向量点乘，可用于获取两向量间的夹角
	Vector3D operator*(Vector3D);		// 3D向量叉乘
	Vector3D operator*(double);
	Vector3D operator-();
	Vector3D normalize();
	Vector3D transform(TransformMatrix4D);	// 3D向量与变换矩阵的乘积，结果为变换后的点坐标
};

class Point2D {
public:
	double x, y;
	Vector3D color;
	Point2D();
	Point2D(double, double);
};

class Triangle2D {
public:
	Point2D p[3];
	Triangle2D();
	Triangle2D(Point2D, Point2D, Point2D);
};

class Vertex							// 顶点的声明
{
public:
	Vector3D position;					// 顶点的坐标
	Vector3D color;
	Vector3D normal;
	Point2D pViewport;
	Vector3D* surfaceNormals;
	int cSurface;
	double uv[2];
	Vertex(Vector3D);
	Vertex(double, double, double);
	Vertex();
	Vector3D averageNormal();
	void updateNormal();
	//~Vertex();
};

class Camera							// 摄像机的声明
{
public:
	Vector3D position;					// 摄像机的坐标(位置)
	Vector3D direction;					// 摄像机的拍摄方向
	Vector3D view_up;					// 摄像机的视图方向
	Camera(Vector3D);
	Camera();
	//~Camera();
};

//class Material
//{
//public:
//	double shininess;
//};

class Triangle							// 三角形的声明
{
public:
	Vertex v[3];						// 三角形的三个顶点
	Triangle2D tViewport;				// 三角形在屏幕上的坐标
	Vector3D normal;
	double specular;
	double diffuse;
	double phong;
	Triangle(Vertex&, Vertex&, Vertex&);
	Triangle(const Triangle&);
	void addSurface(Vertex&);
	//~Triangle();
	//void WriteToBuffer(Triangle&, BYTE*, Camera, int, int);
};

class Light
{
public:
	Vector3D color;
	Vector3D direction;
	double nor_ir;						//Normal Irradiance of the directional light source
	double amb_in;						//Ambient Intensity of the light
	//Vector3D ambient;
	//Vector3D diffuse;
	//Vector3D specular;
	Light(Vector3D, Vector3D);
	Light();
	//Light(const Light&);
	//~Light();
	
};

#endif // !LeftHandCoord.h