#include "functions.h"

//Inicialização de variáveis globais
bool neighbor_right = false;
bool neighbor_left = false;
bool neighbor_up = false;
bool neighbor_down = false;
int maze_size_row = 0, maze_size_col = 0, stk_size = 0;

//Inicialização da pilha
stk *stk_begin(){
    //printf("\n\n--STACK BEGIN--");
    
    //Criação
    stk *stk_visited = (stk*) malloc(sizeof(stk));
    if(stk_visited == NULL){
        printf("Erro de alocação da pilha!\n");
        exit(1);
    }
    
    //Inicialização
    stk_visited->top = NULL;
    return stk_visited;
}

//Insere item na pilha
stk *push(pos *visited_pos, stk *stk_visited){
    //printf("\n--PUSH--");

    //alocando espaço de memória para novo elemento (nó)
    node *new_node = (node*) malloc(sizeof(node));
    if(new_node == NULL){
        printf("Erro de alocação do nó (push)!\n");
        exit(1);
    }
    else{
        new_node->visited_pos[0] = visited_pos->row;
        new_node->visited_pos[1] = visited_pos->col;
        new_node->next = stk_visited->top;
        stk_visited->top = new_node;
        //printf("\nPush: [%d]x[%d]",new_node->visited_pos[0], new_node->visited_pos[1]);
        stk_size++;
        return stk_visited;
    }
}

//Retira o primeiro item da pilha (topo)
node *pop(stk *stk_visited){
    //printf("\n--POP--");

    pos *visited_pos = (pos*) malloc(sizeof(pos));
    node *pop_node = stk_visited->top;

    if(pop_node == NULL){
        printf("\nPilha vazia!");
        return NULL;
    }
    else{
        stk_visited->top = pop_node->next;
        pop_node->next = NULL;
        visited_pos->row = pop_node->visited_pos[0];
        visited_pos->col = pop_node->visited_pos[1];
        //printf("\nPop: [%d]x[%d]", visited_pos->row, visited_pos->col);
        stk_size--;
        return pop_node;
    }

}

//Escolha de um vizinho não visitado do nó atual (aleatóriamente)
pos *choose_neighbor(node *current_node){
    //Só entra nesta função se houverem vizinhos não visitados
    //printf("\n--CHOOSE NEIGHBOR--");

    int neighbor;
    pos *neighbor_pos = (pos*) malloc(sizeof(pos));

    while(1){
        //Sorteio de vizinho: 0 - em cima | 1 - em baixo | 2 - esquerda | 3 - direita
        neighbor = rand() % 4;

        if(neighbor == 0 && neighbor_up == true){
            neighbor_pos->row = current_node->visited_pos[0] - 1;
            neighbor_pos->col = current_node->visited_pos[1];
            //printf("\nVizinho escolhido: de cima!");
            neighbor_up = false;
            return neighbor_pos;
        }

        else if(neighbor  == 1 && neighbor_down == true){
            neighbor_pos->row = current_node->visited_pos[0] + 1;
            neighbor_pos->col = current_node->visited_pos[1];
            //printf("\nVizinho escolhido: de baixo!");
            neighbor_down = false;
            return neighbor_pos;
        }

        else if(neighbor  == 2 && neighbor_left == true){
            neighbor_pos->row = current_node->visited_pos[0];
            neighbor_pos->col = current_node->visited_pos[1] - 1;
            //printf("\nVizinho escolhido: da esquerda!");
            neighbor_left = false;
            return neighbor_pos;
        }

        else if(neighbor  == 3 && neighbor_right == true){
            neighbor_pos->row = current_node->visited_pos[0];
            neighbor_pos->col = current_node->visited_pos[1] + 1;
            //printf("\nVizinho escolhido: da direita!");
            neighbor_right = false;
            return neighbor_pos;
        }
    }
}

//Inicialização: define nó de início e fim/chegada
pos *pos_begin(pos *visited_pos){
    //printf("\n\n--POS BEGIN--");
    
    //Início[linha, coluna]: [0, 0]
    begin_pos[0] = 0;
    begin_pos[1] = 0;
    
    //Fim[linha, coluna]: [r, c] -- deve ser um quadrado 2x2 no centro do labirinto
    end_pos[0] = maze_size_row/2-1;
    end_pos[1] = maze_size_col/2-1;

    end_pos[2] = end_pos[0];
    end_pos[3] = end_pos[1] + 1;

    end_pos[4] = end_pos[0] + 1;
    end_pos[5] = end_pos[1];

    end_pos[6] = end_pos[0] + 1;
    end_pos[7] = end_pos[1] + 1;

    //printf("\nIn%ccio: [%d]x[%d]\nFim: [%d]x[%d]\n", 161, begin_pos[0], begin_pos[1], end_pos[2], end_pos[3]);
    
    //Primeiro nó que será visitado
    visited_pos->row = begin_pos[0];
    visited_pos->col = begin_pos[1];

    return visited_pos;
}

