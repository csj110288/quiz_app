#ifndef QUIZ_H
#define QUIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_MAGENTA "\033[1;35m"

#define MAX_QUIZZES 100

typedef struct {
    char category[20];   // LINUX 또는 C_LANG
    char question[200];
    char option1[60];
    char option2[60];
    char option3[60];
    char option4[60];
    int answer;
    char explanation[300]; // 정답 해설
} Quiz;

int load_high_score();
void save_high_score(int score);
void reset_high_score();
int load_quizzes_from_file(Quiz bank[], const char *filename, const char *target_category);
void shuffle_quizzes(Quiz bank[], int size);
void check_answer(int user_ans, int correct_ans, int *score, int *lives);
void start_bgm();
void stop_bgm();
void run_quiz_game();

#endif
