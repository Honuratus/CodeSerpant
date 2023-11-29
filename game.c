#include "game.h"


void generate_food_position(int row, int col, int* food_position) {
    food_position[0] = rand() % (row - 2) + 1; 
    food_position[1] = rand() % (col - 2) + 1; 
}


char** initialize_board(int row,int col){
    int i,j;
    char** board = (char**)malloc(sizeof(char*) * row);
    if(!board){
        printf("Malloc error board**\n");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i<row; i++){
        board[i] = (char*)malloc(sizeof(char) * col);
        if(!board[i]){
            printf("Malloc error board[i]\n");
            exit(EXIT_FAILURE);
        }
    } 

    for(i = 0; i<row; i++){
        for(j = 0; j<col; j++){
            if(i == 0 || i == row-1){
                board[i][j] = '-';
            }
            else{
                if(j == 0 || j == col - 1) board[i][j] = '|';
                else board[i][j] = ' ';
            }
        }
    } 
    return board;
}



void draw_game_board(int row, int col, snake_node** snake, int* food_position){
    snake_node* iter = *snake;
    int i,j,score = get_snake_len(*snake);
    iter = *snake;
    
    char **board = initialize_board(row,col);
    while(iter != NULL){
        board[iter->position.x][iter->position.y] = 'O';
        iter = iter->next;
    }
    board[food_position[0]][food_position[1]] = 'F'; 
    for(i = 0; i<row; i++){
        for(j = 0; j<col; j++){
            printf("%c",board[i][j]);
        }
        printf("\n");
    }
    printf("Score: %d\n",score-1);
    for(i = 0; i<row; i++) free(board[i]);
    free(board);
}


snake_node* initialize_snake(){
    snake_node* node= (snake_node*)malloc(sizeof(snake_node));
    node->position.x = 1;
    node->position.y = 1;
    node->next = NULL;
    return node;
}

snake_node* update_snake_position(snake_node* head, Direction dir) {
    if (head == NULL) {
        printf("Wrong usage of function update_snake_function!");
        exit(EXIT_FAILURE);
    }

    int prevX = head->position.x;
    int prevY = head->position.y;
    int nextX, nextY;

    if(dir == UP){
        head->position.x--;
    }
    else if(dir == DOWN){
        head->position.x++;
    }
    else if(dir == LEFT){
        head->position.y--;
    }
    else if(dir == RIGHT){
        head->position.y++;
    }

    snake_node* iter = head->next;
    while(iter != NULL){
        nextX = iter->position.x;
        nextY = iter->position.y;
        iter->position.x = prevX;
        iter->position.y = prevY;
        prevX = nextX;
        prevY = nextY;
        snake_node* other = iter->next;
        while(other != NULL){
            if(other->position.x == head->position.x && other->position.y == head->position.y){
                printf("Game Over!\n");
                printf("Press any key to exit\n");
                getch();
                exit(EXIT_SUCCESS);
            }
            other = other->next;
        }   
        iter = iter->next;

    }
    return head;   
}

snake_node* add_snake_node(snake_node* head, Direction dir) {
    snake_node* iter = head;
    snake_node* new_node = initialize_snake(NULL);
    
    while(iter->next != NULL){
        iter = iter->next;
    }
    if(dir == UP){
        new_node->position.x = iter->position.x + 1;
        new_node->position.y = iter->position.y;
    }
    else if(dir == DOWN){
        new_node->position.x = iter->position.x - 1;
        new_node->position.y = iter->position.y;
    }
    else if(dir == LEFT){
        new_node->position.x = iter->position.x;
        new_node->position.y = iter->position.y + 1;
    }
    else if(dir == RIGHT){
        new_node->position.x = iter->position.x;
        new_node->position.y = iter->position.y - 1;
    }

    iter->next = new_node;
    return head;
}


Direction get_direction(Position prev, Position curr) {
    if (prev.x == curr.x) {
        if (prev.y < curr.y){
            return RIGHT;
        } 
        else if(prev.y > curr.y){
            return LEFT;
        }
        else{
            return RIGHT;
        }
    } 
    else if (prev.x < curr.x) {
        return DOWN;
    } 
    else {
        return UP;
    }
}

int get_snake_len(snake_node* head){
    snake_node* iter = head;
    int len = 0;
    while(iter != NULL){
        len++;
        iter = iter->next;
    }
    return len;
}