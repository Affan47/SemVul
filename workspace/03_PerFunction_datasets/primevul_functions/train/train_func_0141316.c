AbortDDX(enum ExitCode error)
{
    int i;

    input_lock();


#ifdef DPMSExtension
    if (DPMSPowerLevel != DPMSModeOn)
        DPMSSet(serverClient, DPMSModeOn);
#endif
    if (xf86Screens) {
        for (i = 0; i < xf86NumScreens; i++)
            if (xf86Screens[i]->vtSema) {


                xf86VGAarbiterLock(xf86Screens[i]);
                (xf86Screens[i]->LeaveVT) (xf86Screens[i]);
                xf86VGAarbiterUnlock(xf86Screens[i]);
            }
    }


    ddxGiveUp(error);
}
