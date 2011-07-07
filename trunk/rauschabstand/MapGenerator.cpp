//|||||||||||||||||||||||||||||||||||||||||||||||

#include "MapGenerator.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

MapGenerator::MapGenerator(std::string mapname, SceneManager* sceneMgr,
	unsigned int length, unsigned int width) 
{
	m_map = new Map(mapname, sceneMgr, length, width);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void trippleBump(Map* map, unsigned int t) {
	map->setTimeQuaternion(t-7, Quaternion(1, 0, 0, 0));
	map->setTimeQuaternion(t, Quaternion(Degree(3), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+7, Quaternion(Degree(-6), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+16, Quaternion(Degree(6), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+23, Quaternion(Degree(-6), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+32, Quaternion(Degree(6), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+39, Quaternion(Degree(-6), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+46, Quaternion(1, 0, 0, 0));

	map->setCubes(t, 1, 3, 7, OBSTACLE);
	map->setCubes(t+16, 1, 0, 7, OBSTACLE);
	map->setCubes(t+32, 1, 3, 7, OBSTACLE);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void bigTrippleBump(Map* map, unsigned int t) {
	map->setTimeQuaternion(t-10, Quaternion(1, 0, 0, 0));
	map->setTimeQuaternion(t, Quaternion(Degree(7), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+7, Quaternion(Degree(-14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+16, Quaternion(Degree(14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+23, Quaternion(Degree(-14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+32, Quaternion(Degree(14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+39, Quaternion(Degree(-14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+47, Quaternion(Degree(14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+56, Quaternion(Degree(-14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+65, Quaternion(Degree(14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+73, Quaternion(Degree(-14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+81, Quaternion(Degree(14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+89, Quaternion(Degree(-14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+98, Quaternion(Degree(14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+107, Quaternion(Degree(-14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+115, Quaternion(Degree(14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+123, Quaternion(Degree(-14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+132, Quaternion(Degree(14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+140, Quaternion(Degree(-14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+148, Quaternion(Degree(14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+157, Quaternion(Degree(-14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+166, Quaternion(Degree(14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+174, Quaternion(Degree(-14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+182, Quaternion(Degree(14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+189, Quaternion(Degree(-14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+197, Quaternion(Degree(14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+206, Quaternion(Degree(-14), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+216, Quaternion(1, 0, 0, 0));
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void raise(Map* map, unsigned int t) {
	map->setTimeQuaternion(t-5, Quaternion(1, 0, 0, 0));
	map->setTimeQuaternion(t, Quaternion(Degree(20), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+5, Quaternion(Degree(-10), Vector3(1, 0, 0)));

	map->setCubesRadius(t, 0, 4, HOLE);
	map->setCubesRadius(t, 10, 4, HOLE);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void spin(Map* map, unsigned int t) {
	map->setTimeQuaternion(t-10, Quaternion(1, 0, 0, 0));
	map->setTimeQuaternion(t+30, Quaternion(Degree(50), Vector3(0, -1, 0)));
	map->setTimeQuaternion(t+50, Quaternion(1, 0, 0, 0));

	unsigned int tmp = t;
	tmp = t-9;
	map->setCubes(tmp, 1, 0, 1, OBSTACLE); map->setCubes(tmp, 1, 2, 1, OBSTACLE); map->setCubes(tmp, 1, 4, 1, OBSTACLE); map->setCubes(tmp, 1, 6, 1, OBSTACLE); map->setCubes(tmp, 1, 8, 1, OBSTACLE); map->setCubes(tmp, 1, 10, 1, OBSTACLE);
	tmp = t;
	map->setCubes(tmp, 1, 1, 1, OBSTACLE); map->setCubes(tmp, 1, 3, 1, OBSTACLE); map->setCubes(tmp, 1, 5, 1, OBSTACLE); map->setCubes(tmp, 1, 7, 1, OBSTACLE); map->setCubes(tmp, 1, 9, 1, OBSTACLE); 
	tmp = t+10;
	map->setCubes(tmp, 1, 0, 1, OBSTACLE); map->setCubes(tmp, 1, 2, 1, OBSTACLE); map->setCubes(tmp, 1, 4, 1, OBSTACLE); map->setCubes(tmp, 1, 6, 1, OBSTACLE); map->setCubes(tmp, 1, 8, 1, OBSTACLE); map->setCubes(tmp, 1, 10, 1, OBSTACLE);
	tmp = t+20;
	map->setCubes(tmp, 1, 1, 1, OBSTACLE); map->setCubes(tmp, 1, 3, 1, OBSTACLE); map->setCubes(tmp, 1, 5, 1, OBSTACLE); map->setCubes(tmp, 1, 7, 1, OBSTACLE); map->setCubes(tmp, 1, 9, 1, OBSTACLE);
	tmp = t+30;
	map->setCubes(tmp, 1, 0, 1, OBSTACLE); map->setCubes(tmp, 1, 2, 1, OBSTACLE); map->setCubes(tmp, 1, 4, 1, OBSTACLE); map->setCubes(tmp, 1, 6, 1, OBSTACLE); map->setCubes(tmp, 1, 8, 1, OBSTACLE); map->setCubes(tmp, 1, 10, 1, OBSTACLE);
	tmp = t+40;
	map->setCubes(tmp, 1, 1, 1, OBSTACLE); map->setCubes(tmp, 1, 3, 1, OBSTACLE); map->setCubes(tmp, 1, 5, 1, OBSTACLE); map->setCubes(tmp, 1, 7, 1, OBSTACLE); map->setCubes(tmp, 1, 9, 1, OBSTACLE);
	tmp = t+48;
	map->setCubes(tmp, 1, 0, 1, OBSTACLE); map->setCubes(tmp, 1, 2, 1, OBSTACLE); map->setCubes(tmp, 1, 4, 1, OBSTACLE); map->setCubes(tmp, 1, 6, 1, OBSTACLE); map->setCubes(tmp, 1, 8, 1, OBSTACLE); map->setCubes(tmp, 1, 10, 1, OBSTACLE);

}

//|||||||||||||||||||||||||||||||||||||||||||||||

void gap(Map* map, unsigned int t) {
	map->setTimeQuaternion(t-3, Quaternion(1, 0, 0, 0));
	map->setTimeQuaternion(t, Quaternion(Degree(-20), Vector3(1, 0, 0)));
	map->setTimeQuaternion(t+3, Quaternion(Degree(10), Vector3(1, 0, 0)));

	map->setCubes(t-1, 3, 0, 10, HOLE);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void createMap(Map* map) {
	map->setTimeQuaternion(170, Quaternion(Degree(60), Vector3(-1, 0, 0)));
	trippleBump(map, 180);
	raise(map, 239);
	trippleBump(map, 254);
	raise(map, 310);
	trippleBump(map, 326);
	raise(map, 379);
	spin(map, 397);
	gap(map, 450);

	trippleBump(map, 465);
	raise(map, 524);
	trippleBump(map, 538);
	raise(map, 594);
	trippleBump(map, 609);
	raise(map, 662);
	spin(map, 680);
	
	map->setTimeQuaternion(736-6, Quaternion(1, 0, 0, 0));
	map->setTimeQuaternion(736, Quaternion(Degree(20), Vector3(1, 0, 0)));
	map->setTimeQuaternion(736+6, Quaternion(Degree(-10), Vector3(1, 0, 0)));

	trippleBump(map, 748);
	raise(map, 807);
	trippleBump(map, 821);
	raise(map, 877);
	trippleBump(map, 892);
	raise(map, 945);
	spin(map, 963);

	bigTrippleBump(map, 1025);

	map->setTimeQuaternion(1300, Quaternion(Degree(-20), Vector3(1, 0, 0)));
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void MapGenerator::generateMap() 
{
	//setCubes
	//TODO code more functions to modify Cubes
	m_map->resetCubes();
	//parseAudioForHoles();
	
	/*
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
	*/

	//setTimeQuaternions
	//TODO: move setTimeQuaternions here
	//TODO: make setTimeQuaternions work with audio data
	//m_map->setTimeQuaternions();
	m_map->setTimeQuaternion(0, Quaternion(1, 0, 0, 0));
	//parseAudioForOrientation();
	createMap(m_map);
	m_map->setTimeQuaternion(m_map->getLength(), Quaternion(1, 0, 0, 0));

	m_map->addUpTimeQuaternions();
	m_map->interpolateTimeQuaternions();

	//TODO: seperate into: Obsticales and Map, outside Border and Map, choose material here.
	m_map->generateMesh("Examples/Rockwall");
	m_map->generateMeshObstacles("obstacleMaterial");
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

