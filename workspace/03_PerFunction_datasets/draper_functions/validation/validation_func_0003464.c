repl_cmdline(eap, src, srclen, repl, cmdlinep)
    exarg_T	*eap;
    char_u	*src;
    int		srclen;
    char_u	*repl;
    char_u	**cmdlinep;
{
    int		len;
    int		i;
    char_u	*new_cmdline;


    len = (int)STRLEN(repl);
    i = (int)(src - *cmdlinep) + (int)STRLEN(src + srclen) + len + 3;
    if (eap->nextcmd != NULL)
	i += (int)STRLEN(eap->nextcmd);
    if ((new_cmdline = alloc((unsigned)i)) == NULL)
	return NULL;


    i = (int)(src - *cmdlinep);
    mch_memmove(new_cmdline, *cmdlinep, (size_t)i);

    mch_memmove(new_cmdline + i, repl, (size_t)len);
    i += len;
    STRCPY(new_cmdline + i, src + srclen);
    src = new_cmdline + i;

    if (eap->nextcmd != NULL)
    {
	i = (int)STRLEN(new_cmdline) + 1;
	STRCPY(new_cmdline + i, eap->nextcmd);
	eap->nextcmd = new_cmdline + i;
    }
    eap->cmd = new_cmdline + (eap->cmd - *cmdlinep);
    eap->arg = new_cmdline + (eap->arg - *cmdlinep);
    if (eap->do_ecmd_cmd != NULL && eap->do_ecmd_cmd != dollar_command)
	eap->do_ecmd_cmd = new_cmdline + (eap->do_ecmd_cmd - *cmdlinep);
    vim_free(*cmdlinep);
    *cmdlinep = new_cmdline;

    return src;
}
