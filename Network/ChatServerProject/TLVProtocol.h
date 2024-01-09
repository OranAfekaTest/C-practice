#ifndef __TLVPROTOCOL_H__
#define __TLVPROTOCOL_H__
#include <stddef.h>

typedef enum Tags{
				TLV_REG_REQ = 1,
				TLV_LOG_REQ,
				TLV_JOIN_GROUP,
				TLV_LEAVE_GROUP,
				TLV_CREATE_GROUP,
				TLV_LOG_OUT,
				TLV_RPLY,
				TLV_GROUP_ADD,
				TLV_GROUP_LIST,
				TLV_GROUP_REMOVE
				} Tags;


typedef enum TLVResult{
					TLV_SUCCESS,
					TLV_NOT_INITIALIZED
				}TLVResult;
				
size_t Pack( char* _package, char* _str1, char* _str2, Tags _tag ); /* if tag != 1 _str2 should be NULL */

unsigned char Unpack( char* _package, char* _str1, char* _str2 ); /* if tag != 1 _str2 should be NULL */


#endif /* __TLVPROTOCOL_H__ */

 					
			
