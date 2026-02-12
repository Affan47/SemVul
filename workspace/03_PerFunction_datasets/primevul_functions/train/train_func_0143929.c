InitOutput(ScreenInfo * pScreenInfo, int argc, char **argv)
{
    int i, j, k, scr_index;
    const char **modulelist;
    void **optionlist;
    Pix24Flags screenpix24, pix24;
    MessageType pix24From = X_DEFAULT;
    Bool pix24Fail = FALSE;
    Bool autoconfig = FALSE;
    Bool sigio_blocked = FALSE;
    Bool want_hw_access = FALSE;
    GDevPtr configured_device;

    xf86Initialising = TRUE;

    config_pre_init();

    if (serverGeneration == 1) {
        if ((xf86ServerName = strrchr(argv[0], '/')) != 0)
            xf86ServerName++;
        else
            xf86ServerName = argv[0];

        xf86PrintBanner();
        LogPrintMarkers();
        if (xf86LogFile) {
            time_t t;
            const char *ct;

            t = time(NULL);
            ct = ctime(&t);
            xf86MsgVerb(xf86LogFileFrom, 0, "Log file: \"%s\", Time: %s",
                        xf86LogFile, ct);
        }


        if (!xf86DoConfigure && !xf86DoShowOptions) {
            switch (xf86HandleConfigFile(FALSE)) {
            case CONFIG_OK:
                break;
            case CONFIG_PARSE_ERROR:
                xf86Msg(X_ERROR, "Error parsing the config file\n");
                return;
            case CONFIG_NOFILE:
                autoconfig = TRUE;
                break;
            }
        }

        InstallSignalHandlers();


        LoaderInit();


        LoaderSetPath(xf86ModulePath);

        if (xf86Info.ignoreABI) {
            LoaderSetOptions(LDR_OPT_ABI_MISMATCH_NONFATAL);
        }

        if (xf86DoShowOptions)
            DoShowOptions();

        dbus_core_init();
        systemd_logind_init();


        xf86BusProbe();

        if (xf86DoConfigure)
            DoConfigure();

        if (autoconfig) {
            if (!xf86AutoConfig()) {
                xf86Msg(X_ERROR, "Auto configuration failed\n");
                return;
            }
        }

#ifdef XF86PM
        xf86OSPMClose = xf86OSPMOpen();
#endif

        xf86ExtensionInit();


        if ((modulelist = xf86ModulelistFromConfig(&optionlist))) {
            xf86LoadModules(modulelist, optionlist);
            free(modulelist);
            free(optionlist);
        }


        configured_device = xf86ConfigLayout.screens->screen->device;
        if ((!configured_device) || (!configured_device->driver)) {
            if (!autoConfigDevice(configured_device)) {
                xf86Msg(X_ERROR, "Automatic driver configuration failed\n");
                return;
            }
        }
        if ((modulelist = xf86DriverlistFromConfig())) {
            xf86LoadModules(modulelist, NULL);
            free(modulelist);
        }


        if ((modulelist = xf86InputDriverlistFromConfig())) {
            xf86LoadModules(modulelist, NULL);
            free(modulelist);
        }


        if (xf86NumDrivers == 0) {
            xf86Msg(X_ERROR, "No drivers available.\n");
            return;
        }


        for (i = 0; i < xf86NumDrivers; i++) {
            xorgHWFlags flags = HW_IO;

            if (xf86DriverList[i]->Identify != NULL)
                xf86DriverList[i]->Identify(0);

            if (xf86DriverList[i]->driverFunc)
                xf86DriverList[i]->driverFunc(NULL,
                                              GET_REQUIRED_HW_INTERFACES,
                                              &flags);

            if (NEED_IO_ENABLED(flags))
                want_hw_access = TRUE;


            if (!(flags & HW_SKIP_CONSOLE) && !ServerIsNotSeat0())
                xorgHWOpenConsole = TRUE;
        }

        if (xorgHWOpenConsole)
            xf86OpenConsole();
        else
            xf86Info.dontVTSwitch = TRUE;


	if (want_hw_access)
	    xorgHWAccess = xf86EnableIO();

        if (xf86BusConfig() == FALSE)
            return;

        xf86PostProbe();


        for (j = 0; j < xf86NumScreens - 1; j++) {
            for (i = 0; i < xf86NumScreens - j - 1; i++) {
                if (xf86Screens[i + 1]->confScreen->screennum <
                    xf86Screens[i]->confScreen->screennum) {
                    ScrnInfoPtr tmpScrn = xf86Screens[i + 1];

                    xf86Screens[i + 1] = xf86Screens[i];
                    xf86Screens[i] = tmpScrn;
                }
            }
        }

        for (i = 0; i < xf86NumScreens; i++) {
            xf86Screens[i]->scrnIndex = i;
        }


        for (i = 0; i < xf86NumScreens; i++) {
            xf86VGAarbiterScrnInit(xf86Screens[i]);
            xf86VGAarbiterLock(xf86Screens[i]);
            if (xf86Screens[i]->PreInit &&
                xf86Screens[i]->PreInit(xf86Screens[i], 0))
                xf86Screens[i]->configured = TRUE;
            xf86VGAarbiterUnlock(xf86Screens[i]);
        }
        for (i = 0; i < xf86NumScreens; i++)
            if (!xf86Screens[i]->configured)
                xf86DeleteScreen(xf86Screens[i--]);

        for (i = 0; i < xf86NumGPUScreens; i++) {
            xf86VGAarbiterScrnInit(xf86GPUScreens[i]);
            xf86VGAarbiterLock(xf86GPUScreens[i]);
            if (xf86GPUScreens[i]->PreInit &&
                xf86GPUScreens[i]->PreInit(xf86GPUScreens[i], 0))
                xf86GPUScreens[i]->configured = TRUE;
            xf86VGAarbiterUnlock(xf86GPUScreens[i]);
        }
        for (i = 0; i < xf86NumGPUScreens; i++)
            if (!xf86GPUScreens[i]->configured)
                xf86DeleteScreen(xf86GPUScreens[i--]);


        if (xf86NumScreens == 0) {
            xf86Msg(X_ERROR,
                    "Screen(s) found, but none have a usable configuration.\n");
            return;
        }

        for (i = 0; i < xf86NumScreens; i++) {
            if (xf86Screens[i]->name == NULL) {
                char *tmp;
                XNFasprintf(&tmp, "screen%d", i);
                xf86Screens[i]->name = tmp;
                xf86MsgVerb(X_WARNING, 0,
                            "Screen driver %d has no name set, using `%s'.\n",
                            i, xf86Screens[i]->name);
            }
        }


        for (i = 0; i < xf86NumDrivers; i++)
            if (xf86DriverList[i] && xf86DriverList[i]->refCount <= 0)
                xf86DeleteDriver(i);


        for (i = 0; i < xf86NumScreens; i++)
            xf86InitViewport(xf86Screens[i]);


        screenpix24 = Pix24DontCare;
        for (i = 0; i < xf86NumScreens; i++) {
            if (xf86Screens[i]->imageByteOrder !=
                xf86Screens[0]->imageByteOrder)
                FatalError("Inconsistent display bitmapBitOrder.  Exiting\n");
            if (xf86Screens[i]->bitmapScanlinePad !=
                xf86Screens[0]->bitmapScanlinePad)
                FatalError
                    ("Inconsistent display bitmapScanlinePad.  Exiting\n");
            if (xf86Screens[i]->bitmapScanlineUnit !=
                xf86Screens[0]->bitmapScanlineUnit)
                FatalError
                    ("Inconsistent display bitmapScanlineUnit.  Exiting\n");
            if (xf86Screens[i]->bitmapBitOrder !=
                xf86Screens[0]->bitmapBitOrder)
                FatalError("Inconsistent display bitmapBitOrder.  Exiting\n");


            if (xf86Screens[i]->pixmap24 != Pix24DontCare) {
                if (screenpix24 == Pix24DontCare)
                    screenpix24 = xf86Screens[i]->pixmap24;
                else if (screenpix24 != xf86Screens[i]->pixmap24)
                    FatalError
                        ("Inconsistent depth 24 pixmap format.  Exiting\n");
            }
        }

        if (xf86Info.pixmap24 != Pix24DontCare) {
            pix24 = xf86Info.pixmap24;
            pix24From = xf86Info.pix24From;
            if (screenpix24 != Pix24DontCare &&
                screenpix24 != xf86Info.pixmap24)
                pix24Fail = TRUE;
        }
        else if (screenpix24 != Pix24DontCare) {
            pix24 = screenpix24;
            pix24From = X_PROBED;
        }
        else
            pix24 = Pix24Use32;

        if (pix24Fail)
            FatalError("Screen(s) can't use the required depth 24 pixmap format"
                       " (%d).  Exiting\n", PIX24TOBPP(pix24));


        for (j = 0; j < numFormats && formats[j].depth != 24; j++);
        formats[j].bitsPerPixel = PIX24TOBPP(pix24);


        for (i = 0; i < xf86NumScreens; i++) {
            for (j = 0; j < xf86Screens[i]->numFormats; j++) {
                for (k = 0;; k++) {
                    if (k >= numFormats) {
                        if (k >= MAXFORMATS)
                            FatalError("Too many pixmap formats!  Exiting\n");
                        formats[k] = xf86Screens[i]->formats[j];
                        numFormats++;
                        break;
                    }
                    if (formats[k].depth == xf86Screens[i]->formats[j].depth) {
                        if ((formats[k].bitsPerPixel ==
                             xf86Screens[i]->formats[j].bitsPerPixel) &&
                            (formats[k].scanlinePad ==
                             xf86Screens[i]->formats[j].scanlinePad))
                            break;
                        FatalError("Inconsistent pixmap format for depth %d."
                                   "  Exiting\n", formats[k].depth);
                    }
                }
            }
        }
        formatsDone = TRUE;


        for (i = 0; i < xf86NumScreens; i++) {
            if (xf86Screens[i]->depth == 24) {
                xf86Msg(pix24From, "Depth 24 pixmap format is %d bpp\n",
                        PIX24TOBPP(pix24));
                break;
            }
        }
    }
    else {


        if (xorgHWOpenConsole)
            xf86OpenConsole();

#ifdef XF86PM


        if (xf86OSPMClose)
            xf86OSPMClose();
        if ((xf86OSPMClose = xf86OSPMOpen()) != NULL)
            xf86MsgVerb(X_INFO, 3, "APM registered successfully\n");
#endif


        if (xorgHWAccess)
            xf86EnableIO();
    }

    if (xf86Info.vtno >= 0)
        AddCallback(&RootWindowFinalizeCallback, AddVTAtoms, NULL);

    if (SeatId)
        AddCallback(&RootWindowFinalizeCallback, AddSeatId, SeatId);


    pScreenInfo->imageByteOrder = xf86Screens[0]->imageByteOrder;
    pScreenInfo->bitmapScanlinePad = xf86Screens[0]->bitmapScanlinePad;
    pScreenInfo->bitmapScanlineUnit = xf86Screens[0]->bitmapScanlineUnit;
    pScreenInfo->bitmapBitOrder = xf86Screens[0]->bitmapBitOrder;
    pScreenInfo->numPixmapFormats = numFormats;
    for (i = 0; i < numFormats; i++)
        pScreenInfo->formats[i] = formats[i];


    if (serverGeneration != 1) {
        xf86Resetting = TRUE;

        if (!xf86VTOwner()) {
#ifdef HAS_USL_VTS
            ioctl(xf86Info.consoleFd, VT_RELDISP, VT_ACKACQ);
#endif
            xf86AccessEnter();
            OsBlockSIGIO();
            sigio_blocked = TRUE;
        }
    }

    for (i = 0; i < xf86NumScreens; i++)
        if (!xf86ColormapAllocatePrivates(xf86Screens[i]))
            FatalError("Cannot register DDX private keys");

    if (!dixRegisterPrivateKey(&xf86ScreenKeyRec, PRIVATE_SCREEN, 0))
        FatalError("Cannot register DDX private keys");

    for (i = 0; i < xf86NumGPUScreens; i++) {
        ScrnInfoPtr pScrn = xf86GPUScreens[i];
        xf86VGAarbiterLock(pScrn);


        pScrn->EnableDisableFBAccess = xf86EnableDisableFBAccess;
#ifdef XFreeXDGA
        pScrn->SetDGAMode = xf86SetDGAMode;
#endif
        pScrn->DPMSSet = NULL;
        pScrn->LoadPalette = NULL;
        pScrn->SetOverscan = NULL;
        pScrn->DriverFunc = NULL;
        pScrn->pScreen = NULL;
        scr_index = AddGPUScreen(pScrn->ScreenInit, argc, argv);
        xf86VGAarbiterUnlock(pScrn);
        if (scr_index == i) {
            dixSetPrivate(&screenInfo.gpuscreens[scr_index]->devPrivates,
                          xf86ScreenKey, xf86GPUScreens[i]);
            pScrn->pScreen = screenInfo.gpuscreens[scr_index];

            pScrn->vtSema = TRUE;
        } else {
            FatalError("AddScreen/ScreenInit failed for gpu driver %d %d\n", i, scr_index);
        }
    }

    for (i = 0; i < xf86NumScreens; i++) {
        xf86VGAarbiterLock(xf86Screens[i]);


        xf86Screens[i]->EnableDisableFBAccess = xf86EnableDisableFBAccess;
#ifdef XFreeXDGA
        xf86Screens[i]->SetDGAMode = xf86SetDGAMode;
#endif
        xf86Screens[i]->DPMSSet = NULL;
        xf86Screens[i]->LoadPalette = NULL;
        xf86Screens[i]->SetOverscan = NULL;
        xf86Screens[i]->DriverFunc = NULL;
        xf86Screens[i]->pScreen = NULL;
        scr_index = AddScreen(xf86Screens[i]->ScreenInit, argc, argv);
        xf86VGAarbiterUnlock(xf86Screens[i]);
        if (scr_index == i) {


            dixSetPrivate(&screenInfo.screens[scr_index]->devPrivates,
                          xf86ScreenKey, xf86Screens[i]);
            xf86Screens[i]->pScreen = screenInfo.screens[scr_index];

            xf86Screens[i]->vtSema = TRUE;
        }
        else {

            FatalError("AddScreen/ScreenInit failed for driver %d\n", i);
        }

        DebugF("InitOutput - xf86Screens[%d]->pScreen = %p\n",
               i, xf86Screens[i]->pScreen);
        DebugF("xf86Screens[%d]->pScreen->CreateWindow = %p\n",
               i, xf86Screens[i]->pScreen->CreateWindow);

        if (PictureGetSubpixelOrder(xf86Screens[i]->pScreen) == SubPixelUnknown) {
            xf86MonPtr DDC = (xf86MonPtr) (xf86Screens[i]->monitor->DDC);

            PictureSetSubpixelOrder(xf86Screens[i]->pScreen,
                                    DDC ?
                                    (DDC->features.input_type ?
                                     SubPixelHorizontalRGB : SubPixelNone) :
                                    SubPixelUnknown);
        }
#ifdef RANDR
        if (!xf86Info.disableRandR)
            xf86RandRInit(screenInfo.screens[scr_index]);
        xf86Msg(xf86Info.randRFrom, "RandR %s\n",
                xf86Info.disableRandR ? "disabled" : "enabled");
#endif
    }

    for (i = 0; i < xf86NumGPUScreens; i++)
        AttachUnboundGPU(xf86Screens[0]->pScreen, xf86GPUScreens[i]->pScreen);

    xf86VGAarbiterWrapFunctions();
    if (sigio_blocked)
        OsReleaseSIGIO();

    xf86InitOrigins();

    xf86Resetting = FALSE;
    xf86Initialising = FALSE;

    RegisterBlockAndWakeupHandlers((BlockHandlerProcPtr) NoopDDA, xf86Wakeup,
                                   NULL);
}
