
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int spifd = open("/dev/spiaos", O_RDWR);
    if(spifd < 0) return 1;
    for(;;)
    {
        puts("Ready");
        char line[32];
        fgets(line, 32, stdin);
        line[strcspn(line, "\n")] = 0;
        write(spifd, line, strlen(line));
    }
    return 0;
}
