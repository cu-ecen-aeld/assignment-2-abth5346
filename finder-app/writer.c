/* 
writer.c
By Abel Thomas

Takes in two input arguments which includes 
a file to write to and a string to write the file. 

Sources:
https://www.geeksforgeeks.org/basics-file-handling-c/

*/

#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv){

    //check for 3 arguments
    if(argc != 3){
        syslog(LOG_ERR, "Invalid number of arguments");
        //fprintf(stderr, "Invalid number of arguments");
        return 1;
    }

    char * file_to_write = argv[1];
    char * str_to_write = argv[2];

    //open file with read/write capabilities and overwrites
    FILE *fd = fopen(file_to_write, "w+");

    //open log with user facility
    openlog(NULL, 0, LOG_USER);

    if (fd == NULL) {
        //error

        syslog(LOG_ERR, "Error could not open file");
        fprintf(stderr, "Error could not open file");
        return 1;
    }

    //write to file
    fprintf(fd, "%s", str_to_write);

    //fprintf(stdout, "Writing <%s> to %s", str_to_write, file_to_write);
    
    //log with debug priority to syslog in /ar/log/syslog
    syslog(LOG_DEBUG, "Writing <%s> to %s", str_to_write, file_to_write);
    
    fclose(fd);
    closelog();

}