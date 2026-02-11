dfuUpdateByReset(void) {
    u8 startState = dfuAppStatus.bState;
    userFirmwareLen = 0;

    if (startState == appDETACH) {
        dfuAppStatus.bState = dfuIDLE;
        dfuAppStatus.bStatus = OK;

        nvicDisableInterrupts();
        usbEnbISR();

    } else if (startState == appIDLE || startState == dfuIDLE) {

    } else {


        dfuAppStatus.bState = dfuIDLE;
        dfuAppStatus.bStatus = OK;

        systemHardReset();
    }
}
