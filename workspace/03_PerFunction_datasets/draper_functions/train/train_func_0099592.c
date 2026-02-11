exec_on_server(parmp)
    mparm_T	*parmp;
{
    if (parmp->serverName_arg == NULL || *parmp->serverName_arg != NUL)
    {
# ifdef WIN32

	serverInitMessaging();
# endif


	if (parmp->serverArg)
	{
	    cmdsrv_main(&parmp->argc, parmp->argv,
				    parmp->serverName_arg, &parmp->serverStr);
# ifdef FEAT_MBYTE
	    parmp->serverStrEnc = vim_strsave(p_enc);
# endif
	}


	parmp->servername = serverMakeName(parmp->serverName_arg,
							      parmp->argv[0]);
# ifdef WIN32
	if (parmp->servername != NULL)
	{
	    serverSetName(parmp->servername);
	    vim_free(parmp->servername);
	}
# endif
    }
}
