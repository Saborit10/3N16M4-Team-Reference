/* Aumentar la Memoria de la Pila del Sistema
 - func debe ser declarada static (e.g., static void main2)
 - Tested on: http://coj.uci.cu/24h/problem.xhtml?pid=4150 
**/

static void run_with_stack_size(void (*func)(), size_t stsize) {
    char *stack, *send;
    stack = (char *)malloc(stsize);
    send = stack+stsize-16;
    send = (char *)((uintptr_t)send/16*16);
    
    asm volatile(
        "mov %%rsp, (%0)\n"
        "mov %0, %%rsp\n"
        :
        : "r" (send));
    func();
    
    asm volatile(
        "mov (%0), %%rsp\n"
        :
        : "r" (send));
    free(stack);
}

void main2(){
    cout << dfs() << endl;
}

int main(){
  run_with_stack_size(main2, 100 * (1<<20));
}

/*
  Aumentar la memoria de la stack en ubuntu
*/ 

#include <sys/resource.h>
rlimit r;
getrlimit(3, &r);
r.rlim_max = 1<<30;
r.rlim_cur = 1<<30;
setrlimit(3, &r);
