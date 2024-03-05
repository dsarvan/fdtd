 /* Simulation sources */

#include <string.h>
#include <math.h>

int pulse(int ke, double *ex, double *hy, double *Ex, double *Hy) {
    /* Gaussian pulse source

       :param int ke: number of electric and magnetic field nodes
       :param double *ex: electric field oriented in the x direction
       :param double *hy: magnetic field oriented in the y direction

       :return: *Ex, *Hy: stack of electric and magnetic field
    */

    /* pulse parameters */
    int kc = ke / 2;
    int t0 = 40;
    double spread = 12;
    int nsteps = 500;

    double lbound[2] = {0, 0};
    double hbound[2] = {0, 0};

    /* FDTD loop */
    for (int time_step = 1; time_step <= nsteps; time_step++) {

	    /* calculate the Ex field */
	    for (int k = 1; k < ke; ex[k] = ex[k] + 0.5 * (hy[k-1] - hy[k]), k++);

	    /* put a Gaussian pulse in the middle */
	    ex[kc] = ex[kc] + exp(-0.5 * pow(((t0 - time_step) / spread), 2));

	    /* absorbing boundary conditions */
	    ex[0] = lbound[0], lbound[0] = lbound[1], lbound[1] = ex[1];
	    ex[ke-1] = hbound[0], hbound[0] = hbound[1], hbound[1] = ex[ke-2];

	    /* calculate the Hy field */
	    for (int k = 0; k < ke - 1; hy[k] = hy[k] + 0.5 * (ex[k] - ex[k+1]), k++);

	    memcpy(Ex + (time_step - 1) * ke, ex, ke * sizeof(*ex));
	    memcpy(Hy + (time_step - 1) * ke, hy, ke * sizeof(*hy));
    }

    return 0;
}

int sinusoidal(int ke, double *ex, double *hy, double *Ex, double *Hy) {
    /* Sinusoidal wave source

       :param int ke: number of electric and magnetic field nodes
       :param double *ex: electric field oriented in the x direction
       :param double *hy: magnetic field oriented in the y direction

       :return: *Ex, *Hy: stack of electric and magnetic field
    */

    /* wave parameters */
    float ddx = 0.01;
    float dt = ddx / 6e8;
    float freq = 700e6;
    int nsteps = 500;

    double lbound[2] = {0, 0};
    double hbound[2] = {0, 0};

    /* FDTD loop */
    for (int time_step = 1; time_step <= nsteps; time_step++) {

	    /* calculate the Ex field */
	    for (int k = 1; k < ke; ex[k] = ex[k] + 0.5 * (hy[k-1] - hy[k]), k++);

	    /* put a sinusoidal wave */
	    ex[1] = ex[1] + sin(2 * 3.1415 * freq * dt * time_step);

	    /* absorbing boundary conditions */
	    ex[0] = lbound[0], lbound[0] = lbound[1], lbound[1] = ex[1];
	    ex[ke-1] = hbound[0], hbound[0] = hbound[1], hbound[1] = ex[ke-2];

	    /* calculate the Hy field */
	    for (int k = 0; k < ke - 1; hy[k] = hy[k] + 0.5 * (ex[k] - ex[k+1]), k++);

	    memcpy(Ex + (time_step - 1) * ke, ex, ke * sizeof(*ex));
	    memcpy(Hy + (time_step - 1) * ke, hy, ke * sizeof(*hy));
    }

    return 0;
}
