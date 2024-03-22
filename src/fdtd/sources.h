#ifndef SOURCES_H_
#define SOURCES_H_

/**
 * default values in gaussian pulse
 */
struct gaussian {
    int time_step;
    int t0;
    double spread;
};

/**
 * default values in sinusoidal
 */
struct sinusoidal {
    int time_step;
    double ddx;
    double freq;
};

double gaussian(struct gaussian n);
double sinusoidal(struct sinusoidal n);

#endif /* SOURCES_H_ */
