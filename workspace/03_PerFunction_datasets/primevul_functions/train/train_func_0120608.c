static int disk_error(__G)
    __GDEF
{

    Info(slide, 0x4a1, ((char *)slide, LoadFarString(DiskFullQuery),
      FnFilter1(G.filename)));

#ifndef WINDLL
    fgets(G.answerbuf, sizeof(G.answerbuf), stdin);
    if (*G.answerbuf == 'y')
        G.disk_full = 1;
    else
#endif
        G.disk_full = 2;

    return PK_DISK;

}
