automaticDetectionForArabic( const unsigned char* ptr, int size )
{
    for ( int i = 0; i < size; ++i ) {
        if ( ( ptr[ i ] >= 0x80 && ptr[ i ] <= 0x9F ) || ptr[ i ] == 0xA1 || ptr[ i ] == 0xA2 || ptr[ i ] == 0xA3
             || ( ptr[ i ] >= 0xA5 && ptr[ i ] <= 0xAB ) || ( ptr[ i ] >= 0xAE && ptr[ i ] <= 0xBA )
             || ptr[ i ] == 0xBC || ptr[ i ] == 0xBD || ptr[ i ] == 0xBE || ptr[ i ] == 0xC0
             || ( ptr[ i ] >= 0xDB && ptr[ i ] <= 0xDF ) || ( ptr[ i ] >= 0xF3 ) ) {
            return "cp1256";
        }
    }

    return "iso-8859-6";
}
