Comp_Continue(progfuncs_t *progfuncs)
{
	qccprogfuncs = progfuncs;
	if (setjmp(qcccompileerror))
	{
		PostCompile();
		if (*errorfile && externs->useeditor)
			externs->useeditor(progfuncs, errorfile, errorline, comp_nump, comp_parms);
		return false;
	}

	if (qcc_compileactive)
		QCC_ContinueCompile();
	else
	{
		PostCompile();

		if (*errorfile && externs->useeditor)
			externs->useeditor(progfuncs, errorfile, errorline, comp_nump, comp_parms);

		return false;
	}

	return true;
}
