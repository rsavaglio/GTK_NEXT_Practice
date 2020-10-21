#pragma once

#include "Component.h"
#include "gtkMath.hpp"

namespace gtk {


	class Camera
	{
	public:

		Camera(const bool& perspective) {}

		void SetFOV() {}
		void SetDepth() {}

		// Other camera functions here

	private:

		Transform transform;

	};


	class Transform : public Component
	{
	public:

		Transform() : m_Transform() {}
		Transform(const mat4& transform) : m_Transform(transform) {}
		Transform(const vec3& position) : m_Transform() {}

		void Start() override {}
		void Update() override {}

		void SetPosition(const vec3& position) {}
		void SetRotation(const vec3& rotation) {}
		void SetScale(const vec3& scale) {}


	private:
		mat4 m_Transform;

	};
}

