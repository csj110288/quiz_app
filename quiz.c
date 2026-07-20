#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char question[200];
    char option1[60];
    char option2[60];
    char option3[60];
    char option4[60];
    int answer;
} Quiz;

int main() {
    int user_answer;
    int score = 0;
    int lives = 3;
    int total_questions = 11;
    int high_score = 0; // 역대 최고 점수를 담을 변수

    // 1. [파일에서 최고 점수 불러오기]
    // score.txt 파일이 있으면 읽어오고, 없으면 0점으로 시작합니다.
    FILE *file = fopen("score.txt", "r");
    if (file != NULL) {
        fscanf(file, "%d", &high_score);
        fclose(file); // 읽었으면 파일 닫기
    }

    // 2. [11개 리눅스 명령어 문제 은행]
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

    // 랜덤 문제 섞기
    srand(time(NULL));
    for (int i = total_questions - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Quiz temp = bank[i];
        bank[i] = bank[j];
        bank[j] = temp;
    }

    // 헤더 출력 (불러온 최고 점수 표시!)
    printf("=========================================\n");
    printf("  ★ 11종 리눅스 명령어 마스터 퀴즈 v6.0 ★\n");
    printf("  🏆 역대 최고 기록: [%d점]\n", high_score);
    printf("=========================================\n\n");

    // 문제 출제 루프
    for (int i = 0; i < total_questions; i++) {
        printf("📢 [제 %d 라운드]\n", i + 1);
        printf("%s\n", bank[i].question);
        printf("%s  %s  %s  %s\n", bank[i].option1, bank[i].option2, bank[i].option3, bank[i].option4);
        printf("정답 번호를 입력하세요: ");
        scanf("%d", &user_answer);

        if (user_answer == bank[i].answer) {
            printf("\n⭕ 정답입니다! (+10점)\n");
            score += 10;
        } else {
            printf("\n❌ 틀렸습니다! 정답은 %d번입니다.\n", bank[i].answer);
            lives -= 1;
        }

        printf("▶ 현재 상태 - 점수: %d점 | 남은 목숨: %d개\n", score, lives);
        printf("-----------------------------------------\n\n");

        if (lives == 0) {
            printf("🚨 목숨 소진! GAME OVER 🚨\n");
            break;
        }
    }

    // 최종 결과 출력
    printf("\n============ 최종 성적표 ============\n");
    printf("🏆 이번 판 점수: %d점\n", score);

    // 3. [최고 점수 갱신 확인 및 파일 저장]
    if (score > high_score) {
        printf("🎉 축하합니다! 새로운 최고 기록 달성! (%d점 -> %d점)\n", high_score, score);
        high_score = score;

        // score.txt 파일에 새 최고 점수 저장하기
        file = fopen("score.txt", "w"); // "w" = 새 내용으로 덮어쓰기
        if (file != NULL) {
            fprintf(file, "%d", high_score);
            fclose(file);
            printf("💾 새 최고 기록이 score.txt 파일에 영구 저장되었습니다!\n");
        }
    } else {
        printf("👑 역대 최고 기록: %d점\n", high_score);
    }
    printf("===================================\n");

    return 0;
}
