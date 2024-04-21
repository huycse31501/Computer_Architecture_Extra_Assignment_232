#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

typedef int8_t byte_t;
typedef int16_t half_t;
typedef int32_t word_t;

#define COLUMN_NUM 7
#define ROW_NUM 6

byte_t end_game;       
byte_t current_player; 
byte_t winner;         



byte_t piece_position[COLUMN_NUM][ROW_NUM];


byte_t column_height[COLUMN_NUM];


word_t piece_count;




void print_welcome_prompt(void);
void print_current_player_prompt(void);
void print_placement_column_prompt(void);
void print_ending_prompt(void);

byte_t ask_for_first_player(void);

word_t ask_for_new_piece_column(void);




void update_display_clear(void);

void update_display_add_new_piece(word_t column, byte_t player);




void initialize(void);

byte_t check_column_has_space(word_t column);

void place_piece_into_column(word_t column, byte_t player);

void update_game_state(word_t column);

void change_to_next_player_turn(void);

int main(void)
{
    initialize();
    print_welcome_prompt();
    current_player = ask_for_first_player();

    
    while (!end_game)
    {
        
        print_current_player_prompt();
        
        word_t next_piece_column = ask_for_new_piece_column();

        
        place_piece_into_column(next_piece_column, current_player);
        piece_count++;

        
        
        update_display_add_new_piece(next_piece_column, current_player);

        
        
        
        update_game_state(next_piece_column);

        change_to_next_player_turn();
    }

    
    
    
    print_ending_prompt();
}

void initialize(void)
{
    end_game = 0;
    current_player = 0;
    winner = 0;

    for (word_t i = 0; i < COLUMN_NUM; i++)
    {
        for (word_t j = 0; j < ROW_NUM; j++)
            piece_position[i][j] = 0;
        column_height[i] = 0;
    }

    piece_count = 0;

    update_display_clear();
}

void print_welcome_prompt(void)
{
    printf("Welcome to the game of Find Four\n");
    printf("In this game, two player which are 1 and 2 will take turn to place new pieces into "
           "a arbitrary column. There will be %d columns, each with %d rows.\n",
           COLUMN_NUM, ROW_NUM);
    printf("When put into a column, the piece will naturally fall to the lowest "
           "position. Pieces within each column will stack.\n");
    printf("The game ends when 4 pieces of a player form a horizontal, vertical "
           "or diagonal line. In such case, that player is the winner.");
    printf("In the case there is to space left to place new piece, the result "
           "is a draw between two player.\n");
}

void print_current_player_prompt(void)
{
    printf("Now is the turn of player %" PRId8 "\n", current_player);
}

void print_placement_column_prompt(void)
{
    printf("In which column do you want to place the next piece (0 to %d):\n",
           COLUMN_NUM - 1);
}

void print_ending_prompt(void)
{
    printf("The game ended as a ");

    if (winner == 0)
        printf("draw.\n");
    else if (winner == 1)
        printf("win for player #1.\n");
    else if (winner == 2)
        printf("win for player #2.\n");
}

byte_t ask_for_first_player(void)
{
    printf("Please input the player that will go first (1 or 2):\n");

    word_t first_player;
    while (1)
    {
        scanf("%" PRId32, &first_player); 
        if (first_player == 1 || first_player == 2)
            break;
        else
            printf("Accepted value is 1 or 2.\n");
    }

    return (byte_t) first_player;
}

word_t ask_for_new_piece_column(void)
{
    print_placement_column_prompt();

    word_t next_piece_column;
    while (1)
    {
        scanf("%" PRId32, &next_piece_column); 

        if (next_piece_column < COLUMN_NUM)
        {
            
        }
        else
        {
            printf("Accepted value is within range (0 - %d)\n.", COLUMN_NUM - 1);
            continue;
        }


        if (check_column_has_space(next_piece_column))
            break;
        else
            printf("The column chosen is full, please choose another column.\n");
    }

    return next_piece_column;
}

byte_t check_column_has_space(word_t column)
{
    if (column_height[column] >= ROW_NUM)
        return 0;
    else
        return 1;
}

void place_piece_into_column(word_t column, byte_t current_player)
{
    piece_position[column][column_height[column]] = current_player;
    column_height[column]++;
}

void update_display_clear(void)
{
    
    return;
}

void update_display_add_new_piece(word_t column, byte_t player)
{
    
    return;
}

void update_game_state(word_t column)
{
    word_t new_piece_row = column_height[column] - 1;
    byte_t new_piece_player = piece_position[column][new_piece_row];

    
    word_t inline_piece_count = 1;
    for (word_t i = new_piece_row - 1; i >= 0; i--) 
    {
        if (piece_position[column][i] == new_piece_player)
            inline_piece_count++;
        else
            break;
    }
    for (word_t i = new_piece_row + 1; i < COLUMN_NUM; i++)
    {
        if (piece_position[column][i] == new_piece_player)
            inline_piece_count++;
        else
            break;
    }
    if (inline_piece_count >= 4)
    {
        end_game = 1;
        winner = current_player;
        return;
    }

    
    inline_piece_count = 1;
    for (word_t i = column - 1; i >= 0; i--)
    {
        if (piece_position[i][new_piece_row] == new_piece_player)
            inline_piece_count++;
        else
            break;
    }
    for (word_t i = column + 1; i < ROW_NUM; i++)
    {
        if (piece_position[i][new_piece_row] == new_piece_player)
            inline_piece_count++;
        else
            break;
    }
    if (inline_piece_count >= 4)
    {
        end_game = 1;
        winner = current_player;
        return;
    }

    
    inline_piece_count = 1;
    for (word_t i = 1; (column-i) >= 0 && (new_piece_row+i) < ROW_NUM; i++)
    {
        if (piece_position[column-i][new_piece_row+i] == new_piece_player)
            inline_piece_count++;
        else
            break;
    }
    for (word_t i = 1; (column+i) < COLUMN_NUM && (new_piece_row-i) >= 0; i++)
    {
        if (piece_position[column+i][new_piece_row-i] == new_piece_player)
            inline_piece_count++;
        else
            break;
    }
    if (inline_piece_count >= 4)
    {
        end_game = 1;
        winner = current_player;
        return;
    }

    
    inline_piece_count = 1;
    for (word_t i = 1; (column-i) >= 0 && (new_piece_row-i) >= 0; i++)
    {
        if (piece_position[column-i][new_piece_row-i] == new_piece_player)
            inline_piece_count++;
        else
            break;
    }
    for (word_t i = 1; (column+i) < COLUMN_NUM && (new_piece_row+i) < ROW_NUM; i++)
    {
        if (piece_position[column+i][new_piece_row+i] == new_piece_player)
            inline_piece_count++;
        else
            break;
    }
    if (inline_piece_count >= 4)
    {
        end_game = 1;
        winner = current_player;
        return;
    }

    
    
    if (piece_count == ROW_NUM * COLUMN_NUM)
    {
        end_game = 1;
        winner = 0;
        return;
    }

    return; 
}

void change_to_next_player_turn(void)
{
    if (current_player == 1)
        current_player = 2;
    else if (current_player == 2)
        current_player = 1;
    else
        current_player = 1;
}
