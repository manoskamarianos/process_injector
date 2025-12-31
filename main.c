#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {

    int ret_val = 0;

    if (argc != 4) {
        perror("Usage: ./process_injector <target_pid> <memory_addr> <payload>");
        ret_val = 1;
        goto out;
    }

    int pid = atoi(argv[1]);
    long address = strtol(argv[2], NULL, 0);
    char *path = argv[3];

    int fd = open(path, O_RDONLY);

    ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    wait(NULL);

    char tmp;

    for (size_t i = 0; i < 1000; i++) 
    {
        if (read(fd, &tmp, 1))
            ptrace(PTRACE_POKETEXT, pid, address + i, "A");
    }

out:
    return ret_val;
}
