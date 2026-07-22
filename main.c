#include <stdio.h>
#include <stdlib.h>
#include "quiz.h"

#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN() system("cls")
#else
#define CLEAR_SCREEN() system("clear")
#endif

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int choice;

    while (1) {
        CLEAR_SCREEN();

        // 상단 여백 (3줄) 및 좌측 여백 적용
        printf("\n\n\n");
        printf("    =========================================\n");
        printf(COLOR_MAGENTA "        ★ FULL BGM & COLOR 리눅스 퀴즈 ★\n" COLOR_RESET);
        printf(COLOR_YELLOW  "    =========================================\n" COLOR_RESET);
        printf("      1. 퀴즈 시작\n");
        printf("      2. 최고 기록 리셋\n");
        printf("      3. 게임 종료\n");
        printf("    -----------------------------------------\n");
        printf(COLOR_GREEN "    선택하세요 (1-3): " COLOR_RESET);

        if (scanf("%d", &choice) != 1) {
            printf("\a");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 1) {
            run_quiz_game();
        } else if (choice == 2) {
            reset_high_score();
            printf("\n    엔터 키를 누르면 메뉴로 돌아갑니다...");
            while (getchar() != '\n');
            getchar();
        } else if (choice == 3) {
            printf("\n    게임을 종료합니다. 이용해 주셔서 감사합니다!\n\n");
            break;
        }
    }

    return 0;
}
