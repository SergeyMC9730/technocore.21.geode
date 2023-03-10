#define CAC_PROJ_NAME "Template"

#include "techno.h"
#include "LevelTools.h"
#include "CreatorLayer.h"
#include "InfoLayer.h"
#include "networking.h"
#include "Rainix/LC/main.h"
#include "Rainix/LC/Logger.h"
// #include "GJDialogObject.h"
#include "GameObjectFactory.hpp"
#include "include/gd/level_nodes/GameObject.h"
#include "include/gd/sprite_nodes/PlayerObject.h"
#include "hooks.h"

std::vector<PlayerObject *> player_list;
bool isSetupComplete;

#define kTimeModSlow 0.70f
#define kTimeModNormal 0.9f
#define kTimeModFast 1.1f
#define kTimeModVeryFast 1.3f
#define kTimeModVeryVeryFast 1.6f

namespace Techno {
	namespace Settings {
		bool release = false;
	}

	void playPlayerDeathEffect(PlayerObject *pl) {
		// auto fade = CCFadeTo::create(0.05, 0);
		// pl->runAction(fade);
		// auto cw = CCCircleWave::create(1, 2, 3, false);
		//CCNode *test = CCNode::create();
		// if(GameManager::sharedState()->getPlayLayer()) GameManager::sharedState()->getPlayLayer()->m_objectLayer->addChild(cw);
		// cw->setPosition(pl->getPosition());
	}
	void destroyPlayerByID(int id) {
		// delete 3 (index 2)
		//player_list[id]->playerDestroyed(false);
		// player_list[id]->fadeOutStreak2(0.2f);
		// player_list[id]->stopDashing();
		// player_list[id]->stopRotation(false);
		// player_list[id]->stopAllActions();
		// playPlayerDeathEffect(player_list[id]);
		player_list[id]->removeMeAndCleanup();
		player_list.erase(player_list.begin() + id);
	}
	void destroyPlayerByAddress(PlayerObject *addr) {
		int i = 0;
		int res = 0;
		while(i < player_list.size()) {
			if(addr == player_list[i]) {
				destroyPlayerByID(i);
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
			if(GameManager::sharedState()->getPlayLayer()) addr = GameManager::sharedState()->getPlayLayer();
			else addr = GameManager::sharedState()->m_pLevelEditorLayer;
			auto po = PlayerObject::create(rand() % 12, rand() % 12, (CCLayer *)addr);
			//po->setSecondColor({(unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255)});
			po->setColor({(unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255)});
			if(GameManager::sharedState()->getPlayLayer()) GameManager::sharedState()->getPlayLayer()->m_batchNodePlayer->addChild(po);
			else {
				GameManager::sharedState()->m_pLevelEditorLayer->m_batchNodePlayer->addChild(po);
			}
			po->setPosition(this->getObject()->getPosition());
			// po->addAllParticles();
			// int particles = po->m_particleSystems->count();
			// int i = 0;

			// while(i < particles) {
			// 	if(GameManager::sharedState()->getPlayLayer()) {
			// 		auto ccn = (CCNode *)(po->m_particleSystems->objectAtIndex(i));
			// 		ccn->setParent(GameManager::sharedState()->getPlayLayer()->m_objectLayer);
			// 		// po->m_regularTrail->setParent(GameManager::sharedState()->getPlayLayer()->m_objectLayer);
			// 		// po->m_waveTrail->setParent(GameManager::sharedState()->getPlayLayer()->m_objectLayer);
			// 		//po->m_particleSystem->setParent(GameManager::sharedState()->getPlayLayer()->m_objectLayer);
			// 	}
			// 	i++;
			// }
			player_list.push_back(po);
		}

		void setup() override {
			// Disable glow because there is no glow texture for this sprite
			m_glowEnabled = false;

			// Set custom texture for this object
			overrideSpriteFrame(getTexture());

			// Touch-triggered object with the Modifier type. This object will run onTrigger when collided with
			m_object->m_touchTriggered = true;
			m_object->m_objectType = kGameObjectTypeModifier;

			if(GameManager::sharedState()->getPlayLayer()) {
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
			m_object->m_objectType = kGameObjectTypeModifier;

			if(GameManager::sharedState()->getPlayLayer()) {
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
			LOGI("doing std::string thing 8\n");
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
		}
		void setup() override {
			m_glowEnabled = true;
			overrideSpriteFrame(m_sFrame);
			m_object->m_touchTriggered = true;
			m_object->m_objectType = kGameObjectTypeModifier;
		}
	};


	bool setupStuff() {
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

	void doPlayerJob(float delta) {
		int i = 0;
		while (i < player_list.size()) {
			float dl = delta * 60.f;
			//printf("dl: %f; pspeed: %f; portal at %p\n", dl, player_list[i]->m_playerSpeed, GJBaseGameLayer::get()->m_player1->m_lastActivatedPortal);
			player_list[i]->update(dl);
			if(player_list[i]->isShipMode()) {
				player_list[i]->updateShipRotation(dl);
			} else if (player_list[i]->isBallMode()) {
				player_list[i]->runBallRotation(dl);
			} else {
				player_list[i]->updateRotation(dl);
			}
			player_list[i]->updateRobotAnimationSpeed();
			player_list[i]->updateJump(0);
			player_list[i]->updatePlayerFrame(0);
			player_list[i]->updatePlayerFrame(1);
			if(GameManager::sharedState()->getPlayLayer()) {
				GameManager::sharedState()->getPlayLayer()->checkCollisions(player_list[i], dl);
			} else {
				//GameManager::sharedState()->m_pLevelEditorLayer->checkCollisions(player_list[i], dl);
			}
			player_list[i]->postCollision(dl);

			i++;
		}
	}

	namespace TPlayerObject {
		void (*_playerDestroyed)(PlayerObject *pl, bool p0);
		bool (*_collidedWithObject)(PlayerObject *pl, float dt, GameObject *obj);

		void playerDestroyed(PlayerObject *pl, bool p0) {
			if(GameManager::sharedState()->getPlayLayer()) {
				if((pl == GameManager::sharedState()->getPlayLayer()->m_player1) || (pl == GameManager::sharedState()->getPlayLayer()->m_player2)) {
					_playerDestroyed(pl, p0);
					return;
				} else {
					destroyPlayerByAddress(pl);
					return;
				}
			} else {
				destroyPlayers(false);
				_playerDestroyed(pl, p0);
			}
			return;
		}

		bool collidedWithObject(PlayerObject *pl, float dt, GameObject *obj) {
			if (auto mg = GameObjectFactory::get()->fetch(obj)) {
				mg.value()->onCollide(dt, pl);
				return true;
			} else {
				return _collidedWithObject(pl, dt, obj);
			}
		}

		void applyHooks() {
			HOOK_FUNCX("_ZN12PlayerObject15playerDestroyedEb", playerDestroyed, _playerDestroyed);
			HOOK_FUNCX("_ZN12PlayerObject18collidedWithObjectEfP10GameObject", collidedWithObject, _collidedWithObject);
		}
	}

	namespace TEditorUI {
		CCMenuItemSpriteExtra *add10245;
		CCMenuItemSpriteExtra *add10246;

		void(*_onPause)(CCLayer *eui, CCObject *sender);
		void(*_onStopPlaytest)(CCLayer *eui, CCObject *sender);
		void(*_onPlaytest)(CCLayer *eui, CCObject *sender);
		bool(*_init)(CCLayer *eui, CCObject *lmao);

		class ButtonSet {
		public:
			void on1024(CCObject *sender) {
				auto lel = GameManager::sharedState()->m_pLevelEditorLayer;
				lel->m_gameLayer->addChild(lel->createObject(10245, ccp(rand() % 50 + 100, rand() % 50 + 100), false));
			}

			void on1025(CCObject *sender) {
				auto lel = GameManager::sharedState()->m_pLevelEditorLayer;
				lel->m_gameLayer->addChild(lel->createObject(10246, ccp(rand() % 50 + 100, rand() % 50 + 100), false));
			}
		};
		void onPause(CCLayer *eui, CCObject *sender) {
			_onPause(eui, sender);

			add10245->setVisible(true);
			add10246->setVisible(true);
		}

		void onStopPlaytest(CCLayer *eui, CCObject *sender) {
			_onStopPlaytest(eui, sender);

			destroyPlayers(true);
			add10245->setVisible(true);
			add10246->setVisible(true);
		}

		void onPlaytest(CCLayer *eui, CCObject *sender) {
			_onPlaytest(eui, sender);

			add10245->setVisible(false);
			add10246->setVisible(false);
		}

		bool init(CCLayer *eui, CCLayer *lmao) {
			if(!_init(eui, lmao)) return false;

			const char *a = CreatePlayerTrigger::getTexture();
			const char *b = DestroyPlayersTrigger::getTexture();

			auto cache = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();

			auto spr0 = CCSprite::createWithSpriteFrame(cache->spriteFrameByName(a));
			auto spr1 = CCSprite::createWithSpriteFrame(cache->spriteFrameByName(b));

			auto gjb = CCSprite::create("GJ_button_05.png");
			gjb->setScale(0.75);

			auto btn = CCMenuItemSpriteExtra::create(
				gjb, gjb, eui, menu_selector(ButtonSet::on1024)
			);
			auto btn2 = CCMenuItemSpriteExtra::create(
				gjb, gjb, eui, menu_selector(ButtonSet::on1025)
			);
			spr0->setPosition({15.f, 15.5f});
			spr1->setPosition({15.f, 15.5f});
			spr0->setScale(0.91875f);
			spr1->setScale(0.91875f);
			btn->addChild(spr0);
			btn2->addChild(spr1);
			btn->setPosition(108.f, -234.f);
			btn2->setPosition(108.f, -274.f);

			add10245 = btn;
			add10246 = btn2;

			eui->addChild(btn);
			eui->addChild(btn2);			

			return true;
		}

		void applyHooks() {
			HOOK_FUNCX("_ZN8EditorUI10onPlaytestEPN7cocos2d8CCObjectE", onPlaytest, _onPlaytest);
			HOOK_FUNCX("_ZN8EditorUI7onPauseEPN7cocos2d8CCObjectE", onPause, _onPause);
			HOOK_FUNCX("_ZN8EditorUI14onStopPlaytestEPN7cocos2d8CCObjectE", onStopPlaytest, _onStopPlaytest);
		}

	}

	namespace TPlayLayer {
		bool (*_init)(PlayLayer *pl, GJGameLevel *level);
		void (*_update)(PlayLayer *pl, float f);

		bool init(PlayLayer *pl, GJGameLevel *level) {
			destroyPlayers(false);
			
			return _init(pl, level);
		}
		void update(PlayLayer *pl, float f) {
			_update(pl, f);
			doPlayerJob(f);
		}
		void applyHooks() {
			HOOK_FUNCX("_ZN9PlayLayer4initEP11GJGameLevel", init, _init);
			HOOK_FUNCX("_ZN9PlayLayer6updateEf", update, _update);
		}
	}
	namespace TLevelEditorLayer {
		bool (*_init)(CCLayer *pl, GJGameLevel *level);
		void (*_update)(CCLayer *pl, float f);

		bool init(CCLayer *pl, GJGameLevel *level) {
			destroyPlayers(false);
			
			return _init(pl, level);
		}
		void update(CCLayer *pl, float f) {
			_update(pl, f);
			doPlayerJob(f);
		}

		void applyHooks() {
			HOOK_FUNCX("_ZN16LevelEditorLayer4initEP11GJGameLevel", init, _init);
			HOOK_FUNCX("_ZN16LevelEditorLayer6updateEf", update, _update);
		}
	}

	namespace TKeysLayer {
		bool (*_init)(CCLayer *self);

		bool init(CCLayer *self) {
			if(!_init(self)) return false;

			self->sortAllChildren();
			auto shop1_00 = (CCNode *)(self->getChildren()->objectAtIndex(3));
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
		void applyHooks() {
			HOOK_FUNCX("_ZN9KeysLayer4initEv", init, _init);
		}
	}
	namespace TInfoLayer {
		void applyHooks() {}
	}
	namespace TMessage {
		void test(CCLayer *l) {}
	}
	namespace TMenuLayer {
		class StandardFLAlertLayerProtocol : public FLAlertLayerProtocol {
		public:
			void FLAlert_Clicked(FLAlertLayer *alertlayer, bool btn2) {
				alertlayer->removeMeAndCleanup();
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
				SimpleHTTPRequestLayer *l = (SimpleHTTPRequestLayer *)pTarget;

				l->close();

				alertlayer->removeMeAndCleanup();

				if(btn2) {
					LOGI("doing std::string thing 9\n");
					FLAlertLayer::create((FLAlertLayerProtocol *)(new StandardFLAlertLayerProtocol), "2.2", std::string("It's ok to <cy>wait 2.2..</c>"), "OK", "Yeah")->show();
				}
			};
		};

		bool (*init_o)(MenuLayer *);

		class MenuLayer_IOActions {
		public:
			static void buttonCallback(CCObject * sender) {
				MenuLayer_TestAction *action = new MenuLayer_TestAction;

				CCLayer *cl = (CCLayer *)sender;
				action->setTarget(cl);

				FLAlertLayer::create(action, "Error", "TEST", "OK", "Wait for 2.2")->show();
			}
			void nCallback(CCHttpClient* client, CCHttpResponse* response) {
				// SimpleHTTPRequestLayer *l = (SimpleHTTPRequestLayer *)(response->getHttpRequest()->getTarget());

				// l->close();
				MenuLayer_IOActions::buttonCallback(response->getHttpRequest()->getTarget());

				return;
			}
			void onPlay(CCObject *sender) {
				SimpleHTTPRequestLayer *l = SimpleHTTPRequestLayer::create();
				
				l->start("https://gd.dogotrigger.xyz/tech21/getOfficialLevels21.php?gameVersion=21", httpresponse_selector(MenuLayer_IOActions::nCallback));

				CCNode *cn = (CCNode *)sender;

				cn->addChild(l, 1024);

				l->m_pLC->setPosition(cn->getPositionX(), cn->getPositionY());
				l->setPosition(56, 56);
			}
		};

		bool init(MenuLayer *self)
		{
			if (!init_o(self))
				return false;

			MenuLayer_initH(self);

			CCSize winSize = CCDirector::sharedDirector()->getWinSize();

			auto tch = CCLabelBMFont::create("TechnoGDPS BETA BUILD 1.0", "bigFont.fnt");
			tch->setPositionY(300);
			tch->setPositionX(winSize.width / 2);
			tch->setScale(.375f);
			tch->setAnchorPoint({0.5f, 0.f});

			self->addChild(tch);

			self->sortAllChildren();

			setupStuff();
			// auto shop1_00 = (CCNode *)(self->getChildren()->objectAtIndex(3));
			// shop1_00->sortAllChildren();
			// auto shop1_01 = (CCNode *)(shop1_00->getChildren()->objectAtIndex(0));
			// shop1_01->sortAllChildren();
			// auto shop1_02 = (CCNode *)(shop1_01->getChildren()->objectAtIndex(22));
			// shop1_02->sortAllChildren();
			// auto shop1_03 = (CCNode *)(shop1_02->getChildren()->objectAtIndex(0));
			// shop1_03->sortAllChildren();
			// auto shop1_04 = (CCNode *)(shop1_03->getChildren()->objectAtIndex(0));
			// auto shop2_04 = (CCNode *)(shop1_03->getChildren()->objectAtIndex(1));

			// shop1_04->setPositionX(0.f);
			// shop2_04->removeMeAndCleanup();
			// auto pb00 = (CCNode *)(self->getChildren()->objectAtIndex(2));
			// pb00->sortAllChildren();
			// auto pb01 = (CCNode *)(self->getChildren()->objectAtIndex(0));

			// pb01->removeMeAndCleanup();

			// CCMenu *men = CCMenu::create();
			// CCSprite* PlaySprite = CCSprite::createWithSpriteFrameName("GJ_playBtn_001.png");
			// CCMenuItemSpriteExtra *Play = CCMenuItemSpriteExtra::create(
			// 	PlaySprite,
			// 	PlaySprite,
			// 	PlaySprite,
			// 	menu_selector(MenuLayer_IOActions::onPlay)
			// );
			// men->addChild(Play);
			// men->setPositionY(men->getPositionY() + 10);
			//self->addChild(men);
			// pb00->addChild(men);

			return true;
		}
		void applyHooks() {
			HOOK_FUNC("_ZN9MenuLayer4initEv");
			// HOOK_FUNCX("_ZN9MenuLayer6onPlayEPN7cocos2d8CCObject", onPlay, _onPlay);
		}
	}
	namespace TGameObject {
		void applyHooks() {

		}
	}
	namespace TCreatorLayer {
		#define CHECKPOS(x, y) node2->getPositionX() == x && node2->getPositionY() == y

		bool (*_init)(CCLayer *self);

		bool init(CCLayer *self) {
			if(!_init(self)) return false;

			CCObject *obj = NULL;
			CCNode* node = NULL;
			CCNode *node_to_remove = CCNode::create();
			CCARRAY_FOREACH(self->getChildren(), obj) {
				node = (CCNode *)obj;
				if(node->getPositionX() == 284.5f && node->getPositionY() == 160.f) {
					CCObject *obj2 = NULL;
					CCNode *node2 = NULL;
					CCARRAY_FOREACH(node->getChildren(), obj2) {
						node2 = (CCNode *)obj2;
						if(CHECKPOS(-100.f, 97.f)) { // 0
							node2->setPositionX(-110.f);
							node2->setPositionY(97.f);	
						}
						if(CHECKPOS(0.f, 97.f)) { // 1
							node2->setPositionX(-1.f);
						}
						if(CHECKPOS(100.f, 97.f)) { // 2
							node2->setPositionX(109.f);
						}
						if(CHECKPOS(-150.f, 0.f)) { // 3
							node2->setPositionX(-160.f);
						}
						if(CHECKPOS(-50.f, 0.f)) { // 4
							node2->setPositionX(-52.f);
						}
						if(CHECKPOS(50.f, 0.f)) { // 5
							if(node_to_remove != NULL) {
								node_to_remove->removeMeAndCleanup();
							}
							node_to_remove = node2;
						}
						if(CHECKPOS(-150.f, -97.f)) { // 6
							node2->setPositionX(-113.f);
						}
						if(CHECKPOS(-50.f, -97.f)) { // 7
							node2->setPositionX(-1.f);
						}
						if(CHECKPOS(50.f, -97.f)) { // 8
							node2->setPositionX(56.f);
							node2->setPositionY(0.f);
						}
						if(CHECKPOS(150.f, -97.f)) { // 9
							node2->setPositionX(112.f);
						}
						if(CHECKPOS(150.f, 0.f)) { // 10
							node2->setPositionX(165.f);
						}
					}
				}
			}

			node_to_remove->removeMeAndCleanup();

			return true;
		}
		void applyHooks() {
			HOOK_FUNCX("_ZN12CreatorLayer4initEv", init, _init);
		}
	}
	void applyHooks()
	{
		Techno::TMenuLayer::applyHooks();
		// Techno::TLevelTools::applyHooks();
		Techno::TGameObject::applyHooks();
		Techno::TCreatorLayer::applyHooks();
		Techno::TInfoLayer::applyHooks();
		Techno::TKeysLayer::applyHooks();
		//Techno::TLevelEditorLayer::applyHooks();
		// Techno::TEditorUI::applyHooks();
		Techno::TPlayLayer::applyHooks();
		Techno::TPlayerObject::applyHooks();

		Camila::CGameObject::applyHooks();
		// Camila::CGJBaseGameLayer::applyHooks();	
	}
}

#ifdef __ANDROID__
__attribute__((constructor)) void libinit()
{
	Techno::applyHooks();
	//Rainix_LCLoader();
}
#endif
