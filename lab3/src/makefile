# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Исходные файлы
SOURCES = parallel_min_max.c sequential_min_max.c find_min_max.c utils.c launch_sequential.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLES = parallel_min_max sequential_min_max launch_sequential

# Цель по умолчанию
all: $(EXECUTABLES)

# Основные программы
parallel_min_max: parallel_min_max.o find_min_max.o utils.o
	$(CC) $^ -o $@

sequential_min_max: sequential_min_max.o find_min_max.o utils.o
	$(CC) $^ -o $@

# Программа для запуска через exec
launch_sequential: launch_sequential.o
	$(CC) $^ -o $@

# Компиляция объектных файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJECTS) $(EXECUTABLES) *.txt

# Пересборка
rebuild: clean all

# Тесты
test_parallel: parallel_min_max
	@echo "=== Testing parallel version ==="
	./parallel_min_max --seed 123 --array_size 1000000 --pnum 4

test_sequential: sequential_min_max
	@echo "=== Testing sequential version ==="
	./sequential_min_max 1000000 123

test_exec: sequential_min_max launch_sequential
	@echo "=== Testing exec launch ==="
	./launch_sequential 1000000 123

test_exec_demo: sequential_min_max launch_sequential
	@echo "=== Demo of exec functionality ==="
	@echo "1. First, run sequential_min_max directly:"
	./sequential_min_max 500000 42
	@echo ""
	@echo "2. Now run through exec launcher:"
	./launch_sequential 500000 42

# Специальные цели
.PHONY: all clean rebuild test_parallel test_sequential test_exec test_exec_demo