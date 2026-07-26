#ifndef VECTOR_INTERNAL_H
#define VECTOR_INTERNAL_H

#include "vector.h"

struct Vector {
    uint8_t *data;      // Указатель на данные
    size_t length;      // Количество элементов
    size_t capacity;    // Емкость буфера
    size_t elem_size;   // Размер одного элемента
};

#endif