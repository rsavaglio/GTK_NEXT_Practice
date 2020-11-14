#include "Component.h"

namespace gtk {

	
	//// Scene Object

	SceneObject::SceneObject() : _id(0), _scene(nullptr) {}

	const unsigned int& SceneObject::ID() const
	{
		return _id;
	}

	inline void SceneObject::Init(const unsigned int& id, Scene* scene)
	{
		_id = id;
		_scene = scene;
	}

	Scene& SceneObject::GetScene()
	{
		return *_scene;
	}



	//// Component


	const bool& Component::Active(const bool& setActive) 
	{
		GetScene().ToggleComponent(*this, setActive);

		return setActive;
	}

	const bool& Component::Active()
	{
		return m_Active;
	}


	//// Renderer

	const bool& Renderer::Active(const bool& setActive)
	{
		GetScene().ToggleRenderer(*this, setActive);

		return setActive;
	}

	const bool& Renderer::Active()
	{
		return m_Active;
	}


	//// Camera


}