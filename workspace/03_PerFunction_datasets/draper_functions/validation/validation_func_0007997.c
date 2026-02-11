process_jp2_de(FILE *inptr,struct jp2box *box,int indent)
{
    unsigned long boxoffset,max_offset,dataoffset,tbox;
    unsigned long boxlength;
    unsigned short vers;
    unsigned long flag;
    int chpr = 0;

    if((LIST_MODE))
        chpr = list_jp2box(inptr,box,"JP2.uinf.",indent,1);
    else
        print_jp2box(inptr,box,indent);
    boxoffset = box->boxoffset;
    boxlength = box->boxlength;
    tbox = box->tbox;

    dataoffset = boxoffset + box->dataoffset;
    max_offset = boxoffset + boxlength;

    vers = read_ubyte(inptr,dataoffset);
    print_tag_address(ENTRY,dataoffset,indent + 8,"=");
    if((PRINT_TAGINFO))
    {
        if((PRINT_LONGNAMES))
            chpr += printf("JP2.jp2h.uinf.de.");
        chpr += printf("Version");
    }
    if((PRINT_VALUE))
            chpr += printf(" = %u",vers);
    chpr = newline(chpr);
    dataoffset ++;
    flag = read_ulong(inptr,TIFF_MOTOROLA,dataoffset);
    flag = (flag >> 8) & 0xfff;
    print_tag_address(ENTRY,dataoffset,indent + 8,"=");
    if((PRINT_TAGINFO))
    {
        if((PRINT_LONGNAMES))
            chpr += printf("JP2.jp2h.uinf.de.");
        chpr += printf("flags");
    }
    if((PRINT_VALUE))
        chpr += printf(" = %lu",flag);
    chpr = newline(chpr);
    dataoffset += 3;
    print_tag_address(ENTRY,dataoffset,indent + 8,"=");
    if((PRINT_TAGINFO))
    {
        if((PRINT_LONGNAMES))
            chpr += printf("JP2.jp2h.uinf.de.");
        chpr += printf("Location");
    }
    if((PRINT_VALUE))
    {
        chpr += printf(" (length %lu) = ",max_offset - dataoffset);

        setcharsprinted(chpr);
        print_ascii(inptr,max_offset - dataoffset,dataoffset);
    }
    if((PRINT_SECTION))
    {
        chpr = newline(chpr);
        print_tag_address(SECTION,dataoffset - 1,indent,"@");
        print_jp2type(tbox,1);
    }
    chpr = newline(chpr);
    return(max_offset);
}
