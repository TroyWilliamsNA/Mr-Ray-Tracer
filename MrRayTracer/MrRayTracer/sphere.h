#pragma once
#include "Mesh.h"


class sphere : public Mesh {
public:
	sphere();
	sphere(simplevector center, float r, material* mat) : center(center), radius(r), mat(mat) {}
	~sphere() { delete mat; }
	virtual bool hit(const Ray& r, float min_t, float max_t, hit_record& rec) const;
	material* mat;
	simplevector center;
	float radius;
};


bool sphere::hit(const Ray& r, float min_t, float max_t, hit_record& rec) const {
	float A = dot(r.direction(), r.direction());
	float B = 2 * dot(r.origin() - center, r.direction());
	float C = (dot(r.origin() - center, r.origin() - center) - (radius * radius));
	float desc = (B * B - (4 * A * C));
	if (desc > 0) {
		float t = (-B - sqrt(desc)) / (2*A);
		if ((t < max_t) && (t > min_t)) {
			rec.t = t;
			rec.p = r.p_at_t(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat;
			return true;
		}
		t = (-B + sqrt(desc)) / (2*A);
		if ((t < max_t) && (t > min_t)) {
			rec.t = t;
			rec.p = r.p_at_t(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat;
			return true;
		}
	}
	return false;
}
