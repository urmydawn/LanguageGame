#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define WIDTH 11
#define HEIGHT 11

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

typedef struct Character
{
	int x;
	int y;
	const char* shape;
}Character;

char maze[WIDTH][HEIGHT] = 
{
	{'1','1','1','1','1','1','1','1','1','1','1'},
	{'1','0','1','0','0','0','0','0','1','2','1'},
	{'1','0','1','0','1','1','0','1','1','0','1'},
	{'1','0','1','0','0','1','0','0','1','0','1'},
	{'1','0','1','1','0','1','1','1','1','0','1'},
	{'1','0','0','0','0','1','0','0','0','0','1'},
	{'1','0','1','1','1','1','1','1','0','1','1'},
	{'1','0','1','0','1','0','0','0','0','1','1'},
	{'1','0','0','0','0','0','1','1','0','1','1'},
	{'1','0','1','0','1','0','1','0','0','0','1'},
	{'1','1','1','1','1','1','1','1','1','1','1'},
};

void Render()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (maze[i][j] == '0')
			{
				printf("  ");
			}
			else if (maze[i][j] == '1')
			{
				printf("��");
			}
			else if (maze[i][j] == '2')
			{
				printf("��");
			}
		}
		printf("\n");
	}

}

void Position(int x, int y)
{
	// X�� Y���� �����ϴ� ����ü�Դϴ�.
	COORD position = { x, y };

	// �ܼ� Ŀ���� ��ǥ�� �����ϴ� �Լ��Դϴ�.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

int main()
{
	Character character = { 2, 1,"��" };

	char key = 0;

	Render();

	while (1)
	{
		if (_kbhit())
		{
			key = _getch();

			if (key == -32)
			{
				key = _getch();
			}

			switch (key)
			{
			case UP:
				if (maze[character.y - 1][character.x / 2] != '1') character.y--;
				break;
			case LEFT:
				if (maze[character.y][character.x / 2 - 1] != '1') character.x -= 2;
				break;
			case RIGHT:
				if (maze[character.y][character.x / 2 + 1] != '1') character.x += 2;
				break;
			case DOWN:
				if (maze[character.y + 1][character.x / 2] != '1') character.y++;
				break;

			}

			system("cls");

			Render();
		}
		printf("%s", character.shape);
		Position(character.x, character.y);
	}


	return 0;
}