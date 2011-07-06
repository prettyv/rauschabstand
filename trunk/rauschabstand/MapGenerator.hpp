//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef MAPGENERATOR_HPP
#define MAPGENERATOR_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Map.hpp"

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

class MapGenerator
{
public:
	MapGenerator(std::string mapname, SceneManager* sceneMgr, unsigned int length, unsigned int width);
	void generateMap();
	void parseAudioForOrientation();
	void parseAudioForHoles();

	void setBlockMs(Real blockMs) { m_blockMs = blockMs; }
	Map* getMap() { return m_map; }

private:
	Map*		m_map;
	Real		m_blockMs;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||