#include "Vector2.h"
#include <iostream>

template<class T>
Vector2Template<T>::Vector2Template()
{
	x = 0;
	y = 0;
}

template<class T>
Vector2Template<T>::Vector2Template(T x, T y)
{
	this-> x = x;
	this-> y = y;
}

template<class T>
Vector2Template<T>::~Vector2Template()
{

}

// ‘ã“ü
template<class T>
Vector2Template<T> & Vector2Template::operator=(const Vector2Template<T> & vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}

// ”äŠr‰‰ŽZŽq
template<class T>
bool Vector2Template::operator==(const Vector2Template<T> & vec) const
{
	return ((vec.x == x) && (vec.y == y));
}

template<class T>
bool Vector2Template::operator!=(const Vector2Template<T> & vec) const
{
	return !((vec.x == x) && (vec.y == y));
}

template<class T>
bool Vector2Template::operator>(const Vector2Template<T> & vec) const
{
	return ((vec.x > x)&&(vec.y > y));
}

template<class T>
bool Vector2Template::operator>=(const Vector2Template<T> & vec) const
{
	return ((vec.x >= x) && (vec.y >= y));;
}

template<class T>
bool Vector2Template::operator<(const Vector2Template<T> & vec) const
{
	return ((vec.x < x) && (vec.y < y));;
}

template<class T>
bool Vector2Template::operator<=(const Vector2Template<T> & vec) const
{
	return ((vec.x <= x) && (vec.y <= y));;
}

// “Y‚¦Žš‰‰ŽZ
template<class T>
int & Vector2Template::operator[](T i)
{
	if (i == 0)
	{
		return x;
	}
	else if (i == 1)
	{
		return y;
	}
	else
	{
		return x;	// —áŠOˆ—
	}
}

// ---’P€‰‰ŽZŽq
Vector2 & Vector2::operator+=(const Vector2 & vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

Vector2 & Vector2::operator-=(const Vector2 & vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

Vector2 & Vector2::operator*=(int k)
{
	x *= k;
	y *= k;
	return *this;
}

Vector2 & Vector2::operator/=(int k)
{
	x /= k;
	y /= k;
	return *this;
}

Vector2 Vector2::operator+() const
{
	return *this;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-this->x, -this->y);
}

// ---ÍÞ¸ÄÙ‚Ì‰‰ŽZ

Vector2 operator+(const Vector2& u, const int& k)
{
	Vector2 vec;
	vec.x = u.x + k;
	vec.y = u.y + k;

	return vec;
}
Vector2 operator-(const Vector2 & u, const int & k)
{
	Vector2 vec;
	vec.x = u.x - k;
	vec.y = u.y - k;

	return vec;
}
Vector2 operator%(const Vector2 & u, const int & k)
{
	Vector2 vec;
	vec.x = u.x % k;
	vec.y = u.y % k;

	return vec;
}
Vector2 operator*(const Vector2 & u, const int & k)
{
	Vector2 vec;
	vec.x = u.x * k;
	vec.y = u.y * k;

	return vec;
}
Vector2 operator/(const Vector2 & u, const int & k)
{
	Vector2 vec;
	vec.x = u.x / k;
	vec.y = u.y / k;

	return vec;
}

Vector2 operator+(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;

	return vec;
}
Vector2 operator-(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;

	return vec;
}
Vector2 operator*(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x * v.x;
	vec.y = u.y * v.y;

	return vec;
}
Vector2 operator/(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x / v.x;
	vec.y = u.y / v.y;

	return vec;
}
Vector2 operator%(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x % v.x;
	vec.y = u.y % v.y;

	return vec;
}

Vector2 operator*(const int & k, const Vector2 & u)
{
	Vector2 vec;
	vec.x = k * u.x;
	vec.y = k * u.y;

	return vec;
}