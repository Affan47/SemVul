rollOSR(const unsigned int nGames, const unsigned int anBoard[25], const unsigned int nOut,
        float arProbs[], const unsigned int nMaxProbs, float arGammonProbs[], const unsigned int nMaxGammonProbs)
{

    unsigned int an[25];
    unsigned short int anProb[32];
    unsigned int i;
    unsigned int n, m;
    unsigned int iGame;

    int *anCounts = (int *) g_alloca(nMaxGammonProbs * sizeof(int));

    memset(anCounts, 0, sizeof(int) * nMaxGammonProbs);

    for (i = 0; i < nMaxProbs; ++i)
        arProbs[i] = 0.0f;


    for (iGame = 0; iGame < nGames; ++iGame) {

        memcpy(an, anBoard, sizeof(an));


        n = osr(an, iGame, nGames, nOut);


        m = 0;
        for (i = 0; i < 6; ++i)
            m += an[i];


        ++anCounts[MIN(m == 15 ? n + 1 : n, nMaxGammonProbs - 1)];


        getBearoffProbs(PositionBearoff(an, pbc1->nPoints, pbc1->nChequers), anProb);

        for (i = 0; i < 32; ++i)
            arProbs[MIN(n + i, nMaxProbs - 1)] += anProb[i] / 65535.0f;

    }


    for (i = 0; i < (unsigned int) nMaxProbs; ++i) {
        arProbs[i] /= nGames;

    }


    for (i = 0; i < nMaxGammonProbs; ++i) {
        arGammonProbs[i] = 1.0f * anCounts[i] / nGames;

    }

}
