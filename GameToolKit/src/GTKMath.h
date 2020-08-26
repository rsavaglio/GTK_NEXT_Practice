#pragma once
#include "Core.h"

	namespace gtk {

	#define MTYPE float

	struct vec2
	{
		union {
			MTYPE values[2];
			struct { MTYPE x, y; };
			struct { MTYPE r, g; };
			struct { MTYPE u, v; };
		};

		vec2() :x(0), y(0) {}
		vec2(MTYPE X) : x(X), y(X) {}
		vec2(MTYPE X, MTYPE Y) : x(X), y(Y) {}

		// Indexing
		MTYPE& operator[](unsigned short i) { ASSERT(i < 2); return values[i]; }
		const MTYPE&  operator[](unsigned short i) const { ASSERT(i < 2); return values[i]; }


		// Basic vec2 + vec2 operations
		vec2& Add     (const vec2& other) { x += other.x; y += other.y; return *this; }
		vec2& Subtract(const vec2& other) { x -= other.x; y -= other.y; return *this; }
		vec2& Multiply(const vec2& other) { x *= other.x; y *= other.y; return *this; }
		vec2& Divide  (const vec2& other) { x /= other.x; y /= other.y; return *this; }

		vec2& operator+=(const vec2& other) { return Add(other); }
		vec2& operator-=(const vec2& other) { return Subtract(other); }
		vec2& operator*=(const vec2& other) { return Multiply(other); }
		vec2& operator/=(const vec2& other) { return Divide(other); }

		vec2 operator+(const vec2& other) { return vec2(x + other.x, y + other.y); }
		vec2 operator-(const vec2& other) { return vec2(x - other.x, y - other.y); }
		vec2 operator*(const vec2& other) { return vec2(x * other.x, y * other.y); }
		vec2 operator/(const vec2& other) { return vec2(x / other.x, y / other.y); }


		// Basic vec2 + scalar operations
		vec2 AddScalar       (const MTYPE& scalar) { x += scalar; y += scalar; return *this; }
		vec2 SubtractScalar  (const MTYPE& scalar) { x -= scalar; y -= scalar; return *this; }
		vec2 MultiplyByScalar(const MTYPE& scalar) { x *= scalar; y *= scalar; return *this; }
		vec2 DivideByScalar  (const MTYPE& scalar) { x /= scalar; y /= scalar; return *this; }

		vec2 operator+=(const MTYPE& other) { return AddScalar(other); }
		vec2 operator-=(const MTYPE& other) { return SubtractScalar(other); }
		vec2 operator*=(const MTYPE& other) { return MultiplyByScalar(other); }
		vec2 operator/=(const MTYPE& other) { return DivideByScalar(other); }

		vec2 operator+(const MTYPE& other) { return vec2(x + other, y + other); }
		vec2 operator-(const MTYPE& other) { return vec2(x - other, y - other); }
		vec2 operator*(const MTYPE& other) { return vec2(x * other, y * other); }
		vec2 operator/(const MTYPE& other) { return vec2(x / other, y / other); }

		// Other basic operations
		void Increment ()    { x++; y++; }
		void Decrement ()    { x--; y--; }
		vec2 operator++()    { Increment(); return *this; }
		vec2 operator--()    { Decrement(); return *this; }
		vec2 operator++(int) { vec2 temp = *this; Increment(); return temp; }
		vec2 operator--(int) { vec2 temp = *this; Decrement(); return temp; }

		bool operator==(const vec2& other) { return x == other.x && y == other.y; }
		bool operator!=(const vec2& other) { return !(x == other.x && y == other.y); }


		// Operations I should have studied more during my undergrad
		MTYPE DotProduct  (const vec2& other) { return (x * other.x) + (y * other.y); }
		MTYPE CrossProduct(const vec2& other) { return (x * other.y) - (y * other.x); }

	};

	
	struct mat2
	{
		union {
			MTYPE values[4];
			vec2 rows[2];
		};
		
		mat2() : values{ 0, 0, 
						 0, 0 } {}

		mat2(MTYPE v) : values{ v, 0,
								0, v } {}

		mat2(MTYPE x0, MTYPE x1, MTYPE y0, MTYPE y1) : values{ x0, x1, 
															   y0, y1 } {}

		// Indexing
		MTYPE& operator()(unsigned short column, unsigned short row) 
		{ 
			ASSERT(column < 2 && row < 2); 
			return values[column + row * 2];
		}
		const MTYPE& operator()(unsigned short column, unsigned short row) const 
		{ 
			ASSERT(column < 2 && row < 2); 
			return values[column + row * 2];
		}

		vec2& operator[](unsigned short i) { ASSERT(i < 2); return rows[i]; }
		const vec2& operator[](unsigned short i) const { ASSERT(i < 2); return rows[i]; }

	};

}