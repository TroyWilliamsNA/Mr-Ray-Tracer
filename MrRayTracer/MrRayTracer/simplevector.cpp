#include "simplevector.h"

// _________ CONSTRUCTOR / DESTRUCTOR ____________

simplevector::simplevector()
{
}

simplevector::simplevector(float x1, float x2, float x3) {
	this->x[0] = x1;
	this->x[1] = x2;
	this->x[3] = x3;
}
simplevector::~simplevector()
{
}


// __________ VARIABLE ACCESS FUNCTIONS _____________

float simplevector::x() { return this->x[0]; }
float simplevector::y() { return this->x[1]; }
float simplevector::z() { return this->x[2]; }
float simplevector::r() { return this->x[0]; }
float simplevector::g() { return this->x[1]; }
float simplevector::b() { return this->x[2]; }

const simplevector& simplevector::operator+() const {
	return *this;
}

simplevector simplevector::operator-() const {
	return simplevector(-this->x[0], -this->x[1], -this->x[2]);
}

float simplevector::operator[](int i) const {
	return this->x[i];
}

float& simplevector::operator[](int i) {
	return this->x[i];
}

// ____________ Internal Math Operators _______________

simplevector& simplevector::operator+=(const simplevector& other) 
{
	(*this)[0] += other[0];
	(*this)[1] += other[1];
	(*this)[2] += other[2];
	return *this;
}

simplevector& simplevector::operator-=(const simplevector& other)
{
	(*this)[0] -= other[0];
	(*this)[1] -= other[1];
	(*this)[2] -= other[2];
	return *this;
}

simplevector& simplevector::operator*=(const simplevector& other)
{
	(*this)[0] *= other[0];
	(*this)[1] *= other[1];
	(*this)[2] *= other[2];
	return *this;
}

simplevector& simplevector::operator/=(const simplevector& other)
{
	(*this)[0] /= other[0];
	(*this)[1] /= other[1];
	(*this)[2] /= other[2];
	return *this;
}

simplevector& simplevector::operator*=(const float scalar) {
	(*this)[0] *= scalar;
	(*this)[0] *= scalar;
	(*this)[0] *= scalar;
	return *this;
}

simplevector& simplevector::operator/=(const float scalar) {
	(*this)[0] /= scalar;
	(*this)[0] /= scalar;
	(*this)[0] /= scalar;
	return *this;
}