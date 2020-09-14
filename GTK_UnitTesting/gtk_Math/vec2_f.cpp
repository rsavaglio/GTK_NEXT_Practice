#include "pch.h"
#include "gtk/gtkMath.hpp"

class Vec2_F : public ::testing::Test
{
protected:

	 Vec2_F() : a(15), b(0.005f), c(1.0f, -1.0f), d(99.9f, -99.9f), t(2) {}
	~Vec2_F() {}

	void SetUp() override {}
	void TearDown() override {}

	gtk::vec2 a;
	gtk::vec2 b;
	gtk::vec2 c;
	gtk::vec2 d;
	gtk::vec2 t;
};

TEST_F(Vec2_F, vec2_boolOperators)
{
	gtk::vec2 e(99.9f, -99.9f);
	EXPECT_EQ(d, e);
	EXPECT_TRUE(d == e);
	EXPECT_FALSE(d == a);


	EXPECT_FALSE(d != e);
	EXPECT_TRUE(d != a);

}

TEST_F(Vec2_F, vec2_constructors)
{
	gtk::vec2 x;
	gtk::vec2 y(0.005f);
	gtk::vec2 z(1.0f, -1.0f);
	gtk::vec2 w = { 99.9f, -99.9f };

	EXPECT_FLOAT_EQ(x.x, 0.0f);
	EXPECT_FLOAT_EQ(x.y, 0.0f);

	EXPECT_FLOAT_EQ(y.values[0], 0.005f);
	EXPECT_FLOAT_EQ(y.values[1], 0.005f);

	EXPECT_FLOAT_EQ(z.r,  1.0f);
	EXPECT_FLOAT_EQ(z.g, -1.0f);
	
	EXPECT_FLOAT_EQ(w.u,	99.9f);
	EXPECT_FLOAT_EQ(w.v, -99.9f);
}

TEST_F(Vec2_F, vec2_Add)
{
	// Add
	a.Add(a);
	EXPECT_FLOAT_EQ(a.x, 30);
	EXPECT_FLOAT_EQ(a.y, 30);

	b.Add(b);
	EXPECT_FLOAT_EQ(b.x, 0.01);
	EXPECT_FLOAT_EQ(b.y, 0.01);

	// +=
	a += a;
	EXPECT_FLOAT_EQ(a.x, 60);
	EXPECT_FLOAT_EQ(a.y, 60);

	// +
	gtk::vec2 e = d + d;
	gtk::vec2 f(99.9 + 99.9, -99.9 + -99.9);
	EXPECT_EQ(e, f);
	
}

TEST_F(Vec2_F, vec2_AddScalar)
{
	// Add
	a.AddScalar(15.0f);
	EXPECT_FLOAT_EQ(a.x, 30);
	EXPECT_FLOAT_EQ(a.y, 30);

	b.AddScalar(1.005);
	EXPECT_FLOAT_EQ(b.x, 1.01);
	EXPECT_FLOAT_EQ(b.y, 1.01);
	
	c.AddScalar(-10);
	EXPECT_FLOAT_EQ(c.x, -9.0f);
	EXPECT_FLOAT_EQ(c.y, -11.0f);

	// +=
	a += a;
	EXPECT_FLOAT_EQ(a.x, 60);
	EXPECT_FLOAT_EQ(a.y, 60);

	// +
	gtk::vec2 e(80);
	EXPECT_EQ(a + 20, e);

}

TEST_F(Vec2_F, vec2_Subtract)
{
	// -=
	a -= c;
	EXPECT_FLOAT_EQ(a.x, 14.0f);
	EXPECT_FLOAT_EQ(a.y, 16.0f);

	d -= 10;
	EXPECT_FLOAT_EQ(d.x, 89.9f);
	EXPECT_FLOAT_EQ(d.y, -109.9f);

	// -
	gtk::vec2 e(13.995f, 15.995f);
	EXPECT_TRUE( (a - b) == e);

	gtk::vec2 f(69.0f, -130.8f);
	EXPECT_TRUE( d - 20.9 == f);

}

TEST_F(Vec2_F, vec2_Multiply)
{
	// *=
	a *= t;
	EXPECT_FLOAT_EQ(a.x, 30.0f);
	EXPECT_FLOAT_EQ(a.y, 30.0f);

	c *= 20;
	EXPECT_FLOAT_EQ(c.x,  20.0f);
	EXPECT_FLOAT_EQ(c.y, -20.0f);

	// *
	gtk::vec2 e(2997.0f, -2997.0f);
	EXPECT_TRUE((a * d) == e);
	
	gtk::vec2 f(0.000025, 0.000025);
	EXPECT_TRUE( (b * 0.005f) == f);

}

TEST_F(Vec2_F, vec2_Divide)
{
	// /=
	a /= 3;
	EXPECT_FLOAT_EQ(a.x, 5);
	EXPECT_FLOAT_EQ(a.y, 5);

	d /= b;
	EXPECT_FLOAT_EQ(d.x, 19980);
	EXPECT_FLOAT_EQ(d.y, -19980);


	// /
	EXPECT_FLOAT_EQ((a / 2).x, 2.5f);
	EXPECT_FLOAT_EQ((a / 2).y, 2.5f);

	EXPECT_FLOAT_EQ((d / a).x,  3996.0f);
	EXPECT_FLOAT_EQ((d / a).y, -3996.0f);
}

TEST_F(Vec2_F, vec2_IncrementDecrement)
{
	// Increment
	EXPECT_FLOAT_EQ((c++).x,  1);
	EXPECT_FLOAT_EQ(c.x, 2);
	EXPECT_FLOAT_EQ(c.y, 0);

	EXPECT_FLOAT_EQ((++a).x, 16);
	EXPECT_FLOAT_EQ(a.y, 16);

	// Decrement
	EXPECT_FLOAT_EQ((b--).x, 0.005);
	EXPECT_FLOAT_EQ(b.y, -0.995);

	EXPECT_FLOAT_EQ((--d).x, 98.9);
	EXPECT_FLOAT_EQ(d.y, -100.9);

}

TEST_F(Vec2_F, vec2_DotCross)
{
	// Dot
	EXPECT_FLOAT_EQ(b.Dot(d), 0);

	gtk::vec2 e(-1.1f, 5.9);
	gtk::vec2 f(4.5f, 8.6f);
	EXPECT_FLOAT_EQ(e.Dot(f), 45.79);

	// Cross
	EXPECT_FLOAT_EQ(e.Cross(f), -36.01);

}

TEST_F(Vec2_F, vec2_Length)
{
	// Length
	EXPECT_FLOAT_EQ(a.Length(), 21.21320344f);
	EXPECT_FLOAT_EQ(d.Length(), 141.2799349f);
	
	// Length Squared
	EXPECT_FLOAT_EQ(a.LengthSquared(), 450.0f);
	EXPECT_FLOAT_EQ(d.LengthSquared(), 19960.02f);

}




