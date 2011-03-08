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

	void Viewport::SaveState(TiXmlElement*& element, bool elementIsParent)
	{
		TiXmlElement* elem;

		if (elementIsParent)
		{
			elem = new TiXmlElement("Viewport");
			element->LinkEndChild(elem);
		}
		else
		{
			elem = element;
		}
		
		elem->SetAttribute("width", m_Width);
		elem->SetAttribute("height", m_Height);

		SceneObject::SaveState(elem, false);
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
