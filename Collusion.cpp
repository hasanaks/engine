#include "Collusion.hpp"




void swap(knife_edge* xp, knife_edge* yp)
{
	knife_edge temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selectionSort(std::vector<knife_edge>arr, int n)
{
	int i, j, min_idx;
	// One by one move boundary of 
	// unsorted subarray 
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in 
		// unsorted array 
		min_idx = i;
		for (j = i + 1; j < n; j++)
		{
			if (arr[j].mag < arr[min_idx].mag)
				min_idx = j;
		}
		// Swap the found minimum element 
		// with the first element 
		if (min_idx != i)
			swap(&arr[min_idx], &arr[i]);
	}
}

std::vector<AABB*> boxes;
std::vector<knife_edge> elp;
bool isOverlapping(AABB* a, AABB* b) {
	Vector2f d1 = a->min - b->max;
	Vector2f d2 = b->min - a->max;

	if (d1.x > 0 || d1.y > 0) { return false; }
	if (d2.x > 0 || d2.y > 0) { return false; }
	return true;
}

std::vector<debut> activeList;
std::vector<CollisionPoint*> Collusions;

void EdgeInit() {
	for (int i = 0; i < boxes.size(); i++)
	{
		knife_edge begin{};
		knife_edge end {};
		begin.box = boxes[i];
		begin.b = 1;
		begin.mag = begin.box->min.x;
		end.box = boxes[i];
		end.b = 0;
		end.mag = begin.box->max.x;
		elp.push_back(begin);
		elp.push_back(end);
	}
	selectionSort(elp, elp.size());
}
	void relayer(){
	int id = 0;
	while (id<elp.size()-1)
	{
		if(elp[id].b!=1)
		{
			id++;
			continue;
		}
		int count = id+1;
		knife_edge* key=&elp[id];
		knife_edge* lock=&elp[count];
		while (key->box!=lock->box)
		{
			if (lock->b == 0) { count++; }
			else if (lock->b == 1) {
				debut temp{};
				temp.b1 = key->box;
				temp.b2 = lock->box;
				activeList.push_back(temp);
				count++;

			}
		}

		id++;
	}

}


void isActive() {
	for (int i = 0; i < activeList.size(); i++) {
		AABB* b1 = activeList[0].b1;
		AABB* b2 = activeList[0].b2;
		if(isOverlapping(b1,b2))
		{
			Vector2f d1 = b1->min - b2->max;
			Vector2f d2 = b2->min - b2->max;
			float dis=0.0;
			if (d1.x < 0 && d1.y < 0) { dis=pow(pow(d1.x,2)+pow(d1.y,2),0.5f); }
			if (d2.x < 0 && d2.y < 0) { dis=pow((d2.x, 2) + pow(d2.y, 2), 0.5f); }
			CollisionPoint* col{};
			col->bx1 = b1;
			col->bx2 = b2;
			col->depth = dis;
			Collusions.push_back(col);
		}
	}
}

int narrowPhase(AABB* b1, AABB* b2) {

	//will be done
	return 0;
}