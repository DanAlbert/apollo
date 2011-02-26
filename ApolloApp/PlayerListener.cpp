#include "PlayerListener.h"

PlayerListener::PlayerListener(Apollo::Window* window) : InputListener(window)
{
	playerMoveForward = false;
	playerMoveBackward = false;
	playerRotateLeft = false;
	playerRotateRight = false;
}

PlayerListener::~PlayerListener(void)
{
}

bool PlayerListener::keyPressed(const OIS::KeyEvent& e)
{
	switch (e.key)
	{
	case OIS::KeyCode::KC_UP:
		playerMoveForward = true;
		break;
	case OIS::KeyCode::KC_DOWN:
		playerMoveBackward = true;
		break;
	case OIS::KeyCode::KC_LEFT:
		playerRotateLeft = true;
		break;
	case OIS::KeyCode::KC_RIGHT:
		playerRotateRight = true;
		break;
	default:
		break;
	}

	return true;
}

bool PlayerListener::keyReleased(const OIS::KeyEvent& e)
{
	switch (e.key)
	{
	case OIS::KeyCode::KC_UP:
		playerMoveForward = false;
		break;
	case::OIS::KeyCode::KC_DOWN:
		playerMoveBackward = false;
		break;
	case OIS::KeyCode::KC_LEFT:
		playerRotateLeft = false;
		break;
	case OIS::KeyCode::KC_RIGHT:
		playerRotateRight = false;
		break;
	default:
		break;
	}

	return true;
}