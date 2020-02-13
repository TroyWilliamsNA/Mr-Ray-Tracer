#pragma once

#define _USE_MATH_DEFINES
#include "Ray.h"
#include "math.h"


class Camera
{
public:
	simplevector position;
	simplevector LL;
	simplevector HDir;
	simplevector VDir;
	simplevector lookfrom;
	simplevector lookat;
	simplevector vup;
	float lens_rad;
	simplevector w, u, v;
	Camera(float fov,float aspect_ratio,
		simplevector lookfrom, simplevector lookat,
		simplevector vup, float aperature, float focus_d);
	~Camera();
	Ray get_Ray(float u, float v);
};


Camera::Camera(float fov, float aspect_ratio, simplevector lookfrom,
	simplevector lookat, simplevector vup,float aperature, float focus_d):
	lookfrom(lookfrom), lookat(lookat), vup(vup)
{
	lens_rad = aperature / 2;
	float rad = fov * M_PI / 180;
	float half_height = tan(rad / 2);
	float half_width = aspect_ratio * half_height;
	position = lookfrom;
	w = unit_vector(lookfrom - lookat);
	u = unit_vector(cross(vup, w));
	v = cross(w, u);
	LL = position - half_width*focus_d * u - half_height* focus_d * v - focus_d*w;
	HDir = 2 * half_width * u * focus_d;
	VDir = 2 * half_height * v * focus_d;
}


Camera::~Camera()
{
}

float drand49() {
	return (rand() / (RAND_MAX + 1.0));
}

simplevector rand_on_disk() {
	simplevector random_point(2, 2, 2);
	while (random_point.squared_length() >= 1) {
		random_point = 2.0 * simplevector(drand49(), drand49(), 0) - simplevector(1, 1, 0);
	}
	return random_point;
}

Ray Camera::get_Ray(float s, float t) {
	simplevector rad = lens_rad * rand_on_disk();
	simplevector offset = 0.2 * (u * rad.x() + v * rad.y());
	return Ray(position + offset, LL + (s * HDir) + (t * VDir) - position - offset);
}

