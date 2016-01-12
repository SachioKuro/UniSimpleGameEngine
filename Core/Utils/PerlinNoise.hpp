#pragma once

#define noise_width		100
#define noise_height	100

#define SEED			12345
#define MAX_HEIGHT		10
#define SPREAD			5

#include <random>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <numeric>

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
			void createNoise();
			void debugNoise(); // helper function to write output values to .txt file
			double values[noise_width][noise_height]; // @TODO getNoise() and move values to private
			~PerlinNoise();
		};
	}
}


