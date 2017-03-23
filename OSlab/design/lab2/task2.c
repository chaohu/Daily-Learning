#include <syscall.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    syscall(326,"task.c","dest.c");
    return 0;
}
