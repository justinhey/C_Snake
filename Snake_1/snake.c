



#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<sys/time.h>
#include<signal.h>
#include"snake.h"




struct position food;		/* food position */
Snake_Node *head, *tail;	/* double linked list's head and tail */
int x_dir = 1, y_dir = 0;	/* init dirction of the snake moving */
int ttm = 5, ttg = 5;		/* two timers defined to control speed */



void main(void)
{


}


void Init_Disp()
{
	char wall = ' ';
	int i, j;
	initscr();              // 初始化curses库和tty
	cbreak();				// 开启输入立即响应
	noecho();
	curs_set(0);			// 	使光标不可见

	/* display some message about title and wall */
	attrset(A_NORMAL);		// 普通字符输出(不加亮显示)
	attron(A_REVERSE);		// 字符反白显示
	for (int i = 0; i < LINES; i++)
	{
		mvaddch(i, LEFT_EDGE, wall);
		mvaddch(i, RIGHT_EDGE, wall);
	}
	for (int j = 0; j < COLS; j++)
	{
		mvaddch(0, j, '=');
		mvaddch(TOP_ROW, j, wall);
		mvaddch(BOT_ROW, j, wall);
	}
	attroff(A_REVERSE);		/* turn off REVERSE */
	mvaddstr(1, 2, "Game: snake    version: 1.0    date: 2011/08/22");
	mvaddstr(2, 2, "Author: Dream Fly	Blog: blog.csdn.net/jjzhoujun2010");
	mvaddstr(3, 2, "Usage: Press 'f' to speed up, 's' to speed down,'q' to quit.");
	mvaddstr(4, 2, "       Nagivation key controls snake moving.");
	refresh();
}



/*
 * Function: Food_Disp()
 * Usage: display food position
 * Return: none
 */
void Food_Disp()
{
	/*
	  Srand是种下随机种子数，你每回种下的种子不一样，
	  用Rand得到的随机数就不一样。为了每回种下一个
	  不一样的种子，所以就选用Time(0)，Time(0)是得到
	  当前时时间值（因为每时每刻时间是不一样的了）
	*/
	srand(time(0));
	// rand() % (COLS - 2) 生成 0到(COLS - 2)范围内的随机数
	food.x_pos = rand() % (COLS - 2) + 1;
	food.y_pos = rand() % (LINES - TOP_ROW - 2) + TOP_ROW + 1;
	mvaddch(food.y_pos, food.x_pos, FOOD_SYMBOL);/* display the food */
	refresh();
}

/*
 * Function: DLL_Snake_Create()
 * Usage: create double linked list, and display the snake first node
 * Return: none
 */
void DLL_Snake_Create()
{
	Snake_Node *temp = (Snake_Node *)malloc(sizeof(Snake_Node));
	head = (Snake_Node *)malloc(sizeof(Snake_Node));
	tail = (Snake_Node *)malloc(sizeof(Snake_Node));
	if (temp == NULL || head == NULL || tail == NULL)
	{
		perror("malloc");
	}
	temp->x_pos = 5;
	temp->y_pos = 10;
	head->prev = NULL;
	tail->next = NULL;
	head->next = temp;
	temp->next = tail;
	tail->prev = temp;
	temp->prev = head;
	mvaddch(temp->y_pos,temp->x_pos,SNAKE_SYMBOL);
	refresh();
}




