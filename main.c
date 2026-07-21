#include "quiz.h"

int main() {
    int choice;

    while (1) {
        system("clear");
        printf(COLOR_YELLOW "=========================================\n" COLOR_RESET);
        printf(COLOR_MAGENTA "    ★ FULL BGM & COLOR 리눅스 퀴즈 ★\n" COLOR_RESET);
        printf(COLOR_YELLOW "=========================================\n" COLOR_RESET);
        printf("1. 퀴즈 시작\n");
        printf("2. 최고 기록 리셋\n");
        printf("3. 게임 종료\n");
        printf("-----------------------------------------\n");
        
        while (1) {
            printf(COLOR_CYAN "선택하세요 (1-3): " COLOR_RESET);
            
            // 1, 2, 3 이외의 숫자가 들어오거나 문자가 들어올 경우
            if (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
                printf("\a"); // 경고음
                printf(COLOR_RED "⚠️ [입력 오류] 1, 2, 3 중 하나만 입력해 주세요!\n" COLOR_RESET);
                while (getchar() != '\n'); // 입력 버퍼 비우기
            } else {
                break;
            }
        }

        switch (choice) {
            case 1:
                run_quiz_game();
                break;
            case 2:
                reset_high_score();
                printf("\n엔터 키를 누르면 메인 메뉴로 돌아갑니다...");
                while (getchar() != '\n'); // 버퍼 정리
                getchar(); // 엔터 대기
                break;
            case 3:
                printf(COLOR_GREEN "\n게임을 종료합니다. 수고하셨습니다!\n" COLOR_RESET);
                return 0;
        }
    }
    return 0;
}
