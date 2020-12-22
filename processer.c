#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

//one more than what can come in
#define IN_BUFFER_SIZE 1024+1
#define OUT_BUFFER_SIZE 8192

void catch_error(int er);
void process(char *s);

char in_buff[IN_BUFFER_SIZE];
char out_buff[OUT_BUFFER_SIZE];
int sucssess;

int main() {
    //open pipe in
    int in_pipe = open("waluigi",O_RDONLY);
    catch_error(in_pipe);
    //open pipe out
    int out_pipe = open("wario",O_WRONLY);
    catch_error(out_pipe);

    //pipe open
    //read into buffer
    while(sucssess = read(in_pipe,in_buff, sizeof(in_buff)-1) && sucssess != -1) {
        process(in_buff);
        //write output buffer
        sucssess = write(out_pipe,out_buff,sizeof(out_buff));
        catch_error(sucssess);
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
//stuffs subsets (or as much as will fit) into the output buffer
void process(char *s) {
    //remove newline
    char *p = strchr(s,'\n');
    if(p) {
        *p = '\0';
    }
    int n = strlen(s);

    char tmp[n];
    int i,j;
    int overal_place = 0;;
    for(i = 1; i < 1 << n; i++) {
        for(j = 0; j < n; j++) {
            if(i & (1<<j)) {
                if(overal_place == OUT_BUFFER_SIZE-2){
                    out_buff[overal_place++] = '\n';
                    out_buff[overal_place] = '\0';
                    return;
                }
                out_buff[overal_place++] = s[j];

            }
        }
        if(i != (1 << n) -1 ) {
            if(overal_place == OUT_BUFFER_SIZE-2) {
                out_buff[overal_place++] = '\n';
                out_buff[overal_place] = '\0';
                return;
            }
            out_buff[overal_place++] = ',' ;
        }
    }
    //we know overal_place <= OUT_BUFFER_SIZE-2 as otherwise it would have returned by now
    out_buff[overal_place++] = '\n';
    out_buff[overal_place] = '\0';
}
