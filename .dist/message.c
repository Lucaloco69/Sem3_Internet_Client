#include "network.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <netinet/in.h>
#include <stdbool.h>
#include "message.h"
#include <stdio.h>
#define MSG_MAX 1000

int prepareRequest(char input [13],char *hostName){
char msg[MSG_MAX];

        if(strncmp(input+4,"/myname",7)==0){ //GET-Requests
            snprintf(msg,MSG_MAX,"GET /myname HTTP/1.1\r\nHost: %s\r\nContent-Length: 0\r\nContent-Type: text/html; charset=UTF-8\r\nReferer:???\r\nConnection: close\r\nCookie: username=guest\r\n\r\n",(char*)hostName);
            printf("%s",msg);
            return 0;
        }

        if(strncmp(input+4,"/mixed",6)==0){
            return 0;
        }

        if(strncmp(input+4,"/pdf",4)==0){
            return 0;

        }

        if(strncmp(input+4,"/website",8)==0){
            return 0;

        }

    


        if(strncmp(input+5,"/myname",7)==0){ //POST-Request
            return 0;

        }
    
    return 0;

} 

int evaluateInput(char input [13]){

    if(strncmp(input,"GET",(long unsigned int)3) == 0 && strncmp(input+3," ",(long unsigned int)1) == 0){
        if(strncmp(input+4,"/myname",(long unsigned int)7)==0){
            return 0;
        }

        if(strncmp(input+4,"/mixed",(long unsigned int)6)==0){
            return 0;
        }

        if(strncmp(input+4,"/pdf",(long unsigned int)4)==0){
            return 0;

        }

        if(strncmp(input+4,"/website",(long unsigned int)8)==0){
            return 0;

        }

    }

    if(strncmp(input+4," ",(long unsigned int)1) == 0){

        if(strncmp(input+5,"/myname",(long unsigned int)7)==0){
            return 0;

        }
    
    }
    return -1;
}


