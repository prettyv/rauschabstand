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
        Visuals(SceneManager* pSceneMgr, Map* map);

        void    createVisuals();
        void    updateVisual(Ogre::Real timeSinceLastFrame);
        void    reset(void);

        void    setBoostSpeed(Ogre::Real boostSpeed);

        bool                        timeLowered;
        Ogre::Real                  m_countTime;    // passed seconds since first update

    private:
        static const int CUBE_COUNT = 10;
        static const int BAR_COUNT = 12;

        SceneManager*               m_pSceneMgr;

        std::vector<std::vector<Ogre::SceneNode*> >     m_barNodes;     // for creating the visuals
        std::vector<std::vector<Ogre::StaticGeometry*> >    m_staticCubes;  // after all bars are created, the cubes are instanced and stored in m_staticCubes - only the staticCubes are updated
        std::vector<std::vector<double> >               m_audioData;    // audio data is parsed from txt file into m_audioData and read on every update


        Map*                        m_map;
        int                         m_numberOfCubesCreated;
        Ogre::Real                  m_boostSpeed;



        // helper methods for creating visuals
        void        createVisualBar(const Ogre::Vector3& position, const Ogre::Quaternion& orienation = Quaternion::IDENTITY);
        MaterialPtr getMaterial(std::string name, int red, int green, int blue, int alpha);
        void        parseAudioData(void);

        void        countDownVisuals(void);
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
