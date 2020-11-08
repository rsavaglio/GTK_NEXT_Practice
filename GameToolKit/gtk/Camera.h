#pragma once

#include "Component.h"
#include "gtkMath.hpp"

namespace gtk {

	class Camera
	{
		friend class Scene;

	public:

		void SetPos(const vec3& pos)
		{
			m_Pos = pos;

			Soil();
		}
		void SetPos(const float& x, const float& y, const float& z)
		{
			m_Pos.x = x;
			m_Pos.y = y;
			m_Pos.z = z;

			Soil();
		}

		const vec3& GetPos()
		{
			return m_Pos;
		}

		void SetRot(const vec3& dir)
		{
			m_Rot = dir;

			Soil();
		}
		void SetRot(const float& x, const float& y, const float& z)
		{
			m_Rot.x = x;
			m_Rot.y = y;
			m_Rot.z = z;

			Soil();
		}

		const vec3& GetRot()
		{
			return m_Rot;
		}

		mat4 GetView()
		{
			return m_View;
		}

	private:

		Camera() :m_Dirty(true), m_Pos(0), m_Rot(0, 0, 0), m_WorldUp(0, 1, 0), m_View(1) {}

		void CalculateView()
		{

			// Create orientation vectors
						// Translate
			gtk::mat4 T = { 1.0f, 0.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 1.0f, 0.0f,
							-m_Pos.x,-m_Pos.y, -m_Pos.z, 1.0f };

			// Rotate

			float rx = m_Rot.x * (3.14159265359f / 180.0f);
			float ry = m_Rot.y * (3.14159265359f / 180.0f);
			float rz = m_Rot.z * (3.14159265359f / 180.0f);


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

			R.SetInverse();

			m_View = T * R;

		}

		void Update()
		{
			if (m_Dirty)
			{
				CalculateView();
				m_Dirty = true;
			}
		}

		void Soil()
		{
			m_Dirty = true;
		}

		bool m_Dirty;

		vec3 m_Pos;
		vec3 m_Rot;
		vec3 m_WorldUp;
		
		mat4 m_View;

	};
}

