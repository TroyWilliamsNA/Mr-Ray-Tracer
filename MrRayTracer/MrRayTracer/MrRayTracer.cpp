// MrRayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include "Ray.h"


simplevector color(const Ray& r) {
	simplevector unit_direction = unit_vector(r.direction());
	float t = 0.5 * (unit_direction.y() + 1.0);
	return ((1.0 - t) * simplevector(1.0, 1.0, 1.0) + t * simplevector(0.5, 0.7, 1.0));
}

void create_ppm() {
	std::ofstream oppm("image.ppm");
	int tx = 200;
	int ty = 100;
	oppm << "P3\n" << tx << " " << ty << "\n255" << std::endl;
	simplevector bot_left_corner(-2.0, -1.0, -1.0);
	simplevector horizontal(4.0, 0.0, 0.0);
	simplevector vertical(0.0, 2.0, 0.0);
	simplevector origin(0.0, 0.0, 0.0);
	for (int i = ty - 1; i >= 0; i--) {
		for (int j = 0; j < tx; j++) {
			float u = float(j) / float(tx);
			float v = float(i) / float(ty);
			Ray curr_ray(origin, bot_left_corner + (u * horizontal) + (v * vertical));
			simplevector ray_color = color(curr_ray);
			int ir = int(255.99 * ray_color.r());
			int ig = int(255.99 * ray_color.g());
			int ib = int(255.99 * ray_color.b());
			oppm << ir << " " << ig << " " << ib << std::endl;
		}
	}
}


int main()
{
    std::cout << "Hello MrRay!!\n"; 
	create_ppm();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
