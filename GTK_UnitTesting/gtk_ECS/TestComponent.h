#pragma once
#include "gtk/gtk.h"


class TestComponent : public gtk::Component
{
public:

	const unsigned int _id;

	TestComponent(const gtk::Entity& entity) : _id(entity._id)
	{
		
	}

	void Start() override
	{

	}

	void Update() override
	{

	}

};