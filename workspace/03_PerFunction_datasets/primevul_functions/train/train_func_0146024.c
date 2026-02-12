parse_cino(buf_T *buf)
{
    char_u	*p;
    char_u	*l;
    char_u	*digits;
    int		n;
    int		divider;
    int		fraction = 0;
    int		sw = (int)get_sw_value(buf);


    buf->b_ind_level = sw;


    buf->b_ind_open_imag = 0;


    buf->b_ind_no_brace = 0;


    buf->b_ind_first_open = 0;


    buf->b_ind_open_extra = 0;


    buf->b_ind_close_extra = 0;


    buf->b_ind_open_left_imag = 0;


    buf->b_ind_jump_label = -1;


    buf->b_ind_case = sw;


    buf->b_ind_case_code = sw;


    buf->b_ind_case_break = 0;


    buf->b_ind_scopedecl = sw;


    buf->b_ind_scopedecl_code = sw;


    buf->b_ind_param = sw;


    buf->b_ind_func_type = sw;


    buf->b_ind_cpp_baseclass = sw;


    buf->b_ind_continuation = sw;


    buf->b_ind_unclosed = sw * 2;


    buf->b_ind_unclosed2 = sw;


    buf->b_ind_unclosed_noignore = 0;


    buf->b_ind_unclosed_wrapped = 0;


    buf->b_ind_unclosed_whiteok = 0;


    buf->b_ind_matching_paren = 0;


    buf->b_ind_paren_prev = 0;


    buf->b_ind_comment = 0;


    buf->b_ind_in_comment = 3;


    buf->b_ind_in_comment2 = 0;


    buf->b_ind_maxparen = 20;


    buf->b_ind_maxcomment = 70;


    buf->b_ind_java = 0;


    buf->b_ind_js = 0;


    buf->b_ind_keep_case_label = 0;


    buf->b_ind_cpp_namespace = 0;


    buf->b_ind_if_for_while = 0;


    buf->b_ind_hash_comment = 0;


    buf->b_ind_cpp_extern_c = 0;


    buf->b_ind_pragma = 0;

    for (p = buf->b_p_cino; *p; )
    {
	l = p++;
	if (*p == '-')
	    ++p;
	digits = p;
	n = getdigits(&p);
	divider = 0;
	if (*p == '.')
	{
	    fraction = atol((char *)++p);
	    while (VIM_ISDIGIT(*p))
	    {
		++p;
		if (divider)
		    divider *= 10;
		else
		    divider = 10;
	    }
	}
	if (*p == 's')
	{
	    if (p == digits)
		n = sw;
	    else
	    {
		n *= sw;
		if (divider)
		    n += (sw * fraction + divider / 2) / divider;
	    }
	    ++p;
	}
	if (l[1] == '-')
	    n = -n;


	switch (*l)
	{
	    case '>': buf->b_ind_level = n; break;
	    case 'e': buf->b_ind_open_imag = n; break;
	    case 'n': buf->b_ind_no_brace = n; break;
	    case 'f': buf->b_ind_first_open = n; break;
	    case '{': buf->b_ind_open_extra = n; break;
	    case '}': buf->b_ind_close_extra = n; break;
	    case '^': buf->b_ind_open_left_imag = n; break;
	    case 'L': buf->b_ind_jump_label = n; break;
	    case ':': buf->b_ind_case = n; break;
	    case '=': buf->b_ind_case_code = n; break;
	    case 'b': buf->b_ind_case_break = n; break;
	    case 'p': buf->b_ind_param = n; break;
	    case 't': buf->b_ind_func_type = n; break;
	    case '/': buf->b_ind_comment = n; break;
	    case 'c': buf->b_ind_in_comment = n; break;
	    case 'C': buf->b_ind_in_comment2 = n; break;
	    case 'i': buf->b_ind_cpp_baseclass = n; break;
	    case '+': buf->b_ind_continuation = n; break;
	    case '(': buf->b_ind_unclosed = n; break;
	    case 'u': buf->b_ind_unclosed2 = n; break;
	    case 'U': buf->b_ind_unclosed_noignore = n; break;
	    case 'W': buf->b_ind_unclosed_wrapped = n; break;
	    case 'w': buf->b_ind_unclosed_whiteok = n; break;
	    case 'm': buf->b_ind_matching_paren = n; break;
	    case 'M': buf->b_ind_paren_prev = n; break;
	    case ')': buf->b_ind_maxparen = n; break;
	    case '*': buf->b_ind_maxcomment = n; break;
	    case 'g': buf->b_ind_scopedecl = n; break;
	    case 'h': buf->b_ind_scopedecl_code = n; break;
	    case 'j': buf->b_ind_java = n; break;
	    case 'J': buf->b_ind_js = n; break;
	    case 'l': buf->b_ind_keep_case_label = n; break;
	    case '#': buf->b_ind_hash_comment = n; break;
	    case 'N': buf->b_ind_cpp_namespace = n; break;
	    case 'k': buf->b_ind_if_for_while = n; break;
	    case 'E': buf->b_ind_cpp_extern_c = n; break;
	    case 'P': buf->b_ind_pragma = n; break;
	}
	if (*p == ',')
	    ++p;
    }
}
