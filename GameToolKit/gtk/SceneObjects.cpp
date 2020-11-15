#include "SceneObjects.h"

namespace gtk {

	
	//// Component

	SceneObject::SceneObject() : _id(0), _scene(nullptr), _ent(nullptr) {}

	const vec3& SceneObject::Pos()
	{
		return _ent->_Pos;
	}

	const vec3& SceneObject::Pos(const vec3& pos)
	{
		_ent->_Pos = pos;

		return _ent->_Pos;
	}

	const vec3& SceneObject::Pos(const vec3& pos, const bool& add)
	{
		_ent->_Pos += pos;

		return _ent->_Pos;
	}

	const vec3& SceneObject::Rot()
	{
		return _ent->_Rot;
	}

	const vec3& SceneObject::Rot(const vec3& rot)
	{
		_ent->_Rot = rot;

		return _ent->_Rot;
	}

	const vec3& SceneObject::Rot(const vec3& rot, const bool& add)
	{
		_ent->_Rot += rot;

		return _ent->_Rot;
	}

	const vec3& SceneObject::Scale()
	{
		return _ent->_Scale;
	}

	const vec3& SceneObject::Scale(const vec3& scale)
	{
		_ent->_Scale = scale;

		return _ent->_Scale;
	}

	const vec3& SceneObject::Scale(const vec3& scale, const bool& add)
	{
		_ent->_Scale += scale;

		return _ent->_Scale;
	}

	const unsigned int& SceneObject::ID() const
	{
		return _id;
	}

	Entity& SceneObject::Parent()
	{
		if (_ent->_Parent != nullptr)
		{
			return *_ent->_Parent;
		}
		else
		{
			return *_ent;
		}

	}

	const mat4& SceneObject::TRS()
	{
		return _ent->_TRS;
	}

	void SceneObject::SwitchScene(std::string name)
	{
		_scene->SwitchScene(name);
	}

	inline void SceneObject::Init(const unsigned int& id, Scene* scene, Entity* ent)
	{
		_id = id;
		_scene = scene;
		_ent = ent;
	}

	Scene& SceneObject::GetScene()
	{
		return *_scene;
	}
	
	Entity& SceneObject::GetEntity()
	{
		return *_ent;
	}

	//// Behavior

	const bool& Behavior::Active(const bool& setActive) 
	{
		GetScene().ToggleBehavior(*this, setActive);

		return setActive;
	}

	const bool& Behavior::Active()
	{
		return m_Active;
	}

	//// Camera

	Camera::Camera(const float& near, const float& far)
		: n(near), f(far) {}

	mat4 Camera::GetView()
	{
		return m_View;
	}
	mat4 Camera::GetProj()
	{
		return m_Proj;
	}


	void Camera::CalculateView()
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


		// TODO: User TRS here

		m_View = R * T;

	}

	void PerspectiveCam::SetFOV(float fov)
	{
		m_fov = fov;
	}

	void PerspectiveCam::CalculateProj(const float& width, const float& height)
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

	void OrthoCam::CalculateProj(const float& width, const float& height)
	{
		m_Proj =
		{
			2 / (width - 0), 0, 0, -((width + 0) / (width - 0)),
			0, 2 / (height - 0), 0, -((height + 0) / (height - 0)),
			0, 0, -(2 / (f - n)), -((f + n) / (f - n)),
			0,0,0,1
		};
	}


	//// Renderer

	const bool& Renderer::Active(const bool& setActive)
	{
		GetScene().ToggleRenderer(*this, setActive);

		return setActive;
	}

	const bool& Renderer::Active()
	{
		return m_Active;
	}



	//// Entity

	Entity::Entity()
		: _Parent(nullptr), _Children(), _Active(true),
		_Dirty(true), _Pos(0.0f), _Rot(0.0f), _Scale(1.0f), _TRS(1.0f) {}


	const mat4& Entity::GetTRS()
	{
		return _TRS;
	}

	mat4 Entity::CalcTRS()
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

		return T * R * S;
	}

	void Entity::UpdateRootTRS()
	{
		// This version does not multiply by a parent

		if (_Dirty)
		{
			_TRS = CalcTRS();

			_Dirty = false;

		}

		// Update Children's TRS
		for (auto& child : _Children)
		{
			child->UpdateTRS();
		}
	}

	void Entity::UpdateTRS()
	{
		if (_Dirty)
		{
			_TRS = _Parent->_TRS * CalcTRS();

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

	void Entity::AddChild(Entity* child)
	{
		_Children.push_back(child);
	}

	const bool& Entity::Active(const bool& setActive)
	{

		GetScene().ToggleEntity(*this, setActive);

		return setActive;
	}

	const bool& Entity::Active()
	{
		return _Active;
	}
}