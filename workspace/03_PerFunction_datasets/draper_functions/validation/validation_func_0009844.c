CheckPelle(void)
{
    int i, j, neri;

    if(arcade_teams)
    {
        if(team_a==3)
            RemapAnimObjColor(p->team[0]->players[9].anim, Pens[P_ARANCIO1], Pens[P_GIALLO]);
        else if(team_b==3)
            RemapAnimObjColor(p->team[1]->players[9].anim, Pens[P_ARANCIO1], Pens[P_GIALLO]);
    }


    Progress();

    for(i = 0; i < 2; i++)
    {
        team_t *s = p->team[i];

        D(bug("Check skin color team %ld\n", i));
        neri = 0;

        for(j = 0; j < 10; j++)
        {
            if(IsBlack(&s->players[j]))
                neri++;
        }


        if(neri > 9)
        {
            has_black[i] = FALSE;

            RemapAnimObjColor(s->players[9].anim, Pens[P_ROSSO2], Pens[P_NERO]);
            RemapAnimObjColor(s->players[9].anim, Pens[P_ARANCIO1], Pens[P_ROSSO2]);
        }
        else if(neri > 0)
        {
            anim_t *o;

            if ((o = CopyAnimObj(s->players[9].anim)))
            {
                BOOL fatti = FALSE;
                has_black[i] = TRUE;

                RemapAnimObjColor(o, Pens[P_ROSSO2], Pens[P_NERO]);
                RemapAnimObjColor(o, Pens[P_ARANCIO1], Pens[P_ROSSO2]);

                for(j = 0; j < 9; j++)
                {
                    if(IsBlack(&s->players[j]))
                    {
                        FreeAnimObj(s->players[j].anim);

                        if(!fatti)
                        {
                            s->players[j].anim = o;
                            fatti = TRUE;
                        }
                        else
                        {
                            s->players[j].anim = CloneAnimObj(o);
                        }
                    }
                }

                if(IsBlack(&s->players[9]))
                {
                    j = 8;

                    while(IsBlack(&s->players[j]))
                        j--;

                    FreeAnimObj(s->players[j].anim);
                    s->players[j].anim = s->players[9].anim;
                    s->players[9].anim = CloneAnimObj(o);
                }
                g_neri[i] = o;
            }
        }

        D(bug("%ld black skinned players.\n", neri));
    }
}
