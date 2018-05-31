
#include <Kinect.h>
#include <iostream>
#include <GL/freeglut.h>

using namespace std;
class KinectFunction
{
public:
	int KinectInit();
	void KinectRead();
	~KinectFunction();
	
	IKinectSensor*		pSensor = nullptr;
	IColorFrameReader*	pColorFrameReader = nullptr;
	IDepthFrameReader*	pDepthFrameReader = nullptr;
	ICoordinateMapper*	pCoordinateMapper = nullptr;

	int		iColorWidth = 0,
		iColorHeight = 0;
	UINT	uDepthPointNum = 0;
	UINT	uColorPointNum = 0;
	UINT	uColorBufferSize = 0;

	UINT16*	pDepthBuffer = nullptr;
	BYTE*	pColorBuffer = nullptr;
	CameraSpacePoint* pCSPoints = nullptr;
};

