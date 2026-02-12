static unsigned int FNAME(golomb_decoding)(const unsigned int l, const unsigned int bits,
                                           unsigned int * const codewordlen)
{
    if (bits > VNAME(family).notGRprefixmask[l]) {
        const unsigned int zeroprefix = cnt_l_zeroes(bits);
        const unsigned int cwlen = zeroprefix + 1 + l;
        (*codewordlen) = cwlen;
        return (zeroprefix << l) | ((bits >> (32 - cwlen)) & bppmask[l]);
    } else {
        const unsigned int cwlen = VNAME(family).notGRcwlen[l];
        (*codewordlen) = cwlen;
        return VNAME(family).nGRcodewords[l] + ((bits) >> (32 - cwlen) &
                                                bppmask[VNAME(family).notGRsuffixlen[l]]);
    }
}
