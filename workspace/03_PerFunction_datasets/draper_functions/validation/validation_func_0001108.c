runindofs(runcxdef *ctx, uint indx, uchar *lstp)
{
    uint   lstsiz;
    uchar *orgp = lstp;


    if (indx <= 0) runsig(ctx, ERR_LOWINX);


    lstsiz = osrp2(lstp) - 2;
    lstp += 2;


    for (--indx ; indx && lstsiz ; --indx) lstadv(&lstp, &lstsiz);


    if (!lstsiz) runsig(ctx, ERR_HIGHINX);


    return((uint)(lstp - orgp));
}
