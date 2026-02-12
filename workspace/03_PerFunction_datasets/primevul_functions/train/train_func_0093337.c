int decode_ac_prg_sa( abitreader* huffr, huffTree* actree, short* block, unsigned int* eobrun, int from, int to )
{
    unsigned short n;
    unsigned char  s;
    signed char    z;
    signed char    v;
    int bpos = from;
    int eob = to;
    int hc;
    int l;
    int r;


    if ( (*eobrun) == 0 )
    while ( bpos <= to )
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
            if ( s == 0 ) v = 0;
            else if ( s == 1 ) {
                n = huffr->read( 1 );
                v = ( n == 0 ) ? -1 : 1;
            }
            else return -1;

            while ( true ) {
                if ( block[ bpos ] == 0 ) {
                    if ( z > 0 ) z--;
                    else {
                        block[ bpos++ ] = v;
                        break;
                    }
                }
                else {
                    n = huffr->read( 1 );
                    block[ bpos ] = ( block[ bpos ] > 0 ) ? n : -n;
                }
                if ( bpos++ >= to ) return -1;
            }
        }
        else {
            eob = bpos;
            s = l;
            n = huffr->read( s );
            (*eobrun) = E_DEVLI( s, n );
            break;
        }
    }


    if ( (*eobrun) > 0 ) {
        for ( ; bpos <= to; bpos++ ) {
            if ( block[ bpos ] != 0 ) {
                n = huffr->read( 1 );
                block[ bpos ] = ( block[ bpos ] > 0 ) ? n : -n;
            }
        }

        (*eobrun)--;
    }


    return eob;
}
