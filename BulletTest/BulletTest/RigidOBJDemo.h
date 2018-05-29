#ifndef RIGIDBODYDEMO_H
#define RIGIDBODYDEMO_H

#include "BulletOpenGLApplication.h"

#pragma managed (push,off)
#include <btBulletDynamicsCommon.h>
#pragma managed (pop)


class RigidOBJDemo : public BulletOpenGLApplication {
public:
	RigidOBJDemo();
	~RigidOBJDemo();
	virtual void InitializePhysics() override;
	virtual void ShutdownPhysics() override;
	void CreateObjects();
	virtual void RenderScene() override;
	// target model loaded by glm
	//ֱ��load obj��Bullet�ĺ���
	btRigidBody* BulletLoadObj(GLMmodel* mesh, float x, float y, float z, float scale);
protected:
	GLMmodel* targetModel;
};


#endif //RIGIDBODYDEMO_H