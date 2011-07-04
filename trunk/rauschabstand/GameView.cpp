//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameView.hpp"

#include <OgreOverlayManager.h>
#include <OgreMaterialManager.h>

//|||||||||||||||||||||||||||||||||||||||||||||||
GameView::GameView() {
    m_showHUD           = true;    //false = Debug Hud

    m_highscorePanel    = 0;
    m_gameLogic         = 0;
    m_score             = 0;
    m_scoreOld          = 0;
    m_multiplier        = 0;

    m_sceneManager      = 0;

    
    m_pDetailsPanel		= 0;
    m_bSettingsMode     = false;

    //Material Names
    m_materialNameBoostBar  = "BoostBar";
    m_materialNameLogo      = "Logo";
    m_materialNameTrack     = "Track";
    m_materialNameNumbers   = "Numbers";
    m_materialNameX         = "X";
    m_materialNameMult      = "Multiplikator";
    m_materialNameHighscore = "Highscore";

    //Visuals
    m_timeTest          = 0;
    m_scale             = 0.9;
    m_scaleInvert       = false;

    m_overlayBoost      = 0;
    
    m_panelLogo         = 0;
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

    m_positionLogo      = 0;

    //Positionierung der Einzelnen Overlays
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
        //Logo------------
    m_PosLogoLeft       = 0.2;
    m_PosLogoTop        = 0.85;
    m_DimLogoWidth      = 0.8;
    m_DimLogoHeight     = 0;
    m_PixelLogoWidth    = 3543;
    m_PixelLogoHeight   = 591;
        //Logo End--------
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
    m_PosHighscoreLeft  = 0.2;
    m_PosHighscoreTop   = 0.1;
    m_DimHighscoreWidth = 0.8;
    m_DimHighscoreHeight    = 0;
    m_PixelHighscoreWidth   = 1500;
    m_PixelHighscoreHeight  = 1500;
        //Highscore End---

    //Fade In
     m_alpha            = 0;
     m_fadeIn           = true;

    //Test
    m_boostCharge       = 0;
    m_levelProgress     = 0;
    m_timeHighscoreTest = 0;
}

GameView::~GameView() {
   
}

void GameView::engage(GameLogic* gameLogic, Ogre::SceneManager* sceneManager, Ogre::Camera* pCamera,Ogre::FrameEvent FrameEvent) {

    m_sceneManager  = sceneManager;
    m_gameLogic     = gameLogic;
    m_pCamera       = pCamera;
    m_FrameEvent    = FrameEvent;

    createHUDForDebug();
    createHUD();
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
}

void GameView::disengage() {

}

void GameView::createHUDForDebug() {
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

void GameView::createHUD() {
    OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

    createAllMaterials();
    calculateDimensions();
    //Boost-Balken
    //------------
    // Create a panel
    m_panelBoost = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "Panel_Boost"));
    m_panelBoost->setPosition(m_PosBoostLeft, m_PosBoostTop);
    m_panelBoost->setDimensions(m_DimBoostWidth, m_DimBoostHeight);
    m_panelBoost->setMaterialName(m_materialNameBoostBar+"00");

    // Create an overlay, and add the panel
    m_overlayBoost = overlayManager.create("Overlay_Boost");
    m_overlayBoost->add2D(m_panelBoost);
    m_overlayBoost->show();
    m_overlayBoost->setScale(m_scale,m_scale);
    //------------
    //Boost-Balken - End


    //Track - Balken
    //--------------
    // Create a panel
    m_panelTrack = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "Panel_Track"));
    m_panelTrack->setPosition(m_PosTrackLeft, m_PosTrackTop);
    m_panelTrack->setDimensions(m_DimTrackWidth, m_DimTrackHeight);
    m_panelTrack->setMaterialName(m_materialNameTrack+"00");

    // Create an overlay, and add the panel
    Overlay* overlayTrack = overlayManager.create("Overlay_Track");
    overlayTrack->add2D(m_panelTrack);
    overlayTrack->show();
    //--------------
    //Track - Balken END

    //Logo
    //----
    // Create a panel
    m_panelLogo = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "Panel_Logo"));
    m_panelLogo->setPosition(m_PosLogoLeft, m_PosLogoTop);
    m_panelLogo->setDimensions(m_DimLogoWidth, m_DimLogoHeight);
    m_panelLogo->setMaterialName(m_materialNameLogo);

    // Create an overlay, and add the panel
    Overlay* overlayLogo = overlayManager.create("Overlay_Logo");
    overlayLogo->add2D(m_panelLogo);
    overlayLogo->show();
    //Logo End

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
    overlayNum = overlayManager.create("Overlay_Mult1");
    overlayNum->add2D(m_panelMult1);
    overlayNum->show();

    m_panelMult2 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelMult2"));
    m_panelMult2->setPosition(m_PosMult2Left, m_PosMult2Top);
    m_panelMult2->setDimensions(m_DimMultWidth, m_DimMultHeight);
    m_panelMult2->setMaterialName(m_materialNameMult + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0

    // Create an overlay, and add the panel
    overlayNum = overlayManager.create("Overlay_Mult2");
    overlayNum->add2D(m_panelMult2);
    overlayNum->show();
    //Multiplikator End

    //X
    //----
    // Create a panel
    m_panelX = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "Panel_X"));
    m_panelX->setPosition(m_PosXLeft, m_PosXTop);
    m_panelX->setDimensions(m_DimXWidth, m_DimXHeight);
    m_panelX->setMaterialName(m_materialNameX);

    // Create an overlay, and add the panel
    Overlay* overlayX = overlayManager.create("Overlay_X");
    overlayX->add2D(m_panelX);
    overlayX->show();
    //X End

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
    //overlayHighscore->show();
    //Highscore Background End

}

void GameView::calculateDimensions() {
    
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
    }
    else if (ratio < 1) {   //=Kommt eigentlich nicht vor Mehr höhe als breite
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
        m_DimLogoWidth = 1/ ratio * m_DimLogoWidth;
    } else if (ratio < 1) {
        //Zuerzeit nicht vorgesehen
    }
    //Logo End----------

    //Numbers-----------
    double ratioNumbers = ((double) m_PixelNumWidth) / m_PixelNumHeight;
    m_DimNumHeight = 1 / ratioNumbers * m_DimNumWidth;
    if(ratio > 1) {
        m_DimNumWidth = 1/ ratio * m_DimNumWidth;
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
        m_DimMultWidth = 1/ ratio * m_DimMultWidth;
    } else if (ratio < 1) {
        //Zuerzeit nicht vorgesehen
    }
    //Multiplikaotr End-------

    //Highscore-----------
    double ratioHighscore = ((double) m_PixelHighscoreWidth) / m_PixelHighscoreHeight;
    m_DimHighscoreHeight = 1 / ratioHighscore * m_DimHighscoreWidth;
    if(ratio > 1) {
        m_DimHighscoreWidth = 1/ ratio * m_DimHighscoreWidth;
    } else if (ratio < 1) {
        //Zuerzeit nicht vorgesehen
    }
    //Multiplikaotr End-------
}

void GameView::createAllMaterials() {
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
        }
        else {
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
        }
        else {
            material = materialManager.create(m_materialNameTrack + Ogre::StringConverter::toString(i), "General");
            material->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/Track" + Ogre::StringConverter::toString(i) + "-02.png");
            material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
            material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
            material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
            material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
        }
    }
    // ---------------------

    // Create Logo material
    // ---------------------
    material = materialManager.create(m_materialNameLogo, "General");
    material->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/Logo.jpg");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    //material->setFog(true,Ogre::FogMode::FOG_EXP,Ogre::ColourValue::Blue,0.4,0,1);  //Test
    //Funktioniert
    //material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LayerBlendOperationEx::LBX_MODULATE,Ogre::LayerBlendSource::LBS_MANUAL,Ogre::LayerBlendSource::LBS_TEXTURE,0.5);
    
    //material->setFog(true,FogMode::FOG_LINEAR,Ogre::ColourValue::ColourValue(1.0f, 1.0f,1.0f, 0.5f),0.4,0,1);
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
    material->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/Highscore_Background.png");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    //------------------
}

void GameView::update(Ogre::Real timeSinceLastFrame) {
    m_timeHighscoreTest += timeSinceLastFrame;
    if(m_timeHighscoreTest > 20000) {
        m_highscorePanel->show();
    }

    if (m_showHUD) {
        updateHUD(timeSinceLastFrame);
    }
    else {
        updateHUDForDebug(timeSinceLastFrame);
    }
}

void GameView::updateHUDForDebug(Ogre::Real timeSinceLastFrame) {
    // Update für Highscore
    m_score  = m_gameLogic->getScore();
    m_multiplier = m_gameLogic->getMultiplier();
    m_highscorePanel->setParamValue(0, Ogre::StringConverter::toString(m_score));
    m_highscorePanel->setParamValue(1, Ogre::StringConverter::toString(m_multiplier));
    // Update für Highscore end

    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    OgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);

    
    
    if(!OgreFramework::getSingletonPtr()->m_pTrayMgr->isDialogVisible())
    {
        if(m_pDetailsPanel->isVisible())
        {
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

void GameView::updateScore() {
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

        int num = score.at(score.size()-1-i) - 48;
  
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

void GameView::updateMultiplier() {
    m_multiplier = m_gameLogic->getMultiplier();
    String multiplier = Ogre::StringConverter::toString(m_multiplier);

    if(multiplier.size() < 2) {
        m_panelMult1->setPosition(m_PosMult1Left - 0.03, m_PosMult1Top); //Panel ist am Anfang näher beim x
        m_panelMult2->hide();
    } else {
        m_panelMult1->setPosition(m_PosMult1Left, m_PosMult1Top);
        m_panelMult2->show();
    }

    for(unsigned int i = 0; i < multiplier.size(); i++) {
        int num = multiplier.at(multiplier.size()-1-i) - 48;

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

void GameView::updateHUD(Ogre::Real timeSinceLastFrame) {
    
    updateScore();
    updateMultiplier();

    m_timeTest += timeSinceLastFrame;
    if(m_scaleInvert) {
        m_scale += 0.0005;
    }
    else {
        m_scale -= 0.0005;
    }
    if(m_timeTest > 1000) {
        m_timeTest = 0;
        m_scaleInvert = !m_scaleInvert;

        //Test
        m_boostCharge++;
        if(m_boostCharge > 10) { m_boostCharge = 0;}

        m_levelProgress++;
        if(m_levelProgress > 10) { m_levelProgress = 0;}
    }
    
    //Geht auch!!
    //m_materialBoost->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(m_scale,m_scale);
    m_overlayBoost->setScale(m_scale,m_scale);

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


    //Fade In
    if(m_alpha < 1 && m_fadeIn) {
        m_alpha += 0.01;
        setAlphaToAllPanels();
    }
    else {
        m_alpha = 1.0;
        m_fadeIn = false;
        setAlphaToAllPanels();
    }
    //Fade in End

    /*
    //Test für die Positionierung des Panels
    //Geht!!!
    m_positionLogo += 0.0001;
    m_panelLogo->_setPosition(0.6+m_positionLogo,0.6-m_positionLogo);
    */
}

void GameView::setAlphaToAllPanels() {
    m_panelTrack->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LayerBlendOperationEx::LBX_MODULATE,Ogre::LayerBlendSource::LBS_MANUAL,Ogre::LayerBlendSource::LBS_TEXTURE,m_alpha);
    m_panelX->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LayerBlendOperationEx::LBX_MODULATE,Ogre::LayerBlendSource::LBS_MANUAL,Ogre::LayerBlendSource::LBS_TEXTURE,m_alpha);
    m_panelNum1->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LayerBlendOperationEx::LBX_MODULATE,Ogre::LayerBlendSource::LBS_MANUAL,Ogre::LayerBlendSource::LBS_TEXTURE,m_alpha);
    m_panelNum2->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LayerBlendOperationEx::LBX_MODULATE,Ogre::LayerBlendSource::LBS_MANUAL,Ogre::LayerBlendSource::LBS_TEXTURE,m_alpha);
    m_panelNum3->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LayerBlendOperationEx::LBX_MODULATE,Ogre::LayerBlendSource::LBS_MANUAL,Ogre::LayerBlendSource::LBS_TEXTURE,m_alpha);
    m_panelNum4->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LayerBlendOperationEx::LBX_MODULATE,Ogre::LayerBlendSource::LBS_MANUAL,Ogre::LayerBlendSource::LBS_TEXTURE,m_alpha);
    m_panelNum5->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LayerBlendOperationEx::LBX_MODULATE,Ogre::LayerBlendSource::LBS_MANUAL,Ogre::LayerBlendSource::LBS_TEXTURE,m_alpha);
    m_panelNum6->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LayerBlendOperationEx::LBX_MODULATE,Ogre::LayerBlendSource::LBS_MANUAL,Ogre::LayerBlendSource::LBS_TEXTURE,m_alpha);
    m_panelBoost->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LayerBlendOperationEx::LBX_MODULATE,Ogre::LayerBlendSource::LBS_MANUAL,Ogre::LayerBlendSource::LBS_TEXTURE,m_alpha);
    m_panelLogo->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LayerBlendOperationEx::LBX_MODULATE,Ogre::LayerBlendSource::LBS_MANUAL,Ogre::LayerBlendSource::LBS_TEXTURE,m_alpha);
    m_panelMult1->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LayerBlendOperationEx::LBX_MODULATE,Ogre::LayerBlendSource::LBS_MANUAL,Ogre::LayerBlendSource::LBS_TEXTURE,m_alpha);
    m_panelMult2->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LayerBlendOperationEx::LBX_MODULATE,Ogre::LayerBlendSource::LBS_MANUAL,Ogre::LayerBlendSource::LBS_TEXTURE,m_alpha);
}

void GameView::resumeGame() {
    createHUDForDebug();        //Wird nämlich im Pause-State zerstört
    if (m_showHUD) {
        showAllHUDElements();
        OgreFramework::getSingletonPtr()->m_pTrayMgr->hideAll();
        OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();

        //Fade In
        m_fadeIn = true;
        m_alpha  = 0;
        setAlphaToAllPanels();
    }
}

void GameView::pauseGame() {
    if(m_showHUD) {
        hideAllHUDElements();
        OgreFramework::getSingletonPtr()->m_pTrayMgr->showAll();
    }

}

void GameView::showAllHUDElements() {
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
}

void GameView::hideAllHUDElements() {
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
}

void GameView::keyPressed() {

    if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_L)) {
        m_showHUD = !m_showHUD;

        if(m_showHUD) {
            showAllHUDElements();
            OgreFramework::getSingletonPtr()->m_pTrayMgr->hideAll();
            OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();

            //Fade in
            m_fadeIn = true;
            m_alpha  = 0;
            setAlphaToAllPanels();

        } else {
            OgreFramework::getSingletonPtr()->m_pTrayMgr->showAll();
            hideAllHUDElements();
        }
    }
}

OgreBites::ParamsPanel* GameView::getHighscorePanel() {
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