#pragma once

#include "gtk.h"

#include <unordered_map>
#include <string>

namespace gtk {

	class Scene;

	class Game {

	public:

		// Deletes all scenes in the scene map
		virtual ~Game();

		// Override in custom game class
		virtual void Init() = 0;

		// Starts the active scene
		void Start();

		// Updates the active scene
		void Update(); 
		
		// Shutdown active, change active, start active
		void SwitchScene(const std::string& key);


	protected:

		// Adds a new scene to the scene map
		void AddScene(const std::string& key, Scene* newScene);

	private:

		Scene* m_ActiveScene;
		std::unordered_map<std::string, Scene*> m_SceneMap;

	};

}