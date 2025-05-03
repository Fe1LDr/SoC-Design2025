#include "boot.h"

typedef struct {
    unsigned int size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bitCount;
    unsigned int compression;
    unsigned int sizeImage;
    int xPelsPerMeter;
    int yPelsPerMeter;
    unsigned int clrUsed;
    unsigned int clrImportant;
} BitMapInfo;

typedef struct {
    char magic[2];
    unsigned int fileLength;
    unsigned int reserved;
    unsigned int headerLength;
} BitMapHeader;

#define U32_TO_U8_ARR( arr, number )	( arr )[ 0 ] = ( number ) & 0x000000FF;\
										( arr )[ 1 ] = ( ( number ) & 0x0000FF00 ) >> 8;\
										( arr )[ 2 ] = ( ( number ) & 0x00FF0000 ) >> 16;\
										( arr )[ 3 ] = ( ( number ) & 0xFF000000 ) >> 24;

int convert_to_bmp( int *src, int *dst, int width, int height )
{
	uint32_t length;
    uint8_t *charSrc, *charDst;
	
	charSrc = ( uint8_t * )src;
	charDst = ( uint8_t * )dst;
	
	charDst[ 0 ] = 'B';
	charDst[ 1 ] = 'M';
	length = width * height * 3;
	U32_TO_U8_ARR( charDst + 2, length + 54 );
	charDst[ 6 ] = 0x00;
	charDst[ 7 ] = 0x00;
	charDst[ 8 ] = 0x00;
	charDst[ 9 ] = 0x00;
	U32_TO_U8_ARR( charDst + 10, 54 );
	U32_TO_U8_ARR( charDst + 14, 40 );
	U32_TO_U8_ARR( charDst + 18, width );
	U32_TO_U8_ARR( charDst + 22, height );
	charDst[ 26 ] = 0x01;
	charDst[ 27 ] = 0x00;
	charDst[ 28 ] = 24;
	charDst[ 29 ] = 0x00;
	charDst[ 30 ] = 0x00;	//compression
	charDst[ 31 ] = 0x00;
	charDst[ 32 ] = 0x00;
	charDst[ 33 ] = 0x00;
	U32_TO_U8_ARR( charDst + 34, length );
	memset( charDst + 46, 0x00, 16 );
	charDst += 54;
	
	for( int i = height - 1; i >= 0; i-- )
	{
		memcpy( charDst, charSrc + i * width * 3, width * 3 );
		charDst += width * 3;
	}
	
    return 0;
}
