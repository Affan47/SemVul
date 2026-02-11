angrygods(aligntyp resp_god)
{
    int	maxanger;

    if (Inhell) resp_god = A_NONE;
    u.ublessed = 0;


    if (resp_god != u.ualign.type)
            maxanger =  u.ualign.record/2 + (Luck > 0 ? -Luck/3 : -Luck);
    else
            maxanger =  3*u.ugangr +
                ((Luck > 0 || u.ualign.record >= STRIDENT) ? -Luck/3 : -Luck);
    if (maxanger < 1) maxanger = 1;
    else if (maxanger > 15) maxanger = 15;

    switch (rn2(maxanger))
    {
    case 0:
    case 1:	You_feel("that %s is %s.", align_gname(resp_god),
                         Hallucination ? "bummed" : "displeased");
                break;
    case 2:
    case 3:
                godvoice(resp_god,(char *)0);
                pline("\"Thou %s, %s.\"",
                      (ugod_is_angry() && resp_god == u.ualign.type)
                      ? "hast strayed from the path" :
                      "art arrogant",
                      youmonst.data->mlet == S_HUMAN ? "mortal" : "creature");
                verbalize("Thou must relearn thy lessons!");
                (void) adjattrib(A_WIS, -1, false);
                losexp((char *)0);
                break;
    case 6:	if (!Punished)
                {
                    gods_angry(resp_god);
                    punish((struct obj *)0);
                    break;
                }
    case 4:
    case 5:	gods_angry(resp_god);
                if (!Blind && !Antimagic)
                        pline("%s glow surrounds you.",
                              An(hcolor(NH_BLACK)));
                rndcurse();
                break;
    case 7:
    case 8:	godvoice(resp_god,(char *)0);
                verbalize("Thou durst %s me?",
                          (on_altar() &&
                           (a_align(u.ux,u.uy) != resp_god)) ?
                          "scorn":"call upon");
                pline("\"Then die, %s!\"",
                      youmonst.data->mlet == S_HUMAN ? "mortal" : "creature");
                summon_minion(resp_god, false);
                break;

    default:	gods_angry(resp_god);
                god_zaps_you(resp_god);
                break;
    }
    u.ublesscnt = rnz(300);
    return;
}
