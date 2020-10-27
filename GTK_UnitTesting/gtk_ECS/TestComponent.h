#pragma once

#include "gtk/gtk.h"

class CompTemplate : public gtk::Component
{
public:
	CompTemplate(gtk::Entity* const entity, const gtk::CompGroup& compGroup) : Component(entity, compGroup) {}

	void Start() override
	{

	}

	void Update() override
	{

	}


private:

};

class SceneSwitcherComp : public gtk::Component
{
public:
	SceneSwitcherComp(gtk::Entity* const entity, const gtk::CompGroup& compGroup, gtk::Scene* const scene, std::string nextScene)
		: Component(entity, compGroup), m_SwitchScene(false), m_NextScene(nextScene), _Scene(scene) {}

	bool m_SwitchScene;


	void Start() override
	{

	}

	void Update() override
	{
		if (m_SwitchScene)
		{
			_Scene->SwitchScene(m_NextScene);
		}
	}


private:

	gtk::Scene* const _Scene;
	std::string m_NextScene;
};

class VectorTest : public gtk::Component
{
public:

	VectorTest(gtk::Entity* const entity, const gtk::CompGroup& compGroup, const bool& aOs, SceneSwitcherComp* const sceneSwitcher) 
		: Component(entity, compGroup), addOrSub(aOs), ValueToAdd(5), vec(), UpdateCount(0), m_SSC(sceneSwitcher)
	{
		if (addOrSub)
		{
			vec = { 0, 5 };
		}
		else
		{
			vec = { 0, -5 };
		}
	}

	void Start() override
	{
	}

	void Update() override
	{
		if (addOrSub)
		{
			vec += ValueToAdd;
		}
		else
		{
			vec -= ValueToAdd;
		}

		UpdateCount++;


		if (UpdateCount == 1)
		{
			CheckEquals(5, 10);
		}

		if (UpdateCount == 10)
		{
			CheckEquals(50, 55);
		}

		if (UpdateCount == 100)
		{
			CheckEquals(500, 505);
		}

		if (UpdateCount == 1000)
		{
			CheckEquals(5000, 5005);

			m_SSC->m_SwitchScene = true;
		}
	
	}

private:

	bool addOrSub;
	
	MTYPE ValueToAdd;
	gtk::vec2 vec;

	int UpdateCount;

	SceneSwitcherComp* const m_SSC;

	void CheckEquals(MTYPE x, MTYPE y)
	{
		if (addOrSub)
		{
			EXPECT_EQ(vec.x, x);
			EXPECT_EQ(vec.y, y);
		}
		else
		{
			EXPECT_EQ(vec.x, -x);
			EXPECT_EQ(vec.y, -y);
		}
	}

};



class ToggleComp : public gtk::Component
{
public:
	ToggleComp(gtk::Entity* const entity, const gtk::CompGroup& compGroup) : Component(entity, compGroup) {}

	void Start() override
	{

	}

	void Update() override
	{

	}


private:

};