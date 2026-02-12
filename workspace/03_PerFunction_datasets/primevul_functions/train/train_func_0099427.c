msg_show_console_dialog(
    char_u	*message,
    char_u	*buttons,
    int		dfltbutton)
{
    int		len = 0;
#define HOTK_LEN (has_mbyte ? MB_MAXBYTES : 1)
    int		lenhotkey = HOTK_LEN;
    char_u	*hotk = NULL;
    char_u	*msgp = NULL;
    char_u	*hotkp = NULL;
    char_u	*r;
    int		copy;
#define HAS_HOTKEY_LEN 30
    char_u	has_hotkey[HAS_HOTKEY_LEN];
    int		first_hotkey = FALSE;
    int		idx;

    has_hotkey[0] = FALSE;


    for (copy = 0; copy <= 1; ++copy)
    {
	r = buttons;
	idx = 0;
	while (*r)
	{
	    if (*r == DLG_BUTTON_SEP)
	    {
		if (copy)
		{
		    *msgp++ = ',';
		    *msgp++ = ' ';


		    if (has_mbyte)
			hotkp += STRLEN(hotkp);
		    else
			++hotkp;
		    hotkp[copy_char(r + 1, hotkp, TRUE)] = NUL;
		    if (dfltbutton)
			--dfltbutton;


		    if (idx < HAS_HOTKEY_LEN - 1 && !has_hotkey[++idx])
			first_hotkey = TRUE;
		}
		else
		{
		    len += 3;
		    lenhotkey += HOTK_LEN;
		    if (idx < HAS_HOTKEY_LEN - 1)
			has_hotkey[++idx] = FALSE;
		}
	    }
	    else if (*r == DLG_HOTKEY_CHAR || first_hotkey)
	    {
		if (*r == DLG_HOTKEY_CHAR)
		    ++r;
		first_hotkey = FALSE;
		if (copy)
		{
		    if (*r == DLG_HOTKEY_CHAR)
			*msgp++ = *r;
		    else
		    {

			*msgp++ = (dfltbutton == 1) ? '[' : '(';
			msgp += copy_char(r, msgp, FALSE);
			*msgp++ = (dfltbutton == 1) ? ']' : ')';


			hotkp[copy_char(r, hotkp, TRUE)] = NUL;
		    }
		}
		else
		{
		    ++len;
		    if (idx < HAS_HOTKEY_LEN - 1)
			has_hotkey[idx] = TRUE;
		}
	    }
	    else
	    {

		if (copy)
		    msgp += copy_char(r, msgp, FALSE);
	    }


	    MB_PTR_ADV(r);
	}

	if (copy)
	{
	    *msgp++ = ':';
	    *msgp++ = ' ';
	    *msgp = NUL;
	}
	else
	{
	    len += (int)(STRLEN(message)
			+ 2
			+ STRLEN(buttons)
			+ 3);
	    lenhotkey++;


	    if (!has_hotkey[0])
	    {
		first_hotkey = TRUE;
		len += 2;
	    }


	    vim_free(confirm_msg);
	    confirm_msg = alloc(len);
	    if (confirm_msg == NULL)
		return NULL;
	    *confirm_msg = NUL;
	    hotk = alloc(lenhotkey);
	    if (hotk == NULL)
		return NULL;

	    *confirm_msg = '\n';
	    STRCPY(confirm_msg + 1, message);

	    msgp = confirm_msg + 1 + STRLEN(message);
	    hotkp = hotk;


	    hotkp[copy_char(buttons, hotkp, TRUE)] = NUL;


	    confirm_msg_tail = msgp;
	    *msgp++ = '\n';
	}
    }

    display_confirm_msg();
    return hotk;
}
