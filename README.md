# 61C Project 1: snek

p print_board(state, stdout) to print out your entire board while debugging in cgdb.

## char**

char** 实际上就是一个指向char*类型的指针，也就是说，是一个指向数组开头的指针。

char1 = malloc(21 * sizeof(char));
这一行正确地分配了内存，它为一个字符数组分配了 21 个字符的空间（包括空字符 \0）。
char* char1 = "####################\0";
这一行试图将一个字符串字面量赋值给 char1，但这样做是错误的。字符串字面量（如 "####################\0"）实际上是一个指向字符串开始处的常量指针，因此您不能直接修改这个地址所指向的内容。

利用strcpy可以很方便的赋值

`strcpy(char1, "####################");`

我们使用 strcpy 函数将字符串字面量复制到了 char1 指向的内存区域。
字符串字面量 "####################" 实际上有 20 个字符加上一个自动添加的终止符 \0，所以它只需要 21 个字节的空间。

## 从文件中读取一行

C语言从[stdin](https://so.csdn.net/so/search?q=stdin&spm=1001.2101.3001.7020)读取一行字符串的几种方法

### 1.gets

gets函数的头文件是<stdio.h>,原型如下：

```
char *gets(char *s);
```

gets从stdin中读入一行内容到s指定的[buffer](https://so.csdn.net/so/search?q=buffer&spm=1001.2101.3001.7020)中，当遇到换行符或EOF时读取结束。读取成功时，返回s地址；失败时返回null。需要注意的是，gets会将行末尾的’\n’字符或EOF替换成’\0’，这样，gets读取的内容中不包括’\n’字符。如果要获取读取字符串的长度，可以调用strlen函数获得。

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int size = 1024; 
	char* buff = (char*)malloc(size);
 
	// read lines
	while(NULL != gets(buff)){
		printf("Read line with len: %d\n", strlen(buff));
		printf("%s", buff);
	}
	
	// free buff
	free(buff);	
}

```

### 2.fgets

fgets函数的头文件是<stdio.h>,原型如下：

```
char *fgets(char *s, int size, FILE*stream);
```

fgets从stream中读取最多size-1大小的内容到s指定的buffer中，当遇到换行符或EOF时读取结束。读取成功时，返回s地址；失败时返回null。需要注意的是，fgets会在所读取的内容后面添加’\0’，这样，fgets读取的内容中会包括行末尾的’\n’字符。如果要获取读取字符串的长度，可以调用strlen函数获得。

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main()
{
	int size = 1024;
	char* buff = (char*)malloc(size);
 
	// read lines
	while(NULL != fgets(buff, size, stdin)){
		printf("Read line with len: %d\n", strlen(buff));
		printf("%s", buff);
	}	
	// free buff
	free(buff);	
}
```

### 3.getline

getline函数的头文件是<stdio.h>,原型如下：

```
ssize_t getline(char **lineptr,size_t *n, FILE *stream);
```

getline从stream中读取一行内容到_lineptr所指定的buffer中，当遇到换行符或EOF时读取结束。＊n是_lineptr所指定的buffer的大小，如果＊n小于读入的内容长度，getline会自动扩展buffer长度，并更新_lineptr和_n的值。读取成功时，返回读入的字符个数；失败时返回-1。需要注意的是，gelines读取的内容中会包括行末尾的’\n’字符。

```

#include <stdio.h>
#include <stdlib.h>
 
int
main(void)
{
   char *line = NULL;
   size_t len = 0;
   ssize_t read;
 
   while ((read = getline(&line, &len, stdin)) != -1) {
       printf("Retrieved line of length %zu, %u :\n", read, len);
       printf("%s", line);
   }
 
   free(line);
   exit(EXIT_SUCCESS);
}

```

### 4.自己实现my_getline

可以自己实现，原型如下：

```
int my_getline(char* line, intmax_size);
```

my_getline从stdin中读取最多max_size-1个字符到line所指定的buff中，当遇到换行符或EOF时读取结束。读取成功时，返回读取的字符串长度；失败时返回0。my_getline读取的内容中会包括行末尾的’\n’字符。

```
#include <stdio.h>
#include <stdlib.h>
 
int my_getline(char* line, int max_size)
{
	int c;
	int len = 0;
	while( (c = getchar()) != EOF && len < max_size ){
		line[len++] = c;
		if('\n' == c)
			break;
	}
 
	
	line[len] = '\0';
	return len;
}
 
int main()
{
	int max_size = 1024;
	char* buff = (char*)malloc( sizeof(char) * max_size );
 
	//getline
	int len;
	while(0 != (len = my_getline(buff, max_size))){
		printf("Read line with len: %d\n", len);
		printf("%s", buff);
	}
	
	free(buff);
}

```

参考：

[1] Linux Programmer’s Manual.

[2] Brian W. Kernighan and Dennis M.Ritchie. The C Programming Language, Second Edition.

## 关于`\n`的超级大坑点

一开始我的task1和task3是这样的，前几个测试看起来没有任何问题

```c
game_state_t *create_default_state() {
  // TODO: Implement this function.
  game_state_t *game = malloc(sizeof(game_state_t));

  game->num_rows = 18;
  game->num_snakes = 1;

  game->board = malloc(18 * sizeof(char *));
  for (int i = 0; i < 18; i++) {
    game->board[i] = malloc(21 * sizeof(char));
  }
  strcpy(game->board[0], "####################");
  strcpy(game->board[17], "####################");
  for (int i = 1; i < 17; i++) {
    strcpy(game->board[i], "#                  #");
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

/* Task 3 */
void print_board(game_state_t *state, FILE *fp) {
  // TODO: Implement this function.
  for (int i = 0; i < state->num_rows; i++) {
    fprintf(fp, "%s\n", state->board[i]);
  }
  return;
}
```

实际上有一个大错误！就是我在初始化的时候每一行结尾并没有\n换行符，但是我打印的时候加上了这个换行符，因为前面几个问题都是加载我自己写的初始化board，所以后面才看起来正常。但是一旦做了task5.2这个问题就会暴露出来，因为加载的是它提供给我的board，是有`\n`的board！