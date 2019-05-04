#pragma once
#include "Mesh.h"

class material
{
public:
	virtual bool scatter(const Ray& r_in, const hit_record& rec,
		simplevector& attenuation, Ray& scattered) const = 0;
};


// _______________ Helper functions for the lambertian class. _________________

float drand48() {
	return (rand() / (RAND_MAX + 1.0));
}

simplevector random_in_sphere() {
	simplevector random_point(2, 2, 2);
	while (random_point.squared_length() >= 1.0) {
		random_point = 2.0 * simplevector(drand48(), drand48(), drand48()) - simplevector(1, 1, 1);
	}
	return random_point;
}


// ______________________ LAMBERTIAN CLASS ______________________________

class lambertian : public material {
public:
	lambertian(const simplevector& alb) : albedo(alb) {};
	~lambertian() {};
	virtual bool scatter(const Ray& r_in, const hit_record& rec,
		simplevector& attenuation, Ray& scattered) const override {
		float p = 0.98;
		if (drand48() < p) {
			simplevector target = rec.p + rec.normal + random_in_sphere();
			scattered = Ray(rec.p, target - rec.p);
			attenuation = albedo / p;
			return true;
		}
		else {
			attenuation = albedo / p;
			return false;
		}
		return false;
	};

	simplevector albedo;
};


//  _________________ Helper Class for the metal class. ________________________

simplevector reflect(const simplevector& vec, const simplevector& normal) {
	return (vec - 2 * dot(vec, normal) * normal);
}


class metal : public material {
public:
	metal(const simplevector& alb, float fuzz) : fuzz(fuzz), albedo(alb) {};
	~metal() {};
	virtual bool scatter(const Ray& r_in, const hit_record& rec,
		simplevector& attenuation, Ray& scattered) const override {
		float p = 0.98;
		if (drand48() < p) {
			simplevector reflected = reflect(unit_vector(r_in.direction()), rec.normal);
			scattered = Ray(rec.p, reflected + fuzz*random_in_sphere());
			attenuation = albedo / p;
			return true;
		}
		else {
			attenuation = albedo / p;
			return false;
		}
		return false;
	}
	float fuzz;
	simplevector albedo;
};
