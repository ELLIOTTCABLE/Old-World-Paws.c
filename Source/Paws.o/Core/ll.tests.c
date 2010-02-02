#include "ll.c"

#include <stdbool.h>

#ifndef CEST_H_INCLUDED
#  include "Cest.h"
#endif

bool ll__test_create  (void);
bool ll__test_anterior_insert   (void);
bool ll__test_posterior_insert  (void);
bool ll__test_prefix  (void);
bool ll__test_affix   (void);
bool ll__test_at      (void);

static const int LL_tests_length = 6;
bool (*const LL_tests[])(void) = {
  ll__test_create,
  ll__test_anterior_insert,
  ll__test_posterior_insert,
  ll__test_prefix,
  ll__test_affix,
  ll__test_at
};

bool ll__test_create(void) {
  return true;
}

bool ll__test_anterior_insert(void) {
  return true;
}

bool ll__test_posterior_insert(void) {
  return true;
}

bool ll__test_prefix(void) {
  return true;
}

bool ll__test_affix(void) {
  return true;
}

bool ll__test_at(void) {
  return true;
}
