//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameView.hpp"

#include <OgreOverlayManager.h>
#include <OgreMaterialManager.h>

//|||||||||||||||||||||||||||||||||||||||||||||||
GameView::GameView()
{
    //For GameState
    m_stopAtStart = true;

    m_showHUD           = true;    //false = Debug Hud
    m_scaleMultiplier   = false;
    m_showHighscore     = false;
    m_showStartMenu     = true;

    m_enterGameSelected = false;

    m_fadeHighscoreIn   = true;     //Bei der ersten Anzeige wird die Highscore eingefadet
    m_fadeHUDOut        = true;     //und das Hud ausgefadet
    m_fadeHUDIn         = false;     //Hud beginnt nicht gleich mitn Einfaden erst muss Zeit vergehen
    m_waitForHUDToFadeIn = true;

    m_updateHighscoreFirstTime = true;  //Damit ich den aktuellen Score Stand nur 1x übertragen muss

    //Times + animation
    m_timeScaleMultiplier       = 0;
    m_animationScaleBoost       = 0.95;
    m_timeToWaitForHUDToFadeIn  = 0;

    m_animationScaleMultiplier  = 1;
    m_animationAlphaHighscore   = 0;    //Highscore am Anfang nicht sichtbar
    m_animationAlphaHUD         = 0;
    m_animationAlphaStartMenu  = 1;

    m_animationPosHighscoreNum        = 0.0;
    m_animationScaleHighscoreNumInvert  = false;
    m_timeScaleHighscoreNum = 0;

    m_highscoreCharCount    = 1;    //Ich beginne beim ersten Character in der Highscore

    m_highscorePanel    = 0;
    m_gameLogic         = 0;
    m_score             = 0;
    m_scoreOld          = 0;
    m_multiplier        = 1;
    m_multiplierOld     = 1;    //Startet bei Eins

    m_sceneManager      = 0;


    m_pDetailsPanel     = 0;
    m_bSettingsMode     = false;

    //Material Names
    m_materialNameBoostBar  = "BoostBar";
    m_materialNameLogo      = "Logo";
    m_materialNameTrack     = "Track";
    m_materialNameNumbers   = "Numbers";
    m_materialNameX         = "X";
    m_materialNameMult      = "Multiplikator";
    m_materialNameHighscore = "Highscore";
    m_materialNameStartBackground = "StartBackground";

    //Visuals
    m_timeScaleBoost          = 0;
    m_animationScaleBoostInvert       = false;

    m_overlayBoost      = 0;
    m_overlayMultiplier = 0;

    m_panelLogo         = 0;
    m_panelStartBack    = 0;

    m_panelBoost        = 0;
    m_panelTrack        = 0;
    m_panelX            = 0;
    m_panelHighscore    = 0;

    m_panelNum1         = 0;
    m_panelNum2         = 0;
    m_panelNum3         = 0;
    m_panelNum4         = 0;
    m_panelNum5         = 0;
    m_panelNum6         = 0;

    m_panelMult1        = 0;
    m_panelMult2        = 0;

    m_panelHighNum1     = 0;
    m_panelHighNum2     = 0;
    m_panelHighNum3     = 0;
    m_panelHighNum4     = 0;
    m_panelHighNum5     = 0;
    m_panelHighNum6     = 0;

    m_panelHighName1    = 0;
    m_panelHighName2    = 0;
    m_panelHighName3    = 0;

    m_positionLogo      = 0;

    //Positionierung der Einzelnen Overlays

    //Start Menü------
    //Logo------------
    m_PosLogoLeft       = 0.0;
    m_PosLogoTop        = 0.2;
    m_DimLogoWidth      = 1.3;
    m_DimLogoHeight     = 0;
    m_PixelLogoWidth    = 3685;
    m_PixelLogoHeight   = 638;
    //Logo End--------

    m_PosStartBackLeft      = 0.0;
    m_PosStartBackTop       = 0.0;
    m_DimStartBackWidth     = 1.0;  //Ist übern ganzen Bildschirm
    m_DimStartBackHeight    = 1.0;
    m_PixelStartBackWidth   = 1280;
    m_PixelStartBackHeight  = 1024;
    //Start Menü End--

    //Track-----------
    m_PosTrackLeft      = 0;
    m_PosTrackTop       = 0.5;
    m_DimTrackWidth     = 0.1;  //Gewünscht Breite
    m_DimTrackHeight    = 0;    //Höhe noch unbekannt
    m_PixelTrackWidth   = 188;
    m_PixelTrackHeight  = 825;
    //Track End-------
    //Boost-----------
    m_PosBoostLeft      = 0;
    m_PosBoostTop       = 0;
    m_DimBoostWidth     = 0.4;
    m_DimBoostHeight    = 0;
    m_PixelBoostWidth   = 975;
    m_PixelBoostHeight  = 300;
    //Boost End-------
    //Numbers---------
    m_PosNum1Left       = 0.9;
    m_PosNum1Top        = 0.01;
    m_PosNum2Left       = 0.85;
    m_PosNum2Top        = 0.01;
    m_PosNum3Left       = 0.8;
    m_PosNum3Top        = 0.01;
    m_PosNum4Left       = 0.75;
    m_PosNum4Top        = 0.01;
    m_PosNum5Left       = 0.7;
    m_PosNum5Top        = 0.01;
    m_PosNum6Left       = 0.65;
    m_PosNum6Top        = 0.01;

    m_DimNumWidth       = 0.08;
    m_DimNumHeight      = 0;
    m_PixelNumWidth     = 200;
    m_PixelNumHeight    = 200;
    //Numbers End-----
    //Multiplikator---
    m_PosMult1Left      = 0.52;
    m_PosMult1Top       = 0.01;
    m_PosMult2Left      = 0.47;
    m_PosMult2Top       = 0.01;

    m_DimMultWidth      = 0.1;
    m_DimNumHeight      = 0;
    //Multiplikator End
    //x --------------
    m_PosXLeft          = 0.4;
    m_PosXTop           = 0.01;
    m_DimXWidth         = 0.1;
    m_DimXHeight        = 0;
    m_PixelXWidth       = 375;
    m_PixelXHeight      = 375;
    //x End-----------
    //Highscore-------
    m_PosHighscoreNum1Left      = 0.8;
    m_PosHighscoreNum1Top       = 0.37;
    m_PosHighscoreNum2Left      = 0.75;
    m_PosHighscoreNum2Top       = 0.37;
    m_PosHighscoreNum3Left      = 0.7;
    m_PosHighscoreNum3Top       = 0.37;
    m_PosHighscoreNum4Left      = 0.65;
    m_PosHighscoreNum4Top       = 0.37;
    m_PosHighscoreNum5Left      = 0.6;
    m_PosHighscoreNum5Top       = 0.37;
    m_PosHighscoreNum6Left      = 0.55;
    m_PosHighscoreNum6Top       = 0.37;

    m_PosHighscoreName1Left     = 0.18;
    m_PosHighscoreName1Top      = 0.37;
    m_PosHighscoreName2Left     = 0.24;
    m_PosHighscoreName2Top      = 0.37;
    m_PosHighscoreName3Left     = 0.3;
    m_PosHighscoreName3Top      = 0.37;

    m_DimHighscoreCharWidth     = 0.09;
    m_DimHighscoreCharHeight    = 0;
    m_PixelHighscoreCharWidth   = 200;
    m_PixelHighscoreCharHeight  = 200;

    m_PosHighscoreLeft  = 0.06;
    m_PosHighscoreTop   = 0.04;
    m_DimHighscoreWidth = 1.17;
    m_DimHighscoreHeight    = 0;
    m_PixelHighscoreWidth   = 1280;
    m_PixelHighscoreHeight  = 1024;
    //Highscore End---

    //Test
    m_boostCharge       = 0;
    m_levelProgress     = 0;
    m_timeHighscoreTest = 0;
}

GameView::~GameView()
{

}

void GameView::engage(GameLogic* gameLogic, Ogre::SceneManager* sceneManager, Ogre::Camera* pCamera, Ogre::FrameEvent FrameEvent)
{

    m_sceneManager  = sceneManager;
    m_gameLogic     = gameLogic;
    m_pCamera       = pCamera;
    m_FrameEvent    = FrameEvent;

    createAllMaterials();
    calculateDimensions();
    createHighscore();
    createHUDForDebug();
    createHUD();
    createStartMenu();

    OgreFramework::getSingletonPtr()->m_pTrayMgr->hideAll();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();

    //Jedes Material wird einmal gesetzt, damit es später nicht zu rucklern kommt
    m_panelBoost->setMaterialName(m_materialNameBoostBar + "00");
    m_panelBoost->setMaterialName(m_materialNameBoostBar + "01");
    m_panelBoost->setMaterialName(m_materialNameBoostBar + "02");
    m_panelBoost->setMaterialName(m_materialNameBoostBar + "03");
    m_panelBoost->setMaterialName(m_materialNameBoostBar + "04");
    m_panelBoost->setMaterialName(m_materialNameBoostBar + "05");
    m_panelBoost->setMaterialName(m_materialNameBoostBar + "06");
    m_panelBoost->setMaterialName(m_materialNameBoostBar + "07");
    m_panelBoost->setMaterialName(m_materialNameBoostBar + "08");
    m_panelBoost->setMaterialName(m_materialNameBoostBar + "09");
    m_panelBoost->setMaterialName(m_materialNameBoostBar + "10");
    m_panelBoost->setMaterialName(m_materialNameBoostBar + "00");   //Wieder zurück auf 0

    m_panelTrack->setMaterialName(m_materialNameTrack + "00");
    m_panelTrack->setMaterialName(m_materialNameTrack + "01");
    m_panelTrack->setMaterialName(m_materialNameTrack + "02");
    m_panelTrack->setMaterialName(m_materialNameTrack + "03");
    m_panelTrack->setMaterialName(m_materialNameTrack + "04");
    m_panelTrack->setMaterialName(m_materialNameTrack + "05");
    m_panelTrack->setMaterialName(m_materialNameTrack + "06");
    m_panelTrack->setMaterialName(m_materialNameTrack + "07");
    m_panelTrack->setMaterialName(m_materialNameTrack + "08");
    m_panelTrack->setMaterialName(m_materialNameTrack + "09");
    m_panelTrack->setMaterialName(m_materialNameTrack + "10");
    m_panelTrack->setMaterialName(m_materialNameTrack + "00");      //Wieder zurück auf 0
}

void GameView::disengage()
{
    /*
    //Darf nicht alles löschen!!!
    Ogre::MaterialManager::getSingletonPtr()->destroyAllResourcePools();
    Ogre::OverlayManager::getSingletonPtr()->destroyAll();
    */
}

void GameView::createHighscore()
{
    OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

    Overlay* overlayNum;
    overlayNum = overlayManager.create("Overlay_HighscoreChar");
    overlayNum->show();

    m_panelHighNum1 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelHighscoreNum1"));
    m_panelHighNum1->setPosition(m_PosHighscoreNum1Left, m_PosHighscoreNum1Top);
    m_panelHighNum1->setDimensions(m_DimHighscoreCharWidth, m_DimHighscoreCharHeight);
    overlayNum->add2D(m_panelHighNum1);

    m_panelHighNum2 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelHighscoreNum2"));
    m_panelHighNum2->setPosition(m_PosHighscoreNum2Left, m_PosHighscoreNum2Top);
    m_panelHighNum2->setDimensions(m_DimHighscoreCharWidth, m_DimHighscoreCharHeight);
    overlayNum->add2D(m_panelHighNum2);

    m_panelHighNum3 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelHighscoreNum3"));
    m_panelHighNum3->setPosition(m_PosHighscoreNum3Left, m_PosHighscoreNum3Top);
    m_panelHighNum3->setDimensions(m_DimHighscoreCharWidth, m_DimHighscoreCharHeight);
    overlayNum->add2D(m_panelHighNum3);

    m_panelHighNum4 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelHighscoreNum4"));
    m_panelHighNum4->setPosition(m_PosHighscoreNum4Left, m_PosHighscoreNum4Top);
    m_panelHighNum4->setDimensions(m_DimHighscoreCharWidth, m_DimHighscoreCharHeight);
    overlayNum->add2D(m_panelHighNum4);

    m_panelHighNum5 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelHighscoreNum5"));
    m_panelHighNum5->setPosition(m_PosHighscoreNum5Left, m_PosHighscoreNum5Top);
    m_panelHighNum5->setDimensions(m_DimHighscoreCharWidth, m_DimHighscoreCharHeight);
    overlayNum->add2D(m_panelHighNum5);

    m_panelHighNum6 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelHighscoreNum6"));
    m_panelHighNum6->setPosition(m_PosHighscoreNum6Left, m_PosHighscoreNum6Top);
    m_panelHighNum6->setDimensions(m_DimHighscoreCharWidth, m_DimHighscoreCharHeight);
    overlayNum->add2D(m_panelHighNum6);

    m_panelHighName1 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelHighscoreName1"));
    m_panelHighName1->setPosition(m_PosHighscoreName1Left, m_PosHighscoreName1Top);
    m_panelHighName1->setDimensions(m_DimHighscoreCharWidth, m_DimHighscoreCharHeight);
    m_panelHighName1->setMaterialName(m_materialNameHighscoreName + Ogre::StringConverter::toString(88));   //Es steht am Anfang überall X
    overlayNum->add2D(m_panelHighName1);

    m_panelHighName2 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelHighscoreName2"));
    m_panelHighName2->setPosition(m_PosHighscoreName2Left, m_PosHighscoreName2Top);
    m_panelHighName2->setDimensions(m_DimHighscoreCharWidth, m_DimHighscoreCharHeight);
    m_panelHighName2->setMaterialName(m_materialNameHighscoreName + Ogre::StringConverter::toString(88));   //Es steht am Anfang überall X
    overlayNum->add2D(m_panelHighName2);

    m_panelHighName3 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelHighscoreName3"));
    m_panelHighName3->setPosition(m_PosHighscoreName3Left, m_PosHighscoreName3Top);
    m_panelHighName3->setDimensions(m_DimHighscoreCharWidth, m_DimHighscoreCharHeight);
    m_panelHighName3->setMaterialName(m_materialNameHighscoreName + Ogre::StringConverter::toString(88));   //Es steht am Anfang überall X
    overlayNum->add2D(m_panelHighName3);

    //Highscore Background
    //--------------------
    // Create a panel
    m_panelHighscore = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "Panel_HighscoreBackground"));
    m_panelHighscore->setPosition(m_PosHighscoreLeft, m_PosHighscoreTop);
    m_panelHighscore->setDimensions(m_DimHighscoreWidth, m_DimHighscoreHeight);
    m_panelHighscore->setMaterialName(m_materialNameHighscore);

    // Create an overlay, and add the panel
    Overlay* overlayHighscore = overlayManager.create("Overlay_HighscoreBackground");
    overlayHighscore->add2D(m_panelHighscore);
    overlayHighscore->show();

    //Highscore Background End

    //Ich muss irgendein Material vorher setzten
    m_panelHighNum1->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0
    m_panelHighNum2->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0
    m_panelHighNum3->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0
    m_panelHighNum4->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0
    m_panelHighNum5->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0
    m_panelHighNum6->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0

    setAlphaToHighscorePanels();
}

void GameView::createHUDForDebug()
{
    Ogre::StringVector itemsScore;
    itemsScore.push_back("Score");
    itemsScore.push_back("Multiplier");

    m_highscorePanel = OgreFramework::getSingletonPtr()->m_pTrayMgr->createParamsPanel(OgreBites::TL_TOP, "Highscore", 160, itemsScore);
    m_highscorePanel->show();

    OgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    //OgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel(OgreBites::TL_TOP, "GameLbl", "Game mode", 250);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();

    Ogre::StringVector items;
    items.push_back("cam.pX");
    items.push_back("cam.pY");
    items.push_back("cam.pZ");
    items.push_back("cam.oW");
    items.push_back("cam.oX");
    items.push_back("cam.oY");
    items.push_back("cam.oZ");
    items.push_back("Mode");

    m_pDetailsPanel = OgreFramework::getSingletonPtr()->m_pTrayMgr->createParamsPanel(OgreBites::TL_TOPLEFT, "DetailsPanel", 200, items);
    m_pDetailsPanel->show();

    Ogre::StringVector chatModes;
    chatModes.push_back("Solid mode");
    chatModes.push_back("Wireframe mode");
    chatModes.push_back("Point mode");
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createLongSelectMenu(OgreBites::TL_TOPRIGHT, "ChatModeSelMenu", "ChatMode", 200, 3, chatModes);
}

void GameView::createStartMenu()
{
    OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

    Overlay* overlayStart = overlayManager.create("Overlay_Start");
    overlayStart->show();



    //Background
    m_panelStartBack = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "Panel_StartBackground"));
    m_panelStartBack->setPosition(m_PosStartBackLeft, m_PosStartBackTop);
    m_panelStartBack->setDimensions(m_DimStartBackWidth, m_DimStartBackHeight);
    m_panelStartBack->setMaterialName(m_materialNameStartBackground);
    overlayStart->add2D(m_panelStartBack);
    //Background End

    //Logo
    //----
    // Create a panel
    m_panelLogo = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "Panel_Logo"));
    m_panelLogo->setPosition(m_PosLogoLeft, m_PosLogoTop);
    m_panelLogo->setDimensions(m_DimLogoWidth, m_DimLogoHeight);
    m_panelLogo->setMaterialName(m_materialNameLogo);
    overlayStart->add2D(m_panelLogo);
    //Logo End
}

void GameView::createHUD()
{
    OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

    m_overlayMultiplier = overlayManager.create("Overlay_Multiplier");

    //Boost-Balken
    //------------
    // Create a panel
    m_panelBoost = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "Panel_Boost"));
    m_panelBoost->setPosition(m_PosBoostLeft, m_PosBoostTop);
    m_panelBoost->setDimensions(m_DimBoostWidth, m_DimBoostHeight);
    m_panelBoost->setMaterialName(m_materialNameBoostBar + "00");

    // Create an overlay, and add the panel
    m_overlayBoost = overlayManager.create("Overlay_Boost");
    m_overlayBoost->add2D(m_panelBoost);
    m_overlayBoost->show();
    m_overlayBoost->setScale(m_animationScaleBoost, m_animationScaleBoost);
    //------------
    //Boost-Balken - End


    //Track - Balken
    //--------------
    // Create a panel
    m_panelTrack = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "Panel_Track"));
    m_panelTrack->setPosition(m_PosTrackLeft, m_PosTrackTop);
    m_panelTrack->setDimensions(m_DimTrackWidth, m_DimTrackHeight);
    m_panelTrack->setMaterialName(m_materialNameTrack + "00");

    // Create an overlay, and add the panel
    Overlay* overlayTrack = overlayManager.create("Overlay_Track");
    overlayTrack->add2D(m_panelTrack);
    overlayTrack->show();
    //--------------
    //Track - Balken END

    //Numbers for Points
    //------------------
    Overlay* overlayNum;

    m_panelNum1 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelNum1"));
    m_panelNum1->setPosition(m_PosNum1Left, m_PosNum1Top);
    m_panelNum1->setDimensions(m_DimNumWidth, m_DimNumHeight);
    m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0

    // Create an overlay, and add the panel
    overlayNum = overlayManager.create("Overlay_Num1");
    overlayNum->add2D(m_panelNum1);
    overlayNum->show();

    m_panelNum2 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelNum2"));
    m_panelNum2->setPosition(m_PosNum2Left, m_PosNum2Top);
    m_panelNum2->setDimensions(m_DimNumWidth, m_DimNumHeight);
    m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0

    // Create an overlay, and add the panel
    overlayNum = overlayManager.create("Overlay_Num2");
    overlayNum->add2D(m_panelNum2);
    overlayNum->show();

    m_panelNum3 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelNum3"));
    m_panelNum3->setPosition(m_PosNum3Left, m_PosNum3Top);
    m_panelNum3->setDimensions(m_DimNumWidth, m_DimNumHeight);
    m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0

    // Create an overlay, and add the panel
    overlayNum = overlayManager.create("Overlay_Num3");
    overlayNum->add2D(m_panelNum3);
    overlayNum->show();

    m_panelNum4 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelNum4"));
    m_panelNum4->setPosition(m_PosNum4Left, m_PosNum4Top);
    m_panelNum4->setDimensions(m_DimNumWidth, m_DimNumHeight);
    m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0

    // Create an overlay, and add the panel
    overlayNum = overlayManager.create("Overlay_Num4");
    overlayNum->add2D(m_panelNum4);
    overlayNum->show();

    m_panelNum5 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelNum5"));
    m_panelNum5->setPosition(m_PosNum5Left, m_PosNum5Top);
    m_panelNum5->setDimensions(m_DimNumWidth, m_DimNumHeight);
    m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0

    // Create an overlay, and add the panel
    overlayNum = overlayManager.create("Overlay_Num5");
    overlayNum->add2D(m_panelNum5);
    overlayNum->show();

    m_panelNum6 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelNum6"));
    m_panelNum6->setPosition(m_PosNum6Left, m_PosNum6Top);
    m_panelNum6->setDimensions(m_DimNumWidth, m_DimNumHeight);
    m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0

    // Create an overlay, and add the panel
    overlayNum = overlayManager.create("Overlay_Num6");
    overlayNum->add2D(m_panelNum6);
    overlayNum->show();
    //Number for Points End

    //Multiplikator----
    m_panelMult1 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelMult1"));
    m_panelMult1->setPosition(m_PosMult1Left, m_PosMult1Top);
    m_panelMult1->setDimensions(m_DimMultWidth, m_DimMultHeight);
    m_panelMult1->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0

    // Create an overlay, and add the panel
    m_overlayMultiplier->add2D(m_panelMult1);
    m_overlayMultiplier->show();

    m_panelMult2 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelMult2"));
    m_panelMult2->setPosition(m_PosMult2Left, m_PosMult2Top);
    m_panelMult2->setDimensions(m_DimMultWidth, m_DimMultHeight);
    m_panelMult2->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0

    // Create an overlay, and add the panel
    m_overlayMultiplier->add2D(m_panelMult2);
    m_overlayMultiplier->show();
    //Multiplikator End

    //X
    //----
    // Create a panel
    m_panelX = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "Panel_X"));
    m_panelX->setPosition(m_PosXLeft, m_PosXTop);
    m_panelX->setDimensions(m_DimXWidth, m_DimXHeight);
    m_panelX->setMaterialName(m_materialNameX);

    // Create an overlay, and add the panel
    m_overlayMultiplier->add2D(m_panelX);
    m_overlayMultiplier->show();
    //X End

    setAlphaToAllHUDPanels();  //Damit das HUD am Anfang Transparet ist

}

void GameView::calculateDimensions()
{

    //Bildschirmauflösung feststellen
    //GetSystemMetrics(SM_CXSCREEN);
    int height    = OgreFramework::getSingletonPtr()->m_pRenderWnd->getHeight();
    int widthTest = OgreFramework::getSingletonPtr()->m_pRenderWnd->getWidth();
    double ratio  = ((double)widthTest) / height;

    //Track ------------
    //Ohne Bildschirmauflösung
    double ratioTrack = ((double) m_PixelTrackWidth) / m_PixelTrackHeight;
    m_DimTrackHeight = 1 / ratioTrack * m_DimTrackWidth;

    //Mit Bildschirmauflösung, hier gehört die Breite oder Höhe noch angepasst
    if(ratio > 1) { //=Breitbild
        //Die Breite vom Track gehört verkleinert
        m_DimTrackWidth = 1 / ratio * m_DimTrackWidth;
    } else if (ratio < 1) { //=Kommt eigentlich nicht vor Mehr höhe als breite
        //ist einmal nicht vorgesehen
    }

    //Wenns genau eins ist, dann passts
    //Track End---------

    //Boost-------------
    double ratioBoost = ((double) m_PixelBoostWidth ) / m_PixelBoostHeight;
    m_DimBoostHeight = 1 / ratioBoost * m_DimBoostWidth;

    if(ratio > 1) {
        m_DimBoostWidth = 1 / ratio * m_DimBoostWidth;
    } else if (ratio < 1) {
        //Zuerzeit nicht vorgesehen
    }

    //Boost End---------

    //Logo--------------
    double ratioLogo = ((double) m_PixelLogoWidth) / m_PixelLogoHeight;
    m_DimLogoHeight = 1 / ratioLogo * m_DimLogoWidth;

    if(ratio > 1) {
        m_DimLogoWidth = 1 / ratio * m_DimLogoWidth;
    } else if (ratio < 1) {
        //Zuerzeit nicht vorgesehen
    }

    //Logo End----------

    //Numbers-----------
    double ratioNumbers = ((double) m_PixelNumWidth) / m_PixelNumHeight;
    m_DimNumHeight = 1 / ratioNumbers * m_DimNumWidth;

    if(ratio > 1) {
        m_DimNumWidth = 1 / ratio * m_DimNumWidth;
    } else if (ratio < 1) {
        //Zuerzeit nicht vorgesehen
    }

    //Numbers End-------

    //x-----------------
    double ratioX = ((double) m_PixelXWidth) / m_PixelXHeight;
    m_DimXHeight = 1 / ratioX * m_DimXWidth;

    if (ratio > 1) {
        m_DimXWidth = 1 / ratio * m_DimXWidth;
    } else if (ratio < 1) {
        //Zuerzeit nicht vorgesehen
    }

    //x End-------------

    //Multiplikator-----------
    //Ratio ist gleich wie bei den Numbers
    m_DimMultHeight = 1 / ratioNumbers * m_DimMultWidth;

    if(ratio > 1) {
        m_DimMultWidth = 1 / ratio * m_DimMultWidth;
    } else if (ratio < 1) {
        //Zuerzeit nicht vorgesehen
    }

    //Multiplikaotr End-------

    //Highscore-----------
    double ratioHighscore = ((double) m_PixelHighscoreWidth) / m_PixelHighscoreHeight;
    m_DimHighscoreHeight = 1 / ratioHighscore * m_DimHighscoreWidth;

    if(ratio > 1) {
        m_DimHighscoreWidth = 1 / ratio * m_DimHighscoreWidth;
    } else if (ratio < 1) {
        //Zuerzeit nicht vorgesehen
    }

    double ratioHighscoreChar = ((double) m_PixelHighscoreCharWidth) / m_PixelHighscoreCharHeight;
    m_DimHighscoreCharHeight = 1 / ratioHighscoreChar * m_DimHighscoreCharWidth;

    if(ratio > 1) {
        m_DimHighscoreCharWidth = 1 / ratio * m_DimHighscoreCharWidth;
    } else if (ratio < 1) {
        //Zuerzeit nicht vorgesehen
    }

    //Highscore End-------
}

void GameView::createAllMaterials()
{
    MaterialManager& materialManager = Ogre::MaterialManager::getSingleton();

    MaterialPtr material;

    // Create boost material
    // ---------------------
    for(int i = 0; i < 11; i++) {
        if(i < 10) {
            material = materialManager.create(m_materialNameBoostBar + "0" + Ogre::StringConverter::toString(i), "General");
            material->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/Bars0" + Ogre::StringConverter::toString(i) + "-01.png");
            material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
            material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
            material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
            material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
        } else {
            material = materialManager.create(m_materialNameBoostBar + Ogre::StringConverter::toString(i), "General");
            material->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/Bars" + Ogre::StringConverter::toString(i) + "-01.png");
            material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
            material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
            material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
            material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
        }
    }

    // ---------------------

    // Create Track material
    // ---------------------
    for(int i = 0; i < 11; i++) {
        if(i < 10) {
            material = materialManager.create(m_materialNameTrack + "0" + Ogre::StringConverter::toString(i), "General");
            material->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/Track0" + Ogre::StringConverter::toString(i) + "-02.png");
            material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
            material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
            material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
            material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
        } else {
            material = materialManager.create(m_materialNameTrack + Ogre::StringConverter::toString(i), "General");
            material->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/Track" + Ogre::StringConverter::toString(i) + "-02.png");
            material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
            material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
            material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
            material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
        }
    }

    // ---------------------

    // Create Numbers material
    //------------------------
    for(int i = 0; i < 10; i++) {
        material = materialManager.create(m_materialNameNumbers + Ogre::StringConverter::toString(i), "General");
        material->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/Num_" + Ogre::StringConverter::toString(i) + ".png");
        material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
        material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
        material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
        material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    }

    //------------------------

    // Create Multiplikator material
    //------------------------
    for(int i = 0; i < 10; i++) {
        material = materialManager.create(m_materialNameMult + Ogre::StringConverter::toString(i), "General");
        material->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/Num_" + Ogre::StringConverter::toString(i) + "_Orange.png");
        material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
        material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
        material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
        material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    }

    //------------------------

    // Create X material
    //------------------
    material = materialManager.create(m_materialNameX, "General");
    material->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/X.png");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    //------------------

    // Create Highscore Background material
    //------------------
    material = materialManager.create(m_materialNameHighscore, "General");
    material->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/Highscore_Background_1280x1024.png");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    //------------------

    // Create Highscore Number materials
    //------------------
    for(int i = 0; i < 10; i++) {
        material = materialManager.create(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(i), "General");
        material->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/Char_" + Ogre::StringConverter::toString(i) + "_200x200.png");
        material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
        material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
        material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
        material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    }

    //------------------

    //Create Highscore Character materials
    //------------------
    for(int i = 65; i <= 90; i++) {
        material = materialManager.create(m_materialNameHighscoreName + Ogre::StringConverter::toString(i), "General");
        material->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/Char_" + Ogre::StringConverter::toString(i) + "_200x200.png");
        material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
        material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
        material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
        material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    }

    //------------------

    //Materials for Start Menü
    //-------------------

    // Create Logo material
    // ---------------------
    material = materialManager.create(m_materialNameLogo, "General");
    material->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/Logo_FadeOut.png");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    //material->setFog(true,Ogre::FogMode::FOG_EXP,Ogre::ColourValue::Blue,0.4,0,1);  //Test
    //Funktioniert
    //material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LayerBlendOperationEx::LBX_MODULATE,Ogre::LayerBlendSource::LBS_MANUAL,Ogre::LayerBlendSource::LBS_TEXTURE,0.5);

    //material->setFog(true,FogMode::FOG_LINEAR,Ogre::ColourValue::ColourValue(1.0f, 1.0f,1.0f, 0.5f),0.4,0,1);
    // ---------------------

    //Start Menü Background
    material = materialManager.create(m_materialNameStartBackground, "General");
    material->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/StartMenueBackground.jpg");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);

    material = materialManager.create(m_materialNameStartBackground + "Active", "General");
    material->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/StartMenueBackgroundActive.jpg");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    //Start Menü Background END
}

void GameView::update(Ogre::Real timeSinceLastFrame)
{

    if(timeSinceLastFrame == 0) {
        return;   //Dann ist nix passiert
    }

    if(m_showStartMenu) {
        m_animationAlphaStartMenu -= 0.01;

        if(m_animationAlphaStartMenu <= 0) {
            m_animationAlphaStartMenu = 0;
            m_showStartMenu = false;
        }

        setAlphaToStartMenuPanels();
    }

    if (m_showHUD) {

        if(m_showHighscore) {
            updateHighscore(timeSinceLastFrame);

            if(m_fadeHUDOut) {
                m_animationAlphaHUD -= 0.01;

                if(m_animationAlphaHUD <= 0) {
                    m_animationAlphaHUD = 0;
                    m_fadeHUDOut = false;
                }

                setAlphaToAllHUDPanels();
            }
        } else {
            updateHUD(timeSinceLastFrame);
        }
    } else {
        updateHUDForDebug(timeSinceLastFrame);
    }
}

void GameView::updateHighscore(Ogre::Real timeSinceLastFrame)
{

    if(m_updateHighscoreFirstTime) {
        m_updateHighscoreFirstTime = false;
        getScoreForHighscore();
    }

    if(m_fadeHighscoreIn) {
        m_animationAlphaHighscore += 0.01;

        if(m_animationAlphaHighscore > 0.9) {
            m_fadeHighscoreIn = false;
            m_animationAlphaHighscore = 0.9;
        }

        setAlphaToHighscorePanels();
    }

    m_timeScaleHighscoreNum += timeSinceLastFrame;

    if(m_animationScaleHighscoreNumInvert) {
        m_animationPosHighscoreNum += 0.001;
    } else {
        m_animationPosHighscoreNum -= 0.001;
    }

    if(m_timeScaleHighscoreNum > 100) {
        m_timeScaleHighscoreNum = 0;
        m_animationScaleHighscoreNumInvert = !m_animationScaleHighscoreNumInvert;

        if(m_animationScaleHighscoreNumInvert) { //Dann ist man wieder am Anfang
            m_animationPosHighscoreNum = 0;
        }
    }

    switch(m_highscoreCharCount) {
        case 1:
            m_panelHighName1->setPosition(m_PosHighscoreName1Left, m_PosHighscoreName1Top + m_animationPosHighscoreNum);
            m_panelHighName2->setPosition(m_PosHighscoreName2Left, m_PosHighscoreName2Top);
            m_panelHighName3->setPosition(m_PosHighscoreName3Left, m_PosHighscoreName3Top);
            break;
        case 2:
            m_panelHighName1->setPosition(m_PosHighscoreName1Left, m_PosHighscoreName1Top);
            m_panelHighName2->setPosition(m_PosHighscoreName2Left, m_PosHighscoreName2Top + m_animationPosHighscoreNum);
            m_panelHighName3->setPosition(m_PosHighscoreName3Left, m_PosHighscoreName3Top);
            break;
        case 3:
            m_panelHighName1->setPosition(m_PosHighscoreName1Left, m_PosHighscoreName1Top);
            m_panelHighName2->setPosition(m_PosHighscoreName2Left, m_PosHighscoreName2Top);
            m_panelHighName3->setPosition(m_PosHighscoreName3Left, m_PosHighscoreName3Top + m_animationPosHighscoreNum);
            break;
    }

}

void GameView::updateHUDForDebug(Ogre::Real timeSinceLastFrame)
{
    // Update für Highscore
    m_score  = m_gameLogic->getScore();
    m_multiplier = m_gameLogic->getMultiplier();
    m_highscorePanel->setParamValue(0, Ogre::StringConverter::toString(m_score));
    m_highscorePanel->setParamValue(1, Ogre::StringConverter::toString(m_multiplier));
    // Update für Highscore end

    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    OgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);



    if(!OgreFramework::getSingletonPtr()->m_pTrayMgr->isDialogVisible()) {
        if(m_pDetailsPanel->isVisible()) {
            m_pDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(m_pCamera->getDerivedPosition().x));
            m_pDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(m_pCamera->getDerivedPosition().y));
            m_pDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(m_pCamera->getDerivedPosition().z));
            m_pDetailsPanel->setParamValue(3, Ogre::StringConverter::toString(m_pCamera->getDerivedOrientation().w));
            m_pDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(m_pCamera->getDerivedOrientation().x));
            m_pDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(m_pCamera->getDerivedOrientation().y));
            m_pDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(m_pCamera->getDerivedOrientation().z));

            if(m_bSettingsMode)
                m_pDetailsPanel->setParamValue(7, "Buffered Input");
            else
                m_pDetailsPanel->setParamValue(7, "Un-Buffered Input");
        }
    }
}

void GameView::updateScore()
{
    m_scoreOld  = m_score;
    m_score     = m_gameLogic->getScore();

    //Check if Score was reset
    if(m_scoreOld > m_score) {
        m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));
        m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));
        m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));
        m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));
        m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));
        m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));
    }

    String score = Ogre::StringConverter::toString(m_score);

    for(unsigned int i = 0; i < score.size(); i++) {

        int num = score.at(score.size() - 1 - i) - 48;

        switch(num) {
            case 0:

                switch(i) {
                    case 0:
                        m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 1:

                switch(i) {
                    case 0:
                        m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 2:

                switch(i) {
                    case 0:
                        m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 3:

                switch(i) {
                    case 0:
                        m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 4:

                switch(i) {
                    case 0:
                        m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 5:

                switch(i) {
                    case 0:
                        m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 6:

                switch(i) {
                    case 0:
                        m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 7:

                switch(i) {
                    case 0:
                        m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 8:

                switch(i) {
                    case 0:
                        m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 9:

                switch(i) {
                    case 0:
                        m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
        }
    }
}

void GameView::getScoreForHighscore()
{
    m_score     = m_gameLogic->getScore();

    String score = Ogre::StringConverter::toString(m_score);

    for(unsigned int i = 0; i < score.size(); i++) {

        int num = score.at(score.size() - 1 - i) - 48;

        switch(num) {
            case 0:

                switch(i) {
                    case 0:
                        m_panelHighNum1->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelHighNum2->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelHighNum3->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelHighNum4->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelHighNum5->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelHighNum6->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 1:

                switch(i) {
                    case 0:
                        m_panelHighNum1->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelHighNum2->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelHighNum3->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelHighNum4->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelHighNum5->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelHighNum6->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 2:

                switch(i) {
                    case 0:
                        m_panelHighNum1->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelHighNum2->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelHighNum3->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelHighNum4->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelHighNum5->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelHighNum6->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 3:

                switch(i) {
                    case 0:
                        m_panelHighNum1->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelHighNum2->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelHighNum3->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelHighNum4->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelHighNum5->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelHighNum6->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 4:

                switch(i) {
                    case 0:
                        m_panelHighNum1->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelHighNum2->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelHighNum3->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelHighNum4->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelHighNum5->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelHighNum6->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 5:

                switch(i) {
                    case 0:
                        m_panelHighNum1->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelHighNum2->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelHighNum3->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelHighNum4->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelHighNum5->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelHighNum6->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 6:

                switch(i) {
                    case 0:
                        m_panelHighNum1->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelHighNum2->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelHighNum3->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelHighNum4->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelHighNum5->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelHighNum6->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 7:

                switch(i) {
                    case 0:
                        m_panelHighNum1->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelHighNum2->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelHighNum3->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelHighNum4->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelHighNum5->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelHighNum6->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 8:

                switch(i) {
                    case 0:
                        m_panelHighNum1->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelHighNum2->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelHighNum3->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelHighNum4->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelHighNum5->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelHighNum6->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 9:

                switch(i) {
                    case 0:
                        m_panelHighNum1->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelHighNum2->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 2:
                        m_panelHighNum3->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 3:
                        m_panelHighNum4->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 4:
                        m_panelHighNum5->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                    case 5:
                        m_panelHighNum6->setMaterialName(m_materialNameHighscoreNumbers + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
        }
    }
}

void GameView::updateMultiplier(Ogre::Real timeSinceLastFrame)
{
    m_multiplierOld = m_multiplier;
    m_multiplier    = m_gameLogic->getMultiplier();

    if(m_multiplierOld < m_multiplier) {
        m_scaleMultiplier = true;
    }

    //Animation
    if(m_scaleMultiplier) {
        m_timeScaleMultiplier += timeSinceLastFrame;

        if(m_timeScaleMultiplier < 200) {
            m_animationScaleMultiplier += 0.1;
            m_panelMult1->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(m_animationScaleMultiplier, m_animationScaleMultiplier);
            m_panelMult2->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(m_animationScaleMultiplier, m_animationScaleMultiplier);
            m_panelX->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(m_animationScaleMultiplier, m_animationScaleMultiplier);

        } else {
            m_animationScaleMultiplier -= 0.1;
            m_panelMult1->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(m_animationScaleMultiplier, m_animationScaleMultiplier);
            m_panelMult2->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(m_animationScaleMultiplier, m_animationScaleMultiplier);
            m_panelX->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(m_animationScaleMultiplier, m_animationScaleMultiplier);

            if(m_timeScaleMultiplier > 200) {
                m_timeScaleMultiplier = 0;
                m_scaleMultiplier = false;
                //Rücksetzen der Panels
                m_animationScaleMultiplier = 1;
                m_panelMult1->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(m_animationScaleMultiplier, m_animationScaleMultiplier);
                m_panelMult2->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(m_animationScaleMultiplier, m_animationScaleMultiplier);
                m_panelX->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(m_animationScaleMultiplier, m_animationScaleMultiplier);

            }
        }
    }

    String multiplier = Ogre::StringConverter::toString(m_multiplier);

    if(multiplier.size() < 2) {
        m_panelMult1->setPosition(m_PosMult1Left - 0.03, m_PosMult1Top); //Panel ist am Anfang näher beim x
        m_panelMult2->hide();
    } else {
        m_panelMult1->setPosition(m_PosMult1Left, m_PosMult1Top);
        m_panelMult2->show();
    }

    for(unsigned int i = 0; i < multiplier.size(); i++) {
        int num = multiplier.at(multiplier.size() - 1 - i) - 48;

        switch(num) {
            case 0:

                switch(i) {
                    case 0:
                        m_panelMult1->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelMult2->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 1:

                switch(i) {
                    case 0:
                        m_panelMult1->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelMult2->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 2:

                switch(i) {
                    case 0:
                        m_panelMult1->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelMult2->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 3:

                switch(i) {
                    case 0:
                        m_panelMult1->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelMult2->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 4:

                switch(i) {
                    case 0:
                        m_panelMult1->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelMult2->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 5:

                switch(i) {
                    case 0:
                        m_panelMult1->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelMult2->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 6:

                switch(i) {
                    case 0:
                        m_panelMult1->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelMult2->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 7:

                switch(i) {
                    case 0:
                        m_panelMult1->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelMult2->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 8:

                switch(i) {
                    case 0:
                        m_panelMult1->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelMult2->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
            case 9:

                switch(i) {
                    case 0:
                        m_panelMult1->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                    case 1:
                        m_panelMult2->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(num));
                        break;
                }

                break;
        }
    }
}

void GameView::updateHUD(Ogre::Real timeSinceLastFrame)
{

    updateScore();
    updateMultiplier(timeSinceLastFrame);

    //Update der Anzeige
    m_levelProgress = (int) (m_gameLogic->getProgress() * 10);  //Funktioniert aber nicht richtig mit dem Level Begin!!!!!
    m_boostCharge = (int) (m_gameLogic->getBoostLevel() * 10);

    /*
    //Testweiße muss noch umbestellt werden
    m_timeHighscoreTest += timeSinceLastFrame;
    if(m_timeHighscoreTest > 20000) {
        m_showHighscore = true;
    }
    */

    if(m_levelProgress == 10) {
        m_showHighscore = true;
    }

    m_timeScaleBoost += timeSinceLastFrame;

    if(m_animationScaleBoostInvert) {
        m_animationScaleBoost += 0.0002 * m_boostCharge;
    } else {
        m_animationScaleBoost -= 0.0002 * m_boostCharge;
    }

    if(m_timeScaleBoost > 180) {
        m_timeScaleBoost = 0;
        m_animationScaleBoostInvert = !m_animationScaleBoostInvert;

        if(m_animationScaleBoostInvert) { //Dann ist man wieder am Anfang
            m_animationScaleBoost = 0.95;
        }
    }

    //Geht auch!!
    //m_materialBoost->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(m_scale,m_scale);
    m_overlayBoost->setScale(m_animationScaleBoost, m_animationScaleBoost);

    switch(m_boostCharge) {
        case 0:
            m_panelBoost->setMaterialName(m_materialNameBoostBar + "00");
            break;
        case 1:
            m_panelBoost->setMaterialName(m_materialNameBoostBar + "01");
            break;
        case 2:
            m_panelBoost->setMaterialName(m_materialNameBoostBar + "02");
            break;
        case 3:
            m_panelBoost->setMaterialName(m_materialNameBoostBar + "03");
            break;
        case 4:
            m_panelBoost->setMaterialName(m_materialNameBoostBar + "04");
            break;
        case 5:
            m_panelBoost->setMaterialName(m_materialNameBoostBar + "05");
            break;
        case 6:
            m_panelBoost->setMaterialName(m_materialNameBoostBar + "06");
            break;
        case 7:
            m_panelBoost->setMaterialName(m_materialNameBoostBar + "07");
            break;
        case 8:
            m_panelBoost->setMaterialName(m_materialNameBoostBar + "08");
            break;
        case 9:
            m_panelBoost->setMaterialName(m_materialNameBoostBar + "09");
            break;
        case 10:
            m_panelBoost->setMaterialName(m_materialNameBoostBar + "10");
            break;
    }

    switch(m_levelProgress) {
        case 0:
            m_panelTrack->setMaterialName(m_materialNameTrack + "00");
            break;
        case 1:
            m_panelTrack->setMaterialName(m_materialNameTrack + "01");
            break;
        case 2:
            m_panelTrack->setMaterialName(m_materialNameTrack + "02");
            break;
        case 3:
            m_panelTrack->setMaterialName(m_materialNameTrack + "03");
            break;
        case 4:
            m_panelTrack->setMaterialName(m_materialNameTrack + "04");
            break;
        case 5:
            m_panelTrack->setMaterialName(m_materialNameTrack + "05");
            break;
        case 6:
            m_panelTrack->setMaterialName(m_materialNameTrack + "06");
            break;
        case 7:
            m_panelTrack->setMaterialName(m_materialNameTrack + "07");
            break;
        case 8:
            m_panelTrack->setMaterialName(m_materialNameTrack + "08");
            break;
        case 9:
            m_panelTrack->setMaterialName(m_materialNameTrack + "09");
            break;
        case 10:
            m_panelTrack->setMaterialName(m_materialNameTrack + "10");
            break;
    }


    if(m_waitForHUDToFadeIn) {
        m_timeToWaitForHUDToFadeIn += timeSinceLastFrame;

        if(m_timeToWaitForHUDToFadeIn >= 4000) {
            m_fadeHUDIn = true;
            m_waitForHUDToFadeIn = false;
        }

        setAlphaToAllHUDPanels();
    }

    //Fade In
    if(m_fadeHUDIn) {
        if(m_animationAlphaHUD < 1) {
            m_animationAlphaHUD += 0.01;
            setAlphaToAllHUDPanels();
        } else {
            m_animationAlphaHUD = 1.0;
            m_fadeHUDIn = false;
            setAlphaToAllHUDPanels();
            setAlphaToAllHUDMaterials();    //Bis jetzt nur alle boost Materials
        }
    }

    //Fade in End

    /*
    //Test für die Positionierung des Panels
    //Geht!!!
    m_positionLogo += 0.0001;
    m_panelLogo->_setPosition(0.6+m_positionLogo,0.6-m_positionLogo);
    */
}

void GameView::setAlphaToStartMenuPanels()
{
    m_panelLogo->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaStartMenu);
    m_panelStartBack->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaStartMenu);
}

void GameView::setAlphaToAllHUDMaterials()
{
    MaterialManager* materialManager = Ogre::MaterialManager::getSingletonPtr();
    ((MaterialPtr) materialManager->getByName(m_materialNameBoostBar + "00"))->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    ((MaterialPtr) materialManager->getByName(m_materialNameBoostBar + "01"))->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    ((MaterialPtr) materialManager->getByName(m_materialNameBoostBar + "02"))->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    ((MaterialPtr) materialManager->getByName(m_materialNameBoostBar + "03"))->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    ((MaterialPtr) materialManager->getByName(m_materialNameBoostBar + "04"))->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    ((MaterialPtr) materialManager->getByName(m_materialNameBoostBar + "05"))->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    ((MaterialPtr) materialManager->getByName(m_materialNameBoostBar + "06"))->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    ((MaterialPtr) materialManager->getByName(m_materialNameBoostBar + "07"))->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    ((MaterialPtr) materialManager->getByName(m_materialNameBoostBar + "08"))->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    ((MaterialPtr) materialManager->getByName(m_materialNameBoostBar + "09"))->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    ((MaterialPtr) materialManager->getByName(m_materialNameBoostBar + "10"))->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);

}

void GameView::setAlphaToAllHUDPanels()
{
    m_panelTrack->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    m_panelX->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    m_panelNum1->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    m_panelNum2->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    m_panelNum3->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    m_panelNum4->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    m_panelNum5->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    m_panelNum6->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    m_panelBoost->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    m_panelMult1->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);
    m_panelMult2->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHUD);

}

void GameView::setAlphaToHighscorePanels()
{
    m_panelHighscore->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHighscore);
    m_panelHighNum1->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHighscore);
    m_panelHighNum2->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHighscore);
    m_panelHighNum3->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHighscore);
    m_panelHighNum4->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHighscore);
    m_panelHighNum5->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHighscore);
    m_panelHighNum6->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHighscore);
    m_panelHighName1->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHighscore);
    m_panelHighName2->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHighscore);
    m_panelHighName3->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, m_animationAlphaHighscore);
}

void GameView::resumeGame()
{
    createHUDForDebug();        //Wird nämlich im Pause-State zerstört

    if (m_showHUD) {
        showAllHUDElements();
        OgreFramework::getSingletonPtr()->m_pTrayMgr->hideAll();
        OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();

        //Fade In
        m_fadeHUDIn = true;
        m_animationAlphaHUD  = 0;
        setAlphaToAllHUDPanels();
    }
}

void GameView::pauseGame()
{
    if(m_showHUD) {
        hideAllHUDElements();
        OgreFramework::getSingletonPtr()->m_pTrayMgr->showAll();
    }

}

void GameView::showAllHUDElements()
{
    m_panelLogo->show();
    m_panelNum1->show();
    m_panelNum2->show();
    m_panelNum3->show();
    m_panelNum4->show();
    m_panelNum5->show();
    m_panelNum6->show();
    m_panelMult1->show();
    m_panelMult2->show();
    m_panelTrack->show();
    m_panelBoost->show();
    m_panelX->show();

    m_panelHighscore->show();
    m_panelHighName1->show();
    m_panelHighName2->show();
    m_panelHighName3->show();
    m_panelHighNum1->show();
    m_panelHighNum2->show();
    m_panelHighNum3->show();
    m_panelHighNum4->show();
    m_panelHighNum5->show();
    m_panelHighNum6->show();
}

void GameView::hideAllHUDElements()
{
    m_panelLogo->hide();
    m_panelNum1->hide();
    m_panelNum2->hide();
    m_panelNum3->hide();
    m_panelNum4->hide();
    m_panelNum5->hide();
    m_panelNum6->hide();
    m_panelMult1->hide();
    m_panelMult2->hide();
    m_panelTrack->hide();
    m_panelBoost->hide();
    m_panelX->hide();

    m_panelHighscore->hide();
    m_panelHighName1->hide();
    m_panelHighName2->hide();
    m_panelHighName3->hide();
    m_panelHighNum1->hide();
    m_panelHighNum2->hide();
    m_panelHighNum3->hide();
    m_panelHighNum4->hide();
    m_panelHighNum5->hide();
    m_panelHighNum6->hide();
}

void GameView::keyPressed(const OIS::KeyEvent& keyEventRef)
{
    OIS::Keyboard* myKeyboard = OgreFramework::getSingletonPtr()->m_pKeyboard;

    if(m_showHighscore) {
        unsigned int myKeyCode = keyEventRef.text;

        if(myKeyCode >= 65 && myKeyCode <= 90 || myKeyCode >= 97 && myKeyCode <= 154) {

            if(myKeyCode >= 97) {
                myKeyCode -= 32;
            }

            switch (m_highscoreCharCount) {
                case 1:
                    m_panelHighName1->setMaterialName(m_materialNameHighscoreName + Ogre::StringConverter::toString(myKeyCode));
                    break;
                case 2:
                    m_panelHighName2->setMaterialName(m_materialNameHighscoreName + Ogre::StringConverter::toString(myKeyCode));
                    break;
                case 3:
                    m_panelHighName3->setMaterialName(m_materialNameHighscoreName + Ogre::StringConverter::toString(myKeyCode));
                    break;
            }

            m_highscoreCharCount += 1;

            if(m_highscoreCharCount > 3) {
                m_highscoreCharCount = 1;
            }

            setAlphaToHighscorePanels();    //Damit die neuen Buchstaben auch wieder transparent sind
        }
    } else {

        if(myKeyboard->isKeyDown(OIS::KC_RETURN)) {
            m_stopAtStart = false;
        }

        if(myKeyboard->isKeyDown(OIS::KC_L)) {
            m_showHUD = !m_showHUD;

            if(m_showHUD) {
                showAllHUDElements();
                OgreFramework::getSingletonPtr()->m_pTrayMgr->hideAll();
                OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();

                //Fade in
                m_fadeHUDIn = true;
                m_animationAlphaHUD  = 0;
                setAlphaToAllHUDPanels();

            } else {
                OgreFramework::getSingletonPtr()->m_pTrayMgr->showAll();
                hideAllHUDElements();
            }
        }
    }
}

void GameView::mouseMoved(const OIS::MouseEvent& evt)
{
    if(m_showStartMenu) {
        int displayWidth = evt.state.width;
        int displayHeight = evt.state.height;
        int xAbs = evt.state.X.abs;
        int yAbs = evt.state.Y.abs;

        if( xAbs >= ((int) (displayWidth * 0.22)) && xAbs <= ((int) (displayWidth * 0.78)) &&
            yAbs >= ((int) (displayHeight * 0.58)) && yAbs <= ((int) (displayHeight * 0.69))) {
            m_panelStartBack->setMaterialName(m_materialNameStartBackground + "Active");
            m_enterGameSelected = true;
        } else {
            m_panelStartBack->setMaterialName(m_materialNameStartBackground);
            m_enterGameSelected = false;
        }
    }
}

void GameView::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
    if(m_enterGameSelected) {
        m_stopAtStart = false;
    }
}

bool GameView::getHighscoreShown()
{
    return m_showHighscore;
}

OgreBites::ParamsPanel* GameView::getHighscorePanel()
{
    return m_highscorePanel;
}


//Eventuell noch ins KeyPressed reingeben - falls benötigt
//--------------------------------------------------------
/*
    if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_I))
    {
        if(m_pDetailsPanel->getTrayLocation() == OgreBites::TL_NONE)
        {
            OgreFramework::getSingletonPtr()->m_pTrayMgr->moveWidgetToTray(m_pDetailsPanel, OgreBites::TL_TOPLEFT, 0);
            m_pDetailsPanel->show();
        }
        else
        {
            OgreFramework::getSingletonPtr()->m_pTrayMgr->removeWidgetFromTray(m_pDetailsPanel);
            m_pDetailsPanel->hide();
        }
    }

    if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_TAB))
    {
        m_bSettingsMode = !m_bSettingsMode;
        return true;
    }

    if((m_bSettingsMode && OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_RETURN)) ||
       (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_NUMPADENTER)))
    {
    }

    if(!m_bSettingsMode || (m_bSettingsMode && !OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_O)))
        OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
        */

/*
    if(m_bSettingsMode == true)
    {
        if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_S))
        {
            OgreBites::SelectMenu* pMenu = (OgreBites::SelectMenu*)OgreFramework::getSingletonPtr()->m_pTrayMgr->getWidget("ChatModeSelMenu");
            if(pMenu->getSelectionIndex() + 1 < (int)pMenu->getNumItems())
                pMenu->selectItem(pMenu->getSelectionIndex() + 1);
        }

        if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_W))
        {
            OgreBites::SelectMenu* pMenu = (OgreBites::SelectMenu*)OgreFramework::getSingletonPtr()->m_pTrayMgr->getWidget("ChatModeSelMenu");
            if(pMenu->getSelectionIndex() - 1 >= 0)
                pMenu->selectItem(pMenu->getSelectionIndex() - 1);
        }
    }
    */
//--------------------------------------------------------
