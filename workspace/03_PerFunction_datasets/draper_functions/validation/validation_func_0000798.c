PF_centerprintf (edict_t *ent, char *fmt, ...)
{
	char		msg[1024];
	va_list		argptr;
	int			n;

	if (!ent)
	{
		Com_Printf ("WARNING: PF_centerprintf to NULL ent, ignored\n");
		return;
	}

	n = NUM_FOR_EDICT(ent);
	if (n < 1 || n > maxclients->integer)
		return;

	va_start (argptr,fmt);
	vsnprintf(msg, sizeof(msg), fmt, argptr);
	va_end (argptr);

	MSG_WriteByte (&sv.multicast,svc_centerprint);
	MSG_WriteString (&sv.multicast,msg);
	PF_Unicast (ent, true);
}
