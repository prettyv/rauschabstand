//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameLogic.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

GameLogic::GameLogic(SceneManager* sceneMgr, Camera* camera, AudioPlayer* audioPlayer)
{
	m_gameLogicStates = INIT;

	m_sceneMgr = sceneMgr;
	m_camera = camera;
	m_audioPlayer = audioPlayer;

	m_map = new Map("map01", m_sceneMgr);
	m_player = new Player("Player", m_sceneMgr, m_camera, m_map);

	m_t = 0;
	m_u = 0;
	m_score = 0;
	m_multiplier = 1;
	m_timeCloseToHole = 0;
	m_countdownTime = 0;
	m_blockMs = Real(0.015);
	m_blockMsSide = Real(0.9);
}

GameLogic::~GameLogic()
{
	delete m_map;
	delete m_player;
}

void GameLogic::init()
{
	m_map->createRandomMap(84 * m_blockMs * 1000, 10);

	start();
}

void GameLogic::start()
{
	m_gameLogicStates = COUNTDOWN;
}

void GameLogic::reset()
{

}

void GameLogic::update(double timeSinceLastFrame)
{
	//TODO countdown
	if (m_gameLogicStates == COUNTDOWN) {
		m_countdownTime += timeSinceLastFrame;
		if (m_countdownTime > 5000)
		{
			m_gameLogicStates = RUNNING;
			m_audioPlayer->play();
		}
		m_player->update(timeSinceLastFrame, m_t, m_u);
	} else if (m_gameLogicStates == RUNNING) {
		
		double tdif = m_blockMs * timeSinceLastFrame;
		m_t += tdif;
		m_score += (unsigned long) (m_multiplier * tdif * 100);
		m_t = m_t >= m_map->getLength() ? m_map->getLength() : m_t;

		if (m_player->getJumpHeight() < DEADHEIGHT)
		{
			m_t = 0;
			m_u = 0;
			m_player->resetToStart();
		}

		if (m_map->isCloseToHole(m_t, m_u, 50))
		{
			m_timeCloseToHole += timeSinceLastFrame;
			if (m_timeCloseToHole > 80)
			{
				m_multiplier++;
				m_timeCloseToHole = 0;
			}
		}
		else
		{
			m_timeCloseToHole = 0;
		}

		m_player->update(timeSinceLastFrame, m_t, m_u);
	}
}

void GameLogic::update(Ogre::Real elapsedTime, OIS::Keyboard* input) {
	//TODO: move Inputcontrol from player here

	if (input->isKeyDown(OIS::KC_A))
	{
		m_u += m_blockMsSide * elapsedTime;
		m_u = m_u < m_map->getWidth() * 100 / (double) 2 ? m_u : m_map->getWidth() * 100 / (double) 2;
	}
	if (input->isKeyDown(OIS::KC_D))
	{
		m_u -= m_blockMsSide * elapsedTime;
		m_u = m_u > -m_map->getWidth() * 100 / (double) 2 ? m_u : -m_map->getWidth() * 100 / (double) 2;
	}
	if (input->isKeyDown(OIS::KC_SPACE))
	{
		m_player->jump(elapsedTime, m_t, m_u);
	}
}

void GameLogic::keyReleased(Real timeSinceLastFrame, const OIS::KeyEvent & keyEventRef)
{
	//TODO: move Inputcontrol from player here
	m_player->keyReleased(timeSinceLastFrame, keyEventRef);
}

//|||||||||||||||||||||||||||||||||||||||||||||||