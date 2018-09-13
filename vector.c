#include "adhocc.h"

vector* new_vector_cap(int cap) {
  vector* v = malloc(sizeof(vector));
  v->data = malloc(cap*sizeof(void*));
  v->cap = cap;
  v->len = 0;
  return v;
}
vector* new_vector() {
  return new_vector_cap(256);
}

void vector_extend(vector* v) {
  if (v->cap < v->len+1) {
    v->data = realloc(v->data, v->cap*2*sizeof(void*));
    v->cap *= 2;
  }
}

void* vector_get(vector* v, int index) {
  return v->data[index];
}
void vector_set(vector* v, int index, void* elem) {
  v->data[index] = elem;
}

void vector_push(vector* v, void* elem) {
  vector_extend(v);
  vector_set(v, v->len++, elem);
}
