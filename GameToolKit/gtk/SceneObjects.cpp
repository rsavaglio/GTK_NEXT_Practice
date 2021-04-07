#include "SceneObjects.h"

namespace gtk {

	
	//// Component

	SceneObject::SceneObject() : _id(0), _scene(nullptr), _ent(nullptr) {}

	const std::string& SceneObject::GetName()
	{
		// TODO: insert return statement here
		return _ent->_Name;
	}

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

	const vec3& SceneObject::GlobalPos()
	{
		return _ent->_globalPos;
	}

	vec3 SceneObject::Right()
	{
		vec3 r = _ent->_right;
		return r;
	}

	vec3 SceneObject::Up()
	{
		vec3 u = _ent->_up;
		return u;
	}

	vec3 SceneObject::Forward()
	{
		vec3 f = _ent->_forward;
		return f;
	}

	void SceneObject::SetColor(const vec3& color)
	{
		_scene->SetColourOnRenderer(_ent->ID(), color);
	}

	const int& SceneObject::State()
	{
		return _scene->GetState();
	}

	const int& SceneObject::State(const int& newState)
	{
		_scene->SetState(newState);
		return _scene->GetState();
	}

	void SceneObject::Trigger(const int& code)
	{
		// Triggers any of its behaviours
		_scene->TriggerBehaviours(_ent->ID(), code);
	}

	void SceneObject::TriggerCollision(Entity& other)
	{
		// Triggers any of its behaviours
		_scene->TriggerOnCollision(_ent->ID(), other);
	}

	void SceneObject::SwitchScene(std::string name)
	{
		_scene->SwitchScene(name);
	}

	float SceneObject::LERP(const float& s, const float& e, const float& t)
	{
		return (1 - t) * s + t * e;
	}

	vec4 SceneObject::LERP(const vec4& s, const vec4& e, const float& t)
	{
		vec4 temp(0);

		temp.x = (1 - t) * s.x + t * e.x;
		temp.y = (1 - t) * s.y + t * e.y;
		temp.z = (1 - t) * s.z + t * e.z;
		temp.w = (1 - t) * s.w + t * e.w;

		return temp;
	}

	vec3 SceneObject::LERP(const vec3& s, const vec3& e, const float& t)
	{
		vec3 temp(0);

		temp.x = (1 - t) * s.x + t * e.x;
		temp.y = (1 - t) * s.y + t * e.y;
		temp.z = (1 - t) * s.z + t * e.z;

		return temp;
	}

	vec2 SceneObject::LERP(const vec2& s, const vec2& e, const float& t)
	{
		vec2 temp(0);
		temp.x = (1 - t) * s.x + t * e.x;
		temp.y = (1 - t) * s.y + t * e.y;
		return temp;
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

	const mat4& Camera::GetView()
	{
		return m_View;
	}
	const mat4& Camera::GetProj()
	{
		return m_Proj;
	}

	std::vector<Entity*> Camera::GetParents(Entity& ent)
	{
		std::vector<Entity*> parents;

		// Not at the top, go deeper
		if (ent._Parent != &ent)
		{
			parents = GetParents(*ent._Parent);
			parents.push_back(&ent);
		}
		else // At the top, add yourself and return
		{
			parents.push_back(&ent);
		}

		return parents;
	}


	void Camera::CalculateView()
	{
		// TODO: allow other scaling

		mat4 trs;
		
		// Cam has a parent
		if (&GetEntity().Parent() != &GetEntity())
		{
			mat4 parentTRS = Parent().TRS();
			mat4 camTR = GetEntity().CalcTR();

			trs = parentTRS * camTR;
		}
		else 
		{
			trs = GetEntity().CalcTR();
		}
		
		mat3 R =
		{
			trs(0,0), trs(1,0), trs(2,0),
			trs(0,1), trs(1,1), trs(2,1),
			trs(0,2), trs(1,2), trs(2,2),
		};
		R.SetInverse();

		vec3 iPos = R * vec3(trs(0, 3), trs(1, 3), trs(2, 3));

		mat4 final
		{
			R(0,0), R(1,0), R(2,0), 0,
			R(0,1), R(1,1), R(2,1), 0,
			R(0,2), R(1,2), R(2,2), 0,
			-iPos.x, -iPos.y, -iPos.z, 1
		};

		m_View = final;

	}

	void Camera::CalculateView2()
	{

		// Translate
		gtk::mat4 T = { 1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						-Pos().x, -Pos().y, -Pos().z, 1.0f };


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
						0, 0, 0, 1.0f };


		R.SetInverse();

		m_View = T * R;

	}

	PerspectiveCam::PerspectiveCam(const float& near, const float& far, const float& fov)
		: Camera(near, far), m_fov(fov) {}

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
			0, 0, f/(f-n), 1,
			0,0,-(( n * f) / (n - f)),0
		};
	}


	OrthoCam::OrthoCam(const float& near, const float& far)
		: Camera(near, far) {}

	void OrthoCam::CalculateProj(const float& width, const float& height)
	{

		float l = -(width * 0.5);
		float r = width * 0.5;

		float b = -(height * 0.5);
		float t = height * 0.5;

		m_Proj =
		{
			2 / (r - l), 0, 0, 0,
			0, 2 / (t - b), 0, 0,
			0, 0, 1/(f - n), 0,
			-((r + l)/(r - l)),-((t + b)/(t - b)),-((n)/(f-n)),1
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
		: _Name(""), _Parent(nullptr), _Children(), _Active(true),
		_Pos(0.0f), _Rot(0.0f), _Scale(1.0f), _TRS(1.0f), _globalPos(1.0f) {}


	const mat4& Entity::GetTRS()
	{
		return _TRS;
	}

	mat4 Entity::CalcTR()
	{
		// Rotate
		float rx = Rot().x * (3.14159265359f / 180.0f);
		float ry = Rot().y * (3.14159265359f / 180.0f);
		float rz = Rot().z * (3.14159265359f / 180.0f);

		gtk::mat4 TR = 
		{ 
		  cosf(ry) * cosf(rz),
		  sinf(rx) * sinf(ry) * cosf(rz) + cosf(rx) * sinf(rz),
		 -cosf(rx) * sinf(ry) * cosf(rz) + sinf(rx) * sinf(rz), 0,
		 
		 -cosf(ry) * sinf(rz),
		 -sinf(rx) * sinf(ry) * sinf(rz) + cosf(rx) * cosf(rz),
		  cosf(rx) * sinf(ry) * sinf(rz) + sinf(rx) * cosf(rz), 0,
		
		  sinf(ry),
		 -sinf(rx) * cosf(ry),
		  cosf(rx) * cosf(ry), 0,
		
		  Pos().x, Pos().y, Pos().z, 1
		};

		return TR;
	}

	mat4 Entity::CalcTRS()
	{

		// Translate, Rotate, Scale

		float rx = _Rot.x * (3.14159265359f / 180.0f);
		float ry = _Rot.y * (3.14159265359f / 180.0f);
		float rz = _Rot.z * (3.14159265359f / 180.0f);


		gtk::mat4 TRS = { (cosf(ry) * cosf(rz)) * _Scale.x,
						 (sinf(rx) * sinf(ry) * cosf(rz) + cosf(rx) * sinf(rz)) * _Scale.x,
						(-cosf(rx) * sinf(ry) * cosf(rz) + sinf(rx) * sinf(rz)) * _Scale.x,
						 0.0f,
						(-cosf(ry) * sinf(rz))* _Scale.y,
						(-sinf(rx) * sinf(ry) * sinf(rz) + cosf(rx) * cosf(rz)) * _Scale.y,
						 (cosf(rx) * sinf(ry) * sinf(rz) + sinf(rx) * cosf(rz)) * _Scale.y,
						 0.0f,
						 (sinf(ry)) * _Scale.z,
						(-sinf(rx) * cosf(ry)) * _Scale.z,
						 (cosf(rx) * cosf(ry)) * _Scale.z,
						 0.0f,
						 _Pos.x, _Pos.y, _Pos.z, 1.0f };

		return TRS;
	}

	void Entity::UpdateRootTRS()
	{

		// Global Position
		_globalPos = vec3(_Pos.x, _Pos.y, _Pos.z);

		// This version does not multiply by a parent
		_TRS = CalcTRS();

		// Right
		_right.x = _TRS[0][0];
		_right.y = _TRS[0][1];
		_right.z = _TRS[0][2];
		_right.Normalize();

		// Up
		_up.x = _TRS[1][0];
		_up.y = _TRS[1][1];
		_up.z = _TRS[1][2];
		_up.Normalize();

		// Forward
		_forward.x = _TRS[2][0];
		_forward.y = _TRS[2][1];
		_forward.z = _TRS[2][2];
		_forward.Normalize();

		// Update Children's TRS
		for (auto& child : _Children)
		{
			child->UpdateTRS();
		}
	}

	void Entity::UpdateTRS()
	{

		// Global Position
		vec4 p = vec4(_Pos.x, _Pos.y, _Pos.z, 1.0f);
		p = _Parent->_TRS * p;
		_globalPos = vec3(p.x, p.y, p.z);


		// Get full transform
		_TRS = _Parent->_TRS * CalcTRS();


		// Right
		vec4 temp(1.0f, 0.0f, 0.0f, 1.0f);
		vec4 t = _TRS * temp;
		_right.x = t.x;
		_right.y = t.y;
		_right.z = t.z;
		_right.Normalize();

		// Up
		temp = vec4(0.0f, 1.0f, 0.0f, 1.0f);
		t = _TRS * temp;
		_up.x = t.x;
		_up.y = t.y;
		_up.z = t.z;
		_up.Normalize();

		// Forward
		temp = vec4(0.0f, 0.0f, 1.0f, 1.0f);
		t = _TRS * temp;
		_forward.x = t.x;
		_forward.y = t.y;
		_forward.z = t.z;
		_forward.Normalize();



		// Update Children's TRS
		for (auto& child : _Children)
		{
			child->UpdateTRS();
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
	const bool& Collider::Active(const bool& setActive)
	{
		GetScene().ToggleCollider(*this, setActive);

		return setActive;
	}
	const bool& Collider::Active()
	{
		return m_Active;
	}



	Model::Model(std::string filePath) : _vbo(), _ibo()
	{
		LoadObject(filePath);
	}

	const std::vector<gtk::vec4>& Model::GetVBO() const
	{
		return _vbo;
	}

	const std::vector<int>& Model::GetIBO() const
	{
		return _ibo;
	}

	void Model::LoadObject(std::string filePath)
	{
		using namespace std;

		// TODO: Add flyweight here, longer load time for every object that needs an obj

		// Open File
		fstream file;
		file.open(filePath);
		ASSERT(file.is_open());

		string prefix;

		// Find the verts
		while (prefix != "v")
		{
			file >> prefix;
		}

		// Add each vert to vbo
		float x, y, z;
		while (prefix == "v")
		{
			file >> x;
			file >> y;
			file >> z;

			gtk::vec4 newVert = { x, y, z, 1.0f };
			_vbo.push_back(newVert);

			file >> prefix;
		}

		// Find the faces
		while (prefix != "f")
		{
			file >> prefix;
		}

		int e1 = 0;
		int e2 = 0;
		int e3 = 0;

		// Add each quad to ibo
		while (!file.eof())
		{

			file >> e1;
			file >> e2;
			file >> e3;

			e1 -= 1;
			e2 -= 1;
			e3 -= 1;

			_ibo.push_back(e1);
			_ibo.push_back(e2);

			_ibo.push_back(e2);
			_ibo.push_back(e3);

			_ibo.push_back(e3);
			_ibo.push_back(e1);

			file >> prefix;

		}

		file.close();
	}
}