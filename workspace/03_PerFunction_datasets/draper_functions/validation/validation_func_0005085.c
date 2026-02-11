ajVdwallReadNew(AjPFile inf)
{
    AjPVdwall vdwall = NULL;
    AjPStr line = NULL;
    ajint nres = 0;
    ajint natm = 0;
    ajint rcnt = 0;
    ajint acnt = 0;
    char id1 = '\0';
    AjPStr id3 = NULL;


    line = ajStrNew();
    id3 = ajStrNew();


    while ((ajReadlineTrim(inf, &line)))
    {

        if (ajStrPrefixC(line, "NR"))
        {
            ajFmtScanS(line, "%*s %d", &nres);


            vdwall = ajVdwallNew(nres);

        }

        else if (ajStrPrefixC(line, "AA"))
        {
            rcnt++;
            acnt = 0;
            ajFmtScanS(line, "%*s %S", &id3);
        }

        else if (ajStrPrefixC(line, "ID"))
            ajFmtScanS(line, "%*s %c", &id1);

        else if (ajStrPrefixC(line, "NN"))
        {
            ajFmtScanS(line, "%*s %d", &natm);


            vdwall->Res[rcnt - 1] = ajVdwresNew(natm);


            vdwall->Res[rcnt - 1]->Id1 = id1;
            ajStrAssignS(&vdwall->Res[rcnt - 1]->Id3, id3);

        }

        else if (ajStrPrefixC(line, "AT"))
        {
            acnt++;
            ajFmtScanS(line, "%*s %S %*c %f",
                       &vdwall->Res[rcnt - 1]->Atm[acnt - 1],
                       &vdwall->Res[rcnt - 1]->Rad[acnt - 1]);
        }
    }

    ajStrDel(&line);
    ajStrDel(&id3);

    return vdwall;
}
