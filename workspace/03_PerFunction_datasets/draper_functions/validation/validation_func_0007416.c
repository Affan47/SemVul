NsDbLoadDriver(char *driver)
{
    Tcl_HashEntry  *hPtr;
    char           *module, *path;
    int             new;
    DbDriver	   *driverPtr;
    static int 	    initialized = NS_FALSE;

    if (initialized == NS_FALSE) {
	Tcl_InitHashTable(&driversTable, TCL_STRING_KEYS);
	initialized = NS_TRUE;
    }

    hPtr = Tcl_CreateHashEntry(&driversTable, driver, &new);
    if (new == 0) {
	driverPtr = (DbDriver *) Tcl_GetHashValue(hPtr);
    } else {
	driverPtr = ns_malloc(sizeof(DbDriver));
	memset(driverPtr, 0, sizeof(DbDriver));
	driverPtr->name = Tcl_GetHashKey(&driversTable, hPtr);
        Tcl_SetHashValue(hPtr, driverPtr);
        module = Ns_ConfigGetValue("ns/db/drivers", driver);
        if (module == NULL) {
	    Ns_Log(Error, "dbdrv: no such driver '%s'", driver);
	} else {
	    path = Ns_ConfigGetPath(NULL, NULL, "db", "driver", driver, NULL);
            if (Ns_ModuleLoad(driver, path, module, "Ns_DbDriverInit")
		    != NS_OK) {
		Ns_Log(Error, "dbdrv: failed to load driver '%s'",
		       driver);
            }
        }
    }
    if (driverPtr->registered == 0) {
	return NULL;
    }

    return driverPtr;
}
