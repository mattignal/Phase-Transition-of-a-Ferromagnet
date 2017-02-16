## Numerically Estimates Temperature of Phase Transition of 2-D Ferromagnetic Ising Model on Triangular Lattice

#### At critical (low) temperature, there is a phase transition between ferromagnetic and a paramagnetic phases of a system. 

* Monte Carlo simulations are used to evaluate this phase transition using the Ising model of a ferromagnet, which uses a random algorithm and computes averages.

* Model contains variables which denote magnetic dipole moments of atomic spins in state +1 or -1. 

* Arrangement of spins is in a triangular lattice, allowing for six nearest neighbor interactions.

* Metropolis algorithm calculates the Ising model at each step. Determines neighbors by using periodic boundary conditions and the sum of neighbor spins.

* A position on the lattice is selected, and then if the change in energy is < 0, the spin is flipped, if it is > 0 a random number is generated between 0 and 1 and is weighed against the Boltzmann Probability factor. If it is less than this, the spin is flipped.

* A new lattice is produced from the old lattice and the changes in configuration. The average magnetization and energy per spin are calculated.

* In the main function, the system is thermalized and achieves equilibrium. Production steps are performed and data is accumulated.

* The chosen grid is 64 x 64 and 60 loops are completed.

The phase transition is illustrated by the graph. Temperature is plotted between 3 and 5 Kelvin. Phase transition clearly occurs at ~3.7 Kelvin.

![alt tag](https://github.com/matthewignal/m2/blob/master/metropolis.png)
