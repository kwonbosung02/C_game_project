#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#include<Windows.h>               //윈도우 제공 기능 사용 위해
#include<conio.h>                 //getch,kbhit 사용 위해
#include<MMSystem.h>              //음악 재생 위해서 추가
#pragma comment(lib, "winmm.lib" )//음악 재생 위해서 추가

#define MAX_X 180                 //도트 기준점 화면 크기
#define MAX_Y 40                  //도트 기준점 화면 크기

#define LEFT   75                 //Player2 이동 키보드 값

#define RIGHT  77                 //

#define UP     72                 //

#define DOWN   80                 //

#define GET_H  5				  //초코비 모양 도트 위치 조정

#ifndef __COLOR_LIST_			  //색상 리스트, 열거형 정의
#define __COLOR_LIST_             //콘솔 텍스트 색상
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

typedef struct _HERO {			//플레이어 정보 구조체
	int *color;					//플레이어 색상
	char *shape;				//플레이어 모양

}HERO;



int array_intro[17][24] =		//게임 시작시 나타나는 짱구 얼굴 인트로
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
int chocobi[7][38] =      //게임 이름 도트
{
   0,0,1,0,0,0,1,1,1,1,1,0,1,0,0,1,0,1,0,0,1,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,
   1,1,1,1,1,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,
   0,0,1,0,0,0,0,0,1,1,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,1,1,0,1,0,0,0,1,0,1,
   0,1,0,1,0,0,0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,
   1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,0,1,1,1,0,
   0,0,1,0,0,0,0,0,1,0,0,0,1,1,1,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,
   1,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,1,0,0,0,1,0,1,0,0,1,1,1,0
};

int chocomon[23][24] =    //게임 이름 옆의 초코비 공룡 도트
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
int chocobee[7][9] =      //초코비 도트
{
   0,0,0,0,1,0,0,0,0,
   0,0,0,1,2,1,0,0,0,
   0,1,1,1,2,1,1,1,0,
   0,1,2,2,2,2,2,1,0,
   0,0,1,2,2,2,1,0,0,
   0,0,1,2,1,2,1,0,0,
   0,0,1,1,0,1,1,0,0
};
int space[7][29] =        //press도트
{
   1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,
   1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
   1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
   1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,
   1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
   1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
   1,0,0,0,0,0,1,0,0,0,1,0,1,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0
};

int gotoxy(int x, int y);							//좌표이동
int Cursor_set();									//커서 설정

void resize();										//화면 크기 조정
void setColor(int foreground, int background);		//텍스트, 배경 색 변경
void Press_anyKey();								//짱구 인트로 도트, 키 누르면 시작 함수


void Print_background();							//인플레이시 벽 생성

void game_set_controll();							//게임 이름 도트 띄우는 함수
void game_set_chocomon();							//게임 이름 옆의 공룡 띄우는 함수

void game_set_choco_star(int x, int y);			    //초코비 띄우는 함수
void game_set_start();								//인게임 시작화면

void game_set_character(HERO * a, HERO * b);	    //케릭터 선택 함수


void get_player1_xy(int *x, int *y);				//플레이어 1 좌표

void get_player2_xy(int *x, int *y);				//플레이어 2 좌표

void make_chocobee();								//초코비 생성

void display_score(int * score, int *score2);		//점수판

void display_all_score(int * win1, int * total_game);//전적 생성 n 승 m 패

int x_c;											 //초코비 x 좌표 값												
int y_c;											 //초코비 y 좌표 값


int score = 0;										 //플레이어 1 초코비 먹은 수
int score2 = 0;										 //플레이어 2 초코비 먹은 수
									
int win1 = 0;

int total_game = 0;
int main()
{

	setColor(black, white);							 //글씨 검정, 배경 흰색

	resize();										 //콘솔 크기 설정
	Cursor_set();
	PlaySound(NULL, 0, 0);
	PlaySound(TEXT("Intro.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);//음악 재생 시작 (인트로)
	HERO Bosung = { 0,0 };							 //플레이어1
	HERO Bosung2 = { 0,0 };							 //플레이어2
	Sleep(200);
	
	Press_anyKey();									 //짱구 도트 띄운다
	Sleep(300);

	game_set_controll();							 //게임 이름 띄우기 (초코비 지키깅~)
	game_set_chocomon();							 //초코비 공룡 띄우기
	game_set_choco_star(0,0);					     //초코비 띄우기
	game_set_choco_star(16,0);					     //
	game_set_choco_star(32,0);						 //
	game_set_choco_star(48,0);                       //
	game_set_choco_star(64,0);                       //
	Sleep(3000);
	
	system("cls");									 //화면을 지운다~
	
	while (_kbhit()) _getch();
	game_set_start();								 //게임 시작 화면

	
	game_set_character(&Bosung, &Bosung2);			 //플레이어 정보 설정 색, 모양
	PlaySound(NULL, 0, 0);
	PlaySound(TEXT("DUNDUN.wav"),NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);//음악재생 (인게임)

	int x1 = 4, y1 = 6;								 //플레이어 1 처음 위치
	int x2 = MAX_X - 6, y2 = 6;						 //플레이어 2 처음 위치
							
	char ch;										 //getch 저장에 씀

	make_chocobee();								 //화면에 초코비 별모양을 띄움

	Print_background();							     //인게임 배경 생성

	while (1)
	{
		display_score(&score, &score2);				 //점수 표시
		get_player1_xy(&x1, &y1);					 //플레이어 1 위치정보
		get_player2_xy(&x2, &y2);					 //플레이어 2 위치정보
		display_all_score(&win1, &total_game);		 //전채 승패 표시
		//------플레이어 1 위치 변경 ------//
		if (GetAsyncKeyState('W') & 0x8000)			 //AND연산으로 정확한 눌림 상태 파악
		{
			if (y1 >= 3)
				y1--;
			if (y1 == 2)							 //벽에 도착하면 반대 방향으로 나올 수 있다
				y1 = 37;

		}
		if (GetAsyncKeyState('S') & 0x8000)
		{
			if (y1 <= MAX_Y - 3)
				y1++;
			if (y1 == 38)							 //벽에 도착하면 반대 방향으로 나올 수 있다
				y1 = 3;
		}
		if (GetAsyncKeyState('A') & 0x8000)
		{
			if (x1 >= 0)
				x1 -= 2;

			if (x1 == 0)						     //벽에 도착하면 반대 방향으로 나올 수 있다
				x1 = MAX_X - 4;
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			if (x1 <= MAX_X - 4)
				x1 += 2;
			if (x1 == MAX_X - 2)				     //벽에 도착하면 반대 방향으로 나올 수 있다
				x1 = 2;
		}
		//------플레이어 2 위치 변경 ------//
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

		gotoxy(x1, y1);							//플레이어 1 변경 좌표로 이동
		setColor(Bosung.color, white);			//플레이어 구조체 정보의 색상으로 변굥
		printf("%s", Bosung.shape);				//모양 출력
		gotoxy(x2, y2);							//플레이어 2 변경 좌표로 이동
		setColor(Bosung2.color, white);			//색상 설정
		printf("%s", Bosung2.shape);			//모양 출력

		if ((x1 == x_c || x1 == x_c + 1 || x1 == x_c - 1) && (y1 == y_c || y1 == y_c - 2))//플레이어 1이 초코비를 먹엇는지 판별
		{
			make_chocobee();															  //초코비 만듬
			score++;																	  //점수 올림

			display_score(&score, &score2);												  //점수 표시
		}
		if ((x2 == x_c || x2 == x_c + 1 || x2 == x_c - 1) && (y2 == y_c || y2 == y_c - 2))//플레이어 2가 초코비를 먹었는지 판별
		{
			make_chocobee();															  //초코비 만듬
			score2++;																	  //점수 올림

			display_score(&score, &score2);												  //점수 표시
		}


		if (score == 7)																	  //점수 7점 되면 승자 판별
		{
			system("cls");																	

			//Sleep(100);
			while (1)
			{
				PlaySound(NULL, 0, 0);
				PlaySound(TEXT("winwin.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); //게임 엔딩 노래 재생
				game_set_choco_star(-14 - 36, (-8));									  //초코비 띄우기~~7개
				game_set_choco_star(-14 - 18, (-8));									  //
				game_set_choco_star(-14, (-8));											  //
				game_set_choco_star(4, (-8));											  //
				game_set_choco_star(22, (-8));											  //
				game_set_choco_star(22 + 18, (-8));										  //
				game_set_choco_star(22 + 36, (-8));										  //
				gotoxy(MAX_X / 2 - 8, MAX_Y / 2 + 4);								      //글자 띄우기
				setColor(black, white);
				printf("플레이어 2가 졌다");
				Sleep(800);
				gotoxy(MAX_X / 2 - 10, MAX_Y / 2 + 7);
				printf("다시하려면 R키를 눌러라");
				while (1)																  //R or r키 누르면 다시시작
				{
					if (_kbhit() == 1)
					{
						ch = _getch();
						if (ch == 'r' || ch == 'R')
						{
							score = 0;													  //점수 초기화
							score2 = 0;													  //
							x1 = 4, y1 = 6;												  //좌표 초기화
							x2 = MAX_X - 6, y2 = 6;										  //
							win1++;														  //최종 승패 관련 변수 값 추가
							total_game++;												  //

							break;

						}
					}
				}

				
				while (_kbhit()) _getch();
				system("cls");
				main();																	  //R 혹은 r키 눌리면 반복문 종료, 메인함수 호출
			}
		}

		if (score2 == 7)																  //플레이어 2에 해당하며 윗 부분과 동일하다
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
				printf("플레이어 1이 졌다");
				Sleep(800);
				gotoxy(MAX_X / 2 - 10, MAX_Y / 2 + 7);
				printf("다시하려면 R키를 눌러라");
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




//좌표이동 -입력받은 값에 따라 이동
int gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	return 0;
}

//커서 설정 -사이즈 1, 안보임
int Cursor_set()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	return 0;
}

//콘솔 사이즈 조정
void resize()
{
	system("mode con cols=180 lines=40");
}

//색상 조정 함수, 열거형 데이터 -> 정수 0 ~ 15, 해당 글자 색으로 변경
void setColor(int foreground, int background)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int code = foreground + background * 16;				
	SetConsoleTextAttribute(consoleHandle, code); //입력한 글자, 배경색상에 맞게 변경

}

//짱구 인트로 도트
void Press_anyKey()
{
	int i = 0;									 //배열 이동 위한 변수
	int j = 0;									 //배열 이동 위한 변수
	int cnt = 0;
	char ch;

	gotoxy(MAX_X / 2 - 18, MAX_Y / 2 - 16);      //좌표 이동
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
				if (array_intro[i][j] == 0)      //배열값이 0이면 빈칸

					printf("  ");

				if (array_intro[i][j] == 1)      //배열값이 1이면 색칠

					setColor(white, black),
					printf("  "),
					setColor(white, white);

			}
			Sleep(80);							 //1줄이 끝나면 0.08초 딜레이
			cnt++;
			gotoxy(MAX_X / 2 - 18, MAX_Y / 2 - 16 + cnt);//1줄 내려간다

		}
		cnt += 5;

		gotoxy(MAX_X / 2 - 22, MAX_Y / 2 - 16 + cnt);
		for (i = 0; i < 7; i++)
		{
			for (j = 0; j < 29; j++)
			{
				if (space[i][j] == 0)
					printf("  ");

				if (space[i][j] == 1)			 //배열값이 1이면 색칠

					setColor(white, black),
					printf("  "),
					setColor(white, white);
			}
			Sleep(80);
			//1줄이 끝나면 0.08초 딜레이
			cnt++;
			gotoxy(MAX_X / 2 - 22, MAX_Y / 2 - 16 + cnt);//1줄 내려간다

		}




		cnt = 0;								  //for문이 끝나면 화면을 지운다.


		Sleep(500);
		system("cls");
		gotoxy(MAX_X / 2 - 18, MAX_Y / 2 - 16);   //좌표 시작지점으로 이동
		Sleep(100);



	}

}


//인게임 시에 배경화면을 띄우는 함수
void Print_background()
{
	int y = 0;									  //좌표이동 위한 변수
	int x = 0;									  //
	gotoxy(0, 4);
	for (y = 4; y <= MAX_Y; y++)				  //반복문을 돌리어 맵을 그린다
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


//게임 이름 띄우는 함수
void game_set_controll() 
{
	int i = 0;								//배열 이동 위한 변수 
	int j = 0;								//
	gotoxy(MAX_X / 2 - 12, MAX_Y / 2 - 10); //게임 이름 표시할 좌표로 이동
	setColor(black, white);
	int cnt = 0;							//한 줄 그리고 한칸씩 내려가기 위해 필요한 변수
	for (i = 0; i < 7; i++)					//그린다
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

//게임 이름 옆의 공룡 띄우는 함수
void game_set_chocomon() 
{
	int i = 0;								//베열 이동 위한 변수
	int j = 0;								//
	gotoxy(MAX_X / 2 - 60, MAX_Y / 2 - 10);	//그릴 좌표로 이동
	setColor(black, white);
	int cnt = 0;
	for (i = 0; i < 23; i++)				//주어진 배열의 값에 따라 색상을 설정하여 그림을 그린다
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
//게임 이름 아래의 초코비 띄우는 함수
void game_set_choco_star(int x, int y) 
{
	int i = 0;								//베열 이동 위한 변수
	int j = 0;								//

	gotoxy(MAX_X / 2 - 12 + x, MAX_Y / 2 + 3 + y);//주어진 값에 따라 좌표 이동 가능하게 함 (엔딩에서도 쓰기 때문)
	setColor(black, white);					
	int cnt = 0;
	for (i = 0; i < 7; i++)					//주어진 배열의 값에 따라 색상을 설정하여 그림을 그린다
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
//인게임에서 게임에 관한 설명을 해줌
void game_set_start()
{
	
	while (1)								//게임에 대해 간단한 설명을 해주고, 키보드를 누르면 다음 화면으로 넘어간다
	{

		gotoxy(MAX_X / 2 - 10, 15 - GET_H);
		setColor(black, white);

		printf("★초코비 지키기 게임★");

		gotoxy(MAX_X / 2 - 12, 19 - GET_H);
		printf("게임은 해보면서 배우는 거유");

		gotoxy(MAX_X / 2 - 11, 23 - GET_H);
		printf("WASD, 화살표 키로 움직여유");

		gotoxy(MAX_X / 2 - 14, 25 - GET_H);
		printf("아무키나 누르면 게임이 시작되유");

		if (_kbhit())						//키보드 눌리면 빠져나옴
		{
			system("cls");
			break;
		}
	}

}
//사용자로부터 입력받은 정보에 따라 캐릭터 설정하는 함수
void game_set_character(HERO *a, HERO *b)
{
	gotoxy(MAX_X / 2 - 10, 15 - GET_H);		//캐릭터 정보 출력
	setColor(black, white);
	printf("캐릭터를 고르세염");

	gotoxy(MAX_X / 2 - 15, 19 - GET_H);

	setColor(black, white);
	printf("1.");

	setColor(red, white);
	printf("■");

	setColor(black, white);
	printf("   [짱구] 짱구는 멋있다");

	gotoxy(MAX_X / 2 - 15, 23 - GET_H);

	setColor(black, white);
	printf("2.");

	setColor(brown, white);
	printf("●");

	setColor(black, white);
	printf("   [맹구] 맹구는 맹구다");

	gotoxy(MAX_X / 2 - 15, 27 - GET_H);

	setColor(black, white);
	printf("3.");

	setColor(green, white);
	printf("◆");

	setColor(black, white);
	printf("   [훈이] 훈이는 별로다");

	gotoxy(MAX_X / 2 - 25, 31 - GET_H);
	printf("[ 첫번째 플레이어 숫자키를 누르면 캐릭터가 골라져유 ]");

	char ch = 0;
	
	while (1)												//첫번째 플레이어가 누른 값에 따라 값을 변경한다
	{

		if (_kbhit() == 1)
		{
			ch = _getch();
			if (ch == '1')
			{
				a->color = red; a->shape = "■"; break;		//누른 값이 1일때
			}
			if (ch == '2')
			{
				a->color = brown; a->shape = "●"; break;   //누른 값이 2일때
			}
			if (ch == '3')
			{
				a->color = green; a->shape = "◆"; break;	//누른 값이 3일때
			}


		}
		else;

	}
	Sleep(100);
	while (1)												//첫번째 플레이어가 누른 캐릭터를 표시한다, 선택을 두번째 플레이어에게 넘김
	{
		gotoxy(MAX_X / 2 - 25, 31 - GET_H);
		printf("[ 두번째 플레이어 숫자키를 누르면 캐릭터가 골라져유 ]");
		if (ch == '1')
		{

			gotoxy(MAX_X / 2 - 15, 19 - GET_H);
			printf("1.");
			setColor(red, white);
			printf("■");
			setColor(black, white);

			printf("  - 첫번째 플레이어    ");
			break;
		}
		if (ch == '2')
		{
			gotoxy(MAX_X / 2 - 15, 23 - GET_H);
			printf("2.");
			setColor(brown, white);
			printf("●");
			setColor(black, white);
			printf("  - 첫번째 플레이어    ");
			break;
		}
		if (ch == '3')
		{
			gotoxy(MAX_X / 2 - 15, 27 - GET_H);
			printf("3.");
			setColor(green, white);
			printf("◆");
			setColor(black, white);
			printf("  - 첫번째 플레이어    ");
			break;

		}


	}
	char tmp = 0;

	while (1)											//두번째 플레이어가 게임 캐릭터를 선택한다.
	{
		if (_kbhit() == 1)			
		{
			tmp = _getch();
			if (tmp != ch)								//첫번째 플레이어와 고른 숫자가 다를 경우에만 선택이 된다
			{
				if (tmp == '1')
				{
					b->color = red;
					b->shape = "■";
					gotoxy(MAX_X / 2 - 15, 19 - GET_H);
					printf("1.");
					setColor(red, white);
					printf("■");
					setColor(black, white);

					printf("  - 두번째 플레이어        ");
					break;
				}
				if (tmp == '2')
				{
					b->color = brown;
					b->shape = "●";
					gotoxy(MAX_X / 2 - 15, 23 - GET_H);
					printf("2.");
					setColor(brown, white);
					printf("●");
					setColor(black, white);
					printf("  - 두번째 플레이어          ");
					break;
				}
				if (tmp == '3')
				{
					b->color = green;
					b->shape = "◆";
					gotoxy(MAX_X / 2 - 15, 27 - GET_H);
					printf("3.");
					setColor(green, white);
					printf("◆");
					setColor(black, white);
					printf("  - 두번째 플레이어           ");
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

//플레이어 1의 위치정보를 가져와 표시한다
void get_player1_xy(int *x, int*y)						
{
	gotoxy(5, 1);
	setColor(black, white);
	printf("Player_XY = %03d, %03d", *x, *y);
}

//플레이어 2의 위치정보를 가져와 표시한다
void get_player2_xy(int *x, int*y)
{
	gotoxy(MAX_X - 25, 1);
	setColor(black, white);
	printf("Player_XY = %03d, %03d", *x, *y);
}
//초코비를 그리는 함수이다
void make_chocobee()
{

	x_c = rand() % (MAX_X - 3) + 2;		//랜덤함수를 이용하여 초코비의 좌표를 지정한다
	y_c = rand() % (MAX_Y - 4) + 3;		//
	gotoxy(x_c, y_c);
	setColor(cyan, white);
	printf("★");

}
//플레이어 1과 플레이어 2의 점수를 표시한다
void display_score(int * score, int * score2)
{
	gotoxy(MAX_X / 2 - 10, 1);
	setColor(black, white);

	printf("SCORE  %d : %d", *score, *score2);

}

//플레이어 1과 플레이어 2의 승패 정보를 표시하는 함수이다
void display_all_score(int * win1, int * total_game)
{
	gotoxy(32, 1);
	setColor(black, white);

	printf(" %d승 %d패", *win1, *total_game - * win1);

	gotoxy(MAX_X - 42, 1);

	printf(" %d승 %d패", *total_game - *win1, *win1);


}