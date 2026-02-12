make_get_fullcmd(char_u *makecmd, char_u *fname)
{
    char_u	*cmd;
    unsigned	len;

    len = (unsigned)STRLEN(p_shq) * 2 + (unsigned)STRLEN(makecmd) + 1;
    if (*p_sp != NUL)
	len += (unsigned)STRLEN(p_sp) + (unsigned)STRLEN(fname) + 3;
    cmd = alloc_id(len, aid_qf_makecmd);
    if (cmd == NULL)
	return NULL;
    sprintf((char *)cmd, "%s%s%s", (char *)p_shq, (char *)makecmd,
							       (char *)p_shq);


    if (*p_sp != NUL)
	append_redir(cmd, len, p_sp, fname);


    if (msg_col == 0)
	msg_didout = FALSE;
    msg_start();
    msg_puts(":!");
    msg_outtrans(cmd);

    return cmd;
}
