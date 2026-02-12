int decode_block_seq( abitreader* huffr, huffTree* dctree, huffTree* actree, short* block )
{
    unsigned short n;
    unsigned char  s;
    unsigned char  z;
    int eob = 64;
    int bpos;
    int hc;


    hc = next_huffcode( huffr, dctree, Billing::EXP0_DC, Billing::EXPN_DC);
    if ( hc < 0 ) return -1;
    else s = ( unsigned char ) hc;
    n = huffr->read( s );
    if (s) {
        write_bit_bill(Billing::RES_DC, false, s - 1);
        write_bit_bill(Billing::SIGN_DC, false, 1);
    }
    block[ 0 ] = DEVLI( s, n );
    bool eof_fixup = false;

    for ( bpos = 1; bpos < 64; )
    {

        hc = next_huffcode( huffr, actree,
                            is_edge(bpos) ? Billing::BITMAP_EDGE : Billing::BITMAP_7x7,
                            is_edge(bpos) ? Billing::EXPN_EDGE : Billing::EXPN_7x7);

        if ( hc > 0 ) {
            z = LBITS( hc, 4 );
            s = RBITS( hc, 4 );
            n = huffr->read( s );
            if (s) {
                write_bit_bill(is_edge(bpos) ? Billing::RES_EDGE : Billing::RES_7x7, false, s - 1);
                write_bit_bill(is_edge(bpos) ? Billing::SIGN_EDGE : Billing::SIGN_7x7, false, 1);
            }
            if ( ( z + bpos ) >= 64 ) {
                eof_fixup = true;
                break;
            }
            while ( z > 0 ) {
                block[ bpos++ ] = 0;
                z--;
            }
            block[ bpos++ ] = ( short ) DEVLI( s, n );
        }
        else if ( hc == 0 ) {
            eob = bpos;


            break;
        }
        else {
            return -1;
        }
    }
    if (eof_fixup) {
        always_assert(huffr->eof && "If 0run is longer than the block must be truncated");
        for(;bpos < eob; ++bpos) {
            block[bpos] = 0;
        }
        if (eob) {
            block[eob - 1] = 1;
        }
    }

    return eob;
}
