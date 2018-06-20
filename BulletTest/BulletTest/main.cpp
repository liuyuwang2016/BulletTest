//
// Created by AICDG on 2017/8/9.
//

#include "SoftBodyDemo.h"
#include "RigidOBJDemo.h"
#include "FreeGLUTCallbacks.h"

int main(int argc, char** argv) {
	SoftBodyDemo demo;
    return glutmain(argc, argv, 1920, 1080, "5-Axes Dispenser Bullet", &demo);
}