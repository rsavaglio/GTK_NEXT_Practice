#pragma once
#include "Core.h"
#include <math.h>

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

		friend bool operator==(const vec2& left, const vec2& right)
		{
			return   left.x == right.x && left.y == right.y;
		}

		friend bool operator!=(const vec2& left, const vec2& right)
		{
			return   !(left == right);
		}


		// Operations I should have studied more during my undergrad

		MTYPE Dot  (const vec2& other) { return (x * other.x) + (y * other.y); }
		MTYPE Cross(const vec2& other) { return (x * other.y) - (y * other.x); }

		// TODO: Optimize

		MTYPE Length() const { return sqrt(x * x + y * y); }
		MTYPE LengthSquared() const { return x * x + y * y; }

		vec2& Normalize()
		{
			MTYPE lengthsq = x * x + y * y;

			if (lengthsq == 0)
			{
				x = y = 0.0f;
				return *this;
			}

			float recip = 1 / sqrt(lengthsq);

			x *= recip;
			y *= recip;

			return *this;
		}

	};


	struct vec3
	{
		union {
			MTYPE values[3];
			struct { MTYPE x, y, z; };
			struct { MTYPE r, g, b; };
		};

		vec3() :x(0), y(0), z(0) {}
		vec3(MTYPE X) : x(X), y(X), z(X) {}
		vec3(MTYPE X, MTYPE Y, MTYPE Z) : x(X), y(Y), z(Z) {}

		// Indexing
		MTYPE& operator[](unsigned short i) { ASSERT(i < 3); return values[i]; }
		const MTYPE& operator[](unsigned short i) const { ASSERT(i < 3); return values[i]; }


		// Basic vec2 + vec2 operations
		vec3& Add(const vec3& other)      { x += other.x; y += other.y; z += other.z; return *this; }
		vec3& Subtract(const vec3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
		vec3& Multiply(const vec3& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
		vec3& Divide(const vec3& other)   { x /= other.x; y /= other.y; z /= other.z; return *this; }

		vec3& operator+=(const vec3& other) { return Add(other); }
		vec3& operator-=(const vec3& other) { return Subtract(other); }
		vec3& operator*=(const vec3& other) { return Multiply(other); }
		vec3& operator/=(const vec3& other) { return Divide(other); }

		vec3 operator+(const vec3& other) { return vec3(x + other.x, y + other.y, z + other.z); }
		vec3 operator-(const vec3& other) { return vec3(x - other.x, y - other.y, z - other.z); }
		vec3 operator*(const vec3& other) { return vec3(x * other.x, y * other.y, z * other.z); }
		vec3 operator/(const vec3& other) { return vec3(x / other.x, y / other.y, z / other.z); }


		// Basic vec2 + scalar operations
		vec3& AddScalar(const MTYPE& scalar)        { x += scalar; y += scalar; z += scalar; return *this; }
		vec3& SubtractScalar(const MTYPE& scalar)   { x -= scalar; y -= scalar; z -= scalar; return *this; }
		vec3& MultiplyByScalar(const MTYPE& scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
		vec3& DivideByScalar(const MTYPE& scalar)   { x /= scalar; y /= scalar; z /= scalar; return *this; }

		vec3& operator+=(const MTYPE& other) { return AddScalar(other); }
		vec3& operator-=(const MTYPE& other) { return SubtractScalar(other); }
		vec3& operator*=(const MTYPE& other) { return MultiplyByScalar(other); }
		vec3& operator/=(const MTYPE& other) { return DivideByScalar(other); }

		vec3 operator+(const MTYPE& other) { return vec3(x + other, y + other, z + other); }
		vec3 operator-(const MTYPE& other) { return vec3(x - other, y - other, z - other); }
		vec3 operator*(const MTYPE& other) { return vec3(x * other, y * other, z * other); }
		vec3 operator/(const MTYPE& other) { return vec3(x / other, y / other, z / other); }

		// Other basic operations
		void Increment() { x++; y++; z++; }
		void Decrement() { x--; y--; z--; }
		vec3& operator++() { Increment(); return *this; }
		vec3& operator--() { Decrement(); return *this; }
		vec3  operator++(int) { vec3 temp = *this; Increment(); return temp; }
		vec3  operator--(int) { vec3 temp = *this; Decrement(); return temp; }

		bool operator==(const vec3& other) { return   x == other.x && y == other.y && z == other.z; }
		bool operator!=(const vec3& other) { return !(x == other.x && y == other.y && z == other.z); }

		friend bool operator==(const vec3& left, const vec3& right)
		{
			return   left.x == right.x && left.y == right.y && left.z == right.z;
		}

		friend bool operator!=(const vec3& left, const vec3& right)
		{
			return   !(left == right);
		}


		// Operations I should have studied more during my undergrad
		MTYPE Dot(const vec3& other) { return (x * other.x) + (y * other.y) + (z * other.z); }
		vec3 Cross(const vec3& other)
		{
			gtk::vec3 out;

			// x = values
			// y = values + 1
			// z = values + 2

			out.x = ((*(values + 1)) * (*(other.values + 2))) - ((*(values + 2)) * (*(other.values + 1)));
			out.y = ((*(values + 2)) * (*other.values)      ) - ((*values)       * (*(other.values + 2)));
			out.z = ((*values)       * (*(other.values + 1))) - ((*(values + 1)) * (*other.values)      );

			return out;
		}


		MTYPE Length() const { return sqrt(x * x + y * y + z * z); }
		MTYPE LengthSquared() const { return x * x + y * y + z * z; }

		vec3& Normalize()
		{
			MTYPE lengthsq = x * x + y * y + z * z;

			if (lengthsq == 0)
			{
				x = y = z = 0.0f;
				return *this;
			}

			float recip = 1 / sqrt(lengthsq);

			x *= recip;
			y *= recip;
			z *= recip;

			return *this;
		}

	};

	struct vec4
	{
		union {
			MTYPE values[4];
			struct { MTYPE x, y, z, w; };
			struct { MTYPE r, g, b, a; };
		};

		vec4() :x(0), y(0), z(0), w(0) {}
		vec4(MTYPE X) : x(X), y(X), z(X), w(X) {}
		vec4(MTYPE X, MTYPE Y, MTYPE Z, MTYPE W) : x(X), y(Y), z(Z), w(W) {}

		// Indexing
		MTYPE& operator[](unsigned short i) { ASSERT(i < 4); return values[i]; }
		const MTYPE& operator[](unsigned short i) const { ASSERT(i < 4); return values[i]; }


		// Basic vec2 + vec2 operations
		vec4& Add     (const vec4& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
		vec4& Subtract(const vec4& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
		vec4& Multiply(const vec4& other) { x *= other.x; y *= other.y; z *= other.z; w *= other.w; return *this; }
		vec4& Divide  (const vec4& other) { x /= other.x; y /= other.y; z /= other.z; w /= other.w; return *this; }

		vec4& operator+=(const vec4& other) { return Add(other); }
		vec4& operator-=(const vec4& other) { return Subtract(other); }
		vec4& operator*=(const vec4& other) { return Multiply(other); }
		vec4& operator/=(const vec4& other) { return Divide(other); }

		vec4 operator+(const vec4& other) { return vec4(x + other.x, y + other.y, z + other.z, w + other.w); }
		vec4 operator-(const vec4& other) { return vec4(x - other.x, y - other.y, z - other.z, w - other.w); }
		vec4 operator*(const vec4& other) { return vec4(x * other.x, y * other.y, z * other.z, w * other.w); }
		vec4 operator/(const vec4& other) { return vec4(x / other.x, y / other.y, z / other.z, w / other.w); }


		// Basic vec2 + scalar operations
		vec4& AddScalar       (const MTYPE& scalar) { x += scalar; y += scalar; z += scalar; w += scalar; return *this; }
		vec4& SubtractScalar  (const MTYPE& scalar) { x -= scalar; y -= scalar; z -= scalar; w -= scalar; return *this; }
		vec4& MultiplyByScalar(const MTYPE& scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
		vec4& DivideByScalar  (const MTYPE& scalar) { x /= scalar; y /= scalar; z /= scalar; w /= scalar; return *this; }

		vec4& operator+=(const MTYPE& other) { return AddScalar(other); }
		vec4& operator-=(const MTYPE& other) { return SubtractScalar(other); }
		vec4& operator*=(const MTYPE& other) { return MultiplyByScalar(other); }
		vec4& operator/=(const MTYPE& other) { return DivideByScalar(other); }

		vec4 operator+(const MTYPE& other) { return vec4(x + other, y + other, z + other, w + other); }
		vec4 operator-(const MTYPE& other) { return vec4(x - other, y - other, z - other, w - other); }
		vec4 operator*(const MTYPE& other) { return vec4(x * other, y * other, z * other, w * other); }
		vec4 operator/(const MTYPE& other) { return vec4(x / other, y / other, z / other, w / other); }

		// Other basic operations
		void Increment() { x++; y++; z++; w++; }
		void Decrement() { x--; y--; z--; w--; }
		vec4& operator++() { Increment(); return *this; }
		vec4& operator--() { Decrement(); return *this; }
		vec4  operator++(int) { vec4 temp = *this; Increment(); return temp; }
		vec4  operator--(int) { vec4 temp = *this; Decrement(); return temp; }

		bool operator==(const vec4& other) { return   x == other.x && y == other.y && z == other.z && w == other.w; }
		bool operator!=(const vec4& other) { return !(x == other.x && y == other.y && z == other.z && w == other.w); }

		friend bool operator==(const vec4& left, const vec4& right)
		{
			return   left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
		}

		friend bool operator!=(const vec4& left, const vec4& right)
		{
			return   !(left == right);
		}


		// Operations I should have studied more during my undergrad
		MTYPE Dot(const vec4& other) { return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w); }
		vec4 Cross(const vec4& other)
		{
			gtk::vec4 out;

			// x = values
			// y = values + 1
			// z = values + 2
			// w = walues + 3

			out.x = ((*(values + 1)) * (*(other.values + 2))) - ((*(values + 2)) * (*(other.values + 1)));
			out.y = ((*(values + 2)) * (*other.values)) - ((*values) * (*(other.values + 2)));
			out.z = ((*values) * (*(other.values + 1))) - ((*(values + 1)) * (*other.values));
			out.w = 0; // TODO

			return out;
		}

		MTYPE Length() const { return sqrt(x * x + y * y + z * z + w * w); }
		MTYPE LengthSquared() const { return x * x + y * y + z * z + w * w; }

		vec4& Normalize()
		{
			MTYPE lengthsq = x * x + y * y + z * z + w * w;

			if (lengthsq == 0)
			{
				x = y = z = w = 0.0f;
				return *this;
			}

			float recip = 1 / sqrt(lengthsq);

			x *= recip;
			y *= recip;
			z *= recip;
			w *= recip;

			return *this;
		}



	};



	
	struct mat2
	{
		union {
			MTYPE values[4];
			vec2 cols[2];
		};

		// Column Major Format
		// 1 3
		// 2 4
		
		mat2() : values{ 0, 0, 
						 0, 0 } {}

		mat2(MTYPE v) : values{ v, 0,
								0, v } {}

		mat2(MTYPE x0, MTYPE x1, MTYPE y0, MTYPE y1) : values{ x0, y0, 
															   x1, y1 } {}

		// Indexing
		MTYPE& operator()(unsigned short row, unsigned short column)       
		{ 
			ASSERT(column < 2 && row < 2); 
			return values[column * 2 + row];
		}
		const MTYPE& operator()(unsigned short row, unsigned short column) const 
		{ 
			ASSERT(column < 2 && row < 2); 
			return values[column * 2 + row];
		}

		vec2& operator[](unsigned short i) { ASSERT(i < 2); return cols[i]; }
		const vec2& operator[](unsigned short i) const { ASSERT(i < 2); return cols[i]; }


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
				*(values+3) + scalar
			};
		}
		mat2 operator-(const MTYPE& scalar) 
		{
			return
			{
				*(values)     - scalar,
				*(values + 1) - scalar,
				*(values + 2) - scalar,
				*(values + 3) - scalar
			};
		}
		mat2 operator*(const MTYPE& scalar)
		{
			return
			{
				*(values)     * scalar,
				*(values + 1) * scalar,
				*(values + 2) * scalar,
				*(values + 3) * scalar
			};
		}
		mat2 operator/(const MTYPE& scalar)
		{
			return
			{
				*(values)     / scalar,
				*(values + 1) / scalar,
				*(values + 2) / scalar,
				*(values + 3) / scalar
			};
		}
		
		
		//// mat2 + vec2 Operations
		
		vec2 TransformVec2(const vec2& vec)
		{
			return
			{
				// 0 2 * x  =  0*x + 2*y
				// 1 3   y     1*x + 3*y

				(*(values    )) * vec.x + (*(values + 2)) * vec.y,
				(*(values + 1)) * vec.x + (*(values + 3)) * vec.y
			};
		} vec2 operator*(const vec2& vec) { return TransformVec2(vec); }

		
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
			// TODO
			
			*this = *this * other;

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
				// 0 2 * x0 z2  =  0*x + 2*y, 0*z + 2*w
				// 1 3   y1 w3     1*x + 3*y, 1*z + 3*w

				(*(values    )) * (*(other.values    )) + (*(values + 2)) * (*(other.values + 1)), // 0*x0 + 2*y1
				(*(values    )) * (*(other.values + 2)) + (*(values + 2)) * (*(other.values + 3)), // 0*z2 + 2*w3
				(*(values + 1)) * (*(other.values    )) + (*(values + 3)) * (*(other.values + 1)), // 1*x0 + 3*y1
				(*(values + 1)) * (*(other.values + 2)) + (*(values + 3)) * (*(other.values + 3)) //  1*z2 + 3*w3
			};
		}

		// Bool Operators
		bool operator==(const mat2& other) 
		{ 
			for (int i = 0; i < 4; i++)
			{
				if (*(values + i) != *(other.values + i))
					return false;
			}

			return true;
		}
		bool operator!=(const mat2& other) { return !(*this == other); }

		friend bool operator==(const mat2& left, const mat2& right)
		{
			for (int i = 0; i < 4; i++)
			{
				if (*(left.values + i) != *(right.values + i))
					return false;
			}

			return true;
		}
		friend bool operator!=(const mat2& left, const mat2& right)
		{
			return   !(left == right);
		}
	};

}