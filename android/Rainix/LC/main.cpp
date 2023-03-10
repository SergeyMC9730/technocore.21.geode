#include "includes.h"
#include <fstream>
#include "main.h"
#include "cJSON.h"
#include "Logger.h"
using namespace std;

#define MEMBERBYOFFSET(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)
#define MBO MEMBERBYOFFSET

void addHexSymbol(int value, std::string& str) {
	switch (value) {
	case 0:
		str = str + "0";
		break;
	case 1:
		str = str + "1";
		break;
	case 2:
		str = str + "2";
		break;
	case 3:
		str = str + "3";
		break;
	case 4:
		str = str + "4";
		break;
	case 5:
		str = str + "5";
		break;
	case 6:
		str = str + "6";
		break;
	case 7:
		str = str + "7";
		break;
	case 8:
		str = str + "8";
		break;
	case 9:
		str = str + "9";
		break;
	case 10:
		str = str + "A";
		break;
	case 11:
		str = str + "B";
		break;
	case 12:
		str = str + "C";
		break;
	case 13:
		str = str + "D";
		break;
	case 14:
		str = str + "E";
		break;
	case 15:
		str = str + "F";
		break;
	}
}

std::string getHex(int value) {
	std::string hex = "";
	int secondValue = value / 16;

	int firstByte = value % 16;
	int secondByte = secondValue % 16;
	addHexSymbol(secondByte, hex);
	addHexSymbol(firstByte, hex);
	return hex;
}


struct {
	uint8_t levelCount;
	bool deleteDemonLocks;

	std::array<std::string, 126> names;
	std::array<int, 126> difficulty;
	std::array<int, 126> stars;
	std::array<std::string, 126> music;
}levelInfo;

bool ActiveHooks = 0;

bool once = 1;
unsigned char* Json;
bool noJson = 0;

bool (*MenuLayer_init)(MenuLayer*);
bool MenuLayer_initH(MenuLayer* self) {
	ActiveHooks = 0;

	if (once) {
		unsigned long n = 9999;
		char* buffer = new char[n + 1];
		buffer[n] = 0;
		auto getJson = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename("levelCustomizer.json", false);
		Json = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(getJson.c_str(), "rb", &n);
		if (reinterpret_cast<char*>(Json) != NULL) {
			LOGI("doing std::string thing 1\n");
			std::string JsonStr(reinterpret_cast<char*>(Json));
		}
	}

	if (reinterpret_cast<char*>(Json) == NULL) {
		auto errorLabel = CCLabelBMFont::create("Problem with \"levelCustomizer.json\"", "bigFont.fnt");
		errorLabel->setColor({ 255, 0, 0 });
		errorLabel->setScale(0.6);
		errorLabel->setPosition({ CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height - 10 });
		self->addChild(errorLabel);
		return true;
	}

	if (once) {
		LOGI("doing std::string thing 2\n");
		std::string JsonStr(reinterpret_cast<char*>(Json));
		cJSON* root = cJSON_Parse(JsonStr.c_str());
		cJSON* settings = cJSON_GetObjectItemCaseSensitive(root, "settings");
		cJSON* levelCount = cJSON_GetObjectItemCaseSensitive(settings, "levelCount");
		cJSON* deleteDemonLocks = cJSON_GetObjectItemCaseSensitive(settings, "deleteDemonLocks");
		cJSON* levels = cJSON_GetObjectItemCaseSensitive(root, "levels");

		levelInfo.levelCount = levelCount->valueint;
		levelInfo.deleteDemonLocks = deleteDemonLocks->valueint;

		cJSON* lvl;
		int lvlCounter = 1;
		cJSON_ArrayForEach(lvl, levels) {
			cJSON* name = cJSON_GetObjectItemCaseSensitive(lvl, "name");
			cJSON* difficulty = cJSON_GetObjectItemCaseSensitive(lvl, "difficulty");
			cJSON* stars = cJSON_GetObjectItemCaseSensitive(lvl, "stars");
			cJSON* song = cJSON_GetObjectItemCaseSensitive(lvl, "song");

			levelInfo.names[lvlCounter] = name->valuestring;
			levelInfo.difficulty[lvlCounter] = difficulty->valueint;
			levelInfo.stars[lvlCounter] = stars->valueint;
			levelInfo.music[lvlCounter] = song->valuestring;
			lvlCounter++;
		}

		if (levelInfo.levelCount > 126)
			levelInfo.levelCount = 126;
		if (levelInfo.levelCount < 1)
			levelInfo.levelCount = 1;
		levelInfo.levelCount++;

		PatchManager tmp;
		tmp.addPatch("libcocos2dcpp.so", 0x2C0F1A, getHex(levelInfo.levelCount));

		if (levelInfo.deleteDemonLocks) {
			tmp.addPatch("libcocos2dcpp.so", 0x2C1EEE, "AF42");//lock
			tmp.addPatch("libcocos2dcpp.so", 0x2BF858, "8F42");//lock panel
		}

		tmp.Modify();

		once = 0;
	}

	return true;
}

int publicID;

class LevelPage : public CCNode {};
void (*page)(LevelPage* self, GJGameLevel* lvl);
void pageHook(LevelPage* self, GJGameLevel* lvl) {
	if (!noJson && ActiveHooks) {
		if (lvl->levelID_rand - lvl->levelID_seed != -1) {
			if (levelInfo.names[lvl->levelID_rand - lvl->levelID_seed] != "")
				lvl->levelName = levelInfo.names[lvl->levelID_rand - lvl->levelID_seed];
			else
			lvl->levelName = "Unknown";
			lvl->stars_rand = 1000;
			lvl->stars_seed = 1000 - levelInfo.stars[lvl->levelID_rand - lvl->levelID_seed];
			
			switch (levelInfo.difficulty[lvl->levelID_rand - lvl->levelID_seed]) {
			case 1:
				lvl->difficulty = kGJDifficultyEasy;
				break;
			case 2:
				lvl->difficulty = kGJDifficultyNormal;
				break;
			case 3:
				lvl->difficulty = kGJDifficultyHard;
				break;
			case 4:
				lvl->difficulty = kGJDifficultyHarder;
				break;
			case 5:
				lvl->difficulty = kGJDifficultyInsane;
				break;
			case 6:
				lvl->difficulty = kGJDifficultyDemon;
				break;
			default:
				lvl->difficulty = kGJDifficultyEasy;
				break;
			}
		}
		if (lvl->levelID_rand - lvl->levelID_seed != -1)
			publicID = lvl->levelID_rand - lvl->levelID_seed;
		else
			publicID = levelInfo.levelCount;
	}
	page(self, lvl);	
}


void (*LevelSelectLayerInit)(LevelSettingsLayer* self, int idk);
void LevelSelectLayerInitHook(LevelSettingsLayer* self, int idk) {
	ActiveHooks = 1;
	LevelSelectLayerInit(self, idk);
}

std::string (*music)(std::string self, int id);
std::string musicHook(std::string self, int id) {
	music(self, id);
	if(!noJson && ActiveHooks) {
		if(levelInfo.music[publicID - 1] != "") {
			LOGI("doing std::string thing 3\n");
			self = levelInfo.music[publicID - 1];
		} else {
			LOGI("doing std::string thing 4\n");
			self = "BackOnTrack.mp3";
		}
	}
	return self;
}


void ApplyHooks() {
	// HOOK("_ZN9MenuLayer4initEv", MenuLayer_initH, MenuLayer_init);
	HOOK("_ZN10LevelTools16getAudioFileNameEi", musicHook, music);
	HOOK("_ZN9LevelPage17updateDynamicPageEP11GJGameLevel", pageHook, page);
	HOOK("_ZN16LevelSelectLayer4initEi", LevelSelectLayerInitHook, LevelSelectLayerInit);
}

void ApplyPatches() {
	
}

void Rainix_LCLoader() {
	ApplyHooks();
	ApplyPatches();
}
