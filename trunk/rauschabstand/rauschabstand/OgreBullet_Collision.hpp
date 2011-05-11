//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef OGREBULLET_COLLISSION_HPP
#define OGREBULLET_COLLISSION_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "OgreBulletDynamicsRigidBody.h"				 // for OgreBullet
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h" // for static planes
#include "Shapes/OgreBulletCollisionsBoxShape.h"		 // for Boxes

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

class OgreBullet_Collision : public FrameListener
{
private:
	SceneManager* mSceneMgr; 
	OgreBulletDynamics::DynamicsWorld *mWorld;	// OgreBullet World
	OgreBulletCollisions::DebugDrawer *debugDrawer;
	int mNumEntitiesInstanced;

	std::deque<OgreBulletDynamics::RigidBody *>         mBodies;
	std::deque<OgreBulletCollisions::CollisionShape *>  mShapes;

public:
	OgreBullet_Collision (SceneManager *sceneMgr, RenderWindow* win, Camera* cam, Vector3 &gravityVector, AxisAlignedBox &bounds) : FrameListener(), mSceneMgr(sceneMgr)
	{
		mNumEntitiesInstanced = 0; // how many shapes are created
		mSceneMgr = sceneMgr;
		// Start Bullet
		mWorld = new OgreBulletDynamics::DynamicsWorld(mSceneMgr, bounds, gravityVector);

		// add Debug info display tool
		debugDrawer = new OgreBulletCollisions::DebugDrawer();
		debugDrawer->setDrawWireframe(true);	// we want to see the Bullet containers

		mWorld->setDebugDrawer(debugDrawer);
		mWorld->setShowDebugShapes(true);		// enable it if you want to see the Bullet containers
		SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
		node->attachObject(static_cast <SimpleRenderable *> (debugDrawer));

		// Define a floor plane mesh
		Entity *ent;
		Plane p;
		p.normal = Vector3(0,1,0); p.d = 0;
		MeshManager::getSingleton().createPlane("FloorPlane", 
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
			p, 200000, 200000, 20, 20, true, 1, 9000, 9000, 
			Vector3::UNIT_Z);
		// Create an entity (the floor)
		ent = mSceneMgr->createEntity("floor", "FloorPlane");
		ent->setMaterialName("Examples/BumpyMetal");
		mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

		// add collision detection to it
		OgreBulletCollisions::CollisionShape *Shape;
		Shape = new OgreBulletCollisions::StaticPlaneCollisionShape(Ogre::Vector3(0,1,0), 0); // (normal vector, distance)
		// a body is needed for the shape
		OgreBulletDynamics::RigidBody *defaultPlaneBody = new OgreBulletDynamics::RigidBody("BasePlane",
			mWorld);
		defaultPlaneBody->setStaticShape(Shape, 0.1, 0.8);// (shape, restitution, friction)
		// push the created objects to the deques
		mShapes.push_back(Shape);
		mBodies.push_back(defaultPlaneBody);

	}

	~OgreBullet_Collision() {
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

	bool frameStarted(const FrameEvent& evt)
	{
		bool ret = FrameListener::frameStarted(evt);

		mWorld->stepSimulation(evt.timeSinceLastFrame);	// update Bullet Physics animation

		return ret;
	}

	bool frameEnded(const FrameEvent& evt)
	{
		bool ret = FrameListener::frameEnded(evt);

		mWorld->stepSimulation(evt.timeSinceLastFrame);	// update Bullet Physics animation

		return ret;
	}

	virtual bool processUnbufferedKeyInput(const FrameEvent& evt)
	{
		bool ret = FrameListener::processUnbufferedKeyInput(evt);

		// create and throw a box if 'B' is pressed
		if(mKeyboard->isKeyDown(OIS::KC_B) && mTimeUntilNextToggle <=0)
		{
			Vector3 size = Vector3::ZERO;	// size of the box
			// starting position of the box
			Vector3 position = (mCamera->getDerivedPosition() + mCamera->getDerivedDirection().normalisedCopy() * 10);

			// create an ordinary, Ogre mesh with texture
			Entity *entity = mSceneMgr->createEntity(
				"Box" + StringConverter::toString(mNumEntitiesInstanced),
				"cube.mesh");			    
			entity->setCastShadows(true);
			// we need the bounding box of the box to be able to set the size of the Bullet-box
			AxisAlignedBox boundingB = entity->getBoundingBox();
			size = boundingB.getSize(); size /= 2.0f; // only the half needed
			size *= 0.95f;	// Bullet margin is a bit bigger so we need a smaller size
			// (Bullet 2.76 Physics SDK Manual page 18)
			entity->setMaterialName("Examples/BumpyMetal");
			SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
			node->attachObject(entity);
			node->scale(0.05f, 0.05f, 0.05f);	// the cube is too big for us
			size *= 0.05f;						// don't forget to scale down the Bullet-box too

			// after that create the Bullet shape with the calculated size
			OgreBulletCollisions::BoxCollisionShape *sceneBoxShape = new OgreBulletCollisions::BoxCollisionShape(size);
			// and the Bullet rigid body
			OgreBulletDynamics::RigidBody *defaultBody = new OgreBulletDynamics::RigidBody(
				"defaultBoxRigid" + StringConverter::toString(mNumEntitiesInstanced), 
				mWorld);
			defaultBody->setShape(	node,
				sceneBoxShape,
				0.6f,			// dynamic body restitution
				0.6f,			// dynamic body friction
				1.0f, 			// dynamic bodymass
				position,		// starting position of the box
				Quaternion(0,0,0,1));// orientation of the box
			mNumEntitiesInstanced++;				

			defaultBody->setLinearVelocity(
				mCamera->getDerivedDirection().normalisedCopy() * 7.0f ); // shooting speed
			// push the created objects to the dequese
			mShapes.push_back(sceneBoxShape);
			mBodies.push_back(defaultBody);
			mTimeUntilNextToggle = 0.5;
		}
		return ret;
	}

}

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||