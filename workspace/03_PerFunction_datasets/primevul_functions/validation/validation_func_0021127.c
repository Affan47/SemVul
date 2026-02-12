sug_write(spellinfo_T *spin, char_u *fname)
{
    FILE	*fd;
    wordnode_T	*tree;
    int		nodecount;
    int		wcount;
    char_u	*line;
    linenr_T	lnum;
    int		len;


    fd = mch_fopen((char *)fname, "w");
    if (fd == NULL)
    {
	EMSG2(_(e_notopen), fname);
	return;
    }

    vim_snprintf((char *)IObuff, IOSIZE,
				  _("Writing suggestion file %s ..."), fname);
    spell_message(spin, IObuff);


    if (fwrite(VIMSUGMAGIC, VIMSUGMAGICL, (size_t)1, fd) != 1)
    {
	EMSG(_(e_write));
	goto theend;
    }
    putc(VIMSUGVERSION, fd);


    put_time(fd, spin->si_sugtime);


    spin->si_memtot = 0;
    tree = spin->si_foldroot->wn_sibling;


    clear_node(tree);


    nodecount = put_node(NULL, tree, 0, 0, FALSE);


    put_bytes(fd, (long_u)nodecount, 4);
    spin->si_memtot += nodecount + nodecount * sizeof(int);


    (void)put_node(fd, tree, 0, 0, FALSE);


    wcount = spin->si_spellbuf->b_ml.ml_line_count;
    put_bytes(fd, (long_u)wcount, 4);

    for (lnum = 1; lnum <= (linenr_T)wcount; ++lnum)
    {

	line = ml_get_buf(spin->si_spellbuf, lnum, FALSE);
	len = (int)STRLEN(line) + 1;
	if (fwrite(line, (size_t)len, (size_t)1, fd) == 0)
	{
	    EMSG(_(e_write));
	    goto theend;
	}
	spin->si_memtot += len;
    }


    if (putc(0, fd) == EOF)
	EMSG(_(e_write));

    vim_snprintf((char *)IObuff, IOSIZE,
		 _("Estimated runtime memory use: %d bytes"), spin->si_memtot);
    spell_message(spin, IObuff);

theend:

    fclose(fd);
}
