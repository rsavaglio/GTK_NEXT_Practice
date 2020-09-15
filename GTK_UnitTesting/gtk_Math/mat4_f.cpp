#include "pch.h"
#include "gtk/gtkMath.hpp"

using namespace gtk;

class Mat4_F : public ::testing::Test
{
protected:

	Mat4_F() : a(), b(0.5f), c(-5.0f), i(1), t(2), d(1.0f,  2.0f,  3.0f,  4.0f,
													 5.0f,  6.0f,  7.0f,  8.0f,
													 9.0f,  10.0f, 11.0f, 12.0f,
													 13.0f, 14.0f, 15.0f, 16.0f) {}
	~Mat4_F() {}

	void SetUp() override {}
	void TearDown() override {}

	mat4 a;
	mat4 b;
	mat4 c;
	mat4 i;
	mat4 t;
	mat4 d;
};

TEST_F(Mat4_F, contrustors)
{
	mat4 x;
	EXPECT_FLOAT_EQ(x.values[0],  0.0f);
	EXPECT_FLOAT_EQ(x.values[1],  0.0f);
	EXPECT_FLOAT_EQ(x.values[2],  0.0f);
	EXPECT_FLOAT_EQ(x.values[3],  0.0f);
	EXPECT_FLOAT_EQ(x.values[4],  0.0f);
	EXPECT_FLOAT_EQ(x.values[5],  0.0f);
	EXPECT_FLOAT_EQ(x.values[6],  0.0f);
	EXPECT_FLOAT_EQ(x.values[7],  0.0f);
	EXPECT_FLOAT_EQ(x.values[8],  0.0f);
	EXPECT_FLOAT_EQ(x.values[9],  0.0f);
	EXPECT_FLOAT_EQ(x.values[10], 0.0f);
	EXPECT_FLOAT_EQ(x.values[11], 0.0f);
	EXPECT_FLOAT_EQ(x.values[12], 0.0f);
	EXPECT_FLOAT_EQ(x.values[13], 0.0f);
	EXPECT_FLOAT_EQ(x.values[14], 0.0f);
	EXPECT_FLOAT_EQ(x.values[15], 0.0f);

	mat4 y(5.0f);
	EXPECT_FLOAT_EQ(y.values[0], 5.0f);
	EXPECT_FLOAT_EQ(y.values[1], 0.0f);
	EXPECT_FLOAT_EQ(y.values[2], 0.0f);
	EXPECT_FLOAT_EQ(y.values[3], 0.0f);

	EXPECT_FLOAT_EQ(y.values[4], 0.0f);
	EXPECT_FLOAT_EQ(y.values[5], 5.0f);
	EXPECT_FLOAT_EQ(y.values[6], 0.0f);
	EXPECT_FLOAT_EQ(y.values[7], 0.0f);

	EXPECT_FLOAT_EQ(y.values[8], 0.0f);
	EXPECT_FLOAT_EQ(y.values[9], 0.0f);
	EXPECT_FLOAT_EQ(y.values[10], 5.0f);
	EXPECT_FLOAT_EQ(y.values[11], 0.0f);

	EXPECT_FLOAT_EQ(y.values[12], 0.0f);
	EXPECT_FLOAT_EQ(y.values[13], 0.0f);
	EXPECT_FLOAT_EQ(y.values[14], 0.0f);
	EXPECT_FLOAT_EQ(y.values[15], 5.0f);

	mat4 z = d;

	EXPECT_FLOAT_EQ(d.values[0], 1.0f);
	EXPECT_FLOAT_EQ(d.values[1], 2.0f);
	EXPECT_FLOAT_EQ(d.values[2], 3.0f);
	EXPECT_FLOAT_EQ(d.values[3], 4.0f);
	EXPECT_FLOAT_EQ(d.values[4], 5.0f);
	EXPECT_FLOAT_EQ(d.values[5], 6.0f);
	EXPECT_FLOAT_EQ(d.values[6], 7.0f);
	EXPECT_FLOAT_EQ(d.values[7], 8.0f);	
	EXPECT_FLOAT_EQ(d.values[8], 9.0f);
	EXPECT_FLOAT_EQ(d.values[9], 10.0f);
	EXPECT_FLOAT_EQ(d.values[10], 11.0f);
	EXPECT_FLOAT_EQ(d.values[11], 12.0f);			
	EXPECT_FLOAT_EQ(d.values[12], 13.0f);
	EXPECT_FLOAT_EQ(d.values[13], 14.0f);
	EXPECT_FLOAT_EQ(d.values[14], 15.0f);
	EXPECT_FLOAT_EQ(d.values[15], 16.0f);

	EXPECT_EQ(d, z);
	EXPECT_NE(d, x);

}


TEST_F(Mat4_F, scalars)
{
	// Add
	EXPECT_EQ(d + 2, mat4(3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f));
	EXPECT_EQ(d += 2, mat4(3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f));
	EXPECT_EQ(d, mat4(3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f));

	// Subtract
	EXPECT_EQ(d - 2, mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
	EXPECT_EQ(d -= 2, mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
	EXPECT_EQ(d, mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));

	// Multiply
	EXPECT_EQ(d * 2, mat4(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f));
	EXPECT_EQ(d *= 2, mat4(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f));
	EXPECT_EQ(d, mat4(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f));

	// Divide
	EXPECT_EQ(d / 2, mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
	EXPECT_EQ(d /= 2, mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
	EXPECT_EQ(d, mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
}


TEST_F(Mat4_F, mats)
{
	mat4 x = {
		16, 15, 14, 13,
		12, 11, 10, 9,
		8,  7,  6,  5,
		4,  3,  2,  1
	};

	// Add
	EXPECT_EQ(d + x, mat4(17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17));
	EXPECT_EQ(d += x, mat4(17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17));
	EXPECT_EQ(d, mat4(17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17));

	// Subtract
	EXPECT_EQ(d - x, mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
	EXPECT_EQ(d -= x, mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
	EXPECT_EQ(d, mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));

	// Multiply
	EXPECT_EQ(d * x, mat4(386, 444, 502, 560, 274, 316, 358, 400, 162, 188, 214, 240, 50, 60, 70, 80));
	EXPECT_EQ(d *= x, mat4(386, 444, 502, 560, 274, 316, 358, 400, 162, 188, 214, 240, 50, 60, 70, 80));
	EXPECT_EQ(d, mat4(386, 444, 502, 560, 274, 316, 358, 400, 162, 188, 214, 240, 50, 60, 70, 80));

}


TEST_F(Mat4_F, vec_transform)
{
	vec4 x = { 16, 15, 14, 13 };

	EXPECT_EQ(d * x, vec4(386, 444, 502, 560));
	EXPECT_EQ(d *= x, vec4(386, 444, 502, 560));
	EXPECT_EQ(d, vec4(386, 444, 502, 560));

}


TEST_F(Mat4_F, inverse)
{
	mat4 x = {
		16, 15, 14, 13,
		12, 11, 10, 9,
		8,  7,  6,  5,
		4,  3,  2,  1
	};

	mat4 y = {
		16, 12, 8, 4,
		15, 11, 7, 3,
		14, 10, 6, 2,
		13, 9,  5, 1
	};

	EXPECT_EQ(x.GetInverse(), y);
	EXPECT_EQ(x.SetInverse(), y);
	EXPECT_EQ(x, y);

}