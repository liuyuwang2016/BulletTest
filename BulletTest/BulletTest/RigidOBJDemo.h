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
	
protected:
	GLMmodel* targetModel;
};


#endif //RIGIDBODYDEMO_H