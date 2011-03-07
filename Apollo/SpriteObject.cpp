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

	void SpriteObject::SaveState(TiXmlElement*& parentElement)
	{
		TiXmlElement* elem = new TiXmlElement("SpriteObject");
		parentElement->LinkEndChild(elem);

		elem->SetAttribute("active", m_Active);
		elem->SetAttribute("visible", m_Visible);
		elem->SetDoubleAttribute("x", m_XPosition);
		elem->SetDoubleAttribute("y", m_YPosition);
		elem->SetDoubleAttribute("rotation", m_Rotation);

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
				// I don't rmember if I did this right... If it doesn't work, this is probabaly the issue.
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