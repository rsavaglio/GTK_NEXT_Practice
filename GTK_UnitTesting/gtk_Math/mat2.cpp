#include "pch.h"
#include "gtk/Math.h"

class Mat2_F : public ::testing::Test
{
protected:

	Mat2_F() : a(), b(0.5f), c(-5.0f), d(1.0f, 2.0f, 3.0f, 4.0f), i(1), t(2) {}
	~Mat2_F() {}

	void SetUp() override {}
	void TearDown() override {}

	gtk::mat2 a;
	gtk::mat2 b;
	gtk::mat2 c;
	gtk::mat2 d;
	gtk::mat2 i;
	gtk::mat2 t;
};

TEST_F(Mat2_F, mat2_boolOperators)
{
	gtk::mat2 e(1, 2, 3, 4);
	EXPECT_EQ(d, e);
	EXPECT_TRUE(d == e);
	EXPECT_FALSE(d == a);
}

TEST_F(Mat2_F, mat2_contrustors)
{
	gtk::mat2 x;
	for (int i = 0; i < 4; i++)
	{
		EXPECT_FLOAT_EQ(x.values[i], 0.0f);
	}
	
	const gtk::mat2 y(1.0f);
	EXPECT_FLOAT_EQ(y.rows[0][0], 1.0f); EXPECT_FLOAT_EQ(y.rows[0][1], 0.0f);
	EXPECT_FLOAT_EQ(y.rows[1][0], 0.0f); EXPECT_FLOAT_EQ(y.rows[1][1], 1.0f);

	gtk::mat2 z = { 1, 2, 3.5f, 4 };
	EXPECT_FLOAT_EQ(z.values[0], 1.0f); EXPECT_FLOAT_EQ(z.values[1], 2.0f);
	EXPECT_FLOAT_EQ(z.values[2], 3.5f); EXPECT_FLOAT_EQ(z.values[3], 4.0f);

	gtk::mat2 w(-499.5f, -55.0f, 2, 1);
	EXPECT_FLOAT_EQ(w.values[0], -499.5f); EXPECT_FLOAT_EQ(w.values[1], -55.0f);
	EXPECT_FLOAT_EQ(w.values[2], 2.0f);    EXPECT_FLOAT_EQ(w.values[3], 1.0f);
}


TEST_F(Mat2_F, mat2_Add)
{
	// += mat2
	gtk::mat2 x(50, 40, -30, -20.5f);
	EXPECT_TRUE((a += x) == x);
	a += x;
	x += x;
	EXPECT_TRUE(a == x);

	// += scalar
	gtk::mat2 y(-10.0, -5.0f, 
				-5.0f, -10.0f);

	c += -5.0f;
	EXPECT_TRUE(c == y);

	// + mat2
	gtk::mat2 z(2.0, 4.0f, 6.0f, 8.0f);
	EXPECT_EQ((d + d), z);
	EXPECT_FALSE(d == z);

	// + scalar
	gtk::mat2 w(1.5f, 2.5f, 3.5f, 4.5f);
	EXPECT_EQ((d + 0.5f), w);
	EXPECT_FALSE(d == w);

}


TEST_F(Mat2_F, mat2_Subtract)
{
	// -= mat2
	gtk::mat2 x(-1, -2, -3, -4);
	a -= d;
	EXPECT_TRUE(a == x);

	// -= scalar
	gtk::mat2 y(1, 0, -1, -2);
	a -= (-2);
	EXPECT_TRUE(a == y);

	// - mat2
	gtk::mat2 z(2, 4, 6, 8);
	EXPECT_EQ((d - x), z);

	// - scalar
	gtk::mat2 w(0.5f, 1.5f, 2.5f, 3.5f);
	EXPECT_EQ((d - 0.5f), w);

}


TEST_F(Mat2_F, mat2_Multiply)
{
	// *= mat2
	a *= d;
	EXPECT_EQ(a, gtk::mat2(0,0,0,0));
	EXPECT_EQ(d, gtk::mat2(1, 2, 3, 4));

	d *= c;
	EXPECT_EQ(d, gtk::mat2(-5, -10, -15, -20));

	// *= scalar
	d *= -2;
	EXPECT_EQ(d, gtk::mat2(10, 20, 30, 40));

	// * mat2
	EXPECT_EQ((d * gtk::mat2(1)), gtk::mat2(10, 20, 30, 40));
	EXPECT_EQ((d * gtk::mat2(1, 2, 3, 4)), gtk::mat2(70, 100, 150, 220));

	// * vec2
	gtk::vec2 v(2, 4);
	EXPECT_EQ((d*v), gtk::vec2(100, 220));

	// * scalar
	EXPECT_EQ((d * -2), gtk::mat2(-20, -40, -60, -80));
}


TEST_F(Mat2_F, mat2_Divide)
{
	// /= by scalar
	EXPECT_EQ((d /= 2), gtk::mat2(0.5, 1, 1.5, 2));
	EXPECT_EQ(d, gtk::mat2(0.5, 1, 1.5, 2));

	// / by scalar
	EXPECT_EQ((d / 2), gtk::mat2(0.25, 0.5, 0.75, 1));
	EXPECT_EQ(d, gtk::mat2(0.5, 1, 1.5, 2));
}


