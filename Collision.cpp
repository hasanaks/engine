#include "Collision.hpp"


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




bool isOverlapping(AABB* a, AABB* b)   //helper funtion
{
	Vector2f d1 = a->min - b->max;
	Vector2f d2 = b->min - a->max;

	if (d1.x() > 0 || d1.y() > 0) { return false; }
	if (d2.x() > 0 || d2.y() > 0) { return false; }
	return true;
} 


//std::vector<CollisionPoint*> Collusions;

std::vector<knife_edge> EdgeInit(std::vector<AABB*>boxes) {
	std::vector<knife_edge> elp;
	for (int i = 0; i < boxes.size(); i++)
	{
		knife_edge begin{};
		knife_edge end {};
		begin.box = boxes[i];
		begin.b = 1;
		begin.mag = begin.box->min.x();
		end.box = boxes[i];
		end.b = 0;
		end.mag = begin.box->max.x();
		elp.push_back(begin);
		elp.push_back(end);
	}
	selectionSort(elp, elp.size());
	return elp;
}//input function


std::vector<debut> relayer(std::vector<knife_edge>elp){ //inp function
	std::vector<debut> activeList;
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
	return activeList;
}


void isActive(std::vector<debut> activeList) {
	for (int i = 0; i < activeList.size(); i++) {
		AABB* b1 = activeList[i].b1;
		AABB* b2 = activeList[i].b2;
		if(!isOverlapping(b1,b2))
		{
			activeList.erase(activeList.begin()+(i-1));
			i--;
		}
	}
}

