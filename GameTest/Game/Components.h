#pragma once
#include "gtk/gtk.h"
#include "app/app.h"

class CompTemplate : public gtk::Component
{
public:
	CompTemplate(gtk::Entity* const entity, const gtk::CompGroup& compGroup) : Component(entity, compGroup) {}

	void Start() override
	{

	}

	void Update(float deltaTime) override
	{

	}


private:

};

class PlayerController : public gtk::Component
{
public:
	PlayerController(gtk::Entity* const entity, const gtk::CompGroup& compGroup, float speed) 
		: Component(entity, compGroup), m_Speed(speed) {}

	void Start() override
	{

	}

	void Update(float deltaTime) override
	{
		m_Entity->_Transform(0, 0) += (App::GetController().GetLeftThumbStickX() * m_Speed);
		m_Entity->_Transform(0, 1) += (App::GetController().GetLeftThumbStickY() * m_Speed);
	}


private:

	float m_Speed;

};