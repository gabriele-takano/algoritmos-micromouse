#ifndef floodfill
#define floodfill

#include "functions.h"
#include "backtracking.h"

display *flooded_maze_begin(display *maze_walls); //inicializar maze_walls sem paredes
void flood_maze(display *maze_walls, int maze_values[maze_size_row][maze_size_col]); //inunda labirinto (atualiza valores de maze_values)
void floodfill_print(display *maze_display, display *maze_walls, int maze_values[maze_size_row][maze_size_col], int visited_maze[maze_size_row][maze_size_col]); //mostra no cmd o labirinto inizial, inundado e resolvido
display *floodfill_wall(display *maze_display, display *maze_walls, pos *current_pos); //atualiza paredes no maze_walls
void verify_neighbor_floodfill(pos *current_pos, display *maze_display); // verifica existência de vizinhos
pos *choose_neighbor_floodfill(int maze_values[maze_size_row][maze_size_col], pos *current_pos); //escolhe vizinho com menor custo
int floodfill_solve(display *maze_display); //recebe maze para resolver e retorna número de passos executados

#endif