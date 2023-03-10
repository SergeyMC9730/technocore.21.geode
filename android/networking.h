// took from opengd and ported to v2

#pragma once

#include "techno.h"
// #include "LoadingCircleLayer.h"
#ifdef __ANDROID__
#include "include/cocos2dx/platform/CCPlatformMacros.h"
#include "include/extensions/network/HttpClient.h"
#include "include/extensions/network/HttpRequest.h"
#else
#include "cocos-headers/cocos2dx/platform/CCPlatformMacros.h"
#include "cocos-headers/extensions/network/HttpClient.h"
#endif

using namespace cocos2d::extension;

class LoadingCircleLayer : public CCLayer {
public:
    CCSprite *m_pCircle;

    bool init();
    CREATE_FUNC(LoadingCircleLayer);

    void update(float delta);
};

class SimpleHTTPRequestLayer: public CCLayer {
public:
    LoadingCircleLayer *m_pLC;
    CCObject *m_pTarget;
    
    bool init();

    // void start(std::string url, std::function<void(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response)> callback);
    void start(const char *url, SEL_HttpResponse callback);
    
    void close();

    CREATE_FUNC(SimpleHTTPRequestLayer);
};
