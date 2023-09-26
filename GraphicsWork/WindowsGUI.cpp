//#include "stdafx.h"
#include <windows.h>
#include <string>
#include <WinUser.h>
#include "DataStructure.h"
#include "WindowsGUI.h"
#include <iostream>
#include "Algorithms.h"

using namespace std;

//变量定义  
HWND hwnd;
HDC hdc;

HDC doubleHdc;
HBITMAP bitmap;
BITMAPINFO bitmapInfo;
long RowBytes;
BYTE* ColorData;
int cameraRot = 1;

bool CamLeft = 0;
bool CamRight = 0;
bool CamIn = 0;
bool CamOut = 0;
bool CamUp = 0;
bool CamDown = 0;

bool ModelBlow = 0;
bool Modelshrink = 0;
bool LightRot = 0;

int times = 0;
int times2 = 0;
int timer = 0;
int fps = 0;

int ScreenWidth = 1024;
int ScreenHeight = 768;
string s;
wchar_t timeFPS[10];

Camera cam;
Light l(Vector3D(255.0, 255.0, 255.0), Vector3D(1.0, 1.0, 0.0));
Vertex v1(0.0, 0.0, 0.0);
Vertex v2(8.0, 0.0, 0.0);
Vertex v3(0.0, 8.0, 0.0);
Vertex v4(0.0, 0.0, 8.0);
Triangle m1(v1, v2, v4);
Triangle m2(v1, v3, v2);
Triangle m3(v1, v4, v3);
Triangle m4(v3, v4, v2);

void WriteColor(Vector3D color, double x, double y)
{
	int loc = (int(y) * 1024 + int(x)) * 3;
	ColorData[loc] = color.x;
	ColorData[loc + 1] = color.y;
	ColorData[loc + 2] = color.z;
}

void GetPos(Triangle& t)
{
	cout << "Triangle:" << endl;
	for (int i = 0; i < 3; i++)
	{
		Vertex v = t.v[i];
		TransformMatrix4D view = ViewTransform(cam);
		TransformMatrix4D proj = PerspProj(0.01, 50.0, ScreenWidth / ScreenHeight);
		TransformMatrix4D port = viewport(ScreenWidth, ScreenHeight);
		Vertex viewV(v), projV(v), screenV(v);
		viewV.position = v.position.transform(view);
		projV.position = viewV.position.transform(proj);
		screenV.position = projV.position.transform(port);
		double viewportX = screenV.position.x;
		double viewportY = screenV.position.y;
		cout << "Vertex " << i << ":\nWorld Coordinate : " <<
			v.position.x << ", " << v.position.y << ", " << v.position.z <<
			"\nCamera Coordinate: " << viewV.position.x << ", " << viewV.position.y << ", " << viewV.position.z <<
			"\nProjected Coordnate: " << projV.position.x << ", " << projV.position.y << ", " << projV.position.z <<
			"\nScreen Coordinate: " << viewportX << ", " << viewportY << endl;
	}
	cout << endl;
}

void WriteToBuffer(Triangle& t)//, BYTE* ColorData, Camera cam, int width, int height)
{
	int x0 = 1024, y0 = 768, x1 = 0, y1 = 0;
	for (int i = 0; i < 3; i++)
	{
		Vector3D lightC = DirectionalLight(l, cam, t.v[i].position, t.normal, t.diffuse, t.specular);
		Vector3D colorNew = t.v[i].color * lightC;
		//t.v[i].color = t.v[i].color * lightC;
		TransformMatrix4D view = ViewTransform(cam);
		TransformMatrix4D proj = PerspProj(0.01, 50.0, ScreenWidth / ScreenHeight);
		TransformMatrix4D port = viewport(ScreenWidth, ScreenHeight);
		Vertex viewV(t.v[i]), projV(t.v[i]), screenV(t.v[i]);
		viewV.position = t.v[i].position.transform(view);
		projV.position = viewV.position.transform(proj);
		screenV.position = projV.position.transform(port);
		t.v[i].pViewport = Point2D(screenV.position.x, screenV.position.y);
		t.v[i].pViewport.color = t.v[i].color;
		Vertex v = t.v[i];
		if (v.pViewport.x >= 0 && v.pViewport.y >= 0)
		{
			if (x0 > v.pViewport.x)
			{
				x0 = v.pViewport.x;
			}
			if (y0 > v.pViewport.y)
			{
				y0 = v.pViewport.y;
			}
			if (x1 < v.pViewport.x)
			{
				x1 = v.pViewport.x;
			}
			if (y1 < v.pViewport.y)
			{
				y1 = v.pViewport.y;
			}
			//WriteColor(v.color, v.pViewport.x, v.pViewport.y);
			WriteColor(colorNew, v.pViewport.x, v.pViewport.y);
		}
	}
	Triangle2D tri2D(t.v[0].pViewport, t.v[1].pViewport, t.v[2].pViewport);
	t.tViewport = tri2D;
	DDALine(t);
	for (int i = x0; i < x1; i++)
	{
		for (int j = y0; j < y1; j++)
		{
			Inside(t, Point2D((double)i + 0.5, (double)j + 0.5));
		}
	}
}

//主函数  
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	//设计窗口类  
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)GetStockObject(WHITE_BRUSH),
		NULL,
		TEXT("MY DEMO")
	};
	//注册窗口类  
	RegisterClass(&wndclass);
	//创建窗口类  
	hwnd = CreateWindow(
		TEXT("MY DEMO"),
		TEXT("My Demo"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		ScreenWidth,
		ScreenHeight,
		NULL,
		NULL,
		hInstance,
		NULL);
	//显示窗口  
	ShowWindow(hwnd, SW_SHOW);
	//更新窗口  
	UpdateWindow(hwnd);

	//初始化  
	init();

	//消息循环  
	MSG Msg;
	BOOL bRet;
	PeekMessage(&Msg, NULL, 0, 0, PM_NOREMOVE);
	while (Msg.message != WM_QUIT)
	{
		bRet = PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE);
		if (bRet)
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		times2 = GetTickCount();
		if (times2 != times)fps = 1000 / (times2 - times);
		Render();
		times = times2;
	}
	CleanUp();

	return Msg.wParam;
}


//窗口过程处理函数  
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rc;
	GetClientRect(hwnd, &rc);
	PAINTSTRUCT ps;
	//wchar_t name[] = L"软渲染管线";
	//wchar_t Notice[] = L"按一次开始，再按一次停止。";
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SetTextColor(hdc, RGB(255, 0, 0));
		SetBkMode(hdc, TRANSPARENT);
		//TextOut(hdc, ScreenWidth + 20, 0, name, lstrlen(name));
		//TextOut(hdc, ScreenWidth + 20, 25, Notice, lstrlen(Notice));
		SetTextColor(hdc, RGB(0, 0, 0));
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			cam.position.x -= 1;
			cout << cam.position.x << "," << cam.position.y << "," << cam.position.z << endl;
			break;
		case VK_RIGHT:
			cam.position.x += 1;
			cout << cam.position.x << "," << cam.position.y << "," << cam.position.z << endl;
			break;
		case VK_UP:
			cam.position.y += 1;
			cout << cam.position.x << "," << cam.position.y << "," << cam.position.z << endl;
			break;
		case VK_DOWN:
			cam.position.y -= 1;
			cout << cam.position.x << "," << cam.position.y << "," << cam.position.z << endl;
			break;
		case VK_NUMPAD5:
			cam.position.z += 1;
			cout << cam.position.x << "," << cam.position.y << "," << cam.position.z << endl;
			break;
		case VK_NUMPAD0:
			cam.position.z -= 1;
			cout << cam.position.x << "," << cam.position.y << "," << cam.position.z << endl;
			break;
		case VK_PRIOR:
			CamDown = 0;
			CamUp = !CamUp;
			break;
		case VK_NEXT:
			CamUp = 0;
			CamDown = !CamDown;
			break;
			//模型旋转
		case VK_F4:
			//Mesh::WorldY = (Mesh::WorldY + 1) % 2;
			break;
		case VK_F5:
			//Mesh::WorldX = (Mesh::WorldX + 1) % 2;
			break;
		case VK_F6:
			//Mesh::WorldZ = (Mesh::WorldZ + 1) % 2;
			break;
		case VK_F7:
			Modelshrink = 0;
			ModelBlow = !ModelBlow;
			break;
		case VK_F9:
			ModelBlow = 0;
			Modelshrink = !Modelshrink;
			break;
		case VK_SPACE:
			LightRot = !LightRot;
			break;
		case VK_ESCAPE:
			CleanUp();
			break;
		case VK_NUMPAD1:
			GetPos(m1);
			break;
		case VK_NUMPAD2:
			GetPos(m2);
			break;
		case VK_NUMPAD3:
			GetPos(m3);
			break;
		case VK_NUMPAD4:
			GetPos(m4);
			break;
		default:
			break;
		}
		break;
	case WM_TIMER:
		//变换判断
		timer++;
		Rotation(m1, 0.0, M_PI / 120, 0.0);
		Rotation(m2, 0.0, M_PI / 120, 0.0);
		Rotation(m3, 0.0, M_PI / 120, 0.0);
		Rotation(m4, 0.0, M_PI / 120, 0.0);
		//在time里输出会叠加像素
		if (timer % 5 == 0)
		{
			s = to_string(fps) + "fps  ";
			swprintf(timeFPS, 10, L"%hs", s.c_str());
			SetTextColor(doubleHdc, RGB(0, 0, 0));
			TextOut(hdc, ScreenWidth + 20, 160, timeFPS, s.length());
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}
//初始化函数  
void init()
{
	if (!hwnd)
	{
		return;
	}
	setScreen(ScreenWidth, ScreenHeight);
	cam.position = Vector3D(0.0, 6.0, 20.0);
	//cam.position = Vector3D(3.0, -1.0, 12.0);
	//cam.direction = Vector3D(0.0, 0.0, 1.0);
	m1.v[0].color = Vector3D(255.0, 0.0, 0.0);//1
	m1.v[1].color = Vector3D(255.0, 0.0, 255.0);//2
	m1.v[2].color = Vector3D(255.0, 255.0, 0.0);//4
	m2.v[0].color = Vector3D(255.0, 0.0, 0.0);//1
	m2.v[1].color = Vector3D(0.0, 255.0, 255.0);//3
	m2.v[2].color = Vector3D(255.0, 0.0, 255.0);//2
	m3.v[0].color = Vector3D(255.0, 0.0, 0.0);//1
	m3.v[1].color = Vector3D(255.0, 255.0, 0.0);//4
	m3.v[2].color = Vector3D(0.0, 255.0, 255.0);//3
	m4.v[0].color = Vector3D(0.0, 255.0, 255.0);//3
	m4.v[1].color = Vector3D(255.0, 255.0, 0.0);//4
	m4.v[2].color = Vector3D(255.0, 0.0, 255.0);//2
	//设备环境获取  
	hdc = GetDC(hwnd);
	//获取当前窗口大小  
	doubleHdc = CreateCompatibleDC(hdc);	//缓存dc
	bitmap = CreateCompatibleBitmap(hdc, ScreenWidth, ScreenHeight);	//兼容位图
	SelectObject(doubleHdc, bitmap);

	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biWidth = ScreenWidth;
	bitmapInfo.bmiHeader.biHeight = ScreenHeight;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biBitCount = 24;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	bitmapInfo.bmiHeader.biSizeImage = ScreenWidth * ScreenHeight;
	bitmapInfo.bmiHeader.biXPelsPerMeter = 3000;
	bitmapInfo.bmiHeader.biYPelsPerMeter = 3000;
	bitmapInfo.bmiHeader.biClrUsed = 0;	//16位图
	bitmapInfo.bmiHeader.biClrImportant = 0;	//所有颜色都重要
	RowBytes = (bitmapInfo.bmiHeader.biWidth * 3 + 3) / 4 * 4;	//保证是4的倍数
	ColorData = new BYTE[RowBytes * ScreenHeight];	//颜色缓存，直接在这上面进行存储
	SetTimer(hwnd, 1, 25, NULL);	//每秒40次变换
}
//渲染  
void Render()
{
	if (hdc && doubleHdc)
	{
		memset(ColorData, 0, RowBytes * ScreenHeight);	//清除颜色缓存
		//变换和存储操作，将colorData的引用传入
		setCam(cam);
		setLight(l);
		WriteToBuffer(m1);
		WriteToBuffer(m2);
		WriteToBuffer(m3);
		WriteToBuffer(m4);

		SetDIBits(hdc, bitmap, 0, ScreenHeight, ColorData, &bitmapInfo, DIB_RGB_COLORS);	//将ColorData传递给bitmap
		BitBlt(hdc, 0, 0, ScreenWidth, ScreenHeight, doubleHdc, 0, 0, SRCCOPY);
	}
}
//清除设备环境  
void CleanUp()
{
	delete[] ColorData;
	KillTimer(hwnd, 1);
	DeleteDC(doubleHdc);
	ReleaseDC(hwnd, hdc);
}