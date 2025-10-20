#ifndef HANOITOWER_SOLVE_H
#define HANOITOWER_SOLVE_H

#include "tools.h"

void solve_dispose();
int **solve_init(int _count);
int solve_find_top(int *tower);
void solve(int n, Towers source, Towers destination, void (*updater)(void));

#endif //HANOITOWER_SOLVE_H