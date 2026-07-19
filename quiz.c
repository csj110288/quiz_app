#include <stdio.h>

int main() {
    int answer;      // 사용자의 입력을 받을 변수 (하나로 통일!)
    int score = 0;   
    int lives = 3;   
    int round = 1;   // 현재 몇 번째 판인지 세어주는 변수 추가

    printf("=========================================\n");
    printf("   ★ 무한  수수께끼 앱 v3.0 ★\n");
    printf("=========================================\n\n");

    // 🔥 [오늘의 핵심 뼈대] while (1)은 "괄호 안이 참(1)인 동안 무한히 반복하라"는 뜻입니다.
    while (1) {
        printf("📢 [제 %d 라운드 시작]\n", round);

        // 번갈아가며 문제가 나오도록 라운드 번호(홀수/짝수)로 문제를 출제합니다.
        if (round % 2 != 0) {
            // [홀수 라운드 문제]
            printf("[문제] C언어에서 화면에 글자를 '출력'하는 함수의 이름은?\n");
            printf("1) scanf  2) main  3) printf  4) include\n");
            printf("정답 번호: ");
            scanf("%d", &answer);

            if (answer == 3) {
                printf("\n⭕ 정답입니다! (+10점)\n");
                score = score + 10;
            } else {
                printf("\n❌ 틀렸습니다! 정답은 3번 printf입니다.\n");
                lives = lives - 1;
            }
        } else {
            // [짝수 라운드 문제]
            printf("[문제] 리눅스에서 '현재 내가 서 있는 방의 주소'를 확인하는 명령어는?\n");
            printf("1) ls  2) cd  3) pwd  4) cat\n");
            printf("정답 번호: ");
            scanf("%d", &answer);

            if (answer == 3) {
                printf("\n⭕ 정답입니다! (+10점)\n");
                score = score + 10;
            } else {
                printf("\n❌ 틀렸습니다! 정답은 3번 pwd입니다.\n");
                lives = lives - 1;
            }
        }

        // 현재 점수 및 목숨 출력
        printf("▶ 현재 상태 - 점수: %d점 | 남은 목숨: %d개\n", score, lives);
        printf("-----------------------------------------\n\n");

        // 🔥 [탈출 장치] 목숨이 0개가 되면 무한 루프를 깨부수고 탈출합니다!
        if (lives == 0) {
            printf("🚨 탈출 불가! 목숨이 모두 소진되었습니다. GAME OVER 🚨\n");
            break; // break를 만나는 순간 while (1) 중괄호를 탈출합니다!
        }

        // 무사히 통과했다면 다음 라운드로 숫자를 올려줍니다.
        round = round + 1;
    }

    // [최종 게임오버 성적표 화면]
    printf("\n============ 최종 성적표 ============\n");
    printf("🏆 최종 돌파 라운드: %d 라운드\n", round);
    printf("💰 최종 획득 점수: %d점\n", score);
    printf("===================================\n");

    return 0;
}
