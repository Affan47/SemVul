spell_add_word(
    char_u	*word,
    int		len,
    int		what,
    int		idx,

    int		undo)
{
    FILE	*fd = NULL;
    buf_T	*buf = NULL;
    int		new_spf = FALSE;
    char_u	*fname;
    char_u	*fnamebuf = NULL;
    char_u	line[MAXWLEN * 2];
    long	fpos, fpos_next = 0;
    int		i;
    char_u	*spf;

    if (!valid_spell_word(word, word + len))
    {
	emsg(_(e_illegal_character_in_word));
	return;
    }

    if (idx == 0)
    {
	if (int_wordlist == NULL)
	{
	    int_wordlist = vim_tempname('s', FALSE);
	    if (int_wordlist == NULL)
		return;
	}
	fname = int_wordlist;
    }
    else
    {

	if (*curwin->w_s->b_p_spf == NUL)
	{
	    init_spellfile();
	    new_spf = TRUE;
	}

	if (*curwin->w_s->b_p_spf == NUL)
	{
	    semsg(_(e_option_str_is_not_set), "spellfile");
	    return;
	}
	fnamebuf = alloc(MAXPATHL);
	if (fnamebuf == NULL)
	    return;

	for (spf = curwin->w_s->b_p_spf, i = 1; *spf != NUL; ++i)
	{
	    copy_option_part(&spf, fnamebuf, MAXPATHL, ",");
	    if (i == idx)
		break;
	    if (*spf == NUL)
	    {
		semsg(_(e_spellfile_does_not_have_nr_entries), idx);
		vim_free(fnamebuf);
		return;
	    }
	}


	buf = buflist_findname_exp(fnamebuf);
	if (buf != NULL && buf->b_ml.ml_mfp == NULL)
	    buf = NULL;
	if (buf != NULL && bufIsChanged(buf))
	{
	    emsg(_(e_file_is_loaded_in_another_buffer));
	    vim_free(fnamebuf);
	    return;
	}

	fname = fnamebuf;
    }

    if (what == SPELL_ADD_BAD || undo)
    {


	fd = mch_fopen((char *)fname, "r");
	if (fd != NULL)
	{
	    while (!vim_fgets(line, MAXWLEN * 2, fd))
	    {
		fpos = fpos_next;
		fpos_next = ftell(fd);
		if (fpos_next < 0)
		    break;
		if (STRNCMP(word, line, len) == 0
			&& (line[len] == '/' || line[len] < ' '))
		{


		    fclose(fd);
		    fd = mch_fopen((char *)fname, "r+");
		    if (fd == NULL)
			break;
		    if (fseek(fd, fpos, SEEK_SET) == 0)
		    {
			fputc('#', fd);
			if (undo)
			{
			    home_replace(NULL, fname, NameBuff, MAXPATHL, TRUE);
			    smsg(_("Word '%.*s' removed from %s"),
							 len, word, NameBuff);
			}
		    }
		    if (fseek(fd, fpos_next, SEEK_SET) != 0)
		    {
			PERROR(_("Seek error in spellfile"));
			break;
		    }
		}
	    }
	    if (fd != NULL)
		fclose(fd);
	}
    }

    if (!undo)
    {
	fd = mch_fopen((char *)fname, "a");
	if (fd == NULL && new_spf)
	{
	    char_u *p;


	    if (!dir_of_file_exists(fname) && (p = gettail_sep(fname)) != fname)
	    {
		int c = *p;


		*p = NUL;
		vim_mkdir(fname, 0755);
		*p = c;
		fd = mch_fopen((char *)fname, "a");
	    }
	}

	if (fd == NULL)
	    semsg(_(e_cant_open_file_str), fname);
	else
	{
	    if (what == SPELL_ADD_BAD)
		fprintf(fd, "%.*s/!\n", len, word);
	    else if (what == SPELL_ADD_RARE)
		fprintf(fd, "%.*s/?\n", len, word);
	    else
		fprintf(fd, "%.*s\n", len, word);
	    fclose(fd);

	    home_replace(NULL, fname, NameBuff, MAXPATHL, TRUE);
	    smsg(_("Word '%.*s' added to %s"), len, word, NameBuff);
	}
    }

    if (fd != NULL)
    {

	mkspell(1, &fname, FALSE, TRUE, TRUE);


	if (buf != NULL)
	    buf_reload(buf, buf->b_orig_mode, FALSE);

	redraw_all_later(UPD_SOME_VALID);
    }
    vim_free(fnamebuf);
}
