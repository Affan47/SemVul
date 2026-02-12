void NsDriverMapVirtualServers(void)
{
    Driver *drvPtr;

    for (drvPtr = firstDrvPtr; drvPtr != NULL;  drvPtr = drvPtr->nextPtr) {
        const Ns_Set *lset;
        size_t        j;
        Tcl_DString   ds, *dsPtr = &ds;
        const char   *path, *defserver, *moduleName;

        moduleName = drvPtr->moduleName;
        defserver  = drvPtr->defserver;


        path = Ns_ConfigGetPath(NULL, moduleName, "servers", (char *)0L);
        lset = Ns_ConfigGetSection(path);

        if (lset == NULL || Ns_SetSize(lset) == 0u) {


            if (drvPtr->server == NULL) {


                if (defserver != NULL) {
                    NsServer   *servPtr = NsGetServer(defserver);

                    Tcl_DStringInit(dsPtr);
                    ServerMapEntryAdd(dsPtr, Ns_InfoHostname(), servPtr, drvPtr, NS_TRUE);
                    Tcl_DStringFree(dsPtr);
                    Ns_Log(Notice, "Global driver has no mapping from host to server (section '%s' missing)",
                           moduleName);
                } else {


                    Ns_Fatal("%s: virtual servers configured,"
                             " but '%s' has no defaultserver defined", moduleName, path);
                }
            }

            continue;
        }


        if (defserver == NULL) {
            if (drvPtr->server != NULL) {


                defserver = drvPtr->server;
            } else {


                Ns_Fatal("%s: virtual servers configured,"
                         " but '%s' has no defaultserver defined", moduleName, path);
            }
        }

        assert(defserver != NULL);

        drvPtr->defMapPtr = NULL;

        Ns_DStringInit(dsPtr);
        for (j = 0u; j < Ns_SetSize(lset); ++j) {
            const char *server  = Ns_SetKey(lset, j);
            const char *host    = Ns_SetValue(lset, j);
            NsServer   *servPtr;


            servPtr = NsGetServer(server);
            if (servPtr == NULL) {
                Ns_Log(Error, "%s: no such server: %s", moduleName, server);
            } else {
                char *writableHost, *hostName, *portStart;

                writableHost = ns_strdup(host);
                Ns_HttpParseHost(writableHost, &hostName, &portStart);

                if (portStart == NULL) {
                    Tcl_DString hostDString;


                    if (drvPtr->port == drvPtr->defport) {
                        ServerMapEntryAdd(dsPtr, host, servPtr, drvPtr,
                                          STREQ(defserver, server));
                    }


                    Tcl_DStringInit(&hostDString);
                    Tcl_DStringAppend(&hostDString, host, -1);
                    (void) Ns_DStringPrintf(&hostDString, ":%hu", drvPtr->port);

                    ServerMapEntryAdd(dsPtr, hostDString.string, servPtr, drvPtr,
                                      STREQ(defserver, server));

                    Tcl_DStringFree(&hostDString);
                } else {


                    unsigned short providedPort = (unsigned short)strtol(portStart+1, NULL, 10);

                    if (providedPort == drvPtr->port) {
                        ServerMapEntryAdd(dsPtr, host, servPtr, drvPtr,
                                          STREQ(defserver, server));


                        if (providedPort == drvPtr->defport) {
                            ServerMapEntryAdd(dsPtr, hostName, servPtr, drvPtr,
                                              STREQ(defserver, server));
                        }
                    } else {
                        Ns_Log(Warning, "%s: driver is listening on port %hu; "
                               "virtual host entry %s ignored",
                               moduleName, drvPtr->port, host);
                    }
                }
                ns_free(writableHost);
            }
        }
        Ns_DStringFree(dsPtr);

        if (drvPtr->defMapPtr == NULL) {
            fprintf(stderr, "--- Server Map: ---\n");
            Ns_SetPrint(lset);
            Ns_Fatal("%s: default server '%s' not defined in '%s'", moduleName, defserver, path);
        }
    }
}
