ex_delfunction(exarg_T *eap)
{
    ufunc_T	*fp = NULL;
    char_u	*p;
    char_u	*name;
    funcdict_T	fudi;
    int		is_global = FALSE;

    p = eap->arg;
    name = trans_function_name(&p, &is_global, eap->skip, 0, &fudi,
								   NULL, NULL);
    vim_free(fudi.fd_newkey);
    if (name == NULL)
    {
	if (fudi.fd_dict != NULL && !eap->skip)
	    emsg(_(e_funcref));
	return;
    }
    if (!ends_excmd(*skipwhite(p)))
    {
	vim_free(name);
	semsg(_(e_trailing_arg), p);
	return;
    }
    set_nextcmd(eap, p);
    if (eap->nextcmd != NULL)
	*p = NUL;

    if (numbered_function(name) && fudi.fd_dict == NULL)
    {
	if (!eap->skip)
	    semsg(_(e_invarg2), eap->arg);
	vim_free(name);
	return;
    }
    if (!eap->skip)
	fp = find_func(name, is_global, NULL);
    vim_free(name);

    if (!eap->skip)
    {
	if (fp == NULL)
	{
	    if (!eap->forceit)
		semsg(_(e_unknown_function_str), eap->arg);
	    return;
	}
	if (fp->uf_calls > 0)
	{
	    semsg(_(e_cannot_delete_function_str_it_is_in_use), eap->arg);
	    return;
	}
	if (fp->uf_flags & FC_VIM9)
	{
	    semsg(_(e_cannot_delete_vim9_script_function_str), eap->arg);
	    return;
	}

	if (fudi.fd_dict != NULL)
	{


	    dictitem_remove(fudi.fd_dict, fudi.fd_di);
	}
	else
	{


	    if (fp->uf_refcount > (func_name_refcount(fp->uf_name) ? 0 : 1))
	    {


		if (func_remove(fp))
		    fp->uf_refcount--;
	    }
	    else
		func_clear_free(fp, FALSE);
	}
    }
}
