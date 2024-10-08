#include "state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_state_t *state, unsigned int row,
                         unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_state_t *state, unsigned int snum);
static char next_square(game_state_t *state, unsigned int snum);
static void update_tail(game_state_t *state, unsigned int snum);
static void update_head(game_state_t *state, unsigned int snum);

/* Task 1 */
game_state_t *create_default_state() {
  // TODO: Implement this function.
  game_state_t *game = malloc(sizeof(game_state_t));

  game->num_rows = 18;
  game->num_snakes = 1;

  game->board = malloc(18 * sizeof(char *));
  for (int i = 0; i < 18; i++) {
    game->board[i] = malloc(21 * sizeof(char));
  }
  strcpy(game->board[0], "####################\n");
  strcpy(game->board[17], "####################\n");
  for (int i = 1; i < 17; i++) {
    strcpy(game->board[i], "#                  #\n");
  };
  snake_t *snake = malloc(sizeof(snake_t));
  snake->tail_row = 2;
  snake->tail_col = 2;
  snake->head_row = 2;
  snake->head_col = 4;
  snake->live = 1;

  game->snakes = snake;

  game->board[2][4] = 'D';
  game->board[2][2] = 'd';
  game->board[2][3] = '>';
  game->board[2][9] = '*';

  return game;
}

/* Task 2 */
void free_state(game_state_t *state) {
  // TODO: Implement this function.
  free(state->snakes);
  for (int i = 0; i < state->num_rows; i++) {
    free(state->board[i]);
  }
  free(state->board);
  free(state);
  return;
}

/* Task 3 */
void print_board(game_state_t *state, FILE *fp) {
  // TODO: Implement this function.
  for (int i = 0; i < state->num_rows; i++) {
    fprintf(fp, "%s", state->board[i]);
  }
  return;
}

/*
  Saves the current state into filename. Does not modify the state object.
  (already implemented for you).
*/
void save_board(game_state_t *state, char *filename) {
  FILE *f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_state_t *state, unsigned int row, unsigned int col) {
  return state->board[row][col];
}

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_state_t *state, unsigned int row,
                         unsigned int col, char ch) {
  state->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  // TODO: Implement this function.
  if (c != 'w' && c != 'a' && c != 's' && c != 'd') {
    return false;
  }
  return true;
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  // TODO: Implement this function.
  if (c != 'W' && c != 'A' && c != 'S' && c != 'D') {
    return false;
  }
  return true;
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  // TODO: Implement this function.
  const char snake_chars[] = "wasd^<v>WASDx";

  // Loop through the list of snake characters
  for (int i = 0; snake_chars[i] != '\0'; i++) {
    if (c == snake_chars[i]) {
      return true;
    }
  }
  return false;
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  // TODO: Implement this function.
  switch (c) {
  case '^':
    return 'w';
    break;
  case '<':
    return 'a';
    break;
  case 'v':
    return 's';
    break;
  case '>':
    return 'd';
    break;
  }
  return '?';
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  // TODO: Implement this function.
  switch (c) {
  case 'W':
    return '^';
    break;
  case 'A':
    return '<';
    break;
  case 'S':
    return 'v';
    break;
  case 'D':
    return '>';
    break;
  }
  return '?';
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  // TODO: Implement this function.
  switch (c) {
  case 'v':
  case 's':
  case 'S':
    return cur_row + 1;
  case '^':
  case 'w':
  case 'W':
    return cur_row - 1;
  }
  return cur_row;
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  // TODO: Implement this function.
  if (c == '>' || c == 'd' || c == 'D') {
    return cur_col + 1;
  } else if (c == '<' || c == 'a' || c == 'A') {
    return cur_col - 1;
  }
  return cur_col;
}

/*
  Task 4.2

  Helper function for update_state. Return the character in the cell the snake
  is moving into.

  This function should not modify anything.
*/
static char next_square(game_state_t *state, unsigned int snum) {
  // TODO: Implement this function.

  snake_t snake = state->snakes[snum];

  unsigned int cur_row = snake.head_row;
  unsigned int cur_col = snake.head_col;

  unsigned int next_row =
      get_next_row(cur_row, get_board_at(state, cur_row, cur_col));
  unsigned int next_col =
      get_next_col(cur_col, get_board_at(state, cur_row, cur_col));

  return get_board_at(state, next_row, next_col);
}

/*
  Task 4.3

  Helper function for update_state. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the
  head.
*/
static void update_head(game_state_t *state, unsigned int snum) {
  // TODO: Implement this function.

  snake_t snake = state->snakes[snum];

  unsigned int cur_row = snake.head_row;
  unsigned int cur_col = snake.head_col;

  unsigned int next_row =
      get_next_row(cur_row, get_board_at(state, cur_row, cur_col));
  unsigned int next_col =
      get_next_col(cur_col, get_board_at(state, cur_row, cur_col));

  char cur_head = get_board_at(state, cur_row, cur_col);

  set_board_at(state, next_row, next_col, cur_head);

  set_board_at(state, cur_row, cur_col, head_to_body(cur_head));

  state->snakes[snum].head_row = next_row;
  state->snakes[snum].head_col = next_col;

  return;
}

/*
  Task 4.4

  Helper function for update_state. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_state_t *state, unsigned int snum) {
  // TODO: Implement this function.
  snake_t snake = state->snakes[snum];

  
    char c = get_board_at(state, snake.tail_row, snake.tail_col);
    set_board_at(state, snake.tail_row, snake.tail_col, ' ');
    unsigned int row = get_next_row(snake.tail_row, c);
    unsigned int col = get_next_col(snake.tail_col, c);
    c = get_board_at(state, row, col);
    set_board_at(state, row, col, body_to_tail(c));
    (state->snakes)[snum].tail_col = col;
    (state->snakes)[snum].tail_row = row;
  

  return;
}

/* Task 4.5 */
void update_state(game_state_t *state, int (*add_food)(game_state_t *state)) {
  // TODO: Implement this function.
  for (unsigned int i = 0; i < state->num_snakes; i++) {
    char c = next_square(state, i);
    if ('#' == c || is_snake(c)) {
      snake_t snake = (state->snakes)[i];
      (state->snakes)[i].live = false;
      set_board_at(state, snake.head_row, snake.head_col, 'x');
    } else if ('*' == c) {
      update_head(state, i);
      add_food(state);
    } else if (' ' == c) {
      update_head(state, i);
      update_tail(state, i);
    }
  }
  return;
}

/* Task 5.1 */
char *read_line(FILE *fp) {
  // TODO: Implement this function.
  int buffer_size = 64;
    char *buffer = (char *)malloc(buffer_size * sizeof(char));
    if(!buffer){
        fprintf(stderr, "内存分配失败\n");
        exit(1);
    }
    int pos = 0;
    while(1){
        if(!fgets(buffer + pos, buffer_size - pos, fp)){
            break;
        }
        char *newline = strchr(buffer + pos, '\n');
        if(newline){
            *newline = '\n';
            *(newline + 1) = '\0';
            break;
        }
        pos = strlen(buffer);
        if(pos == buffer_size - 1){
            buffer_size += buffer_size;
            char *new_buffer = realloc(buffer, buffer_size);
            if(!new_buffer){
                free(buffer);
                fprintf(stderr, "内存分配失败\n");
                exit(1);
            }
            buffer = new_buffer;
            // printf("%d ", buffer_size);
        }
    }
    // printf(" | ");
    return buffer;
}

/* Task 5.2 */
game_state_t *load_board(FILE *fp) {
  // TODO: Implement this function.
  game_state_t *game = malloc(sizeof(game_state_t));
  game->num_snakes = 0;
  game->snakes = NULL;
  int i = 0;

  for (; !feof(fp); i++) {
  game->board = realloc(game->board, sizeof(char *) * (unsigned int) (i + 1) );
  game->board[i] = read_line(fp);
  }
  free(game->board[i-1]);
  game->num_rows = (unsigned int)(i - 1);


  return game;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_state_t *state, unsigned int snum) {
  // TODO: Implement this function.
  snake_t snake = state->snakes[snum];
  
  unsigned int tail_row = snake.tail_row;
  unsigned int tail_col = snake.tail_col;
  char tail = get_board_at(state,tail_row,tail_col);
  char temp = tail;

  unsigned int cur_row = tail_row;
  unsigned int cur_col = tail_col;
  while (!is_head(temp)) {
  cur_row = get_next_row(cur_row,temp);
  cur_col = get_next_col(cur_col, temp);

  temp = get_board_at(state, cur_row, cur_col);
  }

  state->snakes[snum].head_row = cur_row;
  state->snakes[snum].head_col = cur_col;

  return;
}

/* Task 6.2 */
game_state_t *initialize_snakes(game_state_t *state) {
  // TODO: Implement this function.
   unsigned int rows = state -> num_rows;
  unsigned int snakes = 0;
  state -> snakes = (snake_t*)malloc(1000 * sizeof(snake_t));
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < strlen(state -> board[i]); j++){
      if(is_tail(state -> board[i][j])){
        state -> snakes[snakes].tail_row = (unsigned int)i;
        state -> snakes[snakes].tail_col = (unsigned int)j;
        state -> snakes[snakes].live     = true;
        find_head(state, snakes);
        snakes++;
      }
    }
  }
  state -> num_snakes = snakes;
  return state;
}
