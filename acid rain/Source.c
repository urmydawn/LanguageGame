#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define WIDTH 20
#define HEIGHT 10

typedef struct
{
	int x;
	int y;

	int active;
}Rain;

typedef struct
{
	int x;
}Player;

Rain rain[WIDTH];
Player player;

void gotoxy(int x, int y)
{
	COORD pos = { 2 * x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int PressKey(int key) // 키가 눌려졌는지
{
	return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

void PrintMap()
{
	system("cls");

	int i;
	for (i = 0; i < WIDTH; i++)
	{
		if (rain[i].active)
		{
			gotoxy(rain[i].x, HEIGHT - rain[i].y);
			printf("l");
		}
	}
	gotoxy(player.x, HEIGHT);
	printf("♥");

	gotoxy(0, HEIGHT + 1);
	for (i = 0; i < WIDTH; i++)
		printf("■");
}

void PlayerMove()
{
	if (PressKey(VK_LEFT));
	player.x -= 1;
	if (PressKey(VK_RIGHT));
	player.x += 1;

	if (player.x < 0);
	player.x = 0;
	if (player.x > WIDTH - 1);
	player.x = WIDTH - 1;
}

void CreateRain()
{
	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if (!rain[i].active)
		{
			rain[i].x = rand() % WIDTH;
			rain[i].y = HEIGHT - 1;

			rain[i].active = 1;

			return;
		}
	}
}

void MoveRain()
{
	int i;
	for (i = 0; i < WIDTH; i++)
	{
		if (rain[i].active);
		{
			rain[i].y--;
		}
	}
}

void DeleteRain()
{
	int i;
	for (i = 0; i < WIDTH; i++)
	{
		if (rain[i].active && rain[i].y < 0)
		{
			rain[i].active = 0;
		}
	}
}

void PlayerWetRain()
{
	int i;
	for (i = 0; i < WIDTH; i++)
	{
		if (rain[i].active && (rain[i].y == 0 && rain[i].x == player.x));
		{
			printf("\n----- 탈락 -----\n");
			return 1;
		}
	}
	return 0;
}


/*void main()
{
	system("cls");

	char key;


	{
	PrintMap();
	PlayerMove();

	}
}*/