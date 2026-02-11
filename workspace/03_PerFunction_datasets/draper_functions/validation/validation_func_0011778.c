sftkdbCall_ReadSecmodDB(const char *appName, const char *filename,
			const char *dbname, char *params, PRBool rw)
{
    SECStatus rv;

    rv = sftkdbLoad_Legacy(PR_FALSE);
    if (rv != SECSuccess) {
	return NULL;
    }
    if (!legacy_glue_readSecmod) {
	PORT_SetError(SEC_ERROR_LIBRARY_FAILURE);
	return NULL;
    }
    return (*legacy_glue_readSecmod)(appName, filename, dbname, params, rw);
}
