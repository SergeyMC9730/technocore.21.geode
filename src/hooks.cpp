#include <Geode/Geode.hpp>
#include "../include/GameObjectFactory.hpp"
#include <Geode/modify/GameObject.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

USE_GEODE_NAMESPACE();

using namespace cocos2d;

class $modify(GameObjectHook, GameObject) {
	static GameObject* createWithKey(int object_id) {
		auto ctr = GameObjectFactory::get();

		if (auto generator = ctr->fetchGenerator(object_id)) {
			auto obj = GameObject::createWithKey(object_id);
			if (!obj) {
				obj = GameObject::createWithFrame(ctr->fetchTexture(object_id).c_str());
			}
			ctr->addContainer(obj->m_uniqueID, generator.value()(obj));

			return obj;
		} else {
			return GameObject::createWithKey(object_id);
		}
	}

	void triggerObject(GJBaseGameLayer* gl) {
		if (auto mg = GameObjectFactory::get()->fetch(this)) {
			mg.value()->onTrigger(gl);
		} else {
			GameObject::triggerObject(gl);
		}
	}

	void resetObject() {
		if (auto mg = GameObjectFactory::get()->fetch(this)) {
			mg.value()->onReset();
		}

		GameObject::resetObject();
	}

	gd::string getSaveString() {
		std::string dat(GameObject::getSaveString());

		if (auto mg = GameObjectFactory::get()->fetch(this)) {
			for (auto [k, v] : mg.value()->onExport()) {
			    dat += "," + std::to_string(k+1000) + "," + v;
			}
		}

		return gd::string(dat);
	}

	#define PKINT 1
	#define PKFLOAT 10
	#define PARSE_KEY_PKINT(keyN, member) \
		case keyN: {\
			member = std::atoi(parsed); \
			break; \
		}
	#define PARSE_KEY_PKFLOAT(keyN, member) \
		case keyN: {\
			member = std::stof(std::string(parsed)); \
			break; \
		}
	#define PARSE_KEY(keyN, member, vType) PARSE_KEY_##vType(keyN, member)

	static GameObject* objectFromString(gd::string a, bool b) {
		auto object = GameObject::objectFromString(a, b);
		if (!object) return object;

		if (auto mg = GameObjectFactory::get()->fetch(object)) {
			std::map<uint32_t, std::string> m;
			std::string tmp;
			std::string tmp2;
			bool even = false;

			std::stringstream items;
			items << std::string(a);
			while (std::getline(items, tmp, ',')) {
			    if (!even)
			        tmp2 = std::move(tmp);
			    else {
			        int key = stoi(tmp2);
			        if (key > 1000) {
			            m[key-1000] = tmp;
			        }
			    }
			    even = !even;
			}

			mg.value()->onImport(m);
		}

		return object;
	}

	void addGlow() {
		if (auto mg = GameObjectFactory::get()->fetch(this)) {
			if (!mg.value()->isGlowEnabled())
				return;
		}

		GameObject::addGlow();
	}

	void customSetup() {
		GameObject::customSetup();
		if (auto mg = GameObjectFactory::get()->fetch(this)) {
			mg.value()->setup();
		}
	}
};

namespace StandardBaseGame {
	CCDictionaryExt<int, CCNode> m_effectLayerMap;
}

class $modify(GJBaseGameLayer) {
	CCNode* parentForZLayer(int zLayer, bool detailChannel, int batchLayer) {
		auto elm = StandardBaseGame::m_effectLayerMap;

		if (batchLayer == -2) { // -2 is the effect layer
		    if (elm.size() == 0) {
		    	for (int b : {-3, -1, 1, 3, 5, 7, 9, 11}) {
		    		auto node = CCNode::create();
		    		elm[b] = node;

		    		m_objectLayer->addChild(node, b);
		    	}
		    }
		    return elm[zLayer];
		} else {
		    return GJBaseGameLayer::parentForZLayer(zLayer, detailChannel, batchLayer);
		}
	}
	bool init() {
		StandardBaseGame::m_effectLayerMap = CCDictionary::create();

		return GJBaseGameLayer::init();
	}
};

class $modify(CCSprite) {
	void setDisplayFrame(cocos2d::CCSpriteFrame* f) {
		if (f == nullptr) {
			return;
		}

		CCSprite::setDisplayFrame(f);
	}
};