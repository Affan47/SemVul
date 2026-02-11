session_time (PRN *prn)
{
    char timestr[48];
    PRN *myprn = NULL;

    if (prn == NULL) {
	myprn = gretl_print_new(GRETL_PRINT_STDOUT, NULL);
	prn = myprn;
    }

    print_time(timestr);
    pprintf(prn, "%s: %s\n", _("Current session"), timestr);

    if (myprn != NULL) {
	gretl_print_destroy(myprn);
    }
}
