#pragma once
#include "gtk/gtk.h"
#include "app/app.h"
#include "gtk/gtkMath.hpp"
#include <math.h>
#include "enums.h"
#include <string>

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

class TextRenderer : public gtk::Renderer
{

public:
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

class NumUIRenderer : public gtk::Renderer
{

private:
	gtk::vec3 _color;
	int _num;

public:

	NumUIRenderer(const int& text, gtk::vec3 color = gtk::vec3(0.5f, 0.5f, 0.2f)) : _color(color), _num(text)
	{
	}

	void SetNum(int num)
	{
		_num = num;
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

			int num = _num;

			App::Print(p.x / p.z, p.y / p.z, std::to_string(num).c_str(), _color.r, _color.g, _color.b);
		}

	}



};


class SphereCollider : public gtk::Collider
{

public:
	SphereCollider(float radiusMod = 1.0f) : _radiusMod(radiusMod) {}

	void UpdateData() override
	{
		_radius = Scale().x > Scale().y ? Scale().x : Scale().y;
		_radius = _radius > Scale().z ? _radius : Scale().z;

		_radius *= _radiusMod;
		_center = GlobalPos();
	}


	bool Check(Collider& other) override
	{
		if ((_center - other._center).Dot((_center - other.Pos()))
			<= (_radius + other._radius) * (_radius + other._radius)) // If they collide
		{
			return true;
		}

		return false;

	}

private:
	float _radiusMod;

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

class BulletB : public gtk::Behavior
{

private:

	vec3 _dir;
	vec3 _vel;
	float _speed;
	bool _Dead;

public:
	BulletB() :_dir(), _vel(), _speed(10.0), _Dead(true) {}

	void Start() override
	{

	}

	void Update(const float& deltaTime) override
	{
		// Update position
		Pos(_vel * deltaTime * _speed, true);

		if (_Dead)
		{
			GetEntity().Active(false);
		}
	}

	int Trigger(const int& code) override
	{
		// Shoot from shooter position and direction
		_Dead = false;
		_vel = Rot();
		return 0;
	}

	void OnCollision(Entity& other) override
	{
		// BOOM
		if (other.GetName() == "monkey")
		{
			_Dead = true;
		}
	}

};

enum CamState
{
	POS1,
	POS2,
	TOWER
};

class CameraB : public gtk::Behavior
{

private:

	float _speed;


	bool _pos1;
	vec3 _triPos1;
	vec3 _triRot1;

	vec3 _triPos2;
	vec3 _triRot2;

	vec3 _targetPos;
	vec3 _targetRot;

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

};

enum
{
	STANDARD = -1,
	BRUTE = -2,
	SPEEDY = -3,
	BOSS = -4
};

class MonkeyB : public gtk::Behavior
{

private:
	
	Entity& _cursor;

	float _speed;
	int _health;
	int _worth;
	int _strength;

	std::vector<vec3> _path;
	int _currentNode;

	float _T;

public:
	MonkeyB(Entity& cursor, std::vector<vec3> path)
		: _cursor(cursor), _speed(1.0f), _health(5), _worth(1), _strength(1), _path(path), _currentNode(0) {}

	void Start() override
	{
	}

	void Update(const float& deltaTime) override
	{
		if (_health <= 0)
		{
			// Monkey dead
			GetEntity().Active(false);

			// Give player some money
			_cursor.Trigger(_worth);
		}

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
				_cursor.Trigger(-_strength);

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
			_health -= code;
		}
		else
		{
			// Spawn Monkey
			Pos(_path.front());
			_currentNode = 0;
			_T = 0;

			switch (code)
			{
			case STANDARD:
				// Spawn speedy yellow monkey
				SetColor(vec3(0.8f, 0.7f, 0.3f));
				Scale(1.5f);
				_speed = 3.0f;
				_health = 20;
				_worth = 2;
				_strength = 3;
				break;

			case BRUTE:
				// Spawn big blue monkey
				SetColor(vec3(0.2f, 0.3f, 0.8f));
				Scale(3.0f);
				_speed = 2.0f;
				_health = 100;
				_worth = 3;
				_strength = 5;
				break;
			}
		}
		

		return 0;
	}

	void OnCollision(Entity& other) override
	{

		if (other.GetName() == "bullet")
		{
			Trigger(1);
		}

	}



};

struct SpawnGroup
{
	int _count;
	int _type;
	float _delay;
};

struct Wave
{
	// Monkey type, how many, spawn delay between each
	std::vector<SpawnGroup> _spawnList;

	void AddToWave(const int& count, const int& monkeyType, const float& delay)
	{
		_spawnList.push_back({ count, monkeyType, delay });
	}

};

enum
{
	SPAWNING,
	BREAK,
	WIN
};

class BarrelOfMonkeysB : public gtk::Behavior
{

private:

	ObjectPool& _monkeyPool;
	NumUIRenderer& _waveUIRend;

	std::vector<Wave> _waves;
	int _state;
	float _spawnTimer;
	float _timeSinceSpawn;

	int _waveIndex;
	int _spawnIndex;
	int _spawnCount;

private:

	Wave GetWave()
	{
		return _waves[_waveIndex];
	}

	float GetDelay()
	{
		return _waves[_waveIndex]._spawnList[_spawnIndex]._delay;
	}

	int GetType()
	{
		return _waves[_waveIndex]._spawnList[_spawnIndex]._type;
	}

	int GetCount()
	{
		return _waves[_waveIndex]._spawnList[_spawnIndex]._count;
	}


public:
	BarrelOfMonkeysB(NumUIRenderer& waveUIRend, std::vector<Wave> waves, ObjectPool& monkeyPool) :
		_waveUIRend(waveUIRend),_monkeyPool(monkeyPool), _waves(waves),
		_state(SPAWNING), _spawnTimer(2.0f), _timeSinceSpawn(0), _waveIndex(0), _spawnIndex(0), _spawnCount(0) {}


	void Update(const float& deltaTime) override
	{
		float time;
		int type;

		switch (_state)
		{
		case SPAWNING:

			_timeSinceSpawn += deltaTime;

			// If time to spawn next monkey
			time = GetDelay();
			if (_timeSinceSpawn >= time)
			{
				_timeSinceSpawn = 0;

				// Spawn Monkey
				Entity& monkey = _monkeyPool.Create();
				type = GetType();
				monkey.Trigger(type);
				_spawnCount++;

				// Check if at end of spawn group
				if (_spawnCount == GetCount())
				{
					// Go to next group
					_spawnIndex++;
					_spawnCount = 0;

					// if at end of wave
					if (_spawnIndex == GetWave()._spawnList.size())
					{
						_waveIndex++;
						_spawnIndex = 0;

						// If not at end
						if(_waveIndex == _waves.size())
						{
							// YOU WIN!
							_state = WIN;
						}
						else
						{
							// Update the UI
							_waveUIRend.SetNum(_waveIndex + 1);
							
						}
					}
				}

			}


			break;
		case WIN:
			// Hooray


			break;

		}












		//// Spawn yellow
		//if (App::GetController().CheckButton(XINPUT_GAMEPAD_A))
		//{
		//	Entity& newMonkey = _monkeyPool.Create();
		//	newMonkey.Trigger(-1);
		//}


		//// Spawn big blue
		//if (App::GetController().CheckButton(XINPUT_GAMEPAD_B))
		//{
		//	Entity& newMonkey = _monkeyPool.Create();
		//	newMonkey.Trigger(-2);
		//}

	}

};



class TowerB : public gtk::Behavior
{

private:

	Entity* _target;
	ObjectPool& _bulletPool;

	float _shootDelay;
	float _timeSinceShot;

public:
	TowerB(ObjectPool& bulletPool, float shootDelay) : _bulletPool(bulletPool), _shootDelay(shootDelay), _timeSinceShot(0) {}

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
			if ((pos - tPos).Dot((pos - tPos)) <= range && _target->Active())
			{
				if (_timeSinceShot > _shootDelay)
				{
					_timeSinceShot = 0;

					// Shoot the monkey!
					Entity& newBullet = _bulletPool.Create();
					newBullet.Pos(Pos());

					// Get direction for bullet
					vec3 dir = tPos - pos;

					newBullet.Rot(dir);
					newBullet.Trigger(-1);
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


};



class LineRenderer : public gtk::Renderer
{

public:
	gtk::vec4 _e;

	LineRenderer(const gtk::vec3& color, const gtk::vec3& e = vec3() )
		: _e(gtk::vec4(e.x, e.y, e.z, 1.0f)), Renderer(color) {}

	void Start() override
	{
		// Called first frame
	}

	void Draw() override
	{
		Entity& ent = GetEntity();

		gtk::mat4 model = TRS();
		gtk::mat4 view = GetView();
		gtk::mat4 proj = GetProj();


		gtk::vec4 s = proj * view * vec4(Pos().x, Pos().y, Pos().z, 1.0f);
		gtk::vec4 e = proj * view * model * _e;


		// Draw draw lines

		if (s.z > 0 && e.z > 0)
		{
			App::DrawLine(
				s.x / s.z, s.y / s.z,
				e.x / e.z, e.y / e.z,
				_color.x, _color.y, _color.z);
		}
	}

};

class LineRenderer2 : public gtk::Renderer
{

public:
	gtk::vec4 _s;
	gtk::vec4 _e;

	LineRenderer2(const gtk::vec3& color, const gtk::vec3& s = vec3(), const gtk::vec3& e = vec3())
		: _s(gtk::vec4(s.x, s.y, s.z, 1.0f)), _e(gtk::vec4(e.x, e.y, e.z, 1.0f)), Renderer(color) {}

	void Start() override
	{
		// Called first frame
	}

	void Draw() override
	{
		Entity& ent = GetEntity();

		gtk::mat4 model = TRS();
		gtk::mat4 view = GetView();
		gtk::mat4 proj = GetProj();

		gtk::mat4 mvp = proj * view * model;

		gtk::vec4 s = mvp * _s;
		gtk::vec4 e = mvp * _e;


		// Draw draw lines

		if (s.z > 0 && e.z > 0)
		{
			App::DrawLine(
				s.x / s.z, s.y / s.z,
				e.x / e.z, e.y / e.z,
				_color.x, _color.y, _color.z);
		}
	}

};

class RayCollider : public gtk::Collider
{

public:
	vec3 _dir;
private:
	float _radiusMod;

public:
	RayCollider(float radiusMod = 1.0f) : _radiusMod(radiusMod), _dir(vec3()) {}

	void UpdateData() override
	{
		// Doesn't work great with children objects
		_radius = Scale().x > Scale().y ? Scale().x : Scale().y;
		_radius = _radius > Scale().z ? _radius : Scale().z;

		_radius *= _radiusMod;
		_center = GlobalPos();
	}


	bool Check(Collider& other) override
	{

		vec3 w = other._center - _center;
		float wsq = w.Dot(w);
		float proj = w.Dot(_dir);
		float rsq = other._radius * other._radius;

		// if sphere behind ray, no intersection
		if (proj < 0.0f && wsq > rsq)
		{
			return false;
		}

		float vsq = _dir.Dot(_dir);

		// Tesxt length of difference vs. radius
		return (vsq*wsq - proj*proj <= vsq*other._radius*other._radius);

	}

};

enum
{
	SEARCHING,
	SHOOTING,
	CHARGING,
	SHOOT
};

class LaserB : public gtk::Behavior
{

private:

	Entity* _target;
	LineRenderer& _lineRend;
	RayCollider& _rayCol;
	SphereCollider& _rangeCol;
	float _shootDelay;
	float _timeSinceShot;
	int _state;

public:
	LaserB(LineRenderer& lineRend, RayCollider& rayCol, SphereCollider& rangeCol, const float& shootDelay)
		: _target(nullptr), _lineRend(lineRend), _rayCol(rayCol), _rangeCol(rangeCol),
		_shootDelay(shootDelay), _timeSinceShot(0), _state(SEARCHING)  {}

	void Start() override
	{

	}

	void Update(const float& deltaTime) override
	{
		_timeSinceShot += deltaTime;

		vec3 pos;
		vec3 tPos;
		vec3 dir;
		vec3 end;
		float range;

		switch (_state)
		{
		case SEARCHING:

			// Turn on range collider
			_rayCol.Active(false);
			_rangeCol.Active(true);
			_lineRend.Active(false);

			// Set Colour
			SetColor(vec3(0.5f, 0.0f, 0.0f));

			// If target found go to recharging
			if (_target != nullptr)
			{
				_state = CHARGING;
			}

			break;

		case CHARGING:

			_rayCol.Active(false);
			_rangeCol.Active(false);

			// Set Colour
			SetColor(vec3(1.0f, 0.0f, 0.0f));

			pos = Pos();
			tPos = _target->Pos();
			range = (_rangeCol._radius + 6.0f) * (_rangeCol._radius + 6.0f);

			// If target is dead
			if (!_target->Active())
			{
				_state = SEARCHING;
				_target = nullptr;

			}
			else if ((pos - tPos).Dot(pos - tPos) >= range)
			{
				_state = SEARCHING;
				_target = nullptr;
			}
			else
			{
				// If charged go to shooting
				if (_timeSinceShot > _shootDelay)
				{
					_timeSinceShot = 0;
					_state = SHOOTING;
				}
			}

			break;

		case SHOOTING:

			_rayCol.Active(true);
			_rangeCol.Active(false);

			pos = Pos();
			tPos = _target->Pos();
			range = 100;
			dir = tPos - pos;
			end = dir * 5;

			_rayCol._dir = dir;

			_lineRend.Active(true);
			_lineRend._e = vec4(end.x, end.y, end.z, 1.0f);

			// If shot fired go to charging
			_state = SHOOT;
			break;
		
		case SHOOT:
			_state = CHARGING;
			break;
		}

	}

	int Trigger(const int& code) override
	{
		if (code == -1)
		{
			SetColor(vec3(0.5f, 0.0f, 0.0f));
			_state = SEARCHING;
		}
		return 0;
	}

	void OnCollision(Entity& other) override
	{

		if (other.GetName() == "monkey")
		{
			
			switch (_state)
			{
			case SEARCHING:
			
				// Target it!
				_target = &other;
				SetColor(vec3(1.0f, 0.0f, 0.0f));
					
				break;

			case SHOOT:

				other.Trigger(5);

				break;
			}
		}

	}

};

class SawB : public gtk::Behavior 
{

private:

	Entity& _hSpinner;
	Entity& _vSpinner;
	Entity& _dSpinner;

	float _speed;

public:
	SawB(Entity& hSpinner, Entity& vSpinner, Entity& dSpinner)
		: _hSpinner(hSpinner), _vSpinner(vSpinner), _dSpinner(dSpinner), _speed(300.0f) {}


	void Update(const float& deltaTime) override
	{
		_hSpinner.Rot(vec3(0.0f, deltaTime * _speed, 0.0f), true);
		_vSpinner.Rot(vec3(deltaTime * _speed, 0.0f, 0.0f), true);
		_dSpinner.Rot(vec3(0.0f, deltaTime * _speed, 0.0f), true);
	}


	int Trigger(const int& code) override
	{
		switch (code)
		{
		case 1:
			_dSpinner.Active(true);
			break;

		case 2:
			_hSpinner.Active(true);
			break;

		case 3:
			_vSpinner.Active(true);
			break;
		}


		return 0;
	}

};

enum
{
	READY,
	WAITING,
	HIT
};

class SawBladeB : public gtk::Behavior
{

public:
	SawBladeB() : _state(READY), _timeSinceHit(0), _delay(0.2f) {}


	void Update(const float& deltaTime) override
	{

		_timeSinceHit += deltaTime;
		if (_timeSinceHit > _delay)
		{
			SetColor(vec3(0.3f, 0.3f, 1.0f));
		}

	}

	void OnCollision(Entity& other) override
	{
		if (other.GetName() == "monkey")
		{
			if (_timeSinceHit > _delay)
			{
				other.Trigger(10);
				_state = WAITING;
				_timeSinceHit = 0;
			}
			else
			{
				SetColor(vec3(0.0f, 1.0f, 1.0f));
			}
		}
	}


private:

	float _state;
	float _timeSinceHit;
	float _delay;
};

enum class TowerSelection
{
	SHOOTER,
	LASER,
	SAW
};
class TowerMenuB : public gtk::Behavior
{
public:
	TowerSelection _selection;

private:
	
	Entity& _shooterIcon;
	Entity& _laserIcon;
	Entity& _sawIcon;

	Entity* _currentIcon;

public:
	TowerMenuB(Entity& shooter, Entity& laser, Entity& saw) 
		: _shooterIcon(shooter), _laserIcon(laser), _sawIcon(saw), _currentIcon(&shooter) {}

	void Start() override
	{
		_shooterIcon.Scale(1.2f);
	}

	void Update(const float& deltaTime) override
	{
		// Rotate the currently selected icon
		_currentIcon->Rot(vec3(0.0f, 90.0f * deltaTime, 0.0f), true);

		/// Menu Selection with bumpers //
#pragma region MenuSelectionBumpers

		if (App::GetController().CheckButton(XINPUT_GAMEPAD_RIGHT_SHOULDER) || App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT))
		{
			switch (_selection)
			{
			case TowerSelection::SHOOTER:
				_selection = TowerSelection::LASER;
				_currentIcon = &_laserIcon;
				_laserIcon.Scale(1.2f);
				_sawIcon.Scale(vec3(0.7f));
				_shooterIcon.Scale(0.7f);
				break;

			case TowerSelection::LASER:
				_selection = TowerSelection::SAW;
				_sawIcon.Scale(vec3(1.1f));
				_currentIcon = &_sawIcon;
				_laserIcon.Scale(0.7f);
				_shooterIcon.Scale(0.7f);
				break;

			case TowerSelection::SAW:
				_selection = TowerSelection::SHOOTER;
				_currentIcon = &_shooterIcon;
				_shooterIcon.Scale(1.2f);
				_sawIcon.Scale(vec3(0.7f));
				_laserIcon.Scale(0.7f);
				break;
			}

		}

		if (App::GetController().CheckButton(XINPUT_GAMEPAD_LEFT_SHOULDER) || App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT))
		{
			switch (_selection)
			{
			case TowerSelection::SHOOTER:
				_selection = TowerSelection::SAW;
				_sawIcon.Scale(vec3(1.1f));
				_currentIcon = &_sawIcon;
				_laserIcon.Scale(0.7f);
				_shooterIcon.Scale(0.7f);
				break;

			case TowerSelection::LASER:
				_selection = TowerSelection::SHOOTER;
				_currentIcon = &_shooterIcon;
				_shooterIcon.Scale(1.2f);
				_sawIcon.Scale(vec3(0.7f));
				_laserIcon.Scale(0.7f);
				break;

			case TowerSelection::SAW:
				_selection = TowerSelection::LASER;
				_currentIcon = &_laserIcon;
				_laserIcon.Scale(1.2f);
				_sawIcon.Scale(vec3(0.7f));
				_shooterIcon.Scale(0.7f);
				break;
			}

		}

#pragma endregion	


	}

	int Trigger(const int& code) override
	{
		return 0;
	}

	void OnCollision(Entity& other) override
	{

	}

};


class CursorB : public gtk::Behavior
{


private:

	TowerMenuB& _towerMenu;
	ObjectPool& _shooterPool;
	ObjectPool& _laserPool;
	Entity& _saw;
	NumUIRenderer& _moneyUI;
	NumUIRenderer& _sawPriceUI;
	NumUIRenderer& _hpRendUI;

	CursorState _state;
	int _numSaws;
	float _speed;
	vec3 _vel;
	vec3 _velGoal;

	int _money;
	int _shooterPrice;
	int _laserPrice;
	int _sawPrice;

	int _hp;

	void SpawnSawHelper()
	{
		// Purchase saw
		if (_money >= _sawPrice)
		{
			if (_numSaws == 0)
			{
				_saw.Trigger(1);
				_numSaws++;
				_money -= _sawPrice;
				_sawPrice += 10;
				
			}
			else if (_numSaws == 1)
			{
				_saw.Trigger(2);
				_numSaws++;
				_money -= _sawPrice;
				_sawPrice += 10;
			}
			else if (_numSaws == 2)
			{
				_saw.Trigger(3);
				_numSaws++;
				_money -= _sawPrice;
				_sawPriceUI.Active(false);
			}
			else
			{
				// made unhappy sound
			}

			// Update price
			_sawPriceUI.SetNum(_sawPrice);
		}
		else
		{
			// Make unhappy sound
		}
	}

public:
	CursorB(TowerMenuB& towerMenu, ObjectPool& shooterPool, ObjectPool& laserPool, Entity& saw, 
		NumUIRenderer& moneyUI, NumUIRenderer& sawPriceUI, NumUIRenderer& hpRendUI,
			const float& speed)
		: _towerMenu(towerMenu), _shooterPool(shooterPool), _laserPool(laserPool), _saw(saw), 
		_moneyUI(moneyUI), _sawPriceUI(sawPriceUI), _hpRendUI(hpRendUI),
		_state(ON), _numSaws(0), _speed(speed), _vel(), _velGoal(),
		_money(1000), _shooterPrice(5), _laserPrice(8), _sawPrice(10), _hp(50) {}

	void Update(const float& deltaTime) override
	{

		//// Movement ////
#pragma region Movement

		// Update saw position first 
		// so it lags behind a bit
		_saw.Pos(Pos());

		// Update velocity goal from input
		_velGoal.x = App::GetController().GetLeftThumbStickX() * _speed;
		_velGoal.y = App::GetController().GetLeftThumbStickY() * _speed;
		_velGoal.z = (App::GetController().GetRightTrigger() * _speed) - (App::GetController().GetLeftTrigger() * _speed);

		// Lerp current velocity to goal
		_vel = LERP(_vel, _velGoal, deltaTime * 20.0f);

		// Set position from velocity
		Pos(vec3(
			Pos().x + _vel.x * deltaTime,
			Pos().y + _vel.y * deltaTime,
			Pos().z + _vel.z * deltaTime
		));


		// Don't go out of bounds

		// X 
		if (Pos().x > 32.0f)
		{
			Pos(vec3(32.0f, Pos().y, Pos().z));
		}
		else if (Pos().x < -32.0f)
		{
			Pos(vec3(-32.0f, Pos().y, Pos().z));
		}

		// Y
		if (Pos().y > 25.0f)
		{
			Pos(vec3(Pos().x, 25.0f, Pos().z));
		}
		else if (Pos().y < -25.0f)
		{
			Pos(vec3(Pos().x, -25.0f, Pos().z));
		}

		// Z
		if (Pos().z > 25.0f)
		{
			Pos(vec3(Pos().x, Pos().y, 25.0f));
		}
		else if (Pos().z < -15.0f)
		{
			Pos(vec3(Pos().x, Pos().y, -15.0f));
		}




#pragma endregion

		/// Tower Control ///
		Entity* newShooter;
		Entity* newLaser;

		switch (_state)
		{
		case ON: // if not colliding with path or placed tower

			// GREEN
			SetColor(vec3(0.0f, 1.0f, 0.0f));

			// When buying a new tower
			if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
			{
				// Current selection
				switch (_towerMenu._selection)
				{
				case TowerSelection::SHOOTER:

					// Check if enough money
					if (_money >= _shooterPrice)
					{
						_money -= _shooterPrice;

						newShooter = &_shooterPool.Create();
						newShooter->Pos(Pos());
						newShooter->Trigger(-1);
						
					}
					break;

				case TowerSelection::LASER:

					if (_money >= _laserPrice)
					{
						_money -= _laserPrice;

						newLaser = &_laserPool.Create();
						newLaser->Pos(Pos());
						newLaser->Trigger(-1);
					}
					break;
				
				case TowerSelection::SAW:

					SpawnSawHelper();

					break;
				}


			}
			break;
		case OFF:

			if (App::GetController().CheckButton(XINPUT_GAMEPAD_A))
			{
				
				if (_towerMenu._selection == TowerSelection::SAW)
				{
					SpawnSawHelper();
				}
				else
				{
					// Make unhappy sound
				}
			}
			break;
		}

		// Reset state, it's set to off in on collision
		_state = ON;

		// Update the money UI
		_moneyUI.SetNum(_money);

	}

	int Trigger(const int& code) override
	{
		// if mokey died
		if (code > 0)
		{
			//Get Money
			_money += code;
		}
		else // Monkey got to the end
		{
			// Update Health
			_hp += code;

			if (_hp > 0)
			{
				_hpRendUI.SetNum(_hp);
			}
			else
			{
				// GAME OVER sad
				
				_hpRendUI.SetNum(0);
				int i = 0;

			}

		}



		return 0;
	}


	void OnCollision(Entity& other) override
	{
		_state = OFF;
		SetColor(vec3(1.0f, 0.0f, 0.0f));
	}


};
