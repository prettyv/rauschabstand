//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Map.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||


Map::Map(std::string name, Ogre::SceneManager* sceneMgr)
{
	m_name = name;
	m_pSceneMgr = sceneMgr;
	
	m_mapMainNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(m_name);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Map::createRandomMap()
{
	for (unsigned int i = 0; i < LENGTH; i++)
	{
		std::vector<bool> row;
		for (unsigned int j = 0; j < WIDTH; j++)
		{
			bool randomBool = rand() % 2 == 1 ? true : false;
			row.push_back(randomBool);
		}
		m_cubes.push_back(row);
	}

	for (unsigned int i = 0; i < LENGTH; i++) {
		m_quanternions.push_back(
			Ogre::Quaternion(Ogre::Radian(Ogre::Degree(3)), Ogre::Vector3(0, 1, 0)) * 
			Ogre::Quaternion(Ogre::Radian(Ogre::Degree(3)), Ogre::Vector3(0, 0, 1))
		);
	}
	m_quanternions.push_back(Ogre::Quaternion(1, 0, 0, 0));
	
	Ogre::Vector3 pos = Ogre::Vector3(0, 0, 0);
	Ogre::Quaternion quant = Ogre::Quaternion(1, 0, 0, 0);
	for (unsigned int i = 0; i < LENGTH - 1; i++)
	{
		quant = quant * m_quanternions[i];
		Ogre::Quaternion nextQuant = quant * m_quanternions[i + 1];

		for (int x = -250, j = 0; j < WIDTH; j++, x += 50)
		{
			if (/*m_cubes[i][j] == */true)
			{
				Ogre::SceneNode* mNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
				mNode->attachObject(createPlane(x, x + 50, -100, pos, quant, nextQuant));
			}
		}

		pos = pos + quant * Ogre::Vector3(0, 0, -100);
	}  
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Map::update(Ogre::Real elapsedTime)
{
	//empty
}

//|||||||||||||||||||||||||||||||||||||||||||||||

Ogre::ManualObject* Map::createPlane(int left, int right, int back, Ogre::Vector3 pos, 
	Ogre::Quaternion quant, Ogre::Quaternion nextQuant)
{
	Ogre::Vector3 nextPos = pos + quant * Ogre::Vector3(0, 0, back);
	Ogre::Vector3 posMinus50 = pos + quant * Ogre::Vector3(left, 0, 0);
	Ogre::Vector3 posPlus50 = pos + quant * Ogre::Vector3(right, 0, 0);
	Ogre::Vector3 nextPosMinus50 = nextPos + nextQuant * Ogre::Vector3(left, 0, 0);
	Ogre::Vector3 nextPosPlus50 = nextPos + nextQuant * Ogre::Vector3(right, 0, 0);

	Ogre::ManualObject* plane = new Ogre::ManualObject("plane");
	plane->clear();
	plane->begin("");
			plane->position(posMinus50.x, posMinus50.y, posMinus50.z);
			plane->position(nextPosMinus50.x, nextPosMinus50.y, nextPosMinus50.z);
			plane->position(posPlus50.x, posPlus50.y, posPlus50.z);
			plane->position(nextPosPlus50.x, nextPosPlus50.y, nextPosPlus50.z);
			plane->triangle(0, 1, 2);
			plane->triangle(2, 1, 0);
			plane->triangle(1, 3, 2);
			plane->triangle(2, 3, 1);
	plane->end();

	return plane;
}

//|||||||||||||||||||||||||||||||||||||||||||||||