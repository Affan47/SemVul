CL_ParseTaunt( char *s)
{
	int l, j;
	char tauntsound[MAX_OSPATH];


	strcpy( scr_playericon, COM_Parse( &s ) );
	l = strlen(scr_playericon);

	for (j=0 ; j<l ; j++)
		scr_playericon[j] = tolower(scr_playericon[j]);

	Com_sprintf(scr_playericon, sizeof(scr_playericon), "%s_i", scr_playericon);

	strcpy( tauntsound, COM_Parse( &s ) );

	Q_strncpyz2( scr_playername, COM_Parse( &s ), sizeof(scr_playername) );

	if(cl_playtaunts->value)
	{
		S_StartSound (NULL, 0, 0, S_RegisterSound (tauntsound), 1, ATTN_NONE, 0);
		scr_playericonalpha = 2.0;
	}

}
