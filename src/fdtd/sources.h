#ifndef SOURCES_H_
#define SOURCES_H_

/**
 * default values in gaussian pulse
 */
struct gaussian {
    int t;
    int t0;
    double sigma;
};

/**
 * default values in sinusoidal
 */
struct sinusoidal {
    int t;
    double ddx;
    double freq;
};

double gaussian(struct gaussian n);
double normalized_gaussian(struct gaussian n);
double sinusoidal(struct sinusoidal n);

#endif /* SOURCES_H_ */
