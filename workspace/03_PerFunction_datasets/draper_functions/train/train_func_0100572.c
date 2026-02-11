read_jp2box(FILE *inptr,unsigned long offset)
{
    static struct jp2box box;
    struct jp2box *newbox = NULL;

    if(inptr)
    {
        box.boxoffset = offset;
        box.lbox = read_ulong(inptr,TIFF_MOTOROLA,offset);
        if(!feof(inptr) && !(ferror(inptr)))
        {
            box.tbox = read_ulong(inptr,TIFF_MOTOROLA,HERE);
            if(!feof(inptr) && !(ferror(inptr)))
            {
                if(box.lbox == 1)
                {
#if 0
                    box.boxlength = read_ulong64(inptr,TIFF_MOTOROLA,HERE);
                    box.dataoffset = 16;
#else
                    PUSHCOLOR(RED);
                    printf("%s: cannot read 64 bit sizes/offsets yet",Progname);
                    POPCOLOR();
                    newbox = NULL;
#endif
                }
                else
                {
                    box.boxlength = box.lbox;
                    box.dataoffset = 8;
                }
                newbox = &box;
            }
            else
                newbox = NULL;
        }
        else
            newbox = NULL;
    }
    return(newbox);
}
