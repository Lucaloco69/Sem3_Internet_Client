#ifndef CHAT_PROTOCOL_H
#define CHAT_PROTOCOL_H

enum { MSG_MAX = 2097152};

typedef struct __attribute__((packed))
{
	char Version[9];  
	char statusCode[4];
	char statusNachricht[512];
	int contentLength;
	char contentType[512];
	char Connection[10];
	char Cookie[512]; 
	char Server[512]; 
	char Date[512]; 
	char Body[MSG_MAX - 2071];     

}Message;


char *clientReceive(int fd, char *buffer, Message *responseBuffer);
int clientSend(int fd, char *buffer);

#endif
