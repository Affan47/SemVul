int encode_ac_prg_sa( abitwriter* huffw, abytewriter* storw, huffCodes* actbl, short* block, unsigned int* eobrun, int from, int to )
{
    unsigned short n;
    unsigned char  s;
    unsigned char  z;
    int eob = from;
    int bpos;
    int hc;
    int tmp;


    for ( bpos = to; bpos >= from; bpos-- )    {
        if ( ( block[ bpos ] == 1 ) || ( block[ bpos ] == -1 ) ) {
            eob = bpos + 1;
            break;
        }
    }


    if ( ( eob > from ) && ( (*eobrun) > 0 ) ) {
        encode_eobrun( huffw, actbl, eobrun );
        encode_crbits( huffw, storw );
    }


    z = 0;
    for ( bpos = from; bpos < eob; bpos++ )
    {
        tmp = block[ bpos ];

        if ( tmp == 0 ) {
            z++;
            if ( z == 16 ) {
                huffw->write( actbl->cval[ 0xF0 ], actbl->clen[ 0xF0 ] );
                encode_crbits( huffw, storw );
                z = 0;
            }
        }

        else if ( ( tmp == 1 ) || ( tmp == -1 ) ) {

            s = nonzero_bit_length(ABS(tmp));
            n = ENVLI( s, tmp );
            hc = ( ( z << 4 ) + s );

            huffw->write( actbl->cval[ hc ], actbl->clen[ hc ] );
            huffw->write( n, s );

            encode_crbits( huffw, storw );

            z = 0;
        }
        else {
            n = block[ bpos ] & 0x1;
            storw->write( n );
        }
    }


    for ( ;bpos <= to; bpos++ )
    {
        if ( block[ bpos ] != 0 ) {
            n = block[ bpos ] & 0x1;
            storw->write( n );
        }
    }


    if ( eob <= to ) {
        (*eobrun)++;

        if ( (*eobrun) == actbl->max_eobrun ) {
            encode_eobrun( huffw, actbl, eobrun );
            encode_crbits( huffw, storw );
        }
    }


    return eob;
}
