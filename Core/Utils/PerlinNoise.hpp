#pragma once

#define NOISE_MAX_WIDTH		100000
#define NOISE_MAX_HEIGHT	100000

#define NOISE_WIDTH			10
#define NOISE_HEIGHT		10

#define SEED			12345
#define MAX_HEIGHT		15
#define SPREAD			10000

#include <random>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

// PerlinNoise implemented with the help of https://github.com/sol-prog/Perlin_Noise GPLv3
namespace Core {
	namespace Utils {
		using namespace std;
		class PerlinNoise
		{
		private:
			vector<int> p;
			unsigned int segmentWidth, segmentHeight;
			unsigned int maxNoiseWidth, maxNoiseHeight;
			unsigned int height, spread;
		private:
			double fade(double t);
			double grad(int hash, double x, double y, double z);
			double lerp(double t, double a, double b);
			double noise(double x, double y, double z);
			vector<vector<double>> values;
		public:
			PerlinNoise(unsigned int seed, unsigned int maxNoiseWidth, unsigned int maxNoiseHeight, unsigned int segmentWidth, unsigned int segmentHeight, unsigned int height, unsigned int spread); // @TODO constants to constructor parameters? 
											// (like SPREAD, MAX_HEIGHT, noise_width, noise_height)
			vector<vector<double>>* createNoise(unsigned int deltaX, unsigned int deltaY);
			void debugNoise(unsigned int nr); // helper function to write output values to .txt file
			~PerlinNoise();
		};
	}
}


