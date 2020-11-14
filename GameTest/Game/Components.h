#pragma once
#include "gtk/gtk.h"
#include "app/app.h"
#include "gtk/gtkMath.hpp"

class CompTemplate : public gtk::Behavior
{
public:
	CompTemplate(gtk::Entity* const entity, const gtk::UpdateGroup& compGroup) : Behavior(entity, compGroup) {}

	void Start() override
	{

	}

	void Update(float deltaTime) override
	{

	}


private:

};

class PlayerController : public gtk::Behavior
{
public:
	PlayerController(gtk::Entity* const entity, const gtk::UpdateGroup& compGroup, float speed) 
		: Behavior(entity, compGroup), m_Speed(speed) {}

	void Start() override
	{

	}

	void Update(float deltaTime) override
	{

		// Need a better solution for this
		// Base comp should just have these functions


		m_Entity->SetPosX(m_Entity->GetPos().x + (App::GetController().GetLeftThumbStickX() * m_Speed));
		m_Entity->SetPosY(m_Entity->GetPos().y + (App::GetController().GetLeftThumbStickY() * m_Speed));


	}


private:

	float m_Speed;

};

class RotaterComp : public gtk::Behavior
{
public:
	RotaterComp(gtk::Entity* const entity, const gtk::UpdateGroup& compGroup, const gtk::vec3& rotVals) 
		: Behavior(entity, compGroup), animX(rotVals.x), animY(rotVals.y), animZ(rotVals.z) {}

	void Start() override
	{

	}

	void Update(float deltaTime) override
	{
		m_Entity->SetRot(m_Entity->GetRot().x + animX,
						 m_Entity->GetRot().y + animY,
						 m_Entity->GetRot().z + animZ);
	}


private:

	float animX;
	float animY;
	float animZ;

};