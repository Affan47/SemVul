Frdbyte()
{
    struct stream *strm;
    int ch;
    int flg;

    flg = *FLAGPTR(argStkPtr);
    if(flg != fSTREAM || !isinpfile(argStkPtr,BINARY)) {
        error(rdbytesym,err_binp,voidsym);
        return(brkerr());
    }
    strm = STREAMPTR(argStkPtr);
    ch = fgetc(strm->file);
    return(mksfixnum(ch));
}
