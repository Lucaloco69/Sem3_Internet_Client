char *divideBodyFromHeader(char *str);
int evaluateInput(char *input);
char * prepareRequest(char *input,char *hostNamechar,char *userName);
char * prepareRequestWithCookie(char *input,char *hostNamechar,char *userName);
int writeIntoFile(char *body);