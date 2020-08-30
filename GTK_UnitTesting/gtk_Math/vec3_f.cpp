#include "pch.h"
#include "gtk/Math.h"

class Vec3_F : public ::testing::Test
{
protected:

	Vec3_F() : a(1.0f), b(0.5f), c(1.0f, 2.0f, 3.0f), d(-1.0f, -2.0f, -3.0f), t(2) {}
	~Vec3_F() {}

	void SetUp() override {}
	void TearDown() override {}

	gtk::vec3 a;
	gtk::vec3 b;
	gtk::vec3 c;
	gtk::vec3 d;
	gtk::vec3 t;
};

TEST_F(Vec3_F, vec3_boolOperators)
{
	gtk::vec3 e(1);
	EXPECT_EQ(a, e);
	EXPECT_TRUE(d == (c * -1));
	EXPECT_FALSE(d == c);

	gtk::vec3 f(1, 1, 3);
	EXPECT_FALSE(a == f);

	EXPECT_TRUE(a != f);

}


TEST_F(Vec3_F, vec3_constructors)
{
	using namespace gtk;

	vec3 x(1);
	EXPECT_FLOAT_EQ(1, x.x);
	EXPECT_FLOAT_EQ(1, x.y);
	EXPECT_FLOAT_EQ(1, x.z);

	vec3 y(1, 2, 3);
	EXPECT_FLOAT_EQ(y.values[0], 1.0f);
	EXPECT_FLOAT_EQ(y.values[1], 2.0f);
	EXPECT_FLOAT_EQ(y.values[2], 3.0f);

	vec3 z = { -1.2, -2.2, -3.5 };
	EXPECT_FLOAT_EQ(z.r, -1.2f);
	EXPECT_FLOAT_EQ(z.g, -2.2f);
	EXPECT_FLOAT_EQ(z.b, -3.5f);
}

TEST_F(Vec3_F, vec3_Add)
{
	a += c;
	EXPECT_EQ(a, gtk::vec3(2, 3, 4));

	EXPECT_EQ(a + c, gtk::vec3(3, 5, 7));
	EXPECT_EQ(a, gtk::vec3(2, 3, 4));

	EXPECT_EQ(a += 0.5f, gtk::vec3(2.5, 3.5, 4.5));
	EXPECT_EQ(a + 1.5f, gtk::vec3(4.0f, 5.0f, 6.0f));
	EXPECT_EQ(a, gtk::vec3(2.5, 3.5, 4.5));
}


TEST_F(Vec3_F, vec3_Subtract)
{
	b -= a;
	EXPECT_EQ(b, gtk::vec3(-0.5f));

	EXPECT_EQ(b - a, gtk::vec3(-1.5f));
	EXPECT_EQ(b, gtk::vec3(-0.5f));

	EXPECT_EQ(b -= 1, gtk::vec3(-1.5f));
	EXPECT_EQ(b, gtk::vec3(-1.5f));

	EXPECT_EQ(d - 5, gtk::vec3(-6, -7, -8));
	EXPECT_EQ(d, gtk::vec3(-1, -2, -3));
}

TEST_F(Vec3_F, vec3_Multiply)
{
	EXPECT_EQ(a *= t, t);
	EXPECT_EQ(a *= 2, t * 2);
	EXPECT_FALSE(a == t);
	
	EXPECT_EQ(d * t, gtk::vec3(-2, -4, -6));
	EXPECT_TRUE(d != gtk::vec3(-2, -4, -6));
}

TEST_F(Vec3_F, vec3_Divide)
{
	EXPECT_EQ( t / t, a);
	EXPECT_EQ( t /= t, a);
	EXPECT_EQ(t, a);

	EXPECT_EQ(c / 2, gtk::vec3(0.5f, 1.0f, 1.5f));
	EXPECT_EQ(c, gtk::vec3(1.0f, 2.0f, 3.0f));

	EXPECT_EQ(c /= 2, gtk::vec3(0.5f, 1.0f, 1.5f));
	EXPECT_EQ(c, gtk::vec3(0.5f, 1.0f, 1.5f));
}

TEST_F(Vec3_F, vec3_IncrementDecrement)
{
	EXPECT_FALSE(a++ == t);
	EXPECT_TRUE(a == t);

	EXPECT_EQ(++a, gtk::vec3(3));
	EXPECT_EQ(++d, gtk::vec3(0.0, -1.0f, -2.0f));
	EXPECT_EQ(++b, gtk::vec3(1.5f));
}

TEST_F(Vec3_F, vec3_DotCross)
{
	EXPECT_FLOAT_EQ(c.Dot(gtk::vec3(5, 3, 6)), 29);
	EXPECT_EQ(c, gtk::vec3(1, 2, 3));

	EXPECT_EQ(c.Cross(gtk::vec3(5, 3, 6)), gtk::vec3(3, 9, -7));
	EXPECT_EQ(c, gtk::vec3(1, 2, 3));
}





