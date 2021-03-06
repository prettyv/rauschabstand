//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Player.hpp"
#include "MapGenerator.hpp"
#include "Map.hpp"
#include "AudioPlayer.hpp"
#include "Visuals.hpp"

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

enum GameLogicStates {
    INIT,
    COUNTDOWN,
    RUNNING
};

//|||||||||||||||||||||||||||||||||||||||||||||||

class GameLogic
{
    public:
        GameLogic(SceneManager* sceneMgr, Camera* camera, AudioPlayer* audioPlayer);
        ~GameLogic();

        void init();
        void start();
        void update(Ogre::Real timeSinceLastFrame);
        void updatePlayer(Ogre::Real timeSinceLastFrame);
        void playerDies();
        void boostOn();
        void boostOff();

        //input
        void update(Ogre::Real elapsedTime, OIS::Keyboard* input);
        void keyReleased(Real timeSinceLastFrame, const OIS::KeyEvent& keyEventRef );

        //getter
        Map* getMap() {
            return m_map;
        }
        unsigned long getScore() {
            return m_score;
        }
        unsigned long getMultiplier() {
            return m_multiplier;
        }
        Real getProgress() {
            return m_t / (m_map->getLength() - 18 * 20);
        }
        Real getBoostLevel() {
            return m_boostLevel;
        }
        Real getBlockMs() {
            return m_blockMs;
        }

        //setter
        void setVisuals(Visuals* visuals) {
            m_visuals = visuals;
        }
    private:
        GameLogicStates     m_gameLogicStates;

        SceneManager*       m_sceneMgr;
        Camera*             m_camera;

        MapGenerator*       m_mapGenerator;
        Map*                m_map;
        Player*             m_player;
        AudioPlayer*        m_audioPlayer;

        Visuals*            m_visuals;

        Real                m_t;
        Real                m_u;

        unsigned long       m_score;
        unsigned long       m_multiplier;

        unsigned int        m_timeCloseToHole;
        unsigned int        m_timeInObstacle;
        long                m_countdownTime;

        static const int    DEADHEIGHT = -300;      // height when player is dead
//  static const float  BLOCKMS = 0.015f;
//  static const float  BLOCKMSSIDE = 1.0f;

        Real                m_blockMs;
        Real                m_blockMsSide;

        bool                m_boostActive;
        Real                m_boostLevel;
        Real                m_boostSpeed;

        static const int    BOOSTUSEFACTOR = 2000;
        static const int    BOOSTLOADFACTOR = 8000;

        OverlayManager&     m_overlayManager;
        OverlayContainer*   m_countDown;
        Overlay*            m_overlayCountDown;
        bool                m_countdown3_played;
        bool                m_countdown2_played;
        bool                m_countdown1_played;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
