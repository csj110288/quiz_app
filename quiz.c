#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // strcpy() 사용을 위해 추가

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
    int high_score = 0;

    // 최고 점수 파일 불러오기
    FILE *file = fopen("score.txt", "r");
    if (file != NULL) {
        fscanf(file, "%d", &high_score);
        fclose(file);
    }

    // 11개 문제 은행 데이터
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

    // 랜덤 시드 설정
    srand(time(NULL));

    // 1. [문제 전체 순서 섞기]
    for (int i = total_questions - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Quiz temp = bank[i];
        bank[i] = bank[j];
        bank[j] = temp;
    }

    printf("=========================================\n");
    printf("  ★ 완전 무작위 11종 리눅스 퀴즈 v7.0 ★\n");
    printf("  (문제 순서와 보기 1,2,3,4번 위치가 모두 섞입니다!)\n");
    printf("  🏆 역대 최고 기록: [%d점]\n", high_score);
    printf("=========================================\n\n");

    for (int i = 0; i < total_questions; i++) {
        // 2. [★ 핵심 ★ 보기 4개 무작위로 섞는 알고리즘]
        char *opts[4] = {bank[i].option1, bank[i].option2, bank[i].option3, bank[i].option4};
        char *correct_str = opts[bank[i].answer - 1]; // 원래 정답 문장 복사해두기

        // 보기 4개의 위치를 피셔-예이츠 알고리즘으로 섞기
        for (int k = 3; k > 0; k--) {
            int r = rand() % (k + 1);
            char *temp = opts[k];
            opts[k] = opts[r];
            opts[r] = temp;
        }

        // 섞인 보기 위치 중 원래 정답 문장이 몇 번 위치에 가 있는지 찾아 정답 번호 수정!
        int new_answer = 0;
        for (int k = 0; k < 4; k++) {
            if (opts[k] == correct_str) {
                new_answer = k + 1; // 1~4번 생성
                break;
            }
        }

        // 출력할 때 예쁘게 1), 2), 3), 4) 번호 붙이기 (내용물 추출)
        // 기존 보기의 "1) ", "2) " 접두사를 떼고 내용만 가져와 번호 재부여
        printf("📢 [제 %d 라운드]\n", i + 1);
        printf("%s\n", bank[i].question);
        
        // 섞인 보기를 1) ~ 4) 번호와 함께 출력 (앞의 3글자 "1) " 등을 넘어서 출력)
        printf("1) %s  2) %s  3) %s  4) %s\n", 
               opts[0] + 3, opts[1] + 3, opts[2] + 3, opts[3] + 3);
        
        printf("정답 번호를 입력하세요: ");
        scanf("%d", &user_answer);

        if (user_answer == new_answer) {
            printf("\n⭕ 정답입니다! (+10점)\n");
            score += 10;
        } else {
            printf("\n❌ 틀렸습니다! 정답은 %d번입니다.\n", new_answer);
            lives -= 1;
        }

        printf("▶ 현재 상태 - 점수: %d점 | 남은 목숨: %d개\n", score, lives);
        printf("-----------------------------------------\n\n");

        if (lives == 0) {
            printf("🚨 목숨 소진! GAME OVER 🚨\n");
            break;
        }
    }

    // 최종 결과 및 저장
    printf("\n============ 최종 성적표 ============\n");
    printf("🏆 이번 판 점수: %d점\n", score);

    if (score > high_score) {
        printf("🎉 축하합니다! 새로운 최고 기록 달성! (%d점 -> %d점)\n", high_score, score);
        high_score = score;

        file = fopen("score.txt", "w");
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
