#pragma once

namespace gtk {

	class Component
	{
	public:

		// Left off here

		const Entity& _Entity;
		const Scene& _Scene;

		Component(const Entity& entity, const Scene& scene) : _Entity(entity), _Scene(scene) {}
		virtual ~Component() {}

		virtual void Start() {}
		virtual void Update() {}

	};

}