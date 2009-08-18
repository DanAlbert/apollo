#include <RenderSystem.h>
#include <SceneManager.h>
#include <SpriteObject.h>
#include <Viewport.h>

#define PI 3.1415926353

const char szAppTitle[] = "Apollo 2D Rendering Engine";

ATOM				MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

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

	Apollo::RenderSystem* apollo = new Apollo::RenderSystem("apollo.ini");
	Apollo::SceneManager* scene = new Apollo::SceneManager(apollo);

	// Loaded objects cannot be controlled or accessed,
	// objects must have handles other than just pointers
	//if (!scene->LoadState("savedscene.xml"))
	{
		scene->GetViewport()->SetPosition(0.0f, 0.0f);

		Apollo::SpriteObject* spr = scene->CreateSpriteObject("Resources/Sprites/Water.xml");
		Apollo::SpriteObject* child = scene->CreateSpriteObject("Resources/Sprites/Water.xml");
		Apollo::SpriteObject* ship = scene->CreateSpriteObject("Resources/Sprites/Ship.xml");

		child->SetParent(spr);
		child->SetRelativePosition(64.0f, 0.0f);

		ship->SetPosition((apollo->GetWidth() / 2) - (ship->GetWidth() / 2),
			(apollo->GetHeight() / 2) - (ship->GetHeight() / 2));
		ship->Rotate(PI);
	}

	float xMod = 2.0f;
	float yMod = 1.0f;
	float cMod = 1.0f;

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
			/*if ((spr->GetXPosition() > 736) || (spr->GetXPosition() < 0))
			{
				xMod *= -1;
			}

			if ((spr->GetYPosition() > 536) || (spr->GetYPosition() < 0))
			{
				yMod *= -1;
			}

			if ((child->GetRelativeXPosition() < 64) || (child->GetRelativeXPosition() > 128))
			{
				cMod *= -1;
			}

			spr->Move(xMod, yMod);
			child->Move(cMod, 0.0f);*/

			apollo->StartDrawing();
			
			scene->Update();
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