#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

//we want this buffer to be larger than the other one
#define BUFFER_SIZE 1024+1

void catch_error(int er);
void process(char *s);

char buff[BUFFER_SIZE];
int sucssess;

int main() {
    //open pipe in
    int in_pipe = open("waluigi",O_RDONLY);
    catch_error(in_pipe);

    //pipe open
    //read into buffer
    while(sucssess = read(in_pipe,buff, sizeof(buff)-1) && sucssess != -1) {
        process(buff);
    }
    //error on read
    catch_error(sucssess);

    return 0;
}

void catch_error(int er) {
    if(er == -1) {
        printf("error %d: %s\n",errno ,strerror(errno));
        exit(-1);
    }
}
void process(char *s) {
    //remove newline
    char *p = strchr(s,'\n');
    if(p) {
        *p = '\0';
    }
    int n = strlen(s);

    char tmp[n];
    int i,j,c;
    for(i = 0; i < 1 << n; i++) {
        c = 0;
        for(j = 0; j < n; j++) {
            if(i & (1<<j)) {
                tmp[c++] = s[j];
            }
        }
        tmp[c] = '\0';
        printf("subset %d: %s\n",i+1,tmp);
    }
}
