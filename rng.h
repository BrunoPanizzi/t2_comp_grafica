#ifndef rng_h
#define rng_h

// include necessary libs


int randi(int min, int max);
float randf(float min, float max);
double randd(double min, double max);


#ifdef rng_impl

#include <stdlib.h>
#include <time.h>

// Seed the random number generator with the current time
void seed() {
    static int seeded = 0;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }
}

int randi(int min, int max) {
		seed();
    return min + rand() % ((max + 1) - min);
}

float randf(float min, float max) {
		seed();
    float scale = rand() / (float) RAND_MAX;
    return min + scale * (max - min);
}

double randd(double min, double max) {
		seed();
    double scale = rand() / (double) RAND_MAX;
    return min + scale * (max - min);
}


#endif // rng_impl

#endif // rng_h
