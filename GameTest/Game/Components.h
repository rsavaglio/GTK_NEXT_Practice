#pragma once
#include "gtk/gtk.h"
#include "app/app.h"
#include "gtk/gtkMath.hpp"

using namespace gtk;

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

class SphereB : public gtk::Behavior
{
public:
	
	SphereB() : _vel(), _acc(0.0f, -9.8f, 0.0f) {}

	void Start() override
	{
	}

	void Update(const float& deltaTime) override
	{

		gtk::vec3 p = Pos();

		// Update position
		Pos(p + (_vel * deltaTime) + ((_acc * (deltaTime * deltaTime)) * (1 / 2)));

		// Update velocity
		_vel = _vel + (_acc * deltaTime);
	}

	int Trigger(const int& code) override
	{

		_vel = 0;

		return 0;
	}


private:

	gtk::vec3 _vel;
	gtk::vec3 _acc;

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


class CameraController : public gtk::Behavior
{
public:
	CameraController(float speed)
		: m_Speed(speed) {}

	void Start() override
	{

	}

	void Update(const float& deltaTime) override
	{

		// Need a better solution for this
		// Base comp should just have these functions


		Pos((Pos().x, Pos().y, Pos().z + (App::GetController().GetLeftThumbStickY() * m_Speed)));
	}

	int Trigger(const int& code)
	{
		return 0;
	}


private:

	float m_Speed;

};

class SphereManager : public gtk::Behavior
{

public:
	SphereManager(const float& delay, ObjectPool& pool) : _delay(delay), _time(0), _spherePool(pool) {}

	void Start() override
	{

	}

	void Update(const float& deltaTime) override
	{
		_time += deltaTime;

		if (_time >= _delay)
		{
			Entity& newSphere = _spherePool.Create();

			newSphere.Pos(vec3(((rand() % 20) - 10), 0.0f, 0.0f));

			// Resets velocity on sphere
			newSphere.Trigger(1);

			_time = 0;

		}

	}

	int Trigger(const int& code) override
	{

		return 0;
	}


private:

	float _delay;
	float _time;
	ObjectPool& _spherePool;

};