#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("ParkourCPP");
	//eglView->setFrameSize(320, 240);
    //eglView->setFrameSize(480, 320);
	eglView->setFrameSize(960, 640);
	//eglView->setFrameSize(1136, 640);
	//eglView->setFrameSize(1024, 768);
    return CCApplication::sharedApplication()->run();
}
