//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Map.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

Map::Map(std::string name, SceneManager* sceneMgr)
{
	m_name = name;
	m_pSceneMgr = sceneMgr;
	
	m_mapMainNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(m_name);

	m_t = 0;
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

	for (unsigned int i = 0; i < LENGTH; i++)
	{
		m_rotationalSpline.addPoint(
			Quaternion(Ogre::Degree(3), Vector3(0, 1, 0)) * 
			Quaternion(Ogre::Degree(3), Vector3(0, 0, 1))
		);
	}
	m_rotationalSpline.addPoint(Ogre::Quaternion(1, 0, 0, 0));
	
	Ogre::Vector3 pos = Ogre::Vector3(0, 0, 0);
	Ogre::Quaternion quant = Ogre::Quaternion(1, 0, 0, 0);
	for (unsigned int i = 0; i < LENGTH - 1; i++)
	{
		quant = quant * m_rotationalSpline.getPoint(i);
		Ogre::Quaternion nextQuant = quant * m_rotationalSpline.getPoint(i + 1);

		for (int x = -250, j = 0; j < WIDTH; j++, x += 50)
		{
			if (/*m_cubes[i][j] == */true)
			{
				Ogre::SceneNode* mNode = m_mapMainNode->createChildSceneNode();
				mNode->attachObject(createPlane(x, x + 50, -100, pos, quant, nextQuant));
			}
		}

		pos = pos + quant * Ogre::Vector3(0, 0, -100);
	}  
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Map::update(Ogre::Real elapsedTime, OIS::Keyboard *input)
{
	if (input->isKeyDown (OIS::KC_W))
	{
		m_mapMainNode->translate(m_mapMainNode->getOrientation() * Vector3(0, 0, 1. * elapsedTime));
		m_t += elapsedTime / 100;

		/*float t = m_t < LENGTH ? m_t < 0 ? 0 : m_t : LENGTH - 1;
		m_mapMainNode->setOrientation(m_rotationalSpline.interpolate(t, true));*/
	}
	if (input->isKeyDown (OIS::KC_S))
	{
		m_mapMainNode->translate(m_mapMainNode->getOrientation() * Vector3(0, 0, -1 * elapsedTime));
		m_t -= elapsedTime / 100;
		//m_mapMainNode->rotate(m_quanternions[(int) m_t]);
	}
	if (input->isKeyDown (OIS::KC_A))
	{
		m_mapMainNode->translate(m_mapMainNode->getOrientation() * Vector3(0.5 * elapsedTime, 0, 0));
	}
	if (input->isKeyDown (OIS::KC_D))
	{
		m_mapMainNode->translate(m_mapMainNode->getOrientation() * Vector3(-0.5 * elapsedTime, 0, 0));
	}
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