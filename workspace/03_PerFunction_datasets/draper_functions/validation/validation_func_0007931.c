cmd_destruct(CMD_DATA *p_cmd)
{
	if (!p_cmd)
	{
		return RC_INVALID_POINTER;
	}

	if (p_cmd->argv)
	{
		int i;

		for (i = 0; i < p_cmd->argc; ++i)
		{
			if (p_cmd->argv[i])
			{
				free(p_cmd->argv[i]);
			}
		}
		free(p_cmd->argv);
	}

	return RC_OK;
}
