//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef RAYCASTSPACESHIP_HPP
#define RAYCASTSPACESHIP_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Ogre.h"
#include "OgreBulletDynamics.h"

//|||||||||||||||||||||||||||||||||||||||||||||||

enum QueryFlag
{
	ANY_QUERY_MASK					= 1<<0,
	RAGDOLL_QUERY_MASK				= 1<<1,
	GEOMETRY_QUERY_MASK				= 1<<2,
	VEHICLE_QUERY_MASK				= 1<<3,
	STATIC_GEOMETRY_QUERY_MASK		= 1<<4
};

//|||||||||||||||||||||||||||||||||||||||||||||||

class RaycastSpaceship
{
public:
	RaycastSpaceship(Ogre::SceneManager *sceneMgr, OgreBulletDynamics::DynamicsWorld* world);

	virtual ~RaycastSpaceship(){};

	void init();

private:
	OgreBulletDynamics::WheeledRigidBody        *mCarChassis;
	OgreBulletDynamics::VehicleTuning	        *mTuning;
	OgreBulletDynamics::VehicleRayCaster	    *mVehicleRayCaster;
	OgreBulletDynamics::RaycastVehicle	        *mVehicle;

	Ogre::Entity    *mChassis;
	Ogre::Entity    *mWheels[4];
	Ogre::SceneNode *mWheelNodes[4];


	int mWheelsEngine[4];
	int mWheelsEngineCount;
	int mWheelsSteerable[4];
	int mWheelsSteerableCount;

	float mEngineForce;
	float mSteering;

	int mWheelEngineStyle;
	int mWheelSteeringStyle;


	bool mSteeringLeft;
	bool mSteeringRight;

	Ogre::SceneManager* m_sceneMgr;
	OgreBulletDynamics::DynamicsWorld* m_world;

};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||