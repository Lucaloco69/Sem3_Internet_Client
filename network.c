#include <errno.h>
#include "network.h"
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include "message.h"

//Return Pointer to Body of Response or NULL
char *clientReceive(int fd, char *buffer, Message *responseBuffer)
{  
	ssize_t bytes_read;

	bytes_read = read(fd, buffer, MSG_MAX);
    printf("%s",buffer);

	if(bytes_read > 0) {
        //TEST
        char *body = divideBodyFromHeader(buffer);

        getHeadersFromRequest(responseBuffer,buffer,10);
		return body;
	}
	else if (bytes_read == 0) {
        printf("Fehler beim empfangen der Daten");
		return NULL;

	}
     printf("Fehler beim empfangen der Daten");

	return NULL;
}


int clientSend(int fd, char *buffer) {
   
    ssize_t bytes_sent = send(fd, buffer, strlen(buffer), 0);
    
    if (bytes_sent == -1) {
        perror("Fehler beim Senden");
        return -1;
    }
    
    if ((size_t)bytes_sent != strlen(buffer)) {
        fprintf(stderr, "Nicht alle Daten wurden gesendet. Nur %zd von %zu Bytes gesendet.\n", bytes_sent, strlen(buffer));
        return -1;
    }

    return 0;
}

