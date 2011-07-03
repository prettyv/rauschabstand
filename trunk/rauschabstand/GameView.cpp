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
    m_multiplier        = 0;

    m_sceneManager      = 0;

    
    m_pDetailsPanel		= 0;
    m_bSettingsMode     = false;

    //Material Names
    m_materialNameBoostBar  = "BoostBar";
    m_materialNameLogo      = "Logo";
    m_materialNameTrack     = "Track";
    m_materialNameNumbers   = "Numbers";

    //Visuals
    m_timeTest          = 0;
    m_scale             = 0.9;
    m_scaleInvert       = false;

    m_overlayBoost      = 0;
    
    m_panelLogo         = 0;
    m_panelBoost        = 0;
    m_panelTrack        = 0;

    m_panelNum1         = 0;
    m_panelNum2         = 0;
    m_panelNum3         = 0;
    m_panelNum4         = 0;
    m_panelNum5         = 0;
    m_panelNum6         = 0;

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

    m_DimNumWidth       = 0.1;
    m_DimNumHeight      = 0;
    m_PixelNumWidth     = 200;
    m_PixelNumHeight    = 200;
        //Numbers End-----

    //Test
    m_boostCharge       = 0;
    m_levelProgress     = 0;
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
    Overlay* overlayNum;

    m_panelNum1 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelNum1"));
    m_panelNum1->setPosition(m_PosNum1Left, m_PosNum1Top);
    m_panelNum1->setDimensions(m_DimNumWidth, m_DimNumHeight);
    m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0

    // Create an overlay, and add the panel
    overlayNum = overlayManager.create("Overlay_Num1");
    overlayLogo->add2D(m_panelNum1);
    overlayLogo->show();

    m_panelNum2 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelNum2"));
    m_panelNum2->setPosition(m_PosNum2Left, m_PosNum2Top);
    m_panelNum2->setDimensions(m_DimNumWidth, m_DimNumHeight);
    m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0

    // Create an overlay, and add the panel
    overlayNum = overlayManager.create("Overlay_Num2");
    overlayLogo->add2D(m_panelNum2);
    overlayLogo->show();

    m_panelNum3 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelNum3"));
    m_panelNum3->setPosition(m_PosNum3Left, m_PosNum3Top);
    m_panelNum3->setDimensions(m_DimNumWidth, m_DimNumHeight);
    m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0

    // Create an overlay, and add the panel
    overlayNum = overlayManager.create("Overlay_Num3");
    overlayLogo->add2D(m_panelNum3);
    overlayLogo->show();

    m_panelNum4 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelNum4"));
    m_panelNum4->setPosition(m_PosNum4Left, m_PosNum4Top);
    m_panelNum4->setDimensions(m_DimNumWidth, m_DimNumHeight);
    m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0

    // Create an overlay, and add the panel
    overlayNum = overlayManager.create("Overlay_Num4");
    overlayLogo->add2D(m_panelNum4);
    overlayLogo->show();

    m_panelNum5 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelNum5"));
    m_panelNum5->setPosition(m_PosNum5Left, m_PosNum5Top);
    m_panelNum5->setDimensions(m_DimNumWidth, m_DimNumHeight);
    m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0

    // Create an overlay, and add the panel
    overlayNum = overlayManager.create("Overlay_Num5");
    overlayLogo->add2D(m_panelNum5);
    overlayLogo->show();

    m_panelNum6 = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelNum6"));
    m_panelNum6->setPosition(m_PosNum6Left, m_PosNum6Top);
    m_panelNum6->setDimensions(m_DimNumWidth, m_DimNumHeight);
    m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(0));   //Es steht am Anfang überall 0

    // Create an overlay, and add the panel
    overlayNum = overlayManager.create("Overlay_Num6");
    overlayLogo->add2D(m_panelNum6);
    overlayLogo->show();
    //Number for Points End

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
    //material->setFog(true,Ogre::FogMode::FOG_EXP,Ogre::ColourValue::Blue,0.4,0,1);  //Test
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
}

void GameView::update(Ogre::Real timeSinceLastFrame) {
    
    if (m_showHUD) {
        updateHUD(timeSinceLastFrame);
        updateScore();
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
    m_score  = m_gameLogic->getScore();
    m_multiplier = m_gameLogic->getMultiplier();
    String score = Ogre::StringConverter::toString(m_score);

    for(unsigned int i = 0; i < score.size(); i++) {
        //int test = 3;
        int test = score.at(score.size()-1-i) - 48;
  
        switch(test) {
        case 0:
            switch(i) {
            case 0:
                m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 1:
                m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 2:
                m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 3:
                m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 4:
                m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 5:
                m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            }
            break;
        case 1:
            switch(i) {
            case 0:
                m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 1:
                m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 2:
                m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 3:
                m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 4:
                m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 5:
                m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            }
            break;
        case 2:
            switch(i) {
            case 0:
                m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 1:
                m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 2:
                m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 3:
                m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 4:
                m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 5:
                m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            }
            break;
        case 3:
            switch(i) {
            case 0:
                m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 1:
                m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 2:
                m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 3:
                m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 4:
                m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 5:
                m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            }
            break;
        case 4:
            switch(i) {
            case 0:
                m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 1:
                m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 2:
                m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 3:
                m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 4:
                m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 5:
                m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            }
            break;
        case 5:
            switch(i) {
            case 0:
                m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 1:
                m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 2:
                m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 3:
                m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 4:
                m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 5:
                m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            }
            break;
        case 6:
            switch(i) {
            case 0:
                m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 1:
                m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 2:
                m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 3:
                m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 4:
                m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 5:
                m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            }
            break;
        case 7:
            switch(i) {
            case 0:
                m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 1:
                m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 2:
                m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 3:
                m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 4:
                m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 5:
                m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            }
            break;
        case 8:
            switch(i) {
            case 0:
                m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 1:
                m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 2:
                m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 3:
                m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 4:
                m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 5:
                m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            }
            break;
        case 9:
            switch(i) {
            case 0:
                m_panelNum1->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 1:
                m_panelNum2->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 2:
                m_panelNum3->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 3:
                m_panelNum4->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 4:
                m_panelNum5->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            case 5:
                m_panelNum6->setMaterialName(m_materialNameNumbers + Ogre::StringConverter::toString(test));
                break;
            }
            break;
        }
    }
}

void GameView::updateHUD(Ogre::Real timeSinceLastFrame) {

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


    /*
    //Test für die Positionierung des Panels
    //Geht!!!
    m_positionLogo += 0.0001;
    m_panelLogo->_setPosition(0.6+m_positionLogo,0.6-m_positionLogo);
    */
}

void GameView::resumeGame() {
    createHUDForDebug();        //Wird nämlich im Pause-State zerstört
    if (m_showHUD) {
        showAllHUDElements();
        OgreFramework::getSingletonPtr()->m_pTrayMgr->hideAll();
        OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();
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
    m_panelTrack->show();
    m_panelBoost->show();
}

void GameView::hideAllHUDElements() {
    m_panelLogo->hide();
    m_panelNum1->hide();
    m_panelNum2->hide();
    m_panelNum3->hide();
    m_panelNum4->hide();
    m_panelNum5->hide();
    m_panelNum6->hide();
    m_panelTrack->hide();
    m_panelBoost->hide();
}

void GameView::keyPressed() {

    if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_L)) {
        m_showHUD = !m_showHUD;

        if(m_showHUD) {
            showAllHUDElements();
            OgreFramework::getSingletonPtr()->m_pTrayMgr->hideAll();
            OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();

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