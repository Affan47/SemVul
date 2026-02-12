DriverWriterFromObj( Tcl_Interp *interp, Tcl_Obj *driverObj, Ns_Conn *conn, DrvWriter **wrPtrPtr) {
    Driver       *drvPtr;
    const char   *driverName = NULL;
    int           driverNameLen = 0;
    DrvWriter    *wrPtr = NULL;
    Ns_ReturnCode result;


    if (driverObj == NULL) {
        if (conn != NULL) {
            driverName = Ns_ConnDriverName(conn);
            driverNameLen = (int)strlen(driverName);
        }
    } else {
        driverName = Tcl_GetStringFromObj(driverObj, &driverNameLen);
    }

    if (driverName != NULL) {

        for (drvPtr = firstDrvPtr; drvPtr != NULL; drvPtr = drvPtr->nextPtr) {
            if (strncmp(driverName, drvPtr->threadName, (size_t)driverNameLen) == 0) {
                if (drvPtr->writer.firstPtr != NULL) {
                    wrPtr = &drvPtr->writer;
                }
                break;
            }
        }
    }
    if (unlikely(wrPtr == NULL)) {
        Ns_TclPrintfResult(interp, "no writer configured for a driver with name %s",
                           driverName);
        result = NS_ERROR;
    } else {
        *wrPtrPtr = wrPtr;
        result = NS_OK;
    }

    return result;
}
