#include "pch.h"
#include "gtk/gtkMath.hpp"

using namespace gtk;

class Mat3_F : public ::testing::Test
{
protected:

	Mat3_F() : a(), b(0.5f), c(-5.0f), i(1), t(2), d(1.0f, 2.0f, 3.0f, 
													 4.0f, 5.0f, 6.0f,
													 7.0f, 8.0f, 9.0f) {}
	~Mat3_F() {}

	void SetUp() override {}
	void TearDown() override {}

	mat3 a;
	mat3 b;
	mat3 c;
	mat3 i;
	mat3 t;
	mat3 d;
};

TEST_F(Mat3_F, contrustors)
{
	mat3 x;
	EXPECT_EQ(x, mat3(0, 0, 0,
					  0, 0, 0,
					  0, 0, 0));

	EXPECT_EQ(d, mat3(1, 2, 3, 
					  4, 5, 6,
				      7, 8, 9));

	mat3 y(5.0f);
	EXPECT_EQ(y, mat3(5.0f, 0.0f, 0.0f, 
					  0.0f, 5.0f, 0.0f,
					  0.0f, 0.0f, 5.0f));
}


TEST_F(Mat3_F, scalars)
{
	// Add
	EXPECT_EQ(d + 1, mat3(2, 3, 4, 5, 6, 7, 8, 9, 10));
	EXPECT_EQ(d += 1, mat3(2, 3, 4, 5, 6, 7, 8, 9, 10));
	EXPECT_EQ(d, mat3(2, 3, 4, 5, 6, 7, 8, 9, 10));

	// Subtract
	EXPECT_EQ(d - 1, mat3(1, 2, 3, 4, 5, 6, 7, 8, 9));
	EXPECT_EQ(d -= 1, mat3(1, 2, 3, 4, 5, 6, 7, 8, 9));
	EXPECT_EQ(d, mat3(1, 2, 3, 4, 5, 6, 7, 8, 9));

	// Multiply
	EXPECT_EQ(d * 2, mat3(2, 4, 6, 8, 10, 12, 14, 16, 18));
	EXPECT_EQ(d *= 2, mat3(2, 4, 6, 8, 10, 12, 14, 16, 18));
	EXPECT_EQ(d, mat3(2, 4, 6, 8, 10, 12, 14, 16, 18));

	// Divide
	EXPECT_EQ(d / 2, mat3(1, 2, 3, 4, 5, 6, 7, 8, 9));
	EXPECT_EQ(d /= 2, mat3(1, 2, 3, 4, 5, 6, 7, 8, 9));
	EXPECT_EQ(d, mat3(1, 2, 3, 4, 5, 6, 7, 8, 9));
}


TEST_F(Mat3_F, mats)
{
	mat3 x(d);

	// Add
	EXPECT_EQ(d + x, mat3(2, 4, 6, 8, 10, 12, 14, 16, 18));
	EXPECT_EQ(d += x, mat3(2, 4, 6, 8, 10, 12, 14, 16, 18));
	EXPECT_EQ(d, mat3(2, 4, 6, 8, 10, 12, 14, 16, 18));

	// Subtract
	EXPECT_EQ(d - x, mat3(1, 2, 3, 4, 5, 6, 7, 8, 9));
	EXPECT_EQ(d -= x, mat3(1, 2, 3, 4, 5, 6, 7, 8, 9));
	EXPECT_EQ(d, mat3(1, 2, 3, 4, 5, 6, 7, 8, 9));

	// Multiply
	mat3 y(2, 4, 3, 1, 3, 2, 4, 2, 2);
	EXPECT_EQ(d * y, mat3(39, 48, 57, 27, 33, 39, 26, 34, 42));
	EXPECT_EQ(d *= y, mat3(39, 48, 57, 27, 33, 39, 26, 34, 42));
	EXPECT_EQ(d, mat3(39, 48, 57, 27, 33, 39, 26, 34, 42));

}


TEST_F(Mat3_F, vec_transform)
{
	vec3 x(2, 3, 1);
	EXPECT_EQ(d * x, vec3(21, 27, 33));

}


TEST_F(Mat3_F, inverse)
{
	EXPECT_EQ(d.GetInverse(), mat3(1, 4, 7, 2, 5, 8, 3, 6, 9));
	EXPECT_EQ(d.SetInverse(), mat3(1, 4, 7, 2, 5, 8, 3, 6, 9));
	EXPECT_EQ(d, mat3(1, 4, 7, 2, 5, 8, 3, 6, 9));

}