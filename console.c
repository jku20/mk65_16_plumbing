#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

void catch_error(int er);

char buff[BUFFER_SIZE];
int sucssess;

int main() {
    //make pipe
    sucssess = mkfifo("waluigi",0644);
    if(errno != EEXIST) catch_error(sucssess);

    //open pipe out
    int out_pipe = open("waluigi",O_WRONLY);
    catch_error(out_pipe);

    //pipe open, write stuff
    while(fgets(buff, sizeof(buff), stdin)) {
        sucssess = write(out_pipe,buff,sizeof(buff));
        catch_error(sucssess);
    }

    return 0;
}

void catch_error(int er) {
    if(er == -1) {
        printf("error %d: %s\n",errno ,strerror(errno));
        exit(-1);
    }
}
