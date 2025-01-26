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

char *divideBodyFromHeader(char *str);


char * prepareRequest(char *input,char *hostName,char* userName){
     char *msg = (char *)malloc(MSG_MAX * sizeof(char));
     if (msg == NULL) {
        perror("Fehler bei der Speicherzuweisung für msg");
        return NULL;
     }

        if(strncmp(input+4,"/myname",7)==0){ //GET-Requests
            snprintf(msg,MSG_MAX,"GET /myname HTTP/1.1\r\nHost: LAyerServer\r\nContent-Length: 0\r\nContent-Type: text/html; charset=UTF-8\r\nReferer: http://%s.com\r\nConnection: close\r\n\r\n",(char*)hostName);
            printf("%s",msg);
            return msg;
        }

        if(strncmp(input+4,"/mixed",6)==0){
            snprintf(msg,MSG_MAX,"GET /mixed HTTP/1.1\r\nHost: LAyerServer\r\nContent-Length: 0\r\nContent-Type: text/html; charset=UTF-8\r\nReferer: http://%s.com\r\nConnection: close\r\n\r\n",(char*)hostName);
            printf("%s",msg);
            printf("Hallo");
            return msg;
        }

        if(strncmp(input+4,"/pdf",4)==0){
            snprintf(msg,MSG_MAX,"GET /pdf HTTP/1.1\r\nHost: LAyerServer\r\nContent-Length: 0\r\nContent-Type: text/html; charset=UTF-8\r\nReferer: http://%s.com\r\nConnection: close\r\n",(char*)hostName);
            printf("%s",msg);
            return msg;

        }

        if(strncmp(input+4,"/website",8)==0){
            snprintf(msg,MSG_MAX,"GET /website HTTP/1.1\r\nHost: LAyerServer\r\nContent-Length: 0\r\nContent-Type: text/html; charset=UTF-8\r\nReferer: http://%s.com\r\nConnection: close\r\n",(char*)hostName);
            printf("%s",msg);
            return msg;

        }

        if(strncmp(input+5,"/myname",7)==0 && hostName[0]!='\0'){ //POST-Request
        snprintf(msg,MSG_MAX,"POST /myname HTTP/1.1\r\nHost: LAyerServer\r\nContent-Length: %ld\r\nContent-Type: application/json\r\nReferer: http://%s.com\r\nConnection: close\r\n\r\nusername:%s",strlen(userName),(char*)hostName,(char*)userName);
            printf("Hier funzt noch alles");
            printf("%s",msg);
            printf("Hallo?");
            return msg;

        }
        free(msg);
    
    return NULL;

} 

int evaluateInput(char *input){
   
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
            return 1;

        }
    
    }
    return -1;
}


char *divideBodyFromHeader(char *str)
{
    
    for(int i = 0; i < strlen(str); i++)
    {

        if(*(str + i) == 13 && *(str + i + 1) == 10 && *(str + i + 2) == 13 && *(str + i + 3) == 10)
        {
            *(str + i + 2) = 0;

            return (str + i +  4);
        } 
    } 

    return NULL;

} 

int writeIntoFile(char *body, Message *responseBuffer){
    FILE *file;
    file = NULL;
    printf("hi");
    printf("%s",responseBuffer->contentType);
    if(strcmp(responseBuffer->contentType," text/html")==0 || strcmp(responseBuffer->contentType," text/plain")==0){
        file = fopen("requestedData.txt", "w");
    }

    if(strcmp(responseBuffer->contentType," application/pdf")==0){
         file = fopen("requestedData.pdf", "w");
    
    }

    if(strcmp(responseBuffer->contentType," multipart/form-data; boundary=--------------------------104850386028541947603269")==0){
        
    }


    printf("\nIn writeIntoFile:\n %s\n",body);

    if (file == NULL) {
        printf("Fehler beim Öffnen der Datei");
        return 1;
    }
    printf("Länge des Body %ld", strlen(body));
    ssize_t outcome=fwrite(body, sizeof(char), strlen(body), file);
      
    if (outcome != strlen(body)) {
        perror("Fehler beim Schreiben in die Datei");
        fclose(file);
        return 1;
    }

    printf("\nEine Datei mit den angeforderten Daten wurde erfolgreich erstellt\n");
    fclose(file);
    return 0;

}

char * prepareRequestWithCookie(char *input,char *hostName,char* userName,char* cookie){
     char *msg = (char *)malloc(MSG_MAX * sizeof(char));
     if (msg == NULL) {
        perror("Fehler bei der Speicherzuweisung für msg");
        return NULL;
     }

        if(strncmp(input+4,"/myname",7)==0){ 
            snprintf(msg,MSG_MAX,"GET /myname HTTP/1.1\r\nHost: LAyerServer\r\nContent-Length: 0\r\nContent-Type: text/html; charset=UTF-8\r\nReferer: http://%s.com\r\nConnection: close\r\nCooke: %s\r\n\r\n",(char*)hostName,(char*)cookie);
            printf("%s",msg);
            return msg;
        }

        if(strncmp(input+4,"/mixed",6)==0){
            snprintf(msg,MSG_MAX,"GET /mixed HTTP/1.1\r\nHost: LAyerServer\r\nContent-Length: 0\r\nContent-Type: text/html; charset=UTF-8\r\nReferer: http://%s.com\r\nConnection: close\r\nCookie: %s\r\n\r\n",(char*)hostName,(char*)cookie);
            printf("%s",msg);
            return msg;
        }

        if(strncmp(input+4,"/pdf",4)==0){
            snprintf(msg,MSG_MAX,"GET /pdf HTTP/1.1\r\nHost: LAyerServer\r\nContent-Length: 0\r\nContent-Type: text/html; charset=UTF-8\r\nReferer: http://%s.com\r\nConnection: close\r\nCookie: %s\r\n\r\n",(char*)hostName,(char*)cookie);
            printf("%s",msg);
            return msg;

        }

        if(strncmp(input+4,"/website",8)==0){
            snprintf(msg,MSG_MAX,"GET /website HTTP/1.1\r\nHost: LAyerServer\r\nContent-Length: 0\r\nContent-Type: text/html; charset=UTF-8\r\nReferer: http://%s.com\r\nConnection: close\r\nCookie: %s\r\n\r\n",(char*)hostName,(char*)cookie);
            printf("%s",msg);
            return msg;

        }

        if(strncmp(input+5,"/myname",7)==0 && hostName[0]!='\0'){ //POST-Request
        snprintf(msg,MSG_MAX,"POST /myname HTTP/1.1\r\nHost: LAyerServer\r\nContent-Length: %ld\r\nContent-Type: application/json\r\nReferer: http://%s.com\r\nConnection: close\r\nCookie: %s\r\n\r\nusername:%s",strlen(userName),hostName,userName,(char*)cookie);
            printf("Hier funzt noch alles");
            printf("%s",msg);
            printf("Hallo?");
            return msg;

        }
        free(msg);
    
    return NULL;

}

int getHeadersFromRequest(Message *buffer, char *strBuf, int maxHeaders)
{
    printf("In getHeadersFromRequest\n");
    char httpStr[MSG_MAX];

    strcpy(httpStr, strBuf); 

    char *headerlines[maxHeaders];

    //strcpy(httpStr, strBuf); 
    char *firstLine = strtok(httpStr, "\r\n");

    for(int i = 0; i < maxHeaders; i++)
    {
        printf(" First for  %d\n",i);
        
        char *headerLine = strtok(NULL, "\r\n");

        headerlines[i] = headerLine;
        printf("\nheaderline: %s\n",headerlines[i]);
    }

    for(int i = 0; i < maxHeaders; i++)
    {
        //infoPrint("Die %d. Zeile: %s", i, headerlines[i] );

        char *key = strtok(headerlines[i], ":");

        if(key == NULL)
        {
            break;
        } 

        char *value = strtok(NULL, "\r\n");
        printf("\nKey: %s",key);

        if(strcmp(key, "Content-Length") == 0)
        {

            buffer->contentLength = atoi(value);
        } 

        else if(strcmp(key, "Content-Type") == 0)
        {
            strncpy(buffer->contentType, value, 511);
            buffer->contentType[strlen(value)] = 0; 
            printf("\nIn Alessio: %s\n",buffer->contentType);
        } 

        else if(strcmp(key, "Set-Cookie") == 0)
        {
            char *val = strtok(value, "=");

            val = strtok(NULL, ";");

            strncpy(buffer->Cookie,val,strlen(val));//Da val ein char pointer und Cookie ein char []
            buffer->Cookie[sizeof(buffer->Cookie) - 1] = '\0';
        }  
    }

} 



