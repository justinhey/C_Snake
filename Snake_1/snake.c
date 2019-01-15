



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
	initscr();              // ��ʼ��curses���tty
	cbreak();				// ��������������Ӧ
	noecho();
	curs_set(0);			// 	ʹ��겻�ɼ�

	/* display some message about title and wall */
	attrset(A_NORMAL);		// ��ͨ�ַ����(��������ʾ)
	attron(A_REVERSE);		// �ַ�������ʾ
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
	  Srand�������������������ÿ�����µ����Ӳ�һ����
	  ��Rand�õ���������Ͳ�һ����Ϊ��ÿ������һ��
	  ��һ�������ӣ����Ծ�ѡ��Time(0)��Time(0)�ǵõ�
	  ��ǰʱʱ��ֵ����Ϊÿʱÿ��ʱ���ǲ�һ�����ˣ�
	*/
	srand(time(0));
	// rand() % (COLS - 2) ���� 0��(COLS - 2)��Χ�ڵ������
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




