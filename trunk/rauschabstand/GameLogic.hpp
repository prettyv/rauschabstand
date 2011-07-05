//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Player.hpp"
#include "MapGenerator.hpp"
#include "Map.hpp"
#include "AudioPlayer.hpp"

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
	GameLogic(SceneManager* sceneMgr, Camera* camera, AudioPlayer* audioPlayer);
	~GameLogic();

	void init();
	void start();
	void reset();
	void update(Ogre::Real timeSinceLastFrame);
	void updatePlayer(Ogre::Real timeSinceLastFrame);
	void playerDies();

	//input
	void update(Ogre::Real elapsedTime, OIS::Keyboard *input);
	void keyReleased(Real timeSinceLastFrame, const OIS::KeyEvent & keyEventRef );

	//getter
	Map* getMap() { return m_map; }
	unsigned long getScore() { return m_score; }
	unsigned long getMultiplier() { return m_multiplier; }
	Real getProgress() { return m_map->getLength() / m_t; }
private:
	GameLogicStates		m_gameLogicStates;

	SceneManager*		m_sceneMgr;
	Camera*				m_camera;

	MapGenerator*		m_mapGenerator;
	Map*				m_map;
	Player*				m_player;
	AudioPlayer*		m_audioPlayer;

	Real				m_t;
	Real				m_u;

	unsigned long		m_score;
	unsigned long		m_multiplier;

	unsigned int		m_timeCloseToHole;
	long				m_countdownTime;

	static const int	DEADHEIGHT = -300;		// height when player is dead
// 	static const float	BLOCKMS = 0.015f;
// 	static const float	BLOCKMSSIDE = 1.0f;

	Real				m_blockMs;
	Real				m_blockMsSide;

	// COUNTDOWN BEGIN
	OverlayManager& overlayManager;
	OverlayContainer* m_countDown;
	Overlay* overlayCountDown;
	// COUNTDOWN END
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||