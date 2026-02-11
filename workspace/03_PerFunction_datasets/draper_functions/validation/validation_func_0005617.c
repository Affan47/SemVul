cmc_config_destroy(CmdCfg *cmc)
{
	if(cmc != NULL)
	{
		cmc_config_unregister(cmc);
		if(cmc->fields != NULL)
		{
			g_list_foreach(cmc->fields, free_field, NULL);
			g_list_free(cmc->fields);
		}
		g_free(cmc);
	}
}
