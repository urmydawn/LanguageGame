#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define WIDTH 20
#define HEIGHT 10

typedef struct // �Ѿ��� ǥ���ϴ� ����ü
{
	int x;
	int y;

	int active;
}Bullet;

typedef struct // �÷��̾ ǥ���ϴ� ����ü
{
	int x;
}Player;

Bullet bullet[WIDTH];
Player player;

void gotoxy(int x, int y) // Ŀ���� �̵���Ű�� �Լ�
{
	COORD pos = { 2 * x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int PressKey(int key) // Ű�� ���������� Ȯ���ϴ� �Լ�
{
	return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

void Reset() // ������ �ʱ�ȭ ��Ű�� �Լ�
{
	int i;

	for (i = 0; i < WIDTH; i++) // ��� �Ѿ��� 0���� �ʱ�ȭ
		bullet[i].active = 0;

	player.x = WIDTH / 2; // �÷��̾� ��ġ�� ���� / 2 (�߾�)�� ����
}

void CreateBullet() // �Ѿ��� ������Ű�� �Լ�
{
	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if (!bullet[i].active)
		{
			bullet[i].x = rand() % WIDTH; // �������� �Ѿ��� ������ ��ǥ ����
			bullet[i].y = HEIGHT - 1; // �Ѿ��� ������ ��ġ 10 - 1

			bullet[i].active = 1;

			return; // �ϳ��� �����ϰ� Ż��
		}
	}
}

void MoveBullet() // �Ѿ��� �Ʒ��� �̵���Ű�� �Լ�
{
	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if (bullet[i].active) // �Ѿ��� Ȱ��ȭ �Ǿ��ٸ�
		{
			bullet[i].y--; // y ����
		}
	}
}

void DeleteBullet() // �Ѿ��� ����� �Լ�
{
	int i;

	for (i = 0; i < WIDTH; i++)
	{
		if (bullet[i].active && bullet[i].y < 0) // �Ѿ��� Ȱ��ȭ �Ǿ���, �Ѿ��� y�� 0���� ������
		{
			bullet[i].active = 0; // �Ѿ��� ��Ȱ��ȭ
		}
	}
}

int PlayerTouchBullet() // �Ѿ��� �÷��̾�� ����� ��
{
	int i;
	for (i = 0; i < WIDTH; i++)
	{
		if (bullet[i].active && (bullet[i].y == 0) && (bullet[i].x == player.x))
			// �Ѿ��� Ȱ��ȭ �ư�, �Ѿ��� y �� 0�̰�, �Ѿ��� x�� �÷��̾��� x�� ���� ��
		{
			printf("\n----- Ż���ϼ̽��ϴ�! -----");
			return 1;
		}
	}
	return 0;
}

void MovePlayer() // �÷��̾ �̵���Ű�� �Լ�
{
	if (PressKey(VK_LEFT)) // ������ ������
		player.x -= 1; // �������� �̵�
	if (PressKey(VK_RIGHT)) // �������� ������
		player.x += 1; // ���������� �̵�

	if (player.x < 0) // �÷��̾ 0���� ������
		player.x = 0; // 0���� �̵� (�� ���� ���)
	if (player.x > WIDTH - 1) // �÷��̾ WIDTH - 1 (19)���� ũ��
		player.x = WIDTH - 1; // WIDTH - 1 (19) �� ����
}

void PrintMap() // ���� ����ϴ� �Լ�
{
	system("cls");

	int i;
	for (i = 0; i < WIDTH; i++)
	{
		if (bullet[i].active) // Ȱ��ȭ�� �Ѿ��� �ִٸ�
		{
			gotoxy(bullet[i].x, HEIGHT - bullet[i].y); // �Ѿ��� ��ġ�� �̵�
			printf("��"); // �Ѿ� ���
		}
	}

	// �÷��̾� ���
	gotoxy(player.x, HEIGHT);
	printf("��"); // �÷��̾� ���

	// �� �ϴܿ� �� ���
	gotoxy(0, HEIGHT + 1);
	for (i = 0; i < WIDTH; i++)
		printf("��"); // �� ���
}

// ������ �����ϴ� ���� �Լ�
void main()
{
	char key; // �Է� Ű ����


	Reset(); // ���� �ʱ�ȭ

	// ���� ����
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