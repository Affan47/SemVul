mkfount(int mazeflag, struct mkroom *croom)
{
    coord m;
    int tryct = 0;

    do {
        if (++tryct > 200)
        {
            return;
        }
        if (mazeflag)
        {
            mazexy(&m);
        }
        else
        {
            if (!somexy(croom, &m))
            {
                return;
            }
        }
    } while(occupied(m.x, m.y) || bydoor(m.x, m.y));


    levl[m.x][m.y].typ = FOUNTAIN;

    if(!rn2(7)) levl[m.x][m.y].blessedftn = 1;

    level.flags.nfountains++;
}
