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

		virtual void	SaveState(TiXmlElement*& parentElement) = 0;

		virtual void	Update(long dTime)					= 0;
		virtual void	Draw(long dTime, GameObject* view)	= 0;

		// Accessors //
		inline bool			GetActive(void)		const	{	return m_Active;	}
		inline bool			GetVivible(void)	const	{	return m_Visible;	}
		inline float		GetXPosition(void)	const	{	return m_XPosition;	}
		inline float		GetYPosition(void)	const	{	return m_YPosition;	}
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

		void SetParent(GameObject* parent);
		void RemoveParent(void);

		void AddChild(GameObject* child);		// DO NOT CALL DIRECTLY
		void RemoveChild(GameObject* child);	// ONLY TO BE CALLED BY SetParent() AND RemoveParent()
		

	protected:
		bool			m_Active;
		bool			m_Visible;
		float			m_XPosition;
		float			m_YPosition;
		unsigned int	m_Width;
		unsigned int	m_Height;

		GameObject*					m_Parent;
		std::vector<GameObject*>	m_Children;
	};
}

#endif // __GAMEOBJECT_H__