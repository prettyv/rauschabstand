//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AppState.hpp"

#include "DotSceneLoader.hpp"

#include "GameLogic.hpp"
#include "OgreFontManager.h"

#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>

//|||||||||||||||||||||||||||||||||||||||||||||||

class GameView {

public:
    GameView();
    ~GameView();

    void engage(GameLogic* gameLogic, Ogre::SceneManager* sceneManager, Ogre::Camera* pCamera,Ogre::FrameEvent FrameEvent);
    void disengage();
    void update(Ogre::Real timeSinceLastFrame);

    void keyPressed();

    void pauseGame();
    void resumeGame();

    //getters
    OgreBites::ParamsPanel* getHighscorePanel();

private:
    void showAllHUDElements();
    void hideAllHUDElements();
    void createHUD();
    void createHUDForDebug();
    void createAllMaterials();
    void calculateDimensions();
    void updateHUD(Ogre::Real timeSinceLastFrame);
    void updateHUDForDebug(Ogre::Real timeSinceLastFrame);
    void updateScore();
    void updateMultiplier(Ogre::Real timeSinceLastFrame);

    void setAlphaToAllPanels();

private:
    //Status
    bool                        m_showHUD;
    bool                        m_scaleMultiplier;
    
    OgreBites::ParamsPanel*		m_pDetailsPanel;
    
    bool						m_bSettingsMode;
    Ogre::Camera*				m_pCamera;
    Ogre::FrameEvent            m_FrameEvent;
    // For Highscore
    unsigned long               m_score;
    unsigned long               m_scoreOld;
    unsigned int                m_multiplier;
    unsigned int                m_multiplierOld;

    //Material Names
    String                      m_materialNameBoostBar;
    String                      m_materialNameTrack;
    String                      m_materialNameLogo;
    String                      m_materialNameNumbers;
    String                      m_materialNameX;
    String                      m_materialNameMult;
    String                      m_materialNameHighscore;
    // For Overlays
    OverlayContainer*           m_panelLogo;
    OverlayContainer*           m_panelBoost;
    OverlayContainer*           m_panelTrack;
    OverlayContainer*           m_panelX;
    OverlayContainer*           m_panelHighscore;

    OverlayContainer*           m_panelNum1;
    OverlayContainer*           m_panelNum2;
    OverlayContainer*           m_panelNum3;
    OverlayContainer*           m_panelNum4;
    OverlayContainer*           m_panelNum5;
    OverlayContainer*           m_panelNum6;

    OverlayContainer*           m_panelMult1;
    OverlayContainer*           m_panelMult2;

    //Overlays
    Ogre::Overlay*              m_overlayBoost;
    Ogre::Overlay*              m_overlayMultiplier;
    
    Ogre::SceneManager*         m_sceneManager;
    GameLogic*					m_gameLogic;
    OgreBites::ParamsPanel*		m_highscorePanel;

    //Variabeln für den Fortschritt
    int                         m_boostCharge;
    int                         m_levelProgress;

    //Variabeln für die Positionierung und die Größe der Overlays
    double                      m_PosTrackLeft;
    double                      m_PosTrackTop;
    double                      m_DimTrackWidth;
    double                      m_DimTrackHeight;
    int                         m_PixelTrackWidth;
    int                         m_PixelTrackHeight;

    double                      m_PosBoostLeft;
    double                      m_PosBoostTop;
    double                      m_DimBoostWidth;
    double                      m_DimBoostHeight;
    int                         m_PixelBoostWidth;
    int                         m_PixelBoostHeight;

    double                      m_PosLogoLeft;
    double                      m_PosLogoTop;
    double                      m_DimLogoWidth;
    double                      m_DimLogoHeight;
    int                         m_PixelLogoWidth;
    int                         m_PixelLogoHeight;

        //Numbers
    double                      m_PosNum1Left;
    double                      m_PosNum1Top;
    double                      m_PosNum2Left;
    double                      m_PosNum2Top;
    double                      m_PosNum3Left;
    double                      m_PosNum3Top;
    double                      m_PosNum4Left;
    double                      m_PosNum4Top;
    double                      m_PosNum5Left;
    double                      m_PosNum5Top;
    double                      m_PosNum6Left;
    double                      m_PosNum6Top;

    double                      m_DimNumWidth;
    double                      m_DimNumHeight;
    int                         m_PixelNumWidth;    //auch für Mult
    int                         m_PixelNumHeight;

    double                      m_PosMult1Left;
    double                      m_PosMult1Top;
    double                      m_PosMult2Left;
    double                      m_PosMult2Top;

    double                      m_DimMultWidth;
    double                      m_DimMultHeight;
        //Numbers End

    double                      m_PosXLeft;
    double                      m_PosXTop;
    double                      m_DimXWidth;
    double                      m_DimXHeight;
    int                         m_PixelXWidth;
    int                         m_PixelXHeight;

    double                      m_PosHighscoreLeft;
    double                      m_PosHighscoreTop;
    double                      m_DimHighscoreWidth;
    double                      m_DimHighscoreHeight;
    int                         m_PixelHighscoreWidth;
    int                         m_PixelHighscoreHeight;

    //Fade In
    double                      m_alpha;
    bool                        m_fadeIn;

    //Times
    Ogre::Real                  m_timeScaleMultiplier;

    //Animation
    double                      m_animationScaleMultiplier;
    
    //Test
    double                      m_positionLogo;
    double                      m_scale;
    bool                        m_scaleInvert;  //nur zum Testen
    Ogre::Real                  m_timeTest;

    Ogre::Real                  m_timeHighscoreTest;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||