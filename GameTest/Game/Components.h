#pragma once
#include "gtk/gtk.h"
#include "app/app.h"
#include "gtk/gtkMath.hpp"
#include <math.h>
#include "enums.h"
#include <string>


// For tweaking gameplay

// Wave Countdown
#define COUNTDOWN_TIME 8.0f

// Player Stats
#define STARTING_MONEY 16
#define STARTING_HP    20

// Shooter
#define SHOOTER_PRICE 6
#define SHOOTER_STR  1
#define SHOOTER_RATE 0.3f
#define BULLET_SPD   10.0f
#define SHOOTER_RNG  6.7f
#define MAX_SHOOTERS 20

// Laser
#define LASER_PRICE 10
#define LASER_STR	2
#define LASER_RATE  0.5f
#define MAX_LASERS  20

// Saw
#define SAW_STR		2
#define SAW_RATE	0.3f
#define SAW_PRICE_1 12
#define SAW_PRICE_2 16
#define SAW_PRICE_3 20

// Standard Money
#define MONK_COLOR vec3(0.8f, 0.7f, 0.3f)
#define MONK_SIZE  1.5f
#define MONK_SPD   2.2f
#define MONK_HP	   12
#define MONK_WORTH 1
#define MONK_STR   3
#define MONK_SPIN  50.0f

// Brute Monkey
#define BRUTE_COLOR vec3(0.2f, 0.3f, 0.8f)
#define BRUTE_SIZE  3.0f
#define BRUTE_SPD   1.8f
#define BRUTE_HP	65
#define BRUTE_WORTH 2
#define BRUTE_STR   3
#define BRUTE_SPIN  20.0f

// Tiny Monkey
#define TINY_COLOR vec3(0.2f, 0.7f, 0.3f)
#define TINY_SIZE  1.0f
#define TINY_SPD   3.0f
#define TINY_HP	   8
#define TINY_WORTH 1
#define TINY_STR   1
#define TINY_SPIN -200.0f

// Boss Monkey
#define BOSS_COLOR vec3(1.0f, 0.2f, 0.2f)
#define BOSS_SIZE  5.0f
#define BOSS_SPD   1.0f
#define BOSS_HP	   400
#define BOSS_WORTH 5
#define BOSS_STR   5
#define BOSS_SPIN 10.0f

// Boss Monkey
#define MEGA_COLOR vec3(1.0f, 0.1f, 1.0f)
#define MEGA_SIZE  7.0f
#define MEGA_SPD   0.8f
#define MEGA_HP	   2500
#define MEGA_WORTH 20
#define MEGA_STR   10
#define MEGA_SPIN  8.0f


using namespace gtk;

class BehaviorTemplate : public gtk::Behavior
{

public:
	BehaviorTemplate() {}

	// Called before the first update
	void Start() override {}

	void Update(const float& deltaTime) override {}

	// Use for sending messages through entities
	int Trigger(const int& code) override
	{
		return 0;
	}

	void OnCollision(Entity& other) override {}

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

class BulletB : public gtk::Behavior
{

private:

	vec3 _dir;
	vec3 _vel;
	float _speed;
	bool _Dead;

public:
	BulletB() :_dir(), _vel(), _speed(BULLET_SPD), _Dead(true) {}

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
			other.Trigger(SHOOTER_STR);
		}
	}

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

enum MonkeyTypes
{
	STANDARD = -1,
	BRUTE = -2,
	TINY = -3,
	BOSS = -4,
	MEGA = -5

};

class MonkeyB : public gtk::Behavior
{

private:
	
	Entity& _cursor;

	float _speed;
	int _health;
	int _worth;
	int _strength;
	float _spinSpd;

	std::vector<vec3> _path;
	int _currentNode;

	float _T;

public:
	MonkeyB(Entity& cursor, std::vector<vec3> path)
		: _cursor(cursor), _speed(1.0f), _health(1), _worth(1), _strength(1), _spinSpd(1), _path(path), _currentNode(0) {}

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

		// Spin
		Rot(vec3(0.0f, _spinSpd * deltaTime, 0.0f), true);

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
				SetColor(MONK_COLOR);
				Scale(MONK_SIZE);
				_speed    = MONK_SPD;
				_health   = MONK_HP;
				_worth    = MONK_WORTH;
				_strength = MONK_STR;
				_spinSpd  = MONK_SPIN;
				break;

			case BRUTE:
				// Spawn big blue monkey
				SetColor(BRUTE_COLOR);
				Scale(BRUTE_SIZE);
				_speed    = BRUTE_SPD;
				_health   = BRUTE_HP;
				_worth    = BRUTE_WORTH;
				_strength = BRUTE_STR;
				_spinSpd =  BRUTE_SPIN;
				break;

			case TINY:
				// Spawn big blue monkey
				SetColor(TINY_COLOR);
				Scale(TINY_SIZE);
				_speed    = TINY_SPD;
				_health   = TINY_HP;
				_worth    = TINY_WORTH;
				_strength = TINY_STR;
				_spinSpd  = TINY_SPIN;
				break;

			case BOSS:
				// Spawn big blue monkey
				SetColor(BOSS_COLOR);
				Scale(BOSS_SIZE);
				_speed    = BOSS_SPD;
				_health   = BOSS_HP;
				_worth    = BOSS_WORTH;
				_strength = BOSS_STR;
				_spinSpd =  TINY_SPIN;
				break;

			case MEGA:
				// Spawn big blue monkey
				SetColor(MEGA_COLOR);
				Scale(MEGA_SIZE);
				_speed = MEGA_SPD;
				_health = MEGA_HP;
				_worth = MEGA_WORTH;
				_strength = MEGA_STR;
				_spinSpd = MEGA_SPIN;
				break;
			}
		}
		

		return 0;
	}

	void OnCollision(Entity& other) override
	{


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
	int numMonkeys = 0;
	std::vector<SpawnGroup> _spawnList;

	// Count, Type of monkey, spawn delay between each
	void AddToWave(const int& count, const int& monkeyType, const float& delay)
	{
		numMonkeys += count;
		_spawnList.push_back({ count, monkeyType, delay });
	}

};

enum GameState
{
	SPAWNING,
	WAIT,
	COUNTDOWN,
	WIN,
	LOSE
};

class BarrelOfMonkeysB : public gtk::Behavior
{

private:

	Entity& _loseText;
	Entity& _winText;
	Entity& _banana;
	Entity& _giantMonkey;
	Entity& _barrel;
	Entity& _cursor;
	ObjectPool& _monkeyPool;
	NumUIRenderer& _waveUIRend;

	std::vector<Wave> _waves;
	int _state;
	float _spawnTimer;
	float _timeSinceSpawn;

	int _waveIndex;
	int _spawnIndex;
	int _spawnCount;

	float _countdown;

public:

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

	int GetCountInWave()
	{
		int i = _waves[_waveIndex].numMonkeys;
		return i;
	}


public:
	BarrelOfMonkeysB(Entity& loseText, Entity& winText, 
		Entity& banana, Entity& giantMonkey, Entity& barrel, Entity& cursor, 
		NumUIRenderer& waveUIRend, std::vector<Wave> waves, ObjectPool& monkeyPool) :
		_loseText(loseText), _winText(winText), 
		_banana(banana), _giantMonkey(giantMonkey),
		_barrel(barrel), _cursor(cursor), _waveUIRend(waveUIRend),_monkeyPool(monkeyPool), _waves(waves),
		_state(COUNTDOWN), _spawnTimer(2.0f), _timeSinceSpawn(0), _waveIndex(0), _spawnIndex(0), _spawnCount(0), _countdown(COUNTDOWN_TIME) {}


	void Update(const float& deltaTime) override
	{
		float time;
		int type;
		int i;

		switch (_state)
		{
		case SPAWNING:

			_barrel.Rot(vec3(0.0f, deltaTime * 50.f, 0.0f), true);

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
						
						_spawnIndex = 0;

						// End of wave
						// Wait for monkeys to die
						_state = WAIT;
						_barrel.SetColor(vec3(0.5f, 0.2f, 0.1f));
							
					}
				}

			}


			break;

		case WAIT:
			
			// All monkeys in wave have spawned, wait for last monkey to die
			i = 0;
			
			break;

		case COUNTDOWN:

			_countdown -= deltaTime;

			_waveUIRend.SetNum(_countdown);
			
			if (_countdown <= 0.0f)
			{
				_state = SPAWNING;
				_barrel.SetColor(vec3(0.8f, 0.5f, 0.25f));

				_countdown = COUNTDOWN_TIME;
				// Update the UI
				_waveUIRend.SetNum(_waveIndex + 1);

				// Tell cursor new round started
				_cursor.Trigger(0);
			}

			break;


		case WIN:

			// Move banana to center
			_banana.Pos(LERP(_banana.Pos(), vec3(0.0f, 0.22f, -20.5f), deltaTime * 2));

			// When at center show text and poll for input
			if (_banana.Pos() == vec3(0.0f, 0.22f, -20.5f))
			{
				_winText.Active(true);
				if (App::GetController().CheckButton(XINPUT_GAMEPAD_A))
				{
					SwitchScene("MainMenu");
				}
			}



			break;
		
		case LOSE:		
			_giantMonkey.Pos(LERP(_giantMonkey.Pos(), vec3(0.0f, 0.22f, -23.5f), deltaTime * 2));

			if (_giantMonkey.Pos() == vec3(0.0f, 0.22f, -23.5f))
			{
				_loseText.Active(true);
				if (App::GetController().CheckButton(XINPUT_GAMEPAD_A))
				{
					SwitchScene("MainMenu");
				}

			}



			break;

		}
	}

	int Trigger(const int& code) override
	{

		// Wave has ended 
		if (code == -1)
		{
			// If more waves
			if (_waveIndex < _waves.size() -1 )
			{
				if(_state != LOSE && _state != WIN)
				{
					// Start countdown
					_state = COUNTDOWN;
					_waveIndex++;
				}

			}
			else // If no more waves
			{
				// WIN!
				if (_state != LOSE)
				{
					_state = WIN;
				}
			}

		}
		else if (code == -2) // Cursor sends -2 when HP is 0
		{
			if (_state != WIN)
			{
				_state = LOSE;
				_giantMonkey.Active(true);
			}
		}


		return 0;
	}


};

class ShooterB : public gtk::Behavior
{

private:

	Entity* _target;
	ObjectPool& _bulletPool;

	float _shootDelay;
	float _timeSinceShot;

public:
	ShooterB(ObjectPool& bulletPool) : _bulletPool(bulletPool), _shootDelay(SHOOTER_RATE), _timeSinceShot(0) {}

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
			float r = SHOOTER_RNG;

			// If they collide
			if ((pos - tPos).Dot((pos - tPos)) <= (r+r)*(r+r) && _target->Active())
			{
				// Check shoot delay
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

enum LaserState
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
	LaserB(LineRenderer& lineRend, RayCollider& rayCol, SphereCollider& rangeCol)
		: _target(nullptr), _lineRend(lineRend), _rayCol(rayCol), _rangeCol(rangeCol),
		_shootDelay(LASER_RATE), _timeSinceShot(0), _state(SEARCHING)  {}

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
			end = dir * 3;

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

				other.Trigger(LASER_STR);

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

enum SawState
{
	READY,
	WAITING,
	HIT
};

class SawBladeB : public gtk::Behavior
{

public:
	SawBladeB() : _state(READY), _timeSinceHit(0), _delay(SAW_RATE) {}


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
				other.Trigger(SAW_STR);
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

	BarrelOfMonkeysB& _barrelOfMonkeys;
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
	int _deadMonkeyCount;

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
				_sawPrice = SAW_PRICE_2;
				
			}
			else if (_numSaws == 1)
			{
				_saw.Trigger(2);
				_numSaws++;
				_money -= _sawPrice;
				_sawPrice = SAW_PRICE_3;
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
	CursorB(BarrelOfMonkeysB& barrelOfMonkeys, TowerMenuB& towerMenu, ObjectPool& shooterPool, ObjectPool& laserPool, Entity& saw, 
		NumUIRenderer& moneyUI, NumUIRenderer& sawPriceUI, NumUIRenderer& hpRendUI,
			const float& speed)
		: _barrelOfMonkeys(barrelOfMonkeys), _towerMenu(towerMenu), _shooterPool(shooterPool), _laserPool(laserPool), _saw(saw), 
		_moneyUI(moneyUI), _sawPriceUI(sawPriceUI), _hpRendUI(hpRendUI),
		_state(ON), _numSaws(0), _speed(speed), _vel(), _velGoal(),
		_money(STARTING_MONEY), _shooterPrice(SHOOTER_PRICE), _laserPrice(LASER_PRICE), _sawPrice(SAW_PRICE_1), _hp(STARTING_HP), _deadMonkeyCount(0) {}

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
		// Track dying monkeys with 

		// A code of 0 means a new round has started

		//if (code == 0)
		//{
		//	_deadMonkeyCount = 0;
		//}

		// if monkey died
		if (code > 0)
		{
			_deadMonkeyCount++;

			//Get Money
			_money += code;
		}
		else if (code < 0) // Monkey got to the end
		{
			_deadMonkeyCount++;

			// Update Health
			_hp += code;

			if (_hp > 0)
			{
				// Set health UI
				_hpRendUI.SetNum(_hp);
			}
			else
			{
				// GAME OVER sad
				_barrelOfMonkeys.Trigger(-2);
				_hpRendUI.SetNum(0);
				int i = 0;

			}

		}

		int waveCount = _barrelOfMonkeys.GetCountInWave();
		if (_deadMonkeyCount >= waveCount)
		{
			// Wave has ended
			_deadMonkeyCount = 0;
			_barrelOfMonkeys.Trigger(-1);
		}


		return 0;
	}


	void OnCollision(Entity& other) override
	{
		_state = OFF;
		SetColor(vec3(1.0f, 0.0f, 0.0f));
	}


};

class MenuMonkeyB : public gtk::Behavior
{

private:

	
	float _speed;
	float _spinSpd;

	std::vector<vec3> _path;
	int _currentNode;
	float _T;

public:
	MenuMonkeyB(int startNode, float speed, float spin, std::vector<vec3> path)
		: _speed(speed),_spinSpd(spin), _path(path), _currentNode(startNode) {}

	void Start() override
	{
	}

	void Update(const float& deltaTime) override
	{

		// Moving from node to node
		_T += deltaTime * _speed;

		// Spin
		Rot(vec3(0.0f, _spinSpd * deltaTime, 0.0f), true);

		// If at next node
		if (_T >= 1.0f)
		{
			_T = 0;
			// If not at the end of path
			if (_currentNode != _path.size() - 2)
			{
				// Next node
				_currentNode++;
			}
			else // End
			{
				// Start again
				_currentNode = 0;
			}
		}

		Pos(LERP(_path[_currentNode], _path[_currentNode + 1], _T));

	}


};

class MenuSelectorB : public gtk::Behavior
{
private:
	
	Entity& _text1;
	Entity& _text2;

	bool _state;
	float _spin;

public:
	MenuSelectorB(Entity& text1, Entity& text2, float spin)
	: _text1(text1), _text2(text2), _state(true), _spin(spin) {}

	// Called before the first update
	void Start() override {}

	void Update(const float& deltaTime) override
	{
		Rot(vec3(0.0f, _spin * deltaTime, 0.0f), true);

		if (_state)
		{
			// Set Pos
			Pos(vec3(-4.5f, 2.0f, 0.0f));
			if (App::GetController().CheckButton(XINPUT_GAMEPAD_A))
			{
				SwitchScene("L1");
			}
		}
		else
		{
			// Set Pos
			Pos(vec3(4.0f, 2.0f, 0.0f));
			
			if (App::GetController().CheckButton(XINPUT_GAMEPAD_A))
			{
				SwitchScene("L2");
			}

		}
		
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT)
			|| App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT))
		{
			_state = !_state;
		}

	}

};