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


class ShooterB : public gtk::Behavior
{

public:
	ShooterB(const float& speed, ObjectPool& bulletPool) 
		: _speed(speed), _vel(), _velGoal(), _bulletPool(bulletPool) {}

	void Start() override
	{

	}

	void Update(const float& deltaTime) override
	{

		// During Gameplay
		if (State() == 2)
		{
			//// Movement ////

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


			//// Bullets ////

			if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
			{
				Entity& bullet = _bulletPool.Create();
				bullet.Trigger(1);
			}

		}

	}

	int Trigger(const int& code) override
	{
		return 0;
	}


private:

	float _speed;
	vec2 _vel;
	vec2 _velGoal;
	ObjectPool& _bulletPool;
};

class LERPatState : public gtk::Behavior
{

public:
	LERPatState(int state, float speed, const vec3& pos, const vec3& rot) : _state(state), _speed(speed), _targetPos(pos), _targetRot(rot) {}

	void Start() override
	{
		// Start Music
		App::PlaySound(".\\TestData\\Layer1.wav", true);
		App::PlaySound(".\\TestData\\Layer2.wav", true);

		App::PlaySound(".\\TestData\\Layer3.wav", true);
		App::SetSoundVolume(".\\TestData\\Layer3.wav", -10000);
		
		App::PlaySound(".\\TestData\\Layer4.wav", true);
		App::SetSoundVolume(".\\TestData\\Layer4.wav", -10000);
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

			if (Pos() == _targetPos)
			{
				State(2);
			}
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

class BulletB : public gtk::Behavior
{

public:
	BulletB(Entity& shooter) : _vel(), _speed(5.0), _shooter(shooter) {}

	void Start() override
	{

	}

	void Update(const float& deltaTime) override
	{
		// Update position
		Pos(_vel * deltaTime * _speed, true);
	}

	int Trigger(const int& code) override
	{
		// Shoot from shooter position and direction
		_vel = _shooter.Forward();
		Pos(_shooter.Pos());
		return 0;
	}

	void OnCollision(Entity& other) override
	{
		// BOOM
	}


private:

	vec3 _vel;
	float _speed;
	Entity& _shooter;

};


class SphereCollider : public gtk::Collider
{

public:
	SphereCollider() {}


	bool Check(Collider& other) override
	{
		if (true) // If they collide
		{
			return true;
		}

		return false;

	}

private:



};