//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameView.hpp"

#include <OgreOverlayManager.h>
#include <OgreMaterialManager.h>

//|||||||||||||||||||||||||||||||||||||||||||||||
GameView::GameView() {
    m_highscorePanel    = 0;
    m_gameLogic         = 0;
    m_score             = 0;
    m_multiplier        = 0;

    m_sceneManager      = 0;

    //Visuals
    m_timeTest          = 0;
    m_scale             = 0.9;
    m_scaleInvert       = false;

    m_showHUD           = false;
}

GameView::~GameView() {
   
}

void GameView::engage(GameLogic* gameLogic, Ogre::SceneManager* sceneManager) {

    m_sceneManager = sceneManager;
    m_gameLogic = gameLogic;

    Ogre::StringVector items;
    items.push_back("Score");
    items.push_back("Multiplier");

    m_highscorePanel = OgreFramework::getSingletonPtr()->m_pTrayMgr->createParamsPanel(OgreBites::TL_TOP, "Highscore", 160, items);
    m_highscorePanel->show();

    if (m_showHUD) {
        createHUD();
    }
}

void GameView::createHUD() {
    OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
    MaterialManager& materialManager = Ogre::MaterialManager::getSingleton();
    
    //Bildschirmauflösung feststellen
    //GetSystemMetrics(SM_CXSCREEN);
    Ogre::Real height = OgreFramework::getSingletonPtr()->m_pViewport->getHeight();
    Ogre::Real width = OgreFramework::getSingletonPtr()->m_pViewport->getWidth();
    Ogre::Real ratio = width/height;


    //Boost-Balken
    //------
    // Create background material
    m_materialBoost = materialManager.create("Background", "General");
    m_materialBoost->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/Bars09-01.png");
    m_materialBoost->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    m_materialBoost->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    m_materialBoost->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    m_materialBoost->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    //m_material->setTransparencyCastsShadows(true);
    
    // Create background rectangle
    Rectangle2D* recBoost = new Rectangle2D(true);
    recBoost->setCorners(-1, 1, -0.2, 0.6);
    recBoost->setMaterial("Background");
    
    // Render the background before everything else
    //m_rect->setRenderQueueGroup(RENDER_QUEUE_BACKGROUND); 
    
    // Hacky, but we need to set the bounding box to something big
    // NOTE: If you are using Eihort (v1.4), please see the note below on setting the bounding box
    recBoost->setBoundingBox(AxisAlignedBox(-100000.0*Vector3::UNIT_SCALE, 100000.0*Vector3::UNIT_SCALE)); 
    
    // Attach background to the scene
    SceneNode* nodeBoost = m_sceneManager->getRootSceneNode()->createChildSceneNode("Background");
    nodeBoost->attachObject(recBoost);
    //material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setScrollAnimation(-0.25, 0.0);
    m_materialBoost->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(m_scale, m_scale);
    //Boost-Balken - End


    //Track - Balken
    //------
    m_materialTrack = materialManager.create("Track", "General");
    m_materialTrack->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/Track04-02.png");
    m_materialTrack->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    m_materialTrack->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    m_materialTrack->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    m_materialTrack->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);

    Rectangle2D* recTrack = new Rectangle2D(true);
    recTrack->setCorners(-1,-0.1,-0.8,-1.0);
    recTrack->setMaterial("Track");
    recTrack->setBoundingBox(AxisAlignedBox(-100000.0*Vector3::UNIT_SCALE, 100000.0*Vector3::UNIT_SCALE)); 

    SceneNode* nodeTrack = m_sceneManager->getRootSceneNode()->createChildSceneNode("Track");
    nodeTrack->attachObject(recTrack);

    //Track - Balken END

    //Logo
    //----
    m_materialLogo = materialManager.create("Logo", "General");
    m_materialLogo->getTechnique(0)->getPass(0)->createTextureUnitState("rauschabstand Visuals/Logo.jpg");
    m_materialLogo->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    m_materialLogo->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    m_materialLogo->getTechnique(0)->getPass(0)->setLightingEnabled(false);

    Rectangle2D* recLogo = new Rectangle2D(true);
    recLogo->setCorners(-0.5,-0.7,0.5,-1.0);
    recLogo->setMaterial("Logo");
    recLogo->setBoundingBox(AxisAlignedBox(-100000.0*Vector3::UNIT_SCALE, 100000.0*Vector3::UNIT_SCALE)); 

    SceneNode* node = m_sceneManager->getRootSceneNode()->createChildSceneNode("Logo");
    node->attachObject(recLogo);
    //Logo End
    

    /*
    -Erster Test-

    // Create a panel
    OverlayContainer* panel = static_cast<OverlayContainer*>(
        overlayManager.createOverlayElement("Panel", "PanelName"));
    panel->setMetricsMode(Ogre::GMM_PIXELS);
    panel->setPosition(400, 300);
    panel->setDimensions(2000, 2000);
    //panel->setMaterialName("MaterialName"); // Optional background material

    // Create a text area
    TextAreaOverlayElement* textArea = static_cast<TextAreaOverlayElement*>(
        overlayManager.createOverlayElement("TextArea", "TextAreaName"));
    textArea->setMetricsMode(Ogre::GMM_PIXELS);
    textArea->setPosition(10, 10);
    textArea->setDimensions(200, 200);
    textArea->setCaption("Hello, World!");
    textArea->setCharHeight(16);
    //textArea->setFontName("TrebuchetMSBold");       //geht irgendwie nicht
    textArea->setColourBottom(ColourValue(0.3, 0.5, 0.3));
    textArea->setColourTop(ColourValue(0.5, 0.7, 0.5));

    // Create an overlay, and add the panel
    Overlay* overlay = overlayManager.create("OverlayName");
    overlay->add2D(panel);

    // Add the text area to the panel
    panel->addChild(textArea);

    // Show the overlay
    overlay->show();
    */
}

void GameView::disengage() {

}

void GameView::update(Ogre::Real timeSinceLastFrame) {
    // Update für Highscore
    m_score  = m_gameLogic->getScore();
    m_multiplier = m_gameLogic->getMultiplier();
    m_highscorePanel->setParamValue(0, Ogre::StringConverter::toString(m_score));
    m_highscorePanel->setParamValue(1, Ogre::StringConverter::toString(m_multiplier));
    // Update für Highscore end

    if (m_showHUD) {
        updateHUD(timeSinceLastFrame);
    }
}

void GameView::updateHUD(Ogre::Real timeSinceLastFrame) {
    //Update für Visuals Test
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
    }

    m_materialBoost->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScale(m_scale,m_scale);


    //Update für Visuals Test End
}

OgreBites::ParamsPanel* GameView::getHighscorePanel() {
    return m_highscorePanel;
}