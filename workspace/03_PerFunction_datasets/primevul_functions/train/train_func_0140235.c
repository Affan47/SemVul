void Scanner::shift_ptrs_and_fpos(ptrdiff_t offs)
{

    shift_ptrs(offs);


    for (size_t i = files.size(); i --> 0; ) {
        Input *in = files[i];
        if (in->so == ENDPOS && in->eo == ENDPOS) break;
        DASSERT(in->so != ENDPOS && in->eo != ENDPOS);
        in->so += offs;
        in->eo += offs;
    }
}
