#pragma once

#include "gtkMath.hpp"
#include <vector>
#include <math.h>

namespace gtk {
	
	class Entity
	{
		friend class Scene;

	public:

		const unsigned int _id;

		Entity* const _Parent;

		mat4 GetWorldTranform()
		{
			return _TRS;
		}

		void SetPos(const float& x, const float& y, const float& z);
		void SetPos(const vec3& pos);
		void SetPos(const vec4& rot);
		void SetPosX(float x);
		void SetPosY(float y);
		void SetPosZ(float z);
		const vec4& GetPos();

		void SetRot(const float& x, const float& y, const float& z);
		void SetRot(const vec3& rot);
		void SetRot(const vec4& rot);
		void SetRotX(float x);
		void SetRotY(float y);
		void SetRotZ(float z);
		const vec4& GetRot();

		void SetScale(const float& x, const float& y, const float& z);
		void SetScale(const vec3& scale);
		void SetScale(const vec4& scale);
		void SetScaleX(float x);
		void SetScaleY(float y);
		void SetScaleZ(float z);
		const vec4& GetScale();

	private:

		// Call CreateEntity() from a Scene
		Entity(const unsigned int& id, Entity* const parent);

		void UpdateTRS();
		void Soil();

		bool _Active;

		std::vector<Entity*> _Children;

		void AddChild(Entity* const child)
		{
			_Children.push_back(child);
		}

		// Dirty Flag
		bool _Dirty;

		// Tranform Data
		vec4 _Pos;
		vec4 _Rot;
		vec4 _Scale;

		mat4 _TRS;

	};



}

