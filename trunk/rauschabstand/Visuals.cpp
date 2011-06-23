//|||||||||||||||||||||||||||||||||||||||||||||||

#include <math.h>

#include "Visuals.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

Visuals::Visuals(SceneManager* pSceneMgr, Map* map, double totalTracklength,  
				 double* audioSpectrumData0, double* audioSpectrumData1, double* audioSpectrumData2, double* audioSpectrumData3, double* audioSpectrumData4)
{
	m_pSceneMgr = pSceneMgr;
	m_map = map;

	m_totalTracklength = totalTracklength;

	m_audioSpectrumData0 = audioSpectrumData0;
	m_audioSpectrumData1 = audioSpectrumData1;
	m_audioSpectrumData2 = audioSpectrumData2;
	m_audioSpectrumData3 = audioSpectrumData3;
	m_audioSpectrumData4 = audioSpectrumData4;

	m_numberOfCubes = 0;


	for (int i=0; i<5; ++i)
	{
		m_parentCubeNode0[i] = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("parentCubeNode0" + StringConverter::toString(i));
	}
	for (int i=0; i<5; ++i)
	{
		m_parentCubeNode1[i] = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("parentCubeNode1" + StringConverter::toString(i));
	}
	for (int i=0; i<5; ++i)
	{
		m_parentCubeNode2[i] = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("parentCubeNode2" + StringConverter::toString(i));
	}
	for (int i=0; i<5; ++i)
	{
		m_parentCubeNode3[i] = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("parentCubeNode3" + StringConverter::toString(i));
	}
	for (int i=0; i<5; ++i)
	{
		m_parentCubeNode4[i] = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("parentCubeNode4" + StringConverter::toString(i));
	}
	

	// actually useless var, just for "faking" the audio-input:
	m_countTime = 0.0;


	// creating staticGeometry
	for (int i=0; i<5; ++i)
	{
		m_staticCubes0[i] = m_pSceneMgr->createStaticGeometry("Visuals0" + StringConverter::toString(i));
		m_staticCubes0[i]->setRegionDimensions(Ogre::Vector3(1000000, 1000000, 1000000));
		m_staticCubes0[i]->setOrigin(Ogre::Vector3(0, 0, 0));

		m_staticCubes1[i] = m_pSceneMgr->createStaticGeometry("Visuals1" + StringConverter::toString(i));
		m_staticCubes1[i]->setRegionDimensions(Ogre::Vector3(1000000, 1000000, 1000000));
		m_staticCubes1[i]->setOrigin(Ogre::Vector3(0, 0, 0));

		m_staticCubes2[i] = m_pSceneMgr->createStaticGeometry("Visuals2" + StringConverter::toString(i));
		m_staticCubes2[i]->setRegionDimensions(Ogre::Vector3(1000000, 1000000, 1000000));
		m_staticCubes2[i]->setOrigin(Ogre::Vector3(0, 0, 0));

		m_staticCubes3[i] = m_pSceneMgr->createStaticGeometry("Visuals3" + StringConverter::toString(i));
		m_staticCubes3[i]->setRegionDimensions(Ogre::Vector3(1000000, 1000000, 1000000));
		m_staticCubes3[i]->setOrigin(Ogre::Vector3(0, 0, 0));

		m_staticCubes4[i] = m_pSceneMgr->createStaticGeometry("Visuals4" + StringConverter::toString(i));
		m_staticCubes4[i]->setRegionDimensions(Ogre::Vector3(1000000, 1000000, 1000000));
		m_staticCubes4[i]->setOrigin(Ogre::Vector3(0, 0, 0));
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

void Visuals::updateVisual(Ogre::Real timeSinceLastFrame) {

	m_countTime += timeSinceLastFrame;
	int currentSecond = m_countTime / 1000;	// timeSinceLastFrame is updated in ms
	Ogre::Real currentMs = m_countTime / 1000 - (int)(m_countTime / 1000);

	if (currentSecond > m_totalTracklength)
	{
		return ;
	}


	// m_audioSpectrumData0
	int spectrumDifference0 = m_audioSpectrumData0[currentSecond+1] - m_audioSpectrumData0[currentSecond];

	for (int i=1; i<=std::abs(spectrumDifference0); ++i)
	{
		if (currentMs < (Ogre::Real)(i)/(Ogre::Real)(std::abs(spectrumDifference0)))
		{

			if (spectrumDifference0 > 0)
			{

				for (int j=0; j<=m_audioSpectrumData0[currentSecond]+i; ++j)
				{
					m_staticCubes0[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData0[currentSecond]+i); ++j)
				{
					m_staticCubes0[5-j]->setVisible(false);
				}

			} else {

				for (int j=0; j<=m_audioSpectrumData0[currentSecond]-i; ++j)
				{
					m_staticCubes0[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData0[currentSecond]-i); ++j)
				{
					m_staticCubes0[5-j]->setVisible(false);
				}

			}

			break;
		}
	}

	// m_audioSpectrumData1
	int spectrumDifference1 = m_audioSpectrumData1[currentSecond+1] - m_audioSpectrumData1[currentSecond];

	for (int i=1; i<=std::abs(spectrumDifference1); ++i)
	{
		if (currentMs < (Ogre::Real)(i)/(Ogre::Real)(std::abs(spectrumDifference1)))
		{

			if (spectrumDifference1 > 0)
			{

				for (int j=0; j<=m_audioSpectrumData1[currentSecond]+i; ++j)
				{
					m_staticCubes1[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData1[currentSecond]+i); ++j)
				{
					m_staticCubes1[5-j]->setVisible(false);
				}

			} else {

				for (int j=0; j<=m_audioSpectrumData1[currentSecond]-i; ++j)
				{
					m_staticCubes1[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData1[currentSecond]-i); ++j)
				{
					m_staticCubes1[5-j]->setVisible(false);
				}

			}

			break;
		}
	}

	// m_audioSpectrumData2
	int spectrumDifference2 = m_audioSpectrumData2[currentSecond+1] - m_audioSpectrumData2[currentSecond];

	for (int i=1; i<=std::abs(spectrumDifference2); ++i)
	{
		if (currentMs < (Ogre::Real)(i)/(Ogre::Real)(std::abs(spectrumDifference2)))
		{

			if (spectrumDifference2 > 0)
			{

				for (int j=0; j<=m_audioSpectrumData2[currentSecond]+i; ++j)
				{
					m_staticCubes2[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData2[currentSecond]+i); ++j)
				{
					m_staticCubes2[5-j]->setVisible(false);
				}

			} else {

				for (int j=0; j<=m_audioSpectrumData2[currentSecond]-i; ++j)
				{
					m_staticCubes2[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData2[currentSecond]-i); ++j)
				{
					m_staticCubes2[5-j]->setVisible(false);
				}

			}

			break;
		}
	}

	// m_audioSpectrumData3
	int spectrumDifference3 = m_audioSpectrumData3[currentSecond+1] - m_audioSpectrumData3[currentSecond];

	for (int i=1; i<=std::abs(spectrumDifference3); ++i)
	{
		if (currentMs < (Ogre::Real)(i)/(Ogre::Real)(std::abs(spectrumDifference3)))
		{

			if (spectrumDifference3 > 0)
			{

				for (int j=0; j<=m_audioSpectrumData3[currentSecond]+i; ++j)
				{
					m_staticCubes3[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData3[currentSecond]+i); ++j)
				{
					m_staticCubes3[5-j]->setVisible(false);
				}

			} else {

				for (int j=0; j<=m_audioSpectrumData3[currentSecond]-i; ++j)
				{
					m_staticCubes3[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData3[currentSecond]-i); ++j)
				{
					m_staticCubes3[5-j]->setVisible(false);
				}

			}

			break;
		}
	}

	// m_audioSpectrumData4
	int spectrumDifference4 = m_audioSpectrumData4[currentSecond+1] - m_audioSpectrumData4[currentSecond];

	for (int i=1; i<=std::abs(spectrumDifference4); ++i)
	{
		if (currentMs < (Ogre::Real)(i)/(Ogre::Real)(std::abs(spectrumDifference4)))
		{

			if (spectrumDifference4 > 0)
			{

				for (int j=0; j<=m_audioSpectrumData4[currentSecond]+i; ++j)
				{
					m_staticCubes4[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData4[currentSecond]+i); ++j)
				{
					m_staticCubes4[5-j]->setVisible(false);
				}

			} else {

				for (int j=0; j<=m_audioSpectrumData4[currentSecond]-i; ++j)
				{
					m_staticCubes4[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData4[currentSecond]-i); ++j)
				{
					m_staticCubes4[5-j]->setVisible(false);
				}

			}

			break;
		}
	}

}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Visuals::createVisuals() {
	// create materials
	MaterialPtr green = getMaterial("green", 0, 210, 25, 180);
	MaterialPtr darkGreen = getMaterial("darkGreen", 20, 110, 30, 180);
	MaterialPtr yellow = getMaterial("yellow", 250, 255, 0, 180);
	MaterialPtr orange = getMaterial("orange", 255, 160, 0, 180);
	MaterialPtr red = getMaterial("red", 210, 0, 0, 180);

	// create visuals
	int width = m_map->getWidth() / 2.0 * 100;
	for (int i=0; i<m_map->getLength(); i=i+2)
	{
		createVisualBar(m_map->getPosition(i, m_map->getWidth() / 2.0 * 100.0), m_map->getOrientation(i));
	}

	for (int i=0; i<m_map->getLength(); i=i+2)
	{
		createVisualBar(m_map->getPosition(i, -m_map->getWidth() / 2.0 * 100.0), m_map->getOrientation(i));
	}

	// INSTANCING BEGIN
	// adding scenenodes to staticCubes in order to render all cube entities in one batch
	for (int i=0; i<5; ++i)
	{
		m_staticCubes0[i]->addSceneNode(m_parentCubeNode0[i]);
		m_staticCubes1[i]->addSceneNode(m_parentCubeNode1[i]);
		m_staticCubes2[i]->addSceneNode(m_parentCubeNode2[i]);
		m_staticCubes3[i]->addSceneNode(m_parentCubeNode3[i]);
		m_staticCubes4[i]->addSceneNode(m_parentCubeNode4[i]);

		// creating staticGeometry
		m_staticCubes0[i]->build();
		m_staticCubes1[i]->build();
		m_staticCubes2[i]->build();
		m_staticCubes3[i]->build();
		m_staticCubes4[i]->build();
	}

	// destroy entities since they are now instanced via the staticCubes
	/*
	for (int i=0; i<m_numberOfCubes; ++i)
	{
		for (int j=0; j<5; ++j)
		{
			m_pSceneMgr->destroyEntity("cubeEntity" + StringConverter::toString(i) + StringConverter::toString(j));
		}
	}
	*/
	for (int i=0; i<5; ++i)
	{
		m_pSceneMgr->destroySceneNode(m_parentCubeNode0[i]);
		m_pSceneMgr->destroySceneNode(m_parentCubeNode1[i]);
		m_pSceneMgr->destroySceneNode(m_parentCubeNode2[i]);
		m_pSceneMgr->destroySceneNode(m_parentCubeNode3[i]);
		m_pSceneMgr->destroySceneNode(m_parentCubeNode4[i]);
	}
	// INSTANCING END
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Visuals::createVisualBar(const Ogre::Vector3& position, const Ogre::Quaternion& orienation) {
	// create bar itself
	SceneNode* childCubeNode;
	Entity* cubeEntity;


	//wievielte runde?
	//runde = (derzeitige anzahl durchl�ufe - (derzeitige anzahl % 5)) : 5
	//runde = (m_numberOfCubes - (m_numberOfCubes%5)) : 5

	for (int i=0; i<5; ++i)
	{
		cubeEntity = m_pSceneMgr->createEntity("cubeEntity" + StringConverter::toString(m_numberOfCubes) + StringConverter::toString(i), "cube.mesh");
		cubeEntity->setCastShadows(false);

		switch (m_numberOfCubes % 5) {
		case 0:
			childCubeNode = m_parentCubeNode0[i]->createChildSceneNode("childCubeNode" + StringConverter::toString(m_numberOfCubes) + StringConverter::toString(i));
			break;
		case 1:
			childCubeNode = m_parentCubeNode1[i]->createChildSceneNode("childCubeNode" + StringConverter::toString(m_numberOfCubes) + StringConverter::toString(i));
			break;
		case 2:
			childCubeNode = m_parentCubeNode2[i]->createChildSceneNode("childCubeNode" + StringConverter::toString(m_numberOfCubes) + StringConverter::toString(i));
			break;
		case 3:
			childCubeNode = m_parentCubeNode3[i]->createChildSceneNode("childCubeNode" + StringConverter::toString(m_numberOfCubes) + StringConverter::toString(i));
			break;
		case 4:
			childCubeNode = m_parentCubeNode4[i]->createChildSceneNode("childCubeNode" + StringConverter::toString(m_numberOfCubes) + StringConverter::toString(i));
			break;
		}

		childCubeNode->scale(0.65f, 0.5f, 0.65f);
		childCubeNode->attachObject(cubeEntity);
		childCubeNode->setOrientation(orienation);
		childCubeNode->setPosition(position);

		switch (i) {
		case 0:
			cubeEntity->setMaterialName("green");
			
			break;
		case 1:
			cubeEntity->setMaterialName("darkGreen");
			childCubeNode->translate(0, 55, 0, Ogre::Node::TS_LOCAL);
			break;
		case 2:
			cubeEntity->setMaterialName("yellow");
			childCubeNode->translate(0, 110, 0, Ogre::Node::TS_LOCAL);
			break;
		case 3:
			cubeEntity->setMaterialName("orange");
			childCubeNode->translate(0, 165, 0, Ogre::Node::TS_LOCAL);
			break;
		case 4:
			cubeEntity->setMaterialName("red");
			childCubeNode->translate(0, 220, 0, Ogre::Node::TS_LOCAL);
			break;
		}
	}

	++m_numberOfCubes;
}

//|||||||||||||||||||||||||||||||||||||||||||||||