#pragma once

#define NOISE_MAX_WIDTH		1000
#define NOISE_MAX_HEIGHT	1000

#define NOISE_WIDTH			10
#define NOISE_HEIGHT		10

#define SEED			12345
#define MAX_HEIGHT		30
#define SPREAD			100

#include <random>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <string>

// PerlinNoise implemented with the help of https://github.com/sol-prog/Perlin_Noise GPLv3
namespace Core {
	namespace Utils {
		using namespace std;
		class PerlinNoise
		{
		std::vector<int> p;

		private:
			double fade(double t);
			double grad(int hash, double x, double y, double z);
			double lerp(double t, double a, double b);
			double noise(double x, double y, double z);
		public:
			PerlinNoise(unsigned int seed); // @TODO constants to constructor parameters? 
											// (like SPREAD, MAX_HEIGHT, noise_width, noise_height)
			void createNoise(double deltaX, double deltaY);
			void debugNoise(unsigned int nr); // helper function to write output values to .txt file
			double values[NOISE_WIDTH][NOISE_HEIGHT]; // @TODO getNoise() and move values to private
			~PerlinNoise();
		};
	}
}


