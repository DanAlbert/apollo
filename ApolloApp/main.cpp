#include <RenderSystem.h>
#include <Sprite.h>

const char szAppTitle[] = "Apollo 2D Rendering Engine";

ATOM				MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(hPrevInstance);

	MSG msg;

	long cTime = GetTickCount();
	long lastTime = cTime;
	int index = 0;

#ifdef _DEBUG
	AllocConsole();
	freopen("conin$", "r", stdin); 
	freopen("conout$", "w", stdout); 
	freopen("conout$", "w", stderr);
#endif

	MyRegisterClass(hInstance);

	Apollo::RenderSystem* apollo = new Apollo::RenderSystem();
	Apollo::Sprite* spr = new Apollo::Sprite("Resources/Sprites/Water.xml", apollo);

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
			cTime = GetTickCount();

			long dTime = cTime - lastTime;
			lastTime = cTime;

			apollo->StartDrawing();
			spr->Draw(0.0f, 0.0f, dTime);
			apollo->EndDrawing();
		}

		done = GetAsyncKeyState(VK_ESCAPE) & 0x8000 ? true : false;
	}

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