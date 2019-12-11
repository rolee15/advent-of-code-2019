#include "Layer.h"
#include <fstream>
#include <iostream>

Layer::Layer(int width, int height)
	: _width(width), _height(height)
{
	for (int i = 0; i < _height * _width; ++i)
		_pixels.push_back(2);
}

void Layer::setPixels(std::vector<int>& p)
{
	_pixels = p;
}

int Layer::getNumberCount(int n)
{
	int cnt = 0;
	for (unsigned int i = 0; i < _pixels.size(); ++i)
	{
		if (_pixels[i] == n)
			cnt++;
	}

	return cnt;
}

int Layer::getPixel(int i, int j)
{
	return _pixels[i * _width + j];
}

void Layer::setPixel(int i, int j, int n)
{
	_pixels[i * _width + j] = n;
}

Layers::Layers(const char* input, int width, int height)
	: _width(width), _height(height)
{
	char ch;
	std::ifstream infile(input);

	int cnt = 0;
	std::vector<int> pixels;
	while (infile >> ch)
	{
		pixels.push_back(ch - 48);
		cnt++;

		if (cnt == _width * _height)
		{
			Layer* l = new Layer(_width, _height);
			l->setPixels(pixels);
			_layers.push_back(l);

			pixels.clear();
			cnt = 0;
		}
	}


	infile.close();
}

Layer* Layers::findLeastZeroes()
{
	int zeroes = INT_MAX;
	Layer* l = nullptr;

	for (unsigned int i = 0; i < _layers.size(); ++i)
	{
		if (_layers[i]->getNumberCount(0) < zeroes)
		{
			zeroes = _layers[i]->getNumberCount(0);
			l = _layers[i];
		}
	}

	return l;
}

Layer* Layers::combine()
{
	Layer* l = new Layer(_width, _height);
	for (int i = 0; i < _height; ++i)
	{
		for (int j = 0; j < _width; ++j)
		{
			int ind = 0;
			while (_layers[ind]->getPixel(i, j) == 2)
			{
				ind++;
			}

			l->setPixel(i, j, _layers[ind]->getPixel(i, j));
		}
	}

	return l;
}

std::ostream& operator<<(std::ostream& out, const Layer& l)
{
	for (int i = 0; i < l._height; ++i)
	{
		for (int j = 0; j < l._width; ++j)
		{
			out << l._pixels[i * l._width + j];
		}
		out << "\n";
	}
	
	return out;
}
