#include <Geode/Geode.hpp>
#include "../include/GameObjectFactory.hpp"
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/KeysLayer.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include "networking.h"

#include <Geode/modify/MenuLayer.hpp>

USE_GEODE_NAMESPACE();

#define kTimeModSlow 0.70f
#define kTimeModNormal 0.9f
#define kTimeModFast 1.1f
#define kTimeModVeryFast 1.3f
#define kTimeModVeryVeryFast 1.6f

using namespace cocos2d;

namespace TechnoSettings {
	bool release = true;
}

std::vector<PlayerObject *> player_list;
bool isSetupComplete = false;

namespace AnabanLevels {
	class AnabanLevel : public CCObject {
	public:
		GJGameLevel *m_pLevel;
		int m_nId;

		AnabanLevel(GJGameLevel *level, int id) : m_pLevel(level), m_nId(id) {
			this->autorelease();
		}

		void setLID(int id) {
			m_nId = id;
		}
		void setLevel(GJGameLevel *level) {
			m_pLevel = level;
		}
	};

	GJGameLevel *levels[8] = {0};
	int levelids[8] = {23079417, 23916625};
	CCArray *levels2;

	GJGameLevel *l0;
	GJGameLevel *l1;

	void init() {
		l0 = GJGameLevel::create();
		l0->m_levelName = "u suk 105359";
		l0->m_levelDesc = "Release 2.1 already RubNum";
		l0->m_levelString = "";
		l0->m_creatorName = "anaban";
		l0->m_recordString = "";
		l0->m_userID = 18348456;
		l0->m_accountID = 5375519;
		l0->m_fastEditorZoom = 1.0f;
		l0->m_isEditable = true;
		l0->m_workingTime2 = 1;
		l0->m_workingTime = 1;
		l0->m_isVerified = 1;
		l0->m_isVerifiedRaw = true;
		l0->m_isUploaded = true;
		l0->m_isUnlocked = true;
		l0->m_levelVersion = 69;
		l0->m_isChkValid = true;
		l0->m_isCompletionLegitimate = true;
		l0->m_levelLength = 05;
		l0->m_songID = 1337;
		l0->m_dislikes = 0;
		l0->m_coins = 0;
		l0->m_downloads = 0;
		l0->m_gameVersion = 20;
		l0->m_starsRequested = 69;
		l0->m_levelID = 23079417;
		l0->m_levelType = GJLevelType::Saved;
		l0->m_M_ID = 23079417;
		l0->m_levelNotDownloaded = false;

		l1 = GJGameLevel::create();
		l1->m_levelName = "??? 98624";
		l1->m_levelDesc = "??\n\n";
		l1->m_levelString = "";
		l1->m_creatorName = "anaban";
		l1->m_recordString = "";
		l1->m_userID = 18348456;
		l1->m_accountID = 5375519;
		l1->m_fastEditorZoom = 1.0f;
		l1->m_isEditable = true;
		l1->m_workingTime2 = 1;
		l1->m_starsRequested = 13;
		l1->m_workingTime = 1;
		l1->m_isVerified = 1;
		l1->m_isVerifiedRaw = true;
		l1->m_isUploaded = true;
		l1->m_isUnlocked = true;
		l1->m_levelVersion = 13;
		l1->m_isChkValid = true;
		l1->m_isCompletionLegitimate = true;
		l1->m_levelLength = 05;
		l1->m_songID = 1337;
		l1->m_dislikes = 0;
		l1->m_coins = 0;
		l1->m_downloads = 0;
		l1->m_gameVersion = 20;
		l1->m_levelID = 23916625;
		l1->m_levelType = GJLevelType::Saved;
		l1->m_M_ID = 23916625;
		l1->m_levelNotDownloaded = false;

		levels2 = CCArray::create(l0, l1, nullptr);

		levels[0] = l0;
		levels[1] = l1;
	}

	GJGameLevel *findByID(int id) {
		int i = 0;
		while(i < 2) {
			GJGameLevel *l = levels[i];
			printf("%d %d %d\n", levelids[i], id, i);
			if(levelids[i] == id) return l;
			i++;
		}
		return nullptr;
	}
}

void destroyPlayers(bool onScreen) {
	if(onScreen) {
		int i = 0;
		while(i < player_list.size()) {
			//player_list[i]->m_particleSystem->removeFromParentAndCleanup(true);
			player_list[i]->removeMeAndCleanup();
			i++;
		}
	}
	player_list.clear();
}
void playPlayerDeathEffect(PlayerObject *pl) {
	auto fade = CCFadeTo::create(0.05, 0);
	pl->runAction(fade);
	auto cw = CCCircleWave::create(1, 2, 3, false);
	//CCNode *test = CCNode::create();
	// if(PlayLayer::get()) PlayLayer::get()->m_objectLayer->addChild(cw);
	// cw->setPosition(pl->getPosition());
}
void destroyPlayerByID(int id) {
	// delete 3 (index 2)
	//player_list[id]->playerDestroyed(false);
	if(TechnoSettings::release == false) printf( "deleting player by id %d\n", id);
	player_list[id]->fadeOutStreak2(0.2f);
	player_list[id]->stopDashing();
	player_list[id]->stopRotation(false);
	player_list[id]->stopAllActions();
	playPlayerDeathEffect(player_list[id]);
	if(TechnoSettings::release == false) printf( "cleaning up\n");
	player_list.erase(player_list.begin() + id);
}
void destroyPlayerByAddress(PlayerObject *addr) {
	int i = 0;
	int res = 0;
	while(i < player_list.size()) {
		if(addr == player_list[i]) {
			destroyPlayerByID(i);
			if(TechnoSettings::release == false) printf( "destroyed player %d\n", i);
			return;
		}
		i++;
	}
}

// Create new object
class CreatePlayerTrigger : public GameObjectController {
 public:
	CreatePlayerTrigger(GameObject* g) : GameObjectController(g) {}

	static const char *getTexture() {
		return "edit_ePCreateBtn_001.png";
	}

	// What happens when the object is "triggered"
	void onTrigger(GJBaseGameLayer* gl) override {
		// auto r = CCScaleTo::create(1.0, 1.25f, 0.75f);
		
		// gl->m_objectLayer->runAction(r);
		//FLAlertLayer::create("test", "lol", "OK")->show();

		void *addr;
		if(PlayLayer::get()) addr = PlayLayer::get();
		else addr = LevelEditorLayer::get();
		auto po = PlayerObject::create(rand() % 12, rand() % 12, (CCLayer *)addr);
		po->setSecondColor({(unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255)});
		po->setColor({(unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255)});
		if(PlayLayer::get()) PlayLayer::get()->m_batchNodePlayer->addChild(po);
		else {
			LevelEditorLayer::get()->m_batchNodePlayer->addChild(po);
		}
		po->setPosition(this->getObject()->getPosition());
		// po->addAllParticles();
		// int particles = po->m_particleSystems->count();
		// int i = 0;

		// while(i < particles) {
		// 	if(PlayLayer::get()) {
		// 		auto ccn = (CCNode *)(po->m_particleSystems->objectAtIndex(i));
		// 		ccn->setParent(PlayLayer::get()->m_objectLayer);
		// 		// po->m_regularTrail->setParent(PlayLayer::get()->m_objectLayer);
		// 		// po->m_waveTrail->setParent(PlayLayer::get()->m_objectLayer);
		// 		//po->m_particleSystem->setParent(PlayLayer::get()->m_objectLayer);
		// 	}
		// 	i++;
		// }
		player_list.push_back(po);
		if(TechnoSettings::release == false) printf( "created player %d\n", player_list.size() - 1);
	}

	void setup() override {
		// Disable glow because there is no glow texture for this sprite
		m_glowEnabled = false;

		// Set custom texture for this object
		overrideSpriteFrame(getTexture());

		// Touch-triggered object with the Modifier type. This object will run onTrigger when collided with
		m_object->m_touchTriggered = true;
		m_object->m_objectType = GameObjectType::Modifier;

		if(PlayLayer::get()) {
			m_object->setVisible(false);
		}
	}
};

class DestroyPlayersTrigger : public GameObjectController {
 public:
	DestroyPlayersTrigger(GameObject* g) : GameObjectController(g) {}

	static const char *getTexture() {
		return "edit_ePDestroyBtn_001.png";
	}

	// What happens when the object is "triggered"
	void onTrigger(GJBaseGameLayer* gl) override {
		int i = 0;

		while(i < player_list.size()) {
			destroyPlayerByID(i);
			i++;
		}
	}

	void setup() override {
		// Disable glow because there is no glow texture for this sprite
		m_glowEnabled = false;

		// Set custom texture for this object
		overrideSpriteFrame(getTexture());

		// Touch-triggered object with the Modifier type. This object will run onTrigger when collided with
		m_object->m_touchTriggered = true;
		m_object->m_objectType = GameObjectType::Modifier;

		if(PlayLayer::get()) {
			m_object->setVisible(false);
		}
	}
};

class BoostPortal : public GameObjectController {
protected:
	std::string m_sFrame;
	float m_fSpeed;
public:
	BoostPortal(GameObject *g, std::string frame, float speed) : GameObjectController(g) {
		m_sFrame = frame;
		m_fSpeed = speed;
	}

	void onTrigger(GJBaseGameLayer *gl) {
		gl->m_player1->m_playerSpeed = m_fSpeed;
		gl->m_player1->m_lastPortalPos = m_object->getPosition();
		gl->m_player1->m_lastActivatedPortal = m_object;
		if(gl->m_player2) {
			gl->m_player2->m_playerSpeed = m_fSpeed;
			gl->m_player2->m_lastPortalPos = m_object->getPosition();
			gl->m_player2->m_lastActivatedPortal = m_object;
		}

		int i = 0;
		while(i < player_list.size()) {
			player_list[i]->m_playerSpeed = m_fSpeed;
			player_list[i]->m_lastPortalPos = m_object->getPosition();
			player_list[i]->m_lastActivatedPortal = m_object;
			i++;
		}

		if(TechnoSettings::release == false) printf("Players speed are set to %f\n", m_fSpeed);
	}

	void setup() override {
		if(TechnoSettings::release == false) printf("setup portal %s\n", m_sFrame.c_str());
		m_glowEnabled = true;
		overrideSpriteFrame(m_sFrame);
		m_object->m_touchTriggered = true;
		m_object->m_objectType = GameObjectType::Modifier;
	}
};

class $modify(KeysLayer) {
	bool init() {
		if(!KeysLayer::init()) return false;
	
		this->sortAllChildren();
		auto shop1_00 = (CCNode *)(this->getChildren()->objectAtIndex(3));
		shop1_00->sortAllChildren();
		auto shop1_01 = (CCNode *)(shop1_00->getChildren()->objectAtIndex(0));
		shop1_01->sortAllChildren();
		auto shop1_02 = (CCNode *)(shop1_01->getChildren()->objectAtIndex(22));
		shop1_02->sortAllChildren();
		auto shop1_03 = (CCNode *)(shop1_02->getChildren()->objectAtIndex(0));
		shop1_03->sortAllChildren();
		auto shop1_04 = (CCNode *)(shop1_03->getChildren()->objectAtIndex(0));
		auto shop2_04 = (CCNode *)(shop1_03->getChildren()->objectAtIndex(1));

		shop1_04->setPositionX(0.f);
		shop2_04->removeMeAndCleanup();

		return true;
	}
};

bool setupStuff() {
	if(isSetupComplete) return false;

	if(TechnoSettings::release == false) {
		bool ac = AllocConsole();
		if(!ac) return false;
		freopen("conin$","r",stdin);
		freopen("conout$","w",stdout);
		freopen("conout$","w",stderr);
	}

	ObjectToolbox::sharedState()->addObject(10245, "edit_ePCreateBtn_001.png");
	ObjectToolbox::sharedState()->addObject(10246, "edit_ePDestroyBtn_001.png");

	GameObjectFactory::get()->add(10245, [](GameObject* g) {
		return new CreatePlayerTrigger(g);
	});
	GameObjectFactory::get()->add(10246, [](GameObject* g) {
		return new DestroyPlayersTrigger(g);
	});

	GameObjectFactory::get()->add(200, [](GameObject* g) {
		return new BoostPortal(g, "boost_01_001.png", kTimeModSlow);
	});
	GameObjectFactory::get()->add(201, [](GameObject* g) {
		return new BoostPortal(g, "boost_02_001.png", kTimeModNormal);
	});
	GameObjectFactory::get()->add(202, [](GameObject* g) {
		return new BoostPortal(g, "boost_03_001.png", kTimeModFast);
	});
	GameObjectFactory::get()->add(203, [](GameObject* g) {
		return new BoostPortal(g, "boost_04_001.png", kTimeModVeryFast);
	});
	GameObjectFactory::get()->add(1334, [](GameObject* g) {
		return new BoostPortal(g, "boost_05_001.png", kTimeModVeryVeryFast);
	});
	
	AnabanLevels::init();

	return true;
}

void doPlayerJob(float delta) {
	int i = 0;
	while (i < player_list.size()) {
		float dl = delta * 60.f;
		printf("dl: %f; pspeed: %f; portal at %p\n", dl, player_list[i]->m_playerSpeed, GJBaseGameLayer::get()->m_player1->m_lastActivatedPortal);
		player_list[i]->update(dl);
		if(player_list[i]->m_isShip) {
			player_list[i]->updateShipRotation(dl);
		} else if (player_list[i]->m_isBall) {
			player_list[i]->runBallRotation(dl);
		} else {
			player_list[i]->updateRotation(dl);
		}
		player_list[i]->updateRobotAnimationSpeed();
		player_list[i]->updateJump(0);
		player_list[i]->updatePlayerFrame(0);
		player_list[i]->updatePlayerFrame(1);
		if(PlayLayer::get()) {
			PlayLayer::get()->checkCollisions(player_list[i], dl);
		} else {
			LevelEditorLayer::get()->checkCollisions(player_list[i], dl);
		}
		player_list[i]->postCollision(dl);

		i++;
	}
}

class $modify(LevelTools) {
    static bool verifyLevelIntegrity(gd::string idk, int lid) {
		if(!TechnoSettings::release) {
			printf("warn: level would be forced to be loaded\n");
		}
        return true;
    }
};

bool ISGDH = false;

class $modify(TLevelSearchLayer, LevelSearchLayer) {
	bool useGDH = false;
	CCSprite *enabledGDH;
	CCSprite *disabledGDH;

	CCMenuItemToggler *spr;

	void setGDHistoryButton(CCObject *obj) {
		auto l = reinterpret_cast<TLevelSearchLayer *>(obj);

		l->m_fields->useGDH = !l->m_fields->useGDH;
		ISGDH = l->m_fields->useGDH;

		if(!TechnoSettings::release) {
			printf("state is set to %d\n", l->m_fields->useGDH);
		}
	}

	bool init() {
		ISGDH = false;

		if(!LevelSearchLayer::init()) return false;

		m_fields->enabledGDH = CCSprite::createWithSpriteFrameName("controllerBtn_A_001.png");
		m_fields->disabledGDH = CCSprite::createWithSpriteFrameName("controllerBtn_B_001.png");

		auto menu = CCMenu::create();

		// spr->initWithNormalSprite(enabledGDHsabledGDH, disabledGDH, this, menu_selector(TLevelSearchLayer::setGDHistoryButton));, di
		//m_fields->spr = CCMenuItemSprite::create(m_fields->enabledGDH, m_fields->disabledGDH, m_fields->disabledGDH, menu_selector(TLevelSearchLayer::setGDHistoryButton));
		// m_fields->spr = CCMenuItemSpriteExtra::create(m_fields->enabledGDH, this, menu_selector(TLevelSearchLayer::setGDHistoryButton));
		CCMenuItemToggler* ch1_box = CCMenuItemToggler::create(m_fields->disabledGDH, m_fields->enabledGDH, this, menu_selector(TLevelSearchLayer::setGDHistoryButton));
		m_fields->spr = ch1_box;

		menu->addChild(m_fields->spr);
		menu->setPosition({50, 50});

		//this->addChild(menu);

		return true;
	}
};

class $modify(TLevelBrowserLayer, LevelBrowserLayer) {
	int m_nLevelID;
	CCArray *m_pArray;

	bool isCorrect(const char *idk) {
		return true;
	}

	void requestComplete(CCHttpClient* client, CCHttpResponse* response) {
		SimpleHTTPRequestLayer *a = (SimpleHTTPRequestLayer *)response->getHttpRequest()->getTarget();
		TLevelBrowserLayer *lb = (TLevelBrowserLayer *)a->m_pObj2;
		a->close();

		printf("succeed: %d\n", response->isSucceed());

		if(!response->isSucceed()) {
			const char *err = response->getErrorBuffer();
			printf("%d %s %s\n", response->getResponseCode(), response->getResponseData()->data(), err);
		} else {
			printf("%s");
		}

		CCArray *arr;

		auto l0 = GJGameLevel::create();
		l0->m_levelName = "u suk 105359";
		l0->m_levelDesc = "Release 2.1 already RubNum";
		l0->m_levelString = "";
		l0->m_creatorName = "anaban";
		l0->m_recordString = "";
		l0->m_userID = 18348456;
		l0->m_accountID = 5375519;
		l0->m_fastEditorZoom = 1.0f;
		l0->m_isEditable = true;
		l0->m_workingTime2 = 1;
		l0->m_workingTime = 1;
		l0->m_isVerified = 1;
		l0->m_isVerifiedRaw = true;
		l0->m_isUploaded = true;
		l0->m_isUnlocked = true;
		l0->m_levelVersion = 69;
		l0->m_isChkValid = true;
		l0->m_isCompletionLegitimate = true;
		l0->m_levelLength = 05;
		l0->m_songID = 1337;
		l0->m_dislikes = 0;
		l0->m_coins = 0;
		l0->m_downloads = 0;
		l0->m_gameVersion = 20;
		l0->m_starsRequested = 69;
		l0->m_levelID = 23079417;
		l0->m_levelType = GJLevelType::Saved;
		l0->m_M_ID = 23079417;
		l0->m_levelNotDownloaded = false;

		auto l1 = GJGameLevel::create();
		l1->m_levelName = "??? 98624";
		l1->m_levelDesc = "??\n\n";
		l1->m_levelString = "";
		l1->m_creatorName = "anaban";
		l1->m_recordString = "";
		l1->m_userID = 18348456;
		l1->m_accountID = 5375519;
		l1->m_fastEditorZoom = 1.0f;
		l1->m_isEditable = true;
		l1->m_workingTime2 = 1;
		l1->m_starsRequested = 13;
		l1->m_workingTime = 1;
		l1->m_isVerified = 1;
		l1->m_isVerifiedRaw = true;
		l1->m_isUploaded = true;
		l1->m_isUnlocked = true;
		l1->m_levelVersion = 13;
		l1->m_isChkValid = true;
		l1->m_isCompletionLegitimate = true;
		l1->m_levelLength = 05;
		l1->m_songID = 1337;
		l1->m_dislikes = 0;
		l1->m_coins = 0;
		l1->m_downloads = 0;
		l1->m_gameVersion = 20;
		l1->m_levelID = 23916625;
		l1->m_levelType = GJLevelType::Saved;
		l1->m_M_ID = 23916625;
		l1->m_levelNotDownloaded = false;

		arr = CCArray::create(l0, l1, nullptr);

		lb->m_itemCount = 2;
		lb->m_pageStartIdx = 1;
		lb->m_pageEndIdx = 1;
		lb->setupLevelBrowser(arr);
		char *p0 = (char *)lb;
		char *p1 = (char *)&lb->m_pageEndIdx;
		printf("offset = %d\n", p1 - p0);
		//lb->loadingLevelsFinished(arr, "123");

		ISGDH = false;
	}

	void loadPage(GJSearchObject *obj) {
		printf("hook 1\n");
		int levelid = 0;
		if(!ISGDH) {
			LevelBrowserLayer::loadPage(obj);
			return;
		}
		levelid = std::atoi(obj->m_searchQuery.c_str());
		printf("levelid: %d\n", levelid);

		CCArray *arr = CCArray::create();

		LoadingCircleLayer *cl = LoadingCircleLayer::create();
		//setupLevelBrowser(arr);

		std::string str = "";
		str = "https://history.geometrydash.eu/api/v1/level/";
		str += std::to_string(levelid);
		str += "/";

		m_fields->m_nLevelID = levelid;
		m_fields->m_pArray = arr;

		printf("request: %s\n", str.c_str());

		SimpleHTTPRequestLayer *a = SimpleHTTPRequestLayer::create();
		a->setReferer("https://history.geometrydash.eu/");
		a->start(str.c_str(), httpresponse_selector(TLevelBrowserLayer::requestComplete), this);
		auto winSize = CCDirector::sharedDirector()->getWinSize();
		cl->setPosition({winSize.width / 2, winSize.height / 2});
		addChild(a, 100);
	}
};

bool mainPlayerDied = false;
bool shouldSchedule = false;
bool isCompeletedLVL = false;

class $modify(TPlayerObject, PlayerObject) {
	void update(float delta) {
		PlayerObject::update(delta);
	}
	void playerDestroyed(bool p0) {
		int i = 0;

		if(PlayLayer::get()) {
			if(TechnoSettings::release == false) printf( "Player %p died (%p %p)\n", this, PlayLayer::get()->m_player1,  PlayLayer::get()->m_player2);

			if((this == PlayLayer::get()->m_player1) || (this == PlayLayer::get()->m_player2)) {
				if(TechnoSettings::release == false) printf( "main player, using standard function\n");
				PlayerObject::playerDestroyed(p0);
				goto end;
			} else {
				if(TechnoSettings::release == false) printf("dummy player, using custom death code\n");
				destroyPlayerByAddress(this);
				goto end;
			}
		}
		skip:
		if(TechnoSettings::release == false) printf("death skipped, using standard function + custom code\n");
		PlayerObject::playerDestroyed(p0);
		if(TechnoSettings::release == false) printf( "destroyed main player\n");
		while(i < player_list.size()) {
			destroyPlayerByID(i);
			if(TechnoSettings::release == false) printf( "destroyed dummy player %d\n", i);
			i++;
		}
		end:
		return;
	}
	void collidedWithObject(float dt, GameObject* obj) {
		if (auto mg = GameObjectFactory::get()->fetch(obj)) {
			mg.value()->onCollide(dt, this);
		} else {
			PlayerObject::collidedWithObject(dt, obj);
		}
	}

};

class $modify(LevelEditorLayer) {
	bool init(GJGameLevel *level) {
		destroyPlayers(false);
		if(TechnoSettings::release == false) printf( "player list is cleaned up\n");

		return LevelEditorLayer::init(level);
	}
	void update(float f) {
		LevelEditorLayer::update(f);
		doPlayerJob(f);
	}
};

class $modify(TPlayLayer, PlayLayer) {
	bool init(GJGameLevel *p0) {
		destroyPlayers(false);
		if(TechnoSettings::release == false) printf( "player list is cleaned up\n");

		return PlayLayer::init(p0);
	}
	void update(float f) {
		PlayLayer::update(f);
		doPlayerJob(f);
	}
};

class $modify(CreatorLayer) {
	bool check_position(CCNode *nd, float x, float y) {
		return nd->getPositionX() == x && nd->getPositionY() == y;
	}

	bool init() {
		if(!CreatorLayer::init()) return false;

		CCObject *obj1;
		CCNode *nd1;
		CCNode *node_to_remove = CCNode::create();

		CCARRAY_FOREACH(this->getChildren(), obj1) {
			nd1 = (CCNode *)obj1;

			if(check_position(nd1, 284.5f, 160.f)) {
				CCObject *obj2;
				CCNode *nd2;

				CCARRAY_FOREACH(nd1->getChildren(), obj2) {
					nd2 = (CCNode *)obj2;

					if (check_position(nd2, -100.f, 97.f)) { // 0
						nd2->setPositionX(-110.f);
						nd2->setPositionY(97.f);
					}
					if (check_position(nd2, 0.f, 97.f)) { // 1
						nd2->setPositionX(-1.f);
					}
					if (check_position(nd2, 100.f, 97.f)) { // 2
						nd2->setPositionX(109.f);
					}
					if (check_position(nd2, -150.f, 0.f)) { // 3
						nd2->setPositionX(-160.f);
					}
					if (check_position(nd2, -50.f, 0.f)) { // 4
						nd2->setPositionX(-52.f);
					}
					if (check_position(nd2, 50.f, 0.f)) { // 5
						if (node_to_remove != NULL)
						{
							node_to_remove->removeMeAndCleanup();
						}
						node_to_remove = nd2;
					}
					if (check_position(nd2, -150.f, -97.f)) { // 6
						nd2->setPositionX(-113.f);
					}
					if (check_position(nd2, -50.f, -97.f)) { // 7
						nd2->setPositionX(-1.f);
					}
					if (check_position(nd2, 50.f, -97.f)) { // 8
						nd2->setPositionX(56.f);
						nd2->setPositionY(0.f);
					}
					if (check_position(nd2, 150.f, -97.f)) { // 9
						nd2->setPositionX(112.f);
					}
					if (check_position(nd2, 150.f, 0.f)) { // 10
						nd2->setPositionX(165.f);
					}
				}
			}
		}

		node_to_remove->removeMeAndCleanup();

		return true;
	}
};

namespace TechnoEditorUI {
	CCMenuItemSpriteExtra *add10245;
	CCMenuItemSpriteExtra *add10246;
};

class $modify(TEditorUI, EditorUI) {
	void on1024(CCObject *sender) {
		auto lel = LevelEditorLayer::get();
		lel->getObjectLayer()->addChild(lel->createObject(10245, ccp(rand() % 50 + 100, rand() % 50 + 100), false));
	}
	void on1025(CCObject *sender) {
		auto lel = LevelEditorLayer::get();
		lel->getObjectLayer()->addChild(lel->createObject(10246, ccp(rand() % 50 + 100, rand() % 50 + 100), false));
	}

	void onPause(CCObject *sender) {
		EditorUI::onPause(sender);

		TechnoEditorUI::add10245->setVisible(true);
		TechnoEditorUI::add10246->setVisible(true);
	}

	void onStopPlaytest(cocos2d::CCObject* sender) {
		EditorUI::onStopPlaytest(sender);

		int i = 0;

		while(i < player_list.size()) {
			destroyPlayerByID(i);
			i++;
		}
		destroyPlayers(true);
		if(TechnoSettings::release == false) printf( "player list is cleaned up\n");
		
		TechnoEditorUI::add10245->setVisible(true);
		TechnoEditorUI::add10246->setVisible(true);
	}
	void onPlaytest(cocos2d::CCObject *sender) {
		EditorUI::onPlaytest(sender);

		TechnoEditorUI::add10245->setVisible(false);
		TechnoEditorUI::add10246->setVisible(false);
	}
	bool init(LevelEditorLayer *l0) {
		if(!EditorUI::init(l0)) return false;

        // auto spr = ButtonSprite::create("add obj 10245");
		// auto spr2 = ButtonSprite::create("add obj 10246");
		const char *a = CreatePlayerTrigger::getTexture();
		const char *b = DestroyPlayersTrigger::getTexture();

		auto cache = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();

		auto spr0 = CCSprite::createWithSpriteFrame(cache->spriteFrameByName(a));
		auto spr1 = CCSprite::createWithSpriteFrame(cache->spriteFrameByName(b));

		auto gjb = CCSprite::create("GJ_button_05.png");
		gjb->setScale(0.75);

        auto btn = CCMenuItemSpriteExtra::create(
            gjb, this, menu_selector(TEditorUI::on1024)
        );
		auto btn2 = CCMenuItemSpriteExtra::create(
            gjb, this, menu_selector(TEditorUI::on1025)
        );
		spr0->setPosition({15.f, 15.5f});
		spr1->setPosition({15.f, 15.5f});
		spr0->setScale(0.91875f);
		spr1->setScale(0.91875f);
		btn->addChild(spr0);
		btn2->addChild(spr1);
		btn->setPosition(128.f, 67.f);
		btn2->setPosition(128.f, 24.f);
		btn->setID("create-player-button");
		btn2->setID("destroy-players-button");

		CCMenu *topLeftMenu = dynamic_cast<CCMenu *>(getChildByID("toolbar-categories-menu"));

		topLeftMenu->addChild(btn);
		topLeftMenu->addChild(btn2);

		TechnoEditorUI::add10245 = btn;
		TechnoEditorUI::add10246 = btn2;

		return true;
	}
};

class MenuLayer_TestAction : public FLAlertLayerProtocol {
private:
	CCObject *pTarget;
public:
	void setTarget(CCObject *target) {
		pTarget = target;
	}
	
	void FLAlert_Clicked(FLAlertLayer *alertlayer, bool btn2) {
		if(btn2) {
			FLAlertLayer::create("My response", "Yea, just wait for 2.2, <cg>nothing special about that</c>", "OK")->show(); 
		}

		SimpleHTTPRequestLayer *l = (SimpleHTTPRequestLayer *)pTarget;

		l->close();

		alertlayer->removeMeAndCleanup();
	};
};

void buttonCallback(CCObject * sender) {
	MenuLayer_TestAction *action = new MenuLayer_TestAction;

	action->setTarget(sender);

	auto alert = FLAlertLayer::create(action, "Error" ,"New levels will be added after <cg>CC!</c>", "Ok", "wait for 2.2");
	alert->show();
}

class $modify(TMenuLayer, MenuLayer) {
	void nCallback(CCHttpClient* client, CCHttpResponse* response) {
		buttonCallback(response->getHttpRequest()->getTarget());

		return;
	}

	// void onPlay(CCObject *sender) {
	// 	SimpleHTTPRequestLayer *l = SimpleHTTPRequestLayer::create();
	// 	l->start("https://gd.dogotrigger.xyz/tech21/getOfficialLevels21.php?gameVersion=21", httpresponse_selector(TMenuLayer::nCallback));

	// 	CCNode *cn = (CCNode *)sender;

	// 	cn->addChild(l, 1024);

	// 	l->m_pLC->setPosition(cn->getPositionX(), cn->getPositionY());
	// 	l->setPosition(56, 56);
	// }
	bool init() {
		if(!MenuLayer::init()) return false;

		setupStuff();

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		auto tch = CCLabelBMFont::create((TechnoSettings::release == false) ? "TechnoGDPS BETA BUILD 1.0" : "TechnoGDPS RELEASE 1.0", "bigFont.fnt");
		tch->setPositionY(300);
		tch->setPositionX(winSize.width / 2);
		tch->setScale(.375f);
		tch->setAnchorPoint({0.5f, 0.f});

		addChild(tch);

		return true;
	}
};

GEODE_API void GEODE_DLL geode_load(Mod*) {
	// Register our custom object with an Object ID of 1. This overrides the existing object.
	
}
