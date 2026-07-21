# 🐧 Linux Command CLI Quiz Game (C Language)

C언어로 작성된 터미널 기반의 리눅스 명령어 학습 퀴즈 게임입니다.

## ✨ 주요 기능 및 특징
- **모듈화 구조**: 헤더 파일(`quiz.h`)과 기능별 소스 파일(`main.c`, `quiz_functions.c`) 분리
- **입력 예외 처리**: 1~4 이외의 숫자/문자 입력 시 경고음(`\a`) 발생 및 재입력 유도
- **화면 자동 청소**: 매 라운드 `system("clear")`를 통한 깔끔한 UI 유지
- **BGM & ANSI Color**: 배경음악 재생 및 알록달록한 터미널 색상 출력
- **최고 기록 저장**: 파일 입출력(`score.txt`)을 통한 점수 영구 보관

## 🚀 실행 방법 (컴파일 및 실행)
```bash
gcc main.c quiz_functions.c -o quiz
./quiz
