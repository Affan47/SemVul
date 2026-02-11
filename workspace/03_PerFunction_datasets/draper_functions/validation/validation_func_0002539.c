initPostCrawfordMETFromParameters(float afMETPostCrawford[MAXSCORE], metparameters * pmp)
{

    if (!strcmp((char *) pmp->szName, "zadeh")) {

        float rG = 0.25f;
        float rFD2 = 0.015f;
        float rFD4 = 0.004f;
        listOLD *pl;
        parameter *pp;


        for (pl = pmp->lParameters.plNext; pl != &pmp->lParameters; pl = pl->plNext) {

            pp = pl->p;

            if (!strcmp((char *) pp->szName, "gammon-rate-trailer"))
                rG = pp->value;
            else if (!strcmp((char *) pp->szName, "free-drop-2-away"))
                rFD2 = pp->value;
            else if (!strcmp((char *) pp->szName, "free-drop-4-away"))
                rFD4 = pp->value;

        }


        initPostCrawfordMET(afMETPostCrawford, 0, rG, rFD2, rFD4);
        return 0;

    } else if (!strcmp((char *) pmp->szName, "mec")) {

        float rG = 0.25f;
        float rFD2 = 0.015f;
        float rFD4 = 0.004f;
        float rWR = 0.5f;
        listOLD *pl;
        parameter *pp;


        for (pl = pmp->lParameters.plNext; pl != &pmp->lParameters; pl = pl->plNext) {

            pp = pl->p;

            if (!strcmp((char *) pp->szName, "gammon-rate"))
                rG = pp->value;
            else if (!strcmp((char *) pp->szName, "free-drop-2-away"))
                rFD2 = pp->value;
            else if (!strcmp((char *) pp->szName, "free-drop-4-away"))
                rFD4 = pp->value;
            else if (!strcmp((char *) pp->szName, "win-rate"))
                rWR = pp->value;

        }


        mec_pc(rG, rFD2, rFD4, rWR, afMETPostCrawford);

        return 0;

    } else {


        return -1;

    }

}
