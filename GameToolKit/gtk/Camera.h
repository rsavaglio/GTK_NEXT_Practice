#pragma once

#include "Component.h"
#include "gtkMath.hpp"

namespace gtk {

	class Camera
	{
	public:

		Camera() : m_View(1), m_Proj(1) {}

		mat4 m_View;
		mat4 m_Proj;
		

	private:

	};
}

