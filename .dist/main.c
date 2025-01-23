#include "connectionhandler.h"
#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>

int main(int argc, char **argv) {  // main sollte den Rückgabetyp 'int' haben
    char input[13]; //13byte weil Null-Terminierung

    if (argc < 3) {  // Argumente überprüfen
        printf("Usage: %s <host> <port>\n", argv[0]);
        return 1;
    }
    printf("argv1 %s und argv2 %s",argv[1],argv[2]);
    // Stelle sicher, dass createSocket korrekt funktioniert
    createSocket(argv[2], argv[1]);

    // Benutzereingabe abfragen
    printf("Was wollen Sie machen?\n");
    printf("Eine Webseite anfragen: GET /website  \n");
    printf("Eine PDF anfragen: GET /pdf \n");
    printf("Einen/Ein Text/Bild anfragen: GET /mixed \n");
    printf("Benutzernamen für Server setzen: POST /myname \n");
    printf("Client-Namen des Servers anfragen: GET /myname \n");

    fgets(input, sizeof(input), stdin);
    printf("%s",input);
    printf("Ein deutlich längerer");
    
    return 0;  // main muss einen int-Wert zurückgeben
}
