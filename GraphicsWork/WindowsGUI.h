#pragma once

#include <windows.h>
#include <string>
#include <WinUser.h>
#include "DataStructure.h"


//函数声明  
void WriteColor(Vector3D color, double x, double y);
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);//窗口处理函数  
void init();//初始化设备环境  
void Render();//渲染函数  
void CleanUp();//释放设备环境  