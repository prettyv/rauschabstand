//|||||||||||||||||||||||||||||||||||||||||||||||

#include "MapGenerator.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

MapGenerator::MapGenerator(std::string mapname, SceneManager* sceneMgr, 
	unsigned int length, unsigned int width) 
{
	m_map = new Map(mapname, sceneMgr, length, width);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void MapGenerator::generateMap() 
{
	//setCubes
	//TODO code more functions to modify Cubes
	m_map->resetCubes();
	m_map->setCubes(60, 10, 0, 5, OBSTACLE);
	m_map->setCubes(60, 10, -5, 5, HOLE);
	m_map->setCubes(65, 5, 3, 4, NORMAL);
	m_map->setCubesRadius(75, 0, 3, HOLE);
	m_map->setCubesRadius(85, 0, 4, HOLE);
	m_map->setCubesRadius(100, 0, 5, HOLE);
	m_map->setCubesRadius(120, 0, 6, HOLE);
	m_map->setCubesRadius(140, 0, 7, HOLE);
	m_map->setCubesRadius(160, -4, 7, HOLE);
	//m_map->setCubesRadius(75, 14, 7, HOLE);
	//use these last
	m_map->setCubesRow(0, 10, NORMAL);		//start is normal
	m_map->setCubesRow(-5, 5, HOLE);		//cuts of end


	//setTimeQuaternions
	//TODO: move setTimeQuaternions here
	//TODO: make setTimeQuaternions work with audio data
	m_map->setTimeQuaternions();

	m_map->addUpTimeQuaternions();
	m_map->interpolateTimeQuaternions();

	//TODO: seperate into: Obsticales and Map, outside Border and Map, choose material here.
	m_map->generateMesh();
}

//|||||||||||||||||||||||||||||||||||||||||||||||