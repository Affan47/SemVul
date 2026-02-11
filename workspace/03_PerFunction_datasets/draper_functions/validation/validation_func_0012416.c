detect_endian( void )
{
    short a = 0x1234;
    unsigned char *uc = ( unsigned char * ) &a;

    return ( uc[ 0 ] == 0x12 && uc[ 1 ] == 0x34 ) ? MSBFirst : LSBFirst;
}
