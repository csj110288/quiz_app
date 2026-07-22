# 실행 파일 이름 및 컴파일러 설정
CC = gcc
CFLAGS = -W -Wall
TARGET = quiz
OBJS = main.o quiz_functions.o

# 기본 빌드 명령 (make 입력 시 실행)
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# .c 파일을 .o 오브젝트 파일로 만드는 규칙
%.o: %.c quiz.h
	$(CC) $(CFLAGS) -c $< -o $@

# 청소 명령 (make clean 입력 시 빌드 결과물 삭제)
clean:
	rm -f $(OBJS) $(TARGET)
