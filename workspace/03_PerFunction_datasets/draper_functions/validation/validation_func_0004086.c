CL_ParseServerData (sizebuf_t *msg)
{
	char	*str;
	int		i;

	Com_DPrintf ("Serverdata packet received.\n");


	CL_ClearState ();
	cls.state = ca_connected;


	i = MSG_ReadLong (msg);
	cls.serverProtocol = i;

	cl.servercount = MSG_ReadLong (msg);
	cl.attractloop = MSG_ReadByte (msg);

	if (cl.attractloop) {

	}
	else if (i != PROTOCOL_VERSION_DEFAULT && i != PROTOCOL_VERSION_R1Q2) {
		Com_Error (ERR_DROP, "Server is using unknown protocol %d.", i);
	}


	str = MSG_ReadString (msg);
	Q_strncpyz (cl.gamedir, str, sizeof(cl.gamedir));
	str = cl.gamedir;


	if (!Com_ServerState()) {
		Cvar_SetLatched("game", str);
		if( FS_NeedRestart() ) {
			CL_RestartFilesystem(true);
		}
	}


	cl.playernum = MSG_ReadShort (msg);


	str = MSG_ReadString (msg);

	cl.pmp.strafeHack = false;
	cl.pmp.speedMultiplier = 1;
	cl.pmp.airaccelerate = 0;
	cls.protocolVersion = 0;

	if (cls.serverProtocol == PROTOCOL_VERSION_R1Q2)
	{
		i = MSG_ReadByte(msg);
		if( i ) {
			Com_Printf("'Enhanced' R1Q2 servers are not supported, falling back to protocol 34.\n" );
			CL_Disconnect();
			cls.serverProtocol = PROTOCOL_VERSION_DEFAULT;
			CL_Reconnect_f ();
			return false;
		}
		i = MSG_ReadShort(msg);
		if (i < PROTOCOL_VERSION_R1Q2_MINIMUM || i > PROTOCOL_VERSION_R1Q2_CURRENT)
		{
			if (cl.attractloop)
			{
				if ( i < PROTOCOL_VERSION_R1Q2_MINIMUM )
					Com_Printf("This demo was recorded with an earlier version of the R1Q2 protocol. It may not play back properly.\n");
				else
					Com_Printf("This demo was recorded with a later version of the R1Q2 protocol. It may not play back properly.\n");
			}
			else
			{
				if( i < PROTOCOL_VERSION_R1Q2_MINIMUM ) {
					Com_Printf("Server uses OLDER minor R1Q2 protocol version than minimum supported (%i < %i), falling back to protocol 34.\n", i, PROTOCOL_VERSION_R1Q2_MINIMUM);
					CL_Disconnect();
					cls.serverProtocol = PROTOCOL_VERSION_DEFAULT;
					CL_Reconnect_f ();
					return false;
				}
				Com_Printf("Server uses NEWER minor R1Q2 protocol version (%i > %i), some features will be unavailable.\n", i, PROTOCOL_VERSION_R1Q2_CURRENT);
			}
		}

		if (i >= PROTOCOL_VERSION_R1Q2_STRAFE) {
			MSG_ReadByte(msg);
			cl.pmp.strafeHack = MSG_ReadByte(msg);
		}

		cl.pmp.speedMultiplier = 2;
		cls.protocolVersion = i;
	}


	if (cl.playernum == -1)
	{
		SCR_PlayCinematic (str);
	}
	else
	{

		Com_Printf("\n\n\35\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\37\n\n");
		Com_Printf ("%c%s\n", 2, str);


		cl.refresh_prepped = false;

        if((unsigned)cl.playernum >= MAX_CLIENTS) {
            cl.playernum = ( MAX_CLIENTS - 1 );
        }
	}

	return true;
}
