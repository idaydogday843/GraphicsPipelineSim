#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "DataStructure.h"
#include "Algorithms.h"
#include "WindowsGUI.h"

Light::Light(Vector3D color, Vector3D direction)
{
	Light::color = color;
	Light::direction = direction;
	Light::nor_ir = 1.0;
	Light::amb_in = 0.6;
}

Light::Light()
{
	Light::color = Vector3D(255.0, 255.0, 255.0);
	Light::direction = Vector3D(0.0, 1.0, 0.0);
	Light::nor_ir = 1.0;
	Light::amb_in = 0.6;
}