#include "pch.h"
#include "gtk/gtkMath.h"

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

	EXPECT_FALSE(d != e);
	EXPECT_TRUE(d != a);
}

TEST_F(Mat2_F, mat2_contrustors)
{

}


TEST_F(Mat2_F, mat2_Add)
{

}


TEST_F(Mat2_F, mat2_Subtract)
{

}


TEST_F(Mat2_F, mat2_Multiply)
{

}


TEST_F(Mat2_F, mat2_Divide)
{

}


