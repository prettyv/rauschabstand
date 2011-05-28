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
	m_jumpNode = m_sideNode->createChildSceneNode(m_name + "_sideNode" + "_jumpNode");
    m_playerEntity = m_pSceneMgr->createEntity(m_name, "razor.mesh");
	m_jumpNode->attachObject(m_playerEntity);
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
    m_tightness = 1.0f;

	m_speed = Vector3(0, 0, 0);
	m_t = 0;
	m_u = 0;
	m_mass = 1;

	m_playerMainNode->setPosition(0, 0, 0);
	m_sideNode->setPosition(0, 0, 0);
	m_jumpNode->setPosition(0, 300, 0);

	m_map = map;

	m_throughHole = false;
	m_jumping = false;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Player::update (double elapsedTime)
{
	//TODO: cleanup, remove magic numbers, move to gamestate.cpp(?), pack into functions

	// set player orientation to local map orientation
	Quaternion orientation = m_map->getOrientation(m_t);
	m_playerMainNode->setOrientation(orientation * Quaternion(0, 0, 1, 0));

	Vector3 gravity = Vector3(0, -0.02, 0);

	// calculate distanceToMap
	double distanceToMap = m_jumpNode->getPosition().y - 50;

	// calculate mapAntiGravity with distanceToMap
	Vector3 mapAntiGravity;
	if (distanceToMap < 1) {	// prevent division by zero
		mapAntiGravity = Vector3(0, 0.05, 0);
	} else {
		mapAntiGravity = Vector3(0, 0.05 / distanceToMap, 0);
	}

	// TODO: remove mass??
	if (!m_map->isHoleInMap(m_t, m_u) && !m_throughHole)
	{
		m_speed += mapAntiGravity * m_mass;
	}
	m_speed += gravity * m_mass;

	// simulate friction
	m_speed *= 0.98;

	// translate node
	m_jumpNode->translate(m_speed * elapsedTime);

	// if jumpposition < THROUGHHOLE -> speed auf 0
	Vector3 jumpPosition = m_jumpNode->getPosition();
	if (jumpPosition.y < THROUGHHOLEHEIGHT)
	{
		if (m_map->isHoleInMap(m_t, m_u))
		{
			m_throughHole = true;
		}
		else if (!m_throughHole)
		{
			m_jumpNode->setPosition(0, 0, 0);
			m_speed = Vector3(0, 0, 0);
		}
	}

	if (jumpPosition.y < DEADHEIGHT)
	{
		// reset to start
		m_throughHole = false;

		m_playerMainNode->setPosition(0, 0, 0);
		m_t = 0;
		m_sideNode->setPosition(0, 0, 0);
		m_u = 0;
		m_jumpNode->setPosition(0, 300, 0);

		m_speed = Vector3(0, 0, 0);
	}

	//TODO: fix bug: checks before player is really jumping, result: double jump speed
	// check if back from jump..
	if (m_jumping && jumpPosition.y < 50) {
		m_jumping = false;
	}

	m_playerMainNode->setPosition(m_map->getPosition(m_t, 0));
	
	updateCamera();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Player::update (Real elapsedTime, OIS::Keyboard *input) {

	//TODO: remove this input, should be moving by it self..
    if (input->isKeyDown (OIS::KC_W)) 
	{
		//TODO: * elapsedTime
		m_t += 0.2;
		m_t = m_t >= m_map->getLength() ? m_map->getLength() : m_t;
		updateCamera();
	}

    if (input->isKeyDown (OIS::KC_S))
	{
		//TODO: * elapsedTime
		m_t -= 0.2;
		m_t = m_t < 0 ? 0 : m_t;
		updateCamera();
	}

    if (input->isKeyDown (OIS::KC_A))
	{
		m_u += 0.4 * elapsedTime;
		m_u = m_u < m_map->getWidth() * 100 / (double) 2 ? m_u : m_map->getWidth() * 100 / (double) 2;
		m_sideNode->setPosition(Vector3(m_u, 0, 0));
		updateCamera();
    }

	if (input->isKeyDown (OIS::KC_D))
	{
		m_u -= 0.4 * elapsedTime;
		m_u = m_u > -m_map->getWidth() * 100 / (double) 2 ? m_u : -m_map->getWidth() * 100 / (double) 2;
		m_sideNode->setPosition(Vector3(m_u, 0, 0));
		updateCamera();
    }

	// jump
	// player can only jump when
	// - space key is pressed
	// - player is not jumping
	// - player is not above a hole
	// - player has fallen through a hole
	if (input->isKeyDown (OIS::KC_SPACE) && 
			!m_jumping && 
			!m_map->isHoleInMap(m_t, m_u) && 
			m_jumpNode->getPosition().y > THROUGHHOLEHEIGHT)
	{
		//TODO: fix jump
		double distanceToMap = m_jumpNode->getPosition().y;

		if (distanceToMap < 1) {	// prevent division by zero
			m_speed = Vector3(0, 0.05, 0) * elapsedTime;
		} else {
			m_speed = Vector3(0, 0.05 /*/ distanceToMap*/, 0) * elapsedTime;
		}
		m_jumping = true;
	}

}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Player::updateCamera()
{
	Vector3 displacement = ( m_cameraPosition->_getDerivedPosition() - m_chaseCamera->getPosition() ) * m_tightness;
	m_chaseCamera->translate(displacement);

	//TODO: rotate camera..
	Quaternion orientation = m_map->getOrientation(m_t);
	m_chaseCamera->setOrientation(orientation);
	//m_cameraTarget->setOrientation(orientation);

	displacement = ( m_targetPosition->_getDerivedPosition() - m_cameraTarget->getPosition() ) * m_tightness;
	m_cameraTarget->translate(displacement);
}

//|||||||||||||||||||||||||||||||||||||||||||||||