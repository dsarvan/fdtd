/* Simulation sources */

#include <math.h>
#include "sources.h"


/**
 * Gaussian pulse source
 *
 * :param int time_step: an integer counter that serves as the temporal index
 * :param int t0: time step at which gaussian function is maximum, default 40
 * :param double spread: width of the gaussian pulse, default 12
 *
 * :return: gaussian pulse
 * :rtype: double
 */
double gaussian(struct gaussian n) {

    int t0 = n.t0 ? n.t0 : 40;
    double spread = n.spread ? n.spread : 12;
    int time_step = n.time_step ? n.time_step : 0;

    return exp(-0.5 * pow(((t0 - time_step) / spread), 2));
}

/**
 * Sinusoidal wave source
 *
 * :param int time_step: an integer counter that serves as the temporal index
 * :param double ddx: the cell size (m), default 0.01 m
 * :param double freq: frequency of the sinusoidal wave source, default 700 MHz
 *
 * :return: sinusoidal wave
 * :rtype: double
 */
double sinusoidal(struct sinusoidal n) {

    double ddx = n.ddx ? n.ddx : 0.01;
    double freq = n.freq ? n.freq : 700e6;
    int time_step = n.time_step ? n.time_step : 0;

    double dt = ddx / 6e8;

    return sin(2 * M_PI * freq * dt * time_step);
}
