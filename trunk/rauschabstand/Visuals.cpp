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
}


MaterialPtr Visuals::getMaterial(std::string name, int red, int green, int blue) {

	// Create the texture
	TexturePtr texture = TextureManager::getSingleton().createManual(
		name, // name
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
			*pDest++ = 180; // A
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

void Visuals::updateVisual(double timeSinceLastFrame) {

	m_countTime += timeSinceLastFrame;
	int currentSecond = m_countTime / 1000;	// timeSinceLastFrame is updated in ms
	double currentMs = m_countTime / 1000 - (int)(m_countTime / 1000);

	if (currentSecond > m_totalTracklength)
	{
		return ;
	}


	// m_audioSpectrumData0
	int spectrumDifference0 = m_audioSpectrumData0[currentSecond+1] - m_audioSpectrumData0[currentSecond];

	for (int i=1; i<=std::abs(spectrumDifference0); ++i)
	{
		if (currentMs < (double)(i)/(double)(std::abs(spectrumDifference0)))
		{

			if (spectrumDifference0 > 0)
			{

				for (int j=0; j<=m_audioSpectrumData0[currentSecond]+i; ++j)
				{
					m_parentCubeNode0[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData0[currentSecond]+i); ++j)
				{
					m_parentCubeNode0[5-j]->setVisible(false);
				}

			} else {

				for (int j=0; j<=m_audioSpectrumData0[currentSecond]-i; ++j)
				{
					m_parentCubeNode0[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData0[currentSecond]-i); ++j)
				{
					m_parentCubeNode0[5-j]->setVisible(false);
				}

			}

			break;
		}
	}

	// m_audioSpectrumData1
	int spectrumDifference1 = m_audioSpectrumData1[currentSecond+1] - m_audioSpectrumData1[currentSecond];

	for (int i=1; i<=std::abs(spectrumDifference1); ++i)
	{
		if (currentMs < (double)(i)/(double)(std::abs(spectrumDifference1)))
		{

			if (spectrumDifference1 > 0)
			{

				for (int j=0; j<=m_audioSpectrumData1[currentSecond]+i; ++j)
				{
					m_parentCubeNode1[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData1[currentSecond]+i); ++j)
				{
					m_parentCubeNode1[5-j]->setVisible(false);
				}

			} else {

				for (int j=0; j<=m_audioSpectrumData1[currentSecond]-i; ++j)
				{
					m_parentCubeNode1[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData1[currentSecond]-i); ++j)
				{
					m_parentCubeNode1[5-j]->setVisible(false);
				}

			}

			break;
		}
	}

	// m_audioSpectrumData2
	int spectrumDifference2 = m_audioSpectrumData2[currentSecond+1] - m_audioSpectrumData2[currentSecond];

	for (int i=1; i<=std::abs(spectrumDifference2); ++i)
	{
		if (currentMs < (double)(i)/(double)(std::abs(spectrumDifference2)))
		{

			if (spectrumDifference2 > 0)
			{

				for (int j=0; j<=m_audioSpectrumData2[currentSecond]+i; ++j)
				{
					m_parentCubeNode2[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData2[currentSecond]+i); ++j)
				{
					m_parentCubeNode2[5-j]->setVisible(false);
				}

			} else {

				for (int j=0; j<=m_audioSpectrumData2[currentSecond]-i; ++j)
				{
					m_parentCubeNode2[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData2[currentSecond]-i); ++j)
				{
					m_parentCubeNode2[5-j]->setVisible(false);
				}

			}

			break;
		}
	}

	// m_audioSpectrumData3
	int spectrumDifference3 = m_audioSpectrumData3[currentSecond+1] - m_audioSpectrumData3[currentSecond];

	for (int i=1; i<=std::abs(spectrumDifference3); ++i)
	{
		if (currentMs < (double)(i)/(double)(std::abs(spectrumDifference3)))
		{

			if (spectrumDifference3 > 0)
			{

				for (int j=0; j<=m_audioSpectrumData3[currentSecond]+i; ++j)
				{
					m_parentCubeNode3[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData3[currentSecond]+i); ++j)
				{
					m_parentCubeNode3[5-j]->setVisible(false);
				}

			} else {

				for (int j=0; j<=m_audioSpectrumData3[currentSecond]-i; ++j)
				{
					m_parentCubeNode3[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData3[currentSecond]-i); ++j)
				{
					m_parentCubeNode3[5-j]->setVisible(false);
				}

			}

			break;
		}
	}

	// m_audioSpectrumData4
	int spectrumDifference4 = m_audioSpectrumData4[currentSecond+1] - m_audioSpectrumData4[currentSecond];

	for (int i=1; i<=std::abs(spectrumDifference4); ++i)
	{
		if (currentMs < (double)(i)/(double)(std::abs(spectrumDifference4)))
		{

			if (spectrumDifference4 > 0)
			{

				for (int j=0; j<=m_audioSpectrumData4[currentSecond]+i; ++j)
				{
					m_parentCubeNode4[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData4[currentSecond]+i); ++j)
				{
					m_parentCubeNode4[5-j]->setVisible(false);
				}

			} else {

				for (int j=0; j<=m_audioSpectrumData4[currentSecond]-i; ++j)
				{
					m_parentCubeNode4[j]->setVisible(true);
				}

				for (int j=1; j<5-(m_audioSpectrumData4[currentSecond]-i); ++j)
				{
					m_parentCubeNode4[5-j]->setVisible(false);
				}

			}

			break;
		}
	}

}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Visuals::createVisuals() {
	// create materials
	MaterialPtr green = getMaterial("green", 0, 210, 25);
	MaterialPtr darkGreen = getMaterial("darkGreen", 20, 110, 30);
	MaterialPtr yellow = getMaterial("yellow", 250, 255, 0);
	MaterialPtr orange = getMaterial("orange", 255, 160, 0);
	MaterialPtr red = getMaterial("red", 210, 0, 0);

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

	// for testing only:
	for (int i=0; i<5; ++i)
	{
		m_parentCubeNode1[i]->setVisible(false);
		m_parentCubeNode2[i]->setVisible(false);
		m_parentCubeNode3[i]->setVisible(false);
		m_parentCubeNode4[i]->setVisible(false);
		m_parentCubeNode0[i]->setVisible(false);
	}
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Visuals::createVisualBar(Ogre::Vector3& position, const Ogre::Quaternion& orienation) {
	// create bar itself
	SceneNode* childCubeNode;
	Entity* cubeEntity;
	
	//wievielte runde?
	//runde = (derzeitige anzahl durchläufe - (derzeitige anzahl % 5)) : 5
	//runde = (m_numberOfCubes - (m_numberOfCubes%5)) : 5

	for (int i=0; i<5; ++i)
	{
		cubeEntity = m_pSceneMgr->createEntity("cubeEntity" + StringConverter::toString(m_numberOfCubes) + StringConverter::toString(i), "cube.mesh");

		
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

		childCubeNode->scale(0.65, 0.5, 0.65);
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