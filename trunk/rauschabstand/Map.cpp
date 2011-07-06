//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Map.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

Map::Map(std::string name, SceneManager* sceneMgr, 
	unsigned int length, unsigned int width)
{
	m_name = name;
	m_pSceneMgr = sceneMgr;
	m_length = length;
	m_width	= width;
	
	m_mapMainNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(m_name);
	m_rotationalSpline = Ogre::RotationalSpline();
	m_pointsSpline = Ogre::SimpleSpline();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Map::resetCubes() 
{
	m_cubes.clear();
	for (unsigned int i = 0; i < m_length; i++)
	{
		std::vector<HolesOrObstacles> row;
		for (unsigned int j = 0; j < m_width; j++)
		{
			row.push_back(NORMAL);
		}
		m_cubes.push_back(row);
	}
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Map::setCubesRow(int start, unsigned int length, HolesOrObstacles holeOrObstacle) 
{
	start = start < 0 ? m_length + start : start;

	std::vector<HolesOrObstacles> row;
	for (unsigned int i = 0; i < m_width; i++)
	{
		row.push_back(holeOrObstacle);
	}
	for (unsigned int i = start; i < start + length && i < m_length; i++)
	{
		m_cubes[i] = row;
	}
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Map::setCubes(int start, unsigned int length, int startV, unsigned int width, HolesOrObstacles holeOrObstacle)
{
	start = start < 0 ? m_length + start : start;
	startV = startV < 0 ? m_width + startV : startV;

	for (unsigned int i = start; i < start + length && i < m_length; i++)
	{
		std::vector<HolesOrObstacles> row = m_cubes[i];
		for (unsigned int j = startV; j < startV + width && j < m_width; j++)
		{
			row[j] = holeOrObstacle;
		}
		m_cubes[i] = row;
	}
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Map::setCubesRadius(int x, int y, unsigned int radius, HolesOrObstacles holeOrObstacle) 
{
	//x = x < 0 ? m_length + x : x;

	int start = x - radius - 1 < 0 ? 0 : x - radius - 1;
	for (unsigned int i = start; i < x + radius + 1 && i < m_length; i++) {
		std::vector<HolesOrObstacles> row = m_cubes[i];
		for (unsigned int j = 0; j < m_width; j++)
		{
			if (pow((double) i - (double) x, 2) + pow((double) j - (double) y, 2) <= pow((double) radius, 2))
			{
				row[j] = holeOrObstacle;
			}
		}
		m_cubes[i] = row;
	}
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Map::setTimeQuaternions() 
{
	TimeQuaternion timeQuat;
	timeQuat.m_t = 0;
	timeQuat.m_quanternion = Quaternion(1, 0, 0, 0);
	m_timeQuaternions.push_back(timeQuat);

	TimeQuaternion timeQuat1;
	TimeQuaternion timeQuat2;
	TimeQuaternion timeQuat3;
	TimeQuaternion timeQuat4;
	TimeQuaternion timeQuat5;
	TimeQuaternion timeQuat6;
	TimeQuaternion timeQuat7;

	timeQuat.m_t = 212;
	timeQuat.m_quanternion = Quaternion(1, 0, 0, 0);
	m_timeQuaternions.push_back(timeQuat);

	timeQuat1.m_t = 220;
	timeQuat1.m_quanternion = Quaternion(Degree(5), Vector3(1, 0, 0));
	m_timeQuaternions.push_back(timeQuat1);
	timeQuat2.m_t = 224;
	timeQuat2.m_quanternion = Quaternion(Degree(-10), Vector3(1, 0, 0));
	m_timeQuaternions.push_back(timeQuat2);
	timeQuat3.m_t = 232;
	timeQuat3.m_quanternion = Quaternion(Degree(10), Vector3(1, 0, 0));
	m_timeQuaternions.push_back(timeQuat3);
	timeQuat4.m_t = 236;
	timeQuat4.m_quanternion = Quaternion(Degree(-10), Vector3(1, 0, 0));
	m_timeQuaternions.push_back(timeQuat4);
	timeQuat4.m_t = 244;
	timeQuat4.m_quanternion = Quaternion(Degree(10), Vector3(1, 0, 0));
	m_timeQuaternions.push_back(timeQuat4);
	timeQuat4.m_t = 248;
	timeQuat4.m_quanternion = Quaternion(Degree(-10), Vector3(1, 0, 0));
	m_timeQuaternions.push_back(timeQuat4);

	timeQuat.m_t = 256;
	timeQuat.m_quanternion = Quaternion(1, 0, 0, 0);
	m_timeQuaternions.push_back(timeQuat);

	/*
	Raise(m_timeQuaternions, 3, 4, timeQuat1, timeQuat2, timeQuat3, timeQuat4);
	mediumRaise(m_timeQuaternions, 15, 48, timeQuat1, timeQuat2);
	Raise(m_timeQuaternions, 3, 59, timeQuat1, timeQuat2, timeQuat3, timeQuat4);
	mediumRaise(m_timeQuaternions, 15, 105, timeQuat1, timeQuat2);
	Raise(m_timeQuaternions, 3, 115, timeQuat1, timeQuat2, timeQuat3, timeQuat4);
	mediumRaise(m_timeQuaternions, 15, 160, timeQuat1, timeQuat2);

	sideRollUp(m_timeQuaternions, 60, 170, timeQuat1, timeQuat2);

	Raise(m_timeQuaternions, 3, 235, timeQuat1, timeQuat2, timeQuat3, timeQuat4);
	mediumRaise(m_timeQuaternions, 15, 281, timeQuat1, timeQuat2);
	Raise(m_timeQuaternions, 3, 292, timeQuat1, timeQuat2, timeQuat3, timeQuat4);
	mediumRaise(m_timeQuaternions, 15, 338, timeQuat1, timeQuat2);
	Raise(m_timeQuaternions, 3, 349, timeQuat1, timeQuat2, timeQuat3, timeQuat4);
	mediumRaise(m_timeQuaternions, 15, 394, timeQuat1, timeQuat2);

	sideRollDown(m_timeQuaternions, 60, 404, timeQuat1, timeQuat2);

	Raise(m_timeQuaternions, 3, 469, timeQuat1, timeQuat2, timeQuat3, timeQuat4);
	mediumRaise(m_timeQuaternions, 15, 514, timeQuat1, timeQuat2);
	Raise(m_timeQuaternions, 3, 526, timeQuat1, timeQuat2, timeQuat3, timeQuat4);
	mediumRaise(m_timeQuaternions, 15, 571, timeQuat1, timeQuat2);
	Raise(m_timeQuaternions, 3, 583, timeQuat1, timeQuat2, timeQuat3, timeQuat4);
	mediumRaise(m_timeQuaternions, 15, 628, timeQuat1, timeQuat2);

	sideRollDown(m_timeQuaternions, 60, 628, timeQuat1, timeQuat2);

	lightBump(m_timeQuaternions, 5, 698, timeQuat1, timeQuat2, timeQuat3, timeQuat4);
	lightBump(m_timeQuaternions, 5, 712, timeQuat1, timeQuat2, timeQuat3, timeQuat4);
	lightBump(m_timeQuaternions, 5, 726, timeQuat1, timeQuat2, timeQuat3, timeQuat4);
	*/

	TimeQuaternion timeQuat0;
	timeQuat0.m_t = m_length;
	timeQuat0.m_quanternion = Quaternion(1, 0, 0, 0);
	m_timeQuaternions.push_back(timeQuat0);
}

void Map::setTimeQuaternion(unsigned int t, Quaternion quat) 
{
	//TODO: check if t is better than last t.

	t = t > m_length ? m_length : t;

	TimeQuaternion timeQuat;
	timeQuat.m_t = t;
	timeQuat.m_quanternion = quat;
	m_timeQuaternions.push_back(timeQuat);
}

void Map::addUpTimeQuaternions() 
{
	for (unsigned int i = 0; i < m_timeQuaternions.size() - 1; i++)
	{
		m_timeQuaternions[i + 1].m_quanternion = m_timeQuaternions[i].m_quanternion * m_timeQuaternions[i + 1].m_quanternion;
	}
}

void Map::interpolateTimeQuaternions() 
{
	Vector3 currentPos = Vector3(0, 0, 0);
	for (unsigned int i = 0; i < m_timeQuaternions.size() - 1; i++)
	{
		TimeQuaternion from = m_timeQuaternions[i];
		TimeQuaternion to = m_timeQuaternions[i + 1];
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
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Map::generateMesh(std::string materialName)
{
	Ogre::ManualObject* plane = new Ogre::ManualObject("plane");
	plane->estimateIndexCount(m_length * m_width * 8);
	plane->estimateVertexCount(m_length * m_width * 8);
	plane->clear();
	plane->begin(materialName);
	
	Ogre::Vector3 pos = Ogre::Vector3(0, 0, 0);
	Ogre::Quaternion quat;
	Ogre::Quaternion quatNext;
	unsigned long planeNum = 0;
	for (unsigned int i = 0; i < m_length; i++)
	{
		quat = m_rotationalSpline.getPoint(i);
		quatNext = m_rotationalSpline.getPoint(i + 1);

		for (int x = -100 * (m_width / (double) 2), j = 0; (unsigned) j < m_width; j++, x += 100)
		{
			int back = -100;
			int left = x;
			int right = x + 100;
			int down = -20 ;

			Ogre::Vector3 nextPos =				pos + quat * Ogre::Vector3(0, 0, back);
			Ogre::Vector3 posMinus50 =			pos + quat * Ogre::Vector3(left, 0, 0);
			Ogre::Vector3 posPlus50 =			pos + quat * Ogre::Vector3(right, 0, 0);
			Ogre::Vector3 nextPosMinus50 =		nextPos + quatNext * Ogre::Vector3(left, 0, 0);
			Ogre::Vector3 nextPosPlus50 =		nextPos + quatNext * Ogre::Vector3(right, 0, 0);

			//TODO: fix normals?
			plane->position(posMinus50);		plane->normal((quat * Vector3(0, 1, 0)).normalisedCopy()); plane->textureCoord(1, 1);
			plane->position(nextPosMinus50);	plane->normal((quat * Vector3(0, 1, 0)).normalisedCopy()); plane->textureCoord(1, 0);
			plane->position(posPlus50);			plane->normal((quat * Vector3(0, 1, 0)).normalisedCopy()); plane->textureCoord(0, 1);
			plane->position(nextPosPlus50);		plane->normal((quat * Vector3(0, 1, 0)).normalisedCopy()); plane->textureCoord(0, 0);

			Ogre::Vector3 nextPosDown =			nextPos + quat * Ogre::Vector3(0, down, 0);
			Ogre::Vector3 posMinus50Down =		posMinus50 + quat * Ogre::Vector3(0, down, 0);
			Ogre::Vector3 posPlus50Down =		posPlus50 + quat * Ogre::Vector3(0, down, 0);
			Ogre::Vector3 nextPosMinus50Down =	nextPosMinus50 + quatNext * Ogre::Vector3(0, down, 0);
			Ogre::Vector3 nextPosPlus50Down =	nextPosPlus50 + quatNext * Ogre::Vector3(0, down, 0);

			//TODO: fix normals?
			plane->position(posMinus50Down);	plane->normal((quat * Vector3(-1, -1, 1)).normalisedCopy()); plane->textureCoord(0, 0);
			plane->position(nextPosMinus50Down);plane->normal((quat * Vector3(-1, -1, -1)).normalisedCopy()); plane->textureCoord(0, 1);
			plane->position(posPlus50Down);		plane->normal((quat * Vector3(1, -1, 1)).normalisedCopy()); plane->textureCoord(1, 0);
			plane->position(nextPosPlus50Down);	plane->normal((quat * Vector3(1, -1, -1)).normalisedCopy()); plane->textureCoord(1, 1);

			if (m_cubes[planeNum / (double) m_width][planeNum % m_width] != HOLE)
			{
				if (m_cubes[planeNum / (double) m_width][planeNum % m_width] == NORMAL)
				{
					//top
					plane->triangle(0 + planeNum * 8, 1 + planeNum * 8, 2 + planeNum * 8);
					plane->triangle(2 + planeNum * 8, 1 + planeNum * 8, 0 + planeNum * 8);
					plane->triangle(1 + planeNum * 8, 3 + planeNum * 8, 2 + planeNum * 8);
					plane->triangle(2 + planeNum * 8, 3 + planeNum * 8, 1 + planeNum * 8);
				}

				//bottom
 				plane->triangle(4 + planeNum * 8, 5 + planeNum * 8, 6 + planeNum * 8);
 				plane->triangle(6 + planeNum * 8, 5 + planeNum * 8, 4 + planeNum * 8);
 				plane->triangle(5 + planeNum * 8, 7 + planeNum * 8, 6 + planeNum * 8);
 				plane->triangle(6 + planeNum * 8, 7 + planeNum * 8, 5 + planeNum * 8);

				if (planeNum % m_width == 0 || m_cubes[planeNum / (double) m_width][(planeNum - 1) % m_width] == HOLE)
				{
					//left
					plane->triangle(0 + planeNum * 8, 4 + planeNum * 8, 5 + planeNum * 8);
					plane->triangle(5 + planeNum * 8, 4 + planeNum * 8, 0 + planeNum * 8);
					plane->triangle(0 + planeNum * 8, 1 + planeNum * 8, 5 + planeNum * 8);
					plane->triangle(5 + planeNum * 8, 1 + planeNum * 8, 0 + planeNum * 8);
				}
				if (planeNum % m_width == m_width - 1 || m_cubes[planeNum / (double) m_width][(planeNum + 1) % m_width] == HOLE)
				{
					//right
					plane->triangle(2 + planeNum * 8, 6 + planeNum * 8, 7 + planeNum * 8);
					plane->triangle(7 + planeNum * 8, 6 + planeNum * 8, 2 + planeNum * 8);
					plane->triangle(2 + planeNum * 8, 3 + planeNum * 8, 7 + planeNum * 8);
					plane->triangle(7 + planeNum * 8, 3 + planeNum * 8, 2 + planeNum * 8);
				}
				if (planeNum / (double) m_width >= m_length - 1 || m_cubes[(planeNum + m_width) / (double) m_width][planeNum % m_width] == HOLE)
				{
					//back
					plane->triangle(5 + planeNum * 8, 7 + planeNum * 8, 1 + planeNum * 8);
					plane->triangle(1 + planeNum * 8, 7 + planeNum * 8, 5 + planeNum * 8);
					plane->triangle(1 + planeNum * 8, 3 + planeNum * 8, 7 + planeNum * 8);
					plane->triangle(7 + planeNum * 8, 3 + planeNum * 8, 1 + planeNum * 8);
				}
				if (planeNum / (double) m_width <= m_width || m_cubes[(planeNum - m_width) / (double) m_width][planeNum % m_width] == HOLE)
				{
					//front
					plane->triangle(2 + planeNum * 8, 6 + planeNum * 8, 4 + planeNum * 8);
					plane->triangle(4 + planeNum * 8, 6 + planeNum * 8, 2 + planeNum * 8);
					plane->triangle(0 + planeNum * 8, 4 + planeNum * 8, 2 + planeNum * 8);
					plane->triangle(2 + planeNum * 8, 4 + planeNum * 8, 0 + planeNum * 8);
				}

			}
			planeNum++;
		}
		pos = pos + quat * Ogre::Vector3(0, 0, -100);
	}  

	plane->end();
	plane->setCastShadows(false);
	m_mapMainNode->attachObject(plane);
	MeshPtr ptr = plane->convertToMesh("planeMesh");
	Entity* planeEntity = m_pSceneMgr->createEntity("planeEntity", "planeMesh");
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Map::generateMeshObstacles(std::string materialName) 
{
	Ogre::ManualObject* obstacles = new Ogre::ManualObject("obstacles");
	obstacles->estimateIndexCount(m_length * m_width * 8);
	obstacles->estimateVertexCount(m_length * m_width * 8);
	obstacles->clear();
	obstacles->begin(materialName);

	Ogre::Vector3 pos = Ogre::Vector3(0, 0, 0);
	Ogre::Quaternion quat;
	Ogre::Quaternion quatNext;
	unsigned long planeNum = 0;

	m_obstaclePositions.clear();

	for (unsigned int i = 0; i < m_length; i++)
	{
		quat = m_rotationalSpline.getPoint(i);
		quatNext = m_rotationalSpline.getPoint(i + 1);

		for (int x = -100 * (m_width / (double) 2), j = 0; (unsigned) j < m_width; j++, x += 100)
		{
			int back = -100;
			int left = x;
			int right = x + 100;
			int up = 100;

			Ogre::Vector3 nextPos =				pos + quat * Ogre::Vector3(0, 0, back);
			Ogre::Vector3 posMinus50 =			pos + quat * Ogre::Vector3(left, 0, 0);
			Ogre::Vector3 posPlus50 =			pos + quat * Ogre::Vector3(right, 0, 0);
			Ogre::Vector3 nextPosMinus50 =		nextPos + quatNext * Ogre::Vector3(left, 0, 0);
			Ogre::Vector3 nextPosPlus50 =		nextPos + quatNext * Ogre::Vector3(right, 0, 0);

			//TODO: fix normals
			obstacles->position(posMinus50);	obstacles->normal((quat * Vector3(0, 1, 0)).normalisedCopy()); obstacles->textureCoord(1, 1);
			obstacles->position(nextPosMinus50);obstacles->normal((quat * Vector3(0, 1, 0)).normalisedCopy()); obstacles->textureCoord(1, 0);
			obstacles->position(posPlus50);		obstacles->normal((quat * Vector3(0, 1, 0)).normalisedCopy()); obstacles->textureCoord(0, 1);
			obstacles->position(nextPosPlus50);	obstacles->normal((quat * Vector3(0, 1, 0)).normalisedCopy()); obstacles->textureCoord(0, 0);

			Ogre::Vector3 nextPosUp =			nextPos + quat * Ogre::Vector3(0, up, 0);
			Ogre::Vector3 posMinus50Up =		posMinus50 + quat * Ogre::Vector3(0, up, 0);
			Ogre::Vector3 posPlus50Up =			posPlus50 + quat * Ogre::Vector3(0, up, 0);
			Ogre::Vector3 nextPosMinus50Up =	nextPosMinus50 + quatNext * Ogre::Vector3(0, up, 0);
			Ogre::Vector3 nextPosPlus50Up =		nextPosPlus50 + quatNext * Ogre::Vector3(0, up, 0);

			//TODO: fix normals
			obstacles->position(posMinus50Up);	obstacles->normal((quat * Vector3(-1, 1, 1)).normalisedCopy()); obstacles->textureCoord(0, 0);
			obstacles->position(nextPosMinus50Up);obstacles->normal((quat * Vector3(-1, 1, -1)).normalisedCopy()); obstacles->textureCoord(0, 1);
			obstacles->position(posPlus50Up);	obstacles->normal((quat * Vector3(1, 1, 1)).normalisedCopy()); obstacles->textureCoord(1, 0);
			obstacles->position(nextPosPlus50Up);obstacles->normal((quat * Vector3(1, 1, -1)).normalisedCopy()); obstacles->textureCoord(1, 1);

			if (m_cubes[planeNum / (double) m_width][planeNum % m_width] == OBSTACLE)
			{

				//TODO: check if this hack works..
				m_obstaclePositions.push_back(posMinus50);

				//top
				obstacles->triangle(4 + planeNum * 8, 5 + planeNum * 8, 6 + planeNum * 8);
				obstacles->triangle(6 + planeNum * 8, 5 + planeNum * 8, 4 + planeNum * 8);
				obstacles->triangle(5 + planeNum * 8, 7 + planeNum * 8, 6 + planeNum * 8);
				obstacles->triangle(6 + planeNum * 8, 7 + planeNum * 8, 5 + planeNum * 8);

				if (planeNum % m_width == 0 || m_cubes[planeNum / (double) m_width][(planeNum - 1) % m_width] != OBSTACLE)
				{
					//left
					obstacles->triangle(0 + planeNum * 8, 4 + planeNum * 8, 5 + planeNum * 8);
					obstacles->triangle(5 + planeNum * 8, 4 + planeNum * 8, 0 + planeNum * 8);
					obstacles->triangle(0 + planeNum * 8, 1 + planeNum * 8, 5 + planeNum * 8);
					obstacles->triangle(5 + planeNum * 8, 1 + planeNum * 8, 0 + planeNum * 8);
				}
				if (planeNum % m_width == m_width - 1 || m_cubes[planeNum / (double) m_width][(planeNum + 1) % m_width] != OBSTACLE)
				{
					//right
					obstacles->triangle(2 + planeNum * 8, 6 + planeNum * 8, 7 + planeNum * 8);
					obstacles->triangle(7 + planeNum * 8, 6 + planeNum * 8, 2 + planeNum * 8);
					obstacles->triangle(2 + planeNum * 8, 3 + planeNum * 8, 7 + planeNum * 8);
					obstacles->triangle(7 + planeNum * 8, 3 + planeNum * 8, 2 + planeNum * 8);
				}
				if (planeNum / (double) m_width >= m_length - 1 || m_cubes[(planeNum + m_width) / (double) m_width][planeNum % m_width] != OBSTACLE)
				{
					//back
					obstacles->triangle(9 + planeNum * 8, 7 + planeNum * 8, 1 + planeNum * 8);
					obstacles->triangle(1 + planeNum * 8, 7 + planeNum * 8, 5 + planeNum * 8);
					obstacles->triangle(1 + planeNum * 8, 3 + planeNum * 8, 7 + planeNum * 8);
					obstacles->triangle(7 + planeNum * 8, 3 + planeNum * 8, 1 + planeNum * 8);
				}
				if (planeNum / (double) m_width <= m_width || m_cubes[(planeNum - m_width) / (double) m_width][planeNum % m_width] != OBSTACLE)
				{
					//front
					obstacles->triangle(2 + planeNum * 8, 6 + planeNum * 8, 4 + planeNum * 8);
					obstacles->triangle(4 + planeNum * 8, 6 + planeNum * 8, 2 + planeNum * 8);
					obstacles->triangle(0 + planeNum * 8, 4 + planeNum * 8, 2 + planeNum * 8);
					obstacles->triangle(2 + planeNum * 8, 4 + planeNum * 8, 0 + planeNum * 8);
				}
			}
			planeNum++;
		}
		pos = pos + quat * Ogre::Vector3(0, 0, -100);
	}  

	obstacles->end();
	obstacles->setCastShadows(true);

	//TODO: fix graphics bug when no obstacles
	/*if (m_obstaclePositions.size() <= 0) 
	{
		return;
	}*/

	m_mapMainNode->attachObject(obstacles);

	MeshPtr ptr = obstacles->convertToMesh("obstaclesMesh");
	Entity* obstaclesEntity = m_pSceneMgr->createEntity("obstaclesEntity", "obstaclesMesh");
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
	j = (unsigned int) j > m_width ? m_width : j;

	return m_cubes.at(t).at(j) == HOLE;
}

bool Map::isObstacleInMap(double t, double u)
{
	t = t < 0 ? 0 : t;
	t = t >= m_length ? m_length - 1 : t;

	//TODO: wtf, fix this mess!
	int j = u + (m_width / (double) 2) * 100;
	j /= (double) 100;
	j = m_width - j;
	j -= 1;
	j = j < 0 ? 0 : j;
	j = (unsigned int) j > m_width ? m_width : j;

	return m_cubes.at(t).at(j) == OBSTACLE;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool Map::isCloseToHoleObstacle(double t, double u, double closeDistance, 
	HolesOrObstacles holeOrObstacle)
{
	if (isObstacleInMap(t, u)) 
	{
		return false;
	}

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

	int minDistance = 10000;
	for (unsigned int i = 0; i < row.size(); i++)
	{
		if (row[i] == holeOrObstacle)
		{
			int distance = abs(u - (i * 100 + 50));
			if (distance < closeDistance)
			{
				return true;
			}
		}
	}

	return false;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

// HELPER FUNCTIONS
/*
void lightBump(std::vector<TimeQuaternion>& timeQuaternions, int degree, int time, 
	TimeQuaternion& timeQuat1, TimeQuaternion& timeQuat2, TimeQuaternion& timeQuat3, TimeQuaternion& timeQuat4) {

		timeQuat1.m_t = time;
		timeQuat1.m_quanternion = Quaternion(Degree(degree), Vector3(1, 0, 0));
		timeQuaternions.push_back(timeQuat1);
		timeQuat2.m_t = time+1;
		timeQuat2.m_quanternion = Quaternion(Degree(-degree), Vector3(1, 0, 0));
		timeQuaternions.push_back(timeQuat2);
		timeQuat3.m_t = time+2;
		timeQuat3.m_quanternion = Quaternion(Degree(-degree), Vector3(1, 0, 0));
		timeQuaternions.push_back(timeQuat3);
		timeQuat4.m_t = time+3;
		timeQuat4.m_quanternion = Quaternion(Degree(degree), Vector3(1, 0, 0));
		timeQuaternions.push_back(timeQuat4);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void mediumRaise(std::vector<TimeQuaternion>& timeQuaternions, int degree, int time, 
	TimeQuaternion& timeQuat1, TimeQuaternion& timeQuat2) {

		timeQuat1.m_t = time;
		timeQuat1.m_quanternion = Quaternion(Degree(degree), Vector3(1, 0, 0));
		timeQuaternions.push_back(timeQuat1);
		timeQuat2.m_t = time+5;
		timeQuat2.m_quanternion = Quaternion(Degree(-degree), Vector3(1, 0, 0));
		timeQuaternions.push_back(timeQuat2);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Raise(std::vector<TimeQuaternion>& timeQuaternions, int degree, int time, 
	TimeQuaternion& timeQuat1, TimeQuaternion& timeQuat2, TimeQuaternion& timeQuat3, TimeQuaternion& timeQuat4) {

		lightBump(timeQuaternions, degree, time, timeQuat1, timeQuat2, timeQuat3, timeQuat4);
		lightBump(timeQuaternions, degree, time+12, timeQuat1, timeQuat2, timeQuat3, timeQuat4);
		lightBump(timeQuaternions, degree, time+24, timeQuat1, timeQuat2, timeQuat3, timeQuat4);
}


//|||||||||||||||||||||||||||||||||||||||||||||||

void sideRollUp(std::vector<TimeQuaternion>& timeQuaternions, int degree, int time, 
TimeQuaternion& timeQuat1, TimeQuaternion& timeQuat2) {

timeQuat1.m_t = time;
timeQuat1.m_quanternion = Quaternion(1, 0, 0, 0);
timeQuaternions.push_back(timeQuat1);
timeQuat2.m_t = time+60;
timeQuat2.m_quanternion = Quaternion(Degree(degree), Vector3(0, -1, 1));
timeQuaternions.push_back(timeQuat2);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void sideRollDown(std::vector<TimeQuaternion>& timeQuaternions, int degree, int time, 
TimeQuaternion& timeQuat1, TimeQuaternion& timeQuat2) {

timeQuat1.m_t = time;
timeQuat1.m_quanternion = Quaternion(1, 0, 0, 0);
timeQuaternions.push_back(timeQuat1);
timeQuat2.m_t = time+60;
timeQuat2.m_quanternion = Quaternion(Degree(degree), Vector3(0, 1, 1));
timeQuaternions.push_back(timeQuat2);
}
*/
//|||||||||||||||||||||||||||||||||||||||||||||||