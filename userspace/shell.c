#include <unistd.h>
#include <sys/types.h> // pid_t
#include <sys/wait.h>  // siginfo_t P_ALL WEXITED

int cool_waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options, void *);

void motd()
{
    write(1, "__        __   _                          _ \n", 45);
    write(1, "\\ \\      / /__| | ___ ___  _ __ ___   ___| |\n", 45);
    write(1, " \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ |\n", 45);
    write(1, "  \\ V  V /  __/ | (_| (_) | | | | | |  __/_|\n", 45);
    write(1, "   \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___(_)\n", 45);

    write(1, " _____                  _        ___  ____  \n", 45);
    write(1, "| ____|_ __   ___   ___| |__    / _ \\/ ___| \n", 45);
    write(1, "|  _| | '_ \\ / _ \\ / __| '_ \\  | | | \\___ \\ \n", 45);
    write(1, "| |___| | | | (_) | (__| | | | | |_| |___) |\n", 45);
    write(1, "|_____|_| |_|\\___/ \\___|_| |_|  \\___/|____/ \n", 45);
}

int main()
{
    motd();
    char command[255];
    char *tip = "EnochOS -> # ";
    size_t tipLen = 13;
    for (;;)
    {
        write(1, tip, tipLen);
        int count = read(0, command, 255);
        command[count - 1] = 0; // 替换掉command结尾的\n变成\0
        pid_t fork_result = fork();
        if (fork_result == 0)
        {
            execve(command, 0, 0);
            break;
        }
        else
        {
            siginfo_t info;
            // int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);
            /* This is the glibc and POSIX interface; see VERSIONS for information on the raw system call. */
            // 等待所有进程都退出了再进行下一次shell
            cool_waitid(P_ALL, 0, &info, WEXITED, 0);
            // waitid(P_ALL, 0, &info, WEXITED); // 使用GNU库进行静态链接
        }
    }
    _exit(0);
}
