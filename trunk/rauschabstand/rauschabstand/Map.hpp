//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef MAP_HPP
#define MAP_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include <string>
#include <vector>
#include <sstream>

#include "AdvancedOgreFramework.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||


class Map
{
public:
	Map(std::string name, Ogre::SceneManager* sceneMgr);

	void createRandomMap();
	void update(Ogre::Real elapsedTime);

private:
	Ogre::ManualObject* createPlane(int left, int right, int back, Ogre::Vector3 pos, 
		Ogre::Quaternion quant, Ogre::Quaternion nextQuant);

private:
	static const int				WIDTH = 5;
	static const int				LENGTH = 20;

	std::vector<std::vector<bool>>	m_cubes;
	std::vector<Ogre::Quaternion>	m_quanternions;
	
    Ogre::SceneManager*				m_pSceneMgr;

    Ogre::SceneNode*				m_mapMainNode;
    std::string						m_name;                 // name of the player
};


//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||