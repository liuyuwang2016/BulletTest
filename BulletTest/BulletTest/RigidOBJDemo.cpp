#include "RigidOBJDemo.h"


RigidOBJDemo::RigidOBJDemo():
        BulletOpenGLApplication()
{
}

RigidOBJDemo::~RigidOBJDemo()
{
	ShutdownPhysics();
}

void RigidOBJDemo::InitializePhysics()
{
	// create the collision configuration
	m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
	// create the dispatcher
	m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
	// create the broadphase
	m_pBroadphase = new btDbvtBroadphase();
	// create the constraint solver
	m_pSolver = new btSequentialImpulseConstraintSolver();
	// create the world
	m_pWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfiguration);

	// create our scene's physics objects
	CreateObjects();
}

void RigidOBJDemo::ShutdownPhysics()
{
	delete m_pWorld;
	delete m_pSolver;
	delete m_pBroadphase;
	delete m_pDispatcher;
	delete m_pCollisionConfiguration;
}

void RigidOBJDemo::CreateObjects()
{
	CreateGameObject(new btBoxShape(btVector3(1, 50, 50)), 0, btVector3(1.0f, 0.6f, 0.6f), btVector3(0.0f, 0.0f, 0.0f));

	targetModel = glmReadOBJ("src/model/Workpiece.obj");

	CreateObjGameObject(targetModel, 1, new btBoxShape(btVector3(50, 50, 50)), 0, btVector3(0.2f, 0.2f, 0.6f), btVector3(0.0f, 0.0f, 0.0f));
}

void RigidOBJDemo::RenderScene()
{
	BulletOpenGLApplication::RenderScene();
}

