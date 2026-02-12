int decode_eobrun_sa( abitreader* huffr, short* block, unsigned int* eobrun, int from, int to )
{
    unsigned short n;
    int bpos;


    for ( bpos = from; bpos <= to; bpos++ ) {
        if ( block[ bpos ] != 0 ) {
            n = huffr->read( 1 );
            block[ bpos ] = ( block[ bpos ] > 0 ) ? n : -n;
        }
    }


    (*eobrun)--;


    return 0;
}
