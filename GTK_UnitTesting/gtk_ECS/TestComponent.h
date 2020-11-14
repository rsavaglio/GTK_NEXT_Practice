#pragma once

#include "gtk/gtk.h"

class CompTemplate : public gtk::Behavior
{
public:
	CompTemplate() {}

	void Start() override
	{

	}

	void Update(const float& deltaTime) override
	{

	}

	int Trigger(const int& code) override
	{

	}


private:

};

class SceneSwitcherComp : public gtk::Behavior
{
public:
	SceneSwitcherComp(gtk::Scene& scene, std::string nextScene)
		: m_NextScene(nextScene), _Scene(scene) {}

	void Start() override
	{

	}

	void Update(const float& deltaTime) override
	{
	}

	int Trigger(const int& code) override
	{

		_Scene.SwitchScene(m_NextScene);

		return 1;
	}


private:

	gtk::Scene& _Scene;
	std::string m_NextScene;
};

class VectorTest : public gtk::Behavior
{
public:

	VectorTest(const bool& aOs, Behavior& sceneSwitcher) 
		: addOrSub(aOs), ValueToAdd(5), vec(), UpdateCount(0), m_SSC(sceneSwitcher)
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

	void Update(const float& deltaTime) override
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

			m_SSC.Trigger(1);
		}
	
	}

	int Trigger(const int& code) override
	{

		return 0;
	}

private:

	bool addOrSub;
	
	MTYPE ValueToAdd;
	gtk::vec2 vec;

	int UpdateCount;

	Behavior& m_SSC;

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



class TogglerComp : public gtk::Behavior
{

public:
	TogglerComp(
		gtk::Entity& entityToToggle, gtk::Behavior& compToToggle, gtk::Renderer& rendToToggle)
		: m_UpdateCount(0), m_EntToToggle(entityToToggle), m_CompToToggle(compToToggle), m_RendToToggle(rendToToggle) {}

	void Start() override
	{

	}

	void Update(const float& deltaTime) override
	{
		if (m_UpdateCount == 10)
		{
			m_CompToToggle.Active(false);
			
			// Should do nothing
			m_CompToToggle.Active(false);
			m_RendToToggle.Active(true);

		}

		if (m_UpdateCount == 20)
		{
			m_CompToToggle.Active(true);
			m_RendToToggle.Active(false);

			// Should do nothing
			m_CompToToggle.Active(true);
			m_RendToToggle.Active(false);
		}


		if (m_UpdateCount == 30)
		{
			m_RendToToggle.Active(true);
		}

		if (m_UpdateCount == 40)
		{
			// Toggle entity off while comp and rend are active

			// Toggle Entity
			m_EntToToggle.Active(false);
			m_EntToToggle.Active(false); // Should do nothing
		}

		if (m_UpdateCount == 50)
		{
			// Toggle entity off while comp and rend are active

			// Toggle Entity
			m_EntToToggle.Active(true);
			m_EntToToggle.Active(true); // Should do nothing

		}

		if (m_UpdateCount == 60)
		{

			// Toggle Entity
			m_EntToToggle.Active(false);

			// Toggle Comp
			m_CompToToggle.Active(false);

		}

		if (m_UpdateCount == 70)
		{

			// Toggle Entity
			m_EntToToggle.Active(true);
		}


		if (m_UpdateCount == 80)
		{
			// Toggle Comp
			m_CompToToggle.Active(true);
		}

		if (m_UpdateCount == 90)
		{
			// Toggle Comp
			m_CompToToggle.Active(false);

			// Toggle Entity
			m_EntToToggle.Active(false);
		}

		if (m_UpdateCount == 100)
		{

			// Toggle Entity
			m_EntToToggle.Active(true);
		}

		if (m_UpdateCount == 110)
		{
			// Toggle Comp
			m_CompToToggle.Active(true);
		}

		if (m_UpdateCount == 120)
		{
			m_EntToToggle.Active(false);

			m_RendToToggle.Active(false);
		}

		if (m_UpdateCount == 130)
		{
			m_EntToToggle.Active(true);
		}

		if (m_UpdateCount == 140)
		{
			m_RendToToggle.Active(true);
		}

		if (m_UpdateCount == 150)
		{
			m_RendToToggle.Active(false);

			m_EntToToggle.Active(false);
		}

		if (m_UpdateCount == 160)
		{
			m_EntToToggle.Active(true);
		}

		if (m_UpdateCount == 170)
		{
			m_RendToToggle.Active(true);
		}


		m_UpdateCount++;
	}

	int Trigger(const int& code) override
	{

		return m_UpdateCount;
	}

private:
	unsigned int m_UpdateCount;

	gtk::Entity& m_EntToToggle;
	gtk::Behavior& m_CompToToggle;
	gtk::Renderer& m_RendToToggle;
};

class ToggleMeComp : public gtk::Behavior
{
public:
	ToggleMeComp() : m_UpdateCount(0) {}

	void Start() override
	{

	}

	void Update(const float& deltaTime) override
	{
		m_UpdateCount++;
	}

	int Trigger(const int& code) override
	{

		return 0;
	}

	unsigned int m_UpdateCount;

};