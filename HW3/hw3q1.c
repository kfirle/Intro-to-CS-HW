/*-------------------------------------------------------------------------
  Include files:
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

/*=========================================================================
  Constants and definitions:
=========================================================================*/
/* put your #defines and typedefs here*/
#define DOWN 2
#define LEFT 4
#define RIGHT 6
#define UP 8
#define INDEX_ARRAY_SIZE 2
#define EMPTY_INDEX_CELL -1
#define MIN_STEPS_WITHOUT_FOOD 2
#define MIN_BOARD_SIZE 4
#define MAX_BOARD_SIZE 25
#define N 25
#define ROWS_INDEXES 0
#define COLUMN_INDEXES 1
#define BOARD_ELEMENT '#'
#define EMPTY_BOARD_CELL ' '
#define FOOD 'F'
#define PERCENT 0
#define FIRST_PLAYER PERCENT
#define PERCENT_HEAD '%'
#define PERCENT_BODY '*'
#define SHTRODEL 1
#define SHTRODEL_HEAD '@'
#define SHTRODEL_BODY '+'
#define ILLEGAL_MOVE 0
#define SNAKE_DIES 1
#define ERROR -999
#define SNAKE_ATE 2
#define SNAKE_MOVED 1
#define USED_SOLTS 6
#define GAME_OVER -1
#define PLAYERS_NUM 2
#define INITIAL_SNAKE_SIZE 3
#define TWO_NUMBERS 2

/*-------------------------------------------------------------------------
*   Function declaration
*------------------------------------------------------------------------*/

void print_introduction_msg();
 //print welcome message , and introduction message to the game
void print_board_size_msg();
//print message to enter board size
void print_steps_without_food();
//print message to enter maximum number of steps can snake do without food
void print_food_location_msg();
//print message to insert place for next food
void help_print_board(int size);
//printing static part of the board
void print_board(char board[N][N], int size);
//print the current board for the user
void print_player_message(int player);
//print message when we switch between users
void print_insert_direction();
//print message asking the user to insert his move
void print_finsih_msg(int player,int finish_reason );
//get the player who lose and the reason of losing and print message state
void print_error_input();
//print message - there is error in the input
void print_invalid_input();
//print message - re-insert valid input
void print_full_board();
//print message - full board - no winner

int get_board_size();
int get_max_steps_without_food();
void clean_indexes_array (int p_index[INDEX_ARRAY_SIZE][N*N]);
void clean_the_board(char board[N][N], int size);
void save_initial_snakes_indexes(int size,int p0_index[INDEX_ARRAY_SIZE]
                                 [N*N],int p1_index[INDEX_ARRAY_SIZE]
                                 [N*N]);
void pre_game(char board[N][N],int size,int p0_index[INDEX_ARRAY_SIZE]
              [N*N],int p1_index[INDEX_ARRAY_SIZE][N*N]);
int get_food_locaction(char board[N][N],int size);
int food_existence (char board[N][N],int size);
int valid_direction_input(int dir);
int get_direction();
int valid_move(char board[N][N],int size,int i,int j,int dir);
int move(char board[N][N],int i,int j,int dir,int p_index
         [INDEX_ARRAY_SIZE][N*N],int player);
int get_snake_size(int p_index[INDEX_ARRAY_SIZE][N*N]);
int move_down(char board[N][N],int p_index[INDEX_ARRAY_SIZE]
              [N*N],int player);
int move_up(char board[N][N],int p_index[INDEX_ARRAY_SIZE]
            [N*N],int player);
int move_left(char board[N][N],int p_index[INDEX_ARRAY_SIZE]
              [N*N],int player);
int move_right(char board[N][N],int p_index[INDEX_ARRAY_SIZE]
               [N*N],int player);
int move_down_and_eat(char board[N][N],int p_index[INDEX_ARRAY_SIZE]
                      [N*N],int player);
int move_up_and_eat(char board[N][N],int p_index[INDEX_ARRAY_SIZE]
                    [N*N],int player);
int move_left_and_eat(char board[N][N],int p_index[INDEX_ARRAY_SIZE]
                      [N*N],int player);
int move_right_and_eat(char board[N][N],int p_index[INDEX_ARRAY_SIZE]
                       [N*N],int player);
int is_snake_dying(int max_steps,int steps_without_food,int player);
int is_board_full(char board[N][N],int size,int board_spaces);
int turn(char board[N][N],int size,int p_index[INDEX_ARRAY_SIZE][N*N]
         ,int player,int board_space);
void game(char board[N][N],int size,int max_steps_without_food,int
    p0_index[INDEX_ARRAY_SIZE][N*N],int p1_index[INDEX_ARRAY_SIZE][N*N]);
void move_the_tail(char board[N][N],int p_index[INDEX_ARRAY_SIZE][N*N]);
void update_indexes_array(int p_index[INDEX_ARRAY_SIZE][N*N],
                          int snake_size);
void update_head_after_eating(char board[N][N],int p_index
                              [INDEX_ARRAY_SIZE][N*N],int old_head_row,
                              int old_head_column,int player);

int main()
{
    int size,max_steps_without_food;
    int p0_index[INDEX_ARRAY_SIZE][N*N],p1_index[INDEX_ARRAY_SIZE][N*N];
    char board[N][N];
    size = get_board_size();
    if(size != ERROR)
    {
        max_steps_without_food = get_max_steps_without_food();
        if(max_steps_without_food != ERROR)
        {
            pre_game(board,size,p0_index,p1_index);
            game(board,size,max_steps_without_food,p0_index,p1_index);
        }
    }
  return 0;
}

//add here your own function implementation.

int get_board_size()
//length: 12 rows
//printing intro msg and reading the board size from the referee
{
    int size1;
    print_introduction_msg();
    print_board_size_msg();
    if(scanf("%d", &size1)!=1)
    {
        print_error_input();
        return ERROR;
    }
    while(size1 <MIN_BOARD_SIZE || size1 >MAX_BOARD_SIZE)
    {
       print_invalid_input();
       if(scanf("%d", &size1)!=1)
        {
            print_error_input();
            return ERROR;
        }
    }
    return size1;
}

int get_max_steps_without_food()
//length: 11 rows
//reading the food limit from the referee
{
    int max_steps1;
    print_steps_without_food();
    if(scanf("%d", &max_steps1)!=1)
    {
        print_error_input();
        return ERROR;
    }
    while(max_steps1 <MIN_STEPS_WITHOUT_FOOD)
    {
       print_invalid_input();
       if(scanf("%d", &max_steps1)!=1)
        {
            print_error_input();
            return ERROR;
        }
    }
    return max_steps1;
}

void clean_indexes_array (int p_index[INDEX_ARRAY_SIZE][N*N])
//length: 3 rows
//setting the indexes array's cells to -1
{
    for(int i=0;i<INDEX_ARRAY_SIZE;i++)
    {
        for(int j=0;j<(N*N);j++)
        {
            p_index[i][j]=EMPTY_INDEX_CELL;
        }
    }
}

void clean_the_board(char board[N][N], int size)
//length: 3 rows
//cleaning the board by changing the board cells to space
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            board[i][j]=EMPTY_BOARD_CELL;
        }
    }
}

void save_initial_snakes_indexes(int size,int p0_index[INDEX_ARRAY_SIZE]
                                [N*N],int p1_index[INDEX_ARRAY_SIZE][N*N])
//length: 6 rows
//saving the indexes of the snakes before the game starts
{
    for(int i=0;i<INITIAL_SNAKE_SIZE;i++)
    {
        p0_index[ROWS_INDEXES][i]=0;
        p0_index[COLUMN_INDEXES][i]=i;
    }
    for(int i=0;i<INITIAL_SNAKE_SIZE;i++)
    {
        p1_index[ROWS_INDEXES][i]=size-1;
        p1_index[COLUMN_INDEXES][i]=i;
    }
}

void pre_game(char board[N][N],int size,int p0_index[INDEX_ARRAY_SIZE]
              [N*N],int p1_index[INDEX_ARRAY_SIZE][N*N])
//length: 10 rows
//placing the snakes on the board and running the pre-game procedures
{
    clean_the_board(board,size);
    clean_indexes_array(p0_index);
    clean_indexes_array(p1_index);
    board[0][0] = PERCENT_HEAD;
    for(int i=1;i<INITIAL_SNAKE_SIZE;i++)
    {
        board[0][i] = PERCENT_BODY;
    }
    board[size-1][0] = SHTRODEL_HEAD;
    for(int i=1;i<INITIAL_SNAKE_SIZE;i++)
    {
        board[size-1][i] = SHTRODEL_BODY;
    }
    save_initial_snakes_indexes(size,p0_index,p1_index);
}

int get_food_locaction(char board[N][N],int size)
//length: 12 rows
//reading the food location from the referee
{
    int row1,column1,invalid=1;
    print_food_location_msg();
    while(invalid ==1)
    {
        if(scanf("%d %d", &row1, &column1)!=TWO_NUMBERS)
        {
            print_error_input();
            return ERROR;
        }
        if((row1>=0 && row1<size)&&(column1>=0 && column1 <size))
        {
            if(board[row1][column1]==EMPTY_BOARD_CELL)
            {
                board[row1][column1]=FOOD;
                return 0;
            }
        }
        print_invalid_input();
    }
    return 0;
}

int food_existence (char board[N][N],int size)
//length: 5 rows
//checking whether there is food on the board
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if(board[i][j]==FOOD)
            {
                return 1;
            }
        }
    }
    return 0;
}

int valid_direction_input(int dir)
//length: 6 rows
// checking if the input is 2/4/6/8
{
    switch(dir)
    {
    case DOWN:
        return DOWN;
    case LEFT:
        return LEFT;
    case RIGHT:
        return RIGHT;
    case UP:
        return UP;
    }
    return 0;
}

int get_direction()
//length: 13 rows
//reading the player's move
{
    int direction1,valid_dir=0;
    print_insert_direction();
    if(scanf("%d", &direction1)!=1)
    {
        print_error_input();
        return ERROR;
    }
    valid_dir = valid_direction_input(direction1);
    while(valid_dir==0)
    {
       print_invalid_input();
       if(scanf("%d", &direction1)!=1)
       {
           print_error_input();
           return ERROR;
       }
       valid_dir = valid_direction_input(direction1);
    }
    return direction1;
}

int valid_move(char board[N][N],int size,int i,int j,int dir)
//length: 14 rows
//checking if the move is a legal move
//int i - the head's row index, int j - the head's column index
{
    switch(dir)
    {
    case DOWN:
        if(i+1<size)
        {
            return (board[i+1][j]==EMPTY_BOARD_CELL||board[i+1][j]==FOOD);
        }
        return ILLEGAL_MOVE;
    case LEFT:
        if(j-1>=0)
        {
            return (board[i][j-1]==EMPTY_BOARD_CELL||board[i][j-1]==FOOD);
        }
        return ILLEGAL_MOVE;
    case RIGHT:
        if(j+1<size)
        {
            return(board[i][j+1]==EMPTY_BOARD_CELL||board[i][j+1]==FOOD);
        }
        return ILLEGAL_MOVE;
    case UP:
        if(i-1>=0)
        {
            return (board[i-1][j]==EMPTY_BOARD_CELL||board[i-1][j]==FOOD);
        }
        return ILLEGAL_MOVE;
    }
    return ILLEGAL_MOVE;
}

int move(char board[N][N],int i,int j,int dir,int p_index
         [INDEX_ARRAY_SIZE][N*N],int player)
//length: 14 rows
//calling the relevant moving function
//int i - the head's row index, int j - the head's column index
{
    switch(dir)
    {
        case DOWN:
        {
            if(board[i+1][j]==EMPTY_BOARD_CELL)
            {
                return move_down(board,p_index,player);
            }
            else
            {
                return move_down_and_eat(board,p_index,player);
            }
        }
        case LEFT:
        {
            if(board[i][j-1]==EMPTY_BOARD_CELL)
            {
                return move_left(board,p_index,player);
            }
            else
            {
                return move_left_and_eat(board,p_index,player);
            }
        }
        case RIGHT:
        {
            if(board[i][j+1]==EMPTY_BOARD_CELL)
            {
                return move_right(board,p_index,player);
            }
            else
            {
                return move_right_and_eat(board,p_index,player);
            }
        }
        case UP:
        {
            if(board[i-1][j]==EMPTY_BOARD_CELL)
            {
                return move_up(board,p_index,player);
            }
            else
            {
                return move_up_and_eat(board,p_index,player);
            }
        }
    }
    return 1;
}

int get_snake_size(int p_index[INDEX_ARRAY_SIZE][N*N])
//length: 4 rows
//returns the snake's size
{
    int count=0;
    while(p_index[ROWS_INDEXES][count]!=EMPTY_INDEX_CELL)
    {
        count++;
    }
    return count;
}

void move_the_tail(char board[N][N],int p_index[INDEX_ARRAY_SIZE][N*N])
//length: 5 rows
//moving the snake's tail
{
    int snake_size = get_snake_size(p_index);
    int tail_row=p_index[ROWS_INDEXES][snake_size-1];
    int tail_column=p_index[COLUMN_INDEXES][snake_size-1];
    board[tail_row][tail_column]=EMPTY_BOARD_CELL;
    update_indexes_array(p_index,snake_size);
}

void update_indexes_array(int p_index[INDEX_ARRAY_SIZE][N*N],
                          int snake_size)
//length: 3 rows
//updating the snake's indexes array
{
    for(int i=snake_size-1;i>0;i--)
    {
        p_index[ROWS_INDEXES][i] = p_index[ROWS_INDEXES][i-1];
        p_index[COLUMN_INDEXES][i] = p_index[COLUMN_INDEXES][i-1];
    }
}
int move_down(char board[N][N],int p_index[INDEX_ARRAY_SIZE]
              [N*N],int player)
//length: 10 rows
//moving the snake down by one square
{
    move_the_tail(board,p_index);
    p_index[ROWS_INDEXES][0]++;
    int head_row = p_index[ROWS_INDEXES][0];
    int head_column = p_index[COLUMN_INDEXES][0];
    if(player==PERCENT)
    {
        board[head_row][head_column]=PERCENT_HEAD;
        board[head_row-1][head_column]=PERCENT_BODY;
    }
    else
    {
        board[head_row][head_column]=SHTRODEL_HEAD;
        board[head_row-1][head_column]=SHTRODEL_BODY;
    }
    return SNAKE_MOVED;
}

int move_up(char board[N][N],int p_index[INDEX_ARRAY_SIZE]
            [N*N],int player)
//length: 10 rows
//moving the snake up by one square
{
    move_the_tail(board,p_index);
    p_index[ROWS_INDEXES][0]--;
    int head_row = p_index[ROWS_INDEXES][0];
    int head_column = p_index[COLUMN_INDEXES][0];
    if(player==PERCENT)
    {
        board[head_row][head_column]=PERCENT_HEAD;
        board[head_row+1][head_column]=PERCENT_BODY;
    }
    else
    {
        board[head_row][head_column]=SHTRODEL_HEAD;
        board[head_row+1][head_column]=SHTRODEL_BODY;
    }
    return SNAKE_MOVED;
}

int move_left(char board[N][N],int p_index[INDEX_ARRAY_SIZE]
              [N*N],int player)
//length: 10 rows
//moving the snake left by one square
{
    move_the_tail(board,p_index);
    p_index[COLUMN_INDEXES][0]--;
    int head_row = p_index[ROWS_INDEXES][0];
    int head_column = p_index[COLUMN_INDEXES][0];
    if(player==PERCENT)
    {
        board[head_row][head_column]=PERCENT_HEAD;
        board[head_row][head_column+1]=PERCENT_BODY;
    }
    else
    {
        board[head_row][head_column]=SHTRODEL_HEAD;
        board[head_row][head_column+1]=SHTRODEL_BODY;
    }
    return SNAKE_MOVED;
}

int move_right(char board[N][N],int p_index[INDEX_ARRAY_SIZE]
               [N*N],int player)
//length: 10 rows
//moving the snake right by one square
{
    move_the_tail(board,p_index);
    p_index[COLUMN_INDEXES][0]++;
    int head_row = p_index[ROWS_INDEXES][0];
    int head_column = p_index[COLUMN_INDEXES][0];
    if(player==PERCENT)
    {
        board[head_row][head_column]=PERCENT_HEAD;
        board[head_row][head_column-1]=PERCENT_BODY;
    }
    else
    {
        board[head_row][head_column]=SHTRODEL_HEAD;
        board[head_row][head_column-1]=SHTRODEL_BODY;
    }
    return SNAKE_MOVED;
}

void update_head_after_eating(char board[N][N],int p_index
                              [INDEX_ARRAY_SIZE][N*N],int old_head_row,
                              int old_head_column,int player)
//length: 7 rows
//change the position of the head on the board after the snake eats
{
    int head_row = p_index[ROWS_INDEXES][0];
    int head_column = p_index[COLUMN_INDEXES][0];
    if(player==PERCENT)
    {
        board[head_row][head_column]=PERCENT_HEAD;
        board[old_head_row][old_head_column]=PERCENT_BODY;
    }
    else
    {
        board[head_row][head_column]=SHTRODEL_HEAD;
        board[old_head_row][old_head_column]=SHTRODEL_BODY;
    }
}
int move_down_and_eat(char board[N][N],int p_index[INDEX_ARRAY_SIZE]
                      [N*N],int player)
//length: 8 rows
//moving the snake down into a food square
{
    int old_head_row = p_index[ROWS_INDEXES][0];
    int old_head_column = p_index[COLUMN_INDEXES][0];
    int snake_size = get_snake_size(p_index);
    update_indexes_array(p_index,snake_size+1);
    p_index[ROWS_INDEXES][0]++;
    update_head_after_eating(board,p_index,old_head_row,old_head_column
                             ,player);
    return SNAKE_ATE;
}

int move_up_and_eat(char board[N][N],int p_index[INDEX_ARRAY_SIZE]
                    [N*N],int player)
//length: 8 rows
//moving the snake up into a food square
{
    int old_head_row = p_index[ROWS_INDEXES][0];
    int old_head_column = p_index[COLUMN_INDEXES][0];
    int snake_size = get_snake_size(p_index);
    update_indexes_array(p_index,snake_size+1);
    p_index[ROWS_INDEXES][0]--;
    update_head_after_eating(board,p_index,old_head_row,old_head_column
                             ,player);
    return SNAKE_ATE;
}

int move_left_and_eat(char board[N][N],int p_index[INDEX_ARRAY_SIZE]
                      [N*N],int player)
//length: 8 rows
//moving the snake left into a food square
{
    int old_head_row = p_index[ROWS_INDEXES][0];
    int old_head_column = p_index[COLUMN_INDEXES][0];
    int snake_size = get_snake_size(p_index);
    update_indexes_array(p_index,snake_size+1);
    p_index[COLUMN_INDEXES][0]--;
    update_head_after_eating(board,p_index,old_head_row,old_head_column
                             ,player);
    return SNAKE_ATE;
}

int move_right_and_eat(char board[N][N],int p_index[INDEX_ARRAY_SIZE]
                       [N*N],int player)
//length: 8 rows
//moving the snake right into a food square
{
    int old_head_row = p_index[ROWS_INDEXES][0];
    int old_head_column = p_index[COLUMN_INDEXES][0];
    int snake_size = get_snake_size(p_index);
    update_indexes_array(p_index,snake_size+1);
    p_index[COLUMN_INDEXES][0]++;
    update_head_after_eating(board,p_index,old_head_row,old_head_column
                             ,player);
    return SNAKE_ATE;
}

int is_snake_dying(int max_steps,int steps_without_food,int player)
//length: 4 rows
/*checking whether the snake has reached the limit of steps without food
and finishing the game if it has*/
{
    if(steps_without_food == max_steps)
    {
        print_finsih_msg(player,SNAKE_DIES);
        return 1;
    }
    return 0;
}

int is_board_full(char board[N][N],int size,int board_spaces)
//length: 5 rows
//checking whether the board is full and finishing the game if it is
{
    if(board_spaces==0)
    {
        print_board(board,size);
        print_full_board();
        return 1;
    }
    return 0;
}

int turn(char board[N][N],int size,int p_index[INDEX_ARRAY_SIZE][N*N]
         ,int player,int board_space)
//length: 16 rows
//checking if the game is over and running the player's turn if it is not
{
    int head_row_i=p_index[ROWS_INDEXES][0];
    int head_column_i=p_index[COLUMN_INDEXES][0];
    if(is_board_full(board,size,board_space)==1)
    {
        return GAME_OVER;
    }
    if(food_existence(board,size)==0)
    {
        if(get_food_locaction(board,size)== ERROR)
        {
            return GAME_OVER;
        }
    }
    print_board(board,size);
    print_player_message(player);
    int dir = get_direction();
    if(dir == ERROR)
    {
        return GAME_OVER;
    }
    if(valid_move(board,size,head_row_i,head_column_i,dir)==ILLEGAL_MOVE)
    {
        print_finsih_msg(player,ILLEGAL_MOVE);
        return GAME_OVER;
    }
    return move(board,head_row_i,head_column_i,dir,p_index,player);
}

void game(char board[N][N],int size,int max_steps_without_food,
          int p0_index[INDEX_ARRAY_SIZE][N*N],int p1_index
          [INDEX_ARRAY_SIZE][N*N])
//length: 14 rows
/*calling the turn function for each player by his turn and finishes
running the program when the game is over*/
{
    int board_space=((size*size)-USED_SOLTS),player=PERCENT,turn_status=1;
    int steps_without_food [] ={0,0};
    while(turn_status!=GAME_OVER)
    {
        if(player==PERCENT)
        {
            turn_status = turn(board,size,p0_index,player,board_space);
        }
        else
        {
            turn_status = turn(board,size,p1_index,player,board_space);
        }
        if(turn_status==SNAKE_ATE)
        {
            steps_without_food[player]=0;
            board_space--;
        }
        else
        {
            steps_without_food[player]++;
        }
        if(is_snake_dying(max_steps_without_food,
                          steps_without_food[player],player))
        {
            turn_status=GAME_OVER;
        }
        player=(player+1)%PLAYERS_NUM;
    }
}

void print_introduction_msg()
{
    printf("Welcome to multi-snake  game, The game have 2 player Percent and Shtrodel.\n"
    "The game starts with PERCENT player.\n");
    printf("You have to choose 4 moves :Up,Down,Right and Left "
    "The Percent player is the snake that starts in (0,0)\n\n");
}

void print_board_size_msg(){
    printf("Insert board size between 4 and 25:\n");
}

void print_steps_without_food(){
    printf("Insert the maximum number of steps the snake can do without food:\n");
}

void print_food_location_msg(){
    printf("in order to continue the game please Insert a row then column numbers to place the next food: \n");
}

void help_print_board(int size)
{
    int i=0;
    printf("%c",BOARD_ELEMENT);
    for(i=0;i<size;i++)
    {
        printf("%c",BOARD_ELEMENT);
    }
    printf("%c\n",BOARD_ELEMENT);
}

void print_board(char board[N][N], int size)
{
    int i=0,j=0;
    help_print_board(size);
    for(i=0;i<size;i++)
    {
        printf("%c",BOARD_ELEMENT);
        for(j=0;j<size;j++)
        {
            printf("%c",board[i][j]);
        }
        printf("%c\n",BOARD_ELEMENT);
    }
    help_print_board(size);
    printf("\n\n");
}

void print_player_message(int player )
{
    printf("******* Turn of %c ***********\n",player==PERCENT?PERCENT_HEAD:SHTRODEL_HEAD);
}

void print_insert_direction(){
    printf("Enter the direction to move your snake: (2-down,4-left,6-right,8-up):\n");
}

void print_finsih_msg(int player ,int finish_reason)
{
    printf("\nThe game finish and the winner is:\n");
    printf("*** %s player ****.\n",player==PERCENT?"SHTRODEL":"PERCENT");
    printf("The reason is %s of the ",finish_reason==ILLEGAL_MOVE? "Illegal move" : "Snake die");
    printf("%s player.\n\n",player==PERCENT?"PERCENT":"SHTRODEL");
}

void print_invalid_input(){
    printf("Please re-Inset valid input:\n");
}

void print_full_board(){
    printf("Full Board. The game over with no Winner.\n");
}
void print_error_input(){
    printf("Error with the input.\n");
}
