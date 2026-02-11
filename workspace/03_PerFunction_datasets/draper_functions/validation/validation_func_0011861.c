SB_Init(void)
{
    int i;
    int startLump;

    PatchLTFACE = W_CacheLumpName(DEH_String("LTFACE"), PU_STATIC);
    PatchRTFACE = W_CacheLumpName(DEH_String("RTFACE"), PU_STATIC);
    PatchBARBACK = W_CacheLumpName(DEH_String("BARBACK"), PU_STATIC);
    PatchINVBAR = W_CacheLumpName(DEH_String("INVBAR"), PU_STATIC);
    PatchCHAIN = W_CacheLumpName(DEH_String("CHAIN"), PU_STATIC);
    if (deathmatch)
    {
        PatchSTATBAR = W_CacheLumpName(DEH_String("STATBAR"), PU_STATIC);
    }
    else
    {
        PatchSTATBAR = W_CacheLumpName(DEH_String("LIFEBAR"), PU_STATIC);
    }
    if (!netgame)
    {
        PatchLIFEGEM = W_CacheLumpName(DEH_String("LIFEGEM2"), PU_STATIC);
    }
    else
    {
        PatchLIFEGEM = W_CacheLumpNum(W_GetNumForName(DEH_String("LIFEGEM0"))
                                      + consoleplayer, PU_STATIC);
    }
    PatchLTFCTOP = W_CacheLumpName(DEH_String("LTFCTOP"), PU_STATIC);
    PatchRTFCTOP = W_CacheLumpName(DEH_String("RTFCTOP"), PU_STATIC);
    PatchSELECTBOX = W_CacheLumpName(DEH_String("SELECTBOX"), PU_STATIC);
    PatchINVLFGEM1 = W_CacheLumpName(DEH_String("INVGEML1"), PU_STATIC);
    PatchINVLFGEM2 = W_CacheLumpName(DEH_String("INVGEML2"), PU_STATIC);
    PatchINVRTGEM1 = W_CacheLumpName(DEH_String("INVGEMR1"), PU_STATIC);
    PatchINVRTGEM2 = W_CacheLumpName(DEH_String("INVGEMR2"), PU_STATIC);
    PatchBLACKSQ = W_CacheLumpName(DEH_String("BLACKSQ"), PU_STATIC);
    PatchARMCLEAR = W_CacheLumpName(DEH_String("ARMCLEAR"), PU_STATIC);
    PatchCHAINBACK = W_CacheLumpName(DEH_String("CHAINBACK"), PU_STATIC);
    startLump = W_GetNumForName(DEH_String("IN0"));
    for (i = 0; i < 10; i++)
    {
        PatchINumbers[i] = W_CacheLumpNum(startLump + i, PU_STATIC);
    }
    PatchNEGATIVE = W_CacheLumpName(DEH_String("NEGNUM"), PU_STATIC);
    FontBNumBase = W_GetNumForName(DEH_String("FONTB16"));
    startLump = W_GetNumForName(DEH_String("SMALLIN0"));
    for (i = 0; i < 10; i++)
    {
        PatchSmNumbers[i] = W_CacheLumpNum(startLump + i, PU_STATIC);
    }
    playpalette = W_GetNumForName(DEH_String("PLAYPAL"));
    spinbooklump = W_GetNumForName(DEH_String("SPINBK0"));
    spinflylump = W_GetNumForName(DEH_String("SPFLY0"));
}
