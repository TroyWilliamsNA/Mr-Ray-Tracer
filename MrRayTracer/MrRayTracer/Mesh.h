#pragma once
#include "Ray.h"


class material;

struct hit_record {
	float t;
	simplevector p;
	simplevector normal;
	material* mat_ptr;
};

class Mesh
{
public:
	virtual bool hit(const Ray& r, float min_t, float max_t, hit_record& rec) const = 0;
};

