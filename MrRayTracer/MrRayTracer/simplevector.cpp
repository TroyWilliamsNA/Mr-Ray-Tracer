#include "simplevector.h"

// _________ CONSTRUCTOR / DESTRUCTOR ____________

simplevector::simplevector()
{
	// Initalize the vector to [0,0,0]
	v[0] = 0; v[1] = 0; v[2] = 0;
}

simplevector::simplevector(float x1, float x2, float x3) {
	this->v[0] = x1;
	this->v[1] = x2;
	this->v[2] = x3;
}
simplevector::~simplevector()
{
}


// __________ Variable Access Functions _____________

float simplevector::x() const { return this->v[0]; }
float simplevector::y() const { return this->v[1]; }
float simplevector::z() const { return this->v[2]; }
float simplevector::r() const { return this->v[0]; }
float simplevector::g() const { return this->v[1]; }
float simplevector::b() const { return this->v[2]; }

// The following (+ -) are not the addition and subtraction operators
const simplevector& simplevector::operator+() const {
	return *this;
}

simplevector simplevector::operator-() const {
	return simplevector(-this->v[0], -this->v[1], -this->v[2]);
}

float simplevector::operator[](int i) const {
	return this->v[i];
}

float& simplevector::operator[](int i) {
	return this->v[i];
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

// _________ Internal Utility Functions ___________

float simplevector::squared_length() {
	float a = this->v[0];
	float b = this->v[1];
	float c = this->v[2];
	return pow(a, 2.0) + pow(b, 2.0) + pow(c, 2.0);
}

float simplevector::length() {
	return sqrt(this->squared_length());
}

void simplevector::compress_to_unit() {
	float length = this->length();
	this->v[0] /= length;
	this->v[1] /= length;
	this->v[2] /= length;
}

// __________  External Math Operators ____________

// These allow vector multiplication with vectors and scalars
// This section has poor style cause everything does exactly
// what you would expect and I just wanted it to be compact.
simplevector operator+(const simplevector& v1,const simplevector& v2) {
	return simplevector(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]); }
simplevector operator-(const simplevector& v1, const simplevector& v2) {
	return simplevector(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]); }
simplevector operator*(const simplevector& v1, const simplevector& v2) {
	return simplevector(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]); }
simplevector operator/(const simplevector& v1, const simplevector& v2) {
	return simplevector(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]); }
simplevector operator*(const simplevector& v, const float s) {
	return simplevector(v[0] * s, v[1] * s, v[2] * s); }
simplevector operator/(const simplevector& v, const float s) {
	return simplevector(v[0] / s, v[1] / s, v[2] / s); }
simplevector operator*(const float s, const simplevector& v) {
	return simplevector(v[0] * s, v[1] * s, v[2] * s); }
simplevector operator/(const float s, const simplevector& v) {
	return simplevector(v[0] / s, v[1] / s, v[2] / s); }


// _____________ External Math Functions _________________

float dot(const simplevector& v1, const simplevector& v2) {
	return ((v1[0] * v2[0]) + (v1[1] * v2[1]) + (v1[2] * v2[2]));
}

simplevector cross(const simplevector& v1, const simplevector& v2) {
	return simplevector(
		(v1[1] * v2[2] - v1[2] * v2[1]),
		(v1[2] * v2[0] - v1[0] * v2[2]),
		(v1[0] * v2[1] - v1[1] * v2[0]));
}

simplevector unit_vector(simplevector v) {
	return v / v.length();
}

// ____________ Input Output External Operators _______________

std::istream& operator>>(std::istream& in, simplevector& v) {
	in >> v[0] >> v[1] >> v[2];
	return in;
}

std::ostream& operator<<(std::ostream& out, simplevector& v) {
	out << v[0] << " " << v[1] << " " << v[2];
	return out;
}