#include <RenderSystem.h>
#include <SpriteObject.h>
#include <Viewport.h>

#include "GameManager.h"
#include "PlayerListener.h"

const char szAppTitle[] = "Apollo 2D Rendering Engine";

ATOM				MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

// Testing functions
void createScene(Apollo::RenderSystem* renderSystem, GameManager* gameManager);

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
	Apollo::RenderSystem* apollo = Apollo::RenderSystem::Create("RenderDirect3D9.dll");

	GameManager* scene = new GameManager(apollo);

	if (!scene->LoadState("savedscene.xml"))
	{
		createScene(apollo, scene);
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

void createScene(Apollo::RenderSystem* renderSystem, GameManager* gameManager)
{
	gameManager->GetViewport()->SetPosition(0.0f, 0.0f);

	Apollo::SpriteObject* spr = gameManager->CreateSpriteObject("Resources/Sprites/Water.xml");
	Apollo::SpriteObject* child = gameManager->CreateSpriteObject("Resources/Sprites/Water.xml");

	Player* ship = gameManager->CreatePlayer("Resources/Players/Player.xml");

	child->SetParent(spr);
	child->SetRelativePosition(64.0f, 0.0f);

	ship->SetPosition((renderSystem->GetWidth() / 2.0f) - (ship->GetWidth() / 2.0f),
		(renderSystem->GetHeight() / 2.0f) - (ship->GetHeight() / 2.0f));
	ship->Rotate((float)PI);
}