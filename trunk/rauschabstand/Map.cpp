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

void Map::createRandomMap(unsigned int length, unsigned int width)
{
	m_length = length;
	m_width	= width;

	for (unsigned int i = 0; i < m_length; i++)
	{
		std::vector<HolesOrObstacles> row;
		for (unsigned int j = 0; j < m_width; j++)
		{
			HolesOrObstacles randomBool = rand() % 8 != 0 ? NORMAL : HOLE;
			randomBool = rand() % 20 == 0 ? OBSTACLE : randomBool;
			row.push_back(randomBool);
		}
		m_cubes.push_back(row);
	}

	std::vector<TimeQuaternion> timeQuaternions;
	TimeQuaternion timeQuat;
	timeQuat.m_t = 0;
	timeQuat.m_quanternion = Quaternion(1, 0, 0, 0);
	timeQuaternions.push_back(timeQuat);
	TimeQuaternion timeQuat2;
	timeQuat2.m_t = 20;
	timeQuat2.m_quanternion = Quaternion(1, 0, 0, 0);
	timeQuaternions.push_back(timeQuat2);
	TimeQuaternion timeQuat3;
	timeQuat3.m_t = 100;
	timeQuat3.m_quanternion = Quaternion(Degree(90), Vector3(1, 0, 0));
	timeQuaternions.push_back(timeQuat3);
	TimeQuaternion timeQuat4;
	timeQuat4.m_t = 150;
	timeQuat4.m_quanternion = Quaternion(Degree(90), Vector3(0, 0, 1));
	timeQuaternions.push_back(timeQuat4);
	TimeQuaternion timeQuat5;
	timeQuat5.m_t = 200;
	timeQuat5.m_quanternion = Quaternion(Degree(-90), Vector3(0, 1, 0));
	timeQuaternions.push_back(timeQuat5);

	for (unsigned int i = 0; i < timeQuaternions.size() - 1; i++)
	{
		timeQuaternions[i + 1].m_quanternion = timeQuaternions[i].m_quanternion * timeQuaternions[i + 1].m_quanternion;
	}

	Vector3 currentPos = Vector3(0, 0, 0);
	for (unsigned int i = 0; i < timeQuaternions.size() - 1; i++)
	{
		TimeQuaternion from = timeQuaternions[i];
		TimeQuaternion to = timeQuaternions[i + 1];
		float slerpFactor = 0;
		for (unsigned int t = from.m_t; t < to.m_t; t++)
		{
			slerpFactor += 1 / (float) (to.m_t - from.m_t);
			Quaternion inputQuaternion = Quaternion::Slerp(slerpFactor, from.m_quanternion, to.m_quanternion, false);

			m_rotationalSpline.addPoint(inputQuaternion);
			m_pointsSpline.addPoint(currentPos);
			currentPos += inputQuaternion * Ogre::Vector3(0, 0, -100);
		}
	}
	m_rotationalSpline.addPoint(m_rotationalSpline.getPoint(m_rotationalSpline.getNumPoints() - 1));
	m_pointsSpline.addPoint(currentPos);

	Ogre::ManualObject* plane = new Ogre::ManualObject("plane");
	plane->estimateIndexCount(m_length * m_width * 4);
	plane->estimateVertexCount(m_length * m_width * 4);
	plane->clear();
	plane->begin("Examples/Rockwall");
	
	Ogre::Vector3 pos = Ogre::Vector3(0, 0, 0);
	Ogre::Quaternion quat;
	Ogre::Quaternion nextQuat;
	unsigned long planeNum = 0;
	for (unsigned int i = 0; i < m_length; i++)
	{
		quat = m_rotationalSpline.getPoint(i);
		nextQuat = m_rotationalSpline.getPoint(i + 1);

		for (int x = -100 * (m_width / (double) 2), j = 0; j < m_width; j++, x += 100)
		{
			int back = -100;
			int left = x;
			int right = x + 100;
			int down = -100;
			int up = 100;

			Ogre::Vector3 nextPos = pos + quat * Ogre::Vector3(0, 0, back);
			Ogre::Vector3 posMinus50 = pos + quat * Ogre::Vector3(left, 0, 0);
			Ogre::Vector3 posPlus50 = pos + quat * Ogre::Vector3(right, 0, 0);
			Ogre::Vector3 nextPosMinus50 = nextPos + nextQuat * Ogre::Vector3(left, 0, 0);
			Ogre::Vector3 nextPosPlus50 = nextPos + nextQuat * Ogre::Vector3(right, 0, 0);

			plane->position(posMinus50.x, posMinus50.y, posMinus50.z); plane->normal((quat * Vector3(0, 1, 0)).normalisedCopy()); plane->textureCoord(0, 0);
			plane->position(nextPosMinus50.x, nextPosMinus50.y, nextPosMinus50.z); plane->normal((quat * Vector3(0, 1, 0)).normalisedCopy()); plane->textureCoord(0, 1);
			plane->position(posPlus50.x, posPlus50.y, posPlus50.z); plane->normal((quat * Vector3(0, 1, 0)).normalisedCopy()); plane->textureCoord(1, 0);
			plane->position(nextPosPlus50.x, nextPosPlus50.y, nextPosPlus50.z); plane->normal((quat * Vector3(0, 1, 0)).normalisedCopy()); plane->textureCoord(1, 1);

			Ogre::Vector3 nextPosDown = nextPos + quat * Ogre::Vector3(0, down, 0);
			Ogre::Vector3 posMinus50Down = posMinus50 + quat * Ogre::Vector3(0, down, 0);
			Ogre::Vector3 posPlus50Down = posPlus50 + quat * Ogre::Vector3(0, down, 0);
			Ogre::Vector3 nextPosMinus50Down = nextPosMinus50 + nextQuat * Ogre::Vector3(0, down, 0);
			Ogre::Vector3 nextPosPlus50Down = nextPosPlus50 + nextQuat * Ogre::Vector3(0, down, 0);

			plane->position(posMinus50Down.x, posMinus50Down.y, posMinus50Down.z); plane->normal((quat * Vector3(0, -1, 0)).normalisedCopy()); plane->textureCoord(0, 0);
			plane->position(nextPosMinus50Down.x, nextPosMinus50Down.y, nextPosMinus50Down.z); plane->normal((quat * Vector3(0, -1, 0)).normalisedCopy()); plane->textureCoord(0, 1);
			plane->position(posPlus50Down.x, posPlus50Down.y, posPlus50Down.z); plane->normal((quat * Vector3(0, -1, 0)).normalisedCopy()); plane->textureCoord(1, 0);
			plane->position(nextPosPlus50Down.x, nextPosPlus50Down.y, nextPosPlus50Down.z); plane->normal((quat * Vector3(0, -1, 0)).normalisedCopy()); plane->textureCoord(1, 1);

			Ogre::Vector3 nextPosUp = nextPos + quat * Ogre::Vector3(0, up, 0);
			Ogre::Vector3 posMinus50Up = posMinus50 + quat * Ogre::Vector3(0, up, 0);
			Ogre::Vector3 posPlus50Up = posPlus50 + quat * Ogre::Vector3(0, up, 0);
			Ogre::Vector3 nextPosMinus50Up = nextPosMinus50 + nextQuat * Ogre::Vector3(0, up, 0);
			Ogre::Vector3 nextPosPlus50Up = nextPosPlus50 + nextQuat * Ogre::Vector3(0, up, 0);

			plane->position(posMinus50Up.x, posMinus50Up.y, posMinus50Up.z); plane->normal((quat * Vector3(-1, 1, 1)).normalisedCopy()); plane->textureCoord(0, 0);
			plane->position(nextPosMinus50Up.x, nextPosMinus50Up.y, nextPosMinus50Up.z); plane->normal((quat * Vector3(-1, 1, -1)).normalisedCopy()); plane->textureCoord(0, 1);
			plane->position(posPlus50Up.x, posPlus50Up.y, posPlus50Up.z); plane->normal((quat * Vector3(1, 1, 1)).normalisedCopy()); plane->textureCoord(1, 0);
			plane->position(nextPosPlus50Up.x, nextPosPlus50Up.y, nextPosPlus50Up.z); plane->normal((quat * Vector3(1, 1, -1)).normalisedCopy()); plane->textureCoord(1, 1);

			if (m_cubes[planeNum / (double) width][planeNum % width] != HOLE)
			{
				plane->triangle(0 + planeNum * 12, 1 + planeNum * 12, 2 + planeNum * 12);
				plane->normal(quat * Vector3(0, 1, 0));
				plane->triangle(2 + planeNum * 12, 1 + planeNum * 12, 0 + planeNum * 12);
				plane->normal(quat * Vector3(0, 1, 0));
				plane->triangle(1 + planeNum * 12, 3 + planeNum * 12, 2 + planeNum * 12);
				plane->normal(quat * Vector3(0, 1, 0));
				plane->triangle(2 + planeNum * 12, 3 + planeNum * 12, 1 + planeNum * 12);
				plane->normal(quat * Vector3(0, 1, 0));

				/*plane->triangle(4 + planeNum * 8, 5 + planeNum * 8, 6 + planeNum * 8);
				plane->triangle(6 + planeNum * 8, 5 + planeNum * 8, 4 + planeNum * 8);
				plane->triangle(5 + planeNum * 8, 7 + planeNum * 8, 6 + planeNum * 8);
				plane->triangle(6 + planeNum * 8, 7 + planeNum * 8, 5 + planeNum * 8);*/
			}
			if (m_cubes[planeNum / (double) width][planeNum % width] == OBSTACLE)
			{
				//top
				plane->triangle(8 + planeNum * 12, 9 + planeNum * 12, 10 + planeNum * 12);
				plane->normal(quat * Vector3(0, 1, 0));
				plane->triangle(10 + planeNum * 12, 9 + planeNum * 12, 8 + planeNum * 12);
				plane->normal(quat * Vector3(0, 1, 0));
				plane->triangle(9 + planeNum * 12, 11 + planeNum * 12, 10 + planeNum * 12);
				plane->normal(quat * Vector3(0, 1, 0));
				plane->triangle(10 + planeNum * 12, 11 + planeNum * 12, 9 + planeNum * 12);
				plane->normal(quat * Vector3(0, 1, 0));

				//left
				plane->triangle(0 + planeNum * 12, 8 + planeNum * 12, 9 + planeNum * 12);
				plane->normal(quat * Vector3(-1, 0, 0));
				plane->triangle(9 + planeNum * 12, 8 + planeNum * 12, 0 + planeNum * 12);
				plane->normal(quat * Vector3(-1, 0, 0));
				plane->triangle(0 + planeNum * 12, 1 + planeNum * 12, 9 + planeNum * 12);
				plane->normal(quat * Vector3(-1, 0, 0));
				plane->triangle(9 + planeNum * 12, 1 + planeNum * 12, 0 + planeNum * 12);
				plane->normal(quat * Vector3(-1, 0, 0));

				//right
				plane->triangle(2 + planeNum * 12, 10 + planeNum * 12, 11 + planeNum * 12);
				plane->normal(quat * Vector3(1, 0, 0));
				plane->triangle(11 + planeNum * 12, 10 + planeNum * 12, 2 + planeNum * 12);
				plane->normal(quat * Vector3(1, 0, 0));
				plane->triangle(2 + planeNum * 12, 3 + planeNum * 12, 11 + planeNum * 12);
				plane->normal(quat * Vector3(1, 0, 0));
				plane->triangle(11 + planeNum * 12, 3 + planeNum * 12, 2 + planeNum * 12);
				plane->normal(quat * Vector3(1, 0, 0));

				//back
				plane->triangle(9 + planeNum * 12, 11 + planeNum * 12, 1 + planeNum * 12);
				plane->normal(quat * Vector3(0, 0, -1));
				plane->triangle(1 + planeNum * 12, 11 + planeNum * 12, 9 + planeNum * 12);
				plane->normal(quat * Vector3(0, 0, -1));
				plane->triangle(1 + planeNum * 12, 3 + planeNum * 12, 11 + planeNum * 12);
				plane->normal(quat * Vector3(0, 0, -1));
				plane->triangle(11 + planeNum * 12, 3 + planeNum * 12, 1 + planeNum * 12);
				plane->normal(quat * Vector3(0, 0, -1));

				//back
				plane->triangle(2 + planeNum * 12, 10 + planeNum * 12, 8 + planeNum * 12);
				plane->normal(quat * Vector3(0, 0, 1));
				plane->triangle(8 + planeNum * 12, 10 + planeNum * 12, 2 + planeNum * 12);
				plane->normal(quat * Vector3(0, 0, 1));
				plane->triangle(0 + planeNum * 12, 8 + planeNum * 12, 2 + planeNum * 12);
				plane->normal(quat * Vector3(0, 0, 1));
				plane->triangle(2 + planeNum * 12, 8 + planeNum * 12, 0 + planeNum * 12);
				plane->normal(quat * Vector3(0, 0, 1));
			}
			planeNum++;
		}

		pos = pos + quat * Ogre::Vector3(0, 0, -100);
	}  

	/*for (int i = 0; i < m_width * m_length; i++)
	{
		if (m_cubes[i / (double) width][i % width])
		{
			plane->triangle(0 + i * 4, 1 + i * 4, 2 + i * 4);
			plane->triangle(2 + i * 4, 1 + i * 4, 0 + i * 4);
			plane->triangle(1 + i * 4, 3 + i * 4, 2 + i * 4);
			plane->triangle(2 + i * 4, 3 + i * 4, 1 + i * 4);
		}
	}*/

	plane->end();
	plane->setCastShadows(false);

	m_mapMainNode->attachObject(plane);

	MeshPtr ptr = plane->convertToMesh("planeMesh");
	Entity* planeEntity = m_pSceneMgr->createEntity("planeEntity", "planeMesh");
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
	t = t < 0 ? 0 : t;
	t = t >= m_length ? m_length - 1 : t;
	int index = (int) t;
	double t2 = t - index;
	Ogre::Vector3 tPos = m_pointsSpline.interpolate(index, t2);
	Ogre::Quaternion quant = getOrientation(t);
	
	return tPos + quant * Ogre::Vector3(u, 0, 0);
}

//|||||||||||||||||||||||||||||||||||||||||||||||


bool Map::isHoleInMap(double t, double u)
{
	t = t < 0 ? 0 : t;
	t = t >= m_length ? m_length - 1 : t;

	//TODO: wtf, fix this mess!
	int j = u + (m_width / (double) 2) * 100;
	j /= (double) 100;
	j = m_width - j;
	j -= 1;
	j = j < 0 ? 0 : j;
	j = j > m_width ? m_width : j;

	return m_cubes.at(t).at(j) == HOLE;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool Map::isCloseToHole(double t, double u, double closeDistance)
{
	t = t < 0 ? 0 : t;
	t = t >= m_length ? m_length - 1 : t;
	std::vector<HolesOrObstacles> row = m_cubes[t];

	//TODO: wtf, fix this mess!
	double j = u + (m_width / (double) 2) * 100;
	j /= (double) 100;
	j = m_width - j;
	j -= 1;
	j = j < 0 ? 0 : j;
	j = j > m_width ? m_width : j;

	u = u + (m_width / (double) 2) * 100;
	u = m_width * 100 - u;
	u = u < 0 ? 0 : u;
	u = u > m_width * 100 ? m_width * 100 : u;

	if (row[j] == HOLE)
	{
		return false;
	}

	int minDistance = 10000;
	for (int i = 0; i < row.size(); i++)
	{
		if (row[i] == HOLE)
		{
			int distance = abs(u - i * 100);
			if (distance < closeDistance)
			{
				return true;
			}
		}
	}

	return false;
}

//|||||||||||||||||||||||||||||||||||||||||||||||