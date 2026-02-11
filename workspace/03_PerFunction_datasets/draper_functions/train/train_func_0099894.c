Cbuf_AddText (char *text)
{
	int		l;

	l = strlen (text);

	if (cmd_text.cursize + l >= cmd_text.maxsize)
	{
		Com_Printf ("Cbuf_AddText: overflow! Discarding text: %s\n", text);
		return;
	}
	SZ_Write (&cmd_text, text, l);
}
