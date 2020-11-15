#pragma once
#include "gtk/gtk.h"
#include "app/app.h"
#include "gtk/gtkMath.hpp"

class BehaviorTemplate : public gtk::Behavior
{
public:
	BehaviorTemplate() {}

	void Start() override
	{

	}

	void Update(const float& deltaTime) override
	{

	}

	int Trigger(const int& code) override
	{

		return 0;
	}


private:

};

class PlayerController : public gtk::Behavior
{
public:
	PlayerController(float speed) 
		: m_Speed(speed) {}

	void Start() override
	{

	}

	void Update(const float& deltaTime) override
	{

		// Need a better solution for this
		// Base comp should just have these functions


		Pos((Pos().x + (App::GetController().GetLeftThumbStickX() * m_Speed), Pos().y, Pos().z));
		Pos((Pos().x, Pos().y + (App::GetController().GetLeftThumbStickY() * m_Speed), Pos().z));
	}

	int Trigger(const int& code)
	{
		return 0;
	}


private:

	float m_Speed;

};

class RotaterComp : public gtk::Behavior
{
public:
	RotaterComp(const gtk::vec3& rotVals) 
		: anim(rotVals) {}

	void Start() override
	{

	}

	void Update(const float& deltaTime) override
	{
		Rot(anim, true);
	}

	int Trigger(const int& code) override
	{
		return 0;
	}

private:

	gtk::vec3 anim;

};