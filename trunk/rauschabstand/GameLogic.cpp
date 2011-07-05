//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameLogic.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

GameLogic::GameLogic(SceneManager* sceneMgr, Camera* camera, AudioPlayer* audioPlayer) : overlayManager(Ogre::OverlayManager::getSingleton())
{
	m_gameLogicStates = INIT;

	m_sceneMgr = sceneMgr;
	m_camera = camera;
	m_audioPlayer = audioPlayer;

	m_blockMs = Real(0.0175);
	m_blockMsSide = Real(0.9);

	m_mapGenerator = new MapGenerator("map01", m_sceneMgr, (84 + 10) * m_blockMs * 1000, 10);
	//map length: songlength: 84sec, countdown: 10sec
	m_map = m_mapGenerator->getMap();
	m_player = new Player("Player", m_sceneMgr, m_camera, m_map);

	m_t = 0;
	m_u = 0;
	m_score = 0;
	m_multiplier = 1;
	m_timeCloseToHole = 0;
	m_countdownTime = 0;
	m_boostActive = false;
	m_boostLevel = 0;
	m_boostSpeed = 1;


	// COUNTDOWN BEGIN
	//overlayManager = Ogre::OverlayManager::getSingleton();
	m_countDown = 0;
	overlayCountDown = 0;

	// create material
	MaterialManager& materialManager = Ogre::MaterialManager::getSingleton();
	for(int i = 1; i < 4; i++) {
		MaterialPtr material = materialManager.create("CountDown" + Ogre::StringConverter::toString(i), "General");
		material->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/Num_" + Ogre::StringConverter::toString(i) + ".png");
		material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
		material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
		material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
		material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
	}

	m_countDown = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "CountDown"));
	m_countDown->setPosition(0.4f, 0.4f);
	m_countDown->setDimensions(0.2f, 0.2f);
	m_countDown->setMaterialName("CountDown1");
	m_countDown->setMaterialName("CountDown2");
	m_countDown->setMaterialName("CountDown3");
	overlayCountDown = overlayManager.create("Overlay_CountDown");
	overlayCountDown->add2D(m_countDown);
	overlayCountDown->hide();
	// COUNTDOWN END
}

GameLogic::~GameLogic()
{
	delete m_map;
	delete m_player;
	delete m_mapGenerator;
}

void GameLogic::init()
{
	m_mapGenerator->generateMap();
	m_audioPlayer->addObstacles(m_map->getObstaclePositions());
	start();
}

void GameLogic::start()
{
	m_gameLogicStates = COUNTDOWN;
}

void GameLogic::update(Ogre::Real timeSinceLastFrame)
{
	//TODO: fix start when everything is loaded..
	if (m_gameLogicStates == INIT)
	{
		return;
	}

	Ogre::Real tdif = m_blockMs * timeSinceLastFrame * m_boostSpeed;
	Ogre::Real shipPosPrev = m_t;
	m_t += tdif;
	m_score += (unsigned long) (m_multiplier * m_boostSpeed * tdif * 10);	//boost == score bonus...
	m_t = m_t >= m_map->getLength() ? m_map->getLength() : m_t;

	if (m_player->getJumpHeight() < DEADHEIGHT)
	{
		playerDies();
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

	m_audioPlayer->updateObstacles(m_map->getPosition(shipPosPrev, m_u) - m_map->getPosition(m_t, m_u));

	if (m_gameLogicStates == COUNTDOWN) {
		m_score = 0;

		m_countdownTime += timeSinceLastFrame;

		if (m_countdownTime >= 7000 && m_countdownTime < 8000) {
			overlayCountDown->show();
		} else if (m_countdownTime >= 8000 && m_countdownTime < 9000) {
			m_countDown->setMaterialName("CountDown2");
		} else if (m_countdownTime >= 9000 && m_countdownTime < 10000) {
			m_countDown->setMaterialName("CountDown1");
		} else if (m_countdownTime > 10000) {
			overlayCountDown->hide();

			m_gameLogicStates = RUNNING;
			m_audioPlayer->play();
			m_audioPlayer->playObstacles();
		}
	}

	//TODO: test
	if (m_boostActive) 
	{
		m_boostLevel -= timeSinceLastFrame / Real(1000);
		if (m_boostLevel <= 0) 
		{
			boostOff();
		}
	}
	else 
	{
		if (m_boostLevel < 1) 
		{
			m_boostLevel += timeSinceLastFrame / Real(10000);
		}
		else 
		{
			m_boostLevel = 1;
		}
	}
}

void GameLogic::update(Ogre::Real elapsedTime, OIS::Keyboard* input) {
	Ogre::Real shipPosPrev = m_u;
	
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
	// kill player for debug
	if (input->isKeyDown(OIS::KC_K))
	{
		playerDies();
	}
	if (input->isKeyDown(OIS::KC_LSHIFT))
	{
		if (!m_boostActive && m_boostLevel > Real(0.1) && m_gameLogicStates == RUNNING) 
		{
			boostOn();
		}
	}
	m_player->update(elapsedTime, input);
}

void GameLogic::keyReleased(Real timeSinceLastFrame, const OIS::KeyEvent& keyEventRef)
{
	m_player->keyReleased(timeSinceLastFrame, keyEventRef);

	if (keyEventRef.key == OIS::KC_LSHIFT) 
	{
		if (m_boostActive) 
		{
			boostOff();
		}
	}
}

void GameLogic::playerDies() 
{
	m_t = 0;
	m_u = 0;
	m_score = 0;
	m_multiplier = 1;
	m_player->resetToStart();
	m_audioPlayer->stop();
	m_audioPlayer->reset(m_map->getObstaclePositions());
	m_boostActive = false;
	m_boostLevel = 0;
	m_boostSpeed = 1;
	m_countDown->setMaterialName("CountDown3");
	m_gameLogicStates = COUNTDOWN;
	m_countdownTime = 0;
	m_visuals->reset();
}

void GameLogic::boostOn() 
{
	m_boostActive = true;
	//TODO: turn on blur
	//TODO: speed up visuals
	//speed up sound
	m_audioPlayer->increasePitch(1.0f);
	//speed up level
	m_boostSpeed = 2;

	Ogre::CompositorManager::getSingleton().setCompositorEnabled(OgreFramework::getSingletonPtr()->m_pViewport, "Motion Blur", true);
	//Ogre::CompositorManager::getSingleton().setCompositorEnabled(OgreFramework::getSingletonPtr()->m_pViewport, "Radial Blur", true);
}

void GameLogic::boostOff() 
{
	m_boostActive = false;
	//TODO: turn off blur
	//TODO: speed down visuals
	//speed down sound
	m_audioPlayer->decreasePitch(1.0f);
	//speed down level
	m_boostSpeed = 1;

	Ogre::CompositorManager::getSingleton().setCompositorEnabled(OgreFramework::getSingletonPtr()->m_pViewport, "Motion Blur", false);
	//Ogre::CompositorManager::getSingleton().setCompositorEnabled(OgreFramework::getSingletonPtr()->m_pViewport, "Radial Blur", false);
}

//|||||||||||||||||||||||||||||||||||||||||||||||