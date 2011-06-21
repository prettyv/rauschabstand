//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef VISUALS_HPP
#define VISUALS_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AdvancedOgreFramework.hpp"
#include "Map.hpp"

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

class Visuals
{
public:
	Visuals(SceneManager* pSceneMgr, Map* map,  double totalTracklength, 
		    double* audioSpectrumData0, double* audioSpectrumData1, double* audioSpectrumData2, double* audioSpectrumData3, double* audioSpectrumData4);

	void	createVisuals();
	void	updateVisual(Ogre::Real timeSinceLastFrame);

private:
	SceneManager*				m_pSceneMgr;
	SceneNode*					m_parentCubeNode0[5];
	SceneNode*					m_parentCubeNode1[5];
	SceneNode*					m_parentCubeNode2[5];
	SceneNode*					m_parentCubeNode3[5];
	SceneNode*					m_parentCubeNode4[5];

	// audio-data for the visualization of the spectrum - each array-entry is equal to the spectrum-data at a certain second: m_audioSpectrumData0[5] = Spectrum at 5 seconds
	double*						m_audioSpectrumData0;
	double*						m_audioSpectrumData1;
	double*						m_audioSpectrumData2;
	double*						m_audioSpectrumData3;
	double*						m_audioSpectrumData4;

	// counting the seconds that already passed
	Ogre::Real						m_countTime;

	double						m_totalTracklength;

	Map*						m_map;

	int							m_numberOfCubes;

	

	// helper methods to create visuals
	void		createVisualBar(const Ogre::Vector3& position, const Ogre::Quaternion& orienation = Quaternion::IDENTITY);
	MaterialPtr	getMaterial(std::string name, int red, int green, int blue, int alpha);
	
};


//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||