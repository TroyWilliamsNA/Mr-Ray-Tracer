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


// ____________________________ METAL MATERIAL _________________________________

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


// ___________ dielectric Helper Functions ___________________

bool refract(const simplevector& dir, const simplevector& norm,
	float n_ratio, simplevector& refracted) {
	simplevector unit = unit_vector(dir);
	float dt = dot(unit, norm);
	float discriminant = 1.0 - n_ratio * n_ratio * (1 - dt * dt);
	if (discriminant > 0) {
		refracted = n_ratio * (unit - norm * dt) - norm * sqrt(discriminant);
		return true;
	}
	else {
		return false;
	}
}

float schlick(float cosine, float ref_idx) {
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}


// ________________________ DIALETRIC MATERIAL _____________________________

class dielectric : public material {
public:
	dielectric(simplevector alb, float refractive_index) : ref_idx(refractive_index), albedo(alb) {};
	~dielectric() {};

	virtual bool scatter(const Ray& r_in, const hit_record& rec,
		simplevector& attenuation, Ray& scattered) const override {


		
		simplevector outward_normal;
		simplevector reflected = reflect(r_in.direction(), rec.normal);
		float n_ratio;
		attenuation = albedo;
		simplevector refracted;
		float reflect_probability;
		float cosine;
		if (dot(r_in.direction(), rec.normal) > 0) {
			outward_normal = -rec.normal;
			n_ratio = ref_idx;
			//cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
			cosine = dot(r_in.direction(), rec.normal) / r_in.direction().length();
			cosine = sqrt(1 - ref_idx * ref_idx * (1 - cosine * cosine));
		}
		else {
			outward_normal = rec.normal;
			n_ratio = (1.0 / ref_idx);
			cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}
		if (refract(r_in.direction(), outward_normal, n_ratio, refracted)) {
			reflect_probability = schlick(cosine, ref_idx);
		}
		else {
			reflect_probability = 1.0;
			return false;
		}
		if (drand48() < reflect_probability) {
			simplevector reflected = reflect(r_in.direction(), rec.normal);
			scattered = Ray(rec.p, reflected);
		} 
		else {
			scattered = Ray(rec.p, refracted);
		}
		return true;
	}
	
	
	float ref_idx;
	simplevector albedo;
};
