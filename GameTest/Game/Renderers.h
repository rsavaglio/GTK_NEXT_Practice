#pragma once

#include "gtk/gtk.h"
#include "app\app.h"

#include <array>
#include <math.h>


class RendTemplate : public gtk::Renderer
{

public:

	RendTemplate() {}

	void Start() override
	{
		// Called first frame
	}

	void Draw() override
	{
		// Draw stuff
	}

};


class SpriteRenderer : public gtk::Renderer
{

public:

	SpriteRenderer(const char* filePath, const int& col, const int& row) : m_Sprite(nullptr) 
	{
		// Setup sprite
		m_Sprite = App::CreateSprite(filePath, col, row);
	}

	// Helper
	float GetRotFromParents(gtk::Entity& ent)
	{
		// Base case, at root entity
		if (&ent.Parent() == &ent)
		{
			return ent.Rot().z;
		}
		else
		{
			// Not at root yet
			return ent.Rot().z + GetRotFromParents(ent.Parent());
		}
	}

	float GetScaleFromParents(gtk::Entity& ent)
	{
		// Base case, at root entity
		if (&ent.Parent() == &ent)
		{
			return ent.Scale().z;
		}
		else
		{
			// Not at root yet
			return ent.Scale().z * GetScaleFromParents(ent.Parent());
		}
	}

	void Start() override
	{
		
	}
	
	void Draw() override
	{
		gtk::mat4 model = TRS();
		gtk::mat4 view = GetView();
		gtk::mat4 proj = GetProj();

		gtk::mat4 mvp = proj * view * model;


		gtk::vec4 p = { 0.0f, 0.0f, 0.0f, 1.0f };

		p = mvp * p;

		// Only draw when infront of camera
		if (p.z > 0)
		{

			m_Sprite->SetPosition(p.x / p.z, p.y / p.z);

			m_Sprite->SetAngle(GetRotFromParents(GetEntity()) * PI / 180);

			m_Sprite->SetScale(GetScaleFromParents(GetEntity()) / p.z);

			// Draw sprite
			m_Sprite->Draw();
		}

	}

private:

	CSimpleSprite* m_Sprite;

};



class DirRenderer : public gtk::Renderer
{

public:

	DirRenderer() {}

	void Start() override
	{
		// Called first frame
	}

	void Draw() override
	{
		Entity& ent = GetEntity();

		gtk::vec4 s;
		gtk::vec4 e;

		gtk::mat4 model = TRS();
		gtk::mat4 view = GetView();
		gtk::mat4 proj = GetProj();

		gtk::mat4 mvp = proj * view * model;


		// Draw Directional Vectors

		// Right, Red
		s = gtk::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		e = gtk::vec4(1.0f, 0.0f, 0.0f, 1.0f);

		s = mvp * s;
		e = mvp * e;

		if (s.z > 0 && e.z > 0)
		{
			App::DrawLine(
				s.x / s.z, s.y / s.z,
				e.x / e.z, e.y / e.z,
				1.0f, 0.0f, 0.0f);
		}


		// Up, Green

		s = gtk::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		e = gtk::vec4(0.0f, 1.0f, 0.0f, 1.0f);

		s = mvp * s;
		e = mvp * e;

		if (s.z > 0 && e.z > 0)
		{
			App::DrawLine(
				s.x / s.z, s.y / s.z,
				e.x / e.z, e.y / e.z,
				0.0f, 1.0f, 0.0f);
		}

		// Forward, blue

		s = gtk::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		e = gtk::vec4(0.0f, 0.0f, 1.0f, 1.0f	);

		s = mvp * s;
		e = mvp * e;

		if (s.z > 0 && e.z > 0)
		{
			App::DrawLine(
				s.x / s.z, s.y / s.z,
				e.x / e.z, e.y / e.z,
				0.0f, 0.0f, 1.0f);
		}
	}

};


