#pragma once

#include "gtkMath.hpp"
#include "Scene.h"

#include <vector>
#include <string>

namespace gtk {

	//////////////////////////////////////////
	//				SceneObject				//		
	//////////////////////////////////////////

	// Base class for anything mananged by the scene
	// Provides handy functions

	class Entity;
	class Scene;

	class SceneObject
	{
		friend class Scene;

	public:

		SceneObject();
		virtual ~SceneObject() {}

		const vec3& Pos();
		const vec3& Pos(const vec3& pos);
		const vec3& Pos(const vec3& pos, const bool& add);

		const vec3& Rot();
		const vec3& Rot(const vec3& pos);
		const vec3& Rot(const vec3& pos, const bool& add);

		const vec3& Scale();
		const vec3& Scale(const vec3& pos);
		const vec3& Scale(const vec3& pos, const bool& add);

		const bool& Active(const bool& setActive);
		const bool& Active();

		Entity& Parent();
		const mat4& TRS();

		void SwitchScene(std::string name);

		// TODO
		const vec3& Forward() {}
		void Instantiate() {}


	protected:
		
		virtual inline void Init(Scene* scene, Entity* ent);

		Scene& GetScene();
		Entity& GetEntity();

		bool _Active;

	private:

		Scene* _scene;
		Entity* _ent;

	};

	//////////////////////////////////////////
	//				Behaviors				//		
	//////////////////////////////////////////

	class Behavior : public SceneObject
	{
		friend class Scene;

	public:

		Behavior() {}
		virtual ~Behavior() {}



		virtual int Trigger(const int& code) = 0;

	protected:

		virtual void Start() = 0;
		virtual void Update(const float& deltaTime) = 0;

	private:
	};


	//////////////////////////////////////////
	//				Cameras  				//		
	//////////////////////////////////////////

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

	class Renderer : public SceneObject
	{
		friend class Scene;

	public:

		Renderer()
			: m_LayerID(), m_Camera(nullptr), m_Active(true) {}
		virtual ~Renderer() {}

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

	//////////////////////////////////////////
	//				Entities				//		
	//////////////////////////////////////////
	
	class Entity : public SceneObject
	{
		friend class Scene;
		friend class SceneObject;

	public:

		const mat4& GetTRS();

	private:

		// Call CreateEntity() from a Scene
		Entity(Entity* parent, Scene& scene);
		void AddChild(Entity* child);

		void UpdateRootTRS();
		void UpdateTRS();
		void Soil();

		mat4 CalcTRS();

	private:

		Entity* _Parent;
		Scene& _Scene;

		std::vector<Entity*> _Children;


		bool _Dirty;  // Update transform

		vec3 _Pos;
		vec3 _Rot;
		vec3 _Scale;
		mat4 _TRS;

	};




}