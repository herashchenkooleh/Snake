#include "AppDelegate.hpp"

#include <vector>
#include <string>

#include "LaunchGameScene.hpp"
#include "AppMacros.hpp"

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // Initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Snake Game");
        director->setOpenGLView(glview);
    }

    director->setOpenGLView(glview);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);

    Size frameSize = glview->getFrameSize();
    
    vector<string> searchPath;

    searchPath.push_back(gameResource.directory);
    director->setContentScaleFactor(MIN(gameResource.size.height/designResolutionSize.height, gameResource.size.width/designResolutionSize.width));

    FileUtils::getInstance()->setSearchPaths(searchPath);

    director->setDisplayStats(false);

    director->setAnimationInterval(1.0f / 60);

    auto scene = LaunchGameScene::scene();

    // Run
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}
