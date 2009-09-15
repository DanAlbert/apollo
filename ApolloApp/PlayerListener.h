#ifndef __PLAYERLISTENER_H__
#define __PLAYERLISTENER_H__

#include <InputListener.h>

class PlayerListener : public Apollo::InputListener
{
public:
	PlayerListener(Apollo::Window* window);
	virtual ~PlayerListener(void);

	bool keyPressed(const OIS::KeyEvent& e);
	bool keyReleased(const OIS::KeyEvent& e);

	bool GetPlayerMoveForward(void)		const	{	return m_PlayerMoveForward;		}
	bool GetPlayerMoveBackward(void)	const	{	return m_PlayerMoveBackward;	}
	bool GetPlayerRotateLeft(void)		const	{	return m_PlayerRotateLeft;		}
	bool GetPlayerRotateRight(void)		const	{	return m_PlayerRotateRight;		}

protected:
	bool m_PlayerMoveForward;
	bool m_PlayerMoveBackward;
	bool m_PlayerRotateLeft;
	bool m_PlayerRotateRight;
};

#endif // __PLAYERLISTENER_H__