#pragma once

#include "gtk.h"
#include "Camera.h"
#include "Entity.h"

#include <vector>

namespace gtk {

	class CompGroup
	{
		friend class Scene;

	public:
		const unsigned int _id;

	private:

		CompGroup(const unsigned int& id) : _id(id) {}
	};

	class Component
	{
		friend class Scene;

	public:

		Component(Entity* const entity, const CompGroup& compGroup) : m_Entity(entity), m_GroupID(compGroup._id), m_Active(true) {}
		virtual ~Component() {}

	protected:

		virtual void Start() = 0;
		virtual void Update(float deltaTime) = 0;

	protected:
		
		Entity* const m_Entity;
		const unsigned int m_GroupID;

	private:

		bool m_Active;

	};

	class Renderer
	{
		friend class Scene;

	public:

		Renderer(Entity* const entity) : m_Entity(entity), m_Active(true) {}
		virtual ~Renderer() {}

	protected:

		virtual void Start() = 0;
		virtual void Draw() = 0;

	protected:
		Entity* const m_Entity;

	private:
		bool m_Active;

	};


}