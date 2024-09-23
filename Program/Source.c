#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

#define WIDTH 30
#define HEIGHT 15 // ���̴� 15�� �ٿ��� �׽�Ʈ
#define MAX_PROJECTILES 5

typedef struct Character {
    int x;
    int y;
    const char* shape;
} Character;

typedef struct Projectile {
    int x;
    int y;
    const char* shape;
    int active; // ����ü�� Ȱ��ȭ�Ǿ� �ִ��� ����
} Projectile;

char testmap[HEIGHT][WIDTH] = {
    {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
};

void Render(Character character, Projectile projectiles[], int projectile_count) {
    Position(0, 0); // Ŀ���� ���� ���� ��ġ�� �̵�
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == character.y && j == character.x / 2) {
                printf("%s", character.shape); // ĳ���� ���
            }
            for (int k = 0; k < projectile_count; k++) {
                if (projectiles[k].active && i == projectiles[k].y && j == projectiles[k].x / 2) {
                    printf("O"); // ����ü ���
                }
            }
            if (testmap[i][j] == '0') {
                printf("  ");
            }
            else if (testmap[i][j] == '1') {
                printf("��");
            }
        }
        printf("\n");
    }
}

void Position(int x, int y) {
    COORD position = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void MoveProjectiles(Projectile projectiles[], int projectile_count) {
    for (int i = 0; i < projectile_count; i++) {
        if (projectiles[i].active) {
            projectiles[i].y++;

            // �������� �¿�� �̵�
            if (rand() % 5 == 0) {
                projectiles[i].x += (rand() % 3 - 1) * 2; // -1, 0, 1 �� �������� ����
                // ��� üũ
                if (projectiles[i].x < 0) projectiles[i].x = 0;
                if (projectiles[i].x >= WIDTH * 2) projectiles[i].x = (WIDTH * 2) - 2; // x ��ǥ �ִ밪 ����
            }

            if (projectiles[i].y >= HEIGHT) { // ȭ���� �Ѿ�� ��Ȱ��ȭ
                projectiles[i].active = 0;
            }
        }
    }
}

void SpawnProjectile(Projectile projectiles[], int projectile_count) {
    for (int i = 0; i < projectile_count; i++) {
        if (!projectiles[i].active) {
            projectiles[i].x = rand() % (WIDTH * 2);
            projectiles[i].y = 0;
            projectiles[i].active = 1; // ����ü Ȱ��ȭ
            break; // �ϳ��� ����ü�� ����
        }
    }
}

int main() {
    srand(time(NULL)); // ���� �õ� �ʱ�ȭ
    Character character = { 2, 1, "��" };
    Projectile projectiles[MAX_PROJECTILES] = { 0 }; // ���� ���� ����ü
    char key = 0;

    while (1) {
        // ����ü �̵�
        MoveProjectiles(projectiles, MAX_PROJECTILES);

        // �浹 �˻�
        for (int i = 0; i < MAX_PROJECTILES; i++) {
            if (projectiles[i].active && projectiles[i].x / 2 == character.x / 2 && projectiles[i].y == character.y) {
                printf("����� �׾����ϴ�!\n");
                return 0; // ���� ����
            }
        }

        // Ű �Է� ó��
        if (_kbhit()) {
            key = _getch();
            if (key == -32) {
                key = _getch();
            }

            switch (key) {
            case UP:
                if (testmap[character.y - 1][character.x / 2] != '1') character.y--;
                break;
            case LEFT:
                if (testmap[character.y][character.x / 2 - 1] != '1') character.x -= 2;
                break;
            case RIGHT:
                if (testmap[character.y][character.x / 2 + 1] != '1') character.x += 2;
                break;
            case DOWN:
                if (testmap[character.y + 1][character.x / 2] != '1') character.y++;
                break;
            }
        }

        // ���ο� ����ü ����
        if (rand() % 10 < 2) { // 20% Ȯ���� ����ü ����
            SpawnProjectile(projectiles, MAX_PROJECTILES);
        }

        // ��ü ȭ�� ������ �ʰ� ĳ���Ϳ� ����ü�� ������Ʈ
        Render(character, projectiles, MAX_PROJECTILES);
        Position(character.x, character.y);
        Sleep(100); // ����ü �̵� �ӵ��� ����
    }

    return 0;
}
