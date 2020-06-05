#include <stdint.h>
#include "tinyecc.h"

/*
 * convert hex data from a buffer to a bytestring.
 * return the number of bytes stored
 */
uint16_t tinyecc_hex2bin(uint8_t * dest, uint16_t destroom, const char * hex, uint16_t hexlen)
{
	uint16_t i,j;
	uint8_t ch;
	uint8_t byte;
	uint8_t digits;
    /* checks */
    if(dest==NULL || hex==NULL || destroom==0 || hexlen==0) {
        return 0;
    }

    /* convert */
	digits=0;
	byte=0;
	for(i=0,j=0;i<hexlen;i++) {
		ch=hex[i];
		if(ch>='0' && ch<='9') {
			ch -= '0';
		} else if(ch>='A' && ch<='F') {
			ch -= 'A';
			ch += 10;
		} else if(ch>='a' && ch<='f') {
			ch -= 'a';
			ch += 10;
		} else {
			//not an hex char, discard
			continue;
		}
		digits++;
		byte<<=4;
		byte |= (ch&0x0F);
		if(digits==2 && destroom>0) {
			dest[j++] = byte;
			byte = 0;
			digits = 0;
			destroom--;
		}
	}
    return j;
}

