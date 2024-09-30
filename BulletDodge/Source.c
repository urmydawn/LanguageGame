#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define WIDTH 20
#define HEIGHT 10

typedef struct // 총알을 표현하는 구조체
{
	int x;
	int y;

	int active;
}Bullet;

typedef struct // 플레이어를 표현하는 구조체
{
	int x;
}Player;

Bullet bullet[WIDTH];
Player player;

void gotoxy(int x, int y) // 커서를 이동시키는 함수
{
	COORD pos = { 2 * x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int PressKey(int key) // 키가 눌려졌는지 확인하는 함수
{
	return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

void Reset() // 게임을 초기화 시키는 함수
{
	int i;

	for (i = 0; i < WIDTH; i++) // 모든 총알을 0으로 초기화
		bullet[i].active = 0;

	player.x = WIDTH / 2; // 플레이어 위치를 가로 / 2 (중앙)로 설정
}

void CreateBullet() // 총알을 생성시키는 함수
{
	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if (!bullet[i].active)
		{
			bullet[i].x = rand() % WIDTH; // 랜덤으로 총알이 떨어질 좌표 생성
			bullet[i].y = HEIGHT - 1; // 총알이 떨어질 위치 10 - 1

			bullet[i].active = 1;

			return; // 하나만 생성하고 탈출
		}
	}
}

void MoveBullet() // 총알을 아래로 이동시키는 함수
{
	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if (bullet[i].active) // 총알이 활설화 되었다면
		{
			bullet[i].y--; // y 감소
		}
	}
}

void DeleteBullet() // 총알을 지우는 함수
{
	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if (bullet[i].active && bullet[i].y < 0) // 총알이 활성화 되었고, 총알의 y가 0보다 작으면
		{
			bullet[i].active = 0; // 총알을 비활성화
		}
	}
}

int PlayerTouchBullet() // 총알이 플레이어에게 닿았을 때
{
	int i;
	for (i = 0; i < WIDTH; i++)
	{
		if (bullet[i].active && (bullet[i].y == 0) && (bullet[i].x == player.x))
			// 총알이 활성화 됐고, 총알의 y 가 0이고, 총알의 x와 플레이어의 x가 같을 때
		{
			printf("\n----- 탈락하셨습니다! -----");
			return 1;
		}
	}
	return 0;
}

void MovePlayer() // 플레이어를 이동시키는 함수
{
	if (PressKey(VK_LEFT)) // 왼쪽을 누르면
		player.x -= 1; // 왼쪽으로 이동
	if (PressKey(VK_RIGHT)) // 오른쪽을 누르면
		player.x += 1; // 오른쪽으로 이동

	if (player.x < 0) // 플레이어가 0보다 작으면
		player.x = 0; // 0으로 이동 (벽 같은 기능)
	if (player.x > WIDTH - 1) // 플레이어가 WIDTH - 1 (19)보다 크면
		player.x = WIDTH - 1; // WIDTH - 1 (19) 로 설정
}

void PrintMap() // 맵을 출력하는 함수
{
	system("cls");

	int i;
	for (i = 0; i < WIDTH; i++)
	{
		if (bullet[i].active) // 활성화된 총알이 있다면
		{
			gotoxy(bullet[i].x, HEIGHT - bullet[i].y); // 총알의 위치로 이동
			printf("♠"); // 총알 모양
		}
	}

	// 플레이어 출력
	gotoxy(player.x, HEIGHT);
	printf("♥"); // 플레이어 모양

	// 맵 하단에 땅 출력
	gotoxy(0, HEIGHT + 1);
	for (i = 0; i < WIDTH; i++)
		printf("▨"); // 땅 모양
}

// 게임을 실행하는 메인 함수
void main()
{
	char key; // 입력 키 변수


	Reset(); // 게임 초기화

	// 게임 루프
	do
	{
		srand((int)malloc(NULL));

		CreateBullet();
		MoveBullet();
		DeleteBullet();
		MovePlayer();
		PrintMap();
		Sleep(100);
	} while (!(PlayerTouchBullet()));
}