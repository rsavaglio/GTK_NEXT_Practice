#pragma once

#include "gtkMath.hpp"
#include "Scene.h"

#include <vector>

namespace gtk {

	//////////////////////////////////////////
	//				Components				//		
	//////////////////////////////////////////

	// Base class for anything that is added to Entities

	class Component
	{
		friend class Scene;

	public:

		Component();
		virtual ~Component() {}

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
	//				Behaviors				//		
	//////////////////////////////////////////


	class UpdateGroup
	{
		friend class Scene;

	public:
		const unsigned int _id;

	private:

		UpdateGroup(const unsigned int& id) : _id(id) {}
	};

	class Behavior : public Component
	{
		friend class Scene;

	public:

		Behavior() 
			: m_GroupID(0), m_Active(true) {}
		virtual ~Behavior() {}

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
	//				Cameras  				//		
	//////////////////////////////////////////

	class Camera : public Component
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


		void SetFOV(float fov);

	protected:

		void CalculateProj(const float& width, const float& height) override;

	private:

		float m_fov;

	};

	class OrthoCam : public Camera
	{

	public:

		OrthoCam(const float& near, const float& far)
			: Camera(near, far) {}

		void CalculateProj(const float& width, const float& height) override;

	private:

	};


	//////////////////////////////////////////
	//				Renderers				//		
	//////////////////////////////////////////

	class RenderLayer
	{
		friend class Scene;

	public:
		const unsigned int _id;

	private:

		RenderLayer(const unsigned int& id) : _id(id) {}
	};

	class Renderer : public Component
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

}