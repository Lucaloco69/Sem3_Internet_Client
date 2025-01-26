#include "connectionhandler.h"
#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>
#include <string.h> 
#include <stdbool.h>
#include "network.h"
#define MSG_MAX 2097152
#include "message.h"
bool firstTime=true;

int main(int argc, char **argv) {
    Message  *responseBuffer = (Message*)malloc(sizeof(Message));
     if (responseBuffer == NULL) {
        perror("Malloc für responseBuffer fehlgeschlagen");
        // free(httpReq);
        // free(input);
        // free(name);
        // free(content);
        exit(EXIT_FAILURE);
    }

    while(1){
    char *httpReq = (char *)malloc(MSG_MAX * sizeof(char));
     if (httpReq == NULL) {
        perror("Malloc für httpReq fehlgeschlagen");
        exit(EXIT_FAILURE);
    }

    char *input = (char *)malloc(MSG_MAX * sizeof(char));
     if (input == NULL) {
        perror("Malloc für input fehlgeschlagen");
        free(httpReq);
        exit(EXIT_FAILURE);
    }
  
    char *name = (char *)malloc(MSG_MAX * sizeof(char));
    if (name == NULL) {
        perror("Malloc für name fehlgeschlagen");
        free(httpReq);
        free(input);
        exit(EXIT_FAILURE);
    }

    char *content = (char *)malloc(MSG_MAX * sizeof(char));
    if (content == NULL) {
        perror("Malloc für content fehlgeschlagen");
        free(httpReq);
        free(input);
        free(name);
        exit(EXIT_FAILURE);
    }

    


    if (argc > 3) {
        printf("Zu viele Argumente\n");
        free(input); 
        free(name); 
        free(httpReq);
        free(responseBuffer);
        free(content);  
        return 1;
    }

    if(firstTime==false){
    char again[10] ;
    printf("Noch eine Request schicken? Y | n\n");
    fgets(again, MSG_MAX, stdin);

    if(strcmp(again ,"n") == 0){
        free(input); 
        free(name); 
        free(httpReq);
        free(responseBuffer);
        free(content); 
        break;
    }
    }

    int fd = createSocket(argv[2], argv[1]);
    if (fd < 0) {
        perror("Fehler beim Erstellen des Sockets");
        free(input); 
        free(name); 
        free(httpReq);
        free(responseBuffer);
        free(content);   
        return 1;
    }

    printf("Was wollen Sie machen?\n");
    printf("Eine Webseite anfragen: GET /website\n");
    printf("Eine PDF anfragen: GET /pdf\n");
    printf("Einen/Ein Text/Bild anfragen: GET /mixed\n");
    printf("Benutzernamen für Server setzen: POST /myname\n");
    printf("Client-Namen des Servers anfragen: GET /myname\n");

    fgets(input, MSG_MAX, stdin);
    int store = evaluateInput(input);
    if (store == -1) {
        perror("Falsche Eingabe");
        free(input); 
        free(name); 
        free(httpReq);
        free(responseBuffer);
        free(content); 
        close(fd);
        exit(EXIT_FAILURE);
    }
    if (store == 1) {
        printf("Geben Sie den Benutzernamen an:");
        fgets(name, MSG_MAX, stdin);  
    }
    if(firstTime == false){
    httpReq = prepareRequestWithCookie(input, argv[1], name,responseBuffer->Cookie);
    if (httpReq == NULL) {
        perror("Fehler beim Vorbereiten der Anfrage");
        free(input); 
        free(name); 
        free(httpReq);
        free(responseBuffer);
        free(content); 
        close(fd);
        exit(EXIT_FAILURE);
    }
    }else{
       
         httpReq = prepareRequest(input, argv[1], name);
    if (httpReq == NULL) {
        perror("Fehler beim Vorbereiten der Anfrage");
        free(input); 
        free(name); 
        free(httpReq);
        free(responseBuffer);
        free(content); 
        close(fd);
        exit(EXIT_FAILURE);
    }

    }
    
    if(clientSend(fd, httpReq)!=0){
        free(input); 
        free(name); 
        free(httpReq);
        free(responseBuffer);
        free(content); 
        exit(EXIT_FAILURE);

    }

    char *rcvResult = clientReceive(fd,content, responseBuffer);
    if(rcvResult == NULL){
        free(input); 
        free(name); 
        free(httpReq);
        free(responseBuffer);
        free(content); 
        exit(EXIT_FAILURE);

    }
    char* image;
    char* text;
    if(strcmp(responseBuffer->contentType," multipart/form-data; boundary=--------------------------104850386028541947603269")==0){
        splitIntoImgAndText(rcvResult,image,text);
    }
    
    if(writeIntoFile(rcvResult, responseBuffer,image,text)!=0){
        free(input); 
        free(name); 
        free(httpReq);
        free(responseBuffer);
        free(content); 
        exit(EXIT_FAILURE);
    }

   
    firstTime=false;
    }

    return 0;
}
