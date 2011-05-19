//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef PLAYER_HPP
#define PLAYER_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include <string>

#include "AdvancedOgreFramework.hpp"
#include "Map.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

class Player {
public:
    Player(std::string name, Ogre::SceneManager* sceneMgr, Ogre::Camera* camera, Map* map);

	void update(double elapsedTime);
    void update(Ogre::Real elapsedTime, OIS::Keyboard *input);

private:
	
	void updateCamera();

public:

	// player
	Ogre::SceneNode*				m_playerMainNode;		// for time position (t) and orienation
	Ogre::SceneNode*				m_sideNode;				// for side position (u)
	Ogre::SceneNode*				m_jumpNode;				// for up position (jumping)
	Ogre::Entity*					m_playerEntity;

private:
    Ogre::SceneManager*				m_pSceneMgr;

    // player
    std::string						m_name;                 // name of the player
    Ogre::SceneNode*				m_cameraPosition;       // representing the camera position relative to the player -> changes automatically when player is moved
    Ogre::SceneNode*				m_targetPosition;       // representing the camera target relative to the player -> changes automatically when player is moved

    // camera
    Ogre::SceneNode*				m_cameraTarget;         // actual target of the camera
    Ogre::SceneNode*				m_chaseCamera;          // actual cameraNode
    Ogre::Camera*					m_camera;               // actual camera
    Ogre::Real						m_tightness;            // determines the movement of the camera -> 1 means tight movement, while 0 means no movement

	Map*							m_map;

	Ogre::Vector3					m_speed;				// speed vector
	double							m_t;					// position on map
	double							m_u;
	double							m_mass;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||