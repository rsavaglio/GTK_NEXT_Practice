#pragma once

#include "gtk.h"
#include "Camera.h"
#include "Entity.h"

#include <vector>

namespace gtk {


	//////////////////////////////////////////
	//				Components				//		
	//////////////////////////////////////////
	class Camera;

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

		Component(Entity* const entity, const CompGroup& compGroup) 
			: m_Entity(entity), m_GroupID(compGroup._id), m_Active(true) {}
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

	//////////////////////////////////////////
	//				Renderers				//		
	//////////////////////////////////////////

	class RenderLayer
	{
		friend class Scene;

	public:
		const unsigned int _id;

	protected:



	private:

		RenderLayer(const unsigned int& id) : _id(id) {}
	};

	class Renderer
	{
		friend class Scene;

	public:

		Renderer(Entity* const entity, Camera* const camera,  const RenderLayer& renderLayer)
			: m_Entity(entity), m_Camera(camera), m_LayerID(renderLayer._id), m_Active(true) {}
		virtual ~Renderer() {}

	protected:

		virtual void Start() = 0;
		virtual void Draw() = 0;

	protected:
		Entity* const m_Entity;
		Camera* const m_Camera;
		const unsigned int m_LayerID;

	private:
		bool m_Active;

	};


	class Camera : public Component
	{
		friend class Scene;

	public:
		Camera(Entity* const entity, const CompGroup& compGroup, float near, float far)
			: Component(entity, compGroup), m_id(entity->_id),
			m_View(1), m_Proj(1), n(near), f(far) {}

		virtual ~Camera() {}

		virtual void Start() = 0;
		virtual void Update(float deltaTime) = 0;


		// View and Projection
		mat4 GetView()
		{
			return m_View;
		}
		mat4 GetProj()
		{
			return m_Proj;
		}

	protected:

		void CalculateView()
		{

			// Translate
			gtk::mat4 T = { 1.0f, 0.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 1.0f, 0.0f,
							-m_Entity->GetPos().x, -m_Entity->GetPos().y, m_Entity->GetPos().z, 1.0f };


			// Rotate
			float rx = m_Entity->GetRot().x * (3.14159265359f / 180.0f);
			float ry = m_Entity->GetRot().y * (3.14159265359f / 180.0f);
			float rz = m_Entity->GetRot().z * (3.14159265359f / 180.0f);


			gtk::mat4 R = { cosf(ry) * cosf(rz),
							 sinf(rx) * sinf(ry) * cosf(rz) + cosf(rx) * sinf(rz),
							-cosf(rx) * sinf(ry) * cosf(rz) + sinf(rx) * sinf(rz),
							 0.0f,
							-cosf(ry) * sinf(rz),
							-sinf(rx) * sinf(ry) * sinf(rz) + cosf(rx) * cosf(rz),
							 cosf(rx) * sinf(ry) * sinf(rz) + sinf(rx) * cosf(rz),
							 0.0f,
							 sinf(ry),
							-sinf(rx) * cosf(ry),
							 cosf(rx) * cosf(ry),
							 0.0f,
							 0.0f, 0.0f, 0.0f, 1.0f };


			m_View = R * T;

		}
		virtual void CalculateProj(float width, float height) = 0;

	protected:

		unsigned int m_id;
		mat4 m_View;
		mat4 m_Proj;

		float n;
		float f;

	};

	class PerspectiveCam : public Camera
	{

	public:

		PerspectiveCam(Entity* const entity, const CompGroup& compGroup, float near, float far, float fov)
			: Camera(entity, compGroup, near, far), m_fov(fov) {}


		void SetFOV(float fov)
		{
			m_fov = fov;
		}

		void Start() override
		{

		}

		void Update(float deltaTime) override
		{

		}

	protected:

		void CalculateProj(float width, float height) override
		{
			float a = width / height;
			float d = 1 / (tan((m_fov * (3.14159265359f / 180.0f)) / 2));


			m_Proj =
			{
				d / a, 0, 0, 0,
				0, d, 0, 0,
				0, 0, (n + f) / (n - f), -1,
				0,0,(2 * n * f) / (n - f),0
			};
		}

	private:

		float m_fov;

	};

	class OrthoCam : public Camera
	{

	public:

		OrthoCam(Entity* const entity, const CompGroup& compGroup, float near, float far)
			: Camera(entity, compGroup, near, far) {}

		void Start() override
		{

		}

		void Update(float deltaTime) override
		{

		}


		void CalculateProj(float width, float height) override
		{
			m_Proj =
			{
				2 / (width - 0), 0, 0, -((width + 0) / (width - 0)),
				0, 2 / (height - 0), 0, -((height + 0) / (height - 0)),
				0, 0, -(2 / (f - n)), -((f + n) / (f - n)),
				0,0,0,1
			};
		}

	private:

	};

}