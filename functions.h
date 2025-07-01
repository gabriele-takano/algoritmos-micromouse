#ifndef functions
#define functions

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/*-------- Backtracking Functions --------*/
//Inicialização de variáveis
bool neighbor_right;
bool neighbor_left;
bool neighbor_up;
bool neighbor_down;
int maze_size_row, maze_size_col, stk_size;
int begin_pos[2], end_pos[8]; //coordenadas de início e fim

//Nó da pilha: armazena a posição visitada [linha, coluna] e o endereço do próximo nó
typedef struct node{
    int visited_pos[2]; //vetor para armazenar linha e coluna visitada
    struct node *next;
}node;

//Pilha: armazena/aponta para o item do topo da pilha
typedef struct stk{
    node *top;
}stk;

//Controle das posições acessadas
typedef struct pos{
    int row; //linha
    int col; //coluna
}pos;

//Labirinto para exibição 
typedef struct display{
    char pos_maze[300][300]; //Armazenar as informações de paredes e conteúdo das células |__|
}display;

typedef struct previous_pos{
    pos* matrix[300][300];
}previous_pos;

stk *stk_begin();
stk *push(pos *visited_pos, stk *stk_visited);
node *pop(stk *stk_visited);
pos *choose_neighbor(node *current_node);

/*-------- General Functions --------*/
pos *pos_begin(pos *visited_pos);

#endif