#include "pch.h"
#include "gtk/gtkMath.hpp"

using namespace gtk;

class Vec4_F : public ::testing::Test
{
protected:

	Vec4_F() : a(1.0f), b(0.5f), c(1.0f, 2.0f, 3.0f, 4.0f), d(-1.0f, -2.0f, -3.0f, -4.0f), t(2) {}
	~Vec4_F() {}

	void SetUp() override {}
	void TearDown() override {}

	vec4 a;
	vec4 b;
	vec4 c;
	vec4 d;
	vec4 t;
};

TEST_F(Vec4_F, vec4_boolOperators)
{


	vec4 x(0.5f);

	EXPECT_TRUE(x == b);
	EXPECT_FALSE(c == x);

	vec4 y(-1.0f, -2.0f, -3.0f, -4.0f);

	EXPECT_TRUE(d == y);
	EXPECT_FALSE(d == c);

}


TEST_F(Vec4_F, vec4_constructors)
{
	vec4 x;
	EXPECT_FLOAT_EQ(x.x, 0.0f);
	EXPECT_FLOAT_EQ(x.y, 0.0f);
	EXPECT_FLOAT_EQ(x.z, 0.0f);
	EXPECT_FLOAT_EQ(x.w, 0.0f);


	vec4 y(199.0f);
	EXPECT_FLOAT_EQ(y.r, 199.0f);
	EXPECT_FLOAT_EQ(y.g, 199.0f);
	EXPECT_FLOAT_EQ(y.b, 199.0f);
	EXPECT_FLOAT_EQ(y.a, 199.0f);

	vec4 z(2, 4, 6.6f, 8);
	EXPECT_FLOAT_EQ(z.values[0], 2.0f);
	EXPECT_FLOAT_EQ(z[1], 4.0f);
	EXPECT_FLOAT_EQ(z[2], 6.6f);
	EXPECT_FLOAT_EQ(z[3], 8.0f);


	vec4 w = { 1, 3, 5, 7 };
	EXPECT_FLOAT_EQ(w.x, 1.0f);
	EXPECT_FLOAT_EQ(w.y, 3.0f);
	EXPECT_FLOAT_EQ(w.b, 5.0f);
	EXPECT_FLOAT_EQ(w.a, 7.0f);

}

TEST_F(Vec4_F, vec4_Add)
{

	vec4 x(1);
	EXPECT_EQ(x += a, vec4(2));
	EXPECT_EQ(x += c, vec4(3, 4, 5, 6));

	EXPECT_EQ(x + a, vec4(4, 5, 6, 7));
	EXPECT_EQ(x, vec4(3, 4, 5, 6));

	vec4 y(-50.5, -40, 30, 20);
	EXPECT_EQ(y += 20.0f, vec4(-30.5, -20, 50, 40));
	EXPECT_EQ(y + (-0.5f), vec4(-31.0, -20.5, 49.5f, 39.5f));
	
	
	EXPECT_EQ(y, vec4(-30.5, -20, 50, 40));

}


TEST_F(Vec4_F, vec4_Subtract)
{
	vec4 x(3);
	EXPECT_EQ(x -= a, vec4(2));
	EXPECT_EQ(x - c, vec4(1.0f, 0.0f, -1.0f, -2.0f));
	EXPECT_EQ(x -= c, vec4(1, 0, -1, -2));
	
	EXPECT_EQ(x -= -2, vec4(3, 2, 1, 0));
	EXPECT_EQ(x - 2, vec4(1, 0, -1, -2));
}

TEST_F(Vec4_F, vec4_Multiply)
{
	vec4 x(1);
	EXPECT_EQ(x *= c, vec4(1, 2, 3, 4));

	EXPECT_EQ(x * c, vec4(1, 4, 9, 16));
	EXPECT_EQ(x *= c, vec4(1, 4, 9, 16));

	EXPECT_EQ(x *= 4, vec4(4, 16, 36, 64));
	EXPECT_EQ(x * 0.5, vec4(2, 8, 18, 32));
	EXPECT_EQ(x, vec4(4, 16, 36, 64));
}


TEST_F(Vec4_F, vec4_Divide)
{
	vec4 x(24);
	EXPECT_EQ(x /= c, vec4(24, 12, 8, 6));
	EXPECT_EQ(x / b, vec4(48, 24, 16, 12));


	EXPECT_EQ(x /= 2, vec4(12, 6, 4, 3));
	EXPECT_EQ(x / 2, vec4(6, 3, 2, 1.5));
	EXPECT_EQ(x, vec4(12, 6, 4, 3));

}

TEST_F(Vec4_F, vec4_IncrementDecrement)
{
	EXPECT_EQ(c++, vec4(1,2,3,4));
	EXPECT_EQ(++c, vec4(3, 4, 5, 6));
	EXPECT_EQ(c, vec4(3, 4, 5, 6));

	EXPECT_EQ(c--, vec4(3, 4, 5, 6));
	EXPECT_EQ(--c, vec4(1, 2, 3, 4));
	EXPECT_EQ(c,   vec4(1, 2, 3, 4));
}

TEST_F(Vec4_F, vec4_DotCross)
{
	vec4 x(-5);
	EXPECT_FLOAT_EQ(c.Dot(x), -50);
	EXPECT_EQ(c, vec4(1, 2, 3, 4));
}


TEST_F(Vec4_F, vec4_Length)
{
	// Length
	EXPECT_FLOAT_EQ(c.Length(), 5.477225575f);

	// Length Squared
	EXPECT_FLOAT_EQ(c.LengthSquared(), 30.0f);

}


