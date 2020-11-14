#pragma once

#include "gtkMath.hpp"
#include "Entity.h"
#include "Scene.h"

#include <vector>

namespace gtk {

	//////////////////////////////////////////
	//				SceneObjects			//		
	//////////////////////////////////////////

	// Base class for anything that is added to Entities
	// These are the functions available when creating custom classes

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

		void Parent() {}
		void TRS() {}

		void Instantiate() {} // How could this work?

	protected:
		
		virtual inline void Init(const unsigned int& id, Scene* scene);

		Scene& GetScene();

	private:

		unsigned int _id;
		Scene* _scene;
	
	
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
		
		Camera(const float& near, const float& far);

		virtual ~Camera() {}


		// View and Projection
		mat4 GetView();
		mat4 GetProj();

	protected:

		void CalculateView();
		virtual void CalculateProj(const float& width, const float& height) = 0;

	protected:

		mat4 m_View;
		mat4 m_Proj;

		float n;
		float f;

	};

	class PerspectiveCam : public Camera
	{

	public:

		PerspectiveCam(const float& near, const float& far, const float& fov)
			: Camera(near, far), m_fov(fov) {}


		void SetFOV(float fov)
		{
			m_fov = fov;
		}

	protected:

		void CalculateProj(const float& width, const float& height) override
		{
			float a = width / height;
			float d = 1 / (tanf((m_fov * (3.14159265359f / 180.0f)) / 2));


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

		OrthoCam(const float& near, const float& far)
			: Camera(near, far) {}

		void CalculateProj(const float& width, const float& height) override
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