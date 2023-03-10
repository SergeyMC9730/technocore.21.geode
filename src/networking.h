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
private:
    const char *m_pReferer;
public:
    LoadingCircleLayer *m_pLC;
    CCObject *m_pObj2;
    
    bool init();

    void setReferer(const char *url);

    // void start(std::string url, std::function<void(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response)> callback);
    void start(const char *url, SEL_HttpResponse callback);
    void start(const char *url, SEL_HttpResponse callback, CCObject *obj2);
    
    void close();

    CREATE_FUNC(SimpleHTTPRequestLayer);
};