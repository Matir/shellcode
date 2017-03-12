#include <sys/mman.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define SC_LENGTH 1024*1024

int debug_enabled = 0;

void debug(char *fmt, ...) {
  va_list ap;
  if (!debug)
    return;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
}

int main(int argc, char **argv) {
  void *code;
  int r;

  debug_enabled = (getenv("DEBUG") != NULL) ? 1 : 0;
  code = mmap(NULL, SC_LENGTH, PROT_READ|PROT_WRITE|PROT_EXEC,
      MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
  if (code == MAP_FAILED) {
    fprintf(stderr, "Failed to allocate memory for mapping.\n");
    return 1;
  }
  debug("Allocated 0x%08x bytes at %p.  Send shellcode now.\n", SC_LENGTH, code);
  r = read(0, code, SC_LENGTH);
  debug("Read 0x%08x bytes.  Executing.\n", r);
  ((void(*)())code)();
  return 0;
}
