# m2
Numerically Estimates Temperature of Phase Transition of 2-D Ferromagnetic Ising Model on Triangular Lattice

Model contains variables which denote magnetic dipole moments of atomic spins in state +1 or -1.

Arrangement of spins is in a triangular lattice, allowing for nearest neighbor interactions.

Monte Carlo Methods for Ising Model of a Ferromagnet are used. Random variables are used in concert with stochastic simulation.

Metropolis algorithm calculates Ising model. Determines neighbors by using periodic boundary conditions and the sum of neighbor spins.

A position on the lattice is selected, and then if the change in energy is < 0, the spin is flipped, if it is > 0 a random number is generated between 0 and 1 and is weighed against the Boltzmann Probability factor. If it is less than this, the spin is flipped.

A new lattice is produced from the old lattice and the changes in configuration.

Phase transition is illustrated by graph. Temperature is plotted between 3 and 5 Kelvin. Phase transition clearly occurs at ~3.7 Kelvin.

Grid is 64 x 64 and 60 loops are completed.
