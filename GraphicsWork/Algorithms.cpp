#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "DataStructure.h"
#include "WindowsGUI.h"
#include "Algorithms.h"
using namespace std;

double width;
double height;
Camera myCam;
Light myLight;


void setScreen(double w, double h)
{
	width = w;
	height = h;
}

void setLight(Light l)
{
	myLight = l;
}

void setCam(Camera cam)
{
	myCam = cam;
}

void Rotation(Triangle& tr, double x, double y, double z)
{
	TransformMatrix4D trans = ModelTransform(2, x, y, z);
	for (int i = 0; i < 3; i++)
	{
		tr.v[i].position = tr.v[i].position.transform(trans);
	}
}

void Scale(Triangle& tr, double x, double y, double z)
{
	TransformMatrix4D trans = ModelTransform(1, x, y, z);
	for (int i = 0; i < 3; i++)
	{
		tr.v[i].position = tr.v[i].position.transform(trans);
	}
}

void Translation(Triangle& tr, double x, double y, double z)
{
	TransformMatrix4D trans = ModelTransform(0, x, y, z);
	for (int i = 0; i < 3; i++)
	{
		tr.v[i].position = tr.v[i].position.transform(trans);
	}
}

TransformMatrix4D ModelTransform(int type, double x, double y, double z)
{
	TransformMatrix4D model = TransformMatrix4D();
	if (type == 0)
	{
		model.elements[0][3] = x;
		model.elements[1][3] = y;
		model.elements[2][3] = z;
	}
	if (type == 1)
	{
		model.elements[0][0] = x;
		model.elements[1][1] = y;
		model.elements[2][2] = z;
	}
	if (type == 2)
	{
		double eleX[4][4] = {
			{1.0, 0.0, 0.0, 0.0},
			{0.0, cos(x), -sin(x), 0.0},
			{0.0, sin(x), cos(x), 0.0},
			{0.0, 0.0, 0.0, 1.0}
		};
		double eleY[4][4] = {
			{cos(y), 0.0, sin(y), 0.0},
			{0.0, 1.0, 0.0, 0.0},
			{-sin(y), 0.0, cos(y), 0.0},
			{0.0, 0.0, 0.0, 1.0}
		};
		double eleZ[4][4] = {
			{cos(z), -sin(z), 0.0, 0.0},
			{sin(z), cos(z), 0.0, 0.0},
			{0.0, 0.0, 1.0, 0.0},
			{0.0, 0.0, 0.0, 1.0}
		};
		TransformMatrix4D rotX = TransformMatrix4D(eleX[0]);
		TransformMatrix4D rotY = TransformMatrix4D(eleY[0]);
		TransformMatrix4D rotZ = TransformMatrix4D(eleZ[0]);
		model = rotX * rotY * rotZ;
	}
	return model;
}

TransformMatrix4D ViewTransform(Camera cam)
{
	double view_translate[4][4] = {
		{1.0, 0.0, 0.0, -cam.position.x},
		{0.0, 1.0, 0.0, -cam.position.y},
		{0.0, 0.0, 1.0, -cam.position.z},
		{0.0, 0.0, 0.0, 1.0}
	};
	double view_rotate[4][4] = {
		{(cam.direction * cam.view_up).x, (cam.direction * cam.view_up).y, (cam.direction * cam.view_up).z, 0.0},
		{cam.view_up.x, -cam.view_up.y, cam.view_up.z, 0.0},
		{cam.direction.x, cam.direction.y, -cam.direction.z, 0.0},
		{0.0, 0.0, 0.0, 1.0}
	};
	TransformMatrix4D result = TransformMatrix4D(*view_rotate) * TransformMatrix4D(*view_translate);
	//result.get_matrix_elements();
	return result;
}

TransformMatrix4D OrthoProj(double left, double right, double bottom, double top, double _near, double _far)//(double left = -1.0, double right = 1.0, double bottom = -1.0, double top = 1.0, double _near = -1.0, double _far = 1.0)
{
	double ortho_scale[4][4] = {
		{2.0 / (right - left), 0.0, 0.0, 0.0},
		{0.0, 2.0 / (top - bottom), 0.0, 0.0},
		{0.0, 0.0, 2.0 / (_far - _near), 0.0},
		{0.0, 0.0, 0.0, 1.0}
	};
	double ortho_translate[4][4] = {
		{1.0, 0.0, 0.0, (right + left) / -2.0},
		{0.0, 1.0, 0.0, (top + bottom) / -2.0},
		{0.0, 0.0, 1.0, (_far + _near) / -2.0},
		{0.0, 0.0, 0.0, 1.0}
	};
	TransformMatrix4D result = TransformMatrix4D(*ortho_scale) * TransformMatrix4D(*ortho_translate);
	//result.get_matrix_elements();
	return result;
}

TransformMatrix4D PerspProj(double _near, double _far, double aspect, double fov)
{
	double pers_ortho[4][4] = {
			{_near, 0.0, 0.0, 0.0},
			{0.0, _near, 0.0, 0.0},
			{0.0, 0.0, _near + _far, _near * _far},
			{0.0, 0.0, 1.0, 0.0}
	};
	TransformMatrix4D result = OrthoProj(-tan(fov * 0.5) * aspect * _near,
		tan(fov * 0.5) * aspect * _near,
		-tan(fov * 0.5) * _near,
		tan(fov * 0.5) * _near, _near, _far) * TransformMatrix4D(*pers_ortho);
	//result.get_matrix_elements();
	return result;
}

TransformMatrix4D viewport(double width, double height)
{
	double viewport[4][4] = {
		{width / 2, 0.0, 0.0, width / 2},
		{0.0, height / 2, 0.0, height / 2},
		{0.0, 0.0, 1.0, 0.0},
		{0.0, 0.0, 0.0, 1.0}
	};
	return TransformMatrix4D(*viewport);
}

void DDALine(Triangle& tr)//(int x0, int y0, int x1, int y1)
{
	Triangle2D t = tr.tViewport;
	for (int i = 0; i < 3; i++)
	{
		Point2D p1, p2;
		Vertex v1, v2;
		if (i != 2)
		{
			v1 = tr.v[i];
			v2 = tr.v[i + 1];
		}
		else
		{
			v1 = tr.v[i];
			v2 = tr.v[0];
		}
		p1 = v1.pViewport;
		p2 = v2.pViewport;
		Point2D *points = Clipping(p1, p2);
		int x0 = int(p1.x), y0 = int(p1.y), x1 = int(p2.x), y1 = int(p2.y);
		bool greater = (x1 >= x0);
		double dx, dy, x, y;
		if (x1 >= x0)
		{
			dx = x1 - x0;
			dy = y1 - y0;
			x = x0;
			y = y0;
		}
		else
		{
			dx = x0 - x1;
			x = x1;
			dy = y0 - y1;
			y = y1;
		}
		Point2D p(x, y);
		if (dx >= dy)
		{
			double slope = dy / dx;
			for (int i = 0; i < dx; i++)
			{
				Vector3D pp = (v2.position - v1.position) * (i / dx) + v1.position;
				Vector3D pc = (v2.normal - v1.normal) * (i / dx) + v1.normal;
				Vector3D mc = DirectionalLight(myLight, myCam, pp, pc, tr.diffuse, tr.specular);
				Vector3D b;
				if (greater)
				{
					b = p2.color * (i / dx) + p1.color * (1 - i / dx);
				}
				else
				{
					b = p1.color * (i / dx) + p2.color * (1 - i / dx);
				}
				p.color = Vector3D(b.x * mc.x, b.y * mc.y, b.z * mc.z);
				WriteColor(p.color, x, y);
				x++;
				y += slope;
			}
		}
		else
		{
			double slope = dx / dy;
			for (int i = 0; i < dy; i++)
			{
				Vector3D pp = (v2.position - v1.position) * (i / dy) + v1.position;
				Vector3D mc = DirectionalLight(myLight, myCam, pp, tr.normal, tr.diffuse, tr.specular);
				Vector3D b;
				if (greater)
				{
					b = p2.color * (i / dy) + p1.color * (1 - i / dy);
				}
				else
				{
					b = p1.color * (i / dy) + p2.color * (1 - i / dy);
				}
				p.color = Vector3D(b.x * mc.x, b.y * mc.y, b.z * mc.z);
				WriteColor(p.color, x, y);
				y++;
				x += slope;
			}
		}
	}
}

Vector3D DirectionalLight(Light l, Camera c, Vector3D position, Vector3D normal, double cDiffuse, double cSpecular)
{
	Vector3D diffuse = DiffuseLight(l, normal, cDiffuse);
	Vector3D specular = SpecularLight(l, c, position, normal, cSpecular);
	Vector3D ambient = AmbientLight(l);
	Vector3D color = diffuse + specular + ambient;
	if (color.x > 1.0)
	{
		color.x = 1.0;
	}
	if (color.y > 1.0)
	{
		color.y = 1.0;
	}
	if (color.z > 1.0)
	{
		color.z = 1.0;
	}
	return color;
}

Vector3D AmbientLight(Light l)
{
	return l.color * l.amb_in * (1.0 / 256.0);
}

Vector3D DiffuseLight(Light l, Vector3D normal, double diffuse)
{
	//cout << (t.diffuse * l.nor_ir * max(t.normal.dot_product(-l.direction.normalize()), 0.0)) << endl;
	Vector3D dNormal = -l.direction.normalize();
	double in = normal.dot_product(dNormal);
	double x = diffuse * l.nor_ir * in;
	return l.color * (x / 256.0);
	//return l.color * (t.diffuse * l.nor_ir * max(t.normal.dot_product(-l.direction.normalize()), 0.0)) * (1.0 / 255.0);
}

Vector3D SpecularLight(Light l, Camera c, Vector3D position, Vector3D normal, double specular)
{
	Vector3D h = (-l.direction + (position - c.direction)).normalize();
	return l.color * (specular * l.nor_ir * pow(max(0, normal.dot_product(h)), 2)) * (1.0 / 256.0);
}

void Inside(Triangle& tr, Point2D p)
{
	Triangle2D t = tr.tViewport;
	Vector3D v1(t.p[0].x - t.p[2].x, t.p[0].y - t.p[2].y, 1.0);
	Vector3D v2(t.p[1].x - t.p[0].x, t.p[1].y - t.p[0].y, 1.0);
	Vector3D v3(t.p[2].x - t.p[1].x, t.p[2].y - t.p[1].y, 1.0);
	Vector3D v4(p.x - t.p[2].x, p.y - t.p[2].y, 1.0);
	Vector3D v5(p.x - t.p[0].x, p.y - t.p[0].y, 1.0);
	Vector3D v6(p.x - t.p[1].x, p.y - t.p[1].y, 1.0);
	double d1 = (v1 * v4).z, d2 = (v2 * v5).z, d3 = (v3 * v6).z;
	if (d1 < 0 && d2 < 0 && d3 < 0)
	{
		Vector3D barycentric = Barycentric(t, p);
		Vector3D b = t.p[0].color * barycentric.x + t.p[1].color * barycentric.y + t.p[2].color * barycentric.z;
		Vector3D vPosition = Vector3D(tr.v[0].position * barycentric.x + tr.v[1].position * barycentric.y + tr.v[2].position * barycentric.z);
		Vector3D vNormal = Vector3D(tr.v[0].normal * barycentric.x + tr.v[1].normal * barycentric.y + tr.v[2].normal * barycentric.z);
		Vector3D mc = DirectionalLight(myLight, myCam, vPosition, vNormal, tr.diffuse, tr.specular);
		p.color = Vector3D(b.x * mc.x, b.y * mc.y, b.z * mc.z);
		//p.color = t.p[0].color * barycentric.x + t.p[1].color * barycentric.y + t.p[2].color * barycentric.z;
		WriteColor(p.color, p.x, p.y);
	}
	if (d1 > 0 && d2 > 0 && d3 > 0)
	{
		Vector3D barycentric = Barycentric(t, p);
		Vector3D b = t.p[0].color * barycentric.x + t.p[1].color * barycentric.y + t.p[2].color * barycentric.z;
		Vector3D vPosition = Vector3D(tr.v[0].position * barycentric.x + tr.v[1].position * barycentric.y + tr.v[2].position * barycentric.z);
		Vector3D vNormal = Vector3D(tr.v[0].normal * barycentric.x + tr.v[1].normal * barycentric.y + tr.v[2].normal * barycentric.z);
		Vector3D mc = DirectionalLight(myLight, myCam, vPosition, tr.normal, tr.diffuse, tr.specular);
		//Vector3D mc = DirectionalLight(myLight, myCam, vPosition, tr.normal, tr.diffuse, tr.specular);
		//p.color = t.p[0].color * barycentric.x + t.p[1].color * barycentric.y + t.p[2].color * barycentric.z;
		p.color = Vector3D(b.x * mc.x, b.y * mc.y, b.z * mc.z);
		WriteColor(p.color, p.x, p.y);
	}
}

Vector3D Barycentric(Triangle2D& t, Point2D p)
{
	double u, v, w;
	Vector3D v1 = Vector3D(t.p[1].x - t.p[0].x, t.p[1].y - t.p[0].y, 1.0);
	Vector3D v2 = Vector3D(t.p[2].x - t.p[0].x, t.p[2].y - t.p[0].y, 1.0);
	Vector3D v3 = Vector3D(p.x - t.p[0].x, p.y - t.p[0].y, 1.0);
	double dot11 = v1.dot_product(v1);
	double dot12 = v1.dot_product(v2);
	double dot22 = v2.dot_product(v2);
	double dot31 = v3.dot_product(v1);
	double dot32 = v3.dot_product(v2);
	v = (dot22 * dot31 - dot12 * dot32) / (dot11 * dot22 - dot12 * dot12);
	w = (dot11 * dot32 - dot12 * dot31) / (dot11 * dot22 - dot12 * dot12);
	u = 1.0 - v - w;
	return Vector3D(u, v, w);
}

Point2D* Clipping(Point2D p1, Point2D p2)
{
	Point2D pair[2];
	bool d10 = p1.x < 0, d11 = p1.x > width, d12 = p1.y < 0, d13 = p1.y > height,
		d20 = p2.x < 0, d21 = p2.x > width, d22 = p2.y < 0, d23 = p2.y > height;
	if ((d10 && d20) || (d11 && d21) || (d12 && d22) || (d13 && d23))
	{
		pair[0] = Point2D(-1.0, -1.0);
		pair[1] = Point2D(-1.0, -1.0);
	}

	if (!(d10 || d20) && !(d11 || d21) && !(d12 || d22) && !(d13 || d23))
	{
		pair[0] = p1;
		pair[1] = p2;
	}

	else
	{
		double dx = p2.x - p1.x, dy = p2.y - p1.y;
		double slope;
		if (dy != 0)
		{
			slope = dy / dx;
		}
		else if (dy == 0)
		{
			slope = 0;
		}
		if (!(d10 || d11 || d12 || d13))
		{
			pair[0] = p1;
			if (d20)
			{
				Point2D pp1(0, p1.y + (0 - p1.x) * slope);
				Point2D pp2;
				if (d22)
				{
					pp2 = Point2D(p1.x + (0 - p1.y) / slope, 0);
				}
				else if (d23)
				{
					pp2 = Point2D(p1.x + (height - p1.y) / slope, height);
				}
				if (pp2.x <= 0.0)
				{
					pair[1] = pp1;
				}
				else
				{
					pair[1] = pp2;
				}
			}
			if (d21)
			{
				Point2D pp1(width, p1.y + (0 - p1.x) * slope);
				Point2D pp2;
				if (d22)
				{
					pp2 = Point2D(p1.x + (0 - p1.y) / slope, 0);
				}
				else if (d23)
				{
					pp2 = Point2D(p1.x + (height - p1.y) / slope, height);
				}
				if (pp2.x >= width)
				{
					pair[1] = pp1;
				}
				else
				{
					pair[1] = pp2;
				}
			}
		}
		if (!(d20 || d21 || d22 || d23))
		{
			pair[0] = p2;
			if (d10)
			{
				Point2D pp1(0, p2.y + (0 - p2.x) * slope);
				Point2D pp2;
				if (d12)
				{
					pp2 = Point2D(p2.x + (0 - p2.y) / slope, 0);
				}
				else if (d13)
				{
					pp2 = Point2D(p2.x + (height - p2.y) / slope, height);
				}
				if (pp2.x <= 0.0)
				{
					pair[1] = pp1;
				}
				else
				{
					pair[1] = pp2;
				}
			}
			if (d11)
			{
				Point2D pp1(width, p2.y + (0 - p2.x) * slope);
				Point2D pp2;
				if (d12)
				{
					pp2 = Point2D(p2.x + (0 - p2.y) / slope, 0);
				}
				else if (d13)
				{
					pp2 = Point2D(p2.x + (height - p2.y) / slope, height);
				}
				if (pp2.x >= width)
				{
					pair[1] = pp1;
				}
				else
				{
					pair[1] = pp2;
				}
			}
		}
	}
	return pair;

}
