#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#include<Windows.h>               //������ ���� ��� ��� ����
#include<conio.h>                 //getch,kbhit ��� ����
#include<MMSystem.h>              //���� ��� ���ؼ� �߰�
#pragma comment(lib, "winmm.lib" )//���� ��� ���ؼ� �߰�

#define MAX_X 180                 //��Ʈ ������ ȭ�� ũ��
#define MAX_Y 40                  //��Ʈ ������ ȭ�� ũ��

#define LEFT   75                 //Player2 �̵� Ű���� ��

#define RIGHT  77                 //

#define UP     72                 //

#define DOWN   80                 //

#define GET_H  5				  //���ں� ��� ��Ʈ ��ġ ����

#ifndef __COLOR_LIST_			  //���� ����Ʈ, ������ ����
#define __COLOR_LIST_             //�ܼ� �ؽ�Ʈ ����
enum
{
	black,
	blue,
	green,
	cyan,
	red,
	purple,
	brown,
	lightgray,
	darkgray,
	lightblue,
	lightgreen,
	lightcyan,
	lightred,
	lightpurple,
	yellow,
	white
};
#endif

typedef struct _HERO {			//�÷��̾� ���� ����ü
	int *color;					//�÷��̾� ����
	char *shape;				//�÷��̾� ���

}HERO;



int array_intro[17][24] =		//���� ���۽� ��Ÿ���� ¯�� �� ��Ʈ��
{
0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,
0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,0,0,
0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,
0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,1,1,0,0,0,0,1,0,0,
0,0,0,0,1,1,0,1,0,1,1,0,0,0,1,0,1,1,0,0,0,1,0,0,
0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,0,0,
0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,1,0,0,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
0,1,0,0,0,1,0,0,1,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,
0,0,1,1,0,1,0,0,1,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,
0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0
};
int chocobi[7][38] =      //���� �̸� ��Ʈ
{
   0,0,1,0,0,0,1,1,1,1,1,0,1,0,0,1,0,1,0,0,1,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,
   1,1,1,1,1,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,
   0,0,1,0,0,0,0,0,1,1,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,1,1,0,1,0,0,0,1,0,1,
   0,1,0,1,0,0,0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,
   1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,0,1,1,1,0,
   0,0,1,0,0,0,0,0,1,0,0,0,1,1,1,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,
   1,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,1,0,0,0,1,0,1,0,0,1,1,1,0
};

int chocomon[23][24] =    //���� �̸� ���� ���ں� ���� ��Ʈ
{

   0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,
   0,1,0,0,0,0,0,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,
   1,3,1,1,1,1,1,3,3,1,1,1,3,1,1,1,3,3,1,1,0,0,0,0,
   1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,0,0,0,
   0,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,1,0,0,0,
   0,0,1,0,1,0,1,0,1,0,0,1,3,3,3,3,3,3,3,3,1,0,0,0,
   0,0,1,0,1,0,1,0,1,0,0,1,3,3,3,3,3,3,3,3,1,0,0,0,
   0,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,1,0,0,0,
   1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,0,0,0,0,
   0,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,1,0,0,0,0,0,
   0,0,0,0,0,0,0,1,3,3,3,3,3,3,3,1,3,1,0,0,0,0,0,0,
   0,0,0,0,1,1,1,1,3,3,3,3,3,3,3,3,1,0,0,0,0,0,0,0,
   0,0,0,1,3,3,3,1,3,3,3,3,3,3,3,3,3,1,0,0,0,0,0,0,
   0,0,0,1,3,3,1,3,3,3,3,3,3,3,4,4,1,0,0,0,0,0,0,0,
   0,0,0,1,3,1,3,3,3,3,3,3,3,4,3,3,1,1,0,0,0,0,0,0,
   0,0,0,0,1,3,3,3,3,3,3,3,3,3,3,4,4,1,1,0,0,0,0,0,
   0,1,1,1,1,3,3,3,3,3,3,3,3,3,4,3,3,3,1,1,0,0,0,0,
   1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,1,1,0,0,0,
   1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3,4,1,1,0,0,
   1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,0,
   1,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

};
int chocobee[7][9] =      //���ں� ��Ʈ
{
   0,0,0,0,1,0,0,0,0,
   0,0,0,1,2,1,0,0,0,
   0,1,1,1,2,1,1,1,0,
   0,1,2,2,2,2,2,1,0,
   0,0,1,2,2,2,1,0,0,
   0,0,1,2,1,2,1,0,0,
   0,0,1,1,0,1,1,0,0
};
int space[7][29] =        //press��Ʈ
{
   1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,
   1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
   1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
   1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,
   1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
   1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
   1,0,0,0,0,0,1,0,0,0,1,0,1,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0
};

int gotoxy(int x, int y);							//��ǥ�̵�
int Cursor_set();									//Ŀ�� ����

void resize();										//ȭ�� ũ�� ����
void setColor(int foreground, int background);		//�ؽ�Ʈ, ��� �� ����
void Press_anyKey();								//¯�� ��Ʈ�� ��Ʈ, Ű ������ ���� �Լ�


void Print_background();							//���÷��̽� �� ����

void game_set_controll();							//���� �̸� ��Ʈ ���� �Լ�
void game_set_chocomon();							//���� �̸� ���� ���� ���� �Լ�

void game_set_choco_star(int x, int y);			    //���ں� ���� �Լ�
void game_set_start();								//�ΰ��� ����ȭ��

void game_set_character(HERO * a, HERO * b);	    //�ɸ��� ���� �Լ�


void get_player1_xy(int *x, int *y);				//�÷��̾� 1 ��ǥ

void get_player2_xy(int *x, int *y);				//�÷��̾� 2 ��ǥ

void make_chocobee();								//���ں� ����

void display_score(int * score, int *score2);		//������

void display_all_score(int * win1, int * total_game);//���� ���� n �� m ��

int x_c;											 //���ں� x ��ǥ ��												
int y_c;											 //���ں� y ��ǥ ��


int score = 0;										 //�÷��̾� 1 ���ں� ���� ��
int score2 = 0;										 //�÷��̾� 2 ���ں� ���� ��
									
int win1 = 0;

int total_game = 0;
int main()
{

	setColor(black, white);							 //�۾� ����, ��� ���

	resize();										 //�ܼ� ũ�� ����
	Cursor_set();
	PlaySound(NULL, 0, 0);
	PlaySound(TEXT("Intro.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);//���� ��� ���� (��Ʈ��)
	HERO Bosung = { 0,0 };							 //�÷��̾�1
	HERO Bosung2 = { 0,0 };							 //�÷��̾�2
	Sleep(200);
	
	Press_anyKey();									 //¯�� ��Ʈ ����
	Sleep(300);

	game_set_controll();							 //���� �̸� ���� (���ں� ��Ű��~)
	game_set_chocomon();							 //���ں� ���� ����
	game_set_choco_star(0,0);					     //���ں� ����
	game_set_choco_star(16,0);					     //
	game_set_choco_star(32,0);						 //
	game_set_choco_star(48,0);                       //
	game_set_choco_star(64,0);                       //
	Sleep(3000);
	
	system("cls");									 //ȭ���� �����~
	
	while (_kbhit()) _getch();
	game_set_start();								 //���� ���� ȭ��

	
	game_set_character(&Bosung, &Bosung2);			 //�÷��̾� ���� ���� ��, ���
	PlaySound(NULL, 0, 0);
	PlaySound(TEXT("DUNDUN.wav"),NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);//������� (�ΰ���)

	int x1 = 4, y1 = 6;								 //�÷��̾� 1 ó�� ��ġ
	int x2 = MAX_X - 6, y2 = 6;						 //�÷��̾� 2 ó�� ��ġ
							
	char ch;										 //getch ���忡 ��

	make_chocobee();								 //ȭ�鿡 ���ں� ������� ���

	Print_background();							     //�ΰ��� ��� ����

	while (1)
	{
		display_score(&score, &score2);				 //���� ǥ��
		get_player1_xy(&x1, &y1);					 //�÷��̾� 1 ��ġ����
		get_player2_xy(&x2, &y2);					 //�÷��̾� 2 ��ġ����
		display_all_score(&win1, &total_game);		 //��ä ���� ǥ��
		//------�÷��̾� 1 ��ġ ���� ------//
		if (GetAsyncKeyState('W') & 0x8000)			 //AND�������� ��Ȯ�� ���� ���� �ľ�
		{
			if (y1 >= 3)
				y1--;
			if (y1 == 2)							 //���� �����ϸ� �ݴ� �������� ���� �� �ִ�
				y1 = 37;

		}
		if (GetAsyncKeyState('S') & 0x8000)
		{
			if (y1 <= MAX_Y - 3)
				y1++;
			if (y1 == 38)							 //���� �����ϸ� �ݴ� �������� ���� �� �ִ�
				y1 = 3;
		}
		if (GetAsyncKeyState('A') & 0x8000)
		{
			if (x1 >= 0)
				x1 -= 2;

			if (x1 == 0)						     //���� �����ϸ� �ݴ� �������� ���� �� �ִ�
				x1 = MAX_X - 4;
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			if (x1 <= MAX_X - 4)
				x1 += 2;
			if (x1 == MAX_X - 2)				     //���� �����ϸ� �ݴ� �������� ���� �� �ִ�
				x1 = 2;
		}
		//------�÷��̾� 2 ��ġ ���� ------//
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (y2 >= 3)
				y2--;
			if (y2 == 2)
				y2 = 37;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			if (y2 <= MAX_Y - 3)
				y2++;
			if (y2 == 38)
				y2 = 3;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			if (x2 >= 0)
				x2 -= 2;

			if (x2 == 0)
				x2 = MAX_X - 4;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			if (x2 <= MAX_X - 4)
				x2 += 2;
			if (x2 == MAX_X - 2)
				x2 = 2;
		}

		gotoxy(x1, y1);							//�÷��̾� 1 ���� ��ǥ�� �̵�
		setColor(Bosung.color, white);			//�÷��̾� ����ü ������ �������� ����
		printf("%s", Bosung.shape);				//��� ���
		gotoxy(x2, y2);							//�÷��̾� 2 ���� ��ǥ�� �̵�
		setColor(Bosung2.color, white);			//���� ����
		printf("%s", Bosung2.shape);			//��� ���

		if ((x1 == x_c || x1 == x_c + 1 || x1 == x_c - 1) && (y1 == y_c || y1 == y_c - 2))//�÷��̾� 1�� ���ں� �Ծ����� �Ǻ�
		{
			make_chocobee();															  //���ں� ����
			score++;																	  //���� �ø�

			display_score(&score, &score2);												  //���� ǥ��
		}
		if ((x2 == x_c || x2 == x_c + 1 || x2 == x_c - 1) && (y2 == y_c || y2 == y_c - 2))//�÷��̾� 2�� ���ں� �Ծ����� �Ǻ�
		{
			make_chocobee();															  //���ں� ����
			score2++;																	  //���� �ø�

			display_score(&score, &score2);												  //���� ǥ��
		}


		if (score == 7)																	  //���� 7�� �Ǹ� ���� �Ǻ�
		{
			system("cls");																	

			//Sleep(100);
			while (1)
			{
				PlaySound(NULL, 0, 0);
				PlaySound(TEXT("winwin.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); //���� ���� �뷡 ���
				game_set_choco_star(-14 - 36, (-8));									  //���ں� ����~~7��
				game_set_choco_star(-14 - 18, (-8));									  //
				game_set_choco_star(-14, (-8));											  //
				game_set_choco_star(4, (-8));											  //
				game_set_choco_star(22, (-8));											  //
				game_set_choco_star(22 + 18, (-8));										  //
				game_set_choco_star(22 + 36, (-8));										  //
				gotoxy(MAX_X / 2 - 8, MAX_Y / 2 + 4);								      //���� ����
				setColor(black, white);
				printf("�÷��̾� 2�� ����");
				Sleep(800);
				gotoxy(MAX_X / 2 - 10, MAX_Y / 2 + 7);
				printf("�ٽ��Ϸ��� RŰ�� ������");
				while (1)																  //R or rŰ ������ �ٽý���
				{
					if (_kbhit() == 1)
					{
						ch = _getch();
						if (ch == 'r' || ch == 'R')
						{
							score = 0;													  //���� �ʱ�ȭ
							score2 = 0;													  //
							x1 = 4, y1 = 6;												  //��ǥ �ʱ�ȭ
							x2 = MAX_X - 6, y2 = 6;										  //
							win1++;														  //���� ���� ���� ���� �� �߰�
							total_game++;												  //

							break;

						}
					}
				}

				
				while (_kbhit()) _getch();
				system("cls");
				main();																	  //R Ȥ�� rŰ ������ �ݺ��� ����, �����Լ� ȣ��
			}
		}

		if (score2 == 7)																  //�÷��̾� 2�� �ش��ϸ� �� �κа� �����ϴ�
		{
			system("cls");

			while (1)
			{
				PlaySound(NULL, 0, 0);
				PlaySound(TEXT("winwin.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				game_set_choco_star(-14-36, (-8));
				game_set_choco_star(-14-18, (-8));
				game_set_choco_star(-14, (-8));
				game_set_choco_star(4, (-8));
				game_set_choco_star(22, (-8));
				game_set_choco_star(22+18, (-8));
				game_set_choco_star(22+36, (-8));
				gotoxy(MAX_X / 2 - 8, MAX_Y / 2 + 4);
				setColor(black, white);
				printf("�÷��̾� 1�� ����");
				Sleep(800);
				gotoxy(MAX_X / 2 - 10, MAX_Y / 2 + 7);
				printf("�ٽ��Ϸ��� RŰ�� ������");
				while (1)
				{
					if (_kbhit() == 1)
					{
						ch = _getch();
						if (ch == 'r' || ch == 'R')
						{
							score = 0;
							score2 = 0;
							x1 = 4, y1 = 6;
							x2 = MAX_X - 6, y2 = 6;
							gotoxy(MAX_X / 2 - 5, 1);
							
							total_game++;
							
							break;

						}
					}
				}
			

				while (_kbhit()) _getch();
				system("cls");
				main();
			}

		}
		Sleep(50);
	}



}




//��ǥ�̵� -�Է¹��� ���� ���� �̵�
int gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	return 0;
}

//Ŀ�� ���� -������ 1, �Ⱥ���
int Cursor_set()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	return 0;
}

//�ܼ� ������ ����
void resize()
{
	system("mode con cols=180 lines=40");
}

//���� ���� �Լ�, ������ ������ -> ���� 0 ~ 15, �ش� ���� ������ ����
void setColor(int foreground, int background)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int code = foreground + background * 16;				
	SetConsoleTextAttribute(consoleHandle, code); //�Է��� ����, ������ �°� ����

}

//¯�� ��Ʈ�� ��Ʈ
void Press_anyKey()
{
	int i = 0;									 //�迭 �̵� ���� ����
	int j = 0;									 //�迭 �̵� ���� ����
	int cnt = 0;
	char ch;

	gotoxy(MAX_X / 2 - 18, MAX_Y / 2 - 16);      //��ǥ �̵�
	while (1)
	{
		if (_kbhit())
		{
			

			system("cls");
			break;
		}


		for (i = 0; i < 17; i++)
		{
			for (j = 0; j < 24; j++)
			{
				if (array_intro[i][j] == 0)      //�迭���� 0�̸� ��ĭ

					printf("  ");

				if (array_intro[i][j] == 1)      //�迭���� 1�̸� ��ĥ

					setColor(white, black),
					printf("  "),
					setColor(white, white);

			}
			Sleep(80);							 //1���� ������ 0.08�� ������
			cnt++;
			gotoxy(MAX_X / 2 - 18, MAX_Y / 2 - 16 + cnt);//1�� ��������

		}
		cnt += 5;

		gotoxy(MAX_X / 2 - 22, MAX_Y / 2 - 16 + cnt);
		for (i = 0; i < 7; i++)
		{
			for (j = 0; j < 29; j++)
			{
				if (space[i][j] == 0)
					printf("  ");

				if (space[i][j] == 1)			 //�迭���� 1�̸� ��ĥ

					setColor(white, black),
					printf("  "),
					setColor(white, white);
			}
			Sleep(80);
			//1���� ������ 0.08�� ������
			cnt++;
			gotoxy(MAX_X / 2 - 22, MAX_Y / 2 - 16 + cnt);//1�� ��������

		}




		cnt = 0;								  //for���� ������ ȭ���� �����.


		Sleep(500);
		system("cls");
		gotoxy(MAX_X / 2 - 18, MAX_Y / 2 - 16);   //��ǥ ������������ �̵�
		Sleep(100);



	}

}


//�ΰ��� �ÿ� ���ȭ���� ���� �Լ�
void Print_background()
{
	int y = 0;									  //��ǥ�̵� ���� ����
	int x = 0;									  //
	gotoxy(0, 4);
	for (y = 4; y <= MAX_Y; y++)				  //�ݺ����� ������ ���� �׸���
	{
		gotoxy(0, y);
		for (x = 0; x < MAX_X / 2; x++)
		{
			if (y == 4 || y == MAX_Y)
			{
				setColor(white, darkgray);
				printf("  ");
				setColor(white, white);
			}
			if (x == 2)
			{
				setColor(white, darkgray);
				printf("  ");
				setColor(white, white);
			}
			if (x == (MAX_X - 2) / 2)
			{
				gotoxy(x * 2, y);
				setColor(white, darkgray);
				printf("  ");
				setColor(white, white);
			}


		}

	}




}


//���� �̸� ���� �Լ�
void game_set_controll() 
{
	int i = 0;								//�迭 �̵� ���� ���� 
	int j = 0;								//
	gotoxy(MAX_X / 2 - 12, MAX_Y / 2 - 10); //���� �̸� ǥ���� ��ǥ�� �̵�
	setColor(black, white);
	int cnt = 0;							//�� �� �׸��� ��ĭ�� �������� ���� �ʿ��� ����
	for (i = 0; i < 7; i++)					//�׸���
	{
		for (j = 0; j < 38; j++)
		{
			if (chocobi[i][j] == 0)   printf("  ");
			if (chocobi[i][j] == 1)setColor(white, green), printf("  "), setColor(white, white);
		}
		cnt++;
		Sleep(80);

		gotoxy(MAX_X / 2 - 12, MAX_Y / 2 - 10 + cnt);

	}

}

//���� �̸� ���� ���� ���� �Լ�
void game_set_chocomon() 
{
	int i = 0;								//���� �̵� ���� ����
	int j = 0;								//
	gotoxy(MAX_X / 2 - 60, MAX_Y / 2 - 10);	//�׸� ��ǥ�� �̵�
	setColor(black, white);
	int cnt = 0;
	for (i = 0; i < 23; i++)				//�־��� �迭�� ���� ���� ������ �����Ͽ� �׸��� �׸���
	{
		for (j = 0; j < 24; j++)
		{
			if (chocomon[i][j] == 0)   
				printf("  ");

			if (chocomon[i][j] == 1)
				setColor(white, black), 
				printf("  "), 
				setColor(white, white);

			if (chocomon[i][j] == 3)
				setColor(white, lightred),
				printf("  "), 
				setColor(white, white);

			if (chocomon[i][j] == 4)
				setColor(white, red), 
				printf("  "), 
				setColor(white, white);
		}
		cnt++;
		Sleep(80);

		gotoxy(MAX_X / 2 - 60, MAX_Y / 2 - 10 + cnt);
	}
}
//���� �̸� �Ʒ��� ���ں� ���� �Լ�
void game_set_choco_star(int x, int y) 
{
	int i = 0;								//���� �̵� ���� ����
	int j = 0;								//

	gotoxy(MAX_X / 2 - 12 + x, MAX_Y / 2 + 3 + y);//�־��� ���� ���� ��ǥ �̵� �����ϰ� �� (���������� ���� ����)
	setColor(black, white);					
	int cnt = 0;
	for (i = 0; i < 7; i++)					//�־��� �迭�� ���� ���� ������ �����Ͽ� �׸��� �׸���
	{
		for (j = 0; j < 9; j++)
		{
			if (chocobee[i][j] == 0)
				printf("  ");

			if (chocobee[i][j] == 1)
				setColor(white, black),
				printf("  "), 
				setColor(white, white);

			if (chocobee[i][j] == 2)
				setColor(brown, brown), 
				printf("  "), 
				setColor(white, white);
		}
		cnt++;
		Sleep(80);

		gotoxy(MAX_X / 2 - 12 + x, MAX_Y / 2 + 3 + +y + cnt);

	}

}
//�ΰ��ӿ��� ���ӿ� ���� ������ ����
void game_set_start()
{
	
	while (1)								//���ӿ� ���� ������ ������ ���ְ�, Ű���带 ������ ���� ȭ������ �Ѿ��
	{

		gotoxy(MAX_X / 2 - 10, 15 - GET_H);
		setColor(black, white);

		printf("�����ں� ��Ű�� ���ӡ�");

		gotoxy(MAX_X / 2 - 12, 19 - GET_H);
		printf("������ �غ��鼭 ���� ����");

		gotoxy(MAX_X / 2 - 11, 23 - GET_H);
		printf("WASD, ȭ��ǥ Ű�� ��������");

		gotoxy(MAX_X / 2 - 14, 25 - GET_H);
		printf("�ƹ�Ű�� ������ ������ ���۵���");

		if (_kbhit())						//Ű���� ������ ��������
		{
			system("cls");
			break;
		}
	}

}
//����ڷκ��� �Է¹��� ������ ���� ĳ���� �����ϴ� �Լ�
void game_set_character(HERO *a, HERO *b)
{
	gotoxy(MAX_X / 2 - 10, 15 - GET_H);		//ĳ���� ���� ���
	setColor(black, white);
	printf("ĳ���͸� ������");

	gotoxy(MAX_X / 2 - 15, 19 - GET_H);

	setColor(black, white);
	printf("1.");

	setColor(red, white);
	printf("��");

	setColor(black, white);
	printf("   [¯��] ¯���� ���ִ�");

	gotoxy(MAX_X / 2 - 15, 23 - GET_H);

	setColor(black, white);
	printf("2.");

	setColor(brown, white);
	printf("��");

	setColor(black, white);
	printf("   [�ͱ�] �ͱ��� �ͱ���");

	gotoxy(MAX_X / 2 - 15, 27 - GET_H);

	setColor(black, white);
	printf("3.");

	setColor(green, white);
	printf("��");

	setColor(black, white);
	printf("   [����] ���̴� ���δ�");

	gotoxy(MAX_X / 2 - 25, 31 - GET_H);
	printf("[ ù��° �÷��̾� ����Ű�� ������ ĳ���Ͱ� ������� ]");

	char ch = 0;
	
	while (1)												//ù��° �÷��̾ ���� ���� ���� ���� �����Ѵ�
	{

		if (_kbhit() == 1)
		{
			ch = _getch();
			if (ch == '1')
			{
				a->color = red; a->shape = "��"; break;		//���� ���� 1�϶�
			}
			if (ch == '2')
			{
				a->color = brown; a->shape = "��"; break;   //���� ���� 2�϶�
			}
			if (ch == '3')
			{
				a->color = green; a->shape = "��"; break;	//���� ���� 3�϶�
			}


		}
		else;

	}
	Sleep(100);
	while (1)												//ù��° �÷��̾ ���� ĳ���͸� ǥ���Ѵ�, ������ �ι�° �÷��̾�� �ѱ�
	{
		gotoxy(MAX_X / 2 - 25, 31 - GET_H);
		printf("[ �ι�° �÷��̾� ����Ű�� ������ ĳ���Ͱ� ������� ]");
		if (ch == '1')
		{

			gotoxy(MAX_X / 2 - 15, 19 - GET_H);
			printf("1.");
			setColor(red, white);
			printf("��");
			setColor(black, white);

			printf("  - ù��° �÷��̾�    ");
			break;
		}
		if (ch == '2')
		{
			gotoxy(MAX_X / 2 - 15, 23 - GET_H);
			printf("2.");
			setColor(brown, white);
			printf("��");
			setColor(black, white);
			printf("  - ù��° �÷��̾�    ");
			break;
		}
		if (ch == '3')
		{
			gotoxy(MAX_X / 2 - 15, 27 - GET_H);
			printf("3.");
			setColor(green, white);
			printf("��");
			setColor(black, white);
			printf("  - ù��° �÷��̾�    ");
			break;

		}


	}
	char tmp = 0;

	while (1)											//�ι�° �÷��̾ ���� ĳ���͸� �����Ѵ�.
	{
		if (_kbhit() == 1)			
		{
			tmp = _getch();
			if (tmp != ch)								//ù��° �÷��̾�� �� ���ڰ� �ٸ� ��쿡�� ������ �ȴ�
			{
				if (tmp == '1')
				{
					b->color = red;
					b->shape = "��";
					gotoxy(MAX_X / 2 - 15, 19 - GET_H);
					printf("1.");
					setColor(red, white);
					printf("��");
					setColor(black, white);

					printf("  - �ι�° �÷��̾�        ");
					break;
				}
				if (tmp == '2')
				{
					b->color = brown;
					b->shape = "��";
					gotoxy(MAX_X / 2 - 15, 23 - GET_H);
					printf("2.");
					setColor(brown, white);
					printf("��");
					setColor(black, white);
					printf("  - �ι�° �÷��̾�          ");
					break;
				}
				if (tmp == '3')
				{
					b->color = green;
					b->shape = "��";
					gotoxy(MAX_X / 2 - 15, 27 - GET_H);
					printf("3.");
					setColor(green, white);
					printf("��");
					setColor(black, white);
					printf("  - �ι�° �÷��̾�           ");
					break;
				}
			}

		}
		else;
	}
	Sleep(500);
	system("cls");
	gotoxy(MAX_X / 2, MAX_Y / 2);

}

//�÷��̾� 1�� ��ġ������ ������ ǥ���Ѵ�
void get_player1_xy(int *x, int*y)						
{
	gotoxy(5, 1);
	setColor(black, white);
	printf("Player_XY = %03d, %03d", *x, *y);
}

//�÷��̾� 2�� ��ġ������ ������ ǥ���Ѵ�
void get_player2_xy(int *x, int*y)
{
	gotoxy(MAX_X - 25, 1);
	setColor(black, white);
	printf("Player_XY = %03d, %03d", *x, *y);
}
//���ں� �׸��� �Լ��̴�
void make_chocobee()
{

	x_c = rand() % (MAX_X - 3) + 2;		//�����Լ��� �̿��Ͽ� ���ں��� ��ǥ�� �����Ѵ�
	y_c = rand() % (MAX_Y - 4) + 3;		//
	gotoxy(x_c, y_c);
	setColor(cyan, white);
	printf("��");

}
//�÷��̾� 1�� �÷��̾� 2�� ������ ǥ���Ѵ�
void display_score(int * score, int * score2)
{
	gotoxy(MAX_X / 2 - 10, 1);
	setColor(black, white);

	printf("SCORE  %d : %d", *score, *score2);

}

//�÷��̾� 1�� �÷��̾� 2�� ���� ������ ǥ���ϴ� �Լ��̴�
void display_all_score(int * win1, int * total_game)
{
	gotoxy(32, 1);
	setColor(black, white);

	printf(" %d�� %d��", *win1, *total_game - * win1);

	gotoxy(MAX_X - 42, 1);

	printf(" %d�� %d��", *total_game - *win1, *win1);


}