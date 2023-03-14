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
#include <Geode/modify/LevelInfoLayer.hpp>
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
	bool release = false;
}

std::vector<PlayerObject *> player_list;
bool isSetupComplete = false;

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
void syncPlayerSpeeds(float sp) {
	int i = 0;
	while(i < player_list.size()) {
		player_list[i]->m_playerSpeed = sp;
		i++;
	}
}
void syncPlayerX(float x) {
	int i = 0;
	while(i < player_list.size()) {
		player_list[i]->m_position.x = x;
		player_list[i]->setPositionX(x);
		i++;
	}
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
		CCPoint pos = this->getObject()->getPosition();
		pos.x = gl->m_player1->getPositionX();
		po->setPosition(pos);
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

namespace XOR {
	std::vector<char> crypt(const std::string &key, std::vector<char>& data) {
		for (size_t i = 0; i != data.size(); i++)
        data[i] ^= key[ i % key.size() ];
		return data;
	}
}

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
		syncPlayerSpeeds(this->m_player1->m_playerSpeed);
		syncPlayerX(this->m_player1->m_position.x);
		syncPlayerX(this->m_player1->getPositionX());
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
		syncPlayerSpeeds(this->m_player1->m_playerSpeed);
		syncPlayerX(this->m_player1->m_position.x);
		syncPlayerX(this->m_player1->getPositionX());
		doPlayerJob(f);
	}
};

class $modify(CreatorLayer) {
	bool check_position(CCNode *nd, float x, float y) {
		return nd->getPositionX() == x && nd->getPositionY() == y;
	}

	bool init() {
		if(!CreatorLayer::init()) return false;

		CCMenu *cbMenu = static_cast<CCMenu *>(this->getChildByID("creator-buttons-menu"));

		CCNode *featuredBtn = 	cbMenu->getChildByID("featured-button");
		CCNode *hafBtn = 		cbMenu->getChildByID("hall-of-fame-button");
		CCNode *mpBtn = 		cbMenu->getChildByID("map-packs-button");
		CCNode *searchBtn = 	cbMenu->getChildByID("search-button");
		CCNode *questsBtn = 	cbMenu->getChildByID("quests-button");
		CCNode *dailyBtn = 		cbMenu->getChildByID("daily-button");
		CCNode *weeklyBtn = 	cbMenu->getChildByID("weekly-button");
		CCNode *gauntletsBtn = 	cbMenu->getChildByID("gauntlets-button");
		CCNode *createBtn = 	cbMenu->getChildByID("create-button");
		CCNode *savedBtn = 		cbMenu->getChildByID("saved-button");
		CCNode *scoresBtn = 	cbMenu->getChildByID("scores-button");

		weeklyBtn->removeMeAndCleanup();

		featuredBtn->setPosition({122.f, 54.f});
		hafBtn->setPosition({228.f, 54.175f});
		mpBtn->setPosition({283.913f, 155.f});
		searchBtn->setPosition({334.f, 54.175f});
		questsBtn->setPosition({64.369f, 155.f});
		dailyBtn->setPosition({174.194f, 155.f});
		gauntletsBtn->setPosition({391.631f, 155.f});
		createBtn->setPosition({122.f, 255.825f});
		savedBtn->setPosition({228.f, 255.825f});
		scoresBtn->setPosition({334.f, 255.825f});

		// auto winsize = CCDirector::sharedDirector()->getWinSize();
		// cbMenu->setPositionX(winsize.width / 2);

		return true;
	}
};


namespace TechnoObjects {
	std::vector<CCLayer *> selectorlayers;
	CCPoint prevPos;
	float prevScale;

	class TechnoObjectSelectorLayer : public CCLayer {
	public:

		static void createCustomObject(int id) {
			auto lel = LevelEditorLayer::get();
			CCPoint pos;
			if(lel->m_currentStartPos == nullptr) {
				pos = ccp(rand() % 50 + 100, rand() % 50 + 100);
				FLAlertLayer::create("Success", "Object was made at the beggining of your level", "OK")->show();
			} else {
				pos = lel->m_currentStartPos->getPosition();
				FLAlertLayer::create("Success", "Object was made at the last Start pos trigger", "OK")->show();
			}
			lel->createObject(id, pos, false);
			lel->sortAllChildren();
			CCLayer *a = static_cast<CCLayer *>(lel->getChildren()->objectAtIndex(2));
			pos.y -= 100;
			pos.x += 100;
			prevPos = a->getPosition();
			prevScale = a->getScale();
			a->runAction(CCEaseInOut::create(CCMoveTo::create(2.f, pos), 2.f));
			a->runAction(CCEaseInOut::create(CCScaleTo::create(2.f, 0.7f), 2.f));
		}
		void recoverFromPosition(CCObject *sender) {
			auto lel = LevelEditorLayer::get();
			CCLayer *a = static_cast<CCLayer *>(lel->getChildren()->objectAtIndex(2));
			a->runAction(CCEaseInOut::create(CCMoveTo::create(2.f, prevPos), 2.f));
			a->runAction(CCEaseInOut::create(CCScaleTo::create(2.f, prevScale), 2.f));
		}

		void on1024(CCObject *sender) {
			TechnoObjectSelectorLayer::createCustomObject(10245);
		}
		void on1025(CCObject *sender) {
			TechnoObjectSelectorLayer::createCustomObject(10246);
		}
		void onExitButton(CCObject *sender) {
			int i = 0;
			while(i < selectorlayers.size()) {
				selectorlayers[i]->removeMeAndCleanup();
				i++;
			}
			selectorlayers.clear();
		}

		bool init() {
			CCLayer *objectSelector = CCLayer::create();
			CCLayer *scale9layer = CCLayer::create();

			const char *a = CreatePlayerTrigger::getTexture();
			const char *b = DestroyPlayersTrigger::getTexture();

			CCScale9Sprite *spr1 = CCScale9Sprite::create("GJ_square02.png");
			auto winsize = CCDirector::sharedDirector()->getWinSize();
			//spr1->setAnchorPoint({0, 1});
			spr1->setContentSize({winsize.width * 0.5f, winsize.height * 0.66666f});

			scale9layer->addChild(spr1);
			objectSelector->addChild(scale9layer, 0);

			//scale9layer->setAnchorPoint({0, 1});
			scale9layer->setPosition({winsize.width / 2, winsize.height / 2});
			
			auto cache = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();

			auto spr0 = CCSprite::createWithSpriteFrame(cache->spriteFrameByName(a));
			auto spr2 = CCSprite::createWithSpriteFrame(cache->spriteFrameByName(b));

			auto gjb = CCSprite::create("GJ_button_05.png");
			gjb->setScale(0.75);

			auto btn = CCMenuItemSpriteExtra::create(
				gjb, this, menu_selector(TechnoObjectSelectorLayer::on1024)
			);
			auto btn2 = CCMenuItemSpriteExtra::create(
				gjb, this, menu_selector(TechnoObjectSelectorLayer::on1025)
			);
			spr0->setPosition({15.f, 15.5f});
			spr2->setPosition({15.f, 15.5f});
			spr0->setScale(0.91875f);
			spr2->setScale(0.91875f);

			btn->addChild(spr0);
			btn2->addChild(spr2);

			auto men1 = CCMenu::create(btn, btn2, nullptr);
			men1->alignItemsHorizontallyWithPadding(20.f);

			objectSelector->addChild(men1, 1);

			men1->setPosition({winsize.width / 2, winsize.height / 2 + 20});

			auto bmf = CCLabelBMFont::create("Object Selector", "bigFont.fnt");
			bmf->setScale(0.5f);
			bmf->setPositionX(winsize.width / 2);
			bmf->setPositionY(winsize.height * 0.8f - 10);
			
			objectSelector->addChild(bmf, 1);

			auto exitBtn = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
			auto btn3 = CCMenuItemSpriteExtra::create(
				exitBtn, this, menu_selector(TechnoObjectSelectorLayer::onExitButton)
			);

			CCMenu *men2 = CCMenu::create();
			CCMenu *men3 = CCMenu::create();

			men2->setPosition({
				winsize.width * 0.25f,
				winsize.height * 0.8f
			});
			auto spr4 = ButtonSprite::create("Previous position");
			auto btn4 = CCMenuItemSpriteExtra::create(
				spr4, this, menu_selector(TechnoObjectSelectorLayer::recoverFromPosition)
			);
			men3->addChild(btn4);
			spr4->setScale(0.7f);
			men3->setPosition({
				winsize.width / 2,
				winsize.height * 0.25f
			});
			men2->addChild(btn3);

			objectSelector->addChild(men3, 2);
			objectSelector->addChild(men2, 2);

			this->addChild(objectSelector);

			auto base = CCSprite::create("square.png");
			base->setPosition({ 0, 0 });
			base->setScale(500.f);
			base->setColor({0, 0, 0});
			base->setOpacity(0);
			base->runAction(CCFadeTo::create(0.3f, 125));

			this->addChild(base, -1);

			objectSelector->setScale(0.1f);
			objectSelector->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.5f, 1.0f), 0.6f));

			selectorlayers.push_back(static_cast<CCLayer *>(this));

			return true;
		}

		CREATE_FUNC(TechnoObjectSelectorLayer);
	};
}

namespace TechnoEditorUI {
	CCMenuItemSpriteExtra *add10245;
};

class $modify(TEditorUI, EditorUI) {
	void on1024(CCObject *sender) {
		auto lel = LevelEditorLayer::get();
		lel->m_editorUI->addChild(TechnoObjects::TechnoObjectSelectorLayer::create(), 999);
	}
	void onPause(CCObject *sender) {
		EditorUI::onPause(sender);

		TechnoEditorUI::add10245->setVisible(true);
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
	}
	void onPlaytest(cocos2d::CCObject *sender) {
		EditorUI::onPlaytest(sender);

		TechnoEditorUI::add10245->setVisible(false);
	}
	bool init(LevelEditorLayer *l0) {
		if(!EditorUI::init(l0)) return false;

		TechnoObjects::selectorlayers.clear();

		auto spr0 = CCSprite::createWithSpriteFrameName("edit_addCBtn_001.png");
        auto btn = CCMenuItemSpriteExtra::create(
            spr0, this, menu_selector(TEditorUI::on1024)
        );
		btn->setID("object-selector-button");

		CCNode *n1 = this->getChildByID("playback-menu");
		CCNode *n2 = n1->getChildByID("music-playback-button");

		btn->setPosition(n2->getPosition());
		btn->setPositionX(btn->getPositionX() + 42);
		btn->setPositionY(btn->getPositionY() + 1);

		n1->addChild(btn);

		TechnoEditorUI::add10245 = btn;

		l0->m_debugDraw = !TechnoSettings::release;

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

	auto alert = FLAlertLayer::create(action, "Error" ,"New levels are gonna be added after <cg>CC!</c>", "Ok", "wait for 2.2");
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
		tch->setPositionY(winSize.height - 20);
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
