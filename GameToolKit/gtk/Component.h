#pragma once

namespace gtk {

	class Component
	{
	public:

		const unsigned int _id;

		Component(const Entity& entity) : _id(entity._id) {}
		
		virtual ~Component() {}

		virtual void Start() {}
		virtual void Update() {

		}

	};
}