#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/syscall.h"
#include "kernel/memlayout.h"
#include "kernel/riscv.h"

void assert_eq(int left, int right) {
  if (left == right) { return; }

  printf("Assertion Failed! (%d != %d)\n", left, right);
  exit(1);
}

int main(int, char**) {
  int pid = getpid();
  int ret, pgid;

  ret = getpgid(-1);
  assert_eq(ret, -1);
  ret = getpgid(4200000000);
  assert_eq(ret, -1);

  pgid = getpgid(1);
  assert_eq(pgid, 1);

  ret = setpgid(-1, 12345);
  assert_eq(ret, -1);
  ret = setpgid(4200000000, 12345);
  assert_eq(ret, -1);
  ret = setpgid(0, -1);
  assert_eq(ret, -1);

  ret = setpgid(1, 12345);
  assert_eq(ret, 0);
  pgid = getpgid(1);
  assert_eq(pgid, 12345);

  ret = setpgid(1, 0);
  assert_eq(ret, 0);
  pgid = getpgid(1);
  assert_eq(pgid, 1);

  pgid = getpgid(0);
  assert_eq(pgid, 1);

  ret = setpgid(0, 12345);
  assert_eq(ret, 0);
  pgid = getpgid(0);
  assert_eq(pgid, 12345);

  ret = setpgid(0, 0);
  assert_eq(ret, 0);
  pgid = getpgid(0);
  assert_eq(pgid, pid);

  exit(0);
}
