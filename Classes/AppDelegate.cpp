#include "AppDelegate.h"
#include "MainScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	pDirector->setDisplayStats(true);
	pDirector->setAnimationInterval(1.0 / 60);

	
	CCSize frameSize = pEGLView->getFrameSize();
	std::vector<std::string> searchPath;
	if (/*frameSize.height > 320*/true)
	{
		//pDirector->setContentScaleFactor(768/frameSize.height);
		pEGLView->setDesignResolutionSize(960, 640, kResolutionFixedHeight);
		searchPath.push_back("HD");
	}
	else
	{
		//pDirector->setContentScaleFactor(MIN(640/frameSize.width, 320/frameSize.height));
		//pDirector->setContentScaleFactor(320/frameSize.height);
		pEGLView->setDesignResolutionSize(640, 320, kResolutionFixedHeight);
		searchPath.push_back("Normal");
	}
	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);

    
    CCScene *pScene = MainLayer::scene();
    pDirector->runWithScene(pScene);

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
