/* ising.c */
void precompute_boltzmann_factors(struct ising *model);
int ising_init(struct ising *model, int lx, int ly, double jc, double h, double t);
void ising_reinit(struct ising *model, double h, double t);
void ising_free(struct ising model);
double magnetization_per_spin(struct ising *model);
double energy_per_spin(struct ising *model);
