#include "Game.h"

namespace gtk {


	Game::~Game()
	{
		Shutdown();
	}

	void Game::Start()
	{
		// Start the active scene
		m_ActiveScene->Init();
	}

	void Game::Update(float deltaTime)
	{
		// Update the active scene
		m_ActiveScene->Update(deltaTime);
	}

	void Game::Render()
	{
		m_ActiveScene->Render();
	}

	void Game::Shutdown()
	{
		// Interate over the scene map
		for (auto& scene : m_SceneMap) 
		{
			// Delete each scene
			delete scene.second;
		}
	}

	void Game::SwitchScene(std::string key)
	{
		// Shutdown active scene
		m_ActiveScene->Shutdown();

		// Set new active scene
		m_ActiveScene = m_SceneMap.at(key);

		// Start new scene
		m_ActiveScene->Init();
	}

	void Game::AddScene(const std::string& key, Scene* newScene)
	{
		// Give the new scene a pointer to this game
		//newScene->m_Game = this;

		// If this is the first scene
		if (m_SceneMap.empty())
		{
			// Set new scene as active scene
			m_ActiveScene = newScene;
		}

		// Add scene to map
		m_SceneMap.insert({ key, newScene });
	}

}