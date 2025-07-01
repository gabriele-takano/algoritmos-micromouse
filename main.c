/*
Gabriele Vilas Boas Takano - 30 jun. 2025
Trabalho de Conclusão de Curso
Orientador: Prof. Dr. Marcio Rodrigues da Cunha
UTFPR - CM | Engenharia Eletrônica
*/

#include "functions.h"
#include "maze.h"
#include "backtracking.h"
#include "wall_follower.h"
#include "floodfill.h"
#include "dijkstra.h"
#include <sys/time.h>

void print_data(int max_count, int steps_count[4][max_count], double time_count[4][max_count], int maze_size_row, int maze_size_col){
    int i, flag = 0, div_media = 0;
    double media = 0;

    //printf("\n-------- LABIRINTO [%d]x[%d] --------", maze_size_row, maze_size_col);

    printf("\n>>>> BACTRACKING <<<<");
    for(i = 0; i < max_count; i++){
        media = media + steps_count[0][i];
    }
    media = media/max_count;
    printf("\nMedia de Passos Executados: %.f", media);

    media = 0;
    div_media = 0;
    flag = 0;
    for(i = 0; i < max_count; i++){
        if(time_count[0][i] >= 0){
            media = media + time_count[0][i] + (steps_count[0][i]*0.5);
            div_media++;
        }
        else
            flag++;
    }
    media = media/div_media;
    printf("\nMedia de Tempo de execu%c%co (ms): %f\n", 135, 198, media);
    printf("Tempos menores que zero: %d\n", flag);

    printf("\n>>>> WALL FOLLOWER <<<<");
    media = 0;
    for(i = 0; i < max_count; i++){
        media = media + steps_count[1][i];   
    }
    media = media/max_count;
    printf("\nMedia de Passos Executados: %.f", media);

    media = 0;
    div_media = 0;
    flag = 0;
    for(i = 0; i < max_count; i++){
        if(time_count[1][i] >= 0){
            media = media + time_count[1][i] + (steps_count[1][i]*0.5);
            div_media++;
        }
        else
            flag++;
    }
    media = media/div_media;
    printf("\nMedia de Tempo de execu%c%co (ms): %f\n", 135, 198, media);
    printf("Tempos menores que zero: %d\n", flag);

    printf("\n>>>> FLOOD FILL <<<<");
    media = 0;
    for(i = 0; i < max_count; i++){
        media = media + steps_count[2][i];   
    }
    media = media/max_count;
    printf("\nMedia de Passos Executados: %.f", media);

    media = 0;
    div_media = 0;
    flag = 0;
    for(i = 0; i < max_count; i++){
        if(time_count[2][i] >= 0){
            media = media + time_count[2][i] + (steps_count[2][i]*0.5);
            div_media++;
        }
        else
            flag++;
    }
    media = media/div_media;
    printf("\nMedia de Tempo de execu%c%co (ms): %f\n", 135, 198, media);
    printf("Tempos menores que zero: %d\n", flag);

    printf("\n>>>> DIJKSTRA <<<<");
    media = 0;
    for(i = 0; i < max_count; i++){
        media = media + steps_count[3][i];   
    }
    media = media/max_count;
    printf("\nMedia de Passos Executados: %.f", media);

    media = 0;
    div_media = 0;
    flag = 0;
    for(i = 0; i < max_count; i++){
        if(time_count[3][i] >= 0){
            media = media + time_count[3][i] + (steps_count[3][i]*0.5);
            div_media++;
        }
        else
            flag++;
    }
    media = media/div_media;
    printf("\nMedia de Tempo de execu%c%co (ms): %f\n", 135, 198, media);
    printf("Tempos menores que zero: %d\n", flag);
}

int main(){
    int size, count = 0;
    display *maze_display = (display*) malloc(sizeof(display));
    int max_count = 100; //número de vezes que os algoritmos serão executados em um único labirinto (default 100)

    /*printf("max_count: ");
    scanf("%d", &max_count);*/
    
    //Variáveis auxiliares para aquisição de dados para os gráficos
    struct timeval start, end;
    double time_taken;
    int steps_count[4][max_count];
    double time_count[4][max_count];

    //Inicializações
    maze_size_row = 4; // 4 - primeiro labirinto 4x4
    maze_size_col = maze_size_row;
    size = 0; // 0 - primeiro tamanho de labirinto (4x4)
    srand((unsigned)time(NULL));

    //maze_choose(); //para escolha manual de maze_size

    while(maze_size_row < 128){ //default 128
        
        printf("\n\n-------- LABIRINTO [%d]x[%d] -------- \n", maze_size_row, maze_size_col);

        for(count = 0; count < max_count; count++){
            //Algoritmos de busca

            //---Backtracking---
            maze_display = maze_defined(maze_display, size);
            
            gettimeofday(&start, NULL);
            steps_count[0][count] = backtracking_solve(maze_display);
            gettimeofday(&end, NULL);
            //printf("\nPassos Executados Backtracking: %d\n", steps_count[0][count]);
            
            time_taken = (end.tv_sec - start.tv_sec) * 1e3;
            time_taken = time_taken + (end.tv_usec - start.tv_usec) * 1e-3;
            time_count[0][count] = time_taken;
            //printf("\nTempo de execu%c%co Backtracking: %.10f ms\n", 135, 198, time_taken);
            
            //---Wall Follower---
            maze_display = maze_defined(maze_display, size);

            gettimeofday(&start, NULL);
            steps_count[1][count] = wall_follower_solve(maze_display);
            gettimeofday(&end, NULL);
            //printf("\nPassos Executados Wall Follower: %d\n", steps_count[1][count]);

            time_taken = (end.tv_sec - start.tv_sec) * 1e3;
            time_taken = time_taken + (end.tv_usec - start.tv_usec) * 1e-3;
            time_count[1][count] = time_taken;
            //printf("\nTempo de execu%c%co Wall Follower: %.10f ms", 135, 198, time_taken);*/

            //---Flood Fill---
                maze_display = maze_defined(maze_display, size);
            
                gettimeofday(&start, NULL);
                steps_count[2][count] = floodfill_solve(maze_display);
                gettimeofday(&end, NULL);
                //printf("\nPassos Executados FloodFill: %d\n", steps_count[2][count]);

                time_taken = (end.tv_sec - start.tv_sec) * 1e3;
                time_taken = time_taken + (end.tv_usec - start.tv_usec) * 1e-3;
                time_count[2][count] = time_taken;
                //printf("\nTempo de execu%c%co Flood Fill: %.10f ms\n", 135, 198, time_taken);
            
            //---Dijkstra---
            maze_display = maze_defined(maze_display, size);
            
            gettimeofday(&start, NULL);
            steps_count[3][count] = dijkstra_solve(maze_display);
            gettimeofday(&end, NULL);
            //printf("\nPassos Executados Dijkstra: %d\n", steps_count[3][count]);

            time_taken = (end.tv_sec - start.tv_sec) * 1e3;
            time_taken = time_taken + (end.tv_usec - start.tv_usec) * 1e-3;
            time_count[3][count] = time_taken;

            //printf("Tempo de execu%c%co Dijkstra: %.10f ms\n", 135, 198, time_taken);
        
        }
        
        print_data(max_count, steps_count, time_count, maze_size_row, maze_size_col);

        //Incrementa o tamanho do labirinto
        maze_size_row = maze_size_row*2;
        maze_size_col = maze_size_row;
        size++;
    }

    return 0;
}

/* Compilação no cmd
gcc.exe -Wall -g -c main.c -o main.o
gcc.exe -Wall -g -c maze.c -o maze.o
gcc.exe -Wall -g -c functions.c -o functions.o
gcc.exe -Wall -g -c backtracking.c -o backtracking.o
gcc.exe -Wall -g -c wall_follower.c -o wall_follower.o
gcc.exe -Wall -g -c floodfill.c -o floodfill.o
gcc.exe -Wall -g -c dijkstra.c -o dijkstra.o
gcc.exe -o micromouse.exe main.o maze.o functions.o backtracking.o wall_follower.o floodfill.o dijkstra.o

micromouse.exe
*/