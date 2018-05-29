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
	CreateGameObject(new btBoxShape(btVector3(1, 50, 50)), 0, btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, 0.0f, 0.0f));
	if (targetModel != NULL) {
		free(targetModel);
	}
	targetModel = glmReadOBJ("src/model/bunny.obj");
	btRigidBody*  pRigidBody = BulletLoadObj(targetModel, 0, 0, 10, 1);
	m_pWorld->addRigidBody(pRigidBody);
}

/*在这里是使用把glm读取obj的方式传送给bullet*/
btRigidBody* RigidOBJDemo::BulletLoadObj(GLMmodel* mesh, float x, float y, float z, float scale)
{
	btTriangleMesh* trimesh = new btTriangleMesh();
	for (int t = 0; t < mesh->numtriangles; t++)
	{
		GLuint index0 = 3 * mesh->triangles[t].vindices[0];
		GLuint index1 = 3 * mesh->triangles[t].vindices[1];
		GLuint index2 = 3 * mesh->triangles[t].vindices[2];

		GLfloat* p0 = &mesh->vertices[index0];
		GLfloat* p1 = &mesh->vertices[index1];
		GLfloat* p2 = &mesh->vertices[index2];

		btVector3 v0(p0[0], p0[1], p0[2]);
		btVector3 v1(p1[0], p1[1], p1[2]);
		btVector3 v2(p2[0], p2[1], p2[2]);

		v0 *= scale;
		v1 *= scale;
		v2 *= scale;

		trimesh->addTriangle(v0, v1, v2);
	}
	btCollisionShape* shape = 0;
	bool useQuantization = true;
	shape = new btConvexTriangleMeshShape(trimesh, useQuantization);

	btTransform trans;
	trans.setIdentity();
	trans.setOrigin(btVector3(x, y, z));
	btDefaultMotionState *StillStateMOT = new btDefaultMotionState(trans);
	btScalar Mass = 1;
	btVector3 FallInertia(0.0f, 0.0f, 0.0f);

	//使用mass, motionstate, shape构建出rigidbody。
	btRigidBody::btRigidBodyConstructionInfo StillRigidCI(Mass, StillStateMOT, shape, FallInertia);
	btRigidBody *Rigid = new btRigidBody(StillRigidCI);

	return Rigid;
}

void RigidOBJDemo::RenderScene()
{
	BulletOpenGLApplication::RenderScene();
}

