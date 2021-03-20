#pragma once
#include "gtk/gtk.h"
#include "app/app.h"
#include "gtk/gtkMath.hpp"
#include <math.h>
#include "enums.h"


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

	void OnCollision(Entity& other) override
	{

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


class ShooterB : public gtk::Behavior
{

public:
	ShooterB(const float& speed)
		: _speed(speed), _vel(), _velGoal() {}

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
				//Entity& bullet = _bulletPool.Create();
				//bullet.Trigger(1);
			}

		}

	}

	int Trigger(const int& code) override
	{
		return 0;
	}

	void OnCollision(Entity& other) override
	{
		SwitchScene("PracScene");
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
		// Start Music
		App::PlaySound(".\\TestData\\Layer1.wav", true);
		App::PlaySound(".\\TestData\\Layer2.wav", true);

		App::PlaySound(".\\TestData\\Layer3.wav", true);
		App::SetSoundVolume(".\\TestData\\Layer3.wav", -10000);
		
		App::PlaySound(".\\TestData\\Layer4.wav", true);
		App::SetSoundVolume(".\\TestData\\Layer4.wav", -10000);

		State(2);
	}

	void Update(const float& deltaTime) override
	{


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

enum CamState
{
	POS1,
	POS2,
	TOWER
};

class CameraB : public gtk::Behavior
{

public:
	CameraB(float speed) : 
		_speed(speed) {}

	void Start() override
	{
	}

	void Update(const float& deltaTime) override
	{

		// Rotate parent's y

		Parent().Rot(vec3(
			Parent().Rot().x,
			App::GetController().GetRightThumbStickX() * _speed * deltaTime,
			Parent().Rot().z
		), true);

		// Rotate my x
		Rot(vec3(
			App::GetController().GetRightThumbStickY() * -_speed * deltaTime,
			Rot().y,
			Rot().z
		), true);

	}

	int Trigger(const int& code) override
	{
		return 0;
	}

	void OnCollision(Entity& other) override
	{

	}


private:

	float _speed;


	bool _pos1;
	vec3 _triPos1;
	vec3 _triRot1;

	vec3 _triPos2;
	vec3 _triRot2;

	vec3 _targetPos;
	vec3 _targetRot;

};


class CursorB : public gtk::Behavior
{

public:
	CursorB(Entity& tower, const float& speed)
		: _tower(tower), _state(ON), _speed(speed), _vel(), _velGoal() {}

	void Update(const float& deltaTime) override
	{

		//// Movement ////

		// Update velocity goal from input
		_velGoal.x = App::GetController().GetLeftThumbStickX() * _speed;
		_velGoal.y = App::GetController().GetLeftThumbStickY() * _speed;

		// Lerp current velocity to goal
		_vel = LERP(_vel, _velGoal, deltaTime * 20.0f);

		// Set position from velocity
		Pos(vec3(
			Pos().x + _vel.x * deltaTime,
			Pos().y + _vel.y * deltaTime,
			Pos().z
		));


		// Don't go out of bounds
		if (Pos().y > 25.0f)
		{
			Pos(vec3(Pos().x, 25.0f, Pos().z));
		}
		else if (Pos().y < -25.0f)
		{
			Pos(vec3(Pos().x, -25.0f, Pos().z));
		}

		if (Pos().x > 32.0f)
		{
			Pos(vec3(32.0f, Pos().y, Pos().z));
		}
		else if (Pos().x < -32.0f)
		{
			Pos(vec3(-32.0f, Pos().y, Pos().z));
		}


		switch (_state)
		{
		case ON:

			// GREEN
			SetColor(vec3(0.0f, 1.0f, 0.0f));

			// If the player presses X
			if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
			{
				_tower.Active(true);
				_tower.Pos(Pos());
				_tower.Trigger(-1);
			}

			break;
		case OFF:

			// RED
			SetColor(vec3(1.0f, 0.0f, 0.0f));

			break;
		}

		_state = ON;
	}

	int Trigger(const int& code) override
	{
		return 0;
	}


	void OnCollision(Entity& other) override
	{
		_state = OFF;
	}



private:

	Entity& _tower;

	CursorState _state;
	float _speed;
	vec2 _vel;
	vec2 _velGoal;
	
};

class MonkeyB : public gtk::Behavior
{

public:
	MonkeyB(std::vector<vec3> path)
	: _speed(1.0f), _path(path), _currentNode(0){}

	void Start() override
	{
	}

	void Update(const float& deltaTime) override
	{
		// Moving from node to node
		_T += deltaTime * _speed;

		// If at next node
		if (_T >= 1.0f)
		{
			// If not at the end of path
			if (_currentNode != _path.size() - 2)
			{
				// Reset lerp and go to next node
				_T = 0;
				_currentNode++;
			}
			else // Monkey reaches banana!
			{
				// TODO: Do something bad to the player


				// Disable Monkey
				GetEntity().Active(false);
				
			}

		}

		Pos(LERP(_path[_currentNode], _path[_currentNode + 1], _T));

	}

	int Trigger(const int& code) override
	{
		if (code > 0)
		{
			// Take damage

		}
		else
		{
			// Spawn Monkey
			Pos(_path.front());
			_currentNode = 0;

			switch (code)
			{
			case -1:
				// Spawn speedy yellow monkey
				SetColor(vec3(0.8f, 0.7f, 0.3f));
				Scale(1.0f);
				_speed = 5.0f;
				break;

			case -2:
				// Spawn big blue monkey
				SetColor(vec3(0.2f, 0.3f, 0.8f));
				Scale(3.0f);
				_speed = 2.0f;
				break;
			}
		}
		

		return 0;
	}

	void OnCollision(Entity& other) override
	{

	}

private:

	float _speed;
	std::vector<vec3> _path;
	int _currentNode;

	float _T;

};

class BarrelOfMonkeysB : public gtk::Behavior
{

public:
	BarrelOfMonkeysB(ObjectPool& monkeyPool) : _monkeyPool(monkeyPool) {}


	void Update(const float& deltaTime) override
	{
		// Spawn yellow
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_A))
		{
			Entity& newMonkey = _monkeyPool.Create();
			newMonkey.Trigger(-1);
		}


		// Spawn big blue
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B))
		{
			Entity& newMonkey = _monkeyPool.Create();
			newMonkey.Trigger(-2);
		}

	}

private:
	ObjectPool& _monkeyPool;
};



class TowerB : public gtk::Behavior
{

public:
	TowerB(float shootDelay) : _shootDelay(shootDelay), _timeSinceShot(0) {}

	void Start() override
	{

	}

	void Update(const float& deltaTime) override
	{
		// Update time
		_timeSinceShot += deltaTime;

		// If there's a target
		if (_target != nullptr)
		{
			// Do collision on target
			vec3 pos = Pos();
			vec3 tPos = _target->Pos();
			float range = 100;

			// If they collide
			if ((pos - tPos).Dot((pos - tPos)) <= range)
			{
				if (_timeSinceShot > _shootDelay)
				{
					_timeSinceShot = 0;
					// Shoot the monkey!

				}
			}
			else
			{
				// Set to no target
				_target = nullptr;
				SetColor(vec3(0.0f, 0.0f, 1.0f));
			}
		}

	}

	int Trigger(const int& code) override
	{
		if (code == -1)
		{
			SetColor(vec3(0.0f, 0.0f, 1.0f));
		}
		return 0;
	}

	void OnCollision(Entity& other) override
	{
		// If there is no target
		if (_target == nullptr)
		{
			// if other is a monkey
			if (other.GetName() == "monkey")
			{
				// Target it!
				_target = &other;
				SetColor(vec3(1.0f, 0.0f, 0.0f));
			}
		}
	}

private:

	Entity* _target;
	
	float _shootDelay;
	float _timeSinceShot;
};