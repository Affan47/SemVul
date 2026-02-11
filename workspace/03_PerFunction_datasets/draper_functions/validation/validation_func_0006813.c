InitParameters()

{

    extern int FineVPonBottom;
    extern char InitScreenMode;

    Parameters.kpCellName = malloc(80);
    if (Parameters.kpCellName == NULL) {
        CDStatusInt = CDMALLOCFAILED;
        MallocFailed();
    }
    Parameters.kpTopName = malloc(80);
    if (Parameters.kpTopName == NULL) {
        CDStatusInt = CDMALLOCFAILED;
        MallocFailed();
    }
    Parameters.kpCommand = malloc(80);
    if (Parameters.kpCommand == NULL) {
        CDStatusInt = CDMALLOCFAILED;
        MallocFailed();
    }
    Parameters.kpTopDesc                  = NULL;
    Parameters.kpCellDesc                 = NULL;
    Parameters.kpShowContext              = True;
    Parameters.kpLayer                    = 1;
    Parameters.kp45s                      = False;
    Parameters.kpStretchType              = STR_TBRL;
    Parameters.kpEnableSelectQRedisplay   = True;
    Parameters.kpLayerSpecificSelection   = False;
    Parameters.kpClipVerticesToGrid       = False;
    Parameters.kpExpandInstances          = False;
    Parameters.kpShowInstanceMarkers      = False;
    Parameters.kpRotationAngle            = 0;
    Parameters.kpWindowStack              = NULL;
    Parameters.kpSelectTypes[0]           = CDSYMBOLCALL;
    Parameters.kpSelectTypes[1]           = CDPOLYGON;
    Parameters.kpSelectTypes[2]           = CDROUNDFLASH;
    Parameters.kpSelectTypes[3]           = CDLABEL;
    Parameters.kpSelectTypes[4]           = CDWIRE;
    Parameters.kpSelectTypes[5]           = CDBOX;
    Parameters.kpSelectTypes[6]           = EOS;
    Parameters.kpNumX                     = 1;
    Parameters.kpNumY                     = 1;
    Parameters.kpDX                       = 0;
    Parameters.kpDY                       = 0;


    Parameters.kpPointingThreshold = 6;

    Parameters.kpShowBandwidth = False;

    KicCursor.kcX = KicCursor.kcPredX = 0;
    KicCursor.kcY = KicCursor.kcPredY = 0;

    Parameters.kpModified = False;

    View = alloc(kv);
    View->kvFineWindow = alloc(ka);
    View->kvFineViewport = alloc(ka);
    View->kvLargeCoarseViewport = alloc(ka);
    View->kvSmallCoarseViewport = alloc(ka);
    View->kvCoarseWindow = alloc(ka);
    View->kvFineViewportOnBottom = FineVPonBottom;


    View->kvControl = InitScreenMode;

    TInit();
    TStore();
    InitViewport();
    DefaultWindows();
    SQInit();
}
