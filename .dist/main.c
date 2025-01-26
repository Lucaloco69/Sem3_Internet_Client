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
    responseBuffer=(Message*)malloc(sizeof(Message));
     if (responseBuffer == NULL) {
        perror("Malloc für responseBuffer fehlgeschlagen");
        free(httpReq);
        free(input);
        free(name);
        free(content);
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
    if(firstTime==false){
        char *again;
        printf("Noch eine Request schicken? Y | n\n");
        fgets(again, MSG_MAX, stdin);
        if(again[0]=='n'){
            free(input); 
            free(name); 
            free(httpReq);
            free(responseBuffer);
            free(content); 
            close(fd);
            break;
        }
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
    printf("moin");
    if(responseBuffer->Cookie[0]!='\0'){
    httpReq = prepareRequestWithCookie(input, argv[1], name,responseBuffer->Cookie);
    printf("Noch da1?");
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
        printf("FATAL");
         httpReq = prepareRequest(input, argv[1], name);
    printf("Noch da1?");
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

    if(clientReceive(fd,content)!=1){
        free(input); 
        free(name); 
        free(httpReq);
        free(responseBuffer);
        free(content); 
        exit(EXIT_FAILURE);

    }
    
    content = divideBodyFromHeader(content);
    if(writeIntoFile(content)!=0){
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
