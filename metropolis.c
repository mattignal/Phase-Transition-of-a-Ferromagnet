/*
 * Metropolis algorithm for Ising model in two dimensions, on a rectangular grid, 
 * with periodic boundary conditions
 *
 * Inspired by: http://www.physics.buffalo.edu/phy411-506-2004/Topic3/topic3-lec3.pdf
 */

#include "ising_datastructure.h"
#include "ising.h"

#include "metropolis.h"

int metropolis_step (struct ising *model)
{

    int lx = model->Lx;
    int ly = model->Ly;
    int **s = model->s;
    gsl_rng *r = model->r;

    // choose a random spin
    int i = (int) (gsl_rng_uniform (r) * lx);
    int j = (int) (gsl_rng_uniform (r) * ly);

    // find its neighbors using periodic boundary conditions
    int iprev = (i == 0) ? lx - 1 : i - 1;
    int inext = (i == lx - 1) ? 0 : i + 1;
    int jprev = (j == 0) ? ly - 1 : j - 1;
    int jnext = (j == ly - 1) ? 0 : j + 1;

    // find sum of neighbor spins
    int sum_neighbors = s[iprev][j] + s[inext][j] + s[i][jprev] + 
                        s[i][jnext] + s[iprev][jnext] + s[inext][jprev];
    int delta_ss = 2 * s[i][j] * sum_neighbors;

    // ratio of Boltzmann factors
    double ratio = model->w[delta_ss + 12][1 + s[i][j]];

    if (gsl_rng_uniform(r) < ratio)
    {
        s[i][j] = -s[i][j];
        return 1;
    }
    else
    {
        return 0;
    }
}

double one_metropolis_step_per_spin (struct ising *model)
{
    int accepts = 0;
    double acceptance_ratio;
    int n = model->N;

    for (int i = 0; i < n; i++)
    {
        if (metropolis_step (model))
        {
            ++accepts;
        }
    }
    model->steps += 1;
    acceptance_ratio = accepts / ((double) n);

    return acceptance_ratio;
}

