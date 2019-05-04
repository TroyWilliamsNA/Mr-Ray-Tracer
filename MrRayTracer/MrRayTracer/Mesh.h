#pragma once
#include "Ray.h"


struct hit_record {
	float t;
	simplevector p;
	simplevector normal;
};

class Mesh
{
public:
	virtual bool hit(const Ray& r, float min_t, float max_t, hit_record& rec) const = 0;
};

