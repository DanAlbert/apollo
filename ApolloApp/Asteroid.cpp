#include "Asteroid.h"

Asteroid::Asteroid(
	const char* path,
	Apollo::RenderSystem* renderSystem,
	Apollo::Viewport* viewport) :
		GameObject(viewport)
{
	SpriteObject::loadFromFile(path, renderSystem);
	this->velocity = Apollo::Vector2(((rand() % 100) - 50) / 1000.0f, ((rand() % 100) - 50) / 1000.0f);
	this->angularVelocity = ((rand() % 100) - 50) / 10000.0f;
}

Asteroid::~Asteroid(void)
{
}

void Asteroid::SaveState(TiXmlElement*& element, bool elementIsParent)
{
	TiXmlElement* elem;

	if (elementIsParent)
	{
		elem = new TiXmlElement("Asteroid");
		element->LinkEndChild(elem);
	}
	else
	{
		elem = element;
	}

	elem->SetAttribute("resource", this->m_Sprite->GetResourcePath());
	
	GameObject::SaveState(elem, false);
}


void Asteroid::LoadState(TiXmlElement* element, Apollo::SceneObject* parent)
{
	GameObject::LoadState(element, parent);
}

void Asteroid::Update(long dTime)
{
	if (this->m_Active)
	{
		// ASteroid stuff
	}

	GameObject::Update(dTime);
}