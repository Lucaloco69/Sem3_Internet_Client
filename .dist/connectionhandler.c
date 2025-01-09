#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void createSocket(int port, char *ipAddrServer){
    int sock = socket(AF_INET, SOCK_STREAM, 0); //Socket erstellen
    if (sock == -1) {
        perror("Socket konnte nicht erstellt werden");
        exit(EXIT_FAILURE);
    }
    int serverAddr;
    server_addr.sin_family = AF_INET;          
    server_addr.sin_port = htons(80);            
    server_addr.sin_addr.s_addr = inet_addr(serverAddr);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) { //Verbindung herstellen
        perror("Verbindung zum Server fehlgeschlagen");
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("Verbindung zum Server wurde  erfolgreich hergestellt");
}