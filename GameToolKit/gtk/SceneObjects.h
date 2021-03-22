#pragma once

#include "gtkMath.hpp"
#include "Scene.h"

#include <vector>
#include <string>
#include <queue>

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

		const std::string& GetName();

		const vec3& Pos();
		const vec3& Pos(const vec3& pos);
		const vec3& Pos(const vec3& pos, const bool& add);

		const vec3& Rot();
		const vec3& Rot(const vec3& pos);
		const vec3& Rot(const vec3& pos, const bool& add);

		const vec3& Scale();
		const vec3& Scale(const vec3& pos);
		const vec3& Scale(const vec3& pos, const bool& add);

		const unsigned int& ID() const;

		Entity& Parent();
		const mat4& TRS();
		const vec3& GlobalPos();

		vec3 Right();
		vec3 Up();
		vec3 Forward();


		const int& State();
		const int& State(const int& newState);

		void Trigger(const int& code);
		void TriggerCollision(Entity& other);
		void SetColor(const vec3& color);

		void SwitchScene(std::string name);

		// Math Helpers

		float LERP(const float& s, const float& e, const float& t);
		vec4  LERP(const vec4& s, const vec4& e, const float& t);
		vec3  LERP(const vec3& s, const vec3& e, const float& t);
		vec2  LERP(const vec2& s, const vec2& e, const float& t);

	protected:
		
		virtual inline void Init(const unsigned int& id, Scene* scene, Entity* ent);

		Scene& GetScene();
		Entity& GetEntity();

	private:

		unsigned int _id;
		Scene* _scene;
		Entity* _ent;

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

	class Behavior : public SceneObject
	{
		friend class Scene;

	public:

		Behavior() 
			: m_GroupID(0), m_Active(true) {}
		virtual ~Behavior() {}

		const bool& Active(const bool& setActive);
		const bool& Active();

		virtual int Trigger(const int& code) { return 0; };

		virtual void OnCollision(Entity& other) {};

	protected:

		virtual void Start() {};
		virtual void Update(const float& deltaTime) = 0;

	private:

		unsigned int m_GroupID;
		bool m_Active;

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

		const mat4& GetView();
		const mat4& GetProj();

	protected:

		void CalculateView();
		void CalculateView2();
		virtual void CalculateProj(const float& width, const float& height) = 0;

	protected:

		std::vector<Entity*> GetParents(Entity& ent);

		mat4 m_View;
		mat4 m_Proj;

		float n;
		float f;

	private:

	};

	class PerspectiveCam : public Camera
	{

	public:

		PerspectiveCam(const float& near, const float& far, const float& fov);


		void SetFOV(float fov);

	protected:

		void CalculateProj(const float& width, const float& height) override;

	private:

		float m_fov;

	};

	class OrthoCam : public Camera
	{

	public:

		OrthoCam(const float& near, const float& far);

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

		Renderer(vec3 color = vec3(0.5f, 0.5f, 0.2f))
			: _color(color), m_LayerID(), m_Camera(nullptr), m_Active(true) {}
		virtual ~Renderer() {}

		const bool& Active(const bool& setActive);
		const bool& Active();

	protected:

		virtual void Start() = 0;
		virtual void Draw() = 0;


		void SetCamera(const Camera& camera) {}
		
		const mat4& GetView()
		{
			return m_Camera->GetView();
		}
		const mat4& GetProj() 
		{
			return m_Camera->GetProj();
		}


	protected:

		vec3 _color;
		unsigned int m_LayerID;

	private:

		void SetColor(const vec3 color)
		{
			_color = color;
		}
		vec3 GetColor()
		{
			return _color;
		}

		Camera* m_Camera;
		bool m_Active;

	};

	//////////////////////////////////////////
	//				Entities				//		
	//////////////////////////////////////////
	
	class Entity : public SceneObject
	{
		friend class Scene;
		friend class SceneObject;
		friend class Camera;

	public:

		const mat4& GetTRS();

		const bool& Active(const bool& setActive);
		const bool& Active();
	
	private:

		// Call CreateEntity() from a Scene
		Entity();
		Entity(const Entity&) = delete;

		void AddChild(Entity* child);

		mat4 CalcTRS();
		mat4 CalcTR();

		void UpdateRootTRS();
		void UpdateTRS();

	private:

		std::string _Name;

		Entity* _Parent;

		std::vector<Entity*> _Children;

		bool _Active; // Update comps and draw

		vec3 _Pos;
		vec3 _Rot;
		vec3 _Scale;
		
		vec3 _right;
		vec3 _up;
		vec3 _forward;

		vec3 _globalPos;
		
		mat4 _TRS;

	};




	/////// Object Pools //////////


	class ObjectPool
	{
	public:

		virtual ~ObjectPool() {}

		virtual void GeneratePool() = 0;


		virtual Entity& Create(const vec3& vec = vec3())
		{
			Entity* ent = _pool.front();
			_pool.pop();
			_pool.push(ent);

			ent->Active(true);

			return *ent;
		}

	protected:
		std::queue<Entity*> _pool;

		int _count;
		Scene& _scene;
		
		ObjectPool(const int& count, Scene& scene) : _pool(), _count(count), _scene(scene) {}
		ObjectPool(const ObjectPool&) = delete;
	};



	/////////////////////////////////////
	///			Colliders
	/////////////////////////////////////

	class CollisionGroup
	{
		friend class Scene;

	public:
		const unsigned int _id;

	private:

		CollisionGroup(const unsigned int& id) : _id(id) {}
	};

	class Collider : public SceneObject
	{
		friend class Scene;
		friend class Collider;

	public:

		Collider()
			: _center(), _radius(1.0f), m_GroupID(0), m_Active(true) {}
		virtual ~Collider() {}

		const bool& Active(const bool& setActive);
		const bool& Active();

		vec3 _center;
		float _radius;

	protected:

		virtual void UpdateData() = 0;
		virtual bool Check(Collider& other) = 0;


	
	private:

		unsigned int m_GroupID;
		bool m_Active;

	};

}