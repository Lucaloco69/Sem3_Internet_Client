#include <errno.h>
#include "network.h"
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include "message.h"
Message *responseBuffer;


int clientReceive(int fd, char *buffer)
{   printf("Hier in receive");
	ssize_t bytes_read;

	bytes_read = read(fd, buffer, MSG_MAX);
    printf("%s",buffer);

	if(bytes_read > 0) {
        getHeadersFromRequest(responseBuffer,buffer,10);
		return 1;
	}
	else if (bytes_read == 0) {
        printf("Fehler beim empfangen der Daten");
		return 0;

	}
     printf("Fehler beim empfangen der Daten");

	return -1;
}


int clientSend(int fd, char *buffer) {
    printf("ClientSend");
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

