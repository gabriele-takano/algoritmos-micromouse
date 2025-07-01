#ifndef dijkstra
#define dijkstra

#include "functions.h"

#define INF 9999

void verify_update_neighbor_dijkstra(display *maze_display, pos *current_vertex, bool visited[maze_size_row][maze_size_col], int dist[maze_size_row][maze_size_col], int previous[maze_size_row][maze_size_col]);
pos *choose_new_vertex(int dist[maze_size_row][maze_size_col], bool visited[maze_size_row][maze_size_col]);
display *shortest_path_dijkstra(display *shortest_path, pos* current_vertex, int previous[maze_size_row][maze_size_col], display *maze_display);
void print_dijkstra(display *maze_display, display *shortest_path, display *path);
int dijkstra_solve(display *maze_display);

#endif