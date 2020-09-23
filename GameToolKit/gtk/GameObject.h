#pragma once

#include "gtkMath.hpp"
#include <vector>
#include "Component.h"
#include "ComponentList.h"

namespace gtk {

	class GameObject
	{
	public:

		GameObject(const mat4& transform, const ComponentList& componenets)
			:m_Transform(transform), m_Componenets(componenets)
		{
		}

		GameObject(const ComponentList& componenets)
			:m_Transform(), m_Componenets(componenets)
		{
		}

		void Update()
		{
			// Update the components
		}

		void SetTransform(const mat4& transform);
		
		void SetPosition(const float& x, const float& y, const float& z);
		void SetRotation(const float& x, const float& y, const float& z);
		void SetScale(const float& x, const float& y, const float& z);

	private:

		mat4 m_Transform;
		
		// Maybe make my own container that allocates and deallocates for me
		ComponentList m_Componenets;

	};

}