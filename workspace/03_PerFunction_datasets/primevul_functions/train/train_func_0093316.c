int encode_ac_prg_fs( abitwriter* huffw, huffCodes* actbl, short* block, unsigned int* eobrun, int from, int to )
{
    unsigned short n;
    unsigned char  s;
    unsigned char  z;
    int bpos;
    int hc;
    int tmp;


    z = 0;
    for ( bpos = from; bpos <= to; bpos++ )
    {

        tmp = block[ bpos ];
        if ( tmp != 0 ) {

            encode_eobrun( huffw, actbl, eobrun );

            while ( z >= 16 ) {
                huffw->write( actbl->cval[ 0xF0 ], actbl->clen[ 0xF0 ] );
                z -= 16;
            }

            s = nonzero_bit_length(ABS(tmp));
            n = ENVLI( s, tmp);
            hc = ( ( z << 4 ) + s );

            huffw->write( actbl->cval[ hc ], actbl->clen[ hc ] );
            huffw->write( n, s );

            z = 0;
        }
        else {
            z++;
        }
    }


    if ( z > 0 ) {
        (*eobrun)++;

        if ( (*eobrun) == actbl->max_eobrun )
            encode_eobrun( huffw, actbl, eobrun );
        return 1 + to - z;
    }
    else {
        return 1 + to;
    }
}
