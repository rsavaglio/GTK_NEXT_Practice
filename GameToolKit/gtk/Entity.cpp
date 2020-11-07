#include "Entity.h"

namespace gtk {

	Entity::Entity(const unsigned int& id, Entity* const parent)
		: _id(id), _Parent(parent), _Active(true), _Children(),
		_Dirty(true), _Pos(), _Rot(), _Scale(1.0f), _TRS(1) {}

	void Entity::SetPos(const float& x, const float& y, const float& z)
	{
		_Pos = vec3(x, y, z);
		_Dirty = true;
	}

	void Entity::SetPos(const vec3& pos)
	{
		_Pos = pos;
		_Dirty = true;
	}

	void Entity::SetPosX(float x)
	{
		_Pos.x = x;
		_Dirty = true;
	}
	void Entity::SetPosY(float y)
	{
		_Pos.y = y;
		_Dirty = true;
	}
	void Entity::SetPosZ(float z)
	{
		_Pos.z = z;
		_Dirty = true;
	}

	const vec3& Entity::GetPos()
	{
		return _Pos;
	}

	void Entity::SetRot(const float& x, const float& y, const float& z)
	{
		_Rot = vec3(x, y, z);
		_Dirty = true;
	}


	void Entity::SetRot(const vec3& Rot)
	{
		_Rot = Rot;
		_Dirty = true;
	}

	void Entity::SetRotX(float x)
	{
		_Rot.x = x;
		_Dirty = true;
	}
	void Entity::SetRotY(float y)
	{
		_Rot.y = y;
		_Dirty = true;
	}
	void Entity::SetRotZ(float z)
	{
		_Rot.z = z;
		_Dirty = true;
	}

	const vec3& Entity::GetRot()
	{
		return _Rot;
	}

	void Entity::SetScale(const float& x, const float& y, const float& z)
	{
		_Scale = vec3(x, y, z);
		_Dirty = true;
	}

	void Entity::SetScale(const vec3& scale)
	{
		_Scale = scale;
		_Dirty = true;
	}

	void Entity::SetScaleX(float x)
	{
		_Scale.x = x;
		_Dirty = true;
	}
	void Entity::SetScaleY(float y)
	{
		_Scale.y = y;
		_Dirty = true;
	}
	void Entity::SetScaleZ(float z)
	{
		_Scale.z = z;
		_Dirty = true;
	}

	const vec3& Entity::GetScale()
	{
		return _Scale;
	}


}