#include "pch.h"
#include "gtk/Math.h"

class Vec4_F : public ::testing::Test
{
protected:

	Vec4_F() : a(1.0f), b(0.5f), c(1.0f, 2.0f, 3.0f, 4.0f), d(-1.0f, -2.0f, -3.0f, -4.0f), t(2) {}
	~Vec4_F() {}

	void SetUp() override {}
	void TearDown() override {}

	gtk::vec4 a;
	gtk::vec4 b;
	gtk::vec4 c;
	gtk::vec4 d;
	gtk::vec4 t;
};

TEST_F(Vec4_F, vec4_boolOperators)
{

}


TEST_F(Vec4_F, vec4_constructors)
{

}

TEST_F(Vec4_F, vec4_Add)
{

}


TEST_F(Vec4_F, vec4_Subtract)
{

}

TEST_F(Vec4_F, vec4_Multiply)
{

}

TEST_F(Vec4_F, vec4_Divide)
{

}

TEST_F(Vec4_F, vec4_IncrementDecrement)
{

}

TEST_F(Vec4_F, vec4_DotCross)
{

}





