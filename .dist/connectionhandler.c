#include "connectionhandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// Definition der globalen Variable server_addr
struct sockaddr_in server_addr;  // Hier definierst du die Variable

void createSocket(char *port, char *ipAddrServer) {
    int sock = socket(AF_INET, SOCK_STREAM, 0); // Socket erstellen
    if (sock == -1) {
        perror("Socket konnte nicht erstellt werden");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;          
    server_addr.sin_port = htons(atoi(port));  // Port aus Argument (nicht fest auf 80)
    server_addr.sin_addr.s_addr = inet_addr(ipAddrServer);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) { // Verbindung herstellen
        perror("Verbindung zum Server fehlgeschlagen");
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("Verbindung zum Server wurde erfolgreich hergestellt\n");
}
