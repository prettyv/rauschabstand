//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef MAP_HPP
#define MAP_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

#include "AdvancedOgreFramework.hpp"

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

struct TimeQuaternion
{
	unsigned int m_t;
	Quaternion m_quanternion;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

enum HolesOrObstacles {
	NORMAL,
	HOLE,
	OBSTACLE
};

//|||||||||||||||||||||||||||||||||||||||||||||||

class Map
{
public:
	Map(std::string name, Ogre::SceneManager* sceneMgr, unsigned int length, unsigned int width);

	//setCubes:
	void resetCubes();
	void setCubesRow(int start, unsigned int length, HolesOrObstacles holeOrObstacle);
	void setCubes(int start, unsigned int length, int startV, unsigned int width, HolesOrObstacles holeOrObstacle);
	void setCubesRadius(int x, int y, unsigned int radius, HolesOrObstacles holeOrObstacle);

	void setTimeQuaternions();
	void setTimeQuaternion(unsigned int t, Quaternion quat);
	void addUpTimeQuaternions();
	void interpolateTimeQuaternions();
	void generateMesh(std::string materialName);
	void generateMeshObstacles(std::string materialName);

	//getter & setter
	Ogre::Quaternion getOrientation(double t);
	Ogre::Vector3 getPosition(double t, double u);

	bool isCloseToHoleObstacle(double t, double u, double closeDistance, 
		HolesOrObstacles holeOrObstacle);
	bool isHoleInMap(double t, double u);
	bool isObstacleInMap(double t, double u);

	int getLength() { return m_length; }
	int getWidth() { return m_width; }

	std::vector<Vector3> getObstaclePositions() { return m_obstaclePositions; }

private:
	unsigned int								m_length;
	unsigned int								m_width;

	std::vector<std::vector<HolesOrObstacles> >	m_cubes;
	std::vector<TimeQuaternion>					m_timeQuaternions;
	RotationalSpline							m_rotationalSpline;
	SimpleSpline								m_pointsSpline;
	std::vector<Vector3>						m_obstaclePositions;
	
    SceneManager*								m_pSceneMgr;
	
    SceneNode*									m_mapMainNode;
    std::string									m_name;
};


//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||