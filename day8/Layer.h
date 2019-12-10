#pragma once
#include <vector>
#include <ostream>
class Layer
{
	std::vector<int> _pixels;

	int _width;

	int _height;

public:
	
	Layer(int width, int height);

	void setPixels(std::vector<int>& p);

	int getNumberCount(int n);

	int getPixel(int i, int j);

	friend std::ostream& operator<<(std::ostream& out, const Layer& l);
};

class Layers
{
	std::vector<Layer*> _layers;

	int _width;

	int _height;

public:

	Layers(const char* input, int width, int height);

	Layer* findLeastZeroes();

	Layer* combine();
};
