//Algoritmo Flood Fill

#include "floodfill.h"
#include "backtracking.h"
#include "functions.h"

display *flooded_maze_begin(display *maze_walls){
    int row, col;

    for(row = 0; row < maze_size_row+1; row++){
        for(col = 0; col < maze_size_col+maze_size_col+1; col++){
            
            if(row == 0 || ((row == maze_size_row) && (col != 0 && col != maze_size_col+maze_size_col)))
                maze_walls->pos_maze[row][col] = '_';

            else if((col == 0 || col == maze_size_col+maze_size_col) && row != 0)
                maze_walls->pos_maze[row][col] = '|';

            else 
            maze_walls->pos_maze[row][col] = ' ';
        }
    }
    maze_walls->pos_maze[1][0] = '>';
    return maze_walls;
}

void flood_maze(display *maze_walls, int maze_values[maze_size_row][maze_size_col]){
    pos *neighbor_pos = (pos*) malloc(sizeof(pos));
    node *current_node = (node*) malloc(sizeof(node));
    int row, col, cont = 0, current_value = 0, maze_to_visit[maze_size_row][maze_size_col];
    
    //printf("Flood Maze Start\n");

    //maze_to_visit: labirinto de controle de nós/vizinhos visitados
    // 0 - posição não visitada | 1 - posição visitada
    for(row = 0; row < maze_size_row; row++){
        for(col = 0; col < maze_size_col; col++){
            maze_to_visit[row][col] = 0;
            maze_values[row][col] = 9999;
        }
    }

    //atribui 0 para as células de chegada (end_pos) e marca como visitadas (já possuem valores definidos)
    maze_values[end_pos[0]][end_pos[1]] = 0;
    maze_to_visit[end_pos[0]][end_pos[1]] = 1;

    maze_values[end_pos[2]][end_pos[3]] = 0;
    maze_to_visit[end_pos[2]][end_pos[3]] = 1;

    maze_values[end_pos[4]][end_pos[5]] = 0;
    maze_to_visit[end_pos[4]][end_pos[5]] = 1;

    maze_values[end_pos[6]][end_pos[7]] = 0;
    maze_to_visit[end_pos[6]][end_pos[7]] = 1;

    cont = 4;

    while(cont < (maze_size_col*maze_size_row)){
        
        for(row = 0; row < maze_size_row; row++){
            for(col = 0; col < maze_size_col; col++){

                if(maze_values[row][col] == current_value){

                    current_node->visited_pos[0] = row;
                    current_node->visited_pos[1] = col;

                    while(verify_neighbor_backtracking(current_node, maze_to_visit, maze_walls)){ //verifica vizinhos disponiveis
                        neighbor_pos = choose_neighbor(current_node);
                        maze_values[neighbor_pos->row][neighbor_pos->col] = current_value + 1; //maze flooding 
                        maze_to_visit[neighbor_pos->row][neighbor_pos->col] = 1;
                        cont++;
                    } 
                }
            }
        }

        current_value++;
    }

    /*//Imprimir maze_walls
    for(row = 0; row < maze_size_row+1; row++){
        printf("\n");
        for(col = 0; col < maze_size_col+maze_size_col+1; col++){
            printf("%c", maze_walls->pos_maze[row][col]);
        }
    }
    printf("\n");

    //Imprimir maze_values = labirinto inundado
    printf("\nFLOOD_MAZE | Maze_values atualizado:\n");
    for(row = 0; row < maze_size_row; row++){
        printf("\n");
        for(col = 0; col < maze_size_col; col++){
            if(maze_values[row][col] < 10)
                printf("  %d", maze_values[row][col]);
            else
                printf(" %d", maze_values[row][col]);
        }
    }
    printf("\n");*/
    
    //printf("\nFlooded Concluido!\n");
}

void floodfill_print(display *maze_display, display *maze_walls, int maze_values[maze_size_row][maze_size_col], int visited_maze[maze_size_row][maze_size_col]){
    //imprime o maze inicial, o inundado final (com paredes e valores) e o caminho percorrido com '*'.
    int row, col;
    display *maze_solved = (display*) malloc(sizeof(display));

    for(row = 0; row < maze_size_row+1; row++){
            for(col = 0; col < maze_size_col+maze_size_col+1; col++){
                maze_solved->pos_maze[row][col] = maze_display->pos_maze[row][col];
            }
    }

    if(maze_size_row < 32){
        printf("\nParedes Descobertas | Labirinto Inundado:");
        for(row = 0; row < maze_size_row+1; row++){
            printf("\n");
            for(col = 0; col < maze_size_col+maze_size_col+1; col++){
                printf("%c", maze_walls->pos_maze[row][col]);
            }
            printf("    ");
            

            if(row - 1 >= 0){
                for(col = 0; col < maze_size_col; col++){
                    if(maze_values[row-1][col] < 10)
                        printf("   %d", maze_values[row-1][col]);
                    else if (maze_values[row-1][col] < 100)
                        printf("  %d", maze_values[row-1][col]);
                    else
                        printf(" %d", maze_values[row-1][col]);
                }
            }
        }
        printf("\n");

        printf("\nLabirinto Inicial | Caminho Percorrido:");
        for(row = 0; row < maze_size_row+1; row++){
            printf("\n");
            for(col = 0; col < maze_size_col+maze_size_col+1; col++){
                printf("%c", maze_display->pos_maze[row][col]);
                    if(col == maze_size_col+maze_size_col){
                        printf("    ");
                        for(col = 0; col < maze_size_col+maze_size_col+1; col++){
                            if(col < maze_size_col && visited_maze[row][col] == 1)
                                maze_solved->pos_maze[row+1][col+col+1] = '*';
                            printf("%c", maze_solved->pos_maze[row][col]);
                        }
                    }       
                }
            }
        printf("\n");
    }

    else{
        printf("\nParedes Descobertas:");
        for(row = 0; row < maze_size_row+1; row++){
            printf("\n");
            for(col = 0; col < maze_size_col+maze_size_col+1; col++){
                printf("%c", maze_walls->pos_maze[row][col]);
            }
        }
        printf("\n");        

        printf("\nLabirinto Inundado:");
        for(row = 0; row < maze_size_row; row++){ 
            printf("\n");
            for(col = 0; col < maze_size_col; col++){
                    if(maze_values[row][col] < 10)
                        printf("   %d", maze_values[row][col]);
                    else if (maze_values[row][col] < 100)
                        printf("  %d", maze_values[row][col]);
                    else
                        printf(" %d", maze_values[row][col]);
            } 
        }
        printf("\n");

        printf("\nLabirinto Inicial:");
        for(row = 0; row < maze_size_row+1; row++){
            printf("\n");
            for(col = 0; col < maze_size_col+maze_size_col+1; col++){
                printf("%c", maze_display->pos_maze[row][col]);
            }
        }
        printf("\n");

        printf("\nCaminho Percorrido:");        
        for(row = 0; row < maze_size_row+1; row++){
            printf("\n");
            for(col = 0; col < maze_size_col+maze_size_col+1; col++){
                if(col < maze_size_col && visited_maze[row][col] == 1)
                    maze_solved->pos_maze[row+1][col+col+1] = '*';
                printf("%c", maze_solved->pos_maze[row][col]);
            }
        }        
    }
 }

 display *floodfill_wall(display *maze_display, display *maze_walls, pos *current_pos){
    int maze_row, maze_col;

    //conversões para manipulação das variáveis (display *)
    maze_row = current_pos->row + 1;
    maze_col = current_pos->col + current_pos->col + 1;

    maze_walls->pos_maze[maze_row-1][maze_col] = maze_display->pos_maze[maze_row-1][maze_col]; //parede em cima
    maze_walls->pos_maze[maze_row][maze_col] = maze_display->pos_maze[maze_row][maze_col];     //parede embaixo
    maze_walls->pos_maze[maze_row][maze_col-1] = maze_display->pos_maze[maze_row][maze_col-1]; //parede esquerda
    maze_walls->pos_maze[maze_row][maze_col+1] = maze_display->pos_maze[maze_row][maze_col+1]; //parede direita

    /*printf("\nParedes Atualizadas:");
    for(maze_row = 0; maze_row < maze_size_row+1; maze_row++){
            printf("\n");
            for(maze_col = 0; maze_col < maze_size_col+maze_size_col+1; maze_col++){
                printf("%c", maze_walls->pos_maze[maze_row][maze_col]);
            }
        }
    printf("\n");*/

    return maze_walls;
}

void verify_neighbor_floodfill(pos *current_pos, display *maze_display){
    //printf("\n--VERIFY NEIGHBOR FLOODFILL--");
    bool exist_neighbor = false;
    int maze_row, maze_col;
    
    //Redefine referências de vizinhos
    neighbor_right = false;
    neighbor_left = false;
    neighbor_up = false;
    neighbor_down = false;

    //conversões para verificação no maze_display
    maze_row = current_pos->row + 1;
    maze_col = current_pos->col + current_pos->col + 1;  

    //Vizinho em cima
    if(current_pos->row - 1 >= 0 && maze_display->pos_maze[maze_row-1][maze_col] == ' '){ //sem parede
        neighbor_up = true; //ainda não foi visitado
        exist_neighbor = true;
        //printf("\nExiste vizinho em cima!");
    }

    //Vizinho embaixo
    if(current_pos->row + 1 < maze_size_row && maze_display->pos_maze[maze_row][maze_col] != '_'){ 
        neighbor_down = true; //ainda não foi visitado
        exist_neighbor = true;
        //printf("\nExiste vizinho embaixo!");
    }

    //Vizinho na esquerda
    if(current_pos->col - 1 >= 0 && maze_display->pos_maze[maze_row][maze_col-1] != '|'){
        neighbor_left = true; //ainda não foi visitado
        exist_neighbor = true;
        //printf("\nExiste vizinho na esquerda!");
    }

    //Vizinho na direita
    if(current_pos->col + 1 < maze_size_col && maze_display->pos_maze[maze_row][maze_col+1] != '|'){
        neighbor_right = true; //ainda não foi visitado
        exist_neighbor = true;
        //printf("\nExiste vizinho na direita!");
    }

    if(!exist_neighbor){
        //printf("Vizinhos n%co encontrados!\n", 198);
    }
}

pos *choose_neighbor_floodfill(int maze_values[maze_size_row][maze_size_col], pos *current_pos){
    //printf("\n--CHOOSE NEIGHBOR FLOODFILL-\n");
 
    pos *neighbor_pos = (pos*) malloc(sizeof(pos));
    int target_value; 

    target_value = maze_values[current_pos->row][current_pos->col] - 1; //valor atual - 1
    //printf("Target value: %d\n", target_value);

    if(neighbor_up == true && maze_values[current_pos->row - 1][current_pos->col] == target_value){ 
            neighbor_pos->row = current_pos->row - 1;
            neighbor_pos->col = current_pos->col;
            //printf("\nVizinho escolhido: de cima!");
            return neighbor_pos;
    }

    else if(neighbor_down == true && maze_values[current_pos->row + 1][current_pos->col] == target_value){
            neighbor_pos->row = current_pos->row + 1;
            neighbor_pos->col = current_pos->col;
            //printf("\nVizinho escolhido: de baixo!");
            return neighbor_pos;
    }

    else if(neighbor_left == true && maze_values[current_pos->row][current_pos->col - 1] == target_value){
            neighbor_pos->row = current_pos->row;
            neighbor_pos->col = current_pos->col - 1;
            //printf("\nVizinho escolhido: esquerda!");
            return neighbor_pos;
    }

    else if(neighbor_right == true && maze_values[current_pos->row][current_pos->col + 1] == target_value){
            neighbor_pos->row = current_pos->row;
            neighbor_pos->col = current_pos->col + 1;
            //printf("\nVizinho escolhido: direta!");
            return neighbor_pos;
    }

    else{
        printf("Nenhum vizinho escolhido!\n");
        return 0;
    }
}

int floodfill_solve(display *maze_display){
    display *maze_walls = (display*) malloc(sizeof(display));
    pos *current_pos = (pos*) malloc(sizeof(pos));
    //int visited_maze[maze_size_row][maze_size_col]; //marcar quais posições foram visitadas para imprimir ao fim
    int maze_values[maze_size_row][maze_size_col]; //flag que guarda a posição atual (quando for 0, chegou ao end point)
    int row, col, steps = 0;

    //visited_maze: labirinto de controle de vizinhos visitados
    // 0 - posição não visitada | 1 - posição visitada
    for(row = 0; row < maze_size_row; row++){
        for(col = 0; col < maze_size_col; col++){
            //visited_maze[row][col] = 0;
            maze_values[row][col] = 9999;
        }
    }

    maze_walls = flooded_maze_begin(maze_walls); //inicialização de maze_walls sem nenhuma parede ainda
    //floodfill_print(maze_display, maze_walls, maze_values, visited_maze);
    
    current_pos = pos_begin(current_pos); //inicializar posições de início e fim
    floodfill_wall(maze_display, maze_walls, current_pos); //insere paredes da posição inicial
    flood_maze(maze_walls, maze_values);
    //floodfill_print(maze_display, maze_walls, maze_values, visited_maze);

    while(maze_values[current_pos->row][current_pos->col] != 0){ //enquanto não chegar no end point
        steps++;
        
        verify_neighbor_floodfill(current_pos, maze_display);

        current_pos = choose_neighbor_floodfill(maze_values, current_pos); //escolhe vizinho com menor custo

        //visited_maze[current_pos->row][current_pos->col] = 1; //marca posição como visitada (para imprimir depois)
        maze_walls = floodfill_wall(maze_display, maze_walls, current_pos); //atualiza novas paredes descobertas        
        flood_maze(maze_walls, maze_values); //atualiza custos das células
    }

    //floodfill_print(maze_display, maze_walls, maze_values, visited_maze);

    free(maze_walls);
    free(current_pos);

    return steps;
}
