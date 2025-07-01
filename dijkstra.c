//Algoritmo Dijkstra

#include "dijkstra.h"

void verify_update_neighbor_dijkstra(display *maze_display, pos *current_vertex, bool visited[maze_size_row][maze_size_col], int dist[maze_size_row][maze_size_col], int previous[maze_size_row][maze_size_col]){
	int new_value, maze_row, maze_col;
	
	//Conversão do current_vertex para a posição no maze_display
	maze_row = current_vertex->row + 1;
    maze_col = current_vertex->col + current_vertex->col + 1;  

	new_value = dist[current_vertex->row][current_vertex->col] + 1;
	//printf("New_value = %d\n", new_value);

	//Vizinho em cima
    if( current_vertex->row - 1 >= 0 && visited[current_vertex->row - 1][current_vertex->col] == false 
        && maze_display->pos_maze[maze_row - 1][maze_col] != '_' && new_value < dist[current_vertex->row - 1][current_vertex->col]){
        
        dist[current_vertex->row - 1][current_vertex->col] = new_value;
        //vertex_value = x * maze_size_row + y
        previous[current_vertex->row - 1][current_vertex->col] = current_vertex->row * maze_size_row + current_vertex->col;
        //printf("Vizinho em cima atualizado!\n");
    }

    //Vizinho embaixo
    if( current_vertex->row + 1 < maze_size_row && visited[current_vertex->row + 1][current_vertex->col] == 0
        && maze_display->pos_maze[maze_row][maze_col] != '_' && new_value < dist[current_vertex->row + 1][current_vertex->col]){

        dist[current_vertex->row + 1][current_vertex->col] = new_value;
        previous[current_vertex->row + 1][current_vertex->col] = current_vertex->row * maze_size_row + current_vertex->col;
        //printf("Vizinho embaixo atualizado!\n");
    }

    //Vizinho na esquerda
    if( current_vertex->col - 1 >= 0 && visited[current_vertex->row][current_vertex->col - 1] == 0
        && maze_display->pos_maze[maze_row][maze_col - 1] != '|' && new_value < dist[current_vertex->row][current_vertex->col - 1]){

        dist[current_vertex->row][current_vertex->col - 1] = new_value;
        previous[current_vertex->row][current_vertex->col - 1] = current_vertex->row * maze_size_row + current_vertex->col;
        //printf("Vizinho na esquerda atualizado!\n");
    }

    //Vizinho na direita
    if( current_vertex->col + 1 < maze_size_col && visited[current_vertex->row][current_vertex->col + 1] == 0
        && maze_display->pos_maze[maze_row][maze_col + 1] != '|' && new_value < dist[current_vertex->row][current_vertex->col + 1]){
        
        dist[current_vertex->row][current_vertex->col + 1] = new_value;
        previous[current_vertex->row][current_vertex->col + 1] = current_vertex->row * maze_size_row + current_vertex->col;
        //printf("Vizinho na direita atualizado!\n");
    }
}

pos *choose_new_vertex(int dist[maze_size_row][maze_size_col], bool visited[maze_size_row][maze_size_col]){
	pos *new_vertex = (pos*) malloc(sizeof(pos));
	int row, col;
	int min_dist = INF;

	//Escolha do vértice com menor valor de dist e que não foi visitado ainda
	for (row = 0; row < maze_size_row; row++) {
		for (col = 0; col < maze_size_col; col++) {
			if (dist[row][col] < min_dist && visited[row][col] == false) {
				min_dist = dist[row][col];
				new_vertex->row = row;
				new_vertex->col = col;
			}
		}
	}
	
	return new_vertex;
}

display *shortest_path_dijkstra(display *shortest_path, pos* current_vertex, int previous[maze_size_row][maze_size_col], display *maze_display){
	int row, col, prev_value[4], maze_row, maze_col, steps_sp = 0;  

	/*for(row = 0; row < maze_size_row; row++){
            printf("\n");
            for(col = 0; col < maze_size_col; col++){
                printf(" %d ", previous[row][col]);
            }
    }*/

	//Conversão para variavel do tipo display*
	maze_row = maze_size_row + 1;
	maze_col = maze_size_col + maze_size_col + 1;

    for(row = 0; row < maze_row; row++){
            for(col = 0; col < maze_col; col++){
                shortest_path->pos_maze[row][col] = maze_display->pos_maze[row][col];
            }
    }
    
    shortest_path->pos_maze[(current_vertex->row + 1)][(current_vertex->col + current_vertex->col + 1)] = '*';

    while(!(current_vertex->row == begin_pos[0] && current_vertex->col == begin_pos[1])){
    	steps_sp++;
    	//printf("steps_sp: %d\n", steps_sp);

    	if(steps_sp > maze_size_row * maze_size_col){
    		printf("Shortest path nao encontrado!\n");
    		break;
    	}
    	
	    prev_value[0] = (current_vertex->row - 1) * maze_size_row + current_vertex->col;
	    prev_value[1] = (current_vertex->row + 1) * maze_size_row + current_vertex->col;
	    prev_value[2] = current_vertex->row * maze_size_row + (current_vertex->col - 1);
	    prev_value[3] = current_vertex->row * maze_size_row + (current_vertex->col + 1);

	    if(previous[current_vertex->row][current_vertex->col] == prev_value[0]){
	    	current_vertex->row = current_vertex->row - 1;
	    	shortest_path->pos_maze[(current_vertex->row + 1)][(current_vertex->col + current_vertex->col + 1)] = '*';
	    	//printf("prev: %dx%d\n", current_vertex->row, current_vertex->col);
	    }

	    else if(previous[current_vertex->row][current_vertex->col] == prev_value[1]){
	    	current_vertex->row = current_vertex->row + 1;
	    	shortest_path->pos_maze[(current_vertex->row + 1)][(current_vertex->col + current_vertex->col + 1)] = '*';
	    	//printf("prev: %dx%d\n", current_vertex->row, current_vertex->col);
	    }
	    
	    
	    else if(previous[current_vertex->row][current_vertex->col] == prev_value[2]){
	    	current_vertex->col = current_vertex->col - 1;
	    	shortest_path->pos_maze[(current_vertex->row + 1)][(current_vertex->col + current_vertex->col + 1)] = '*';
	    	//printf("prev: %dx%d\n", current_vertex->row, current_vertex->col);
	    }
	    
	    
	    else if(previous[current_vertex->row][current_vertex->col] == prev_value[3]){
	    	current_vertex->col = current_vertex->col + 1;
	    	shortest_path->pos_maze[(current_vertex->row + 1)][(current_vertex->col + current_vertex->col + 1)] = '*';
	    	//printf("prev: %dx%d\n", current_vertex->row, current_vertex->col);
	    }

	    //printf("current_vertex: %dx%d\n", current_vertex->row, current_vertex->col);

    }

    /*for(row = 0; row < maze_row; row++){
        printf("\n");
        for(col = 0; col < maze_col; col++){
            printf("%c", shortest_path->pos_maze[row][col]);
		}
	}*/

	return shortest_path;
}

void print_dijkstra(display *maze_display, display *shortest_path, display *path){
	int row, col;

	if(maze_size_row < 32){
		printf("\nLabirinto Inicial | Caminho Percorrido | Melhor Caminho:");
	    for(row = 0; row < maze_size_row + 1; row++){
	        printf("\n");
	        for(col = 0; col < maze_size_col + maze_size_col + 1; col++){
	            printf("%c", maze_display->pos_maze[row][col]);
	                
	            if(col == maze_size_col + maze_size_col){
	                printf("    ");
	                for(col = 0; col < maze_size_col + maze_size_col + 1; col++){
	                    printf("%c", path->pos_maze[row][col]);
	                    
	            	    if(col == maze_size_col + maze_size_col){
	                	   	printf("    ");
	                    	for(col = 0; col < maze_size_col + maze_size_col + 1; col++){
	                        	printf("%c", shortest_path->pos_maze[row][col]);
	                    	}
	                    }
	                }       
	            }
	        }
	    }
	    printf("\n");
	}

	else{
		printf("\nLabirinto Inicial:");
		for(row = 0; row < maze_size_row + 1; row++){
	        printf("\n");
	        for(col = 0; col < maze_size_col + maze_size_col + 1; col++){
	            printf("%c", maze_display->pos_maze[row][col]);
	        }
	    }
	    printf("\n");

	    printf("\nCaminho Percorrido:");
		for(row = 0; row < maze_size_row + 1; row++){
			printf("\n");
			for(col = 0; col < maze_size_col + maze_size_col + 1; col++){
				printf("%c", path->pos_maze[row][col]);
			}
		}
		printf("\n");

		printf("\nMelhor Caminho:");
		for(row = 0; row < maze_size_row + 1; row++){
			printf("\n");
			for(col = 0; col < maze_size_col + maze_size_col + 1; col++){
	            printf("%c", shortest_path->pos_maze[row][col]);
	       	}
		}
		printf("\n");
	}
}

int dijkstra_solve(display *maze_display){
	pos *current_vertex = (pos*) malloc(sizeof(pos));
	display *shortest_path = (display*) malloc(sizeof(display));
	display *path = (display*) malloc(sizeof(display)); //salvar labirinto inicial sem modificações
	
	bool visited[maze_size_row][maze_size_col]; // false: não visitado | true: visitado
	int dist[maze_size_row][maze_size_col], previous[maze_size_row][maze_size_col]; //marca a distancia do vértice e o vértice anterior
	int row, col, steps = 0;

	//Inicializações
	
	for(row = 0; row < maze_size_row; row++){
		for(col = 0; col< maze_size_col; col++){
			dist[row][col] = INF;
			visited[row][col] = false;
			//previous[row][col] = 0;
		}
	}

	for(row = 0; row < maze_size_row+1; row++){
        for(col = 0; col < maze_size_col+maze_size_col+1; col++){
            path->pos_maze[row][col] = maze_display->pos_maze[row][col];
        }
    }

	current_vertex = pos_begin(current_vertex); //recebe posição de início e salva posição final em end_pos[8]
	dist[current_vertex->row][current_vertex->col] = 0;

	//printf("------------- Dijkstra Begin -------------");

	while(!((current_vertex->row == end_pos[0] && current_vertex->col == end_pos[1]) ||
            (current_vertex->row == end_pos[2] && current_vertex->col == end_pos[3]) ||
            (current_vertex->row == end_pos[4] && current_vertex->col == end_pos[5]) ||
            (current_vertex->row == end_pos[6] && current_vertex->col == end_pos[7]))){
		steps++;
		
		//printf("\nSTEP %d\n", steps);

		current_vertex = choose_new_vertex(dist, visited);
		//printf("Novo vertice escolhido: %dx%d\n", current_vertex->row, current_vertex->col);
		
		if (current_vertex == NULL){
			printf("Novo vertice nao encontrado!\n");
			break;
		}

		verify_update_neighbor_dijkstra(maze_display, current_vertex, visited, dist, previous);
		visited[current_vertex->row][current_vertex->col] = true; //caminho total
		path->pos_maze[current_vertex->row+1][current_vertex->col+current_vertex->col+1] = '*';

		if(steps == maze_size_row*maze_size_col){
			printf("end_point nao encontrado!\n");
			break;
		}
	}
	
	shortest_path = shortest_path_dijkstra(shortest_path, current_vertex, previous, maze_display);
	//print_dijkstra(maze_display, shortest_path, path);
	//printf("Passos executados: %d\n", steps);

	return steps;
}
