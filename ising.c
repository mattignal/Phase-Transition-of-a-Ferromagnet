/*
 * Ising Model in two dimensions, on a rectangular grid, with periodic boundary conditions
 *
 * Inspired by: http://www.physics.buffalo.edu/phy411-506-2004/Topic3/topic3-lec3.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ising_datastructure.h"
#include "ising.h"
#include "matrixmem.h"

void precompute_boltzmann_factors (struct ising *model)
{
    double t = model->T;
    double j = model->J;
    double h = model->H;
    for (int i = -12; i <= 12; i += 4)
    {
        model->w[i + 12][0] = exp (-(i * j + 2 * h) / t);
        model->w[i + 12][2] = exp (-(i * j - 2 * h) / t);
    }
}

int ising_init (struct ising *model, int lx, int ly, double jc, double h, double t)
{
    model->J = jc;               // ferromagnetic coupling
    model->T = t;                // temperature
    model->H = h;                // magnetic field
    model->Lx = lx;              // number of spins in x direction 
    model->Ly = ly;              // number of spins in y direction 
    model->N = lx * ly;          // number of spins
    model->steps = 0;            // steps so far

    /* allocate random number generator */
    gsl_rng *r = gsl_rng_alloc(gsl_rng_taus2);
    model->r = r;

    /* seed the random number generator */
    unsigned long seed = 1UL;
    gsl_rng_set(r, seed);
    model->seed = seed;
    model->cluster = NULL;

    int **s = matrix_allocate_int (lx, ly);
    if (s == NULL)
    {
        return -1;
    }

    model->s = s;
    for (int i = 0; i < lx; i++)
    {
        for (int j = 0; j < ly; j++)
        {
            //s[i][j] = (gsl_rng_uniform(r) < 0.5) ? 1 : -1;        // hot start
            s[i][j] = 1;                                            // cold start
        }
    }

    precompute_boltzmann_factors (model);

    return 0;
}

void ising_reinit (struct ising *model, double h, double t)
{
    model->T = t;                // temperature
    model->H = h;                // magnetic field

    precompute_boltzmann_factors (model);
}

void ising_free (struct ising model)
{
    if (model.cluster != NULL)
    {
        matrix_free (model.cluster);
    }
    matrix_free (model.s);
    gsl_rng_free (model.r);
}

double magnetization_per_spin (struct ising *model)
{
    int sum = 0;
    int **s = model->s;
    int lx = model->Lx;
    int ly = model->Ly;

    for (int i = 0; i < lx; i++)
    {
        for (int j = 0; j < ly; j++)
        {
            sum += s[i][j];
        }
    }
    return sum / ((double) model->N);
}

double energy_per_spin (struct ising *model)
{
    int sum = 0, ssum = 0;
    int **s = model->s;
    int lx = model->Lx;
    int ly = model->Ly;

    for (int i = 0; i < lx; i++)
    {
        for (int j = 0; j < ly; j++)
        {
            sum += s[i][j];
            int inext = (i == lx - 1) ? 0 : i + 1;
            int jnext = (j == ly - 1) ? 0 : j + 1;
            int iprev = (i == 0) ? lx - 1 : i - 1;
            //int jprev = (j == 0) ? ly - 1 : j - 1;

            ssum += s[i][j] * (s[inext][j] + s[i][jnext] + s[iprev][jnext]);
        }
    }
    return -(model->J * ssum + model->H * sum) / model->N;
}
