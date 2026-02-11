e2_action_get_with_custom (gchar *taskname, gchar *arg, gchar **use_arg)
{
	if (taskname == NULL)
		return NULL;
	E2_Action *action = e2_action_get (taskname);
	if (action == NULL)
	{
		action = e2_action_get (_A(17));
		if (arg == NULL || *arg == '\0')
			*use_arg = g_strdup (taskname);
		else
			*use_arg = g_strconcat (taskname, " ", arg, NULL);
	}
	else
	{
		if (arg == NULL)
			*use_arg = g_strdup ("");
		else
			*use_arg = g_strdup (arg);
	}
	return action;
}
