
#include <gsl/gsl_rng.h>

struct ising
{
    int Lx;                     // number of spins in x direction 
    int Ly;                     // number of spins in y direction 
    int N;                      // total number of spins
    int steps;                  // steps so far
    int **s;                    // the spins
    double J;                   // ferromagnetic coupling
    double T;                   // temperature
    double H;                   // magnetic field
    gsl_rng *r;                 // random number generator
    unsigned long seed;         // rng seed
    double w[25][3];            // Boltzmann factors
    int **cluster;              // spin cluster labels
    double addprobability;      // probability to add like spin
};

