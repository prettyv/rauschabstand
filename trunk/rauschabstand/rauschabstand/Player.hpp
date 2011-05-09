//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef PLAYER
#define PLAYER

//|||||||||||||||||||||||||||||||||||||||||||||||

#include <string>

#include "AdvancedOgreFramework.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

class Player {
public:
    Player(std::string name, Ogre::SceneManager* sceneMgr, Ogre::Camera* camera);

    void update(Ogre::Real elapsedTime, OIS::Keyboard *input);

private:
    Ogre::SceneManager*     m_pSceneMgr;

    // player
    Ogre::SceneNode*        m_playerMainNode;
    Ogre::Entity*           m_playerEntity;
    std::string             m_name;                 // name of the player
    Ogre::SceneNode*        m_cameraPosition;       // representing the camera position relative to the player -> changes automatically when player is moved
    Ogre::SceneNode*        m_targetPosition;       // representing the camera target relative to the player -> changes automatically when player is moved

    // camera
    Ogre::SceneNode*        m_cameraTarget;         // actual target of the camera
    Ogre::SceneNode*        m_chaseCamera;          // actual cameraNode
    Ogre::Camera*           m_camera;               // actual camera
    Ogre::Real              m_tightness;            // determines the movement of the camera -> 1 means tight movement, while 0 means no movement
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||