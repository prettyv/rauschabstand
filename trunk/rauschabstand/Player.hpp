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

	void update(Ogre::Real elapsedTime, Real m_t, Real m_u);
    void update(Ogre::Real elapsedTime, OIS::Keyboard *input);
	void keyReleased (Real elapsedTime, const OIS::KeyEvent& keyEvt);

	void jump(Real elapsedTime, Real t, Real u);
	void resetToStart();

	Real getJumpHeight() { return m_jumpNode->getPosition().y; }

private:
	
	void updateCamera(Real t);
public:

	// player
	Ogre::SceneNode*				m_playerMainNode;		// for time position (t) and orienation
	Ogre::SceneNode*				m_sideNode;				// for side position (u)
	Ogre::SceneNode*				m_jumpNode;				// for up position (jumping)
	Ogre::SceneNode*				m_sideRollNode;			// for rolling while steering
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

	static const int				THROUGHHOLEHEIGHT = 0;	// height when fallen through Hole
	bool							m_throughHole;			// true when player has fallen through hole
	bool							m_jumping;				// true when player jumping

	// for side-roll movement while steering
	float							m_rollFactor;			// rolling intensity
	bool							m_rollBack;				// signalizes that the player stopped steering and the model should roll-back
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||