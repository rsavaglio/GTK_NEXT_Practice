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

		m_Sprite->SetPosition(p.x, p.y);

		m_Sprite->SetAngle(GetRotFromParents(GetEntity()) * PI / 180);

		m_Sprite->SetScale((1/p.z) * GetScaleFromParents(GetEntity()));

		// Draw sprite
		m_Sprite->Draw();
	}

private:

	CSimpleSprite* m_Sprite;

};

class CubeRenderer : public gtk::Renderer
{
	

public:

	CubeRenderer()
		:
		_vbo({
			gtk::vec4( 1.0f, 1.0f,-1.0f, 1.0f),
			gtk::vec4(-1.0f, 1.0f,-1.0f, 1.0f),
			gtk::vec4(-1.0f, 1.0f, 1.0f, 1.0f),
			gtk::vec4( 1.0f, 1.0f, 1.0f, 1.0f),
			gtk::vec4( 1.0f,-1.0f,-1.0f, 1.0f),
			gtk::vec4(-1.0f,-1.0f,-1.0f, 1.0f),
			gtk::vec4(-1.0f,-1.0f, 1.0f, 1.0f),
			gtk::vec4( 1.0f,-1.0f, 1.0f, 1.0f)
			}),

		_ibo({0, 1, 1, 2, 2, 3, 3, 0, 
			  4, 5, 5, 6, 6, 7, 7, 4,
			  0, 4, 1, 5, 2, 6, 3, 7}),
		_anim(0)
	{}

	void Start() override
	{
		// Called first frame
	}

	void Draw() override
	{
		gtk::vec4 s;
		gtk::vec4 e;

		for (int i = 0; i < 24; i += 2)
		{
			s = { _vbo[_ibo[i]].x, _vbo[_ibo[i]].y, _vbo[_ibo[i]].z, 1 };
			e = { _vbo[_ibo[i + 1]].x, _vbo[_ibo[i+ 1]].y, _vbo[_ibo[i + 1]].z, 1 };

			gtk::mat4 model = TRS();
			gtk::mat4 view = GetView();
			gtk::mat4 proj = GetProj();

			gtk::mat4 mvp = proj * view * model;

			s = mvp * s;
			e = mvp * e;

			// TODO: Clip
			App::DrawLine(
				s.x / s.z, s.y / s.z,
				e.x / e.z, e.y / e.z,
				0.9f, 0.5f, 0.2f);

		}
	}


private:

	std::array<gtk::vec4, 8> _vbo;
	std::array<int, 24> _ibo;

	float _anim;
};