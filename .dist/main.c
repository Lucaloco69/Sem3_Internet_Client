#include "connectionhandler.h"
#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>
void main (int argc, char **argv){
    createSocket(argv[1],argv[2]);
    //Eine Webseite (GET) b. Eine Pseudo-PDF (GET) c. Text+Bild (Body mit unterschiedliche Daten) (GET) d. 
    //Das Setzen eines bestimmten Nutzernamen Serverseitig für den Cookie (POST) 
    //e. Anfrage des momentanen Serverseitigen Client-Namen (GET)
    printf("Was wollen Sie machen?\n Eine Webseite anfragen: 'A' \n Eine PDF anfragen: 'B' \n Einen/Ein Text/Bild anfragen: 'C' \n Benutzernamen für Server setzen: 'D' \n Client-Namen des Servers anfragen: 'E'");
    char input;
    scanf("%c",input);
    switch (input)
    {
    case 'A':

    case 'B':

    case 'C':

    case 'D':

    case 'E':
        break;
    
    default:
        break;
    }
}