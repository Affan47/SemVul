InitInput(int argc, char **argv)
{
    InputInfoPtr *pInfo;
    DeviceIntPtr dev;

    xf86Info.vtRequestsPending = FALSE;


    InputThreadPreInit();

    mieqInit();


    for (pInfo = xf86ConfigLayout.inputs; pInfo && *pInfo; pInfo++) {
        (*pInfo)->options =
            xf86AddNewOption((*pInfo)->options, "driver", (*pInfo)->driver);
        (*pInfo)->options =
            xf86AddNewOption((*pInfo)->options, "identifier", (*pInfo)->name);

        if (NewInputDeviceRequest((*pInfo)->options, NULL, &dev) == BadAlloc)
            break;
    }

    config_init();
}
