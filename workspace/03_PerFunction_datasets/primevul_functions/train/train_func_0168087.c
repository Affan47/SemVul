extract_bitmap_resource(WinLibrary *fi, WinResource *wr, int *ressize)
{
    Win32BitmapInfoHeader info;
    uint8_t *result;
    uint8_t *resentry;
    uint32_t offbits;
    int size;

    resentry=(uint8_t *)(get_resource_entry(fi,wr,&size));


    memcpy(&info,resentry,sizeof(info));
    fix_win32_bitmap_info_header_endian(&info);


    offbits = info.size+14;


    if (info.bit_count!=24) {


       if (info.clr_used==0) {
           switch (info.bit_count) {
               case 1:
                   offbits += 8;
                   break;
               case 4:
                   offbits += 64;
                   break;
               case 8:
                  offbits += 1024;
           }
       } else {
           offbits += 4 * info.clr_used;
       }
    }


    *ressize = 14+size;
    result = (uint8_t *)xmalloc(*ressize);


    result[0] = 'B';
    result[1] = 'M';
    result[2] = (*ressize & 0x000000ff);
    result[3] = (*ressize & 0x0000ff00)>>8;
    result[4] = (*ressize & 0x00ff0000)>>16;
    result[5] = (*ressize & 0xff000000)>>24;
    result[6] = 0;
    result[7] = 0;
    result[8] = 0;
    result[9] = 0;
    result[10] = (offbits & 0x000000ff);
    result[11] = (offbits & 0x0000ff00)>>8;
    result[12] = (offbits & 0x00ff0000)>>16;
    result[13] = (offbits & 0xff000000)>>24;


    memcpy(result+14,resentry,size);

    return result;
}
