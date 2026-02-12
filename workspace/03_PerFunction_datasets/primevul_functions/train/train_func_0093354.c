int skip_eobrun( int* cmp, int* dpos, int* rstw, unsigned int* eobrun )
{
    if ( (*eobrun) > 0 )
    {

        if ( rsti > 0 ) {
            if ( (int)(*eobrun) > (*rstw) )
                return -1;
            else
                (*rstw) -= (*eobrun);
        }


        if ( cmpnfo[(*cmp)].bch != cmpnfo[(*cmp)].nch ) {
            (*dpos) += ( ( ( (*dpos) % cmpnfo[(*cmp)].bch ) + (*eobrun) ) /
                        cmpnfo[(*cmp)].nch ) * ( cmpnfo[(*cmp)].bch - cmpnfo[(*cmp)].nch );
        }


        if ( cmpnfo[(*cmp)].bcv != cmpnfo[(*cmp)].ncv ) {
            if ( (*dpos) / cmpnfo[(*cmp)].bch >= cmpnfo[(*cmp)].ncv )
                (*dpos) += ( cmpnfo[(*cmp)].bcv - cmpnfo[(*cmp)].ncv ) *
                        cmpnfo[(*cmp)].bch;
        }


        (*dpos) += (*eobrun);


        (*eobrun) = 0;


        if ( (*dpos) == cmpnfo[(*cmp)].bc ) return 2;
        else if ( (*dpos) > cmpnfo[(*cmp)].bc ) return -1;
        else if ( rsti > 0 )
            if ( (*rstw) == 0 ) return 1;
    }

    return 0;
}
