#pragma once

#include "Scene.h"
#include "Component.h"

namespace gtk {

	struct Entity {

		friend class Scene; // only a scene can create entities

		static unsigned int _idProvider;

		const unsigned int _id;
		Scene& _Scene;


		void AddComponenet(const Component& componenet)
		{

			// If componentmap type exists

				// Make sure this entity doesn't already have this type on it

				// Add it to the map
				

			// if no map exists
				
				// Create a new map

				// Add to list
		}


	private:
		
		Entity(Scene& scene) : _id(_idProvider), _Scene(scene)
		{
			_idProvider++;

			_Scene.m_EntityList.push_back(this);
		}

	};
}