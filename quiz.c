#include <stdio.h>

// 1. [문제 카드 세트 만들기] 지문, 보기4개, 정답을 하나로 묶는 구조체 정의
typedef struct {
    char question[200]; // 문제 지문
    char option1[50];   // 보기 1
    char option2[50];   // 보기 2
    char option3[50];   // 보기 3
    char option4[50];   // 보기 4
    int answer;         // 정답 번호 (1~4)
} Quiz;

int main() {
    int user_answer;
    int score = 0;
    int lives = 3;

    // 2. [문제 은행 상자 만들기] 4개의 문제 카드를 미리 등록해 둡니다.
    // 문제를 추가하고 싶다면 이 상자 안에 문제 카드만 줄줄이 추가하면 됩니다!
    Quiz bank[4] = {
        {
            "컴퓨터에서 가장 중요한 '두뇌' 역할을 하는 부품은?",
            "1) RAM", "2) CPU", "3) HDD", "4) GPU",
            2
        },
        {
            "다음 중 인터넷 브라우저가 '아닌' 것은?",
            "1) Chrome", "2) Safari", "3) Linux", "4) Edge",
            3
        },
        {
            "C언어에서 화면에 글자를 '출력'하는 함수는?",
            "1) scanf", "2) main", "3) printf", "4) include",
            3
        },
        {
            "리눅스에서 '현재 내가 서 있는 방의 주소'를 확인하는 명령어는?",
            "1) ls", "2) cd", "3) pwd", "4) cat",
            3
        }
    };

    printf("=========================================\n");
    printf("   ★ 문제 은행 기반 수수께끼 앱 v4.0 ★\n");
    printf("=========================================\n\n");

    // 3. [문제 출제 루프] 문제 상자(bank)에 있는 문제를 0번부터 3번까지 차례대로 출제합니다.
    for (int i = 0; i < 4; i++) {
        printf("📢 [제 %d 라운드]\n", i + 1);
        printf("%s\n", bank[i].question);
        printf("%s  %s  %s  %s\n", bank[i].option1, bank[i].option2, bank[i].option3, bank[i].option4);
        printf("정답 번호를 입력하세요: ");
        scanf("%d", &user_answer);

        // 정답 채점
        if (user_answer == bank[i].answer) {
            printf("\n⭕ 정답입니다! (+10점)\n");
            score += 10;
        } else {
            printf("\n❌ 틀렸습니다! 정답은 %d번입니다.\n", bank[i].answer);
            lives -= 1;
        }

        printf("▶ 현재 상태 - 점수: %d점 | 남은 목숨: %d개\n", score, lives);
        printf("-----------------------------------------\n\n");

        // 목숨이 0개가 되었을 때 게임 오버 탈출 장치
        if (lives == 0) {
            printf("🚨 목숨이 모두 소진되었습니다. GAME OVER 🚨\n");
            break;
        }
    }

    // 최종 결과 출력
    printf("\n============ 최종 성적표 ============\n");
    printf("🏆 최종 획득 점수: %d점\n", score);
    printf("❤️ 남은 목숨: %d개\n", lives);
    printf("===================================\n");

    return 0;
}
