#include "tools.h"
#include <stdio.h>
#include <tgmath.h>

void throw() {
    int *ptr = NULL;
    printf("%d", *ptr); // Cause a segfault
}

RGB_Color HSL_to_RGB(double h, double s, double l) {
    double c = (1 - fabs(2 * l - 1)) * s;
    double hp = h / 60.0;
    double x = c * (1 - fabs(fmod(hp, 2) - 1));
    double r1, g1, b1;

    if (0 <= hp && hp < 1) {
        r1 = c; g1 = x; b1 = 0;
    } else if (1 <= hp && hp < 2) {
        r1 = x; g1 = c; b1 = 0;
    } else if (2 <= hp && hp < 3) {
        r1 = 0; g1 = c; b1 = x;
    } else if (3 <= hp && hp < 4) {
        r1 = 0; g1 = x; b1 = c;
    } else if (4 <= hp && hp < 5) {
        r1 = x; g1 = 0; b1 = c;
    } else if (5 <= hp && hp < 6) {
        r1 = c; g1 = 0; b1 = x;
    } else {
        throw();
    }

    double m = l - c / 2.0;
    RGB_Color result = { r1 + m, g1 + m, b1 + m };
    return result;
}