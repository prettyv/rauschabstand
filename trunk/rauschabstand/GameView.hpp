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

    void engage(GameLogic* gameLogic, Ogre::SceneManager* sceneManager, Ogre::Camera* pCamera,Ogre::FrameEvent FrameEvent);
    void disengage();
    void update(Ogre::Real timeSinceLastFrame);

    void keyPressed(const OIS::KeyEvent &keyEventRef);
    void mouseMoved(const OIS::MouseEvent &evt);
    void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

    void pauseGame();
    void resumeGame();

    //getters
    OgreBites::ParamsPanel* getHighscorePanel();
    bool getHighscoreShown();

private:
    void showAllHUDElements();
    void hideAllHUDElements();
    void createHUD();
    void createHUDForDebug();
    void createHighscore();
    void createAllMaterials();
    void createStartMenu();
    void calculateDimensions();
    void updateHUD(Ogre::Real timeSinceLastFrame);
    void updateHUDForDebug(Ogre::Real timeSinceLastFrame);
    void updateHighscore(Ogre::Real timeSinceLastFrame);
    void updateScore();
    void getScoreForHighscore();
    void updateMultiplier(Ogre::Real timeSinceLastFrame);

    void setAlphaToAllHUDPanels();
    void setAlphaToAllHUDMaterials();
    void setAlphaToHighscorePanels();
    void setAlphaToStartMenuPanels();

public:
    //For GameState
    bool                        m_stopAtStart;
private:
    
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
    String                      m_materialNameHighscoreNumbers;
    String                      m_materialNameHighscoreName;
    String                      m_materialNameStartBackground;
    // For Overlays
    OverlayContainer*           m_panelLogo;
    OverlayContainer*           m_panelStartBack;

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

    //Highscore
    OverlayContainer*           m_panelHighNum1;
    OverlayContainer*           m_panelHighNum2;
    OverlayContainer*           m_panelHighNum3;
    OverlayContainer*           m_panelHighNum4;
    OverlayContainer*           m_panelHighNum5;
    OverlayContainer*           m_panelHighNum6;


    OverlayContainer*           m_panelHighName1;
    OverlayContainer*           m_panelHighName2;
    OverlayContainer*           m_panelHighName3;

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

    //Start Menü

    double                      m_PosLogoLeft;
    double                      m_PosLogoTop;
    double                      m_DimLogoWidth;
    double                      m_DimLogoHeight;
    int                         m_PixelLogoWidth;
    int                         m_PixelLogoHeight;

    double                      m_PosStartBackLeft;
    double                      m_PosStartBackTop;
    double                      m_DimStartBackWidth;
    double                      m_DimStartBackHeight;
    int                         m_PixelStartBackWidth;
    int                         m_PixelStartBackHeight;

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

        //Highscore
    double                      m_DimHighscoreCharWidth;
    double                      m_DimHighscoreCharHeight;
    int                         m_PixelHighscoreCharWidth;
    int                         m_PixelHighscoreCharHeight;

    double                      m_PosHighscoreNum1Left;
    double                      m_PosHighscoreNum1Top;
    double                      m_PosHighscoreNum2Left;
    double                      m_PosHighscoreNum2Top;
    double                      m_PosHighscoreNum3Left;
    double                      m_PosHighscoreNum3Top;
    double                      m_PosHighscoreNum4Left;
    double                      m_PosHighscoreNum4Top;
    double                      m_PosHighscoreNum5Left;
    double                      m_PosHighscoreNum5Top;
    double                      m_PosHighscoreNum6Left;
    double                      m_PosHighscoreNum6Top;

    double                      m_PosHighscoreName1Left;
    double                      m_PosHighscoreName1Top;
    double                      m_PosHighscoreName2Left;
    double                      m_PosHighscoreName2Top;
    double                      m_PosHighscoreName3Left;
    double                      m_PosHighscoreName3Top;

    double                      m_PosHighscoreLeft;
    double                      m_PosHighscoreTop;
    double                      m_DimHighscoreWidth;
    double                      m_DimHighscoreHeight;
    int                         m_PixelHighscoreWidth;
    int                         m_PixelHighscoreHeight;


        //Highscore End

    double                      m_PosXLeft;
    double                      m_PosXTop;
    double                      m_DimXWidth;
    double                      m_DimXHeight;
    int                         m_PixelXWidth;
    int                         m_PixelXHeight;

    //Times
    Ogre::Real                  m_timeScaleMultiplier;
    Ogre::Real                  m_timeToWaitForHUDToFadeIn;
    Ogre::Real                  m_timeScaleBoost;
    Ogre::Real                  m_timeScaleHighscoreNum;

    bool                        m_updateHighscoreFirstTime;
    int                         m_highscoreCharCount;
    //Animation
    bool                        m_fadeHighscoreIn;
    bool                        m_fadeHUDOut;
    bool                        m_fadeHUDIn;
    bool                        m_waitForHUDToFadeIn;

    bool                        m_animationScaleBoostInvert;
    bool                        m_animationScaleHighscoreNumInvert;

    double                      m_animationScaleMultiplier;
    double                      m_animationScaleBoost;

    double                      m_animationPosHighscoreNum;
    double                      m_animationAlphaHighscore;
    double                      m_animationAlphaHUD;
    double                      m_animationAlphaStartMenu;

    //Status
    bool                        m_showHUD;
    bool                        m_scaleMultiplier;
    bool                        m_showHighscore;
    bool                        m_showStartMenu;

    bool                        m_enterGameSelected;
    
    //Test
    double                      m_positionLogo;

    Ogre::Real                  m_timeHighscoreTest;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||