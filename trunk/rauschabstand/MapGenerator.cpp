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
	m_map->setCubes(260, 10, 0, 5, OBSTACLE);
	m_map->setCubes(260, 10, -5, 5, HOLE);
	m_map->setCubes(265, 5, 3, 4, NORMAL);
	m_map->setCubesRadius(375, 0, 3, HOLE);
	m_map->setCubesRadius(385, 0, 4, HOLE);
	m_map->setCubesRadius(400, 0, 5, HOLE);
	m_map->setCubesRadius(420, 0, 6, HOLE);
	m_map->setCubesRadius(440, 0, 7, HOLE);
	m_map->setCubesRadius(460, -4, 7, HOLE);

	//obstacles for debugging sound
	m_map->setCubes(350, 1, -1, 1, OBSTACLE);
	m_map->setCubes(400, 1, -1, 1, OBSTACLE);
	m_map->setCubes(450, 1, -1, 1, OBSTACLE);
	m_map->setCubes(500, 1, -1, 1, OBSTACLE);
	m_map->setCubes(550, 1, -1, 1, OBSTACLE);
	m_map->setCubes(600, 1, -1, 1, OBSTACLE);
	m_map->setCubes(650, 1, -1, 1, OBSTACLE);
	m_map->setCubes(700, 1, -1, 1, OBSTACLE);
	m_map->setCubes(750, 1, -1, 1, OBSTACLE);
	m_map->setCubes(800, 1, -1, 1, OBSTACLE);
	m_map->setCubes(850, 1, -1, 1, OBSTACLE);
	m_map->setCubes(900, 1, -1, 1, OBSTACLE);
	m_map->setCubes(950, 1, -1, 1, OBSTACLE);
	m_map->setCubes(1000, 1, -1, 1, OBSTACLE);
	m_map->setCubes(1050, 1, -1, 1, OBSTACLE);

	//use these last
	m_map->setCubesRow(500, 10, NORMAL);		//start is normal
	m_map->setCubesRow(495, 5, HOLE);		//cuts of end


	//setTimeQuaternions
	//TODO: move setTimeQuaternions here
	//TODO: make setTimeQuaternions work with audio data
	m_map->setTimeQuaternions();

	m_map->addUpTimeQuaternions();
	m_map->interpolateTimeQuaternions();

	//TODO: seperate into: Obsticales and Map, outside Border and Map, choose material here.
	m_map->generateMesh("Examples/Rockwall");
	m_map->generateMeshObstacles("Examples/RustySteel");
}

//|||||||||||||||||||||||||||||||||||||||||||||||