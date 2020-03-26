#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <stdio.h>
#include <string.h>

/*
 * long ptrace(enum __ptrace_request request, pid_t pid,
 *                    void *addr, void *data);
 */

int main()
{
    pid_t child;
    child = fork();
    if(child == 0)
    {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("/bin/ls", "ls", "-la", NULL);
    }
    else
    {
        wait(NULL);
        long rax_reg_value = ptrace(PTRACE_PEEKUSER,
                                    child,
                                    8 * ORIG_RAX,
                                    NULL);
        printf("The child made a "
               "system call %ld\n", rax_reg_value);
        ptrace(PTRACE_CONT, child, NULL, NULL);
    }
    return 0;
}
