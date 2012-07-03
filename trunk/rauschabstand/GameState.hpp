//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AppState.hpp"

#include "DotSceneLoader.hpp"

#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>

#include "Player.hpp"
#include "Map.hpp"
#include "Visuals.hpp"
#include "GameLogic.hpp"
#include "AudioPlayer.hpp"
#include "GameView.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

enum QueryFlags {
    OGRE_HEAD_MASK  = 1 << 0,
    CUBE_MASK       = 1 << 1
};

//|||||||||||||||||||||||||||||||||||||||||||||||

class GameState : public AppState
{
    public:
        GameState();

        DECLARE_APPSTATE_CLASS(GameState)

        void enter();
        void createScene();
        void exit();
        bool pause();
        void resume();

        void getInput();

        bool keyPressed(const OIS::KeyEvent& keyEventRef);
        bool keyReleased(const OIS::KeyEvent& keyEventRef);

        bool mouseMoved(const OIS::MouseEvent& arg);
        bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
        bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);

        void onLeftPressed(const OIS::MouseEvent& evt);
        void itemSelected(OgreBites::SelectMenu* menu);

        void update(Ogre::Real timeSinceLastFrame);

    private:
        OgreBites::ParamsPanel*     m_pDetailsPanel;
        bool                        m_bQuit;

        Ogre::RaySceneQuery*        m_pRSQ;
        Ogre::SceneNode*            m_pCurrentObject;
        Ogre::Entity*               m_pCurrentEntity;
        bool                        m_bLMouseDown, m_bRMouseDown;
        bool                        m_bSettingsMode;

        Visuals*                    m_visuals;

        GameLogic*                  m_gameLogic;
        AudioPlayer*                m_audioPlayer;

        GameView*                   m_gameView;

        bool                        m_audioRunningBeforePause;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
