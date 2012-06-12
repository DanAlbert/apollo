/**
 * @file main.cpp
 * @author Dan Albert <dan@gingerhq.net>
 * @date Last updated 06/11/2012
 * @version 0.2.53
 *
 * @section LICENSE
 * 
 * Apollo 2D Rendering Engine
 * Copyright (C) 2012 Dan Albert
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * @section DESCRIPTION
 * 
 * Defines the entry point for the sample application.
 * 
 */
#include <Font.h>
#include <RenderSystem.h>
#include <SpriteObject.h>
#include <Viewport.h>

#include "GameManager.h"
#include "PlayerListener.h"

#ifndef PI
#define PI 3.1415926353
#endif // PI

#define NUM_ASTEROIDS 8

const char szAppTitle[] = "Apollo 2D Rendering Engine";

ATOM				MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

// Testing functions
void createScene(GameManager* gameManager);
void generateAsteroidField(GameManager* gameManager, int nAsteroids);

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

	Apollo::RenderSystem* apollo = Apollo::RenderSystem::Create("RenderDirect3D9.dll");
	Apollo::Font* font = new Apollo::Font("Resources/Fonts/ApolloSystem.xml", apollo);
	GameManager* scene = new GameManager(apollo);

	if (!scene->LoadState("savedscene.xml"))
	{
		createScene(scene);
	}
	
	long lastTime = 0;
	long frames = 0;
	char fpsString[32] = "0 FPS";

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
			long cTime = GetTickCount();
			long dTime = cTime - lastTime;
			if (dTime > 100)
			{
				lastTime = cTime;

				int fps = floor(frames / (dTime / 1000.0f));
				
				sprintf(fpsString, "%d FPS", fps);
				frames = 0;
			}

			scene->Update();

			apollo->StartDrawing();
			scene->Draw();

			font->DrawText(
				fpsString,
				apollo->GetWidth() - font->TextWidth(fpsString) - 10.0f,
				10.0f,
				Apollo::Color::White);

			apollo->EndDrawing();
			
			frames++;
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

void createScene(GameManager* gameManager)
{
	gameManager->GetViewport()->SetPosition(0.0f, 0.0f);

	//Apollo::SpriteObject* spr = gameManager->CreateSpriteObject("Resources/Sprites/Water.xml");
	//Apollo::SpriteObject* child = gameManager->CreateSpriteObject("Resources/Sprites/Water.xml");

	Player* ship = gameManager->CreatePlayer("Resources/Players/Player.xml");
	
	generateAsteroidField(gameManager, NUM_ASTEROIDS);

	ship->SetPosition((gameManager->GetViewport()->GetWidth() / 2.0f) - (ship->GetWidth() / 2.0f),
		(gameManager->GetViewport()->GetHeight() / 2.0f) - (ship->GetHeight() / 2.0f));
	ship->Rotate((float)PI);
}

void generateAsteroidField(GameManager* gameManager, int nAsteroids)
{
	for (int i = 0; i < nAsteroids; i++)
	{
		Asteroid* asteroid = gameManager->CreateAsteroid("Resources/Sprites/LargeAsteroid.xml");
		
		asteroid->SetPosition(
			rand() % gameManager->GetViewport()->GetWidth(),
			rand() % gameManager->GetViewport()->GetHeight());
	}
}