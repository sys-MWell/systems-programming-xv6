#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_fork(void) {
    return fork();
}

int sys_exit(void) {
    exit();
    return 0;  // not reached
}

int sys_wait(void) {
    return wait();
}

int sys_kill(void) {
    int pid;

    if (argint(0, &pid) < 0) {
        return -1;
    }
    return kill(pid);
}

int sys_getpid(void) {
    return myproc()->pid;
}

int sys_sbrk(void) {
    int addr;
    int n;

    if (argint(0, &n) < 0) {
        return -1;
    }
    addr = myproc()->sz;
    if (growproc(n) < 0) {
        return -1;
    }
    return addr;
}

int sys_sleep(void) {
    int n;
    uint ticks0;

    if (argint(0, &n) < 0) {
        return -1;
    }
    acquire(&tickslock);
    ticks0 = ticks;
    while (ticks - ticks0 < n) {
        if (myproc()->killed) {
            release(&tickslock);
            return -1;
        }
        sleep(&ticks, &tickslock);
    }
    release(&tickslock);
    return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void) {
    uint xticks;

    acquire(&tickslock);
    xticks = ticks;
    release(&tickslock);
    return xticks;
}

// Shutdown Xv6 and stops Qemu
int sys_shutdown(void) {
    int restart;
    argint(0, &restart);
    
    if (restart == 0){
        outw(0x604, 0x2000); //shutdown
    }
    else if (restart == 1)
    {
        unsigned char good = 0x02; 
        while (good & 0x02) { 
            good = inb(0x64); 
        } 
        outb(0x64, 0xFE);    //restart
    }
    
    
    outw(0x604, 0x2000); //shutdown
    return 0;
}