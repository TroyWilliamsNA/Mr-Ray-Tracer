#pragma once

#include <math.h>
#include <stdio.h>
#include <iostream>

class simplevector
{
private:
	float x[3];
public:
	simplevector();
	simplevector(float x1, float x2, float x3);
	~simplevector();

	float x();
	float y();
	float z();
	float r();
	float b();
	float g();

	const simplevector& operator+() const;
	simplevector operator-() const; 
	float operator[](int i) const;
	float& operator[](int i);

	simplevector& operator+=(const simplevector& other);
	simplevector& operator-=(const simplevector& other);
	simplevector& operator*=(const simplevector& other);
	simplevector& operator/=(const simplevector& other);
	simplevector& operator*=(const float scalar);
	simplevector& operator/=(const float scalar);

	float length();
	float squared_length();
	void compress_to_unit();
};

simplevector operator+(const simplevector& v1, const simplevector& v2);
simplevector operator-(const simplevector& v1, const simplevector& v2);
simplevector operator*(const simplevector& v1, const simplevector& v2);
simplevector operator/(const simplevector& v1, const simplevector& v2);

simplevector operator*(const simplevector& v, const float s);
simplevector operator/(const simplevector& v, const float s);
simplevector operator*(const float s, const simplevector& v);
simplevector operator/(const float s, const simplevector& v);

simplevector dot(const simplevector& v1, const simplevector& v2);
simplevector cross(const simplevector& v1, const simplevector& v2);

std::istream& operator>>(std::istream& is, simplevector& v);
std::ostream& operator<<(std::ostream& os, simplevector& v);