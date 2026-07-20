#include <stdio.h>
#include <stdlib.h> // rand(), srand() 사용
#include <time.h>   // time() 사용

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
    int total_questions = 11; // 총 11문제!

    // 1. [11개의 리눅스 명령어 문제 은행 구축]
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

    // 2. [랜덤 시드 초기화] 매번 실행할 때마다 다른 무작위 숫자가 나오도록 설정
    srand(time(NULL));

    // 3. [카드 섞기 알고리즘] 11개의 문제 순서를 무작위로 뒤섞습니다!
    for (int i = total_questions - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Quiz temp = bank[i];
        bank[i] = bank[j];
        bank[j] = temp;
    }

    printf("=========================================\n");
    printf("  ★ 11종 리눅스 명령어 마스터 퀴즈 v5.0 ★\n");
    printf("   (매 실행마다 문제 순서가 무작위로 바뀌어 출력됩니다!)\n");
    printf("=========================================\n\n");

    // 4. [무작위 문제 출제 루프]
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
            printf("🚨 목숨 소진! 리눅스 훈련이 더 필요합니다. GAME OVER 🚨\n");
            break;
        }
    }

    // 최종 결과
    printf("\n============ 최종 성적표 ============\n");
    printf("🏆 최종 획득 점수: %d점 / %d점 만점\n", score, total_questions * 10);
    printf("❤️ 남은 목숨: %d개\n", lives);
    printf("===================================\n");

    return 0;
}
