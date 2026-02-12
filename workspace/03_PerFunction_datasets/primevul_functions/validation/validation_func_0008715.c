undo_allowed(void)
{

    if (!curbuf->b_p_ma)
    {
	EMSG(_(e_modifiable));
	return FALSE;
    }

#ifdef HAVE_SANDBOX

    if (sandbox != 0)
    {
	EMSG(_(e_sandbox));
	return FALSE;
    }
#endif


    if (textlock != 0)
    {
	EMSG(_(e_secure));
	return FALSE;
    }

    return TRUE;
}
