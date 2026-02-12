SockSetServer(Sock *sockPtr)
{
    char    *host;
    Request *reqPtr;
    bool     bad_request = NS_FALSE;
    Driver  *drvPtr;

    NS_NONNULL_ASSERT(sockPtr != NULL);

    reqPtr = sockPtr->reqPtr;
    assert(reqPtr != NULL);

    drvPtr = sockPtr->drvPtr;
    assert(drvPtr != NULL);

    sockPtr->servPtr  = drvPtr->servPtr;
    sockPtr->location = drvPtr->location;

    host = Ns_SetIGet(reqPtr->headers, "Host");
    Ns_Log(DriverDebug, "SockSetServer host '%s' request line '%s'", host, reqPtr->request.line);

    if (unlikely((host == NULL) && (reqPtr->request.version >= 1.1))) {


        Ns_Log(Notice, "request header field \"Host\" is missing in HTTP/1.1 request: \"%s\"\n",
               reqPtr->request.line);
        bad_request = NS_TRUE;
    }

    if (sockPtr->servPtr == NULL) {
        const ServerMap *mapPtr = NULL;

        if (host != NULL) {
            const Tcl_HashEntry *hPtr;
            size_t               hostLength = strlen(host);


            if (host[hostLength] == '.') {
                host[hostLength] = '\0';
            }


            Ns_StrToLower(host);

            hPtr = Tcl_FindHashEntry(&drvPtr->hosts, host);
            Ns_Log(DriverDebug, "SockSetServer driver '%s' host '%s' => %p",
                   drvPtr->moduleName, host, (void*)hPtr);

            if (hPtr != NULL) {


                mapPtr = Tcl_GetHashValue(hPtr);

            } else {


                Ns_Log(DriverDebug,
                       "cannot locate host header content '%s' in virtual hosts "
                       "table of driver '%s', fall back to default '%s'",
                       host, drvPtr->moduleName,
                       drvPtr->defMapPtr->location);

                if (Ns_LogSeverityEnabled(DriverDebug)) {
                    Tcl_HashEntry  *hPtr2;
                    Tcl_HashSearch  search;

                    hPtr2 = Tcl_FirstHashEntry(&drvPtr->hosts, &search);
                    while (hPtr2 != NULL) {
                        Ns_Log(Notice, "... host entry: '%s'\n",
                               (char *)Tcl_GetHashKey(&drvPtr->hosts, hPtr2));
                        hPtr2 = Tcl_NextHashEntry(&search);
                    }
                }
            }
        }
        if (mapPtr == NULL) {


            mapPtr = drvPtr->defMapPtr;
        }
        if (mapPtr != NULL) {
            sockPtr->servPtr  = mapPtr->servPtr;
            sockPtr->location = mapPtr->location;
        }
        if (sockPtr->servPtr == NULL) {
            Ns_Log(Warning, "cannot determine server for request: \"%s\" (host \"%s\")\n",
                   reqPtr->request.line, host);
            bad_request = NS_TRUE;
        }
    }

    if (unlikely(bad_request)) {
        Ns_Log(DriverDebug, "SockSetServer sets method to BAD");
        ns_free((char *)reqPtr->request.method);
        reqPtr->request.method = ns_strdup("BAD");
    }

}
