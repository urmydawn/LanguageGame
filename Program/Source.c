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
#define HEIGHT 15 // 높이는 15로 줄여서 테스트
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
    int active; // 투사체가 활성화되어 있는지 여부
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
    Position(0, 0); // 커서를 맵의 시작 위치로 이동
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == character.y && j == character.x / 2) {
                printf("%s", character.shape); // 캐릭터 출력
            }
            for (int k = 0; k < projectile_count; k++) {
                if (projectiles[k].active && i == projectiles[k].y && j == projectiles[k].x / 2) {
                    printf("O"); // 투사체 출력
                }
            }
            if (testmap[i][j] == '0') {
                printf("  ");
            }
            else if (testmap[i][j] == '1') {
                printf("■");
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

            // 랜덤으로 좌우로 이동
            if (rand() % 5 == 0) {
                projectiles[i].x += (rand() % 3 - 1) * 2; // -1, 0, 1 중 랜덤으로 선택
                // 경계 체크
                if (projectiles[i].x < 0) projectiles[i].x = 0;
                if (projectiles[i].x >= WIDTH * 2) projectiles[i].x = (WIDTH * 2) - 2; // x 좌표 최대값 수정
            }

            if (projectiles[i].y >= HEIGHT) { // 화면을 넘어가면 비활성화
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
            projectiles[i].active = 1; // 투사체 활성화
            break; // 하나의 투사체만 생성
        }
    }
}

int main() {
    srand(time(NULL)); // 랜덤 시드 초기화
    Character character = { 2, 1, "★" };
    Projectile projectiles[MAX_PROJECTILES] = { 0 }; // 여러 개의 투사체
    char key = 0;

    while (1) {
        // 투사체 이동
        MoveProjectiles(projectiles, MAX_PROJECTILES);

        // 충돌 검사
        for (int i = 0; i < MAX_PROJECTILES; i++) {
            if (projectiles[i].active && projectiles[i].x / 2 == character.x / 2 && projectiles[i].y == character.y) {
                printf("당신은 죽었습니다!\n");
                return 0; // 게임 종료
            }
        }

        // 키 입력 처리
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

        // 새로운 투사체 생성
        if (rand() % 10 < 2) { // 20% 확률로 투사체 생성
            SpawnProjectile(projectiles, MAX_PROJECTILES);
        }

        // 전체 화면 지우지 않고 캐릭터와 투사체만 업데이트
        Render(character, projectiles, MAX_PROJECTILES);
        Position(character.x, character.y);
        Sleep(100); // 투사체 이동 속도를 조절
    }

    return 0;
}
