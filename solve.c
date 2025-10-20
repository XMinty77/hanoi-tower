#include "solve.h"
#include "tools.h"
#include <stdlib.h>

int solve_count;
int **solve_towers;

int **solve_init(int _count) {
    solve_count = _count;

    solve_towers = malloc(solve_count * sizeof(int*));
    for (int j = 0; j < 3; j++) {
        solve_towers[j] = malloc(solve_count * sizeof(int));
    }

    for (int i = 0; i < solve_count; i++) {
        solve_towers[1][i] = solve_towers[2][i] = -1;
        solve_towers[0][i] = i;
    }

    return solve_towers;
}

void solve_dispose() {
    for (int i = 0; i < 3; i++) {
        free(solve_towers[i]);
    }
    free(solve_towers);
}

int solve_find_top(int *tower) {
    for (int i = solve_count - 1; i >= 0; i--) {
        if (tower[i] != -1) return i;
    }
    return -1;
}

void solve_move(int *from, int *to) {
    int fromIndex = solve_find_top(from);
    int toIndex = solve_find_top(to) + 1;

    if (fromIndex == -1) throw();

    to[toIndex] = from[fromIndex];
    from[fromIndex] = -1;
}

void solve(int n, Towers source, Towers destination, void (*updater)(void)) {
    if (n == 0) return;

    int *fromTower = solve_towers[source];
    int *toTower = solve_towers[destination];

    Towers buffer;
    if (source == A) buffer = (destination == B) ? C : B;
    else if (source == B) buffer = (destination == A) ? C : A;
    else /* from == C */ buffer = (destination == A) ? B : A;

    solve(n - 1, source, buffer, updater);
    solve_move(fromTower, toTower);
    updater();
    solve(n - 1, buffer, destination, updater);
}