#pragma once

#include "Component.h"
#include "gtkMath.hpp"
#include <math.h>

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
		mat4 GetProj()
		{
			return m_Proj;
		}

	private:

		Camera() :m_Dirty(true), m_Pos(0), m_Rot(0, 0, 0), m_WorldUp(0, 1, 0), m_View(1), m_Proj(1),
		l(0), r(1024), t(768), b(0), n(1), f(100), fov(80){}

		void CalculateView()
		{

			// Translate
			gtk::mat4 T = { 1.0f, 0.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 1.0f, 0.0f,
							-m_Pos.x, -m_Pos.y, m_Pos.z, 1.0f };

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


			m_View = R * T;

			// TODO: Update to use forward vector

		}

		void CalculateProj()
		{
			/*  ORTHO
			m_Proj =
			{
				2/(r-l), 0, 0, -((r+l)/(r-l)),
				0, 2/(t-b), 0, -((t+b)/(t-b)),
				0, 0, -(2/(f-n)), -((f+n)/(f-n)),
				0,0,0,1
			};

			*/

			float a = r / t;
			float d = 1 / (tan((fov * (3.14159265359f / 180.0f)) / 2));


			m_Proj =
			{
				d/a, 0, 0, 0,
				0, d, 0, 0,
				0, 0, (n+f)/(n-f), -1,
				0,0,(2*n*f)/(n-f),0
			};


		}

		void Update()
		{
			if (m_Dirty)
			{
				CalculateView();
				CalculateProj();
				m_Dirty = true;
			}
		}

		void Soil()
		{
			m_Dirty = true;
		}

	private:

		bool m_Dirty;

		vec3 m_Pos;
		vec3 m_Rot;
		vec3 m_WorldUp;

		mat4 m_View;
		mat4 m_Proj;

		float l;
		float r;
		float t;
		float b;
		float n;
		float f;

		float fov;
	};
}

