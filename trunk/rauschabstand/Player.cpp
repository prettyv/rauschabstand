//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Player.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

Player::Player(std::string name, SceneManager* sceneMgr, Camera* camera, Map* map) {
    m_name = name;

    m_pSceneMgr = sceneMgr;

    // player
    m_playerMainNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(m_name);
	m_sideNode = m_playerMainNode->createChildSceneNode(m_name + "_sideNode");
	m_jumpNode = m_sideNode->createChildSceneNode(m_name + "_jumpNode");
	m_sideRollNode = m_jumpNode->createChildSceneNode(m_name + "_sideRollNode");
    m_playerEntity = m_pSceneMgr->createEntity(m_name, "razor.mesh");
	// GLOW SHADER BEGIN
	//m_playerEntity->setMaterialName("glow_playertex");
	// GLOW SHADER END
	Ogre::Light* spotLight = m_pSceneMgr->createLight("spotLight");
	spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
	spotLight->setDiffuseColour(Ogre::ColourValue(0.9f, 0.8f, 0.8f));
	spotLight->setSpecularColour(Ogre::ColourValue(0.9f, 0.8f, 0.8f));
	spotLight->setDirection(Ogre::Vector3(0, 0, 1));
	spotLight->setPosition(Vector3(0, 0, 0));
	spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
	SceneNode* lightNode = m_sideRollNode->createChildSceneNode(m_name + "_lightNode");
	lightNode->attachObject(spotLight);
	lightNode->setPosition(0, 0, 200);
	m_playerEntity->setCastShadows(true);
	m_sideRollNode->attachObject(m_playerEntity);
    m_cameraPosition = m_jumpNode->createChildSceneNode(m_name + "_sight", Vector3 (0, 100, -300));
    m_targetPosition = m_jumpNode->createChildSceneNode(m_name + "_chaseCamera", Vector3 (0, 0, 200));
	m_playerMainNode->setOrientation(Quaternion(0, 0, 1, 0));

    // camera
    m_cameraTarget = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(m_name + "cameraTarget");
    m_chaseCamera = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(m_name + "chaseCamera");
	m_chaseCamera->setPosition(Quaternion(0, 0, 1, 0) * m_cameraPosition->getPosition());
    m_chaseCamera->setAutoTracking(true, m_cameraTarget);   // the camera will always look at the camera target
    m_chaseCamera->setFixedYawAxis(false);   // needed because of auto tracking
    //m_camera = m_pSceneMgr->createCamera(m_name + "_camera");
    m_camera = camera;
    //m_camera->setPosition(0.0, 0.0, 0.0);
    m_chaseCamera->attachObject(m_camera);
    m_tightness = 0.3f;

	m_speed = Vector3(0, 0, 0);

	m_rollFactor = 0;

	m_playerMainNode->setPosition(0, 0, 0);
	m_sideNode->setPosition(0, 0, 0);
	m_jumpNode->setPosition(0, 300, 0);

	m_map = map;

	m_throughHole = false;
	m_jumping = false;

	m_rollBack = false;
	m_boostSpeed = 1;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Player::update (Real timeSinceLastFrame, Real t, Real u)
{
	//TODO: cleanup, remove magic numbers, move to gamestate.cpp(?), pack into functions

	m_sideNode->setPosition(Vector3(u, 0, 0));

	// set player orientation to local map orientation
	Quaternion orientation = m_map->getOrientation(t);
	m_playerMainNode->setOrientation(orientation * Quaternion(0, 0, 1, 0));

	Vector3 gravity = Vector3(0.0f, -0.02f, 0.0f);

	// calculate distanceToMap
	double distanceToMap = m_jumpNode->getPosition().y - 50;

	// calculate mapAntiGravity with distanceToMap
	Vector3 mapAntiGravity;
	if (distanceToMap < 1) {	// prevent division by zero
		mapAntiGravity = Vector3(0.0f, 0.05f, 0.0f);
	} else {
		mapAntiGravity = Vector3(0.0f, 0.05f / distanceToMap, 0.0f);
	}

	// TODO: remove mass??
	if (!m_map->isHoleInMap(t, u) && !m_throughHole)
	{
		m_speed += mapAntiGravity * m_boostSpeed;
	}
	if (m_map->isHoleInMap(t, u)) 
	{
		m_speed += gravity * m_boostSpeed;
	}
	m_speed += gravity * m_boostSpeed;

	// simulate friction
	m_speed *= Real(0.98);

	// translate node
	m_jumpNode->translate(m_speed * timeSinceLastFrame);

	// if jumpposition < THROUGHHOLE -> speed auf 0
	Vector3 jumpPosition = m_jumpNode->getPosition();
	if (jumpPosition.y < THROUGHHOLEHEIGHT)
	{
		if (m_map->isHoleInMap(t, u))
		{
			m_throughHole = true;
		}
		else if (!m_throughHole)
		{
			m_jumpNode->setPosition(0, 0, 0);
			m_speed = Vector3(0, 0, 0);
		}
	}

	//TODO: fix bug: checks before player is really jumping, result: double jump speed
	// check if back from jump..
	if (m_jumping && jumpPosition.y < 50) {
		m_jumping = false;
	}


	// for side-roll movement while steering
	if (m_rollBack && m_rollFactor < 0.04f && m_rollFactor > -0.04f)	// when roll-back has finished set to "normal position"
	{
		m_rollFactor = 0.0f;
		m_rollBack = false;
	} else if (m_rollBack && m_rollFactor < -0.04f)		// rolling-back
	{
		m_rollFactor += 0.005f * timeSinceLastFrame;
		m_sideRollNode->roll(Ogre::Radian(0.005f) * timeSinceLastFrame);
	} else if (m_rollBack && m_rollFactor > 0.04f)		// rolling-back
	{
		m_rollFactor -= 0.005f * timeSinceLastFrame;
		m_sideRollNode->roll(Ogre::Radian(-0.005f) * timeSinceLastFrame);
	}
	

	m_playerMainNode->setPosition(m_map->getPosition(t, 0));
	
	updateCamera(t);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Player::update(Real elapsedTime, OIS::Keyboard *input) {
	if (m_rollFactor < 0.5 && m_rollFactor > -0.5)
	{
		if (input->isKeyDown (OIS::KC_A))
		{
			// for side-roll movement while steering
			m_rollFactor -= 0.005f * elapsedTime;
			m_sideRollNode->roll(Ogre::Radian(-0.005f) * elapsedTime);
			m_rollBack = false;
		}

		if (input->isKeyDown (OIS::KC_D))
		{
			// for side-roll movement while steering
			m_rollFactor += 0.005f * elapsedTime;
			m_sideRollNode->roll(Ogre::Radian(0.005f) * elapsedTime);
			m_rollBack = false;
		}
	}
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Player::jump(Real elapsedTime, Real t, Real u)
{
	// jump
	// player can only jump when
	// - player is not jumping
	// - player is not above a hole
	// - player has fallen through a hole
	if (!m_jumping && 
		!m_map->isHoleInMap(t, u) && 
		m_jumpNode->getPosition().y > THROUGHHOLEHEIGHT)
	{
		//TODO: fix jump
		double distanceToMap = m_jumpNode->getPosition().y;

		if (distanceToMap < 1) {	// prevent division by zero
			m_speed = Vector3(0, 1, 0);
		} else {
			m_speed = Vector3(0, 1 /*/ distanceToMap*/, 0);
		}
		m_jumping = true;
	}
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Player::keyReleased (Real elapsedTime, const OIS::KeyEvent& keyEvt) {
	if (keyEvt.key == OIS::KC_A || keyEvt.key == OIS::KC_D)
	{
		m_rollBack = true;
	}
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Player::updateCamera(Real t)
{
	Vector3 displacement = ( m_cameraPosition->_getDerivedPosition() - m_chaseCamera->getPosition() ) * m_tightness;
	m_chaseCamera->translate(displacement);

	//TODO: rotate camera..
	Quaternion orientation = m_map->getOrientation(t);
	m_chaseCamera->setOrientation(orientation);
	//m_cameraTarget->setOrientation(orientation);

	displacement = ( m_targetPosition->_getDerivedPosition() - m_cameraTarget->getPosition() ) * m_tightness;
	m_cameraTarget->translate(displacement);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Player::resetToStart()
{
	m_throughHole = false;
	m_playerMainNode->setPosition(0, 0, 0);
	m_sideNode->setPosition(0, 0, 0);
	m_jumpNode->setPosition(0, 300, 0);
	m_speed = Vector3(0, 0, 0);
	m_rollFactor = 0;
	m_sideRollNode->setOrientation(1, 0, 0, 0);
}

//|||||||||||||||||||||||||||||||||||||||||||||||