#include "AppDelegate.h"
#include "HomeScene.h"
#include "AndroidScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(960, 640);

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs() {
  //set OpenGL context attributions,now can only set six attributions:
  //red,green,blue,alpha,depth,stencil
  GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
  
  GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
static int register_all_packages() {
  return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
  // initialize director
  auto director = Director::getInstance();
  auto glview = director->getOpenGLView();
  if(!glview) {
    glview = GLViewImpl::create("LetGoBirdy");
    director->setOpenGLView(glview);
  }
  FileUtils::getInstance()->addSearchPath("homescreen/");
  FileUtils::getInstance()->addSearchPath("gamescreen/");
  FileUtils::getInstance()->addSearchPath("dialogimage/");
  FileUtils::getInstance()->addSearchPath("animation/");
  FileUtils::getInstance()->addSearchPath("fonts/");
  
  // turn on display FPS
  director->setDisplayStats(true);
  director->setAnimationInterval(1.0 / 60);
  
  glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::EXACT_FIT);
  register_all_packages();
  
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
  auto scene = HomeScene::createHomeScene();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
  auto scene = AndroidScene::CreateScene();
#endif
  // run
  director->runWithScene(scene);
  return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
  Director::getInstance()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
  Director::getInstance()->startAnimation();
}
