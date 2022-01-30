/* See LICENSE file for copyright and license details. */

/*
 * This file is just simple vanilla C functions.
 */

#include "util.hpp"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void die(const char *fmt, ...) {
  va_list arg;

  va_start(arg, fmt);
  vfprintf(stderr, fmt, arg);
  va_end(arg);

  if (fmt[0] && fmt[strlen(fmt) - 1] == ':') {
    fputc(' ', stderr);
    perror(NULL);
  } else {
    fputc('\n', stderr);
  }

  exit(EXIT_FAILURE);
}
