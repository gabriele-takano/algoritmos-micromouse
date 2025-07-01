#ifndef backtracking
#define backtracking

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <time.h>
#include "functions.h"
#include "maze.h"

bool verify_neighbor_backtracking(node *current_node, int maze_to_visit[maze_size_row][maze_size_col], display *maze_display);
display *backtracking_print(display *maze_begin, int maze_to_visit[maze_size_row][maze_size_col], display *maze_display, stk *stk_visited, int steps);
int backtracking_solve(display *maze_display);

#endif