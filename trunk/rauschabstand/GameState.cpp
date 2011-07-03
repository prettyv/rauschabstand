//|||||||||||||||||||||||||||||||||||||||||||||||

// for faking the AUDIO-DATA
#include <ctime>    // For time()
#include <cstdlib>	// For srand() and rand()

#include "GameState.hpp"
#include "GlowMaterialListener.h"

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

GameState::GameState()
{
    m_bLMouseDown       = false;
    m_bRMouseDown       = false;
    m_bQuit             = false;
    m_bSettingsMode     = false;

    m_pDetailsPanel		= 0;

	m_gameLogic			= 0;
	m_audioPlayer		= 0;

    //Visuals
    m_gameView = new GameView();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::enter()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering GameState...");

	m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "GameSceneMgr");
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.3f, 0.3f, 0.3f));
	m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);

	m_pRSQ = m_pSceneMgr->createRayQuery(Ray());
	m_pRSQ->setQueryMask(OGRE_HEAD_MASK);

	// set SKYBOX using material Examples/SpaceSkyBox from OgreSDK
	m_pSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox", 5000);  // set our skybox

	// camera
    m_pCamera = m_pSceneMgr->createCamera("GameCamera");
    m_pCamera->setNearClipDistance(5);
    m_pCamera->setAspectRatio(Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
        Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));
    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);
	m_pCurrentObject = 0;

	m_audioPlayer = new AudioPlayer("daftp_84_fadeout.wav");
	m_gameLogic	= new GameLogic(m_pSceneMgr, m_pCamera, m_audioPlayer);
	m_gameLogic->init(); 

	createScene();


	// SHADERS BEGIN
	//glow for spaceship/audio-visual/map effects
	{
		CompositorManager::getSingleton().addCompositor(OgreFramework::getSingletonPtr()->m_pViewport, "Glow");
		CompositorManager::getSingleton().setCompositorEnabled(OgreFramework::getSingletonPtr()->m_pViewport, "Glow", true);
		GlowMaterialListener *gml = new GlowMaterialListener();
		Ogre::MaterialManager::getSingleton().addListener(gml);
	}

	//bloom as general post-effect
	//Ogre::CompositorManager::getSingleton().addCompositor(OgreFramework::getSingletonPtr()->m_pViewport, "Bloom");
	//Ogre::CompositorManager::getSingleton().setCompositorEnabled(OgreFramework::getSingletonPtr()->m_pViewport, "Bloom", true);

	//radial blur for boost
	//Ogre::CompositorManager::getSingleton().addCompositor(OgreFramework::getSingletonPtr()->m_pViewport, "Radial Blur");
	//Ogre::CompositorManager::getSingleton().setCompositorEnabled(OgreFramework::getSingletonPtr()->m_pViewport, "Radial Blur", true);
	//SHADERS END

	/*m_audioPlayer->play();*/

	/*
	//Create an Audio Manager
	cAudio::IAudioManager* manager = cAudio::createAudioManager(true);
	//Create an audio source and load a sound from a file
	cAudio::IAudioSource* mysound = manager->create("music","cAudioTheme1.ogg",true);

	if(mysound)
	{
		//Play our source in 2D once.
		mysound->play2d(false);

		//Wait for the sound to finish playing
		//while(mysound->isPlaying())
		//	cAudio::cAudioSleep(10);
	}
	*/

    //Visuals
    m_gameView->engage(m_gameLogic, m_pSceneMgr, m_pCamera, m_FrameEvent);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::pause()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Pausing GameState...");

	// SHADERS BEGIN
	CompositorManager::getSingleton().setCompositorEnabled(OgreFramework::getSingletonPtr()->m_pViewport, "Bloom", false);
	CompositorManager::getSingleton().setCompositorEnabled(OgreFramework::getSingletonPtr()->m_pViewport, "Glow", false);
	// SHADERS END

	//HUD - Visuals
	m_gameView->pauseGame();
	//HUD - Visuals End

	m_audioPlayer->pause();

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::resume()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Resuming GameState...");
    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);
    m_bQuit = false;

	//HUD - Visuals
	m_gameView->resumeGame();
	//HUD - Visuals End

	m_audioPlayer->play();

	// SHADERS BEGIN
    CompositorManager::getSingleton().setCompositorEnabled(OgreFramework::getSingletonPtr()->m_pViewport, "Bloom", true);
	CompositorManager::getSingleton().setCompositorEnabled(OgreFramework::getSingletonPtr()->m_pViewport, "Glow", true);
	// SHADERS END
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::exit()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving GameState...");

	// SHADERS BEGIN
	CompositorManager::getSingleton().removeCompositor(OgreFramework::getSingletonPtr()->m_pViewport, "Glow");
	CompositorManager::getSingleton().setCompositorEnabled(OgreFramework::getSingletonPtr()->m_pViewport, "Glow", false);

	CompositorManager::getSingleton().setCompositorEnabled(OgreFramework::getSingletonPtr()->m_pViewport, "Bloom", false);
	CompositorManager::getSingleton().removeCompositor(OgreFramework::getSingletonPtr()->m_pViewport, "Bloom");
	// SHADERS END

    m_pSceneMgr->destroyCamera(m_pCamera);
    if(m_pSceneMgr)
        OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
	
	m_audioPlayer->stop();
	delete m_audioPlayer;

    //Visuals
    m_gameView->disengage();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::createScene()
{
	//m_pSceneMgr->createLight("Light")->setPosition(75,75,75);

	Ogre::Light* directionalLight = m_pSceneMgr->createLight("directionalLight");
	directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
	directionalLight->setDiffuseColour(Ogre::ColourValue(0.9f, .8f, 0.8f));
	directionalLight->setSpecularColour(Ogre::ColourValue(0.9f, .8f, 0.8f));
	directionalLight->setDirection(Ogre::Vector3(0, -1, 1));


	// AUDIO-VISUALS begin
	// creating visuals
	m_visuals = new Visuals(m_pSceneMgr, m_gameLogic->getMap());
	m_visuals->createVisuals();
	// AUDIO-VISUALS end
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        pushAppState(findByName("PauseState"));
        return true;
    }
    
    //Update für die GameView
    m_gameView->keyPressed();

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	m_gameLogic->keyReleased(m_FrameEvent.timeSinceLastFrame, keyEventRef);

    OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::mouseMoved(const OIS::MouseEvent &evt)
{
    
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt)) return true;
    /*
    if(m_bRMouseDown)
    {
        m_pCamera->yaw(Degree(evt.state.X.rel * -0.1f));
        m_pCamera->pitch(Degree(evt.state.Y.rel * -0.1f));
    }
    */
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;

    if(id == OIS::MB_Left)
    {
        onLeftPressed(evt);
        m_bLMouseDown = true;
    }
    else if(id == OIS::MB_Right)
    {
        m_bRMouseDown = true;
    }
    
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;

    if(id == OIS::MB_Left)
    {
        m_bLMouseDown = false;
    }
    else if(id == OIS::MB_Right)
    {
        m_bRMouseDown = false;
    }
    
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::onLeftPressed(const OIS::MouseEvent &evt)
{
    /*
    if(m_pCurrentObject)
    {
        m_pCurrentObject->showBoundingBox(false);
    }

    Ogre::Ray mouseRay = m_pCamera->getCameraToViewportRay(OgreFramework::getSingletonPtr()->m_pMouse->getMouseState().X.abs / float(evt.state.width),
        OgreFramework::getSingletonPtr()->m_pMouse->getMouseState().Y.abs / float(evt.state.height));
    m_pRSQ->setRay(mouseRay);
    m_pRSQ->setSortByDistance(true);

    Ogre::RaySceneQueryResult &result = m_pRSQ->execute();
    Ogre::RaySceneQueryResult::iterator itr;

    for(itr = result.begin(); itr != result.end(); itr++)
    {
        if(itr->movable)
        {
            OgreFramework::getSingletonPtr()->m_pLog->logMessage("MovableName: " + itr->movable->getName());
            m_pCurrentObject = m_pSceneMgr->getEntity(itr->movable->getName())->getParentSceneNode();
            OgreFramework::getSingletonPtr()->m_pLog->logMessage("ObjName " + m_pCurrentObject->getName());
            m_pCurrentObject->showBoundingBox(true);
            m_pCurrentEntity = m_pSceneMgr->getEntity(itr->movable->getName());
            break;
        }
    }
    */
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::getInput()
{
    if ( OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_W)
        || OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_S)
        || OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_A)
        || OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_D)
		|| OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_SPACE))
	{
		m_gameLogic->update(m_FrameEvent.timeSinceLastFrame, OgreFramework::getSingletonPtr()->m_pKeyboard);
	}
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::update(Ogre::Real timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    OgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);

	m_gameLogic->update(timeSinceLastFrame);

    if(m_bQuit == true)
    {
        popAppState();
        return;
    }
    
    getInput();


	// AUDIO-VISUALS begin
	static int countdown = 0;
	countdown += timeSinceLastFrame;

	m_visuals->updateVisual(timeSinceLastFrame);
	
	// AUDIO-VISUALS end

	
	/*
	if (m_audioPlayer->getPitch() <= 2.0f) {
		//std::cout << m_audioPlayer->getPitch() << std::endl;
		m_audioPlayer->increasePitch((float) timeSinceLastFrame / 5000);
	}
	*/

    m_gameView->update(timeSinceLastFrame);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::itemSelected(OgreBites::SelectMenu* menu)
{
    switch(menu->getSelectionIndex())
    {
    case 0:
        m_pCamera->setPolygonMode(Ogre::PM_SOLID);break;
    case 1:
        m_pCamera->setPolygonMode(Ogre::PM_WIREFRAME);break;
    case 2:
        m_pCamera->setPolygonMode(Ogre::PM_POINTS);break;
    }
}

//|||||||||||||||||||||||||||||||||||||||||||||||