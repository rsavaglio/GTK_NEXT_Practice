#pragma once

namespace gtk {

	class Component
	{
	public:

		const unsigned int _id;

		Component(const int& id) : _id(id) {}
		
		virtual ~Component() {}

		virtual void Start() {}
		virtual void Update() {

		}

	};
}