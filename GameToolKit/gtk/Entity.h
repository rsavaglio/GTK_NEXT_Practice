#pragma once

#include "Scene.h"
#include "Component.h"

namespace gtk {

	struct Entity {

		const unsigned int _id;
		const Scene& _Scene;
		bool _Active;


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

		Entity(const Scene& scene) : _id(_idProvider), _Scene(scene), _Active(true)
		{
			_idProvider++;
		}

		static unsigned int _idProvider;

	};
}