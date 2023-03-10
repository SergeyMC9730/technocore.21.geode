#include "techno.h"
#include "GameObjectFactory.hpp"
#include "hooks.h"
#include <string>
#include <cstdlib>

template <typename T>
std::string to_string(T value)
{
    LOGI("doing std::string thing 13\n");
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

int stoi(std::string s) {
    LOGI("doing std::string thing 14\n");
}

namespace Camila {
	namespace CGameObject {
        // that was very painfully to port

        GameObject *(*_createWithKey)(GameObject *go, int object_id);
        void (*_triggerObject)(GameObject *go, GJBaseGameLayer *gl);
        void (*_resetObject)(GameObject *go);
        std::string (*_getSaveString)(GameObject *go);
        GameObject *(*_objectFromString)(GameObject *go, std::string a, bool b);
        void (*_addGlow)(GameObject *go);
        void (*_customSetup)(GameObject *go);

        GameObject* createWithKey(GameObject *go, int object_id) {
            auto ctr = GameObjectFactory::get();

            if (auto generator = ctr->fetchGenerator(object_id)) {
                auto obj = _createWithKey(go, object_id);
                if (!obj) {
                    obj = GameObject::createWithFrame(ctr->fetchTexture(object_id).c_str());
                }
                ctr->addContainer(obj->m_uniqueID, generator.value()(obj));

                return obj;
            } else {
                return _createWithKey(go, object_id);
            }
        }
        void triggerObject(GameObject *goo, GJBaseGameLayer *gle) {
            if (auto mg = GameObjectFactory::get()->fetch(goo)) {
			    mg.value()->onTrigger(gle);
            } else {
                _triggerObject(goo, gle);
            }
        }
        void resetObject(GameObject *go) {
            if (auto mg = GameObjectFactory::get()->fetch(go)) {
                mg.value()->onReset();
            }

            _resetObject(go);
        }
        std::string getSaveString(GameObject *go) {
            LOGI("doing std::string thing 15\n");
            std::string dat(_getSaveString(go));

            if (auto mg = GameObjectFactory::get()->fetch(go)) {
                int i = 0;

                for (auto d : mg.value()->onExport()) {
                    LOGI("doing std::string thing 16\n");
                    dat += "," + to_string(d.first+1000) + "," + d.second;
                }
            }

            return dat;
        }
        GameObject *objectFromString(GameObject *go, std::string a, bool b) {
            auto object = _objectFromString(go, a, b);
            if (!object) return object;

            if (auto mg = GameObjectFactory::get()->fetch(object)) {
                LOGI("doing std::string thing 17\n");
                std::map<uint32_t, std::string> m;
                LOGI("doing std::string thing 18\n");
                std::string tmp;
                LOGI("doing std::string thing 19\n");
                std::string tmp2;
                bool even = false;

                std::stringstream items;
                LOGI("doing std::string thing 20\n");
                items << std::string(a);
                while (std::getline(items, tmp, ',')) {
                    if (!even)
                        tmp2 = std::move(tmp);
                    else {
                        int key = std::atoi(tmp2.c_str());
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
        void addGlow(GameObject *go) {
            if (auto mg = GameObjectFactory::get()->fetch(go)) {
                if (!mg.value()->isGlowEnabled())
                    return;
            }

            _addGlow(go);
        }

        void customSetup(GameObject *go) {
            _customSetup(go);
            if (auto mg = GameObjectFactory::get()->fetch(go)) {
                mg.value()->setup();
            }
        }
    }
    void CGameObject::applyHooks() {
        HOOK_FUNCX("_ZN10GameObject13createWithKeyEi", createWithKey, _createWithKey);
        HOOK_FUNCX("_ZN10GameObject13triggerObjectEP15GJBaseGameLayer", triggerObject, _triggerObject);
        HOOK_FUNCX("_ZN10GameObject11resetObjectEv", resetObject, _resetObject);
        HOOK_FUNCX("_ZN10GameObject13getSaveStringEv", getSaveString, _getSaveString);
        HOOK_FUNCX("_ZN10GameObject16objectFromStringESsb", objectFromString, _objectFromString);
        HOOK_FUNCX("_ZN10GameObject7addGlowEv", addGlow, _addGlow);
        HOOK_FUNCX("_ZN10GameObject11customSetupEv", customSetup, _customSetup);
    }
	void CGJBaseGameLayer::applyHooks() {
		//HOOK_FUNCX("_ZN15GJBaseGameLayer15parentForZLayerEibi", parentForZLayer, _parentForZLayer);
	}
}