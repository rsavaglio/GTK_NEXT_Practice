#pragma once

#include "gtk/gtk.h"

class CompTemplate : public gtk::Component
{
public:
	CompTemplate(gtk::Entity* const entity, const gtk::CompGroup& compGroup) : Component(entity, compGroup) {}

	void Start() override
	{

	}

	void Update(float deltaTime) override
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

	void Update(float deltaTime) override
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

	void Update(float deltaTime) override
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



class TogglerComp : public gtk::Component
{

public:
	TogglerComp(gtk::Entity* const entity, const gtk::CompGroup& compGroup,
		gtk::Scene* const scene, gtk::Entity* const entityToToggle, gtk::Component* const compToToggle, gtk::Renderer* const rendToToggle)
		: Component(entity, compGroup), m_Scene(scene), m_UpdateCount(0), m_EntToToggle(entityToToggle), m_CompToToggle(compToToggle), m_RendToToggle(rendToToggle) {}

	void Start() override
	{

	}

	void Update(float deltaTime) override
	{
		if (m_UpdateCount == 10)
		{
			m_Scene->ToggleComponent(m_CompToToggle, false);
			
			// Should do nothing
			m_Scene->ToggleComponent(m_CompToToggle, false);
			m_Scene->ToggleRenderer(m_RendToToggle, true);

		}

		if (m_UpdateCount == 20)
		{
			m_Scene->ToggleComponent(m_CompToToggle, true);
			m_Scene->ToggleRenderer(m_RendToToggle, false);

			// Should do nothing
			m_Scene->ToggleComponent(m_CompToToggle, true);
			m_Scene->ToggleRenderer(m_RendToToggle, false);
		}


		if (m_UpdateCount == 30)
		{
			m_Scene->ToggleRenderer(m_RendToToggle, true);
		}

		if (m_UpdateCount == 40)
		{
			// Toggle entity off while comp and rend are active

			// Toggle Entity
			m_Scene->ToggleEntity(m_EntToToggle, false);
			m_Scene->ToggleEntity(m_EntToToggle, false); // Should do nothing
		}

		if (m_UpdateCount == 50)
		{
			// Toggle entity off while comp and rend are active

			// Toggle Entity
			m_Scene->ToggleEntity(m_EntToToggle, true);
			m_Scene->ToggleEntity(m_EntToToggle, true); // Should do nothing

		}

		if (m_UpdateCount == 60)
		{

			// Toggle Entity
			m_Scene->ToggleEntity(m_EntToToggle, false);

			// Toggle Comp
			m_Scene->ToggleComponent(m_CompToToggle, false);

		}

		if (m_UpdateCount == 70)
		{

			// Toggle Entity
			m_Scene->ToggleEntity(m_EntToToggle, true);
		}


		if (m_UpdateCount == 80)
		{
			// Toggle Comp
			m_Scene->ToggleComponent(m_CompToToggle, true);
		}

		if (m_UpdateCount == 90)
		{
			// Toggle Comp
			m_Scene->ToggleComponent(m_CompToToggle, false);

			// Toggle Entity
			m_Scene->ToggleEntity(m_EntToToggle, false);
		}

		if (m_UpdateCount == 100)
		{

			// Toggle Entity
			m_Scene->ToggleEntity(m_EntToToggle, true);
		}

		if (m_UpdateCount == 110)
		{
			// Toggle Comp
			m_Scene->ToggleComponent(m_CompToToggle, true);
		}

		if (m_UpdateCount == 120)
		{
			m_Scene->ToggleEntity(m_EntToToggle, false);

			m_Scene->ToggleRenderer(m_RendToToggle, false);
		}

		if (m_UpdateCount == 130)
		{
			m_Scene->ToggleEntity(m_EntToToggle, true);
		}

		if (m_UpdateCount == 140)
		{
			m_Scene->ToggleRenderer(m_RendToToggle, true);
		}

		if (m_UpdateCount == 150)
		{
			m_Scene->ToggleRenderer(m_RendToToggle, false);

			m_Scene->ToggleEntity(m_EntToToggle, false);
		}

		if (m_UpdateCount == 160)
		{
			m_Scene->ToggleEntity(m_EntToToggle, true);
		}

		if (m_UpdateCount == 170)
		{
			m_Scene->ToggleRenderer(m_RendToToggle, true);
		}


		m_UpdateCount++;
	}

private:
	unsigned int m_UpdateCount;

	gtk::Scene* const m_Scene;
	gtk::Entity* const m_EntToToggle;
	gtk::Component* const m_CompToToggle;
	gtk::Renderer* const m_RendToToggle;


};

class ToggleMeComp : public gtk::Component
{
public:
	ToggleMeComp(gtk::Entity* const entity, const gtk::CompGroup& compGroup) : Component(entity, compGroup), m_UpdateCount(0) {}

	void Start() override
	{

	}

	void Update(float deltaTime) override
	{
		m_UpdateCount++;
	}

	unsigned int m_UpdateCount;

};