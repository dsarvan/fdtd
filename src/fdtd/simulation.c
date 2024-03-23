/* FDTD simulation */

#include <string.h>
#include "sources.h"

#define pulse(...) pulse((struct pulse){__VA_ARGS__});
#define sinusoidal(...) sinusoidal((struct sinusoidal){__VA_ARGS__});

/**
 * Finite-difference time-domain method
 *
 * :param int ke: number of electric and magnetic field nodes
 * :param double *ex: electric field oriented in the x direction
 * :param double *hy: magnetic field oriented in the y direction
 *
 * :return: *Ex, *Hy: stack of electric and magnetic field
 */
int simulate(int ke, double *ex, double *hy, double *Ex, double *Hy) {

    int nsteps = 500;

    double lbound[2] = {0, 0};
    double hbound[2] = {0, 0};

    /* FDTD simulation loop */
    for (int t = 1; t <= nsteps; t++) {

	    /* calculate the Ex field */
	    for (int k = 1; k < ke; ex[k] = ex[k] + 0.5 * (hy[k-1] - hy[k]), k++);

	    /* sinusoidal wave source (frequency 1900 MHz) */
	    ex[1] = ex[1] + sinusoidal(t, .freq = 1900e6);

	    /* absorbing boundary conditions */
	    ex[0] = lbound[0], lbound[0] = lbound[1], lbound[1] = ex[1];
	    ex[ke-1] = hbound[0], hbound[0] = hbound[1], hbound[1] = ex[ke-2];

	    /* calculate the Hy field */
	    for (int k = 0; k < ke - 1; hy[k] = hy[k] + 0.5 * (ex[k] - ex[k+1]), k++);

	    memcpy(Ex + (t - 1) * ke, ex, ke * sizeof(*ex));
	    memcpy(Hy + (t - 1) * ke, hy, ke * sizeof(*hy));
    }

    return 0;
}
