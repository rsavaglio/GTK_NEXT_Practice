#include "pch.h"
#include "gtk/gtkMath.hpp"

class Mat3_F : public ::testing::Test
{
protected:

	Mat3_F() : a(), b(0.5f), c(-5.0f), i(1), t(2), d(1.0f, 2.0f, 3.0f, 
													 4.0f, 5.0f, 6.0f,
													 7.0f, 8.0f, 9.0f) {}
	~Mat3_F() {}

	void SetUp() override {}
	void TearDown() override {}

	gtk::mat3 a;
	gtk::mat3 b;
	gtk::mat3 c;
	gtk::mat3 i;
	gtk::mat3 t;
	gtk::mat3 d;
};

TEST_F(Mat3_F, mat2_contrustors)
{

}


TEST_F(Mat3_F, mat2_Add)
{

}


TEST_F(Mat3_F, mat2_Subtract)
{

}


TEST_F(Mat3_F, mat2_Multiply)
{

}


TEST_F(Mat3_F, mat2_Divide)
{
}