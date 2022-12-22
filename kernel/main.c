#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"

static volatile int started = 0;

// start() jumps here in supervisor mode on all CPUs.
void
main()
{
  if(cpuid() == 0){
    consoleinit();
    printfinit();

    // Practice 1: Modify the xv6 kernel source code so that it prints your
    // student ID and your name during booting. *Please be creative when you
    // print them!*
    printf(
        "\n"
        "xv6 kernel is booting... 👀\n"
        "\n"
        "     ---------\n"
        "    | Hyeon K |\n"
        "     ---------\n"
        "           ||\n"
        "    (\\__/) ||\n"
        "    (•ㅅ•) ||\n"
        "🍆  / 　 づ   🥕🥕\n"
        "\n");

    kinit();         // physical page allocator
    kvminit();       // create kernel page table
    kvminithart();   // turn on paging
    procinit();      // process table
    trapinit();      // trap vectors
    trapinithart();  // install kernel trap vector
    plicinit();      // set up interrupt controller
    plicinithart();  // ask PLIC for device interrupts
    binit();         // buffer cache
    iinit();         // inode table
    fileinit();      // file table
    virtio_disk_init(); // emulated hard disk
    userinit();      // first user process
    __sync_synchronize();
    started = 1;
  } else {
    while(started == 0)
      ;
    __sync_synchronize();
    printf("hart %d starting\n", cpuid());
    kvminithart();    // turn on paging
    trapinithart();   // install kernel trap vector
    plicinithart();   // ask PLIC for device interrupts
  }

  scheduler();        
}
