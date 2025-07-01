//Algoritmo Wall Follwer (right hand rule)

#include "wall_follower.h"
#include "functions.h"

void wall_follower_print(display *maze_begin, display *maze_display){
	int row, col;

    //Imprime o labirinto inicial, intermediário e com a melhor solução lado a lado
    printf("\nLabirinto Inicial | Caminho Percorrido:");
    if(maze_size_row < 32){
        for(row = 0; row < maze_size_row+1; row++){
            printf("\n");
            for(col = 0; col < maze_size_col+maze_size_col+1; col++){
                printf("%c", maze_begin->pos_maze[row][col]);
                
                if(col == maze_size_col+maze_size_col){
                    printf("    ");
                    for(col = 0; col < maze_size_col+maze_size_col+1; col++){
                        printf("%c", maze_display->pos_maze[row][col]);
                    }
                }       
            }
        }
        printf("\n");
    }

    else if(maze_size_row >= 32){
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
                printf("%c", maze_display->pos_maze[row][col]);      
            }
        }
        printf("\n");
    }
}

int wall_follower_solve(display *maze_display){
    pos *current_pos = (pos*) malloc(sizeof(pos));
    display *maze_begin = (display*) malloc(sizeof(display));
    int orientation; //1 para cima | 2 para direita | 3 para baixo | 4 para esquerda
	int row, col, maze_row, maze_col, right_row, right_col, front_col, front_row, steps = 0; //passos do algoritmo

	//Inicializações
	for(row = 0; row < maze_size_row+1; row++){ //salva maze original em maze_begin
        for(col = 0; col < maze_size_col+maze_size_col+1; col++){
        	maze_begin->pos_maze[row][col] = maze_display->pos_maze[row][col];
        }
    }
	current_pos = pos_begin(current_pos); //recebe nó de início e salva nó final em end_pos[8]
	maze_row = current_pos->row + 1; //alterações feitas devido à configuração das matrizes do tipo display
    maze_col = current_pos->col + current_pos->col + 1; 
	maze_display->pos_maze[maze_row][maze_col] = '*'; //marca posição como visitada
	orientation = 2; //direção inicial do robô

	while(!((current_pos->row == end_pos[0] && current_pos->col == end_pos[1]) ||
	        (current_pos->row == end_pos[2] && current_pos->col == end_pos[3]) ||
	        (current_pos->row == end_pos[4] && current_pos->col == end_pos[5]) ||
	        (current_pos->row == end_pos[6] && current_pos->col == end_pos[7]))){
		maze_row = current_pos->row + 1;
    	maze_col = current_pos->col + current_pos->col + 1; 

		if (orientation == 1){ //orientado para cima do labirinto
			right_row = maze_row;
			right_col = maze_col + 1;

			front_row = maze_row - 1;
			front_col = maze_col;

			if(maze_begin->pos_maze[right_row][right_col] != '|' && right_col < (maze_size_col + maze_size_col + 1)){
				orientation = 2; //"robô" gira 90 graus no sentido horário e
				current_pos->col = current_pos->col + 1; //segue até a nova posição
				maze_display->pos_maze[right_row][right_col+1] = '*'; //marca nova posição como visitada
				//printf("\n Direita");
			}

			else if(maze_begin->pos_maze[front_row][front_col] == ' ' && front_row > 0){
				current_pos->row = current_pos->row - 1; //segue até a nova posição
				maze_display->pos_maze[front_row][front_col] = '*';
				//printf("\n Frente");
			}
			
			else{ //se não puder ir para a direita nem para frente
				orientation = 4; //"robô" gira 90 graus no sentido anti horário
				//printf("\n 90 graus anti horario");
			}
		}

		else if (orientation == 2){ //orientado para direita do labirinto
			right_row = maze_row;
			right_col = maze_col;

			front_row = maze_row;
			front_col = maze_col + 1;

			if(maze_begin->pos_maze[right_row][right_col] == ' '){
				orientation = 3;
				current_pos->row = current_pos->row + 1;
				maze_display->pos_maze[right_row + 1][right_col] = '*';
				//printf("\n Direita");
			}

			else if(maze_begin->pos_maze[front_row][front_col] != '|' && front_col < (maze_size_col + maze_size_col + 1)){
				current_pos->col = current_pos->col + 1;
				maze_display->pos_maze[front_row][front_col + 1] = '*';
				//printf("\n Frente");
			}
			
			else{ //se não puder ir para a direita nem para frente
				orientation = 1; //"robô" gira 90 graus no sentido anti horário
				//printf("\n 90 graus anti horario");
			}
		}

		else if (orientation == 3){ //orientado para baixo do labirinto
			right_row = maze_row;
			right_col = maze_col - 1;

			front_row = maze_row;
			front_col = maze_col;

			if(maze_begin->pos_maze[right_row][right_col] != '|' && right_col > 0){
				orientation = 4;
				current_pos->col = current_pos->col - 1;
				maze_display->pos_maze[right_row][right_col-1] = '*';
				//printf("\n Direita");
			}

			else if(maze_begin->pos_maze[front_row][front_col] == ' '){
				current_pos->row = current_pos->row + 1;
				maze_display->pos_maze[front_row + 1][front_col] = '*';
				//printf("\n Frente");
			}
			
			else{ //se não puder ir para a direita nem para frente
				orientation = 2; //"robô" gira 90 graus no sentido anti horário
				//printf("\n 90 graus anti horario");
			}
		}

		else if (orientation == 4){ //orientado para esquerda do labirinto
			right_row = maze_row - 1;
			right_col = maze_col;

			front_row = maze_row;
			front_col = maze_col - 1;

			if(maze_begin->pos_maze[right_row][right_col] == ' ' && right_row > 0){
				orientation = 1;
				current_pos->row = current_pos->row - 1;
				maze_display->pos_maze[right_row][right_col] = '*';
				//printf("\n Direita");
			}

			else if(maze_begin->pos_maze[front_row][front_col] != '|' && front_col > 0){
				current_pos->col = current_pos->col - 1;
				maze_display->pos_maze[front_row][front_col-1] = '*';
				//printf("\n Frente");
			}
			
			else{ //se não puder ir para a direita nem para frente
				orientation = 3; //"robô" gira 90 graus no sentido anti horário
				//printf("\n 90 graus anti horario");
			}
		}

		steps++;		
	}
	
    /*printf("\n\n>>> ALGORITMO WALL FOLLOWER CONCLU%cDO <<<\nLabirinto: [%d]x[%d]\nPassos executados: %d", 
            214, maze_size_row, maze_size_col,steps);*/
	//wall_follower_print(maze_begin, maze_display);

	return steps;
}