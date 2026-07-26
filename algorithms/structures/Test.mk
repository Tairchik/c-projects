CC = gcc
CFLAGS = -Wall -Wextra -Werror -I src/vectror

# Имена тестовых бинарников
TEST_STATIC = vector_test_static
TEST_SHARED = vector_test_dynamic

# Исходный файл теста
TEST_SRC = vector_test.c

# По умолчанию собираем оба варианта
all: static dynamic

# --- 1. Сборка со СТАТИЧЕСКОЙ библиотекой ---
static: libvector.a
	$(CC) $(CFLAGS) $(TEST_SRC) libvector.a -o $(TEST_STATIC)
	@echo "Static test built: ./$(TEST_STATIC)"

# --- 2. Сборка с ДИНАМИЧЕСКОЙ библиотекой ---
dynamic: libvector.so
	$(CC) $(CFLAGS) $(TEST_SRC) -L. -lvector -Wl,-rpath,. -o $(TEST_SHARED)
	@echo "Dynamic test built: ./$(TEST_SHARED)"

# --- Правила вызова главного Makefile для сборки библиотек ---
libvector.a:
	$(MAKE) libvector.a SHARED=0

libvector.so:
	$(MAKE) libvector.so SHARED=1

# --- Запуск тестов ---
run_static: static
	./$(TEST_STATIC)

run_dynamic: dynamic
	./$(TEST_SHARED)

run_all: static dynamic
	@echo "=== Running Static Test ==="
	./$(TEST_STATIC)
	@echo "\n=== Running Dynamic Test ==="
	./$(TEST_SHARED)

clean:
	rm -f $(TEST_STATIC) $(TEST_SHARED)

.PHONY: all static dynamic run_static run_dynamic run_all clean