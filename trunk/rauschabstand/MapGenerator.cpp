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
	//parseAudioForHoles();
	
	m_map->setCubes(300, 1, 5, 1, OBSTACLE);
	m_map->setCubes(350, 1, 5, 1, OBSTACLE);
	m_map->setCubes(400, 1, 5, 1, OBSTACLE);
	m_map->setCubes(450, 1, 5, 1, OBSTACLE);
	m_map->setCubes(500, 1, 5, 1, OBSTACLE);
	m_map->setCubes(550, 1, 5, 1, OBSTACLE);
	m_map->setCubes(600, 1, 5, 1, OBSTACLE);
	m_map->setCubes(650, 1, 5, 1, OBSTACLE);

	m_map->setCubesRadius(300, 10, 3, HOLE);
	m_map->setCubesRadius(400, 10, 3, HOLE);
	m_map->setCubesRadius(500, 10, 3, HOLE);
	m_map->setCubesRadius(600, 10, 3, HOLE);
	m_map->setCubesRadius(700, 10, 3, HOLE);
	m_map->setCubesRadius(800, 10, 3, HOLE);

	//use these last
	m_map->setCubesRow(0, 10, NORMAL);		//start is normal
	m_map->setCubesRow(-5, 5, HOLE);		//cuts of end


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
				unsigned int t = Real(92.5) * m_blockMs * samples + 10000 * m_blockMs;

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

void MapGenerator::parseAudioForHoles() {
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
				unsigned int t = Real(92.5) * m_blockMs * samples + 10000 * m_blockMs;

				if (t - lastT > 5 && countLinenumbers % 12 > 4) 
				{
					if (audioData > 500) 
					{
						int radius = 0;
						if (audioData < 800) 
						{
							radius = 1;
						}
						else if (audioData < 1200)
						{
							radius = 2;
						}
						else 
						{
							radius = 3;
						}
						//int y = ((countLinenumbers % 12) - 5) * 2;
						int y = (int) audioData % 10;
						m_map->setCubesRadius(t, y, radius, HOLE);

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

