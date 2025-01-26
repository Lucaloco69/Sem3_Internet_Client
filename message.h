#include "network.h"
char *divideBodyFromHeader(char *str);
int evaluateInput(char *input);
char * prepareRequest(char *input,char *hostNamechar,char *userName);
char * prepareRequestWithCookie(char *input,char *hostNamechar,char *userName,char *cookie);
int writeIntoFile(char *body, Message *responseBuffer,char* image, char* text);
int getHeadersFromRequest(Message *buffer, char *strBuf, int maxHeaders);
int splitIntoImgAndText(char* mixed,char *img,char* txt);