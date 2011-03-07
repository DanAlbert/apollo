#include "Viewport.h"

namespace Apollo
{
	Viewport::Viewport(unsigned int width, unsigned int height)
	{
		m_Width = width;
		m_Height = height;
	}

	Viewport::~Viewport(void)
	{
		Release();
	}

	void Viewport::SaveState(TiXmlElement*& parentElement)
	{
		TiXmlElement* elem = new TiXmlElement("Viewport");
		parentElement->LinkEndChild(elem);

		elem->SetDoubleAttribute("x", m_XPosition);
		elem->SetDoubleAttribute("y", m_YPosition);
		elem->SetAttribute("width", m_Width);
		elem->SetAttribute("height", m_Height);

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

	void Viewport::LoadState(TiXmlElement* element, SceneObject* parent)
	{
		int width;
		int height;

		element->QueryIntAttribute("width", &width);
		element->QueryIntAttribute("height", &height);
		
		this->Resize(width, height);

		SceneObject::LoadState(element, parent);
	}

	bool Viewport::IsOnScreen(SceneObject* object)
	{
		if (((object->GetXPosition() + object->GetWidth()) > this->GetXPosition()) &&	// Within left bound
			(object->GetXPosition() < (this->GetXPosition() + this->GetWidth())) &&		// Within right bound
			((object->GetYPosition() + object->GetHeight()) > this->GetYPosition()) &&	// Within upper bound
			(object->GetYPosition() < (this->GetYPosition() + this->GetHeight())))		// Within lower bound
		{
			return true;
		}
		
		else
		{
			return false;
		}
	}

	void Viewport::Resize(unsigned int width, unsigned int height)
	{
		m_Width = width;
		m_Height = height;
	}
}
