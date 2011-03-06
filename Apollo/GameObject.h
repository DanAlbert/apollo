#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Apollo.h"

#include <tinyxml.h>
#include <vector>

#include "Debug.h"

namespace Apollo
{
	class APOLLO_API GameObject
	{
	public:
		GameObject(void);
		virtual ~GameObject(void);

		GameObject& operator= (const GameObject& rhs);

		virtual void	Release(bool releaseChildren = true);

		// This should be made private, calling classes made friend
		virtual void	SaveState(TiXmlElement*& parentElement) = 0;
		virtual void	LoadState(TiXmlElement* element, GameObject* parent = NULL);

		virtual void	Update(long dTime)					= 0;
		virtual void	Draw(long dTime, GameObject* view)	= 0;

		// Accessors //
		inline bool			GetActive(void)		const	{	return m_Active;	}
		inline bool			GetVivible(void)	const	{	return m_Visible;	}
		inline float		GetXPosition(void)	const	{	return m_XPosition;	}
		inline float		GetYPosition(void)	const	{	return m_YPosition;	}
		inline float		GetRotation(void)	const	{	return m_Rotation;	}
		inline unsigned int	GetWidth(void)		const	{	return m_Width;		}
		inline unsigned int	GetHeight(void)		const	{	return m_Height;	}
		inline GameObject*	GetParent(void)		const	{	return m_Parent;	}

		float GetRelativeXPosition(void);
		float GetRelativeYPosition(void);

		// Modifiers //
		void SetActive(bool active);
		void SetVisible(bool visible);
		
		void SetPosition(float x, float y);
		void SetRelativePosition(float x, float y);
		void Move(float x, float y);

		void SetRotation(float rotation);
		void Rotate(float rotation);

		void SetParent(GameObject* parent);
		void RemoveParent(void);

	protected:
		bool			m_Active;
		bool			m_Visible;
		float			m_XPosition;
		float			m_YPosition;
		float			m_Rotation;
		unsigned int	m_Width;
		unsigned int	m_Height;

		GameObject*					m_Parent;
		std::vector<GameObject*>	m_Children;

		void addChild(GameObject* child);		// DO NOT CALL DIRECTLY
		void removeChild(GameObject* child);	// ONLY TO BE CALLED BY SetParent() AND RemoveParent()
	};
}

#endif // __GAMEOBJECT_H__