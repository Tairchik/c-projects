#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "sort.h"

#define CHECK_SORTED(arr, size)                                                \
    do {                                                                       \
        int _is_sorted = 1;                                                \
        int _bad_idx = -1;                                                     \
        for (int _i = 0; _i < (size) - 1; _i++) {                              \
            if ((arr)[_i] > (arr)[_i + 1]) {                                   \
                _is_sorted = 0;                                            \
                _bad_idx = _i;                                                 \
                break;                                                         \
            }                                                                  \
        }                                                                      \
        if (_is_sorted == 1) {                                                      \
            printf("[OK] %s:%d: Array is correctly sorted!\n",                 \
                   __FILE__, __LINE__);                                        \
        } else {                                                               \
            fprintf(stderr,                                                    \
                    "[FAIL] %s:%d: Array is NOT sorted! First error at index " \
                    "%d: (%d > %d)\n",                                         \
                    __FILE__, __LINE__, _bad_idx, (arr)[_bad_idx],             \
                    (arr)[_bad_idx + 1]);                                      \
        }                                                                      \
    } while (0)

#define DEFFSIZE 1000

#define SORTARR 0
#define RANDARR 1
#define REVSARR 2

#define TYPES 3

typedef struct
{
    int *arr;
    int size;
    double result_time;
} SortTask;

int *generateSortArray(int size)
{
    int *array = malloc(size * sizeof(int));

    if (!array)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++)
        array[i] = i + 1;

    return array;
}

int *generateReversSortArray(int size)
{
    int *array = malloc(size * sizeof(int));

    if (!array)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++)
        array[i] = size - i;

    return array;
}

int *generateRandomArray(int size)
{
    int *array = malloc(size * sizeof(int));
    if (!array)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    for (int i = 0; i < size; i++)
    {
        array[i] = rand() % size + 1;
    }

    return array;
}

clock_t makeSort(int *arr, int size)
{
    clock_t start, end;

    start = clock();
    sort(arr, size);
    end = clock();

    return end - start;
}

void *thread_worker(void *arg)
{
    struct timespec start, end;
    SortTask *task = (SortTask *)arg;

    clock_gettime(CLOCK_MONOTONIC, &start);
    sort(task->arr, task->size);
    clock_gettime(CLOCK_MONOTONIC, &end);

    task->result_time = (end.tv_sec - start.tv_sec) + 
                        (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int size = DEFFSIZE;

    if (argc == 2)
    {
        size = atoi(argv[1]);
        if (size <= 0)
        {
            fprintf(stderr, "Uncorrect format. Format: ./%s [size]\n\t OR\n./%s", argv[0], argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    int *array[TYPES];

    // Генерация массивов
    array[SORTARR] = generateSortArray(size);
    array[RANDARR] = generateRandomArray(size);
    array[REVSARR] = generateReversSortArray(size);

    // Создаем потоки и задачи для них
    pthread_t threads[TYPES];
    SortTask tasks[TYPES];

    for (int i = 0; i < TYPES; i++)
    {
        tasks[i].arr = array[i];
        tasks[i].size = size;
        tasks[i].result_time = 0;

        pthread_create(&threads[i], NULL, thread_worker, &tasks[i]);
    }

    for (int i = 0; i < TYPES; i++)
        pthread_join(threads[i], NULL);
    
    printf("\nName: %s\n", &argv[0][2]);

    printf("============Sort Array============\n");
    printf("\tSize: %d\n\tTime: %lf (sec)\n", size, tasks[SORTARR].result_time);
    printf("==================================\n");

    printf("===========Revers Array===========\n");
    printf("\tSize: %d\n\tTime: %lf (sec)\n", size, tasks[REVSARR].result_time);
    printf("==================================\n");

    printf("===========Random Array===========\n");
    printf("\tSize: %d\n\tTime: %lf (sec)\n", size, tasks[RANDARR].result_time);
    printf("==================================\n");

        
#ifdef ENABLE_TESTS
    printf("\n============ Running Tests ================\n");
    CHECK_SORTED(tasks[SORTARR].arr, size);
    CHECK_SORTED(tasks[REVSARR].arr, size);
    CHECK_SORTED(tasks[RANDARR].arr, size);
    printf("===========================================\n\n");
#endif

    for (int i = 0; i < TYPES; i++)
        free(tasks[i].arr);

    return 0;
}