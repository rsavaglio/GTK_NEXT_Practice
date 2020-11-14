#pragma once

#include "gtkMath.hpp"
#include "Entity.h"
#include "Scene.h"

#include <vector>

namespace gtk {

	class SceneObject
	{
		friend class Scene;

	public:

		SceneObject();
		virtual ~SceneObject() {}

		const vec3& Pos() { return vec3(0); }
		const vec3& Rot() { return vec3(0); }
		const vec3& Scale() { return vec3(0); }

		const vec3& Forward() { return vec3(0); }

		const unsigned int& ID() const;

	protected:
		
		virtual inline void Init(const unsigned int& id, Scene* scene);

		Scene& GetScene();

	private:

		unsigned int _id;
		Scene* _scene;
	
		inline void SetPos() {}
		inline void SetRot() {}
		inline void SetScale() {}

		inline void SetForward() {}
	
	};

	//////////////////////////////////////////
	//				Components				//		
	//////////////////////////////////////////


	class CompGroup
	{
		friend class Scene;

	public:
		const unsigned int _id;

	private:

		CompGroup(const unsigned int& id) : _id(id) {}
	};

	class Component : public SceneObject
	{
		friend class Scene;

	public:

		Component() 
			: m_GroupID(0), m_Active(true) {}
		virtual ~Component() {}

		const bool& Active(const bool& setActive);
		const bool& Active();


		virtual int Trigger(const int& code) = 0;

	protected:

		virtual void Start() = 0;
		virtual void Update(const float& deltaTime) = 0;

	private:

		unsigned int m_GroupID;
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

	class Camera;

	class Renderer : public SceneObject
	{
		friend class Scene;

	public:

		Renderer()
			: m_LayerID(), m_Camera(nullptr), m_Active(true) {}
		virtual ~Renderer() {}

		const bool& Active(const bool& setActive);

		const bool& Active();

	protected:

		virtual void Start() = 0;
		virtual void Draw() = 0;


		void SetCamera(const Camera& camera) {}
		const mat4& GetView() {}
		const mat4& GetProj() {}


	protected:

		unsigned int m_LayerID;

	private:

		const Camera* m_Camera; // Read only
		bool m_Active;

	};


	class Camera : public SceneObject
	{
		friend class Scene;

	public:
		Camera(float near, float far)
			: m_View(1), m_Proj(1), n(near), f(far) {}

		virtual ~Camera() {}


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
							Pos().x, Pos().y, Pos().z, 1.0f };


			// Rotate
			float rx = Rot().x * (3.14159265359f / 180.0f);
			float ry = Rot().y * (3.14159265359f / 180.0f);
			float rz = Rot().z * (3.14159265359f / 180.0f);


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

		PerspectiveCam(float near, float far, float fov)
			: Camera(near, far), m_fov(fov) {}


		void SetFOV(float fov)
		{
			m_fov = fov;
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

		OrthoCam(const Entity& entity, float near, float far)
			: Camera(near, far) {}

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