Print_Cmd_Output( int sock )
{
	char String[LONG_STRING_SIZE] = "";


	if (feof(sockets[sock].fp))
	{
		KillCommand(sock);
		return -1;
	}

	fgets(String,LONG_STRING_SIZE,sockets[sock].fp);

	if (!feof(sockets[sock].fp) || String[0])
		print_msg(PRT_PROG_OUT,"%s\n",String);

	return 0;
}
