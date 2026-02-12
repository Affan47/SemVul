Perl__load_PL_utf8_foldclosures (pTHX)
{
    assert(! PL_utf8_foldclosures);


    if (! PL_utf8_tofold) {
        U8 dummy[UTF8_MAXBYTES_CASE+1];
        const U8 hyphen[] = HYPHEN_UTF8;


        toFOLD_utf8_safe(hyphen, hyphen + sizeof(hyphen) - 1, dummy, NULL);
        assert(PL_utf8_tofold);
    }
    PL_utf8_foldclosures = _swash_inversion_hash(PL_utf8_tofold);
}
