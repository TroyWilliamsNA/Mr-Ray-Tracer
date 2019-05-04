#pragma once
#include "Mesh.h"

class MeshList
{
public:
	MeshList();
	MeshList(Mesh** l, int n) { list = l; list_size = n; }
	~MeshList();
	virtual bool hit(const Ray& r, float min_t, float max_t, hit_record& rec) const;
	Mesh** list;
	int list_size;
};

bool MeshList::hit(const Ray& r, float min_t, float max_t, hit_record& rec) const {
	hit_record potential_record;
	bool hit_anything = false;
	double closest_so_far = max_t;
	for (int i = 0; i < list_size; i++) {
		if (list[i]->hit(r, min_t, closest_so_far, potential_record)) {
			hit_anything = true;
			closest_so_far = potential_record.t;
			rec = potential_record;
		}
	}
	return hit_anything;
}