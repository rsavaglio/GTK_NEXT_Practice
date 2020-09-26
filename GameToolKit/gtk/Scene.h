#pragma once

#include "Entity.h"
#include "Component.h"

#include <vector>
#include <unordered_map>


namespace gtk {

	struct Scene {

		~Scene() 
		{
			// delete entities

			// delete all componenets
		}

		void Update()
		{
			// Traverse ComponenetSets and call update in each component

		}


		int CreateEntity()
		{
			Entity* newEntity = new Entity(*this);
			m_EntityList.push_back(newEntity);

			return newEntity->_id;
		}

		std::vector<Entity*> m_EntityList;
		std::vector<std::unordered_map<unsigned int, Component>> m_ComponenetMaps;
	};
}