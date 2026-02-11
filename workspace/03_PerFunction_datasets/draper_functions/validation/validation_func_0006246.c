has_other_ion_in_sphere_2(inp_ATOM *at, int iat, int iat_ion_neigh, const char *el, int el_len )
{
#define MAXQ 16
    AT_NUMB q[MAXQ];
    int lenq=0, lenq2, dist = 0, i = 0, iq, neigh, j, nRet=0;
    q[lenq++] = iat;
    at[iat].cFlags = 1;

    iq  = 0;
    dist = 1;

    while ( dist <= 2 ) {
        for ( lenq2 = lenq; iq < lenq2; iq ++ ) {
            i = q[iq];
            for ( j = 0; j < at[i].valence; j ++ ) {
                neigh = at[i].neighbor[j];
                if ( !at[neigh].cFlags &&
                     at[neigh].valence <= 3 &&
                     NULL != memchr( el, at[neigh].el_number, el_len ) ) {
                    q[lenq ++] = neigh;
                    at[neigh].cFlags = 1;
                    if ( neigh != iat_ion_neigh &&
                         at[iat_ion_neigh].charge == at[neigh].charge ) {
                        nRet ++;
                    }
                }
            }
        }
        dist ++;
    }
    for ( iq = 0; iq < lenq; iq ++ ) {
        i = q[iq];
        at[i].cFlags = 0;
    }
    return nRet;
}
