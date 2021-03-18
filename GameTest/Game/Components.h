#pragma once
#include "gtk/gtk.h"
#include "app/app.h"
#include "gtk/gtkMath.hpp"
#include <math.h>

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



class RotatorB : public gtk::Behavior
{
public:
	RotatorB(const gtk::vec3& rotVals) 
		: anim(rotVals) {}

	void Start() override
	{

	}

	void Update(const float& deltaTime) override
	{
		Rot(anim * deltaTime, true);
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
		using namespace std;

		vec3 forward = vec3(

			sin(Rot().y) * cos(Rot().x),
			-sin(Rot().x),
			cos(Rot().x) * cos(Rot().y)
		);


		// Need Quaternions!!!

		Pos( Forward() * (App::GetController().GetLeftThumbStickY() * -m_Speed), true);
		Pos( Right() * (App::GetController().GetLeftThumbStickX() * m_Speed), true);

		Rot(vec3(
			(App::GetController().GetRightThumbStickY() * -m_Speed/10),
			(App::GetController().GetRightThumbStickX() * m_Speed/10), 
			Rot().z), 
			true);
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


class CubeMover : public gtk::Behavior
{

public:
	CubeMover(const float& speed) : _speed(speed){}

	void Start() override
	{

	}

	void Update(const float& deltaTime) override
	{


		// Update velocity goal from input
		_velGoal.x = App::GetController().GetLeftThumbStickX() * _speed;
		_velGoal.y = App::GetController().GetLeftThumbStickY() * _speed;

		// Lerp current velocity to goal
		_vel = LERP(_vel, _velGoal, deltaTime * 10.f);

		// Set position from velocity
		Pos(vec3(
			Pos().x + _vel.x * deltaTime,
			Pos().y + _vel.y * deltaTime,
			Pos().z
		));
	}

	int Trigger(const int& code) override
	{
		return 0;
	}


private:

	float _speed;
	vec2 _vel;
	vec2 _velGoal;

};

class LERPatState : public gtk::Behavior
{

public:
	LERPatState(int state, float speed, const vec3& pos, const vec3& rot) : _state(state), _speed(speed), _targetPos(pos), _targetRot(rot) {}

	void Start() override
	{

	}

	void Update(const float& deltaTime) override
	{
		
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
		{
			State(1);
		}


		if (State() == _state)
		{
			Pos(LERP(Pos(), _targetPos, deltaTime * _speed));
			Rot(LERP(Rot(), _targetRot, deltaTime * _speed));
		}

	}

	int Trigger(const int& code) override
	{
		return 0;
	}


private:

	int _state;
	float _speed;
	vec3 _targetPos;
	vec3 _targetRot;

};