#ifndef maze
#define maze

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "functions.h"

bool verify_neighbor(node *current_node, int maze_to_visit[maze_size_row][maze_size_col], display *maze_display);
bool maze_visited(int maze_to_visit[maze_size_row][maze_size_col]);
void maze_display_print(display *maze_display);
display *maze_display_begin();
display *remove_wall(pos *visited_pos, node *current_node, pos *neighbor_pos, display *maze_display);
display *generate_maze(stk *stk_visited);
display *maze_defined(display *current_maze, int count);

#endif