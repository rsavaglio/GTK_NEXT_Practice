#include "pch.h"
#include "gtk/gtkMath.hpp"
 
using namespace gtk;

class Mat2_F : public ::testing::Test
{
protected:

	Mat2_F() : a(), b(0.5f), c(-5.0f), d(1.0f, 2.0f, 3.0f, 4.0f), i(1), t(2) {}
	~Mat2_F() {}

	void SetUp() override {}
	void TearDown() override {}

	mat2 a;
	mat2 b;
	mat2 c;
	mat2 d;
	mat2 i;
	mat2 t;
};

TEST_F(Mat2_F, boolOperators)
{
	gtk::mat2 e(1, 2, 3, 4);
	EXPECT_EQ(d, e);
	EXPECT_TRUE(d == e);
	EXPECT_FALSE(d == a);

	EXPECT_FALSE(d != e);
	EXPECT_TRUE(d != a);
}

TEST_F(Mat2_F, contrustors)
{
	mat2 x;
	EXPECT_EQ(x, mat2(0, 0, 0, 0));
	
	mat2 y(5.0f);
	EXPECT_EQ(y, mat2(5.0f, 0.0f, 0.0f, 5.0f));

	mat2 z = { 4, 3, 2, 1 };
	EXPECT_FLOAT_EQ(z(0, 0), 4.0f);
	EXPECT_FLOAT_EQ(z(1, 0), 3.0f);
	EXPECT_FLOAT_EQ(z(0, 1), 2.0f);
	EXPECT_FLOAT_EQ(z(1, 1), 1.0f);

	EXPECT_FLOAT_EQ(z[0][0], 4.0f);
	EXPECT_FLOAT_EQ(z[0][1], 3.0f);
	EXPECT_FLOAT_EQ(z[1][0], 2.0f);
	EXPECT_FLOAT_EQ(z[1][1], 1.0f);

}

TEST_F(Mat2_F, scalars)
{
	// Add
	EXPECT_EQ(d + 1,  mat2(2, 3, 4, 5));
	EXPECT_EQ(d += 1, mat2(2, 3, 4, 5));
	EXPECT_EQ(d, mat2(2, 3, 4, 5));

	// Substract
	EXPECT_EQ(d - 1, mat2(1, 2, 3, 4));
	EXPECT_EQ(d -= 1, mat2(1, 2, 3, 4));
	EXPECT_EQ(d, mat2(1, 2, 3, 4));

	// Multiply
	EXPECT_EQ(d * 2, mat2(2, 4, 6, 8));
	EXPECT_EQ(d *= 2, mat2(2, 4, 6, 8));
	EXPECT_EQ(d, mat2(2, 4, 6, 8));

	// Divide		
	EXPECT_EQ(d / 2, mat2(1, 2, 3, 4));
	EXPECT_EQ(d /= 2, mat2(1, 2, 3, 4));
	EXPECT_EQ(d, mat2(1, 2, 3, 4));
}



TEST_F(Mat2_F, mats)
{
	mat2 x(4.0f, 3.0f, 2.0f, 1.0f);

	// Add
	EXPECT_EQ(d + b, mat2(1.5f, 2.0f, 3.0f, 4.5f));
	EXPECT_EQ(d += b, mat2(1.5f, 2.0f, 3.0f, 4.5f));
	EXPECT_EQ(d, mat2(1.5f, 2.0f, 3.0f, 4.5f));

	// Subtract
	EXPECT_EQ(x - d, mat2(2.5f, 1.0f, -1.0f, -3.5f));
	EXPECT_EQ(x -= d, mat2(2.5f, 1.0f, -1.0f, -3.5f));
	EXPECT_EQ(x, mat2(2.5f, 1.0f, -1.0f, -3.5f));

	// Multiply
	d = mat2(1, 2, 3, 4);
	mat2 y(3.0f, 1.0f, 2.0f, 5.0f);
	EXPECT_EQ(d * y, mat2(6, 10, 17, 24));
	EXPECT_EQ(d *= y, mat2(6, 10, 17, 24));
	EXPECT_EQ(d, mat2(6, 10, 17, 24));

}



TEST_F(Mat2_F, transformVec)
{
	vec2 x(5, 6);
	EXPECT_EQ(d * x, vec2(23, 34));
}

TEST_F(Mat2_F, inverse)
{
	EXPECT_EQ(d.GetInverse(), mat2(1, 3, 2, 4));
	EXPECT_EQ(d.SetInverse(), mat2(1, 3, 2, 4));
	EXPECT_EQ(d, mat2(1, 3, 2, 4));
}


