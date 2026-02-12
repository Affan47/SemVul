usm_store_users(int majorID, int minorID, void *serverarg, void *clientarg)
{


    char           *appname = (char *) clientarg;
    if (appname == NULL) {
        appname = netsnmp_ds_get_string(NETSNMP_DS_LIBRARY_ID,
					NETSNMP_DS_LIB_APPTYPE);
    }


    usm_save_users("usmUser", appname);


    return SNMPERR_SUCCESS;
}
