upsc_getbaseinfo(void)
{
	char *buf;

	dstate_setinfo("ups.mfr", "%s",
		((buf = getval("manufacturer")) != NULL) ? buf : "unknown");

	if (!upsc_getvalue("UPTP", NULL, "NNAME", "ups.model", NULL))
		upsc_getvalue("UPTP", NULL, "NNAME", "ups.model", NULL);
	upsc_getvalue("UPSN", "0", "ACSN", "ups.serial", NULL);
}
