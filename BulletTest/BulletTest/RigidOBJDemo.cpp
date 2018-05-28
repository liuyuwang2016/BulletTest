#include "RigidOBJDemo.h"


RigidOBJDemo::RigidOBJDemo():
        BulletOpenGLApplication()
{
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
	if (targetModel != NULL) {
		free(targetModel);
	}
	targetModel = glmReadOBJ("src/model/bunny.obj");
	btRigidBody*  pRigidBody = BulletLoadObj(targetModel, 0, 0, 15, 1);
}

void RigidOBJDemo::RenderScene()
{
	BulletOpenGLApplication::RenderScene();
}

