#include"STD_TYPES.h"
#include"STRING_COMPARE.h"

u8 STR_COMPARE(u8 *ptr1,u8 *ptr2){

	u8 x,i=0;

	while( (ptr1[i]==ptr2[i])){

		i++;

		if(ptr1[i]=='\0' && ptr2[i]=='\0'){x=1;break;}

		else if( (ptr1[i]!='\0' && ptr2[i]=='\0') || (ptr1[i]=='\0' && ptr2[i]!='\0')){x=0;break;}

	}

	if(ptr1[i]!=ptr2[i]){x=0;}

	return x;
}

