#include "Entity.h"

namespace gtk {

	Entity::Entity(const unsigned int& id, Entity* const parent, Scene* const scene)
		: _id(id), _Parent(parent), _Scene(scene), _Children(), _Active(true),
		_Dirty(true), _Pos(), _Rot(), _Scale(1.0f), _TRS(1) {}

	
	const mat4& Entity::GetWorldTranform()
	{
		return _TRS;
	}

	void Entity::SetPos(const float& x, const float& y, const float& z)
	{
		_Pos = vec4(x, y, z, 1);
		Soil();
	}

	void Entity::SetPos(const vec3& pos)
	{
		_Pos = vec4(pos.x, pos.y, pos.z, 1);
		Soil();
	}

	void Entity::SetPos(const vec4& pos)
	{
		_Pos = vec4(pos.x, pos.y, pos.z, 1);
		Soil();
	}

	void Entity::SetPosX(float x)
	{
		_Pos.x = x;
		Soil();
	}
	void Entity::SetPosY(float y)
	{
		_Pos.y = y;
		Soil();
	}
	void Entity::SetPosZ(float z)
	{
		_Pos.z = z;
		Soil();
	}

	const vec4& Entity::GetPos()
	{
		return _Pos;
	}

	void Entity::SetRot(const float& x, const float& y, const float& z)
	{
		_Rot = vec4(x, y, z, 1);
		Soil();
	}

	void Entity::SetRot(const vec3& rot)
	{
		_Rot = vec4(rot.x, rot.y, rot.z, 1);
		Soil();
	}

	void Entity::SetRot(const vec4& rot)
	{
		_Rot = vec4(rot.x, rot.y, rot.z, 1);
		Soil();
	}

	void Entity::SetRotX(float x)
	{
		_Rot.x = x;
		Soil();
	}
	void Entity::SetRotY(float y)
	{
		_Rot.y = y;
		Soil();
	}
	void Entity::SetRotZ(float z)
	{
		_Rot.z = z;
		Soil();
	}

	const vec4& Entity::GetRot()
	{
		return _Rot;
	}

	void Entity::SetScale(const float& x, const float& y, const float& z)
	{
		_Scale = vec4(x, y, z, 1);
		Soil();
	}

	void Entity::SetScale(const vec3& scale)
	{
		_Scale = vec4(scale.x, scale.y, scale.z, 1);
		Soil();
	}
	
	void Entity::SetScale(const vec4& scale)
	{
		_Scale = vec4(scale.x, scale.y, scale.z, 1);
		Soil();
	}

	void Entity::SetScaleX(float x)
	{
		_Scale.x = x;
		Soil();
	}
	void Entity::SetScaleY(float y)
	{
		_Scale.y = y;
		Soil();
	}
	void Entity::SetScaleZ(float z)
	{
		_Scale.z = z;
		Soil();
	}

	const vec4& Entity::GetScale()
	{
		return _Scale;
	}

	void Entity::UpdateTRS()
	{
		if (_Dirty)
		{
			// Translate
			gtk::mat4 T = { 1.0f, 0.0f, 0.0f, 0.0f,
			   0.0f, 1.0f, 0.0f, 0.0f,
			   0.0f, 0.0f, 1.0f, 0.0f,
				_Pos.x, _Pos.y, _Pos.z, 1.0f };

			// Rotate

			float rx = _Rot.x * (3.14159265359f / 180.0f);
			float ry = _Rot.y * (3.14159265359f / 180.0f);
			float rz = _Rot.z * (3.14159265359f / 180.0f);


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

			// Scale
			gtk::mat4 S = { _Scale.x, 0.0f, 0.0f, 0.0f,
							0.0f, _Scale.y, 0.0f, 0.0f,
							0.0f, 0.0f, _Scale.z, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f };

			_TRS = _Parent->_TRS * T * R * S;

			_Dirty = false;

		}
		
		// Update Children's TRS
		for (auto& child : _Children)
		{
			child->UpdateTRS();
		}
	}

	void Entity::Soil()
	{
		_Dirty = true;

		for (auto& child : _Children)
		{
			child->Soil();
		}
	}

	void Entity::AddChild(Entity* const child)
	{
		_Children.push_back(child);
	}

}