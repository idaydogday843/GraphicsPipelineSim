#pragma once

#include <windows.h>
#include <string>
#include <WinUser.h>
#include "DataStructure.h"


//��������  
void WriteColor(Vector3D color, double x, double y);
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);//���ڴ�����  
void init();//��ʼ���豸����  
void Render();//��Ⱦ����  
void CleanUp();//�ͷ��豸����  