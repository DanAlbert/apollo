#ifndef PLAYERLISTENER_H
#define PLAYERLISTENER_H

#include <InputListener.h>

class PlayerListener : public Apollo::InputListener
{
public:
	PlayerListener(Apollo::Window* window);
	virtual ~PlayerListener(void);

	bool keyPressed(const OIS::KeyEvent& e);
	bool keyReleased(const OIS::KeyEvent& e);

	bool GetPlayerMoveForward(void)		const	{	return playerMoveForward;	}
	bool GetPlayerMoveBackward(void)	const	{	return playerMoveBackward;	}
	bool GetPlayerRotateLeft(void)		const	{	return playerRotateLeft;	}
	bool GetPlayerRotateRight(void)		const	{	return playerRotateRight;	}

protected:
	bool playerMoveForward;
	bool playerMoveBackward;
	bool playerRotateLeft;
	bool playerRotateRight;
};

#endif // PLAYERLISTENER_H