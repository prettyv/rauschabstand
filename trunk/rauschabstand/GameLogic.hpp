//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Player.hpp"
#include "Map.hpp"

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

enum GameLogicStates {
	INIT,
	COUNTDOWN,
	RUNNING
};

//|||||||||||||||||||||||||||||||||||||||||||||||

class GameLogic {
public:
	GameLogic(SceneManager* sceneMgr, Camera* camera);
	~GameLogic();

	void init();
	void start();
	void reset();
	void update(double timeSinceLastFrame);
	void updatePlayer(double timeSinceLastFrame);

	//input
	void update(Ogre::Real elapsedTime, OIS::Keyboard *input);
	void keyReleased(Real timeSinceLastFrame, const OIS::KeyEvent & keyEventRef );

	//getter
	Map* getMap() { return m_map; }
	unsigned long getScore() { return m_score; }
	unsigned long getMultiplier() { return m_multiplier; }
private:
	GameLogicStates		m_gameLogicStates;

	SceneManager*		m_sceneMgr;
	Camera*				m_camera;

	Map*				m_map;
	Player*				m_player;

	Real				m_t;
	Real				m_u;

	unsigned long		m_score;
	unsigned long		m_multiplier;

	static const int	DEADHEIGHT = -300;		// height when player is dead
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||