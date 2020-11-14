#include "Component.h"

namespace gtk {

	
	//// Component

	Component::Component() : _id(0), _scene(nullptr) {}

	const unsigned int& Component::ID() const
	{
		return _id;
	}

	inline void Component::Init(const unsigned int& id, Scene* scene)
	{
		_id = id;
		_scene = scene;
	}

	Scene& Component::GetScene()
	{
		return *_scene;
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

}