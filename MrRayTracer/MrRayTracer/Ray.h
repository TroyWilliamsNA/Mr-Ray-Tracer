#pragma once
#include "simplevector.h"

struct Ray {

	Ray() {}
	Ray(const simplevector& Origin, const simplevector& Direction) {
		O = Origin;
		D = Direction;
	}

	simplevector origin() const { return O; }
	simplevector direction() const { return D; }
	simplevector p_at_t(float t) const { return O + (t * D); }

	simplevector O;
	simplevector D;
};