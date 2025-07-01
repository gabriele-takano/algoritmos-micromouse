//Algoritmo Backtracking

#include "backtracking.h"
#include "functions.h"
#include "maze.h"

//Verificação de vizinhos não visitados no nó atual
bool verify_neighbor_backtracking(node *current_node, int maze_to_visit[maze_size_row][maze_size_col], display *maze_display){
    //printf("\n--VERIFY NEIGHBOR--");

    int maze_row, maze_col;
    pos *visited_pos = (pos*) malloc(sizeof(pos));
    bool exist_neighbor = false;
    
    //Redefine referências de vizinhos
    neighbor_right = false;
    neighbor_left = false;
    neighbor_up = false;
    neighbor_down = false;

    visited_pos->row = current_node->visited_pos[0];
    visited_pos->col = current_node->visited_pos[1];
    maze_row = visited_pos->row+1;
    maze_col = visited_pos->col + visited_pos->col + 1;  

    //Vizinho em cima
    if(visited_pos->row - 1 >= 0 && maze_to_visit[visited_pos->row-1][visited_pos->col] == 0 
        && maze_display->pos_maze[maze_row-1][maze_col] != '_'){ //sem parede
        neighbor_up = true; //ainda não foi visitado
        exist_neighbor = true;
        //printf("\nExiste vizinho em cima!");
    }

    //Vizinho embaixo
    if(visited_pos->row + 1 < maze_size_row && maze_to_visit[visited_pos->row+1][visited_pos->col] == 0
        && maze_display->pos_maze[maze_row][maze_col] != '_'){ //' ' alterado para '_' por causa do flood fill
        neighbor_down = true; //ainda não foi visitado
        exist_neighbor = true;
        //printf("\nExiste vizinho embaixo!");
    }

    //Vizinho na esquerda
    if(visited_pos->col - 1 >= 0 && maze_to_visit[visited_pos->row][visited_pos->col-1] == 0
        && maze_display->pos_maze[maze_row][maze_col-1] != '|'){
        neighbor_left = true; //ainda não foi visitado
        exist_neighbor = true;
        //printf("\nExiste vizinho na esquerda!");
    }

    //Vizinho na direita
    if(visited_pos->col + 1 < maze_size_col && maze_to_visit[visited_pos->row][visited_pos->col+1] == 0
        && maze_display->pos_maze[maze_row][maze_col+1] != '|'){
        neighbor_right = true; //ainda não foi visitado
        exist_neighbor = true;
        //printf("\nExiste vizinho na direita!");
    }

    if(exist_neighbor == false){
        //printf("\nSem vizinhos n%co visitados!\n", 198);
        return exist_neighbor;
    }

    return exist_neighbor;
}

display *backtracking_print(display *maze_begin, int maze_to_visit[maze_size_row][maze_size_col], display *maze_display, stk *stk_visited, int steps){
    //printf("\n------BACKTRACKING PRINT---------");
    int row, col;
    node *current_node = NULL;
    pos *visited_pos = (pos*) malloc(sizeof(pos));
    display *maze_solved = (display*) malloc(sizeof(display));

    if(steps == 0){ //primeira vez na função
        for(row = 0; row < maze_size_row+1; row++){
            for(col = 0; col < maze_size_col+maze_size_col+1; col++){
                maze_begin->pos_maze[row][col] = maze_display->pos_maze[row][col];
            }
        }
        return maze_begin;
    }

    else{
        for(row = 0; row < maze_size_row+1; row++){
            for(col = 0; col < maze_size_col+maze_size_col+1; col++){
                maze_solved->pos_maze[row][col] = maze_display->pos_maze[row][col];
            }
        }
    }

    while(stk_visited->top != NULL){
        current_node = pop(stk_visited);
        visited_pos->row = current_node->visited_pos[0]; //linha
        visited_pos->col = current_node->visited_pos[1]; //coluna

        row = visited_pos->row + 1;
        col = visited_pos->col + visited_pos->col + 1;
        maze_display->pos_maze[row][col] = '*';
    }

    //Imprime o labirinto inicial, intermediário e com a melhor solução lado a lado
    printf("\nLabirinto Inicial | Caminho Percorrido | Melhor Caminho:");
    if(maze_size_row < 32){
        for(row = 0; row < maze_size_row+1; row++){
            printf("\n");
            for(col = 0; col < maze_size_col+maze_size_col+1; col++){
                printf("%c", maze_begin->pos_maze[row][col]);
                
                if(col == maze_size_col+maze_size_col){
                    printf("    ");
                    for(col = 0; col < maze_size_col+maze_size_col+1; col++){
                        if(maze_to_visit[row][col] == 1){
                            maze_solved->pos_maze[row+1][col+col+1] = '*';
                        }
                        printf("%c", maze_solved->pos_maze[row][col]);
                        
                        if(col == maze_size_col+maze_size_col){
                            printf("    ");
                            for(col = 0; col < maze_size_col+maze_size_col+1; col++){
                                printf("%c", maze_display->pos_maze[row][col]);
                            } 
                        }
                    }
                }       
            }
        }
        printf("\n");
    }

    if(maze_size_row >= 32){
        for(row = 0; row < maze_size_row+1; row++){
            printf("\n");
            for(col = 0; col < maze_size_col+maze_size_col+1; col++){
                printf("%c", maze_begin->pos_maze[row][col]);      
            }
        }
        printf("\n");          
        
        for(row = 0; row < maze_size_row+1; row++){
            printf("\n");
            for(col = 0; col < maze_size_col+maze_size_col+1; col++){
                if(maze_to_visit[row][col] == 1){
                    maze_solved->pos_maze[row+1][col+col+1] = '*';
                }
                printf("%c", maze_solved->pos_maze[row][col]);      
            }
        }
        printf("\n");

        for(row = 0; row < maze_size_row+1; row++){
            printf("\n");
            for(col = 0; col < maze_size_col+maze_size_col+1; col++){
                printf("%c", maze_display->pos_maze[row][col]);      
            }
        }
        printf("\n");  
    }

    return 0;
}

int backtracking_solve(display *maze_display){ //recebe o labirinto gerado pelo Algoritmo DFS
    //printf("\n\n--BACKTRACKING--");
    pos *visited_pos = (pos*) malloc(sizeof(pos));
    pos *neighbor_pos = (pos*) malloc(sizeof(pos));
    stk *stk_visited = (stk*) malloc(sizeof(stk));
    node *current_node = NULL;
    display *maze_begin = (display*) malloc(sizeof(display));
    int maze_to_visit[maze_size_row][maze_size_col];
    int steps = 0; //passos do algoritmo
    int row, col;
    
    //Inicializações
    stk_size = 0;
    maze_begin = backtracking_print(maze_begin, maze_to_visit, maze_display, stk_visited, steps); //salva labirinto inicial
    stk_visited = stk_begin();
    visited_pos = pos_begin(visited_pos);

    //maze_to_visit: labirinto de controle de nós/vizinhos visitados
    // 0 - posição não visitada | 1 - posição visitada
    for(row = 0; row < maze_size_row; row++){
        for(col = 0; col < maze_size_col; col++){
            maze_to_visit[row][col] = 0;
        }
    }

    //Primeiro nó: atribui a posição de início
    visited_pos->row = begin_pos[0];
    visited_pos->col = begin_pos[1];
    maze_to_visit[visited_pos->row][visited_pos->col] = 1;
    stk_visited = push(visited_pos, stk_visited);

    neighbor_pos->row = begin_pos[0];
    neighbor_pos->col = begin_pos[1];

    //Algoritmo Backtracking
    while(!((neighbor_pos->row == end_pos[0] && neighbor_pos->col == end_pos[1]) ||
            (neighbor_pos->row == end_pos[2] && neighbor_pos->col == end_pos[3]) ||
            (neighbor_pos->row == end_pos[4] && neighbor_pos->col == end_pos[5]) ||
            (neighbor_pos->row == end_pos[6] && neighbor_pos->col == end_pos[7]))){ //enquanto não chegar no end point
        steps++;
        //printf("\n\n--BACKTRACKING | PASSOS EXECUTADOS: %d--", steps);
        
        current_node = pop(stk_visited);
        //printf("\nN%c atual: [%d]x[%d]", 162, current_node->visited_pos[0], current_node->visited_pos[1]);
        
        visited_pos->row = current_node->visited_pos[0];
        visited_pos->col = current_node->visited_pos[1];

        if(verify_neighbor_backtracking(current_node, maze_to_visit, maze_display)){ //se houver vizinhos não visitados retorna true
            stk_visited = push(visited_pos, stk_visited);
            neighbor_pos = choose_neighbor(current_node);
            //printf("\nVizinho escolhido: [%d]x[%d]", neighbor_pos->row, neighbor_pos->col);

            maze_to_visit[neighbor_pos->row][neighbor_pos->col] = 1;
            stk_visited = push(neighbor_pos, stk_visited);
        }
    }

    /*printf("\n\n>>> ALGORITMO BACKTRACKING CONCLU%cDO <<<\nLabirinto: [%d]x[%d]\nTamanho do caminho: %d\nPassos executados: %d", 
            214, maze_size_row, maze_size_col, stk_size-1 ,steps);*/
    //backtracking_print(maze_begin, maze_to_visit, maze_display, stk_visited, steps);
    
    //printf("\nLabirinto: [%d]x[%d]\nTamanho do menor caminho: %d", maze_size_row, maze_size_col, stk_size-1);

    return steps;
}