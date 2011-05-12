//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Map.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

Map::Map(std::string name, SceneManager* sceneMgr, OgreBulletCollision* ogreBulletMain)
{
	m_name = name;
	m_pSceneMgr = sceneMgr;
	
	m_mapMainNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(m_name);

	m_t = 0;
	m_ogreBulletMain = ogreBulletMain;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Map::createRandomMap()
{
	for (unsigned int i = 0; i < MAPLENGTH; i++)
	{
		std::vector<bool> row;
		for (unsigned int j = 0; j < MAPWIDTH; j++)
		{
			bool randomBool = rand() % 2 == 1 ? true : false;
			row.push_back(randomBool);
		}
		m_cubes.push_back(row);
	}

	for (unsigned int i = 0; i < MAPLENGTH; i++)
	{
		m_rotationalSpline.addPoint(
			Quaternion(Ogre::Degree(3), Vector3(0, 1, 0)) * 
			Quaternion(Ogre::Degree(3), Vector3(0, 0, 1))
		);
	}
	m_rotationalSpline.addPoint(Ogre::Quaternion(1, 0, 0, 0));


	Ogre::SceneNode* mNode = m_mapMainNode->createChildSceneNode();
	Ogre::ManualObject* plane = new Ogre::ManualObject("plane");
	plane->estimateIndexCount(MAPLENGTH * MAPWIDTH * 4);
	plane->estimateVertexCount(MAPLENGTH * MAPWIDTH * 4);
	plane->clear();
	plane->begin("");
	
	Ogre::Vector3 pos = Ogre::Vector3(0, 0, 0);
	Ogre::Quaternion quant = Ogre::Quaternion(1, 0, 0, 0);
	for (unsigned int i = 0; i < MAPLENGTH; i++)
	{
		quant = quant * m_rotationalSpline.getPoint(i);
		Ogre::Quaternion nextQuant = quant * m_rotationalSpline.getPoint(i + 1);

		for (int x = -250, j = 0; j < MAPWIDTH; j++, x += 50)
		{
			if (/*m_cubes[i][j] == */true)
			{
				int back = -100;
				int left = x;
				int right = x + 100;

				Ogre::Vector3 nextPos = pos + quant * Ogre::Vector3(0, 0, back);
				Ogre::Vector3 posMinus50 = pos + quant * Ogre::Vector3(left, 0, 0);
				Ogre::Vector3 posPlus50 = pos + quant * Ogre::Vector3(right, 0, 0);
				Ogre::Vector3 nextPosMinus50 = nextPos + nextQuant * Ogre::Vector3(left, 0, 0);
				Ogre::Vector3 nextPosPlus50 = nextPos + nextQuant * Ogre::Vector3(right, 0, 0);

				plane->position(posMinus50.x, posMinus50.y, posMinus50.z);
				plane->position(nextPosMinus50.x, nextPosMinus50.y, nextPosMinus50.z);
				plane->position(posPlus50.x, posPlus50.y, posPlus50.z);
				plane->position(nextPosPlus50.x, nextPosPlus50.y, nextPosPlus50.z);
			}
		}

		pos = pos + quant * Ogre::Vector3(0, 0, -100);
	}  

	for (int i = 0; i < MAPWIDTH * MAPLENGTH; i++)
	{
		plane->triangle(0 + i * 4, 1 + i * 4, 2 + i * 4);
		plane->triangle(2 + i * 4, 1 + i * 4, 0 + i * 4);
		plane->triangle(1 + i * 4, 3 + i * 4, 2 + i * 4);
		plane->triangle(2 + i * 4, 3 + i * 4, 1 + i * 4);
	}

	plane->end();

	//mNode->attachObject(plane);

	MeshPtr ptr = plane->convertToMesh("planeMesh");
	Entity* planeEntity = m_pSceneMgr->createEntity("planeEntity", "planeMesh");

	m_ogreBulletMain->addStaticTrimesh("sceneMesh",
		"planeMesh",
		Ogre::Vector3(0, 0, 0), 
		Quaternion::IDENTITY,
		0.1f, 
		0.8f,
		true);
	
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