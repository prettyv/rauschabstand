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
	//m_map->setTimeQuaternions();
	m_map->setTimeQuaternion(0, Quaternion(1, 0, 0, 0));
	parseAudioForOrientation();
	m_map->setTimeQuaternion(m_map->getLength(), Quaternion(1, 0, 0, 0));

	m_map->addUpTimeQuaternions();
	m_map->interpolateTimeQuaternions();

	//TODO: seperate into: Obsticales and Map, outside Border and Map, choose material here.
	m_map->generateMesh("Examples/Rockwall");
	m_map->generateMeshObstacles("Examples/RustySteel");
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void MapGenerator::parseAudioForOrientation() {
	unsigned int countLinenumbers = 0;
	unsigned int samples = 0;
	double audioData = 0.0;
	std::stringstream sstr;
	unsigned int lastT = 0;

	std::string line;
	std::ifstream myfile ("spectralAnalysis_4096_samples.txt");

	// EINGABEGROESSE (BARCOUNT, CUBECOUNT) ABHAENGIG!
	if (myfile.is_open())
	{
		while (myfile.good())
		{
			getline (myfile,line);

			if (line.size()>0)
			{
				sstr.str(line);
				std::string tmpstr = sstr.str();

				sstr >> audioData;


				// TODO automate range determination
				// get the data in range 0-7
				if (audioData != 0)
				{
					audioData -= 1;
					audioData *= 100000;
				}

				// 12 bands, 16384 samples buffer ~= 0,37s window -> / 370ms || 4096 samples = 92.5ms
				unsigned int t = Real(92.5) * m_blockMs * samples;

				if (t - lastT > 10 && countLinenumbers % 12 < 4) 
				{
					if (audioData > 500) 
					{
						m_map->setTimeQuaternion(t - 2, Quaternion(Degree(audioData / 300), Vector3(1, 0, 0)));
						m_map->setTimeQuaternion(t, Quaternion(Degree(-audioData / 300), Vector3(1, 0, 0)));
						m_map->setTimeQuaternion(t + 2, Quaternion(Degree(-audioData / 300), Vector3(1, 0, 0)));
						m_map->setTimeQuaternion(t + 4, Quaternion(Degree(audioData / 300), Vector3(1, 0, 0)));

						lastT = t;
					}
				}

				sstr.clear();
				line.clear();
				tmpstr.clear();
				audioData = 0.0;
			}

			++countLinenumbers;
			if (countLinenumbers % 12 == 0) 
			{
				++samples;
			}
		}
		myfile.close();
	}
}

//|||||||||||||||||||||||||||||||||||||||||||||||