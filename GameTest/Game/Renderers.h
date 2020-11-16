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

	SpriteRenderer(CSimpleSprite* const sprite) : m_Sprite(sprite) {}

	void Start() override
	{

	}
	
	void Draw() override
	{
		// Set Position Based on Entity
		m_Sprite->SetPosition(Pos().x, Pos().y);
		
		
		m_Sprite->SetScale(0.01f);

		// Draw sprite
		m_Sprite->Draw();
	}

	CSimpleSprite* const m_Sprite;

private:

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

			// Clip using camera world position

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