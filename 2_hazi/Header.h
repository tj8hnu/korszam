// This file contains the vector2 struct

#include <iostream>
#include <cmath>


template<typename T>
struct Vector2
{
	T x, y;

	// Inner functions


	Vector2<T>& operator+=(Vector2<T> const& v)
	{
		x += v.x; y += v.y; 
		return *this;
	}

	Vector2<T>& operator-=(Vector2<T> const& v)
	{
		x -= v.x; y -= v.y;
		return *this;
	}

	Vector2<T>& operator*=(T lambda)
	{
		x *= lambda; y *= lambda;
		return *this;
	}

	Vector2<T>& operator/=(T lambda)
	{
		x /= lambda; y /= lambda;
		return *this;
	}

};


// Outer functions

template<typename T>
std::ostream& operator <<(std::ostream& o, Vector2<T> const& v)
{
	o << v.x << "   " << v.y;
	return o;
};

template<typename T>
std::istream& operator >>(std::istream& i, Vector2<T>& v)
{
	i >> v.x;
	i >> v.y;
	return i;
}

template<typename T>
Vector2<T> operator + (Vector2<T> const& a, Vector2<T> const& b)
{
	return Vector2<T>{ a.x + b.x, a.y + b.y };
};

template<typename T>
Vector2<T> operator - (Vector2<T> const& a, Vector2<T> const& b)
{
	return Vector2<T>{ a.x - b.x, a.y - b.y };
};

template<typename T>
Vector2<T> operator* (Vector2<T> const& a, T lambda)
{
	return Vector2<T>{ a.x* lambda, a.y* lambda };
};

template<typename T>
Vector2<T> operator* (T lambda, Vector2<T> const& a)
{
	return Vector2<T>{ lambda* a.x, lambda* a.y };
};

template<typename T>
Vector2<T> operator/ (Vector2<T> const& a, T lambda)
{
	return Vector2<T>{ a.x / lambda, a.y / lambda };
};

template<typename T>
T dot(Vector2<T> const& a, Vector2<T> const& b)
{
	return a.x * b.x + a.y * b.y;
};

template<typename T>
T length(Vector2<T> const& a)
{
	return sqrt(a.x * a.x + a.y * a.y);
};

template<typename T>
T sqlength(Vector2<T> const& a)
{
	return a.x * a.x + a.y * a.y;
};

template<typename T>
Vector2<T> normalize(Vector2<T> const& a)
{
	return Vector2<T>{ a.x / sqrt(a.x * a.x + a.y * a.y), a.y / sqrt(a.x * a.x + a.y * a.y) };
};