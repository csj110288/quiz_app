#include <stdio.h>

int main() {
    int answer1, answer2, answer3, answer4; // 변수들 준비
    int score = 0;   
    int lives = 3;   // 목숨은 3개!

    printf("=========================================\n");
    printf("   ★ 진정한 삼세판! 수수께끼 앱 v2.5 ★\n");
    printf("=========================================\n\n");

    // ================= [1번 문제] =================
    printf("[문제 1] 컴퓨터에서 가장 중요한 '두뇌' 역할을 하는 부품의 이름은 무엇일까요?\n");
    printf("1) RAM  2) CPU  3) HDD  4) GPU\n");
    printf("정답 번호를 입력하세요: ");
    scanf("%d", &answer1);

    if (answer1 == 2) {
        printf("\n⭕ 정답입니다! (+10점)\n");
        score = score + 10; 
    } else {
        printf("\n❌ 틀렸습니다! 정답은 2번 CPU입니다.\n");
        lives = lives - 1;  
    }
    printf("▶ 현재 상태 - 점수: %d점 | 남은 목숨: %d개\n", score, lives);
    printf("-----------------------------------------\n\n");

    if (lives == 0) {
        printf("🚨 목숨이 모두 소진되었습니다. GAME OVER 🚨\n");
        printf("🏆 최종 점수: %d점\n", score);
        return 0; 
    }

    // ================= [2번 문제] =================
    printf("[문제 2] 다음 중 인터넷 브라우저가 '아닌' 것은 무엇일까요?\n");
    printf("1) Chrome  2) Safari  3) Linux  4) Edge\n");
    printf("정답 번호를 입력하세요: ");
    scanf("%d", &answer2);

    if (answer2 == 3) {
        printf("\n⭕ 정답입니다! (+10점)\n");
        score = score + 10;
    } else {
        printf("\n❌ 틀렸습니다! 정답은 3번 Linux(운영체제)입니다.\n");
        lives = lives - 1;
    }
    printf("▶ 현재 상태 - 점수: %d점 | 남은 목숨: %d개\n", score, lives);
    printf("-----------------------------------------\n\n");

    if (lives == 0) {
        printf("🚨 목숨이 모두 소진되었습니다. GAME OVER 🚨\n");
        printf("🏆 최종 점수: %d점\n", score);
        return 0; 
    }

    // ================= [3번 문제] =================
    // 여기서부터 진짜 긴장감이 시작됩니다!
    printf("[문제 3] C언어에서 화면에 글자를 '출력'할 때 사용하는 함수의 이름은?\n");
    printf("1) scanf  2) include  3) main  4) printf\n");
    printf("정답 번호를 입력하세요: ");
    scanf("%d", &answer3);

    if (answer3 == 4) {
        printf("\n⭕ 정답입니다! (+10점)\n");
        score = score + 10;
    } else {
        printf("\n❌ 틀렸습니다! 정답은 4번 printf입니다.\n");
        lives = lives - 1;
    }
    printf("▶ 현재 상태 - 점수: %d점 | 남은 목숨: %d개\n", score, lives);
    printf("-----------------------------------------\n\n");

    if (lives == 0) {
        printf("🚨 3번 문제에서 목숨 소진! GAME OVER 🚨\n");
        printf("🏆 최종 점수: %d점\n", score);
        return 0; 
    }

    // ================= [4번 문제] =================
    // 앞의 문제들을 최소 2개 이상 맞혀서 목숨을 살려온 자만 볼 수 있는 최종 관문!
    printf("[문제 4] 리눅스 터미널에서 '현재 내가 서 있는 방의 주소'를 확인하는 명령어는?\n");
    printf("1) ls  2) cd  3) pwd  4) cat\n");
    printf("정답 번호를 입력하세요: ");
    scanf("%d", &answer4);

    if (answer4 == 3) {
        printf("\n⭕ 정답입니다! (+10점)\n");
        score = score + 10;
    } else {
        printf("\n❌ 틀렸습니다! 정답은 3번 pwd입니다.\n");
        lives = lives - 1;
    }
    printf("▶ 현재 상태 - 점수: %d점 | 남은 목숨: %d개\n", score, lives);
    printf("-----------------------------------------\n\n");

    if (lives == 0) {
        printf("🚨 마지막 문턱에서 목숨 소진! GAME OVER 🚨\n");
        printf("🏆 최종 점수: %d점\n", score);
        return 0; 
    }

    // ================= [최종 승리 화면] =================
    printf("🎉 축하합니다! 4개의 지옥 코스를 모두 돌파하셨습니다! 🎉\n");
    printf("🏆 최종 점수: %d점\n", score);
    printf("❤️ 남은 목숨: %d개 (생존 완료)\n", lives);
    printf("===================================\n");

    return 0;
}
