//
// Created by AICDG on 2017/8/9.
//


#include "RigidOBJDemo.h"
#include "FreeGLUTCallbacks.h"

int main(int argc, char** argv) {
	RigidOBJDemo demo;
    return glutmain(argc, argv, 800, 600, "5-Axes Dispenser Bullet", &demo);
}