#pragma once

#include "gtk/gtk.h"

#include "app\app.h"

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
		m_Sprite->SetPosition(m_Entity->_Transform(0,0), m_Entity->_Transform(0, 1));
		//m_Sprite->SetAngle();
		m_Sprite->SetScale(2);


		// Draw sprite
		m_Sprite->Draw();

	}

	CSimpleSprite* const m_Sprite;

private:

};
