#include <stdint.h>
#include <stdlib.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  initLineArray(&chunk->lines);
  chunk->code = NULL;
  initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
  if (chunk->capacity <= chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
  }

  if (chunk->count != 0 && chunk->code[chunk->count] == chunk->code[chunk->count - 1]) {
    chunk->lines.lines[chunk->lines.count - 1].count++;
  } else {
    writeLineArray(&chunk->lines, (Line){1, line});
  }

  chunk->code[chunk->count] = byte;
  chunk->count++;
}

void freeChunk(Chunk* chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  freeLineArray(&chunk->lines);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

int addConstant(Chunk *chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

void writeConstant(Chunk *chunk, Value value, int line) {
  int address = addConstant(chunk, value);
  if (address > 255) {
    writeChunk(chunk, OP_CONSTANT_LONG, line);
    writeChunk(chunk, (address >> 16) & 0xFF, line);
    writeChunk(chunk, (address >> 8) & 0xFF, line);
    writeChunk(chunk, address & 0xFF, line);
  } else {
    writeChunk(chunk, OP_CONSTANT, line);
    writeChunk(chunk, address, line);
  }
}
