#pragma once

#include "gtk/gtk.h"

class VectorTest : public gtk::Component
{
public:

	VectorTest(gtk::Entity* const entity, const gtk::CompGroup& compGroup, const bool& aOs) : Component(entity, compGroup), addOrSub(aOs), ValueToAdd(5), vec(), UpdateCount(0)
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
		}
	
	}

private:

	bool addOrSub;
	
	MTYPE ValueToAdd;
	gtk::vec2 vec;

	int UpdateCount;

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