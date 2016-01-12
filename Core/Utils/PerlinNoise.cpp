#include "PerlinNoise.hpp"

namespace Core {
	namespace Utils {

		PerlinNoise::PerlinNoise(unsigned int seed) {
			// Generate a new permutation vector based on the value of seed
			p.resize(256);

			// Fill p with values from 0 to 255
			std::iota(p.begin(), p.end(), 0);

			// Initialize a random engine with seed
			std::default_random_engine engine(seed);

			// Suffle  using the above random engine
			std::shuffle(p.begin(), p.end(), engine);

			// Duplicate the permutation vector
			p.insert(p.end(), p.begin(), p.end());
		}

		// The actual method to fill values[][] with the generated noise values.
		void PerlinNoise::createNoise() {	
			// Visit every pixel of the image and assign a color generated with Perlin noise
			for (unsigned int i = 0; i < noise_height; ++i) {     // y
				for (unsigned int j = 0; j < noise_width; ++j) {  // x
					double x = (double)j / ((double)noise_width);
					double y = (double)i / ((double)noise_height);

					// Typical Perlin noise
					double n = noise(SPREAD * x, SPREAD * y, 0.8);

					// Map the values to the [0, 255] interval, for simplicity we use 
					// tones of grey
					values[j][i] = floor(MAX_HEIGHT * n);
				}
			}
		}

		// linear interpolation
		double PerlinNoise::lerp(double t, double a, double b) {
			return a + t * (b - a); 
		}

		// compute fade curves
		double PerlinNoise::fade(double t) {
			return t * t * t * (t * (t * 6 - 15) + 10);
		}

		// generate gradient value
		double PerlinNoise::grad(int hash, double x, double y, double z) {
			int h = hash & 15;
			// Convert lower 4 bits of hash inot 12 gradient directions
			double u = h < 8 ? x : y,
				v = h < 4 ? y : h == 12 || h == 14 ? x : z;
			return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
		}

		// Noise method to generate noise value by x and y. 
		// z can be chosen freely but will change the results
		double PerlinNoise::noise(double x, double y, double z) {
			// Find the unit cube that contains the point
			int X = (int)floor(x) & 255;
			int Y = (int)floor(y) & 255;
			int Z = (int)floor(z) & 255;

			// Find relative x, y,z of point in cube
			x -= floor(x);
			y -= floor(y);
			z -= floor(z);

			// Compute fade curves for each of x, y, z
			double u = fade(x);
			double v = fade(y);
			double w = fade(z);

			// Hash coordinates of the 8 cube corners
			int A = p[X] + Y;
			int AA = p[A] + Z;
			int AB = p[A + 1] + Z;
			int B = p[X + 1] + Y;
			int BA = p[B] + Z;
			int BB = p[B + 1] + Z;

			// Add blended results from 8 corners of cube
			double res = lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)), lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z))), lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1)), lerp(u, grad(p[AB + 1], x, y - 1, z - 1), grad(p[BB + 1], x - 1, y - 1, z - 1))));
			return (res + 1.0) / 2.0;
		}

		// Debug method to write all values to a .txt file
		void PerlinNoise::debugNoise() {
			ofstream myfile;
			myfile.open("input.txt");
			char buffer[10];

			for (int x = 0; x < noise_width; x++)
			{
				for (int y = 0; y < noise_height; y++)
				{
					sprintf(buffer, "%1.3f ", values[x][y]);
					myfile << buffer;
				}
				myfile << "\n";
			}
			myfile.close();
		}

		PerlinNoise::~PerlinNoise()
		{
		}
	}
}

