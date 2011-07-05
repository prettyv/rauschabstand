//|||||||||||||||||||||||||||||||||||||||||||||||

#include <fstream>
#include <string>

#include "Visuals.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

Visuals::Visuals(SceneManager* pSceneMgr, Map* map) : m_numberOfCubesCreated(0), m_countTime(0.0), m_pSceneMgr(pSceneMgr), m_map(map), timeLowered(false)
{
	// filling up audioData with double vectors
	for (int i=0; i<BAR_COUNT; ++i)
	{
		std::vector<double> currentAudioData;
		m_audioData.push_back(currentAudioData);
	}

	// creating SceneNode for cubes
	for (int i=0; i<BAR_COUNT; ++i)
	{
		std::vector<Ogre::SceneNode*> cubeNodeVector;
		cubeNodeVector.clear();
		for (int j=0; j<CUBE_COUNT; ++j)
		{
			cubeNodeVector.push_back(m_pSceneMgr->getRootSceneNode()->createChildSceneNode("cubeNode" + StringConverter::toString(i) + StringConverter::toString(j)));
		}
		m_barNodes.push_back(cubeNodeVector);
	}

	// creating staticGeometry
	for (int i=0; i<BAR_COUNT; ++i)
	{
		std::vector<Ogre::StaticGeometry*> staticCubeNodeVector;
		staticCubeNodeVector.clear();
		for (int j=0; j<CUBE_COUNT; ++j)
		{
			staticCubeNodeVector.push_back(m_pSceneMgr->createStaticGeometry("staticCube" + StringConverter::toString(i) + StringConverter::toString(j)));
			staticCubeNodeVector[j]->setRegionDimensions(Ogre::Vector3(1000000, 1000000, 1000000));
			staticCubeNodeVector[j]->setOrigin(Ogre::Vector3(0, 0, 0));
		}
		m_staticCubes.push_back(staticCubeNodeVector);
	}
}


MaterialPtr Visuals::getMaterial(std::string name, int red, int green, int blue, int alpha) {

	// Create the texture
	TexturePtr texture = TextureManager::getSingleton().createManual(
		name,				// name
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		TEX_TYPE_2D,      // type
		256, 256,         // width & height
		0,                // number of mipmaps
		PF_BYTE_BGRA,     // pixel format
		TU_DEFAULT);      // usage; should be TU_DYNAMIC_WRITE_ONLY_DISCARDABLE for
	// textures updated very often (e.g. each frame)

	// Get the pixel buffer
	HardwarePixelBufferSharedPtr pixelBuffer = texture->getBuffer();

	// Lock the pixel buffer and get a pixel box
	pixelBuffer->lock(HardwareBuffer::HBL_NORMAL); // for best performance use HBL_DISCARD!
	const PixelBox& pixelBox = pixelBuffer->getCurrentLock();

	uint8* pDest = static_cast<uint8*>(pixelBox.data);

	// Fill in some pixel data. This will give a semi-transparent blue,
	// but this is of course dependent on the chosen pixel format.
	for (size_t j = 0; j < 256; j++) {
		for(size_t i = 0; i < 256; i++)
		{
			*pDest++ = blue; // B
			*pDest++ = green; // G
			*pDest++ = red; // R
			*pDest++ = alpha; // A
		}
	}

	// Unlock the pixel buffer
	pixelBuffer->unlock();

	MaterialPtr material = MaterialManager::getSingleton().create(name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	material->getTechnique(0)->getPass(0)->createTextureUnitState(name);
	material->getTechnique(0)->getPass(0)->setSceneBlending(SBT_TRANSPARENT_ALPHA);

	return material;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Visuals::parseAudioData() {
	int countLinenumbers = 0;
	double audioData = 0.0;
	int spectrumHit = 0;
	std::stringstream sstr;

	std::string line;
	std::ifstream myfile ("spectralAnalysis_4096_samples.txt");

	// EINGABEGROESSE (BARCOUNT, CUBECOUNT) ABHAENGIG!
	if (myfile.is_open())
	{
		while ( myfile.good() )
		{
			getline (myfile,line);

			if (line.size()>0)
			{
				sstr.str(line);
				std::string tmpstr = sstr.str();
				
				sstr >> audioData;


				// TODO automate range determination
				// get the data in range 0-7
				if (audioData != 0)
				{
					audioData -= 1;
					audioData *= 100000;
				}
				
				if (audioData == 0)
				{
					spectrumHit = 1;
				} else if (audioData > 0 && audioData <= 20)
				{
					spectrumHit = 2;
				} else if (audioData > 20 && audioData <= 50)
				{
					spectrumHit = 3;
				} else if (audioData > 50 && audioData <= 100)
				{
					spectrumHit = 4;
				} else if (audioData > 100 && audioData <= 175)
				{
					spectrumHit = 5;
				} else if (audioData > 175 && audioData <= 250)
				{
					spectrumHit = 6;
				} else if (audioData > 250 && audioData <= 500)
				{
					spectrumHit = 7;
				} else if (audioData > 500 && audioData <= 1500)
				{
					spectrumHit = 8;
				} else if (audioData > 1500)
				{
					spectrumHit = 9;
				}


				m_audioData[countLinenumbers % BAR_COUNT].push_back(spectrumHit);

				sstr.clear();
				line.clear();
				tmpstr.clear();
				audioData = 0.0;
				spectrumHit = 0;
			}

			++countLinenumbers;
		}
		myfile.close();
	}
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Visuals::countDownVisuals(void) {
		if (m_countTime < 10000 && m_countTime > 9500)
		{
			for (int i=0; i<BAR_COUNT; ++i)
			{
				for (int j=CUBE_COUNT-1; j>1; --j)
				{
					m_staticCubes[i][j]->setVisible(false);
				}
			}
		} else if (m_countTime < 9500 && m_countTime > 9000)
		{
			for (int i=0; i<BAR_COUNT; ++i)
			{
				for (int j=CUBE_COUNT-1; j>2; --j)
				{
					m_staticCubes[i][j]->setVisible(false);
				}
			}
		} else if (m_countTime < 9000 && m_countTime > 8500)
		{
			for (int i=0; i<BAR_COUNT; ++i)
			{
				for (int j=CUBE_COUNT-1; j>3; --j)
				{
					m_staticCubes[i][j]->setVisible(false);
				}
			}
		} else if (m_countTime < 8500 && m_countTime > 7500)
		{
			for (int i=0; i<BAR_COUNT; ++i)
			{
				for (int j=CUBE_COUNT-1; j>4; --j)
				{
					m_staticCubes[i][j]->setVisible(false);
				}
			}
		} else if (m_countTime < 7500 && m_countTime > 7000)
		{
			for (int i=0; i<BAR_COUNT; ++i)
			{
				for (int j=CUBE_COUNT-1; j>5; --j)
				{
					m_staticCubes[i][j]->setVisible(false);
				}
			}
		} else if (m_countTime < 7000 && m_countTime > 6500)
		{
			for (int i=0; i<BAR_COUNT; ++i)
			{
				for (int j=CUBE_COUNT-1; j>6; --j)
				{
					m_staticCubes[i][j]->setVisible(false);
				}
			}
		} else if (m_countTime < 6500 && m_countTime > 6000)
		{
			for (int i=0; i<BAR_COUNT; ++i)
			{
				for (int j=CUBE_COUNT-1; j>7; --j)
				{
					m_staticCubes[i][j]->setVisible(false);
				}
			}
		} else if (m_countTime < 6000 && m_countTime > 5500)
		{
			for (int i=0; i<BAR_COUNT; ++i)
			{
				for (int j=CUBE_COUNT-1; j>8; --j)
				{
					m_staticCubes[i][j]->setVisible(false);
				}
			}
		} else if (m_countTime < 5500 && m_countTime > 5000)
		{
			for (int i=0; i<BAR_COUNT; ++i)
			{
				for (int j=CUBE_COUNT-1; j>9; --j)
				{
					m_staticCubes[i][j]->setVisible(false);
				}
			}
		}
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Visuals::updateVisual(Ogre::Real timeSinceLastFrame) {
	m_countTime += timeSinceLastFrame;

	// COUNTDOWN_BEGIN
	if (!timeLowered && m_countTime < 10000) {
		countDownVisuals();
	} else {
	// COUNTDOWN_END
		if (!timeLowered)
		{
			m_countTime -= 10000;
			timeLowered = true;
		}
	
	// TODO automate interval determination (-> no manual input of 370ms interval window
	static int timeChanged = 0;	// making sure the visual bars are just updated when needed
	int currentTime = (int)(m_countTime / 92.5);	// 12 bands, 16384 samples buffer ~= 0,37s window -> / 370ms || 4096 samples = 92.5ms
	
	if (currentTime < 904)	// 4096 samples -> 903 audioData
	{
		if (timeChanged != currentTime)	
		{
			for (int bar=0; bar<BAR_COUNT; ++bar)
			{
				for (int spectrum=0; spectrum<=m_audioData[bar][currentTime]; ++spectrum)
				{
					m_staticCubes[bar][spectrum]->setVisible(true);
				}
				for (int spectrum=CUBE_COUNT-1; spectrum>m_audioData[bar][currentTime]; --spectrum)
				{
					m_staticCubes[bar][spectrum]->setVisible(false);
				}
			}

			timeChanged = currentTime;
		}
	} else {	// when song has ended just show one cube
		for (int i=0; i<BAR_COUNT; ++i)
		{
			for (int j=CUBE_COUNT-1; j>1; --j)
			{
				m_staticCubes[i][j]->setVisible(false);
			}
		}
	}



	}
	
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Visuals::createVisuals() {
	// create materials
	// TODO automate material creation (should work with CUBE_COUNT somehow)
	// EINGABEGROESSE (BARCOUNT, CUBECOUNT) ABHAENGIG!
	/*
	MaterialPtr green = getMaterial("green", 0, 210, 25, 180);
	MaterialPtr darkGreen = getMaterial("darkGreen", 20, 110, 30, 180);
	MaterialPtr yellow = getMaterial("yellow", 250, 255, 0, 180);
	MaterialPtr orange = getMaterial("orange", 255, 160, 0, 180);
	MaterialPtr red = getMaterial("red", 210, 0, 0, 180);
	*/
	/*
	MaterialPtr lightblue1 = getMaterial("lightblue1", 209, 237, 255, 160);
	MaterialPtr lightblue2 = getMaterial("lightblue2", 152, 215, 255, 165);
	MaterialPtr lightblue3 = getMaterial("lightblue3", 96, 193, 255, 170);
	MaterialPtr blue1 = getMaterial("blue1", 24, 134, 255, 175);
	MaterialPtr blue2 = getMaterial("blue2", 0, 108, 229, 180);
	MaterialPtr blue3 = getMaterial("blue3", 0, 86, 204, 185);
	MaterialPtr darkblue1 = getMaterial("darkblue1", 0, 34, 204, 190);
	MaterialPtr darkblue2 = getMaterial("darkblue2", 0, 28, 167, 195);
	MaterialPtr darkblue3 = getMaterial("darkblue3", 0, 18, 109, 200);
	MaterialPtr black = getMaterial("black", 0, 21, 82, 205);
	*/
	// create visuals
	int width = m_map->getWidth() / 2.0 * 100;
	for (int i=0; i<m_map->getLength(); i=i+2)
	{
		createVisualBar(m_map->getPosition(i, m_map->getWidth() / 2.0 * 100.0 + 40), m_map->getOrientation(i));
	}

	for (int i=0; i<m_map->getLength(); i=i+2)
	{
		createVisualBar(m_map->getPosition(i, -m_map->getWidth() / 2.0 * 100.0 - 40), m_map->getOrientation(i));
	}
	
	// INSTANCING BEGIN
	// adding scenenodes to staticCubes in order to render all cube entities in one batch
	for (int i=0; i<BAR_COUNT; ++i)
	{
		for (int j=0; j<CUBE_COUNT; ++j)
		{
			m_staticCubes[i][j]->addSceneNode(m_barNodes[i][j]);

			// building staticGeometry
			m_staticCubes[i][j]->build();

		}
	}

	// destroy entities since they are now instanced via the staticCubes
	for (int i=0; i<BAR_COUNT; ++i)
	{
		for (int j=0; j<CUBE_COUNT; ++j)
		{
			m_pSceneMgr->destroySceneNode(m_barNodes[i][j]);
		}
	}

	// INSTANCING END

	// parse wo anders hinverschieben + aufteilen wieviel würfel sichtbar gleich im parse und nurmehr anzahl sichtbarer würferl in m_audioData speichern
	parseAudioData();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Visuals::createVisualBar(const Ogre::Vector3& position, const Ogre::Quaternion& orienation) {
	// create bar itself
	SceneNode* childCubeNode;
	Entity* cubeEntity;

	for (int j=0; j<CUBE_COUNT; ++j)
	{
		cubeEntity = m_pSceneMgr->createEntity("cubeEntity" + StringConverter::toString(m_numberOfCubesCreated) + StringConverter::toString(j), "cube.mesh");
		cubeEntity->setCastShadows(false);

		childCubeNode = m_barNodes[m_numberOfCubesCreated % BAR_COUNT][j]->createChildSceneNode("cubeEntityNode" + StringConverter::toString(m_numberOfCubesCreated) + StringConverter::toString(j));
		
		childCubeNode->scale(0.70f, 0.15f, 0.70f);
		childCubeNode->attachObject(cubeEntity);
		childCubeNode->setOrientation(orienation);
		childCubeNode->setPosition(position);

		// TODO automate setmaterial (should work with CUBE_COUNT somehow)
		// EINGABEGROESSE (BARCOUNT, CUBECOUNT) ABHAENGIG!
		switch (j) {
		case 0:
			cubeEntity->setMaterialName("glow_lightblue1");
			break;
		case 1:
			cubeEntity->setMaterialName("glow_lightblue2");
			childCubeNode->translate(0, 20, 0, Ogre::Node::TS_LOCAL);
			break;
		case 2:
			cubeEntity->setMaterialName("glow_lightblue3");
			childCubeNode->translate(0, 40, 0, Ogre::Node::TS_LOCAL);
			break;
		case 3:
			cubeEntity->setMaterialName("glow_blue1");
			childCubeNode->translate(0, 60, 0, Ogre::Node::TS_LOCAL);
			break;
		case 4:
			cubeEntity->setMaterialName("glow_blue2");
			childCubeNode->translate(0, 80, 0, Ogre::Node::TS_LOCAL);
			break;
		case 5:
			cubeEntity->setMaterialName("glow_blue3");
			childCubeNode->translate(0, 100, 0, Ogre::Node::TS_LOCAL);
			break;
		case 6:
			cubeEntity->setMaterialName("glow_darkblue1");
			childCubeNode->translate(0, 120, 0, Ogre::Node::TS_LOCAL);
			break;
		case 7:
			cubeEntity->setMaterialName("glow_darkblue2");
			childCubeNode->translate(0, 140, 0, Ogre::Node::TS_LOCAL);
			break;
		case 8:
			cubeEntity->setMaterialName("glow_darkblue3");
			childCubeNode->translate(0, 160, 0, Ogre::Node::TS_LOCAL);
			break;
		case 9:
			cubeEntity->setMaterialName("glow_black");
			childCubeNode->translate(0, 180, 0, Ogre::Node::TS_LOCAL);
			break;
		}
	}

	++m_numberOfCubesCreated;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Visuals::reset() {
	m_countTime = Ogre::Real(0.0);
	timeLowered = false;

	for (int i=0; i<BAR_COUNT; ++i)
	{
		for (int j=0; j<=CUBE_COUNT-1; ++j)
		{
			m_staticCubes[i][j]->setVisible(true);
		}
		for (int j=CUBE_COUNT-1; j>CUBE_COUNT-3; --j)
		{
			m_staticCubes[i][j]->setVisible(false);
		}
	}
}

//|||||||||||||||||||||||||||||||||||||||||||||||