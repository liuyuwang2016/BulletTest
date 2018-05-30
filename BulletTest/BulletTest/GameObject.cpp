#include "GameObject.h"

GameObject::GameObject(btCollisionShape* pShape, float mass, const btVector3 &color, const btVector3 &initialPosition, const btQuaternion &initialRotation) {
	// 存储shape之后使用
	m_pShape = pShape;

	// store the color
	m_color = color;

	// create the initial transform
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(initialPosition);
	transform.setRotation(initialRotation);

	// create the motion state from the
	// initial transform
	m_pMotionState = new OpenGLMotionState(transform);

	// calculate the local inertia
	btVector3 localInertia(0,0,0);

	// objects of infinite mass can't
	// move or rotate
	if (mass != 0.0f) {
		pShape->calculateLocalInertia(mass, localInertia);
	}

	// create the rigid body construction
	// info using the mass, motion state
	// and shape
	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, m_pMotionState, pShape, localInertia);

	// create the rigid body
	m_pBody = new btRigidBody(cInfo);
}


GameObject::GameObject(GLMmodel* mesh, float scale, btCollisionShape* pShape, float mass, const btVector3 &color, const btVector3 &initialPosition /*= btVector3(0, 0, 0)*/, const btQuaternion &initialRotation /*= btQuaternion(0, 0, 1, 1)*/)
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
	m_pShape = shape;
	m_color = color;
	btTransform trans;
	trans.setIdentity();
	trans.setOrigin(initialPosition);
	trans.setRotation(initialRotation);
	btDefaultMotionState *StillStateMOT = new btDefaultMotionState(trans);
	
	btVector3 FallInertia(0.0f, 0.0f, 0.0f);
	if (mass != 0.0f) {
		pShape->calculateLocalInertia(mass, FallInertia);
	}
	//使用mass, motionstate, shape构建出rigidbody。
	btRigidBody::btRigidBodyConstructionInfo StillRigidCI(mass, StillStateMOT, shape, FallInertia);
	m_pBody = new btRigidBody(StillRigidCI);
}

GameObject::~GameObject() {
	delete m_pBody;
	delete m_pMotionState;
	delete m_pShape;
}