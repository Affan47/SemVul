D_IntroTick(void)
{
    static boolean didsound = false;

    if(devparm)
        return;

    ++introprogress;
    if(introprogress >= MAXINTROPROGRESS)
    {
        D_IntroBackground();


        if(!didsound)
        {
            S_StartSound(NULL, sfx_psdtha);
            didsound = true;
        }
    }
    else
        D_DrawIntroSequence();
}
