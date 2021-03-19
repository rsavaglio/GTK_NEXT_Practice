#pragma once
#include "gtk/gtk.h"
#include "app\app.h"
#include "gtk/gtkMath.hpp"
#include <math.h>

using namespace gtk;

class SphereCollider : public gtk::Collider
{

public:
	SphereCollider(float radiusMod = 1.0f) : _radiusMod(radiusMod) {}

	void UpdateData() override
	{
		// Doesn't work great with children objects
		_radius = Scale().x > Scale().y ? Scale().x : Scale().y;
		_radius = _radius > Scale().z ? _radius : Scale().z;

		_radius *= _radiusMod;
		_center = Pos();
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