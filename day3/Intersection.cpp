#include "Intersection.h"

Intersection::Intersection(Wire& wl, Wire& wr)
	: w1(wl), w2(wr)
{
}

int Intersection::minsteps()
{
	int minsteps = INT_MAX;

	std::vector<Node> v = w1.crosspoints(w2);

	for (int i = 0; i < v.size(); ++i)
	{
		int dist1 = w1.distance(v[i]);
		int dist2 = w2.distance(v[i]);

		if (dist1 + dist2 < minsteps)
			minsteps = dist1 + dist2;
	}

	return minsteps;
}
