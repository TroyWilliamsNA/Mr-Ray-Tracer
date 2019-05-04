#pragma once

#include "Ray.h"

class Camera
{
public:
	simplevector position;
	simplevector LL;
	simplevector HDir;
	simplevector VDir;
	Camera(simplevector pos, simplevector lowerleft, 
		   simplevector HDirection, simplevector VDirection);
	~Camera();
	Ray get_Ray(float u, float v);
};



Camera::Camera(simplevector pos, simplevector lowerleft,
			   simplevector HDirection, simplevector VDirection)
{
	position = pos;
	LL = lowerleft;
	HDir = HDirection;
	VDir = VDirection;
}


Camera::~Camera()
{
}

Ray Camera::get_Ray(float u, float v) {
	return Ray(position, LL + (u * HDir) + (v * VDir));
}