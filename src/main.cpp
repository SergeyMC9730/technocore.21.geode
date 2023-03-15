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
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/GameObject.hpp>
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
namespace TechnoGroups {
	class TechnoPlayer {
	public:
		PlayerObject *m_pPl;
		bool followPlayer;

		TechnoPlayer() {}
		TechnoPlayer(PlayerObject *pl) {
			m_pPl = pl;
		}
	};

	std::map<int, std::vector<TechnoPlayer *>> groups;
	
	std::vector<TechnoPlayer *> getPlayersFromGroup(int id) {
		for (const auto & [groupID, players] : groups) {
			if(groupID == id) return players;
		}
		return {};
	}
	
	void clear() {
		groups.clear();
	}
	
	void assign(int id, TechnoPlayer *obj) {
		if(getPlayersFromGroup(id).size() == 0) {
			groups.insert(std::pair<int, std::vector<TechnoPlayer *>>(id, {obj}));
			return;
		} else {
			int i = 0;
			for (const auto & [groupID, players] : groups) {
				if(groupID == id) groups.at(i).push_back(obj);
				i++;
			}
		}
	}
	
	void removePlayer(PlayerObject *obj) {
		int ii = 0;
		for (const auto & [groupID, players] : groups) {
			int i = 0; // player_list.erase(player_list.begin() + id)
			while(i < players.size()) {
				if(players[i]->m_pPl == obj) {
					groups.at(ii).erase(players.begin() + i);
				}
				i++;
			}
			ii++;
		}
	}

	TechnoPlayer *plToTP(PlayerObject *po) {
		for (const auto & [groupID, players] : groups) {
			int i = 0;
			while(i < players.size()) {
				if(players[i]->m_pPl == po) {
					return players[i];
				}
				i++;
			}
		}
		return nullptr;
	}

	void eraseGroup(int id) {
		int i = 0;
		for (const auto & [groupID, players] : groups) {
			if(groupID == id) {
				groups.erase(groupID);
			}
			i++;
		}
	}
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
	TechnoGroups::clear();
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
void syncPlayerY(float y) {
	int i = 0;
	while(i < player_list.size()) {
		if(TechnoGroups::plToTP(player_list[i])) {
			if(TechnoGroups::plToTP(player_list[i])->followPlayer) {
				player_list[i]->m_position.y = y;
				player_list[i]->setPositionY(y);
			}
		} else {
			if(!TechnoSettings::release) printf("WARN: Player is not inside techno groups!");
		}
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
	TechnoGroups::removePlayer(player_list[id]);
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

	bool isFollowingPlayer() {
		return getObject()->m_tintTrigger;
	}
	int getPlayerGroupID() {
		return getObject()->m_targetColorID;
	}

	std::map<uint32_t, std::string> onExport() {
		std::map<uint32_t, std::string> mp;

		mp.insert(std::pair<uint32_t, std::string>(23, std::to_string(getObject()->m_targetColorID)));
		mp.insert(std::pair<uint32_t, std::string>(120, std::to_string((int)getObject()->m_tintTrigger)));

		return mp;
	}
	void onImport(std::map<uint32_t, std::string> data) {
		for (const auto & [key, value] : data) {
			switch(key) {
				case 23: {
					getObject()->m_targetColorID = std::stoi(value);
					break;
				}
				case 120: {
					getObject()->m_tintTrigger = bool(std::stoi(value));
					break;
				}
			}
		}
	}

	void onReset() override {
		destroyPlayers(true);
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
		if(isFollowingPlayer()) {
			pos.y = gl->m_player1->getPositionY();
		}
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
		auto tpo = new TechnoGroups::TechnoPlayer(po);
		tpo->followPlayer = isFollowingPlayer();
		TechnoGroups::assign(getPlayerGroupID(), tpo);
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
			m_object->setOpacity(255);
		}
	}
};

class DestroyPlayersTrigger : public GameObjectController {
 public:
	DestroyPlayersTrigger(GameObject* g) : GameObjectController(g) {}

	static const char *getTexture() {
		return "edit_ePDestroyBtn_001.png";
	}

	int getPlayerGroupID() {
		return getObject()->m_targetColorID;
	}

	std::map<uint32_t, std::string> onExport() {
		std::map<uint32_t, std::string> mp;

		mp.insert(std::pair<uint32_t, std::string>(23, std::to_string(getObject()->m_targetColorID)));

		return mp;
	}
	void onImport(std::map<uint32_t, std::string> data) {
		for (const auto & [key, value] : data) {
			switch(key) {
				case 23: {
					getObject()->m_targetColorID = std::stoi(value);
					break;
				}
			}
		}
	}

	// What happens when the object is "triggered"
	void onTrigger(GJBaseGameLayer* gl) override {
		int i = 0;
		auto pls = TechnoGroups::getPlayersFromGroup(getPlayerGroupID());

		while(i < pls.size()) {
			destroyPlayerByAddress(pls[i]->m_pPl);
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

namespace TechnoGarageLayer {
	class GarageDummy {
	public:
		void onDummy(CCObject *sender) {}
	};
	GarageDummy *dummy;
	GJGarageLayer *garage;
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

	TechnoGarageLayer::dummy = new TechnoGarageLayer::GarageDummy();

	return true;
}

void doPlayerJob(float delta) {
	int i = 0;
	float step = std::min(2.0f, delta * 60.0f); // took from opengd
	delta = step;
	while (i < player_list.size()) {
		//printf("dl: %f; pspeed: %f; portal at %p\n", dl, player_list[i]->m_playerSpeed, GJBaseGameLayer::get()->m_player1->m_lastActivatedPortal);
		player_list[i]->update(delta);
		if(player_list[i]->m_isShip) {
			player_list[i]->updateShipRotation(delta);
		} else if (player_list[i]->m_isBall) {
			player_list[i]->runBallRotation(delta);
		} else {
			player_list[i]->updateRotation(delta);
		}
		player_list[i]->updateRobotAnimationSpeed();
		//player_list[i]->updateJump(0);
		player_list[i]->updatePlayerFrame(0);
		player_list[i]->updatePlayerFrame(1);
		if(PlayLayer::get()) {
			PlayLayer::get()->checkCollisions(player_list[i], delta);
		} else {
			LevelEditorLayer::get()->checkCollisions(player_list[i], delta);
		}
		if(TechnoGroups::plToTP(player_list[i]) && PlayLayer::get()) {
			if(TechnoGroups::plToTP(player_list[i])->followPlayer) player_list[i]->setRotation( PlayLayer::get()->m_player1->getRotation());
		}
		player_list[i]->postCollision(delta);

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
		if(PlayLayer::get()) {
			if(this == PlayLayer::get()->m_player2) {
				this->m_position.x = PlayLayer::get()->m_player1->m_position.x;
			} /*else if (this == PlayLayer::get()->m_player1) {
				if(!TechnoSettings::release) printf("DELTA PLAYER %f\n", delta);
			} else {
				if(!TechnoSettings::release) printf("DELTA DUMMY %f\n", delta);
			}*/
		}
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
		// syncPlayerX(this->m_player1->m_position.x);
		int i = 0;
		while(i < player_list.size()) {
			if(TechnoGroups::plToTP(player_list[i])) {
				if(TechnoGroups::plToTP(player_list[i])->followPlayer) {
					syncPlayerY(this->m_player1->getPositionY());
				}
			} else {
				if(!TechnoSettings::release) printf("WARN: Player is not inside techno groups!");
			}
			i++;
		}
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
		if(this->m_player2) {
			this->m_player2->m_position.x = this->m_player1->m_position.x;
		}
		int i = 0;
		while(i < player_list.size()) {
			if(TechnoGroups::plToTP(player_list[i])) {
				if(TechnoGroups::plToTP(player_list[i])->followPlayer) {
					syncPlayerY(this->m_player1->m_position.y);
				}
			} else {
				if(!TechnoSettings::release) printf("WARN: Player is not inside techno groups!");
			}
			i++;
		}
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

		featuredBtn->setPosition({122.f - 6.f, 54.f});
		hafBtn->setPosition({228.f - 6.f, 54.175f});
		mpBtn->setPosition({283.913f - 6.f, 155.f});
		searchBtn->setPosition({334.f - 6.f, 54.175f});
		questsBtn->setPosition({64.369f - 6.f, 155.f});
		dailyBtn->setPosition({174.194f - 6.f, 155.f});
		gauntletsBtn->setPosition({391.631f - 6.f, 155.f});
		createBtn->setPosition({122.f - 6.f, 255.825f});
		savedBtn->setPosition({228.f - 6.f, 255.825f});
		scoresBtn->setPosition({334.f - 6.f, 255.825f});

		auto winsize = CCDirector::sharedDirector()->getWinSize();
		cbMenu->setPositionX(winsize.width / 2);

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
	class CreatePlayerPopup : public CCLayer {
	private:
		CCTextInputNode *m_pInputPGID;
		GameObject *m_pSelectedObject;

		CCMenuItemToggler *m_pFollowPlayer;
	public:
		void onToggler1PressMaybe(CCObject *sender) {}

		void onExitButton(CCObject *sender) {
			int i = 0;
			while(i < selectorlayers.size()) {
				selectorlayers[i]->removeMeAndCleanup();
				i++;
			}
			selectorlayers.clear();
		}

		bool init(GameObject *object) {
			m_pSelectedObject = object;

			CCLayer *objectSelector = CCLayer::create();
			CCLayer *scale9layer = CCLayer::create();

			CCScale9Sprite *spr1 = CCScale9Sprite::create("GJ_square01.png");
			auto winsize = CCDirector::sharedDirector()->getWinSize();
			//spr1->setAnchorPoint({0, 1});
			spr1->setContentSize({winsize.width * 0.66666f, winsize.height * 0.66666f});

			scale9layer->addChild(spr1);
			objectSelector->addChild(scale9layer, 0);

			scale9layer->setPosition({winsize.width / 2, winsize.height / 2});

			auto bmf = CCLabelBMFont::create("Create Player Trigger", "bigFont.fnt");
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
			CCMenu *men1 = CCMenu::create();

			men2->setPosition({
				winsize.width * 0.20f,
				winsize.height * 0.8f
			});
			men3->setPosition({
				winsize.width * 0.27f,
				winsize.height * 0.6f
			});
			men1->setPosition({
				winsize.width * 0.27f,
				winsize.height * 0.45f
			});
			men2->addChild(btn3);

			objectSelector->addChild(men2, 2);

			CCSprite *spr_square = CCSprite::create("square02_001.png");
			spr_square->setOpacity(128);
			spr_square->setScaleY(0.3f);

			CCLabelBMFont *men3_info = CCLabelBMFont::create("Player Group ID", "bigFont.fnt");
			men3_info->setAnchorPoint({0.5f, 0.5f});
			men3_info->setScale(0.5f);
			men3_info->setPositionX(134.f);

			auto inputid = CCTextInputNode::create(32.f, 16.f, "0", "bigFont.fnt");
			men3->addChild(inputid, 1);
			men3->addChild(spr_square, 0);
			men3->addChild(men3_info, 0);

			CCSprite *checkOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
			CCSprite *checkOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");

			m_pFollowPlayer = CCMenuItemToggler::create(checkOff, checkOn, this, menu_selector(CreatePlayerPopup::onToggler1PressMaybe));
			CCLabelBMFont *men1_info = CCLabelBMFont::create("Follow Player", "bigFont.fnt");
			men1_info->setAnchorPoint({0.5f, 0.5f});
			men1_info->setScale(0.5f);
			men1_info->setPositionX(100.f);

			char *buffer = (char *)malloc(128);
			char *currentGroupID = itoa(object->m_targetColorID, buffer, 10);
			free(buffer);

			inputid->setString(currentGroupID);

			m_pInputPGID = inputid;

			men1->addChild(m_pFollowPlayer, 0);
			men1->addChild(men1_info, 1);

			objectSelector->addChild(men1, 2);
			objectSelector->addChild(men3, 2);

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

			scheduleUpdate();

			m_pFollowPlayer->toggle(object->m_tintTrigger);

			return true;
		}

		void update(float delta) {
			m_pSelectedObject->m_targetColorID = atoi(m_pInputPGID->getString());
			if(m_pSelectedObject->m_targetColorID > 65 || m_pSelectedObject->m_targetColorID < 0) {
				m_pSelectedObject->m_targetColorID = 64;
			}
			m_pSelectedObject->m_tintTrigger = m_pFollowPlayer->isToggled();
			
		}

		static CreatePlayerPopup* create(GameObject *object) { 
			CreatePlayerPopup* pRet = new CreatePlayerPopup(); 
			if (pRet && pRet->init(object)) { 
				pRet->autorelease();
				return pRet;
			} else {
				delete pRet;
				pRet = 0;
				return 0; 
			} 
		}
	};

	class DestroyPlayersPopup : public CCLayer {
	private:
		CCTextInputNode *m_pInputPGID;
		GameObject *m_pSelectedObject;
	public:
		void onToggler1PressMaybe(CCObject *sender) {}

		void onExitButton(CCObject *sender) {
			int i = 0;
			while(i < selectorlayers.size()) {
				selectorlayers[i]->removeMeAndCleanup();
				i++;
			}
			selectorlayers.clear();
		}

		bool init(GameObject *object) {
			m_pSelectedObject = object;

			CCLayer *objectSelector = CCLayer::create();
			CCLayer *scale9layer = CCLayer::create();

			CCScale9Sprite *spr1 = CCScale9Sprite::create("GJ_square01.png");
			auto winsize = CCDirector::sharedDirector()->getWinSize();
			//spr1->setAnchorPoint({0, 1});
			spr1->setContentSize({winsize.width * 0.66666f, winsize.height * 0.66666f});

			scale9layer->addChild(spr1);
			objectSelector->addChild(scale9layer, 0);

			scale9layer->setPosition({winsize.width / 2, winsize.height / 2});

			auto bmf = CCLabelBMFont::create("Destroy Players Trigger", "bigFont.fnt");
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
				winsize.width * 0.20f,
				winsize.height * 0.8f
			});
			men3->setPosition({
				winsize.width * 0.27f,
				winsize.height * 0.6f
			});
			men2->addChild(btn3);

			objectSelector->addChild(men2, 2);

			CCSprite *spr_square = CCSprite::create("square02_001.png");
			spr_square->setOpacity(128);
			spr_square->setScaleY(0.3f);

			CCLabelBMFont *men3_info = CCLabelBMFont::create("Player Group ID", "bigFont.fnt");
			men3_info->setAnchorPoint({0.5f, 0.5f});
			men3_info->setScale(0.5f);
			men3_info->setPositionX(134.f);

			auto inputid = CCTextInputNode::create(32.f, 16.f, "0", "bigFont.fnt");
			men3->addChild(inputid, 1);
			men3->addChild(spr_square, 0);
			men3->addChild(men3_info, 0);

			char *buffer = (char *)malloc(128);
			char *currentGroupID = itoa(object->m_targetColorID, buffer, 10);
			free(buffer);

			inputid->setString(currentGroupID);

			m_pInputPGID = inputid;

			objectSelector->addChild(men3, 2);

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

			scheduleUpdate();

			return true;
		}

		void update(float delta) {
			m_pSelectedObject->m_targetColorID = atoi(m_pInputPGID->getString());
			if(m_pSelectedObject->m_targetColorID > 129 || m_pSelectedObject->m_targetColorID < 0) {
				m_pSelectedObject->m_targetColorID = 128;
			}
			
		}

		static DestroyPlayersPopup* create(GameObject *object) { 
			DestroyPlayersPopup* pRet = new DestroyPlayersPopup(); 
			if (pRet && pRet->init(object)) { 
				pRet->autorelease();
				return pRet;
			} else {
				delete pRet;
				pRet = 0;
				return 0; 
			} 
		}
	};
}

namespace TechnoEditorUI {
	CCMenuItemSpriteExtra *add10245;
};

class $modify(TGJGarageLayer, GJGarageLayer) {
	void nCallback(CCHttpClient* client, CCHttpResponse* response) {
		if(!TechnoSettings::release) {
			printf("response: %d %d %s %s\n", response->isSucceed(), response->getResponseCode(), response->getErrorBuffer(), response->getResponseData()->data());
		}
	
		return;
	}

	void onUpdateNickname(CCObject *sender) {
		FLAlertLayer::create("Nickname", "Your nickname would be updated now. (you don't need to wait)", "OK")->show();
		auto gm = GameManager::get();
		if(!TechnoSettings::release) {
			printf("udid: %s\n", gm->m_playerUDID.c_str());
		}
		CCHttpClient *cl = CCHttpClient::getInstance();
		CCHttpRequest *req = new CCHttpRequest;
		req->setRequestType(CCHttpRequest::HttpRequestType::kHttpPost);
		std::string strdata = "udid=";
		strdata += gm->m_playerUDID.c_str();
		strdata += "&nickname=";
		CCTextInputNode *inputnode = static_cast<CCTextInputNode *>(TechnoGarageLayer::garage->getChildByID("username-label"));
		strdata += inputnode->getString();
		std::string str = "https://gd.dogotrigger.xyz/tech21/updateGJNickname.php?";
		str += strdata;
		req->setUrl(str.c_str());
		req->setRequestData(strdata.c_str(), strdata.size());
		if(!TechnoSettings::release) req->setResponseCallback(this, httpresponse_selector(TGJGarageLayer::nCallback));
		cl->send(req);
	}
	bool init() {
		if(!GJGarageLayer::init()) return false;

		if(GJAccountManager::sharedState()->m_accountID != 0) {
			if(!TechnoSettings::release) printf("registered player, skipping!");
			return true;
		} else {
			sortAllChildren();
			SimplePlayer *pl = static_cast<SimplePlayer *>(getChildren()->objectAtIndex(5));
			CCMenu *men = CCMenu::create();
			CCSprite *spr = CCSprite::createWithSpriteFrameName("GJ_rotationControlBtn02_001.png");
			
			auto is = CCMenuItemSpriteExtra::create(spr, this, menu_selector(TGJGarageLayer::onUpdateNickname));
			auto label = CCLabelBMFont::create("Update nickname", "bigFont.fnt");
			label->setPosition({78.f, 0.f});
			label->setScale(0.4f);
			
			men->addChild(is);
			men->addChild(label);
			pl->addChild(men, 16);

			men->setPosition({34.f, 0.f});
			men->setAnchorPoint({0.f, 0.f});
			men->setScale(0.6f);
			
		}
		TechnoGarageLayer::garage = this;
		return true;
	}
};

class $modify(TEditorUI, EditorUI) {
	void editObject(CCObject *sender) {
		
		EditorUI *eui = EditorUI::get();
		auto objects = eui->getSelectedObjects();
		int i = 0;
		while(i < objects->count()) {
			GameObject *obj = static_cast<GameObject *>(objects->objectAtIndex(i));
			if(obj->m_objectID == 10245) { // create player trigger
				auto lel = LevelEditorLayer::get();
				lel->m_editorUI->addChild(TechnoObjects::CreatePlayerPopup::create(obj), 999);
				return;
			} else if(obj->m_objectID == 10246) { // destroy players trigger
				auto lel = LevelEditorLayer::get();
				lel->m_editorUI->addChild(TechnoObjects::DestroyPlayersPopup::create(obj), 999);
				return;
			}
			i++;
		}
		EditorUI::editObject(sender);
	}

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
