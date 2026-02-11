atp_tool_list_append_new (ATPToolList *this, const gchar *name, ATPToolStore storage)
{
	ATPUserTool *tool;

	g_return_val_if_fail (this, NULL);


	tool = atp_user_tool_new (this, name, storage);


	if (tool)
	{
		atp_user_tool_append_list (atp_tool_list_last_in_storage (this, storage), tool);
	}

	return tool;
}
