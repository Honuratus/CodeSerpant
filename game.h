#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#ifndef game
#define game
typedef struct {
    int x;
    int y;
} Position;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct snake_node{
    Position position;
    struct snake_node* next;
}snake_node;

void generate_food_position(int row, int col, int* food_position);
void draw_game_board(int col, int row, snake_node** snake,int* food_position);
snake_node* update_snake_position(snake_node* head, Direction dir);
snake_node* initialize_snake();
snake_node* add_snake_node(snake_node* head,Direction dir);
char** initialize_board(int row,int col);
Direction get_direction(Position prev, Position curr);
int get_snake_len(snake_node* head);

#endif