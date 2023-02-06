#pragma once

#include <Geode/Geode.hpp>

USE_GEODE_NAMESPACE();

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
    
    bool init();

    // void start(std::string url, std::function<void(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response)> callback);
    void start(const char *url, SEL_HttpResponse callback);
    
    void close();

    CREATE_FUNC(SimpleHTTPRequestLayer);
};