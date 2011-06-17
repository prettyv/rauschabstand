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

struct TimeQuaternion
{
	unsigned int m_t;
	Quaternion m_quanternion;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

class Map
{
public:
	Map(std::string name, Ogre::SceneManager* sceneMgr);

	void createRandomMap(unsigned int length, unsigned int width);

	Ogre::Quaternion getOrientation(double t);
	Ogre::Vector3 getPosition(double t, double u);

	bool isHoleInMap(double t, double u);

	int getLength() { return m_length; }
	int getWidth() { return m_width; }

private:
	int	m_length;
	int	m_width;

	std::vector<std::vector<bool> >	m_cubes;
	RotationalSpline				m_rotationalSpline;
	SimpleSpline					m_pointsSpline;
	
    SceneManager*					m_pSceneMgr;

    SceneNode*						m_mapMainNode;
    std::string						m_name;
};


//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||