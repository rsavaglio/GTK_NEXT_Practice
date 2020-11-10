#pragma once

#include "Scene.h"

#include <unordered_map>
#include <string>

namespace gtk {

	class Scene;

	class Game {

	public:

		// Deletes all scenes in the scene map
		virtual ~Game();

		// Starts the active scene
		void Start();

		// Updates the active scene
		void Update(float deltaTime);

		// Calls Draw on active scene's renderers
		void Render();

		// Deletes all scenes
		void Shutdown();
		
		// Shutdown active, change active, start active
		void SwitchScene(std::string key);


	protected:

		// Override in custom game class
		virtual void Init() = 0;

		// Adds a new scene to the scene map
		void AddScene(const std::string& key, Scene* newScene);

	protected:

		// Scenes
		Scene* m_ActiveScene;
		std::unordered_map<std::string, Scene*> m_SceneMap;

	};

}