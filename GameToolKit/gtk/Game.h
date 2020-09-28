#pragma once

#include "Scene.h"
#include <unordered_map>

namespace gtk {

	class Game {

	public:

		Game() {}

		virtual ~Game()
		{
			// Delete all scenes
		}

		void Start()
		{
			// Starts active scene
		}

		void Update() 
		{
			// Update the active scene

		}
		
		void SwitchScene(const std::string& key) 
		{
			// Shutdown active scene

			// Active scene = next scene

			// Start new scene
			
		}

	protected:

		virtual void SetupScenes()
		{
			// To be overriden

			// This is where you create scenes and add them to the game
		}

		void AddScene(const std::string& key)
		{
			// Add scene to map

			// if first scene added, set as the active scene

		}

	private:

		Scene* m_ActiveScene;
		std::unordered_map<std::string, Scene*> m_SceneMap;

	};

}