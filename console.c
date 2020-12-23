#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#define OUT_BUFFER_SIZE 1024
//one more than what could come in
#define IN_BUFFER_SIZE 8192+1

void catch_error(int er);

char out_buff[OUT_BUFFER_SIZE];
char in_buff[IN_BUFFER_SIZE];
int sucssess;

int main() {
    //make pipes
    sucssess = mkfifo("waluigi",0644);
    if(errno != EEXIST) catch_error(sucssess);

    sucssess = mkfifo("wario",0644);
    if(errno != EEXIST) catch_error(sucssess);

    //open pipe out
    int out_pipe = open("waluigi",O_WRONLY);
    catch_error(out_pipe);
    //open pipe in
    int in_pipe = open("wario",O_RDONLY);
    catch_error(out_pipe);

    //remove pipes after connection made
    sucssess = remove("wario");
    catch_error(sucssess);
    sucssess = remove("waluigi");
    catch_error(sucssess);

    //pipe open, write stuff
    while(fgets(out_buff, sizeof(out_buff), stdin)) {
        sucssess = write(out_pipe,out_buff,sizeof(out_buff));
        catch_error(sucssess);
        //read and print response
        sucssess = read(in_pipe,in_buff, sizeof(in_buff)-1);
        catch_error(sucssess);
        //in_buff is expected to be a null terminated string
        printf("%s",in_buff);
    }

    return 0;
}

void catch_error(int er) {
    if(er == -1) {
        printf("error %d: %s\n",errno ,strerror(errno));
        exit(-1);
    }
}
