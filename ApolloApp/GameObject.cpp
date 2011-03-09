#include "GameObject.h"

GameObject::GameObject(Apollo::Viewport* viewport) :
	viewport(viewport)
{
}

GameObject::GameObject(
	const char* path,
	Apollo::RenderSystem* renderSystem,
	Apollo::Viewport* viewport) :
		viewport(viewport),
		velocity()
{
	this->loadFromFile(path, renderSystem);
}

GameObject::~GameObject(void)
{
}

void GameObject::SaveState(TiXmlElement*& element, bool elementIsParent)
{
	TiXmlElement* elem;

	if (elementIsParent)
	{
		elem = new TiXmlElement("GameObject");
		element->LinkEndChild(elem);
	}
	else
	{
		elem = element;
	}
	
	elem->SetDoubleAttribute("velocity.x", this->velocity.x);
	elem->SetDoubleAttribute("velocity.y", this->velocity.y);
	elem->SetDoubleAttribute("angular-velocity", this->angularVelocity);

	SpriteObject::SaveState(elem, false);
}


void GameObject::LoadState(TiXmlElement* element, Apollo::SceneObject* parent)
{
	element->QueryDoubleAttribute("velocity.x", &this->velocity.x);
	element->QueryDoubleAttribute("velocity.y", &this->velocity.y);
	element->QueryDoubleAttribute("angular-velocity", &this->angularVelocity);
	Apollo::SpriteObject::LoadState(element, parent);
}

void GameObject::Update(long dTime)
{
	if (this->m_Active)
	{
		this->updateRotation(dTime);
		this->updatePosition(dTime);
		this->wrapScreenEdges();
	}

	Apollo::SpriteObject::Update(dTime);
}

void GameObject::updatePosition(long dTime)
{
	this->Move(this->velocity.x * dTime, this->velocity.y * dTime);
}

void GameObject::updateRotation(long dTime)
{
	this->Rotate(this->angularVelocity * dTime);
}

void GameObject::wrapScreenEdges(void)
{
	if ((this->m_XPosition + this->m_Width) < this->viewport->GetXPosition())
	{
		this->m_XPosition = this->viewport->GetXPosition() + this->viewport->GetWidth();
	}
	else if (this->m_XPosition > (this->viewport->GetXPosition() + this->viewport->GetWidth()))
	{
		this->m_XPosition = this->viewport->GetXPosition() - this->m_Width;
	}

	if ((this->m_YPosition + this->m_Height) < this->viewport->GetYPosition())
	{
		this->m_YPosition = this->viewport->GetYPosition() + this->viewport->GetHeight();
	}
	else if (this->m_YPosition > (this->viewport->GetYPosition() + this->viewport->GetHeight()))
	{
		this->m_YPosition = this->viewport->GetYPosition() - this->m_Height;
	}
}