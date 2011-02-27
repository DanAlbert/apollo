#include <RenderSystem.h>
#include <SpriteObject.h>
#include <Viewport.h>

#include "GameManager.h"
#include "PlayerListener.h"

const char szAppTitle[] = "Apollo 2D Rendering Engine";

ATOM				MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

typedef Apollo::RenderSystem *(*CreateRenderSystem)(
	const char* configPath,
	const char* windowTitle);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(hPrevInstance);

	MSG msg;

#ifdef _DEBUG
	AllocConsole();
	freopen("conin$", "r", stdin); 
	freopen("conout$", "w", stdout); 
	freopen("conout$", "w", stderr);
#endif

	MyRegisterClass(hInstance);

	//Apollo::RenderSystem* apollo = new Apollo::RenderSystem("apollo.ini");
	Apollo::RenderSystem* apollo;

	HINSTANCE RenderDirect3D9 = LoadLibrary("RenderDirect3D9.dll");
	if (RenderDirect3D9)
	{
		Log("Loaded RenderDirect3D9.dll.");
		CreateRenderSystem ctor= (CreateRenderSystem)GetProcAddress(RenderDirect3D9, "CreateRenderSystem");
		if (!ctor)
		{
			FreeLibrary(RenderDirect3D9);
			ErrorQuit("Failed to load CreateRenderSystem() from RenderDirect3D9.dll.");
		}
		
		apollo = ctor("apollo.ini", "Apollo 2D Rendering Engine");
	}

	GameManager* scene = new GameManager(apollo);

	if (!scene->LoadState("savedscene.xml"))
	{
		scene->GetViewport()->SetPosition(0.0f, 0.0f);

		Apollo::SpriteObject* spr = scene->CreateSpriteObject("Resources/Sprites/Water.xml");
		Apollo::SpriteObject* child = scene->CreateSpriteObject("Resources/Sprites/Water.xml");

		Player* ship = scene->CreatePlayer("Resources/Players/Player.xml");

		child->SetParent(spr);
		child->SetRelativePosition(64.0f, 0.0f);

		ship->SetPosition((apollo->GetWidth() / 2) - (ship->GetWidth() / 2),
			(apollo->GetHeight() / 2) - (ship->GetHeight() / 2));
		ship->Rotate(PI);
	}
	
	long lastTime = 0;

	// Main message loop
	bool done = false;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = true;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			scene->Update();

			apollo->StartDrawing();
			scene->Draw();
			apollo->EndDrawing();
		}

		done = GetAsyncKeyState(VK_ESCAPE) & 0x8000 ? true : false;
	}

	scene->SaveState("savedscene.xml");

	delete scene;
	delete apollo;
	
	FreeLibrary(RenderDirect3D9);
	
	UnregisterClass(szAppTitle, hInstance);

#ifdef _DEBUG
	FreeConsole();
#endif

	return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szAppTitle;
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}