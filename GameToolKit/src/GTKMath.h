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
		      MTYPE& operator[](unsigned short i)       { ASSERT(i < 2); return values[i]; }
		const MTYPE& operator[](unsigned short i) const { ASSERT(i < 2); return values[i]; }


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
		vec2& AddScalar       (const MTYPE& scalar) { x += scalar; y += scalar; return *this; }
		vec2& SubtractScalar  (const MTYPE& scalar) { x -= scalar; y -= scalar; return *this; }
		vec2& MultiplyByScalar(const MTYPE& scalar) { x *= scalar; y *= scalar; return *this; }
		vec2& DivideByScalar  (const MTYPE& scalar) { x /= scalar; y /= scalar; return *this; }

		vec2& operator+=(const MTYPE& other) { return AddScalar(other); }
		vec2& operator-=(const MTYPE& other) { return SubtractScalar(other); }
		vec2& operator*=(const MTYPE& other) { return MultiplyByScalar(other); }
		vec2& operator/=(const MTYPE& other) { return DivideByScalar(other); }

		vec2 operator+(const MTYPE& other) { return vec2(x + other, y + other); }
		vec2 operator-(const MTYPE& other) { return vec2(x - other, y - other); }
		vec2 operator*(const MTYPE& other) { return vec2(x * other, y * other); }
		vec2 operator/(const MTYPE& other) { return vec2(x / other, y / other); }

		// Other basic operations
		void Increment ()    { x++; y++; }
		void Decrement ()    { x--; y--; }
		vec2& operator++()    { Increment(); return *this; }
		vec2& operator--()    { Decrement(); return *this; }
		vec2  operator++(int) { vec2 temp = *this; Increment(); return temp; }
		vec2  operator--(int) { vec2 temp = *this; Decrement(); return temp; }

		bool operator==(const vec2& other) { return   x == other.x && y == other.y ; }
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
		MTYPE& operator()(unsigned short row, unsigned short column)       
		{ 
			ASSERT(column < 2 && row < 2); 
			return values[column + row * 2];
		}
		const MTYPE& operator()(unsigned short row, unsigned short column) const 
		{ 
			ASSERT(column < 2 && row < 2); 
			return values[column + row * 2];
		}

		vec2& operator[](unsigned short i) { ASSERT(i < 2); return rows[i]; }
		const vec2& operator[](unsigned short i) const { ASSERT(i < 2); return rows[i]; }


		///// mat2 + scalar Operations

		mat2& AddScalar(const MTYPE& scalar)
		{
			*(values)     += scalar;
			*(values + 1) += scalar;
			*(values + 2) += scalar;
			*(values + 3) += scalar;

			return *this;

		}        mat2& operator+=(const MTYPE& scalar) { return AddScalar(scalar); }
		mat2& SubtractScalar(const MTYPE& scalar)
		{
			*(values)     -= scalar;
			*(values + 1) -= scalar;
			*(values + 2) -= scalar;
			*(values + 3) -= scalar;

			return *this;

		}   mat2& operator-=(const MTYPE& scalar) { return SubtractScalar(scalar); }
		mat2& MultiplyByScalar(const MTYPE& scalar)
		{
			*(values)     *= scalar;
			*(values + 1) *= scalar;
			*(values + 2) *= scalar;
			*(values + 3) *= scalar;

			return *this;

		} mat2& operator*=(const MTYPE& scalar) { return MultiplyByScalar(scalar); }
		mat2& DivideByScalar(const MTYPE& scalar)
		{
			*(values)     /= scalar;
			*(values + 1) /= scalar;
			*(values + 2) /= scalar;
			*(values + 3) /= scalar;

			return *this;

		}   mat2& operator/=(const MTYPE& scalar) { return DivideByScalar(scalar); }

		mat2 operator+(const MTYPE& scalar) 
		{ 
			return 
			{
				*(values)   + scalar,
				*(values+1) + scalar,
				*(values+2) + scalar,
				*(values+2) + scalar
			};
		}
		mat2 operator-(const MTYPE& scalar) 
		{
			return
			{
				*(values)     - scalar,
				*(values + 1) - scalar,
				*(values + 2) - scalar,
				*(values + 2) - scalar
			};
		}
		mat2 operator*(const MTYPE& scalar)
		{
			return
			{
				*(values)     * scalar,
				*(values + 1) * scalar,
				*(values + 2) * scalar,
				*(values + 2) * scalar
			};
		}
		mat2 operator/(const MTYPE& scalar)
		{
			return
			{
				*(values)     / scalar,
				*(values + 1) / scalar,
				*(values + 2) / scalar,
				*(values + 2) / scalar
			};
		}
		
		
		//// mat2 + vec2 Operations
		
		vec2 MultiplyByVec2(const vec2& vec)
		{
			// a b * x  = ax + by
			// c d   y	  cx + dy

			return { 
				((* values)    * (*vec.values)) + ((*(values+1)) * (*(vec.values+1))), // x1 = ax + by
				((*(values+2)) * (*vec.values)) + ((*(values+3)) * (*(vec.values+1)))  // y1 = cx + dy
			};

		} vec2 operator*(const vec2& vec) { return MultiplyByVec2(vec); }

		
		//// mat2 + mat2 Operations

		mat2& Add(const mat2& other) 
		{ 
			*(values)     += *(other.values);
			*(values + 1) += *(other.values + 1);
			*(values + 2) += *(other.values + 2);
			*(values + 3) += *(other.values + 3);

			return *this;

		} mat2& operator+=(const mat2& other) { return Add(other); }
		mat2& Subtract(const mat2& other)
		{
			*(values)     -= *(other.values);
			*(values + 1) -= *(other.values + 1);
			*(values + 2) -= *(other.values + 2);
			*(values + 3) -= *(other.values + 3);

			return *this;

		} mat2& operator-=(const mat2& other) { return Subtract(other); }
		mat2& Multiply(const mat2& other)
		{
			// a b  *  A B  =  aA + bC, aB + bD
			// c d     C D     cA + dC, cB + dD

			MTYPE a =  *values;
			MTYPE b = (*(values + 1));
			MTYPE c = (*(values + 2));
			MTYPE d = (*(values + 3));

			* values      = (a * (* other.values)   )   + (b * (*(other.values + 2))); // a = aA + bC
			*(values + 1) = (a * (*(other.values + 1))) + (b * (*(other.values + 3))); // b = aB + bD
			*(values + 2) = (c * (*other.values))       + (d * (*(other.values + 2))); // c = cA + dC
			*(values + 3) = (c * (*(other.values + 1))) + (d * (*(other.values + 3))); // d = cB + dD

			return *this;

		} mat2& operator*=(const mat2& other) { return Multiply(other); }

		mat2 operator+(const mat2& other)
		{
			return
			{
				*(values)     + *(other.values),
				*(values + 1) + *(other.values + 1),
				*(values + 2) + *(other.values + 2),
				*(values + 3) + *(other.values + 3)
			};
		}
		mat2 operator-(const mat2& other)
		{
			MTYPE* i = &values[0];
			const MTYPE* j = &other.values[0];

			return
			{
				*(values)     - *(other.values),
				*(values + 1) - *(other.values + 1),
				*(values + 2) - *(other.values + 2),
				*(values + 3) - *(other.values + 3)
			};
		}
		mat2 operator*(const mat2& other)
		{
			return
			{
				((*values) * (*other.values))             + ((*(values + 1)) * (*(other.values + 2))), // a = aA + bC
				((*values) * (*(other.values + 1)))       + ((*(values + 1)) * (*(other.values + 3))), // b = aB + bD
				((*(values + 2)) * (*other.values))       + ((*(values + 3)) * (*(other.values + 2))), // c = cA + dC
				((*(values + 2)) * (*(other.values + 1))) + ((*(values + 3)) * (*(other.values + 3))) // d = cB + dD
			};
		}

	};

}