#include <arpa/inet.h>
#include <sys/socket.h>
void createSocket(int port,char *ipAddrServer);
struct sockaddr_in server_addr; 