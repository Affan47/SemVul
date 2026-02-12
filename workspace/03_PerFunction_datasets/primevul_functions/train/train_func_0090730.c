set_playmode()
{
    if (wizard) {
#ifdef WIZARD
	if (authorize_wizard_mode())
	    Strcpy(plname, "wizard");
	else
#endif
	    wizard = FALSE;

	discover = !wizard;
	iflags.deferred_X = FALSE;
    }

}
