#ifndef RIGIDBODYDEMO_H
#define RIGIDBODYDEMO_H

#include "BulletOpenGLApplication.h"

#pragma managed (push,off)
//#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>
//#include <BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
//#include <BulletSoftBody/btSoftBodyHelpers.h>

#pragma managed (pop)


class RigidOBJDemo : public BulletOpenGLApplication {
public:
	RigidOBJDemo();

	virtual void InitializePhysics() override;
	virtual void ShutdownPhysics() override;
	virtual void RenderScene() override;
	void CreateObjects();

protected:
	
};


#endif //RIGIDBODYDEMO_H