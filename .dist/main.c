#include "connectionhandler.h"
#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>
enum { MSG_MAX = 2097152};
#include "message.h"

int main(int argc, char **argv) {  // main sollte den Rückgabetyp 'int' haben
    char *input=(char *)malloc(MSG_MAX * sizeof(char)); //13byte weil Null-Terminierung
    char *name=(char *)malloc(MSG_MAX * sizeof(char));
    input[strlen(argv[1]+strlen(argv[2]))]='\0';
    name=argv[3];
    name[strlen(argv[3])]='\0';
    if (strncmp(argv[1],"GET",sizeof(argv[1]))) {  // Argumente überprüfen
        if(argc>3){
            printf("Zu viele Argumente für GET-Request");
            return 1;
            
        }   
    }
    
    printf("argv1 %s und argv2 %s",argv[1],argv[2]);
    // Stelle sicher, dass createSocket korrekt funktioniert
    int fd =createSocket(argv[2], argv[1]);

    // Benutzereingabe abfragen
    printf("Was wollen Sie machen?\n");
    printf("Eine Webseite anfragen: GET /website  \n");
    printf("Eine PDF anfragen: GET /pdf \n");
    printf("Einen/Ein Text/Bild anfragen: GET /mixed \n");
    printf("Benutzernamen für Server setzen: POST /myname \n");
    printf("Client-Namen des Servers anfragen: GET /myname \n");

    fgets(input, sizeof(input), stdin);//fgets:Da scanf nur bis zum ersten Leerzeichen 
    if(evaluateInput(input)==-1){
        perror("Falsche Eingabe");
        close(fd);
        exit(EXIT_FAILURE);

    }
    char *httpReq = (char *)malloc(MSG_MAX * sizeof(char));
    httpReq = prepareRequest(input,argv[1],name);

    free(input);
    free(name);
    free(httpReq);
    return 0;
}


