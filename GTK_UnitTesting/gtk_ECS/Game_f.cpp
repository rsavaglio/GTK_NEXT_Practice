#include "pch.h"
#include "TestGame.h"


using namespace gtk;

class TestGame_F : public ::testing::Test
{
protected:

	TestGame_F() : a() {}
	~TestGame_F() {}

	void SetUp() override {}
	void TearDown() override {}

	SceneSwitchingGame a;

};

TEST_F(TestGame_F, SceneSwitching)
{

	SceneSwitchingGame ssGame;
	ssGame.Init();

	ssGame.Start();

	int loopCount = 0;
	while (loopCount++ < 5000)
	{
		ssGame.Update(1);
		ssGame.Render();
	}

}

TEST_F(TestGame_F, TogglingEntities)
{

	ToggleGame tGame;
	tGame.Init();

	tGame.Start();

	int loopCount = 0;
	while (loopCount++ < 5000)
	{
		tGame.Update(1);
		tGame.Render();
	}

}


