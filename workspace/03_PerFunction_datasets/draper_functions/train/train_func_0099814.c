m_initgrp(struct monst *mtmp, int x, int y, int n)
{
    coord mm;
    int cnt = rnd(n);
    struct monst *mon;
#if defined(__GNUC__) && (defined(HPUX) || defined(DGUX))


    int cnttmp,cntdiv;

    cnttmp = cnt;
# ifdef DEBUG
    pline("init group call x=%d,y=%d,n=%d,cnt=%d.", x, y, n, cnt);
# endif
    cntdiv = ((u.ulevel < 3) ? 4 : (u.ulevel < 5) ? 2 : 1);
#endif

    cnt /= (u.ulevel < 3) ? 4 : (u.ulevel < 5) ? 2 : 1;
#if defined(__GNUC__) && (defined(HPUX) || defined(DGUX))
    if (cnt != (cnttmp/cntdiv))
    {
        pline("cnt=%d using %d, cnttmp=%d, cntdiv=%d", cnt,
              (u.ulevel < 3) ? 4 : (u.ulevel < 5) ? 2 : 1,
              cnttmp, cntdiv);
    }
#endif
    if (!cnt)
    {
        cnt++;
    }
#if defined(__GNUC__) && (defined(HPUX) || defined(DGUX))
    if (cnt < 0)
    {
        cnt = 1;
    }
    if (cnt > 10)
    {
        cnt = 10;
    }
#endif

    mm.x = x;
    mm.y = y;
    while(cnt--)
    {
        if (peace_minded(mtmp->data))
        {
            continue;
        }


        if (enexto(&mm, mm.x, mm.y, mtmp->data))
        {
            mon = makemon(mtmp->data, mm.x, mm.y, NO_MM_FLAGS);
            mon->mpeaceful = false;
            mon->mavenge = 0;
            set_malign(mon);


        }
    }
}
