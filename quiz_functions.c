#include "quiz.h"

#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN() system("cls")
#else
#define CLEAR_SCREEN() system("clear")
#endif

void wait_for_enter(const char *message) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf("%s", message);
    getchar();
}

int load_high_score() {
    int high_score = 0;
    FILE *file = fopen("score.txt", "r");
    if (file != NULL) {
        fscanf(file, "%d", &high_score);
        fclose(file);
    }
    return high_score;
}

void save_high_score(int score) {
    FILE *file = fopen("score.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d", score);
        fclose(file);
        printf(COLOR_GREEN "    💾 새 최고 기록이 score.txt 파일에 영구 저장되었습니다!\n" COLOR_RESET);
    }
}

void reset_high_score() {
    FILE *file = fopen("score.txt", "w");
    if (file != NULL) {
        fprintf(file, "0");
        fclose(file);
        printf(COLOR_YELLOW "\n    🧹 최고 기록이 0점으로 리셋되었습니다!\n" COLOR_RESET);
    }
}

int load_quizzes_from_file(Quiz bank[], const char *filename, const char *target_category) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return 0;

    char line[700];
    int count = 0;

    while (fgets(line, sizeof(line), file) != NULL && count < MAX_QUIZZES) {
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) == 0) continue;

        char temp_line[700];
        strcpy(temp_line, line);

        char *cat = strtok(temp_line, "|");
        if (cat == NULL || strcmp(cat, target_category) != 0) {
            continue;
        }

        strcpy(bank[count].category, cat);

        char *token = strtok(NULL, "|");
        if (token) strcpy(bank[count].question, token);

        token = strtok(NULL, "|");
        if (token) strcpy(bank[count].option1, token);

        token = strtok(NULL, "|");
        if (token) strcpy(bank[count].option2, token);

        token = strtok(NULL, "|");
        if (token) strcpy(bank[count].option3, token);

        token = strtok(NULL, "|");
        if (token) strcpy(bank[count].option4, token);

        token = strtok(NULL, "|");
        if (token) bank[count].answer = atoi(token);

        token = strtok(NULL, "|");
        if (token) strcpy(bank[count].explanation, token);

        count++;
    }

    fclose(file);
    return count;
}

void shuffle_quizzes(Quiz bank[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Quiz temp = bank[i];
        bank[i] = bank[j];
        bank[j] = temp;
    }
}

void check_answer(int user_ans, int correct_ans, int *score, int *lives) {
    if (user_ans == correct_ans) {
        printf(COLOR_GREEN "\n    ⭕ 정답입니다! (+10점)\n" COLOR_RESET);
        *score += 10;
    } else {
        printf(COLOR_RED "\n    ❌ 틀렸습니다! 정답은 %d번입니다.\n" COLOR_RESET, correct_ans);
        *lives -= 1;
    }
}

void start_bgm() {
    FILE *f = fopen("bgm.mp3", "r");
    if (f != NULL) {
        fclose(f);
#ifdef _WIN32
        system("start /b ffplay -nodisp -loop 0 bgm.mp3 > NUL 2>&1");
#else
        system("ffplay -nodisp -loop 0 bgm.mp3 > /dev/null 2>&1 &");
#endif
    }
}

void stop_bgm() {
#ifdef _WIN32
    system("taskkill /f /im ffplay.exe > NUL 2>&1");
#else
    system("killall ffplay > /dev/null 2>&1");
#endif
}

void run_quiz_game() {
    CLEAR_SCREEN();
    
    // 분야 선택 화면 상단/좌측 여백
    printf("\n\n\n");
    printf(COLOR_YELLOW "    =========================================\n" COLOR_RESET);
    printf(COLOR_CYAN   "           📚 퀴즈 분야를 선택해 주세요\n" COLOR_RESET);
    printf(COLOR_YELLOW "    =========================================\n" COLOR_RESET);
    printf("     1) 🐧 리눅스 / Bash 명령어 (15문항)\n");
    printf("     2) 💻 C언어 핵심 기초 (15문항)\n");
    printf("    -----------------------------------------\n");
    printf(COLOR_GREEN  "    선택 (1 또는 2): " COLOR_RESET);

    int cat_choice = 0;
    while (1) {
        if (scanf("%d", &cat_choice) == 1 && (cat_choice == 1 || cat_choice == 2)) {
            break;
        }
        printf(COLOR_RED "    ⚠️ 올바른 번호(1 또는 2)를 입력해 주세요: " COLOR_RESET);
        while (getchar() != '\n');
    }

    const char *target_cat = (cat_choice == 1) ? "LINUX" : "C_LANG";
    const char *cat_title = (cat_choice == 1) ? "리눅스/Bash 명령어" : "C언어 핵심 기초";

    Quiz bank[MAX_QUIZZES];
    int total_questions = load_quizzes_from_file(bank, "quizzes.txt", target_cat);

    if (total_questions == 0) {
        printf(COLOR_RED "\n    ⚠️ [오류] 해당 분야의 문제를 불러올 수 없습니다!\n" COLOR_RESET);
        wait_for_enter("\n    엔터 키를 누르면 메인 메뉴로 돌아갑니다...");
        return;
    }

    int user_answer;
    int score = 0;
    int lives = 3;
    int high_score = load_high_score();

    srand(time(NULL));
    shuffle_quizzes(bank, total_questions);

    start_bgm();

    for (int i = 0; i < total_questions; i++) {
        CLEAR_SCREEN();

        // 퀴즈 화면 상단 여백 (3줄) 및 좌측 여백 적용
        printf("\n\n\n");
        printf(COLOR_YELLOW  "    =========================================\n" COLOR_RESET);
        printf(COLOR_MAGENTA "      ★ [%s] 퀴즈 ★\n" COLOR_RESET, cat_title);
        printf(COLOR_YELLOW  "      🏆 역대 최고 기록: [%d점] (총 %d문제)\n", high_score, total_questions);
        printf("    =========================================\n" COLOR_RESET);
        printf("    ▶ 현재 상태 - 점수: " COLOR_YELLOW "%d점" COLOR_RESET " | 남은 목숨: " COLOR_RED "%d개\n" COLOR_RESET, score, lives);
        printf("    -----------------------------------------\n\n");

        char *opts[4] = {bank[i].option1, bank[i].option2, bank[i].option3, bank[i].option4};
        char *correct_str = opts[bank[i].answer - 1];

        for (int k = 3; k > 0; k--) {
            int r = rand() % (k + 1);
            char *temp = opts[k];
            opts[k] = opts[r];
            opts[r] = temp;
        }

        int new_answer = 0;
        for (int k = 0; k < 4; k++) {
            if (opts[k] == correct_str) {
                new_answer = k + 1;
                break;
            }
        }

        printf(COLOR_CYAN "    📢 [제 %d 라운드 / 총 %d문제]\n" COLOR_RESET, i + 1, total_questions);
        printf("    %s\n\n", bank[i].question);
        printf("    1) %-15s 2) %-15s\n", opts[0] + 3, opts[1] + 3);
        printf("    3) %-15s 4) %-15s\n\n", opts[2] + 3, opts[3] + 3);
        
        while (1) {
            printf(COLOR_YELLOW "    정답 번호를 입력하세요 (1~4): " COLOR_RESET);
            if (scanf("%d", &user_answer) != 1 || user_answer < 1 || user_answer > 4) {
                printf("\a");
                printf(COLOR_RED "    ⚠️ [입력 오류] 1, 2, 3, 4 중 하나만 입력해 주세요!\n" COLOR_RESET);
                while (getchar() != '\n'); 
            } else {
                break;
            }
        }

        check_answer(user_answer, new_answer, &score, &lives);

        printf(COLOR_CYAN "\n    💡 [정답 해설]\n" COLOR_RESET);
        printf("       %s\n", bank[i].explanation);
        printf("    -----------------------------------------\n");

        if (lives == 0) {
            printf(COLOR_RED "\n    🚨 목숨 소진! GAME OVER 🚨\n" COLOR_RESET);
            break;
        }

        if (i < total_questions - 1) {
            printf("\n    [1] 다음 문제 계속 풀기  [2] 퀴즈 중단하고 나가기\n");
            printf(COLOR_GREEN "    선택 (1 또는 2): " COLOR_RESET);
            int next_action = 0;
            while (1) {
                if (scanf("%d", &next_action) == 1 && (next_action == 1 || next_action == 2)) {
                    break;
                }
                printf(COLOR_RED "    ⚠️ 1 또는 2를 입력해 주세요: " COLOR_RESET);
                while (getchar() != '\n');
            }

            if (next_action == 2) {
                printf(COLOR_YELLOW "\n    🛑 퀴즈를 중단했습니다. 현재까지 점수가 반영됩니다.\n" COLOR_RESET);
                break;
            }
        }
    }

    stop_bgm();

    printf("\n    ============ 최종 성적표 ============\n");
    printf("    🏆 이번 판 점수: %d점\n", score);

    if (score > high_score) {
        printf(COLOR_GREEN "    🎉 축하합니다! 새로운 최고 기록 달성! (%d점 -> %d점)\n" COLOR_RESET, high_score, score);
        save_high_score(score);
    } else {
        printf("    👑 역대 최고 기록: %d점\n", high_score);
    }
    printf("    ===================================\n");

    wait_for_enter("\n    엔터 키를 누르면 메인 메뉴로 돌아갑니다...");
}
