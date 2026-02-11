corpse_chance(struct monst *mon,
              struct monst *magr,
              bool was_swallowed)
{
    struct permonst *mdat = mon->data;
    int i, tmp;

    if (mdat == &mons[PM_VLAD_THE_IMPALER] || mdat->mlet == S_LICH)
    {
        if (cansee(mon->mx, mon->my) && !was_swallowed)
                pline("%s body crumbles into dust.", s_suffix(Monnam(mon)));
        return false;
    }


    for(i = 0; i < NATTK; i++)
    {
        if (mdat->mattk[i].aatyp == AT_BOOM)
        {
            if (mdat->mattk[i].damn)
                    tmp = d((int)mdat->mattk[i].damn,
                            (int)mdat->mattk[i].damd);
            else if(mdat->mattk[i].damd)
                    tmp = d((int)mdat->mlevel+1, (int)mdat->mattk[i].damd);
            else tmp = 0;
            if (was_swallowed && magr)
            {
                if (magr == &youmonst)
                {
                    There("is an explosion in your %s!",
                          body_part(STOMACH));
                    sprintf(killer_buf, "%s explosion",
                            s_suffix(mdat->mname));
                    if (Half_physical_damage) tmp = (tmp+1) / 2;
                    losehp(tmp, killer_buf, KILLED_BY_AN);
                }
                else
                {
                    if (flags.soundok) You_hear("an explosion.");
                    magr->mhp -= tmp;
                    if (magr->mhp < 1) mondied(magr);
                    if (magr->mhp < 1)
                    {
                        if (canspotmon(magr))
                                pline("%s rips open!", Monnam(magr));
                    }
                    else if (canseemon(magr))
                            pline("%s seems to have indigestion.",
                                  Monnam(magr));
                }

                return false;
            }

            sprintf(killer_buf, "%s explosion", s_suffix(mdat->mname));
            killer = killer_buf;
            killer_format = KILLED_BY_AN;
            explode(mon->mx, mon->my, -1, tmp, MON_EXPLODE, EXPL_NOXIOUS);
            return (false);
        }
    }


    if (LEVEL_SPECIFIC_NOCORPSE(mdat))
            return false;

    if (bigmonst(mdat) || mdat == &mons[PM_LIZARD]
        || is_golem(mdat)
        || is_mplayer(mdat)
        || is_rider(mdat))
            return true;
    return (bool) (!rn2((int)
                        (2 + ((int)(mdat->geno & G_FREQ)<2) + verysmall(mdat))));
}
