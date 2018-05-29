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
	//直接load obj进Bullet的函数
	btRigidBody* BulletLoadObj(GLMmodel* mesh, float x, float y, float z, float scale);
protected:
	GLMmodel* targetModel;
};


#endif //RIGIDBODYDEMO_H