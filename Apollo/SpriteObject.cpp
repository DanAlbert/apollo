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

	void SpriteObject::SaveState(TiXmlElement*& parentElement)
	{
		TiXmlElement* elem = new TiXmlElement("SpriteObject");
		parentElement->LinkEndChild(elem);

		elem->SetAttribute("active", m_Active);		// May not cast correctly
		elem->SetAttribute("visible", m_Visible);	// May not cast correctly
		elem->SetDoubleAttribute("x", m_XPosition);
		elem->SetDoubleAttribute("y", m_YPosition);

		TiXmlElement* spriteElem = new TiXmlElement("Sprite");
		elem->LinkEndChild(spriteElem);

		spriteElem->SetAttribute("resource", m_Sprite->GetResourcePath());
		spriteElem->SetAttribute("cFrame", m_Sprite->GetCurrentFrame());
		spriteElem->SetAttribute("animCount", m_Sprite->GetCurrentFrameTime());

		if (m_Children.size() > 0)
		{
			TiXmlElement* childElem = new TiXmlElement("Children");
			elem->LinkEndChild(childElem);

			for (int i = 0; i < m_Children.size(); ++i)
			{
				m_Children[i]->SaveState(childElem);
			}
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