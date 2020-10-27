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

	TestGame a;

};

TEST_F(TestGame_F, Making_A_Game)
{

	TestGame testGame;
	testGame.Init();

	testGame.Start();

	int loopCount = 0;
	while (loopCount++ < 5000)
	{
		testGame.Update();
	}

}


