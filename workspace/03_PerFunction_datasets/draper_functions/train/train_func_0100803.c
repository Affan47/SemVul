NativeToCeos( void *dst, const void *src, const size_t len, const size_t swapunit)
{
    int i;
    int remainder;
    int units;


    remainder = len % swapunit;

    units = len - remainder;

    for(i = 0;i < units; i += swapunit )
    {
	swapbyte( ( unsigned char *) dst + i, ( unsigned char * ) src + i, swapunit);
    }

    if(remainder)
    {
	memcpy( ( unsigned char * ) dst + i, ( unsigned char * ) src + i, remainder );
    }
}
