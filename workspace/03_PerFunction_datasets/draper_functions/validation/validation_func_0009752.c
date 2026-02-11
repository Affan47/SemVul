RolloutProgress(float aarOutput[][NUM_ROLLOUT_OUTPUTS],
                float aarStdDev[][NUM_ROLLOUT_OUTPUTS],
                const rolloutcontext * prc,
                const cubeinfo aci[],
                unsigned int initial_game_count,
                const int iGame,
                const int iAlternative,
                const int nRank,
                const float rJsd, const int fStopped, const int fShowRanks, int fCubeRollout, void *pUserData)
{

    if (!fShowProgress)
        return;

#if USE_GTK
    if (fX) {
        GTKRolloutProgress(aarOutput, aarStdDev, prc, aci, initial_game_count, iGame, iAlternative,
                           nRank, rJsd, fStopped, fShowRanks, fCubeRollout, pUserData);
        return;
    }
#endif

    TextRolloutProgress(aarOutput, aarStdDev, prc, aci, initial_game_count, iGame, iAlternative,
                        nRank, rJsd, fStopped, fShowRanks, fCubeRollout, pUserData);

}
