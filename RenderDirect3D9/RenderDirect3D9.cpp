#include "RenderDirect3D9.h"

extern "C" __declspec(dllexport) Apollo::RenderSystem* CreateRenderSystem(
	const char* configPath,
	const char* windowTitle)
{
	return new RenderSystem_Direct3D9(configPath, windowTitle);
}