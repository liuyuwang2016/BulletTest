//
// Created by Yvan Liu on 2018.
//

#ifndef BULLETOPENGL_BULLETOPENGLAPPLICATION_H
#define BULLETOPENGL_BULLETOPENGLAPPLICATION_H

#include <GL/freeglut.h>
#pragma managed (push,off)
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
// includes for convex hulls
#include <BulletCollision/CollisionShapes/btConvexPolyhedron.h>
#include <BulletCollision/CollisionShapes/btShapeHull.h>
#pragma managed (pop)
// include our custom Motion State object
#include "OpenGLMotionState.h"

#include "GameObject.h"
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>

// Our custom debug renderer
#include "DebugDrawer.h"
//����objģ��ʹ�õ�glm��
#include "glm.h"
// a convenient typedef to reference an STL vector of GameObjects
// ��GameObject���涨��ģ��������ø�������������
typedef std::vector<GameObject*> GameObjects;

// convenient typedefs for collision events ��������������ײ
typedef std::pair<const btRigidBody*, const btRigidBody*> CollisionPair;
typedef std::set<CollisionPair> CollisionPairs;

// �洢����׷�ٽ���Ľṹ��
struct RayResult {
	btRigidBody* pBody;
	btVector3 hitPoint;
};

// Collision groups for different types of objects. Each value
// is represented by a single bit
enum CollisionGroups {
	COLGROUP_NONE  = 0,
	COLGROUP_STATIC = 1 << 0,
	COLGROUP_BOX  = 1 << 1,
	COLGROUP_SPHERE = 1 << 2
};

class BulletOpenGLApplication {
public:
	BulletOpenGLApplication();
	~BulletOpenGLApplication();
	void Initialize();
	// FreeGLUT �ص����� //
	virtual void Keyboard(unsigned char key, int x, int y);
	virtual void KeyboardUp(unsigned char key, int x, int y);
	virtual void Special(int key, int x, int y);
	virtual void SpecialUp(int key, int x, int y);
	virtual void Reshape(int w, int h);
	virtual void Idle();
	virtual void Mouse(int button, int state, int x, int y);
	virtual void PassiveMotion(int x, int y);
	virtual void Motion(int x, int y);
	virtual void Display();

	// ��Ⱦ�����Ա�����������
	virtual void RenderScene();

	// �������£����Ա�����������
	virtual void UpdateScene(float dt);

	// �������ʷ���ʽ�����Ա����������أ�����BasicDemo
	virtual void InitializePhysics() {};
	virtual void ShutdownPhysics() {};
	
	// ����ĺ���
	void UpdateCamera();
	void RotateCamera(float &angle, float value);
	void ZoomCamera(float distance);

	// �������ĺ���
	void DrawBox(const btVector3 &halfSize);
	void DrawSphere(const btScalar &radius);
	void DrawCylinder(const btScalar &radius, const btScalar &halfHeight);
	void DrawConvexHull(const btCollisionShape* shape);
	void DrawShape(btScalar* transform, const btCollisionShape* pShape, const btVector3 &color);

	// ��������ĺ���
	GameObject* CreateGameObject(btCollisionShape* pShape,
			const float &mass,
			const btVector3 &color = btVector3(1.0f,1.0f,1.0f),
			const btVector3 &initialPosition = btVector3(0.0f,0.0f,0.0f),
			short int group = -1,
			short int mask = -1,
			const btQuaternion &initialRotation = btQuaternion(0,0,1,1));

	void ShootBox(const btVector3 &direction);
	void DestroyGameObject(btRigidBody* pBody);
	GameObject* FindGameObject(btRigidBody* pBody);

	// ����׷��ѡ����
	btVector3 GetPickingRay(int x, int y);
	bool Raycast(const btVector3 &startPosition, const btVector3 &direction, RayResult &output, bool includeStatic = false);

	// Լ���ĺ���
	void CreatePickingConstraint(int x, int y);
	void RemovePickingConstraint();


	// ��ײ�¼�����
	void CheckForCollisionEvents();
	virtual void CollisionEvent(btRigidBody* pBody0, btRigidBody * pBody1);
	virtual void SeparationEvent(btRigidBody * pBody0, btRigidBody * pBody1);

	//ֱ��load obj��Bullet�ĺ���
	btRigidBody* BulletLoadObj(GLMmodel* mesh, float x, float y, float z, float scale);
protected:
	// ������Ʋ���
	btVector3 m_cameraPosition; // the camera's current position
	btVector3 m_cameraTarget;	 // the camera's lookAt target
	float m_nearPlane; // minimum distance the camera will render
	float m_farPlane; // farthest distance the camera will render
	btVector3 m_upVector; // keeps the camera rotated correctly
	float m_cameraDistance; // distance from the camera to its target
	float m_cameraPitch; // pitch of the camera 
	float m_cameraYaw; // yaw of the camera

	int m_screenWidth;
	int m_screenHeight;

	// ���ĵ�Bullet�����
	btBroadphaseInterface* m_pBroadphase;
	btCollisionConfiguration* m_pCollisionConfiguration;
	btCollisionDispatcher* m_pDispatcher;
	btConstraintSolver* m_pSolver;
	btDynamicsWorld* m_pWorld;

	// ����ʱ��ļ�clock
	btClock m_clock;

	// game objects������
	GameObjects m_objects;

	// Debugģʽ����Ⱦ
	DebugDrawer* m_pDebugDrawer;

	// constraint variables
	btRigidBody* m_pPickedBody;				// the body we picked up
	btTypedConstraint*  m_pPickConstraint;	// the constraint the body is attached to
	btScalar m_oldPickingDist;				// the distance from the camera to the hit point (so we can move the object up, down, left and right from our view)

	// collision event variables
	CollisionPairs m_pairsLastUpdate;

};


#endif //BULLETOPENGL_BULLETOPENGLAPPLICATION_H
