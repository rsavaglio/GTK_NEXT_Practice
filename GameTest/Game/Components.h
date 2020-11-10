#pragma once
#include "gtk/gtk.h"
#include "app/app.h"
#include "gtk/gtkMath.hpp"

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

		// Need a better solution for this
		// Base comp should just have these functions


		m_Entity->SetPosX(m_Entity->GetPos().x + (App::GetController().GetLeftThumbStickX() * m_Speed));
		m_Entity->SetPosY(m_Entity->GetPos().y + (App::GetController().GetLeftThumbStickY() * m_Speed));

		m_Entity->_Scene->m_Camera.SetPos(
			m_Entity->_Scene->m_Camera.GetPos().x + (App::GetController().GetLeftThumbStickX() * m_Speed), 
			m_Entity->_Scene->m_Camera.GetPos().y, 
			m_Entity->_Scene->m_Camera.GetPos().z + (App::GetController().GetLeftThumbStickY() * m_Speed));

		m_Entity->_Scene->m_Camera.SetRot(
			m_Entity->_Scene->m_Camera.GetRot().x - (App::GetController().GetRightThumbStickY() * m_Speed),
			m_Entity->_Scene->m_Camera.GetRot().y + (App::GetController().GetRightThumbStickX() * m_Speed),
			m_Entity->_Scene->m_Camera.GetRot().z);

	}


private:

	float m_Speed;

};

class RotaterComp : public gtk::Component
{
public:
	RotaterComp(gtk::Entity* const entity, const gtk::CompGroup& compGroup, const gtk::vec3& rotVals) 
		: Component(entity, compGroup), animX(rotVals.x), animY(rotVals.y), animZ(rotVals.z) {}

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