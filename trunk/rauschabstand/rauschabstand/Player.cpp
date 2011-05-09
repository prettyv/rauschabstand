//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Player.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

Player::Player(std::string name, SceneManager* sceneMgr, Camera* camera) {
    m_name = name;

    m_pSceneMgr = sceneMgr;

    // player
    m_playerMainNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(m_name);
    m_playerEntity = m_pSceneMgr->createEntity(m_name, "razor.mesh");
    m_playerMainNode->attachObject(m_playerEntity);
    m_cameraPosition = m_playerMainNode->createChildSceneNode(m_name + "_sight", Vector3 (0, 100, -300));
    m_targetPosition = m_playerMainNode->createChildSceneNode(m_name + "_chaseCamera", Vector3 (0, 0, 200));

    // camera
    m_cameraTarget = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(m_name + "cameraTarget");
    m_chaseCamera = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(m_name + "chaseCamera");
    m_chaseCamera->setAutoTracking(true, m_cameraTarget);   // the camera will always look at the camera target
    m_chaseCamera->setFixedYawAxis(true);   // needed because of auto tracking
    //m_camera = m_pSceneMgr->createCamera(m_name + "_camera");
    m_camera = camera;
    //m_camera->setPosition(0.0, 0.0, 0.0);
    m_chaseCamera->attachObject(m_camera);
    m_tightness = 1.0f;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Player::update (Real elapsedTime, OIS::Keyboard *input) {
    // handle player+camera movement
    if (input->isKeyDown (OIS::KC_W)) {
        // player movement
        m_playerMainNode->translate(m_playerMainNode->getOrientation () * Vector3 (0, 0, 1.01 * elapsedTime));

        // camera movement
        Vector3 displacement = ( m_cameraPosition->_getDerivedPosition() - m_chaseCamera->getPosition() ) * m_tightness;
        m_chaseCamera->translate(displacement);

        displacement = ( m_targetPosition->_getDerivedPosition() - m_cameraTarget->getPosition() ) * m_tightness;
        m_cameraTarget->translate(displacement);
    }

    if (input->isKeyDown (OIS::KC_S)) {
        m_playerMainNode->translate (m_playerMainNode->getOrientation () * Vector3 (0, 0, -1.01 * elapsedTime));

        // camera movement
        Vector3 displacement = ( m_cameraPosition->_getDerivedPosition() - m_chaseCamera->getPosition() ) * m_tightness;
        m_chaseCamera->translate(displacement);

        displacement = ( m_targetPosition->_getDerivedPosition() - m_cameraTarget->getPosition() ) * m_tightness;
        m_cameraTarget->translate(displacement);
    }

    if (input->isKeyDown (OIS::KC_A)) {
        m_playerMainNode->yaw (Radian (0.001 * elapsedTime));

        // camera movement
        Vector3 displacement = ( m_cameraPosition->_getDerivedPosition() - m_chaseCamera->getPosition() ) * m_tightness;
        m_chaseCamera->translate(displacement);

        displacement = ( m_targetPosition->_getDerivedPosition() - m_cameraTarget->getPosition() ) * m_tightness;
        m_cameraTarget->translate(displacement);
    }

    if (input->isKeyDown (OIS::KC_D)) {
        m_playerMainNode->yaw (Radian (-0.001 * elapsedTime));

        // camera movement
        Vector3 displacement = ( m_cameraPosition->_getDerivedPosition() - m_chaseCamera->getPosition() ) * m_tightness;
        m_chaseCamera->translate(displacement);

        displacement = ( m_targetPosition->_getDerivedPosition() - m_cameraTarget->getPosition() ) * m_tightness;
        m_cameraTarget->translate(displacement);
    }
}

//|||||||||||||||||||||||||||||||||||||||||||||||