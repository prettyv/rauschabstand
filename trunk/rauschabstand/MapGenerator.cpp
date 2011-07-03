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
	m_map->resetCubes();

	//use these last
	m_map->setCubesRow(0, 10, NORMAL);	//start is allways normal
	m_map->setCubesRow(-5, 5, HOLE);	//cuts of end


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