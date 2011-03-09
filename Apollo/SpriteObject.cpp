#include "SpriteObject.h"

namespace Apollo
{
	// Private constructor for derived classes
	SpriteObject::SpriteObject(void)
	{
	}

	SpriteObject::SpriteObject(const char* path, RenderSystem* renderSystem)
	{
		loadFromFile(path, renderSystem);
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

	void SpriteObject::SaveState(TiXmlElement*& element, bool elementIsParent)
	{
		TiXmlElement* elem;

		if (elementIsParent)
		{
			elem = new TiXmlElement("SpriteObject");
			element->LinkEndChild(elem);
		}
		else
		{
			elem = element;
		}
		
		TiXmlElement* spriteElem = new TiXmlElement("Sprite");
		elem->LinkEndChild(spriteElem);

		spriteElem->SetAttribute("resource", m_Sprite->GetResourcePath());
		spriteElem->SetAttribute("cFrame", m_Sprite->GetCurrentFrame());
		spriteElem->SetAttribute("animCount", m_Sprite->GetCurrentFrameTime());

		SceneObject::SaveState(elem, false);
	}

	void SpriteObject::LoadState(TiXmlElement* element, SceneObject* parent)
	{
		TiXmlElement* spriteElem = NULL;
		
		int cFrame;
		int animCount;
		
		spriteElem = element->FirstChildElement("Sprite");

		spriteElem->QueryIntAttribute("cFrame", &cFrame);
		spriteElem->QueryIntAttribute("animCount", &animCount);

		spriteElem = element->FirstChildElement("Sprite");

		this->setSpriteState(cFrame, animCount);
		SceneObject::LoadState(element, parent);
	}

	void SpriteObject::Update(long dTime)
	{
		if (m_Active)
		{
		}
	}

	void SpriteObject::Draw(long dTime, SceneObject* view)
	{
		if (m_Visible)
		{
			if (m_Sprite)
			{
				m_Sprite->Draw(
					m_XPosition - view->GetXPosition(),
					m_YPosition - view->GetYPosition(),
					m_Rotation,
					dTime);
			}
		}
	}

	void SpriteObject::loadFromFile(const char* path, RenderSystem* renderSystem)
	{
		this->m_Sprite = new Sprite(path, renderSystem);

		this->m_Width = m_Sprite->GetMaxWidth();
		this->m_Height = m_Sprite->GetMaxHeight();
	}

	void SpriteObject::setSpriteState(int cFrame, int cFrameTime)
	{
		this->m_Sprite->SetCurrentFrame(cFrame);
		this->m_Sprite->SetCurrentFrameTime(cFrameTime);
	}
}