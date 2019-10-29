#pragma once

// ÃÝÌßÚ°Ä‰»‚µ‚Ü
template<class T> class Vector2Template
{
public:
	Vector2Template();
	Vector2Template(T x, T y);
	~Vector2Template();
	int x;
	int y;

	// ‘ã“ü‰‰ŽZŽq
	Vector2Template& operator = (const Vector2Template& vec);

	// ”äŠr‰‰ŽZŽq
	bool operator == (const Vector2Template& vec)const;
	bool operator != (const Vector2Template& vec)const;
	bool operator > (const Vector2Template& vec)const;
	bool operator >= (const Vector2Template& vec)const;
	bool operator < (const Vector2Template& vec)const;
	bool operator <= (const Vector2Template& vec)const;
	
	// “Y‚¦Žš‰‰ŽZŽq
	T& operator [] (T i);

	// ’P€‰‰ŽZŽq
	Vector2Template& operator += (const Vector2Template& vec);
	Vector2Template& operator -= (const Vector2Template& vec);
	Vector2Template& operator *= (int k);
	Vector2Template& operator /= (int k);

	Vector2Template operator + ()const;
	Vector2Template operator - ()const;
};

// ÍÞ¸ÄÙ‚Ì‰‰ŽZ

// Vector2 + int
template<class T>
Vector2Template<T> operator +(const Vector2Template& u, const T& k);
// Vector2 - int
template<class T>
Vector2Template<T> operator -(const Vector2Template& u, const T& k);
// Vector2 * int
template<class T>
Vector2Template<T> operator *(const Vector2Template& u, const T& k);
// Vector2 / int
template<class T>
Vector2Template<T> operator /(const Vector2Template& u, const T& k);
// Vector2 % int
template<class T>
Vector2Template<T> operator %(const Vector2Template& u, const T& k);

// Vector2 + Vector2
template<class T>
Vector2Template<T> operator +(const Vector2Template& u, const Vector2Template& v);
// Vector2 - Vector2
template<class T>
Vector2Template<T> operator -(const Vector2Template& u, const Vector2Template& v);
// Vector2 * Vector2
template<class T>
Vector2Template<T> operator *(const Vector2Template& u, const Vector2Template& v);
// Vector2 / Vector2
template<class T>
Vector2Template<T> operator /(const Vector2Template& u, const Vector2Template& v);
// Vector2 % Vector2
template<class T>
Vector2Template<T> operator %(const Vector2Template& u, const Vector2Template& v);

// int * Vector2
template<class T>
Vector2Template<T> operator *(const T& k, const Vector2Template& u);



#include "./detelas/Vector2.h"