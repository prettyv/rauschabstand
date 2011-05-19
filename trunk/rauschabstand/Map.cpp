//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Map.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

Map::Map(std::string name, SceneManager* sceneMgr)
{
	m_name = name;
	m_pSceneMgr = sceneMgr;

	m_length = 100;
	m_width	= 5;
	
	m_mapMainNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(m_name);
	m_rotationalSpline = Ogre::RotationalSpline();
	m_pointsSpline = Ogre::SimpleSpline();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Map::createRandomMap(int length, int width)
{
	m_length = length;
	m_width	= width;

	for (unsigned int i = 0; i < m_length; i++)
	{
		std::vector<bool> row;
		for (unsigned int j = 0; j < m_width; j++)
		{
			bool randomBool = rand() % 4 != 0 ? true : false;
			row.push_back(randomBool);
		}
		m_cubes.push_back(row);
	}

	Quaternion currentQuaternion = Quaternion(1, 0, 0, 0);
	Vector3 currentPos = Vector3(0, 0, 0);
	for (unsigned int i = 0; i < m_length; i++)
	{
		// not random but smooth..
		//Quaternion inputQuaternion = Quaternion(Ogre::Degree(3), Vector3(0, 0, 1)) * 
			//Quaternion(Ogre::Degree(3), Vector3(0, 1, 0));

		// true random TODO: needs smoothing
		Vector3 quanternionAxis = Vector3(rand() % 10, rand() % 10, rand() % 10);
		quanternionAxis.normalise();
		Quaternion inputQuaternion = Quaternion(Ogre::Degree(rand() % 3), quanternionAxis);

		currentQuaternion = currentQuaternion * inputQuaternion;
		m_rotationalSpline.addPoint(currentQuaternion);
		m_pointsSpline.addPoint(currentPos);
		currentPos += currentQuaternion * Ogre::Vector3(0, 0, -100);
	}
	m_rotationalSpline.addPoint(currentQuaternion);
	m_pointsSpline.addPoint(currentPos);

	Ogre::ManualObject* plane = new Ogre::ManualObject("plane");
	plane->estimateIndexCount(m_length * m_width * 4);
	plane->estimateVertexCount(m_length * m_width * 4);
	plane->clear();
	plane->begin("");
	
	Ogre::Vector3 pos = Ogre::Vector3(0, 0, 0);
	Ogre::Quaternion quant;
	Ogre::Quaternion nextQuant;
	for (unsigned int i = 0; i < m_length; i++)
	{
		quant = m_rotationalSpline.getPoint(i);
		nextQuant = m_rotationalSpline.getPoint(i + 1);

		for (int x = -100 * (m_width / (double) 2), j = 0; j < m_width; j++, x += 100)
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

		pos = pos + quant * Ogre::Vector3(0, 0, -100);
	}  

	for (int i = 0; i < m_width * m_length; i++)
	{
		if (m_cubes[i / (double) width][i % width])
		{
			plane->triangle(0 + i * 4, 1 + i * 4, 2 + i * 4);
			plane->triangle(2 + i * 4, 1 + i * 4, 0 + i * 4);
			plane->triangle(1 + i * 4, 3 + i * 4, 2 + i * 4);
			plane->triangle(2 + i * 4, 3 + i * 4, 1 + i * 4);
		}
	}

	plane->end();

	m_mapMainNode->attachObject(plane);

	MeshPtr ptr = plane->convertToMesh("planeMesh");
	Entity* planeEntity = m_pSceneMgr->createEntity("planeEntity", "planeMesh");
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Map::update(Ogre::Real elapsedTime, OIS::Keyboard *input)
{

	//TODO: remove function if not needed..

	/*if (input->isKeyDown (OIS::KC_N))
	{
		m_t = m_t >= MAPLENGTH ? MAPLENGTH : m_t + 1;
	}
	if (input->isKeyDown (OIS::KC_M))
	{
		m_t = m_t <= 0 ? 0 : m_t - 1;
	}*/

	/*m_mapMainNode->getChild("planeNode")->setPosition(
		m_rotationalSpline.interpolate(m_t, 0, true).Inverse() * Vector3(0, 0, m_t * 100));
	m_mapMainNode->getChild("planeNode")->setOrientation(
		m_rotationalSpline.interpolate(m_t, 0, true).Inverse());*/

	/*if (input->isKeyDown (OIS::KC_W))
	{
		m_mapMainNode->translate(m_mapMainNode->getOrientation() * Vector3(0, 0, 1. * elapsedTime));
		m_t += elapsedTime / 100;

		//float t = m_t < LENGTH ? m_t < 0 ? 0 : m_t : LENGTH - 1;
		//m_mapMainNode->setOrientation(m_rotationalSpline.interpolate(t, true));
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
	}*/
}

//|||||||||||||||||||||||||||||||||||||||||||||||

Ogre::Quaternion Map::getOrientation(double t)
{
	if ( t < 0)
	{
		t = 0;
	} else if (t >= m_length)
	{
		t = m_length - 1;
	}
	int index = t;
	t -= index;
	return m_rotationalSpline.interpolate(index, t, true);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

Ogre::Vector3 Map::getPosition(double t, double u)
{
	if ( t < 0)
	{
		t = 0;
	} else if (t >= m_length)
	{
		t = m_length - 1;
	}
	int index = (int) t;
	double t2 = t - index;
	Ogre::Vector3 tPos = m_pointsSpline.interpolate(index, t2);
	Ogre::Quaternion quant = getOrientation(t);
	
	return tPos + quant * Ogre::Vector3(u, 0, 0);
}

//|||||||||||||||||||||||||||||||||||||||||||||||