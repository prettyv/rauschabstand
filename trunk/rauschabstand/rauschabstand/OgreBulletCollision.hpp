//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef OGREBULLET_COLLISSION_HPP
#define OGREBULLET_COLLISSION_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "OgreBulletDynamicsRigidBody.h"				 // for OgreBullet
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h" // for static planes
#include "Shapes/OgreBulletCollisionsBoxShape.h"		 // for Boxes

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "OgreBulletCollisionsShape.h"


#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "Shapes/OgreBulletCollisionsSphereShape.h"
#include "Shapes/OgreBulletCollisionsConeShape.h"
#include "Shapes/OgreBulletCollisionsCylinderShape.h"
#include "Shapes/OgreBulletCollisionsTriangleShape.h"
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h"

#include "Shapes/OgreBulletCollisionsCompoundShape.h"

#include "Shapes/OgreBulletCollisionsMultiSphereShape.h"

#include "Shapes/OgreBulletCollisionsConvexHullShape.h"
#include "Shapes/OgreBulletCollisionsMinkowskiSumShape.h"

#include "Shapes/OgreBulletCollisionsTrimeshShape.h"

#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h"

#include "OgreBulletCollisionsRay.h"

#include "Debug/OgreBulletCollisionsDebugLines.h"

#include "OgreBulletDynamicsWorld.h"
#include "OgreBulletDynamicsRigidBody.h"

#include "OgreBulletDynamicsConstraint.h"
#include "Constraints/OgreBulletDynamicsPoint2pointConstraint.h" 

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

class OgreBulletCollision
{
private:
	SceneManager* mSceneMgr; 
	OgreBulletDynamics::DynamicsWorld *mWorld;	// OgreBullet World
	OgreBulletCollisions::DebugDrawer *debugDrawer;
	int mNumEntitiesInstanced;

	std::deque<OgreBulletDynamics::RigidBody *>         mBodies;
	std::deque<OgreBulletCollisions::CollisionShape *>  mShapes;

public:
	OgreBulletCollision (SceneManager *sceneMgr, Vector3 &gravityVector, AxisAlignedBox &bounds) 
		: mSceneMgr(sceneMgr), mNumEntitiesInstanced(0)
	{
		// Start Bullet
		mWorld = new OgreBulletDynamics::DynamicsWorld(mSceneMgr, bounds, gravityVector);

		// add Debug info display tool
		debugDrawer = new OgreBulletCollisions::DebugDrawer();
		debugDrawer->setDrawWireframe(true);	// we want to see the Bullet containers

		mWorld->setDebugDrawer(debugDrawer);
		mWorld->setShowDebugShapes(true);		// enable it if you want to see the Bullet containers
		SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
		node->attachObject(static_cast <SimpleRenderable *> (debugDrawer));

		// create floor plane
		
		// Define a floor plane mesh
		/*Entity *ent;
		Plane p;
		p.normal = Vector3(0,1,0); p.d = -400;
		MeshManager::getSingleton().createPlane("FloorPlane", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, p, 200000, 200000, 20, 20, true, 1, 9000, 9000, Vector3::UNIT_Z);
		
		// Create an entity (the floor)
		ent = mSceneMgr->createEntity("floor", "FloorPlane");
		ent->setMaterialName("Examples/BumpyMetal");
		mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);*/

		createStaticPlaneCollisionShape();
		
	}

	~OgreBulletCollision() {
		// OgreBullet physic delete - RigidBodies
		std::deque<OgreBulletDynamics::RigidBody *>::iterator itBody = mBodies.begin();
		while (mBodies.end() != itBody)
		{   
			delete *itBody; 
			++itBody;
		}	
		// OgreBullet physic delete - Shapes
		std::deque<OgreBulletCollisions::CollisionShape *>::iterator itShape = mShapes.begin();
		while (mShapes.end() != itShape)
		{   
			delete *itShape; 
			++itShape;
		}
		mBodies.clear();
		mShapes.clear();
		delete mWorld->getDebugDrawer();
		mWorld->setDebugDrawer(0);
		delete mWorld;
	}

	void stepSimulation(double timeSinceLastFrame) {
		// update Bullet Physics animation
		mWorld->stepSimulation(timeSinceLastFrame);
	}

	OgreBulletDynamics::RigidBody* createBoxCollisionShape(SceneNode* node, AxisAlignedBox boundingB, Vector3 position, float bodyMass) {
		Vector3 size = Vector3::ZERO;	// size of the box
		
		size = boundingB.getSize(); 
		size /= 2.0f; // only the half needed
		size *= 0.95f;	// Bullet margin is a bit bigger so we need a smaller size

		/*
		SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		node->attachObject(entity);
		node->scale(0.05f, 0.05f, 0.05f);	// the cube is too big for us
		size *= 0.05f;						// don't forget to scale down the Bullet-box too
		*/

		// after that create the Bullet shape with the calculated size
		OgreBulletCollisions::BoxCollisionShape *sceneBoxShape = new OgreBulletCollisions::BoxCollisionShape(size);

		// and the Bullet rigid body
		OgreBulletDynamics::RigidBody* defaultBody = new OgreBulletDynamics::RigidBody(
			"defaultBoxRigid" + StringConverter::toString(mNumEntitiesInstanced), 
			mWorld);
		defaultBody->setShape(	node,
			sceneBoxShape,
			0.6f,			// dynamic body restitution
			0.6f,			// dynamic body friction
			bodyMass, 			// dynamic bodymass
			position,		// starting position of the box
			Quaternion(0,0,0,1));// orientation of the box

		//defaultBody->setLinearVelocity(mCamera->getDerivedDirection().normalisedCopy() * 7.0f ); // shooting speed

		mNumEntitiesInstanced++;

		mShapes.push_back(sceneBoxShape);
		mBodies.push_back(defaultBody);

		return defaultBody;
	}

	void createStaticPlaneCollisionShape() {
		// add collision detection to it
		OgreBulletCollisions::CollisionShape *Shape;
		Shape = new OgreBulletCollisions::StaticPlaneCollisionShape(Ogre::Vector3(0,1,0), -500); // (normal vector, distance)

		/*Vector3* vertices;

		Shape = new OgreBulletCollisions::TriangleMeshCollisionShape(
			//{Vector3(0, -200, 0), Vector3(400, -200, 0), Vector3(0, -200, 400)},
			//3,
			//{0, 1, 2},
			//3,
			//true
		);*/

		// a body is needed for the shape
		OgreBulletDynamics::RigidBody *defaultPlaneBody = new OgreBulletDynamics::RigidBody("BasePlane", mWorld);
		defaultPlaneBody->setStaticShape((OgreBulletCollisions::StaticPlaneCollisionShape*)Shape, 0.1, 0.8);	// (shape, restitution, friction)


		// push the created objects to the deques
		mShapes.push_back(Shape);
		mBodies.push_back(defaultPlaneBody);
	}

	/*
	virtual bool processUnbufferedKeyInput(const FrameEvent& evt)
	{

		// create and throw a box if 'B' is pressed
		if(mKeyboard->isKeyDown(OIS::KC_B) && mTimeUntilNextToggle <=0)
		{
			// starting position of the box
			Vector3 position = (mCamera->getDerivedPosition() + mCamera->getDerivedDirection().normalisedCopy() * 10);

			
			

			
			
							

			
			// push the created objects to the dequese
			
			
		}
		return ret;
	}
	*/

	OgreBulletDynamics::RigidBody* addStaticTrimesh(const Ogre::String &instanceName,
		const Ogre::String &meshName,
		const Ogre::Vector3 &pos, 
		const Ogre::Quaternion &q, 
		const Ogre::Real bodyRestitution, 
		const Ogre::Real bodyFriction,
		bool castShadow,
		SceneNode* node)
	{
		Entity *sceneEntity = mSceneMgr->createEntity(instanceName + StringConverter::toString(mNumEntitiesInstanced), meshName);
		//sceneEntity->setCastShadows (castShadow);

		OgreBulletCollisions::StaticMeshToShapeConverter *trimeshConverter = new OgreBulletCollisions::StaticMeshToShapeConverter(sceneEntity);
		OgreBulletCollisions::TriangleMeshCollisionShape *sceneTriMeshShape = trimeshConverter->createTrimesh();
		delete trimeshConverter;
		OgreBulletDynamics::RigidBody *sceneRigid = new RigidBody(
			instanceName + "Rigid" + StringConverter::toString(mNumEntitiesInstanced),
			mWorld);

		//SceneNode *node = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();
		//node->attachObject (sceneEntity);

		sceneRigid->setStaticShape(node, sceneTriMeshShape, bodyRestitution, bodyFriction, pos);

		//mEntities.push_back(sceneEntity);
		mBodies.push_back(sceneRigid);
		mNumEntitiesInstanced++;

		return sceneRigid;
	}

};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||