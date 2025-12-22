#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;

typedef struct {
  int capacity;
  int count;
  Value *values;
} ValueArray;

typedef struct {
  int count;
  int lineNumber;
} Line;

typedef struct {
  int count;
  int capacity;
  Line *lines;
} LineArray;

void initLineArray(LineArray *array);
void writeLineArray(LineArray *array, Line line);
void freeLineArray(LineArray *array);
int getLine(LineArray *array, int offset);

void initValueArray(ValueArray *array);
void writeValueArray(ValueArray *array, Value value);
void freeValueArray(ValueArray *array);
void printValue(Value value);

#endif
