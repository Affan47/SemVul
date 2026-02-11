clear_fcorr(struct monst *grd, bool forceshow)
{
    int fcx, fcy, fcbeg;
    struct monst *mtmp;

    if (!on_level(&(EGD(grd)->gdlevel), &u.uz))
    {
        return true;
    }
    while ((fcbeg = EGD(grd)->fcbeg) < EGD(grd)->fcend)
    {
        fcx = EGD(grd)->fakecorr[fcbeg].fx;
        fcy = EGD(grd)->fakecorr[fcbeg].fy;
        if ((grd->mhp <= 0 || !in_fcorridor(grd, u.ux, u.uy)) &&
            EGD(grd)->gddone)
        {
                forceshow = true;
        }
        if ((u.ux == fcx && u.uy == fcy && grd->mhp > 0) ||
            (!forceshow && couldsee(fcx,fcy)) ||
            (Punished && !carried(uball) &&
             uball->ox == fcx && uball->oy == fcy))
        {
            return false;
        }

        if ((mtmp = m_at(fcx,fcy)) != 0)
        {
            if (mtmp->isgd)
            {
                return false;
            }
            else if (!in_fcorridor(grd, u.ux, u.uy))
            {
                if (mtmp->mtame)
                {
                    yelp(mtmp);
                }
                rloc(mtmp, false);
            }
        }
        levl[fcx][fcy].typ = EGD(grd)->fakecorr[fcbeg].ftyp;
        map_location(fcx, fcy, 1);
        if (!ACCESSIBLE(levl[fcx][fcy].typ))
        {
            block_point(fcx,fcy);
        }
        EGD(grd)->fcbeg++;
    }
    if (grd->mhp <= 0)
    {
        pline_The("corridor disappears.");
        if (IS_ROCK(levl[u.ux][u.uy].typ))
        {
            You("are encased in rock.");
        }
    }
    return true;
}
