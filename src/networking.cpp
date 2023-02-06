#include "networking.h"

bool LoadingCircleLayer::init() {
    m_pCircle = CCSprite::create("loadingCircle.png");
    this->addChild(m_pCircle);

    scheduleUpdate();

    return true;
}

void LoadingCircleLayer::update(float delta) {
    if(m_pCircle) {
        float rot = m_pCircle->getRotation();
        rot += 3;
        m_pCircle->setRotation(rot);
    }
}

bool SimpleHTTPRequestLayer::init() {
    CCLayer *l = CCLayer::create();
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto base = CCSprite::create("square.png");
    base->setPosition({ 0, 0 });
    base->setScale(500.f);
    base->setColor({0, 0, 0});
    base->setOpacity(0);
    base->runAction(CCFadeTo::create(0.5f, 125));
    auto loadingCircle = LoadingCircleLayer::create();
    loadingCircle->m_pCircle->setOpacity(0);
    loadingCircle->m_pCircle->runAction(CCFadeTo::create(0.5f, 255));
    loadingCircle->setPosition(winSize.width / 2, winSize.height / 2 );
    loadingCircle->addChild(base, -1);
    l->addChild(loadingCircle);

    m_pLC = loadingCircle;

    addChild(l, 1024);

    return true;
}

void SimpleHTTPRequestLayer::start(const char *url, SEL_HttpResponse callback) {
    CCHttpClient *cl = CCHttpClient::getInstance();
    CCHttpRequest *req = new CCHttpRequest;
    req->setRequestType(CCHttpRequest::HttpRequestType::kHttpPost);
    req->setUrl(url);
    req->setResponseCallback(this, callback);
    cl->send(req);
}

void SimpleHTTPRequestLayer::close() {
    m_pLC->removeAllChildrenWithCleanup(true);
    m_pLC->unscheduleUpdate();
    m_pLC->removeFromParentAndCleanup(true);
    m_pLC->release();
}