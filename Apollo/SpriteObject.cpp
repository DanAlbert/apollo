#include "SpriteObject.h"

namespace Apollo
{
	SpriteObject::SpriteObject(const char* szPath, RenderSystem* renderSystem)
	{
		m_Sprite = new Sprite(szPath, renderSystem);
	}

	SpriteObject::~SpriteObject(void)
	{
		Release();
	}

	void SpriteObject::Release(void)
	{
		if (m_Sprite != NULL)
		{
			delete m_Sprite;
			m_Sprite = NULL;
		}
	}

	void SpriteObject::Update(long dTime)
	{
		if (m_Active)
		{
		}
	}

	void SpriteObject::Draw(long dTime)
	{
		if (m_Visible)
		{
			m_Sprite->Draw(m_XPosition, m_YPosition, dTime);
		}
	}
}