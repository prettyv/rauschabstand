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

	m_mapPositionCube = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("mapPositionCube");
	Ogre::Entity* cube = m_pSceneMgr->createEntity("Cube", "cube.mesh");
	m_mapPositionCube->attachObject(cube);
	m_mapPositionCube->scale(0.5, 0.5, 0.5);

	m_speed = Vector3(0, 0, 0);
	m_t = 0;
	m_u = 0;
	m_mass = 1;

	m_playerMainNode->setPosition(0, 0, 0);
	m_sideNode->setPosition(0, 0, 0);
	m_jumpNode->setPosition(0, 300, 0);

	m_map = map;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Player::update (double elapsedTime)
{
	// set player orientation to local map orientation
	Quaternion orientation = m_map->getOrientation(m_t);
	m_playerMainNode->setOrientation(orientation * Quaternion(0, 0, 1, 0));

	// set debug cube position
	m_mapPositionCube->setPosition(m_map->getPosition(m_t, m_u));

	Vector3 gravity = Vector3(0, -0.01, 0);

	// calculate distanceToMap
	double distanceToMap = m_jumpNode->_getDerivedPosition().distance(m_map->getPosition(m_t, m_u)) - 100;

	// calculate mapAntiGravity with distanceToMap
	Vector3 mapAntiGravity;
	if (distanceToMap < 1) {	// prevent division by zero
		mapAntiGravity = Vector3(0, 0.05, 0);
	} else {
		mapAntiGravity = Vector3(0, 0.05 / distanceToMap, 0);
	}

	// TODO: remove mass??
	m_speed += mapAntiGravity * m_mass;
	m_speed += gravity * m_mass;

	// simulate friction
	m_speed *= 0.99;

	// translate node
	m_jumpNode->translate(m_speed * elapsedTime);
	
	updateCamera();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Player::update (Real elapsedTime, OIS::Keyboard *input) {
    // handle player+camera movement
    if (input->isKeyDown (OIS::KC_W)) 
	{
		//TODO: remove this input, should be moving by it self..
		Quaternion orientation = m_map->getOrientation(m_t);
		m_playerMainNode->translate(orientation * Vector3(0, 0, -20));
		m_t += 0.2;
		updateCamera();
	}

    if (input->isKeyDown (OIS::KC_S))
	{
		Quaternion orientation = m_map->getOrientation(m_t);
		m_playerMainNode->translate(orientation * Vector3(0, 0, 20));
		m_t -= 0.2;
		updateCamera();
	}

    if (input->isKeyDown (OIS::KC_A))
	{
		m_u -= 0.4 * elapsedTime;
		m_sideNode->translate(Vector3(0.4 * elapsedTime, 0, 0));
		updateCamera();
    }

	if (input->isKeyDown (OIS::KC_D))
	{
		m_u += 0.4 * elapsedTime;
		m_sideNode->translate(Vector3(-0.4 * elapsedTime, 0, 0));
		updateCamera();
    }

	if (input->isKeyDown (OIS::KC_SPACE))
	{
		//TODO: nur wenn am boden/ bodennähe
		m_speed += Vector3(0, 0.01, 0) * elapsedTime;
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