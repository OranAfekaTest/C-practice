#ifndef _ADTRESULT_H_
#define _ADTRESULT_H_
#include <stddef.h>

/*======================= Macros =======================*/

#define MAX_GROUPS 100
#define FAIL -1
#define SERVER_PORT 3000
#define CHAT_PORT 3001
#define BACK_LOG 100
#define MAX_NAME_LENGTH 32
#define BUFFER_SIZE 1024
#define OFF 0
#define ON 1
#define TRUE 1
#define FALSE 0
#define INIT_SIZE 4
#define IP_LEN 16
#define SEND_PID_FILE "SendPID.txt"
#define RECEIVE_PID_FILE "ReceivePID.txt"

typedef enum ADTResult{
                        SUCCESS,
                        UNINITIALIZED,
                        ALLOCATION_ERROR,
                        INVALID_NAME,
                        INVALID_PASSWORD,
                        SEND_FAILED,
	                    RECEIVE_FAILED,
                        SERVER_IS_FULL,
                        EMPTY_GROUPS,
                        LOGGED_IN
                        
                    }ADTResult;


typedef struct Credentials Credentials;
/*======================= Utillity API =======================*/

void ADTResultHandler(ADTResult _code, const char* _location);
size_t HashFunc( const void* _key );
int KeyComperator(void* _firstKey, void* _secondKey);

#endif /*_ADTRESULT_H_*/