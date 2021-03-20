#pragma once

#include "gtk/gtk.h"
#include "app\app.h"

#include <array>
#include <math.h>
#include <fstream>

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

class TextRenderer : public gtk::Renderer
{

private:

	gtk::vec3 _color;
	const char* _text;

public:

	TextRenderer(const char* text, gtk::vec3 color = gtk::vec3(0.5f, 0.5f, 0.2f)) : _color(color), _text(text)
	{
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

			App::Print(p.x / p.z, p.y / p.z, _text, _color.r, _color.g, _color.b);

		}

	}



};

class CubeRenderer : public gtk::Renderer
{
	

public:

	CubeRenderer(const gtk::vec3& color)
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
		Renderer(color)
	{}

	void Start() override
	{
		// Called first frame
	}

	void Draw() override
	{
		gtk::vec4 s;
		gtk::vec4 e;

		gtk::mat4 model = TRS();
		gtk::mat4 view = GetView();
		gtk::mat4 proj = GetProj();

		gtk::mat4 mvp = proj * view * model;


		for (int i = 0; i < 24; i += 2)
		{
			s = { _vbo[_ibo[i]].x, _vbo[_ibo[i]].y, _vbo[_ibo[i]].z, 1 };
			e = { _vbo[_ibo[i + 1]].x, _vbo[_ibo[i+ 1]].y, _vbo[_ibo[i + 1]].z, 1 };

			s = mvp * s;
			e = mvp * e;


			// Both points infront of camera
			if (s.z > 0 && e.z > 0)
			{
				App::DrawLine(
					s.x / s.z, s.y / s.z,
					e.x / e.z, e.y / e.z,
					0.9f, 0.5f, 0.2f);
			}
		}
	}


private:

	std::array<gtk::vec4, 8> _vbo;
	std::array<int, 24> _ibo;
};

class OBJRenderer : public gtk::Renderer
{


public:


	OBJRenderer(std::string filePath, gtk::vec3 color = vec3(0.5f, 0.5f, 0.2f)) : _vbo(), _ibo(), Renderer(color)
	{
		LoadObject(filePath);
	}

	void Start() override
	{
		// Called first frame
	}

	void Draw() override
	{
		gtk::vec4 s;
		gtk::vec4 e;

		gtk::mat4 model = TRS();
		gtk::mat4 view = GetView();
		gtk::mat4 proj = GetProj();

		gtk::mat4 mvp = proj * view * model;

		// Draw Model
		for (int i = 0; i < _ibo.size(); i += 2)
		{
			s = { _vbo[_ibo[i]].x, _vbo[_ibo[i]].y, _vbo[_ibo[i]].z, 1 };
			e = { _vbo[_ibo[i + 1]].x, _vbo[_ibo[i + 1]].y, _vbo[_ibo[i + 1]].z, 1 };

			s = mvp * s;
			e = mvp * e;

			// Both points infront of camera
			if (s.z > 0 && e.z > 0)
			{
				App::DrawLine(
					s.x / s.z, s.y / s.z,
					e.x / e.z, e.y / e.z,
					_color.x, _color.y, _color.z);
			}

		}
	}


private:

	void LoadObject(std::string filePath)
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
	std::vector<gtk::vec4> _vbo;
	std::vector<int> _ibo;
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


