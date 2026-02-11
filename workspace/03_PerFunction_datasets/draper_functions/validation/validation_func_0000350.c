outHexChar( unsigned code, MifOutputByteStream *o ) {

    MifOutputByteStream &outS = ( o != NULL ) ? *o : os();
    static const char hex[] = "0123456789abcdef";
    outS << "\\x" << hex[(code >> 4) & 0xf] << hex[code & 0xf] << " ";
}
