//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AppState.hpp"

#include "DotSceneLoader.hpp"

#include "GameLogic.hpp"

#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>

//|||||||||||||||||||||||||||||||||||||||||||||||

class GameView {

public:
    GameView();
    ~GameView();

    void engage(GameLogic* gameLogic, Ogre::SceneManager* sceneManager);
    void disengage();
    void update(Ogre::Real timeSinceLastFrame);

    //getters
    OgreBites::ParamsPanel* getHighscorePanel();

private:
    void createHUD();
    void updateHUD(Ogre::Real timeSinceLastFrame);

private:
    // For Highscore
    unsigned long               m_score;
    unsigned int                m_multiplier;

    // For Overlays
    Ogre::Real                      m_timeTest;
    MaterialPtr                 m_materialBoost;
    MaterialPtr                 m_materialLogo;
    MaterialPtr                 m_materialTrack;
    double                      m_scale;
    bool                        m_scaleInvert;  //nur zum Testen
    bool                        m_showHUD;

    Ogre::SceneManager*         m_sceneManager;
    GameLogic*					m_gameLogic;
    OgreBites::ParamsPanel*		m_highscorePanel;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||