#ifndef MY_H_FILE
#define MY_H_FILE
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
class TransformMatrix4D					// �任���������
{
public:
	double elements[4][4];				// �任�����Ԫ��
	TransformMatrix4D(double*);			// �任�����캯��������Ϊ4*4�Ķ�ά����
	TransformMatrix4D();				// �任����Ĭ�Ϲ��캯�������Ϊ4*4��λ����
	TransformMatrix4D(const TransformMatrix4D&);
	//~TransformMatrix4D();
	double* get_matrix_elements();		// ��ȡ�任�����е�Ԫ��
	TransformMatrix4D operator*(TransformMatrix4D);		// ������
	//TransformMatrix4D view_transform(Camera);
	//TransformMatrix4D world_transform(Vector3D);
	//TransformMatrix4D ortho_projection(double, double, double, double, double, double);
	//TransformMatrix4D pers_projection(double, double, double, double);
};

class Vector3D							// 3D����������
{
public:
	double x, y, z;						// 3D������x,y,z����
	Vector3D(double, double, double);	// 3D�������캯��������Ϊx���꣬y���꣬z����
	Vector3D(const Vector3D&);
	Vector3D();							// 3D����Ĭ�Ϲ��캯����������Ϊx
	//~Vector3D();
	Vector3D operator+(Vector3D);		// 3D�����ӷ�����ȡ���������ĺ�
	Vector3D operator-(Vector3D);		// 3D������������ȡ�����ľ���
	double dot_product(Vector3D);		// 3D������ˣ������ڻ�ȡ��������ļн�
	Vector3D operator*(Vector3D);		// 3D�������
	Vector3D operator*(double);
	Vector3D operator-();
	Vector3D normalize();
	Vector3D transform(TransformMatrix4D);	// 3D������任����ĳ˻������Ϊ�任��ĵ�����
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

class Vertex							// ���������
{
public:
	Vector3D position;					// ���������
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

class Camera							// �����������
{
public:
	Vector3D position;					// �����������(λ��)
	Vector3D direction;					// ����������㷽��
	Vector3D view_up;					// ���������ͼ����
	Camera(Vector3D);
	Camera();
	//~Camera();
};

//class Material
//{
//public:
//	double shininess;
//};

class Triangle							// �����ε�����
{
public:
	Vertex v[3];						// �����ε���������
	Triangle2D tViewport;				// ����������Ļ�ϵ�����
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