
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <math.h>

typedef double scalar;

typedef struct {
  uint32_t n;  // # of elements
  scalar e[1]; // elements
} vec;

typedef struct {
  uint32_t m, n; // # of rows, # of cols
  scalar e[1];   // elements
} mtx;

vec* new_vec(uint32_t n_elements) {
  void* ptr = malloc(offsetof(vec, e) + n_elements * sizeof(scalar));
  if (!ptr)
    abort();
  vec* v = (vec*)ptr;
  v->n = n_elements;
  return v;
}

mtx* new_mtx(uint32_t m_rows, uint32_t n_cols) {
  void* ptr = malloc(offsetof(vec, e) + m_rows * n_cols * sizeof(scalar));
  if (!ptr)
    abort();
  mtx* m = (mtx*)ptr;
  m->m = m_rows;
  m->n = n_cols;
  return m;
}

vec* vec_add(vec* sum, vec* a, vec* b) {
  assert(a);
  assert(b);
  assert(a->n == b->n);
  if (sum) {
    assert(sum->n == a->n);
  } else {
    sum = new_vec(a->n);
  }
  for (uint32_t i=0; i < a->n; i++) {
    sum->e[i] = a->e[i] + b->e[i];
  }
}

// Dot product.
scalar vec_dotprd(vec* a, vec* b) {
  assert(a);
  assert(b);
  assert(a->n == b->n);
  scalar prd = 0;
  for (uint32_t i=0; i < a->n; i++) {
    prd = fma(a->e[i], b->e[i], prd);
  }
  return prd;
}

// Euclidean norm of a vector.
scalar vec_norm(vec* a) {
  assert(a);
  scalar sumsq = 0;
  for (uint32_t i=0; i < a->n; i++) {
    scalar elt = a->e[i];
    sumsq += elt * elt;
  }
  return sqrt(sumsq);
}

