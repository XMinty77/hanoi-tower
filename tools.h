#ifndef HANOITOWER_TOOLS_H
#define HANOITOWER_TOOLS_H

typedef enum {
    A, B, C
} Towers;

typedef struct {
    double R, G, B;
} RGB_Color;

void throw();
RGB_Color HSL_to_RGB(double h, double s, double l);

#endif //HANOITOWER_TOOLS_H