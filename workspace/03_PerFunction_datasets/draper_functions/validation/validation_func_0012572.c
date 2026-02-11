AM_initVariables(void)
{
    int pnum;
    static event_t st_notify = { ev_keyup, AM_MSGENTERED, 0, 0 };

    automapactive = true;
    fb = I_VideoBuffer;

    f_oldloc.x = INT_MAX;
    amclock = 0;
    lightlev = 0;

    m_paninc.x = m_paninc.y = 0;
    ftom_zoommul = FRACUNIT;
    mtof_zoommul = FRACUNIT;

    m_w = FTOM(f_w);
    m_h = FTOM(f_h);


    if (playeringame[consoleplayer])
    {
        plr = &players[consoleplayer];
    }
    else
    {
        plr = &players[0];

	for (pnum=0;pnum<MAXPLAYERS;pnum++)
        {
	    if (playeringame[pnum])
            {
                plr = &players[pnum];
		break;
            }
        }
    }

    m_x = plr->mo->x - m_w/2;
    m_y = plr->mo->y - m_h/2;
    AM_changeWindowLoc();


    old_m_x = m_x;
    old_m_y = m_y;
    old_m_w = m_w;
    old_m_h = m_h;


    ST_Responder(&st_notify);

}
