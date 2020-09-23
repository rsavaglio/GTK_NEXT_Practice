#pragma once

namespace gtk {

	class Component
	{
	public:
		virtual ~Component() {}
		virtual void Update() = 0;
	};

}