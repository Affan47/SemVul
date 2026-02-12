setNLSCatalog(struct J9PortLibrary* portLib, UDATA j2seVersion)
{
	J9StringBuffer *nlsSearchPathBuffer = NULL;
	const char *nlsSearchPaths = NULL;
	PORT_ACCESS_FROM_PORT(portLib);

	if ((j2seVersion & J2SE_SERVICE_RELEASE_MASK) >= J2SE_19) {


		nlsSearchPathBuffer = jvmBufferCat(nlsSearchPathBuffer, jvmBufferData(j9libBuffer));
	} else {


		nlsSearchPathBuffer = jvmBufferCat(nlsSearchPathBuffer, jvmBufferData(j9binBuffer));
	}
	nlsSearchPathBuffer = jvmBufferCat(nlsSearchPathBuffer, DIR_SEPARATOR_STR);
	nlsSearchPaths = jvmBufferData(nlsSearchPathBuffer);

	j9nls_set_catalog(&nlsSearchPaths, 1, "java", "properties");
	free(nlsSearchPathBuffer);
	nlsSearchPathBuffer = NULL;
}
