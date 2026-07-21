#include "quiz.h"

// 입력 버퍼를 비우고 엔터 키 1회 입력을 깔끔하게 대기하는 함수
void wait_for_enter(const char *message) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // 잔여 입력 버퍼 비우기
    printf("%s", message);
    getchar(); // 깔끔하게 엔터 키 1회 대기
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
        printf(COLOR_GREEN "💾 새 최고 기록이 score.txt 파일에 영구 저장되었습니다!\n" COLOR_RESET);
    }
}

void reset_high_score() {
    FILE *file = fopen("score.txt", "w");
    if (file != NULL) {
        fprintf(file, "0");
        fclose(file);
        printf(COLOR_YELLOW "\n🧹 최고 기록이 0점으로 리셋되었습니다!\n" COLOR_RESET);
    }
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
        printf(COLOR_GREEN "\n⭕ 정답입니다! (+10점)\n" COLOR_RESET);
        *score += 10;
    } else {
        printf(COLOR_RED "\n❌ 틀렸습니다! 정답은 %d번입니다.\n" COLOR_RESET, correct_ans);
        *lives -= 1;
    }
}

void start_bgm() {
    FILE *f = fopen("bgm.mp3", "r");
    if (f != NULL) {
        fclose(f);
        system("ffplay -nodisp -loop 0 bgm.mp3 > /dev/null 2>&1 &");
    }
}

void stop_bgm() {
    system("killall ffplay > /dev/null 2>&1");
}

void run_quiz_game() {
    int user_answer;
    int score = 0;
    int lives = 3;
    int total_questions = 11;
    int high_score = load_high_score();

    Quiz bank[11] = {
        {"[명령어] 현재 내가 서 있는 디렉토리(방)의 '절대 경로'를 확인하는 명령어는?", "1) ls", "2) cd", "3) pwd", "4) cat", 3},
        {"[명령어] 특정 폴더로 이동하거나 상위 폴더로 나갈 때 사용하는 명령어는?", "1) cd", "2) mv", "3) cp", "4) rm", 1},
        {"[명령어] 현재 폴더에 있는 파일과 폴더 목록을 보여주는 명령어는?", "1) pwd", "2) ls", "3) clear", "4) touch", 2},
        {"[명령어] 터미널 환경에서 C언어 코드를 직접 작성/수정할 수 있는 편집기는?", "1) gcc", "2) nano", "3) git", "4) mkdir", 2},
        {"[명령어] C언어 소스코드(.c)를 실행 파일로 변환(컴파일)해 주는 도구는?", "1) gcc", "2) nano", "3) touch", "4) cat", 1},
        {"[명령어] 내용이 비어있는 새 파일(또는 숨김 파일)을 새로 생성하는 명령어는?", "1) rm", "2) mkdir", "3) touch", "4) ls", 3},
        {"[명령어] 폴더나 파일을 삭제할 때 사용하는 명령어는? (옵션: -rf)", "1) cp", "2) rm", "3) mv", "4) cd", 2},
        {"[명령어] 새로운 폴더(디렉토리)를 생성할 때 쓰는 명령어는?", "1) mkdir", "2) rmdir", "3) touch", "4) nano", 1},
        {"[명령어] 텍스트 파일의 내용을 편집기를 열지 않고 화면에 즉시 출력하는 명령어는?", "1) dog", "2) cat", "3) mouse", "4) print", 2},
        {"[명령어] 터미널 화면에 가득 찬 복잡한 글자들을 싹 지워 깔끔하게 만드는 명령어는?", "1) clean", "2) cls", "3) clear", "4) reset", 3},
        {"[명령어] 작성한 소스코드를 깃허브 원격 저장소에 올리거나 가져오는 버전관리 도구는?", "1) gcc", "2) git", "3) linux", "4) hub", 2}
    };

    srand(time(NULL));
    shuffle_quizzes(bank, total_questions);

    start_bgm();

    for (int i = 0; i < total_questions; i++) {
        system("clear");

        printf(COLOR_YELLOW "=========================================\n" COLOR_RESET);
        printf(COLOR_MAGENTA "  ★ FULL BGM & COLOR 리눅스 퀴즈 ★\n" COLOR_RESET);
        printf(COLOR_YELLOW "  🏆 역대 최고 기록: [%d점]\n", high_score);
        printf("=========================================\n" COLOR_RESET);
        printf("▶ 현재 상태 - 점수: " COLOR_YELLOW "%d점" COLOR_RESET " | 남은 목숨: " COLOR_RED "%d개\n" COLOR_RESET, score, lives);
        printf("-----------------------------------------\n\n");

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

        printf(COLOR_CYAN "📢 [제 %d 라운드]\n" COLOR_RESET, i + 1);
        printf("%s\n", bank[i].question);
        printf("1) %s  2) %s  3) %s  4) %s\n\n", 
               opts[0] + 3, opts[1] + 3, opts[2] + 3, opts[3] + 3);
        
        while (1) {
            printf(COLOR_YELLOW "정답 번호를 입력하세요 (1~4): " COLOR_RESET);
            
            if (scanf("%d", &user_answer) != 1 || user_answer < 1 || user_answer > 4) {
                printf("\a");
                printf(COLOR_RED "⚠️ [입력 오류] 1, 2, 3, 4 중 하나만 입력해 주세요!\n" COLOR_RESET);
                while (getchar() != '\n'); 
            } else {
                break;
            }
        }

        check_answer(user_answer, new_answer, &score, &lives);

        if (lives == 0) {
            printf(COLOR_RED "\n🚨 목숨 소진! GAME OVER 🚨\n" COLOR_RESET);
            break;
        }

        // 마지막 문제가 아니면 진행용 엔터 안내
        if (i < total_questions - 1) {
            wait_for_enter("\n다음 문제로 넘어가려면 엔터 키를 누르세요...");
        }
    }

    stop_bgm();

    // 최종 결과 화면
    system("clear");
    printf("\n============ 최종 성적표 ============\n");
    printf("🏆 이번 판 점수: %d점\n", score);

    if (score > high_score) {
        printf(COLOR_GREEN "🎉 축하합니다! 새로운 최고 기록 달성! (%d점 -> %d점)\n" COLOR_RESET, high_score, score);
        save_high_score(score);
    } else {
        printf("👑 역대 최고 기록: %d점\n", high_score);
    }
    printf("===================================\n");

    // 최종 성적표 출력 후 단 1회의 엔터만 기다리기
    wait_for_enter("\n엔터 키를 누르면 메인 메뉴로 돌아갑니다...");
}
