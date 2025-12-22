#include "value.h"
#include "memory.h"
#include <stdio.h>


void initValueArray(ValueArray *array) {
  array->capacity = 0;
  array->count = 0;
  array->values = NULL;
}

void writeValueArray(ValueArray *array, Value value) {
  if (array->capacity < array->count + 1) {
    int oldCapacity = array->capacity;
    array->capacity = GROW_CAPACITY(oldCapacity);
    array->values = GROW_ARRAY(Value, array->values, oldCapacity, array->capacity);
  }

  array->values[array->count] = value;
  array->count++;
}

void freeValueArray(ValueArray* array) {
  FREE_ARRAY(Value, array->values, array->capacity);
  initValueArray(array);
}

void printValue(Value value) {
  printf("%g", value);
}

void initLineArray(LineArray* array) {
  array->count = 0;
  array->capacity = 0;
  array->lines = NULL;
}

void writeLineArray(LineArray* array, Line line) {
  if (array->capacity < array->count + 1) {
    int oldCapacity = array->capacity;
    array->capacity = GROW_CAPACITY(oldCapacity);
    array->lines = GROW_ARRAY(Line, array->lines, oldCapacity, array->capacity);
  }

  array->lines[array->count] = line;
  array->count++;
}

void freeLineArray(LineArray* array) {
  FREE_ARRAY(Line, array->lines, array->capacity);
  initLineArray(array);
}

int getLine(LineArray* array, int offset) {
  int runningCount = 0;

  for (int i = 0; i < array->count; i++) {
    runningCount += array->lines[i].count;
    if (offset < runningCount) return array->lines[i].lineNumber;
  }
  printf("Error: Invalid offset in getLine.\n");
  return -1;
}
