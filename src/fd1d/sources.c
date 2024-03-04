 /* Simulation sources */

#include <string.h>
#include <math.h>

int pulse(int ke, double *ex, double *hy, double *Ex, double *Hy) {
	/* Gaussian pulse source

	Args:
		ke: number of electric and magnetic field nodes
		ex: electric field oriented in the x direction
		hy: magnetic field oriented in the y direction
		Ex, Hy: stack of electric and magnetic field
	*/

	/* pulse parameters */
	int kc = ke/2;
	int t0 = 40;
	double spread = 12;
	int nsteps = 500;

	/* FDTD loop */
	for (int time_step = 1; time_step <= nsteps; time_step++) {

		/* calculate the Ex field */
		for (int k = 1; k < ke; k++)
			ex[k] = ex[k] + 0.5 * (hy[k-1] - hy[k]);

		/* put a Gaussian pulse in the middle */
		ex[kc] = exp(-0.5 * pow(((t0 - time_step)/spread), 2));

		/* calculate the Hy field */
		for (int k = 0; k < ke-1; k++)
			hy[k] = hy[k] + 0.5 * (ex[k] - ex[k+1]);

		memcpy(Ex + (time_step - 1)*ke, ex, ke*sizeof(*ex));
		memcpy(Hy + (time_step - 1)*ke, hy, ke*sizeof(*hy));
	}

	return 0;
}
