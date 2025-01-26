#include "connectionhandler.h"
#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>
#include <string.h> 
#include <stdbool.h>
#include "network.h"
#define MSG_MAX 2097152
#include "message.h"
bool cookie=true;
bool firstTime=true;

int main(int argc, char **argv) {
    while(1){
    char *httpReq = (char *)malloc(MSG_MAX * sizeof(char));
     if (httpReq == NULL) {
        perror("Malloc für input fehlgeschlagen");
        free(httpReq);
        exit(EXIT_FAILURE);
    }

    char *input = (char *)malloc(MSG_MAX * sizeof(char));
     if (input == NULL) {
        perror("Malloc für input fehlgeschlagen");
        free(input);
        exit(EXIT_FAILURE);
    }
  
    char *name = (char *)malloc(MSG_MAX * sizeof(char));
    if (name == NULL) {
        perror("Malloc für name fehlgeschlagen");
        free(name);
        exit(EXIT_FAILURE);
    }

    char *content = (char *)malloc(MSG_MAX * sizeof(char));
    if (content == NULL) {
        perror("Malloc für file fehlgeschlagen");
        free(content);
        exit(EXIT_FAILURE);
    }
    


    if (argc > 3) {
        printf("Zu viele Argumente\n");
        free(input); 
        free(name);   
        return 1;
    }

    int fd = createSocket(argv[2], argv[1]);
    if (fd < 0) {
        perror("Fehler beim Erstellen des Sockets");
        free(input);
        free(name);  
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
        close(fd);
        exit(EXIT_FAILURE);
    }
    if (store == 1) {
        printf("Geben Sie den Benutzernamen an:");
        fgets(name, MSG_MAX, stdin);  
        cookie=true;
    }
    if(cookie==false){
    httpReq = prepareRequest(input, argv[1], name);
    printf("Noch da1?");
    if (httpReq == NULL) {
        perror("Fehler beim Vorbereiten der Anfrage");
        free(input);
        free(name);
        close(fd);
        exit(EXIT_FAILURE);
    }
    }else{
         httpReq = prepareRequest(input, argv[1], name);
    printf("Noch da1?");
    if (httpReq == NULL) {
        perror("Fehler beim Vorbereiten der Anfrage");
        free(input);
        free(name);
        close(fd);
        exit(EXIT_FAILURE);
    }

    }
    

    clientSend(fd, httpReq);
    printf("Noch da2?");
    clientReceive(fd,content);
    printf("Noch da3?");
    content = divideBodyFromHeader(content);
    writeIntoFile(content);

   
    firstTime=false;
    }

    return 0;
}
