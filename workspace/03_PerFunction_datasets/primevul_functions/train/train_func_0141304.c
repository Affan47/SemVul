ddxGiveUp(enum ExitCode error)
{
    int i;

    xf86VGAarbiterFini();

#ifdef XF86PM
    if (xf86OSPMClose)
        xf86OSPMClose();
    xf86OSPMClose = NULL;
#endif

    for (i = 0; i < xf86NumScreens; i++) {


        xf86Screens[i]->vtSema = FALSE;
    }

#ifdef XFreeXDGA
    DGAShutdown();
#endif

    if (xorgHWOpenConsole)
        xf86CloseConsole();

    systemd_logind_fini();
    dbus_core_fini();

    xf86CloseLog(error);
}
