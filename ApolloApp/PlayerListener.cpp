#include "PlayerListener.h"

PlayerListener::PlayerListener(Apollo::Window* window) : InputListener(window)
{
	m_PlayerMoveForward = false;
	m_PlayerMoveBackward = false;
	m_PlayerRotateLeft = false;
	m_PlayerRotateRight = false;
}

PlayerListener::~PlayerListener(void)
{
}

bool PlayerListener::keyPressed(const OIS::KeyEvent& e)
{
	switch (e.key)
	{
	case OIS::KeyCode::KC_UP:
		m_PlayerMoveForward = true;
		break;
	case::OIS::KeyCode::KC_DOWN:
		m_PlayerMoveBackward = true;
		break;
	case OIS::KeyCode::KC_LEFT:
		m_PlayerRotateLeft = true;
		break;
	case OIS::KeyCode::KC_RIGHT:
		m_PlayerRotateRight = true;
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
		m_PlayerMoveForward = false;
		break;
	case::OIS::KeyCode::KC_DOWN:
		m_PlayerMoveBackward = false;
		break;
	case OIS::KeyCode::KC_LEFT:
		m_PlayerRotateLeft = false;
		break;
	case OIS::KeyCode::KC_RIGHT:
		m_PlayerRotateRight = false;
		break;
	default:
		break;
	}

	return true;
}