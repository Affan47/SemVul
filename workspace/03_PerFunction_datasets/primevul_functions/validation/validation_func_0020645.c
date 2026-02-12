check_for_cryptkey(
    char_u	*cryptkey,
    char_u	*ptr,
    long	*sizep,
    off_T	*filesizep,
    int		newfile,
    char_u	*fname,
    int		*did_ask)
{
    int method = crypt_method_nr_from_magic((char *)ptr, *sizep);
    int b_p_ro = curbuf->b_p_ro;

    if (method >= 0)
    {


	curbuf->b_p_ro = TRUE;


	crypt_set_cm_option(curbuf, method);
	if (cryptkey == NULL && !*did_ask)
	{
	    if (*curbuf->b_p_key)
		cryptkey = curbuf->b_p_key;
	    else
	    {


		smsg((char_u *)_(need_key_msg), fname);
		msg_scroll = TRUE;
		crypt_check_method(method);
		cryptkey = crypt_get_key(newfile, FALSE);
		*did_ask = TRUE;


		if (cryptkey != NULL && *cryptkey == NUL)
		{
		    if (cryptkey != curbuf->b_p_key)
			vim_free(cryptkey);
		    cryptkey = NULL;
		}
	    }
	}

	if (cryptkey != NULL)
	{
	    int header_len;

	    curbuf->b_cryptstate = crypt_create_from_header(
						       method, cryptkey, ptr);
	    crypt_set_cm_option(curbuf, method);


	    header_len = crypt_get_header_len(method);
	    if (*sizep <= header_len)

		return NULL;
	    *filesizep += header_len;
	    *sizep -= header_len;
	    mch_memmove(ptr, ptr + header_len, (size_t)*sizep);


	    curbuf->b_p_ro = b_p_ro;
	}
    }


    else if (newfile && *curbuf->b_p_key != NUL && !starting)
	set_option_value((char_u *)"key", 0L, (char_u *)"", OPT_LOCAL);

    return cryptkey;
}
