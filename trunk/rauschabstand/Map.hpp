//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef MAP_HPP
#define MAP_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include <string>
#include <vector>
#include <sstream>

#include "AdvancedOgreFramework.hpp"

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

class Map
{
public:
	Map(std::string name, Ogre::SceneManager* sceneMgr);

	void createRandomMap(int length, int width);
	void update(Ogre::Real elapsedTime, OIS::Keyboard *input);

	Ogre::Quaternion getOrientation(double t);
	Ogre::Vector3 getPosition(double t, double u);

private:
	int	m_length;
	int	m_width;

	std::vector<std::vector<bool>>	m_cubes;
	Ogre::RotationalSpline			m_rotationalSpline;
	Ogre::SimpleSpline				m_pointsSpline;
	
    Ogre::SceneManager*				m_pSceneMgr;

    Ogre::SceneNode*				m_mapMainNode;
    std::string						m_name;
};


//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||