#include "GameObjectFactory.hpp"

GameObjectFactory* GameObjectFactory::get() {
	static GameObjectFactory* shared;
	if (!shared) {
		shared = new GameObjectFactory;
	}

	return shared;
}

tl::optional<GameObjectFactory::generator_t> GameObjectFactory::fetchGenerator(unsigned int object_id) {
	if (m_generators.count(object_id) > 0) {
		return m_generators[object_id];
	} else {
		return nullptr;
	}
}
std::string const& GameObjectFactory::fetchTexture(unsigned int object_id) {
	LOGI("doing std::string thing 12\n");
	return m_textures[object_id];
}

tl::optional<GameObjectFactory::container_t> GameObjectFactory::fetch(unsigned int uuid) {
	if (m_containers.count(uuid) > 0) {
		return m_containers[uuid];
	} else {
		return {};
	}
}

tl::optional<GameObjectFactory::container_t> GameObjectFactory::fetch(GameObject* obj) {
	return fetch(obj->m_uniqueID);
}

void GameObjectFactory::addContainer(unsigned int uuid, GameObjectFactory::container_t container) {
	m_containers[uuid] = container;
}

void GameObjectFactory::add(unsigned int object_id, GameObjectFactory::generator_t gen) {
	m_generators[object_id] = gen;
}

void GameObjectFactory::add(unsigned int object_id, std::string txt, GameObjectFactory::generator_t gen) {
	LOGI("doing std::string thing 13\n");
	m_textures[object_id] = txt;
	m_generators[object_id] = gen;
}

