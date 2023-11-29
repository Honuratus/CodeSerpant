#include "game.h"

const int row = 16;
const int col = 32;

int main() {
    srand(time(NULL));
    snake_node* snake = initialize_snake();
    if (!snake) {
        printf("Malloc error snake\n");
        exit(EXIT_FAILURE);
    }
    Direction dir = RIGHT;

    int food_position[2];
    generate_food_position(32, 16, food_position);
    
    char ch;
    
    printf("Welcome to Snake Game!\n");
    printf("Press any key to start the game\n");
    getch();


    while (1) {
        if (_kbhit()) {   
            ch = _getch();

            switch (ch) {
                case 'w':
                    dir = UP;
                    break;
                case 'a':
                    dir = LEFT;
                    break;
                case 'd':
                    dir = RIGHT;
                    break;
                case 's':
                    dir = DOWN;
                    break;
            }
        }
        snake = update_snake_position(snake, dir);
        if((snake)->position.x == food_position[0] && snake->position.y == food_position[1]){
            generate_food_position(row,col,food_position);
            snake = add_snake_node(snake,dir);
        } 
        if(snake->position.x <= 0 || snake->position.x >= row || snake->position.y <= 0 || snake->position.y >= col){
            printf("Game Over!\n");
            printf("Press any key to exit\n");
            getch();
            break;
        }
        draw_game_board(row, col, &snake, food_position);
        Sleep(200);
        system("cls");   
    }

    // Free allocated memory before exiting
    snake_node* iter = snake;
    while(iter != NULL){
        snake_node* temp = iter->next;
        free(iter);
        iter = temp;
    }
    return 0;
}