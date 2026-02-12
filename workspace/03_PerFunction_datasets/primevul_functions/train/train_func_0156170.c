get_lval(
    char_u	*name,
    typval_T	*rettv,
    lval_T	*lp,
    int		unlet,
    int		skip,
    int		flags,
    int		fne_flags)
{
    char_u	*p;
    char_u	*expr_start, *expr_end;
    int		cc;
    dictitem_T	*v;
    typval_T	var1;
    typval_T	var2;
    int		empty1 = FALSE;
    char_u	*key = NULL;
    int		len;
    hashtab_T	*ht = NULL;
    int		quiet = flags & GLV_QUIET;
    int		writing;


    CLEAR_POINTER(lp);

    if (skip || (flags & GLV_COMPILING))
    {

	lp->ll_name = name;
	lp->ll_name_end = find_name_end(name, NULL, NULL,
						      FNE_INCL_BR | fne_flags);
	return lp->ll_name_end;
    }


    p = find_name_end(name, &expr_start, &expr_end, fne_flags);
    lp->ll_name_end = p;
    if (expr_start != NULL)
    {

	if (unlet && !VIM_ISWHITE(*p) && !ends_excmd(*p)
						    && *p != '[' && *p != '.')
	{
	    semsg(_(e_trailing_arg), p);
	    return NULL;
	}

	lp->ll_exp_name = make_expanded_name(name, expr_start, expr_end, p);
	if (lp->ll_exp_name == NULL)
	{


	    if (!aborting() && !quiet)
	    {
		emsg_severe = TRUE;
		semsg(_(e_invarg2), name);
		return NULL;
	    }
	}
	lp->ll_name = lp->ll_exp_name;
    }
    else
    {
	lp->ll_name = name;

	if (in_vim9script())
	{

	    if (p == name + 2 && p[-1] == ':')
	    {
		--p;
		lp->ll_name_end = p;
	    }
	    if (*p == ':')
	    {
		scriptitem_T *si = SCRIPT_ITEM(current_sctx.sc_sid);
		char_u	     *tp = skipwhite(p + 1);

		if (tp == p + 1 && !quiet)
		{
		    semsg(_(e_white_space_required_after_str_str), ":", p);
		    return NULL;
		}


		lp->ll_type = parse_type(&tp, &si->sn_type_list, !quiet);
		if (lp->ll_type == NULL && !quiet)
		    return NULL;
		lp->ll_name_end = tp;
	    }
	}
    }


    if ((*p != '[' && *p != '.') || lp->ll_name == NULL)
	return p;

    if (in_vim9script() && lval_root != NULL)
    {

	lp->ll_tv = lval_root;
	v = NULL;
    }
    else
    {
	cc = *p;
	*p = NUL;

	writing = !(flags & GLV_READ_ONLY);
	v = find_var(lp->ll_name, writing ? &ht : NULL,
					 (flags & GLV_NO_AUTOLOAD) || writing);
	if (v == NULL && !quiet)
	    semsg(_(e_undefined_variable_str), lp->ll_name);
	*p = cc;
	if (v == NULL)
	    return NULL;
	lp->ll_tv = &v->di_tv;
    }

    if (in_vim9script() && (flags & GLV_NO_DECL) == 0)
    {
	if (!quiet)
	    semsg(_(e_variable_already_declared), lp->ll_name);
	return NULL;
    }


    var1.v_type = VAR_UNKNOWN;
    var2.v_type = VAR_UNKNOWN;
    while (*p == '[' || (*p == '.' && p[1] != '=' && p[1] != '.'))
    {
	if (*p == '.' && lp->ll_tv->v_type != VAR_DICT)
	{
	    if (!quiet)
		semsg(_(e_dot_can_only_be_used_on_dictionary_str), name);
	    return NULL;
	}
	if (lp->ll_tv->v_type != VAR_LIST
		&& lp->ll_tv->v_type != VAR_DICT
		&& lp->ll_tv->v_type != VAR_BLOB)
	{
	    if (!quiet)
		emsg(_("E689: Can only index a List, Dictionary or Blob"));
	    return NULL;
	}


	if (lp->ll_tv->v_type == VAR_LIST && lp->ll_tv->vval.v_list == NULL)
	    rettv_list_alloc(lp->ll_tv);
	else if (lp->ll_tv->v_type == VAR_BLOB
					     && lp->ll_tv->vval.v_blob == NULL)
	    rettv_blob_alloc(lp->ll_tv);

	if (lp->ll_range)
	{
	    if (!quiet)
		emsg(_("E708: [:] must come last"));
	    return NULL;
	}

	if (in_vim9script() && lp->ll_valtype == NULL
		&& v != NULL
		&& lp->ll_tv == &v->di_tv
		&& ht != NULL && ht == get_script_local_ht())
	{
	    svar_T  *sv = find_typval_in_script(lp->ll_tv);


	    if (sv != NULL)
		lp->ll_valtype = sv->sv_type;
	}

	len = -1;
	if (*p == '.')
	{
	    key = p + 1;
	    for (len = 0; ASCII_ISALNUM(key[len]) || key[len] == '_'; ++len)
		;
	    if (len == 0)
	    {
		if (!quiet)
		    emsg(_(e_emptykey));
		return NULL;
	    }
	    p = key + len;
	}
	else
	{

	    p = skipwhite(p + 1);
	    if (*p == ':')
		empty1 = TRUE;
	    else
	    {
		empty1 = FALSE;
		if (eval1(&p, &var1, &EVALARG_EVALUATE) == FAIL)
		    return NULL;
		if (tv_get_string_chk(&var1) == NULL)
		{

		    clear_tv(&var1);
		    return NULL;
		}
		p = skipwhite(p);
	    }


	    if (*p == ':')
	    {
		if (lp->ll_tv->v_type == VAR_DICT)
		{
		    if (!quiet)
			emsg(_(e_cannot_slice_dictionary));
		    clear_tv(&var1);
		    return NULL;
		}
		if (rettv != NULL
			&& !(rettv->v_type == VAR_LIST
						 && rettv->vval.v_list != NULL)
			&& !(rettv->v_type == VAR_BLOB
						&& rettv->vval.v_blob != NULL))
		{
		    if (!quiet)
			emsg(_("E709: [:] requires a List or Blob value"));
		    clear_tv(&var1);
		    return NULL;
		}
		p = skipwhite(p + 1);
		if (*p == ']')
		    lp->ll_empty2 = TRUE;
		else
		{
		    lp->ll_empty2 = FALSE;

		    if (eval1(&p, &var2, &EVALARG_EVALUATE) == FAIL)
		    {
			clear_tv(&var1);
			return NULL;
		    }
		    if (tv_get_string_chk(&var2) == NULL)
		    {

			clear_tv(&var1);
			clear_tv(&var2);
			return NULL;
		    }
		}
		lp->ll_range = TRUE;
	    }
	    else
		lp->ll_range = FALSE;

	    if (*p != ']')
	    {
		if (!quiet)
		    emsg(_(e_missing_closing_square_brace));
		clear_tv(&var1);
		clear_tv(&var2);
		return NULL;
	    }


	    ++p;
	}

	if (lp->ll_tv->v_type == VAR_DICT)
	{
	    if (len == -1)
	    {

		key = tv_get_string_chk(&var1);
		if (key == NULL)
		{
		    clear_tv(&var1);
		    return NULL;
		}
	    }
	    lp->ll_list = NULL;


	    if (lp->ll_tv->vval.v_dict == NULL)
	    {
		lp->ll_tv->vval.v_dict = dict_alloc();
		if (lp->ll_tv->vval.v_dict == NULL)
		{
		    clear_tv(&var1);
		    return NULL;
		}
		++lp->ll_tv->vval.v_dict->dv_refcount;
	    }
	    lp->ll_dict = lp->ll_tv->vval.v_dict;

	    lp->ll_di = dict_find(lp->ll_dict, key, len);


	    if (rettv != NULL && lp->ll_dict->dv_scope != 0)
	    {
		int prevval;
		int wrong;

		if (len != -1)
		{
		    prevval = key[len];
		    key[len] = NUL;
		}
		else
		    prevval = 0;
		wrong = (lp->ll_dict->dv_scope == VAR_DEF_SCOPE
			       && rettv->v_type == VAR_FUNC
			       && var_wrong_func_name(key, lp->ll_di == NULL))
			|| !valid_varname(key, -1, TRUE);
		if (len != -1)
		    key[len] = prevval;
		if (wrong)
		{
		    clear_tv(&var1);
		    return NULL;
		}
	    }

	    if (lp->ll_valtype != NULL)

		lp->ll_valtype = lp->ll_valtype->tt_member;

	    if (lp->ll_di == NULL)
	    {

		if (lp->ll_dict == get_vimvar_dict()
			 || &lp->ll_dict->dv_hashtab == get_funccal_args_ht())
		{
		    semsg(_(e_illvar), name);
		    clear_tv(&var1);
		    return NULL;
		}


		if (*p == '[' || *p == '.' || unlet)
		{
		    if (!quiet)
			semsg(_(e_dictkey), key);
		    clear_tv(&var1);
		    return NULL;
		}
		if (len == -1)
		    lp->ll_newkey = vim_strsave(key);
		else
		    lp->ll_newkey = vim_strnsave(key, len);
		clear_tv(&var1);
		if (lp->ll_newkey == NULL)
		    p = NULL;
		break;
	    }

	    else if ((flags & GLV_READ_ONLY) == 0
			&& (var_check_ro(lp->ll_di->di_flags, name, FALSE)
			  || var_check_lock(lp->ll_di->di_flags, name, FALSE)))
	    {
		clear_tv(&var1);
		return NULL;
	    }

	    clear_tv(&var1);
	    lp->ll_tv = &lp->ll_di->di_tv;
	}
	else if (lp->ll_tv->v_type == VAR_BLOB)
	{
	    long bloblen = blob_len(lp->ll_tv->vval.v_blob);


	    if (empty1)
		lp->ll_n1 = 0;
	    else

		lp->ll_n1 = (long)tv_get_number(&var1);
	    clear_tv(&var1);

	    if (check_blob_index(bloblen, lp->ll_n1, quiet) == FAIL)
	    {
		clear_tv(&var2);
		return NULL;
	    }
	    if (lp->ll_range && !lp->ll_empty2)
	    {
		lp->ll_n2 = (long)tv_get_number(&var2);
		clear_tv(&var2);
		if (check_blob_range(bloblen, lp->ll_n1, lp->ll_n2, quiet)
								       == FAIL)
		    return NULL;
	    }
	    lp->ll_blob = lp->ll_tv->vval.v_blob;
	    lp->ll_tv = NULL;
	    break;
	}
	else
	{


	    if (empty1)
		lp->ll_n1 = 0;
	    else

		lp->ll_n1 = (long)tv_get_number(&var1);
	    clear_tv(&var1);

	    lp->ll_dict = NULL;
	    lp->ll_list = lp->ll_tv->vval.v_list;
	    lp->ll_li = check_range_index_one(lp->ll_list, &lp->ll_n1, quiet);
	    if (lp->ll_li == NULL)
	    {
		clear_tv(&var2);
		return NULL;
	    }

	    if (lp->ll_valtype != NULL)

		lp->ll_valtype = lp->ll_valtype->tt_member;


	    if (lp->ll_range && !lp->ll_empty2)
	    {
		lp->ll_n2 = (long)tv_get_number(&var2);

		clear_tv(&var2);
		if (check_range_index_two(lp->ll_list,
					    &lp->ll_n1, lp->ll_li,
					    &lp->ll_n2, quiet) == FAIL)
		    return NULL;
	    }

	    lp->ll_tv = &lp->ll_li->li_tv;
	}
    }

    clear_tv(&var1);
    lp->ll_name_end = p;
    return p;
}
