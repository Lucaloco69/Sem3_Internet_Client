#include <arpa/inet.h>
#include <sys/socket.h>
int createSocket(char *port,char *ipAddrServer);
extern struct sockaddr_in server_addr;