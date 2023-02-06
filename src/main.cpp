#include <Geode/Geode.hpp>
#include "../include/GameObjectFactory.hpp"
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/KeysLayer.hpp>
#include "networking.h"

#include <Geode/modify/MenuLayer.hpp>

USE_GEODE_NAMESPACE();

#define kTimeModSlow 0.70f
#define kTimeModNormal 0.9f
#define kTimeModFast 1.1f
#define kTimeModVeryFast 1.3f
#define kTimeModVeryVeryFast 1.6f

using namespace cocos2d;

std::vector<PlayerObject *> player_list;
bool isSetupComplete = false;

void destroyPlayers() {
	player_list.clear();
}
void playPlayerDeathEffect(PlayerObject *pl) {
	auto fade = CCFadeTo::create(0.05, 0);
	printf( "created fade effect\n");
	pl->runAction(fade);
	printf( "fade effect is applied to %p\n", pl);
	auto cw = CCCircleWave::create(1, 2, 3, false);
	printf( "created CCCircleWave at %p\n", cw);
	//CCNode *test = CCNode::create();
	// if(PlayLayer::get()) PlayLayer::get()->m_objectLayer->addChild(cw);
	// cw->setPosition(pl->getPosition());
}
void destroyPlayerByID(int id) {
	// delete 3 (index 2)
	//player_list[id]->playerDestroyed(false);
	printf( "deleting player by id %d\n", id);
	player_list[id]->fadeOutStreak2(0.2f);
	printf( "streak disabled\n");
	player_list[id]->stopDashing();
	printf( "dashing disabled\n");
	player_list[id]->stopRotation(false);
	printf( "rotations are stopped\n");
	player_list[id]->stopAllActions();
	printf( "physics disabled\n");
	playPlayerDeathEffect(player_list[id]);
	printf( "cleaning up\n");
	player_list.erase(player_list.begin() + id);
}
void destroyPlayerByAddress(PlayerObject *addr) {
	printf( "a\n");
	int i = 0;
	printf( "b\n", i);
	int res = 0;
	printf( "c\n", i);
	while(i < player_list.size()) {
		printf( "d\n", i);
		if(addr == player_list[i]) {
			printf( "destroying player %d\n", i);
			destroyPlayerByID(i);
			printf( "destroyed player %d\n", i);
			return;
		}
		i++;
	}
}

// Create new object
class CreatePlayerTrigger : public GameObjectController {
 public:
	CreatePlayerTrigger(GameObject* g) : GameObjectController(g) {}

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
		po->addAllParticles();
		int particles = po->m_particleSystems->count();
		int i = 0;

		while(i < particles) {
			if(PlayLayer::get()) {
				auto ccn = (CCNode *)(po->m_particleSystems->objectAtIndex(i));
				ccn->setParent(PlayLayer::get()->m_objectLayer);
				po->m_regularTrail->setParent(PlayLayer::get()->m_objectLayer);
				po->m_waveTrail->setParent(PlayLayer::get()->m_objectLayer);
				//po->m_particleSystem->setParent(PlayLayer::get()->m_objectLayer);
			}
			i++;
		}
		player_list.push_back(po);
		printf( "created player %d\n", player_list.size() - 1);
	}

	void setup() override {
		// Disable glow because there is no glow texture for this sprite
		m_glowEnabled = false;

		// Set custom texture for this object
		overrideSpriteFrame("block005_11_001.png");

		// Touch-triggered object with the Modifier type. This object will run onTrigger when collided with
		m_object->m_touchTriggered = true;
		m_object->m_objectType = GameObjectType::Modifier;
	}
};

class DestroyPlayersTrigger : public GameObjectController {
 public:
	DestroyPlayersTrigger(GameObject* g) : GameObjectController(g) {}

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
		overrideSpriteFrame("block005_12_001.png");

		// Touch-triggered object with the Modifier type. This object will run onTrigger when collided with
		m_object->m_touchTriggered = true;
		m_object->m_objectType = GameObjectType::Modifier;
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

		printf("Players speed are set to %f\n", m_fSpeed);
	}

	void setup() override {
		printf("setup portal %s\n", m_sFrame.c_str());
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

	bool ac = AllocConsole();
	if(!ac) return false;
	freopen("conin$","r",stdin);
	freopen("conout$","w",stdout);
	freopen("conout$","w",stderr);
	printf("Debugging Window:\n");

	ObjectToolbox::sharedState()->addObject(10245, "block005_11_001.png");
	ObjectToolbox::sharedState()->addObject(10246, "block005_12_001.png");

	GameObjectFactory::get()->add(10245, [](GameObject* g) {
		return new CreatePlayerTrigger(g);
	});
	GameObjectFactory::get()->add(10246, [](GameObject* g) {
		return new DestroyPlayersTrigger(g);
	});

	GameObjectFactory::get()->add(200, [](GameObject* g) {
		printf("creating boost object\n");
		return new BoostPortal(g, "boost_01_001.png", kTimeModSlow);
	});
	GameObjectFactory::get()->add(201, [](GameObject* g) {
		printf("creating boost object\n");
		return new BoostPortal(g, "boost_02_001.png", kTimeModNormal);
	});
	GameObjectFactory::get()->add(202, [](GameObject* g) {
		printf("creating boost object\n");
		return new BoostPortal(g, "boost_03_001.png", kTimeModFast);
	});
	GameObjectFactory::get()->add(203, [](GameObject* g) {
		printf("creating boost object\n");
		return new BoostPortal(g, "boost_04_001.png", kTimeModVeryFast);
	});
	GameObjectFactory::get()->add(1334, [](GameObject* g) {
		printf("creating boost object\n");
		return new BoostPortal(g, "boost_05_001.png", kTimeModVeryVeryFast);
	});

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
		player_list[i]->updateOrientedBox();
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

bool mainPlayerDied = false;
bool shouldSchedule = false;
bool isCompeletedLVL = false;

class $modify(TPlayerObject, PlayerObject) {
	float prevSpeed = 0.f;
	float newSpeed = 0.f;

	void update(float delta) {
		m_fields->newSpeed = this->m_playerSpeed;
		if(m_fields->newSpeed != m_fields->prevSpeed) {
			m_fields->prevSpeed = m_fields->newSpeed;
			printf("speed: %f\n", this->m_playerSpeed);
		}
		PlayerObject::update(delta);
	}
	void playerDestroyed(bool p0) {
		int i = 0;

		if(PlayLayer::get()) {
			printf( "Player %p died (%p %p)\n", this, PlayLayer::get()->m_player1,  PlayLayer::get()->m_player2);

			if((this == PlayLayer::get()->m_player1) || (this == PlayLayer::get()->m_player2)) {
				printf( "main player, using standard function\n");
				PlayerObject::playerDestroyed(p0);
				goto end;
			} else {
				printf("dummy player, using custom death code\n");
				destroyPlayerByAddress(this);
				goto end;
			}
		}
		skip:
		printf("death skipped, using standard function + custom code\n");
		PlayerObject::playerDestroyed(p0);
		printf( "destroyed main player\n");
		while(i < player_list.size()) {
			destroyPlayerByID(i);
			printf( "destroyed dummy player %d\n", i);
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
		destroyPlayers();
		printf( "player list is cleaned up\n");

		return LevelEditorLayer::init(level);
	}
	void update(float f) {
		LevelEditorLayer::update(f);
		doPlayerJob(f);
	}
};

class $modify(TPlayLayer, PlayLayer) {
	bool init(GJGameLevel *p0) {
		destroyPlayers();
		printf( "player list is cleaned up\n");

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

class $modify(TEditorUI, EditorUI) {
	void on1024(CCObject *sender) {
		EditorUI *eui = (EditorUI *)sender;

		auto lel = LevelEditorLayer::get();
		lel->getObjectLayer()->addChild(lel->createObject(10245, ccp(rand() % 50 + 100, rand() % 50 + 100), false));
	}
	void on1025(CCObject *sender) {
		EditorUI *eui = (EditorUI *)sender;

		auto lel = LevelEditorLayer::get();
		lel->getObjectLayer()->addChild(lel->createObject(10246, ccp(rand() % 50 + 100, rand() % 50 + 100), false));
	}

	void onStopPlaytest(cocos2d::CCObject* sender) {
		EditorUI::onStopPlaytest(sender);

		int i = 0;

		while(i < player_list.size()) {
			destroyPlayerByID(i);
			i++;
		}
		destroyPlayers();
		printf( "player list is cleaned up\n");
	}
	bool init(LevelEditorLayer *ll) {
		EditorUI::init(ll);

		auto menu = CCMenu::create();

        auto spr = ButtonSprite::create("add obj 10245");
		auto spr2 = ButtonSprite::create("add obj 10246");

        auto btn = CCMenuItemSpriteExtra::create(
            spr, this, menu_selector(TEditorUI::on1024)
        );
		auto btn2 = CCMenuItemSpriteExtra::create(
            spr2, this, menu_selector(TEditorUI::on1025)
        );
		btn2->setPositionY(50);
        menu->addChild(btn);
		menu->addChild(btn2);

		menu->setPosition(100, 100);

		LevelEditorLayer::get()->getObjectLayer()->addChild(menu);

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

	void onMoreGames(CCObject*) {
		FLAlertLayer::create("no", "no, just no", "OK")->show(); 
	}
	void onPlay(CCObject *sender) {
		SimpleHTTPRequestLayer *l = SimpleHTTPRequestLayer::create();
		l->start("https://gd.dogotrigger.xyz/tech21/getOfficialLevels21.php?gameVersion=21", httpresponse_selector(TMenuLayer::nCallback));

		CCNode *cn = (CCNode *)sender;

		cn->addChild(l, 1024);

		l->m_pLC->setPosition(cn->getPositionX(), cn->getPositionY());
		l->setPosition(56, 56);
	}
	bool init() {
		if(!MenuLayer::init()) return false;

		setupStuff();

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		auto tch = CCLabelBMFont::create("TechnoGDPS BETA BUILD 1.0", "bigFont.fnt");
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
