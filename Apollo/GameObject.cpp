#include "GameObject.h"

namespace Apollo
{
	GameObject::GameObject(void)
	{
		m_Active = true;
		m_Visible = true;
		m_XPosition = 0.0f;
		m_YPosition = 0.0f;
		m_Rotation = 0.0f;
		m_Width = 0;
		m_Height = 0;
		m_Parent = NULL;
	}

	GameObject::~GameObject(void)
	{
		Release();
	}

	GameObject& GameObject::operator =(const GameObject& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		Release();

		m_Active = rhs.m_Active;
		m_Visible = rhs.m_Visible;
		m_XPosition = rhs.m_XPosition;
		m_YPosition = rhs.m_YPosition;
		m_Parent = rhs.m_Parent;
		m_Children = rhs.m_Children;

		return *this;
	}

	void GameObject::Release(bool releaseChildren)
	{
		RemoveParent();

		for (int i = 0; i < m_Children.size(); ++i)
		{
			if (releaseChildren)
			{
				m_Children[i]->Release(releaseChildren);
			}
			else
			{
				m_Children[i]->RemoveParent();
			}
		}
	}

	void GameObject::LoadState(TiXmlElement* element, GameObject* parent)
	{
		int active;
		int visible;
		float x;
		float y;
		float rotation;

		element->QueryIntAttribute("active", &active);
		element->QueryIntAttribute("visible", &visible);
		element->QueryFloatAttribute("x", &x);
		element->QueryFloatAttribute("y", &y);
		element->QueryFloatAttribute("rotation", &rotation);
		
		this->SetParent(parent);
		this->SetActive(active);
		this->SetVisible(visible);
		this->SetPosition(x, y);
		this->SetRotation(rotation);
	}

	float GameObject::GetRelativeXPosition(void)
	{
		if (m_Parent == NULL)
		{
			return m_XPosition;
		}
		else
		{
			return m_XPosition - m_Parent->GetRelativeXPosition();
		}
	}

	float GameObject::GetRelativeYPosition(void)
	{
		if (m_Parent == NULL)
		{
			return m_YPosition;
		}
		else
		{
			return m_YPosition - m_Parent->GetRelativeYPosition();
		}
	}

	void GameObject::SetActive(bool active)
	{
		m_Active = active;

		for (int i = 0; i < m_Children.size(); ++i)
		{
			m_Children[i]->SetActive(m_Active);
		}
	}

	void GameObject::SetVisible(bool visible)
	{
		m_Visible = visible;

		for (int i = 0; i < m_Children.size(); ++i)
		{
			m_Children[i]->SetVisible(m_Visible);
		}
	}

	void GameObject::SetPosition(float x, float y)
	{
		float dX = x - m_XPosition;
		float dY = y - m_YPosition;

		m_XPosition = x;
		m_YPosition = y;

		for (int i = 0; i < m_Children.size(); ++i)
		{
			m_Children[i]->Move(dX, dY);
		}
	}

	void GameObject::SetRelativePosition(float x, float y)
	{
		float dX = x - GetRelativeXPosition();
		float dY = y - GetRelativeYPosition();

		Move(dX, dY); // Will this cause a problem if the parent is moved before the children?

		for (int i = 0; i < m_Children.size(); ++i)
		{
			m_Children[i]->Move(dX, dY);
		}
	}

	void GameObject::Move(float x, float y)
	{
		m_XPosition += x;
		m_YPosition += y;

		for (int i = 0; i < m_Children.size(); ++i)
		{
			m_Children[i]->Move(x, y);
		}
	}

	void GameObject::SetRotation(float rotation)
	{
		m_Rotation = rotation;
	}

	void GameObject::Rotate(float rotation)
	{
		m_Rotation += rotation;
	}

	void GameObject::SetParent(GameObject* parent)
	{
		if (parent)
		{
			RemoveParent();
			parent->addChild(this);
			m_Parent = parent;
		}
	}

	void GameObject::RemoveParent(void)
	{
		if (m_Parent != NULL)
		{
			m_Parent->removeChild(this);
			m_Parent = NULL;
		}
	}

	void GameObject::addChild(GameObject* child)
	{
		m_Children.push_back(child);
	}

	void GameObject::removeChild(GameObject* child)
	{
		for (int i = 0; i < m_Children.size(); ++i)
		{
			if (m_Children[i] == child)
			{
				m_Children.erase(m_Children.begin() + i);
				return;
			}
		}
	}
}