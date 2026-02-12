int decode_ac_prg_fs( abitreader* huffr, huffTree* actree, short* block, unsigned int* eobrun, int from, int to )
{
    unsigned short n;
    unsigned char  s;
    unsigned char  z;
    int eob = to + 1;
    int bpos;
    int hc;
    int l;
    int r;


    if ( (*eobrun) > 0 ) {
        for ( bpos = from; bpos <= to; ++bpos)
            block[ bpos ] = 0;
        (*eobrun)--;
        return from;
    }


    for ( bpos = from; bpos <= to; )
    {

        hc = next_huffcode( huffr, actree,
                            is_edge(bpos) ? Billing::BITMAP_EDGE : Billing::BITMAP_7x7,
                            is_edge(bpos) ? Billing::EXPN_EDGE : Billing::EXPN_7x7);
        if ( hc < 0 ) return -1;
        l = LBITS( hc, 4 );
        r = RBITS( hc, 4 );

        if ( ( l == 15 ) || ( r > 0 ) ) {
            z = l;
            s = r;
            n = huffr->read( s );
            if ( ( z + bpos ) > to )
                return -1;
            while ( z > 0 ) {
                block[ bpos++ ] = 0;
                z--;
            }
            block[ bpos++ ] = ( short ) DEVLI( s, n );
        }
        else {
            eob = bpos;
            s = l;
            n = huffr->read( s );
            (*eobrun) = E_DEVLI( s, n );


            (*eobrun)--;
            break;
        }
    }


    return eob;
}
