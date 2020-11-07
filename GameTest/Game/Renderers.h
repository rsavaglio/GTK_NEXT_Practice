#pragma once

#include "gtk/gtk.h"

#include "app\app.h"

#include <array>
#include <math.h>

class RendTemplate : public gtk::Renderer
{

public:

	RendTemplate(gtk::Entity* const entity) : Renderer(entity) {}

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

	SpriteRenderer(gtk::Entity* const entity, CSimpleSprite* const sprite) 
		: Renderer(entity), m_Sprite(sprite) {}

	void Start() override
	{

	}
	
	void Draw() override
	{
		// Set Position Based on Entity
		m_Sprite->SetPosition(m_Entity->GetPos().x, m_Entity->GetPos().y);
		//m_Sprite->SetAngle();
		m_Sprite->SetScale(2);


		// Draw sprite
		m_Sprite->Draw();

	}

	CSimpleSprite* const m_Sprite;

private:

};

class CubeRenderer : public gtk::Renderer
{
	

public:

	CubeRenderer(gtk::Entity* const entity) : Renderer(entity),
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


		// Translate

		float tx = 500.0f;
		float ty = 500.0f;
		float tz = 10.0f;

		gtk::mat4 T = { 1.0f, 0.0f, 0.0f, 0.0f,
					   0.0f, 1.0f, 0.0f, 0.0f,
					   0.0f, 0.0f, 1.0f, 0.0f,
						tx, ty, tz, 1.0f};

		// Rotate

		float rad = PI / 180; // Converts degrees to rad

		float rx = (0.0f + _anim) * rad;
		float ry = (45.0f + _anim++) * rad;
		float rz = 45.0f;

		gtk::mat4 R = { cos(ry) * cos(rz),
				 sin(rx) * sin(ry) * cos(rz) + cos(rx) * sin(rz),
				-cos(rx) * sin(ry) * cos(rz) + sin(rx) * sin(rz),
				 0,
				-cos(ry) * sin(rz),
				-sin(rx) * sin(ry) * sin(rz) + cos(rx) * cos(rz),
				cos(rx) * sin(ry) * sin(rz) + sin(rx) * cos(rz),
				0,
				sin(ry),
				-sin(rx) * cos(ry),
				cos(rx) * cos(ry),
				0,
				0, 0, 0, 1 };

		// Scale

		float sx = 100.0f;
		float sy = 100.0f;
		float sz = 100.0f;

		gtk::mat4 S = { sx, 0.0f, 0.0f, 0.0f,
						0.0f, sy, 0.0f, 0.0f,
						0.0f, 0.0f, sz, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f };

		gtk::mat4 M = T * R * S;

		for (int i = 0; i < 24; i += 2)
		{
			s = { _vbo[_ibo[i]].x, _vbo[_ibo[i]].y, _vbo[_ibo[i]].z, 1 };
			e = { _vbo[_ibo[i + 1]].x, _vbo[_ibo[i+ 1]].y, _vbo[_ibo[i + 1]].z, 1 };

			// TODO: MVP here

			s = M * s;
			e = M * e;

			App::DrawLine(
				s.x, s.y, 
				e.x, e.y,
				0.9f, 0.5f, 0.2f);
		}
	}


private:
	std::array<gtk::vec4, 8> _vbo;
	std::array<int, 24> _ibo;

	float _anim;
};