//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef MAP_HPP
#define MAP_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include <string>
#include <vector>
#include <sstream>

#include "AdvancedOgreFramework.hpp"
#include "OgreBulletCollision.hpp"

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

//|||||||||||||||||||||||||||||||||||||||||||||||

class Map
{
public:
	Map(std::string name, Ogre::SceneManager* sceneMgr, OgreBulletCollision* ogreBulletMain);

	void createRandomMap();
	void update(Ogre::Real elapsedTime, OIS::Keyboard *input);

	void setPosition(Ogre::Vector3 pos);

private:
	static const int				MAPLENGTH = 30;
	static const int				MAPWIDTH = 5;

	std::vector<std::vector<bool>>	m_cubes;
	Ogre::RotationalSpline			m_rotationalSpline;
	
    Ogre::SceneManager*				m_pSceneMgr;

    Ogre::SceneNode*				m_mapMainNode;
    std::string						m_name;

	float							m_t;
	OgreBulletCollision*			m_ogreBulletMain;

	OgreBulletDynamics::RigidBody*	m_rigidBody;
};


//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||