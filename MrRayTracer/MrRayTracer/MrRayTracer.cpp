// MrRayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include "Ray.h"
#include "sphere.h"
#include "MeshList.h"
#include <vector>
#include <limits>
#include "camera.h"
#include <random>

float drand48() {
	return (rand() / (RAND_MAX + 1.0));
}

simplevector random_in_sphere() {
	std::cout << "new random" << std::endl;
	simplevector random_point(2,2,2);
	while (random_point.squared_length() >= 1.0) {
		random_point = 2.0*simplevector(drand48(), drand48(), drand48()) - simplevector(1,1,1);
	}
	return random_point;
}


simplevector color(const Ray& r, MeshList* world) {
	hit_record rec;
	if (world->hit(r, 0.001, std::numeric_limits<float>::max(), rec)) {
		simplevector target = rec.p + rec.normal + random_in_sphere();
		std::cout << "bounce " << rec.p << std::endl;
		return 0.5*color(Ray(rec.p, target-rec.p), world);
	}
	else {
		simplevector unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return ((1.0 - t) * simplevector(1.0, 1.0, 1.0) + t * simplevector(0.5, 0.7, 1.0));
	}	
}

void create_ppm() {
	std::ofstream oppm("image.ppm");
	int tx = 200;
	int ty = 100;
	int samples = 50;
	oppm << "P3\n" << tx << " " << ty << "\n255" << std::endl;

	Mesh* list[3];
	list[0] = new sphere(simplevector(0, 0, -1), 0.5);
	list[1] = new sphere(simplevector(0, -100.5, -1.0), 100);
	//list[2] = new sphere(simplevector(0, -0.5, -1.0), 0.6);
	MeshList* world = new MeshList(list, 2);

	Camera cam(simplevector(0, 0, 0), simplevector(-2, -1, -1),
			   simplevector(4.0, 0.0, 0.0), simplevector(0.0, 2.0, 0.0));
	
	for (int i = ty - 1; i >= 0; i--) {
		for (int j = 0; j < tx; j++) {
			simplevector AA_color(0, 0, 0);
			for (int s = 0; s < samples; s++) {
				float u = float(j + drand48()) / float(tx);
				float v = float(i + drand48()) / float(ty);
				Ray curr_ray = cam.get_Ray(u, v);
				simplevector p = curr_ray.p_at_t(2.0);
				simplevector ray_color = color(curr_ray, world);
				AA_color += ray_color;
			}
			AA_color /= float(samples);
			AA_color = simplevector(sqrt(AA_color[0]), sqrt(AA_color[1]), sqrt(AA_color[2]));
			int ir = int(255.99 * AA_color.r());
			int ig = int(255.99 * AA_color.g());
			int ib = int(255.99 * AA_color.b());
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
