#include "BulletOpenGLApplication.h"
#include "FreeGLUTCallbacks.h"

int main(int argc, char** argv) {
    BulletOpenGLApplication demo;
    return glutmain(argc, argv, 800, 600, "Yvan's Bullet Checking Demo", &demo);
}